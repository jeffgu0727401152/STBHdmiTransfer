#pragma once

#include "types.h"
#include "SimpleString.h"
#include "Buffer.h"
#include "PtrControl.h"

#define TEXT_DIRECT_NORMAL	0x00000000
#define TEXT_DIRECT_HCENTER	0x00000001
#define TEXT_DIRECT_LEFT 	0x00000002
#define TEXT_DIRECT_RIGHT	0x00000004
#define TEXT_DIRECT_VCENTER	0x00000008
#define TEXT_DIRECT_TOP 	0x00000010
#define TEXT_DIRECT_BOTTOM	0x00000020

typedef struct tagSYSTEMTIME
{
  int tm_sec;			/* Seconds.	[0-60] (1 leap second) */
  int tm_min;			/* Minutes.	[0-59] */
  int tm_hour;			/* Hours.	[0-23] */
  int tm_mday;			/* Day.		[1-31] */
  int tm_mon;			/* Month.	[0-11] */
  int tm_year;			/* Year	- 1900.  */
  int tm_wday;			/* Day of week.	[0-6] */
  int tm_yday;			/* Days in year.[0-365]	*/
} SYSTEMTIME;


#pragma pack(push)
#pragma pack(1)
typedef struct tagUUID
{
	UINT32 u1;
	UINT16 u2;
	UINT16 u3;
	UINT16 u4;
	UINT16 u5;
	UINT32 u6;
} UUID;
#pragma pack(pop)

FILE *vpopen(
	const char* cmdstring,
	const char *type);
int vpclose(
	FILE *fp);

int getlwpid();

void GetPidListByName(
	const char* cProcessName,
	CPtrCtrl *pPidList);
void KillPidByName(
	const char* cProcessName);

void GetPidListByNameWithParam(
	const char* cProcessNameWithParam,
	CPtrCtrl *pPidList);
void KillPidByNameWithParam(
	const char* cProcessNameWithParam);

// 注意，
// 1. 在android系统上，很多命令需要 busybox支持才能执行
// 2. pResultString != NULL使用管道机制获取返回信息, pResultString==NULL 使用 system 命令执行
void do_syscmd(
	CSimpleStringA *pResultString,
	const char *fmt,
	...);

BOOL GetAttrValueFromConfig(
	const CSimpleStringA* pConfigString,
	const char* cAttrName,
	CSimpleStringA *pAttrValue);
void SetAttrValueToConfig(
	CSimpleStringA* pConfigString,
	const char* cAttrName,
	const char* cAttrValue);

// ms
UINT64 GetTickCount();
// us
UINT64 GetTickCountUS();
void Sleep(
	UINT64 uMiliSeconds);
void USleep(
	UINT64 uMicroSeconds);

int IncreaseToPowerOf(
	int nCurValue,
	int nPowerBase);
int DecreaseToPowerOf(
	int nCurValue,
	int nPowerBase);
int GetNearestPowerOf(
	int nCurValue,
	int nPowerBase);
double Distance(
	double x1,
	double y1,
	double x2,
	double y2);

BOOL PtInRect(
	const RECT *prc,
	POINT pt);
void UnionRect(
	RECT *prcDst,
	const RECT *prcSrc1,
	const RECT *prcSrc2);
void SetRectXY(
	RECT *prc,
	int left,
	int top,
	int width,
	int height);
void GetRelativeRect(
	RECT *prcDst,
	const RECT *prcSrc);
void ScaleRect(
	RECT *prc,
	float fXScale,
	float fYScale);
void InflatRect(
	RECT *prc,
	int nWidth,
	int nHeight);
BOOL IsRectEmpty(
	const RECT *prc);
BOOL IsRectEqual(
	const RECT *prc1,
	const RECT *prc2);
void BoundRect(
	RECT *prcDst,
	const RECT *prcSrc,
	const RECT *prcBound);
// cRectString: format(x,y,w,h)
BOOL ParserRectFromString(
	const char *cRectString,
	RECT *pRect);

const BYTE *BufFindPatt(
	const BYTE *pBuf,
	int nBufLen,
	const BYTE *pPatt,
	int nPattlen,
	int nStep);

const char *MemFindBufA(
	const char *cText,
	int nTextLen,
	const char *cPatt,
	int nPattlen);

const wchar_t *MemFindBufW(
	const wchar_t *wszText,
	int nTextLen,
	const wchar_t *wszPatt,
	int nPattlen);

const char *MemFindChrA(
	const char *cBuffer,
	char chr,
	int nBufferLength);

const wchar_t *MemFindChrW(
	const wchar_t *wszBuffer,
	wchar_t chr,
	int nBufferLength);

int StrMaxSameLengthA(
	const char *cStr1,
	const char *cStr2,
	BOOL bIgnoreCase);

void ConvertLongToCharW(
	long number,
	wchar_t *wszNumber,
	int numbers,
	int radix);

void ConvertLongToCharA(
	long number,
	char *cNumber,
	int numbers,
	int radix);

void PrintHexBuffer(
	const void *pBuffer,
	int nLength,
	int CountPerLine);

void ByteToHexA(
	BYTE b,
	char* cHex);

void ByteToHexW(
	BYTE b,
	wchar_t* wszHex);

void BufferToHexStringA(
	const BYTE* pBuffer,
	int nBufferLen,
	CSimpleStringA *pString);

void BufferToHexStringW(
	const BYTE* pBuffer,
	int nBufferLen,
	CSimpleStringW *pString);

BYTE HexStringToByteA(
	const char *cHex);

BYTE HexStringToByteW(
	const wchar_t *wszHex);

UINT32 HexStringToUint32A(
	const char *cHex);

UINT32 HexStringToUint32W(
	const wchar_t *wszHex);

UINT64 HexStringToUint64A(
	const char *cHex);

UINT64 HexStringToUint64W(
	const wchar_t *wszHex);

void HexStringToBufferA(
	const char *cHex,
	int nHexLen,
	CBuffer *pBuffer);

void HexStringToBufferW(
	const wchar_t *wszHex,
	int nHexLen,
	CBuffer *pBuffer);

void HexStringToStringA(
	const char *cHex,
	int nHexLen,
	CSimpleStringA *pString);

void HexStringToStringW(
	const wchar_t *wszHex,
	int nHexLen,
	CSimpleStringA *pString);

BOOL FindStringFromStringWithSeprator(
	const char* cFindFrom,
	int nFindFromLen,
	const char* cTobeFind,
	int nTobeFindLen,
	const char* cSeprators,
	int nSepratorCount);

// call Internal_DelArray to free return value
// sample :
// TCHAR *szString = "a@b.com,c@d.com;e@f.com;"
// CPtrCtrl sDevideList ;
// TCHAR *szDevString = DevideStringByCharList(szString, -1, ",;", 2, &sDevideList, -1) ;
// int i, nCount = sDevideList.GetCount() ;
// for (i = 0 ; i < nCount ; i++)
// {
//		TCHAR *szName = (TCHAR *)sDevideList.GetAt(i) ;
//		printf("%s ", szName) ;
//	}
// Internal_DelArray(szDevString) ;
//
// result is : a@b.com c@d.com e@f.com
// nMaxDevideCount: <=0, devide all by charlist; >0, only nMaxDevideCount string in return
const char* DevideStringByCharListA(
	const  char *cString,
	int nLength,
	const char *cCharList,
	int nListCount,
	BOOL bSkipRepeat,
	CPtrCtrl *pDevideList,
	int nMaxDevideCount);

const wchar_t* DevideStringByCharListW(
	const wchar_t *wszString,
	int nLength,
	const wchar_t *wszCharList,
	int nListCount,
	BOOL bSkipRepeat,
	CPtrCtrl *pDevideList,
	int nMaxDevideCount);

// call Internal_DelArray to free return value
const char* DevideStringByStringListA(
	const char *cString,
	int nLength,
	const char **cStringList,
	int nListCount,
	CPtrCtrl *pDevideList) ;

const wchar_t* DevideStringByStringListW(
	const wchar_t *wszString,
	int nLength,
	const wchar_t **wszStringList,
	int nListCount,
	CPtrCtrl *pDevideList) ;

void Internal_DelArrayA(
	const char* cArray);

void Internal_DelArrayW(
	const wchar_t* wszArray);

void GetTextRectByDirect(
	RECT rcWnd,
	int nTextWidth,
	int nTextHeight,
	int nDirect,
	RECT *prcText);

void ConvertNumberToChineseNumber(
	int nNumber,
	wchar_t *wszChineseNumber,
	int nSize);

void GetProductID(
	char* cProductID,
	int nLength);

void ConvertTmToSystemTime(
	const struct tm *ptm,
	SYSTEMTIME *pst);

void ConvertSystemTimeToTm(
	const SYSTEMTIME *pst,
	struct tm *ptm);

void DumpSystemTime(
	const char *cTag,
	const SYSTEMTIME *pst);
void StringToSystemTime(
	const char* cTimeString,
	SYSTEMTIME *pst);

void CreateUUID_Random(
	UUID *pUUID);
void UUIDToString(
	UUID *pUUID,
	CSimpleStringA *pUUIDString);
