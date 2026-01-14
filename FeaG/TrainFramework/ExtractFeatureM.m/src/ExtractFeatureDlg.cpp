#include "ExtractFeatureDlg.h"
#include "CATApplicationFrame.h"
#include "CATDlgGridConstraints.h"
#include "CATMsgCatalog.h"
#ifdef ExtractFeatureDlg_ParameterEditorInclude
#include "CATIParameterEditorFactory.h"
#include "CATIParameterEditor.h"
#include "CATICkeParm.h"
#endif





ExtractFeatureDlg::ExtractFeatureDlg() :
  CATDlgDialog ((CATApplicationFrame::GetApplicationFrame())->GetMainWindow(),
"ExtractFeatureDlg",CATDlgWndNoButton|CATDlgGridLayout
                               )
{
 _Frame001 = NULL;
 _PushButton002 = NULL;
 _PushButton003 = NULL;
 _PushButton004 = NULL;
 _PushButton005 = NULL;
 _Frame006 = NULL;
 _Label007 = NULL;
 _Editor008 = NULL;
 _Frame009 = NULL;
 _Label010 = NULL;
 _Label011 = NULL;
 _Label012 = NULL;
 _Editor013 = NULL;
 _Editor014 = NULL;
 _Editor015 = NULL;
 _PushButton023 = NULL;
 _PushButton024 = NULL;
 _PushButton025 = NULL;
 _Frame016 = NULL;
 _Label017 = NULL;
 _Label018 = NULL;
 _Label019 = NULL;
 _Editor020 = NULL;
 _Editor021 = NULL;
 _Editor022 = NULL;
 _Editor026 = NULL;
 _Editor027 = NULL;
}


ExtractFeatureDlg::~ExtractFeatureDlg()
{

 _Frame001 = NULL;
 _PushButton002 = NULL;
 _PushButton003 = NULL;
 _PushButton004 = NULL;
 _PushButton005 = NULL;
 _Frame006 = NULL;
 _Label007 = NULL;
 _Editor008 = NULL;
 _Frame009 = NULL;
 _Label010 = NULL;
 _Label011 = NULL;
 _Label012 = NULL;
 _Editor013 = NULL;
 _Editor014 = NULL;
 _Editor015 = NULL;
 _PushButton023 = NULL;
 _PushButton024 = NULL;
 _PushButton025 = NULL;
 _Frame016 = NULL;
 _Label017 = NULL;
 _Label018 = NULL;
 _Label019 = NULL;
 _Editor020 = NULL;
 _Editor021 = NULL;
 _Editor022 = NULL;
 _Editor026 = NULL;
 _Editor027 = NULL;
}



void ExtractFeatureDlg::Build()
{

 _Frame001 = new CATDlgFrame(this, "Frame001", CATDlgGridLayout);
_Frame001 -> SetGridConstraints(0, 0, 1, 1, CATGRID_4SIDES);
 _PushButton002 = new CATDlgPushButton(_Frame001, "PushButton002");
_PushButton002 -> SetGridConstraints(0, 0, 1, 1, CATGRID_4SIDES);
 _PushButton003 = new CATDlgPushButton(_Frame001, "PushButton003");
_PushButton003 -> SetGridConstraints(0, 1, 1, 1, CATGRID_4SIDES);
 _PushButton004 = new CATDlgPushButton(_Frame001, "PushButton004");
_PushButton004 -> SetGridConstraints(0, 2, 1, 1, CATGRID_4SIDES);
 _PushButton005 = new CATDlgPushButton(_Frame001, "PushButton005");
_PushButton005 -> SetGridConstraints(0, 3, 1, 1, CATGRID_4SIDES);
 _Frame006 = new CATDlgFrame(this, "Frame006", CATDlgGridLayout);
_Frame006 -> SetGridConstraints(0, 1, 1, 1, CATGRID_4SIDES);
 _Label007 = new CATDlgLabel(_Frame006, "Label007");
_Label007 -> SetGridConstraints(0, 0, 1, 1, CATGRID_4SIDES);
 _Editor008 = new CATDlgEditor(_Frame006, "Editor008");
_Editor008 -> SetGridConstraints(0, 1, 1, 1, CATGRID_4SIDES);
 _Frame009 = new CATDlgFrame(this, "Frame009", CATDlgGridLayout);
_Frame009 -> SetGridConstraints(1, 0, 1, 1, CATGRID_4SIDES);
 _Label010 = new CATDlgLabel(_Frame009, "Label010");
_Label010 -> SetGridConstraints(0, 0, 1, 1, CATGRID_4SIDES);
 _Label011 = new CATDlgLabel(_Frame009, "Label011");
_Label011 -> SetGridConstraints(1, 0, 1, 1, CATGRID_4SIDES);
 _Label012 = new CATDlgLabel(_Frame009, "Label012");
_Label012 -> SetGridConstraints(2, 0, 1, 1, CATGRID_4SIDES);
 _Editor013 = new CATDlgEditor(_Frame009, "Editor013");
_Editor013 -> SetGridConstraints(0, 1, 1, 1, CATGRID_4SIDES);
 _Editor014 = new CATDlgEditor(_Frame009, "Editor014");
_Editor014 -> SetGridConstraints(1, 1, 1, 1, CATGRID_4SIDES);
 _Editor015 = new CATDlgEditor(_Frame009, "Editor015");
_Editor015 -> SetGridConstraints(2, 1, 1, 1, CATGRID_4SIDES);
 _PushButton023 = new CATDlgPushButton(_Frame009, "PushButton023");
_PushButton023 -> SetGridConstraints(3, 0, 2, 1, CATGRID_4SIDES);
 _PushButton024 = new CATDlgPushButton(_Frame009, "PushButton024");
_PushButton024 -> SetGridConstraints(4, 0, 2, 1, CATGRID_4SIDES);
 _PushButton025 = new CATDlgPushButton(_Frame009, "PushButton025");
_PushButton025 -> SetGridConstraints(5, 0, 2, 1, CATGRID_4SIDES);
 _Frame016 = new CATDlgFrame(this, "Frame016", CATDlgGridLayout);
_Frame016 -> SetGridConstraints(1, 1, 1, 1, CATGRID_4SIDES);
 _Label017 = new CATDlgLabel(_Frame016, "Label017");
_Label017 -> SetGridConstraints(0, 0, 1, 1, CATGRID_4SIDES);
 _Label018 = new CATDlgLabel(_Frame016, "Label018");
_Label018 -> SetGridConstraints(1, 0, 1, 1, CATGRID_4SIDES);
 _Label019 = new CATDlgLabel(_Frame016, "Label019");
_Label019 -> SetGridConstraints(2, 0, 1, 1, CATGRID_4SIDES);
 _Editor020 = new CATDlgEditor(_Frame016, "Editor020");
_Editor020 -> SetGridConstraints(0, 1, 1, 1, CATGRID_4SIDES);
 _Editor021 = new CATDlgEditor(_Frame016, "Editor021");
_Editor021 -> SetGridConstraints(1, 1, 1, 1, CATGRID_4SIDES);
 _Editor022 = new CATDlgEditor(_Frame016, "Editor022");
_Editor022 -> SetGridConstraints(2, 1, 1, 1, CATGRID_4SIDES);
 _Editor026 = new CATDlgEditor(_Frame016, "Editor026");
_Editor026 -> SetGridConstraints(3, 0, 2, 1, CATGRID_4SIDES);
 _Editor027 = new CATDlgEditor(_Frame016, "Editor027");
_Editor027 -> SetGridConstraints(4, 0, 2, 1, CATGRID_4SIDES);

AddAnalyseNotificationCB (this, 
						  GetWindCloseNotification(),
						  (CATCommandMethod)&ExtractFeatureDlg::OnDlgWindCloseNotification,
						  NULL);


}

void ExtractFeatureDlg::OnDlgWindCloseNotification(CATCommand* cmd, CATNotification* evt, CATCommandClientData data)
{
	this -> SetVisibility(CATDlgHide);
}


CATDlgPushButton* ExtractFeatureDlg::GetPushButton(int iValue)
{
	switch (iValue)
	{
	case 1: return _PushButton002; 
	case 2: return _PushButton003; 
	case 3: return _PushButton004; 
	case 4: return _PushButton005; 
	case 5: return _PushButton023; 
	case 6: return _PushButton024; 
	case 7: return _PushButton025; 

	}
	return NULL;
}

CATDlgEditor* ExtractFeatureDlg::GetEditor(int iValue)
{
	switch (iValue)
	{
	case 1: return _Editor008; 
	case 2: return _Editor013; 
	case 3: return _Editor014; 
	case 4: return _Editor015; 
	case 5: return _Editor020; 
	case 6: return _Editor021; 
	case 7: return _Editor022; 
	case 8: return _Editor026; 
	case 9: return _Editor027; 
	}
	return NULL;
}
