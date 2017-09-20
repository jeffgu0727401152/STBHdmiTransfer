#pragma once

#include "PopupWnd.h"

class CLevelWnd : public CBaseWnd
{
	typedef CBaseWnd CParentClass;

public:
	CLevelWnd();
	virtual ~CLevelWnd();

public:
	virtual void Create(
		CE3DCommand *pE3DEngine,
		CBaseWnd *pParent,
		BOOL bHorzLevel,
		BOOL bRevert);

	virtual void ParserXMLNode(
		XMLNode *pNode);

	virtual void OnDestroy();

public:
	void SetLevel(
		int nLevel,
		int nMaxLevel,
		BOOL bShowOneChip);

private:
	BOOL mHorzLevel;
	BOOL mRevert;

	int mChipItemWidth;
	int mChipItemHeight;

	CImageBuffer mChipImageBuffer[2];
};
