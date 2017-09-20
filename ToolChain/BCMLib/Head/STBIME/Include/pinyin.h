/*
 * pinyin.h
 *
 *  Created on: 2013-1-12
 *      Author: kyo
 */

#pragma once

#include <wchar.h>

const wchar_t* pinyin_to_GB2312(
	const wchar_t* wszPinyin);

// return 'a-z', if not found, return '?'
wchar_t GB2312_to_spell(
	wchar_t wszGB2312);