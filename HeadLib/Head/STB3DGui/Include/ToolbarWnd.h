#pragma once

#include "PopupWnd.h"

class IToolbarListener
{
public:
	virtual ~IToolbarListener(void) {}

	virtual CBaseWnd* CreateToolbarItem(
		CBaseWnd *pParentWnd,
		int nItemIndex)=0;
	virtual void DeleteToolbarItem(
		int nItemIndex,
		CBaseWnd *pItemWnd)=0;
	virtual void ParserToolbarItemXml(
		int nItemIndex,
		CBaseWnd *pItemWnd,
		XMLNode *pParentNode,
		const char *cChildNodeName)=0;
	virtual void OnToolbarItemClick(
		int nItemIndex)=0;
};

class CToolbarWnd : public CPopupWnd,
	public IClickEventListener
{
	typedef CPopupWnd CParentClass;

public:
	CToolbarWnd();
	virtual ~CToolbarWnd();

public:
	virtual void Create(
		CE3DCommand *pE3DEngine,
		CBaseWnd *pParent,
		IToolbarListener *pToolbarListener,
		int nMaxItemCount);

	virtual void ParserXMLNode(
		XMLNode *pNode);

	virtual void OnDestroy();

	// interface
public:
	virtual void OnClick(
		CBaseWnd *pWnd,
		POINT ptWnd);

public:
	CBaseWnd* GetItem(
		int nItemIndex);
	void SetItemVisible(
		int nItemIndex,
		BOOL bVisible);

private:
	void UpdateToolbar();

private:
	CPtrListCtrl mItemButtonList;
	SIZE mItemSize;
	int mXOffset;
	int mYOffset;

	IToolbarListener *mpToolbarListener;
};
