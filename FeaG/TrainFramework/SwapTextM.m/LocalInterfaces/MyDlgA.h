#ifndef MyDlgA_H
#define MyDlgA_H

#include "CATDlgDialog.h"
#include "CATDlgInclude.h"


class MyDlgA: public CATDlgDialog
{

  DeclareResource( MyDlgA, CATDlgDialog )

  public:

  MyDlgA();
  virtual ~MyDlgA();

  void Build ();
  void SetData();
  CATUnicodeString getName();
  CATUnicodeString getAge();


  protected:

  private:

 CATDlgFrame*      _Frame001;
 CATDlgLabel*      _Label002;
 CATDlgLabel*      _Label003;
 CATDlgEditor*      _Editor004;
 CATDlgEditor*      _Editor005;

 CATUnicodeString Name;
 CATUnicodeString Age;

};


#endif