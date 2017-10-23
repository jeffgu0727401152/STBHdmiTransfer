#pragma once

#include "BaseWnd.h"
#include "GifWnd.h"

class CPausePage: public CBaseWnd,
	public IGifWndFrameChangeListener
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

	//interface
public:
	virtual void OnGifWndFrameChange(
		CImageBuffer *pImageBuffer,
		int nCurIndex,
		int nTotalIndex,
		UINT64 uUserData);

public:
	void PerformHttpCmd_Pause(
		int nSecondsPerImage,
		RECT rcImagePosition,
		const char *pImageUrlBuffer);

	BOOL PictureLocalDownload(
		const char *cNetFile,
		char cLocalFile[MAX_PATH]);

private:
	CGifWnd mPictureWnd;

	int mShowTimeMS;
	RECT mShowPosition;

	CBaseLock mLock;
	CPtrListCtrl mPictureUrlList;
	int mCurShowIndex;
};

extern CPausePage *gPausePage;
