#include "PlayerCtrl.h"
#include "../GlobalUIClass.h"

CPlayerManager::CPlayerManager()
{
	mMainPlayerIndex = 0;
	mMainPlayerLoopPlay = FALSE;
	mIsHdmiPlaying = FALSE;

	mPipPlayerIndex = 0;
	mPipPlayerLoopPlay = FALSE;

	SetRectXY(&mPreviewRect, 0, 0, 0, 0);
}

CPlayerManager::~CPlayerManager()
{}

void CPlayerManager::SetMainPlayerSource(
	const char* cUrlList,
	BOOL bLoop)
{
	mLock.Lock();

	DelArrayList(&mMainPlayerUrlList, char);
	mMainPlayerIndex = 0;
	mMainPlayerLoopPlay = bLoop;

	CPtrArrayCtrl sUrlList;
	const char *cDevString = DevideStringByCharListA(
		cUrlList,
		-1,
		",",
		1,
		FALSE,
		&sUrlList,
		-1);

	for (int i = 0; i < sUrlList.GetCount(); i++)
	{
		const char* cUrl = (const char*)sUrlList.GetAt(i);
		if (cUrl && cUrl[0])
		{
			char* cVideoUrl = new char[strlen(cUrl)+1];
			if (cVideoUrl)
			{
				strcpy(cVideoUrl, cUrl);
				mMainPlayerUrlList.AddData(cVideoUrl);
			}
		}
	}

	mLock.Unlock();

	Internal_DelArrayA(cDevString);

	SwitchMain();
}

void CPlayerManager::SetPipPlayerSource(
		const char* cUrlList,
		BOOL bLoop,
		RECT rcPreview)
{
	mLock.Lock();

	DelArrayList(&mPiplayerUrlList, char);
	mPipPlayerIndex = 0;
	mPipPlayerLoopPlay = bLoop;
	mPreviewRect = rcPreview;

	switch(gKTVConfig.GetPLTFormat())
	{
	case PLTFORMAT_1080P_E:
	case PLTFORMAT_1080i_E:
		LOGMSG(DBG_LEVEL_I, "%s: g_InitPltFormat is 1080p/i, use the mPreviewRect/2*3 !\n", __PRETTY_FUNCTION__);
		mPreviewRect.bottom = mPreviewRect.bottom/2*3;
		mPreviewRect.left = mPreviewRect.left/2*3;
		mPreviewRect.top = mPreviewRect.top/2*3;
		mPreviewRect.right = mPreviewRect.right/2*3;
		break;
	case PLTFORMAT_720P_E:
		LOGMSG(DBG_LEVEL_I, "%s: g_InitPltFormat is 720p, use the raw mPreviewRect!\n", __PRETTY_FUNCTION__);
		break;
	default:
		LOGMSG(DBG_LEVEL_I, "%s: g_InitPltFormat is not in 0,1,2, use the raw mPreviewRect!\n", __PRETTY_FUNCTION__);
		break;
	}

	CPtrArrayCtrl sUrlList;
	const char *cDevString = DevideStringByCharListA(
		cUrlList,
		-1,
		",",
		1,
		FALSE,
		&sUrlList,
		-1);

	for (int i = 0; i < sUrlList.GetCount(); i++)
	{
		const char* cUrl = (const char*)sUrlList.GetAt(i);
		if (cUrl && cUrl[0])
		{
			char* cVideoUrl = new char[strlen(cUrl)+1];
			if (cVideoUrl)
			{
				strcpy(cVideoUrl, cUrl);
				mPiplayerUrlList.AddData(cVideoUrl);
			}
		}
	}

	mLock.Unlock();

	Internal_DelArrayA(cDevString);

	SwitchPip();
}

void CPlayerManager::OnMsg(
		UINT32 uType,
		UINT64 wParam,
		UINT64 lParam)
{
	switch(uType)
	{
	case MSG_PLAYER_COMPLETE:
		if ((PLAYERINDEX)wParam == PLAYERINDEX_MAIN)
		{
			if ((PLAYCOMPLETE_REASONTYPE)lParam == PlayComplete_ReasonType_StartError)
			{
				mLock.Lock();
				mMainPlayerIndex--;
				if (mMainPlayerIndex<0)
				{
					mMainPlayerIndex = 0;
				}
				mMainPlayerUrlList.DeleteAt(mMainPlayerIndex);

				mLock.Unlock();
			}
			SwitchMain();
		}
		else if ((PLAYERINDEX)wParam == PLAYERINDEX_PIP)
		{
			if ((PLAYCOMPLETE_REASONTYPE)lParam == PlayComplete_ReasonType_StartError)
			{
				mLock.Lock();
				mPipPlayerIndex--;
				if (mPipPlayerIndex<0)
				{
					mPipPlayerIndex = 0;
				}
				mPiplayerUrlList.DeleteAt(mPipPlayerIndex);
				mLock.Unlock();
			}
			SwitchPip();
		}

		break;

	default:
		break;
	}
}

void CPlayerManager::SwitchMain()
{
	mLock.Lock();

	const char* cVideoUrl = NULL;

	if (mMainPlayerUrlList.GetCount() > 0)
	{
		cVideoUrl = (const char*)mMainPlayerUrlList.GetAt(mMainPlayerIndex);

		if (mMainPlayerLoopPlay)
		{
			mMainPlayerIndex = (mMainPlayerIndex+1) % mMainPlayerUrlList.GetCount();
		}
		else
		{
			if (mMainPlayerIndex < mMainPlayerUrlList.GetCount())
			{
				mMainPlayerIndex ++;
			}
		}
	}

	if (cVideoUrl == NULL)
	{
		if (!mIsHdmiPlaying)
		{
			LOGMSG(DBG_LEVEL_I, "%s:%d, main play hdmi!\n", __PRETTY_FUNCTION__, __LINE__);
			gPlayerCtrl->PlayMain(
				"99999910", //SONGID_HDMIIN
				"hdmiin://", //filepath
				FALSE, //loopplay
				FALSE, //passthrough
				0);
			gMultiMediaCtrl->EnableAudioLineInToLineOut(TRUE);
			mIsHdmiPlaying = TRUE;
		}
	}
	else
	{
		gMultiMediaCtrl->EnableAudioLineInToLineOut(FALSE);

		LOGMSG(DBG_LEVEL_I, "%s:%d, main Play video: %s!\n", __PRETTY_FUNCTION__, __LINE__, cVideoUrl);
		gPlayerCtrl->PlayMain(
			"90000000", //SONGID_USER_START
			cVideoUrl, //filepath
			FALSE, //loopplay
			FALSE, //passthrough
			0);
		mIsHdmiPlaying = FALSE;
	}

	mLock.Unlock();
}

void CPlayerManager::SwitchPip()
{
	mLock.Lock();

	const char* cVideoUrl = NULL;

	int nCount = mPiplayerUrlList.GetCount();
	if (nCount > 0)
	{
		cVideoUrl = (const char*)mPiplayerUrlList.GetAt(mPipPlayerIndex);

		if (mPipPlayerLoopPlay)
		{
			mPipPlayerIndex = (mPipPlayerIndex+1) % nCount;
		}
		else
		{
			if (mPipPlayerIndex < nCount)
			{
				mPipPlayerIndex ++;
			}
		}
	}

	if (cVideoUrl == NULL)
	{
		LOGMSG(DBG_LEVEL_I, "%s:%d, stop pip play!\n", __PRETTY_FUNCTION__, __LINE__);
		gPlayerCtrl->StopPreview();
	}
	else
	{
		LOGMSG(DBG_LEVEL_I, "%s:%d, pip Play video: %s!\n", __PRETTY_FUNCTION__, __LINE__, cVideoUrl);
		gPlayerCtrl->StartPreview(
			"90000001", //SONGID_USER_START
			cVideoUrl, //filepath
			FALSE, //loopplay
			FALSE, //top of UI
			mPreviewRect.left,
			mPreviewRect.top,
			RECTWIDTH(mPreviewRect),
			RECTHEIGHT(mPreviewRect));
	}

	mLock.Unlock();
}
