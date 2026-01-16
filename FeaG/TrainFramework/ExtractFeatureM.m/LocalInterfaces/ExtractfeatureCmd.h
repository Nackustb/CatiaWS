#ifndef ExtractfeatureCmd_H
#define ExtractfeatureCmd_H

#include "CATStateCommand.h"
#include "CATBoolean.h"
#include "ExtractFeatureDlg.h"
#include <iostream.h>
#include "CATDialogAgent.h"
#include "CATPathElementAgent.h"

#include "CATCircle.h"
#include "CATMathCircle.h"
#include "CATPathElement.h"
#include "CATMathConstant.h"
#include "CATLine.h"
#include "CATMathPoint.h"
#include "CATMathDirection.h"
#include "CATMathVector.h"
#include "CATPlane.h"
#include "CATPoint.h"

class CATIndicationAgent;
class CATPathElementAgent;
class CATDialogAgent;


class ExtractfeatureCmd : public CATStateCommand
{
	DeclareResource(ExtractfeatureCmd, CATStateCommand)

public:
	ExtractfeatureCmd();
	virtual ~ExtractfeatureCmd();

	virtual void BuildGraph();

	// Select actions
	CATBoolean GetCircleElement(void *data);
	CATBoolean GetLineElement(void *data);
	CATBoolean GetPlaneElement(void *data);
	CATBoolean GetCPointElement(void *data);
	CATBoolean GetProductElement(void *data);

	// Button-agent clear actions
	CATBoolean CDlgAgentClear(void *data);
	CATBoolean LDlgAgentClear(void *data);
	CATBoolean PDlgAgentClear(void *data);
	CATBoolean CPDlgAgentClear(void *data);
	CATBoolean ProDlgAgentClear(void *data);

	// Set parameters (write to members + UI)
	void SetCircleParameter(double circleRadius, double circleCenterX, double circleCenterY, double circleCenterZ);
	void SetPointParameter(double pointX, double pointY, double pointZ);
	void SetLineDirection(double lineDirX, double lineDirY, double lineDirZ);
	void SetPlaneParameter(double planeDir1X, double planeDir1Y, double planeDir1Z,
		double planeDir2X, double planeDir2Y, double planeDir2Z);
	void SetProductParameter(CATUnicodeString productPartNumber);

	// Calculate / Save
	void OnPushButton023PushBActivateNotification(CATCommand* cmd, CATNotification* evt, CATCommandClientData data);
	void OnPushButton035PushBActivateNotification(CATCommand* cmd, CATNotification* evt, CATCommandClientData data);

private:
	CATIndicationAgent* _Indication;
	ExtractFeatureDlg*  _pDlg;

	// Path selection agents
	CATPathElementAgent* _CElementAgent;
	CATPathElementAgent* _LElementAgent;
	CATPathElementAgent* _PElementAgent;
	CATPathElementAgent* _CPElementAgent;
	CATPathElementAgent* _ProElementAgent;

	// Dialog/button agents
	CATDialogAgent* _CDlgAgent;
	CATDialogAgent* _LDlgAgent;
	CATDialogAgent* _PDlgAgent;
	CATDialogAgent* _CPDlgAgent;
	CATDialogAgent* _ProDlgAgent;
	CATDialogAgent* _CalDlgAgent;
	CATDialogAgent* _SaveDlgAgent;

	// Circle
	double circleRadius;
	double circleCenterX;
	double circleCenterY;
	double circleCenterZ;

	// Point
	double pointX;
	double pointY;
	double pointZ;

	// Line direction
	double lineDirX;
	double lineDirY;
	double lineDirZ;

	// Plane normal (from cross product of 2 plane directions)
	double planeNormal[3];

	// Product
	CATUnicodeString productPartNumberText;

	// UI text buffers (for atof / formatting)
	CATUnicodeString CircleRadiusText;
	CATUnicodeString CircleCenterXText;
	CATUnicodeString CircleCenterYText;
	CATUnicodeString CircleCenterZText;

	CATUnicodeString PointXText;
	CATUnicodeString PointYText;
	CATUnicodeString PointZText;

	CATUnicodeString LineDirXText;
	CATUnicodeString LineDirYText;
	CATUnicodeString LineDirZText;

	CATUnicodeString PlaneNormalXText;
	CATUnicodeString PlaneNormalYText;
	CATUnicodeString PlaneNormalZText;
};

#endif