#ifndef CalculateAllowanceCmd_H
#define CalculateAllowanceCmd_H

#include "CATStateCommand.h"
#include "CATBoolean.h"
#include "CalculateAllowanceDlg.h"

class CATIndicationAgent;


class CalculateAllowanceCmd: public CATStateCommand
{

  DeclareResource( CalculateAllowanceCmd, CATStateCommand )

  public:

  CalculateAllowanceCmd();
  virtual ~CalculateAllowanceCmd();


  virtual void     BuildGraph();


  virtual CATBoolean  ActionOne(void * data);

  private:
  CalculateAllowanceDlg * _pDlg;
  CATIndicationAgent	* _Indication;
};

//----------------------------------------------------------------------

#endif
