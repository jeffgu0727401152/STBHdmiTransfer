#include "DownloadTask.h"
#include "DownloadManager.h"
#include "../GlobalUIClass.h"
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string>

DownloadTask::DownloadTask(const char* urls)
{
	mDownloadThreadExit = FALSE;
	DelArrayList(&mDownloadUrlList, char);

	CPtrArrayCtrl sUrlList;
	const char *cDevString = DevideStringByCharListA(
			urls,
			-1,
			",",
			1,
			FALSE,
			&sUrlList,
			-1);

	for (int i = 0; i < sUrlList.GetCount(); i++)
	{
		const char* cUrl = (const char*)sUrlList.GetAt(i);
		if (cUrl && cUrl[0] && strncmp("http", cUrl, 4) == 0)
		{
			char* cVideoUrl = new char[strlen(cUrl)+1];
			if (cVideoUrl)
			{
				strcpy(cVideoUrl, cUrl);
				mDownloadUrlList.AddData(cVideoUrl);
			}
		}
	}

	Internal_DelArrayA(cDevString);
}

DownloadTask::~DownloadTask()
{
	Stop();
	DelArrayList(&mDownloadUrlList, char);
}

void DownloadTask::Start()
{
	if (mDownloadUrlList.IsEmpty())
	{
		LOGMSG(DBG_LEVEL_W, "%s: empty mDownloadUrlList, do nothing\n",__PRETTY_FUNCTION__);
		return;
	}
	LOGMSG(DBG_LEVEL_I, "%s: DownloadThread start\n",__PRETTY_FUNCTION__);
	mDownloadThread.StartThread("DownloadThread", this, 0, STACKSIZE_MIN);
}
void DownloadTask::Stop()
{
	LOGMSG(DBG_LEVEL_I, "%s: DownloadThread stop\n",__PRETTY_FUNCTION__);
	mDownloadThreadExit = TRUE;
	mHttpFileClient.CloseFile();
	mDownloadThread.StopThread();
}

CPtrListCtrl DownloadTask::GetDownloadList()
{
	return mDownloadUrlList;
}

BOOL DownloadTask::ThreadLoop(UINT64 uThreadData)
{
	int downloadIndex = 0;
	mDownloadThreadExit = FALSE;
	while (mDownloadThreadExit!=TRUE && downloadIndex < mDownloadUrlList.GetCount())
	{
		const char* cVideoUrl = NULL;

		if (mDownloadUrlList.GetCount() > 0)
		{
			cVideoUrl = (const char*)mDownloadUrlList.GetAt(downloadIndex);
			downloadIndex ++;
		}
		else
		{
			return FALSE;
		}

		if (cVideoUrl && cVideoUrl[0])
		{
			if (gDownloadManager->IsLocalCacheAvailable(cVideoUrl)==TRUE)
			{
				LOGMSG(DBG_LEVEL_W, "%s cache is exist, will not download again!\n",cVideoUrl);
				continue;
			}

			char storagePath[MAX_PATH];
			gDownloadManager->GetStoragePathByUrl(storagePath,cVideoUrl);

			LOGMSG(DBG_LEVEL_I, "%s download begin to %s\n",cVideoUrl,storagePath);
			BOOL ret = HttpFileCopyFromServer(&mHttpFileClient,cVideoUrl,storagePath,0,gDownloadManager,(UINT64)cVideoUrl);
			if (ret!=TRUE)
			{
				LOGMSG(DBG_LEVEL_W, "%s download failed\n",cVideoUrl);
				continue;
			}
			do_syscmd(NULL, "sync");

			FILE* fp = fopen(storagePath, "rb");
			if (fp)
			{
				UINT64 size = FileSize(fp);
			    do_syscmd(NULL, "echo %llu > %s.size", size, storagePath);
			    do_syscmd(NULL, "sync");
			    fclose(fp);
			}

			LOGMSG(DBG_LEVEL_I, "%s download success\n",cVideoUrl);
		}
	}
	return FALSE;
}