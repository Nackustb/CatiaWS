#include "PadDlg.h"
#include "CATApplicationFrame.h"
#include "CATDlgGridConstraints.h"
#include "CATMsgCatalog.h"
#ifdef PadDlg_ParameterEditorInclude
#include "CATIParameterEditorFactory.h"
#include "CATIParameterEditor.h"
#include "CATICkeParm.h"
#endif


PadDlg::PadDlg() :
  CATDlgDialog ((CATApplicationFrame::GetApplicationFrame())->GetMainWindow(),
"PadDlg",CATDlgWndBtnOKApplyClose|CATDlgGridLayout
                               )
{
 _Label001 = NULL;
 _Label002 = NULL;
 _Label003 = NULL;
 _Editor004 = NULL;
 _Editor005 = NULL;
 _Editor006 = NULL;
 _Label007 = NULL;
 _Label008 = NULL;
 _Label009 = NULL;
}


PadDlg::~PadDlg()
{
 _Label001 = NULL;
 _Label002 = NULL;
 _Label003 = NULL;
 _Editor004 = NULL;
 _Editor005 = NULL;
 _Editor006 = NULL;
 _Label007 = NULL;
 _Label008 = NULL;
 _Label009 = NULL;
}

void PadDlg::Build()
{
 _Label001 = new CATDlgLabel(this, "Label001");
_Label001 -> SetGridConstraints(0, 0, 1, 1, CATGRID_4SIDES);
 _Label002 = new CATDlgLabel(this, "Label002");
_Label002 -> SetGridConstraints(1, 0, 1, 1, CATGRID_4SIDES);
 _Label003 = new CATDlgLabel(this, "Label003");
_Label003 -> SetGridConstraints(2, 0, 1, 1, CATGRID_4SIDES);
 _Editor004 = new CATDlgEditor(this, "Editor004");
_Editor004 -> SetGridConstraints(0, 1, 1, 1, CATGRID_4SIDES);
 _Editor005 = new CATDlgEditor(this, "Editor005");
_Editor005 -> SetGridConstraints(1, 1, 1, 1, CATGRID_4SIDES);
 _Editor006 = new CATDlgEditor(this, "Editor006");
_Editor006 -> SetGridConstraints(2, 1, 1, 1, CATGRID_4SIDES);
_Label007 = new CATDlgLabel(this, "Label007");
_Label007 -> SetGridConstraints(0, 2, 1, 1, CATGRID_4SIDES);
_Label008 = new CATDlgLabel(this, "Label008");
_Label008 -> SetGridConstraints(1, 2, 1, 1, CATGRID_4SIDES);
_Label009 = new CATDlgLabel(this, "Label009");
_Label009 -> SetGridConstraints(2, 2, 1, 1, CATGRID_4SIDES);

AddAnalyseNotificationCB (this, 
						  GetWindCloseNotification(),
						  (CATCommandMethod)&PadDlg::OnPadDlgWindCloseNotification,
						  NULL);
BuildMore();
}

void PadDlg::BuildMore()
{
	_Editor004->SetText("2.0"); 
    _Editor005->SetText("2.0");
    _Editor006->SetText("2.0");
}
void PadDlg::OnPadDlgWindCloseNotification(CATCommand* cmd, CATNotification* evt, CATCommandClientData data)
{
	this -> SetVisibility(CATDlgHide);
}

CATDlgEditor* PadDlg::GetEditor(int iValue)
{
	switch (iValue)
	{
	case 1: return _Editor004;
    case 2: return _Editor005;
	case 3: return _Editor006;
	}
	return NULL;
}
