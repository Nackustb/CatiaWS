#ifndef PadDlg_H
#define PadDlg_H

#include "CATDlgDialog.h"
#include "CATDlgInclude.h"


class PadDlg: public CATDlgDialog
{

  DeclareResource( PadDlg, CATDlgDialog )

  public:

  PadDlg();
  virtual ~PadDlg();

  void Build ();
  void BuildMore();
  CATDlgEditor* GetEditor(int iValue);

  virtual void OnPadDlgWindCloseNotification (CATCommand *, CATNotification* , CATCommandClientData data);

  protected:

  private:


 CATDlgLabel*      _Label001;
 CATDlgLabel*      _Label002;
 CATDlgLabel*      _Label003;
 CATDlgEditor*      _Editor004;
 CATDlgEditor*      _Editor005;
 CATDlgEditor*      _Editor006;
 CATDlgLabel*      _Label007;
 CATDlgLabel*      _Label008;
 CATDlgLabel*      _Label009;
};


#endif

