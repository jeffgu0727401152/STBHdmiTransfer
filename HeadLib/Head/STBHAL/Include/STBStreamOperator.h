/*
 * NetFileCopy.h
 *
 *  Created on: 2013-3-28
 *      Author: kyo
 */
#pragma once

#include "BaseLock.h"
#include "PtrControl.h"
#include "FileOperator.h"
#include "STBVideoDecrypt.h"
#include "HttpFileClient.h"
#include "BasePlayer.h"
#include "streamoperator_def.h"

class CSTBStreamOperator
{
public:
	CSTBStreamOperator();
	virtual ~CSTBStreamOperator();

public:
	BOOL Open(
		const char* cFileName,
		int nPlayerIndex,
		const char* cSTBDecryptOEMID);
	void PrepareClose();
	void Close();

	UINT32 GetBlockSize();
	UINT32 GetCacheBlockCount();
	UINT32 GetRetainBlockCount();

	UINT64 GetFileSize();

	size_t ReadBuffer(
		UINT64 uFromPos,
		BYTE *pBuffer,
		size_t nBufLen,
		UINT64 uTimeout,
		BOOL bUseContinueRead);

	UINT32 ReadOneBlock(
		BYTE **ppWorkingBuffer,
		UINT32 uBlockIndex,
		UINT32 uBlockSize,
		BOOL bLastBlock,
		UINT64 uTimeout,
		BOOL bUseContinueRead);

	BOOL SupportReadRandom();

	void CancelRead();
	void EnableSlowRead(
		BOOL bEnableSlowRead);

	float GetReadSpeedKBPS();

private:
	size_t ReadBufferNoDecrypt(
		UINT64 uFromPos,
		BYTE *pBuffer,
		size_t nBufLen,
		UINT64 uTimeout,
		BOOL bUseContinueRead);

private:
	UINT64 mFileSize;
	UINT32 mBlockSize;
	UINT32 mCacheBlockCount;
	UINT32 mRetainBlockCount;

	BUFFER_FILE_TYPE mBufferFileType;

	BYTE *mpWorkingBuffer;
	float mRealTimeReadSpeedKBPS;

private:
	CHttpFileClient mHttpFile;
	FILE *mpLocalFile;
	BOOL mCancelRead;
	BOOL mEnableSlowRead;

	CSTBVideoDecrypt mSTBVideoDecrypt;
};

void* Default_StreamOperator_Access_Open(
	const char* cFileName,
	int nPlayerIndex,
	const char* cOEMID);
void Default_StreamOperator_Access_PrepareClose(
	void* pHandle);
void Default_StreamOperator_Access_Close(
	void* pHandle);
UINT32 Default_StreamOperator_Access_GetBlockSize(
	void* pHandle);
UINT32 Default_StreamOperator_Access_GetCacheBlockCount(
	void* pHandle);
UINT32 Default_StreamOperator_Access_GetRetainBlockCount(
	void* pHandle);
UINT64 Default_StreamOperator_Access_GetFileSize(
	void* pHandle);
size_t Default_StreamOperator_Access_ReadBuffer(
	void* pHandle,
	UINT64 uFromPos,
	BYTE *pBuffer,
	size_t nBufLen,
	UINT64 uTimeout,
	BOOL bUseContinueRead);
UINT32 Default_StreamOperator_Access_ReadOneBlock(
	void* pHandle,
	BYTE **ppWorkingBuffer,
	UINT32 uBlockIndex,
	UINT32 uBlockSize,
	BOOL bLastBlock,
	UINT64 uTimeout,
	BOOL bUseContinueRead);
BOOL Default_StreamOperator_Access_SupportReadRandom(
	void* pHandle);
void Default_StreamOperator_Access_CancelRead(
	void* pHandle);
void Default_StreamOperator_Access_EnableSlowRead(
	void* pHandle,
	BOOL bEnableSlowRead);
float Default_StreamOperator_Access_GetReadSpeedKBPS(
	void* pHandle);

void* Default_StreamOperator_Process_Init(
	void* pHandle);
void Default_StreamOperator_Process_Deinit(
	void* pHandle,
	void *pUserData);
void Default_StreamOperator_Process_BufferPostCallback(
	void* pHandle,
	void *pUserData,
	UINT64 uDataPos,
	BYTE *pBuffer,
	UINT32 nBufLen);
