#ifndef ExtractfeatureCmd_H
#define ExtractfeatureCmd_H

#include "CATStateCommand.h"
#include "CATBoolean.h"
#include "ExtractFeatureDlg.h"
#include <iostream.h>
#include "CATDialogAgent.h"
#include "CATPathElementAgent.h"

#include "CATCircle.h"
#include "CATMathCircle.h"
#include "CATPathElement.h"
#include "CATMathConstant.h"
#include "CATLine.h"
#include "CATMathPoint.h"
#include "CATMathDirection.h"
#include "CATMathVector.h"
#include "CATPlane.h"
#include "CATPoint.h"

class CATIndicationAgent;
class CATPathElementAgent;
class CATDialogAgent;


class ExtractfeatureCmd: public CATStateCommand
{
  DeclareResource( ExtractfeatureCmd, CATStateCommand )

  public:

  ExtractfeatureCmd();
  virtual ~ExtractfeatureCmd();
  CATBoolean GetCircleElement(void *data);

  CATBoolean GetLineElement(void *data);

  CATBoolean GetPlaneElement(void *data);

  CATBoolean GetCPointElement(void *data);

  CATBoolean GetProductElement(void *data);

  CATBoolean CDlgAgentClear( void *data );

  CATBoolean LDlgAgentClear( void *data );

  CATBoolean PDlgAgentClear( void *data );

  CATBoolean CPDlgAgentClear( void *data );

  CATBoolean ProDlgAgentClear( void *data );

  void SetCParameter(double r,double cx2,double cy2,double cz2);

  void SetCPParameter(double cx,double cy,double cz);

  void SetLParameter(double lx,double ly,double lz);

  void SetPParameter(double px1,double py1,double pz1,double px2,double py2,double pz2);

  void SetProParameter(CATUnicodeString name);

  void OnCalButton(CATCommand* cmd, CATNotification* evt, CATCommandClientData data);

  double GetCParameter();

  double GetLParameter();

  double GetPParameter();

  double r,cx,cy,cz,cx2,cy2,cz2,lx,ly,lz,px1,py1,pz1,px2,py2,pz2,px,py,pz,A[3];
  CATUnicodeString R,Cx,Cy,Cz,Cx2,Cy2,Cz2,Lx,Ly,Lz,Px,Py,Pz,A1,A2,A3,NAME;

  virtual void     BuildGraph();


  private:
  ExtractFeatureDlg* _pDlg;
  CATIndicationAgent	* _Indication;

  CATDialogAgent * _CDlgAgent;
  CATDialogAgent * _LDlgAgent;
  CATDialogAgent * _PDlgAgent;
  CATDialogAgent * _CPDlgAgent;
  CATDialogAgent * _ProDlgAgent;
  CATDialogAgent * _CalDlgAgent;
  CATPathElementAgent * _CElementAgent;
  CATPathElementAgent * _LElementAgent;
  CATPathElementAgent * _PElementAgent;
  CATPathElementAgent * _CPElementAgent;
  CATPathElementAgent * _ProElementAgent;
};

//----------------------------------------------------------------------

#endif
