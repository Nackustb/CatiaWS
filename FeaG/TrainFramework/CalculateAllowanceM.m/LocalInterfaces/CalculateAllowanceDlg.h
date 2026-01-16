#ifndef CalculateAllowanceDlg_H
#define CalculateAllowanceDlg_H

#include "CATDlgDialog.h"
#include "CATDlgInclude.h"


class CalculateAllowanceDlg: public CATDlgDialog
{

  DeclareResource( CalculateAllowanceDlg, CATDlgDialog )

  public:

  CalculateAllowanceDlg();
  virtual ~CalculateAllowanceDlg();

  void Build ();
  void OnDlgWindCloseNotification(CATCommand* cmd, CATNotification* evt, CATCommandClientData data);
  CATDlgPushButton* GetPushButton(int iValue);
  CATDlgEditor*     GetEditor(int iValue);
  CATDlgCheckButton* GetCheckButton(int iValue);
  protected:

  private:


 CATDlgFrame*      _Frame001;
 CATDlgEditor*      _Editor006;
 CATDlgFrame*      _Frame004;
 CATDlgEditor*      _Editor007;
 CATDlgFrame*      _Frame008;
 CATDlgLabel*      _Label009;
 CATDlgEditor*      _Editor011;
 CATDlgLabel*      _Label010;
 CATDlgEditor*      _Editor012;
 CATDlgEditor*      _Editor017;
 CATDlgEditor*      _Editor018;
 CATDlgEditor*      _Editor019;
 CATDlgFrame*      _Frame022;
 CATDlgEditor*      _Editor023;
 CATDlgLabel*      _Label025;
 CATDlgLabel*      _Label026;
 CATDlgLabel*      _Label027;
 CATDlgFrame*      _Frame028;
 CATDlgCheckButton*      _CheckButton029;
 CATDlgCheckButton*      _CheckButton030;
 CATDlgCheckButton*      _CheckButton031;
 CATDlgPushButton*      _PushButton024;
};
#endif
