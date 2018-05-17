/*
 * DownloadTask.h
 *
 *  Created on: 2018-5-16
 *      Author: tiny
 */

#pragma once

#include "BaseThread.h"
#include "types.h"
#include "BaseApp.h"
#include <vector>

class DownloadTask : public IThreadFuncInterface
{
public:
	DownloadTask();
	virtual ~DownloadTask();

public:
	void Start(const char* netURLsP);
	void Stop();

	// interface
public:
	virtual BOOL ThreadLoop(
		UINT64 uThreadData);

private:
	CBaseThread mDownloadThread;
	char netURLs[MAX_PATH];
};
