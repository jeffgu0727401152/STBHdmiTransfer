#pragma once

#include "BaseWnd.h"

class CCloseRoomPage: public CBaseWnd
{
	typedef CBaseWnd CParentClass;

public:
	CCloseRoomPage();
	virtual ~CCloseRoomPage();

public:
	virtual void Create(
		CE3DCommand *pE3DEngine,
		CBaseWnd *pParent);

	virtual void OnLoadResource();

	virtual void OnWindowVisible(
		BOOL bVisible);

	// interface
public:
	void OnMsg(
		UINT32 uType,
		UINT64 wParam,
		UINT64 lParam);

public:
	void PerformHttpCmd_CloseRoom(
		const char *cVideoUrlBuffer);

private:
	CBaseLock mLock;
	CPtrListCtrl mVideoUrlList;
	int mCurPlayIndex;
};

extern CCloseRoomPage *gCloseRoomPage;
