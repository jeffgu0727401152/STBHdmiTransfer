/*************************************************************************
                             All Rights Reserved
                                 R&D Dept.
*************************************************************************/


/*************************************************************************

Filename:       damd_porting_gfx.h

Description:    图形控制相关接口

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
#ifndef _WSD_AL_GFX_H_
#define _WSD_AL_GFX_H_

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
描述: 颜色类型定义

成员:
	WSD_AL_GFX_COLOR_ARGB8888_E: 32位色,ARGB，Alpha 8bit，R/G/B各8bit

	WSD_AL_GFX_COLOR_ABGR8888_E: 32位色,ABGR，Alpha 8bit，R/G/B各8bit

	WSD_AL_GFX_COLOR_ARGB1555_E: 16位色,ARGB，Alpha 1bit，R/G/B各5bit

    WSD_AL_GFX_COLOR_ABGR1555_E: 16位色,ABGR，Alpha 1bit，R/G/B各5bit
    
    WSD_AL_GFX_COLOR_ARGB4444_E: 15位色,ABGR，Alpha 4bit，R/G/B各4bit
	
注意: 
******************************************************************/
typedef enum _wsd_al_gfx_color_format_e_
{
	WSD_AL_GFX_COLOR_ARGB8888_E = 0,
	WSD_AL_GFX_COLOR_ABGR8888_E,
	WSD_AL_GFX_COLOR_ARGB1555_E,
	WSD_AL_GFX_COLOR_ABGR1555_E,
	WSD_AL_GFX_COLOR_ARGB4444_E,
	WSD_AL_GFX_COLOR_MAX_E
}WSD_AL_GFX_COLOR_FROMAT_E;


/******************************************************************
描述: 绘图模式定义

成员:
	WSD_AL_GFX_COMPOPT_COPY_E: 拷贝模式

	WSD_AL_GFX_COMPOPT_BLEND_E: 混合模式
	
注意: 
******************************************************************/
typedef enum _wsd_al_gfx_compopt_e_
{
	WSD_AL_GFX_COMPOPT_COPY_E = 0,   /* Copy source to output */
	WSD_AL_GFX_COMPOPT_BLEND_E,      /* Source over dest */
	WSD_AL_GFX_COMPOPT_MAX_E
}WSD_AL_GFX_COMPOPT_E;


typedef struct _wsd_image_src_type_t_
{
    D_BOOL     ImageSrcType;          /*图片来源类型,DecodeType=0为文件，DecodeType=1为buffer */
	D_UINT8   *pImageName;            /*需要解码的图片名称，当DecodeType=0 时有效*/
	D_VOID    *pImageBuffer;          /*需要解码的图片存储地址，当DecodeType=1 时有效*/
	D_UINT32   ImageBufferSize;       /*需要解码的图片大小，当DecodeType=1 时有效*/
} WSD_IMAGE_SRC_TYPE_T;


typedef struct _wsd_image_info_t_
{
    D_INT32  SurfaceHandle;            /*解码后存放图片信息的句柄*/
	D_UINT16 Width;	                  /*图片宽度*/						
	D_UINT16 Height; 				  /*图片高度*/			
	D_UINT32 Size;                    /*解码后存放图片数据buf 大小*/
	D_VOID  *pData;	                  /*解码后存放图片数据buf 指针*/
} WSD_IMAGE_INFO_T;


/***********************************************************************
*                                全局宏定义
***********************************************************************/
typedef void *WSD_AL_GFX_EGL_WINDOW; /** opengl es 窗口句柄类型定义 **/


/***********************************************************************
*                                全局数据结构定义
***********************************************************************/
/******************************************************************
描述: 位图信息结构定义

成员:
	ColorFormat: 颜色类型

	bpp: 颜色bit位数,16/32

	Width: 位图宽度

	Height: 位图高度
	
	Pitch: 每行占有的byte数

    pBits: 位图内存地址
    
    Size: 位图内存长度
    
    pData: 位图私有数据,外部不得使用
	
注意: 
******************************************************************/
typedef struct _wsd_al_gfx_bitmap_t_
{
	WSD_AL_GFX_COLOR_FROMAT_E ColorFormat;
	D_UINT32 bpp;

	D_UINT16 Width;							
	D_UINT16 Height; 						

	D_UINT32 Pitch; 						

	D_VOID  *pBits;
	D_UINT32 Size;
    
	D_VOID  *pData;	
}WSD_AL_GFX_BITMAP_T;


/******************************************************************
描述: Opengl专用位图信息结构定义

成员:
	Width: 位图宽度

	Height: 位图高度
	
    pPixmap: 位图内存地址
    
    pSurface: 位图私有数据,外部不得使用
	
注意: 
******************************************************************/
typedef struct _wsd_al_gfx_pixmap_t_
{
	D_UINT16 Width;
	D_UINT16 Height;
   
	D_VOID  *pPixmap;	
	D_VOID  *pSurface;    
}WSD_AL_GFX_PIXMAP_T;


/******************************************************************
描述: 位图拷贝属性

成员:
	pForBitmap: 位图宽度

	ForRect: 位图高度
	
       pBckBitmap: 位图内存地址
    
	BckRect: 位图私有数据,外部不得使用

	pDstBitmap

      	DstRect

      	Compopt
注意: 
      pBckBitmap为空或者等于pDstBitmap时,直接将pForBitmap按照
      绘图模式拷贝到pDstBitmap
      如果pBckBitmap不为空，则将pForBitmap 和pBckBitma 做混合后，
      拷贝到pDstBitmap
      Compopt = WSD_AL_GFX_COMPOPT_COPY_E时，直接把pForBitmap拷贝到
      pDstBitmap
******************************************************************/
typedef struct _wsd_al_gfx_blit_param_t_
{
	WSD_AL_GFX_BITMAP_T *pForBitmap;
	D_RECT ForRect;

	WSD_AL_GFX_BITMAP_T *pBckBitmap;
	D_RECT BckRect;
	
	WSD_AL_GFX_BITMAP_T *pDstBitmap;
	D_RECT DstRect;

	WSD_AL_GFX_COMPOPT_E Compopt;
}WSD_AL_GFX_BLIT_PARAM_T;


/***********************************************************************
*                                导出函数
***********************************************************************/
/******************************************************************
函数原型: WSD_AL_GFX_Init

功能描述: 图形控制初始化函数

参    数: 无

返 回 值:  
    D_SUCCESS: 成功
    D_FAILURE: 失败
    
注    意: 
******************************************************************/
D_INT32 WSD_AL_GFX_Init(D_VOID);


/******************************************************************
函数原型: WSD_AL_GFX_UnInit

功能描述: 图形控制去初始化函数

参    数: 无

返 回 值:  
    D_SUCCESS: 成功
    D_FAILURE: 失败
    
注    意: 
******************************************************************/
D_INT32 WSD_AL_GFX_UnInit(D_VOID);


/******************************************************************
函数原型: WSD_AL_GFX_CreateEglWindow

功能描述: Opengl窗口创建函数

参    数:
    Width(in) : 窗口宽度
    Height(in): 窗口高度

返 回 值: 返回窗口句柄，
    非NULL: 成功
    NULL: 失败
    
注    意: 
******************************************************************/
WSD_AL_GFX_EGL_WINDOW WSD_AL_GFX_CreateEglWindow(D_UINT16 Width, D_UINT16 Height);


/******************************************************************
函数原型: WSD_AL_GFX_DestroyEglWindow

功能描述: Opengl窗口销毁函数

参    数:
    Window(in): 窗口句柄，由WSD_AL_GFX_CreateEglWindow函数创建

返 回 值:  
    D_SUCCESS: 成功
    D_FAILURE: 失败
    
注    意: 
******************************************************************/
D_INT32 WSD_AL_GFX_DestroyEglWindow(WSD_AL_GFX_EGL_WINDOW Window);


/******************************************************************
函数原型: WSD_AL_GFX_SetUseOpenglES2

功能描述: 设定 opengl 版本

参    数:
   bUseES2: 0-使用ES1.1other-使用ES2.0

返 回 值:  
    D_SUCCESS: 成功
    D_FAILURE: 失败
    
注    意: 
    在使用opengl函数之前，需要调用此函数进行初始化。
******************************************************************/
D_VOID WSD_AL_GFX_SetUseOpenglES2(D_BOOL bUseES2);

/******************************************************************
函数原型: WSD_AL_GFX_InitEgl

功能描述: Opengl初始化函数

参    数:
    Window(in): 窗口句柄，由WSD_AL_GFX_CreateEglWindow函数创建

返 回 值:  
    D_SUCCESS: 成功
    D_FAILURE: 失败
    
注    意: 
    在使用opengl函数之前，需要调用此函数进行初始化。
******************************************************************/
D_INT32 WSD_AL_GFX_InitEgl(WSD_AL_GFX_EGL_WINDOW Window);


/******************************************************************
函数原型: WSD_AL_GFX_CreateBitmap

功能描述: 位图创建函数

参    数:
    ColorFormat(in): 颜色类型
    Width(in) : 位图宽度
    Height(in): 位图高度

返 回 值: 返回位图信息句柄，
    非NULL: 成功
    NULL: 失败
    
注    意: 
******************************************************************/
WSD_AL_GFX_BITMAP_T * WSD_AL_GFX_CreateBitmap(WSD_AL_GFX_COLOR_FROMAT_E ColorFormat,
                                                    D_UINT16 Width, D_UINT16 Height);


/******************************************************************
函数原型: WSD_AL_GFX_DestroyBitmap

功能描述: 位图销毁函数

参    数: 
    pBitmap(in): 位图信息句柄，由WSD_AL_GFX_CreateBitmap函数创建
	
返 回 值:  
	D_SUCCESS: 成功
	D_FAILURE: 失败

注    意:
******************************************************************/
D_INT32 WSD_AL_GFX_DestroyBitmap(WSD_AL_GFX_BITMAP_T *pBitmap);



/******************************************************************
函数原型: WSD_AL_GFX_FlushBitmap

功能描述: 位图销毁函数

参    数: 
    pBitmap(in): 位图信息句柄，由WSD_AL_GFX_FlushBitmap函数创建
	
返 回 值:  
	D_SUCCESS: 成功
	D_FAILURE: 失败

注    意:
******************************************************************/
D_INT32 WSD_AL_GFX_FlushBitmap(WSD_AL_GFX_BITMAP_T *pBitmap);


/******************************************************************
函数原型: WSD_AL_GFX_SetAlpha

功能描述: 透明度设置函数

参    数:
    Alpha(in): 透明度，取值范围【0,255】

返 回 值:  
    D_SUCCESS: 成功
    D_FAILURE: 失败
    
注    意: 
    Alpha = 0 时表示全透明，Alpha = 255 时表示不透明
******************************************************************/
D_INT32 WSD_AL_GFX_SetAlpha(D_UINT8 Alpha);


/******************************************************************
函数原型: WSD_AL_GFX_GetBrightness

功能描述: 亮度获取函数

参    数:
    Brightness(in): 亮度，取值范围【0,100】
    
返 回 值:  
    D_SUCCESS: 成功
    D_FAILURE: 失败
    
注    意: 
******************************************************************/
D_INT32 WSD_AL_GFX_GetBrightness(D_UINT8 *pBrightness);


/******************************************************************
函数原型: WSD_AL_GFX_SetBrightness

功能描述: 亮度设置函数

参    数:
    Brightness(in): 亮度，取值范围【0,100】
    
返 回 值:  
    D_SUCCESS: 成功
    D_FAILURE: 失败
    
注    意: 
******************************************************************/
D_INT32 WSD_AL_GFX_SetBrightness(D_UINT8 Brightness);


/******************************************************************
函数原型: WSD_AL_GFX_GetContrast

功能描述: 对比度获取函数

参    数:
    Contrast(in): 对比度，取值范围【0,100】

返 回 值:  
    D_SUCCESS: 成功
    D_FAILURE: 失败
    
注    意: 
******************************************************************/
D_INT32 WSD_AL_GFX_GetContrast(D_UINT8 *pContrast);


/******************************************************************
函数原型: WSD_AL_GFX_SetContrast

功能描述: 对比度设置函数

参    数:
    Contrast(in): 对比度，取值范围【0,255】

返 回 值:  
    D_SUCCESS: 成功
    D_FAILURE: 失败
    
注    意: 
******************************************************************/
D_INT32 WSD_AL_GFX_SetContrast(D_UINT8 Contrast);


/******************************************************************
函数原型: WSD_AL_GFX_SetSaturation

功能描述: 饱和度设置函数

参    数:
    Contrast(in): 饱和度，取值范围【0,255】

返 回 值:  
    D_SUCCESS: 成功
    D_FAILURE: 失败
    
注    意: 
******************************************************************/
D_INT32 WSD_AL_GFX_SetSaturation(D_UINT8 Saturation);


/******************************************************************
函数原型: WSD_AL_GFX_SetHue

功能描述: 色度设置函数

参    数:
    Hue(in): 色度，取值范围【0,255】

返 回 值:  
    D_SUCCESS: 成功
    D_FAILURE: 失败
    
注    意: 
******************************************************************/
D_INT32 WSD_AL_GFX_SetHue(D_UINT8 Hue);


/******************************************************************
函数原型: WSD_AL_GFX_CreatePixmap

功能描述: opengl专用位图创建函数

参    数:
    pPixmap(in) : 位图宽度和高度
    pPixmap(out): 位图信息

返 回 值: 
    D_SUCCESS: 成功
    D_FAILURE: 失败
    
注    意: 
    pPixmap既做传入参数，也做传出参数
******************************************************************/
D_INT32 WSD_AL_GFX_CreatePixmap(WSD_AL_GFX_PIXMAP_T *pPixmap);


/******************************************************************
函数原型: WSD_AL_GFX_DestroyPixmap

功能描述: opengl专用位图销毁函数

参    数:
    pPixmap(in): 位图信息,由WSD_AL_GFX_CreatePixmap函数创建

返 回 值:  
    D_SUCCESS: 成功
    D_FAILURE: 失败
    
注    意: 
******************************************************************/
D_INT32 WSD_AL_GFX_DestroyPixmap(WSD_AL_GFX_PIXMAP_T *pPixmap);


/******************************************************************
函数原型: WSD_AL_GFX_2DInit

功能描述:2D 图形控制初始化函数

参    数: 无

返 回 值:  
    D_SUCCESS: 成功
    D_FAILURE: 失败
    
注    意: 
******************************************************************/
D_INT32 WSD_AL_GFX_2DInit(D_VOID);


/******************************************************************
函数原型: WSD_AL_GFX_2DGetBitmap

功能描述:2D 显示图层图像信息获取函数

参    数: 
    pBitmap(out):返回图像信息

返 回 值:  
    D_SUCCESS: 成功
    D_FAILURE: 失败
    
注    意: 
******************************************************************/
D_INT32 WSD_AL_GFX_2DGetBitmap(WSD_AL_GFX_BITMAP_T *pBitmap);


/******************************************************************
函数原型: WSD_AL_GFX_2DFillRect

功能描述:2D 显示图层图像信息获取函数

参    数: 
    pBitmap(out):返回图像信息

返 回 值:  
    D_SUCCESS: 成功
    D_FAILURE: 失败
    
注    意: 
******************************************************************/
D_INT32 WSD_AL_GFX_2DFillRect(WSD_AL_GFX_BITMAP_T *pBitmap, D_RECT Rect, D_INT32 Color);


/******************************************************************
函数原型: WSD_AL_GFX_2DBlit

功能描述:2D 图形拷贝函数

参    数: 
    pParam(in):图像拷贝属性信息

返 回 值:  
    D_SUCCESS: 成功
    D_FAILURE: 失败
    
注    意: 
******************************************************************/
D_INT32 WSD_AL_GFX_2DBlit(WSD_AL_GFX_BLIT_PARAM_T *pParam);


/******************************************************************
函数原型: WSD_AL_GFX_2DShow

功能描述:2D 图像显示函数，直接输出到屏幕

参    数: 
    pBitmap(in): 图像信息
    SrcRect(in):  图像区域
    DstRect(in):  屏幕区域
    
返 回 值:  
    D_SUCCESS: 成功
    D_FAILURE: 失败
    
注    意: 
******************************************************************/
D_INT32 WSD_AL_GFX_2DShow(WSD_AL_GFX_BITMAP_T *pBitmap, D_RECT SrcRect, D_RECT DstRect);


/******************************************************************
函数原型: WSD_AL_GFX_2DFlush

功能描述:2D 屏幕显示刷新函数

参    数: 无

返 回 值:  
    D_SUCCESS: 成功
    D_FAILURE: 失败
    
注    意: 
******************************************************************/
D_INT32 WSD_AL_GFX_2DFlush(D_VOID);


/*****************************************************************************************************************
函数原型: WSD_AL_GFX_ImageDecode

功能描述: 将图片硬解码后，将数据存入内存buffer

参	  数: 
	pImageDecode(in): 图片解码方式和原始图片路径，具体信息参考WSD_IMAGE_SRC_TYPE_T结构体
	pImageInfo(out): 图片解码后的信息，具体信息参考pImageInfo结构体
	
返 回 值:  
    D_SUCCESS: 成功
    D_FAILURE: 失败

注	  意: 必须与WSD_AL_GFX_FreeSurface成对出现，解码数据使用完需要释放内存。
******************************************************************************************************************/
D_INT32 WSD_AL_GFX_ImageDecode(WSD_IMAGE_SRC_TYPE_T *pImageDecode, WSD_IMAGE_INFO_T *pImageInfo);


/******************************************************************
函数原型: WSD_AL_GFX_FreeSurface

功能描述: 释放surface资源

参    数: 
    Surface(in)：Surface句柄

返 回 值:  
    D_SUCCESS: 成功
    D_FAILURE: 失败
    
注    意: 
******************************************************************/
D_INT32 WSD_AL_GFX_FreeSurface (D_INT32 Surface);


#ifdef __cplusplus
}
#endif

#endif
