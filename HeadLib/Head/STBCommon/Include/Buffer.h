#pragma once

#include "types.h"

class CBuffer
{
public:
	CBuffer();
	virtual ~CBuffer(void);

public:
	void BindBuffer(
		const void *pBuffer,
		UINT32 uBufLen);
	void SetBuffer(
		const void *pBuffer,
		UINT32 uBufLen);
	void AppendBuffer(
		const void *pBuffer,
		UINT32 uBufLen);
	void Delete();
	const BYTE *GetBuffer() const;
	UINT32 GetAvailSize() const;
	UINT32 GetLeftSize() const;
	UINT32 GetBufSize() const;

	BOOL IsBindBuffer();

private:
	void ReAllocBuffer(
		UINT32 uSize);

private:
	BYTE *mpBuffer;
	UINT32 muBufSize;
	UINT32 muAvialble;
	BOOL mIsBind;
};
