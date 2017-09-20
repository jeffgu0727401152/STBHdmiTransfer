#pragma once

#include "BaseLock.h"
#include "BaseEvent.h"
#include "BaseThread.h"
#include "PtrControl.h"
#include "SocketInterface.h"

class CTCPSocketClient : public IThreadFuncInterface
{
public:
	CTCPSocketClient();
	virtual ~CTCPSocketClient();

public:
	BOOL Create(
		const char *cServerAddr,
		UINT16 uPort,
		BOOL bLocalSocket,
		BOOL bRawSocket,
		BOOL bUseMatchCode,
		IClientSocketListener *pSocketListener,
		UINT64 uUserData,
		const char* cSocketThreadName);
	void Close();

	BOOL IsConnect();

	BOOL SendData(
		int nToSocket,
		const void *pData,
		int nLength);

public:
	virtual BOOL ThreadLoop(
		UINT64 uThreadData);

private:
	CBaseLock mCreateCloseLock;
	int mSocketFD;
	BOOL mCancelConnect;

	BOOL mRawSocket;
	BOOL mUseMatchCode;
	IClientSocketListener *mpSocketListener;
	UINT64 mUserData;
	CBaseThread  mRecvThread;
};
