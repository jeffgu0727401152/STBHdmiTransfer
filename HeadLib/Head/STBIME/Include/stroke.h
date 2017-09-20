/*
 * pinyin.h
 *
 *  Created on: 2013-1-12
 *      Author: kyo
 */

#pragma once

#include <wchar.h>

#define STROKE_CHAR_COUNT	6
extern const wchar_t STROKE_WCHAR[STROKE_CHAR_COUNT];

const char* convertToStrokeCode(
	const wchar_t* wszStrokeChar);

int stroke_to_chinese(
	const char* cStroke,
	wchar_t* wszCandidate,
	int nCandidateBufLen);

char GetCharFirstStroke(
	wchar_t wszChinese);

int GetStringFirstStroke(
	const wchar_t* wszChinese,
	char* cStrokeArray,
	int nArraySize);
