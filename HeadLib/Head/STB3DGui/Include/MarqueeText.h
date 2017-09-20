#pragma once

#include "BaseWnd.h"

class IMarqueeTextListener
{
public:
	virtual ~IMarqueeTextListener(void) {}

	virtual void OnMarqueeRepeat(
		CBaseWnd *pWnd)=0;
};

class CMarqueeText: public CBaseWnd,
	public IThreadFuncInterface
{
	typedef CBaseWnd CParentClass;

public:
	CMarqueeText();
	virtual ~CMarqueeText();

public:
	void Create(
		CE3DCommand *pE3DEngine,
		CBaseWnd *pParent,
		UINT32 uFlag=WINDOWFLAG_DEFAULT,
		UINT32 uState=WINDOWSTATE_DEFAULT);

	virtual void ParserXMLNode(
		XMLNode *pNode);

	virtual void OnDestroy();

	virtual void OnWindowVisible(
		BOOL bVisible);

	// interface
public:
	virtual BOOL ThreadLoop(
		UINT64 uThreadData);

public:
	void SetMarqueeTextListener(
		IMarqueeTextListener *pListener);

	void SetMarqueeParam(
		int nUpdateInterval,
		int nLengthPerStep);

	void Reset();

	void SetMarqueeText(
		const char *cText);
	void SetMarqueeText(
		const wchar_t *wszText);

private:
	void UpdateMarqueeTextPos(
		int nMoveLength);

private:
	CBaseWnd mLeftTextWnd;
	CBaseWnd mRightTextWnd;

	CBaseLock mLock;
	CPtrListCtrl mBkTextureList;
	int mTextureWidth;
	int mTextureHeight;
	int mLeftWndTextureIndex;

	int mUpdateInterval;//ms
	int mLengthPerStep;

	int mMarqueeLength;
	int mHideLength;

	CBaseThread mUpdateThread;
	CBaseEvent mStopEvent;
	BOOL mExitThread;

	IMarqueeTextListener* mpMarqueeTextListener;
};

