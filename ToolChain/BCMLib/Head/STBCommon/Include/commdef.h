/*
���ߣ�kyo wang
�����ʹ�ò������˴��룬�����뱣����ע�Ͳ���
*/
#ifndef __COMMON_DEFINE_HEADER__
#define __COMMON_DEFINE_HEADER__

#pragma GCC diagnostic ignored "-Waddress"

#ifndef UNREFERENCED_PARAMETER
#define UNREFERENCED_PARAMETER(P)          (P)
#endif

#ifndef NULL
#define NULL 0
#endif

#ifndef TRUE
#define TRUE 1
#endif 

#ifndef FALSE
#define FALSE 0
#endif 

#ifndef M_PI
#define M_PI       3.14159265358979323846
#endif

#define SIZE_1K		1024
#define SIZE_1M		(1024*1024)
#define SIZE_1G		(1024*1024*1024)
#define SIZE_1T		(((UINT64)SIZE_1M)*((UINT64)SIZE_1M))

#ifndef Get2Max
#define Get2Max(a,b)            (((a) > (b)) ? (a) : (b))
#endif

#ifndef Get2Min
#define Get2Min(a,b)            (((a) < (b)) ? (a) : (b))
#endif

#ifndef Get3Min
#define Get3Min(x1,x2,x3)	(((x1)<(x2)?(x1):(x2))<(x3)?((x1)<(x2)?(x1):(x2)):(x3))
#endif

#ifndef Get3Max
#define Get3Max(x1,x2,x3)	(((x1)>(x2)?(x1):(x2))>(x3)?((x1)>(x2)?(x1):(x2)):(x3))
#endif

#ifndef between
#define between(x, a, b)	((((x)>=(a))&&((x)<=(b)))||(((x)>=(b))&&((x)<=(a))))
#endif

#ifndef ALIGN4
#define ALIGN4(x)			((((UINT32)x)+3) & (0xFFFFFFFC))
#endif

#ifndef ALIGN8
#define ALIGN8(x)			((((UINT32)x)+7) & (0xFFFFFFF8))
#endif

#ifndef LIMITTOMAX
#define LIMITTOMAX(x, maxvalue)		((x) > (maxvalue) ? (maxvalue) : (x))
#endif

#ifndef LIMITTOBOUND
#define LIMITTOBOUND(x, l, h)	\
{								\
	if ((x) < (l))				\
	{							\
		(x)=(l);				\
	}							\
	else if ((x) > (h))			\
	{							\
		(x)=(h);				\
	} 							\
}
#endif

#ifndef INTERVAL
#define INTERVAL(a, b)			((a) < (b) ? ((b)-(a)) : ((a)-(b)))
#endif

#ifndef ENLARGETOTIMES
#define ENLARGETOTIMES(x, y)	(((x) % (y) == 0) ? (x) : ((x) + (y) - (x) % (y)))
#endif

#ifndef TRUNCTOTIMES
#define TRUNCTOTIMES(v, x)		(((v) / (x)) * (x))
#endif

#ifndef RECTWIDTH
#define RECTWIDTH(rc)			(((rc).right)-((rc).left))
#endif

#ifndef RECTHEIGHT
#define RECTHEIGHT(rc)			(((rc).bottom)-((rc).top))
#endif

#ifndef RECTWIDTHCENTER
#define RECTWIDTHCENTER(rc)		((((rc).left)+((rc).right))/2)
#endif

#ifndef RECTHEIGHTCENTER
#define RECTHEIGHTCENTER(rc)	((((rc).top)+((rc).bottom))/2)
#endif

// align to (sizeof(int))
#ifndef _INTSIZEOF
#define _INTSIZEOF(TYPE)		((sizeof(TYPE)+sizeof(int)-1) & ~(sizeof(int)-1))
#endif

#ifndef ROUND_POSITIVE
#define ROUND_POSITIVE(x)		((((double)(x)-(int)(x))>0.5)?((int)((x)+1)):((int)(x)))
#endif
#ifndef ROUND_NEGATIVE
#define ROUND_NEGATIVE(x)		((((int)(x)-(double)(x))>0.5)?((int)((x)-1)):((int)(x)))
#endif

#ifndef ROUND
#define ROUND(x)				(((x)>0) ? ROUND_POSITIVE(x) : ROUND_NEGATIVE(x))
#endif

#ifndef OFFSETOF
#define OFFSETOF(s,m)			((size_t)&(((s*)0)->m))
#endif

#ifndef MEMBERSIZE
#define MEMBERSIZE(type, member) sizeof(((type *)0)->member)
#endif

#ifndef ARRAYSIZE
#define ARRAYSIZE(a)			(sizeof(a)/sizeof(a[0])) 
#endif

#ifndef MULDIV
#define MULDIV(a,b,c)			(((a)*(b))/(c))
#endif

#ifndef BMP_LINE_WIDTH
#define BMP_LINE_WIDTH(nImageWidth, nBitCount) (2 * 2 * (((nImageWidth) * (nBitCount) + 31) >> 5))
#endif

#ifndef BMP_RGBDATA_SIZE
#define BMP_RGBDATA_SIZE(nImageWidth, nImageHeight, nBitCount) (BMP_LINE_WIDTH(nImageWidth, nBitCount)*(nImageHeight))
#endif

//((x) < (0) ? (0) : ((x) > (255) ? (255) : (x)))	
#ifndef LIMITUNCHAR
#define LIMITUNCHAR(x_int, c_char)	\
{									\
	if ((x_int) < 0)				\
	{								\
		(c_char)=0x00;				\
	}								\
	else if ((x_int) > 0xFF)		\
	{								\
		(c_char)=0xFF;				\
	} 								\
	else							\
	{								\
		(c_char)=(BYTE)(x_int);		\
	}								\
}
#endif

#ifndef MAKEUINT32
#define MAKEUINT32(a,b,c,d)	((UINT32)(\
	(((UINT32)((BYTE)(a))) << 0) | \
	(((UINT32)((BYTE)(b))) << 8) | \
	(((UINT32)((BYTE)(c))) << 16) | \
	(((UINT32)((BYTE)(d))) << 24) \
	))
#endif

#ifndef GETUINT32_BYTE3
#define GETUINT32_BYTE3(x)	((BYTE)(((x)&0xFF000000) >> 24))
#endif

#ifndef GETUINT32_BYTE2
#define GETUINT32_BYTE2(x)	((BYTE)(((x)&0x00FF0000) >> 16))
#endif

#ifndef GETUINT32_BYTE1
#define GETUINT32_BYTE1(x)	((BYTE)(((x)&0x0000FF00) >> 8))
#endif

#ifndef GETUINT32_BYTE0
#define GETUINT32_BYTE0(x)	((BYTE)(((x)&0x000000FF)))
#endif

#ifndef LOWORD
#define LOWORD(x) (((UINT32)x) & 0x0000FFFF)
#endif

#ifndef HIWORD
#define HIWORD(x) ((((UINT32)x) & 0xFFFF0000) >> 16)
#endif

#ifndef POINTTOUINT32
#define POINTTOUINT32(pt) ((UINT32)((((pt.x) & 0x0000FFFF) | (((pt.y)<<16)&0xFFFF0000))))
#endif

#ifndef ISVALID_HANDLE
#define ISVALID_HANDLE(x)	(((x) && ((x) != INVALID_HANDLE_VALUE)) ? TRUE : FALSE)
#endif

#ifndef ISVALID_SOCKET
#define ISVALID_SOCKET(x)	(((x) && ((x) > 0)) ? TRUE : FALSE)
#endif

#ifndef	SAFE_RELEASE
#define SAFE_RELEASE(x)   				\
{										\
    if (x)                				\
    {                       			\
        (x)->Release();       			\
        (x) = NULL;           			\
    }									\
}
#endif

#ifndef SAFE_ADDREF
#define SAFE_ADDREF(x)    				\
{										\
    if (x)                				\
    {                       			\
        (x)->AddRef();        			\
    }									\
}
#endif

#ifndef SAFE_FREE
#define SAFE_FREE(x)    				\
{										\
    if (x)                				\
    {                       			\
        free(x);           				\
        (x) = NULL;          			\
    }									\
}
#endif

#ifndef SAFE_DELETE
#define SAFE_DELETE(x)    				\
{										\
    if (x)                				\
    {                       			\
        delete (x);           			\
        (x) = NULL;          			\
    }									\
}
#endif

#ifndef SAFE_DELETEARRAY
#define SAFE_DELETEARRAY(x)   			\
{										\
    if (x)                    			\
    {                           		\
        delete[] (x);             		\
        (x) = NULL;               		\
    }									\
}
#endif

#ifndef SAFE_CLOSEFILE
#define SAFE_CLOSEFILE(x)						\
{												\
	if (x)										\
	{											\
		fclose(x);								\
		(x) = NULL;								\
	}											\
}
#endif

#ifndef SAFE_CLOSESOCKET
#define SAFE_CLOSESOCKET(h)				\
{										\
	if (ISVALID_SOCKET(h))				\
	{									\
		closesocket(h);				\
		(h) = NULL;					\
	}									\
}
#endif

#ifndef	SAFE_POINTER_SETVALUE
#define SAFE_POINTER_SETVALUE(p, v)  	\
{										\
	if (p)                				\
	{                       			\
		*(p) = (v);						\
	}									\
}
#endif

#ifndef	SAFE_STRNCPY
#define SAFE_STRNCPY(dst, src, dstBufLen)  					\
{															\
	if ((dst) && (src))   				    				\
	{                       								\
	    if ((dstBufLen) > 1)								\
	    {													\
	    	int nSrcLen = strlen(src);						\
	    	int nCopyLen = Get2Min(((int)(dstBufLen-1)), nSrcLen);	\
			memmove((dst), (src), nCopyLen);				\
			(dst)[nCopyLen] = '\0';   						\
		}													\
		else												\
		{													\
			(dst)[0] = '\0';								\
		}													\
	}														\
	else if(dst)											\
	{				                  						\
		(dst)[0] = '\0';         							\
	}														\
}
#endif

#ifndef	SAFE_WCSNCPY
#define SAFE_WCSNCPY(dst, src, dstBufLen)  					\
{															\
	if ((dst) && (src))   				    				\
	{                       								\
	    if ((dstBufLen) > 0)								\
	    {													\
	    	int nSrcLen = wcslen(src);						\
	    	int nCopyLen = Get2Min(((int)(dstBufLen-1)), nSrcLen);	\
			memmove((dst), (src), nCopyLen*sizeof(wchar_t));\
			(dst)[nCopyLen] = L'\0';   						\
		}													\
		else												\
		{													\
			(dst)[0] = L'\0';								\
		}													\
	}														\
	else if(dst)											\
	{				                   						\
		(dst)[0] = L'\0';         							\
	}														\
}
#endif

#ifdef _UNICODE
#define SAFE_TCSNCPY	SAFE_WCSNCPY
#else
#define SAFE_TCSNCPY	SAFE_STRNCPY
#endif

#ifndef SKIP_WCHARLIST_DOWN
#define SKIP_WCHARLIST_DOWN(pBuffer, pBufEnd, wcCharArray, nCount)\
{																\
	while ((pBuffer) < (pBufEnd))								\
	{															\
		WCHAR wc = *(pBuffer);									\
		int i;													\
		for ( i = 0; i < (nCount); i++ )						\
		{														\
			if (wc == (wcCharArray)[i])							\
			{													\
				(pBuffer) ++;									\
				break;											\
			}													\
		}														\
		if ( i == (nCount) )									\
		{														\
			break;												\
		}														\
	}															\
}
#endif

#ifndef SKIP_WCHARLIST_UP
#define SKIP_WCHARLIST_UP(pBuffer, pBufStart, wcCharArray, nCount)\
{																\
	while ((pBuffer) > (pBufStart))								\
	{															\
		WCHAR wc = *(pBuffer);									\
		int i;													\
		for ( i = 0; i < (nCount); i++ )						\
		{														\
			if (wc == (wcCharArray)[i])							\
			{													\
				(pBuffer) --;									\
				break;											\
			}													\
		}														\
		if ( i == (nCount) )									\
		{														\
			break;												\
		}														\
	}															\
}
#endif

#ifndef SKIP_WCHAR_DOWN
#define SKIP_WCHAR_DOWN(pBuffer, pBufEnd, wcChar)		\
{														\
	WCHAR wcCharArray[1];								\
	wcCharArray[0] = (wcChar);							\
	SKIP_WCHARLIST_DOWN(pBuffer, pBufEnd, wcCharArray, 1);\
}
#endif

#ifndef SKIP_WCHAR_UP
#define SKIP_WCHAR_UP(pBuffer, pBufStart, wcChar)		\
{														\
	WCHAR wcCharArray[1];								\
	wcCharArray[0] = (wcChar);							\
	SKIP_WCHARLIST_UP(pBuffer, pBufStart, wcCharArray, 1);\
}
#endif

#ifndef SKIP_CHARLIST_DOWN
#define SKIP_CHARLIST_DOWN(pBuffer, pBufEnd, cCharArray, nCount)\
{																\
	while ((pBuffer) < (pBufEnd))								\
	{															\
		char c = *(pBuffer);									\
		int i;													\
		for ( i = 0; i < (nCount); i++ )						\
		{														\
			if (c == (cCharArray)[i])							\
			{													\
				(pBuffer) ++;									\
				break;											\
			}													\
		}														\
		if ( i == (nCount) )									\
		{														\
			break;												\
		}														\
	}															\
}
#endif

#ifndef SKIP_CHARLIST_UP
#define SKIP_CHARLIST_UP(pBuffer, pBufStart, cCharArray, nCount)\
{																\
	while ((pBuffer) > (pBufStart))								\
	{															\
		char c = *(pBuffer);									\
		int i;													\
		for ( i = 0; i < (nCount); i++ )						\
		{														\
			if (c == (cCharArray)[i])							\
			{													\
				(pBuffer) --;									\
				break;											\
			}													\
		}														\
		if ( i == (nCount) )									\
		{														\
			break;												\
		}														\
	}															\
}
#endif

#ifndef SKIP_CHAR_DOWN
#define SKIP_CHAR_DOWN(pBuffer, pBufEnd, cChar)			\
{														\
	char cCharArray[1];								\
	cCharArray[0] = (cChar);							\
	SKIP_CHARLIST_DOWN(pBuffer, pBufEnd, cCharArray, 1);\
}
#endif

#ifndef SKIP_CHAR_UP
#define SKIP_CHAR_UP(pBuffer, pBufStart, cChar)			\
{														\
	char cCharArray[1];								\
	cCharArray[0] = (cChar);							\
	SKIP_CHARLIST_UP(pBuffer, pBufStart, cCharArray, 1);\
}
#endif

#ifndef EQUAL_POINT
#define EQUAL_POINT(pt1, pt2) ((((pt1)->x) == ((pt2)->x) && ((pt1)->y) == ((pt2)->y)) ? TRUE : FALSE)
#endif

#ifndef IsRectIntersect
#define IsRectIntersect(prc1, prc2) \
	(((prc1)->left < (prc2)->right) && \
	((prc1)->right > (prc2)->left) && \
	((prc1)->top < (prc2)->bottom) && \
	((prc1)->bottom > (prc2)->top))
#endif

#ifndef IsRectInRect
#define IsRectInRect(prc1, prc2) \
	(((prc1)->left >= (prc2)->left) && \
	((prc1)->right <= (prc2)->right) && \
	((prc1)->top >= (prc2)->top) && \
	((prc1)->bottom <= (prc2)->bottom))
#endif

#endif //__COMMON_DEFINE_HEADER__
