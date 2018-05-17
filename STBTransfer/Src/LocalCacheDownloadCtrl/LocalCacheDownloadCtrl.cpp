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
#include "DownloadTask.h"

DownloadManager::DownloadManager()
{
	memset(m_location,0,sizeof(char)* (MAX_PATH));
	mStartPlay = false;
	playerCurrentIndex = 0;
	mCurrentDownload = NULL;
}
DownloadManager::~DownloadManager()
{
	//
}
// fCurSpeedKBPS: K-Bytes per second
void DownloadManager::OnNetFileCopyProgress(
		UINT64 uUserData,
		UINT64 uHasCopySize,
		UINT64 uNeedCopySize,
		float fCurSpeedKBPS,
		UINT64 *puLimitSpeedBPS)
{
	printf("[DownloadManager::OnNetFileCopyProgress]\n");
	printf("INT64 uUserData %d, UINT64 uHasCopySize %d, UINT64 uNeedCopySize %d, float fCurSpeedKBPS %f, UINT64 *puLimitSpeedBPS %d\n",(int)uUserData,(int)uHasCopySize,(int)uNeedCopySize,fCurSpeedKBPS,(int)*puLimitSpeedBPS);
}

void DownloadManager::OnMsg(
			UINT32 uType,
			UINT64 wParam,
			UINT64 lParam)
{
	if (uType == MSG_DOWNLOAD_COMPLETE)
	{
		if(false == mStartPlay)
		{
			mStartPlay = true;
			collectingDiskInformationAndUpdatePlayerList(0);
		}
	}else if(uType == MSG_PLAYER_COMPLETE)
	{
		if(mStartPlay)
		{
			printf("DownloadManager::OnMsg MSG_PLAYER_COMPLETE mStartPlay here\n");
			collectingDiskInformationAndUpdatePlayerList(1);
		}
	}
}

void DownloadManager::collectingDiskInformationAndUpdatePlayerList(int direction)
{
	int count = mDownloadList.size();
	if(count == 0)
	{
		printf("error\n");
		return;
	}
	if(0 == direction)
	{
		playerCurrentIndex = 0;
	}else
	{
		playerCurrentIndex = (playerCurrentIndex+direction) % count;
	}

	while(access(mDownloadList[playerCurrentIndex].localURL, 0) == -1)
	{
		playerCurrentIndex = (playerCurrentIndex+1) % count;
	}
	gPlayerManager->SetMainPlayerSource(mDownloadList[playerCurrentIndex].localURL, FALSE);
}

void DownloadManager::startDownloadToTargetLocationWithNetURLs(const char* netURLs,char* localURLs)
{
	if(mCurrentDownload == NULL)
	{
		mCurrentDownload = new DownloadTask();
	}else
	{
		mCurrentDownload->Stop();
		delete mCurrentDownload;
		mCurrentDownload = new DownloadTask();
	}

	mCurrentDownload->Start(netURLs);
}

void DownloadManager::setDownloadLocation(const char* location)
{
	if(location)
	{
		if(location[strlen(location)-1] == '/')
		{
			strcpy(m_location,location);
		}else
		{
			strcpy(m_location,location);
			strcat(m_location,"/");
		}
	}else
	{
		printf("can't set location with invalid value.");
	}

    if (access(location, 0) == -1)
    {  
        std::cout<< location <<" is not existing"<<std::endl;
        std::cout<<"now make it"<<std::endl;  
  
        int flag=mkdir(location, 0777);  

        if (flag == 0)  
        {  
            std::cout<<"make successfully"<<std::endl;  
        } else {  
            std::cout<<"make errorly"<<std::endl;  
        }
    }else
    {
    	std::cout<< location <<" is existing"<<std::endl;
    }
}
