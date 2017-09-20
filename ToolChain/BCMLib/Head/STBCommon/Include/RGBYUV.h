/*
���ߣ�kyo wang
�����ʹ�ò������˴��룬�����뱣����ע�Ͳ���
*/
#ifndef __RGBYUV_HEADER__
#define __RGBYUV_HEADER__

#include "types.h"

#ifndef GetRValue
#define GetRValue(rgb)      ((BYTE)(rgb))
#endif

#ifndef GetGValue
#define GetGValue(rgb)      ((BYTE)(((UINT16)(rgb)) >> 8))
#endif

#ifndef GetBValue
#define GetBValue(rgb)      ((BYTE)((rgb)>>16))
#endif

#ifndef GETRGB555BValue
#define GETRGB555BValue(rgb)	((BYTE) (((((UINT16)(rgb))&0x7C00))>>7))
#endif

#ifndef GETRGB555GValue
#define GETRGB555GValue(rgb)	((BYTE) (((((UINT16)(rgb))&0x03E0))>>2))
#endif

#ifndef GETRGB555RValue
#define GETRGB555RValue(rgb)	((BYTE) (((((UINT16)(rgb))&0x001F))<<3))
#endif

#ifndef RGB555
#define RGB555(r, g, b)       \
	((UINT16)((((BYTE)(r))>>3) | \
	(((UINT16)(((BYTE)(g))>>3))<<5) | \
	(((UINT16)(((BYTE)(b))>>3))<<10)))
#endif

#ifndef RGB555TODWORD
#define RGB555TODWORD(r1, g1, b1, r2, g2, b2)       \
	((UINT32)((((UINT32)(((BYTE)(r1))>>3))<<0)  | \
	(((UINT32)(((BYTE)(g1))>>3))<<5)  | \
	(((UINT32)(((BYTE)(b1))>>3))<<10) | \
	(((UINT32)(((BYTE)(r2))>>3))<<16) | \
	(((UINT32)(((BYTE)(g2))>>3))<<21) | \
	(((UINT32)(((BYTE)(b2))>>3))<<26)))
#endif

#ifndef GETRGB565BValue
#define GETRGB565BValue(rgb)	((BYTE) (((((UINT16)(rgb))&0xF800))>>8))
#endif

#ifndef GETRGB565GValue
#define GETRGB565GValue(rgb)	((BYTE) (((((UINT16)(rgb))&0x07E0))>>3))
#endif

#ifndef GETRGB565RValue
#define GETRGB565RValue(rgb)	((BYTE) (((((UINT16)(rgb))&0x001F))<<3))
#endif

#ifndef RGB
#define RGB(r, g, b)   ((UINT32)((BYTE)(r) | ((BYTE)(g << 8)) | ((BYTE)(b << 16))))
#endif

#ifndef RGB565
#define RGB565(r, g, b)       \
	((UINT16)((((BYTE)(r))>>3) | \
	(((UINT16)(((BYTE)(g))>>2))<<5) | \
	(((UINT16)(((BYTE)(b))>>3))<<11)))
#endif

#ifndef RGB565TODWORD
#define RGB565TODWORD(r1, g1, b1, r2, g2, b2)       \
	((UINT32)((((UINT32)(((BYTE)(r1))>>3))<<0)  | \
	(((UINT32)(((BYTE)(g1))>>2))<<5)  | \
	(((UINT32)(((BYTE)(b1))>>3))<<11) | \
	(((UINT32)(((BYTE)(r2))>>3))<<16) | \
	(((UINT32)(((BYTE)(g2))>>2))<<21) | \
	(((UINT32)(((BYTE)(b2))>>3))<<27)))
#endif

#ifndef GETRGB666BValue
#define GETRGB666BValue(rgb)	((BYTE) (((((UINT32)(rgb))&0x003F))<<2))
#endif

#ifndef GETRGB666GValue
#define GETRGB666GValue(rgb)	((BYTE) (((((UINT32)(rgb))&0x00000FC00))>>4))
#endif

#ifndef GETRGB666RValue
#define GETRGB666RValue(rgb)	((BYTE) (((((UINT32)(rgb))&0x0003F000))>>10))
#endif

#ifndef RGB666
#define RGB666(r, g, b)		((UINT32)((((BYTE)(r))>>2) | ((UINT32)((((BYTE)(g))>>2)<<6)) | ((UINT32)(((((BYTE)(b))>>2)<<12)))
#endif

#ifndef RGB565_BGR565
#define RGB565_BGR565(rgb)		((UINT16)(((((UINT16)(rgb))&0xF800)>>11) | \
								((((UINT16)(rgb))&0x07E0)) | \
								((((UINT16)(rgb))&0x001F)<<11)	\
								))
#endif

#ifndef RGB555_BGR555
#define RGB555_BGR555(rgb)		((UINT16)(((((UINT16)(rgb))&0x7C00)>>10) | \
								((((UINT16)(rgb))&0x03E0)) | \
								((((UINT16)(rgb))&0x001F)<<10)	  \
								))
#endif

#ifndef RGB666_BGR666
#define RGB666_BGR666(rgb)		((UINT32)(((((UINT32)(rgb))&0x0000003F)<<12) | \
								((((UINT32)(rgb))&0x00000FC0)) | \
								((((UINT32)(rgb))&0x0003F000)>>12)   \
								))
#endif

#ifndef RGB888_BGR888
#define RGB888_BGR888(rgb)		((UINT32)(((((UINT32)(rgb))&0x000000FF)<<16) | \
								((((UINT32)(rgb))&0x0000FF00)) | \
								((((UINT32)(rgb))&0x00FF0000)>>16)   \
								))
#endif

#ifndef RGB555_RGB565
#define RGB555_RGB565(rgb)		((UINT16)(((((UINT16)(rgb))&0x7C00)<<1) | \
								((((UINT16)(rgb))&0x03E0)<<1) | \
								((((UINT16)(rgb))&0x001F))	  \
								))
#endif

#ifndef RGB565_RGB555
#define RGB565_RGB555(rgb)		((UINT16)(((((UINT16)(rgb))&0xF800)>>1) | \
								((((UINT16)(rgb))&0x07C0)>>1) | \
								((((UINT16)(rgb))&0x001F))	  \
								))
#endif

#ifndef RGB888_RGB555
#define RGB888_RGB555(rgb)		((UINT16)(((((UINT32)(rgb))&0x000000F8)>>3) | \
								((((UINT32)(rgb))&0x0000F800)>>6) | \
								((((UINT32)(rgb))&0x00F80000)>>9)   \
								))
#endif

#ifndef RGB888_RGB565
#define RGB888_RGB565(rgb)		((UINT16)(((((UINT32)(rgb))&0x000000F8)>>3) | \
								((((UINT32)(rgb))&0x0000FC00)>>5) | \
								((((UINT32)(rgb))&0x00F80000)>>8)   \
								))
#endif

#ifndef RGB555_RGB888
#define RGB555_RGB888(rgb)		((UINT32)(((((UINT32)(rgb))&0x0000001F)<<3) | \
								((((UINT32)(rgb))&0x000003E0)<<6) | \
								((((UINT32)(rgb))&0x00007C00)<<9)   \
								))
#endif

#ifndef RGB565_RGB888
#define RGB565_RGB888(rgb)		((UINT32)(((((UINT32)(rgb))&0x0000001F)<<3) | \
								((((UINT32)(rgb))&0x000007E0)<<5) | \
								((((UINT32)(rgb))&0x0000F800)<<8)   \
								))
#endif

// 555<->666 FORMAT
#ifndef RGB_SAME_555_666
#define RGB_SAME_555_666(rgb)	((UINT32)(((((UINT32)(rgb))&0x00007C00)<<3) | \
								((((UINT32)(rgb))&0x000003E0)<<2) | \
								((((UINT32)(rgb))&0x0000001F)<<1)	\
								))
#endif

#ifndef RGB_INVERT_555_666
#define RGB_INVERT_555_666(rgb)	((UINT32)(((((UINT32)(rgb))&0x00007C00)>>9) | \
								((((UINT32)(rgb))&0x000003E0)<<2) | \
								((((UINT32)(rgb))&0x0000001F)<<13)	\
								))
#endif

#ifndef RGB_SAME_666_555
#define RGB_SAME_666_555(rgb)	((UINT16)(((((UINT32)(rgb))&0x0003E000)>>3) | \
								((((UINT32)(rgb))&0x00000F80)>>2) | \
								((((UINT32)(rgb))&0x0000003E)>>1)   \
								))
#endif

#ifndef RGB_INVERT_666_555
#define RGB_INVERT_666_555(rgb)	((UINT16)(((((UINT32)(rgb))&0x0003E000)>>13) | \
								((((UINT32)(rgb))&0x00000F80)>>2) | \
								((((UINT32)(rgb))&0x0000003E)<<9)   \
								))
#endif
// 555<->666 FORMAT

// 666<->565 FORMAT
#ifndef RGB_INVERT_565_666
#define RGB_INVERT_565_666(rgb)	((UINT32)(((((UINT32)(rgb))&0x0000F800)>>10) | \
								((((UINT32)(rgb))&0x000007E0)<<1) | \
								((((UINT32)(rgb))&0x0000001F)<<13)	\
								))
#endif

#ifndef RGB_SAME_565_666
#define RGB_SAME_565_666(rgb)	((UINT32)(((((UINT32)(rgb))&0x0000F800)<<2) | \
								((((UINT32)(rgb))&0x000007E0)<<1) | \
								((((UINT32)(rgb))&0x0000001F)<<1)	\
								))
#endif

#ifndef RGB_INVERT_666_565
#define RGB_INVERT_666_565(rgb)	((UINT16)(((((UINT32)(rgb))&0x0003E000)>>13) | \
								((((UINT32)(rgb))&0x00000FC0)>>1) | \
								((((UINT32)(rgb))&0x0000003E)<<10)   \
								))
#endif

#ifndef RGB_SAME_666_565
#define RGB_SAME_666_565(rgb)	((UINT16)(((((UINT32)(rgb))&0x0003E000)>>2) | \
								((((UINT32)(rgb))&0x00000FC0)>>1) | \
								((((UINT32)(rgb))&0x0000003E)>>1)	\
								))
#endif
// 666<->565 FORMAT

// 666<->888 FORMAT
#ifndef RGB_INVERT_888_666
#define RGB_INVERT_888_666(rgb)	((UINT32)(((((UINT32)(rgb))&0x00FC0000)>>18) | \
								((((UINT32)(rgb))&0x0000FC00)>>4) | \
								((((UINT32)(rgb))&0x000000FC)<<10)   \
								))
#endif

#ifndef RGB_SAME_888_666
#define RGB_SAME_888_666(rgb)	((UINT32)(((((UINT32)(rgb))&0x00FC0000)>>6) | \
								((((UINT32)(rgb))&0x0000FC00)>>4) | \
								((((UINT32)(rgb))&0x000000FC)>>2)   \
								))
#endif

#ifndef RGB_SAME_666_888
#define RGB_SAME_666_888(rgb)	((UINT32)(((((UINT32)(rgb))&0x0000003F)<<2) | \
								((((UINT32)(rgb))&0x00000FC0)<<4) | \
								((((UINT32)(rgb))&0x0003F000)<<6)   \
								))
#endif

#ifndef RGB_INVERT_666_888
#define RGB_INVERT_666_888(rgb)	((UINT32)(((((UINT32)(rgb))&0x0000003F)<<18) | \
								((((UINT32)(rgb))&0x00000FC0)<<4) | \
								((((UINT32)(rgb))&0x0003F000)>>10)   \
								))
#endif
// 666<->888 FORMAT

/************************************************************************/
/* rgb <-> yuv function                                                 */
/************************************************************************/

	void InitLookupTable(
		void) ;


	void RGBToYUV(
		BYTE r,
		BYTE g,
		BYTE b,
		BYTE &y,
		BYTE &u,
		BYTE &v) ;


	void YUVToRGB(
		BYTE y,
		BYTE u,
		BYTE v,
		BYTE &r,
		BYTE &g,
		BYTE &b) ;


	void YUVToYUYV_422(
		int x_dim,
		int y_dim,
		const BYTE *yuv422,
		BOOL bYUVI422,
		BYTE *yuyv422) ;


	void YUYVToYUV_422(
		int x_dim,
		int y_dim,
		const BYTE *yuyv422,
		BYTE *yuv422,
		BOOL bYUVI422) ;


	void YUYV422ToYUV420(
		int x_dim,
		int y_dim,
		const BYTE *yuyv422,
		BYTE *yuv420,
		BOOL bYUVI420) ;


	void YUV422ToYUV420(
		int x_dim,
		int y_dim,
		const BYTE *yuv422,
		BOOL bYUVI422,
		BYTE *yuv420,
		BOOL bYUVI420) ;


	void YUV420ToYUV422(
		int x_dim,
		int y_dim,
		const BYTE *yuv420,
		BOOL bYUVI420,
		BYTE *yuv422,
		BOOL bYUVI422) ;


	void RGB888ToYUV420(
		int x_dim,
		int y_dim,
		const BYTE *rgb888,
		BYTE *yuv420,
		BOOL bYUVI420,
		int nRGBStride,
		BOOL bBGROrder) ;


	void YUV420ToRGB888(
		int x_dim,
		int y_dim,
		const BYTE *yuv420,
		BOOL bYUVI420,
		BYTE *rgb888,
		int nRGBStride,
		BOOL bBGROrder) ;


	void RGB555ToYUV420(
		int x_dim,
		int y_dim,
		const BYTE *rgb555,
		BYTE *yuv420,
		BOOL bYUVI420,
		int nRGBStride,
		BOOL bBGROrder) ;


	void YUV420ToRGB555(
		int x_dim,
		int y_dim,
		const BYTE *yuv420,
		BOOL bYUVI420,
		BYTE *rgb555,
		int nRGBStride,
		BOOL bBGROrder) ;


	void RGB565ToYUV420(
		int x_dim,
		int y_dim,
		const BYTE *rgb565,
		BYTE *yuv420,
		BOOL bYUVI420,
		int nRGBStride,
		BOOL bBGROrder) ;


	void YUV420ToRGB565(
		int x_dim,
		int y_dim,
		const BYTE *yuv420,
		BOOL bYUVI420,
		BYTE *rgb565,
		int nRGBStride,
		BOOL bBGROrder) ;


	void RGB888ToYUV422(
		int x_dim,
		int y_dim,
		const BYTE *rgb888,
		BYTE *yuv422,
		BOOL bYUVI422,
		int nRGBStride,
		BOOL bBGROrder) ;


	void YUV422ToRGB888(
		int x_dim,
		int y_dim,
		const BYTE *yuv422,
		BOOL bYUVI422,
		BYTE *rgb888,
		int nRGBStride,
		BOOL bBGROrder) ;


	void RGB555ToYUV422(
		int x_dim,
		int y_dim,
		const BYTE *rgb555,
		BYTE *yuv422,
		BOOL bYUVI422,
		int nRGBStride,
		BOOL bBGROrder) ;


	void YUV422ToRGB555(
		int x_dim,
		int y_dim,
		const BYTE *yuv422,
		BOOL bYUVI422,
		BYTE *rgb555,
		int nRGBStride,
		BOOL bBGROrder) ;


	void RGB565ToYUV422(
		int x_dim,
		int y_dim,
		const BYTE *rgb565,
		BYTE *yuv422,
		BOOL bYUVI422,
		int nRGBStride,
		BOOL bBGROrder) ;


	void YUV422ToRGB565(
		int x_dim,
		int y_dim,
		const BYTE *yuv422,
		BOOL bYUVI422,
		BYTE *rgb565,
		int nRGBStride,
		BOOL bBGROrder) ;


	void RGB888ToYUV444(
		int x_dim,
		int y_dim,
		const BYTE *rgb888,
		BYTE *yuv444,
		BOOL bYUVI444,
		int nRGBStride,
		BOOL bBGROrder) ;


	void YUV444ToRGB888(
		int x_dim,
		int y_dim,
		const BYTE *yuv444,
		BOOL bYUVI444,
		BYTE *rgb888,
		int nRGBStride,
		BOOL bBGROrder) ;


	void RGB565ToYUV444(
		int x_dim,
		int y_dim,
		const BYTE *rgb565,
		BYTE *yuv444,
		BOOL bYUVI444,
		int nRGBStride,
		BOOL bBGROrder) ;


	void YUV444ToRGB565(
		int x_dim,
		int y_dim,
		const BYTE *yuv444,
		BOOL bYUVI444,
		BYTE *rgb565,
		int nRGBStride,
		BOOL bBGROrder) ;


	void RGB555ToYUV444(
		int x_dim,
		int y_dim,
		const BYTE *rgb555,
		BYTE *yuv444,
		BOOL bYUVI444,
		int nRGBStride,
		BOOL bBGROrder) ;


	void YUV444ToBGR555(
		int x_dim,
		int y_dim,
		const BYTE *yuv444,
		BOOL bYUVI444,
		BYTE *rgb555,
		int nRGBStride,
		BOOL bBGROrder) ;


	void RGB565ToRGB555(
		int x_dim,
		int y_dim,
		const BYTE *rgb565,
		BYTE *rgb555,
		int n565Stride,
		int n555Stride,
		BOOL bBGROrder) ;


	void RGB555ToRGB565(
		int x_dim,
		int y_dim,
		const BYTE *rgb555,
		BYTE *rgb565,
		int n555Stride,
		int n565Stride,
		BOOL bBGROrder) ;


	void RGB888ToRGB565(
		int x_dim,
		int y_dim,
		const BYTE *rgb888,
		BYTE *rgb565,
		int n888Stride,
		int n565Stride,
		BOOL bBGROrder) ;


	void RGB565ToRGB888(
		int x_dim,
		int y_dim,
		const BYTE *rgb565,
		BYTE *rgb888,
		int n565Stride,
		int n888Stride,
		BOOL bBGROrder) ;


	void RGB888ToRGB555(
		int x_dim,
		int y_dim,
		const BYTE *rgb888,
		BYTE *rgb555,
		int n888Stride,
		int n555Stride,
		BOOL bBGROrder) ;


	void RGB555ToRGB888(
		int x_dim,
		int y_dim,
		const BYTE *rgb555,
		BYTE *rgb888,
		int n555Stride,
		int n888Stride,
		BOOL bBGROrder) ;

	

	void YUY2ToRGB888(
		int x_dim,
		int y_dim,
		const BYTE *yuv,
		BYTE *rgb888,
		int nRGBStride,
		BOOL bBGROrder) ;

	void YUY2ToARGB32(
		int x_dim,
		int y_dim,
		const BYTE *yuv,
		BYTE *argb32,
		int nRGBStride,
		int bBGROrder,
		const BYTE *alpha,
		int nAlphaStride);

	void YVY2ToRGB888(
		int x_dim,
		int y_dim,
		const BYTE *yuv,
		BYTE *rgb888,
		int nRGBStride,
		BOOL bBGROrder) ;

	void YVY2ToARGB32(
		int x_dim,
		int y_dim,
		const BYTE *yuv,
		BYTE *argb32,
		int nRGBStride,
		int bBGROrder,
		const BYTE *alpha,
		int nAlphaStride);

	void YUV420SPToYUV420(
		int width,
		int height,
		const BYTE* yuv420sp,
		BYTE* yuv420,
		BOOL bYUVI420);

	void YUV420ToYUV420SP(
		int width,
		int height,
		const BYTE* yuv420,
		BOOL bYUVI420,
		BYTE* yuv420sp);

/************************************************************************/
/* rgb <-> yuv function                                                 */
/************************************************************************/
#endif //__RGBYUV_HEADER__
