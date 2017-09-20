#pragma once

#include "BaseButton.h"
#include "BaseEdit.h"
#include "PopupWnd.h"
#include "../InputMethodWnd/InputMethodWnd.h"

#define COLOR_INPUT_WRONG (0xFFA15CD9)
#define COLOR_INPUT_NORMAL (0xFFFFFFFF)

class CSettingModifyPage : public CBaseWnd,public IClickEventListener
{
public:
	CSettingModifyPage();
	virtual ~CSettingModifyPage();

	void UpdateEditBkgroundTexture();

	bool PromptInvalidEditContent();

	void UpdateUiFromConfig();

	void CommitSettingToConfig();

	void ConfigEthNet();

public:
	virtual void Create(
		CE3DCommand *pE3DEngine,
		CBaseWnd *pParent);

	virtual void OnLoadResource();

	virtual void OnWindowVisible(
		BOOL bVisible);

// interface
public:
	virtual void OnMsg(
		UINT32 uType,
		UINT64 wParam,
		UINT64 lParam);

	virtual void OnClick(
		CBaseWnd *pWnd,
		POINT ptWnd);

	virtual void OnTimer(
		int nTimerID);

private:
	CBaseWnd mStateText;
    CBaseWnd mTitleStbSettingsWnd;
	CBaseWnd mTitleNetworkSettingsWnd;
	CBaseWnd mTitleConnectSettingsWnd;
	CBaseWnd mTitleRoomInfoSettingsWnd;

	CBaseWnd mStbIpPromptWnd;
	CBaseWnd mStbMacTextPromptWnd;
	CBaseWnd mNetGatePromptWnd;
	CBaseWnd mMaskPromptWnd;
	CBaseWnd mDns0PromptWnd;
	CBaseWnd mDns1PromptWnd;
	CBaseWnd mServerIpPromptWnd;
	CBaseWnd mVodIpPromptWnd;
	CBaseWnd mRoomNamePromptWnd;

	CBaseEdit mStbIpEdit;
	CBaseWnd mStbMacText;
	CBaseEdit mNetGateEdit;
	CBaseEdit mMaskEdit;
	CBaseEdit mDns0Edit;
	CBaseEdit mDns1Edit;
	CBaseEdit mServerIpEdit;
	CBaseEdit mVodIpEdit;
	CBaseEdit mRoomNameEdit;

	CBaseWnd mVersionText;
	CBaseButton mVerifyBtn;
	CBaseButton mBackBtn;

	CBaseWnd mWarningPromptWnd;

	CInputMethodWnd mInputMethodWnd;

	CTexture mEditBkgroundTexture[2];

	int mCountdownTimeMS;
	int mCountdown;
};
