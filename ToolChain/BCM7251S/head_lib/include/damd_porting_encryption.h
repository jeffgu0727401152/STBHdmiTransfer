/*************************************************************************
                             All Rights Reserved
                                 R&D Dept.
*************************************************************************/


/*************************************************************************

Filename:       damd_porting_encryption.h

Description:    加密相关接口

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
#ifndef _WSD_AL_ENCRYPTION_H_
#define _WSD_AL_ENCRYPTION_H_

#ifdef __cplusplus
extern "C" {
#endif

/***********************************************************************
*                                包含头文件
************************************************************************/


/***********************************************************************
*                                常量定义
***********************************************************************/


/***********************************************************************
*                                全局宏定义
***********************************************************************/


/***********************************************************************
*                                全局数据结构定义
***********************************************************************/


/***********************************************************************
*                                导出函数
***********************************************************************/
/******************************************************************
函数原型: WSD_ENC_Init

功能描述: 初始化加密设备

参    数: 无

返 回 值:  
	D_SUCCESS: 成功
	D_FAILURE: 失败
	
注    意: 
******************************************************************/
D_INT32 WSD_ENC_Init(D_VOID);

/******************************************************************
函数原型: WSD_ENC_Reset

功能描述: 软件复位

参    数:

返 回 值:  
    D_SUCCESS: 成功
    D_FAILURE: 失败
    
注    意: 
******************************************************************/
D_INT32 WSD_ENC_Reset(D_INT32 tBool);

/******************************************************************
函数原型: WSD_ENC_Uninit

功能描述: 加密去初始化

参    数:


返 回 值:
    D_SUCCESS: 成功
    D_FAILURE: 失败

注    意:
******************************************************************/
D_INT32 WSD_ENC_Uninit(D_VOID);


#ifdef __cplusplus
}
#endif

#endif

