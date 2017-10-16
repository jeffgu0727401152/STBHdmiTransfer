#pragma once

#include "BaseWnd.h"
#include "AnimationEffect.h"

class CRadioButtonGroup;

class CBaseButton: public CBaseWnd,
	public IAnimationEffectListener
{
	typedef CBaseWnd CParentClass;

public:
	CBaseButton();
	virtual ~CBaseButton();

public:
	void Create(
		CE3DCommand *pE3DEngine,
		CBaseWnd *pParent,
		int nButtonType=BUTTONTYPE_NORMAL,
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
	virtual void OnSubclassTouchLeave(
		CBaseWnd *pOldTouchWnd,
		CBaseWnd *pNewTouchWnd);

	virtual void OnSubclassClick(
		CBaseWnd *pWnd,
		POINT ptWnd);

public:
	void SetBtnType(
		int nButtonType);

	virtual void SetBkgroundTexture(
		CTexture *pBackground);

	// 0-normal, 1-pressed
	void SetBtnTextures(
		CTexture buttonTextures[2]);

	void SetRadioBtnPressed(
		BOOL bPressed);

	void SetRadioBtnPressed(
		BOOL bPressed,
		BOOL bNotifyClick,
		BOOL bNotifyOnlyStateChanged);

	BOOL IsRadioBtnPressed();

	void SetRadioGroup(
		CRadioButtonGroup *pRadioGroup);

private:
	void OnButtonStateChange();

private:
	int mButtonType;

	CTexture mButtonTextures[2];
	// 0-normal, 1-pressed
	int mButtonState;
	int mOldBtnState;

	// 0-normal, 1-pressing
	CAnimationEffect* mpNormalButtonEffect[2];

	// 0-normal, 1-pressing
	CAnimationEffect* mpPressedButtonEffect[2];

	CAnimationEffect* mpCurBtnEffect;

	CRadioButtonGroup *mpRadioGroup;
};

class CRadioButtonGroup
{
public:
	CRadioButtonGroup();
	virtual ~CRadioButtonGroup();

public:
	void AddToGroup(
		CBaseButton *pButton);

	void DelFromGroup(
		CBaseButton *pButton);

	void SetSelectButton(
		CBaseButton *pButton);

	void SetSelectButton(
		CBaseButton *pButton,
		BOOL bNotifyClick,
		BOOL bNotifyOnlyStateChanged);

	CBaseButton* GetSelectButton();
	int GetSelectIndex();

private:
	CBaseButton* mpSelectButton;
	CPtrListCtrl mRadioButtonList;
};
