#include "MyPraTranscmd.h"
#include "CATApplicationFrame.h"
#include "CATCreateExternalObject.h"  // 创建实例化的类
CATCreateClass( MyPraTranscmd);

MyPraTranscmd::MyPraTranscmd() :
CATCommand (NULL, "MyPraTranscmd")
,dlga(NULL)
,dlgb(NULL)
{
	CATApplicationFrame * pFrame = CATApplicationFrame::GetFrame();

	if (NULL != pFrame)
	{
		CATDialog * pParent = (CATDialog *)pFrame->GetMainWindow();

		if(pParent != NULL)
		{
			dlga = new MyDlgA();
			dlga->Build();			  
			dlgb = new MyDlgB();
			dlgb->Build();
		}
	}
	RequestStatusChange (CATCommandMsgRequestExclusiveMode);  	  
}
MyPraTranscmd::~MyPraTranscmd()
{
	if(dlga != NULL)
		dlga->RequestDelayedDestruction();	// 延迟破坏
	if(dlgb != NULL)
		dlgb->RequestDelayedDestruction();
}

// 产生对话框
CATStatusChangeRC MyPraTranscmd::Activate( CATCommand * iFromClient, CATNotification * iEvtDat)
{
	if(dlga != NULL)
		dlga->SetVisibility(CATDlgShow);  // 可视化设置

	AddAnalyseNotificationCB(
		dlga,
		dlga->GetDiaOKNotification(),
		(CATCommandMethod)&MyPraTranscmd::MyDlgAOKCB,
		NULL);

	AddAnalyseNotificationCB(
		dlga,
		dlga->GetDiaCANCELNotification(),
		(CATCommandMethod)&MyPraTranscmd::MyDlgACancelCB,
		NULL);

	AddAnalyseNotificationCB(
		dlgb,
		dlgb->GetDiaOKNotification(),
		(CATCommandMethod)&MyPraTranscmd::MyDlgBOKCB,
		NULL);

	AddAnalyseNotificationCB(
		dlgb,
		dlgb->GetDiaCANCELNotification(),
		(CATCommandMethod)&MyPraTranscmd::MyDlgBCancelCB,
		NULL);	
	return (CATStatusChangeRCCompleted);
}

// 关闭对话框A
CATStatusChangeRC MyPraTranscmd::Desactivate( CATCommand * iFromClient, CATNotification * iEvtDat)
{
	if(dlga != NULL)
		dlga->SetVisibility(CATDlgHide);
	return (CATStatusChangeRCCompleted);
}

// 对话框A的取消命令，直接退出
CATStatusChangeRC MyPraTranscmd::Cancel( CATCommand * iFromClient, CATNotification * iEvtDat)
{
	if(dlga != NULL)
		dlga->SetVisibility(CATDlgHide);
	RequestDelayedDestruction();
	return (CATStatusChangeRCCompleted);
}

// 对话框A的确定命令，保存数据，关联对话框B
void MyPraTranscmd::MyDlgAOKCB(CATCommand * iCommand,
							   CATNotification * iNotification,
							   CATCommandClientData iUsefulData)
{		
	CATUnicodeString strName, strAge, mesg;
	mesg = "";
	strName = "";
	strAge = "";
	dlga->SetData();
	strName = dlga->getName();
	strAge = dlga->getAge();
	dlga->SetVisibility(CATDlgHide);	
	mesg.Append(strName);
	mesg.Append(strAge);
	dlgb->SetMesgStr(mesg);	
	dlgb->SetVisibility(CATDlgShow);	
}

void MyPraTranscmd::MyDlgACancelCB(CATCommand * iCommand,
								   CATNotification * iNotification,
								   CATCommandClientData iUsefulData)
{
	this->Cancel(iCommand, iNotification);
}

// 对话框B的“确定”和“取消”按钮功能相同
void MyPraTranscmd::MyDlgBOKCB(CATCommand * iCommand,
							   CATNotification * iNotification,
							   CATCommandClientData iUsefulData)
{
	this->Cancel(iCommand, iNotification);
}

void MyPraTranscmd::MyDlgBCancelCB(CATCommand * iCommand,
								   CATNotification * iNotification,
								   CATCommandClientData iUsefulData)
{
	this->Cancel(iCommand, iNotification);
}
