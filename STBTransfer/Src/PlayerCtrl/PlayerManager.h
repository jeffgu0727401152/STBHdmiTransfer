#pragma once

#include "PlayerCtrl.h"

class CPlayerManager : public IMessageOwner
{
public:
	CPlayerManager();
	~CPlayerManager();

public:
	void SetMainPlayerSource(
		const char* cUrlList,
		BOOL bLoop);

	void SetPipPlayerSource(
		const char* cUrlList,
		BOOL bLoop,
		RECT rcPreview);

	virtual void OnMsg(
		UINT32 uType,
		UINT64 wParam,
		UINT64 lParam);

private:
	void SwitchMain();
	void SwitchPip();

private:
	CBaseLock mLock;

	CPtrListCtrl mMainPlayerUrlList;
	int mMainPlayerIndex;
	BOOL mMainPlayerLoopPlay;
	BOOL mIsHdmiPlaying;

	CPtrListCtrl mPiplayerUrlList;
	int mPipPlayerIndex;
	BOOL mPipPlayerLoopPlay;
	RECT mPreviewRect;
};
