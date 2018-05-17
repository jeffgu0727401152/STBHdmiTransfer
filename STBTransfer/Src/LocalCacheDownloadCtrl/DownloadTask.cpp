#include "DownloadTask.h"
#include "LocalCacheDownloadCtrl.h"
#include "../GlobalUIClass.h"
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <iostream>
#include <string>

DownloadTask::DownloadTask()
{
	//
}
DownloadTask::~DownloadTask()
{
	//
}

void DownloadTask::Start(const char* netURLsP)
{
	strcpy(netURLs,netURLsP);
	mDownloadThread.StartThread("CheckOnlineThread", this, 0, STACKSIZE_MIN);
}
void DownloadTask::Stop()
{
	mDownloadThread.StopThread();
}

BOOL DownloadTask::ThreadLoop(
		UINT64 uThreadData)
{

	gDownloadManager->mStartPlay = false;

	char* splitHead = (char*)netURLs;
	char* splitLastHead = splitHead;

	if(NULL == splitHead || splitHead[0] == '\0')
	{
		printf("[startDownloadToTargetLocationWithNetURLs] invalid netURLs\n");
		return false;
	}

	int netWaitCount = 0;
	int localExistedCount = 0;

	while(true)
	{
		char localFileURL[MAX_PATH];
		char netFileURL[MAX_PATH];

		bool breakTag = false;
		splitHead = strchr(splitLastHead, ',');
		if(NULL == splitHead)
		{
			strcpy(netFileURL,splitLastHead);
			breakTag =true;
		}else
		{
			strncpy(netFileURL,splitLastHead,splitHead-splitLastHead);
			netFileURL[splitHead-splitLastHead]='\0';
		}

		strcpy(localFileURL,gDownloadManager->m_location);
		char* fileName = strrchr(netFileURL,'/');
		if(fileName)
		{
			strcat(localFileURL,fileName+1);
		}else
		{
			strcat(localFileURL,netFileURL);
		}
		OPENROOM_DOWNLOAD_UNIT downloadUnit;
		strcpy(downloadUnit.localURL,localFileURL);
		strcpy(downloadUnit.netURL,netFileURL);
		downloadUnit.isDownloading = false;

		if (access(localFileURL, 0) == -1)
		{
			downloadUnit.isLocalExited = false;
		}else
		{
			downloadUnit.isLocalExited = true;
		}

		gDownloadManager->mDownloadList.push_back(downloadUnit);

		//strcat(localURLs,localFileURL);
		if(breakTag)
		{
			break;
		}else
		{
			//strcat(localURLs,",");
		}

		splitLastHead = splitHead+1;
	}

	int count = gDownloadManager->mDownloadList.size();
	for(int i = 0;i<count;i++)
	{
		printf("[netFileURL] %d: %s\n",netWaitCount,gDownloadManager->mDownloadList[i].netURL);
		printf("[localFileURL]%d: %s\n",localExistedCount,gDownloadManager->mDownloadList[i].localURL);
		if(gDownloadManager->mDownloadList[i].isLocalExited)
		{
			localExistedCount++;
			theBaseApp->PostMsg(gDownloadManager, MSG_DOWNLOAD_COMPLETE, 0, 0);
		}else
		{
			netWaitCount++;
			CHttpFileClient sHttpFileClient;
			HttpFileCopyFromServer(&sHttpFileClient,gDownloadManager->mDownloadList[i].netURL,gDownloadManager->mDownloadList[i].localURL,0,gDownloadManager,0);
			gDownloadManager->mDownloadList[i].isLocalExited = true;
			theBaseApp->PostMsg(gDownloadManager, MSG_DOWNLOAD_COMPLETE, 0, 0);
		}
	}

//	printf("[localURLs] %s",localURLs);
	return false;
}
