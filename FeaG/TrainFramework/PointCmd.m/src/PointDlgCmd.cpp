//=================================================================
// Command / Dialog / UI
//=================================================================
#include "PointDlgCmd.h"
#include "CATApplicationFrame.h"
#include "CATCreateExternalObject.h"
#include "CATDialogState.h"
#include "CATDialogAgent.h"
#include "CATPathElementAgent.h"
#include "CATDlgGridConstraints.h"
#include "CATMsgCatalog.h"
#include "CATUnicodeString.h"
#include <windows.h>

//=================================================================
// Editor / Document / Container
//=================================================================
#include "CATFrmEditor.h"
#include "CATDocument.h"
#include "CATDocumentServices.h"
#include "CATIDocRoots.h"
#include "CATInit.h"
#include "CATIContainerOfDocument.h"
#include "CATIContainer.h"

//=================================================================
// Spec / Model 基础接口
//=================================================================
#include "CATISpecObject.h"
#include "CATILinkableObject.h"
#include "CATIInstance.h"
#include "CATIModelEvents.h"
#include "CATIRedrawEvent.h"
#include "CATModify.h"
#include "CATLISTV_CATISpecObject.h"

//=================================================================
// Sketcher（草图体系）
//=================================================================
#include "CATISketch.h"
#include "CATISketchFactory.h"
#include "CATI2DWFFactory.h"
#include "CATI2DPoint.h"
#include "CATI2DCurve.h"
#include "CATI2DCircle.h"

//=================================================================
// Part Design（零件 / Pad / Prism）
//=================================================================
#include "CATIPrtContainer.h"
#include "CATIPrtFactory.h"
#include "CATIPrtPart.h"
#include "CATIPad.h"
#include "CATLimitDefs.h"

//=================================================================
// GSM / 构造几何
//=================================================================
#include "CATIGSMFactory.h"
#include "CATIGSMPoint.h"
#include "CATIGSMProceduralView.h"
#include "CATIGSMCircle.h"
#include "CATIGSMTool.h"

//=================================================================
// Math（方向 / 向量 / 平面 / 位姿）
//=================================================================
#include "CATMathPoint.h"
#include "CATMathPlane.h"
#include "CATMathVector.h"
#include "CATMathDirection.h"
#include "CATMathTransformation.h"
#include <math.h>

//=================================================================
// Geometry（低层几何实体）
//=================================================================
#include "CATPoint.h"
#include "CATLine.h"
#include "CATCircle.h"
#include "CATConic.h"
#include "CATPlane.h"

//=================================================================
// Product / 属性 / 检索 / 位姿
//=================================================================
#include "CATIProduct.h"
#include "CATIParmPublisher.h"
#include "CATIDescendants.h"
#include "CATIAlias.h"
#include "CATIMovable.h"

CATCreateClass(PointDlgCmd);
PointDlgCmd::PointDlgCmd() :
CATStateCommand("PointDlgCmd", CATDlgEngOneShot, CATCommandModeExclusive)
, _pDlg(NULL)
, _pEditor(NULL)
, _pHSO(NULL)
, _pISO(NULL)
, _pSelectCurvePathAgent(NULL)
, _pCurveFieldAgent(NULL)
, _pModelFieldAgent(NULL)
, _pOKAgent(NULL)
, _pAPPLYAgent(NULL)
, _pCLOSEAgent(NULL)
, _pModeAgent(NULL)
, _spSelectCurveObj(NULL_var)
, _spSelectCurveProduct(NULL_var)
, _spActiveProduct(NULL_var)
, _spSelectedSketch(NULL_var)
, _spSelectedCircle2D(NULL_var)
, _spPointObj(NULL_var)
, _spSelectedCurve2D(NULL_var)

{
	CATApplicationFrame * pFrame = CATApplicationFrame::GetFrame();
	if (pFrame != NULL)
	{
		CATDialog * pParent = (CATDialog *)pFrame->GetMainWindow();
		if (pParent != NULL)
		{
			_pDlg = new PointDlg();
			_pDlg->Build();
		}
	}
	RequestStatusChange(CATCommandMsgRequestExclusiveMode);
}

PointDlgCmd::~PointDlgCmd()
{
	if (_pDlg != NULL)
		_pDlg->RequestDelayedDestruction();
}

//=================================================================
// Command life-cycle
//=================================================================
CATStatusChangeRC PointDlgCmd::Activate(CATCommand * iFromClient, CATNotification * iEvtDat)
{
	if (_pDlg != NULL)
		_pDlg->SetVisibility(CATDlgShow);
	return CATStatusChangeRCCompleted;
}

CATStatusChangeRC PointDlgCmd::Desactivate(CATCommand * iFromClient, CATNotification * iEvtDat)
{
	if (_pDlg != NULL)
		_pDlg->SetVisibility(CATDlgHide);
	return CATStatusChangeRCCompleted;
}

CATStatusChangeRC PointDlgCmd::Cancel(CATCommand * iFromClient, CATNotification * iEvtDat)
{
	if (_pDlg != NULL)
		_pDlg->SetVisibility(CATDlgHide);
	RequestDelayedDestruction();
	return CATStatusChangeRCCompleted;
}

//=================================================================
// State chart
//=================================================================
void PointDlgCmd::BuildGraph()
{
	// -------------------------
	// Selection agent
	// -------------------------
	_pSelectCurvePathAgent = new CATPathElementAgent("SelectCircleAgent");
	_pSelectCurvePathAgent->AddElementType(IID_CATISpecObject);
	_pSelectCurvePathAgent->SetBehavior(CATDlgEngWithPSO | CATDlgEngWithPrevaluation);

	// -------------------------
	// Dialog agents (buttons)
	// -------------------------
	_pOKAgent = new CATDialogAgent("ok agent");
	_pOKAgent->AcceptOnNotify(_pDlg, _pDlg->GetDiaOKNotification());

	_pAPPLYAgent = new CATDialogAgent("apply agent");
	_pAPPLYAgent->AcceptOnNotify(_pDlg, _pDlg->GetDiaAPPLYNotification());

	_pCLOSEAgent = new CATDialogAgent("close agent");
	_pCLOSEAgent->AcceptOnNotify(_pDlg, _pDlg->GetDiaCLOSENotification());
	_pCLOSEAgent->AcceptOnNotify(_pDlg, _pDlg->GetWindCloseNotification());

	// -------------------------
	// Mode agent (Combo005)
	// -------------------------
	_pModeAgent = NULL;

	CATDlgCombo * pCombo = (_pDlg ? _pDlg->GetCombo(1) : NULL);
	CATNotification * pNfy = (_pDlg ? _pDlg->GetCombo005SelectNotification() : NULL);

	// -------------------------
	// Initial state
	// -------------------------
	CATDialogState * InitialState = GetInitialState("Initial State");
	InitialState->AddDialogAgent(_pSelectCurvePathAgent);
	InitialState->AddDialogAgent(_pOKAgent);
	InitialState->AddDialogAgent(_pAPPLYAgent);
	InitialState->AddDialogAgent(_pCLOSEAgent);

	// -------------------------
	// Transitions (buttons)
	// -------------------------
	AddTransition(
		InitialState,
		NULL,
		IsOutputSetCondition(_pOKAgent),
		Action((ActionMethod)&PointDlgCmd::ActionOK)
		);

	AddTransition(
		InitialState,
		NULL,
		IsOutputSetCondition(_pAPPLYAgent),
		Action((ActionMethod)&PointDlgCmd::ActionAPPLY)
		);

	AddTransition(
		InitialState,
		NULL,
		IsOutputSetCondition(_pCLOSEAgent),
		Action((ActionMethod)&PointDlgCmd::ActionCLOSE)
		);

	// -------------------------
	// Transitions (selection)
	// -------------------------
	AddTransition(
		InitialState,
		InitialState,
		IsOutputSetCondition(_pSelectCurvePathAgent),
		Action((ActionMethod)&PointDlgCmd::ActionSelectCurve)
		);

	// -------------------------
	// Transitions (mode change)
	// -------------------------
	if (pCombo != NULL && pNfy != NULL)
	{
		_pModeAgent = new CATDialogAgent("mode agent");
		_pModeAgent->AcceptOnNotify(pCombo, pNfy);
		InitialState->AddDialogAgent(_pModeAgent);

		AddTransition(
			InitialState,
			InitialState,
			IsOutputSetCondition(_pModeAgent),
			Action((ActionMethod)&PointDlgCmd::ActionModeChanged)
			);
	}
}

//=================================================================
// Actions: buttons
//=================================================================
CATBoolean PointDlgCmd::ActionCLOSE(void * data)
{
	return TRUE;
}

CATBoolean PointDlgCmd::ActionAPPLY(void * data)
{
	return ApplyByMode();
}

CATBoolean PointDlgCmd::ActionOK(void * data)
{
	return ApplyByMode();
}

//=================================================================
// Mode dispatch
//=================================================================
CATBoolean PointDlgCmd::ApplyByMode()
{
	const int mode = GetCurrentMode();
	if (mode == kModeCircleCenter)
		return ApplyCircleCenter();
	return ApplyCurveDistance();
}

//=================================================================
// Actions: selection
//=================================================================
CATBoolean PointDlgCmd::ActionSelectCurve(void * data)
{
	CATPathElement * pPath = _pSelectCurvePathAgent->GetValue();
	if (pPath == NULL) return FALSE;

	CATISketch_var spSketch = pPath->FindElement(IID_CATISketch);
	if (spSketch == NULL_var)
	{
		::MessageBoxA(NULL, "请选择草图内的几何。", "提示", MB_OK);
		_pSelectCurvePathAgent->InitializeAcquisition();
		return TRUE;
	}

	const int mode = GetCurrentMode();

	CATUnicodeString showText("Selected");

	if (mode == kModeCircleCenter)
	{
		CATI2DCircle_var spCircle2D = pPath->FindElement(IID_CATI2DCircle);
		if (spCircle2D == NULL_var)
		{
			::MessageBoxA(NULL, "圆心模式：请选择 2D 圆。", "提示", MB_OK);
			_pSelectCurvePathAgent->InitializeAcquisition();
			return TRUE;
		}

		_spSelectedSketch   = spSketch;
		_spSelectedCircle2D = spCircle2D;
		_spSelectedCurve2D  = NULL_var;

		showText = "2D Circle";
	}
	else
	{
		CATI2DCurve_var spCurve2D = pPath->FindElement(IID_CATI2DCurve);
		if (spCurve2D == NULL_var)
		{
			::MessageBoxA(NULL, "曲线距离模式：请选择 2D 曲线。", "提示", MB_OK);
			_pSelectCurvePathAgent->InitializeAcquisition();
			return TRUE;
		}

		_spSelectedSketch   = spSketch;
		_spSelectedCurve2D  = spCurve2D;
		_spSelectedCircle2D = NULL_var;

		showText = "2D Curve";
	}

	if (_pDlg)
	{
		CATDlgSelectorList * pList = _pDlg->GetSelectorList(1); 
		if (pList)
		{
			pList->ClearLine();
			pList->SetLine(showText, -1, CATDlgDataAdd);
			int iRow = 0;
			pList->SetSelect(&iRow, 1, 1);
		}
	}

	_pSelectCurvePathAgent->InitializeAcquisition();
	return TRUE;
}



//=================================================================
// Mode helpers
//=================================================================
int PointDlgCmd::GetCurrentMode() const
{
	if (_pDlg == NULL) return kModeCurveDistance;

	CATDlgCombo * pCombo = _pDlg->GetCombo(1);
	if (pCombo == NULL) return kModeCurveDistance;

	int sel = 0;
	sel = pCombo->GetSelect();
	return sel;
}

CATBoolean PointDlgCmd::ActionModeChanged(void * data)
{
	const int mode = GetCurrentMode();
	CATDlgSpinner * pSpin = _pDlg->GetSpinner(1);
	if (_pDlg)
	{
		CATDlgSelectorList * pList = _pDlg->GetSelectorList(1);
		if (pList)
		{
			pList->ClearLine();
			pList->SetLine(CATUnicodeString("No selection"), -1, CATDlgDataAdd);
		}
	}

	if (pSpin && mode == kModeCircleCenter)

	{

		pSpin->SetValue(0.0); 

	}
	_spSelectedCurve2D = NULL_var;
	_spSelectedSketch = NULL_var;
	_spSelectedCircle2D = NULL_var;

	if (_pSelectCurvePathAgent)
		_pSelectCurvePathAgent->InitializeAcquisition();
	if (_pModeAgent)
		_pModeAgent->InitializeAcquisition();

	return TRUE;
}

//=================================================================
// Mode implementations
//=================================================================
CATBoolean PointDlgCmd::ApplyCircleCenter()
{
	if (_spSelectedSketch == NULL_var || _spSelectedCircle2D == NULL_var)
	{
		::MessageBoxA(NULL, "请先选择一个草图圆。", "提示", MB_OK);
		return TRUE;
	}

	double center[2] = {0.0, 0.0};
	double radius = 0.0;
	HRESULT hr = _spSelectedCircle2D->GetCircleData(center, &radius);
	if (FAILED(hr))
	{
		::MessageBoxA(NULL, "无法获取圆几何数据。", "错误", MB_OK);
		return TRUE;
	}

	HRESULT rc = _spSelectedSketch->OpenEdition();
	if (FAILED(rc))
	{
		::MessageBoxA(NULL, "OpenEdition 失败，无法进入草图编辑。", "错误", MB_OK);
		return TRUE;
	}

	CATI2DWFFactory_var sp2DFactory = _spSelectedSketch;
	if (sp2DFactory == NULL_var)
	{
		_spSelectedSketch->CloseEdition();
		::MessageBoxA(NULL, "无法获取 CATI2DWFFactory。", "错误", MB_OK);
		return TRUE;
	}

	CATI2DPoint_var spCenterPoint = sp2DFactory->CreatePoint(center);

	_spSelectedSketch->CloseEdition();

	if (spCenterPoint == NULL_var)
	{
		::MessageBoxA(NULL, "创建圆心点失败。", "错误", MB_OK);
	}



	return TRUE;
}


CATBoolean PointDlgCmd::ApplyCurveDistance()
{
	if (_spSelectedSketch == NULL_var || _spSelectedCurve2D == NULL_var)
	{
		::MessageBoxA(NULL, "请先选择一个草图 2D 曲线。", "提示", MB_OK);
		return TRUE;
	}

	// 读取距离（保持你现有逻辑：Spinner * 1000）
	double dist = 0.0;
	if (_pDlg)
	{
		CATDlgSpinner * pSpin = _pDlg->GetSpinner(1);
		if (pSpin) dist = pSpin->GetValue();
		dist = dist * 1000.0;
	}

	if (dist < 0.0)
	{
		::MessageBoxA(NULL, "距离参数必须 >= 0。", "提示", MB_OK);
		return TRUE;
	}

	// 取参数范围
	double u0 = 0.0, u1 = 0.0;
	HRESULT hr = _spSelectedCurve2D->GetParamExtents(&u0, &u1);
	if (FAILED(hr))
	{
		::MessageBoxA(NULL, "无法获取曲线参数范围。", "错误", MB_OK);
		return TRUE;
	}

	// 从起点参数 u0 出发，沿曲线逻辑方向走 dist，求目标参数
	double uTarget = u0;
	hr = _spSelectedCurve2D->GetParamAtLength(u0, dist, &uTarget);
	if (FAILED(hr))
	{
		// 常见原因：dist 超过曲线总长或曲线不可计算；此时落到末端参数
		uTarget = u1;
	}

	// 由参数取点（替换掉不存在的 GetPoint）
	double pt[2] = { 0.0, 0.0 };
	hr = _spSelectedCurve2D->GetPointAtParam(uTarget, pt);
	if (FAILED(hr))
	{
		::MessageBoxA(NULL, "曲线取点失败（GetPointAtParam）。", "错误", MB_OK);
		return TRUE;
	}

	// 进入草图编辑并创建 2D 点
	hr = _spSelectedSketch->OpenEdition();
	if (FAILED(hr))
	{
		::MessageBoxA(NULL, "OpenEdition 失败，无法进入草图编辑。", "错误", MB_OK);
		return TRUE;
	}

	CATI2DWFFactory_var sp2DFactory = _spSelectedSketch;
	if (sp2DFactory == NULL_var)
	{
		_spSelectedSketch->CloseEdition();
		::MessageBoxA(NULL, "无法获取 CATI2DWFFactory。", "错误", MB_OK);
		return TRUE;
	}

	CATI2DPoint_var spPt = sp2DFactory->CreatePoint(pt);

	_spSelectedSketch->CloseEdition();

	if (spPt == NULL_var)
	{
		::MessageBoxA(NULL, "创建曲线距离点失败。", "错误", MB_OK);
	}

	return TRUE;
}
