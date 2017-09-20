/*************************************************************************
                             All Rights Reserved
                                 R&D Dept.
*************************************************************************/


/*************************************************************************

Filename:       damd_porting_osd.h

Description:    OSD显示控制函数

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
#ifndef _WSD_AL_OSD_H_
#define _WSD_AL_OSD_H_

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
/******************************************************************
描述: 调色板定义

成员:
	r: 红色值
	
	g: 绿色值

    b: 蓝色值

    _padding: 预留
		
注意: 
******************************************************************/
typedef struct _mw_palentry_
{
	D_UINT8 r;
	D_UINT8	g;
	D_UINT8	b;
	D_UINT8 _padding;
} MWPALENTRY;

typedef struct sRECT
{
    int x;
    int y;
    unsigned int width;
    unsigned int height;
} sRECT;

typedef struct bsurface_settings
{
	sRECT position; /* Position and size of the surface.
		position.width and height are readonly */
	unsigned int visible; /* Defaults to false. On magnum platforms, this causes a 
		surface to be automatically blitted to the framebuffer when bgraphics_sync
		is called. On legacy platforms, this causes the surface to be blended into
		the display by the compositor. */
	unsigned char alpha; /* 0x00 to 0xFF where 0xFF is opaque and 0x00 is transparent. 
		On magnum platforms, this is only used when automatically blitting to 
		the framebuffer with bgraphics_sync. On legacy platforms, this controls
		the alpha blending with the compositor. */
} bsurface_settings;


/***********************************************************************
*                                导出函数
***********************************************************************/
/******************************************************************
函数原型: WSD_AL_OSD_Init

功能描述: 初始化OSD设备，并将OSD framebuffer映射到用户空间；

参    数: 
    Bit(in)：framebuffer 每一像素的bit数,预留使用，目前固定采用32位色ARGB

返 回 值:  
    非NULL: 成功
    NULL:   失败
    
注    意: 
    在进行OSD画图之前，必须首先调用该函数，完成OSD的初始化动作。
    该函数同时负责内部变量的初始化及framebuffer向用户空间的映射。
******************************************************************/
D_INT32 WSD_AL_OSD_Init (D_INT32 Bit);

/******************************************************************
函数原型: WSD_AL_OSD_Close

功能描述: 关闭OSD设备

参    数: 
    SurfaceHandle(in)：OSD设备句柄，由WSD_AL_OSD_Init创建

返 回 值:  
    D_SUCCESS: 成功
    D_FAILURE: 失败
    
注    意: 
    此函数会关闭OSD设备，并释放相关资源。
******************************************************************/
D_INT32 WSD_AL_OSD_Close (D_INT32 SurfaceHandle);


/******************************************************************
函数原型: WSD_AL_OSD_Disable

功能描述: 禁用OSD输出

参    数: 
    SurfaceHandle(in)：OSD设备句柄，由WSD_AL_OSD_Init创建

返 回 值:  
    D_SUCCESS: 成功
    D_FAILURE: 失败
    
注    意: 
    此函数用于暂时禁用OSD设备，但不会释放OSD资源及清空OSD Framebuffer。
    用户可以使用下面的WSD_AL_OSD_Enable()函数重新激活OSD。
******************************************************************/
D_INT32 WSD_AL_OSD_Disable (D_INT32 SurfaceHandle);


/******************************************************************
函数原型: WSD_AL_OSD_Enable

功能描述: 启用OSD输出

参    数: 
    SurfaceHandle(in)：OSD设备句柄，由WSD_AL_OSD_Init创建

返 回 值:  
    D_SUCCESS: 成功
    D_FAILURE: 失败
    
注    意: 
    用于激活并重新启用OSD设备，与WSD_AL_OSD_Disable（）函数对应。
******************************************************************/
D_INT32 WSD_AL_OSD_Enable (D_INT32 SurfaceHandle);


/**
 功能描述：创建Surface；
 入口参数：nWidth，nHeight ；
 返回参数：返回OSD 设备句柄；
 **/
int WSD_AL_OSD_CreateSurface(int nWidth, int nHeight);

/**
 功能描述：Surface销毁
 入口参数：SurfaceHandle句柄；
 返回参数：无；
 说    明:
 **/
void WSD_AL_OSD_SurfaceDestroy(int SurfaceHandle);

/**
 功能描述：填充Surface
 入口参数：nSurface句柄；
 返回参数：无；
 说    明:
 **/
void WSD_AL_OSD_GetSurfaceInfo(int nSurface, bsurface_settings **settings);

/**
 功能描述：Surface销毁
 入口参数：SurfaceHandle句柄；
 返回参数：无；
 说    明:
 **/
void WSD_AL_OSD_GetSurfaceMemory(int nSurface, int **buffer,unsigned int *pitch);

/**
 功能描述：填充Surface
 入口参数：nSurface句柄；
 返回参数：无；
 说    明:
 **/
void WSD_AL_OSD_SurfaceFill(int nSurface, int height, int width, int x, int y, unsigned int pixel);

/**
 功能描述：拷贝Surface
 入口参数：nSurface句柄；
 返回参数：无；
 说    明:
 **/
void WSD_AL_OSD_SurfaceCopy(int destsurface,int dest_x,int dest_y,int dest_w,int dest_h,int srcsurface,int src_x,int src_y,int src_w,int src_h);

void WSD_AL_OSD_SurfaceBlit(int destsurface, const sRECT **destrect, unsigned int operation, int src1, const sRECT **src1_rect, int src2, const sRECT **src2_rect, unsigned int pixel1, unsigned int pixel2);

/**
 功能描述：设置Graphics buffer 大小
 入口参数：nDisplayIndex 代表是哪一个DISPLAY, 0:VGA  1:TV
                             nSurface句柄
 返回参数：无；
 说    明:
 **/
void WSD_AL_OSD_SetGraphicsFramebuffer(int nDisplayIndex, int nFBIndex, int nSurface);

/**
 功能描述：获取Graphics buffer 大小
 入口参数：nDisplayIndex 代表是哪一个DISPLAY, 0:VGA  1:TV
                             nSurface句柄
 返回参数：无；
 说    明:
 **/
int WSD_AL_OSD_GetGraphicsFramebufferSurface(int nDisplayIndex, int nFBIndex);

int WSD_AL_OSD_Get3DGraphicsFramebufferSurface(int nDisplayIndex);

/******************************************************************
函数原型: WSD_AL_OSD_SetCoordinate

功能描述: 设置用户自定义坐标原点

参	  数: 
	X(in): 新坐标系原点x坐标
	Y(in): 新坐标系原点y坐标

返 回 值:  
	D_SUCCESS: 成功
	D_FAILURE: 失败
	
注	  意: 
    调用此函数以后，用户绘制的操作的坐标都相对于该函数设置的X,Y，而不是0，0
    这样可以不修改画图函数即可改变画图位置。
******************************************************************/
D_INT32 WSD_AL_OSD_SetCoordinate(D_INT32 X, D_INT32 Y);


/******************************************************************
函数原型: WSD_AL_OSD_SetScreenSize

功能描述: 设置OSD在Screen上显示大小

参	  数: 
	X(in): 新坐标系原点x坐标
	Y(in): 新坐标系原点y坐标
    Width(in) : 可绘制区域的宽度
    Height(in): 可绘制区域的高度

返 回 值:  
	D_SUCCESS: 成功
	D_FAILURE: 失败
	
注	  意: 
	调用此函数以后，用户绘制的操作的坐标都相对于该函数设置的X,Y，
	操作的宽度不能超过Width，Height
******************************************************************/
D_INT32 WSD_AL_OSD_SetScreenSize(D_INT32 X, D_INT32 Y, D_INT32 Width, D_INT32 Height);


/******************************************************************
函数原型: WSD_AL_OSD_GetScreenSize

功能描述: 获取当前OSD 绘制区域的长、宽

参	  数: 
    pWidth(out) : 返回可绘制区域的宽度
    pHeight(out): 返回可绘制区域的高度

返 回 值:  
	D_SUCCESS: 成功
	D_FAILURE: 失败
	
注	  意: 
******************************************************************/
D_INT32 WSD_AL_OSD_GetScreenSize(D_INT32 *pWidth, D_INT32 *pHeight);


/******************************************************************
函数原型: WSD_AL_OSD_SetAlpha

功能描述: 设置OSD输出透明度

参    数: 
    Alpha(in)：透明度，使用范围【0,255】

返 回 值:  
    D_SUCCESS: 成功
    D_FAILURE: 失败
    
注    意: 
    调用该函数以后，所有输出，会使用此值作为颜色的透明度
******************************************************************/ 
D_INT32 WSD_AL_OSD_SetAlpha(D_UINT8 Alpha);


/******************************************************************
函数原型: WSD_AL_OSD_SetPalatte

功能描述: 设置自定义调色板

参    数: 
    First(in): 调色板起始索引，范围【0,255】
    Count(in): 调色板数目
    pPal(in) : 调色板信息指针

返 回 值:  
    D_SUCCESS: 成功
    D_FAILURE: 失败
    
注    意: 
******************************************************************/ 
D_INT32 WSD_AL_OSD_SetPalatte(D_INT32 First, D_INT32 Count, MWPALENTRY *pPal);


/******************************************************************
函数原型: WSD_AL_OSD_ClearScreen

功能描述: 屏幕清除函数

参    数: 无

返 回 值:  
    D_SUCCESS: 成功
    D_FAILURE: 失败
    
注    意: 
    调用该函数以后，OSD屏幕会被清除成全透明黑色0x00000000
    调用该函数以后，要调用WSD_AL_OSD_Update函数同步到输出
******************************************************************/ 
D_INT32 WSD_AL_OSD_ClearScreen (D_VOID);


/******************************************************************
函数原型: WSD_AL_OSD_ClearRect

功能描述: 屏幕区域清除函数

参    数: 
    x(in): 清除区域左上角X轴坐标
    y(in): 清除区域左上角Y轴坐标
    Width(in): 清除区域宽度
    height(in): 清除区域高度

返 回 值:  
    D_SUCCESS: 成功
    D_FAILURE: 失败
    
注    意: 
    调用该函数以后，OSD屏幕指定区域会被清除成全透明黑色0x00000000
    调用该函数以后，要调用WSD_AL_OSD_Update函数同步到输出
******************************************************************/
D_INT32 WSD_AL_OSD_ClearRect(D_INT32 X, D_INT32 Y, D_INT32 Width, D_INT32 Height);


/******************************************************************
函数原型: WSD_AL_OSD_DrawPixel

功能描述: 画点

参	  数: 
    X(in): 横坐标
    Y(in): 纵坐标；
    Color(in): 绘制颜色
    
返 回 值:  
	D_SUCCESS: 成功
	D_FAILURE: 失败
	
注	  意: 
    调用该函数以后，要调用WSD_AL_OSD_Update函数同步到输出
******************************************************************/ 
D_INT32 WSD_AL_OSD_DrawPixel(D_INT32 X, D_INT32 Y, D_UINT32 Color);


/******************************************************************
函数原型: WSD_AL_OSD_ReadPixel

功能描述: 读出Screen某一点的颜色

参	  数: 
	X(in): 横坐标
	Y(in): 纵坐标；
	
返 回 值:  指定点的颜色值
	
注	  意: 
******************************************************************/ 
D_UINT32 WSD_AL_OSD_ReadPixel(D_INT32 X, D_INT32 Y);


/******************************************************************
函数原型: WSD_AL_OSD_DrawHline

功能描述: 画横线

参	  数: 
    xStart(in): 起点横坐标
    xEnd(in)  : 终点横坐标
    Y(in)     : 纵坐标；
    Color(in) : 绘制颜色
    
返 回 值:  
	D_SUCCESS: 成功
	D_FAILURE: 失败
	
注	  意: 
    调用该函数以后，要调用WSD_AL_OSD_Update函数同步到输出
******************************************************************/  
D_INT32 WSD_AL_OSD_DrawHline(D_INT32 xStart, D_INT32 xEnd, D_INT32 Y, D_UINT32 Color);


/******************************************************************
函数原型: WSD_AL_OSD_DrawVline

功能描述: 画竖线

参	  数: 
	X(in)     : 横坐标
	yStart(in): 起点纵坐标
	yEnd(in)  : 终点纵坐标
	Color(in) :	绘制颜色
	
返 回 值:  
	D_SUCCESS: 成功
	D_FAILURE: 失败
	
注	  意: 
	调用该函数以后，要调用WSD_AL_OSD_Update函数同步到输出
******************************************************************/  
D_INT32 WSD_AL_OSD_DrawVline(D_INT32 X, D_INT32 yStart, D_INT32 yEnd, D_UINT32 Color);


/******************************************************************
函数原型: WSD_AL_OSD_FillRect

功能描述: 填充矩形

参	  数: 
	X(in): 起点横坐标
	y(in): 起点纵坐标
	Width(in) : 宽度
	Height(in): 高度
	Color(in) : 绘制颜色
	
返 回 值:  
	D_SUCCESS: 成功
	D_FAILURE: 失败
	
注	  意: 
	调用该函数以后，要调用WSD_AL_OSD_Update函数同步到输出
******************************************************************/
D_INT32 WSD_AL_OSD_FillRect(D_INT32 X, D_INT32 Y, D_INT32 Width, D_INT32 Height, D_UINT32 Color);


/******************************************************************
函数原型: WSD_AL_OSD_FillRect

功能描述: 画矩形

参	  数: 
	X(in): 起点横坐标
	y(in): 起点纵坐标
	Width(in) : 宽度
	Height(in): 高度
	Color(in) : 绘制颜色
	
返 回 值:  
	D_SUCCESS: 成功
	D_FAILURE: 失败
	
注	  意: 
	调用该函数以后，要调用WSD_AL_OSD_Update函数同步到输出
******************************************************************/
D_INT32 WSD_AL_OSD_DrawRect(D_INT32 X, D_INT32 Y, D_INT32 Width, D_INT32 Height, D_UINT32 Color);


/******************************************************************
函数原型: WSD_AL_OSD_DrawBmp

功能描述: 把位图绘制到OSD指定位置

参	  数: 
	xStart(in): 起点横坐标
	yStart(in): 起点纵坐标
	Zoom(in)  : 缩放比例,预留使用
	FileName(in): 文件路径
	
返 回 值:  
	D_SUCCESS: 成功
	D_FAILURE: 失败
	
注	  意: 
    该接口只支持bmp图片，调用该函数以后，要调用WSD_AL_OSD_Update函数同步到输出
******************************************************************/
D_INT32 WSD_AL_OSD_DrawBmp(D_INT32 xStart, D_INT32 yStart, D_INT32 Zoom, D_UINT8 *FileName);


/******************************************************************
函数原型: WSD_AL_OSD_DrawPic

功能描述: 把图片绘制到OSD指定位置

参	  数: 
	xStart(in): 起点横坐标
	yStart(in): 起点纵坐标
	Zoom(in)  : 缩放比例,预留使用
	FileName(in): 文件路径
	
返 回 值:  
	D_SUCCESS: 成功
	D_FAILURE: 失败
	
注	  意: 
	该接口支持bmp、JPEG、PNG、GIF 图片，调用该函数以后，要调用WSD_AL_OSD_Update函数同步到输出
******************************************************************/
D_INT32 WSD_AL_OSD_DrawPic(D_INT32 xStart, D_INT32 yStart, D_INT32 Zoom, D_UINT8 *FileName);



/******************************************************************
函数原型: WSD_AL_OSD_DrawBmpBuffer

功能描述: 把内存中的位图绘制到OSD指定位置

参	  数: 
	xStart(in): 起点横坐标
	yStart(in): 起点纵坐标
	Zoom(in)  : 缩放比例,预留使用
	pBuffer(in): 位图内容指针
	
返 回 值:  
	D_SUCCESS: 成功
	D_FAILURE: 失败
	
注	  意: 
    该接口只支持bmp图片，调用该函数以后，要调用WSD_AL_OSD_Update函数同步到输出
******************************************************************/
D_INT32 WSD_AL_OSD_DrawBmpBuffer(D_INT32 xStart, D_INT32 yStart, D_INT32 Zoom, D_UINT8 *pBuffer);


/******************************************************************
函数原型: WSD_AL_OSD_DrawPicBuffer

功能描述: 把内存中的图片绘制到OSD指定位置

参	  数: 
	xStart(in): 起点横坐标
	yStart(in): 起点纵坐标
	Zoom(in)  : 缩放比例,预留使用
	pBuffer(in):图片内容指针
	Size(in): 位图内容长度
	
返 回 值:  
	D_SUCCESS: 成功
	D_FAILURE: 失败
	
注	  意: 
    该接口支持bmp、JPEG、PNG、GIF 图片，调用该函数以后，要调用WSD_AL_OSD_Update函数同步到输出
******************************************************************/
D_INT32 WSD_AL_OSD_DrawPicBuffer(D_INT32 xStart, D_INT32 yStart, D_INT32 Zoom, D_UINT8 *pBuffer, D_INT32 Size);


/******************************************************************
函数原型: WSD_AL_OSD_GetAddr

功能描述: 得到OSD buffer的地址,得到该地址后可直接操作OSD buffer，
          可完全控制OSD显示,提供足够的灵活性；

参	  数: 
	X(in): 横坐标
	Y(in): 纵坐标
	pString(in): 字体数据
	fColor(in): 前景色
	bColor(in): 背景色
	
返 回 值:  
	非NULL: 成功
	NULL  : 失败
	
注	  意: 
	对OSD buffer操作以后，要调用WSD_AL_OSD_Update函数同步到输出
******************************************************************/
D_UINT8* WSD_AL_OSD_GetAddr(D_VOID);


/******************************************************************
函数原型: WSD_AL_OSD_CopyToScreen

功能描述: 把内存数据拷贝到指定的OSD区域

参	  数: 
	X(in): 横坐标
	Y(in): 纵坐标
	pBuf(in): 内存数据地址指针
	Width(in): 内存数据的宽度
	Height(in): 内存数据的高度
	
返 回 值:  
	D_SUCCESS: 成功
	D_FAILURE: 失败
	
注	  意: 
	使用该函数以后，要调用WSD_AL_OSD_Update函数同步到输出
******************************************************************/
D_INT32 WSD_AL_OSD_CopyToScreen(D_INT32 X, D_INT32 Y, D_INT8 *pBuf, D_INT32 Width, D_INT32 Height);


/******************************************************************
函数原型: WSD_AL_OSD_Update

功能描述: 把OSD buffer数据同步到输出端口

参	  数: 无
	
返 回 值:  
	D_SUCCESS: 成功
	D_FAILURE: 失败
	
注	  意: 
******************************************************************/
D_INT32 WSD_AL_OSD_Update(D_VOID);

/******************************************************************
函数原型: WSD_AL_OSD_UpdateWithEgl

功能描述: 把OSD buffer混合OSD egl数据到输出端口

参	  数: 
	eglTopOfOsd: 0: egl内容在OSD buffer之下， 1: egl内容在OSD buffer之上


返 回 值:
	D_SUCCESS: 成功
	D_FAILURE: 失败

注	  意:
******************************************************************/
D_INT32 WSD_AL_OSD_UpdateWithEgl(D_BOOL eglTopOfOsd);

/******************************************************************
函数原型: WSD_AL_OSD_InitEgl

功能描述: OSD Opengl 初始化函数

参    数:
	width: OSD opengl 宽
	height: OSD opengl 高

返 回 值:
    D_SUCCESS: 成功
    D_FAILURE: 失败

注    意:
    在使用opengl函数之前，需要调用此函数进行初始化。
******************************************************************/
D_INT32 WSD_AL_OSD_InitEgl(D_INT32 width, D_INT32 height);


/******************************************************************
函数原型: WSD_AL_OSD_GetEglContent

功能描述: 获取OpenGLBuffer内容

参    数:

返 回 值:
    D_SUCCESS: 成功
    D_FAILURE: 失败

注    意:
******************************************************************/
D_INT32 WSD_AL_OSD_GetEglContent(D_INT32 x, D_INT32 y, D_INT32 width, D_INT32 height, D_UINT8* buff);
#ifdef __cplusplus
}
#endif

#endif
