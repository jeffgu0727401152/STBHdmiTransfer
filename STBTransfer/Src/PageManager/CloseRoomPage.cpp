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

	if (bVisible)
	{
	}
	else
	{
		gPlayerCtrl->StopMain();

		DelArrayList(&mVideoUrlList, char);
		mCurPlayIndex = 0;

		UnRegisterBroadcastMsg(MSG_PLAYER_COMPLETE);
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
		if (mVideoUrlList.GetCount() > 0)
		{
			mCurPlayIndex = (mCurPlayIndex+1) % mVideoUrlList.GetCount();
			if (mCurPlayIndex == mVideoUrlList.GetCount())
			{
				DelArrayList(&mVideoUrlList, char);
				mCurPlayIndex = 0;

				UnRegisterBroadcastMsg(MSG_PLAYER_COMPLETE);
				gPageManager->SetCurrentPage(Page_Hdmi);
			}
			else
			{
				// 播放下一个视频
				const char* cVideoUrl = (const char*)mVideoUrlList.GetAt(mCurPlayIndex);
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
			DelArrayList(&mVideoUrlList, char);
			mCurPlayIndex = 0;

			UnRegisterBroadcastMsg(MSG_PLAYER_COMPLETE);
			gPageManager->SetCurrentPage(Page_Hdmi);
		}
		break;

	default:
		break;
	}
}

void CCloseRoomPage::PerformHttpCmd_CloseRoom(
	const char *cVideoUrlBuffer)
{
	DelArrayList(&mVideoUrlList, char);
	mCurPlayIndex = 0;

	CPtrArrayCtrl sUrlList;
	const char *cDevString = DevideStringByCharListA(
		cVideoUrlBuffer,
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

	// 播放第一个视频
	if (mVideoUrlList.GetCount() > 0)
	{
		RegisterBroadcastMsg(MSG_PLAYER_COMPLETE);
		gPageManager->SetCurrentPage(Page_CloseRoom);

		const char* cVideoUrl = (const char*)mVideoUrlList.GetAt(0);
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
