#pragma once

#include "Texture.h"

class CE3DCommand;
class CPictureBox
{
public:
	CPictureBox();
	virtual ~CPictureBox();

public:
	void Create(
		CE3DCommand *pE3DEngine);
	void Delete();

	void Show(
		BOOL bVisible);

	BOOL HasTexture();
	void SetTexture(
		CTexture *pTexture);
	void UpdateByImageBuffer(
		CImageBuffer *pImageBuffer,
		RECT  *prcUpdate);
	void GetTexture(
		CTexture *pTexture);
	void SetAlphaColor(
		UINT32 uARGB);
	UINT32 GetAlphaColor();
	int GetAngle();

	// bound & display rect is relative to whole screen coordinate
	void SetPosition(
		float *pzPos,
		RECT *prcBound,
		RECT *prcControl,
		int *pnAngle);
	void GetPosition(
		float *pzPos,
		RECT *prcBound,
		RECT *prcControl,
		int *pnAngle);

	void GetFontDrawRect(
		RECT *prcFont,
		RECT rcControl,
		int nFontDirect);

private:
	void UpdateShow();

private:
	CE3DCommand *mE3DEngine;

	CBaseLock mPictureBoxLock;
	void *mpPictureBox;
	float mZPos;
	int mAngle;
	RECT mBoundRect;
	RECT mControlRect;
	CTexture mTexture;
	UINT32 mAlphaColor;
	BOOL mCreated;
	BOOL mNeedVisible;
	BOOL mHasShown;
	BOOL mNeedUpdatePosition;
	BOOL mIsLocalTexture;
};
