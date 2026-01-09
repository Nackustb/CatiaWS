#include "PointDlg.h"
#include "CATApplicationFrame.h"
#include "CATDlgGridConstraints.h"
#include "CATMsgCatalog.h"
#ifdef PointDlg_ParameterEditorInclude
#include "CATIParameterEditorFactory.h"
#include "CATIParameterEditor.h"
#include "CATICkeParm.h"
#endif



PointDlg::PointDlg() :
  CATDlgDialog ((CATApplicationFrame::GetApplicationFrame())->GetMainWindow(),
"PointDlg",CATDlgWndBtnOKApplyClose|CATDlgGridLayout
                               )
{
 _Label001 = NULL;
 _Label002 = NULL;
 _Label003 = NULL;
 _SelectorList004 = NULL;
 _Combo005 = NULL;
 _Spinner008 = NULL;
}


PointDlg::~PointDlg()
{
 _Label001 = NULL;
 _Label002 = NULL;
 _Label003 = NULL;
 _SelectorList004 = NULL;
 _Combo005 = NULL;
 _Spinner008 = NULL;
}



void PointDlg::Build()
{
 _Label001 = new CATDlgLabel(this, "Label001");
_Label001 -> SetGridConstraints(0, 0, 1, 1, CATGRID_4SIDES);
 _Label002 = new CATDlgLabel(this, "Label002");
_Label002 -> SetGridConstraints(1, 0, 1, 1, CATGRID_4SIDES);
 _Label003 = new CATDlgLabel(this, "Label003");
_Label003 -> SetGridConstraints(2, 0, 1, 1, CATGRID_4SIDES);
 _SelectorList004 = new CATDlgSelectorList(this, "SelectorList004");
 _SelectorList004 -> SetVisibleTextHeight(1);
 _SelectorList004 -> SetVisibleTextWidth(10);
_SelectorList004 -> SetGridConstraints(1, 1, 1, 1, CATGRID_4SIDES);
 _Combo005 = new CATDlgCombo(this, "Combo005", CATDlgCmbDropDown);
_Combo005 -> SetGridConstraints(0, 1, 1, 1, CATGRID_4SIDES);
 _Spinner008 = new CATDlgSpinner(this, "Spinner008", CATDlgSpnEntry|CATDlgSpnDouble);
 _Spinner008 -> SetMinMaxStep(0.000000, 10.000000, 0.00010);
 _Spinner008 -> SetUnit (CATDlgControl::Millimeter);
 _Spinner008 -> SetPrecision( 6 );
_Spinner008 -> SetGridConstraints(2, 1, 1, 1, CATGRID_4SIDES);

AddAnalyseNotificationCB (this, 
						  GetWindCloseNotification(),
						  (CATCommandMethod)&PointDlg::OnPointDlgWindCloseNotification,
						  NULL);

BuildMore();
}
void PointDlg::BuildMore()
{

	_Combo005->ClearLine();
	_Combo005->SetLine("曲线上的距离",1);
	_Combo005->SetLine("圆的中心",1);
	_Combo005->SetField("曲线上的距离");

	_SelectorList004->ClearLine();
	_SelectorList004->SetLine("No selection",0,CATDlgDataModify);
	int iTabRow = 0; 
	_SelectorList004->SetSelect(&iTabRow,1,0);


	_Spinner008->SetValue(0.00010);
}

CATDlgSelectorList* PointDlg::GetSelectorList(int iValue)
{
	switch (iValue)
	{
	case 1: return _SelectorList004; // 返回 SelectorList
	}
	return NULL;
}

CATDlgCombo* PointDlg::GetCombo(int iValue)
{
	switch (iValue)
	{
	case 1: return _Combo005; // 返回 Combo
	}
	return NULL;
}

CATDlgSpinner* PointDlg::GetSpinner(int iValue)
{
	switch (iValue)
	{
	case 1: return _Spinner008; // 返回 Spinner
	}
	return NULL;
}


CATNotification * PointDlg::GetCombo005SelectNotification()
{
	if (_Combo005 == NULL) return NULL;
	return _Combo005->GetComboSelectNotification();
}

void PointDlg::OnPointDlgWindCloseNotification(CATCommand* cmd, CATNotification* evt, CATCommandClientData data)
{
	this -> SetVisibility(CATDlgHide);
}
