#pragma once

#include "types.h"
#include <pthread.h>

//---------------------------------------------------------------

class CBaseLock
{
public:
	CBaseLock();
	virtual ~CBaseLock();

	void Lock();
	void Unlock();

private:
	friend class CBaseEvent;
	pthread_mutex_t m_Mutex;
};
