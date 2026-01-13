#include "AddDocCmd.h"
#include "CATIndicationAgent.h"
#include "CATMathPlane.h"

#include "CATCreateExternalObject.h"
CATCreateClass( AddDocCmd);


//-------------------------------------------------------------------------
// Constructor
//-------------------------------------------------------------------------
AddDocCmd::AddDocCmd() :
  CATStateCommand ("AddDocCmd", CATDlgEngOneShot, CATCommandModeExclusive)
  ,_Indication(NULL)
  ,_pDlg(NULL)
  ,_pEditor(NULL)
  ,_pHSO(NULL)
  ,_pISO(NULL)
  ,_pSelectProductPathAgent(NULL)
  ,_spSelectedProduct(NULL_var)
  ,_spActiveProduct(NULL_var)
{
	_pDlg = new AddDocDlg();
	_pDlg->Build();
	_pDlg->SetVisibility(CATDlgShow);
}

//-------------------------------------------------------------------------
// Destructor
//-------------------------------------------------------------------------
AddDocCmd::~AddDocCmd()
{
	if (_Indication != NULL) _Indication->RequestDelayedDestruction();
	if (_pDlg) _pDlg->RequestDelayedDestruction();

	if (_pSelectProductPathAgent) { delete _pSelectProductPathAgent; _pSelectProductPathAgent = NULL; }

	_pEditor = NULL;
	_pHSO = NULL;
	_pISO = NULL;
}


//-------------------------------------------------------------------------
// BuildGraph()
//-------------------------------------------------------------------------
void AddDocCmd::BuildGraph()
{
	// 选择 Product 的 agent（图形区/树上点选）
	_pSelectProductPathAgent = new CATPathElementAgent("select product agent");
	_pSelectProductPathAgent->SetOrderedElementType("CATIProduct");
	_pSelectProductPathAgent->SetBehavior(CATDlgEngWithPrevaluation | CATDlgEngWithCSO | CATDlgEngWithUndo);

	// 初始状态
	CATDialogState * InitialState = GetInitialState("Initial State");
	InitialState->AddDialogAgent(_pSelectProductPathAgent);

	AddTransition(InitialState, InitialState,
		IsOutputSetCondition(_pSelectProductPathAgent),
		Action((ActionMethod)&AddDocCmd::ActionOne));
}


//-------------------------------------------------------------------------
// ActionOne ()
//-------------------------------------------------------------------------
CATBoolean AddDocCmd::ActionOne(void *data)
{
	if (_pSelectProductPathAgent == NULL) return TRUE;

	CATPathElement * pPath = _pSelectProductPathAgent->GetValue();
	if (pPath == NULL) return TRUE;

	CATIProduct_var spProd = pPath->FindElement(IID_CATIProduct);
	if (spProd == NULL_var)
	{
		_pSelectProductPathAgent->InitializeAcquisition();
		return TRUE;
	}

	_spSelectedProduct = spProd;


	if (_pDlg)
	{
		_pDlg->SetTargetProduct(spProd);   // 关键：让位姿按钮的目标跟随选择
		CATDlgSelectorList * pList = _pDlg->GetSelectorList(1);
		if (pList)
		{
			CATUnicodeString name;

			CATIProduct * piProd = NULL;
			HRESULT hr = spProd->QueryInterface(IID_CATIProduct, (void**)&piProd);
			if (SUCCEEDED(hr) && piProd != NULL)
			{
				name = piProd->GetPartNumber();
				piProd->Release();
				piProd = NULL;
			}

			pList->ClearLine();
			pList->SetLine(name);
		}
	}

	_pSelectProductPathAgent->InitializeAcquisition();
	return TRUE;
}
