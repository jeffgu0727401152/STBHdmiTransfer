#pragma once

#include "types.h"

class CSimpleStringA;

class CSimpleStringW
{
public:
	CSimpleStringW();
	CSimpleStringW(
		const CSimpleStringA *pString);
	CSimpleStringW(
		const CSimpleStringW *pString);
	virtual ~CSimpleStringW();

public:
	void Append(
		char cChar);
	void Append(
		const char* cString,
		int nLength=-1);
	void Append(
		wchar_t wszChar);
	void Append(
		const wchar_t* wszString,
		int nLength=-1);

	void Set(
		char cChar);
	void Set(
		const char* cString,
		int nLength=-1);
	void Set(
		wchar_t wszChar);
	void Set(
		const wchar_t* wszString,
		int nLength=-1);
	void Set(
		const CSimpleStringA *pString);
	void Set(
		const CSimpleStringW *pString);

	void Replace(
		const char* cOld,
		const char* cNew,
		BOOL bIgnoreCase=FALSE);

	void Replace(
		const wchar_t* wszOld,
		const wchar_t* wszNew,
		BOOL bIgnoreCase=FALSE);

	BOOL IsDigit() const;
	BOOL IsAlpha() const;

	void ToLower();
	void ToUpper();
	void ToTraditionalChinese();
	void ToSimpleChinese();

	void Trunk(
		int nNewLength);

	void AppendFormat(
		const char *fmt, ...);
#ifndef ANDROID
	void AppendFormat(
		const wchar_t *fmt, ...);
#endif

	void Format(
		const char *fmt, ...);
#ifndef ANDROID
	void Format(
		const wchar_t *fmt, ...);
#endif

	BOOL Equal(
		char cChar,
		BOOL bIgnoreCase=FALSE) const;
	BOOL Equal(
		wchar_t wszChar,
		BOOL bIgnoreCase=FALSE) const;
	BOOL Equal(
		const char* cString,
		int nLength=-1,
		BOOL bIgnoreCase=FALSE) const;
	BOOL Equal(
		const CSimpleStringA *pString,
		BOOL bIgnoreCase=FALSE) const;
	BOOL Equal(
		const wchar_t* wszString,
		int nLength=-1,
		BOOL bIgnoreCase=FALSE) const;
	BOOL Equal(
		const CSimpleStringW *pString,
		BOOL bIgnoreCase=FALSE) const;

	void Free();

	const wchar_t* GetString() const;
	int GetLength() const;

private:
	int DecreaseCapability(
		int nCapability,
		int nSize);
	int IncreaseCapability(
		int nCapability,
		int nSize);

	BOOL ReAlloc(
		int nSize);

	void AppendInternal(
		const char* cString,
		int nLength);
	void AppendInternal(
		const wchar_t* wszString,
		int nLength);
	void FreeInternal();

private:
	wchar_t *mwszString;
	int mStringLength;
	int mCapbility;
};

class CSimpleStringA
{
public:
	CSimpleStringA();
	CSimpleStringA(
		const CSimpleStringA *pString);
	CSimpleStringA(
		const CSimpleStringW *pString);
	virtual ~CSimpleStringA();

public:
	void Append(
		char cChar);
	void Append(
		const char* cString,
		int nLength=-1);
	void Append(
		wchar_t wszChar);
	void Append(
		const wchar_t* wszString,
		int nLength=-1);

	void Set(
		char cChar);
	void Set(
		const char* cString,
		int nLength=-1);
	void Set(
		wchar_t wszChar);
	void Set(
		const wchar_t* wszString,
		int nLength=-1);
	void Set(
		const CSimpleStringA *pString);
	void Set(
		const CSimpleStringW *pString);

	void Replace(
		const char* cOld,
		const char* cNew,
		BOOL bIgnoreCase=FALSE);

	void Replace(
		const wchar_t* wszOld,
		const wchar_t* wszNew,
		BOOL bIgnoreCase=FALSE);

	BOOL IsDigit() const;
	BOOL IsAlpha() const;

	void ToLower();
	void ToUpper();
	void ToTraditionalChinese();
	void ToSimpleChinese();

	void Trunk(
		int nNewLength);

	void AppendFormat(
		const char *fmt, ...);
#ifndef ANDROID
	void AppendFormat(
		const wchar_t *fmt, ...);
#endif

	void Format(
		const char *fmt, ...);
#ifndef ANDROID
	void Format(
		const wchar_t *fmt, ...);
#endif

	BOOL Equal(
		char cChar,
		BOOL bIgnoreCase=FALSE) const;
	BOOL Equal(
		wchar_t wszChar,
		BOOL bIgnoreCase=FALSE) const;
	BOOL Equal(
		const char* ctring,
		int nLength=-1,
		BOOL bIgnoreCase=FALSE) const;
	BOOL Equal(
		const CSimpleStringA *pString,
		BOOL bIgnoreCase=FALSE) const;
	BOOL Equal(
		const wchar_t* wszString,
		int nLength=-1,
		BOOL bIgnoreCase=FALSE) const;
	BOOL Equal(
		const CSimpleStringW *pString,
		BOOL bIgnoreCase=FALSE) const;

	void Free();

	const char* GetString() const;
	int GetLength() const;

private:
	int DecreaseCapability(
		int nCapability,
		int nSize);
	int IncreaseCapability(
		int nCapability,
		int nSize);

	BOOL ReAlloc(
		int nSize);

	void AppendInternal(
		const char* cString,
		int nLength);
	void AppendInternal(
		const wchar_t* wszString,
		int nLength);
	void FreeInternal();

private:
	char *mcString;
	int mStringLength;
	int mCapbility;
};

BOOL IsDigitString(
	const char* cString);
BOOL IsAlphaString(
	const char* cString);

void ToLowerString(
	char* cString);
void ToUpperString(
	char* cString);

BOOL IsDigitString(
	const wchar_t* wszString);
BOOL IsAlphaString(
	const wchar_t* wszString);

void ToLowerString(
	wchar_t* wszString);
void ToUpperString(
	wchar_t* wszString);
