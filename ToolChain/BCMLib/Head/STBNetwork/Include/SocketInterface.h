/*
 * SocketInterface.h
 *
 *  Created on: 2013-1-30
 *      Author: kyo
 */

#ifndef SOCKETINTERFACE_H_
#define SOCKETINTERFACE_H_

#include "types.h"
#include "PtrControl.h"
#include "SimpleString.h"
#include "Buffer.h"
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <arpa/inet.h>

#define UDP_MAX_SIZE	1400

#define MSG_TO_ALLSOCKET			(-1)
#define MSG_TO_OTHERSOCKET			(-2)
#define MSG_TO_SERVERSOCKET			(-3)


class IClientSocketListener
{
public:
	virtual ~IClientSocketListener(void) {}

	virtual void OnClientReceiveTCPData(
		UINT64 uUserData,
		int nSocketFD,
		const void *pBuffer,
		int nLength)
	{}

	virtual void OnClientDisconnectFromServer(
		UINT64 uUserData,
		int nSocketFD)
	{}
};

class IServerSocketListener
{
public:
	virtual ~IServerSocketListener(void) {}

	virtual void OnServerReceiveTCPData(
		UINT64 uUserData,
		int nSocketFD,
		const void *pBuffer,
		int nLength)
	{}

	virtual void OnServerAcceptClient(
		UINT64 uUserData,
		int nSocketFD)
	{}

	virtual void OnServerCloseClient(
		UINT64 uUserData,
		int nSocketFD)
	{}
};

class IUDPSocketListener
{
public:
	virtual ~IUDPSocketListener(void) {}

	virtual void OnUDPDataReceived(
		UINT64 uUserData,
		const void *pBuffer,
		int nLength)
	{}
};

#pragma pack(push)
#pragma pack(1)

typedef struct tagSOCKETPACKET
{
	int nToSocket;
	int nDataLen;
	BYTE *pDataBuf;
}SOCKETPACKET;

#pragma pack(pop)

typedef struct tagIPINTERFACEINFO
{
	char cName[16];
	char cMac[32];
	char cIPv4[16];
	char cNetmask[16];
	char cGateway[16];
} IPINTERFACEINFO;

BOOL IsValidIPAddr4(
	const char* cIPAddr);

BOOL ResolveHostname(
	const char* cHostName,
	CSimpleStringA* pIPAddr);

void GetDNSList(
	CPtrCtrl *pDNSList);
void FreeDNSList(
	CPtrCtrl *pDNSList);

// pNetcardList: char list
void GetNetcardList(
	CPtrCtrl *pNetcardList);

void FreeNetcardList(
	CPtrCtrl *pNetcardList);

void GetEthMacAddress(
	CSimpleStringA *pMacAddr);

void GetAvailbalEthNetworkInterface(
	CSimpleStringA *pInterfaceName);

void GetAvailbalWlanNetworkInterface(
	CSimpleStringA *pInterfaceName);

void GetIPInterfaceInfoList(
	CPtrCtrl *pIPInterfaceInfoList);

void FreeIPInterfaceInfoList(
	CPtrCtrl *pIPInterfaceInfoList);

void GetEthDefaultIPSetting(
	IPINTERFACEINFO *pIPInterface);

void GetWlanDefaultIPSetting(
	IPINTERFACEINFO *pIPInterface);

void SetIPInfo(
	const char* cInterfaceName,
	const char* cIPAddr=NULL,
	const char* cNetmask=NULL,
	const char* cGateWay=NULL);

void GetDefaultDNS(
	char cDNS[16]);

void SetDNS(
	const char* cDNS);

BOOL IsNetworkAvailable(
	const char *cInterfaceName);

void SetSocketMatchCode(
	UINT32 uMatchCode);
UINT32 GetSocketMatchCode();

BOOL RecvTCPPacket(
	int nSocketFD,
	BOOL bUseMatchCode,
	SOCKETPACKET *pPacket);
BOOL RecvTCPRaw(
	int nSocketFD,
	CBuffer *pBuffer);

BOOL RecvUDPPacket(
	int nSocketFD,
	BOOL bUseMatchCode,
	struct sockaddr_in *pRecvAddr,
	socklen_t uAddrSize,
	SOCKETPACKET *pPacket);
BOOL RecvUDPRaw(
	int nSocketFD,
	struct sockaddr_in *pRecvAddr,
	socklen_t uAddrSize,
	CBuffer *pBuffer);

void FreePacketBuffer(
	SOCKETPACKET *pPacket);

BOOL SendPacket(
	int nSocketFD,
	BOOL bUDPSocket,
	UINT16 uBroadcastPort,
	SOCKETPACKET *pPacket);
BOOL SendRaw(
	int nSocketFD,
	BOOL bUDPSocket,
	UINT16 uBroadcastPort,
	CBuffer *pBuffer);

// 这是使用普通的socket直接传输数据，
// 不包含 SOCKETPACKET头 以及 matchcode, socket tag信息
// nSocketFD==-1: will create a new socket to transfer
void BoradcastRaw(
	int nSocketFD,
	UINT16 uSendPort,
	const void* pBuffer,
	int nBufLen,
	UINT64 uTimeout);

UINT16 GetPeerIPAddrPort(
	int nSocketFD,
	char* cIPAddr,
	int nIPAddrBufLen);

#endif /* SOCKETINTERFACE_H_ */
