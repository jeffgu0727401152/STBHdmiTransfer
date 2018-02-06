#pragma once

#include "types.h"
#include "BaseLock.h"
#include "ImageBuffer.h"

/**                                   5 dimesion point
 *
 *                                            (p0)  *
 *                                              *              *
 *                               (p1)  *                         *  (p4)
 *                                            *                 *
 *                                     (p2)  * * * * *  (p3)
 *
 * */

class C5DimensionBuffer
{
public:
	C5DimensionBuffer();
	virtual ~C5DimensionBuffer();

public:
	void Create(
		CImageBuffer* pBkImageBuffer);
	void Delete();

	void GetResult(
		CImageBuffer* pResuleImageBuffer,
		POINT ptValue[5],
		UINT32 uColor);

private:
	CImageBuffer mBkImageBuffer;
};
