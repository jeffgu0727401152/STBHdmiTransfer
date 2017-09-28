#include "PageManager.h"
#include "BaseApp.h"

const char* gPageName[Page_Count] =
{
	"Page_Hdmi",
	"Page_SettingModify",
	"Page_SettingInfo",
	"Page_Pause",
	"Page_CloseRoom",
	"Page_OpenRoom",
	"Page_FirstLanch"
};

CPageManager::CPageManager()
{
	mLastPageType = Page_Hdmi;
	mCurPageType = Page_Count;
}

CPageManager::~CPageManager()
{
	LOGMSG(DBG_LEVEL_I, "function %s quit\n", __PRETTY_FUNCTION__);
}

void CPageManager::Create(
	CE3DCommand *pE3DEngine,
	CBaseWnd *pParent)
{
	LOGMSG(DBG_LEVEL_I, "%s +++\n", __PRETTY_FUNCTION__);

	mHdmiPage.Create(pE3DEngine, pParent);
	mSettingModifyPage.Create(pE3DEngine, pParent);
	mSettingInfoPage.Create(pE3DEngine, pParent);
	mPausePage.Create(pE3DEngine, pParent);
	mCloseRoomPage.Create(pE3DEngine, pParent);
	mOpenRoomPage.Create(pE3DEngine, pParent);
	mFirstLanchPage.Create(pE3DEngine, pParent);

	mpPageWnd[Page_Hdmi] = &mHdmiPage;
	mpPageWnd[Page_SettingModify] = &mSettingModifyPage;
	mpPageWnd[Page_SettingInfo] = &mSettingInfoPage;
	mpPageWnd[Page_Pause] = &mPausePage;
	mpPageWnd[Page_CloseRoom] = &mCloseRoomPage;
	mpPageWnd[Page_OpenRoom] = &mOpenRoomPage;
	mpPageWnd[Page_FirstLaunch] = &mFirstLanchPage;

	int i;
	for ( i = 0; i < Page_Count; i++ )
	{
		mPageList.AddData((const void *)((UINT64)i));
	}

	LOGMSG(DBG_LEVEL_I, "%s ---\n", __PRETTY_FUNCTION__);
}

void CPageManager::SetCurrentPage(
	PAGE_TYPE ePageType)
{
	mLock.Lock();

	if (ePageType != mCurPageType)
	{
		int nIndex = mPageList.FindFirst(
			(const void *)((UINT64)ePageType));
		if (nIndex >= 0)
		{
			mPageList.MoveData(nIndex, 1, 0);
			ShowPage();
		}
	}

	mLock.Unlock();
}

PAGE_TYPE CPageManager::GetCurPageType()
{
	return mCurPageType;
}

void CPageManager::ShowPage()
{
	mCurPageType = (PAGE_TYPE)((UINT64)mPageList.GetAt(0));
	LOGMSG(DBG_LEVEL_I, "ShowPage %s\n", gPageName[mCurPageType]);

	int nPageCount = mPageList.GetCount();
	int i;
	for (i = 1; i < nPageCount; i++)
	{
		PAGE_TYPE ePageType =
			(PAGE_TYPE)((UINT64)mPageList.GetAt(i));
		mpPageWnd[ePageType]->SetWindowVisible(FALSE);
	}

	mpPageWnd[mCurPageType]->SetWindowVisible(TRUE);
	CBaseWnd *pFocusWnd = mpPageWnd[mCurPageType]->FindFirstCanFocusWnd();;
	if (pFocusWnd)
	{
		theBaseApp->SetFocusWnd(pFocusWnd);
	}
}
