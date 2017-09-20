#pragma once

#include "BaseWnd.h"
#include "E2DEffectFly.h"

class ISlideWndListener
{
public:
	virtual ~ISlideWndListener(void) {}

	virtual void OnSlideStart(
		CBaseWnd *pWnd,
		BOOL bEndVisible,
		UINT64 uUserData)
	{}

	virtual void OnSlideStep(
		CBaseWnd *pWnd,
		int nCurStep,
		int nTotalStep,
		UINT64 uUserData)
	{}

	virtual void OnSlideEnd(
		CBaseWnd *pWnd,
		BOOL bEndVisible,
		UINT64 uUserData)
	{}
};

class CSlideWnd: public CBaseWnd,
	public IE2DEffectListener
{
	typedef CBaseWnd CParentClass;

public:
	CSlideWnd();
	virtual ~CSlideWnd();

public:
	virtual void Create(
		CE3DCommand *pE3DEngine,
		const char *cClassName,
		CBaseWnd *pParent,
		UINT32 uFlag,
		UINT32 uState);

	virtual void ParserXMLNode(
		XMLNode *pNode);

	virtual void SetWindowVisible(
		BOOL bVisible);

	// interface
public:
	virtual void OnEffetStart(
		CE2DEffect *pEffect,
		UINT64 uUserData);
	virtual void OnEffetStep(
		CE2DEffect *pEffect,
		UINT64 uUserData,
		int nCurStep,
		int nTotalStep);
	virtual void OnEffetStop(
		CE2DEffect *pEffect,
		UINT64 uUserData);

public:
	void SetHidePosition(
		RECT rcHide);

	void SetSlideParameter(
		ISlideWndListener *pOnSlideWndListener=NULL,
		UINT64 uUserData=0,
		UINT64 uSlideMS=300);

public:
	void OnEnumChildWnd(
		CBaseWnd *pChildWnd);

private:
	void InitFlyItem();

private:
	BOOL mSliding;

	CE2DEffectFly mFlyEffect;

	ISlideWndListener *mpOnSlideWndListener;
	UINT64 mUserData;
	UINT64 mSlideTime;

	BOOL mEndVisible;
	RECT mrcHide;
};
