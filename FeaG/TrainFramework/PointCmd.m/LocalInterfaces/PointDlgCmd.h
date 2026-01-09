#ifndef PointDlgCmd_H
#define PointDlgCmd_H
#include "CATStateCommand.h"
#include "CATBoolean.h"
#include "PointDlg.h"
#include "CATDialogAgent.h"
#include "CATPathElementAgent.h"
#include "CATHSO.h"
#include "CATISO.h"
#include "CATISpecObject.h"
#include "CATIProduct.h"
#include "CATFrmEditor.h"
#include "CATISketch.h"
#include "CATI2DCircle.h"
#include "CATI2DCurve.h"

class CATIndicationAgent;


class PointDlgCmd: public CATStateCommand
{
  DeclareResource( PointDlgCmd, CATStateCommand )

  public:

  PointDlgCmd();
  virtual ~PointDlgCmd();
  virtual void     BuildGraph();
  
	
  CATBoolean ActionOK (void *data);
  CATBoolean ActionAPPLY (void *data);
  CATBoolean ActionCLOSE (void *data);
  CATBoolean ActionSelectCurve(void *data);
  virtual CATStatusChangeRC Activate(CATCommand * iFromClient,CATNotification * iEvtDat);
  virtual CATStatusChangeRC Desactivate(CATCommand * iFromClient,CATNotification * iEvtDat);
  virtual CATStatusChangeRC Cancel(CATCommand * iFromClient,CATNotification * iEvtDat);

  void CreateGeometry(CATCommand * iFromClient, CATNotification * iEvtDat);
  
  enum SelectMode
  {
	  kModeCurveDistance = 0,
	  kModeCircleCenter  = 1
  };

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
  CATISketch_var  _spSelectedSketch;
  CATI2DCircle_var _spSelectedCircle2D;
  CATI2DCurve_var _spSelectedCurve2D;

  CATISpecObject_var   _spPointObj;               // 创建的点
  CATListValCATISpecObject_var _ListOfCircles;
  CATDialogAgent * _pModeAgent;

  int GetCurrentMode() const;
  CATBoolean ActionModeChanged(void * data);
  CATBoolean ApplyByMode();
  CATBoolean ApplyCircleCenter();
  CATBoolean ApplyCurveDistance();
};

//----------------------------------------------------------------------

#endif
