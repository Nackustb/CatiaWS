#include "AddDocDlg.h"
#include "CATApplicationFrame.h"
#include "CATDlgGridConstraints.h"
#include "CATMsgCatalog.h"

#ifdef AddDocDlg_ParameterEditorInclude
#include "CATIParameterEditorFactory.h"
#include "CATIParameterEditor.h"
#include "CATICkeParm.h"
#endif

AddDocDlg::AddDocDlg() :
CATDlgDialog((CATApplicationFrame::GetApplicationFrame())->GetMainWindow(),
			 "AddDocDlg",
			 CATDlgWndNoButton | CATDlgGridLayout)
{
	_Frame006 = NULL;
	_PushButton003 = NULL;
	_Label004 = NULL;
	_PushButton002 = NULL;
	_Editor005 = NULL;

	_Frame007 = NULL;
	_Label008 = NULL;
	_Label009 = NULL;
	_Label011 = NULL;
	_Label010 = NULL;
	_Label012 = NULL;
	_Label013 = NULL;

	_Spinner020 = NULL;
	_Spinner022 = NULL;
	_Spinner023 = NULL;
	_Spinner024 = NULL;
	_Spinner026 = NULL;
	_Spinner027 = NULL;

	_PushButton028 = NULL;
	_SelectorList029 = NULL;
	_Label030 = NULL;

	_pDlgFile = NULL;
	_spImportedProduct = NULL_var;
}

AddDocDlg::~AddDocDlg()
{
	_Frame006 = NULL;
	_PushButton003 = NULL;
	_Label004 = NULL;
	_PushButton002 = NULL;
	_Editor005 = NULL;

	_Frame007 = NULL;
	_Label008 = NULL;
	_Label009 = NULL;
	_Label011 = NULL;
	_Label010 = NULL;
	_Label012 = NULL;
	_Label013 = NULL;

	_Spinner020 = NULL;
	_Spinner022 = NULL;
	_Spinner023 = NULL;
	_Spinner024 = NULL;
	_Spinner026 = NULL;
	_Spinner027 = NULL;

	_PushButton028 = NULL;
	_SelectorList029 = NULL;
	_Label030 = NULL;

	_pDlgFile = NULL;
	_spImportedProduct = NULL_var;
}

void AddDocDlg::Build()
{
	_pDlgFile = new CATDlgFile(this, "Ñ¡ÔñÎÄ¼þ", CATDlgFileSave);

	_Frame006 = new CATDlgFrame(this, "Frame006", CATDlgGridLayout);
	_Frame006->SetGridConstraints(0, 0, 1, 1, CATGRID_4SIDES);

	_PushButton003 = new CATDlgPushButton(_Frame006, "PushButton003");
	_PushButton003->SetGridConstraints(0, 0, 2, 1, CATGRID_4SIDES);

	_Label004 = new CATDlgLabel(_Frame006, "Label004", CATDlgLabCenter);
	_Label004->SetGridConstraints(1, 0, 1, 1, CATGRID_4SIDES);

	_PushButton002 = new CATDlgPushButton(_Frame006, "PushButton002");
	_PushButton002->SetGridConstraints(2, 0, 2, 1, CATGRID_4SIDES);

	_Editor005 = new CATDlgEditor(_Frame006, "Editor005");
	_Editor005->SetGridConstraints(1, 1, 1, 1, CATGRID_4SIDES);

	_Frame007 = new CATDlgFrame(_Frame006, "Frame007", CATDlgGridLayout);
	_Frame007->SetGridConstraints(3, 0, 2, 1, CATGRID_4SIDES);

	_Label008 = new CATDlgLabel(_Frame007, "Label008");
	_Label008->SetGridConstraints(1, 0, 1, 1, CATGRID_4SIDES);

	_Label009 = new CATDlgLabel(_Frame007, "Label009");
	_Label009->SetGridConstraints(2, 0, 1, 1, CATGRID_4SIDES);

	_Label010 = new CATDlgLabel(_Frame007, "Label010");
	_Label010->SetGridConstraints(3, 0, 1, 1, CATGRID_4SIDES);

	_Label011 = new CATDlgLabel(_Frame007, "Label011");
	_Label011->SetGridConstraints(4, 0, 1, 1, CATGRID_4SIDES);

	_Label012 = new CATDlgLabel(_Frame007, "Label012");
	_Label012->SetGridConstraints(5, 0, 1, 1, CATGRID_4SIDES);

	_Label013 = new CATDlgLabel(_Frame007, "Label013");
	_Label013->SetGridConstraints(6, 0, 1, 1, CATGRID_4SIDES);

	_Spinner020 = new CATDlgSpinner(_Frame007, "Spinner020", CATDlgSpnEntry | CATDlgSpnDouble);
	_Spinner020->SetMinMaxStep(-10000.000000, 10000.000000, 0.0010000);
	_Spinner020->SetUnit(CATDlgControl::Millimeter);
	_Spinner020->SetPrecision(0);
	_Spinner020->SetGridConstraints(1, 1, 1, 1, CATGRID_4SIDES);

	_Spinner022 = new CATDlgSpinner(_Frame007, "Spinner022", CATDlgSpnEntry | CATDlgSpnDouble);
	_Spinner022->SetMinMaxStep(-10000.000000, 10000.000000, 0.0010000);
	_Spinner022->SetUnit(CATDlgControl::Millimeter);
	_Spinner022->SetPrecision(0);
	_Spinner022->SetGridConstraints(2, 1, 1, 1, CATGRID_4SIDES);

	_Spinner023 = new CATDlgSpinner(_Frame007, "Spinner023", CATDlgSpnEntry | CATDlgSpnDouble);
	_Spinner023->SetMinMaxStep(-10000.000000, 10000.000000, 0.0010000);
	_Spinner023->SetUnit(CATDlgControl::Millimeter);
	_Spinner023->SetPrecision(0);
	_Spinner023->SetGridConstraints(3, 1, 1, 1, CATGRID_4SIDES);

	double deg2rad = CATPI / 180.0;

	_Spinner024 = new CATDlgSpinner(_Frame007, "Spinner024", CATDlgSpnEntry | CATDlgSpnDouble);
	_Spinner024->SetMinMaxStep(-360.0 * deg2rad, 360.0 * deg2rad, 1.0 * deg2rad);
	_Spinner024->SetUnit(CATDlgControl::Degree);
	_Spinner024->SetPrecision(0);
	_Spinner024->SetGridConstraints(4, 1, 1, 1, CATGRID_4SIDES);

	_Spinner027 = new CATDlgSpinner(_Frame007, "Spinner027", CATDlgSpnEntry | CATDlgSpnDouble);
	_Spinner027->SetMinMaxStep(-360.0 * deg2rad, 360.0 * deg2rad, 1.0 * deg2rad);
	_Spinner027->SetUnit(CATDlgControl::Degree);
	_Spinner027->SetPrecision(0);
	_Spinner027->SetGridConstraints(5, 1, 1, 1, CATGRID_4SIDES);

	_Spinner026 = new CATDlgSpinner(_Frame007, "Spinner026", CATDlgSpnEntry | CATDlgSpnDouble);
	_Spinner026->SetMinMaxStep(-360.0 * deg2rad, 360.0 * deg2rad, 1.0 * deg2rad);
	_Spinner026->SetUnit(CATDlgControl::Degree);
	_Spinner026->SetPrecision(0);
	_Spinner026->SetGridConstraints(6, 1, 1, 1, CATGRID_4SIDES);

	_SelectorList029 = new CATDlgSelectorList(_Frame007, "SelectorList029");
	_SelectorList029->SetVisibleTextHeight(1);
	_SelectorList029->SetGridConstraints(0, 1, 1, 1, CATGRID_4SIDES);

	_Label030 = new CATDlgLabel(_Frame007, "Label030");
	_Label030->SetGridConstraints(0, 0, 1, 1, CATGRID_4SIDES);

	_PushButton028 = new CATDlgPushButton(_Frame006, "PushButton028");
	_PushButton028->SetGridConstraints(4, 0, 2, 1, CATGRID_4SIDES);

	AddAnalyseNotificationCB(_pDlgFile,
		_pDlgFile->GetDiaOKNotification(),
		(CATCommandMethod)&AddDocDlg::ActOnOK,
		NULL);

	AddAnalyseNotificationCB(_PushButton003,
		_PushButton003->GetPushBActivateNotification(),
		(CATCommandMethod)&AddDocDlg::OnPushButton003PushBActivateNotification,
		NULL);

	AddAnalyseNotificationCB(_PushButton002,
		_PushButton002->GetPushBActivateNotification(),
		(CATCommandMethod)&AddDocDlg::OnPushButton002PushBActivateNotification,
		NULL);

	AddAnalyseNotificationCB(_PushButton028,
		_PushButton028->GetPushBActivateNotification(),
		(CATCommandMethod)&AddDocDlg::OnPushButton028PushBActivateNotification,
		NULL);

	AddAnalyseNotificationCB(this,
		GetWindCloseNotification(),
		(CATCommandMethod)&AddDocDlg::DocWindCloseNotification,
		NULL);
}

void AddDocDlg::OnPushButton003PushBActivateNotification(CATCommand* cmd, CATNotification* evt, CATCommandClientData data)
{
	_pDlgFile->SetVisibility(CATDlgShow);
	CATUnicodeString names[2] = { "CATPart files", "CATProduct files" };
	CATString patterns[2] = { "*.CATPart", "*.CATProduct" };
	_pDlgFile->SetFilterStrings(names, patterns, 2);
	_pDlgFile->SetFileName("Part1.CATPart");
}

void AddDocDlg::OnPushButton002PushBActivateNotification(CATCommand* cmd, CATNotification* evt, CATCommandClientData data)
{
	if (_Editor005 == NULL) return;

	CATUnicodeString fileName = _Editor005->GetText();
	//cout << "Open fileName is " << fileName << endl;

	CATDocument* pInsertDoc = NULL;
	HRESULT rc = CATDocumentServices::OpenDocument(fileName, pInsertDoc);
	if (FAILED(rc) || pInsertDoc == NULL) return;

	CATFrmLayout* pLayout = CATFrmLayout::GetCurrentLayout();
	if (pLayout == NULL) return;
	CATFrmWindow* pWindow = pLayout->GetCurrentWindow();
	if (pWindow == NULL) return;
	CATFrmEditor* pEditor = pWindow->GetEditor();
	if (pEditor == NULL) return;
	CATDocument* pDoc = pEditor->GetDocument();
	if (pDoc == NULL) return;

	CATIDocRoots* piDocRootsOnDoc = NULL;
	rc = pDoc->QueryInterface(IID_CATIDocRoots, (void**)&piDocRootsOnDoc);
	if (FAILED(rc) || piDocRootsOnDoc == NULL) return;

	CATIProduct_var spRootProduct;
	CATListValCATBaseUnknown_var* pRootProducts = piDocRootsOnDoc->GiveDocRoots();
	if (pRootProducts != NULL)
	{
		if (pRootProducts->Size() > 0) spRootProduct = (*pRootProducts)[1];
		delete pRootProducts;
		pRootProducts = NULL;
	}
	piDocRootsOnDoc->Release();
	piDocRootsOnDoc = NULL;
	if (spRootProduct == NULL_var) return;

	CATIDocRoots* piDocRootsOnNewDoc = NULL;
	rc = pInsertDoc->QueryInterface(IID_CATIDocRoots, (void**)&piDocRootsOnNewDoc);
	if (FAILED(rc) || piDocRootsOnNewDoc == NULL) return;

	CATIProduct_var spProduct;
	CATListValCATBaseUnknown_var* pRootProducts2 = piDocRootsOnNewDoc->GiveDocRoots();
	if (pRootProducts2 != NULL)
	{
		if (pRootProducts2->Size() > 0) spProduct = (*pRootProducts2)[1];
		delete pRootProducts2;
		pRootProducts2 = NULL;
	}
	piDocRootsOnNewDoc->Release();
	piDocRootsOnNewDoc = NULL;
	if (spProduct == NULL_var) return;

	spRootProduct->AddProduct(spProduct);

	_spImportedProduct = spProduct;

	CATUnicodeString name;
	CATIProduct* piProd = NULL;
	HRESULT hrName = spProduct->QueryInterface(IID_CATIProduct, (void**)&piProd);
	if (SUCCEEDED(hrName) && piProd != NULL)
	{
		name = piProd->GetPartNumber();
		piProd->Release();
		piProd = NULL;
	}

	if (_SelectorList029)
	{
		_SelectorList029->SetLine(name);
	}

	CATIProduct* piRootProduct = NULL;
	rc = spRootProduct->QueryInterface(IID_CATIProduct, (void**)&piRootProduct);
	if (SUCCEEDED(rc) && piRootProduct != NULL)
	{
		CATIModelEvents_var spEvents = piRootProduct;
		CATModify ModifyEvent(piRootProduct);
		spEvents->Dispatch(ModifyEvent);

		CATIRedrawEvent_var spRedraw = piRootProduct;
		spRedraw->Redraw();

		piRootProduct->Release();
		piRootProduct = NULL;
	}
}

void AddDocDlg::OnPushButton028PushBActivateNotification(CATCommand* cmd, CATNotification* evt, CATCommandClientData data)
{
	if (_spImportedProduct == NULL_var) return;

	double xm = _Spinner020->GetValue();
	double ym = _Spinner022->GetValue();
	double zm = _Spinner023->GetValue();
	double xr = _Spinner024->GetValue();
	double yr = _Spinner027->GetValue();
	double zr = _Spinner026->GetValue();
	//cout << "xm=" << xm << " ym=" << ym << " zm=" << zm << " xr=" << xr << " yr=" << yr << " zr=" << zr << endl;

	HRESULT rc = E_FAIL;

	CATIMovable* piMovableOnProd = NULL;
	rc = _spImportedProduct->QueryInterface(IID_CATIMovable, (void**)&piMovableOnProd);
	if (FAILED(rc) || piMovableOnProd == NULL) return;

	CATMathTransformation InitialPosition;
	rc = piMovableOnProd->GetAbsPosition(InitialPosition);
	piMovableOnProd->Release();
	piMovableOnProd = NULL;
	if (FAILED(rc)) return;

	double radianAnglex = xr;
	double radianAngley = yr;
	double radianAnglez = zr;

	double valuearray[16];
	valuearray[0]  = CATCos(radianAngley) * CATCos(radianAnglez);
	valuearray[1]  = CATCos(radianAngley) * CATSin(radianAnglez);
	valuearray[2]  = -CATSin(radianAngley);
	valuearray[3]  = 0;

	valuearray[4]  = CATSin(radianAnglex) * CATSin(radianAngley) * CATCos(radianAnglez) - CATCos(radianAnglex) * CATSin(radianAnglez);
	valuearray[5]  = CATSin(radianAnglex) * CATSin(radianAngley) * CATSin(radianAnglez) + CATCos(radianAnglex) * CATCos(radianAnglez);
	valuearray[6]  = CATSin(radianAnglex) * CATCos(radianAngley);
	valuearray[7]  = 0;

	valuearray[8]  = CATCos(radianAnglex) * CATSin(radianAngley) * CATCos(radianAnglez) + CATSin(radianAnglex) * CATSin(radianAnglez);
	valuearray[9]  = CATCos(radianAnglex) * CATSin(radianAngley) * CATSin(radianAnglez) - CATSin(radianAnglex) * CATCos(radianAnglez);
	valuearray[10] = CATCos(radianAnglex) * CATCos(radianAngley);
	valuearray[11] = 0;

	valuearray[12] = xm;
	valuearray[13] = ym;
	valuearray[14] = zm;
	valuearray[15] = 1;

	CATMathTransformation MovePosition, ResultPosition;
	MovePosition.SetCoef(valuearray, 16);

	ResultPosition = TwoMatrixesMultiply(MovePosition, InitialPosition);

	CATIMovable* piMovableOnInstPrd = NULL;
	rc = _spImportedProduct->QueryInterface(IID_CATIMovable, (void**)&piMovableOnInstPrd);
	if (SUCCEEDED(rc) && piMovableOnInstPrd != NULL)
	{
		piMovableOnInstPrd->SetPosition(ResultPosition, NULL_var);
		piMovableOnInstPrd->Release();
		piMovableOnInstPrd = NULL;
	}
}

CATMathTransformation AddDocDlg::TwoMatrixesMultiply(CATMathTransformation iMatrix1, CATMathTransformation iMatrix2)
{
	double v1[16];
	double v2[16];
	double vR[16];
	iMatrix1.GetCoef(v1, 16);
	iMatrix2.GetCoef(v2, 16);

	vR[0]  = v1[0]*v2[0]   + v1[4]*v2[1]   + v1[8]*v2[2]   + v1[12]*v2[3];
	vR[1]  = v1[1]*v2[0]   + v1[5]*v2[1]   + v1[9]*v2[2]   + v1[13]*v2[3];
	vR[2]  = v1[2]*v2[0]   + v1[6]*v2[1]   + v1[10]*v2[2]  + v1[14]*v2[3];
	vR[3]  = v1[3]*v2[0]   + v1[7]*v2[1]   + v1[11]*v2[2]  + v1[15]*v2[3];

	vR[4]  = v1[0]*v2[4]   + v1[4]*v2[5]   + v1[8]*v2[6]   + v1[12]*v2[7];
	vR[5]  = v1[1]*v2[4]   + v1[5]*v2[5]   + v1[9]*v2[6]   + v1[13]*v2[7];
	vR[6]  = v1[2]*v2[4]   + v1[6]*v2[5]   + v1[10]*v2[6]  + v1[14]*v2[7];
	vR[7]  = v1[3]*v2[4]   + v1[7]*v2[5]   + v1[11]*v2[6]  + v1[15]*v2[7];

	vR[8]  = v1[0]*v2[8]   + v1[4]*v2[9]   + v1[8]*v2[10]  + v1[12]*v2[11];
	vR[9]  = v1[1]*v2[8]   + v1[5]*v2[9]   + v1[9]*v2[10]  + v1[13]*v2[11];
	vR[10] = v1[2]*v2[8]   + v1[6]*v2[9]   + v1[10]*v2[10] + v1[14]*v2[11];
	vR[11] = v1[3]*v2[8]   + v1[7]*v2[9]   + v1[11]*v2[10] + v1[15]*v2[11];

	vR[12] = v1[0]*v2[12]  + v1[4]*v2[13]  + v1[8]*v2[14]  + v1[12]*v2[15];
	vR[13] = v1[1]*v2[12]  + v1[5]*v2[13]  + v1[9]*v2[14]  + v1[13]*v2[15];
	vR[14] = v1[2]*v2[12]  + v1[6]*v2[13]  + v1[10]*v2[14] + v1[14]*v2[15];
	vR[15] = v1[3]*v2[12]  + v1[7]*v2[13]  + v1[11]*v2[14] + v1[15]*v2[15];

	CATMathTransformation oRMatrix;
	oRMatrix.SetCoef(vR, 16);
	return oRMatrix;
}

void AddDocDlg::ActOnOK(CATCommand* cmd, CATNotification* evt, CATCommandClientData data)
{
	CATUnicodeString fileName;
	_pDlgFile->GetSelection(fileName);
	_Editor005->SetText(fileName);
	_pDlgFile->SetVisibility(CATDlgHide);
}

void AddDocDlg::DocWindCloseNotification(CATCommand* cmd, CATNotification* evt, CATCommandClientData data)
{
	this->SetVisibility(CATDlgHide);
}

CATDlgSelectorList* AddDocDlg::GetSelectorList(int iValue)
{
	switch (iValue)
	{
	case 1: return _SelectorList029;
	}
	return NULL;
}

CATDlgSpinner* AddDocDlg::GetSpinner(int iValue)
{
	switch (iValue)
	{
	case 1: return _Spinner020;
	case 2: return _Spinner022;
	case 3: return _Spinner023;
	case 4: return _Spinner024;
	case 5: return _Spinner027;
	case 6: return _Spinner026;
	}
	return NULL;
}

void AddDocDlg::SetTargetProduct(CATIProduct_var iProd)
{
	_spImportedProduct = iProd;
}