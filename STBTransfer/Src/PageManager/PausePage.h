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

	void PictureTextureDownload(int urlListIdx);

private:
	CBaseWnd mPictureWnd;

	int mShowTimeMS;
	RECT mShowPosition;
	CPtrListCtrl mPictureUrlList;
	CPtrListCtrl mPictureTextureList;
	int mCurShowIndex;
};

extern CPausePage *gPausePage;
