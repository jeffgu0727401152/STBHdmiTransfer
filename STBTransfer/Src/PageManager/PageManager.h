#pragma once

#include "HdmiPage.h"
#include "SettingModifyPage.h"
#include "SettingInfoPage.h"
#include "PausePage.h"
#include "CloseRoomPage.h"
#include "OpenRoomPage.h"

typedef enum ePAGE_TYPE
{
	Page_Hdmi=0,				// HDMI 页面
	Page_SettingModify,		// 设置页面
	Page_SettingInfo,			// 显示设置页面
	Page_Pause,					// 暂停页面
	Page_CloseRoom,			// 关房页面
	Page_OpenRoom,			// 开放页面
	Page_Count
} PAGE_TYPE;

class CPageManager
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

private:
	virtual void ShowPage();

public:
	CHdmiPage mHdmiPage;
	CSettingModifyPage mSettingModifyPage;
	CSettingInfoPage mSettingInfoPage;
	CPausePage mPausePage;
	CCloseRoomPage mCloseRoomPage;
	COpenRoomPage mOpenRoomPage;

private:
	PAGE_TYPE mCurPageType;
	PAGE_TYPE mLastPageType;

	CBaseWnd *mpPageWnd[Page_Count];
	CPtrListCtrl mPageList;
	CBaseLock mLock;
};
