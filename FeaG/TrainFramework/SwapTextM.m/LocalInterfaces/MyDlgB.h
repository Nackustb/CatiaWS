#ifndef MyDlgB_H
#define MyDlgB_H

#include "CATDlgDialog.h"
#include "CATDlgInclude.h"
#include "MyDlgA.h"

class MyDlgB: public CATDlgDialog
{

  DeclareResource( MyDlgB, CATDlgDialog )

  public:

  MyDlgB();
  virtual ~MyDlgB();

  void Build ();
  void SetMesgStr(CATUnicodeString mesgStr);

  protected:

  private:


 CATDlgFrame*      _Frame001;
 CATDlgLabel*      _Label002;
 CATDlgEditor*      _Editor003;
};


#endif