/*
 * PlayerCmdServer.h
 *
 *  Created on: 2013-1-18
 *      Author: kyo
 */

#pragma once

#include "curlhelp.h"
#include "BaseThread.h"

class CHttpCmdClient : public IThreadFuncInterface
{
public:
	CHttpCmdClient();
	virtual ~CHttpCmdClient();

public:
	void Start(
		const char* cServerIP,
		int nServerPort);
	void Stop();

	// interface
public:
	virtual BOOL ThreadLoop(
		UINT64 uThreadData);

public:
	BOOL GetIsServerOnline();
	BOOL ClientVerify(
		const char* cMac,
		const char* cStbIP,
		const char* cVodIP,
		const char* cRoomID);
	BOOL ClientOpen(
		const char* cVodIP,
		CSimpleStringA *pResultUrlString);

private:
	char mServerIP[16];
	int mServerPort;

	BOOL mIsServerOnline;

	int mExitThread;
	CBaseEvent mExitEvent;
	CBaseThread mCheckOnlineThread;
};
