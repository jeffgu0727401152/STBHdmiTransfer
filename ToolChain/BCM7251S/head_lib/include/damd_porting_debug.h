/*************************************************************************
                             All Rights Reserved
                                 R&D Dept.
*************************************************************************/


/*************************************************************************

Filename:       damd_porting_debug.h

Description:    日志信息控制相关接口

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
#ifndef _WSD_AL_DEBUG_H_
#define _WSD_AL_DEBUG_H_

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
描述: 模块定义

成员:
    MODULE_DEFAULT: 全体模块, 用来设置默认级别
    
    MODULE_PLAT:系统模块
    
    MODULE_GFX: 图形模块
    
    MODULE_AUDIO: 音频模块
    
	MODULE_AUDIO_952: 952音频模块
	
	MODULE_AUDIO_BBE: BBE模块
	
    MODULE_GUIDE: 导唱模块
    
    MODULE_IO: 遥控器及面板按键模块
    
    MODULE_OSD: OSD显示模块
    
	MODULE_STREAM: 播放器模块
	
	MODULE_PCM: 混音播放器模块
	
	MODULE_RECORD: 录音模块
	
	MODULE_TEMP: 温度控制模块
	
	MODULE_PT2314: PT2314麦克风模块
	
	MODULE_MIC: 麦克风模块
	
	MODULE_ALC5640: ALC564音频处理模块
	
	MODULE_I2C: I2C处理模块

    MODULE_DM2016:2016加密狗模块

注意: 
******************************************************************/
typedef enum
{
    MODULE_DEFAULT = 0,
    MODULE_PLAT    = 1, 
    MODULE_GFX,         
    MODULE_AUDIO,       
	MODULE_AUDIO_952,   
	MODULE_AUDIO_BBE,	
    MODULE_GUIDE,       
    MODULE_IO,          
    MODULE_OSD,         
	MODULE_STREAM, 	    
	MODULE_PCM, 	    
	MODULE_RECORD, 	    
	MODULE_TEMP,        
	MODULE_PT2314,
	MODULE_MIC,
	MODULE_ALC5640,
	MODULE_WM8731,
	MODULE_I2C,
	MODULE_DM2016,
	MODULE_CS8406,
	MODULE_CS4398,
	MODULE_ROLAND,
	MODULE_CS8416,
	MODULE_CS42L52,
	MODULE_HDMIIN,
	MODULE_CAMERA,
	MODULE_RTC,
	MODULE_SINGER,
	MODULE_CLOUD,
    MODULE_MAX
}DBG_MODULE_T;


/******************************************************************
描述: 日志级别定义

成员:
	DBG_NONE: 未做单独设置，使用全局输出级别

	DBG_DEBUG: 详细调试信息

	DBG_WARN : 警告信息

	DBG_ERROR: 错误信息
	
	DBG_INFO: 永久显示信息
注意: 
******************************************************************/
typedef enum
{
	DBG_NONE  = -1, /* 未做单独设置，使用全局输出级别 */
	DBG_DEBUG = 0,	/* 输出 debug	级别信息 */
	DBG_WARN  = 1,	/* 输出 Warning 级别信息 */
	DBG_ERROR = 2,  /* 输出 Error   级别信息 */
	DBG_INFO  = 3,	/* 输出 Info    级别信息 */
}DBG_LEVEL_T;


/***********************************************************************
*                                全局宏定义
***********************************************************************/
#define PRINT_DEBUG(Module, fmt, arg...)  WSD_DBG_Print(Module, DBG_DEBUG, __FUNCTION__, __LINE__, fmt, ##arg)
#define PRINT_WARN(Module, fmt, arg...)  WSD_DBG_Print(Module, DBG_WARN, __FUNCTION__, __LINE__, fmt, ##arg)
#define PRINT_ERROR(Module, fmt, arg...) WSD_DBG_Print(Module, DBG_ERROR, __FUNCTION__, __LINE__, fmt, ##arg)
#define PRINT_INFO(Module, fmt, arg...)  WSD_DBG_Print(Module, DBG_INFO, __FUNCTION__, __LINE__, fmt, ##arg)


/***********************************************************************
*                                全局数据结构定义
***********************************************************************/


/***********************************************************************
*                                导出函数
***********************************************************************/
/******************************************************************
函数原型: WSD_DBG_Init

功能描述: 日志打印初始化函数

参    数: 无

返 回 值:  
    D_SUCCESS: 成功
    D_FAILURE: 失败
    
注    意: 
******************************************************************/
D_INT32 WSD_DBG_Init(D_VOID);


/******************************************************************
函数原型: WSD_DBG_SetLevel

功能描述: 日志打印初级别设置函数

参    数:
    Module(in): 模块名，见DBG_MODULE_T定义
    Level(in) : 调试级别，见DBG_LEVEL_T定义

返 回 值:  
    D_SUCCESS: 成功
    D_FAILURE: 失败
    
注    意: 
    设置了调试级别以后，小于调试级别的信息将不会打印出来
******************************************************************/
D_INT32 WSD_DBG_SetLevel(DBG_MODULE_T Module, DBG_LEVEL_T Level);


/******************************************************************
函数原型: WSD_DBG_Print

功能描述: 信息打印函数

参    数:
    Module(in): 模块名，见DBG_MODULE_T定义
    Level(in) : 调试级别，见DBG_LEVEL_T定义
    Func(in): 函数名
    Line(in): 文件行信息
    fmt(in) : 调试信息
    
返 回 值:  
    D_SUCCESS: 成功
    D_FAILURE: 失败
    
注    意: 
******************************************************************/
D_INT32 WSD_DBG_Print(DBG_MODULE_T Module, DBG_LEVEL_T Level, const char *Func, const char* Line, const char *fmt, ...);


#ifdef __cplusplus
}
#endif

#endif
