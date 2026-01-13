#ifndef AddDocDlg_H
#define AddDocDlg_H

//==============================
// Dialog 基类 / 控件
//==============================
#include "CATDlgDialog.h"
#include "CATDlgInclude.h"
#include "CATDlgFile.h"

//==============================
// Editor / Document / Layout
//==============================
#include "CATApplicationFrame.h"
#include "CATFrmWindow.h"
#include "CATFrmEditor.h"
#include "CATDocument.h"
#include "CATDocumentServices.h"

//==============================
// Product / Roots（用于 AddProduct 导入）
/*
  CATIDocRoots：从文档得到根对象列表
  CATIProduct ：根产品/组件节点
*/
#include "CATIDocRoots.h"
#include "CATIProduct.h"
#include "CATListOfCATBaseUnknown.h"

//==============================
// 刷新事件（导入后刷新树/显示）
#include "CATIModelEvents.h"
#include "CATModify.h"
#include "CATIRedrawEvent.h"

//==============================
// 位姿变换（移动/旋转）
#include "CATMathTransformation.h"
#include "CATIMovable.h"
#include "CATMathTransformation1D.h"

//==============================
// 标准库
#include <iostream.h>
#include <math.h>
#include <windows.h>

#include "CATUnicodeString.h"
#include "CATListOfCATUnicodeString.h"
#include "CATLISTV_CATBaseUnknown.h"   

class AddDocDlg : public CATDlgDialog
{
  DeclareResource(AddDocDlg, CATDlgDialog)

public:
  AddDocDlg();
  virtual ~AddDocDlg();

  void Build();
  CATDlgSelectorList* GetSelectorList(int iValue);
  CATDlgSpinner*      GetSpinner(int iValue);

  // 4x4 变换矩阵相乘：用于复合 MovePosition 与 InitialPosition
  CATMathTransformation TwoMatrixesMultiply(CATMathTransformation iMatrix1, CATMathTransformation iMatrix2);

  // 关闭窗口回调
  virtual void DocWindCloseNotification(CATCommand*, CATNotification*, CATCommandClientData data);
  void SetTargetProduct(CATIProduct_var iProd);
protected:
  // 导入按钮：OpenDocument + AddProduct，并记录 _spImportedProduct
  virtual void OnPushButton002PushBActivateNotification(CATCommand*, CATNotification*, CATCommandClientData data);

  // 选择文件按钮：弹出文件选择对话框
  virtual void OnPushButton003PushBActivateNotification(CATCommand*, CATNotification*, CATCommandClientData data);

  // 位姿按钮：对 _spImportedProduct 做 SetPosition
  virtual void OnPushButton028PushBActivateNotification(CATCommand*, CATNotification*, CATCommandClientData data);
  

private:
  // 文件对话框 OK 回调：把路径写回 Editor
  void ActOnOK(CATCommand* cmd, CATNotification* evt, CATCommandClientData data);

private:
  //==============================
  // Dialog 控件
  //==============================
  CATDlgFile*         pDlgFile;

  CATDlgFrame*        _Frame006;
  CATDlgPushButton*   _PushButton003;
  CATDlgLabel*        _Label004;
  CATDlgPushButton*   _PushButton002;
  CATDlgEditor*       _Editor005;

  CATDlgFrame*        _Frame007;
  CATDlgLabel*        _Label008;
  CATDlgLabel*        _Label009;
  CATDlgLabel*        _Label011;
  CATDlgLabel*        _Label010;
  CATDlgLabel*        _Label012;
  CATDlgLabel*        _Label013;

  CATDlgSpinner*      _Spinner020; // X(mm)
  CATDlgSpinner*      _Spinner022; // Y(mm)
  CATDlgSpinner*      _Spinner023; // Z(mm)
  CATDlgSpinner*      _Spinner024; // Rx(显示Degree，GetValue为rad)
  CATDlgSpinner*      _Spinner026; // Rz(显示Degree，GetValue为rad) 你当前代码里与027有互换
  CATDlgSpinner*      _Spinner027; // Ry(显示Degree，GetValue为rad)

  CATDlgPushButton*   _PushButton028;
  CATDlgSelectorList* _SelectorList029;
  CATDlgLabel*        _Label030;

  // 最近一次导入得到的 Product（供位姿按钮使用）
  CATIProduct_var     _spImportedProduct;
};

#endif
