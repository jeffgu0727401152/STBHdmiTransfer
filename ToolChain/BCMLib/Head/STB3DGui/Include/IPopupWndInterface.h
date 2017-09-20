#pragma once

#include "BaseWnd.h"

class IPopupWndInterface
{
public:
	IPopupWndInterface();
	virtual ~IPopupWndInterface();

public:
	void OnPopupWndActivate(
		CBaseWnd *pWnd,
		BOOL bActivate);

public:
	void SetAutoHideWhenInactive(
		BOOL bAutoHideWhenInactive);
	BOOL IsAutoHideWhenInactive();

	// 点击到如下窗口时，不会auto hide
	void AddNonAutoHideWnd(
		CBaseWnd *pWnd);

private:
	BOOL mbAutoHideWhenInactive;
	CPtrListCtrl mNonAutoHideWndList;
};
