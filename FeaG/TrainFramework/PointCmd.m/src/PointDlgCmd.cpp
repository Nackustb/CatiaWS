//=================================================================
// Command / Dialog / UI
//=================================================================
#include "PointDlgCmd.h"
#include "CATApplicationFrame.h"
#include "CATCreateExternalObject.h"
#include "CATDialogState.h"
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
#include "CATDialogAgent.h"
#include "CATPathElementAgent.h"
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

CATCreateClass( PointDlgCmd);


PointDlgCmd::PointDlgCmd() :
  CATStateCommand ("PointDlgCmd", CATDlgEngOneShot, CATCommandModeExclusive) 
  ,_pDlg(NULL)
  , _pEditor(NULL)
  , _pHSO(NULL)
  , _pISO(NULL)
  , _pSelectCurvePathAgent(NULL)
  , _pCurveFieldAgent(NULL)
  , _pModelFieldAgent(NULL)
  , _pOKAgent(NULL)
  , _pAPPLYAgent(NULL)
  , _pCLOSEAgent(NULL)
  , _spSelectCurveObj(NULL_var)
  , _spSelectCurveProduct(NULL_var)
  , _spActiveProduct(NULL_var)
  ,_spSelectedSketch(NULL_var)
  ,_spSelectedCircle2D(NULL_var)
  , _spPointObj(NULL_var)
{
	CATApplicationFrame * pFrame = CATApplicationFrame::GetFrame();

	if (NULL != pFrame)
	{
		CATDialog * pParent = (CATDialog *)pFrame->GetMainWindow();

		if(pParent != NULL)
		{
			_pDlg = new PointDlg();
			_pDlg->Build();			  
		}
	}
	RequestStatusChange (CATCommandMsgRequestExclusiveMode);  	  
}

PointDlgCmd::~PointDlgCmd()
{
   if (_pDlg != NULL) 
	   _pDlg->RequestDelayedDestruction();
}


CATStatusChangeRC PointDlgCmd::Activate( CATCommand * iFromClient, CATNotification * iEvtDat)
{
	if(_pDlg != NULL)
		_pDlg->SetVisibility(CATDlgShow);  // 可视化设置


	return (CATStatusChangeRCCompleted);
}

CATStatusChangeRC PointDlgCmd::Desactivate( CATCommand * iFromClient, CATNotification * iEvtDat)
{
	if(_pDlg != NULL)
		_pDlg->SetVisibility(CATDlgHide);
	return (CATStatusChangeRCCompleted);
}

CATStatusChangeRC PointDlgCmd::Cancel( CATCommand * iFromClient, CATNotification * iEvtDat)
{
	if(_pDlg != NULL)
		_pDlg->SetVisibility(CATDlgHide);
	RequestDelayedDestruction();
	return (CATStatusChangeRCCompleted);
}


void PointDlgCmd::BuildGraph()
{

// SelectCurvePathAgent
	_pSelectCurvePathAgent = new CATPathElementAgent("SelectCircleAgent");
	_pSelectCurvePathAgent->AddElementType(IID_CATISpecObject);

	_pSelectCurvePathAgent->SetBehavior(CATDlgEngWithPSO | CATDlgEngWithPrevaluation);

// OK agent
	_pOKAgent = new CATDialogAgent("ok agent");
	_pOKAgent->AcceptOnNotify(_pDlg, _pDlg->GetDiaOKNotification());
// APPLY agent
	_pAPPLYAgent = new CATDialogAgent("apply agent");
	_pAPPLYAgent->AcceptOnNotify(_pDlg, _pDlg->GetDiaAPPLYNotification());
// CLOSE agent
	_pCLOSEAgent = new CATDialogAgent("close agent");
	_pCLOSEAgent->AcceptOnNotify(_pDlg, _pDlg->GetDiaCLOSENotification());
	_pCLOSEAgent->AcceptOnNotify(_pDlg, _pDlg->GetWindCloseNotification());

	CATDialogState * InitialState = GetInitialState("Initial State");
	InitialState->AddDialogAgent(_pSelectCurvePathAgent);
	InitialState->AddDialogAgent(_pOKAgent);
	InitialState->AddDialogAgent(_pAPPLYAgent);
	InitialState->AddDialogAgent(_pCLOSEAgent);
	
	AddTransition(
	  InitialState,
	  NULL,
	  IsOutputSetCondition(_pOKAgent),
	  Action((ActionMethod)&PointDlgCmd::ActionOK)
	);

	AddTransition(
	  InitialState,
	  NULL,
	  //InitialState,
	  IsOutputSetCondition(_pAPPLYAgent),
	  Action((ActionMethod)&PointDlgCmd::ActionAPPLY)
	);

	AddTransition(
	  InitialState,
	  NULL,
	  IsOutputSetCondition(_pCLOSEAgent),
	  Action((ActionMethod)&PointDlgCmd::ActionCLOSE)
	);

	AddTransition(
		InitialState,
		InitialState, 
		IsOutputSetCondition(_pSelectCurvePathAgent),
		Action((ActionMethod)&PointDlgCmd::ActionSelectCurve)
		);
}

CATBoolean PointDlgCmd::ActionAPPLY(void *data)
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

	_spSelectedSketch->OpenEdition();

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
		::MessageBoxA(NULL, "创建圆心点失败。", "错误", MB_OK);

	return TRUE;
}


CATBoolean PointDlgCmd::ActionCLOSE(void *data)
{
	return TRUE;
}

CATBoolean PointDlgCmd::ActionOK(void *data)
{
	return TRUE;
}


CATBoolean PointDlgCmd::ActionSelectCurve(void *data)
{
	CATPathElement * pPath = _pSelectCurvePathAgent->GetValue();
	if (NULL == pPath) return FALSE;

	CATISketch_var spSketch = pPath->FindElement(IID_CATISketch);
	if (spSketch == NULL_var)
	{
		::MessageBoxA(NULL, "请选择草图内部的圆。", "提示", MB_OK);
		_pSelectCurvePathAgent->InitializeAcquisition();
		return TRUE;
	}

	CATI2DCircle_var spCircle2D = pPath->FindElement(IID_CATI2DCircle);
	if (spCircle2D == NULL_var)
	{
		::MessageBoxA(NULL, "选择的对象不是有效的2D圆。", "提示", MB_OK);
		_pSelectCurvePathAgent->InitializeAcquisition();
		return TRUE;
	}

	_spSelectedSketch = spSketch;
	_spSelectedCircle2D = spCircle2D;

	CATDlgSelectorList* pList = _pDlg->GetSelectorList(1);
	if (pList)
	{
		pList->ClearLine();
		CATUnicodeString name = "2D Circle";
		pList->SetLine(name, -1, CATDlgDataAdd);
		int iRow = 0;
		pList->SetSelect(&iRow, 1, 1);
	}

	_pSelectCurvePathAgent->InitializeAcquisition();
	return TRUE;
}
