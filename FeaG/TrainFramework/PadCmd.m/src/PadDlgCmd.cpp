//=================================================================
// Command / Dialog / UI
//=================================================================
#include "PadDlgCmd.h"
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
CATCreateClass( PadDlgCmd);


PadDlgCmd::PadDlgCmd() :
  CATStateCommand ("PadDlgCmd", CATDlgEngOneShot, CATCommandModeExclusive) 
  ,_pDlg(NULL)
  , _pEditor(NULL)
{
	CATApplicationFrame * pFrame = CATApplicationFrame::GetFrame();

	if (NULL != pFrame)
	{
		CATDialog * pParent = (CATDialog *)pFrame->GetMainWindow();

		if(pParent != NULL)
		{
			_pDlg = new PadDlg();
			_pDlg->Build();			  
		}
	}
	RequestStatusChange (CATCommandMsgRequestExclusiveMode);  	  
}

PadDlgCmd::~PadDlgCmd()
{

     if (_pDlg != NULL) 
	   _pDlg->RequestDelayedDestruction();
}


CATStatusChangeRC PadDlgCmd::Activate( CATCommand * iFromClient, CATNotification * iEvtDat)
{
	if(_pDlg != NULL)
		_pDlg->SetVisibility(CATDlgShow);  // 可视化设置


	return (CATStatusChangeRCCompleted);
}

CATStatusChangeRC PadDlgCmd::Desactivate( CATCommand * iFromClient, CATNotification * iEvtDat)
{
	if(_pDlg != NULL)
		_pDlg->SetVisibility(CATDlgHide);
	return (CATStatusChangeRCCompleted);
}

CATStatusChangeRC PadDlgCmd::Cancel( CATCommand * iFromClient, CATNotification * iEvtDat)
{
	if(_pDlg != NULL)
		_pDlg->SetVisibility(CATDlgHide);
	RequestDelayedDestruction();
	return (CATStatusChangeRCCompleted);
}

void PadDlgCmd::BuildGraph()
{

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
	InitialState->AddDialogAgent(_pOKAgent);
	InitialState->AddDialogAgent(_pAPPLYAgent);
	InitialState->AddDialogAgent(_pCLOSEAgent);
	
	AddTransition(
	  InitialState,
	  NULL,
	  IsOutputSetCondition(_pOKAgent),
	  Action((ActionMethod)&PadDlgCmd::ActionOK)
	);

	AddTransition(
	  InitialState,
	  NULL,
	  //InitialState,
	  IsOutputSetCondition(_pAPPLYAgent),
	  Action((ActionMethod)&PadDlgCmd::ActionAPPLY)
	);

	AddTransition(
	  InitialState,
	  NULL,
	  IsOutputSetCondition(_pCLOSEAgent),
	  Action((ActionMethod)&PadDlgCmd::ActionCLOSE)
	);
}


CATBoolean PadDlgCmd::ActionAPPLY(void *data)
{
    // =================================================================================
    // 1. 环境初始化与容器获取 (Context & Container Retrieval)
    // =================================================================================
    
    // 获取当前编辑器
    CATFrmEditor * piEditor = CATFrmEditor::GetCurrentEditor();
    if (NULL == piEditor) return FALSE;

    CATDocument * piDocument = piEditor->GetDocument();
    if (NULL == piDocument) return FALSE;

    // 获取文档初始化接口
    CATInit * piInitLink = NULL;
    HRESULT hr = piDocument->QueryInterface(IID_CATInit, (void**)&piInitLink);
    if (FAILED(hr) || NULL == piInitLink)
    {
        ::MessageBoxA(NULL, "错误：无法获取文档 Init 接口。", "系统错误", MB_OK | MB_ICONERROR);
        return FALSE;
    }

    // 获取零件容器 (Root Container)
    CATIPrtContainer * piRootContainer = (CATIPrtContainer*)piInitLink->GetRootContainer("CATIPrtContainer");

    if (piInitLink)
    {
        piInitLink->Release();
        piInitLink = NULL;
    }

    if (NULL == piRootContainer) 
    {
        ::MessageBoxA(NULL, "错误：无法获取零件容器！\n请确保当前处于 Part Design 工作台。", "环境错误", MB_OK | MB_ICONERROR);
        return FALSE; 
    }

    // =================================================================================
    // 2. 数据获取与处理 (Data Parsing & Processing)
    // =================================================================================

    // 定义单位转换系数 (mm -> m)
    // 工程注释：CATIA 内核默认单位为米。界面输入通常为毫米，必须转换。
    const double mm_to_m = 1; 

    double Length = 0.0;
    double Width  = 0.0;
    double Height = 0.0;

    // 安全获取输入值
    CATUnicodeString strL, strW, strH;
    
    // Length
    if (_pDlg->GetEditor(1)) {
        strL = _pDlg->GetEditor(1)->GetText();
        if (strL.ConvertToNum(&Length)) {
            Length = Length * mm_to_m; // 转换为米
        }
    }
    // Width
    if (_pDlg->GetEditor(2)) {
        strW = _pDlg->GetEditor(2)->GetText();
        if (strW.ConvertToNum(&Width)) {
            Width = Width * mm_to_m;
        }
    }
    // Height
    if (_pDlg->GetEditor(3)) {
        strH = _pDlg->GetEditor(3)->GetText();
        if (strH.ConvertToNum(&Height)) {
            Height = Height * mm_to_m;
        }
    }

    // [Debug] 数据校验 - 这是一个常用的调试手段
    // 如果数值过小（例如用户没输入），阻止运行以防止 Update 报错
    if (Length < 1e-6 || Width < 1e-6 || Height < 1e-6)
    {
        CATUnicodeString debugMsg;
        debugMsg.BuildFromNum(Length * 1000.0); // 还原成 mm 显示
        CATUnicodeString msg = "检测到输入数值异常 (接近0或未输入)。\n读取到的 Length (mm): " + debugMsg;
        ::MessageBoxA(NULL, msg.ConvertToChar(), "数据校验失败", MB_OK | MB_ICONWARNING);
        
        // 记得释放容器指针
        piRootContainer->Release(); 
        return FALSE;
    }

    // =================================================================================
    // 3. 几何构建：草图 (Sketch Creation)
    // =================================================================================

    // 获取草图工厂 (智能指针自动管理生命周期)
    CATISketchFactory_var spSketchFactOnPrtCont(piRootContainer);
    if (NULL_var == spSketchFactOnPrtCont) {
        piRootContainer->Release();
        return FALSE;
    }

    CATIPrtPart_var spPart = piRootContainer->GetPart();
    if (NULL_var == spPart) {
        piRootContainer->Release();
        return FALSE;
    }

    // 获取参考平面列表
    CATListValCATISpecObject_var spListRefPlanes = spPart->GetReferencePlanes();
    if (spListRefPlanes.Size() < 2) {
        piRootContainer->Release();
        return FALSE;
    }

    // 选择 XY 平面 (通常 List[1] 是 XY，但建议检查名称，这里暂按索引)
    CATISpecObject_var spSketchPlane = spListRefPlanes[1];

    // 创建草图特征
    CATISketch_var spSketch = spSketchFactOnPrtCont->CreateSketch(spSketchPlane);
    if (NULL_var == spSketch) {
        piRootContainer->Release();
        return FALSE;
    }

    // 获取 2D 线框工厂
    CATI2DWFFactory_var spWF2DFactOnSketch(spSketch);

    double pt1[2] = { 0.0,    0.0 };
    double pt2[2] = { Length, 0.0 };
    double pt3[2] = { 0.0,    Width };
    double pt4[2] = { Length, Width };

    // 打开草图编辑模式
    spSketch->OpenEdition();

    // 创建四条线
    CATISpecObject_var spLine1 = spWF2DFactOnSketch->CreateLine(pt1, pt2);
    CATISpecObject_var spLine2 = spWF2DFactOnSketch->CreateLine(pt2, pt4); // 注意顺序：pt2 -> pt4
    CATISpecObject_var spLine3 = spWF2DFactOnSketch->CreateLine(pt4, pt3); // pt4 -> pt3
    CATISpecObject_var spLine4 = spWF2DFactOnSketch->CreateLine(pt3, pt1); // pt3 -> pt1 (闭合)


    // 关闭草图 (此时系统会计算几何拓扑)
    spSketch->CloseEdition();

    // =================================================================================
    // 4. 实体特征构建：凸台 (Pad Creation)
    // =================================================================================

    // 获取零件工厂
    CATIPrtFactory_var spPrtFactOnPrtCont(piRootContainer);
    
    // [关键] 工厂获取完毕后，raw pointer 使用结束，必须释放
    piRootContainer->Release();
    piRootContainer = NULL; 

    // 创建 Pad
    CATISpecObject_var spSpecObj = spPrtFactOnPrtCont->CreatePad(spSketch);
    if (NULL_var == spSpecObj) return FALSE;

    CATIPad_var spPadOnSpecObj(spSpecObj);
    
    // 设置拉伸方向 (默认通常是 sketch 法向，这里显式指定 Z 轴)
    CATMathDirection dirZ(0.0, 0.0, 1.0);
    spPadOnSpecObj->ModifyDirection(dirZ);

    // 设置拉伸参数
    spPadOnSpecObj->ModifyEndType(catOffsetLimit);
    spPadOnSpecObj->ModifyEndOffset(Height); 
    spPadOnSpecObj->ModifyStartType(catOffsetLimit);
    spPadOnSpecObj->ModifyStartOffset(0.0);

    // =================================================================================
    // 5. 更新模型 (Update)
    // =================================================================================

    CATTry 
    {
        spSpecObj->Update(); 
    }
    CATCatch(CATError, error)
    {
        ::MessageBoxA(NULL, "模型更新失败！可能是草图未闭合或参数过小。", "Update Error", MB_OK);
        Flush(error); 
        return FALSE;
    }
    CATEndTry

    return TRUE;
}
CATBoolean PadDlgCmd::ActionCLOSE(void *data)
{
	return TRUE;
}

CATBoolean PadDlgCmd::ActionOK(void *data)
{
	ActionCLOSE(data);
	return TRUE;
}