/*
 * LocalCacheDownloadCtrl.h
 *
 *  Created on: 2018-5-14
 *      Author: tiny
 */

#pragma once

#include "HttpFileClient.h"
#include "types.h"
#include "BaseApp.h"

class DownloadTask;

class DownloadManager: public INetFileCopyProgressListener
{
public:
	DownloadManager();
	virtual ~DownloadManager();

	// interface
	virtual void OnNetFileCopyProgress(
		UINT64 uUserData,
		UINT64 uHasCopySize,
		UINT64 uNeedCopySize,
		float fCurSpeedKBPS,
		UINT64 *puLimitSpeedBPS);

public: 
	void StartDownload(const char* urls);
	BOOL GetDownloadPathByUrl(char* path,const char* url);
	BOOL IsLocalCacheAvailable(const char* url);
	const char* GetLocalVideoList();
	const char* GetDownloadLocation();

private:
	void SetDownloadLocation(const char* location);
	void SetVideoLocation(const char* location);
	void RemoveTmpFile();
	BOOL NeedReplaceVideo();
	BOOL CheckFileSize(const char* filePath);
	void ParseVideoList();

private:
	char mDownloadLocation[MAX_PATH];
	char mVideoLocation[MAX_PATH];
	DownloadTask* mDownloadTask;
	CSimpleStringA mLocalVideoList;
};
