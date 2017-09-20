#pragma once

#include "BaseWnd.h"
#include "BaseButton.h"

class ISpinPositionChangeEventListener
{
public:
	virtual ~ISpinPositionChangeEventListener(void) {}

	virtual void OnSpinPositionChange(
		CBaseWnd *pWnd,
		int nOldPosition,
		int nNewPosition,
		BOOL bChangeEnd)=0;
};

class CBaseSpin: public CBaseWnd,
	public ITouchEventListener
{
	typedef CBaseWnd CParentClass;

public:
	CBaseSpin();
	virtual ~CBaseSpin();

public:
	virtual void Create(
		CE3DCommand *pE3DEngine,
		CBaseWnd *pParent,
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
	virtual void SetWindowTextA(
		const char *cText);
	virtual void SetWindowTextW(
		const wchar_t *wszText);
	virtual const wchar_t* GetWindowTextW();

	void SetSpinPromptTextA(
		const char* cText);
	void SetSpinPromptTextW(
		const wchar_t *wszText);

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
	int GetDefault();

	void SetOnTouchListener(
		ITouchEventListener *pOnTouchListener);

	void SetOnPositionChangeListener(
		ISpinPositionChangeEventListener *pOnPositionChangeListener);

public:
	int mMin;
	int mMax;
	int mPos;
	int mDefault;

	CBaseWnd mPromptWnd;
	CBaseButton mDownBtn;
	CBaseWnd mValueWnd;
	CBaseButton mUpBtn;

	CBaseWnd* mpPressedWnd;

	ITouchEventListener *mpCustomOnTouchListener;

	int mIntervalIndex;
	ISpinPositionChangeEventListener *mpOnPositionChangeListener;
};
