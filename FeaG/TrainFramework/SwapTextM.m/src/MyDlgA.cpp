#include "MyDlgA.h"
#include "CATApplicationFrame.h"
#include "CATDlgGridConstraints.h"
#include "CATMsgCatalog.h"
#ifdef MyDlgA_ParameterEditorInclude
#include "CATIParameterEditorFactory.h"
#include "CATIParameterEditor.h"
#include "CATICkeParm.h"
#endif


MyDlgA::MyDlgA() :
  CATDlgDialog ((CATApplicationFrame::GetApplicationFrame())->GetMainWindow(),
"MyDlgA",CATDlgGridLayout)

{
 _Frame001 = NULL;
 _Label002 = NULL;
 _Label003 = NULL;
 _Editor004 = NULL;
 _Editor005 = NULL;
}


MyDlgA::~MyDlgA()
{
 _Frame001 = NULL;
 _Label002 = NULL;
 _Label003 = NULL;
 _Editor004 = NULL;
 _Editor005 = NULL;
}



void MyDlgA::Build()
{

 _Frame001 = new CATDlgFrame(this, "Frame001", CATDlgGridLayout);
_Frame001 -> SetGridConstraints(0, 0, 1, 1, CATGRID_4SIDES);
 _Label002 = new CATDlgLabel(_Frame001, "Label002");
_Label002 -> SetGridConstraints(0, 0, 1, 1, CATGRID_4SIDES);
 _Label003 = new CATDlgLabel(_Frame001, "Label003");
_Label003 -> SetGridConstraints(1, 0, 1, 1, CATGRID_4SIDES);
 _Editor004 = new CATDlgEditor(_Frame001, "Editor004");
_Editor004 -> SetGridConstraints(0, 1, 1, 1, CATGRID_4SIDES);
 _Editor005 = new CATDlgEditor(_Frame001, "Editor005");
_Editor005 -> SetGridConstraints(1, 1, 1, 1, CATGRID_4SIDES);


}

void MyDlgA::SetData(){
	this->Name=_Editor004->GetText();
	this->Age=_Editor005->GetText(); 
}

CATUnicodeString MyDlgA::getName(){
	return this->Name;
}

CATUnicodeString MyDlgA::getAge(){
	return this->Age;
}
