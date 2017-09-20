#pragma once
#include "BitmapOperator.h"
#include "ImageBuffer.h"

class CMarqueeBuffer:public CImageBuffer
{
public:
	CMarqueeBuffer();
	virtual ~CMarqueeBuffer();

public:
	// TURE: a new line Marquee
	BOOL Marquee(
		int nWidth);

	void Reset(
		int nStartPos);

	void MarqueeDrawToImageBuffer(
		CImageBuffer *pTo,
		const RECT& rcCopyTo,
		BOOL bTransparent,
		int nDrawMode);

private:
	int mStartPos;
};
