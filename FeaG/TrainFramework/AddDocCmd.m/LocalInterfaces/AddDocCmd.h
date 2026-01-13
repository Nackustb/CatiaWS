#ifndef AddDocCmd_H
#define AddDocCmd_H

#include "CATStateCommand.h"
#include "CATBoolean.h"

#include "AddDocDlg.h"

#include "CATFrmEditor.h"
#include "CATHSO.h"
#include "CATISO.h"

#include "CATPathElementAgent.h"
#include "CATPathElement.h"

#include "CATIProduct.h"


class CATIndicationAgent;


class AddDocCmd: public CATStateCommand
{
  DeclareResource(AddDocCmd, CATStateCommand)

public:
  AddDocCmd();
  virtual ~AddDocCmd();

  virtual void BuildGraph();
  virtual CATBoolean ActionOne(void * data);

private:
  AddDocDlg* _pDlg;

  CATIndicationAgent* _Indication;

  CATFrmEditor* _pEditor;
  CATHSO* _pHSO;
  CATISO* _pISO;

  // 选择 Product 的 Agent
  CATPathElementAgent* _pSelectProductPathAgent;

  // 当前选中的 Product
  CATIProduct_var _spSelectedProduct;

  // 当前激活 Product
  CATIProduct_var _spActiveProduct;
};

//----------------------------------------------------------------------

#endif
