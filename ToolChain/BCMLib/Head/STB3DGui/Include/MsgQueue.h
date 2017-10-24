#pragma once

#include "types.h"
#include "PtrControl.h"
#include "BaseEvent.h"
#include "BaseLock.h"

class IMessageOwner
{
public:
	virtual ~IMessageOwner(void) {}

	virtual BOOL CanDispatchMsg(){return TRUE;}

	virtual void OnMsg(
		UINT32 uType,
		UINT64 wParam,
		UINT64 lParam)=0;
};

typedef struct tagMESSAGE
{
	IMessageOwner *pOwner;
	UINT32 uType;
	UINT64 wParam;
	UINT64 lParam;
}MESSAGE;

typedef struct tagBROADCASTMSG
{
	CPtrListCtrl sOwnerList;
	UINT32 uType;
} BROADCASTMSG;

#define MSG_REMOVE_FLAG_CMP_NONE			0
#define MSG_REMOVE_FLAG_CMP_WPARAM		1
#define MSG_REMOVE_FLAG_CMP_LPARAM		2
#define MSG_REMOVE_FLAG_CMP_ALLPARAM	3

class CMsgQueue
{
public:
	CMsgQueue();
	virtual ~CMsgQueue();

public:
	void AddMsg(
		IMessageOwner *pOwner,
		UINT32 uType,
		UINT64 wParam,
		UINT64 lParam);

	void RegisterBroadcastMsg(
		IMessageOwner *pOwner,
		UINT32 uType);
	void UnRegisterBroadcastMsg(
		IMessageOwner *pOwner,
		UINT32 uType);

	void AddBroadcastMsg(
		UINT32 uType,
		UINT64 wParam,
		UINT64 lParam,
		BOOL bOverlap,
		IMessageOwner *pExcludeOwner);
	void RemoveBroadcastMsg(
		UINT32 uType);

	void GetMsg(
		MESSAGE *pMsg);

	BOOL PeekMsg(
		IMessageOwner *pOwner,
		UINT32 uTypeMin,
		UINT32 uTypeMax,
		UINT32 uFlag,
		MESSAGE *pMsg);

	BOOL HasMsg(
		IMessageOwner *pOwner,
		UINT32 uTypeMin,
		UINT32 uTypeMax);

	void RemoveMsg(
		IMessageOwner *pOwner,
		UINT32 uTypeMin,
		UINT32 uTypeMax,
		UINT64 wParam=0,
		UINT64 lParam=0,
		UINT32 uRemoveFlag=MSG_REMOVE_FLAG_CMP_NONE);

private:
	void RemoveAllMsg();

private:
	CPtrListCtrl mMsgList;
	CPtrListCtrl mBroadcastMsgList;
	CBaseLock mMsgListLock;
	CBaseEvent mMsgEvent;
};
