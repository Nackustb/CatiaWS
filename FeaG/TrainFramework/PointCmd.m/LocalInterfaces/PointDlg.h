#ifndef PointDlg_H
#define PointDlg_H

#include "CATDlgDialog.h"
#include "CATDlgInclude.h"


class PointDlg: public CATDlgDialog
{

  DeclareResource( PointDlg, CATDlgDialog )

  public:

  PointDlg();
  virtual ~PointDlg();

  void Build ();
  void BuildMore();
  CATDlgSelectorList* GetSelectorList(int iValue);
  CATDlgCombo*        GetCombo(int iValue);
  CATDlgSpinner*      GetSpinner(int iValue);

  virtual void OnPointDlgWindCloseNotification (CATCommand *, CATNotification* , CATCommandClientData data);
   
  protected:

  private:


 CATDlgLabel*      _Label001;
 CATDlgLabel*      _Label002;
 CATDlgLabel*      _Label003;
 CATDlgSelectorList*      _SelectorList004;
 CATDlgCombo*      _Combo005;
 CATDlgSpinner*      _Spinner008;
};


#endif