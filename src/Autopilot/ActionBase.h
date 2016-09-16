
#ifndef OPENKAI_SRC_AUTOPILOT_ACTIONBASE_H_
#define OPENKAI_SRC_AUTOPILOT_ACTIONBASE_H_

#include "../Base/common.h"
#include "../Interface/_Mavlink.h"
#include "../Interface/_RC.h"
#include "../Stream/_Stream.h"
#include "../Detector/_Cascade.h"
#include "../Tracker/_ROITracker.h"
#include "../Detector/_Bullseye.h"
#include "../Detector/_AprilTags.h"
#include "commonAutopilot.h"


namespace kai
{

class ActionBase
{
public:
	ActionBase();
	~ActionBase();

	bool init(Config* pConfig, string name);
	void update(void);
	bool draw(Frame* pFrame, iVec4* pTextPos);

public:

	AUTOPILOT_CONTROL* m_pCtrl;
	_RC* m_pVI;
	_Mavlink* m_pMavlink;




};

}

#endif
