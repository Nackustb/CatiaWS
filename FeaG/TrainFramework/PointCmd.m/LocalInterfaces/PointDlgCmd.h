#ifndef PointDlgCmd_H
#define PointDlgCmd_H
#include "CATStateCommand.h"
#include "CATBoolean.h"
#include "PointDlg.h"
#include "CATIMeasurableCurve.h"
#include "CATIMeasurableCircle.h"
#include "CATFrmEditor.h"
#include "CATHSO.h"
#include "CATISO.h"
#include "CATPathElementAgent.h"
#include "CATFeatureImportAgent.h"
#include "CATFeatureAgent.h"
#include "CATIProduct.h"
#include "CATDlgNotify.h"
#include "CATApplicationFrame.h"
#include "CATIBuildPath.h"
#include "CATPathElement.h"
#include "CATIProduct.h"
#include "CATILinkableObject.h"
#include "CATDocument.h"
#include "CATIDocId.h"
#include "CATIPrtPart.h"
#include "CATISpecObject.h"
#include "CATIBRepAccess.h"
#include "CATIFeaturize.h"
#include "CATIModelEvents.h"
#include "LifeCycleObject.h"
#include "CATDelete.h"
#include "CATIDescendants.h"
#include "CATIGSMFactory.h"
#include "CATICkeParmFactory.h"
#include "CATIDatumFactory.h"
#include "CATGeoFactory.h"
#include "CATIMechanicalRootFactory.h"
#include "CATIPrtPart.h"
#include "CATSoftwareConfiguration.h"
#include "CATTopData.h"
#include "CATIGSMProceduralView.h"
#include "CATIPrtContainer.h"
#include "CATInit.h"
#include "CATModify.h"
#include "CATIModelEvents.h"
#include "CATIGSMPointCenter.h"
#include "CATMfErrUpdate.h"
#include "CATIGSMPointOnCurve.h"
#include "CATIContainerOfDocument.h"
#include "CATMmrInterPartCopy.h"
#include "CATIVisProperties.h"
#include "CATVisPropertiesValues.h"
#include "CATIRedrawEvent.h"
#include "CATIContainer.h"
#include "CATICutAndPastable.h"
#include "CATIRedrawEvent.h"
#include "CATIContainer.h"
#include "CATICutAndPastable.h"
#include "CATFormat.h"
#include "CATIMechanicalFeature.h"

#include <iostream.h>



class CATIndicationAgent;


class PointDlgCmd: public CATStateCommand
{
  DeclareResource( PointDlgCmd, CATStateCommand )

  public:

  PointDlgCmd();
  virtual ~PointDlgCmd();
  virtual void     BuildGraph();
  
  //********元素过滤********
  CATBoolean CheckSelectedCurve(void *data);

  //********检查输入是否完整********
  CATBoolean CheckInPut();

  //********获取选择对象********
  CATBoolean SelectCurve(void *data);

  //********单击选择对象********
  CATBoolean ActionCurveFiled(void *data);

  //********选择创建模式********
  CATBoolean ActionModeFiled(void *data);

  //********点击OK********
  CATBoolean ActionOK(void *data);

  //********点击APPLY********
  CATBoolean ActionAPPLY(void *data);

  //********点击CLOSE********
  CATBoolean ActionCLOSE(void *data);

  //********高亮元素********
  void UpdateHSO(CATBaseUnknown_var spSpecObj, CATFrmEditor *pEditor, CATHSO *pHSO);

  //********提示窗口********
	void CreateMsgBoxOptError(CATUnicodeString usMsg, CATUnicodeString title="Error");

  //********判断是否为装配********
	CATBoolean IsProduct(CATIProduct_var ispiPrd);

  //********元素特征化********
	CATBoolean Featurize(CATBaseUnknown_var spSelection, CATISpecObject_var& ospSpecOnSelection);

  //********创建点********
	CATBoolean DeleteObject(CATISpecObject_var SpecToRemove);

  //********删除元素********
	CATBoolean CreatePoint();

  //********获取容器********
	CATIPrtContainer_var GetPrtContainer(CATIProduct_var ispiObject);

  //********根据名称获取几何集********
	HRESULT GetGSMTool(CATISpecObject_var ispTargetFatherObj,
					   CATUnicodeString istrName,
					   CATISpecObject_var &ospiSpecGeoSet,
					   CATBoolean isSame=FALSE);

  //********刷新对象********
	HRESULT ObjectUpdate(CATISpecObject_var isoSpecObject);

  //********获取GeoFactory********
	CATGeoFactory_var GetProductGeoFactory(CATIProduct_var ispProduct);

  //********关联拷贝********
	HRESULT CopyWithLink(CATBaseUnknown_var ispSource,
						 CATIProduct_var ispInstanceSource,
						 CATBaseUnknown_var ispTarget,
						 CATIProduct_var ispInstanceTarget,
						 CATISpecObject_var spSelectCurveObj);
  //********设置隐藏显示********
	HRESULT SetHideOrShow(CATISpecObject_var spSpecObject, CATBoolean IfHide);

  //********拷贝元素********
	HRESULT CutAndPaste(CATISpecObject_var ispSpecOnTarget,
						CATISpecObject_var ispSpecOnSource,
						CATISpecObject_var &ospSpecOnTarget);

  private:
  PointDlg* _pDlg;

  CATFrmEditor * _pEditor;   // 当前编辑器
  CATHSO       * _pHSO;      // 高亮选择对象
  CATISO       * _pISO;      // 隔离选择对象

  CATPathElementAgent* _pSelectCurvePathAgent; //选择元素
  CATDialogAgent* _pCurveFieldAgent;  // 单击元素
  CATDialogAgent* _pModelFieldAgent;  // 选择模式
  CATDialogAgent* _pOKAgent;          // OK
  CATDialogAgent* _pAPPLYAgent;       // APPLY
  CATDialogAgent* _pCLOSEAgent;       // CLOSE

  CATISpecObject_var   _spSelectCurveObj;        // 选择的元素
  CATIProduct_var     _spSelectCurveProduct;    // 选择元素所在的 Product
  CATIProduct_var     _spActiveProduct;          // 当前激活的 Product
  CATISpecObject_var   _spPointObj;               // 创建的点

};

#endif
