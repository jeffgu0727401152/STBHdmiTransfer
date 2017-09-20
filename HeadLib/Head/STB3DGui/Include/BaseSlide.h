#pragma once

#include "BaseWnd.h"
#include "BaseButton.h"
#include "RoundWnd.h"

class ISlidePositionChangeEventListener
{
public:
	virtual ~ISlidePositionChangeEventListener(void) {}

	virtual void OnSlidePositionChange(
		CBaseWnd *pWnd,
		int nOldPosition,
		int nNewPosition,
		BOOL bChangeEnd)=0;
};

class CBaseSlide: public CBaseWnd,
	public ITouchEventListener
{
	typedef CBaseWnd CParentClass;

public:
	CBaseSlide();
	virtual ~CBaseSlide();

public:
	// bHorzSlide: 1: Horizontal slide; 0: vertical
	// bRevert: Horizontal slide; 1: from right to left 0: from left to right
	//	                 vertical slide; 1: from top to bottom 0: from bottom to top
	virtual void Create(
		CE3DCommand *pE3DEngine,
		CBaseWnd *pParent,
		BOOL bHorizSlide,
		BOOL bRevert,
		BOOL bProcessWndStretch=TRUE,
		UINT32 uFlag=WINDOWFLAG_DEFAULT,
		UINT32 uState=WINDOWSTATE_DEFAULT);

	virtual void ParserXMLNode(
		XMLNode *pNode);

	virtual void OnTimer(
		int nTimerID);

	// interface
public:
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
	void SetSlidePosition(
		RECT rcSlide,
		RECT rcBar,
		RECT rcThumb,
		RECT rcHeadBtn,
		RECT rcTailBtn);

	void SetMinMax(
		int nMin,
		int nMax);
	void SetPos(
		int nPos);
	void SetPos(
		int nPos,
		BOOL bNotifyListener,
		BOOL bNotifyOnlyPosChanged);
	void SetDefault(
		int nDefault);

	int GetPos();
	int GetMin();
	int GetMax();
	int GetLength();
	int GetDefault();

	void SetOnTouchListener(
		ITouchEventListener *pOnTouchListener);

	void SetOnPositionChangeListener(
		ISlidePositionChangeEventListener *pOnPositionChangeListener);

private:
	void GetThumbRectByPos(
		POINT ptBar,
		RECT *prcThumb,
		RECT *prcProcess);
	int GetPosByThumbRect(
		RECT rcThumb);
	void Update();
	BOOL UpdatePos(
		int nPos);

public:
	int mMin;
	int mMax;
	int mPos;
	int mDefault;

	BOOL mHorizSlide;
	BOOL mRevert;
	BOOL mThumbPressed;

	CBaseWnd mBarWnd;
	CRoundWnd mProcessWnd;
	CBaseButton mThumbBtn;
	CBaseButton mHeadBtn;
	CBaseButton mTailBtn;

	CBaseWnd* mpPressedWnd;

	int mIntervalIndex;

	ITouchEventListener *mpCustomOnTouchListener;
	ISlidePositionChangeEventListener *mpOnPositionChangeListener;
};
