#pragma once

#include "Buffer.h"

BOOL InitSysLibCodeConvert();
void DeInitSysLibCodeConvert();

typedef enum eCHARSETTYPE
{
	CHARSETTYPE_UTF8=0,
	CHARSETTYPE_UNICODE,
	CHARSETTYPE_GB2312,
	CHARSETTYPE_BIG5,
	CHARSETTYPE_GBK
} CHARSETTYPE;

BOOL ConvertCharset(
	CHARSETTYPE eFromType,
	const CBuffer* pFromBuffer,
	CHARSETTYPE eToType,
	CBuffer* pToBuffer);

BOOL icu_mbstowcs(
	wchar_t* wszString,
	int nDstLength,
	const char* cString,
	int nSrcLength);
BOOL icu_wcstombs(
	char* cString,
	int nDstLength,
	const wchar_t* wszString,
	int nSrcLength);

void ConvertGB2312ToUTF8_File(
	const char* cGB2312File,
	const char* cUTF8File);
void ConvertGB2312ToUTF8_Folder(
	const char* cGB2312Folder,
	const char* cUTF8Folder);


#ifdef ANDROID
int android_wcscasecmp(
	const wchar_t *wcsStr1,
	const wchar_t *wcsStr2);
int android_wcsncasecmp(
	const wchar_t *wcsStr1,
	const wchar_t *wcsStr2,
	int nLength);
#endif
