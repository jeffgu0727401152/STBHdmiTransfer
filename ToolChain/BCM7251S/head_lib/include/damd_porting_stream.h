/*************************************************************************
                             All Rights Reserved
                                 R&D Dept.
*************************************************************************/


/*************************************************************************

Filename:       damd_porting_stream.h

Description:    播放器相关函数

Author:

Date:

Modify Log:
 ------------------------------------------------------------------------
1.
 修改人  :
 修改时间:
 修改原因:
 修改方法:
 ------------------------------------------------------------------------
2.
 修改人  :
 修改时间:
 修改原因:
 修改方法:
 ------------------------------------------------------------------------
*************************************************************************/
#ifndef _WSD_AL_PLAYER_H_
#define _WSD_AL_PLAYER_H_

#ifdef __cplusplus
extern "C" {
#endif

/***********************************************************************
*                                包含头文件
************************************************************************/
#include <unistd.h>
#include "damd_base_type.h"
#include "damd_porting_media.h"


/***********************************************************************
*                                常量定义
***********************************************************************/
/******************************************************************
描述: 播放器类型定义

成员:
	WSD_AL_PLAYER_MAIN_E: 主播放器

	WSD_AL_PLAYER_PIP_E : 预览播放器

	WSD_AL_PLAYER_PCM_E : 混音播放器

注意:
******************************************************************/
typedef enum wsd_al_player_type_e_
{
    WSD_AL_PLAYER_MAIN_E = 0,
	WSD_AL_PLAYER_PIP_E  = 1,
	WSD_AL_PLAYER_PCM_E  = 2,
	WSD_AL_PLAYER_BACK_E = 3,
	WSD_AL_PLAYER_MAX_E  = 4,
}WSD_AL_PLAYER_TYPE_E;


/******************************************************************
描述: 播放模式类型定义

成员:
	WSD_AL_PLAY_FILE_E  : 本地文件播放

	WSD_AL_PLAY_STREAM_E: 流化接口播放

	WSD_AL_PLAY_NET_E   : 网络播放

    WSD_AL_PLAY_BUF_E   : 填充数据播放

注意:
    WSD_AL_PLAY_NET_E方式下，只支持http、hls模式，其他的不支持
******************************************************************/
typedef enum _wsd_al_play_mode_e_
{
    WSD_AL_PLAY_FILE_E   = 1,
	WSD_AL_PLAY_STREAM_E = 2,
	WSD_AL_PLAY_NET_E    = 3,
	WSD_AL_PLAY_BUF_E    = 4,
	WSD_AL_PLAY_HDMIIN_E = 5
}WSD_AL_PLAY_MODE_E;


/******************************************************************
描述: 播放器状态类型定义

成员:
	WSD_AL_PLAYER_PLAYING_E : 正在播放

	WSD_AL_PLAYER_STOPED_E  : 播放停止

    WSD_AL_PLAYER_PAUSED_E  : 播放暂停

    WSD_AL_PLAYER_TRICK_E  : 快退快进

注意:
******************************************************************/
typedef enum _wsd_al_player_sate_e_
{
    WSD_AL_PLAYER_STOPED_E    = 0,
	WSD_AL_PLAYER_PLAYING_E = 1,
	WSD_AL_PLAYER_PAUSED_E  = 2,
	WSD_AL_PLAYER_TRICK_E   = 3,
}WSD_AL_PLAYER_STATE_E;


/******************************************************************
描述: 播放器事件类型定义

成员:
	STREAM_PLAYBACK_COMPLETE      : 播放结束

	STREAM_FAST_FORWORD_COMPLETE  : 快进到尾

	STREAM_FAST_BACKWORD_COMPLETE : 快退到头

    STREAM_ERROR       : 播放错误

    STREAM_PARSE_ERROR : 文件解析错误

    STREAM_SHOW_PIC	   : 播放开始并显示第一贞视频图像

注意:
******************************************************************/
typedef enum stream_event_type
{
    STREAM_PLAYBACK_COMPLETE         = 2,
    STREAM_FAST_FORWORD_COMPLETE     = 20,   //xKF50974 add for fastforword
    STREAM_FAST_BACKWORD_COMPLETE    = 21,   //xKF50974 add for fast backword
    STREAM_ERROR                     = 100,
	STREAM_PARSE_ERROR				 = 101,
    STREAM_SHOW_PIC                  = 200,
    STREAM_FIRST_AUD 				 = 201
}STREAM_EVENT_T;


/***********************************************************************
*                                全局宏定义
***********************************************************************/
/** 播放器类型宏定义，兼容老的代码 **/
#define PLAYER_MAIN WSD_AL_PLAYER_MAIN_E
#define PLAYER_PIP  WSD_AL_PLAYER_PIP_E
#define PLAYER_PCM  WSD_AL_PLAYER_PCM_E
#define PLAYER_BACK  WSD_AL_PLAYER_BACK_E
#define PLAYER_MAX  WSD_AL_PLAYER_MAX_E

/** 播放模式宏定义，兼容老的代码 **/
#define FILE_STREAM WSD_AL_PLAY_FILE_E
#define BUF_STREAM  WSD_AL_PLAY_STREAM_E
#define NET_STREAM  WSD_AL_PLAY_NET_E
#define LIVE_STREAM WSD_AL_PLAY_BUF_E
#define HDMIIN_STREAM WSD_AL_PLAY_HDMIIN_E


/** 播放状态宏定义，兼容老的代码 **/
#define STATE_STOP   WSD_AL_PLAYER_STOPED_E
#define STATE_PLAY   WSD_AL_PLAYER_PLAYING_E
#define STATE_PAUSE  WSD_AL_PLAYER_PAUSED_E
#define STATE_FAST   WSD_AL_PLAYER_TRICK_E


/***********************************************************************
*                                全局数据结构定义
***********************************************************************/
/******************************************************************
描	述: 播放时间回调函数定义

参	数:
	Event(in): 播放事件

返回值:
	D_SUCCESS: 成功
	D_FAILURE: 失败

注	意:
******************************************************************/
typedef int (*STREAM_CALLBACK)(STREAM_EVENT_T Event);


/******************************************************************
描	述: 流化读函数定义

参	数:
	fd(in): 流化控制句柄
    buf(out): 存储读取到的数据
    length(out): 读出长度

返回值: 返回实际读取到的数目

注	意:
******************************************************************/
typedef ssize_t (*STREAM_READ)(void *fd, void *buf,  size_t length);


/******************************************************************
描	述: 流化位置跳转函数定义

参	数:
	fd(in): 流化控制句柄
    offset(in): 跳转偏移量
    whence(in): 跳转的起点，

返回值: 返回实际跳转到的位置

注	意:
    whence = SEEK_SET(0) 表示Seek from beginning of file.
    whence = SEEK_CUR(1) 表示Seek from current position.
    whence = SEEK_END(2) 表示Set file pointer to EOF plus "offset"
******************************************************************/
typedef off_t (*STREAM_SEEK)(void *fd, off_t offset, int whence);


/******************************************************************
描	述: 流化文件长度获取函数定义

参	数:
	fd(in): 流化控制句柄
    first(out): 文件起点，一般为0
    last(out): 文件长度

返回值: 返回0成功，其他失败

注	意:
    whence = SEEK_SET(0) 表示Seek from beginning of file.
    whence = SEEK_CUR(1) 表示Seek from current position.
    whence = SEEK_END(2) 表示Set file pointer to EOF plus "offset"
******************************************************************/
typedef int (*STREAM_BOUNDS)(void *fd, off_t *first, off_t *last);


/******************************************************************
描述: 流化读写函数定义

成员:
	fd : 流化文件句柄，作为pReadFunc、pSeekFunc、pBoundsFunc的第一个参数传递给相关函数使用

	pReadFunc  : 读函数指针

	pSeekFunc  : 跳转函数指针

    pBoundsFunc: 文件长度信息获取函数指针

注意:
******************************************************************/
typedef struct _stream_io_func_t_
{
    D_VOID *fd;

	STREAM_READ    pReadFunc;
	STREAM_SEEK    pSeekFunc;
	STREAM_BOUNDS  pBoundsFunc;
}STREAM_IO_FUNC_T;


/******************************************************************
描述: 播放源信息定义

成员:
	PlayMode : 播放的数据元类型，支持WSD_AL_PLAY_MODE_E定义的模式，具体的见WSD_AL_PLAY_MODE_E的说明

	MediaParam: 播放的媒体信息，一般由WSD_AL_PLAYER_Probexx函数获取到

	SourceInfo: 播放文件相关的信息，是一个共用体。
	            SourceInfo.File.FilePath  : 表示本地文件的路径，在PlayMode = WSD_AL_PLAY_FILE_E 时需要设置,
	            SourceInfo.Stream.DataFunc: 表示流化播放的数据读写函数，在 PlayMode = WSD_AL_PLAY_STREAM_E 时需要设置,
	            SourceInfo.Stream.DataFunc: 表示流化播放的索引数据读写函数，在 PlayMode = WSD_AL_PLAY_STREAM_E 时需要设置,
	            SourceInfo.Net.NetUrl     : 表示网络播放的url信息，在 PlayMode = WSD_AL_PLAY_NET_E 时需要设置,

注意:
    MediaParam在网络播放下，不需要配置，其他的均需要配置
    MediaParam由WSD_AL_PLAYER_Probex媒体信息解析函数获取到
    PlayMode = WSD_AL_PLAY_FILE_E 时需要设置SourceInfo.File.FilePath
    PlayMode = WSD_AL_PLAY_STREAM_E 时需要设置SourceInfo.Stream.DataFunc、SourceInfo.Stream.DataFunc
	PlayMode = WSD_AL_PLAY_NET_E 时需要设置SourceInfo.Net.NetUrl
******************************************************************/
typedef struct _wsd_al_play_source_t_
{
	WSD_AL_PLAY_MODE_E PlayMode;
    MEDIA_PARAM_T      MediaParam;

    union
	{
        struct
		{
			D_UINT8 FilePath[URL_LEN];
        }File;

        struct
		{
			STREAM_IO_FUNC_T  DataFunc;
			STREAM_IO_FUNC_T  IndexFunc;
        }Stream;

    	struct
    	{
			D_UINT8 NetUrl[URL_LEN];
    	}Net;
	}SourceInfo;
}WSD_AL_PLAY_SOURCE_T;


/******************************************************************
描述: 播放属性定义

成员:
	Cycle: 自动循环播放，默认值是D_FALSE
	       D_TRUE : 表示播放结束以后，自动从头循环播放
	       D_FALSE: 表示播放结束以后，停止播放，等待应用控制

	Sync: 音视频同步标识，默认值是D_TRUE
	       D_TRUE : 表示同步方式播放
	       D_FALSE: 表示异步方式播放

	MuitleChannel: 多音轨模式标记，默认值是D_FALSE
	       D_TRUE : 表示多音轨模式
	       D_FALSE: 表示卡拉OK双声道模式

    PassThrough: 透传标记，音频外部解码，默认值是D_FALSE
	       D_TRUE : 表示主芯片不解，透传给外设解码
	       D_FALSE: 主芯片解码后输出

注意:
    1、 PassThrough只有在【MuitleChannel = D_TRUE】时起作用
    2、【 MuitleChannel = D_TRUE 】时Sync自动到D_FALSE模式，
******************************************************************/
typedef struct _wsd_al_play_param_t_
{
	D_BOOL Cycle;
	D_BOOL Sync;
	D_BOOL MuitleChannel;
	D_BOOL PassThrough;
}WSD_AL_PLAY_PARAM_T;

typedef struct _wsd_al_win_info_t_
{
    int x;
    int y;
    unsigned int width;
    unsigned int height;
} WSD_AL_WIN_INFO_T;

/******************************************************************
描述: 播放状态信息定义

成员:
	PlayMode : 播放的类型，具体含义见WSD_AL_PLAY_MODE_E定义

	PlayState: 播放的状态，具体含义见WSD_AL_PLAYER_STATE_E定义

	PlaySpeed: 播放的速率，(-32, -16, -8, -4, -2, 1, 2, 4, 8, 16, 32)

注意:
    Mode值兼容老版本的FILE_STREAM、BUF_STREAM、NET_STREAM、LIVE_STREAM
    State值兼容老版本的STATE_STOP、STATE_PLAY、STATE_PAUSE、STATE_FAST
******************************************************************/
typedef struct _wsd_al_player_status_t_
{
    WSD_AL_PLAY_MODE_E    PlayMode;
    WSD_AL_PLAYER_STATE_E PlayState;

	D_INT32 PlaySpeed;
}WSD_AL_PLAYER_STATUS_T;


/***********************************************************************
*                                导出函数
***********************************************************************/
/******************************************************************
函数原型: WSD_AL_PLAYER_Init

功能描述: 播放器初始化函数

参	  数: 无

返 回 值:
	D_SUCCESS: 成功
	D_FAILURE: 失败

注	  意:
    在进行播放之前，必须首先调用该函数，完成播放及资源的初始化动作。
******************************************************************/
D_INT32 WSD_AL_PLAYER_Init();


/******************************************************************
函数原型: WSD_AL_PLAYER_UnInit

功能描述: 播放器销毁函数

参	  数: 无

返 回 值:
	D_SUCCESS: 成功
	D_FAILURE: 失败

注	  意:
    此函数会关闭播放设备，并释放相关资源。
******************************************************************/
D_INT32 WSD_AL_PLAYER_UnInit ();


/******************************************************************
函数原型: WSD_AL_PLAYER_SetCallback

功能描述: 注册播放事件通知函数

参	  数:
    index(in)    : 播放器类型,具体值见WSD_AL_PLAYER_TYPE_E定义
    pCallback(in): 事件通知函数

返 回 值:
	D_SUCCESS: 成功
	D_FAILURE: 失败

注	  意:
    此函数在WSD_AL_PLAYER_Play函数调用之前使用
******************************************************************/
D_INT32 WSD_AL_PLAYER_SetCallback(D_INT32 index, STREAM_CALLBACK pCallback);


/******************************************************************
函数原型: WSD_AL_PLAYER_ProbeFile

功能描述: 本地文件媒体信息解析函数

参	  数:
	pFile(in)       : 文件路径
	pMediaParam(out): 返回媒体信息

返 回 值:
	D_SUCCESS: 成功
	D_FAILURE: 失败

注	  意:
    解析出来的媒体信息，供应用及WSD_AL_PLAYER_SetSource函数使用
******************************************************************/
D_INT32 WSD_AL_PLAYER_ProbeFile(D_UINT8 *pFile, MEDIA_PARAM_T *pMediaParam);


/******************************************************************
函数原型: WSD_AL_PLAYER_ProbeStream

功能描述: 从流化接口中解析媒体信息

参	  数:
	pIoFunc(in)     : 流化读写函数
	pMediaParam(out): 返回媒体信息

返 回 值:
	D_SUCCESS: 成功
	D_FAILURE: 失败

注	  意:
    解析出来的媒体信息，供应用及WSD_AL_PLAYER_SetSource函数使用
******************************************************************/
D_INT32 WSD_AL_PLAYER_ProbeStream(STREAM_IO_FUNC_T *pIoFunc, MEDIA_PARAM_T *pMediaParam);


/******************************************************************
函数原型: WSD_AL_PLAYER_ProbeBuf

功能描述: 从内存数据中解析媒体信息

参	  数:
	pBuf(in): 数据指针
	Len(in) : 数据长度
	pMediaParam(out): 返回媒体信息

返 回 值:
	D_SUCCESS: 成功
	D_FAILURE: 失败

注	  意:
    解析出来的媒体信息，供应用及WSD_AL_PLAYER_SetSource函数使用
******************************************************************/
D_INT32 WSD_AL_PLAYER_ProbeBuffer(D_UINT8 *pBuf, D_INT32 Len, MEDIA_PARAM_T *pMediaParam);


/******************************************************************
函数原型: WSD_AL_PLAYER_SetSource

功能描述: 播放信息设置函数

参	  数:
    index(in)  : 播放器类型,具体值见WSD_AL_PLAYER_TYPE_E定义
	pSource(in): 需要播放的媒体相关信息，具体定义见WSD_AL_PLAY_SOURCE_T结构

返 回 值:
	D_SUCCESS: 成功
	D_FAILURE: 失败

注	  意:
    WSD_AL_PLAY_SOURCE_T中的MediaParam由WSD_AL_PLAYER_Probexx相关函数获取到
    该函数是启动播放的第一个函数，只有调用了WSD_AL_PLAYER_SetSource其他函数才能够起作用。
    调用该函数以后，播放属性自动恢复到默认值:
      a、使用非循环方式 【 Cycle = D_FALSE 】
      b、同步播放模式 【 Sync = D_TRUE 】
	  c、2声道卡拉OK音轨模式进行播放 【 MuitleChannel = D_FALSE 】
      d、非透传模式 【 PassThrough = D_FALSE 】
******************************************************************/
D_INT32 WSD_AL_PLAYER_SetSource(D_INT32 index, WSD_AL_PLAY_SOURCE_T *pSource);


/******************************************************************
函数原型: WSD_AL_PLAYER_GetParam

功能描述: 获取播放属性设置函数

参	  数:
    index(in) : 播放器类型,具体值见WSD_AL_PLAYER_TYPE_E定义
	pParam(out): 返回播放属性相关信息，具体定义见WSD_AL_PLAY_PARAM_T结构

返 回 值:
	D_SUCCESS: 成功
	D_FAILURE: 失败

注	  意:
******************************************************************/
D_INT32 WSD_AL_PLAYER_GetParam(D_INT32 index, WSD_AL_PLAY_PARAM_T *pParam);


/******************************************************************
函数原型: WSD_AL_PLAYER_SetParam

功能描述: 播放属性设置函数

参	  数:
    index(in) : 播放器类型,具体值见WSD_AL_PLAYER_TYPE_E定义
	pParam(in): 播放属性相关信息，具体定义见WSD_AL_PLAY_PARAM_T结构

返 回 值:
	D_SUCCESS: 成功
	D_FAILURE: 失败

注	  意:
    此函数在WSD_AL_PLAYER_SetSource函数调用以后，WSD_AL_PLAYER_Play函数调用之前使用
    设置时，所有属性必须全部设置正确，不支持单个属性配置, 默认播放属性为:
      a、使用非循环方式 【 Cycle = D_FALSE 】
      b、同步播放模式 【 Sync = D_TRUE 】
	  c、2声道卡拉OK音轨模式进行播放 【 MuitleChannel = D_FALSE 】
      d、非透传模式 【 PassThrough = D_FALSE 】
     一般使用WSD_AL_PLAYER_GetParam获取属性，修改相应选项后，再调用此函数设置
******************************************************************/
D_INT32 WSD_AL_PLAYER_SetParam(D_INT32 index, WSD_AL_PLAY_PARAM_T *pParam);


/******************************************************************
函数原型: WSD_AL_PLAYER_Play

功能描述: 启动播放

参	  数:
    index(in): 播放器类型,具体值见WSD_AL_PLAYER_TYPE_E定义

返 回 值:
	D_SUCCESS: 成功
	D_FAILURE: 失败

注	  意:
    该函数内会申请相关资源，只有调用WSD_AL_PLAYER_Stop后才会被释放
******************************************************************/
D_INT32 WSD_AL_PLAYER_Play(D_INT32 index);


/******************************************************************
函数原型: WSD_AL_PLAYER_Stop

功能描述: 停止播放

参	  数:
    index(in): 播放器类型,具体值见WSD_AL_PLAYER_TYPE_E定义

返 回 值:
	D_SUCCESS: 成功
	D_FAILURE: 失败

注	  意:
    该函数内会释放WSD_AL_PLAYER_Play函数内申请的相关资源
******************************************************************/
D_INT32 WSD_AL_PLAYER_Stop(D_INT32 index);


/******************************************************************
函数原型: WSD_AL_PLAYER_Pause

功能描述: 暂停播放

参	  数:
    index(in): 播放器类型,具体值见WSD_AL_PLAYER_TYPE_E定义

返 回 值:
	D_SUCCESS: 成功
	D_FAILURE: 失败

注	  意:
    调用该函数暂停以后，通过调用WSD_AL_PLAYER_Resume函数回复
******************************************************************/
D_INT32 WSD_AL_PLAYER_Pause(D_INT32 index);


/******************************************************************
函数原型: WSD_AL_PLAYER_Resume

功能描述: 暂停后恢复播放

参	  数:
    index(in): 播放器类型,具体值见WSD_AL_PLAYER_TYPE_E定义

返 回 值:
	D_SUCCESS: 成功
	D_FAILURE: 失败

注	  意:
    调用该函数暂停以后，通过调用WSD_AL_PLAYER_Resume函数回复
******************************************************************/
D_INT32 WSD_AL_PLAYER_Resume(D_INT32 index);


/******************************************************************
函数原型: WSD_AL_PLAYER_Trick

功能描述: 按指定倍速播放

参	  数:
    index(in): 播放器类型,具体值见WSD_AL_PLAYER_TYPE_E定义
    Speed(in): 指定播放速率，支持的值为(-32, -16, -8, -4, -2, 1, 2, 4, 8, 16, 32)

返 回 值:
	D_SUCCESS: 成功
	D_FAILURE: 失败

注	  意:
******************************************************************/
D_INT32 WSD_AL_PLAYER_Trick(D_INT32 index, D_INT32 Speed);


/******************************************************************
函数原型: WSD_AL_PLAYER_Forward

功能描述: 快进播放

参	  数:
	index(in): 播放器类型,具体值见WSD_AL_PLAYER_TYPE_E定义

返 回 值:
	D_SUCCESS: 成功
	D_FAILURE: 失败

注	  意:
	目前支持五级快进(2,4,8,16,32)，每调用一次此函数，快进增加一级，
	当在第五级(32倍速)时，再次调用此函数，自动转为正常播放。
    次功能在Buffer播放模式下不支持，其他模式均支持
******************************************************************/
D_INT32 WSD_AL_PLAYER_Forward(D_INT32 index);


/******************************************************************
函数原型: WSD_AL_PLAYER_Backward

功能描述: 快退播放

参	  数:
	index(in): 播放器类型,具体值见WSD_AL_PLAYER_TYPE_E定义

返 回 值:
	D_SUCCESS: 成功
	D_FAILURE: 失败

注	  意:
	目前支持五级级快退(-2,-4,-8,-16,-32)，每调用一次此函数，快退增加一级，
	当在第五级(-32倍速)时，再次调用此函数，自动转为正常播放。
	次功能在Buffer播放模式下不支持，其他模式均支持
******************************************************************/
D_INT32 WSD_AL_PLAYER_Backward(D_INT32 index);


/******************************************************************
函数原型: WSD_AL_PLAYER_GetStatus

功能描述: 获得当前播放状态

参	  数:
	index(in): 播放器类型,具体值见WSD_AL_PLAYER_TYPE_E定义
    pStatus(out): 返回播放状态信息

返 回 值:
    D_SUCCESS: 成功
    D_FAILURE: 失败

注	  意:
******************************************************************/
D_INT32 WSD_AL_PLAYER_GetStatus(D_INT32 index, WSD_AL_PLAYER_STATUS_T *pStatus);


/******************************************************************
函数原型: WSD_AL_PLAYER_GetDuration

功能描述: 片源播放总时长获取函数

参	  数:
	index(in) : 播放器类型,具体值见WSD_AL_PLAYER_TYPE_E定义
	pMsec(out): 返回片源播放总时长

返 回 值:
    D_SUCCESS: 成功
    D_FAILURE: 失败

注	  意:
******************************************************************/
D_INT32 WSD_AL_PLAYER_GetDuration(D_INT32 index, D_INT32 *pMsec);


/******************************************************************
函数原型: WSD_AL_PLAYER_GetCurPosition

功能描述: 获取当前播放时间

参	  数:
	index(in) : 播放器类型,具体值见WSD_AL_PLAYER_TYPE_E定义
	pMsec(out): 返回当前播放时间

返 回 值:
    D_SUCCESS: 成功
    D_FAILURE: 失败

注	  意:
******************************************************************/
D_INT32 WSD_AL_PLAYER_GetCurPosition(D_INT32 index, D_INT32 *pMsec);


/******************************************************************
函数原型: WSD_AL_PLAYER_SeekTo

功能描述: 播放跳转函数，跳转到指定时间开始播放

参	  数:
	index(in): 播放器类型,具体值见WSD_AL_PLAYER_TYPE_E定义
	Msec(in) : 跳转时间

返 回 值:
    D_SUCCESS: 成功
    D_FAILURE: 失败

注	  意:
    次功能在Buffer播放模式下不支持，其他模式均支持
******************************************************************/
D_INT32 WSD_AL_PLAYER_SeekTo(D_INT32 index, D_INT32 msec);


/******************************************************************
函数原型: WSD_AL_PLAYER_WriteBuffer

功能描述: 播放数据推送函数，

参	  数:
	index(in): 播放器类型,具体值见WSD_AL_PLAYER_TYPE_E定义
	pBuf(in) : 需要推送的数据指针
    len(in)  : 需要推送的数据长度

返 回 值:
    D_SUCCESS: 成功
    D_FAILURE: 失败

注	  意:
    次功能仅在Buffer播放模式下支持，其他模式均不支持
******************************************************************/
D_INT32 WSD_AL_PLAYER_WriteBuffer(D_INT32 index, D_UINT8 *pBuf, D_INT32 len);


/******************************************************************
函数原型: WSD_AL_PLAYER_FlushBuffer

功能描述: 播放等待函数，等待数据播放结束

参	  数:
	index(in): 播放器类型,具体值见WSD_AL_PLAYER_TYPE_E定义

返 回 值:
	D_SUCCESS: 成功
	D_FAILURE: 失败

注	  意:
	在一个文件播放完毕后，应使用此函数等待缓冲区中的数据播放完毕，然后调用STOP命令。
******************************************************************/
D_INT32 WSD_AL_PLAYER_FlushBuffer(D_INT32 index);


/******************************************************************
函数原型: WSD_AL_PLAYER_ShowPlayWindow

功能描述: 播放窗口显示控制

参	  数:
	index(in): 播放器类型,具体值见WSD_AL_PLAYER_TYPE_E定义
	show(in) : 窗口显示状态，D_FALSE表示隐藏窗口,D_TRUE表示显示窗口

返 回 值:
	D_SUCCESS: 成功
	D_FAILURE: 失败

注	  意:
******************************************************************/
D_INT32 WSD_AL_PLAYER_ShowPlayWindow(D_INT32 index, D_BOOL show);


/******************************************************************
函数原型: WSD_AL_PLAYER_ShowPlayWindow

功能描述: 设置播放窗口位置

参	  数:
	index(in): 播放器类型,具体值见WSD_AL_PLAYER_TYPE_E定义
	x(in): 起点横坐标
    y(in): 起点纵坐标
    w(in): 宽度
    h(in): 高度

返 回 值:
	D_SUCCESS: 成功
	D_FAILURE: 失败

注	  意:
******************************************************************/
D_INT32 WSD_AL_PLAYER_SetPlayWindow(D_INT32 index, D_INT32 x, D_INT32 y, D_INT32 w, D_INT32 h);


/******************************************************************
函数原型: WSD_AL_PLAYER_GetPlayWindow

功能描述: 获取播放窗口位置信息

参	  数:
	index(in): 播放器类型,具体值见WSD_AL_PLAYER_TYPE_E定义
	x(out): 返回起点横坐标
    y(out): 返回起点纵坐标
    w(out): 返回宽度
    h(out): 返回高度

返 回 值:
	D_SUCCESS: 成功
	D_FAILURE: 失败

注	  意:
******************************************************************/
D_INT32 WSD_AL_PLAYER_GetPlayWindow(D_INT32 index, D_INT32 *x, D_INT32 *y, D_INT32 *w, D_INT32 *h);

/******************************************************************
功能描述：获取当前播放窗口信息；
入口参数：*x - 起点横坐标；
     	                     *y - 起点纵坐标；
     	                     *w - 宽度；
      	                     *h - 高度；
      	                     *visible,
      	                     *zorder
返回参数：无；
说    明：与WSD_AL_PLAYER_GetPlayWindow功能相同，只是多了visible 和zorder
******************************************************************/
int WSD_AL_PLAYER_GetPlayWindowInfo(int index, int *x, int *y, int *w, int *h, int *visible, int *zorder);

/******************************************************************
功能描述：设置播放窗口；
入口参数：x - 起点横坐标；
                       	  y - 起点纵坐标；
                     	  w - 宽度；
                 	  h - 高度；
返回参数：成功，返回0；失败，返回错误码(<0)；
说    明：此函数用于设置播放窗口大小，默认值为：
          x=0 ；y = 0 ；w = 720 ；h = 576。
          与WSD_AL_PLAYER_SetPlayWindow功能相同，只是多了visible 和zorder
******************************************************************/
int WSD_AL_PLAYER_SetPlayWindowInfo(int index, int x, int y, int w, int h, int visible, int zorder);


/******************************************************************
函数原型: WSD_AL_PLAYER_SwitchTvWindow

功能描述:  切换主播放器与预览播放器到电视窗口

参	  数:
	index(in): 播放器类型,具体值见WSD_AL_PLAYER_TYPE_E定义
返 回 值:
	D_SUCCESS: 成功
	D_FAILURE: 失败

注	  意:
******************************************************************/
D_INT32 WSD_AL_PLAYER_SwitchTvWindow(D_INT32 index);

/******************************************************************
功能描述：判断缓冲区的数据是否播放完毕；
入口参数：无；
返回参数：无；
说    明：
******************************************************************/
int WSD_AL_PLAYER_GetVideoPlayEndStatus(int index);

int WSD_AL_PLAYER_SetAudioParams(int index, int nSample_rate,int nBits_per_sample, int nChannels);

/******************************************************************
函数原型: WSD_AL_PLAYER_GetAllAudioChannel

功能描述: 获取总音轨数

参	  数:
	index(in): 播放器类型,具体值见WSD_AL_PLAYER_TYPE_E定义
	value(out): 返回总音轨数

返 回 值:
	D_SUCCESS: 成功
	D_FAILURE: 失败

注	  意:
******************************************************************/
D_INT32 WSD_AL_PLAYER_GetAllAudioChannel(D_INT32 index, D_INT32 *value);


/******************************************************************
函数原型: WSD_AL_PLAYER_GetCurAudioChannel

功能描述: 获取当前播放的音轨索引

参	  数:
	index(in): 播放器类型,具体值见WSD_AL_PLAYER_TYPE_E定义
	value(out): 返回当前播放的音轨索引

返 回 值:
	D_SUCCESS: 成功
	D_FAILURE: 失败

注	  意:
******************************************************************/
D_INT32 WSD_AL_PLAYER_GetCurAudioChannel(D_INT32 index, D_INT32 *value);


/******************************************************************
函数原型: WSD_AL_PLAYER_SetCurAudioChannel

功能描述: 播放指定索引对应的音轨

参	  数:
	index(in): 播放器类型,具体值见WSD_AL_PLAYER_TYPE_E定义
	value(in): 需要播放的音轨索引

返 回 值:
	D_SUCCESS: 成功
	D_FAILURE: 失败

注	  意:
******************************************************************/
D_INT32 WSD_AL_PLAYER_SetCurAudioChannel(D_INT32 index, D_INT32 value);


/******************************************************************
函数原型: WSD_AL_PLAYER_SetBrightness

功能描述: 播放器亮度设置

参	  数:
	index(in): 播放器类型,具体值见WSD_AL_PLAYER_TYPE_E定义
	value(in): 亮度值，使用范围【0,255】

返 回 值:
	D_SUCCESS: 成功
	D_FAILURE: 失败

注	  意:
******************************************************************/
D_INT32 WSD_AL_PLAYER_SetBrightness(D_INT32 index, D_UINT8 value);


/******************************************************************
函数原型: WSD_AL_PLAYER_SetContrast

功能描述: 播放器对比度设置

参	  数:
	index(in): 播放器类型,具体值见WSD_AL_PLAYER_TYPE_E定义
	value(in): 对比度值，使用范围【0,255】

返 回 值:
	D_SUCCESS: 成功
	D_FAILURE: 失败

注	  意:
******************************************************************/
D_INT32 WSD_AL_PLAYER_SetContrast(D_INT32 index, D_UINT8 value);


/******************************************************************
函数原型: WSD_AL_PLAYER_SetSaturation

功能描述: 播放器饱和度设置

参	  数:
	index(in): 播放器类型,具体值见WSD_AL_PLAYER_TYPE_E定义
	value(in): 饱和度值，使用范围【0,255】

返 回 值:
	D_SUCCESS: 成功
	D_FAILURE: 失败

注	  意:
******************************************************************/
D_INT32 WSD_AL_PLAYER_SetSaturation(D_INT32 index, D_UINT8 value);


/******************************************************************
函数原型: WSD_AL_PLAYER_GetPicture

功能描述: 获取当前播放的画面，并存储在pSurface中

参	  数:
	index(in): 播放器类型,具体值见WSD_AL_PLAYER_TYPE_E定义
	pSurface(in): 内存信息，用于存储图片，该数据由WSD_AL_GFX_CreatePixmap函数创建

返 回 值:
	D_SUCCESS: 成功
	D_FAILURE: 失败

注	  意:
******************************************************************/
D_INT32 WSD_AL_PLAYER_GetPicture(D_INT32 index, D_VOID *pSurface);


/******************************************************************
函数原型: WSD_AL_PLAYER_GetVideoTime

功能描述: 获取当前视频的PTS值，用于显示subtitle

参	  数:
	index(in) : 播放器类型,具体值见WSD_AL_PLAYER_TYPE_E定义
	pTime(out): 返回当前视频的PTS值

返 回 值:
	D_SUCCESS: 成功
	D_FAILURE: 失败

注	  意:
******************************************************************/
D_INT32 WSD_AL_PLAYER_GetVideoTime(D_INT32 index, D_INT32 *pTime);

/******************************************************************
  函数原型: WSD_AL_PLAYER_GetFirstVideoPts

  功能描述:获得视频解码的第一帧

  参数:  decode_id: 第几路视频0:第一路视频 1:第二路视频

                passed: 返回 第一帧

  返回值: 0：失败  1：成功

 ******************************************************************/
unsigned int WSD_AL_PLAYER_GetFirstVideoPts(int index, int *passed);

int WSD_AL_PLAYER_VideoReadComplete(int index, int len);

/******************************************************************
功能描述：从SDK中得到视频数据的缓存地址；
入口参数：len： buffer的长度;
返回参数：视频数据的缓存地址；
说 明：无。
******************************************************************/
int WSD_AL_PLAYER_GetBufferSize(int index, char **pBuf, int len);


#ifdef __cplusplus
}
#endif

#endif
