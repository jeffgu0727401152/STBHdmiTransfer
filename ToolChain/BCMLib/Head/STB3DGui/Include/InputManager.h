#pragma once

#include "IInputManager.h"
#include "BaseLock.h"
#include "FileOperator.h"

#include "DirectionKey.h"

#ifdef HAVE_TS_DEV
#include "TouchDevice.h"
#endif

#ifdef HAVE_EVENT_DEV
#include "EventDevice.h"
#endif

#include "MonkeyDevice.h"

#ifdef HAVE_TS_DEV
void GetTSEventDevice(
	CSimpleStringA *pEventName);
#endif

#ifdef HAVE_EVENT_DEV
typedef struct tagUEVENTINFO {
    const char *action;
    const char *path;
    const char *subsystem;
    const char *devname;
    const char *firmware;
    int major;
    int minor;
} UEVENTINFO;
#endif

class CInputManager : public IInputManager,
	public IMessageOwner
#ifdef HAVE_EVENT_DEV
	,public IThreadFuncInterface
#endif
{
public:
	CInputManager();
	virtual ~CInputManager();

	// interface
public:
	virtual void OnMsg(
		UINT32 uType,
		UINT64 wParam,
		UINT64 lParam);

	virtual void ReportMouse(
		DEVICETYPE eDeviceType,
		BOOL bPressed,
		int xPos,
		int yPos);

	virtual void ReportKey(
		BOOL bPressed,
		int nKeyValue);

	virtual int GetXPos();
	virtual int GetYPos();
	virtual int GetXPosMax();
	virtual int GetYPosMax();

public:
	void SetInputType(
		INPUTTYPE type);
	INPUTTYPE GetInputType();
	void SetMonkeyParam(
		UINT64 uInterval);

	void Start(
		int nMouseXMax,
		int nMouseYMax);
	void Stop();
	void Pause();
	void Resume();

	void SimulateMouse(
		BOOL bAbsTouch,
		int fd,
		int x,
		int y);
	void SimulateKey(
		int fd,
		int keycode,
		int value);

	UINT64 GetLastInputEventTime();

#ifdef HAVE_EVENT_DEV
public:
	void StartWatchInputDevice();
	void StopWatchInputDevice();
	void ReadNotifyEvent();
	void OpenUEventSocket();
	void CloseUEventSocket();
	void ReadUEvent();

	virtual BOOL ThreadLoop(
		UINT64 uThreadData);

private:
	void AddEventDevicesFromInputDevice();

	void ParseUevent(
		const char *msg,
		UEVENTINFO *uevent);
#endif

private:
	BOOL mLastPressed;
	UINT64 mLastClickTime;
	POINT mLastTouchPos;
	int mContinueClickCount;

	UINT64 mLastInputEventTime;

	BOOL mStopped;
	BOOL mPausedCount;

	INPUTTYPE mInputType;

	CDirectionKey mDirectionKey;

#ifdef HAVE_TS_DEV
	CTouchDevice mTouchDevice;
#endif

#ifdef HAVE_EVENT_DEV
	CEventDevice mEventDevice;

	CBaseThread mWatchInputDeviceThread;
	int mInputDeviceInotifyFD;
	int mUEventFD;
	int mInputDeviceWatchFD;
#endif

	CMonkeyDevice mMonkeyDevice;

	int mCurXPos;
	int mCurYPos;
	int mXPosMax;
	int mYPosMax;
} ;
