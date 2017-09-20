/*************************************************************************
                             All Rights Reserved
                                 R&D Dept.
*************************************************************************/


/*************************************************************************

Filename:       damd_base_type.h

Description:    基础类型定义

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
#ifndef _WSD_BASE_TYPE_H_
#define _WSD_BASE_TYPE_H_

#ifdef __cplusplus
extern "C" {
#endif

/***********************************************************************
*                                包含头文件
************************************************************************/


/***********************************************************************
*                                常量定义
***********************************************************************/
typedef signed long    D_INT32;
typedef signed short   D_INT16;
typedef signed char    D_INT8;
typedef unsigned long  D_UINT32;
typedef unsigned short D_UINT16;
typedef unsigned char  D_UINT8;
typedef char           D_BOOL;
#define D_VOID			void
//typedef void           D_VOID;

#define D_SCREEN_VGA_WIDTH    (1280)
#define D_SCREEN_VGA_HEIGHT   (720)

#define D_SCREEN_OSD_WIDTH    (1280)
#define D_SCREEN_OSD_HEIGHT   (720)

#define D_SCREEN_CVBS_WIDTH    (720)
#define D_SCREEN_CVBS_HEIGHT   (576)

#ifndef D_SUCCESS
#define D_SUCCESS    (0)
#endif

#ifndef D_FAILURE
#define D_FAILURE    (0xFFFFFFFF)
#endif

#ifndef D_TRUE
#define D_TRUE       (0x01)
#endif

#ifndef D_FALSE
#define D_FALSE      (0x00)
#endif

#ifndef NULL
#define NULL         (0)
#endif

#ifndef URL_LEN
#define URL_LEN      (512+1)
#endif

#define USE_SHARE_EGL_CONTEXT

/***********************************************************************
*                                全局宏定义
***********************************************************************/


/***********************************************************************
*                                全局数据结构定义
***********************************************************************/
typedef struct _d_rect_
{
    D_INT32 Left;
    D_INT32 Top;
    D_INT32 Right;
    D_INT32 Bottom;
}D_RECT;


#ifdef __cplusplus
}
#endif

#endif
