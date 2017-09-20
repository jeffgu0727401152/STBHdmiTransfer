#pragma once

#include "BaseLock.h"

//---------------------------------------------------------------

class CBaseEvent
{
public:
	CBaseEvent(
		CBaseLock *pLock = NULL,
		BOOL bManualReset = FALSE);
	virtual ~CBaseEvent();

	void Set();
	BOOL Wait();
	BOOL Wait(
		UINT64 uMiliSeconds);
	BOOL WaitUS(
		UINT64 uMicroSeconds);
	void Reset();
	BOOL IsSet();
	BOOL IsWaiting();

private:
	BOOL            m_ManualReset;
	volatile BOOL   m_State;
	volatile BOOL   m_IsWaiting;
	pthread_cond_t  m_Condition;

	pthread_mutex_t* mp_Mutex;
	BOOL mIsAttached;
};
