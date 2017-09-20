/*
 * MT_Download.h
 *
 *  Created on: 2014-2-4
 *      Author: kyo
 */

#ifndef MT_DOWNLOAD_H_
#define MT_DOWNLOAD_H_

#include "types.h"
#include "FileOperator.h"
#include "BaseThread.h"
#include "NetFileStruct.h"
#include "HttpFileClient.h"

#define MT_DOWNLOAD_THREAD_COUNT	1

typedef struct tagMTDOWNLOAD_BLOCK
{
	char cNetFile[MAX_PATH];
	char cLocalFile[MAX_PATH];
	UINT64 uStartPos;
	UINT64 uEndPos;
	UINT64 uCopiedSize;
	float fCurSpeedKBPS;
} MTDOWNLOAD_BLOCK;

typedef struct tagMTDOWNLOAD_THREADINFO
{
	MTDOWNLOAD_BLOCK* pBlockInfo;
	CHttpFileClient sHttpFileClient;
	CBaseThread sBlockThread;
} MTDOWNLOAD_THREADINFO;

class IMultiThreadDownloadFailedListener
{
public:
	virtual ~IMultiThreadDownloadFailedListener(void) {}

	virtual void OnMultiThreadOneBlockDownloadComplete(
		UINT64 uUserData,
		BOOL bSuccess)=0;
};

class CMultiThreadDownload : public IThreadFuncInterface
{
public:
	CMultiThreadDownload();
	virtual ~CMultiThreadDownload();

public:
	// return TRUE to continue loop, return FALSE to end loop
	virtual BOOL ThreadLoop(
		UINT64 uThreadData);

public:
	void DownloadFile(
		BOOL bWaitForDownloadEnd,
		MTDOWNLOAD_BLOCK pBlockInfo[MT_DOWNLOAD_THREAD_COUNT],
		UINT32 uCacheSize,
		INetFileCopyProgressListener *pCopyProgreccListener,
		IMultiThreadDownloadFailedListener *pDownloadFailedListener,
		UINT64 uUserData);
	void CancelDownload();
	void PauseDownload();
	void ResumeDownload();
	BOOL IsDownloadingStart();

private:
	// return TRUE indicate need re-download
	// this maybe caused by socket error
	BOOL DownloadOneBlock(
		MTDOWNLOAD_THREADINFO *pBlockThreadInfo);

	void WaitForDownloadEnd();

private:
	BOOL mDownloadingStart;

	MTDOWNLOAD_THREADINFO mBlockThreadInfo[MT_DOWNLOAD_THREAD_COUNT];
	UINT32 mCacheSize;
	BOOL mStopping;
	CBaseEvent mPauseEvent;
	CBaseEvent mRedownloadEvent;
	INetFileCopyProgressListener *mpCopyProgressListener;
	IMultiThreadDownloadFailedListener *mpDownloadFailedListener;
	UINT64 mUserData;
};



#endif /* MT_DOWNLOAD_H_ */
