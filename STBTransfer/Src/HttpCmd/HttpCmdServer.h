/*
 * PlayerCmdServer.h
 *
 *  Created on: 2013-1-18
 *      Author: kyo
 */

#pragma once

#include "TCPSocketServer.h"

#include "HttpCmdStruct.h"

class CHttpCmdServer : public CTCPSocketServer,
	public IServerSocketListener
{
	typedef CTCPSocketServer CParentClass;

public:
	CHttpCmdServer();
	virtual ~CHttpCmdServer();

public:
	BOOL Create(
		UINT16 uServerPort,
		BOOL bLocalSocket,
		const char* cSocketThreadName);

	// interface:
public:
	virtual void OnServerReceiveTCPData(
		UINT64 uUserData,
		int nSocketFD,
		const void *pBuffer,
		int nBufLen);

private:
	void OnRequestRebootCmd(
		int nSocketFD,
		HTTPCMDREQREBOOTCMD *pReqRebootCmd);

	void OnRequestPauseCmd(
		int nSocketFD,
		HTTPCMDREQPAUSECMD *pReqPauseCmd);
	void OnRequestResumeCmd(
		int nSocketFD,
		HTTPCMDREQRESUMECMD *pReqResumeCmd);

	void OnRequestOpenRoomCmd(
		int nSocketFD,
		HTTPCMDREQOPENROOMCMD *pReqOpenRoomCmd);
	void OnRequestCloseRoomCmd(
		int nSocketFD,
		HTTPCMDREQCLOSEROOMCMD *pReqCloseRoomCmd);

	void OnRequestCheckStatusCmd(
		int nSocketFD,
		HTTPCMDREQCHECKSTATUSCMD *pReqCheckStatusCmd);

private:
	CBaseLock mOperatorLock;
};
