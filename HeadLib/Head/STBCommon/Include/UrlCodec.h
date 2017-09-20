#pragma once

#include "SimpleString.h"

void EncodeURL(
	const char *cInputString,
	CSimpleStringA *pOutput);

void DecodeURL(
	const char *cInputString,
	CSimpleStringA *pOutput);
