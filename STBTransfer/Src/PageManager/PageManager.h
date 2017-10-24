#pragma once

#include "BaseApp.h"
#include "BlankPage.h"
#include "SettingModifyPage.h"
#include "SettingInfoPage.h"
#include "PicturePage.h"

typedef enum ePAGE_TYPE
{
	Page_Blank=0,					// 透传页面
	Page_SettingModify,		// 设置页面
	Page_SettingInfo,				// 显示设置页面
	Page_Picture,						// 图片页面
	Page_Count
} PAGE_TYPE;

class CPageManager : public IMessageOwner
{
public:
	CPageManager();
	virtual ~CPageManager();

public:
	void Create(
		CE3DCommand *pE3DEngine,
		CBaseWnd *pParent);

	void SetCurrentPage(
		PAGE_TYPE ePageType);

	PAGE_TYPE GetCurPageType();

	virtual void OnMsg(
		UINT32 uType,
		UINT64 wParam,
		UINT64 lParam);

private:
	virtual void ShowPage();

public:
	CBlankPage mBlankPage;
	CSettingModifyPage mSettingModifyPage;
	CSettingInfoPage mSettingInfoPage;
	CPicturePage mPicturePage;

private:
	PAGE_TYPE mCurPageType;
	PAGE_TYPE mLastPageType;

	CBaseWnd *mpPageWnd[Page_Count];
	CPtrListCtrl mPageList;
	CBaseLock mLock;
};
