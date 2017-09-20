#include "HandWriteOperator.h"

#ifdef PC_VERSION
#include "hwdataT.c"
extern const unsigned char arrayHwdataT[];
#else
#include "hwdata-b5-R.c"
#include "hwdata-gb-R.c"
extern const unsigned long arrayDwBigR[];
extern const unsigned long arrayHwdataR[];
#endif

CHandWriteOperator::CHandWriteOperator()
{
	mTraditional = FALSE;
	mInited = FALSE;

	Init(FALSE);
}

CHandWriteOperator::~CHandWriteOperator()
{
	DeInit();
}

void CHandWriteOperator::Init(BOOL bTraditional)
{
	if (mInited && (mTraditional == bTraditional))
	{
		return;
	}

	mHWDataLock.Lock();

	if (mInited)
	{
		WWExitRecognition();
	}

	const void *arrayHwdata = NULL;
#ifdef PC_VERSION
	arrayHwdata = arrayHwdataT;
#else
	if (bTraditional)
	{
		arrayHwdata = arrayDwBigR;
	}
	else
	{
		arrayHwdata = arrayHwdataR;
	}
#endif

	WWInitRecognition(arrayHwdata, 0);
	mInited = TRUE;
	mTraditional = bTraditional;

	mHWDataLock.Unlock();
}

void CHandWriteOperator::DeInit()
{
	if (mInited)
	{
		WWExitRecognition();
		mInited = FALSE;
	}
}

int CHandWriteOperator::Recognize(
	const short* pStrokeAry,
	unsigned short * pResultStr,
	int iCount,
	HW_UINT32 uMatchRange)
{
#if defined(BCM7251S) || defined(BCM7252S) || defined(HISI3719C)
	return WWRecognize(
#else
	return WWRecognizeChar(
#endif
		pStrokeAry,
		pResultStr,
		iCount,
		uMatchRange);
}
