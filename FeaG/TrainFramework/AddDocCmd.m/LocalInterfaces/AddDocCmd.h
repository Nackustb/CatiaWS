#ifndef AddDocCmd_H
#define AddDocCmd_H

#include "CATStateCommand.h"
#include "CATBoolean.h"
#include "AddDocDlg.h"
class CATIndicationAgent;


class AddDocCmd: public CATStateCommand
{
  // Allows customization/internationalization of command's messages
  // ---------------------------------------------------------------
  DeclareResource( AddDocCmd, CATStateCommand )

  public:

  AddDocCmd();
  virtual ~AddDocCmd();

  virtual void     BuildGraph();

  virtual CATBoolean  ActionOne(void * data);

  private:
  AddDocDlg* _pDlg;
  CATIndicationAgent	* _Indication;
};

//----------------------------------------------------------------------

#endif
