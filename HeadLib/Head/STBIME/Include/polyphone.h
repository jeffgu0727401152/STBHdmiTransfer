
#pragma once

#include <wchar.h>

typedef struct tagPOLYPHONE
{
	const wchar_t* wszWord;
	const wchar_t* wszSpell;
	int nCount;
} POLYPHONE;

// 返回符合多音字词组的拼音
// 例如，GetPolyphoneSpell(L"所长室")，返回"sz"
const POLYPHONE* GetMatchPolyphone(
	const wchar_t* wszCompare,
	int nCompareLen);
