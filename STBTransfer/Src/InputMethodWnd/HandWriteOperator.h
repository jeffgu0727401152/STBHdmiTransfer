#pragma once

#include "types.h"
#include "BaseLock.h"
#include "WWHW.h"

class CHandWriteOperator
{
public:
	CHandWriteOperator();
	virtual ~CHandWriteOperator();

public:
	void Init(BOOL bTraditional);
	void DeInit();
	int Recognize(
		const short* pStrokeAry,
		unsigned short * pResultStr,
		int iCount,
		HW_UINT32 uMatchRange);

private:
	CBaseLock mHWDataLock;
	BOOL mInited;
	BOOL mTraditional;
};
