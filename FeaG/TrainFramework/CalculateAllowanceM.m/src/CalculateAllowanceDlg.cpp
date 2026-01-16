#include "CalculateAllowanceDlg.h"
#include "CATApplicationFrame.h"
#include "CATDlgGridConstraints.h"
#include "CATMsgCatalog.h"
#ifdef CalculateAllowanceDlg_ParameterEditorInclude
#include "CATIParameterEditorFactory.h"
#include "CATIParameterEditor.h"
#include "CATICkeParm.h"
#endif


CalculateAllowanceDlg::CalculateAllowanceDlg() :
  CATDlgDialog ((CATApplicationFrame::GetApplicationFrame())->GetMainWindow(),
"CalculateAllowanceDlg",CATDlgGridLayout
                               )
{
 _Frame001 = NULL;
 _Editor006 = NULL;
 _Frame004 = NULL;
 _Editor007 = NULL;
 _Frame008 = NULL;
 _Label009 = NULL;
 _Editor011 = NULL;
 _Label010 = NULL;
 _Editor012 = NULL;
 _Editor017 = NULL;
 _Editor018 = NULL;
 _Editor019 = NULL;
 _Frame022 = NULL;
 _Editor023 = NULL;
 _Label025 = NULL;
 _Label026 = NULL;
 _Label027 = NULL;
 _Frame028 = NULL;
 _CheckButton029 = NULL;
 _CheckButton030 = NULL;
 _CheckButton031 = NULL;
 _PushButton024 = NULL;
}

CalculateAllowanceDlg::~CalculateAllowanceDlg()
{
 _Frame001 = NULL;
 _Editor006 = NULL;
 _Frame004 = NULL;
 _Editor007 = NULL;
 _Frame008 = NULL;
 _Label009 = NULL;
 _Editor011 = NULL;
 _Label010 = NULL;
 _Editor012 = NULL;
 _Editor017 = NULL;
 _Editor018 = NULL;
 _Editor019 = NULL;
 _Frame022 = NULL;
 _Editor023 = NULL;
 _Label025 = NULL;
 _Label026 = NULL;
 _Label027 = NULL;
 _Frame028 = NULL;
 _CheckButton029 = NULL;
 _CheckButton030 = NULL;
 _CheckButton031 = NULL;
 _PushButton024 = NULL;
}



void CalculateAllowanceDlg::Build()
{
 _Frame001 = new CATDlgFrame(this, "Frame001", CATDlgGridLayout);
_Frame001 -> SetGridConstraints(0, 0, 1, 1, CATGRID_4SIDES);
 _Editor006 = new CATDlgEditor(_Frame001, "Editor006", CATDlgEdtMultiline);
 _Editor006 -> SetVisibleTextWidth(10);
_Editor006 -> SetGridConstraints(0, 0, 1, 1, CATGRID_4SIDES);
 _Frame004 = new CATDlgFrame(this, "Frame004", CATDlgGridLayout);
_Frame004 -> SetGridConstraints(0, 1, 1, 1, CATGRID_4SIDES);
 _Editor007 = new CATDlgEditor(_Frame004, "Editor007", CATDlgEdtMultiline);
 _Editor007 -> SetVisibleTextWidth(10);
_Editor007 -> SetGridConstraints(0, 0, 1, 1, CATGRID_4SIDES);
 _Frame008 = new CATDlgFrame(this, "Frame008", CATDlgGridLayout);
_Frame008 -> SetGridConstraints(1, 0, 2, 1, CATGRID_4SIDES);
 _Label009 = new CATDlgLabel(_Frame008, "Label009");
_Label009 -> SetGridConstraints(0, 0, 1, 1, CATGRID_4SIDES);
 _Editor011 = new CATDlgEditor(_Frame008, "Editor011");
_Editor011 -> SetGridConstraints(0, 1, 1, 1, CATGRID_4SIDES);
 _Label010 = new CATDlgLabel(_Frame008, "Label010");
_Label010 -> SetGridConstraints(1, 0, 1, 1, CATGRID_4SIDES);
 _Editor012 = new CATDlgEditor(_Frame008, "Editor012");
_Editor012 -> SetGridConstraints(1, 1, 1, 1, CATGRID_4SIDES);
 _Editor017 = new CATDlgEditor(this, "Editor017");
_Editor017 -> SetGridConstraints(2, 1, 1, 1, CATGRID_4SIDES);
 _Editor018 = new CATDlgEditor(this, "Editor018");
_Editor018 -> SetGridConstraints(3, 1, 1, 1, CATGRID_4SIDES);
 _Editor019 = new CATDlgEditor(this, "Editor019");
_Editor019 -> SetGridConstraints(4, 1, 1, 1, CATGRID_4SIDES);
 _Frame022 = new CATDlgFrame(this, "Frame022", CATDlgGridLayout);
_Frame022 -> SetGridConstraints(6, 0, 2, 1, CATGRID_4SIDES);
 _Editor023 = new CATDlgEditor(_Frame022, "Editor023", CATDlgEdtMultiline);
 _Editor023 -> SetVisibleTextWidth(20);
_Editor023 -> SetGridConstraints(0, 0, 1, 1, CATGRID_4SIDES);
 _Label025 = new CATDlgLabel(this, "Label025", CATDlgLabCenter);
_Label025 -> SetGridConstraints(2, 0, 1, 1, CATGRID_4SIDES);
 _Label026 = new CATDlgLabel(this, "Label026", CATDlgLabCenter);
_Label026 -> SetGridConstraints(3, 0, 1, 1, CATGRID_4SIDES);
 _Label027 = new CATDlgLabel(this, "Label027", CATDlgLabCenter);
_Label027 -> SetGridConstraints(4, 0, 1, 1, CATGRID_4SIDES);
 _Frame028 = new CATDlgFrame(this, "Frame028", CATDlgGridLayout);
_Frame028 -> SetGridConstraints(5, 0, 1, 1, CATGRID_4SIDES);
 _CheckButton029 = new CATDlgCheckButton(_Frame028, "CheckButton029");
_CheckButton029 -> SetGridConstraints(0, 0, 1, 1, CATGRID_4SIDES);
 _CheckButton030 = new CATDlgCheckButton(_Frame028, "CheckButton030");
_CheckButton030 -> SetGridConstraints(0, 1, 1, 1, CATGRID_4SIDES);
 _CheckButton031 = new CATDlgCheckButton(_Frame028, "CheckButton031");
_CheckButton031 -> SetGridConstraints(0, 2, 1, 1, CATGRID_4SIDES);
 _PushButton024 = new CATDlgPushButton(this, "PushButton024");
_PushButton024 -> SetGridConstraints(5, 1, 1, 1, CATGRID_4SIDES);
  AddAnalyseNotificationCB(this,
                           GetWindCloseNotification(),
                           (CATCommandMethod)&CalculateAllowanceDlg::OnDlgWindCloseNotification,
                           NULL);
}


void CalculateAllowanceDlg::OnDlgWindCloseNotification(CATCommand* cmd, CATNotification* evt, CATCommandClientData data)
{
  this->SetVisibility(CATDlgHide);
}



CATDlgPushButton* CalculateAllowanceDlg::GetPushButton(int iValue)
{
  switch (iValue)
  {
  case 1: return _PushButton024;
  }
  return NULL;
}

CATDlgEditor* CalculateAllowanceDlg::GetEditor(int iValue)
{
  switch (iValue)
  {
  case 1: return _Editor006;
  case 2: return _Editor007;
  case 3: return _Editor011;
  case 4: return _Editor012;
  case 5: return _Editor017;
  case 6: return _Editor018;
  case 7: return _Editor019;
  case 8: return _Editor023;
  }
  return NULL;
}


CATDlgCheckButton* CalculateAllowanceDlg::GetCheckButton(int iValue)
{
  switch (iValue)
  {
  case 1: return _CheckButton029;
  case 2: return _CheckButton030;
  case 3: return _CheckButton031;

  }
  return NULL;
}
