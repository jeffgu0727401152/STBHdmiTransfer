#pragma once

#include "types.h"
#include <linux/input.h>

#define INPUTEVENT_BUF_NUM 64
#define INPUTDEV_POLL_TIMEOUT 500

typedef enum eDEVICETYPE
{
	DEVICETYPE_UNKNOWN=0,
	DEVICETYPE_SIMULATION,
	DEVICETYPE_KBDMOUSE,
	DEVICETYPE_TOUCHSCREEN,
} DEVICETYPE;

typedef enum eINPUTTYPE
{
	INPUTTYPE_DEVICE,
	INPUTTYPE_MONKEY
} INPUTTYPE;

class IInputManager
{
public:
	virtual ~IInputManager(void) {}

	virtual void ReportMouse(
		DEVICETYPE eDeviceType,
		BOOL bPressed,
		int xPos,
		int yPos) = 0;

	virtual void ReportKey(
		BOOL bPressed,
		int nKeyValue) = 0;

	virtual int GetXPos() = 0;
	virtual int GetYPos() = 0;
	virtual int GetXPosMax() = 0;
	virtual int GetYPosMax() = 0;
};
