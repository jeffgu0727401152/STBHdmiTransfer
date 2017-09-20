#ifndef __HSDEF_H__
#define __HSDEF_H__


#ifndef BOOL
#define BOOL int
#endif

#ifndef FALSE
#define FALSE 0
#endif

#ifndef TRUE
#define TRUE 1
#endif

#ifndef BUILD_WEBKIT
#ifndef bool
#define bool BOOL
#endif
#ifndef false
#define false FALSE
#endif

#ifndef true
#define true TRUE
#endif
#endif

#ifndef NULL
#define NULL 0
#endif

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;

typedef unsigned int uint32_t;
#define HAVE_UINT32_T 1
typedef  unsigned long long uint64_t;
typedef  long long int64_t;

#ifndef UInt8
typedef unsigned char       	UInt8;
typedef unsigned short     	UInt16;
typedef unsigned int        	UInt32;
#endif

/* used by hsdtv */
#ifndef BYTE
typedef unsigned char       	BYTE;
typedef unsigned short     	UINT16;
typedef unsigned int        	UINT32;
/*typedef unsigned long long  UINT64;*/
typedef short      		INT16;
typedef int        		INT32;
/*typedef long long  		INT64;*/
typedef unsigned short     	WORD;
typedef unsigned int        	DWORD;

typedef unsigned long		ULONG;
typedef unsigned char       	UCHAR;
#endif

#ifndef MAX
#define MAX(a,b)        (((a) > (b)) ? (a) : (b))
#define MIN(a,b)        (((a) < (b)) ? (a) : (b))
#define ABS(a)          (((a) > 0  ) ? (a) : (-(a)))
#endif

#define STREQ(a,b)      (strcmp((a),(b))==0)
#define STRNEQ(a,b,c)   (strncmp((a),(b),(c))==0)
#define EOS             '\0'
#define TAB             '\t'
#define SPACE           ' '
#define DONT_CARE (CHAR) -1

#define _1K10     1000
#define _1M10 (_1K10 * _1K10)

#define _1K2     1024
#define _1M2 (_1K2 * _1K2)

#define _1_SEC  1000  /*1000 yanliting modify 081020*/
#define _1_MIN  (_1_SEC * 60)
#define _1_HOUR (_1_MIN * 60)

#endif



