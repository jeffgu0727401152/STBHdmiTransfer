#pragma once

#include "BaseWnd.h"

class COpenRoomPage: public CBaseWnd
{
	typedef CBaseWnd CParentClass;

public:
	COpenRoomPage();
	virtual ~COpenRoomPage();

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
	void PerformHttpCmd_OpenRoom(
		const char* cQRCodeString,
		RECT rcQRCodePosition,
		const char *cVideoUrlBuffer);

private:
	void CreateQRImage(
		RECT rcQRCodePosition,
		const char* cString);

private:
	CBaseWnd mPictureWnd;

	CBaseLock mLock;
	CPtrListCtrl mVideoUrlList;
	int mCurPlayIndex;
};

extern COpenRoomPage *gOpenRoomPage;
