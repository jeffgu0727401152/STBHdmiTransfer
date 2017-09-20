/*************************************************************************
                             All Rights Reserved
                                 R&D Dept.
*************************************************************************/


/*************************************************************************

Filename:       damd_porting_dm2016.h

Description:    DM2016加密狗相关接口

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
#ifndef _WSD_AL_DM2016_H_
#define _WSD_AL_DM2016_H_

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
函数原型: WSD_AL_DM2016_Init

功能描述: DM2016加密狗初始化函数

参    数: 无

返 回 值:  
    D_SUCCESS: 成功
    D_FAILURE: 失败
    
注    意: 
******************************************************************/
D_INT32 WSD_AL_DM2016_Init(D_VOID);


/******************************************************************
函数原型: WSD_AL_DM2016_WriteKey

功能描述: DM2016加密狗密钥写函数

参    数:
    pKey(in): 16字节的密钥
    
返 回 值:  
    D_SUCCESS: 成功
    D_FAILURE: 失败
    
注    意: 
    密钥长度固定16字节
******************************************************************/
D_INT32 WSD_AL_DM2016_WriteKey(D_UINT8 *pKey);


/******************************************************************
函数原型: WSD_AL_DM2016_Enc

功能描述: DM2016加密狗加密函数

参    数:
    pKey(in): 16字节的秘钥
    pDate(in) : 8字节加密前的明文
    pEncDate(out): 8字节加密后的密文
    
返 回 值:  
    D_SUCCESS: 成功
    D_FAILURE: 失败
    
注    意: 
    密钥长度固定16字节,明文和密文长度固定8字节
******************************************************************/
D_INT32 WSD_AL_DM2016_Enc(D_UINT8 *pKey, D_UINT8 *pData, D_UINT8 *pEncData);


/******************************************************************
函数原型: WSD_AL_DM2016_Dec

功能描述: DM2016加密狗解密函数

参    数:
    pKey(in): 16字节的秘钥
    pDate(in) : 8字节解密前的密文
    pDecDate(out): 8字节解密后的明文
    
返 回 值:  
    D_SUCCESS: 成功
    D_FAILURE: 失败
    
注    意: 
    密钥长度固定16字节,明文和密文长度固定8字节
******************************************************************/
D_INT32 WSD_AL_DM2016_Dec(D_UINT8 *pData, D_UINT8 *pDecDate);


#ifdef __cplusplus
}
#endif

#endif
