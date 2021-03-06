#pragma once

#include "BaseButton.h"
#include "BaseEdit.h"
#include "PopupWnd.h"
#include "BaseSpin.h"
#include "BaseSlide.h"
#include "BaseComboBox.h"


class CSettingInfoPage : public CBaseWnd,
	public IClickEventListener,
	public ISlidePositionChangeEventListener,
	public ISpinPositionChangeEventListener,
	public IComboBoxSelectListener
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

	virtual void OnSlidePositionChange(
		CBaseWnd *pWnd,
		int nOldPosition,
		int nNewPosition,
		BOOL bChangeEnd);

	virtual void OnSpinPositionChange(
		CBaseWnd *pWnd,
		int nOldPosition,
		int nNewPosition,
		BOOL bChangeEnd);

	virtual void OnComboBoxSelectItem(
		CBaseWnd* pWnd,
		int nItemIndex,
		COMBOITEM *pItem);

private:
	CBaseWnd mStateText;
	CBaseButton mGoModifyBtn;
	CBaseButton mBackBtn;

    CBaseWnd mTitleStbSettingsWnd;
	CBaseWnd mTitleNetworkSettingsWnd;
	CBaseWnd mTitleConnectSettingsWnd;
	CBaseWnd mTitleRoomInfoSettingsWnd;
	CBaseWnd mTitleCVBSOffsetWnd;

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

	// 音量
	CBaseSpin mMainVolumeSpin;
	CBaseSlide mMainVolumeSlide;
	// 视频显示格式
	CBaseWnd mVideoFormatText;
	CBaseWnd mVideoTipText;
	//CBaseButton mVideoFormatBtn[3];
	//CRadioButtonGroup mVideoFormatBtnGroup;
	CBaseComboBox mVideoFormatComboBox;

	CBaseSpin mCVBSLeftOffsetSpin;
	CBaseSpin mCVBSRightOffsetSpin;
	CBaseSpin mCVBSTopOffsetSpin;
	CBaseSpin mCVBSBottomOffsetSpin;

	int mUpdateTimeMS;
};
