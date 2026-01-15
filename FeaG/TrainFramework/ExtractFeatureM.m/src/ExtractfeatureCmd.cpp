#include "ExtractfeatureCmd.h"
#include "CATIndicationAgent.h"
#include "CATMathPlane.h"
#include "CATIProduct.h"

#include "CATCreateExternalObject.h"
CATCreateClass( ExtractfeatureCmd);

ExtractfeatureCmd::ExtractfeatureCmd() :
  CATStateCommand ("ExtractfeatureCmd", CATDlgEngOneShot, CATCommandModeExclusive) 
  ,_Indication(NULL)
  ,_pDlg(NULL)
  ,_CElementAgent(NULL)
  ,_LDlgAgent(NULL)
  ,_LElementAgent(NULL)
  ,_PDlgAgent(NULL)
  ,_PElementAgent(NULL)
  ,_CPDlgAgent(NULL)
  ,_CPElementAgent(NULL)
  ,_ProDlgAgent(NULL)
  ,_ProElementAgent(NULL)
{
	_pDlg = new ExtractFeatureDlg();
	_pDlg->Build();
	_pDlg->SetVisibility(CATDlgShow);
}

ExtractfeatureCmd::~ExtractfeatureCmd()
{
   if (_Indication != NULL) 
      _Indication->RequestDelayedDestruction();
   if (_CDlgAgent != NULL) 
	   _CDlgAgent->RequestDelayedDestruction();
   if (_CElementAgent != NULL) 
	   _CElementAgent->RequestDelayedDestruction();
   if (_LDlgAgent != NULL) 
	   _LDlgAgent->RequestDelayedDestruction();
   if (_LElementAgent != NULL) 
	   _LElementAgent->RequestDelayedDestruction();
   if (_PDlgAgent != NULL) 
	   _PDlgAgent->RequestDelayedDestruction();
   if (_PElementAgent != NULL) 
	   _PElementAgent->RequestDelayedDestruction();
   if (_CPDlgAgent != NULL) 
	   _CPDlgAgent->RequestDelayedDestruction();
   if (_CPElementAgent != NULL) 
	   _CPElementAgent->RequestDelayedDestruction();
   if (_ProDlgAgent != NULL) 
	   _ProDlgAgent->RequestDelayedDestruction();
   if (_ProElementAgent != NULL) 
	   _ProElementAgent->RequestDelayedDestruction();
   if (_pDlg!=NULL)
	   _pDlg->RequestDelayedDestruction();
   
}

void ExtractfeatureCmd::BuildGraph()
{
	_CElementAgent=new CATPathElementAgent("GetCircle");
	_CElementAgent->AddElementType(IID_CATCircle);
	_CElementAgent->SetBehavior(
		CATDlgEngWithPrevaluation |
		CATDlgEngWithCSO);

	_LElementAgent=new CATPathElementAgent("GetLine");
	_LElementAgent->AddElementType(IID_CATLine);
	_LElementAgent->SetBehavior(
		CATDlgEngWithPrevaluation |
		CATDlgEngWithCSO);

	_PElementAgent=new CATPathElementAgent("GetPlane");
	_PElementAgent->AddElementType(IID_CATPlane);
	_PElementAgent->SetBehavior(
		CATDlgEngWithPrevaluation |
		CATDlgEngWithCSO);

	_CPElementAgent=new CATPathElementAgent("GetPoint");
	_CPElementAgent->AddElementType(IID_CATPoint);
	_CPElementAgent->SetBehavior(
		CATDlgEngWithPrevaluation |
		CATDlgEngWithCSO);

	_ProElementAgent=new CATPathElementAgent("GetProduct");
	_ProElementAgent->AddElementType(IID_CATIProduct);
	_ProElementAgent->SetBehavior(
		CATDlgEngWithPrevaluation |
		CATDlgEngWithCSO);

	_CDlgAgent=new CATDialogAgent("CircleDlg");
	_CDlgAgent->AcceptOnNotify(_pDlg->GetPushButton(2),_pDlg->GetPushButton(2)->GetPushBActivateNotification()); 

	_LDlgAgent=new CATDialogAgent("LineDlg");
	_LDlgAgent->AcceptOnNotify(_pDlg->GetPushButton(3),_pDlg->GetPushButton(3)->GetPushBActivateNotification()); 

	_PDlgAgent=new CATDialogAgent("PlaneDlg");
	_PDlgAgent->AcceptOnNotify(_pDlg->GetPushButton(4),_pDlg->GetPushButton(4)->GetPushBActivateNotification()); 

	_CPDlgAgent=new CATDialogAgent("PointDlg");
	_CPDlgAgent->AcceptOnNotify(_pDlg->GetPushButton(1),_pDlg->GetPushButton(1)->GetPushBActivateNotification()); 

	_ProDlgAgent=new CATDialogAgent("ProductDlg");
	_ProDlgAgent->AcceptOnNotify(_pDlg->GetPushButton(6),_pDlg->GetPushButton(6)->GetPushBActivateNotification()); 

	_CalDlgAgent=new CATDialogAgent("CalDlg");
	_CalDlgAgent->AcceptOnNotify(_pDlg->GetPushButton(5),_pDlg->GetPushButton(5)->GetPushBActivateNotification()); 

	_SaveDlgAgent=new CATDialogAgent("SaveDlg");
	_SaveDlgAgent->AcceptOnNotify(_pDlg->GetPushButton(7),_pDlg->GetPushButton(7)->GetPushBActivateNotification()); 

	CATDialogState * pDlgState=GetInitialState("DlgState");

	pDlgState->AddDialogAgent(_CDlgAgent);
	pDlgState->AddDialogAgent(_LDlgAgent);
	pDlgState->AddDialogAgent(_PDlgAgent);
	pDlgState->AddDialogAgent(_CPDlgAgent);
	pDlgState->AddDialogAgent(_ProDlgAgent);
	pDlgState->AddDialogAgent(_CalDlgAgent);
	pDlgState->AddDialogAgent(_SaveDlgAgent);

	CATDialogState * pGetCircleState=AddDialogState("getCircle");
	pGetCircleState->AddDialogAgent(_CElementAgent);

	CATDialogState * pGetLineState=AddDialogState("getLine");
	pGetLineState->AddDialogAgent(_LElementAgent);

	CATDialogState * pGetPlaneState=AddDialogState("getPlane");
	pGetPlaneState->AddDialogAgent(_PElementAgent);

	CATDialogState * pGetPointState=AddDialogState("getPoint");
	pGetPointState->AddDialogAgent(_CPElementAgent);

	CATDialogState * pGetProductState=AddDialogState("getProduct");
	pGetProductState->AddDialogAgent(_ProElementAgent);

	AddTransition( pDlgState, pGetPointState,
		IsOutputSetCondition (_CPDlgAgent),
		Action ((ActionMethod) &ExtractfeatureCmd::CPDlgAgentClear));

	AddTransition( pGetPointState, pDlgState,
		IsOutputSetCondition (_CPElementAgent),
		Action ((ActionMethod) &ExtractfeatureCmd::GetCPointElement));

	AddTransition( pDlgState, pGetCircleState,
		IsOutputSetCondition (_CDlgAgent),
		Action ((ActionMethod) &ExtractfeatureCmd::CDlgAgentClear));

	AddTransition( pGetCircleState, pDlgState,
		IsOutputSetCondition (_CElementAgent),
		Action ((ActionMethod) &ExtractfeatureCmd::GetCircleElement));

	AddTransition( pDlgState, pGetLineState,
		IsOutputSetCondition (_LDlgAgent),
		Action ((ActionMethod) &ExtractfeatureCmd::LDlgAgentClear));

	AddTransition( pGetLineState, pDlgState,
		IsOutputSetCondition (_LElementAgent),
		Action ((ActionMethod) &ExtractfeatureCmd::GetLineElement));

	AddTransition( pDlgState, pGetPlaneState,
		IsOutputSetCondition (_PDlgAgent),
		Action ((ActionMethod) &ExtractfeatureCmd::PDlgAgentClear));

	AddTransition( pGetPlaneState, pDlgState,
		IsOutputSetCondition (_PElementAgent),
		Action ((ActionMethod) &ExtractfeatureCmd::GetPlaneElement));

	AddTransition( pDlgState, pGetProductState,
		IsOutputSetCondition (_ProDlgAgent),
		Action ((ActionMethod) &ExtractfeatureCmd::ProDlgAgentClear));

	AddTransition( pGetProductState, pDlgState,
		IsOutputSetCondition (_ProElementAgent),
		Action ((ActionMethod) &ExtractfeatureCmd::GetProductElement));

	AddTransition(pDlgState, pDlgState,
		IsOutputSetCondition(_CalDlgAgent),
		Action((ActionMethod)&ExtractfeatureCmd::OnPushButton023PushBActivateNotification));

	AddTransition(pDlgState, pDlgState,
		IsOutputSetCondition(_SaveDlgAgent),
		Action((ActionMethod)&ExtractfeatureCmd::OnPushButton035PushBActivateNotification));

}



CATBoolean ExtractfeatureCmd::GetCircleElement(void *data)
{
	double radius;
	double x,y,z;

	CATAngle StartAngle,EndAngle;
	CATMathPoint origin;

	CATPathElement * pModelPath = _CElementAgent->GetValue();
	CATBaseUnknown * pExpectedPoint = NULL ;
	if (pModelPath && pModelPath->GetSize())
	{
		int ElementCountInPath = pModelPath->GetSize() - 1;
		pExpectedPoint = (*pModelPath)[ElementCountInPath];
	}

	if (pExpectedPoint)
	{
		CATCircle * pExpectedPointAsISysPoint = NULL;                
		HRESULT rc = pExpectedPoint->QueryInterface(IID_CATCircle,
			(void**)&pExpectedPointAsISysPoint);
		if (SUCCEEDED(rc))
		{
			radius=pExpectedPointAsISysPoint->GetRadius();
			StartAngle=pExpectedPointAsISysPoint->GetStartAngle();
			EndAngle=pExpectedPointAsISysPoint->GetEndAngle();
			origin=pExpectedPointAsISysPoint->GetOrigin();
			origin.GetCoord(x,y,z);

			pExpectedPointAsISysPoint->Release();
		}
	}

	SetCParameter(radius,x,y,z);

	_CElementAgent->InitializeAcquisition();

	return TRUE;
}

CATBoolean ExtractfeatureCmd::GetLineElement(void *data)
{
	CATMathPoint point;
	CATMathDirection direction;

	double x,y,z;

	double norm;
	double ix,iy,iz;

	CATPathElement * pModelPathL = _LElementAgent->GetValue();
	CATBaseUnknown * pExpectedPointL = NULL ;
	if (pModelPathL && pModelPathL->GetSize())
	{
		int ElementCountInPathL = pModelPathL->GetSize() - 1;
		pExpectedPointL = (*pModelPathL)[ElementCountInPathL];
	}

	if (pExpectedPointL)
	{
		CATLine * pExpectedPointAsISysPointL = NULL;                
		HRESULT rc = pExpectedPointL->QueryInterface(IID_CATLine,
			(void**)&pExpectedPointAsISysPointL);
		if (SUCCEEDED(rc))
		{
			point=pExpectedPointAsISysPointL->GetOrigin();
			direction=pExpectedPointAsISysPointL->GetDirection();

			point.GetCoord(x,y,z);

			norm=direction.Norm();
			direction.GetCoord(ix,iy,iz);

			pExpectedPointAsISysPointL->Release();
		}
	}

	SetLParameter(ix,iy,iz);

	_LElementAgent->InitializeAcquisition();

	return TRUE;
}

CATBoolean ExtractfeatureCmd::GetPlaneElement(void *data)
{
	CATMathPlane plane;
	CATMathVector vector1,vector2;
	CATMathPoint plPoint;

	double x,y,z;
	double x1,x2,y1,y2,z1,z2;

	CATPathElement * pModelPathL = _PElementAgent->GetValue();
	CATBaseUnknown * pExpectedPlane = NULL ;
	if (pModelPathL && pModelPathL->GetSize())
	{
		int ElementCountInPathL = pModelPathL->GetSize() - 1;
		pExpectedPlane = (*pModelPathL)[ElementCountInPathL];
	}

	if (pExpectedPlane)
	{
		CATPlane * pExpectedPointAsISysPointL = NULL;                
		HRESULT rc = pExpectedPlane->QueryInterface(IID_CATPlane,
			(void**)&pExpectedPointAsISysPointL);
		if (SUCCEEDED(rc))
		{
			pExpectedPointAsISysPointL->GetAxis(plane);

			plane.GetDirections(vector1,vector2);

			vector1.GetCoord(x1,y1,z1);
			vector2.GetCoord(x2,y2,z2);

			plPoint=plane.GetOrigin();
			plPoint.GetCoord(x,y,z);

			pExpectedPointAsISysPointL->Release();
		}
	}

	SetPParameter(x1,y1,z1,x2,y2,z2);
	
	_PElementAgent->InitializeAcquisition();

	return TRUE;
}

CATBoolean ExtractfeatureCmd::GetCPointElement(void *data)
{
	double x,y,z;

	CATMathPoint origin;

	CATPathElement * pModelPath = _CPElementAgent->GetValue();
	CATBaseUnknown * pExpectedPoint = NULL ;
	if (pModelPath && pModelPath->GetSize())
	{
		int ElementCountInPath = pModelPath->GetSize() - 1;
		pExpectedPoint = (*pModelPath)[ElementCountInPath];
	}

	if (pExpectedPoint)
	{
		CATPoint * pExpectedPointAsISysPoint = NULL;                
		HRESULT rc = pExpectedPoint->QueryInterface(IID_CATPoint,
			(void**)&pExpectedPointAsISysPoint);
		if (SUCCEEDED(rc))
		{
			/*origin=pExpectedPointAsISysPoint->GetOrigin();
			origin.GetCoord(x,y,z);*/

			pExpectedPointAsISysPoint->GetCoord(x,y,z);

			pExpectedPointAsISysPoint->Release();
		}
	}

	SetCPParameter(x,y,z);

	_CPElementAgent->InitializeAcquisition();

	return TRUE;
}

CATBoolean ExtractfeatureCmd::GetProductElement(void *data)
{

	CATUnicodeString name;

	CATPathElement * pModelPath = _ProElementAgent->GetValue();
	CATBaseUnknown * pExpectedProduct = NULL ;
	if (pModelPath && pModelPath->GetSize())
	{
		int ElementCountInPath = pModelPath->GetSize() - 1;
		pExpectedProduct = (*pModelPath)[ElementCountInPath];
	}

	if (pExpectedProduct)
	{
		CATIProduct * spProduct = NULL;                
		HRESULT rc = pExpectedProduct->QueryInterface(IID_CATIProduct,
			(void**)&spProduct);
		if (SUCCEEDED(rc))
		{
			name=spProduct->GetPartNumber();

			spProduct->Release();
		}
	}

	SetProParameter(name);

	_CPElementAgent->InitializeAcquisition();

	return TRUE;
}

CATBoolean ExtractfeatureCmd::CDlgAgentClear( void *data )
{
	_CDlgAgent->InitializeAcquisition();
	
	return TRUE;
}

CATBoolean ExtractfeatureCmd::LDlgAgentClear( void *data )
{
	_LDlgAgent->InitializeAcquisition();

	return TRUE;
}

CATBoolean ExtractfeatureCmd::PDlgAgentClear( void *data )
{
	_PDlgAgent->InitializeAcquisition();

	return TRUE;
}

CATBoolean ExtractfeatureCmd::CPDlgAgentClear( void *data )
{
	_CPDlgAgent->InitializeAcquisition();

	return TRUE;
}

CATBoolean ExtractfeatureCmd::ProDlgAgentClear( void *data )
{
	_ProDlgAgent->InitializeAcquisition();

	return TRUE;
}

void ExtractfeatureCmd::SetCParameter(double r,double cx2,double cy2,double cz2)
{

	this->r=r;
	this->cx2=cx2;
	this->cy2=cy2;
	this->cz2=cz2;

	CATUnicodeString s,s1;
	s="";
	s1="";
	s.BuildFromNum(cx2,"%.2f");
	s.Append(",");
	s1.BuildFromNum(cy2,"%.2f");
	s.Append(s1);
	s.Append(",");
	s1.BuildFromNum(cz2,"%.2f");
	s.Append(s1);
	_pDlg->GetEditor(3)->SetText(s);

	s1.BuildFromNum(r,"%.2f");
	R.BuildFromNum(r,"%.2f");
	r=atof(R);
	_pDlg->GetEditor(4)->SetText(s1);

	Cx2.BuildFromNum(this->cx2,"%.2f");
	this->cx2=atof(Cx2);
	Cy2.BuildFromNum(this->cy2,"%.2f");
	this->cy2=atof(Cy2);
	Cz2.BuildFromNum(this->cz2,"%.2f");
	this->cz2=atof(Cz2);

}
void ExtractfeatureCmd::SetCPParameter(double cx,double cy,double cz)
{
	this->cx=cx;
	this->cy=cy;
	this->cz=cz;

	CATUnicodeString s,s1;
	s="";
	s1="";
	s.BuildFromNum(cx,"%.2f");
	s.Append(",");
	s1.BuildFromNum(cy,"%.2f");
	s.Append(s1);
	s.Append(",");
	s1.BuildFromNum(cz,"%.2f");
	s.Append(s1);
	_pDlg->GetEditor(2)->SetText(s);

	Cx.BuildFromNum(this->cx,"%.2f");
	this->cx=atof(Cx);
	Cy.BuildFromNum(this->cy,"%.2f");
	this->cy=atof(Cy);
	Cz.BuildFromNum(this->cz,"%.2f");
	this->cz=atof(Cz);
	//s1.BuildFromNum(r,"%.2f");
	//_Editor009->SetText(s1);

}

void ExtractfeatureCmd::SetLParameter(double lx,double ly,double lz)
{
	this->lx=lx;
	this->ly=ly;
	this->lz=lz;

	CATUnicodeString s,s1;
	s="";
	s1="";
	s.BuildFromNum(lx,"%.2f");
	s.Append(",");
	s1.BuildFromNum(ly,"%.2f");
	s.Append(s1);
	s.Append(",");
	s1.BuildFromNum(lz,"%.2f");
	s.Append(s1);
	_pDlg->GetEditor(1)->SetText(s);

	Lx.BuildFromNum(this->lx,"%.2f");
	this->lx=atof(Lx);
	Ly.BuildFromNum(this->ly,"%.2f");
	this->ly=atof(Ly);
	Lz.BuildFromNum(this->lz,"%.2f");
	this->lz=atof(Lz);

}
void ExtractfeatureCmd::SetPParameter(double px1,double py1,double pz1,double px2,double pyll,double pz2)
{

	this->px1=px1;
	this->py1=py1;
	this->pz1=pz1;

	this->px2=px2;
	this->py2=py2;
	this->pz2=pz2;

	A[0]=py1*pz2-py2*pz1;
	A[1]=pz1*px2-pz2*px1;
	A[2]=px1*py2-px2*py1;

	CATUnicodeString s,s1;
	s="";
	s1="";
	s.BuildFromNum(px1,"%.2f");
	s.Append(",");
	s1.BuildFromNum(py1,"%.2f");
	s.Append(s1);
	s.Append(",");
	s1.BuildFromNum(pz1,"%.2f");
	s.Append(s1);
	_pDlg->GetEditor(5)->SetText(s);

	s="";
	s1="";
	s.BuildFromNum(px2,"%.2f");
	s.Append(",");
	s1.BuildFromNum(py2,"%.2f");
	s.Append(s1);
	s.Append(",");
	s1.BuildFromNum(pz2,"%.2f");
	s.Append(s1);
	_pDlg->GetEditor(6)->SetText(s);

	s="";
	s1="";
	s.BuildFromNum(A[0],"%.2f");
	s.Append(",");
	s1.BuildFromNum(A[1],"%.2f");
	s.Append(s1);
	s.Append(",");
	s1.BuildFromNum(A[2],"%.2f");
	s.Append(s1);
	_pDlg->GetEditor(7)->SetText(s);

	Px.BuildFromNum(A[0],"%.2f");
	px=atof(Px);
	Py.BuildFromNum(A[1],"%.2f");
	py=atof(Py);
	Pz.BuildFromNum(A[2],"%.2f");
	pz=atof(Pz);


}

void ExtractfeatureCmd::SetProParameter(CATUnicodeString name)
{
	NAME.Append(name);
	_pDlg->GetEditor(9)->SetText(NAME);
}

void ExtractfeatureCmd::OnPushButton023PushBActivateNotification(CATCommand* cmd, CATNotification* evt, CATCommandClientData data)
{
	
	_CalDlgAgent->InitializeAcquisition();
	double B = lx*A[0] + ly*A[1] + lz*A[2];
	double C = sqrt(lx*lx + ly*ly + lz*lz);
	double D = sqrt(A[0]*A[0] + A[1]*A[1] + A[2]*A[2]);

	const double eps = 1e-12;
	CATUnicodeString s;


	double cosv = B / (C * D);

	if (cosv > 1.0)  cosv = 1.0;
	if (cosv < -1.0) cosv = -1.0;

	double a_rad = acos(fabs(cosv)); // [0, pi]
	double a_deg = a_rad * (180.0 / 3.14159265358979323846); // [0, 180]

	s.BuildFromNum(a_deg, "%.2f");

	_pDlg->GetEditor(8)->SetText(s);


}



void ExtractfeatureCmd::OnPushButton035PushBActivateNotification(CATCommand* cmd, CATNotification* evt, CATCommandClientData data)
{
	_SaveDlgAgent->InitializeAcquisition();

	struct ComUtil
	{
		static VARIANT VtI4(long v) { VARIANT x; VariantInit(&x); x.vt = VT_I4; x.lVal = v; return x; }
		static VARIANT VtBool(BOOL v) { VARIANT x; VariantInit(&x); x.vt = VT_BOOL; x.boolVal = v ? VARIANT_TRUE : VARIANT_FALSE; return x; }
		static VARIANT VtBstr(const wchar_t* ws) { VARIANT x; VariantInit(&x); x.vt = VT_BSTR; x.bstrVal = SysAllocString(ws); return x; }

		static std::wstring AnsiToWide(const char* s)
		{
			if (!s) return L"";
			int n = MultiByteToWideChar(CP_ACP, 0, s, -1, NULL, 0);
			if (n <= 0) return L"";
			std::wstring ws; ws.resize(n - 1);
			MultiByteToWideChar(CP_ACP, 0, s, -1, &ws[0], n);
			return ws;
		}

		static std::wstring ToWide(CATUnicodeString us)
		{
			const char* p = us.ConvertToChar();
			std::wstring ws = AnsiToWide(p);
			return ws;
		}

		static HRESULT AutoWrap(int autoType, VARIANT* pvResult, IDispatch* pDisp, LPOLESTR ptName, int cArgs, ...)
		{
			if (!pDisp) return E_INVALIDARG;

			DISPID dispid;
			HRESULT hr = pDisp->GetIDsOfNames(IID_NULL, &ptName, 1, LOCALE_USER_DEFAULT, &dispid);
			if (FAILED(hr)) return hr;

			VARIANT* pArgs = NULL;
			if (cArgs > 0) pArgs = new VARIANT[cArgs];

			va_list marker;
			va_start(marker, cArgs);
			for (int i = 0; i < cArgs; i++) pArgs[i] = va_arg(marker, VARIANT);
			va_end(marker);

			DISPPARAMS dp;
			dp.cArgs = cArgs;
			dp.rgvarg = pArgs;

			DISPID dispidNamed = DISPID_PROPERTYPUT;
			if (autoType & DISPATCH_PROPERTYPUT)
			{
				dp.cNamedArgs = 1;
				dp.rgdispidNamedArgs = &dispidNamed;
			}
			else
			{
				dp.cNamedArgs = 0;
				dp.rgdispidNamedArgs = NULL;
			}

			if (pvResult) VariantInit(pvResult);
			hr = pDisp->Invoke(dispid, IID_NULL, LOCALE_USER_DEFAULT, autoType, &dp, pvResult, NULL, NULL);

			if (pArgs) delete[] pArgs;
			return hr;
		}
	};

	// 角度 0~180（与你按钮5一致）
	double B = lx*A[0] + ly*A[1] + lz*A[2];
	double C = sqrt(lx*lx + ly*ly + lz*lz);
	double D = sqrt(A[0]*A[0] + A[1]*A[1] + A[2]*A[2]);
	double a_deg = 0.0;
	if (C > 1e-12 && D > 1e-12)
	{
		double cosv = B / (C * D);
		if (cosv > 1.0)  cosv = 1.0;
		if (cosv < -1.0) cosv = -1.0;
		double a_rad = acos(fabs(cosv));
		a_deg = a_rad * (180.0 / 3.14159265358979323846);
	}

	wchar_t tempPathW[MAX_PATH] = { 0 };
	GetTempPathW(MAX_PATH, tempPathW);
	std::wstring savePath = L"D:\\CatiaWS\\FeaG\\ExtractFeature.xls";

	HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);
	if (FAILED(hr))
	{
		::MessageBoxA(NULL, "CoInitializeEx failed.", "Error", MB_OK | MB_ICONERROR);
		return;
	}

	CLSID clsid;
	hr = CLSIDFromProgID(L"Excel.Application", &clsid);
	if (FAILED(hr))
	{
		CoUninitialize();
		::MessageBoxA(NULL, "Excel.Application not found. Please install Microsoft Excel.", "Error", MB_OK | MB_ICONERROR);
		return;
	}

	IDispatch* pExcel = NULL;
	hr = CoCreateInstance(clsid, NULL, CLSCTX_LOCAL_SERVER, IID_IDispatch, (void**)&pExcel);
	if (FAILED(hr) || !pExcel)
	{
		CoUninitialize();
		::MessageBoxA(NULL, "Failed to start Excel.", "Error", MB_OK | MB_ICONERROR);
		return;
	}

	{
		VARIANT v = ComUtil::VtBool(FALSE);
		ComUtil::AutoWrap(DISPATCH_PROPERTYPUT, NULL, pExcel, L"Visible", 1, v);
		VariantClear(&v);
	}

	VARIANT vWorkbooks;
	hr = ComUtil::AutoWrap(DISPATCH_PROPERTYGET, &vWorkbooks, pExcel, L"Workbooks", 0);
	if (FAILED(hr) || vWorkbooks.vt != VT_DISPATCH)
	{
		pExcel->Release();
		CoUninitialize();
		::MessageBoxA(NULL, "Failed to get Workbooks.", "Error", MB_OK | MB_ICONERROR);
		return;
	}
	IDispatch* pWorkbooks = vWorkbooks.pdispVal;

	VARIANT vWb;
	hr = ComUtil::AutoWrap(DISPATCH_METHOD, &vWb, pWorkbooks, L"Add", 0);
	if (FAILED(hr) || vWb.vt != VT_DISPATCH)
	{
		pWorkbooks->Release();
		pExcel->Release();
		CoUninitialize();
		::MessageBoxA(NULL, "Failed to add Workbook.", "Error", MB_OK | MB_ICONERROR);
		return;
	}
	IDispatch* pWorkbook = vWb.pdispVal;

	VARIANT vSheet;
	hr = ComUtil::AutoWrap(DISPATCH_PROPERTYGET, &vSheet, pExcel, L"ActiveSheet", 0);
	if (FAILED(hr) || vSheet.vt != VT_DISPATCH)
	{
		pWorkbook->Release();
		pWorkbooks->Release();
		pExcel->Release();
		CoUninitialize();
		::MessageBoxA(NULL, "Failed to get ActiveSheet.", "Error", MB_OK | MB_ICONERROR);
		return;
	}
	IDispatch* pSheet = vSheet.pdispVal;

	VARIANT vCells;
	hr = ComUtil::AutoWrap(DISPATCH_PROPERTYGET, &vCells, pSheet, L"Cells", 0);
	if (FAILED(hr) || vCells.vt != VT_DISPATCH)
	{
		pSheet->Release();
		pWorkbook->Release();
		pWorkbooks->Release();
		pExcel->Release();
		CoUninitialize();
		::MessageBoxA(NULL, "Failed to get Cells.", "Error", MB_OK | MB_ICONERROR);
		return;
	}
	IDispatch* pCells = vCells.pdispVal;

	struct WriteCellHelper
	{
		static void Write(IDispatch* pCells, long r, long c, const wchar_t* text)
		{
			VARIANT vr = ComUtil::VtI4(r);
			VARIANT vc = ComUtil::VtI4(c);
			VARIANT vCell;
			HRESULT hr = ComUtil::AutoWrap(DISPATCH_PROPERTYGET, &vCell, pCells, L"Item", 2, vc, vr);
			VariantClear(&vr);
			VariantClear(&vc);
			if (SUCCEEDED(hr) && vCell.vt == VT_DISPATCH)
			{
				IDispatch* pCell = vCell.pdispVal;
				VARIANT vText = ComUtil::VtBstr(text);
				ComUtil::AutoWrap(DISPATCH_PROPERTYPUT, NULL, pCell, L"Value2", 1, vText);
				VariantClear(&vText);
				pCell->Release();
			}
		}
		static void WriteNum(IDispatch* pCells, long r, long c, double v)
		{
			VARIANT vr = ComUtil::VtI4(r);
			VARIANT vc = ComUtil::VtI4(c);
			VARIANT vCell;
			HRESULT hr = ComUtil::AutoWrap(DISPATCH_PROPERTYGET, &vCell, pCells, L"Item", 2, vc, vr);
			VariantClear(&vr);
			VariantClear(&vc);
			if (SUCCEEDED(hr) && vCell.vt == VT_DISPATCH)
			{
				IDispatch* pCell = vCell.pdispVal;
				VARIANT vNum; VariantInit(&vNum); vNum.vt = VT_R8; vNum.dblVal = v;
				ComUtil::AutoWrap(DISPATCH_PROPERTYPUT, NULL, pCell, L"Value2", 1, vNum);
				VariantClear(&vNum);
				pCell->Release();
			}
		}
	};

	WriteCellHelper::Write(pCells, 1, 1, L"Product");
	WriteCellHelper::Write(pCells, 1, 2, L"CircleCenterX");
	WriteCellHelper::Write(pCells, 1, 3, L"CircleCenterY");
	WriteCellHelper::Write(pCells, 1, 4, L"CircleCenterZ");
	WriteCellHelper::Write(pCells, 1, 5, L"Radius");
	WriteCellHelper::Write(pCells, 1, 6, L"PointX");
	WriteCellHelper::Write(pCells, 1, 7, L"PointY");
	WriteCellHelper::Write(pCells, 1, 8, L"PointZ");
	WriteCellHelper::Write(pCells, 1, 9, L"LineDirX");
	WriteCellHelper::Write(pCells, 1, 10, L"LineDirY");
	WriteCellHelper::Write(pCells, 1, 11, L"LineDirZ");
	WriteCellHelper::Write(pCells, 1, 12, L"PlaneNormalX");
	WriteCellHelper::Write(pCells, 1, 13, L"PlaneNormalY");
	WriteCellHelper::Write(pCells, 1, 14, L"PlaneNormalZ");
	WriteCellHelper::Write(pCells, 1, 15, L"AngleDeg");

	std::wstring wName = ComUtil::ToWide(NAME);
	WriteCellHelper::Write(pCells, 2, 1, wName.c_str());
	WriteCellHelper::WriteNum(pCells, 2, 2, cx2);
	WriteCellHelper::WriteNum(pCells, 2, 3, cy2);
	WriteCellHelper::WriteNum(pCells, 2, 4, cz2);
	WriteCellHelper::WriteNum(pCells, 2, 5, r);
	WriteCellHelper::WriteNum(pCells, 2, 6, cx);
	WriteCellHelper::WriteNum(pCells, 2, 7, cy);
	WriteCellHelper::WriteNum(pCells, 2, 8, cz);
	WriteCellHelper::WriteNum(pCells, 2, 9, lx);
	WriteCellHelper::WriteNum(pCells, 2, 10, ly);
	WriteCellHelper::WriteNum(pCells, 2, 11, lz);
	WriteCellHelper::WriteNum(pCells, 2, 12, A[0]);
	WriteCellHelper::WriteNum(pCells, 2, 13, A[1]);
	WriteCellHelper::WriteNum(pCells, 2, 14, A[2]);
	WriteCellHelper::WriteNum(pCells, 2, 15, a_deg);

	{
		VARIANT vPath = ComUtil::VtBstr(savePath.c_str());
		VARIANT vFmt = ComUtil::VtI4(56);
		ComUtil::AutoWrap(DISPATCH_METHOD, NULL, pWorkbook, L"SaveAs", 2, vFmt, vPath);
		VariantClear(&vPath);
		VariantClear(&vFmt);
	}

	{
		VARIANT vFalse = ComUtil::VtBool(FALSE);
		ComUtil::AutoWrap(DISPATCH_METHOD, NULL, pWorkbook, L"Close", 1, vFalse);
		VariantClear(&vFalse);
	}

	ComUtil::AutoWrap(DISPATCH_METHOD, NULL, pExcel, L"Quit", 0);

	pCells->Release();
	pSheet->Release();
	pWorkbook->Release();
	pWorkbooks->Release();
	pExcel->Release();
	CoUninitialize();

	::MessageBoxW(NULL, savePath.c_str(), L"Excel saved to:", MB_OK);
}
