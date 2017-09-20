#pragma once

#include "BaseEvent.h"
#include "BaseLock.h"

#define STACKSIZE_HEAVY		(SIZE_1M*8)
#define STACKSIZE_LIGHT		(SIZE_1M*4)
#define STACKSIZE_MIN		(SIZE_1M*2)
#define STACKSIZE_DEFAULT	STACKSIZE_LIGHT

class CBaseThread;
class IThreadFuncInterface
{
public:
	virtual ~IThreadFuncInterface(void) {}

public:
	// return TRUE to continue loop, return FALSE to end loop
	virtual BOOL ThreadLoop(
		UINT64 uThreadData)=0;
};

class CBaseThread
{
public:
	CBaseThread();
	virtual ~CBaseThread();

public:	
	BOOL StartThread(
		const char* cThreadName,
		IThreadFuncInterface *pThreadFunc,
		UINT64 uThreadData,
		int nStackSize,
		BOOL bAutoDetach=FALSE);
	void StopThread();
	void StopThreadImmediate();
	void PauseThread();
	void ResumeThread();
	BOOL IsThreadRunning();
	BOOL IsThreadNeedExit();

public:
	LPVOID WrapThreadFunc();

private:
	CBaseLock mThreadLock;
	pthread_t mThreadID;
	BOOL mExitThread;
	BOOL mAutoDetach;

	CBaseEvent mRunEvent;
	BOOL mThreadHasExited;

	int mLWPID;
	char mThreadName[128];
	IThreadFuncInterface* mpThreadFunc;
	UINT64 mThreadData;
};

#ifndef ANDROID
void thread_callstack_sighandler(
	int sig);
#endif
void DumpThreadStack();
void DumpAllThreadsStackBySignal(
	int nExcludeTid);
