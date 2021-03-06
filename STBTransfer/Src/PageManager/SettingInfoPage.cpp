#include "SettingInfoPage.h"
#include "BaseApp.h"
#include "XMLParser.h"
#include "../Version.h"
#include "../GlobalUIClass.h"

#define TIMERID_UPDATESTATEUI		1

CSettingInfoPage::CSettingInfoPage()
{
	mUpdateTimeMS = 1000;
}

CSettingInfoPage::~CSettingInfoPage()
{
	LOGMSG(DBG_LEVEL_I, "function %s quit\n", __PRETTY_FUNCTION__);
}

void CSettingInfoPage::Create(
	CE3DCommand *pE3DEngine,
	CBaseWnd *pParent)
{
	LOGMSG(DBG_LEVEL_I, "%s +++\n", __PRETTY_FUNCTION__);

	CBaseWnd::Create(
		pE3DEngine,
		"SettingInfoPage",
		pParent,
		WINDOWFLAG_DEFAULT,
		WINDOWSTATE_INVISIBLE);

	RegisterBroadcastMsg(WNDBCMSG_CONTINUE_CLICK);

	mStateText.CreateStatic(pE3DEngine,this);

	mBackBtn.Create(pE3DEngine, this);
	mBackBtn.SetOnClickListener(this);

    mTitleStbSettingsWnd.CreateStatic(pE3DEngine,this);
    mTitleNetworkSettingsWnd.CreateStatic(pE3DEngine,this);
	mTitleConnectSettingsWnd.CreateStatic(pE3DEngine,this);
	mTitleRoomInfoSettingsWnd.CreateStatic(pE3DEngine,this);
	mTitleCVBSOffsetWnd.CreateStatic(pE3DEngine,this);

	mStbIpPromptWnd.CreateStatic(pE3DEngine,this);
	mStbMacTextPromptWnd.CreateStatic(pE3DEngine,this);
	mNetGatePromptWnd.CreateStatic(pE3DEngine,this);
	mMaskPromptWnd.CreateStatic(pE3DEngine,this);
	mDns0PromptWnd.CreateStatic(pE3DEngine,this);
	mDns1PromptWnd.CreateStatic(pE3DEngine,this);
	mServerIpPromptWnd.CreateStatic(pE3DEngine,this);
	mVodIpPromptWnd.CreateStatic(pE3DEngine,this);
	mRoomNamePromptWnd.CreateStatic(pE3DEngine,this);

	mStbIpText.CreateStatic(pE3DEngine,this);
	mStbMacText.CreateStatic(pE3DEngine,this);
	mNetGateText.CreateStatic(pE3DEngine, this);
	mMaskText.CreateStatic(pE3DEngine, this);
	mDns0Text.CreateStatic(pE3DEngine, this);
	mDns1Text.CreateStatic(pE3DEngine, this);
	mServerIpText.CreateStatic(pE3DEngine, this);
	mVodIpText.CreateStatic(pE3DEngine, this);
	mRoomNameText.CreateStatic(pE3DEngine, this);

	mVersionText.CreateStatic(pE3DEngine,this);

	mGoModifyBtn.Create(pE3DEngine, this);
	mGoModifyBtn.SetOnClickListener(this);

	mMainVolumeSpin.Create(pE3DEngine, this);
	mMainVolumeSpin.SetOnPositionChangeListener(this);
	mMainVolumeSlide.Create(pE3DEngine, this, TRUE, FALSE);
	mMainVolumeSlide.SetOnPositionChangeListener(this);

	mCVBSLeftOffsetSpin.Create(pE3DEngine, this);
	mCVBSLeftOffsetSpin.SetOnPositionChangeListener(this);
	mCVBSRightOffsetSpin.Create(pE3DEngine, this);
	mCVBSRightOffsetSpin.SetOnPositionChangeListener(this);
	mCVBSTopOffsetSpin.Create(pE3DEngine, this);
	mCVBSTopOffsetSpin.SetOnPositionChangeListener(this);
	mCVBSBottomOffsetSpin.Create(pE3DEngine, this);
	mCVBSBottomOffsetSpin.SetOnPositionChangeListener(this);

	mVideoFormatText.CreateStatic(pE3DEngine,this);
	mVideoTipText.CreateStatic(pE3DEngine,this);
	/*for ( int i = 0; i < 3; i++ )
	{
		mVideoFormatBtn[i].Create(pE3DEngine, this, BUTTONTYPE_RADIO);
		mVideoFormatBtn[i].SetOnClickListener(this);
		mVideoFormatBtnGroup.AddToGroup(&(mVideoFormatBtn[i]));
	}*/
	mVideoFormatComboBox.Create(pE3DEngine, this);
	LOGMSG(DBG_LEVEL_I, "%s ---\n", __PRETTY_FUNCTION__);
}

void CSettingInfoPage::OnLoadResource()
{
	CBaseWnd::OnLoadResource();

	UIRESITEM* pItemData =
		theBaseApp->GetResourceItem("xml/SettingInfoPage");
	if (!pItemData)
	{
		LOGMSG(DBG_LEVEL_E, "failed to get item, file=%s!!\n", __FILE__);
		return;
	}

	XMLParser parser;
	if(!parser.LoadFromBuffer(&(pItemData->sXmlBuffer)))
	{
		LOGMSG(DBG_LEVEL_E, "failed to load xml buffer, file=%s!!\n", __FILE__);
		return;
	}

	// read from xml
	XMLNode rootnode;
	if ( !parser.GetNode("SettingInfoPage", &rootnode) )
	{
		LOGMSG(DBG_LEVEL_E, "failed to Get xml root node %s!!\n", "SettingInfoPage");
		return;
	}

	CBaseWnd::ParserXMLNode(&rootnode);

	mVideoFormatText.ParserChildNode(&rootnode,"VideoFormatText");
	mVideoTipText.ParserChildNode(&rootnode,"VideoTipText");

	mStateText.ParserChildNode(&rootnode, "StateText");
	mBackBtn.ParserChildNode(&rootnode, "BackBtn");

    mTitleStbSettingsWnd.ParserChildNode(&rootnode, "TitleStbSettingsWnd");
	mTitleNetworkSettingsWnd.ParserChildNode(&rootnode, "TitleNetworkSettingsWnd");
	mTitleConnectSettingsWnd.ParserChildNode(&rootnode, "TitleConnectSettingsWnd");
	mTitleRoomInfoSettingsWnd.ParserChildNode(&rootnode, "TitleRoomInfoSettingsWnd");
	mTitleCVBSOffsetWnd.ParserChildNode(&rootnode, "TitleCVBSOffsetWnd");

	mStbIpPromptWnd.ParserChildNode(&rootnode, "StbIpPromptWnd");
	mStbMacTextPromptWnd.ParserChildNode(&rootnode, "StbMacTextPromptWnd");
	mNetGatePromptWnd.ParserChildNode(&rootnode, "NetGatePromptWnd");
	mMaskPromptWnd.ParserChildNode(&rootnode, "MaskPromptWnd");
	mDns0PromptWnd.ParserChildNode(&rootnode, "Dns0PromptWnd");
	mDns1PromptWnd.ParserChildNode(&rootnode, "Dns1PromptWnd");
	mServerIpPromptWnd.ParserChildNode(&rootnode, "ServerIpPromptWnd");
	mVodIpPromptWnd.ParserChildNode(&rootnode, "VodIpPromptWnd");
	mRoomNamePromptWnd.ParserChildNode(&rootnode, "RoomNamePromptWnd");

	mStbIpText.ParserChildNode(&rootnode, "StbIpText");
	mStbMacText.ParserChildNode(&rootnode, "StbMacText");
	mNetGateText.ParserChildNode(&rootnode, "NetGateText");
	mMaskText.ParserChildNode(&rootnode, "MaskText");
	mDns0Text.ParserChildNode(&rootnode, "Dns0Text");
	mDns1Text.ParserChildNode(&rootnode, "Dns1Text");
	mServerIpText.ParserChildNode(&rootnode, "ServerIpText");
	mVodIpText.ParserChildNode(&rootnode, "VodIpText");
	mRoomNameText.ParserChildNode(&rootnode, "RoomNameText");
	mVersionText.ParserChildNode(&rootnode, "VersionText");

	mGoModifyBtn.ParserChildNode(&rootnode, "GoModifyBtn");

	mMainVolumeSpin.ParserChildNode(&rootnode, "MainVolumeSpin");
	mMainVolumeSlide.ParserChildNode(&rootnode, "MainVolumeSlide");

	mCVBSLeftOffsetSpin.ParserChildNode(&rootnode, "CVBSLeftOffsetSpin");
	mCVBSRightOffsetSpin.ParserChildNode(&rootnode, "CVBSRightOffsetSpin");
	mCVBSTopOffsetSpin.ParserChildNode(&rootnode, "CVBSTopOffsetSpin");
	mCVBSBottomOffsetSpin.ParserChildNode(&rootnode, "CVBSBottomOffsetSpin");
	
	//LoadResource VideoFormatBtn XML
	/*CSimpleStringA sTmpString;
	for ( int i = 0; i < 3; i++ )
	{
		sTmpString.Format("VideoFormatBtn%d", i);
		mVideoFormatBtn[i].ParserChildNode(&rootnode, sTmpString.GetString());
	}
	//gPlayerCtrl->SetPLTFormat((PLTFORMAT)gKTVConfig.GetPLTFormat());
	mVideoFormatBtnGroup.SetSelectButton(&(mVideoFormatBtn[gKTVConfig.GetPLTFormat()]));*/

	mVideoFormatComboBox.ParserChildNode(&rootnode, "VideoFormatComboBox");
	mVideoFormatComboBox.AddComboItem("1080P",	0, 0);
	mVideoFormatComboBox.AddComboItem("1080I",	1, 1);
	mVideoFormatComboBox.AddComboItem("720P",	2, 2);
	mVideoFormatComboBox.AddComboItem("NTSL",	3, 3);
	mVideoFormatComboBox.SetSelectIndex(0,  FALSE);
	mVideoFormatComboBox.SetComboBoxSelectListener(this);

	mCVBSLeftOffsetSpin.SetPos(gKTVConfig.GetCVBSLeftOffset(), TRUE, FALSE);
	mCVBSRightOffsetSpin.SetPos(gKTVConfig.GetCVBSRightOffset(), TRUE, FALSE);
	mCVBSTopOffsetSpin.SetPos(gKTVConfig.GetCVBSTopOffset(), TRUE, FALSE);
	mCVBSBottomOffsetSpin.SetPos(gKTVConfig.GetCVBSBottomOffset(), TRUE, FALSE);
	printf("[CSettingInfoPage::OnLoadResource] %d;%d;%d;%d\n",gKTVConfig.GetCVBSLeftOffset(),gKTVConfig.GetCVBSRightOffset(),gKTVConfig.GetCVBSTopOffset(),gKTVConfig.GetCVBSBottomOffset());

	mVideoFormatComboBox.SetSelectIndex((PLTFORMAT)gKTVConfig.GetPLTFormat(),FALSE);
	gPlayerCtrl->SetPLTFormat(gKTVConfig.GetPLTFormat());

	mMainVolumeSpin.SetWindowVisible(TRUE);
	mMainVolumeSlide.SetWindowVisible(TRUE);
	mVideoTipText.SetWindowVisible(FALSE);
}

void CSettingInfoPage::OnWindowVisible(
	BOOL bVisible)
{
	CBaseWnd::OnWindowVisible(bVisible);

	LOGMSG(DBG_LEVEL_I, "======CSettingInfoPage OnWindowVisible=%d======!\n", bVisible);


	if (bVisible)
	{
		UpdateUiFromConfig();
		UpdateStateText();
		AddTimer(TIMERID_UPDATESTATEUI, mUpdateTimeMS);
		
		if (mMainVolumeSpin.IsWindowVisible())
		{
			LOGMSG(DBG_LEVEL_I, "%s: main volume setting slidebar is here,so EnableAudioLineInToLineOut!\n", __PRETTY_FUNCTION__);
			gMultiMediaCtrl->EnableAudioLineInToLineOut(TRUE);
		}
	}
	else
	{
		DelTimer(TIMERID_UPDATESTATEUI);
	}
}

void CSettingInfoPage::OnTimer(int nTimerID)
{
	CBaseWnd::OnTimer(nTimerID);

	if (TIMERID_UPDATESTATEUI == nTimerID)
	{
		UpdateStateText();
	}
}

void CSettingInfoPage::OnClick(
	CBaseWnd *pWnd,
	POINT ptWnd)
{
	if (pWnd == &mGoModifyBtn)
	{
		gPageManager->SetCurrentPage(Page_SettingModify);
	}
	else if (pWnd == &mBackBtn)
	{
		gPlayerManager->SetMainPlayerSource(NULL, FALSE);
		gPageManager->SetCurrentPage(Page_Blank);
	}
	/*else
	{
		for ( int i = 0; i < 3; i++ )
		{
			if (pWnd == &(mVideoFormatBtn[i]))
			{
				gKTVConfig.SetPLTFormat((PLTFORMAT)i);
				gPlayerCtrl->SetPLTFormat((PLTFORMAT)i);
				return;
			}
		}
	}
	*/
}

void CSettingInfoPage::OnComboBoxSelectItem(
	CBaseWnd* pWnd,
	int nItemIndex,
	COMBOITEM *pItem)
{
	if (pWnd == &mVideoFormatComboBox)
	{
		gKTVConfig.SetPLTFormat((PLTFORMAT)nItemIndex);
#if 1
		gPlayerCtrl->SetPLTFormat((PLTFORMAT)nItemIndex);
#else
		LOGMSG(DBG_LEVEL_I, "%s: gInitPltFormat=%d, nItemIndex=%d!\n", __PRETTY_FUNCTION__,gInitPltFormat,nItemIndex);
		mVideoTipText.SetWindowVisible(((PLTFORMAT)nItemIndex)==gInitPltFormat ? FALSE : TRUE);
		system("sync");
#endif
	}
}

void CSettingInfoPage::OnMsg(
	UINT32 uType,
	UINT64 wParam,
	UINT64 lParam)
{
	CBaseWnd::OnMsg(uType, wParam, lParam);

	switch(uType)
	{
	case WNDBCMSG_CONTINUE_CLICK:
		if ((int)lParam >= 5)
		{
			if ( (gPageManager->GetCurPageType() == Page_SettingModify) || (gPageManager->GetCurPageType() == Page_SettingInfo) )
			{
				LOGMSG(DBG_LEVEL_I, "%s: in setting info/modify Page, we ignore this request!\n", __PRETTY_FUNCTION__);
			}
			else
			{
				gPageManager->SetCurrentPage(Page_SettingInfo);
			}
		}
		break;

	default:
		break;
	}
}

void CSettingInfoPage::OnSlidePositionChange(
	CBaseWnd *pWnd,
	int nOldPosition,
	int nNewPosition,
	BOOL bChangeEnd)
{
	if (pWnd == &mMainVolumeSlide)
	{
		CSimpleStringA sTmp;
		sTmp.Format("%d", nNewPosition);
		mMainVolumeSpin.SetWindowTextA(sTmp.GetString());
		mMainVolumeSpin.SetPos(nNewPosition);

		gKTVConfig.SetMainVolume(nNewPosition);
		gPlayerCtrl->SetMainVolume(gKTVConfig.GetMainVolume());
	}
}

void CSettingInfoPage::OnSpinPositionChange(
	CBaseWnd *pWnd,
	int nOldPosition,
	int nNewPosition,
	BOOL bChangeEnd)
{
	if (pWnd == &mMainVolumeSpin)
	{
		mMainVolumeSlide.SetPos(nNewPosition, TRUE, FALSE);
	}
	else if(pWnd == &mCVBSLeftOffsetSpin)
	{
		CSimpleStringA sTmp;
		sTmp.Format("%d", nNewPosition);
		mCVBSLeftOffsetSpin.SetWindowTextA(sTmp.GetString());
		mCVBSLeftOffsetSpin.SetPos(nNewPosition);

		gKTVConfig.SetCVBSLeftOffset(nNewPosition);
		gPlayerCtrl->SetCVBSOffset(
			gKTVConfig.GetCVBSLeftOffset(),
			gKTVConfig.GetCVBSRightOffset(),
			gKTVConfig.GetCVBSTopOffset(),
			gKTVConfig.GetCVBSBottomOffset());
		//todo
	}
	else if(pWnd == &mCVBSRightOffsetSpin)
	{
		CSimpleStringA sTmp;
		sTmp.Format("%d", nNewPosition);
		mCVBSRightOffsetSpin.SetWindowTextA(sTmp.GetString());
		mCVBSRightOffsetSpin.SetPos(nNewPosition);

		gKTVConfig.SetCVBSRightOffset(nNewPosition);
		gPlayerCtrl->SetCVBSOffset(
			gKTVConfig.GetCVBSLeftOffset(),
			gKTVConfig.GetCVBSRightOffset(),
			gKTVConfig.GetCVBSTopOffset(),
			gKTVConfig.GetCVBSBottomOffset());
		//
	}
	else if(pWnd == &mCVBSTopOffsetSpin)
	{
		CSimpleStringA sTmp;
		sTmp.Format("%d", nNewPosition);
		mCVBSTopOffsetSpin.SetWindowTextA(sTmp.GetString());
		mCVBSTopOffsetSpin.SetPos(nNewPosition);

		gKTVConfig.SetCVBSTopOffset(nNewPosition);
		gPlayerCtrl->SetCVBSOffset(
			gKTVConfig.GetCVBSLeftOffset(),
			gKTVConfig.GetCVBSRightOffset(),
			gKTVConfig.GetCVBSTopOffset(),
			gKTVConfig.GetCVBSBottomOffset());
		//
	}else if(pWnd == &mCVBSBottomOffsetSpin)
	{
		CSimpleStringA sTmp;
		sTmp.Format("%d", nNewPosition);
		mCVBSBottomOffsetSpin.SetWindowTextA(sTmp.GetString());
		mCVBSBottomOffsetSpin.SetPos(nNewPosition);

		gKTVConfig.SetCVBSBottomOffset(nNewPosition);
		gPlayerCtrl->SetCVBSOffset(
			gKTVConfig.GetCVBSLeftOffset(),
			gKTVConfig.GetCVBSRightOffset(),
			gKTVConfig.GetCVBSTopOffset(),
			gKTVConfig.GetCVBSBottomOffset());
		//
	}
}

void CSettingInfoPage::UpdateStateText()
{
	if (gKTVConfig.IsConfigFileValid())
	{
		if (gHttpCmdClient->GetIsServerOnline())
		{
			if (gProgramBootMode == Mode_Factory)
				mStateText.SetWindowTextA("状态：连接成功(工厂启动)！");
			else if (gProgramBootMode == Mode_Local)
				mStateText.SetWindowTextA("状态：连接成功(本地启动)！");
			else
				mStateText.SetWindowTextA("状态：连接成功！");
		}
		else
		{
			if (gProgramBootMode == Mode_Factory)
				mStateText.SetWindowTextA("状态：连接离线(工厂启动)！");
			else if (gProgramBootMode == Mode_Local)
				mStateText.SetWindowTextA("状态：连接离线(本地启动)！");
			else
				mStateText.SetWindowTextA("状态：连接离线！");
		}
	}
	else
	{
		mStateText.SetWindowTextA("状态：设置未经认证！");
	}
}

void CSettingInfoPage::UpdateUiFromConfig()
{
	const char *pRawTmpStr;

	pRawTmpStr = gKTVConfig.GetStbIP();
	if (pRawTmpStr[0]!='\0')
		mStbIpText.SetWindowTextA(pRawTmpStr);
	else
		mStbIpText.SetWindowTextA("无");

	pRawTmpStr = gKTVConfig.GetMacAddr();
	char targetFormatMacStr[18];
	memset(targetFormatMacStr,0,18);
	for (int i =0; i<6; i++)
	{
	    snprintf(targetFormatMacStr + 3*i,3,"%s",&(pRawTmpStr[2*i]));
	    if (i!=5) targetFormatMacStr[3*i + 2] = ':';
	}
	mStbMacText.SetWindowTextA(targetFormatMacStr);

	pRawTmpStr = gKTVConfig.GetNetGate();
	if (pRawTmpStr[0]!='\0')
		mNetGateText.SetWindowTextA(pRawTmpStr);
	else
		mNetGateText.SetWindowTextA("无");

	pRawTmpStr = gKTVConfig.GetNetMask();
	if (pRawTmpStr[0]!='\0')
		mMaskText.SetWindowTextA(pRawTmpStr);
	else
		mMaskText.SetWindowTextA("无");

	pRawTmpStr = gKTVConfig.GetDNS0();
	if (pRawTmpStr[0]!='\0')
		mDns0Text.SetWindowTextA(pRawTmpStr);
	else
		mDns0Text.SetWindowTextA("无");

	pRawTmpStr = gKTVConfig.GetDNS1();
	if (pRawTmpStr[0]!='\0')
		mDns1Text.SetWindowTextA(pRawTmpStr);
	else
		mDns1Text.SetWindowTextA("无");

	pRawTmpStr = gKTVConfig.GetServerIP();
	if (pRawTmpStr[0]!='\0')
		mServerIpText.SetWindowTextA(pRawTmpStr);
	else
		mServerIpText.SetWindowTextA("无");

	pRawTmpStr = gKTVConfig.GetVodIP();
	if (pRawTmpStr[0]!='\0')
		mVodIpText.SetWindowTextA(pRawTmpStr);
	else
		mVodIpText.SetWindowTextA("无");

	pRawTmpStr = gKTVConfig.GetRoomName();
	if (pRawTmpStr[0]!='\0')
		mRoomNameText.SetWindowTextA(pRawTmpStr);
	else
		mRoomNameText.SetWindowTextA("无");

	char version_str[256];
	snprintf(version_str, 256, "%s %s", "程序版本:",SW_VERSION);
	mVersionText.SetWindowTextA(version_str);

	mMainVolumeSpin.SetPos(gKTVConfig.GetMainVolume(), TRUE, FALSE);
}

