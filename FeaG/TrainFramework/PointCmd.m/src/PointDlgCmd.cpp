#include "PointDlgCmd.h"

#include "CATCreateExternalObject.h"
#include "CATDialogState.h"
#include "CATDialogAgent.h"
#include "CATUnicodeString.h"

#include "CATIndicationAgent.h"
#include "CATFrmEditor.h"
#include "CATDocument.h"
#include "CATIContainerOfDocument.h"
#include "CATIContainer.h"

#include <windows.h>

CATCreateClass(PointDlgCmd);


PointDlgCmd::PointDlgCmd() :
CATStateCommand("PointDlgCmd", CATDlgEngOneShot, CATCommandModeExclusive),
_pDlg(NULL),
_pEditor(NULL),
_pHSO(NULL),
_pISO(NULL),
_pSelectCurvePathAgent(NULL),
_pCurveFieldAgent(NULL),
_pModelFieldAgent(NULL),
_pOKAgent(NULL),
_pAPPLYAgent(NULL),
_pCLOSEAgent(NULL),
_spSelectCurveObj(NULL_var),
_spSelectCurveProduct(NULL_var),
_spActiveProduct(NULL_var),
_spPointObj(NULL_var)
{
	HRESULT rc = E_FAIL;

	// 1、获得Editor、HSO、ISO
	_pEditor = NULL;
	_pEditor = CATFrmEditor::GetCurrentEditor();
	_pHSO = NULL;
	if ( _pEditor == NULL )
	{
		CreateMsgBoxOptError("There is no open file, please open a file");
		RequestDelayedDestruction();
		return;
	}

	_pHSO = _pEditor->GetHSO();
	_pISO = _pEditor->GetISO();
	//2、获得当前的Part
	CATPathElement pUIElem = _pEditor->GetUIActiveObject();

	CATIProduct_var spActiveProduct=NULL_var;
	rc = pUIElem.Search(IID_CATIProduct, (void**)&spActiveProduct);
	if(spActiveProduct==NULL_var)
	{
		CATIPrtPart*pPrtPart=NULL;
		rc = pUIElem.Search(IID_CATIPrtPart, (void**)&pPrtPart);
		if(pPrtPart==NULL)
		{
			RequestDelayedDestruction();
			return;
		}

		CATISpecObject_var spProductObj = pPrtPart->GetProduct();
		if(spProductObj==NULL)
		{
			RequestDelayedDestruction();
			return;
		}
		spActiveProduct =spProductObj;
	}
	if(spActiveProduct==NULL_var)
	{
		RequestDelayedDestruction();
		return;
	}

	if (IsProduct(spActiveProduct))
	{
		CreateMsgBoxOptError("The active object is not a part, please active a part");
		RequestDelayedDestruction();
		return;
	}

	_spActiveProduct=spActiveProduct;
	//3、对话框初始化
	_pDlg = new PointDlg();
	_pDlg->Build();
	_pDlg->SetVisibility(CATDlgShow);
	//4、检查输入是否完整
	CheckInPut();

}

PointDlgCmd::~PointDlgCmd()
{
	if (_pDlg)
		_pDlg->RequestDelayedDestruction();

	if (_pSelectCurvePathAgent) { delete _pSelectCurvePathAgent; _pSelectCurvePathAgent = NULL; }
	if (_pCurveFieldAgent)      { delete _pCurveFieldAgent;      _pCurveFieldAgent = NULL; }
	if (_pModelFieldAgent)      { delete _pModelFieldAgent;      _pModelFieldAgent = NULL; }
	if (_pOKAgent)              { delete _pOKAgent;              _pOKAgent = NULL; }
	if (_pAPPLYAgent)           { delete _pAPPLYAgent;           _pAPPLYAgent = NULL; }
	if (_pCLOSEAgent)           { delete _pCLOSEAgent;           _pCLOSEAgent = NULL; }

	_pEditor = NULL;
	_pHSO = NULL;
	_pISO = NULL;
}


void PointDlgCmd::BuildGraph()
{
	// 元素选择 agent
	_pSelectCurvePathAgent = new CATPathElementAgent("select agent");
	_pSelectCurvePathAgent->SetOrderedElementType("CATIMeasurableCurve"); // 元素选择类型
	_pSelectCurvePathAgent->SetBehavior(CATDlgEngWithPrevaluation | CATDlgEngWithCSO | CATDlgEngWithUndo);
	CATAcquisitionFilter * pSketchFilter = Filter((FilterMethod)&PointDlgCmd::CheckSelectedCurve, (void*)NULL);
	_pSelectCurvePathAgent->SetFilter(pSketchFilter);

	// 单击元素 agent
	_pCurveFieldAgent = new CATDialogAgent("click element agent");
	_pCurveFieldAgent->AcceptOnNotify(_pDlg->GetSelectorList(1), _pDlg->GetSelectorList(1)->GetListSelectNotification());

	// 选项切换模式 agent
	_pModelFieldAgent = new CATDialogAgent("select mode agent");
	_pModelFieldAgent->AcceptOnNotify(_pDlg->GetCombo(1), _pDlg->GetCombo(1)->GetComboSelectNotification());

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

	// 建立初始状态
	CATDialogState * InitialState = GetInitialState("Initial State");
	InitialState->AddDialogAgent(_pSelectCurvePathAgent);
	InitialState->AddDialogAgent(_pCurveFieldAgent);
	InitialState->AddDialogAgent(_pModelFieldAgent);
	InitialState->AddDialogAgent(_pOKAgent);
	InitialState->AddDialogAgent(_pAPPLYAgent);
	InitialState->AddDialogAgent(_pCLOSEAgent);


	AddTransition(InitialState, InitialState,
		IsOutputSetCondition(_pSelectCurvePathAgent),
		Action((ActionMethod)&PointDlgCmd::SelectCurve));
	AddTransition(InitialState, InitialState,
		IsOutputSetCondition(_pCurveFieldAgent),
		Action((ActionMethod)&PointDlgCmd::ActionCurveFiled));
	AddTransition(InitialState, InitialState,
		IsOutputSetCondition(_pModelFieldAgent),
		Action((ActionMethod)&PointDlgCmd::ActionModeFiled));
	AddTransition(InitialState, NULL,
		IsOutputSetCondition(_pOKAgent),
		Action((ActionMethod)&PointDlgCmd::ActionOK));
	AddTransition(InitialState, InitialState,
		IsOutputSetCondition(_pAPPLYAgent),
		Action((ActionMethod)&PointDlgCmd::ActionAPPLY));
	AddTransition(InitialState, NULL,
		IsOutputSetCondition(_pCLOSEAgent),
		Action((ActionMethod)&PointDlgCmd::ActionCLOSE));

}




CATBoolean PointDlgCmd::CheckSelectedCurve(void *data)
{
	CATBaseUnknown * pBaseUnknown = _pSelectCurvePathAgent->GetElementValue();
	if (NULL == pBaseUnknown)
	{
		return FALSE;
	}

	// 判断是否是可测量曲线
	CATIMeasurableCurve_var spMeasurableCurve = pBaseUnknown;
	if (spMeasurableCurve == NULL_var)
	{
		return FALSE;
	}

	// 判断是否是圆
	CATIMeasurableCircle_var spMeasurableCircle = pBaseUnknown;

	CATUnicodeString strMode;
	int iSelect = _pDlg->GetCombo(1)->GetSelect();
	_pDlg->GetCombo(1)->GetLine(strMode, iSelect);

	if (strMode == "圆的中心")
	{
		if (spMeasurableCircle == NULL_var)
		{
			return FALSE;
		}
	}
	else
	{
		if (spMeasurableCircle != NULL_var)
		{
			return FALSE;
		}
	}

	return TRUE;
}

CATBoolean PointDlgCmd::CheckInPut()
{
	_pDlg->SetOKSensitivity(CATDlgDisable);
	_pDlg->SetAPPLYSensitivity(CATDlgDisable);
	if (_spActiveProduct==NULL_var || _spSelectCurveObj==NULL_var || _spSelectCurveProduct==NULL_var)
		return FALSE;

	CATUnicodeString strMode;
	int iSelect = _pDlg->GetCombo(1)->GetSelect();
	_pDlg->GetCombo(1)->GetLine(strMode, iSelect);
	if (strMode=="曲线上的距离")
	{
		double userDistance =0;
		userDistance=_pDlg->GetSpinner(1)->GetValue();
		userDistance=1000*userDistance;
		if (userDistance<0.001)
		{
			return FALSE;
		}
	}

	_pDlg->SetAPPLYSensitivity(CATDlgEnable);
	return TRUE;
}

CATBoolean PointDlgCmd::SelectCurve(void *data)
{
	HRESULT rc = E_FAIL;

	if (_pHSO)
		_pHSO->Empty();

	// 获取选择的对象
	CATBaseUnknown * pSelection = _pSelectCurvePathAgent->GetElementValue();
	if (pSelection == NULL)
	{
		_pSelectCurvePathAgent->InitializeAcquisition();
		return FALSE;
	}

	// 获取 PathElement
	CATPathElement * pPathElement = _pSelectCurvePathAgent->GetValue();
	if (pPathElement == NULL)
	{
		_pSelectCurvePathAgent->InitializeAcquisition();
		return FALSE;
	}

	_pSelectCurvePathAgent->InitializeAcquisition();

	// 获取所选对象所在的Product
	CATIProduct_var spProductSelection = NULL_var;
	CATBaseUnknown * pProduct = pPathElement->FindElement(IID_CATIProduct);
	if (pProduct == NULL)
	{
		pProduct = pPathElement->FindElement(IID_CATIPrtPart);
		if (pProduct == NULL)
		{
			return FALSE;
		}
		CATIPrtPart_var spPart = pProduct;
		if (spPart == NULL_var)
		{
			return FALSE;
		}
		CATISpecObject_var spPartObject = spPart->GetProduct();
		if (spPartObject == NULL_var)
		{
			return FALSE;
		}
		spProductSelection = spPartObject;
	}
	else
		spProductSelection = pProduct;
	
	if (spProductSelection == NULL_var)
	{
		cout << "获取选择的对象所在的Product失败" << endl;
		return FALSE;
	}
	// 选择对象特征化
	CATISpecObject_var spSpecOnSelection=pPathElement->FindElement(IID_CATISpecObject);
	// Featurize(pSelection, spSpecOnSelection);
	if (spSpecOnSelection==NULL_var)
	{
		cout<<"获取选择的对象的Spec失败"<<endl;
		return FALSE;
	}

	_spSelectCurveObj = spSpecOnSelection;
	_spSelectCurveProduct = spProductSelection;

	// 获取选择对象的名称
	CATIAlias_var spAlias = spSpecOnSelection;
	if (spAlias == NULL_var)
	return FALSE;

	CATUnicodeString strName = spAlias->GetAlias();
	cout << "选择对象的名称:" << strName << endl;

	// 显示选择对象的名称到SelectorList
	_pDlg->GetSelectorList(1)->ClearLine();
	_pDlg->GetSelectorList(1)->SetLine(strName, -1, CATDlgDataModify);

	// 设置第一行选中
	int iTabRow = 0;
	_pDlg->GetSelectorList(1)->SetSelect(&iTabRow, 1, 0);

	// 高亮选择的对象
	UpdateHSO(pSelection, _pEditor, _pHSO);

	// 检查输入是否完整
	CheckInPut();

	return TRUE;

}

CATBoolean PointDlgCmd::ActionCurveFiled( void *data )
{
	_pCurveFieldAgent->InitializeAcquisition();

	HRESULT rc = E_FAIL;

	if (_pHSO)
		_pHSO->Empty();

	if (_pISO)
		_pISO->Empty();

	// 获取选中行
	int nbOfTemplate = _pDlg->GetSelectorList(1)->GetLineCount();
	int nbSelectCount = _pDlg->GetSelectorList(1)->GetSelectCount();
	int *pArrSelectObjIndex = new int[nbSelectCount]; // 存储选中的对象
	_pDlg->GetSelectorList(1)->GetSelect(pArrSelectObjIndex, nbSelectCount); // 获取选中的数组

	if (nbSelectCount < 1 || _spSelectCurveObj == NULL_var)
	{
		return FALSE;
	}

	// 高亮选择的对象
	UpdateHSO(_spSelectCurveObj, _pEditor, _pHSO);

	return TRUE;
}
CATBoolean PointDlgCmd::ActionModeFiled( void *data )
{
	_pModelFieldAgent->InitializeAcquisition();

	CATUnicodeString strMode;
	int iSelect = _pDlg->GetCombo(1)->GetSelect();
	_pDlg->GetCombo(1)->GetLine(strMode, iSelect);

	if (strMode == "曲线上的距离")
	{
		// 参数值控件不灰显
		_pDlg->GetSpinner(1)->SetSensitivity(CATDlgEnable);
	}

	if (strMode == "圆的中心")
	{
		// 参数值控件设置位0, 灰显
		_pDlg->GetSpinner(1)->SetValue(0.00);
		_pDlg->GetSpinner(1)->SetSensitivity(CATDlgDisable);
	}

	// 检查输入是否完整
	CheckInPut();

	return TRUE;
}

CATBoolean PointDlgCmd::ActionOK(void *data)
{
	ActionAPPLY(data);
	ActionCLOSE(data);
	return TRUE;
}

CATBoolean PointDlgCmd::ActionAPPLY( void *data )
{
	//Agent初始化
	_pAPPLYAgent->InitializeAcquisition();

	//创建点
	CATBoolean isReturn = CreatePoint();
	if (isReturn==FALSE)
		return FALSE;

	//OK不灰显
	_pDlg->SetOKSensitivity(CATDlgEnable);
	return TRUE;
}

CATBoolean PointDlgCmd::ActionCLOSE( void *data )
{
	_pCLOSEAgent->InitializeAcquisition();
	return TRUE;
}

void PointDlgCmd::UpdateHSO(CATBaseUnknown_var spSpecObj, CATFrmEditor *pEditor, CATHSO *pHSO)
{
	// to do
}

void PointDlgCmd::CreateMsgBoxOptError(CATUnicodeString usMsg, CATUnicodeString title)
{
	const char *pMsg = usMsg.ConvertToChar();
	const char *pTit = title.ConvertToChar();
	::MessageBoxA(NULL, pMsg ? pMsg : "Error", pTit ? pTit : "Error", MB_OK | MB_ICONERROR);
}

CATBoolean PointDlgCmd::IsProduct(CATIProduct_var ispiPrd)
{
	if (ispiPrd == NULL_var)
		return FALSE;

	CATIPrtContainer_var spPrtContainer = GetPrtContainer(ispiPrd);
	if (spPrtContainer != NULL_var)
		return FALSE; 

	return TRUE; 
}

CATBoolean PointDlgCmd::Featurize(CATBaseUnknown_var spSelection, CATISpecObject_var& ospSpecOnSelection)
{
	ospSpecOnSelection = NULL_var;
	if (spSelection == NULL_var) return FALSE;

	CATISpecObject_var spSO = spSelection;
	if (spSO != NULL_var)
	{
		ospSpecOnSelection = spSO;
		return TRUE;
	}

	CATIFeaturize_var spFeaturize = spSelection;
	if (spFeaturize == NULL_var) return FALSE;

	CATISpecObject_var spBRepFeature = spFeaturize->FeaturizeR(0);
	if (spBRepFeature == NULL_var) return FALSE;
	ospSpecOnSelection = spBRepFeature;
	return TRUE;
}

CATBoolean PointDlgCmd::DeleteObject(CATISpecObject_var SpecToRemove)
{
 //to do 
	return TRUE;
}

CATBoolean PointDlgCmd::CreatePoint()
{
	CATSoftwareConfiguration * pConfig = new CATSoftwareConfiguration();//配置指针
	CATTopData Topdata(pConfig);
	CATIGSMProceduralView_var spProceduralView = NULL_var;
	CATIAlias_var spAlias=NULL_var;
	CATISpecObject_var spSpecOnTemp=NULL_var;

	//1、判断输入是否完整
	CATBoolean isReturn = CheckInPut();
	if (isReturn==FALSE)
	{
		CreateMsgBoxOptError("The input is incomplete, please check");
		return FALSE;
	}

	//2、删除已创建的元素
	if (_spPointObj!=NULL_var)
		DeleteObject(_spPointObj);

	//3、变量赋空
	_spPointObj=NULL_var;

	//4、获取当前激活Part的容器
	CATIPrtContainer_var spPrtContainer=GetPrtContainer(_spActiveProduct);
	if (spPrtContainer==NULL_var)
	{
		cout<<"GetPrtContainer Failed"<<endl;
		return FALSE;
	}
	//5、获取工厂
	CATIGSMFactory_var spGSMFactory=spPrtContainer;
	CATICkeParmFactory_var spCkeParmFactory=spPrtContainer;
	CATIMechanicalRootFactory_var spMechRootFactory=spPrtContainer;
	CATIDatumFactory_var spDatumFactory=spPrtContainer;
	CATGeoFactory_var spGeoFactory=GetProductGeoFactory(_spActiveProduct);

	if (spGSMFactory==NULL_var || spCkeParmFactory==NULL_var || spDatumFactory==NULL_var || 
		spGeoFactory==NULL_var || spMechRootFactory==NULL_var)
	{
		cout<<"Get Factory Failed"<<endl;
		return FALSE;
	}

	CATISpecObject_var spPartObj=spPrtContainer->GetPart();
	if (spPartObj==NULL_var)
	{
		cout<<"GetPart Failed"<<endl;
		return FALSE;
	}

	CATIPrtPart_var spPrtPart=spPartObj;
	if (spPrtPart==NULL_var)
	{
		cout<<"GetPart Failed"<<endl;
		return FALSE;
	}
	//6、获取CAD_Deliverables几何集，不存在则创建
	CATISpecObject_var spSpecGeoSet=NULL_var;
	GetGSMTool(spPrtPart, "CAD_Deliverables", spSpecGeoSet, TRUE);
	if (spSpecGeoSet==NULL_var)
		spMechRootFactory->CreateGeometricalSet("CAD_Deliverables", spPrtPart, spSpecGeoSet, -1);
	if (spSpecGeoSet == NULL_var)
	{
		cout<<"CreateGeometricalSet Failed"<<endl;
		return FALSE;
	}

	//7、如跨零件操作，需将参考元素拷贝到当前激活零件
	CATISpecObject_var spSelectCurveObj=NULL_var;
	if (_spSelectCurveProduct->IsEqual(_spActiveProduct))
		spSelectCurveObj=_spSelectCurveObj;
	else
	{
		//设置当前工作对象
		spPrtPart->SetCurrentFeature(spSpecGeoSet);
		//CutAndPaste(spSpecGeoSet, _spSelectCurveObj, spSelectCurveObj);
		CopyWithLink(_spSelectCurveObj, _spSelectCurveProduct, spSpecGeoSet, _spActiveProduct, spSelectCurveObj);

		//隐藏参考线
		SetHideOrShow(spSelectCurveObj, TRUE);
	}

	if (spSelectCurveObj == NULL_var)
	{
		cout<<"Get Ref Curve Failed"<<endl;
		return FALSE;
	}
	//8、获取创建模式
	CATUnicodeString strMode;
	int iSelect = _pDlg->GetCombo(1)->GetSelect();
	_pDlg->GetCombo(1)->GetLine(strMode, iSelect);

#ifndef 曲线上创建点

	if (strMode=="曲线上的距离")
	{
		//9、获取界面参数值
		double userDistance =0;
		userDistance=_pDlg->GetSpinner(1)->GetValue();
		userDistance=1000*userDistance;
		if (userDistance<0.001)
		{
			return FALSE;
		}

		//10、创建距离参数
		CATICkeParm_var spCkeParm=spCkeParmFactory->CreateLength("Length", userDistance/1000);
		if (spCkeParm == NULL_var)
		{
			cout<<"CreateLength Failed"<<endl;
			return FALSE;
		}
	
		//11、创建曲线上的点
	CATGSMOrientation iOrientation = CATGSMSameOrientation;
	CATIGSMPointOnCurve_var spGSMPointOnCurve=spGSMFactory->CreatePoint(spSelectCurveObj, NULL_var, spCkeParm, iOrientation, CATIGSMPointOnCurve::Geodesic);
		if (spGSMPointOnCurve == NULL_var)
		{
			cout<<"Create Point On Curve Failed"<<endl;
			return FALSE;
		}

		//12、挂结构树
		spProceduralView = spGSMPointOnCurve;
		if (NULL_var != spProceduralView )
			spProceduralView->InsertInProceduralView(spSpecGeoSet);

		spSpecOnTemp=spGSMPointOnCurve;
		//13、设置点名称
		CATUnicodeString strName;
		spAlias = _spSelectCurveObj;
		if (spAlias != NULL_var)
			strName = spAlias->GetAlias();

		spAlias = spSpecOnTemp;
		if (spAlias != NULL_var)
			spAlias->SetAlias(strName + "上的点");

		//14、点更新
		ObjectUpdate(spSpecOnTemp);

		_spPointObj = spSpecOnTemp;
	}
#endif

#ifndef 圆弧创建中心点
	if (strMode=="圆的中心")
	{
		//9、创建圆弧的中心
		CATIGSMPointCenter_var spGSMPointCenter = spGSMFactory->CreatePoint(spSelectCurveObj);
		if (spGSMPointCenter == NULL_var)
		{
			return FALSE;
		}

		//10、挂结构树
		spProceduralView = spGSMPointCenter;
		if (NULL_var != spProceduralView)
			spProceduralView->InsertInProceduralView(spSpecGeoSet);

		spSpecOnTemp = spGSMPointCenter;

		//11、设置点名称
		CATUnicodeString strName;
		spAlias = _spSelectCurveObj;
		if (spAlias != NULL_var)
			strName = spAlias->GetAlias();

		spAlias = spSpecOnTemp;
		if (spAlias != NULL_var)
			spAlias->SetAlias(strName + "的圆心");

		//12、点更新
		ObjectUpdate(spSpecOnTemp);
		_spPointObj = spSpecOnTemp;

	}
#endif

	return TRUE;
}

CATIPrtContainer_var PointDlgCmd::GetPrtContainer(CATIProduct_var ispiObject)
{
	CATIPrtContainer_var spPrtCont = NULL_var;

	CATFrmEditor *pEd = CATFrmEditor::GetCurrentEditor();
	if (pEd == NULL) return spPrtCont;

	CATDocument *pDoc = pEd->GetDocument();
	if (pDoc == NULL) return spPrtCont;

	CATInit *piInit = NULL;
	HRESULT hr = pDoc->QueryInterface(IID_CATInit, (void**)&piInit);
	if (FAILED(hr) || piInit == NULL) return spPrtCont;

	CATIPrtContainer *pRoot = (CATIPrtContainer*)piInit->GetRootContainer("CATIPrtContainer");
	piInit->Release();

	if (pRoot)
	{
		spPrtCont = pRoot;
		pRoot->Release();
	}

	return spPrtCont;
}

HRESULT PointDlgCmd::GetGSMTool(CATISpecObject_var ispTargetFatherObj,
								CATUnicodeString istrName,
								CATISpecObject_var &ospiSpecGeoSet,
								CATBoolean isSame)
{
	ospiSpecGeoSet = NULL_var;
	return E_NOTIMPL;
}

HRESULT PointDlgCmd::ObjectUpdate(CATISpecObject_var isoSpecObject)
{
	if (isoSpecObject == NULL_var) return E_FAIL;

	HRESULT hr = S_OK;

	CATTry
	{
		hr = isoSpecObject->Update();
	}
	CATCatch(CATError, iErr)
	{
		hr = E_FAIL;
	}
	CATEndTry

		return hr;
}



CATGeoFactory_var PointDlgCmd::GetProductGeoFactory(CATIProduct_var ispProduct)
{
	CATGeoFactory_var spGeoFactory = NULL_var;

	if (ispProduct == NULL_var) return spGeoFactory;

	CATFrmEditor * pEd = CATFrmEditor::GetCurrentEditor();
	if (pEd == NULL) return spGeoFactory;

	CATDocument * pDoc = pEd->GetDocument();
	if (pDoc == NULL) return spGeoFactory;

	CATIContainerOfDocument * pDocCont = NULL;
	HRESULT hr = pDoc->QueryInterface(IID_CATIContainerOfDocument, (void**)&pDocCont);
	if (FAILED(hr) || pDocCont == NULL) return spGeoFactory;

	CATIContainer * pResCont = NULL;
	pDocCont->GetResultContainer(pResCont);
	pDocCont->Release();

	if (pResCont == NULL) return spGeoFactory;

	CATGeoFactory * pGeoFactory = NULL;
	hr = pResCont->QueryInterface(IID_CATGeoFactory, (void**)&pGeoFactory);
	pResCont->Release();

	if (FAILED(hr) || pGeoFactory == NULL) return spGeoFactory;

	spGeoFactory = pGeoFactory;
	pGeoFactory->Release();

	return spGeoFactory;
}


HRESULT PointDlgCmd::CopyWithLink(CATBaseUnknown_var ispSource,
								  CATIProduct_var ispInstanceSource,
								  CATBaseUnknown_var ispTarget,
								  CATIProduct_var ispInstanceTarget,
								  CATISpecObject_var spSelectCurveObj)
{
	return E_NOTIMPL;
}

HRESULT PointDlgCmd::SetHideOrShow(CATISpecObject_var spSpecObject, CATBoolean IfHide)
{
	return E_NOTIMPL;
}

HRESULT PointDlgCmd::CutAndPaste(CATISpecObject_var ispSpecOnTarget,
								 CATISpecObject_var ispSpecOnSource,
								 CATISpecObject_var &ospSpecOnTarget)
{
	ospSpecOnTarget = NULL_var;
	return E_NOTIMPL;
}
