#pragma once

#include "E3DCommand.h"

class CE3DCommand;
class CE3DWndEffect : public I3DListViewDataProvider
{
public:
	CE3DWndEffect();
	virtual ~CE3DWndEffect();

public:
	void Create(
		CE3DCommand *pE3DEngine);
	void Delete();

public:
	void SetDisplayParameter(
		RECT rcDisplay,
		float fZorderStart,
		float fZorderEnd);

	void SetBubbleParameter(
		const char* cBubbleImgPath);

	void Show(
		BOOL bVisible);

	// interface
public:
	virtual RESULT GetItemData(
		ITEM_DATA_TYPE type,
		void* data);
	virtual RESULT ReleaseItemData(
		ITEM_DATA_TYPE type,
		const void* data);
	virtual void OnBaseIndexChanged(
		int nNewBaseIndex);

private:
	void FreeBubbleItemList();

private:
	CE3DCommand *mE3DEngine;

	RECT mListCtrlRect;
	float mZorderStart;
	float mZorderEnd;

	I3DListView* mE3DListView;
	I3DListViewEffector *mpEffector;

	CPtrListCtrl mBubbleItemList;
};
