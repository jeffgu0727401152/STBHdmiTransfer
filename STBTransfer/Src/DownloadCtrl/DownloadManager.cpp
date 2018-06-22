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
	mLocalVideoList.Format("");
	mDownloadLocation[0] = '\0';
	mVideoLocation[0] = '\0';
	SetDownloadLocation(DOWNLOAD_FOLDER);
	SetVideoLocation(VIDEO_FOLDER);

	RemoveTmpFile();

	if (NeedReplaceVideo()==TRUE)
	{
		do_syscmd(NULL, "mv %s %s_old", mVideoLocation,mVideoLocation);
		do_syscmd(NULL, "mv %s %s", mDownloadLocation,mVideoLocation);
		do_mkdir(mDownloadLocation, 0777);
		do_syscmd(NULL, "sync");
	}

	ParseVideoList();
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

	// 检查下载目录是否存在不需要下载的文件,如果有文件不在下载列表中,则删除
	// 主要用于上次开机没有下载完成,所以下载目录还没有重命名成播放目录,但是此时视频已经变了
	CPtrListCtrl sArcList;
	GetLocalFolderFileList(
		mDownloadLocation,
		NULL,
		&sArcList,
		NULL,
		FALSE);

	const char* cDownloadedFileName = NULL;
	for (int i=0; i < sArcList.GetCount(); i++)
	{
		cDownloadedFileName = (const char*)sArcList.GetAt(i);
		std::string fileNameStr = cDownloadedFileName;
		std::string suffixStr = fileNameStr.substr(fileNameStr.find_last_of('.') + 1);

		if (suffixStr.compare("tmp")==0 || suffixStr.compare("size")==0 || suffixStr.compare("flag")==0)
		{
			continue;
		}

		int ret = mDownloadTask->GetDownloadList().FindFirst(cDownloadedFileName,FindUrlByPath);
		if (ret<0)
		{
			char cDeletePath[MAX_PATH];
			char cDeleteSizePath[MAX_PATH];
			sprintf(cDeletePath, "%s/%s", mDownloadLocation, cDownloadedFileName);
			sprintf(cDeleteSizePath, "%s/%s.size", mDownloadLocation, cDownloadedFileName);
			LOGMSG(DBG_LEVEL_I, "%s not found in new download list, remove it\n",cDeletePath);
			remove(cDeletePath);
			remove(cDeleteSizePath);
		}
	}

	// 检查播放目录是否存在需要下载的文件,如果有文件都在下载列表中,则不需要再次下载
	int findVideoCount = 0;
	int videoFileCount = 0;
	CPtrListCtrl sPlayList;
	GetLocalFolderFileList(
		mVideoLocation,
		NULL,
		&sPlayList,
		NULL,
		FALSE);

	const char* cVideoFileName = NULL;
	for (int i=0; i < sPlayList.GetCount(); i++)
	{
		cVideoFileName = (const char*)sPlayList.GetAt(i);
		std::string fileNameStr = cVideoFileName;
		std::string suffixStr = fileNameStr.substr(fileNameStr.find_last_of('.') + 1);

		if (suffixStr.compare("tmp")==0 || suffixStr.compare("size")==0 || suffixStr.compare("flag")==0)
		{
			continue;
		}

		videoFileCount++;

		int ret = mDownloadTask->GetDownloadList().FindFirst(cVideoFileName,FindUrlByPath);
		if (ret>=0)
		{
			findVideoCount++;
			LOGMSG(DBG_LEVEL_I, "%s found in download list\n",cVideoFileName);
		}
		else
		{
			LOGMSG(DBG_LEVEL_I, "%s not found in download list\n",cVideoFileName);
		}
	}

	LOGMSG(DBG_LEVEL_I, "video file count=%d,download list size=%d, find %d in download list\n",
			videoFileCount,mDownloadTask->GetDownloadList().GetCount(),findVideoCount);

	if (findVideoCount != mDownloadTask->GetDownloadList().GetCount() || videoFileCount != mDownloadTask->GetDownloadList().GetCount() )
	{
		LOGMSG(DBG_LEVEL_I, "file in %s folder is not same as download list, will download\n",mVideoLocation);
		mDownloadTask->Start();
	}
	else
	{
		// Video目录下的文件与要下载的完全一致,就不会start上面的Task,那么就需要我们这边删除以下done.flag以防Download目录只剩下done.flag
		// 主要用于防止这种情况: Video目录下有视频A,服务器先要求我们下载 视频B,我们下载完成并设置done.flag,然后服务器又要求我们下载视频A
		LOGMSG(DBG_LEVEL_I, "file in %s folder is same as download list, just delete done flag\n",mVideoLocation);
		do_syscmd(NULL,"rm %s/done.flag",mDownloadLocation);
		do_syscmd(NULL,"sync");
	}
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

const char* DownloadManager::GetDownloadLocation()
{
	return mDownloadLocation;
}


void DownloadManager::SetVideoLocation(const char* location)
{
	if(location && strlen(location)>0)
	{
		strcpy(mVideoLocation,location);
		if(mVideoLocation[strlen(mVideoLocation)-1] == '/')
		{
			mVideoLocation[strlen(mVideoLocation)-1] = '\0';
		}
	}
	else
	{
		LOGMSG(DBG_LEVEL_W, "invalid location. use default path\n");
	}

	if(IsFileExist(mVideoLocation) == TRUE)
	{
		if (IsDir(mVideoLocation) != TRUE)
		{
			RemoveFile(mVideoLocation, NULL, TRUE, TRUE);
			do_mkdir(location, 0777);
		}
	}
	else
	{
		do_mkdir(mVideoLocation, 0777);
	}
}

BOOL DownloadManager::GetDownloadPathByUrl(char* path,const char* url)
{
	char name[PATH_MAX];
	GetFileShortName(name,url);
	sprintf(path, "%s/%s", mDownloadLocation, name);
	return TRUE;
}

BOOL DownloadManager::IsLocalCacheAvailable(const char* url)
{
	char fileName[PATH_MAX];
	char storagePath[PATH_MAX];
	GetFileShortName(fileName,url);
	sprintf(storagePath, "%s/%s", mDownloadLocation, fileName);

	return CheckFileSize(storagePath);
}

const char* DownloadManager::GetLocalVideoList()
{
	return mLocalVideoList.GetString();
}

BOOL DownloadManager::NeedReplaceVideo()
{
	char doneFlagPath[MAX_PATH];
	sprintf(doneFlagPath, "%s/%s", mDownloadLocation, "done.flag");

	if (IsFileExist(doneFlagPath))
	{
		return TRUE;
	}

	return FALSE;
}

void DownloadManager::ParseVideoList()
{
	CPtrListCtrl sArcList;
	GetLocalFolderFileList(
		mVideoLocation,
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

		if (suffixStr.compare("tmp")==0 || suffixStr.compare("size")==0 || suffixStr.compare("flag")==0)
		{
			continue;
		}

		char storagePath[MAX_PATH];
		sprintf(storagePath, "%s/%s", mVideoLocation, cVideoFileName);

		if (CheckFileSize(storagePath) == TRUE)
		{
			if (mLocalVideoList.GetLength()!=0)
			{
				mLocalVideoList.Append(',');
			}
			mLocalVideoList.Append(storagePath);
		}
	}
	LOGMSG(DBG_LEVEL_I, "parse result:%s\n",mLocalVideoList.GetString());
}

BOOL DownloadManager::CheckFileSize(const char* filePath)
{
	char fileName[PATH_MAX];
	char parentDir[PATH_MAX];
	GetFileParentDir(parentDir,filePath);
	GetFileShortName(fileName,filePath);
	char storagePath[MAX_PATH];
	char sizeFilePath[MAX_PATH];
	sprintf(storagePath, "%s/%s", parentDir, fileName);
	sprintf(sizeFilePath, "%s/%s.size", parentDir, fileName);

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

	if (strlen(mVideoLocation)>0)
	{
		RemoveFile(mVideoLocation,".tmp",TRUE,TRUE);
		char videoPathOld[MAX_PATH];
		sprintf(videoPathOld,"%s%s",mVideoLocation,"_old");
		do_syscmd(NULL,"rm -rf %s",videoPathOld);
		do_syscmd(NULL,"sync");
	}
}
