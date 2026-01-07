#ifndef MyPraTranscmd_H
#define MyPraTranscmd_H

#include "CATCommand.h"
#include "MyDlgA.h"
#include "MyDlgB.h"

class MyPraTranscmd: public CATCommand
{
public:
	MyPraTranscmd();
	virtual ~MyPraTranscmd();

	virtual CATStatusChangeRC Activate(CATCommand * iFromClient,CATNotification * iEvtDat);

	virtual CATStatusChangeRC Desactivate(CATCommand * iFromClient,CATNotification * iEvtDat);

	virtual CATStatusChangeRC Cancel(CATCommand * iFromClient,CATNotification * iEvtDat);

	void MyDlgAOKCB(CATCommand * iCommand,CATNotification * iNotification,CATCommandClientData iUsefulData);

	void MyDlgACancelCB(CATCommand * iCommand,CATNotification * iNotification,CATCommandClientData iUsefulData);

	void MyDlgBOKCB(CATCommand * iCommand,CATNotification * iNotification,CATCommandClientData iUsefulData);

	void MyDlgBCancelCB(CATCommand * iCommand,CATNotification * iNotification,CATCommandClientData iUsefulData);

private:
	MyDlgA* dlga;
	MyDlgB* dlgb;
};

#endif
