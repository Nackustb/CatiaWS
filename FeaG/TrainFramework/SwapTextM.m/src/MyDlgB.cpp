
#include "MyDlgB.h"
#include "CATApplicationFrame.h"
#include "CATDlgGridConstraints.h"
#include "CATMsgCatalog.h"
#ifdef MyDlgB_ParameterEditorInclude
#include "CATIParameterEditorFactory.h"
#include "CATIParameterEditor.h"
#include "CATICkeParm.h"
#endif


MyDlgB::MyDlgB() :
  CATDlgDialog ((CATApplicationFrame::GetApplicationFrame())->GetMainWindow(),
"MyDlgB",CATDlgGridLayout
                               )
{
 _Frame001 = NULL;
 _Label002 = NULL;
 _Editor003 = NULL;
}


MyDlgB::~MyDlgB()
{

 _Frame001 = NULL;
 _Label002 = NULL;
 _Editor003 = NULL;
}



void MyDlgB::Build()
{

 _Frame001 = new CATDlgFrame(this, "Frame001", CATDlgGridLayout);
_Frame001 -> SetGridConstraints(0, 0, 1, 1, CATGRID_4SIDES);
 _Label002 = new CATDlgLabel(_Frame001, "Label002");
_Label002 -> SetGridConstraints(0, 0, 1, 1, CATGRID_4SIDES);
 _Editor003 = new CATDlgEditor(_Frame001, "Editor003");
_Editor003 -> SetGridConstraints(0, 1, 1, 1, CATGRID_4SIDES);

}

void MyDlgB::SetMesgStr(CATUnicodeString mesgStr){		
	this->_Editor003->SetText(mesgStr);	
}