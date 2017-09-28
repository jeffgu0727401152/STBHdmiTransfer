#pragma once

#include "BaseWnd.h"

class CFirstLaunchPage:
		public CBaseWnd,
		public IThreadFuncInterface
{
	typedef CBaseWnd CParentClass;

public:
	CFirstLaunchPage();
	virtual ~CFirstLaunchPage();

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

	virtual BOOL ThreadLoop(
		UINT64 uThreadData);

public:
	void StartGetClientOpenUrl();
	void StopGetClientOpenUrl();
	void PerformLaunchVideo();

private:
	CBaseLock mLock;
	CPtrListCtrl mVideoUrlList;
	int mCurPlayIndex;

	int mExitThread;
	CBaseEvent mExitEvent;
	CBaseThread mGetOpenVideoUrlThread;
};

extern CFirstLaunchPage *gFirstLanchPage;
