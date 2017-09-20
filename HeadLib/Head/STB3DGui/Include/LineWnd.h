#pragma once

#include "BaseWnd.h"

class CLineWnd: public CBaseWnd,
	public IE3DRefreshListener
{
	typedef CBaseWnd CParentClass;

public:
	CLineWnd();
	virtual ~CLineWnd();

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
	virtual void OnRefresh();

protected:
	virtual void OnSubclassTouchDown(
		CBaseWnd *pWnd,
		POINT ptWnd);
	virtual void OnSubclassTouchUp(
		CBaseWnd *pWnd,
		POINT ptWnd,
		int xDistance,
		int yDistance,
		UINT64 uUsedTime);
	virtual void OnSubclassTouchMove(
		CBaseWnd *pWnd,
		POINT ptWnd);

public:
	void SetLineBorder(
		int uBorder);
	void SetLineColor(
		UINT32 uColor);
	void SetBkColor(
		UINT32 uColor);

	void LineStart(
		int x,
		int y);
	void LineTo(
		int x,
		int y);
	void Clear(
		RECT *prcRect);

	CImageBuffer* GetLineImageBuffer();
	BOOL HasLocus();

private:
	UINT32 mLineColor;
	UINT32 mBkColor;
	int mLineBorder;

	UINT32* mpColorBuffer;
	CImageBuffer mLineBuffer;
	CImageBuffer mBkGroundBuffer;
	BOOL mBkGroundShown;

	POINT mLastPoint;
	RECT mInvalidRect;
	CImageBuffer mUpdateBuffer;
	CBaseLock mUpdateLock;
};

