/*
 * IHALInterface.h
 *
 *  Created on: 2013-1-16
 *      Author: kyo
 */
#pragma once

#include "types.h"
#include "SimpleString.h"

#define PLAYER_STATE_STOP		0
#define PLAYER_STATE_PLAYING	1
#define PLAYER_STATE_PAUSE		2

// driver中支持的enum类型个数
#define MAIN_VOLUME_MAX	15
#define PCM_VOLUME_MAX	15
#define MIC_VOLUME_MAX	15

#define ENOUGH_FILE_PATH	2048

typedef enum ePLAYERINDEX
{
	PLAYERINDEX_MAIN=0,
	PLAYERINDEX_PIP,
	PLAYERINDEX_PCM,
	PLAYERINDEX_CVBS,
} PLAYERINDEX;

typedef enum ePLAYCOMPLETE_REASONTYPE
{
	PlayComplete_ReasonType_Over=0,
	PlayComplete_ReasonType_StartError,
	PlayComplete_ReasonType_StreamError
} PLAYCOMPLETE_REASONTYPE;

typedef enum eHTTPSTREAMCALLBACKTYPE
{
	HTTPSTREAMCALLBACKTYPE_DISABLE=0, // 不回报
	HTTPSTREAMCALLBACKTYPE_CACHING, // 仅在缓存的时候回报
	HTTPSTREAMCALLBACKTYPE_ALWAYS, // 下载每个block后回报
} HTTPSTREAMCALLBACKTYPE;

#define AUDIO_STREAM_MAXCOUNT 	20
typedef struct tagMEDIAPROBEINFO
{
	unsigned int 		mediaType;
	unsigned int	 	videoPid;
	unsigned int 		videoCodec;
	unsigned int 		videoWidth;
	unsigned int 		videoHeight;
	unsigned int 		videoBitrate;
	unsigned int	 	audioCount;
	unsigned int	 	audioPid[AUDIO_STREAM_MAXCOUNT];
	unsigned int		audioCodec[AUDIO_STREAM_MAXCOUNT];
	unsigned int		audioSampleRate[AUDIO_STREAM_MAXCOUNT];
	unsigned int		audioSampleSize[AUDIO_STREAM_MAXCOUNT];
	unsigned int		audioBitrate[AUDIO_STREAM_MAXCOUNT];
} MEDIAPROBEINFO;

class IAVPlayEventListener
{
public:
	virtual ~IAVPlayEventListener(void) {}

	virtual void OnPlayCompleteEvent(
		PLAYERINDEX ePlayerIndex,
		PLAYCOMPLETE_REASONTYPE eReasonType)=0;

	virtual void OnFirstAudioPtsEvent(
		PLAYERINDEX ePlayerIndex)=0;
	virtual void OnFirstVideoPtsEvent(
		PLAYERINDEX ePlayerIndex)=0;

	virtual void OnHttpStreamCaching(
		PLAYERINDEX ePlayerIndex,
		BOOL bCaching,
		float fReadSpeedKBPS)=0;
};

class IAVPlayerInterface
{
public:
	virtual ~IAVPlayerInterface(void) {}

public:
	virtual void SetAVPlayEventListener(
		IAVPlayEventListener* pListener)=0;

	virtual void SetHttpStreamCallbackType(
		HTTPSTREAMCALLBACKTYPE eType)=0;

	virtual void SetForceUseSTBStream(
		BOOL bForceUseSTBStream)=0;

	virtual void SetOEMID(
		const char* cOEMID)=0;

	virtual void SetDataSource(
		BOOL bNetworkEdition,
		PLAYERINDEX ePlayerIndex,
		BOOL bLoopPlay,
		BOOL bPassThrough,
		const char* cSongID,
		const char* cFileName)=0;

	virtual void GetProbeInfoByBuffer(
		const BYTE* pProbeBuffer,
		int nBufLength,
		MEDIAPROBEINFO *pProbeInfo)=0;
	virtual void SetProbeInfo(
		MEDIAPROBEINFO *pProbeInfo)=0;
	virtual void WritePushBuffer(
		const BYTE* pBuffer,
		int nBufLength)=0;
	virtual void FlushPushBuffer()=0;

	virtual BOOL Start()=0;
	virtual void Stop()=0;
	virtual void Pause()=0;
	virtual void Resume()=0;
	virtual void Replay()=0;
	virtual void SeekTo(
		int nPositionMS)=0;

	virtual int GetPositionMS()=0;
	virtual int GetDurationMS()=0;
	virtual int GetPlayerState()=0;
	virtual BOOL IsForceStop()=0;
	virtual PLAYERINDEX GetPlayerIndex()=0;

	virtual BOOL IsLoopPlay()=0;
	virtual BOOL IsPassThrough()=0;
	virtual const char* GetSongID()=0;
	virtual const char* GetFileName()=0;
	virtual BOOL IsNeedShow()=0;
	virtual BOOL IsTopOfUI()=0;
	virtual RECT GetDisplayRect()=0;
	virtual void SetDisplayRect(
		BOOL bShow,
		BOOL bTopOfUI,
		int x,
		int y,
		int w,
		int h)=0;

	virtual void GetVideoBuffer(
		BYTE* pBuffer,
		int nWidth,
		int nHeight,
		int nBytesPerPixel)=0;

	virtual void SaveVideoFrame(
		const char* cSaveToFileName)=0;
};

IAVPlayerInterface* CreateAVPlayerInterface();
void DeleteAVPlayerInterface(
	IAVPlayerInterface* pAVPlayerInterface);


typedef enum ePLTFORMAT
{
	PLTFORMAT_1080P_E=0,
	PLTFORMAT_1080i_E,
	PLTFORMAT_720P_E,
	PLTFORMAT_NTSC_E,
	PLTFORMAT_4K_P30_E,
	PLTFORMAT_4K_P60_E,
	PLTFORMAT_COUNT
}PLTFORMAT;

class IPlayCtrlEventListener
{
public:
	virtual ~IPlayCtrlEventListener(void) {}

	virtual void OnHdmiOutConnect()=0;
	virtual void OnHdmiOutDisconnect()=0;

	virtual void OnHdmiInConnect()=0;
	virtual void OnHdmiInDisconnect()=0;
};

class IPlayerCtrlInterface
{
public:
	virtual ~IPlayerCtrlInterface(void) {}

	virtual void SetAVPlayEventListener(
		IAVPlayEventListener* pListener)=0;

	virtual void SetPlayCtrlEventListener(
		IPlayCtrlEventListener* pListener)=0;

	virtual void OnInit(
		int nDisplayWidth,
		int nDisplayHeight,
		int nExtraParamter)=0;
	virtual void OnDeInit()=0;

	// setting control
public:
	virtual void SetMainVolume(
		int nVolume)=0;
	virtual void SetPcmVolume(
		int nVolume)=0;
	virtual void SetMicVolume(
		int nVolume)=0;
	virtual void SetMute(
		BOOL bMute)=0;
	virtual void SetAccompany(
		BOOL bMute,
		int  nMusicTrack,
		BOOL bAccompany)=0;
	virtual void SetPLTFormat(
		PLTFORMAT ePLTFormat)=0;
	virtual void SetCVBSOffset(
		int nLeftOffset,
		int nTopOffset,
		int nRightOffset,
		int nBottomOffset)=0;
};

IPlayerCtrlInterface* CreatePlayerCtrlInterface();
void DeletePlayerCtrlInterface(
	IPlayerCtrlInterface* pPlayerCtrlInterface);



typedef enum eUSERLOGINTYPE
{
	USERLOGINTYPE_BY_ACCOUNT_E, /**< 帐户名加密码登录 */
	USERLOGINTYPE_BY_PHONE_E, /**< 手机号加密码登录 */
	USERLOGINTYPE_BY_VERIFY_CODE_E, /**< 手机号加验证码登录 */
} USERLOGINTYPE;

typedef enum eCLOUD_USER_RESPONSE_RESULT
{
	CLOUD_USER_RESPONSE_RESULT_OK=0,
	CLOUD_USER_RESPONSE_RESULT_ERR_UNKNOWN,
	CLOUD_USER_RESPONSE_RESULT_TIMEOUT,
	CLOUD_USER_RESPONSE_RESULT_ERR_NOTEXIST,
	CLOUD_USER_RESPONSE_RESULT_ERR_PASSWORD_INVALID,
	CLOUD_USER_RESPONSE_RESULT_ERR_TOKEN_EXPIRED,
	CLOUD_USER_RESPONSE_RESULT_ERR_MAXCOUNT
} CLOUD_USER_RESPONSE_RESULT;

class ICloudEventListener
{
public:
	virtual ~ICloudEventListener(void) {}

	virtual void OnCloudLoginExpired(
		UINT64 uUserData)=0;
};

class ICloudInterface
{
public:
	virtual ~ICloudInterface(void) {}

	virtual BOOL OnInit(
		const char* cProjectName,
		ICloudEventListener* pCloudEventListener,
		UINT64 uUserData)=0;
	virtual void OnDeInit()=0;

	virtual CLOUD_USER_RESPONSE_RESULT DeleteMediaFile(
		int nMediaID)=0;
	virtual CLOUD_USER_RESPONSE_RESULT GetMediaUrl(
		int nMediaID,
		int nTranscodeType,
		CSimpleStringA* pMediaUrl,
		CSimpleStringA* pVodUrl)=0;

public:
	// 用户注册
	virtual CLOUD_USER_RESPONSE_RESULT CloudUserRegister(
		const char* cUserName,
		const char* cPassword,
		const char* cNickName,
		const char* cBirthday,
		const char* cPhone,
		char cGender)=0;
	// 用户登陆
	virtual CLOUD_USER_RESPONSE_RESULT CloudUserLogin(
		USERLOGINTYPE eLoginType,
		const char* cUserName,
		const char* cPassword,
		CSimpleStringA* pNickName,
		CSimpleStringA* pBirthday,
		CSimpleStringA* pPhone,
		char* cGender)=0;
	// 用户登出
	virtual CLOUD_USER_RESPONSE_RESULT CloudUserLogout()=0;
	// 删除用户
	virtual CLOUD_USER_RESPONSE_RESULT CloudUserDelete()=0;
	// 修改密码
	virtual CLOUD_USER_RESPONSE_RESULT CloudUserChangePassword(
		const char* oldPassword,
		const char* cNewPassword)=0;
	// 修改用户信息
	virtual CLOUD_USER_RESPONSE_RESULT CloudUserChangeInfomation(
		const char* cNickName,
		const char* cBirthday,
		const char* cPhone,
		char cGender)=0;
};

ICloudInterface* CreateCloudInterface();
void DeleteCloudInterface(
	ICloudInterface* pCloudInterface);



typedef struct tagUSBAUDIOINPUTDEV
{
	UINT32 uCardID;
	char id[1024];
	char name[1024];
} USBAUDIOINPUTDEV;

typedef enum eVIDEORECORD_QUALITYTYPE
{
	VIDEORECORD_QUALITYTYPE_LOW=0,
	VIDEORECORD_QUALITYTYPE_NORMAL,
	VIDEORECORD_QUALITYTYPE_HIGH
} VIDEORECORD_QUALITYTYPE;

typedef enum eLIVEBROADCAST_EVENTTYPE
{
	LIVEBROADCAST_EVENTTYPE_UNKNOWN=0,
	LIVEBROADCAST_EVENTTYPE_INITERROR,
	LIVEBROADCAST_EVENTTYPE_OPENINPUTERROR,
	LIVEBROADCAST_EVENTTYPE_OPENOUTPUTERROR,
	LIVEBROADCAST_EVENTTYPE_READINPUTERROR,
	LIVEBROADCAST_EVENTTYPE_WRITEOUTPUTERROR
} LIVEBROADCAST_EVENTTYPE;

class ICameraDataCallbackListener
{
public:
	virtual ~ICameraDataCallbackListener(void) {}

	virtual BOOL OnCameraDataYUV422(
		UINT64 uUserData,
		int nWidth,
		int nHeight,
		BYTE* pYUV422,
		int nYUV422Length)=0;

	virtual BOOL OnCameraDataARGB32(
		UINT64 uUserData,
		int nWidth,
		int nHeight,
		BYTE* pARGB32,
		int nARGB32Length)=0;
};

class ICameraColorKeyCallbackListener
{
public:
	virtual ~ICameraColorKeyCallbackListener(void) {}

	virtual void OnColorKeyLearnComplete(
		UINT64 uUserData)=0;
};

typedef enum eUPLOAD_STOPREASON
{
	UPLOAD_STOPREASON_BY_NONE = 0,
	UPLOAD_STOPREASON_BY_USER,
	UPLOAD_STOPREASON_BY_MAXSIZE,
	UPLOAD_STOPREASON_BY_CONNECTION
} UPLOAD_STOPREASON;

class IUploadProgressListener
{
public:
	virtual ~IUploadProgressListener(void) {}

	virtual int OnUploadProgress(
		UINT64 uUserData,
		int nTotalUploadBytes,
		int nDroppedBytes,
		int nSizeToUpload,
		float fSpeed,
		BOOL bStopped,
		UPLOAD_STOPREASON eStopReason)=0;
};

class ILiveBroadcastEventCallbackListener
{
public:
	virtual ~ILiveBroadcastEventCallbackListener(void) {}

	virtual void OnLiveBroadcastEventCallback(
		UINT64 uUserData,
		LIVEBROADCAST_EVENTTYPE eEventType)=0;
};

class IVideoRecordBufferCallbackListener
{
public:
	virtual ~IVideoRecordBufferCallbackListener(void) {}

	virtual void OnVideoRecordBufferCallback(
		UINT64 uUserData,
		BYTE* pBuffer,
		int nLength)=0;
};

class IMultiMediaInterface
{
public:
	virtual ~IMultiMediaInterface(void) {}

	// devices
public:
	virtual void StartCamera(
		const char* cDevName,
		SIZE szResolution,
		int nFrameRate,
		int nHorzFlip,
		RECT rcCamera,
		ICameraDataCallbackListener* pCameraDataCallbackListener,
		UINT64 uUserData)=0;
	virtual void GetCameraResolution(
		SIZE* pszResolution)=0;
	virtual void StopCamera()=0;
	virtual BOOL CameraGetAutoWhiteBalance(
		int *autoWB,
		int *defvalue)=0;
	virtual BOOL CameraSetAutoWhiteBalance(
		int autoWB)=0;
	virtual BOOL CameraGetWhiteBalance(
		int *min,
		int *max,
		int *value,
		int *defvalue)=0;
	virtual BOOL CameraSetWhiteBalance(
		int value)=0;
	virtual BOOL CameraGetAutoFocus(
		int *autoFocus,
		int *defvalue)=0;
	virtual BOOL CameraSetAutoFocus(
		int autoFocus)=0;
	virtual BOOL CameraGetFocus(
		int *min,
		int *max,
		int *value,
		int *defvalue)=0;
	virtual BOOL CameraSetFocus(
		int value)=0;
	virtual BOOL CameraGetAutoExposure(
		int *autoExp,
		int *defvalue)=0;
	virtual BOOL CameraSetAutoExposure(
		int autoExp)=0;
	virtual BOOL CameraGetExposure(
		int *min,
		int *max,
		int *value,
		int *defvalue)=0;
	virtual BOOL CameraSetExposure(
		int value)=0;
	virtual BOOL CameraGetAutoGain(
		int *autoGain,
		int *defvalue)=0;
	virtual BOOL CameraSetAutoGain(
		int autoGain)=0;
	virtual BOOL CameraGetGain(
		int *min,
		int *max,
		int *value,
		int *defvalue)=0;
	virtual BOOL CameraSetGain(
		int value)=0;
	virtual void CameraColorKeyInit(
		int nWidth,
		int nHeight)=0;
		virtual void CameraColorKeyDeInit()=0;
	virtual void CameraColorKeyEnable(
		BOOL bEnable)=0;
	virtual void CameraColorKeyLearning(
		int nColorKeyDetectFrames,
		ICameraColorKeyCallbackListener* pCameraColorKeyCallbackListener,
		UINT64 uUserData)=0;
	virtual void CameraDecoratorInit(
		const char *faceCascadeFilename)=0;
	virtual void CameraDecoratorDeinit()=0;
	virtual void CameraDecoratorEnable(
		BOOL bEnable)=0;
	virtual void CameraDecoratorSetting(
		unsigned char* pDecoratorBuffer,
		int nDecoratorBufWidth,
		int nDecoratorBufHeight,
		int nFaceLeft,
		int nFaceTop,
		int nFaceWidth,
		int nFaceHeight)=0;

	virtual void I2SAudioInputInit()=0;
	virtual void I2SAudioInputDeInit()=0;
	virtual void I2SAudioInputStart()=0;
	virtual void I2SAudioInputStop()=0;
	virtual BOOL IsI2SAudioInputStarted()=0;
	virtual void I2SLineInToLineOutStart()=0;
	virtual void I2SLineInToLineOutStop()=0;

	virtual void USBAudioInputDevEnum(
		USBAUDIOINPUTDEV* pDevArray,
		UINT32* pnDevCount)=0;
	virtual void USBAudioInputInit(
		void** ppUsbAudioDevHandle,
		UINT32 uCardID,
		int nChannelCount,
		int nSampleRate)=0;
	virtual void USBAudioInputDeInit(
		void* pUsbAudioDevHandle)=0;
	virtual void USBAudioInputStart(
		void* pUsbAudioDevHandle)=0;
	virtual void USBAudioInputStop(
		void* pUsbAudioDevHandle)=0;
	virtual BOOL IsUSBAudioInputStarted()=0;

	virtual void EnableHdmiIn(
		BOOL bEnable)=0;

	virtual void MuteHdmiInputAudio(
		BOOL bMute)=0;

	// recorder
public:
	virtual void SetRecordStereo(
		BOOL bUseStereo)=0;

	virtual CLOUD_USER_RESPONSE_RESULT StartAudioRecord(
		IUploadProgressListener* pUploadProgressListener,
		UINT64 uUploadProgressUserData,
		int nTranscodeType,
		const char* cSongName,
		const char* cSingerName)=0;
	virtual void StopAudioRecord(
		int* pnMediaID)=0;

	virtual CLOUD_USER_RESPONSE_RESULT StartVideoRecord(
		VIDEORECORD_QUALITYTYPE eVideoQualityType,
		int nVideoWidth,
		int nVideoHeight,
		int nFrameRate,
		BOOL bIncludePlayer,
		PLAYERINDEX ePlayerIndex,
		BOOL bIncludeCamera,
		RECT rcCamera,
		BOOL bIncludeOSD,
		RECT rcOSDFrom,
		RECT rcOSDTo,
		BOOL bEnableUpload,
		IUploadProgressListener* pUploadProgressListener,
		UINT64 uUploadProgressUserData,
		int nTranscodeType,
		const char* cSongName,
		const char* cSingerName,
		BOOL bEnableLiveBroadcast,
		ILiveBroadcastEventCallbackListener* pLiveBroadcastEventCallbackListener,
		UINT64 uLiveBroadcastEventUserData,
		const char* cWrapFormat,
		const char* cBroadcastUrl,
		IVideoRecordBufferCallbackListener* pVideoRecordBufferCallbackListener,
		UINT64 uVideoRecordBufferUserData)=0;
	virtual void StopVideoRecord(
		int* pnMediaID)=0;
};

IMultiMediaInterface* CreateMultiMediaInterface();
void DeleteMultiMediaInterface(
	IMultiMediaInterface* pMultiMediaInterface);



class IOSDInterface
{
public:
	virtual ~IOSDInterface(void) {}

public:
	virtual void OSDHWInit()=0;
	virtual void OSDHWDeinit()=0;
	virtual BOOL IsBGROrder()=0;
	virtual BOOL UseOpenGL()=0;
	virtual BYTE* GetOSDHWAddress()=0;
	virtual void ReleaseOSDHWAddress(
		BYTE*  pOSDAddress)=0;
	virtual void OSDHWRefresh()=0;
	virtual void OSDHWRefreshWithEgl(
		BOOL bEglOnOSD)=0;

	virtual void OSDEGLInit(
		int nWidth,
		int nHeight)=0;
	virtual void OSDReadEGLBuffer(
		int nLeft,
		int nTop,
		int nWidth,
		int nHeight,
		BYTE* pBuffer)=0;
};

IOSDInterface* CreateOSDInterface();
void DeleteOSDInterface(
	IOSDInterface* pOSDInterface);

class IAudioEffectInterface
{
public:
	virtual ~IAudioEffectInterface(void) {}

	virtual void OnInit(
		int nParamter)=0;
	virtual void OnDeInit()=0;

	// EQ control
public:
	virtual BOOL GetAECardVersion(
		CSimpleStringA *pVersion)=0;

	virtual void ProcessCommand(
		const char* pAECmd)=0;
};

IAudioEffectInterface* CreateAudioEffectInterface();
void DeleteAudioEffectInterface(
	IAudioEffectInterface* pAudioEffectInterface);


typedef enum eSCORECHANNELMODE
{
	SCORECHANNELMODE_MONO,
	SCORECHANNELMODE_LEFT,
	SCORECHANNELMODE_RIGHT,
	SCORECHANNELMODE_STEREO,
} SCORECHANNELMODE;

typedef struct tagSCOREINDICATOR
{
	int nStartTime;			/**< 起始时间，单位:ms */
	int nKeepTime;			/**< 持续时长，单位:ms */
	int nNoteLevel;			/**< 音符等级，0~127 */
} SCOREINDICATOR;

typedef enum eSCORE_MATCH_TYPE
{
	SCORE_MATCH_TYPE_HIT=0,
	SCORE_MATCH_TYPE_OUTOFTUNE,
	SCORE_MATCH_TYPE_OUTOFSYNC,
	SCORE_MATCH_TYPE_HIT_PERFECT,
	SCORE_MATCH_TYPE_HIT_NORMAL,
	SCORE_MATCH_TYPE_HIT_BAD
}SCORE_MATCH_TYPE;

class IScoreEventListener
{
public:
	virtual ~IScoreEventListener(void) {}

	virtual void OnScoreMatchEvent(
		SCORE_MATCH_TYPE eMatchType,
		int nPitchOffset,
		UINT64 uUserData)=0;
};

class IScoreInterface
{
public:
	virtual ~IScoreInterface(void) {}

	virtual BOOL OnInit(
		IScoreEventListener* pScoreEventListener,
		UINT64 uUserData,
		const char* cCacheDir,
		int nSampleRate,
		SCORECHANNELMODE eChannelMode,
		int nErrorThreshold,
		int nMicSilentThreshold)=0;
	virtual void OnDeInit()=0;

public:
	// 加载歌曲评分资料
	virtual BOOL PrepareScore(
		const char* cSongID,
		BOOL bUseUsbScore,
		void* pUsbAudioDevHandle)=0;
	// 获取评分资料信息
	virtual void GetNoteLevelRange(
		int* pnMin,
		int* pnMax)=0;
	virtual int GetIndicatorCount()=0;
	virtual void GetIndicator(
		SCOREINDICATOR* pIndicators,
		int* pnCount)=0;
	// 评分
	virtual void StartScore()=0;
	virtual void StopScore(
		void* pUsbAudioDevHandle)=0;
	virtual void PauseScore()=0;
	virtual void ResumeScore()=0;
	virtual void SetOriginalSingerMode(
		BOOL bOriginalSingerMode)=0;

	virtual void GetCurrentNoteLevel(
		int* pnNoteLevel,
		BOOL* pbHit)=0;
	virtual void GetCurrentScore(
		int* pnScore)=0;
	virtual void GetLastScoreDetail(
		int* pnTimbreScore,
		int* pnTuneScore,
		int* pnRhythmScore,
		int* pnMelodyScore,
		int* pnStabilityScore)=0;
	virtual void GetRanking(
		int nScore,
		int* pnRanking,
		int* pnBeatCount)=0;
	virtual void GetSongMaxScore(
		CSimpleStringA* pMaxScoreOwner,
		int* pnMaxScore)=0;
	virtual void GetScoreTime(
		int *pScoreTime)=0;
};

IScoreInterface* CreateScoreInterface();
void DeleteScoreInterface(
		IScoreInterface* pScoreInterface);


typedef enum eIOTYPE
{
	IOTYPE_NONE=0,
	IOTYPE_IR,
	IOTYPE_FP,
	IOTYPE_HS,
	IOTYPE_LED,
	IOTYPE_SATA
} IOTYPE;

class IIONotifyListener
{
public:
	virtual ~IIONotifyListener(void) {}

	virtual void OnIONotify(
		IOTYPE eIOType,
		int nID,
		int nState,
		UINT64 uUserData)=0;
};

class IIOInterface
{
public:
	virtual ~IIOInterface(void) {}

	virtual BOOL OnInit(
		IIONotifyListener* pIONotifyListener,
		UINT64 uUserData)=0;
	virtual void OnDeInit()=0;

public:
	virtual BOOL IsHeadsetPlugged()=0;
};

IIOInterface* CreateIOInterface();
void DeleteIOInterface(
	IIOInterface* pIOInterface);

