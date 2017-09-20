/*
 * NetFileCopy.h
 *
 *  Created on: 2013-3-28
 *      Author: kyo
 */
#pragma once

#include "BaseThread.h"
#include "BaseLock.h"
#include "PtrControl.h"
#include "FileOperator.h"
#include "BasePlayer.h"
#include "STBVideoDecrypt.h"
#include "STBStreamOperator.h"
#include "HttpFileClient.h"

//#define DEBUG_STB_STREAM
#ifdef DEBUG_STB_STREAM
#define LOCAL_COMPARE_FILENAME	"/mnt/sda/sda1/xinheniyuehui.mkv"
#endif

// 如果需求的数据不再缓存中，使用 indexstream 直接读取数据
//#define USE_INDEXSTREAM_WHEN_DATA_NOT_INCACHE
#ifdef USE_INDEXSTREAM_WHEN_DATA_NOT_INCACHE
#define SETCACHEINDEX_MISSED_COUNT		20
#else
#define SETCACHEINDEX_MISSED_COUNT		0
#endif

// 如果读取的数据不再缓存中，需要等缓存满了再返回
// android 版本不需要等待 cache full，否则可能会有ANR产生
#define READ_NOT_WAIT_CACHE_FULL

ssize_t simple_datastream_read(
	void* handle,
	void *buf,
	size_t length);
off64_t simple_datastream_seek(
	void* handle,
	off64_t offset,
	int whence);
int simple_datastream_bounds(
	void* handle,
	off64_t *first,
	off64_t *last);

ssize_t simple_indexstream_read(
	void* handle,
	void *buf,
	size_t length);
off64_t simple_indexstream_seek(
	void* handle,
	off64_t offset,
	int whence);
int simple_indexstream_bounds(
	void* handle,
	off64_t *first,
	off64_t *last);

ssize_t stb_datastream_read(
	void* handle,
	void *buf,
	size_t length);
off64_t stb_datastream_seek(
	void* handle,
	off64_t offset,
	int whence);
int stb_datastream_bounds(
	void* handle,
	off64_t *first,
	off64_t *last);

ssize_t stb_indexstream_read(
	void* handle,
	void *buf,
	size_t length);
off64_t stb_indexstream_seek(
	void* handle,
	off64_t offset,
	int whence);
int stb_indexstream_bounds(
	void* handle,
	off64_t *first,
	off64_t *last);

typedef enum eBUFFER_PREFETCH_STATE
{
	BufferPrefetchState_Inited=0,
	BufferPrefetchState_Reading,
	BufferPrefetchState_Complete,
} BUFFER_PREFETCH_STATE;

typedef struct tagBLOCKBUFFERINFO
{
	UINT32 uBlockIndex;
	BUFFER_PREFETCH_STATE ePrefetchState;
	UINT32 uBlockSize;
	BYTE *pBuffer;
} BLOCKBUFFERINFO;

class CStreamCacheBuffer
{
public:
	CStreamCacheBuffer();
	virtual ~CStreamCacheBuffer();

public:
	BOOL Create(
		UINT64 uFileSize,
		UINT32 uBlockSize,
		UINT32 uCacheCount,
		UINT32 uRetainCount);
	void Delete();

public:
	void Lock();
	void Unlock();

	size_t ReadCacheBuffer(
		UINT64 uPos,
		BYTE *pBuffer,
		size_t nBufLen);
	size_t ReadFromBlockLocked(
		UINT32 uBlockIndex,
		UINT32 uBlockStartPos,
		void *pBuffer,
		size_t nBufLen);
	BLOCKBUFFERINFO* GetBlockInfoLocked(
		UINT32 uBlockIndex);

	UINT32 GetTotalBlockCount();
	UINT32 GetCacheBlockCount();
	UINT32 GetRetainBlockCount();
	UINT32 GetCacheStartIndex();
	UINT32 GetPrefetchStartIndex();
	UINT32 ComputeHasFetchedCacheBlockCount();

	// return value:
	// 有block处于读取中被更改index返回TRUE，否则返回FALSE
	//
	BOOL SetPrefetchStartIndex(
		UINT32 uPrefetchStartIndex);

private:
	UINT64 mFileSize;
	UINT32 mBlockSize;
	UINT32 mTotalBlockCount;
	UINT32 mCacheBlockCount;
	UINT32 mRetainBlockCount;
	UINT32 mCacheStartIndex;
	UINT32 mPrefetchStartIndex;

	CBaseLock mBufListLock;
	CPtrListCtrl mBlockBufferInfoList;
};

class CSTBIndexStreamReader
{
public:
	CSTBIndexStreamReader();
	virtual ~CSTBIndexStreamReader();

public:
	// PS bReadNoCache: 只能在没有加密的情况下使用
	BOOL Open(
		CStreamCacheBuffer *pStreamCacheBuffer,
		const char* cFileName,
		int nPlayerIndex,
		const char* cSTBDecryptOEMID);

	void PrepareClose();
	void Close();

	size_t Read(
		BYTE *pBuffer,
		size_t nBufLen);
	UINT64 Seek(
		UINT64 lOffset);

	UINT64 GetSize();
	UINT64 GetPos();

public:
	void SetStreamOperatorAccessFunction(
		STREAMOPERATOR_ACCESS_INFO* pStreamAccessFunction);
	void SetStreamOperatorProcessFunction(
		STREAMOPERATOR_PROCESS_INFO* pStreamProcessFunction);

private:
	BOOL mPrepareClose;

	CBaseEvent mReadCompleteEvent;
	BOOL mSeeking;

	UINT64 mFileSize;
	UINT32 mBlockSize;
	UINT64 mReadPos;

	CStreamCacheBuffer *mpStreamCacheBuffer;

	// data operator function define
	STREAMOPERATOR_ACCESS_OPEN mpfn_SO_A_Open;
	STREAMOPERATOR_ACCESS_PREPARECLOSE mpfn_SO_A_PrepareClose;
	STREAMOPERATOR_ACCESS_CLOSE mpfn_SO_A_Close;
	STREAMOPERATOR_ACCESS_GETBLOCKSIZE mpfn_SO_A_GetBlockSize;
	STREAMOPERATOR_ACCESS_GETCACHEBLOCKCOUNT mpfn_SO_A_GetCacheBlockCount;
	STREAMOPERATOR_ACCESS_GETRETAINBLOCKCOUNT mpfn_SO_A_GetRetainBlockCount;
	STREAMOPERATOR_ACCESS_GETFILESIZE mpfn_SO_A_GetFileSize;
	STREAMOPERATOR_ACCESS_READBUFFER mpfn_SO_A_ReadBuffer;
	STREAMOPERATOR_ACCESS_READONEBLOCK mpfn_SO_A_ReadOneBlock;
	STREAMOPERATOR_ACCESS_SUPPORTREADRANDOM mpfn_SO_A_SupportReadRandom;
	STREAMOPERATOR_ACCESS_CANCELREAD mpfn_SO_A_CancelRead;
	STREAMOPERATOR_ACCESS_ENABLESNOWREAD mpfn_SO_A_EnableSlowRead;
	STREAMOPERATOR_ACCESS_GETREADSPEEDKBPS mpfn_SO_A_GetReadSpeedKBPS;
	void *mStreamOperatorHandle;

	STREAMOPERATOR_PROCESS_INIT mpfn_SO_P_Init;
	STREAMOPERATOR_PROCESS_DEINIT mpfn_SO_P_Deinit;
	STREAMOPERATOR_PROCESS_BUFFERPOSTCALLBACK mpfn_SO_P_BufferPostCallback;
	void *mpStreamOperatorProcessUserData;

#ifdef DEBUG_STB_STREAM
public:
	FILE *mLocalCompareFile;
#endif
};

class CSTBDataStreamReader :
	public IThreadFuncInterface
{
public:
	CSTBDataStreamReader();
	virtual ~CSTBDataStreamReader();

	// interface
public:
	virtual BOOL ThreadLoop(
		UINT64 uThreadData);

	BOOL DownloadBlock(
		UINT32 uDownloadBlockIndex,
		UINT32 uTotalBlockCount);

public:
	// PS bReadNoCache: 只能在没有加密的情况下使用
	BOOL Open(
		CStreamCacheBuffer *pStreamCacheBuffer,
		const char* cFileName,
		int nPlayerIndex,
		const char* cSTBDecryptOEMID);

	void PrepareClose();
	void Close();

	size_t Read(
		BYTE *pBuffer,
		size_t nBufLen);
	UINT64 Seek(
		UINT64 lOffset);

	UINT64 GetSize();
	UINT64 GetPos();

public:
	void SetHttpStreamEventListener(
		IHttpStreamEventListener *pHttpStreamEventListener);

	virtual void SetHttpStreamCallbackType(
		HTTPSTREAMCALLBACKTYPE eType);

	void SetStreamOperatorAccessFunction(
		STREAMOPERATOR_ACCESS_INFO* pStreamAccessFunction);
	void SetStreamOperatorProcessFunction(
		STREAMOPERATOR_PROCESS_INFO* pStreamProcessFunction);

private:
	BOOL mExitThread;
	CBaseThread mDataReadThread;
	CBaseEvent mPrefetchStartEvent;
	BOOL mAllCacheHasDownload;
	BOOL mCurFetchBlockIndexNeedChange;

	BOOL mPrepareClose;

	CBaseEvent mReadCompleteEvent;
	BOOL mSeeking;

	UINT64 mFileSize;
	UINT32 mBlockSize;
	UINT64 mReadPos;

	CStreamCacheBuffer *mpStreamCacheBuffer;

	// data operator function define
	STREAMOPERATOR_ACCESS_OPEN mpfn_SO_A_Open;
	STREAMOPERATOR_ACCESS_PREPARECLOSE mpfn_SO_A_PrepareClose;
	STREAMOPERATOR_ACCESS_CLOSE mpfn_SO_A_Close;
	STREAMOPERATOR_ACCESS_GETBLOCKSIZE mpfn_SO_A_GetBlockSize;
	STREAMOPERATOR_ACCESS_GETCACHEBLOCKCOUNT mpfn_SO_A_GetCacheBlockCount;
	STREAMOPERATOR_ACCESS_GETRETAINBLOCKCOUNT mpfn_SO_A_GetRetainBlockCount;
	STREAMOPERATOR_ACCESS_GETFILESIZE mpfn_SO_A_GetFileSize;
	STREAMOPERATOR_ACCESS_READBUFFER mpfn_SO_A_ReadBuffer;
	STREAMOPERATOR_ACCESS_READONEBLOCK mpfn_SO_A_ReadOneBlock;
	STREAMOPERATOR_ACCESS_SUPPORTREADRANDOM mpfn_SO_A_SupportReadRandom;
	STREAMOPERATOR_ACCESS_CANCELREAD mpfn_SO_A_CancelRead;
	STREAMOPERATOR_ACCESS_ENABLESNOWREAD mpfn_SO_A_EnableSlowRead;
	STREAMOPERATOR_ACCESS_GETREADSPEEDKBPS mpfn_SO_A_GetReadSpeedKBPS;
	void *mStreamOperatorHandle;

	STREAMOPERATOR_PROCESS_INIT mpfn_SO_P_Init;
	STREAMOPERATOR_PROCESS_DEINIT mpfn_SO_P_Deinit;
	STREAMOPERATOR_PROCESS_BUFFERPOSTCALLBACK mpfn_SO_P_BufferPostCallback;
	void *mpStreamOperatorProcessUserData;

	IHttpStreamEventListener *mpHttpStreamEventListener;
	HTTPSTREAMCALLBACKTYPE mHttpStreamCallbackType;

#ifdef DEBUG_STB_STREAM
public:
	FILE *mLocalCompareFile;
#endif

#ifdef USE_INDEXSTREAM_WHEN_DATA_NOT_INCACHE
	CSTBIndexStreamReader mMissedReader;
	UINT32 mMissedReadCount;
#endif
};
