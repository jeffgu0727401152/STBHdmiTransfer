#pragma once

#include "E2DEffect.h"
#include "PictureBox.h"
#include "PtrControl.h"

typedef struct tagFLYITEM
{
	CPictureBox itemPictureBox;
	RECT rcFrom;
	RECT rcTo;
	int nAlphaFrom;
	int nAlphaTo;
	int nStartAngle;
	BOOL bRotate;
	BOOL bKeepItemWhenStop;
	float xSlideStepLen;
	float ySlideStepLen;
	float wSlideStepLen;
	float hSlideStepLen;
} FLYITEM;

class CE2DEffectFly : public CE2DEffect
{
	typedef CE2DEffect CParentClass;

public:
	CE2DEffectFly();
	virtual ~CE2DEffectFly();

//interface
protected:
	virtual void OnStart();

	virtual void OnStep(
		int nCurStep,
		int nTotalStep);

	virtual void OnStop();

public:
	void AddFlyItem(
		CTexture* pItemTexture,
		UINT32 uColor,
		RECT rcFrom,
		RECT rcTo,
		int nAlphaFrom,
		int nAlphaTo,
		BOOL bRotate,
		BOOL bKeepItemWhenStop);
	void RemoveAllFlyItem();
	BOOL HasFlyItem();

private:
	CPtrListCtrl mFlyItemList;
	CBaseLock mFlyItemListLock;
};

