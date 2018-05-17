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

typedef struct tagDownloadUnit
{
	char netURL[MAX_PATH];
	char localURL[MAX_PATH];

	BOOL isDownloading;
	BOOL isLocalExited;
}OPENROOM_DOWNLOAD_UNIT;

class DownloadManager: public INetFileCopyProgressListener ,public IMessageOwner

{
public:
	DownloadManager();
	virtual ~DownloadManager();

	// fCurSpeedKBPS: K-Bytes per secondss
	virtual void OnNetFileCopyProgress(
		UINT64 uUserData,
		UINT64 uHasCopySize,
		UINT64 uNeedCopySize,
		float fCurSpeedKBPS,
		UINT64 *puLimitSpeedBPS);
	std::vector<OPENROOM_DOWNLOAD_UNIT> mDownloadList;

	virtual void OnMsg(
			UINT32 uType,
			UINT64 wParam,
			UINT64 lParam);
	void collectingDiskInformationAndUpdatePlayerList(int direction);

public: 
	void startDownloadToTargetLocationWithNetURLs(const char* netURLs,char* localURLs);
	void setDownloadLocation(const char* location);

	BOOL mStartPlay;

	char m_location[MAX_PATH];

	DownloadTask* mCurrentDownload;

	int playerCurrentIndex;
};
