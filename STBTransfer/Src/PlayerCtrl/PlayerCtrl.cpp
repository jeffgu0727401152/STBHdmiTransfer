#include "PlayerCtrl.h"
#include <errno.h>
#include <signal.h>
#include <dlfcn.h>
#include "commfunc.h"
#include "DbgOutput.h"
#include "FileOperator.h"
#include "BaseApp.h"
#include "../GlobalUIClass.h"


CAVPlayer::CAVPlayer(
	PLAYERINDEX ePlayerIndex)
{
	mPlayerIndex = ePlayerIndex;

	mpAVPlayerInterface = CreateAVPlayerInterface();
	if (mpAVPlayerInterface)
	{
		mpAVPlayerInterface->SetAVPlayEventListener(this);
	}
}

CAVPlayer::~CAVPlayer()
{
	if (mpAVPlayerInterface)
	{
		mpAVPlayerInterface->Stop();

		DeleteAVPlayerInterface(mpAVPlayerInterface);
		mpAVPlayerInterface = NULL;
	}
}

void CAVPlayer::OnPlayCompleteEvent(
	PLAYERINDEX ePlayerIndex,
	PLAYCOMPLETE_REASONTYPE eReasonType)
{
	if (!mpAVPlayerInterface)
	{
		return;
	}

	if (mpAVPlayerInterface->IsForceStop())
	{
		return;
	}

	if (((eReasonType == PlayComplete_ReasonType_StartError) ||
		(eReasonType == PlayComplete_ReasonType_StreamError)) ||
		((eReasonType == PlayComplete_ReasonType_Over) &&
		!mpAVPlayerInterface->IsLoopPlay()))
	{
		LOGMSG(DBG_LEVEL_I,"OnPlayComplete, index=%d, reason=%d+++!\n",
			ePlayerIndex, eReasonType);

		if (ePlayerIndex == PLAYERINDEX_MAIN)
		{
			theBaseApp->AddBroadcastMsg(
				MSG_PLAYER_COMPLETE,
				(UINT64)ePlayerIndex,
				(UINT64)eReasonType,
				FALSE,
				NULL);
		}

		LOGMSG(DBG_LEVEL_I,"OnPlayComplete ---!\n");
	}
}

void CAVPlayer::OnFirstAudioPtsEvent(
	PLAYERINDEX ePlayerIndex)
{}
void CAVPlayer::OnFirstVideoPtsEvent(
	PLAYERINDEX ePlayerIndex)
{}

void CAVPlayer::OnHttpStreamCaching(
	PLAYERINDEX ePlayerIndex,
	BOOL bCaching,
	float fReadSpeedKBPS)
{}

void CAVPlayer::SetForceUseSTBStream(
	BOOL bForceUseSTBStream)
{
	if (mpAVPlayerInterface)
	{
		mpAVPlayerInterface->SetForceUseSTBStream(bForceUseSTBStream);
	}
}

void CAVPlayer::SetDataSource(
	BOOL bLoopPlay,
	BOOL bPassThrough,
	const char* cSongID,
	const char* cFileName)
{
#ifdef NETWORK_EDITION
	BOOL bNetworkEdition = TRUE;
#else
	BOOL bNetworkEdition = FALSE;
#endif

	if (mpAVPlayerInterface)
	{
		mpAVPlayerInterface->SetDataSource(
			bNetworkEdition,
			mPlayerIndex,
			bLoopPlay,
			bPassThrough,
			cSongID,
			cFileName);
	}
}

void CAVPlayer::Start()
{
	if (mpAVPlayerInterface)
	{
		mpAVPlayerInterface->Start();
	}
}

void CAVPlayer::Stop()
{
	if (mpAVPlayerInterface)
	{
		mpAVPlayerInterface->Stop();
	}
}

void CAVPlayer::Pause()
{
	if (mpAVPlayerInterface)
	{
		mpAVPlayerInterface->Pause();
	}
}

void CAVPlayer::Resume()
{
	if (mpAVPlayerInterface)
	{
		mpAVPlayerInterface->Resume();
	}
}

void CAVPlayer::Replay()
{
	if (mpAVPlayerInterface)
	{
		mpAVPlayerInterface->Replay();
	}
}


void CAVPlayer::SeekTo(
	int nPositionMS)
{
	if (mpAVPlayerInterface)
	{
		mpAVPlayerInterface->SeekTo(nPositionMS);
	}
}

void CAVPlayer::SetDisplayRect(
	BOOL bShow,
	BOOL bTopOfUI,
	int x,
	int y,
	int w,
	int h)
{
	if (mpAVPlayerInterface)
	{
		mpAVPlayerInterface->SetDisplayRect(bShow, bTopOfUI, x, y, w, h);
	}
}

BOOL CAVPlayer::IsNeedShow()
{
	if (mpAVPlayerInterface)
	{
		return mpAVPlayerInterface->IsNeedShow();
	}
	else
	{
		return FALSE;
	}
}

BOOL CAVPlayer::IsTopOfUI()
{
	if (mpAVPlayerInterface)
	{
		return mpAVPlayerInterface->IsTopOfUI();
	}
	else
	{
		return FALSE;
	}
}

RECT CAVPlayer::GetDisplayRect()
{
	if (mpAVPlayerInterface)
	{
		return mpAVPlayerInterface->GetDisplayRect();
	}
	else
	{
		RECT rcEmpyt = {0, 0, 0, 0};
		return rcEmpyt;
	}
}

BOOL CAVPlayer::IsPassThrough()
{
	if (mpAVPlayerInterface)
	{
		return mpAVPlayerInterface->IsPassThrough();
	}
	else
	{
		return FALSE;
	}
}

int CAVPlayer::GetPositionMS()
{
	if (mpAVPlayerInterface)
	{
		return mpAVPlayerInterface->GetPositionMS();
	}
	else
	{
		return 0;
	}
}

int CAVPlayer::GetDurationMS()
{
	if (mpAVPlayerInterface)
	{
		return mpAVPlayerInterface->GetDurationMS();
	}
	else
	{
		return 0;
	}
}

int CAVPlayer::GetPlayerState()
{
	if (mpAVPlayerInterface)
	{
		return mpAVPlayerInterface->GetPlayerState();
	}
	else
	{
		return PLAYER_STATE_STOP;
	}
}

const char* CAVPlayer::GetSongID()
{
	if (mpAVPlayerInterface)
	{
		return mpAVPlayerInterface->GetSongID();
	}
	else
	{
		return NULL;
	}
}

const char* CAVPlayer::GetFileName()
{
	if (mpAVPlayerInterface)
	{
		return mpAVPlayerInterface->GetFileName();
	}
	else
	{
		return NULL;
	}
}



CPlayerCtrl::CPlayerCtrl():
	mMainPlayer(PLAYERINDEX_MAIN),
	mPIPPlayer(PLAYERINDEX_PIP),
	mAudioPlayer(PLAYERINDEX_PCM)
{
	mInitialized = FALSE;

	mMute = FALSE;
	mMainVolume = (MAIN_VOLUME_MAX+1)/2;
	mPcmVolume = (PCM_VOLUME_MAX+1)/2;
	mMicVolume = (MIC_VOLUME_MAX+1)/2;
	mPLTFormat = PLTFORMAT_1080P_E;

	mpPlayerCtrlInterface = NULL;
}

CPlayerCtrl::~CPlayerCtrl()
{
	Stop();
}

void CPlayerCtrl::OnPlayCompleteEvent(
	PLAYERINDEX ePlayerIndex,
	PLAYCOMPLETE_REASONTYPE eReasonType)
{
	LOGMSG(DBG_LEVEL_I,"%s: ePlayerIndex=%d, eReasonType=%d\n",
		__PRETTY_FUNCTION__,
		ePlayerIndex,
		eReasonType);
	switch(ePlayerIndex)
	{
	case PLAYERINDEX_MAIN:
		mMainPlayer.OnPlayCompleteEvent(PLAYERINDEX_MAIN, eReasonType);
		break;
	case PLAYERINDEX_PIP:
		mPIPPlayer.OnPlayCompleteEvent(PLAYERINDEX_PIP, eReasonType);
		break;
	case PLAYERINDEX_PCM:
		mAudioPlayer.OnPlayCompleteEvent(PLAYERINDEX_PCM, eReasonType);
		break;

	default:
		break;
	}
}

void CPlayerCtrl::OnFirstAudioPtsEvent(
	PLAYERINDEX ePlayerIndex)
{}
void CPlayerCtrl::OnFirstVideoPtsEvent(
	PLAYERINDEX ePlayerIndex)
{}

void CPlayerCtrl::OnHttpStreamCaching(
	PLAYERINDEX ePlayerIndex,
	BOOL bCaching,
	float fReadSpeedKBPS)
{}

void CPlayerCtrl::OnHdmiOutConnect()
{
}

void CPlayerCtrl::OnHdmiOutDisconnect()
{
}

void CPlayerCtrl::OnHdmiInConnect()
{
	gHdmiPage->PostMsg(MSG_HDMIIN_CONNECT, 0, 0);
}

void CPlayerCtrl::OnHdmiInDisconnect()
{
	gHdmiPage->PostMsg(MSG_HDMIIN_DISCONNECT, 0, 0);
}

void CPlayerCtrl::Start()
{
	if (mInitialized)
	{
		LOGMSG(DBG_LEVEL_I, "%s: already Initialized\n", __PRETTY_FUNCTION__);
		return;
	}

	mInitialized = TRUE;

	mpPlayerCtrlInterface = CreatePlayerCtrlInterface();
	if (mpPlayerCtrlInterface)
	{
		mpPlayerCtrlInterface->SetAVPlayEventListener(this);
		mpPlayerCtrlInterface->SetPlayCtrlEventListener(this);
		mpPlayerCtrlInterface->OnInit(
			gKTVConfig.GetDisplayWidth(),
			gKTVConfig.GetDisplayHeight(),
			0);
	}

	mMainPlayer.SetForceUseSTBStream(gKTVConfig.IsForceUseSTBStream());
	mPIPPlayer.SetForceUseSTBStream(gKTVConfig.IsForceUseSTBStream());
	mAudioPlayer.SetForceUseSTBStream(gKTVConfig.IsForceUseSTBStream());
}

void CPlayerCtrl::Stop()
{
	if (!mInitialized)
	{
		LOGMSG(DBG_LEVEL_I, "%s: already DeInitialized\n", __PRETTY_FUNCTION__);
		return;
	}

	mInitialized = FALSE;

	LOGMSG(DBG_LEVEL_I, "function %s quit\n", __PRETTY_FUNCTION__);

	mMainPlayer.Stop();
	mPIPPlayer.Stop();
	mAudioPlayer.Stop();

	if (mpPlayerCtrlInterface)
	{
		mpPlayerCtrlInterface->OnDeInit();
		DeletePlayerCtrlInterface(mpPlayerCtrlInterface);
		mpPlayerCtrlInterface = NULL;
	}
}

// main player
void CPlayerCtrl::PlayMain(
	const char* cSongID,
	const char* cFileName,
	BOOL bLoopPlay,
	BOOL bPassThrough,
	int nMusicTrack)
{
	LOGMSG(DBG_LEVEL_I, "Play Main Start. \n");

	mMainPlayer.Stop();

	if (!cFileName)
	{
		return;
	}

	//cFileName = "https://booth-vietnam.oss-cn-hongkong.aliyuncs.com/multimedia/542687ea14735f99cdbe570c4e9dd595.dat";

	LOGMSG(DBG_LEVEL_I,"PlayMain:filename=%s\n", cFileName);

	mMainPlayer.SetForceUseSTBStream(gKTVConfig.IsForceUseSTBStream());

	mMainPlayer.SetDataSource(
		bLoopPlay,
		bPassThrough,
		cSongID,
		cFileName);

	mMainPlayer.Start();

	LOGMSG(DBG_LEVEL_I, "SetMainVolume ... \n");
	SetMainVolume(mMainVolume);
	LOGMSG(DBG_LEVEL_I, "SetMute ... \n");
	SetMute(mMute);

	LOGMSG(DBG_LEVEL_I, "Play Main Over. \n");
}

void CPlayerCtrl::PauseMain()
{
	LOGMSG(DBG_LEVEL_I, "%s \n", __PRETTY_FUNCTION__);
	mMainPlayer.Pause();
}

void CPlayerCtrl::ResumeMain()
{
	LOGMSG(DBG_LEVEL_I, "%s \n", __PRETTY_FUNCTION__);
	mMainPlayer.Resume();
}

void CPlayerCtrl::StopMain()
{
	LOGMSG(DBG_LEVEL_I, "%s \n", __PRETTY_FUNCTION__);
	mMainPlayer.SetDisplayRect(FALSE, mMainPlayer.IsTopOfUI(), 0, 0, 0, 0);
	mMainPlayer.Stop();
}

//Preview
void CPlayerCtrl::StartPreview(
	const char* cSongID,
	const char* cFileName,
	BOOL bLoopPlay,
	BOOL bTopOfUI,
	int x,
	int y,
	int w,
	int h)
{
	LOGMSG(DBG_LEVEL_I, "%s \n", __PRETTY_FUNCTION__);
	mPIPPlayer.SetForceUseSTBStream(gKTVConfig.IsForceUseSTBStream());

	mPIPPlayer.SetDataSource(
		bLoopPlay,
		FALSE,
		cSongID,
		cFileName);

	mPIPPlayer.SetDisplayRect(TRUE, bTopOfUI, x, y, w, h);

#if (!defined(PC_VERSION)) && (!defined(ANDROID))
	// BCM7231 830 的板子必须在 启动Preview后，重置一次MTV，否则会有黑屏的可能
	BOOL bMTVVisible = mMainPlayer.IsNeedShow();
	BOOL bMTVTopOfUI = mMainPlayer.IsTopOfUI();
	RECT rcMTVDisplay = mMainPlayer.GetDisplayRect();
	mMainPlayer.SetDisplayRect(
		FALSE,
		bMTVTopOfUI,
		rcMTVDisplay.left,
		rcMTVDisplay.top,
		RECTWIDTH(rcMTVDisplay),
		RECTHEIGHT(rcMTVDisplay));
#endif

	mPIPPlayer.Start();

#if (!defined(PC_VERSION)) && (!defined(ANDROID))
	mMainPlayer.SetDisplayRect(
		bMTVVisible,
		bMTVTopOfUI,
		rcMTVDisplay.left,
		rcMTVDisplay.top,
		RECTWIDTH(rcMTVDisplay),
		RECTHEIGHT(rcMTVDisplay));
#endif
}

void CPlayerCtrl::PausePreview()
{
	LOGMSG(DBG_LEVEL_I, "%s \n", __PRETTY_FUNCTION__);
	mPIPPlayer.Pause();
}

void CPlayerCtrl::ResumePreview()
{
	LOGMSG(DBG_LEVEL_I, "%s \n", __PRETTY_FUNCTION__);
	mPIPPlayer.Resume();
}

void CPlayerCtrl::StopPreview()
{
	LOGMSG(DBG_LEVEL_I, "%s \n", __PRETTY_FUNCTION__);
	mPIPPlayer.SetDisplayRect(FALSE, mPIPPlayer.IsTopOfUI(), 0, 0, 0, 0);
	mPIPPlayer.Stop();
}

void CPlayerCtrl::SetPreviewRect(
	BOOL bTopOfUI,
	int x,
	int y,
	int w,
	int h)
{
	mPIPPlayer.SetDisplayRect(TRUE, bTopOfUI, x, y, w, h);
}

// audio player
void CPlayerCtrl::PlayAudio(
	const char* cFileName,
	BOOL bLoopPlay,
	BOOL bPassThrough)
{
	mAudioPlayer.SetForceUseSTBStream(gKTVConfig.IsForceUseSTBStream());

	mAudioPlayer.SetDataSource(
		bLoopPlay,
		bPassThrough,
		"",
		cFileName);
	mAudioPlayer.Start();

	SetPcmVolume(mPcmVolume);
}

void CPlayerCtrl::PauseAudio()
{
	mAudioPlayer.Pause();
}

void CPlayerCtrl::ResumeAudio()
{
	mAudioPlayer.Resume();
}

void CPlayerCtrl::StopAudio()
{
	mAudioPlayer.Stop();
}

void CPlayerCtrl::SetMainVolume(
	int nVolume)
{
	if (nVolume > MAIN_VOLUME_MAX)
	{
		nVolume = MAIN_VOLUME_MAX;
	}
	else if (nVolume < 0)
	{
		nVolume = 0;
	}

	mMainVolume = nVolume;

	if (!mMute)
	{
		if (mpPlayerCtrlInterface)
		{
			mpPlayerCtrlInterface->SetMainVolume(nVolume);
		}
	}
}

void CPlayerCtrl::SetPcmVolume(
	int nVolume)
{
	if (nVolume > PCM_VOLUME_MAX)
	{
		nVolume = PCM_VOLUME_MAX;
	}
	else if (nVolume < 0)
	{
		nVolume = 0;
	}

	mPcmVolume = nVolume;

	if (!mMute)
	{
		if (mpPlayerCtrlInterface)
		{
			mpPlayerCtrlInterface->SetPcmVolume(nVolume);
		}
	}
}

void CPlayerCtrl::SetMicVolume(
	int nVolume)
{
	if (nVolume > MIC_VOLUME_MAX)
	{
		nVolume = MIC_VOLUME_MAX;
	}
	else if (nVolume < 0)
	{
		nVolume = 0;
	}

	mMicVolume = nVolume;

	if (!mMute)
	{
		if (mpPlayerCtrlInterface)
		{
			mpPlayerCtrlInterface->SetMicVolume(nVolume);
		}
	}
}

void CPlayerCtrl::SetMute(
	BOOL bMute)
{
	if (mMute == bMute)
	{
		return;
	}

	mMute = bMute;

	if (mpPlayerCtrlInterface)
	{
		mpPlayerCtrlInterface->SetMute(mMute);
	}

	if (!mMute)
	{
		SetMainVolume(mMainVolume);
		SetPcmVolume(mPcmVolume);
		SetMicVolume(mMicVolume);
	}
}

void CPlayerCtrl::SetPLTFormat(
	PLTFORMAT ePLTFormat)
{
	mPLTFormat = ePLTFormat;

	if (mpPlayerCtrlInterface)
	{
		mpPlayerCtrlInterface->SetPLTFormat(mPLTFormat);
	}
}


CMultiMediaCtrl::CMultiMediaCtrl()
{
	mpMultiMediaInterface = NULL;
}

CMultiMediaCtrl::~CMultiMediaCtrl()
{
	Stop();
}

void CMultiMediaCtrl::Start()
{
	mpMultiMediaInterface = CreateMultiMediaInterface();
	EnableHdmiIn(TRUE);
	EnableHdmiInputComponent(TRUE, FALSE);
}

void CMultiMediaCtrl::Stop()
{
	EnableHdmiIn(FALSE);

	if (mpMultiMediaInterface)
	{
		DeleteMultiMediaInterface(mpMultiMediaInterface);
		mpMultiMediaInterface = NULL;
	}
}

void CMultiMediaCtrl::EnableHdmiIn(
	BOOL bEnable)
{
	if (mpMultiMediaInterface)
	{
		LOGMSG(DBG_LEVEL_I, "EnableHdmiIn bEnable=%d\n", bEnable);
		mpMultiMediaInterface->EnableHdmiIn(bEnable);
	}
}

void CMultiMediaCtrl::EnableHdmiInputComponent(
	BOOL bEnableVideo,
	BOOL bEnableAudio)
{
	if (mpMultiMediaInterface)
	{
		LOGMSG(DBG_LEVEL_I, "EnableHdmiInputComponent bEnableVideo=%d, bEnableAudio=%d\n", bEnableVideo, bEnableAudio);
		mpMultiMediaInterface->EnableHdmiInputComponent(bEnableVideo, bEnableAudio);
	}
}

void CMultiMediaCtrl::EnableAudioLineInToLineOut(
	BOOL bEnable)
{
	if (mpMultiMediaInterface)
	{
		LOGMSG(DBG_LEVEL_I, "EnableAudioLineInToLineOut bEnable=%d\n", bEnable);
		mpMultiMediaInterface->EnableAudioLineInToLineOut(bEnable);
	}
}
