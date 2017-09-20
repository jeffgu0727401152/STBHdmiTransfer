#pragma once

#include "BaseButton.h"
#include "BaseEdit.h"
#include "PopupWnd.h"


class CSettingInfoPage : public CBaseWnd,
	public IClickEventListener
{
public:
	CSettingInfoPage();
	virtual ~CSettingInfoPage();

	void UpdateUiFromConfig();

	void UpdateStateText();

public:
	virtual void Create(
		CE3DCommand *pE3DEngine,
		CBaseWnd *pParent);

	virtual void OnLoadResource();

	virtual void OnWindowVisible(
		BOOL bVisible);

// interface
public:
	virtual void OnClick(
		CBaseWnd *pWnd,
		POINT ptWnd);

	virtual void OnMsg(
		UINT32 uType,
		UINT64 wParam,
		UINT64 lParam);

	virtual void OnTimer(
		int nTimerID);

private:
	CBaseWnd mStateText;
	CBaseButton mGoModifyBtn;
	CBaseButton mBackBtn;

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

	CBaseWnd mStbIpText;
	CBaseWnd mStbMacText;
	CBaseWnd mNetGateText;
	CBaseWnd mMaskText;
	CBaseWnd mDns0Text;
	CBaseWnd mDns1Text;
	CBaseWnd mServerIpText;
	CBaseWnd mVodIpText;
	CBaseWnd mRoomNameText;

	CBaseWnd mVersionText;

	int mUpdateTimeMS;
};
