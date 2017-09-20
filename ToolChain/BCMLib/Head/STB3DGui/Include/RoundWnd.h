#pragma once

#include "BaseWnd.h"

class CRoundWnd: public CBaseWnd
{
	typedef CBaseWnd CParentClass;

public:
	CRoundWnd();
	virtual ~CRoundWnd();

public:
	void Create(
		CE3DCommand *pE3DEngine,
		CBaseWnd *pParent,
		BOOL bHoriz,
		BOOL bStretch,
		UINT32 uFlag=WINDOWFLAG_DEFAULT,
		UINT32 uState=WINDOWSTATE_DEFAULT);

	virtual void ParserXMLNode(
		XMLNode *pNode);

	virtual void OnWindowSizeChange(
		RECT rcOldRelative,
		RECT rcNewRelative);

public:
	int GetHeadLen();
	int GetTailLen();

private:
	void UpdateCenterBkground(
		RECT rcCenter);

public:
	CBaseWnd mHeadWnd;
	CBaseWnd mTailWnd;
	CBaseWnd mCenterWnd;

	BOOL mHoriz;
	BOOL mStretch;
	int mHeadLen;
	int mTailLen;

	CImageBuffer mCenterImageBuffer;
};

