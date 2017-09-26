#include "XMLParser.h"
#include "BaseApp.h"
#include "../GlobalUIClass.h"
#include "CloseRoomPage.h"

CCloseRoomPage *gCloseRoomPage=NULL;

CCloseRoomPage::CCloseRoomPage()
{
	gCloseRoomPage = this;

	mCurPlayIndex = 0;
}

CCloseRoomPage::~CCloseRoomPage()
{
	LOGMSG(DBG_LEVEL_I, "function %s quit\n", __PRETTY_FUNCTION__);
}

void CCloseRoomPage::Create(
	CE3DCommand *pE3DEngine,
	CBaseWnd *pParent)
{
	LOGMSG(DBG_LEVEL_I, "%s +++\n", __PRETTY_FUNCTION__);

	CParentClass::Create(
		pE3DEngine,
		"CloseRoomPage",
		pParent,
		WINDOWFLAG_DEFAULT,
		WINDOWSTATE_INVISIBLE);

	LOGMSG(DBG_LEVEL_I, "%s ---\n", __PRETTY_FUNCTION__);
}

void CCloseRoomPage::OnLoadResource()
{
	CParentClass::OnLoadResource();

	UIRESITEM* pItemData =
		theBaseApp->GetResourceItem("xml/CloseRoomPage");
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
	if ( !parser.GetNode("CloseRoomPage", &rootnode) )
	{
		LOGMSG(DBG_LEVEL_E, "failed to Get xml root node %s!!\n", "CloseRoomPage");
		return;
	}

	CParentClass::ParserXMLNode(&rootnode);
}

void CCloseRoomPage::OnWindowVisible(
	BOOL bVisible)
{
	CBaseWnd::OnWindowVisible(bVisible);

	LOGMSG(DBG_LEVEL_I, "======CCloseRoomPage OnWindowVisible=%d======!\n", bVisible);

	if (bVisible)
	{
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

void CCloseRoomPage::OnMsg(
	UINT32 uType,
	UINT64 wParam,
	UINT64 lParam)
{
	CParentClass::OnMsg(uType, wParam, lParam);

	switch(uType)
	{
	case MSG_PLAYER_COMPLETE:
		{
			LOGMSG(DBG_LEVEL_I, "CCloseRoomPage::OnMsg MSG_PLAYER_COMPLETE!\n");
			mLock.Lock();
			int nCount = mVideoUrlList.GetCount();
			mLock.Unlock();
			if (nCount > 0)
			{
				mCurPlayIndex = mCurPlayIndex + 1;
				if (mCurPlayIndex >= nCount)
				{
					mLock.Lock();
					DelArrayList(&mVideoUrlList, char);
					mCurPlayIndex = 0;
					mLock.Unlock();

					UnRegisterBroadcastMsg(MSG_PLAYER_COMPLETE);
					gPageManager->SetCurrentPage(Page_Hdmi);
				}
				else
				{
					// 播放下一个视频
					const char* cVideoUrl = (const char*)mVideoUrlList.GetAt(mCurPlayIndex);
					LOGMSG(DBG_LEVEL_I, "%s:%d, PlayMain!\n", __PRETTY_FUNCTION__, __LINE__);
					gPlayerCtrl->PlayMain(
						"90000000", //SONGID_USER_START
						cVideoUrl, //filepath
						FALSE, //loopplay
						FALSE, //passthrough
						0);
				}
			}
			else
			{
				mLock.Lock();
				DelArrayList(&mVideoUrlList, char);
				mCurPlayIndex = 0;
				mLock.Unlock();

				UnRegisterBroadcastMsg(MSG_PLAYER_COMPLETE);
				gPageManager->SetCurrentPage(Page_Hdmi);
			}
		}
		break;

	default:
		break;
	}
}

void CCloseRoomPage::PerformHttpCmd_CloseRoom(
	const char *cVideoUrlBuffer)
{
	mLock.Lock();
	DelArrayList(&mVideoUrlList, char);
	mCurPlayIndex = 0;
	mLock.Unlock();

	CPtrArrayCtrl sUrlList;
	const char *cDevString = DevideStringByCharListA(
		cVideoUrlBuffer,
		-1,
		",",
		1,
		FALSE,
		&sUrlList,
		-1);

	LOGMSG(DBG_LEVEL_I, "CCloseRoomPage::PerformHttpCmd_CloseRoom cVideoUrlBuffer=%s urlCount=%d!\n", cVideoUrlBuffer, sUrlList.GetCount());

	mLock.Lock();
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
	int nCount = mVideoUrlList.GetCount();
	mLock.Unlock();

	Internal_DelArrayA(cDevString);

	// 播放第一个视频
	if (nCount > 0)
	{
		RegisterBroadcastMsg(MSG_PLAYER_COMPLETE);
		gPageManager->SetCurrentPage(Page_CloseRoom);

		const char* cVideoUrl = (const char*)mVideoUrlList.GetAt(0);

		LOGMSG(DBG_LEVEL_I, "%s:%d, PlayMain!\n", __PRETTY_FUNCTION__, __LINE__);
		gPlayerCtrl->PlayMain(
			"90000000", //SONGID_USER_START
			cVideoUrl, //filepath
			FALSE, //loopplay
			FALSE, //passthrough
			0);
	}
	else
	{
		gPageManager->SetCurrentPage(Page_Hdmi);
	}
}
