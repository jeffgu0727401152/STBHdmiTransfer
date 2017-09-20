#pragma once

#ifdef HAVE_TS_DEV

#include "IInputManager.h"
#include "tslib.h"
#include "BaseThread.h"

class CTouchDevice :public CBaseThread,
	public IThreadFuncInterface
{
	typedef CBaseThread CParentClass;

public:
	CTouchDevice(
		IInputManager *pInputManager);
	virtual ~CTouchDevice();

	// interface
public:
	virtual BOOL ThreadLoop(
		UINT64 uThreadData);

public:
	void StartDevice(
		const char* cEventName);
	void StopDevice();

private:
	void ReadTSSamples();

private:
	IInputManager *mpInputManager;

	struct tsdev * mpTouchDevice;
};

#endif
