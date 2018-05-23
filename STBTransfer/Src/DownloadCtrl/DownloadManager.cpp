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
	//const char* url = (const char*)uUserData;
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

	const char* cVideoFileName = NULL;
	for (int i=0; i < sArcList.GetCount(); i++)
	{
		cVideoFileName = (const char*)sArcList.GetAt(i);
		std::string fileNameStr = cVideoFileName;
		std::string suffixStr = fileNameStr.substr(fileNameStr.find_last_of('.') + 1);

		if (suffixStr.compare("tmp")==0 || suffixStr.compare("size")==0)
		{
			continue;
		}

		int ret = mDownloadTask->GetDownloadList().FindFirst(cVideoFileName,FindUrlByPath);
		if (ret<0)
		{
			char cDeletePath[MAX_PATH];
			char cDeleteSizePath[MAX_PATH];
			sprintf(cDeletePath, "%s/%s", mDownloadLocation, cVideoFileName);
			sprintf(cDeleteSizePath, "%s/%s.size", mDownloadLocation, cVideoFileName);
			LOGMSG(DBG_LEVEL_I, "%s not found in new download list, remove it\n",cDeletePath);
			remove(cDeletePath);
			remove(cDeleteSizePath);
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

BOOL DownloadManager::IsLocalCacheAvailable(const char* url)
{
	char fileName[PATH_MAX];
	char storagePath[PATH_MAX];
	char sizeFilePath[PATH_MAX];
	GetFileShortName(fileName,url);
	sprintf(storagePath, "%s/%s",
			mDownloadLocation,
			fileName);
	sprintf(sizeFilePath, "%s/%s.size",
			mDownloadLocation,
			fileName);

	if (IsFileExist(storagePath)==FALSE || IsDir(storagePath)==TRUE )
	{
		return FALSE;
	}

	if (IsFileExist(sizeFilePath)==FALSE || IsDir(sizeFilePath)==TRUE )
	{
		return FALSE;
	}

	FILE* fp = fopen(storagePath, "rb");
	if (fp)
	{
		UINT64 fileSize = FileSize(fp);
	    fclose(fp);

	    FILE* sfp = fopen(sizeFilePath, "rb");
		if (sfp)
		{
			char fileBuf[256];
			memset(fileBuf,0,sizeof(fileBuf));
			FileRead(sfp, (void *)fileBuf, sizeof(fileBuf));
			fclose(sfp);
			UINT64 requireSize = atoi(fileBuf);
			LOGMSG(DBG_LEVEL_I, "requireSize=%llu, fileSize=%llu\n",requireSize,fileSize);
			if (requireSize==fileSize)
			{
				return TRUE;
			}
		}
	}

	return FALSE;
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
