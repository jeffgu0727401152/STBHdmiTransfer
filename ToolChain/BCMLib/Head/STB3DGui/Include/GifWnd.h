#pragma once

#include "BaseWnd.h"
#include "AnimationEffect.h"

class CGifWnd: public CBaseWnd,
	public IAnimationEffectListener
{
	typedef CBaseWnd CParentClass;

public:
	CGifWnd();
	virtual ~CGifWnd();

public:
	virtual void Create(
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
	virtual void OnAnimationFrameChange(
		CAnimationEffect *pEffect,
		CImageBuffer *pImageBuffer,
		int nCurIndex,
		int nTotalIndex,
		UINT64 uUserData);

public:
	BOOL LoadFromImageFile(
		const char* cImageFileName);
	BOOL LoadFromImageBuffer(
		CImageBuffer *pImageBuf);
	BOOL LoadFromGifFile(
		const char* cGifFileName);
	BOOL LoadFromGifBuffer(
		CBuffer *pGifBuf);

public:
	CAnimationEffect mAnimationEffect;
};
