#include "FirstLaunchPage.h"

#include "XMLParser.h"
#include "BaseApp.h"
#include "../GlobalUIClass.h"

#define GET_URL_RETRY_COUNT 3

CFirstLaunchPage *gFirshLaunchPage=NULL;

CFirstLaunchPage::CFirstLaunchPage()
{
	gFirshLaunchPage = this;

	mCurPlayIndex = 0;

	mExitThread = FALSE;
}

CFirstLaunchPage::~CFirstLaunchPage()
{
	LOGMSG(DBG_LEVEL_I, "function %s quit\n", __PRETTY_FUNCTION__);
}

void CFirstLaunchPage::Create(
	CE3DCommand *pE3DEngine,
	CBaseWnd *pParent)
{
	LOGMSG(DBG_LEVEL_I, "%s +++\n", __PRETTY_FUNCTION__);

	CParentClass::Create(
		pE3DEngine,
		"FirstLaunchPage",
		pParent,
		WINDOWFLAG_DEFAULT,
		WINDOWSTATE_INVISIBLE);

	LOGMSG(DBG_LEVEL_I, "%s ---\n", __PRETTY_FUNCTION__);
}

void CFirstLaunchPage::OnLoadResource()
{
	CParentClass::OnLoadResource();

	UIRESITEM* pItemData =
		theBaseApp->GetResourceItem("xml/FirstLaunchPage");
	if (!pItemData)
	{
		LOGMSG(DBG_LEVEL_E, "failed to get item, file=%s!!\n", __FILE__);
		return;
	}

	XMLParser parser;
	if(!parser.LoadFromBuffer(&(pItemData->sXmlBuffer)))
	{
		LOGMSG(DBG_LEVEL_E, "failed to load xml buffer, file=%s!!\n", __FILE__);
		return;
	}

	// read from xml
	XMLNode rootnode;
	if ( !parser.GetNode("FirstLaunchPage", &rootnode) )
	{
		LOGMSG(DBG_LEVEL_E, "failed to Get xml root node %s!!\n", "FirstLaunchPage");
		return;
	}

	CParentClass::ParserXMLNode(&rootnode);
}

void CFirstLaunchPage::OnWindowVisible(
	BOOL bVisible)
{
	CBaseWnd::OnWindowVisible(bVisible);

	LOGMSG(DBG_LEVEL_I, "======CFirstLaunchPage OnWindowVisible=%d======!\n", bVisible);

	if (bVisible)
	{
		PerformLaunchVideo();
	}
	else
	{
		UnRegisterBroadcastMsg(MSG_PLAYER_COMPLETE);

		gPlayerCtrl->StopMain();

		mLock.Lock();
		DelArrayList(&mVideoUrlList, char);
		mCurPlayIndex = 0;
		mLock.Unlock();
	}
}

void CFirstLaunchPage::OnMsg(
	UINT32 uType,
	UINT64 wParam,
	UINT64 lParam)
{
	CParentClass::OnMsg(uType, wParam, lParam);

	switch(uType)
	{
	case MSG_PLAYER_COMPLETE:
		if (IsWindowVisible())
		{
			LOGMSG(DBG_LEVEL_I, "CFirstLaunchPage::OnMsg MSG_PLAYER_COMPLETE!\n");

			if (lParam == PlayComplete_ReasonType_StartError)
			{
				LOGMSG(DBG_LEVEL_E, "CFirstLaunchPage, play failed, idx = %d, total video = %d!\n",
						mCurPlayIndex, mVideoUrlList.GetCount());
				mLock.Lock();
				mVideoUrlList.DeleteAt(mCurPlayIndex);
				mCurPlayIndex--;
				mLock.Unlock();
			}

			char cVideoUrlLocal[MAX_PATH] = {0};

			mLock.Lock();
			int nCount = mVideoUrlList.GetCount();
			if (nCount > 0)
			{
				mCurPlayIndex = (mCurPlayIndex+1) % nCount;
				// 播放下一个视频
				const char* cVideoUrl = (const char*)mVideoUrlList.GetAt(mCurPlayIndex);
				SAFE_STRNCPY(cVideoUrlLocal, cVideoUrl, MAX_PATH);
			}
			mLock.Unlock();

			if (cVideoUrlLocal[0])
			{
				LOGMSG(DBG_LEVEL_I, "%s:%d, PlayMain!\n", __PRETTY_FUNCTION__, __LINE__);
				gPlayerCtrl->PlayMain(
					"90000000", //SONGID_USER_START
					cVideoUrlLocal, //filepath
					FALSE, //loopplay
					FALSE, //passthrough
					0);
			}
			else
			{
				LOGMSG(DBG_LEVEL_I, "%s:%d, mVideoUrlList empty,show hdmi page!\n", __PRETTY_FUNCTION__, __LINE__);
				gPageManager->SetCurrentPage(Page_Hdmi);
			}
		}
		break;

	default:
		break;
	}
}

BOOL CFirstLaunchPage::ThreadLoop(
	UINT64 uThreadData)
{
	CSimpleStringA sURLs;
	BOOL clientOpenResult = FALSE;
	UINT32 clientOpenUrlRequestCount = 0;

	while (!mExitThread)
	{
		clientOpenUrlRequestCount++;
		if(clientOpenUrlRequestCount > GET_URL_RETRY_COUNT)
		{
			LOGMSG(DBG_LEVEL_W, "%s:%d, reach the GET_URL_RETRY_COUNT, break threadloop!\n", __PRETTY_FUNCTION__, __LINE__);
			break;
		}

		do
		{
			clientOpenResult = gHttpCmdClient->ClientOpen(gKTVConfig.GetVodIP(),&sURLs);
		} while (0);

		if (clientOpenResult==TRUE)
		{
			mLock.Lock();
			DelArrayList(&mVideoUrlList, char);

			CPtrArrayCtrl sUrlList;
			const char *cDevString = DevideStringByCharListA(
				sURLs.GetString(),
				-1,
				",",
				1,
				FALSE,
				&sUrlList,
				-1);

			for (int i = 0; i < sUrlList.GetCount(); i++)
			{
				const char* cUrl = (const char*)sUrlList.GetAt(i);
				if (cUrl && cUrl[0])
				{
					char* cVideoUrl = new char[strlen(cUrl)+1];
					if (cVideoUrl)
					{
						strcpy(cVideoUrl, cUrl);
						mVideoUrlList.AddData(cVideoUrl);
					}
				}
			}

			Internal_DelArrayA(cDevString);

			LOGMSG(DBG_LEVEL_I, "%s:%d, GetClientOpenUrl get %d urls!\n", __PRETTY_FUNCTION__, __LINE__,mVideoUrlList.GetCount());

			mLock.Unlock();
			break;
		}
		mExitEvent.Wait(2000);
	}

	if (mVideoUrlList.GetCount()>0)
	{
		LOGMSG(DBG_LEVEL_I, "FirstLaunch Get mVideoUrlList, try to change page\n");
		PAGE_TYPE currentPage  = gPageManager->GetCurPageType();
		if(Page_Hdmi == currentPage)
		{
			LOGMSG(DBG_LEVEL_I, "FirstLaunch Change page from Page_Hdmi to FirstLaunch\n");
			gPageManager->SetCurrentPage(Page_FirstLaunch);
		}
	}

	return FALSE;
}

void CFirstLaunchPage::StartGetClientOpenUrl()
{
	mExitThread = FALSE;
	mExitEvent.Reset();
	mGetOpenVideoUrlThread.StartThread("GetClientOpenUrlThread", this, 0, STACKSIZE_MIN);
}

void CFirstLaunchPage::StopGetClientOpenUrl()
{
	mExitThread = TRUE;
	mExitEvent.Set();
	mGetOpenVideoUrlThread.StopThread();
}

void CFirstLaunchPage::PerformLaunchVideo()
{
	mLock.Lock();

	mCurPlayIndex = 0;
	int nCount = mVideoUrlList.GetCount();
	char cVideoUrlLocal[MAX_PATH] = {0};
	const char* cVideoUrl = (const char*)mVideoUrlList.GetAt(0);
	SAFE_STRNCPY(cVideoUrlLocal, cVideoUrl, MAX_PATH);

	mLock.Unlock();

	// 播放第一个视频
	if (nCount  > 0 && cVideoUrlLocal[0])
	{
		RegisterBroadcastMsg(MSG_PLAYER_COMPLETE);
		gPageManager->SetCurrentPage(Page_FirstLaunch);

		LOGMSG(DBG_LEVEL_I, "%s:%d, PlayMain!\n", __PRETTY_FUNCTION__, __LINE__);
		gPlayerCtrl->PlayMain(
			"90000000", //SONGID_USER_START
			cVideoUrlLocal, //filepath
			FALSE, //loopplay
			FALSE, //passthrough
			0);
	}
	else
	{
		LOGMSG(DBG_LEVEL_I, "%s:%d, mVideoUrlList empty,show hdmi page!\n", __PRETTY_FUNCTION__, __LINE__);
		gPageManager->SetCurrentPage(Page_Hdmi);
	}
}
