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
#include "HttpFileClient.h"

class CHttpFileClient;

class DownloadTask : public IThreadFuncInterface
{
public:
	DownloadTask(const char* urls);
	virtual ~DownloadTask();

public:
	void Start();
	void Stop();
	CPtrListCtrl GetDownloadList();

public:
	virtual BOOL ThreadLoop(
		UINT64 uThreadData);

private:
	CHttpFileClient mHttpFileClient;
	CBaseThread mDownloadThread;
	CPtrListCtrl mDownloadUrlList;
	int mDownloadThreadExit;
};
