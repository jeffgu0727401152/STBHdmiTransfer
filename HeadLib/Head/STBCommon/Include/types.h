#pragma once

typedef unsigned short UINT16;
typedef unsigned int UINT32;
typedef unsigned long long UINT64;
typedef long long int INT64;
typedef int BOOL;
typedef void * LPVOID;
typedef void * HANDLE;
typedef unsigned char BYTE;

#if defined(ANDROID)
#define fseeko64 fseek
#define ftello64 ftell
#endif

#ifndef _WIN32
typedef struct tagRECT
{
	int left;
	int top;
	int right;
	int bottom;
} RECT;

typedef struct tagPOINT
{
	int x;
	int y;
} POINT;

typedef struct tagSIZE
{
	int cx;
	int cy;
} SIZE;

typedef struct tagBLOB
{
    UINT32 cbSize;
    BYTE *pBlobData;
} BLOB;
#endif

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <locale.h>
#endif

#include "commdef.h"
