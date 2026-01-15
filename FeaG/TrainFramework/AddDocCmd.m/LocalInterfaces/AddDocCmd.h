#ifndef AddDocCmd_H
#define AddDocCmd_H

//=================================================================
// Command 基类 / 基础类型
//=================================================================
#include "CATStateCommand.h"
#include "CATBoolean.h"

//=================================================================
// Dialog
//=================================================================
#include "AddDocDlg.h"

//=================================================================
// Editor / Selection（HSO/ISO）
//=================================================================
#include "CATFrmEditor.h"
#include "CATHSO.h"
#include "CATISO.h"

//=================================================================
// Selection Agent（选择 Product）
//=================================================================
#include "CATPathElementAgent.h"
#include "CATPathElement.h"

//=================================================================
// Product
//=================================================================
#include "CATIProduct.h"

class CATIndicationAgent;

class AddDocCmd : public CATStateCommand
{
	DeclareResource(AddDocCmd, CATStateCommand)

public:
	AddDocCmd();
	virtual ~AddDocCmd();

	virtual void BuildGraph();
	virtual CATBoolean ActionOne(void* data);

private:
	// Dialog
	AddDocDlg* _pDlg;

	// Indication（如果后续需要点选）
	CATIndicationAgent* _Indication;

	// Editor / HSO / ISO
	CATFrmEditor* _pEditor;
	CATHSO*       _pHSO;
	CATISO*       _pISO;

	// 选择 Product 的 Agent
	CATPathElementAgent* _pSelectProductPathAgent;

	// 当前选中的 Product
	CATIProduct_var _spSelectedProduct;

	// 当前激活 Product
	CATIProduct_var _spActiveProduct;
};

#endif
