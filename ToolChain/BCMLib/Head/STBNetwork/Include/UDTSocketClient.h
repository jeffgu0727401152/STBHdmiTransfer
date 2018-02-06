#pragma once

#include "BaseLock.h"
#include "BaseEvent.h"
#include "BaseThread.h"
#include "PtrControl.h"
#include "SocketInterface.h"

class CUDTSocketClient : public IThreadFuncInterface
{
public:
	CUDTSocketClient();
	virtual ~CUDTSocketClient();

public:
	BOOL Create(
		const char *cServerAddr,
		UINT16 uPort,
		BOOL bRawSocket,
		BOOL bUseMatchCode,
		IClientSocketListener *pSocketListener,
		UINT64 uUserData,
		const char* cSocketThreadName);
	void Close();

	BOOL IsConnect();

	BOOL SendData(
		UDTSOCKET nToSocket,
		const void *pData,
		int nLength);

public:
	virtual BOOL ThreadLoop(
		UINT64 uThreadData);

private:
	CBaseLock mCreateCloseLock;
	UDTSOCKET mSocketFD;
	BOOL mCancelConnect;

	BOOL mRawSocket;
	BOOL mUseMatchCode;
	IClientSocketListener *mpSocketListener;
	UINT64 mUserData;
	CBaseThread  mRecvThread;
};
