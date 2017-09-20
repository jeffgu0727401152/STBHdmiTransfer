#pragma once

#include "types.h"
#include "BaseLock.h"
#include "BaseEvent.h"
#include "BaseThread.h"
#include "PtrControl.h"
#include "SocketInterface.h"

// UDP data will use SendMessage Function,
// and not need call FreePacket Function to release'

class CUDPSocket : public IThreadFuncInterface
{
public:
	CUDPSocket();
	virtual ~CUDPSocket();

public:
	BOOL Create(
		const char* cBindIP,
		UINT16 uPort,
		BOOL bRawSocket,
		BOOL bUseMatchCode,
		IUDPSocketListener *pSocketListener,
		UINT64 uUserData,
		const char* cSocketThreadName) ;
	void Close();

	BOOL SendData(
		const void *pData,
		int nLength);

public:
	virtual BOOL ThreadLoop(
		UINT64 uThreadData);

private:
	BOOL BindPort(
		const char* cBindIP,
		UINT16 uPort) ;

private:
	CBaseLock mCreateCloseLock;
	int mSocketFD;

	BOOL mRawSocket;
	BOOL mUseMatchCode;
	UINT16 mBroadCastPort;
	IUDPSocketListener *mpSocketListener;
	UINT64 mUserData;
	CBaseThread mRecvThread;
	char mBindIP[16];
};
