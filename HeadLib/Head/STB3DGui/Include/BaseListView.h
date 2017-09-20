#pragma once

#include "BaseButton.h"

typedef enum ePAGEMOVINGTYPE
{
	PAGEMOVING_TYPE_NOTMOVE=0,
	PAGEMOVING_TYPE_CURPAGE,
	PAGEMOVING_TYPE_PREVPAGE,
	PAGEMOVING_TYPE_NEXTPAGE,
} PAGEMOVINGTYPE;

typedef struct tagLISTVIEWITEM
{
	UINT64 sUserData;
	CBaseButton sItemContainer;

	// CBaseWnd*
	CPtrListCtrl sSubItems;
} LISTVIEWITEM;

typedef struct tagLISTVIEWHEADERBOUNDWND
{
	CBaseWnd sBoundWnd;

	// CBaseWnd*
	CPtrListCtrl sSubHeads;
} LISTVIEWHEADERBOUNDWND;

typedef struct tagLISTVIEWITEMBOUNDWND
{
	CBaseWnd sBoundWnd;
	CPtrListCtrl sItemList;
} LISTVIEWITEMBOUNDWND;

class IListViewListener
{
public:
	virtual ~IListViewListener(void) {}

	virtual CBaseWnd* CreateListViewSubHeader(
		CBaseWnd *pContainer,
		int nSubHeaderIndex)
	{
		return NULL;
	}
	virtual void DeleteListViewSubHeader(
		int nSubHeaderIndex,
		CBaseWnd *pSubHeaderWnd)
	{}
	virtual void ParserListViewHeaderXml(
		int nSubHeaderIndex,
		CBaseWnd *pSubHeaderWnd,
		XMLNode *pParentNode,
		const char *cChildNodeName)
	{}

	virtual CBaseWnd* CreateListViewSubItem(
		CBaseWnd *pContainer,
		int nSubItemIndex)=0;
	virtual void DeleteListViewSubItem(
		int nSubItemIndex,
		CBaseWnd *pSubItemWnd)=0;
	virtual void ParserListViewItemXml(
		int nSubItemIndex,
		CBaseWnd *pSubItemWnd,
		XMLNode *pParentNode,
		const char *cChildNodeName)=0;

	// if subitem == -1, indicate the item container has clicked
	virtual void OnListViewItemTouchDown(
		int nItemIndex,
		int nSubItemIndex,
		CBaseWnd *pSubItemWnd)
	{}
	// if subitem == -1, indicate the item container has clicked
	virtual void OnListViewItemTouchUp(
		int nItemIndex,
		int nSubItemIndex,
		CBaseWnd *pSubItemWnd)
	{}
	// if subitem == -1, indicate the item container has clicked
	virtual void OnListViewItemClicked(
		int nItemIndex,
		int nSubItemIndex,
		CBaseWnd *pSubItemWnd)
	{}
	virtual void OnListViewItemMove(
		int nOldItemIndex,
		int nNewItemIndex)
	{}
	virtual void OnListviewHeaderDraw(
		int nSubItemIndex,
		CBaseWnd *pSubHeaderWnd)
	{}
	// return TRUE if has draw, return FALSE will set this item invisible
	virtual BOOL OnListviewItemDraw(
		int nItemIndex,
		LISTVIEWITEM *pLVItem)
	{
		return FALSE;
	}
	virtual void OnListViewPageIndexChange(
		int nOldPageIndex,
		int nNewPageIndex,
		int nPageCount)
	{}
};

class CBaseListView : public CBaseWnd,
	public IClickEventListener,
	public ITouchEventListener
{
	typedef CBaseWnd CParentClass;

public:
	CBaseListView();
	virtual ~CBaseListView();

public:
	virtual void Create(
		CE3DCommand *pE3DEngine,
		CBaseWnd *pParent,
		IListViewListener *pListener,
		BOOL bEnableMoveItem,
		int nItemCountPerPage,
		int nSubItemCount);

	virtual void ParserXMLNode(
		XMLNode *pNode);

	virtual void OnDestroy();

	virtual void OnWindowVisible(
		BOOL bVisible);

	virtual void OnTimer(
		int nTimerID);

	// interface
public:
	virtual void OnMsg(
		UINT32 uType,
		UINT64 wParam,
		UINT64 lParam);

	virtual void OnClick(
		CBaseWnd *pWnd,
		POINT ptWnd);

	virtual void OnTouchDown(
		CBaseWnd *pWnd,
		POINT ptWnd);
	virtual void OnTouchMove(
		CBaseWnd *pWnd,
		POINT ptWnd);
	virtual void OnTouchUp(
		CBaseWnd *pWnd,
		POINT ptWnd,
		int xDistance,
		int yDistance,
		UINT64 uUsedTime);

public:
	void SetItemCount(
		int nItemCount);
	void SetPageIndex(
		int nPageIndex);
	int GetItemCount();
	int GetCurPageIndex();
	int GetCountPerPage();
	CBaseWnd* GetCurPageSubItem(
		int nItemIndex,
		int nSubIndex);

	void Refresh();
	void PrevPage();
	void NextPage();

private:
	int GetCurPageItemIndexByPoint(
		POINT ptScreen);
	int GetCurPageItemSubIndexByPoint(
		int nItemIndex,
		POINT ptScreen);

	void Reposition();
	void RepositionLVItemBoundWnd(
		LISTVIEWITEMBOUNDWND* pLVItemBoundWnd);

	void CreateLVHeaderBoundWnd(
		CE3DCommand *pE3DEngine);
	void DeleteLVHeaderBoundWnd();
	void ParserLVHeaderBoundWnd(
		XMLNode *pNode);

	void CreateLVItemBoundWnd(
		CE3DCommand *pE3DEngine,
		LISTVIEWITEMBOUNDWND* pLVItemBoundWnd);
	void DeleteLVItemBoundWnd(
		LISTVIEWITEMBOUNDWND* pLVItemBoundWnd);
	void ParserLVItemBoundWnd(
		LISTVIEWITEMBOUNDWND* pLVItemBoundWnd,
		XMLNode *pNode);

	void RefreshInternal();
	void PrevPageInternal();
	void NextPageInternal();

	void RefreshHeader();

	void RefreshPrevPage();
	void RefreshCurPage();
	void RefreshNextPage();

	void MoveCurPage(
		int nOffset);
	void MovePrevPage();
	void MoveNextPage();

	void MovingStep();
	void StopMoving();

private:
	BOOL mEnableMoveItem;

	PAGEMOVINGTYPE mMovingType;
	int mLengthPerStep;

	LISTVIEWHEADERBOUNDWND mLVHeaderBoundWnd;

	LISTVIEWITEMBOUNDWND mLVItemBoundWnd1;
	LISTVIEWITEMBOUNDWND mLVItemBoundWnd2;
	LISTVIEWITEMBOUNDWND mLVItemBoundWnd3;
	LISTVIEWITEMBOUNDWND* mpPrevLVItemBoundWnd;
	LISTVIEWITEMBOUNDWND* mpCurLVItemBoundWnd;
	LISTVIEWITEMBOUNDWND* mpNextLVItemBoundWnd;
	int mItemCount;
	int mSubItemCount;
	int mItemCountPerPage;
	int mCurPageIndex;

	RECT mItemBoundRect;
	SIZE mItemContainerSize;
	SIZE mItemOffsetSize;

	CBaseWnd *mpPressedWnd;
	POINT mPtPressed;
	int mPressedItemIndex;
	int mPressedItemSubIndex;
	int mCurMoveItemIndex;
	LISTVIEWITEM *mpPressedLVItem;
	RECT mRcPressedItem;

	IListViewListener *mpListener;
};
