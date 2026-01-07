#ifndef PadDlgCmd_H
#define PadDlgCmd_H

#include "CATStateCommand.h"
#include "CATBoolean.h"
#include "PadDlg.h"
#include "CATDialogAgent.h"
#include "CATPathElementAgent.h"
#include "CATHSO.h"
#include "CATISO.h"
#include "CATISpecObject.h"
#include "CATIProduct.h"
#include "CATFrmEditor.h"
class CATIndicationAgent;


class PadDlgCmd: public CATStateCommand
{

  DeclareResource( PadDlgCmd, CATStateCommand )

  public:

  PadDlgCmd();
  virtual ~PadDlgCmd();

  virtual void     BuildGraph();

  CATBoolean ActionOK (void *data);
  CATBoolean ActionAPPLY (void *data);
  CATBoolean ActionCLOSE (void *data);
  virtual CATStatusChangeRC Activate(CATCommand * iFromClient,CATNotification * iEvtDat);
  virtual CATStatusChangeRC Desactivate(CATCommand * iFromClient,CATNotification * iEvtDat);
  virtual CATStatusChangeRC Cancel(CATCommand * iFromClient,CATNotification * iEvtDat);


  private:
  PadDlg* _pDlg;
  CATFrmEditor * _pEditor;   // µ±Ç°±à¼­Æ÷
  CATDialogAgent* _pOKAgent;          // OK
  CATDialogAgent* _pAPPLYAgent;       // APPLY
  CATDialogAgent* _pCLOSEAgent;       // CLOSE
};

//----------------------------------------------------------------------

#endif
