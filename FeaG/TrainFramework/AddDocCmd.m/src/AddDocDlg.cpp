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
// 以 CATIA 主窗口为父窗口创建对话框
CATDlgDialog ((CATApplicationFrame::GetApplicationFrame())->GetMainWindow(),
			 "AddDocDlg",CATDlgWndNoButton|CATDlgGridLayout)
{
	// 初始化控件指针
	_PushButton002 = NULL;
	_PushButton003 = NULL;
	_Label004 = NULL;
	_Editor005 = NULL;
}


AddDocDlg::~AddDocDlg()
{
	// 置空指针（实际销毁由对话框框架管理）
	_PushButton002 = NULL;
	_PushButton003 = NULL;
	_Label004 = NULL;
	_Editor005 = NULL;
}



void AddDocDlg::Build()
{
	// 文件选择对话框
	pDlgFile = new CATDlgFile(this,"选择文件",CATDlgFileSave);

	// 打开按钮（PushButton002）
	_PushButton002 = new CATDlgPushButton(this, "PushButton002");
	_PushButton002 -> SetGridConstraints(2, 0, 2, 1, CATGRID_4SIDES);

	// 选择文件按钮（PushButton003）
	_PushButton003 = new CATDlgPushButton(this, "PushButton003");
	_PushButton003 -> SetGridConstraints(0, 0, 2, 1, CATGRID_4SIDES);

	// 标签
	_Label004 = new CATDlgLabel(this, "Label004");
	_Label004 -> SetGridConstraints(1, 0, 1, 1, CATGRID_4SIDES);

	// 路径输入框/显示框
	_Editor005 = new CATDlgEditor(this, "Editor005");
	_Editor005 -> SetGridConstraints(1, 1, 1, 1, CATGRID_4SIDES);

	// 文件对话框点击 OK 后回调：把选中的路径写回 Editor
	AddAnalyseNotificationCB(pDlgFile,
		pDlgFile -> GetDiaOKNotification(),
		(CATCommandMethod)&AddDocDlg::ActOnOK,
		NULL);

	// PushButton002 点击回调：根据 Editor 里的路径打开文档
	AddAnalyseNotificationCB (_PushButton002, 
		_PushButton002->GetPushBActivateNotification(),
		(CATCommandMethod)&AddDocDlg::OnPushButton002PushBActivateNotification,
		NULL);

	// PushButton003 点击回调：弹出文件选择框
	AddAnalyseNotificationCB (_PushButton003, 
		_PushButton003->GetPushBActivateNotification(),
		(CATCommandMethod)&AddDocDlg::OnPushButton003PushBActivateNotification,
		NULL);

	AddAnalyseNotificationCB (this, 
		GetWindCloseNotification(),
		(CATCommandMethod)&AddDocDlg::DocWindCloseNotification,
		NULL);

}



void AddDocDlg::OnPushButton003PushBActivateNotification(CATCommand* cmd, CATNotification* evt, CATCommandClientData data)
{
	// 显示文件选择对话框，并限制为 CATPart
	pDlgFile -> SetVisibility(CATDlgShow);
	CATUnicodeString nameExtension = CATUnicodeString("CATPart files");
	CATString filterExtension = CATString("*.CATPart");
	pDlgFile -> SetFilterStrings(&nameExtension,&filterExtension,1);
	pDlgFile -> SetFileName("Part1.CATPart");
}

void AddDocDlg::OnPushButton002PushBActivateNotification(CATCommand* cmd, CATNotification* evt, CATCommandClientData data)
{
	// 1) 取路径
	if (_Editor005 == NULL) return;

	CATUnicodeString fileName = _Editor005->GetText();
	cout << "Open fileName is " << fileName << endl;

	// 2) 打开文档（加载到会话）
	CATDocument* pInsertDoc = NULL;
	HRESULT rc = CATDocumentServices::OpenDocument(fileName, pInsertDoc);
	if (FAILED(rc) || pInsertDoc == NULL) return;

	// 3) 获取 CATIDocumentEdit，用于创建窗口
	CATIDocumentEdit* piDocEdit = NULL;
	rc = pInsertDoc->QueryInterface(IID_CATIDocumentEdit, (void**)&piDocEdit);
	if (FAILED(rc) || piDocEdit == NULL) return;

	CATIDocumentEdit_var spDocEdit = piDocEdit;
	piDocEdit->Release();
	piDocEdit = NULL;

	// 4) 获取 CATIEditor，用于拿到对应的 CATFrmEditor
	CATIEditor* piEditor = NULL;
	rc = pInsertDoc->QueryInterface(IID_CATIEditor, (void**)&piEditor);
	if (FAILED(rc) || piEditor == NULL) return;

	CATIEditor_var spEditor = piEditor;
	piEditor->Release();
	piEditor = NULL;

	// 5) 获取文档的 Frame Editor（用于窗口创建）
	CATFrmEditor* pFrmEditor = spEditor->GetEditor();
	if (pFrmEditor == NULL) return;

	// 6) 创建默认窗口（否则可能“打开但不可见”）
	pFrmEditor->AddRef();
	CATFrmWindow* pWin = spDocEdit->CreateDefaultWindow(pFrmEditor);
	pFrmEditor->Release();

	if (pWin == NULL) return;

	// 7) 打开成功后隐藏当前对话框
	SetVisibility(CATDlgHide);
}




void AddDocDlg::ActOnOK(CATCommand* cmd, CATNotification* evt, CATCommandClientData data)
{
	// 获取所选路径并写入 Editor
	CATUnicodeString fileName;
	pDlgFile -> GetSelection(fileName);
	_Editor005 -> SetText(fileName);
	pDlgFile -> SetVisibility(CATDlgHide);
}


void AddDocDlg::DocWindCloseNotification(CATCommand* cmd, CATNotification* evt, CATCommandClientData data)
{
	this -> SetVisibility(CATDlgHide);
}