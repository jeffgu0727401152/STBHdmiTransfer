#include "SettingModifyPage.h"
#include "BaseApp.h"
#include "XMLParser.h"
#include "../Version.h"
#include "../GlobalUIClass.h"
#include "../InputMethodWnd/InputMethodWnd.h"
#include "../KTVConfig.h"

#define TIMERID_COUNTDOWN		1

CSettingModifyPage::CSettingModifyPage()
{
	mCountdownTimeMS = 1000;
	mCountdown = 6;
	mSetCompareString.Set(SPECIAL_ROOMNAME_SET_VERIFY);
	mCleanCompareString.Set(SPECIAL_ROOMNAME_CLEAN_VERIFY);
}

CSettingModifyPage::~CSettingModifyPage()
{
	LOGMSG(DBG_LEVEL_I, "function %s quit\n", __PRETTY_FUNCTION__);
}

void CSettingModifyPage::Create(
	CE3DCommand *pE3DEngine,
	CBaseWnd *pParent)
{
	LOGMSG(DBG_LEVEL_I, "%s +++\n", __PRETTY_FUNCTION__);

	CBaseWnd::Create(
		pE3DEngine,
		"SettingModifyPage",
		pParent,
		WINDOWFLAG_DEFAULT,
		WINDOWSTATE_INVISIBLE);

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

	mStbIpEdit.Create(pE3DEngine, this);
	mStbIpEdit.EnableCursor(TRUE);
	mStbIpEdit.SetTextMaxLength(16);
	mStbIpEdit.SetOnClickListener(this);

	mStbMacText.CreateStatic(pE3DEngine,this);

	mNetGateEdit.Create(pE3DEngine, this);
	mNetGateEdit.EnableCursor(TRUE);
	mNetGateEdit.SetTextMaxLength(16);
	mNetGateEdit.SetOnClickListener(this);

	mMaskEdit.Create(pE3DEngine, this);
	mMaskEdit.EnableCursor(TRUE);
	mMaskEdit.SetTextMaxLength(16);
	mMaskEdit.SetOnClickListener(this);

	mDns0Edit.Create(pE3DEngine, this);
	mDns0Edit.EnableCursor(TRUE);
	mDns0Edit.SetTextMaxLength(16);
	mDns0Edit.SetOnClickListener(this);

	mDns1Edit.Create(pE3DEngine, this);
	mDns1Edit.EnableCursor(TRUE);
	mDns1Edit.SetTextMaxLength(16);
	mDns1Edit.SetOnClickListener(this);

	mServerIpEdit.Create(pE3DEngine, this);
	mServerIpEdit.EnableCursor(TRUE);
	mServerIpEdit.SetTextMaxLength(16);
	mServerIpEdit.SetOnClickListener(this);

	mVodIpEdit.Create(pE3DEngine, this);
	mVodIpEdit.EnableCursor(TRUE);
	mVodIpEdit.SetTextMaxLength(16);
	mVodIpEdit.SetOnClickListener(this);

	mRoomNameEdit.Create(pE3DEngine, this);
	mRoomNameEdit.EnableCursor(TRUE);
	mRoomNameEdit.SetTextMaxLength(16);
	mRoomNameEdit.SetOnClickListener(this);

	mVersionText.CreateStatic(pE3DEngine,this);

	mVerifyBtn.Create(pE3DEngine, this);
	mVerifyBtn.SetOnClickListener(this);

	mWarningPromptWnd.CreateStatic(pE3DEngine, this);

	mInputMethodWnd.Create(pE3DEngine, this);
	mInputMethodWnd.SetMsgRecvWnd(this);
	mInputMethodWnd.AddIMEType(IMETYPE_LETTER);
	mInputMethodWnd.AddIMEType(IMETYPE_SYMBOL);
	mInputMethodWnd.AddIMEType(IMETYPE_HANDWRITE);
	mInputMethodWnd.AddIMEType(IMETYPE_CHINESE);
	mInputMethodWnd.SetIMEType(IMETYPE_LETTER);

	LOGMSG(DBG_LEVEL_I, "%s ---\n", __PRETTY_FUNCTION__);
}

void CSettingModifyPage::OnLoadResource()
{
	CBaseWnd::OnLoadResource();

	UIRESITEM* pItemData =
		theBaseApp->GetResourceItem("xml/SettingModifyPage");
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
	if ( !parser.GetNode("SettingModifyPage", &rootnode) )
	{
		LOGMSG(DBG_LEVEL_E, "failed to Get xml root node %s!!\n", "MyFirstWnd");
		return;
	}

	XmlLoadBtnTextures(&rootnode,"EditBkgroundImage",mEditBkgroundTexture);

	mBackBtn.ParserChildNode(&rootnode, "BackBtn");

	mStateText.ParserChildNode(&rootnode, "StateText");

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

	mStbIpEdit.ParserChildNode(&rootnode, "StbIpEdit");
	mStbMacText.ParserChildNode(&rootnode, "StbMacText");
	mNetGateEdit.ParserChildNode(&rootnode, "NetGateEdit");
	mMaskEdit.ParserChildNode(&rootnode, "MaskEdit");
	mDns0Edit.ParserChildNode(&rootnode, "Dns0Edit");
	mDns1Edit.ParserChildNode(&rootnode, "Dns1Edit");
	mServerIpEdit.ParserChildNode(&rootnode, "ServerIpEdit");
	mVodIpEdit.ParserChildNode(&rootnode, "VodIpEdit");
	mRoomNameEdit.ParserChildNode(&rootnode, "RoomNameEdit");
	mVersionText.ParserChildNode(&rootnode, "VersionText");

	mWarningPromptWnd.ParserChildNode(&rootnode, "WarningPromptWnd");

	UpdateUiFromConfig();

	mVerifyBtn.ParserChildNode(&rootnode, "VerifyBtn");

	mInputMethodWnd.ParserChildNode(&rootnode, "InputMethodWnd");

	CBaseWnd::ParserXMLNode(&rootnode);
}

void CSettingModifyPage::OnWindowVisible(
	BOOL bVisible)
{
	CBaseWnd::OnWindowVisible(bVisible);

	LOGMSG(DBG_LEVEL_I, "======CSettingModifyPage OnWindowVisible=%d======!\n", bVisible);

	if (bVisible)
	{
		if (!gKTVConfig.IsConfigFileValid())
		{
		    mStateText.SetWindowVisible(TRUE);
			mStateText.SetWindowTextA("状态：设置未经认证！");
		}
		else
		{
			mStateText.SetWindowVisible(FALSE);
		}

		UpdateEditBkgroundTexture();
		PromptInvalidEditContent();
	}
	else
	{
		DelTimer(TIMERID_COUNTDOWN);
	}
}

void CSettingModifyPage::OnMsg(
	UINT32 uType,
	UINT64 wParam,
	UINT64 lParam)
{
	CBaseWnd::OnMsg(uType, wParam, lParam);

	CBaseEdit *pActiveEdit = CBaseEdit::GetActiveEditWnd();
	if (!pActiveEdit || !pActiveEdit->IsWindowEnable())
	{
		return;
	}

	switch(uType)
	{
	case INPUTWND_WCHARMSG:
		pActiveEdit->AddChar((wchar_t)wParam);
		break;

	case INPUTWND_WSTRINGMSG:
		pActiveEdit->SetWindowTextW(((CSimpleStringW*)wParam)->GetString());
		delete ((CSimpleStringW*)wParam);
		break;

	case INPUTWND_LANGUAGETYPEMSG:
	case INPUTWND_WORDCOUNTTYPEMSG:
		pActiveEdit->ClearText();
		break;

	case INPUTWND_BACKMSG:
		pActiveEdit->BackChar();
		if (pActiveEdit->IsEmpty())
		{
			PromptInvalidEditContent();
		}
		break;

	case INPUTWND_CLEARMSG:
		pActiveEdit->ClearText();
		PromptInvalidEditContent();
		break;

	case INPUTWND_SWITCHIME:
		break;

	default:
		break;
	}
}

void CSettingModifyPage::OnClick(
	CBaseWnd *pWnd,
	POINT ptWnd)
{
	if (pWnd == &mVerifyBtn)
	{
		if (gProgramBootMode==Mode_Factory)
		{
			PromptInvalidEditContent();
			LOGMSG(DBG_LEVEL_W, "gProgramBootMode is Mode_Factory, so do nothing just return after verifyClick!\n");
			return;
		}

		if (!PromptInvalidEditContent())
		{
			LOGMSG(DBG_LEVEL_I, "Edit text content is ok, so save settings to configure file!\n");
			ConfigEthNet();
			CommitSettingToConfig();

			//将server ip在主板上储存起来,下次主板启动会根据ip从server上远程mount启动
			CSimpleStringA sTmpCmd;
			sTmpCmd.Format("echo %ls > /stb/config/app/serverip.dat",mServerIpEdit.GetWindowTextW());
			system(sTmpCmd.GetString());
			sTmpCmd.Format("echo %ls > /stb/config/app/deviceip.dat",mStbIpEdit.GetWindowTextW());
			system(sTmpCmd.GetString());
			sTmpCmd.Format("echo %ls > /stb/config/app/mask.dat",mMaskEdit.GetWindowTextW());
			system(sTmpCmd.GetString());
			sTmpCmd.Format("echo %ls > /stb/config/app/gateway.dat",mNetGateEdit.GetWindowTextW());
			system(sTmpCmd.GetString());

			//使用新的Server IP与Port启动服务
			gHttpCmdClient->Stop();
			gHttpCmdClient->Start(gKTVConfig.GetServerIP(), gKTVConfig.GetServerPort());

			mStateText.SetWindowTextA("状态：认证进行中 。。。");
			mStateText.SetWindowVisible(TRUE);

			const char *pRawTmpStr;
			pRawTmpStr = gKTVConfig.GetMacAddr();
			char targetFormatMacStr[18];
			memset(targetFormatMacStr,0,18);
			for (int i =0; i<6; i++)
			{
			    snprintf(targetFormatMacStr + 3*i,3,"%s",&(pRawTmpStr[2*i]));
			    if (i!=5) targetFormatMacStr[3*i + 2] = ':';
			}

			BOOL clientVerifyResult = gHttpCmdClient->ClientVerify(
				/*gKTVConfig.GetMacAddr(),*/
				targetFormatMacStr,
				gKTVConfig.GetStbIP(),
				gKTVConfig.GetVodIP(),
				gKTVConfig.GetRoomName());

			CSimpleStringA sTmp;
			sTmp.Set(mRoomNameEdit.GetWindowTextW());

			if (sTmp.Equal(&mSetCompareString,FALSE))
			{
				LOGMSG(DBG_LEVEL_I, "room name is %s, so force set ISVERIFIED flag in configure!\n",mSetCompareString.GetString());
				mStateText.SetWindowTextA("状态：设置为已认证！！！");
				gKTVConfig.SetConfigFileValid(TRUE);
				system("sync");
			}
			else if (sTmp.Equal(&mCleanCompareString,FALSE))
			{
				LOGMSG(DBG_LEVEL_I, "room name is %s, so force clean ISVERIFIED flag in configure!\n",mCleanCompareString.GetString());
				mStateText.SetWindowTextA("状态：设置为未认证！！！");
				gKTVConfig.SetConfigFileValid(FALSE);
				system("sync");
			}
			else if (clientVerifyResult)
			{
				LOGMSG(DBG_LEVEL_I, "VerifyResult is ok, so set flag in configure & reboot!\n");
				mStateText.SetWindowTextA("状态：认证成功！");

				//在configure中设置标志，表示已经配置过一次,下次启动不再是首次开机
				gKTVConfig.SetConfigFileValid(TRUE);
				system("sync");

				//倒数5下然后重启主板
				mCountdown = 6;
				AddTimer(TIMERID_COUNTDOWN, mCountdownTimeMS);
			}
			else
			{
				mStateText.SetWindowTextA("状态：认证失败！");
			}
		}
	}
	else if (pWnd == &mBackBtn)
	{
		gPageManager->SetCurrentPage(Page_SettingInfo);
	}
	else
	{
		PromptInvalidEditContent();
		UpdateEditBkgroundTexture();
	}
}

void CSettingModifyPage::OnTimer(
	int nTimerID)
{
	CBaseWnd::OnTimer(nTimerID);

	if (TIMERID_COUNTDOWN == nTimerID)
	{
		if (mCountdown<=0)
		{
			DelTimer(TIMERID_COUNTDOWN);
			system("sync");
			system("reboot");
			return;
		}

		mCountdown--;
		char countdownStr[128];
		snprintf(countdownStr, 128, "%s%d%s", "*认证成功 系统将在",mCountdown,"秒后自动重启");
		mWarningPromptWnd.SetWindowTextA(countdownStr);
		mWarningPromptWnd.SetWindowVisible(true);
	}
}

void CSettingModifyPage::UpdateEditBkgroundTexture()
{
	CBaseEdit* pTmpEdit = CBaseEdit::GetActiveEditWnd();
	if (!pTmpEdit || !pTmpEdit->IsWindowEnable())
	{
		return;
	}

	mStbIpEdit.SetBkgroundTexture(&(mEditBkgroundTexture[0]));
	mNetGateEdit.SetBkgroundTexture(&(mEditBkgroundTexture[0]));
	mMaskEdit.SetBkgroundTexture(&(mEditBkgroundTexture[0]));
	mDns0Edit.SetBkgroundTexture(&(mEditBkgroundTexture[0]));
	mDns1Edit.SetBkgroundTexture(&(mEditBkgroundTexture[0]));
	mServerIpEdit.SetBkgroundTexture(&(mEditBkgroundTexture[0]));
	mVodIpEdit.SetBkgroundTexture(&(mEditBkgroundTexture[0]));
	mRoomNameEdit.SetBkgroundTexture(&(mEditBkgroundTexture[0]));

	pTmpEdit->SetBkgroundTexture(&(mEditBkgroundTexture[1]));
	return;
}

bool CSettingModifyPage::PromptInvalidEditContent()
{
	CSimpleStringA sTmp;
	sTmp.Set(mStbIpEdit.GetWindowTextW());
	if(sTmp.GetLength()>0 && !IsValidIPAddr4(sTmp.GetString()))
		mStbIpEdit.SetFontColor(COLOR_INPUT_WRONG);
	else
		mStbIpEdit.SetFontColor(COLOR_INPUT_NORMAL);

	sTmp.Set(mNetGateEdit.GetWindowTextW());
	if(sTmp.GetLength()>0 && !IsValidIPAddr4(sTmp.GetString()))
		mNetGateEdit.SetFontColor(COLOR_INPUT_WRONG);
	else
		mNetGateEdit.SetFontColor(COLOR_INPUT_NORMAL);

	sTmp.Set(mMaskEdit.GetWindowTextW());
	if(sTmp.GetLength()>0 && !IsValidIPAddr4(sTmp.GetString()))
		mMaskEdit.SetFontColor(COLOR_INPUT_WRONG);
	else
		mMaskEdit.SetFontColor(COLOR_INPUT_NORMAL);

	sTmp.Set(mDns0Edit.GetWindowTextW());
	if(sTmp.GetLength()>0 && !IsValidIPAddr4(sTmp.GetString()))
		mDns0Edit.SetFontColor(COLOR_INPUT_WRONG);
	else
		mDns0Edit.SetFontColor(COLOR_INPUT_NORMAL);

	sTmp.Set(mDns1Edit.GetWindowTextW());
	if(sTmp.GetLength()>0 && !IsValidIPAddr4(sTmp.GetString()))
		mDns1Edit.SetFontColor(COLOR_INPUT_WRONG);
	else
		mDns1Edit.SetFontColor(COLOR_INPUT_NORMAL);

	sTmp.Set(mServerIpEdit.GetWindowTextW());
	if(sTmp.GetLength()>0 && !IsValidIPAddr4(sTmp.GetString()))
		mServerIpEdit.SetFontColor(COLOR_INPUT_WRONG);
	else
		mServerIpEdit.SetFontColor(COLOR_INPUT_NORMAL);

	sTmp.Set(mVodIpEdit.GetWindowTextW());
	if(sTmp.GetLength()>0 && !IsValidIPAddr4(sTmp.GetString()))
		mVodIpEdit.SetFontColor(COLOR_INPUT_WRONG);
	else
		mVodIpEdit.SetFontColor(COLOR_INPUT_NORMAL);

	if (mStbIpEdit.GetFontColor() == COLOR_INPUT_WRONG ||
			mNetGateEdit.GetFontColor() == COLOR_INPUT_WRONG ||
			mMaskEdit.GetFontColor() == COLOR_INPUT_WRONG ||
			mDns0Edit.GetFontColor() == COLOR_INPUT_WRONG ||
			mDns1Edit.GetFontColor() == COLOR_INPUT_WRONG ||
			mServerIpEdit.GetFontColor() == COLOR_INPUT_WRONG ||
			mVodIpEdit.GetFontColor() == COLOR_INPUT_WRONG)
	{
		mWarningPromptWnd.SetWindowVisible(true);
		return true;
	}
	else
	{
		mWarningPromptWnd.SetWindowVisible(false);
	    return false;
	}
}

void CSettingModifyPage::UpdateUiFromConfig()
{
	const char *pRawTmpStr;
	pRawTmpStr = gKTVConfig.GetStbIP();
	if (pRawTmpStr[0]!='\0')
		mStbIpEdit.SetWindowTextA(pRawTmpStr);

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
		mNetGateEdit.SetWindowTextA(pRawTmpStr);

	pRawTmpStr = gKTVConfig.GetNetMask();
	if (pRawTmpStr[0]!='\0')
		mMaskEdit.SetWindowTextA(pRawTmpStr);

	pRawTmpStr = gKTVConfig.GetDNS0();
	if (pRawTmpStr[0]!='\0')
		mDns0Edit.SetWindowTextA(pRawTmpStr);

	pRawTmpStr = gKTVConfig.GetDNS1();
	if (pRawTmpStr[0]!='\0')
		mDns1Edit.SetWindowTextA(pRawTmpStr);

	pRawTmpStr = gKTVConfig.GetServerIP();
	if (pRawTmpStr[0]!='\0')
		mServerIpEdit.SetWindowTextA(pRawTmpStr);

	pRawTmpStr = gKTVConfig.GetVodIP();
	if (pRawTmpStr[0]!='\0')
		mVodIpEdit.SetWindowTextA(pRawTmpStr);

	pRawTmpStr = gKTVConfig.GetRoomName();
	if (pRawTmpStr[0]!='\0')
		mRoomNameEdit.SetWindowTextA(pRawTmpStr);

	char version_str[256];
	snprintf(version_str, 256, "%s %s", "程序版本:",SW_VERSION);
	mVersionText.SetWindowTextA(version_str);
}

void CSettingModifyPage::CommitSettingToConfig()
{
	CSimpleStringA sTmp;
	sTmp.Set(mStbIpEdit.GetWindowTextW());
	if(sTmp.GetLength()>0)
	{
		gKTVConfig.SetStbIP(sTmp.GetString());
	}

	sTmp.Set(mNetGateEdit.GetWindowTextW());
	if(sTmp.GetLength()>0)
	{
		gKTVConfig.SetNetGate(sTmp.GetString());
	}

	sTmp.Set(mMaskEdit.GetWindowTextW());
	if(sTmp.GetLength()>0)
	{
		gKTVConfig.SetNetMask(sTmp.GetString());
	}

	sTmp.Set(mDns0Edit.GetWindowTextW());
	if(sTmp.GetLength()>0)
	{
		gKTVConfig.SetDNS0(sTmp.GetString());
	}

	sTmp.Set(mDns1Edit.GetWindowTextW());
	if(sTmp.GetLength()>0)
	{
		gKTVConfig.SetDNS1(sTmp.GetString());
	}

	sTmp.Set(mServerIpEdit.GetWindowTextW());
	if(sTmp.GetLength()>0)
	{
		gKTVConfig.SetServerIP(sTmp.GetString());
	}

	sTmp.Set(mVodIpEdit.GetWindowTextW());
	if(sTmp.GetLength()>0)
	{
		gKTVConfig.SetVodIP(sTmp.GetString());
	}

	sTmp.Set(mRoomNameEdit.GetWindowTextW());
	if(sTmp.GetLength()>0 && !sTmp.Equal(&mSetCompareString,FALSE) && !sTmp.Equal(&mCleanCompareString,FALSE))
	{
		gKTVConfig.SetRoomName(sTmp.GetString());
	}
}

void CSettingModifyPage::ConfigEthNet()
{
	CSimpleStringA sInterfaceName;
	CSimpleStringA sTmpStbIP;
	CSimpleStringA sTmpNetGate;
	CSimpleStringA sTmpNetMask;

	GetAvailbalEthNetworkInterface(&sInterfaceName);
	sTmpStbIP.Set(mStbIpEdit.GetWindowTextW());
	sTmpNetGate.Set(mNetGateEdit.GetWindowTextW());
	sTmpNetMask.Set(mMaskEdit.GetWindowTextW());

	SetIPInfo(
		sInterfaceName.GetString(),
		sTmpStbIP.GetString(),
		sTmpNetMask.GetString(),
		sTmpNetGate.GetString());

#ifndef PC_VERSION
	// PC 机器，请不要设置 DNS，否则可能导致无法上网
	CSimpleStringA sTmpDNS;
	sTmpDNS.Set(mDns0Edit.GetWindowTextW());
	SetDNS(sTmpDNS.GetString());
	sTmpDNS.Set(mDns1Edit.GetWindowTextW());
	SetDNS(sTmpDNS.GetString());
#endif
}
