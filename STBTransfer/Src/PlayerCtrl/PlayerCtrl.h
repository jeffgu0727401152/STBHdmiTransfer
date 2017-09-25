/*
 * PlayerCtrl.h
 *
 *  Created on: 2013-1-16
 *      Author: kyo
 */
#pragma once

#include "types.h"
#include "FileOperator.h"
#include "BaseThread.h"
#include "IHALInterface.h"

class CAVPlayer : public IAVPlayEventListener
{
public:
	CAVPlayer(
		PLAYERINDEX ePlayerIndex);
	virtual ~CAVPlayer();

	// interface
public:
	virtual void OnPlayCompleteEvent(
		PLAYERINDEX ePlayerIndex,
		PLAYCOMPLETE_REASONTYPE eReasonType);

	virtual void OnFirstAudioPtsEvent(
		PLAYERINDEX ePlayerIndex);
	virtual void OnFirstVideoPtsEvent(
		PLAYERINDEX ePlayerIndex);

	virtual void OnHttpStreamCaching(
		PLAYERINDEX ePlayerIndex,
		BOOL bCaching,
		float fReadSpeedKBPS);

public:
	void SetForceUseSTBStream(
		BOOL bForceUseSTBStream);

	void SetDataSource(
		BOOL bLoopPlay,
		BOOL bPassThrough,
		const char* cSongID,
		const char* cFileName);

	void Start();
	void Stop();
	void Pause();
	void Resume();
	void Replay();

	void SeekTo(
		int nPositionMS);

	void SetDisplayRect(
		BOOL bShow,
		BOOL bTopOfUI,
		int x,
		int y,
		int w,
		int h);
	BOOL IsNeedShow();
	BOOL IsTopOfUI();
	RECT GetDisplayRect();

	BOOL IsPassThrough();
	int GetPositionMS();
	int GetDurationMS();
	int GetPlayerState();
	const char* GetSongID();
	const char* GetFileName();

protected:
	PLAYERINDEX mPlayerIndex;
	IAVPlayerInterface *mpAVPlayerInterface;
};

class CPlayerCtrl :
	public IPlayCtrlEventListener,
	public IAVPlayEventListener
{
public:
	CPlayerCtrl();
	virtual ~CPlayerCtrl();

	// interface
public:
	virtual void OnPlayCompleteEvent(
		PLAYERINDEX ePlayerIndex,
		PLAYCOMPLETE_REASONTYPE eReasonType);

	virtual void OnFirstAudioPtsEvent(
		PLAYERINDEX ePlayerIndex);
	virtual void OnFirstVideoPtsEvent(
		PLAYERINDEX ePlayerIndex);

	virtual void OnHttpStreamCaching(
		PLAYERINDEX ePlayerIndex,
		BOOL bCaching,
		float fReadSpeedKBPS);

	virtual void OnHdmiOutConnect();
	virtual void OnHdmiOutDisconnect();
	virtual void OnHdmiInConnect();
	virtual void OnHdmiInDisconnect();

public:
	void Start();
	void Stop();

	// main player
public:
	void PlayMain(
		const char* cSongID,
		const char* cFileName,
		BOOL bLoopPlay,
		BOOL bPassThrough,
		int nMusicTrack);
	void PauseMain();
	void ResumeMain();
	void StopMain();

	// preview player
public:
	void StartPreview(
		const char* cSongID,
		const char* cFileName,
		BOOL bLoopPlay,
		BOOL bTopOfUI,
		int x,
		int y,
		int w,
		int h);
	void PausePreview();
	void ResumePreview();
	void StopPreview();

	void SetPreviewRect(
		BOOL bTopOfUI,
		int x,
		int y,
		int w,
		int h);

	// audio player
public:
	void PlayAudio(
		const char* cFileName,
		BOOL bLoopPlay,
		BOOL bPassThrough);
	void PauseAudio();
	void ResumeAudio();
	void StopAudio();

	// setting control
public:
	void SetMainVolume(
		int nVolume);
	void SetPcmVolume(
		int nVolume);
	void SetMicVolume(
		int nVolume);
	void SetMute(
		BOOL bMute);
	void SetPLTFormat(
		PLTFORMAT ePLTFormat);

private:
	BOOL mInitialized;

	IPlayerCtrlInterface *mpPlayerCtrlInterface;
	CAVPlayer mMainPlayer;
	CAVPlayer mPIPPlayer;
	CAVPlayer mAudioPlayer;

	BOOL mMute;
	int mMainVolume;
	int mPcmVolume;
	int mMicVolume;
	PLTFORMAT mPLTFormat;
};


class CMultiMediaCtrl
{
public:
	CMultiMediaCtrl();
	virtual ~CMultiMediaCtrl();

public:
	void Start();
	void Stop();

	// devices
public:
	void EnableHdmiIn(
		BOOL bEnable);
	void EnableHdmiInputComponent(
		BOOL bEnableVideo,
		BOOL bEnableAudio);
	void EnableAudioLineInToLineOut(
		BOOL bEnable);

private:
	IMultiMediaInterface *mpMultiMediaInterface;
};

