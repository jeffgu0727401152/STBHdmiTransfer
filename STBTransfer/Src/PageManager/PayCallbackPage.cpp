#include "XMLParser.h"
#include "BaseApp.h"
#include "../GlobalUIClass.h"
#include "PayCallbackPage.h"

CPayCallbackPage *gPayCallbackPage=NULL;

CPayCallbackPage::CPayCallbackPage()
{
	gPayCallbackPage = this;

	mCurPlayIndex = 0;
}

CPayCallbackPage::~CPayCallbackPage()
{
	LOGMSG(DBG_LEVEL_I, "function %s quit\n", __PRETTY_FUNCTION__);
}

void CPayCallbackPage::Create(
	CE3DCommand *pE3DEngine,
	CBaseWnd *pParent)
{
	LOGMSG(DBG_LEVEL_I, "%s +++\n", __PRETTY_FUNCTION__);

	CParentClass::Create(
		pE3DEngine,
		"PayCallbackPage",
		pParent,
		WINDOWFLAG_DEFAULT,
		WINDOWSTATE_INVISIBLE);

	LOGMSG(DBG_LEVEL_I, "%s ---\n", __PRETTY_FUNCTION__);
}

void CPayCallbackPage::OnLoadResource()
{
	CParentClass::OnLoadResource();

	UIRESITEM* pItemData =
		theBaseApp->GetResourceItem("xml/PayCallbackPage");
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
	if ( !parser.GetNode("PayCallbackPage", &rootnode) )
	{
		LOGMSG(DBG_LEVEL_E, "failed to Get xml root node %s!!\n", "PayCallbackPage");
		return;
	}

	CParentClass::ParserXMLNode(&rootnode);
}

void CPayCallbackPage::OnWindowVisible(
	BOOL bVisible)
{
	CBaseWnd::OnWindowVisible(bVisible);

	LOGMSG(DBG_LEVEL_I, "======CPayCallbackPage OnWindowVisible=%d======!\n", bVisible);

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

void CPayCallbackPage::OnMsg(
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
			LOGMSG(DBG_LEVEL_I, "CPayCallbackPage::OnMsg MSG_PLAYER_COMPLETE!\n");

			BOOL bAllPlayComplete = FALSE;
			char cVideoUrlLocal[MAX_PATH] = {0};

			mLock.Lock();

			int nCount = mVideoUrlList.GetCount();
			if (nCount > 0)
			{
				mCurPlayIndex = mCurPlayIndex + 1;
				if (mCurPlayIndex >= nCount)
				{
					DelArrayList(&mVideoUrlList, char);
					mCurPlayIndex = 0;
					bAllPlayComplete = TRUE;
				}
				else
				{
					// 播放下一个视频
					const char* cVideoUrl = (const char*)mVideoUrlList.GetAt(mCurPlayIndex);
					SAFE_STRNCPY(cVideoUrlLocal, cVideoUrl, MAX_PATH);
				}
			}
			else
			{
				DelArrayList(&mVideoUrlList, char);
				mCurPlayIndex = 0;
				bAllPlayComplete = TRUE;
			}

			mLock.Unlock();

			if (bAllPlayComplete)
			{
				UnRegisterBroadcastMsg(MSG_PLAYER_COMPLETE);
				gPageManager->SetCurrentPage(Page_Hdmi);
			}
			else if (cVideoUrlLocal[0])
			{
				LOGMSG(DBG_LEVEL_I, "%s:%d, PlayMain!\n", __PRETTY_FUNCTION__, __LINE__);
				gPlayerCtrl->PlayMain(
					"90000000", //SONGID_USER_START
					cVideoUrlLocal, //filepath
					FALSE, //loopplay
					FALSE, //passthrough
					0);
			}
		}
		break;

	default:
		break;
	}
}

void CPayCallbackPage::PerformHttpCmd_PayCallback(
	const char *cVideoUrlBuffer)
{
	mLock.Lock();

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

	LOGMSG(DBG_LEVEL_I, "CPayCallbackPage::PerformHttpCmd_PayCallback cVideoUrlBuffer=%s urlCount=%d!\n", cVideoUrlBuffer, sUrlList.GetCount());

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

	int nCount = mVideoUrlList.GetCount();

	char cVideoUrlLocal[MAX_PATH] = {0};
	const char* cVideoUrl = (const char*)mVideoUrlList.GetAt(0);
	SAFE_STRNCPY(cVideoUrlLocal, cVideoUrl, MAX_PATH);

	mLock.Unlock();

	// 播放第一个视频
	if (nCount > 0 && cVideoUrlLocal[0])
	{
		RegisterBroadcastMsg(MSG_PLAYER_COMPLETE);
		gPageManager->SetCurrentPage(Page_PayCallback);

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
		gPageManager->SetCurrentPage(Page_Hdmi);
	}
}
