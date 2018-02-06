#pragma once

#include "BaseLock.h"
#include "BaseEvent.h"
#include "BaseThread.h"
#include "PtrControl.h"
#include "SocketInterface.h"

class CUDTSocketServer : public IThreadFuncInterface
{
public:
	CUDTSocketServer();
	virtual ~CUDTSocketServer();

public:
	BOOL Create(
		UINT16 uServerPort,
		BOOL bRawSocket,
		BOOL bUseMatchCode,
		IServerSocketListener *pSocketListener,
		UINT64 uUserData,
		const char* cSocketThreadName) ;
	void Close();

	BOOL SendData(
		UDTSOCKET nSocketFD,
		const void *pData,
		int nLength);

	void BroadcastData(
		UDTSOCKET nIgnoreSock,
		const void *pData,
		int nLength);

public:
	virtual BOOL ThreadLoop(
		UINT64 uThreadData);

private:
	BOOL RecvClientSocketData(
		UDTSOCKET nClientSocket);

	void CloseClientSocket(
		UDTSOCKET nClientSocket);

private:
	CBaseLock mCreateCloseLock;
	UDTSOCKET mServerSocketFD;

	BOOL mRawSocket;
	BOOL mUseMatchCode;
	IServerSocketListener *mpSocketListener;
	UINT64 mUserData;
	CBaseThread mAcceptThread;
	CBaseThread mRecvThread;
	CBaseEvent mExitEvent;
	CBaseLock mClientSocketListLock;
	CPtrArrayCtrl mClientSocketList;
};
