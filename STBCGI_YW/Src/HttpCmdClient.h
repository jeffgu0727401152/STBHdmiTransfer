/*
 * PlayerCmdServer.h
 *
 *  Created on: 2013-1-18
 *      Author: kyo
 */
#pragma once

#include "TCPSocketClient.h"
#include "HttpCmdStruct.h"

typedef struct tagHTTPCMDREQWITHEVENT
{
	int nRequestID;
	CBaseEvent complete;
} HTTPCMDREQWITHEVENT;

class CHttpCmdClient : public CTCPSocketClient,
	public IClientSocketListener
{
	typedef CTCPSocketClient CParentClass;

public:
	CHttpCmdClient();
	virtual ~CHttpCmdClient();

public:
	BOOL Create(
		const char *cServerAddr,
		UINT16 uPort,
		BOOL bLocalSocket,
		const char* cSocketThreadName);

	// interface:
public:
	virtual void OnClientReceiveData(
		UINT64 uUserData,
		int nSocketFD,
		const void *pBuffer,
		int nBufLen);

	virtual void OnClientDisconnectFromServer(
		UINT64 uUserData,
		int nSocketFD);

public:
	BOOL SendCheckStatusCmd(
		CSimpleStringA *pResultString);

	BOOL SendRebootCmd(
		CSimpleStringA *pResultString);

	BOOL SendPauseCmd(
		int nSecondsPerImage,
		RECT rcImagePosition,
		int nImageUrlBufLength,
		const char *cImageUrlBuffer,
		BOOL bImageNeedLoop,
		CSimpleStringA *pResultString);
	BOOL SendResumeCmd(
		CSimpleStringA *pResultString);

	BOOL SendOpenRoomCmd(
		const char* cQRCodeString,
		RECT rcQRCodePosition,
		int nVideoUrlBufLength,
		const char *cVideoUrlBuffer,
		int nImageUrlBufLength,
		const char *cImageUrlBuffer,
		RECT rcImagePosition,
		int nSecondsPerImage,
		BOOL bImageNeedLoop,
		CSimpleStringA *pResultString);
	BOOL SendCloseRoomCmd(
		int nVideoUrlBufLength,
		const char *cVideoUrlBuffer,
		CSimpleStringA *pResultString);
	BOOL SendPayCallbackCmd(
		int nVideoUrlBufLength,
		const char *cVideoUrlBuffer,
		CSimpleStringA *pResultString);

	BOOL SendPipPreviewCmd(
		RECT rcPipPosition,
		int nVideoUrlBufLength,
		const char *cVideoUrlBuffer,
		CSimpleStringA *pResultString);

private:
	void OnResponseCheckStatusCmd(
		HTTPCMDRESCHECKSTATUSCMD *pResCheckStatusCmdParam);

	void OnResponseRebootCmd(
		HTTPCMDRESREBOOTCMD *pResRebootCmdParam);

	void OnResponsePauseCmd(
		HTTPCMDRESPAUSECMD *pResPauseCmdParam);
	void OnResponseResumeCmd(
		HTTPCMDRESRESUMECMD *pResResumeCmdParam);

	void OnResponseOpenRoomCmd(
		HTTPCMDRESOPENROOMCMD *pResOpenRoomCmdParam);
	void OnResponseCloseRoomCmd(
		HTTPCMDRESCLOSEROOMCMD *pResCloseRoomCmdParam);
	void OnResponsePayCallbackCmd(
		HTTPCMDRESPAYCALLBACKCMD *pResPayCallbackCmdParam);

	void OnResponsePipPreviewCmd(
		HTTPCMDRESPIPPREVIEWCMD *pResPipPreviewCmdParam);

private:
	CBaseLock mRequestWithEventListLock;
	// NETFILEREQWITHEVENT
	CPtrListCtrl mRequestWithEventList;

	int mRequestID;
};
