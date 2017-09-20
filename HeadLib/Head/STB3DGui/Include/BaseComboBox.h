#pragma once

#include "BaseButton.h"
#include "PopupWnd.h"

typedef struct tagCOMBOITEM
{
	CSimpleStringA sDescripeText;
	UINT64 uUserData;

	CImageBuffer sTextImageBuffer;
} COMBOITEM;

class IComboBoxSelectListener
{
public:
	virtual ~IComboBoxSelectListener(void) {}

	virtual void OnComboBoxSelectItem(
		CBaseWnd* pWnd,
		int nItemIndex,
		COMBOITEM *pItem)
	{}
};

class CBaseComboBox: public CBaseWnd,
	public IClickEventListener,
	public ITouchEventListener
{
	typedef CBaseWnd CParentClass;

public:
	CBaseComboBox();
	virtual ~CBaseComboBox();

public:
	void Create(
		CE3DCommand *pE3DEngine,
		CBaseWnd *pParent,
		UINT32 uFlag=WINDOWFLAG_DEFAULT,
		UINT32 uState=WINDOWSTATE_DEFAULT);

	virtual void ParserXMLNode(
		XMLNode *pNode);

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
	virtual void OnTouchLeave(
		CBaseWnd *pOldTouchWnd,
		CBaseWnd *pNewTouchWnd);

public:
	void SetComboBoxSelectListener(
		IComboBoxSelectListener *pComboBoxSelectListener);

	int FindItem(
		const char* cDescripeText,
		BOOL bIgnoreCase);

	void AddComboItem(
		const char* cDescripeText,
		UINT64 uUserData,
		int nIndex=-1);

	void DeleteItem(
		int nIndex);

	void DeleteAllItem();

	void SetSelectIndex(
		int nItemIndex,
		BOOL bNotifyListener);

	int GetSelectIndex();

private:
	int GetComboItemByPoint(
		POINT ptCombo);

	void UpdateComboWnd();

	void CreateImageBufferWithSpecialSelectedIndex(
		int nSelectedIndex,
		CImageBuffer *pImageBuffer);

private:
	CBaseButton mTitleBtn;
	CPopupWnd mComboWnd;

	CImageBuffer mComboBkImageBuffer;
	int mXOffset;
	int mYOffset;

	CImageBuffer mItemBkImageBuffer;
	CImageBuffer mSelectedItemBkImageBuffer;
	int mItemHeight;

	IComboBoxSelectListener *mpComboBoxSelectListener;
	CPtrListCtrl mComboItemList;
	int mSelecteItemIndex;

	int mPressedItemIndex;
	BOOL mIsTouchDown;
};

