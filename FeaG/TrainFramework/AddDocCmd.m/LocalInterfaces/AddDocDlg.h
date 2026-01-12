#ifndef AddDocDlg_H
#define AddDocDlg_H
#include "CATDlgDialog.h"
#include "CATDlgInclude.h"
#include "CATDlgFile.h"
#include "CATDocumentServices.h"
#include <iostream.h>
#include "CATIEditor.h"
#include "CATIDocumentEdit.h"
#include "CATDocument.h"
#include "CATFrmWindow.h"
#include "CATFrmEditor.h"
#include <windows.h>

class AddDocDlg: public CATDlgDialog
{

  DeclareResource( AddDocDlg, CATDlgDialog )

  public:

  AddDocDlg();
  virtual ~AddDocDlg();

  void Build ();
  virtual void DocWindCloseNotification (CATCommand *, CATNotification* , CATCommandClientData data);

  protected:
  virtual void OnPushButton002PushBActivateNotification (CATCommand *, CATNotification* , CATCommandClientData data);
  virtual void OnPushButton003PushBActivateNotification (CATCommand *, CATNotification* , CATCommandClientData data);

  private:

 CATDlgFile *pDlgFile;
 void ActOnOK(CATCommand * cmd,CATNotification * evt,CATCommandClientData data);
 CATDlgPushButton*      _PushButton002;
 CATDlgPushButton*      _PushButton003;
 CATDlgLabel*      _Label004;
 CATDlgEditor*      _Editor005;
};

//----------------------------------------------------------------------

#endif
