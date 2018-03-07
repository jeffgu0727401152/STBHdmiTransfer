/*************************************************************************
                             All Rights Reserved
                                 R&D Dept.
*************************************************************************/


/*************************************************************************

Filename:       damd_porting_platform.h

Description:    平台相关函数

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
#ifndef _WSD_AL_PLATFORM_H_
#define _WSD_AL_PLATFORM_H_

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
描述: 输出端口定义

成员:
    WSD_PORT_VGA_E:  VGA输出端口
    
    WSD_PORT_HDMI_E: HDMI输出端口

    WSD_PORT_CVBS_E: CVBS输出端口

注意: 
******************************************************************/
typedef enum
{
	WSD_PORT_VGA_E = 0,
	WSD_PORT_HDMI_E,
	WSD_PORT_CVBS_E,
	WSD_PORT_MAX_E
}WSD_PORT_E;


/******************************************************************
描述: 输出制式定义

成员:
    WSD_FORMAT_NTSC_E:  NTSC
    
    WSD_FORMAT_720P_E:  720p 60Hz

    WSD_FORMAT_1080i_E: 1080i 60Hz

    WSD_FORMAT_1080P_E: 1080p 60Hz

    WSD_FORMAT_2160P_30_E: 4K 30Hz

    WSD_FORMAT_2160P_60_E: 4K 60Hz

注意: 
******************************************************************/
typedef enum
{
    WSD_FORMAT_NTSC_E,
	WSD_FORMAT_720P_E,
	WSD_FORMAT_1080i_E,
	WSD_FORMAT_1080P_E,
    WSD_FORMAT_2160P_30_E,
    WSD_FORMAT_2160P_60_E,
	WSD_FORMAT_MAX_E
}WSD_FORMAT_E;


/******************************************************************
描述: 显示的数据源定义

成员:
    WSD_LAYER_SOURCE_GUI:  图形图像
    
    WSD_LAYER_SOURCE_MAIN_VIDEO: 主视频窗口

    WSD_LAYER_SOURCE_PIP_VIDEO: 预览窗口

注意: 
******************************************************************/
typedef enum
{
    WSD_LAYER_SOURCE_GUI = 0,
    WSD_LAYER_SOURCE_MAIN_VIDEO,
	WSD_LAYER_SOURCE_PIP_VIDEO
}WSD_LAYER_SOURCE_ID_E;


/******************************************************************
描述: 系统事件定义

成员:
	SYS_EVENT_HDMI_OUT_CONNECT:  HDMI 输出插入事件

	SYS_EVENT_HDMI_OUT_DISCONNECT: HDMI 输出拔除事件

	SYS_EVENT_HDMI_IN_CONNECT:  HDMI 输入插入事件

	SYS_EVENT_HDMI_IN_DISCONNECT: HDMI 输入拔除事件

注意: 
******************************************************************/
typedef enum _wsd_sys_event_e_ 
{
    SYS_EVENT_HDMI_OUT_CONNECT = 0,
    SYS_EVENT_HDMI_OUT_DISCONNECT,
    SYS_EVENT_HDMI_IN_CONNECT,
    SYS_EVENT_HDMI_IN_DISCONNECT,
    SYS_EVENT_MAX
}WSD_SYS_EVENT_E;


/***********************************************************************
*                                全局宏定义
***********************************************************************/
/******************************************************************
描  述: 系统时间回调函数定义

参  数:
    Event:系统事件

返回值:  
	D_SUCCESS: 成功
	D_FAILURE: 失败
	
注  意: 
******************************************************************/
typedef int (*SYS_EVENT_NOTIFY)(WSD_SYS_EVENT_E Event);


/***********************************************************************
*                                全局数据结构定义
***********************************************************************/
/******************************************************************
描述: 系统初始化参数定义

成员:
	OutFormat:  各端口输出制式
	
	pSysNotify: 系统事件回调函数

	SingleScreen:单屏输出

注意: 
******************************************************************/
typedef struct _wsd_plat_init_param_
{
	WSD_FORMAT_E OutFormat[WSD_PORT_MAX_E];
	
	SYS_EVENT_NOTIFY pSysNotify;

	D_BOOL SingleScreen;

	D_BOOL UHDEnable;
}WSD_PLAT_INIT_PARAM_T;


/******************************************************************
描述: 端口输出属性定义

成员:
	Format: 端口输出制式
	
	Layer0Source: 第0层数据源，取值见WSD_LAYER_SOURCE_ID_E定义
	
    Layer1Source: 第1层数据源，取值见WSD_LAYER_SOURCE_ID_E定义
    
    Layer2Source: 第2层数据源，取值见WSD_LAYER_SOURCE_ID_E定义

注意: 
    显示层次从0-2; 0层为最底层，2为最高层，2叠加在1上上面
******************************************************************/
typedef struct _wsd_output_param_t_
{
    WSD_FORMAT_E Format;
	
	int Layer0Source;
	int Layer1Source;
	int Layer2Source;
}WSD_OUTPUT_PARAM_T;


/***********************************************************************
*                                导出函数
***********************************************************************/
/******************************************************************
函数原型: WSD_AL_PLT_GetDefInitParam

功能描述: 平台初始化默认参数获取函数

参    数: 
    pInitParam(out): 返回初始化默认参数信息

返 回 值:  
	D_SUCCESS: 成功
	D_FAILURE: 失败
	
注    意: 
******************************************************************/
D_INT32 WSD_AL_PLT_GetDefInitParam(WSD_PLAT_INIT_PARAM_T *pInitParam);


/******************************************************************
函数原型: WSD_AL_PLT_Init

功能描述: 平台初始化函数

参    数: 
    pInitParam(in): 初始化默认参数

返 回 值: 
    D_SUCCESS: 成功
    D_FAILURE: 失败
    
注    意: 
    如果pInitParam为NULL,函数内将自动使用默认值
******************************************************************/
D_INT32 WSD_AL_PLT_Init(WSD_PLAT_INIT_PARAM_T *pInitParam);

/******************************************************************
函数原型: WSD_AL_PLT_GetInitParam

功能描述: 平台初始化参数获取函数

参    数: 
    pInitParam(out): 返回初始化参数信息

返 回 值:  
	D_SUCCESS: 成功
	D_FAILURE: 失败
	
注    意: 
******************************************************************/
D_INT32 WSD_AL_PLT_GetInitParam(WSD_PLAT_INIT_PARAM_T *pInitParam);

/******************************************************************
函数原型: WSD_AL_PLT_GetID

功能描述: 平台唯一ID获取函数

参    数: 无

返 回 值:  
    非NULL: 成功
    NULL: 失败
    
注    意: 
    返回的ID长度固定16字节
******************************************************************/
D_UINT8 * WSD_AL_PLT_GetID(D_VOID);


/******************************************************************
函数原型: WSD_AL_PLT_SetNotify

功能描述: 系统事件回调设置函数

参    数: 
    pNotify(in): 系统事件通知函数指针

返 回 值:  
    D_SUCCESS: 成功
    D_FAILURE: 失败
    
注    意: 
******************************************************************/
D_INT32 WSD_AL_PLT_SetSysNotify(SYS_EVENT_NOTIFY pNotify);


/******************************************************************
函数原型: WSD_AL_PLT_GetOuputParam

功能描述: 端口输出参数获取函数

参    数: 
    Port(in)   : 输出端口，含义见WSD_PORT_E定义
    pParam(out): 返回输出端口属性信息

返 回 值:  
    D_SUCCESS: 成功
    D_FAILURE: 失败
    
注    意: 
    目前各端口只支持部分属性，信息如下
    1、HDMI端口(WSD_PORT_HDMI_E)目前只支持Format属性配置
    2、VGA端口(WSD_PORT_VGA_E)目前只支持Lay属性配置
******************************************************************/
D_INT32 WSD_AL_PLT_GetOuputParam(WSD_PORT_E Port, WSD_OUTPUT_PARAM_T *pParam);


/******************************************************************
函数原型: WSD_AL_PLT_SetOuputParam

功能描述: 端口输出参数设置函数

参    数: 
    Port(in)  : 输出端口，含义见WSD_PORT_E定义
    pParam(in): 输出端口属性信息

返 回 值:  
    D_SUCCESS: 成功
    D_FAILURE: 失败
    
注    意: 
    目前各端口只支持部分属性的配置，信息如下
    1、HDMI端口(WSD_PORT_HDMI_E)目前只支持Format属性配置
    2、VGA端口(WSD_PORT_VGA_E)目前只支持Lay属性配置
******************************************************************/
D_INT32 WSD_AL_PLT_SetOuputParam(WSD_PORT_E Port, WSD_OUTPUT_PARAM_T *pParam);


/******************************************************************
函数原型: WSD_AL_PLT_SetCVBSOffset

功能描述: 设置CVBS显示边界偏移

参    数: 
    nLeftOffset(in): CVBS 左边界偏移
    nTopOffset(in): CVBS 上边界偏移
    nRightOffset(in): CVBS 右边界偏移
    nBottomOffset(in): CVBS 下边界偏移

返 回 值:  
    D_SUCCESS: 成功
    D_FAILURE: 失败
******************************************************************/
D_INT32 WSD_AL_PLT_SetCVBSOffset(
	int nLeftOffset,
	int nTopOffset,
	int nRightOffset,
	int nBottomOffset);


/******************************************************************
函数原型: WSD_AL_PLT_EnterStandby

功能描述: 系统待机处理函数

参    数: 无

返 回 值:  
    D_SUCCESS: 成功
    D_FAILURE: 失败
    
注    意: 
    调用此函数以后，进入真待机模式,再次按面板待机键,直接重启系统
******************************************************************/
D_INT32 WSD_AL_PLT_EnterStandby(D_VOID);


/******************************************************************
函数原型: WSD_AL_PLT_System_Command

功能描述: 系统命令函数

参    数: 无

返 回 值:  
    D_SUCCESS: 成功
    D_FAILURE: 失败
    
注    意: 
    此函数可代替系统的system命令
******************************************************************/
D_INT32 WSD_AL_PLT_System_Command(char *cmd);


/******************************************************************
函数原型: WSD_AL_PLT_HdmiShot

功能描述:HDMI输出图像抓屏函数

参    数: 无

返 回 值:  
    D_SUCCESS: 成功
    D_FAILURE: 失败
    
注    意: 
	pSurface为WSD_AL_GFX_CreateBitmap创建的WSD_AL_GFX_BITMAP_T结构内
	的pBitmap->pData
	
      WSD_AL_GFX_BITMAP_T *pBitmap;
            
      pBitmap = WSD_AL_GFX_CreateBitmap(WSD_AL_GFX_COLOR_ABGR8888_E, 640, 360);
      WSD_AL_PLT_HdmiShot(pBitmap->pData);
      ...............
      WSD_AL_GFX_DestroyBitmap(pBitmap);
******************************************************************/
D_INT32 WSD_AL_PLT_HdmiShot(D_VOID *pSurface);

/******************************************************************
函数原型: Print_NEXUS_Heap_Status

功能描述: 打印出nexus heap 的内存使用情况

参    数: 
    

返 回 值:  
    
注    意: 
******************************************************************/
void Print_NEXUS_Heap_Status(void);

#ifdef __cplusplus
}
#endif

#endif
