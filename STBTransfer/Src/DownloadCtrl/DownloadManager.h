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
#include <vector>

class DownloadTask;

class DownloadManager: public INetFileCopyProgressListener
{
public:
	DownloadManager();
	virtual ~DownloadManager();

	virtual void OnNetFileCopyProgress(
		UINT64 uUserData,
		UINT64 uHasCopySize,
		UINT64 uNeedCopySize,
		float fCurSpeedKBPS,
		UINT64 *puLimitSpeedBPS);

public: 
	void StartDownload(const char* urls);
	BOOL GetStoragePathByUrl(char* path,const char* url);
	BOOL IsLocalCacheAvailable(const char* url);

private:
	void SetDownloadLocation(const char* location);
	void RemoveTmpFile();

private:
	char mDownloadLocation[MAX_PATH];
	DownloadTask* mDownloadTask;
};
