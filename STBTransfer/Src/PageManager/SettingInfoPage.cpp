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

	mStateText.ParserChildNode(&rootnode, "StateText");

	mBackBtn.ParserChildNode(&rootnode, "BackBtn");

    mTitleStbSettingsWnd.ParserChildNode(&rootnode, "TitleStbSettingsWnd");
	mTitleNetworkSettingsWnd.ParserChildNode(&rootnode, "TitleNetworkSettingsWnd");
	mTitleConnectSettingsWnd.ParserChildNode(&rootnode, "TitleConnectSettingsWnd");
	mTitleRoomInfoSettingsWnd.ParserChildNode(&rootnode, "TitleRoomInfoSettingsWnd");

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

	CBaseWnd::ParserXMLNode(&rootnode);
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
		gPageManager->SetCurrentPage(Page_Hdmi);
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
			if ( (gPageManager->GetCurPageType() == Page_SettingModify) )
			{
				LOGMSG(DBG_LEVEL_I, "%s: in setting modify Page, we ignore this request!\n", __PRETTY_FUNCTION__);
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

void CSettingInfoPage::UpdateStateText()
{
	if (gKTVConfig.IsConfigFileValid())
	{
		if (gHttpCmdClient->GetIsServerOnline())
		{
			if(IsFileExist("/networkflag.txt"))
				mStateText.SetWindowTextA("状态：连接成功！");
			else
				mStateText.SetWindowTextA("状态：连接成功(本地启动)！");
		}
		else
		{
			if(IsFileExist("/networkflag.txt"))
				mStateText.SetWindowTextA("状态：连接离线！");
			else
				mStateText.SetWindowTextA("状态：连接离线(本地启动)！");
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
}

