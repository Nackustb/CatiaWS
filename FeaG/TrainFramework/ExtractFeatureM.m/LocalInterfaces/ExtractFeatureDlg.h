#ifndef ExtractFeatureDlg_H
#define ExtractFeatureDlg_H

#include "CATDlgDialog.h"
#include "CATDlgInclude.h"


class ExtractFeatureDlg: public CATDlgDialog
{

  DeclareResource( ExtractFeatureDlg, CATDlgDialog )

  public:

  ExtractFeatureDlg();
  virtual ~ExtractFeatureDlg();

  void Build ();
  CATDlgPushButton* GetPushButton(int iValue);
  CATDlgEditor*      GetEditor(int iValue);

  void OnDlgWindCloseNotification(CATCommand* cmd, CATNotification* evt, CATCommandClientData data);

  protected:

  private:

 CATDlgFrame*      _Frame001;
 CATDlgPushButton*      _PushButton002;
 CATDlgPushButton*      _PushButton003;
 CATDlgPushButton*      _PushButton004;
 CATDlgPushButton*      _PushButton005;
 CATDlgFrame*      _Frame006;
 CATDlgLabel*      _Label007;
 CATDlgEditor*      _Editor008;
 CATDlgFrame*      _Frame009;
 CATDlgLabel*      _Label010;
 CATDlgLabel*      _Label011;
 CATDlgLabel*      _Label012;
 CATDlgEditor*      _Editor013;
 CATDlgEditor*      _Editor014;
 CATDlgEditor*      _Editor015;
 CATDlgPushButton*      _PushButton023;
 CATDlgPushButton*      _PushButton024;
 CATDlgPushButton*      _PushButton025;
 CATDlgFrame*      _Frame016;
 CATDlgLabel*      _Label017;
 CATDlgLabel*      _Label018;
 CATDlgLabel*      _Label019;
 CATDlgEditor*      _Editor020;
 CATDlgEditor*      _Editor021;
 CATDlgEditor*      _Editor022;
 CATDlgEditor*      _Editor026;
 CATDlgEditor*      _Editor027;
};

//----------------------------------------------------------------------

#endif
