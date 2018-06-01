#pragma once

#include "GifWnd.h"

class CPicturePage: public CBaseWnd,
	public IGifWndFrameChangeListener
{
	typedef CBaseWnd CParentClass;

public:
	CPicturePage();
	virtual ~CPicturePage();

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
	void PerformHttpCmd_SetQRCode(
		const char* cQRCodeString,
		RECT rcQRCodePosition);

	void PerformHttpCmd_SetPicture(
		const char* cPictureUrlList,
		RECT rcPicturePosition,
		int nSecondsPerImage,
		BOOL bLoop);

private:
	void CreateQRImage(
		const char* cString,
		CImageBuffer* pImageBuffer);

	BOOL PictureLocalDownload(
		const char *cNetFile,
		char cLocalFile[MAX_PATH]);

private:
	CGifWnd mPictureWnd;
	CGifWnd mQRcodeWnd;

	int mShowTimeMS;

	CBaseLock mLock;
	CPtrListCtrl mPictureUrlList;
	int mCurShowIndex;
	BOOL mPictureLoop;
};

extern CPicturePage *gPicturePage;
