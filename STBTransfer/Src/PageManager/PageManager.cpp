#include "PageManager.h"
#include "BaseApp.h"
#include "../GlobalUIClass.h"

const char* gPageName[Page_Count] =
{
	"Page_Blank",
	"Page_SettingModify",
	"Page_SettingInfo",
	"Page_Picture",
};

CPageManager::CPageManager()
{
	mLastPageType = Page_Blank;
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

	mBlankPage.Create(pE3DEngine, pParent);
	mSettingModifyPage.Create(pE3DEngine, pParent);
	mSettingInfoPage.Create(pE3DEngine, pParent);
	mPicturePage.Create(pE3DEngine, pParent);

	mpPageWnd[Page_Blank] = &mBlankPage;
	mpPageWnd[Page_SettingModify] = &mSettingModifyPage;
	mpPageWnd[Page_SettingInfo] = &mSettingInfoPage;
	mpPageWnd[Page_Picture] = &mPicturePage;

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
	theBaseApp->PostMsg(this, MSG_PAGESWITCH, ePageType, 0);
}

PAGE_TYPE CPageManager::GetCurPageType()
{
	return mCurPageType;
}

void CPageManager::OnMsg(
		UINT32 uType,
		UINT64 wParam,
		UINT64 lParam)
{
	if (uType == MSG_PAGESWITCH)
	{
		PAGE_TYPE ePageType = (PAGE_TYPE)wParam;

		mLock.Lock();

		if (ePageType != mCurPageType)
		{
			if(Page_SettingModify == ePageType || Page_SettingInfo == ePageType)
			{
				theBaseApp->ForceShowCursor(TRUE);
				theBaseApp->EnableDrawCursor(TRUE);

			}
			else
			{
				theBaseApp->ForceShowCursor(FALSE);
				theBaseApp->EnableDrawCursor(FALSE);
			}
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
