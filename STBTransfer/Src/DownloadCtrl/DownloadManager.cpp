#include "DownloadManager.h"
#include "DownloadTask.h"
#include "../GlobalUIClass.h"
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>

int FindUrlByPath(const void *pItem, const void *pData)
{
	const char *pUrl = (const char *)pItem;
	const char *pPath  = (const char *)pData;

	if (pUrl && pPath)
	{
		char urlName[PATH_MAX];
		char pathName[PATH_MAX];
		GetFileShortName(urlName,pUrl);
		GetFileShortName(pathName,pPath);
		if (strcmp(urlName, pathName) == 0)
		{
			return 1;
		}
	}
	return 0;
}

DownloadManager::DownloadManager()
{
	mDownloadTask = NULL;
	memset(mDownloadLocation,0,sizeof(mDownloadLocation));
	SetDownloadLocation(DOWNLOAD_FOLDER);
	RemoveTmpFile();
}

DownloadManager::~DownloadManager()
{
	if (mDownloadTask)
	{
		delete mDownloadTask;
		mDownloadTask = NULL;
	}
}

void DownloadManager::OnNetFileCopyProgress(
		UINT64 uUserData,
		UINT64 uHasCopySize,
		UINT64 uNeedCopySize,
		float fCurSpeedKBPS,
		UINT64 *puLimitSpeedBPS)
{
	if (gKTVConfig.GetDownloadSpeedLimit() > 0) {
		*puLimitSpeedBPS = gKTVConfig.GetDownloadSpeedLimit();
	}
}

void DownloadManager::StartDownload(const char* urls)
{
	if(mDownloadTask)
	{
		delete mDownloadTask;
		mDownloadTask = NULL;
	}

	mDownloadTask = new DownloadTask(urls);

	CPtrListCtrl sArcList;
	GetLocalFolderFileList(
		mDownloadLocation,
		NULL,
		&sArcList,
		NULL,
		FALSE);

	const char* cVideoPath = NULL;
	for (int i=0; i < sArcList.GetCount(); i++)
	{
		cVideoPath = (const char*)sArcList.GetAt(i);
		int ret = mDownloadTask->GetDownloadList().FindFirst(cVideoPath,FindUrlByPath);
		if (ret<0)
		{
			char cDeletePath[MAX_PATH];
			CombinePathName(cDeletePath, mDownloadLocation, cVideoPath);
			LOGMSG(DBG_LEVEL_I, "%s not found in new download list, remove it\n",cDeletePath);
			remove(cDeletePath);
		}
	}

	mDownloadTask->Start();
}

void DownloadManager::SetDownloadLocation(const char* location)
{
	if(location && strlen(location)>0)
	{
		strcpy(mDownloadLocation,location);
		if(mDownloadLocation[strlen(mDownloadLocation)-1] == '/')
		{
			mDownloadLocation[strlen(mDownloadLocation)-1] = '\0';
		}
	}
	else
	{
		LOGMSG(DBG_LEVEL_W, "invalid location. use default path\n");
	}

	if(IsFileExist(mDownloadLocation) == TRUE)
	{
		if (IsDir(mDownloadLocation) != TRUE)
		{
			RemoveFile(mDownloadLocation, NULL, TRUE, TRUE);
			do_mkdir(location, 0777);
		}
	}
	else
	{
		do_mkdir(mDownloadLocation, 0777);
	}
}

BOOL DownloadManager::GetStoragePathByUrl(char* path,const char* url)
{
	char name[PATH_MAX];
	GetFileShortName(name,url);
	sprintf(path, "%s/%s",
			mDownloadLocation,
			name);
	return TRUE;
}

void DownloadManager::RemoveTmpFile()
{
	if (strlen(mDownloadLocation)>0)
	{
		RemoveFile(mDownloadLocation,".tmp",TRUE,TRUE);
	}
	else
	{
		LOGMSG(DBG_LEVEL_W, "unknown mDownloadlocation, do nothing\n");
	}
}
