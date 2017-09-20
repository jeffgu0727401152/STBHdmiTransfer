/*
 * BasePlayer.h
 *
 *  Created on: 2013-1-16
 *      Author: kyo
 */
#pragma once

#include "types.h"
#include "commfunc.h"
#include "BaseLock.h"
#include "FileOperator.h"
#include "DbgOutput.h"
#include "Song.h"
#include "IHALInterface.h"

typedef enum eBUFFER_FILE_TYPE
{
	BufferFileType_File=0,
	BufferFileType_Http
} BUFFER_FILE_TYPE;

class IHttpStreamEventListener
{
public:
	virtual ~IHttpStreamEventListener(void) {}

	virtual void OnHttpStreamCaching(
		BOOL bCaching,
		float fReadSpeedKBPS)=0;
};

class CBasePlayer : public IAVPlayerInterface
{
public:
	CBasePlayer()
	{
		mNetworkEdition = FALSE;
		mPlayerIndex = PLAYERINDEX_MAIN;
		mLoopPlay = FALSE;
		mPassThrough = FALSE;
		mForceUseSTBStream = FALSE;

		mNeedShow = FALSE;
		mTopOfUI = FALSE;
		SetRectXY(&mDisplayRect, 0, 0, 0, 0);

		mSongID[0] = '\0';
		mOEMID[0] = '\0';

		mPlayerState = PLAYER_STATE_STOP;
		mForceStop = FALSE;

		mpPlayEventListener = NULL;

		mHttpStreamCallbackType = HTTPSTREAMCALLBACKTYPE_CACHING;
	}

	virtual ~CBasePlayer(void) {}

public:
	virtual void SetAVPlayEventListener(
		IAVPlayEventListener *pListener)
	{
		mpPlayEventListener = pListener;
	}

	virtual void SetHttpStreamCallbackType(
		HTTPSTREAMCALLBACKTYPE eType)
	{
		mHttpStreamCallbackType = eType;
		HalPlayer_SetHttpStreamCallbackType();
	}

	virtual void SetForceUseSTBStream(
		BOOL bForceUseSTBStream)
	{
		mForceUseSTBStream = bForceUseSTBStream;
	}

	virtual void SetOEMID(
		const char* cOEMID)
	{
		SAFE_STRNCPY(mOEMID, cOEMID, 17);
	}

	virtual void SetDataSource(
		BOOL bNetworkEdition,
		PLAYERINDEX ePlayerIndex,
		BOOL bLoopPlay,
		BOOL bPassThrough,
		const char* cSongID,
		const char* cFileName)
	{
		mPlayerLock.Lock();

		mNetworkEdition = bNetworkEdition;
		mPlayerIndex = ePlayerIndex;
		mLoopPlay = bLoopPlay;
		mPassThrough = bPassThrough;

		SAFE_STRNCPY(mSongID, cSongID, KTV_ID_LENGTH);
		SAFE_STRNCPY(mFileName, cFileName, ENOUGH_FILE_PATH);

		LOGMSG(DBG_LEVEL_I,"SetDataSource:\n"
			"is network edition=%d\n"
			"player index=%d\n"
			"loop play=%d\n"
			"passthrough=%d\n"
			"songid=%s\n"
			"File name=%s\n",
			mNetworkEdition,
			mPlayerIndex,
			mLoopPlay,
			mPassThrough,
			mSongID,
			mFileName);

		mPlayerLock.Unlock();
	}

	virtual void Start()
	{
		mPlayerLock.Lock();

		Stop();

		mForceStop = FALSE;
		if (HalPlayer_Start())
		{
			mPlayerState = PLAYER_STATE_PLAYING;
		}
		else
		{
			HalPlayer_Stop();
		}

		mPlayerLock.Unlock();
	}

	virtual void Stop()
	{
		mPlayerLock.Lock();

		if (mPlayerState != PLAYER_STATE_STOP)
		{
			mPlayerState = PLAYER_STATE_STOP;
			mForceStop = TRUE;
			HalPlayer_Stop();
		}

		mPlayerLock.Unlock();
	}

	virtual void Pause()
	{
		mPlayerLock.Lock();

		if (mPlayerState == PLAYER_STATE_PLAYING)
		{
			mPlayerState = PLAYER_STATE_PAUSE;
			HalPlayer_Pause();
		}

		mPlayerLock.Unlock();
	}

	virtual void Resume()
	{
		mPlayerLock.Lock();

		if (mPlayerState == PLAYER_STATE_PAUSE)
		{
			mPlayerState = PLAYER_STATE_PLAYING;
			HalPlayer_Resume();
		}

		mPlayerLock.Unlock();
	}

	virtual void Replay()
	{
		mPlayerLock.Lock();

		HalPlayer_Replay();

		mPlayerLock.Unlock();
	}

	virtual void SeekTo(
		int nPositionMS)
	{
		mPlayerLock.Lock();

		HalPlayer_Seek(nPositionMS);

		mPlayerLock.Unlock();
	}

	virtual int GetPositionMS()
	{
		mPlayerLock.Lock();

		int nPositionMS = HalPlayer_GetPositionMS();

		mPlayerLock.Unlock();

		return nPositionMS;
	}

	virtual int GetDurationMS()
	{
		mPlayerLock.Lock();

		int nDurationMS = HalPlayer_GetDurationMS();

		mPlayerLock.Unlock();

		return nDurationMS;
	}

	virtual int GetPlayerState()
	{
		return mPlayerState;
	}

	virtual BOOL IsForceStop()
	{
		return mForceStop;
	}

	virtual BOOL IsNetworkEdition()
	{
		return mNetworkEdition;
	}

	virtual PLAYERINDEX GetPlayerIndex()
	{
		return mPlayerIndex;
	}

	virtual BOOL IsLoopPlay()
	{
		return mLoopPlay;
	}

	virtual BOOL IsPassThrough()
	{
		return mPassThrough;
	}

	virtual HTTPSTREAMCALLBACKTYPE GetHttpStreamCallbackType()
	{
		return mHttpStreamCallbackType;
	}

	virtual BOOL IsForceUseSTBStream()
	{
		return mForceUseSTBStream;
	}

	virtual const char* GetSongID()
	{
		return mSongID;
	}

	virtual const char* GetFileName()
	{
		return mFileName;
	}

	virtual const char* GetOEMID()
	{
		return mOEMID;
	}

	virtual BOOL IsNeedShow()
	{
		return mNeedShow;
	}

	virtual BOOL IsTopOfUI()
	{
		return mTopOfUI;
	}

	virtual RECT GetDisplayRect()
	{
		return mDisplayRect;
	}

	virtual void SetDisplayRect(
		BOOL bShow,
		BOOL bTopOfUI,
		int x,
		int y,
		int w,
		int h)
	{
		mPlayerLock.Lock();

		LOGMSG(DBG_LEVEL_I,"SetDisplayRect:\n"
			"player index=%d\n"
			"ShowUI=%d\n"
			"Top Of UI=%d\n"
			"Display rect=(%d, %d, %d, %d)\n",
			mPlayerIndex,
			bShow,
			bTopOfUI,
			x,
			y,
			x+w,
			y+h);

		RECT rcNew = {x, y, x+w, y+h};

		if ((mNeedShow != bShow) ||
			(mTopOfUI != bTopOfUI) ||
			(!IsRectEqual(&mDisplayRect, &rcNew)))
		{
			mNeedShow = bShow;
			mTopOfUI = bTopOfUI;
			SetRectXY(&mDisplayRect, x, y, w, h);

			if (mPlayerState != PLAYER_STATE_STOP)
			{
				HalPlayer_UpdateDisplayPos();
			}
		}

		mPlayerLock.Unlock();
	}

	virtual void GetVideoBuffer(
		BYTE *pBuffer,
		int nWidth,
		int nHeight,
		int nBytesPerPixel)
	{
		mPlayerLock.Lock();

		HalPlayer_GetVideoBuffer(
			pBuffer,
			nWidth,
			nHeight,
			nBytesPerPixel);

		mPlayerLock.Unlock();
	}

	virtual void SaveVideoFrame(
		const char* cSaveToFileName)
	{
		mPlayerLock.Lock();

		HalPlayer_SaveVideoFrame(cSaveToFileName);

		mPlayerLock.Unlock();
	}

	// interface:
protected:
	virtual void SendPlayerCompleteEvent(
		PLAYCOMPLETE_REASONTYPE eReasonType)
	{
		if (mpPlayEventListener)
		{
			mpPlayEventListener->OnPlayCompleteEvent(mPlayerIndex, eReasonType);
		}
	}

	virtual void SendFirstAudioPtsEvent()
	{
		if (mpPlayEventListener)
		{
			mpPlayEventListener->OnFirstAudioPtsEvent(mPlayerIndex);
		}
	}

	virtual void SendFirstVideoPtsEvent()
	{
		if (mpPlayEventListener)
		{
			mpPlayEventListener->OnFirstVideoPtsEvent(mPlayerIndex);
		}
	}

	virtual void SendHttpStreamEvent(
		BOOL bCaching,
		float fReadSpeedKBPS)
	{
		if (mpPlayEventListener)
		{
			mpPlayEventListener->OnHttpStreamCaching(
				mPlayerIndex,
				bCaching,
				fReadSpeedKBPS);
		}
	}

	virtual void HalPlayer_SetHttpStreamCallbackType()
	{
	}

	virtual BOOL HalPlayer_Start()
	{
		return FALSE;
	}

	virtual void HalPlayer_Stop()
	{}

	virtual void HalPlayer_Pause()
	{}

	virtual void HalPlayer_Resume()
	{}

	virtual void HalPlayer_Replay()
	{}

	virtual void HalPlayer_Seek(
		int nPositionMS)
	{}

	virtual int HalPlayer_GetPositionMS()
	{
		return 0;
	}

	virtual int HalPlayer_GetDurationMS()
	{
		return 0;
	}

	virtual void HalPlayer_UpdateDisplayPos()
	{}

	virtual void HalPlayer_GetVideoBuffer(
		BYTE *pBuffer,
		int nWidth,
		int nHeight,
		int nBytesPerPixel)
	{}

	virtual void HalPlayer_SaveVideoFrame(
		const char* cSaveToFileName)
	{}

private:
	CBaseLock mPlayerLock;
	int  mPlayerState;
	BOOL mForceStop;

	BOOL mNetworkEdition;
	PLAYERINDEX mPlayerIndex;
	BOOL mLoopPlay;
	BOOL mPassThrough;
	BOOL mForceUseSTBStream;

	char mSongID[KTV_ID_LENGTH];
	char mFileName[ENOUGH_FILE_PATH];
	char mOEMID[17];

	BOOL mNeedShow;
	BOOL mTopOfUI;
	RECT mDisplayRect;

	IAVPlayEventListener *mpPlayEventListener;

	HTTPSTREAMCALLBACKTYPE mHttpStreamCallbackType;
};

class CBasePlayerCtrl : public IPlayerCtrlInterface
{
public:
	CBasePlayerCtrl()
	{
		mpPlayEventListener = NULL;
		mpPlayCtrlEventListener = NULL;
	}

	virtual ~CBasePlayerCtrl(void) {}

	virtual void SetAVPlayEventListener(
		IAVPlayEventListener *pListener)
	{
		mpPlayEventListener = pListener;
	}

	virtual void SetPlayCtrlEventListener(
		IPlayCtrlEventListener *pListener)
	{
		mpPlayCtrlEventListener = pListener;
	}

	virtual void OnInit(
		int nDisplayWidth,
		int nDisplayHeight,
		int nExtraParamter){}
	virtual void OnDeInit(){}

	// setting control
public:
	virtual void SetMainVolume(
		int nVolume){}
	virtual void SetPcmVolume(
		int nVolume){}
	virtual void SetMicVolume(
		int nVolume){}
	virtual void SetMute(
		BOOL bMute){}
	virtual void SetAccompany(
		BOOL bMute,
		int  nMusicTrack,
		BOOL bAccompany){}
	virtual void SetPLTFormat(
		PLTFORMAT ePLTFormat){}

protected:
	IAVPlayEventListener *mpPlayEventListener;
	IPlayCtrlEventListener *mpPlayCtrlEventListener;
};

class CBaseAudioEffect : public IAudioEffectInterface
{
public:
	CBaseAudioEffect()
	{
	}

	virtual ~CBaseAudioEffect(void) {}

	virtual void OnInit(
		int nParamter){}
	virtual void OnDeInit(){}

public:
	virtual void ProcessCommand(
		const char* pAECmd){}
};
