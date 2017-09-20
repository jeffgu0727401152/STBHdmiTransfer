#pragma once
#include "types.h"

void Big5ToGbA(
	const char *cBig5,
	int nBig5Length,
	char *cGB,
	int nGBLength);

void GbToBig5A(
	const char *cGB,
	int nGBLength,
	char *cBig5,
	int nBig5Length);

BOOL IsChineseA(
	char cChar1,
	char cChar2);
