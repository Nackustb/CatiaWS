#include "CalculateAllowanceCmd.h"
#include "CATIndicationAgent.h"
#include "CATMathPlane.h"
#include "CATDialogState.h"
#include "CATCreateExternalObject.h"
CATCreateClass( CalculateAllowanceCmd);

CalculateAllowanceCmd::CalculateAllowanceCmd() :
  CATStateCommand ("CalculateAllowanceCmd", CATDlgEngOneShot, CATCommandModeExclusive) 
  ,_Indication(NULL)
  ,_pDlg(NULL)
{
	_pDlg = new CalculateAllowanceDlg();
	_pDlg->Build();
	_pDlg->SetVisibility(CATDlgShow);
}


CalculateAllowanceCmd::~CalculateAllowanceCmd()
{
    if (_Indication != NULL) _Indication->RequestDelayedDestruction();
   	if (_pDlg != NULL) _pDlg->RequestDelayedDestruction();
}



void CalculateAllowanceCmd::BuildGraph()
{



  _Indication = new CATIndicationAgent ("Indication");
  CATMathPlane PlaneXY;
  _Indication -> SetMathPlane (PlaneXY);
  CATDialogState * initialState = GetInitialState("initialState");
  initialState -> AddDialogAgent (_Indication);
  
  AddTransition( initialState, NULL, 
                 IsOutputSetCondition (_Indication),
                 Action ((ActionMethod) &CalculateAllowanceCmd::ActionOne));
}



CATBoolean CalculateAllowanceCmd::ActionOne( void *data )
{
 
  return TRUE;
}
