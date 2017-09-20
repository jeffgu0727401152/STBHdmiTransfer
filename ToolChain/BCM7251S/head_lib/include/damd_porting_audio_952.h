/*************************************************************************
                             All Rights Reserved
                                 R&D Dept.
*************************************************************************/


/*************************************************************************

Filename:       damd_porting_audio_952.h

Description:    

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
#ifndef _WSD_AL_AUDIO_952_H_
#define _WSD_AL_AUDIO_952_H_

#ifdef __cplusplus
extern "C" {
#endif

/***********************************************************************
*                                包含头文件
************************************************************************/


/***********************************************************************
*                                常量定义
***********************************************************************/
typedef enum
{	  
	WSD_952_WORK_KARAOKE = 0,
	WSD_952_WORK_AV,
	WSD_952_WORK_MAX
}WSD_952_WORK_MODE_E;


/** DTV And MUSIC is on AV Work Mode 
      KARAOKE is for KARAOKE Work Mode **/
typedef enum
{	  
	WSD_952_SURROUND_DTV_THROUGH = 0,
	WSD_952_SURROUND_DTV_THEATER,
	WSD_952_SURROUND_DTV_MOVIE,
	WSD_952_SURROUND_DTV_DRAMA,
	WSD_952_SURROUND_DTV_SPORTS,
	WSD_952_SURROUND_DTV_VARIETY_MUSIC,
	WSD_952_SURROUND_DTV_GAME,	
	WSD_952_SURROUND_MUSIC_THROUGH,
	WSD_952_SURROUND_MUSIC_LARGE_HALL_0,
	WSD_952_SURROUND_MUSIC_LARGE_HALL_1,
	WSD_952_SURROUND_MUSIC_SMALL_HALL,
	WSD_952_SURROUND_MUSIC_SHOE_BOX,
	WSD_952_SURROUND_MUSIC_OPERA_HOUSE,
	WSD_952_SURROUND_KARAOKE_THROUGH,
	WSD_952_SURROUND_KARAOKE_ECHO,
	WSD_952_SURROUND_KARAOKE_SUPER_ECHO,
	WSD_952_SURROUND_KARAOKE_ON_STAGE,
	WSD_952_SURROUND_KARAOKE_PRO,
	WSD_952_SURROUND_KARAOKE_SUPER_PRO,
	WSD_952_SURROUND_MAX
}WSD_952_SURROUND_MODE_E;


typedef enum 
{
	WSD_952_LEVEL_ZERO = 0x00E3,
	WSD_952_LEVEL_LOW,
	WSD_952_LEVEL_MIDLOW,
	WSD_952_LEVEL_MID,
	WSD_952_LEVEL_MIDHIGHT,
	WSD_952_LEVEL_HIGHT
}WSD_952_LEVEL_E;


/***********************************************************************
*                                全局宏定义
***********************************************************************/
#define WSD_FM_TOTAL_NUM (59)

#define WSD_KC_MIN_LEVEL (-24)
#define WSD_KC_MAX_LEVEL (24)

#define WSD_GEQ_MIN_LEVEL (-10)
#define WSD_GEQ_MAX_LEVEL (10)

#define WSD_MAX_VOLUME (250)


/***********************************************************************
*                                全局数据结构定义
***********************************************************************/
typedef struct _wsd_952_kc_param_e_
{
    int Enable;
	int Level;   /** [-24-24] **/
}WSD_952_KC_PARAM_E;


typedef struct _wsd_952_geq_param_e_
{
    int Enable;
	int BassLevel;   /** [-5-5]    **/
	int TrebleLevel; /** [-5-5]    **/
	int GEQ0Level;   /** [-10-10] **/
	int GEQ1Level;   /** [-10-10] **/
	int GEQ2Level;   /** [-10-10] **/
	int GEQ3Level;   /** [-10-10] **/	
	int GEQ4Level;   /** [-10-10] **/
}WSD_952_GEQ_PARAM_E;

typedef struct _wsd_952_level_param_e_
{
	WSD_952_LEVEL_E LDLevel;   /** 麦克风进入--- only for karaoke work mode**/
	WSD_952_LEVEL_E RELevel;   /** 麦克风echo 后的level**/
	WSD_952_LEVEL_E LPSLevel;  /** 音乐lenvel -- only for karaoke work mode **/ 
	WSD_952_LEVEL_E ERLevel;   /** 音乐ER 处理后 LEVEL**/
	WSD_952_LEVEL_E P3DLevel;  /** mic 混合后的level**/
}WSD_952_LEVEL_PARAM_E;


/***********************************************************************
*                                导出函数
***********************************************************************/
/******************************************************************
功能描述：
入口参数：
返回参数：
说    明：
例    子：
******************************************************************/
int WSD_AL_AUDIO_952_Init(void);


/******************************************************************
功能描述：
入口参数：
返回参数：
说    明：
例    子：
******************************************************************/
int WSD_AL_AUDIO_952_SetMute(int Mute);


/******************************************************************
功能描述：
入口参数：
返回参数：
说    明：
例    子：
******************************************************************/
int WSD_AL_AUDIO_952_SetVolume(int Volume);


/******************************************************************
功能描述：
入口参数：
返回参数：
说    明：
例    子：
******************************************************************/
int WSD_AL_AUDIO_952_SetWorkMode(WSD_952_WORK_MODE_E WorkMode);


/******************************************************************
功能描述：
入口参数：
返回参数：
说    明：
例    子：
******************************************************************/
int WSD_AL_AUDIO_952_SetSurroundMode(WSD_952_SURROUND_MODE_E SurroundMode);


/******************************************************************
功能描述：
入口参数：
返回参数：
说    明：
例    子：
******************************************************************/
int WSD_AL_AUDIO_952_SetKc(WSD_952_KC_PARAM_E *pParam);


/******************************************************************
功能描述：
入口参数：
返回参数：
说    明：
例    子：
******************************************************************/
int WSD_AL_AUDIO_952_FmEnable(int enable);


/******************************************************************
功能描述：
入口参数：
返回参数：
说    明：
例    子：
******************************************************************/
int WSD_AL_AUDIO_952_FmPlay(int index);


/******************************************************************
功能描述：
入口参数：
返回参数：
说    明：
例    子：
******************************************************************/
int WSD_AL_AUDIO_952_SetGeq(WSD_952_GEQ_PARAM_E *pParam);


/******************************************************************
功能描述：
入口参数：
返回参数：
说    明：
例    子：
******************************************************************/
int WSD_AL_AUDIO_952_SetLevel(WSD_952_LEVEL_PARAM_E *pParam);


#ifdef __cplusplus
}
#endif

#endif
