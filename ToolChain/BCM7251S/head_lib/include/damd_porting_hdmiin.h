/*************************************************************************
                             All Rights Reserved
                                 R&D Dept.
*************************************************************************/


/*************************************************************************

Filename:       damd_porting_stream.h

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
#ifndef _WSD_AL_HDMIIN_H_
#define _WSD_AL_HDMIIN_H_

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

D_VOID WSD_AL_HDMIIN_Init(D_VOID);
D_VOID WSD_AL_HDMIIN_Uninit(D_VOID);

D_VOID WSD_AL_HDMIIN_MuteAudio(D_BOOL bMute);

#ifdef __cplusplus
}
#endif

#endif
