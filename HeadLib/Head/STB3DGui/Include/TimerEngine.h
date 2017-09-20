#pragma once

#include "BaseThread.h"
#include "MsgQueue.h"

typedef struct tagTIMER
{
	IMessageOwner *pOwner;
	int nTimerID;
	UINT64 uDelayTime; //ms
	UINT64 uNextRunTime;
}TIMER;

class CTimerEngine: public CBaseThread,
	public IThreadFuncInterface
{
	typedef CBaseThread CParentClass;

public:
	CTimerEngine();
	virtual ~CTimerEngine();

public:
	void Start(
		CMsgQueue *pMsgQueue);
	void Stop();
	void Pause();
	void Resume();
	virtual BOOL ThreadLoop(
		UINT64 uThreadData);

public:
	void AddTimer(
		IMessageOwner *pOwner,
		int nTimerID,
		UINT64 uDelayTime);
	void DelTimer(
		IMessageOwner *pOwner,
		int nTimerID);
	void ResetTimer(
		IMessageOwner *pOwner,
		int nTimerID);
	void RemoveAllTimerByOwner(
		IMessageOwner *pOwner);

private:
	UINT64 UpdateNextTimer();

private:
	CMsgQueue *mpMsgQueue;
	CPtrListCtrl mTimerList;
	CBaseLock mTimerListLock;
	CBaseEvent mTimerEvent;
	BOOL mExitThread;
};
