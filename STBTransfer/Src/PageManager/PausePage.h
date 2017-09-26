#pragma once

#include "BaseWnd.h"

class CPausePage: public CBaseWnd
{
	typedef CBaseWnd CParentClass;

public:
	CPausePage();
	virtual ~CPausePage();

public:
	virtual void Create(
		CE3DCommand *pE3DEngine,
		CBaseWnd *pParent);

	virtual void OnLoadResource();

	virtual void OnWindowVisible(
		BOOL bVisible);

	virtual void OnTimer(
		int nTimerID);

public:
	void PerformHttpCmd_Pause(
		int nSecondsPerImage,
		RECT rcImagePosition,
		const char *pImageUrlBuffer);

	BOOL PictureTextureDownload(
		const char *cNetFile,
		CTexture *pTexture);

private:
	CBaseWnd mPictureWnd;

	int mShowTimeMS;
	RECT mShowPosition;

	CBaseLock mLock;
	CPtrListCtrl mPictureUrlList;
	int mCurShowIndex;
};

extern CPausePage *gPausePage;
