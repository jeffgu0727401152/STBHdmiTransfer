#pragma once

#include "BaseLock.h"
#include "BaseEvent.h"
#include "BaseThread.h"
#include "PtrControl.h"
#include "SocketInterface.h"

class CTCPSocketServer : public IThreadFuncInterface
{
public:
	CTCPSocketServer();
	virtual ~CTCPSocketServer();

public:
	BOOL Create(
		UINT16 uServerPort,
		BOOL bLocalSocket,
		BOOL bRawSocket,
		BOOL bUseMatchCode,
		IServerSocketListener *pSocketListener,
		UINT64 uUserData,
		const char* cSocketThreadName) ;
	void Close();

	BOOL SendData(
		int nSocketFD,
		const void *pData,
		int nLength);

	void BroadcastData(
		int nIgnoreSock,
		const void *pData,
		int nLength);

public:
	virtual BOOL ThreadLoop(
		UINT64 uThreadData);

private:
	BOOL RecvClientSocketData(
		int nClientSocket);

	void CloseClientSocket(
		int nSocketFD);

private:
	CBaseLock mCreateCloseLock;
	int mServerSocketFD;

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
