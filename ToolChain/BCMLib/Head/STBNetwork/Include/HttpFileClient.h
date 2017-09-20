/*
 * PlayerCmdServer.h
 *
 *  Created on: 2013-1-18
 *      Author: kyo
 */
#pragma once

#include "types.h"
#include "BaseThread.h"
#include "BaseLock.h"
#include "Buffer.h"
#include "SimpleString.h"
#include "NetFileStruct.h"
#include "curlhelp.h"

class CHttpFileClient : public IThreadFuncInterface,
		public IHttpDataCallback
{
public:
	CHttpFileClient();
	virtual ~CHttpFileClient();

public:
	// return TRUE to continue loop, return FALSE to end loop
	virtual BOOL ThreadLoop(
		UINT64 uThreadData);

	virtual UINT32 OnHttpDataRecvCallback(
		const BYTE *pHttpData,
		UINT32 uDataSize,
		UINT64 uUserData);

	virtual int OnHttpDataProgressCallback(
		UINT64 uUserData);

public:
	BOOL OpenFile(
		const char *cURL);
	// disable all later read request
	void PrepareClose();
	BOOL CloseFile();

	// read use a thread to download all left data
	UINT32 ReadFile_Continue(
		void *pBuffer,
		UINT32 nBufLen,
		UINT64 uTimeout);
	// read data by position
	UINT32 ReadFile_Part(
		void *pBuffer,
		UINT32 nBufLen,
		UINT64 uTimeout);
	// stop current read request
	void CancelRead();

	float GetTotalAvgDownloadSpeedKBPS();
	float GetRealTimeDownloadSpeedKBPS();
	void LimitReadSpeed(
		UINT64 uBytesPerSecond);

	INT64 SeekFile(
		INT64 offset,
		int whence);

	UINT64 GetFilePos();
	UINT64 GetFileSize();

private:
	const HTTPFILEINFO* GetHttpFileInfo();

	void StartHttpReadThread();
	void StopHttpReadThread();

protected:
	CBaseLock mCURLLock;
	HTTPFILEINFO mHttpFileInfo;

	BOOL mPrepareClose;
	BOOL mCancelRead;
	UINT64 mCurPos;

	BOOL mPosHasChanged;
	CBaseThread mHttpReadThread;
	CBaseLock mHttpBufferLock;
	CBuffer mHttpReadBuffer;
	CBaseEvent mHttpReadStartEvent;
	CBaseEvent mHttpReadCompleteEvent;
	CBaseEvent mHttpReadRequestEvent;
	UINT64 mTransferStartTime;
	UINT64 mLastReadStartTime;
	UINT64 mLastReadDataSize;

	float mRealTimeDownloadSpeedKBPS;
	UINT64 mLmitReadSpeedBPS;
};

BOOL HttpFileCopyFromServer(
	CHttpFileClient *pHttpFileClient,
	const char *cURL,
	const char *cLocalFile,
	UINT64 uTimeout,
	INetFileCopyProgressListener *pListener,
	UINT64 uUserData);
