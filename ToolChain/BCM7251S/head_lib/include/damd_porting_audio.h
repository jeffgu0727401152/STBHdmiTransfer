/*************************************************************************
                             All Rights Reserved
                                 R&D Dept.
*************************************************************************/


/*************************************************************************

Filename:       damd_porting_audio.h

Description:    声音相关接口

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
#ifndef _WSD_AL_AUDIO_H_
#define _WSD_AL_AUDIO_H_

#ifdef __cplusplus
extern "C" {
#endif

/***********************************************************************
*                                包含头文件
************************************************************************/


/***********************************************************************
*                                常量定义
***********************************************************************/
/******************************************************************
描述: 声道定义

成员:
	WSD_AL_AUDIO_TRACK_LEFT_E: 左声道，left-> left, left->right

	WSD_AL_AUDIO_TRACK_RIGHT_E: 右声道，right-> left, right->right

	WSD_AL_AUDIO_TRACK_STEREO_E: 混合声 , left-> left, right->right
	
注意: 
******************************************************************/
typedef enum _wsd_al_audio_track_e_
{     
	WSD_AL_AUDIO_TRACK_LEFT_E = 0,
	WSD_AL_AUDIO_TRACK_RIGHT_E,
	WSD_AL_AUDIO_TRACK_STEREO_E,
	WSD_AL_AUDIO_TRACK_MAX_E,
}WSD_AL_AUDIO_TRACK_E;

/******************************************************************
描述: EQ 设置类型

成员:
	WSD_AL_AUDIO_EQ_TYPE_MUSIC_E: 设置music EQ

	WSD_AL_AUDIO_EQ_TYPE_MIC_E: 设置mic EQ

注意: 
******************************************************************/
typedef enum _wsd_al_audio_eq_type_e_
{
	WSD_AL_AUDIO_EQ_TYPE_MUSIC_E,
	WSD_AL_AUDIO_EQ_TYPE_MIC_E,
	WSD_AL_AUDIO_EQ_TYPE_MAX_E
}WSD_AL_AUDIO_EQ_TYPE_E;

/******************************************************************
描述: mic 混响回音等级设置

成员:
	WSD_AL_AUDIO_MIC_KARAOKE_ECHO_E:典型回音效果
	
	WSD_AL_AUDIO_MIC_KARAOKE_SUPER_ECHO_E:立体回音效果
	
	WSD_AL_AUDIO_MIC_KARAOKE_ON_STAGE_E:舞台立体回音效果
	
	WSD_AL_AUDIO_MIC_KARAOKE_PRO_E:音乐厅立体声回音效果
	
	WSD_AL_AUDIO_MIC_KARAOKE_SUPER_PRO_E:音乐厅增强立体声回音效果
注意: 
******************************************************************/
typedef enum _wsd_al_audio_mic_echo_e_
{
	WSD_AL_AUDIO_MIC_KARAOKE_ECHO_E,
	WSD_AL_AUDIO_MIC_KARAOKE_SUPER_ECHO_E,
	WSD_AL_AUDIO_MIC_KARAOKE_ON_STAGE_E,
	WSD_AL_AUDIO_MIC_KARAOKE_PRO_E,
	WSD_AL_AUDIO_MIC_KARAOKE_SUPER_PRO_E,
	WSD_AL_AUDIO_MIC_KARAOKE_MAX_E
}WSD_AL_AUDIO_MIC_ECHO_E;


typedef struct _wsd_al_audio_mic_echo_param_e_
{
    int UserDataEnable;       /*用户自定义开关*/

    /*默认回声*/
	WSD_AL_AUDIO_MIC_ECHO_E PresetEcho;

	D_UINT8 *pbUserData;       /*用户自定义响度参数，UserDataEnable = D_TRUE时有效*/
}WSD_AL_AUDIO_MIC_ECHO_PARAM_E;

/******************************************************************
描述: 默认预设响度

成员:
	WSD_AL_AUDIO_LOUDNESS_DEQ0_LOW_E
	
	WSD_AL_AUDIO_LOUDNESS_DEQ0_HIGH_E
	
	WSD_AL_AUDIO_LOUDNESS_DEQ1_LOW_E
	
	WSD_AL_AUDIO_LOUDNESS_DEQ1_HIGH_E
	
注意: 
******************************************************************/
typedef enum _wsd_al_audio_preset_loudness_e_
{
	WSD_AL_AUDIO_LOUDNESS_DEQ0_LOW_E,
	WSD_AL_AUDIO_LOUDNESS_DEQ0_HIGH_E,
	WSD_AL_AUDIO_LOUDNESS_DEQ1_LOW_E,
	WSD_AL_AUDIO_LOUDNESS_DEQ1_HIGH_E,
	WSD_AL_AUDIO_LOUDNESS_MAX_E
}WSD_AL_AUDIO_PRESET_LOUDNESS_E;

/******************************************************************
描述: 原唱音量处理

成员:
	WSD_AL_AUDIO_VOICE_CANCEL_CLOSE_E: 关闭原唱音量处理
	
	WSD_AL_AUDIO_VOICE_CANCEL_OPEN_E:降低原唱音量
	
	WSD_AL_AUDIO_VOICE_CANCEL_AUTO_E:自动处理
		
注意: 
******************************************************************/
typedef enum _wsd_al_audio_voice_cancel_e_
{
	WSD_AL_AUDIO_VOICE_CANCEL_CLOSE_E,
	WSD_AL_AUDIO_VOICE_CANCEL_OPEN_E,
	WSD_AL_AUDIO_VOICE_CANCEL_AUTO_E,
	WSD_AL_AUDIO_VOICE_CANCEL_MAX_E
}WSD_AL_AUDIO_VOICE_CANCEL_E;

/***********************************************************************
*                                全局宏定义
***********************************************************************/
#define WSD_VOLUME_MIN (0)    /** music 最小音量 **/
#define WSD_VOLUME_MAX (400)  /** music 最大音量 **/
#define WSD_MIC_VOLUME_MIN (0)    /** mic 最小音量 **/
#define WSD_MIC_VOLUME_MAX (100)  /** mic 最大音量 **/

#define WSD_VOLUME_DB_MIN (-70) /** 最小db 音量 **/
#define WSD_VOLUME_DB_MAX (0)   /** 最大db 音量 **/

#define WSD_TONE_MIN  (-24)    /** 最小音调 **/
#define WSD_TONE_MAX  (24)     /** 最大音调 **/

#define WSD_PCM_VOLUME_MIN (0)   /** 混音最小音量 **/
#define WSD_PCM_VOLUME_MAX (32)  /** 混音最大音量 **/

#define WSD_LR_BALANCE_MIN (-33) /*左右声道均衡最小值*/
#define WSD_LR_BALANCE_MAX (33)  /*左右声道均衡最大值*/

/***********************************************************************
*                                全局数据结构定义
***********************************************************************/
typedef struct _wsd_al_audio_loudness_param_e_
{
	int LoudnessEnable; 	  /*响度开关*/
	int UserDataEnable; 	  /*用户自定义开关*/

	/*默认预设响度*/
	WSD_AL_AUDIO_PRESET_LOUDNESS_E PresetLoudness;

	D_UINT8 *pbUserData;	   /*用户自定义响度参数，UserDataEnable = D_TRUE时有效*/
}WSD_AL_AUDIO_LOUDNESS_PARAM_E;


/***********************************************************************
*                                导出函数
***********************************************************************/
/******************************************************************
函数原型: WSD_AL_AUDIO_SetTrack

功能描述: 声道设置函数

参    数:
    Track(in): 声道值，取值见 WSD_AL_AUDIO_TRACK_E 枚举

返 回 值:  
	D_SUCCESS: 成功
	D_FAILURE: 失败
	
注    意: 
******************************************************************/
D_INT32 WSD_AL_AUDIO_SetTrack(WSD_AL_AUDIO_TRACK_E Track);

/***********************************************************************************************
函数原型: WSD_AL_AUDIO_SetVolume

功能描述: 音量设置函数,支持音效子板音量设置

参    数:
	Volume(in): 音量值，取值范围[WSD_VOLUME_MIN, WSD_VOLUME_MAX],即【0,400】

返 回 值:  
	D_SUCCESS: 成功
	D_FAILURE: 失败
	
注    意: 
***********************************************************************************************/
D_INT32 WSD_AL_AUDIO_SetVolume(D_INT32 Volume);

/***********************************************************************************************
函数原型: WSD_AL_AUDIO_SetMicVolume

功能描述: mic 音量设置函数

参    数:
	Volume(in): 音量值，取值范围[WSD_MIC_VOLUME_MIN, WSD_MIC_VOLUME_MAX],即【0,100】

返 回 值:  
	D_SUCCESS: 成功
	D_FAILURE: 失败
	
注    意: 
***********************************************************************************************/
D_INT32 WSD_AL_AUDIO_SetMicVolume(D_INT32 Volume);

/******************************************************************
函数原型: WSD_AL_AUDIO_SetMute

功能描述: 静音设置函数

参    数:
	bMute(in): D_FALSE表示取消静音
	           D_TRUE表示打开静音

返 回 值:  
	D_SUCCESS: 成功
	D_FAILURE: 失败
	
注    意: 
******************************************************************/
D_INT32 WSD_AL_AUDIO_SetMute(int bMute);

/******************************************************************
函数原型: WSD_AL_AUDIO_SetHdmiMute

功能描述: HDMI静音设置函数

参    数:
	bMute(in): D_FALSE表示取消静音
	           D_TRUE表示打开静音

返 回 值:  
	D_SUCCESS: 成功
	D_FAILURE: 失败
	
注    意:
******************************************************************/
D_INT32 WSD_AL_AUDIO_SetHdmiMute(int bMute);

/******************************************************************
函数原型: WSD_AL_AUDIO_SetSpdifMute

功能描述: 光纤静音设置函数

参    数:
	bMute(in): D_FALSE表示取消静音
	           D_TRUE表示打开静音

返 回 值:  
	D_SUCCESS: 成功
	D_FAILURE: 失败
	
注    意: 
******************************************************************/
D_INT32 WSD_AL_AUDIO_SetSpdifMute(int bMute);

/******************************************************************
函数原型: WSD_AL_AUDIO_SetPcmVolume

功能描述: 混音音量设置函数

参    数:
	Volume(in): 音量值，取值范围[WSD_PCM_VOLUME_MIN, WSD_PCM_VOLUME_MAX],即【0,32】

返 回 值:  
	D_SUCCESS: 成功
	D_FAILURE: 失败
	
注    意: 
******************************************************************/
D_INT32 WSD_AL_AUDIO_SetPcmVolume(int Volume);

/**********************************************************************************
函数原型: WSD_AL_AUDIO_SetTone

功能描述: 音调设置函数

参    数:
	Value(in): 音调值，取值范围[WSD_TONE_MIN, WSD_TONE_MAX],即【-24,24】
	Enable(in):音调设置开关，Enable=D_TRUE打开，Enable=D_FALSE关闭

返 回 值:  
	D_SUCCESS: 成功
	D_FAILURE: 失败
	
注    意: 0为原调，0 ~ 24为升调，-24 ~ 0降调
		   范围-1200cent~+1200cent, 每步增加或减少50 cent.
***********************************************************************************/
D_INT32 WSD_AL_AUDIO_SetTone(D_INT32 Value, D_BOOL Enable);

/***********************************************************************************
函数原型: WSD_AL_AUDIO_SetEQ

功能描述: 音调设置函数

参    数:
	EqType(in): 设置EQ 对象，music还是mic，请参考WSD_AL_AUDIO_EQ_TYPE_E
	Enable(in):EQ 设置开关，Enable=D_TRUE打开，Enable=D_FALSE关闭
	pEqData(in):该指针指向一个保存有10段EQ值的数组
	                   该数组内的EQ 数据是通过工具调试好输入
	                   请向FAE 获取工具和使用方法
返 回 值:  
	D_SUCCESS: 成功
	D_FAILURE: 失败
	
注    意: 
************************************************************************************/
D_INT32 WSD_AL_AUDIO_SetEQ(WSD_AL_AUDIO_EQ_TYPE_E EqType, D_BOOL Enable, D_UINT8 *pEqData);

/***********************************************************************************
函数原型: WSD_AL_AUDIO_SetLrBalance

功能描述: 左右声道均衡设置函数

参    数:
	bBalID(in): 范围:[-33  --- 33] ,0为Center，-1 -- -33 to the left，1 -- 33 to the right

返 回 值:  
	D_SUCCESS: 成功
	D_FAILURE: 失败
	
注    意: 
************************************************************************************/
D_INT32 WSD_AL_AUDIO_SetLrBalance(D_INT8 bBalID);

/***********************************************************************************
函数原型: WSD_AL_AUDIO_SetMicEcho

功能描述: 设置mic 回音效果

参    数:
	pMicEcho(in): 回音效果参数，请参考WSD_AL_AUDIO_MIC_ECHO_PARAM_E

返 回 值:  
	D_SUCCESS: 成功
	D_FAILURE: 失败
	
注    意: 
************************************************************************************/
D_INT32 WSD_AL_AUDIO_SetMicEcho(WSD_AL_AUDIO_MIC_ECHO_PARAM_E *pMicEcho);

/***********************************************************************************
函数原型: WSD_AL_AUDIO_SetLoudness

功能描述: 设置响度

参    数:
	pLoudnessParam(in): 响度效果参数，请参考WSD_AL_AUDIO_LOUDNESS_PARAM_E

返 回 值:  
	D_SUCCESS: 成功
	D_FAILURE: 失败
	
注    意: 此接口支持两种模式:
                 1.预定义响度值，请参考WSD_AL_AUDIO_PRESET_LOUDNESS_E
                 2.用户自定义，与EQ 相同，请向FAE申请工具。                                           
************************************************************************************/
D_INT32 WSD_AL_AUDIO_SetLoudness(WSD_AL_AUDIO_LOUDNESS_PARAM_E *pLoudnessParam);

/***********************************************************************************
函数原型: WSD_AL_AUDIO_SetVoiceCancel

功能描述: 降低原唱音量

参    数:
	VoiceCancel(in): 原唱音量处理参数，请参考WSD_AL_AUDIO_VOICE_CANCEL_E

返 回 值:  
	D_SUCCESS: 成功
	D_FAILURE: 失败
	
注    意:                                          
************************************************************************************/
D_INT32 WSD_AL_AUDIO_SetVoiceCancel(WSD_AL_AUDIO_VOICE_CANCEL_E VoiceCancel);


#ifdef __cplusplus
}
#endif

#endif
