#pragma once

#include "BaseWnd.h"

class CPopupWndManager
{
public:
	CPopupWndManager();
	virtual ~CPopupWndManager();

public:
	void AddPopupWnd(
		CBaseWnd *pPopupWnd,
		int nIndex);

	void DelPopupWnd(
		CBaseWnd *pPopupWnd);

	BOOL BringToTop(
		CBaseWnd *pPopupWnd);

	CBaseWnd* FindWndByPoint(
		POINT ptScreen,
		float fMinZorder,
		float fMaxZorder);

	CBaseWnd* FindWndByRect(
		RECT rcScreen,
		float fMinZorder,
		float fMaxZorder);

	void UpdatePopupZorder(
		float *pfZorder,
		float fZorderDelta,
		BOOL bVisibleOnly);

	void DumpPopupWndList();

private:
	BOOL BringToTopInternal(
		CBaseWnd *pPopupWnd);

private:
	CPtrListCtrl mPopupWndList;
	CBaseLock mPopupWndListLock;
};
