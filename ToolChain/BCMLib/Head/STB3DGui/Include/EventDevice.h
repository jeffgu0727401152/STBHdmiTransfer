#pragma once

#ifdef HAVE_EVENT_DEV

#include "IInputManager.h"
#include "PtrControl.h"
#include "BaseThread.h"
#include "BaseLock.h"

typedef struct tagMOUSEEVENTINFO
{
	BOOL bPressed;
	int xPos;
	int yPos;
} MOUSEEVENTINFO;

typedef struct tagKEYBDEVENTINFO
{
	BOOL bPressed;
	int nKeyValue;
} KEYBDEVENTINFO;

typedef enum eMOUSETYPE
{
	MOUSETYPE_IMPS2 = 0,
	MOUSETYPE_REL,
	MOUSETYPE_ABS,
	MOUSETYPE_ABS_MT
} MOUSETYPE;

typedef struct tagDEVINFO
{
	char cEventName[32];
	int nFD;

	MOUSETYPE eMouseType;

	BOOL bIsMouseEvent;

	int nMinX, nMaxX;
	int nMinY, nMaxY;
} DEVINFO;

class CEventDevice : public CBaseThread,
	public IThreadFuncInterface
{
public:
	CEventDevice(
		IInputManager *pInputManager);
	virtual ~CEventDevice();

	// interface
public:
	virtual BOOL ThreadLoop(
		UINT64 uThreadData);

public:
	// in some machine, mouse move and mouse press are in two event
	void AddEventDevice(
		const char *cEventName);
	void DelEventDevice(
		const char *cEventName);
	void DelAllEventDevice();

	void StartDevice();
	void StopDevice();

private:
	void GetDeviceType(
		int nFD,
		DEVINFO *pDevInfo);

	BOOL ReadIMPS2Mouse(
		DEVINFO *pDevInfo);
	BOOL ReadInputEvent(
		DEVINFO *pDevInfo);

	void UpdateMouseX(
		int dx,
		int* pxPos);
	void UpdateMouseY(
		int dy,
		int* pyPos);

private:
	IInputManager *mpInputManager;

	MOUSEEVENTINFO mMouseData;
	KEYBDEVENTINFO mKeybdData;

	CPtrListCtrl mEventDeviceList;
	CBaseLock mEventDeviceListLock;
};

#endif
