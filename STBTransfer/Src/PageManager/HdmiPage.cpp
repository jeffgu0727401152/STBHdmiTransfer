#include "XMLParser.h"
#include "BaseApp.h"
#include "../GlobalUIClass.h"
#include "HdmiPage.h"

CHdmiPage *gHdmiPage=NULL;

CHdmiPage::CHdmiPage()
{
	gHdmiPage = this;

	mHdmiInConnected = FALSE;
}

CHdmiPage::~CHdmiPage()
{
	LOGMSG(DBG_LEVEL_I, "function %s quit\n", __PRETTY_FUNCTION__);
}

void CHdmiPage::Create(
	CE3DCommand *pE3DEngine,
	CBaseWnd *pParent)
{
	LOGMSG(DBG_LEVEL_I, "%s +++\n", __PRETTY_FUNCTION__);

	CParentClass::Create(
		pE3DEngine,
		"HdmiPage",
		pParent,
		WINDOWFLAG_DEFAULT,
		WINDOWSTATE_INVISIBLE);

	LOGMSG(DBG_LEVEL_I, "%s ---\n", __PRETTY_FUNCTION__);
}

void CHdmiPage::OnLoadResource()
{
	CParentClass::OnLoadResource();

	UIRESITEM* pItemData =
		theBaseApp->GetResourceItem("xml/HdmiPage");
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
	if ( !parser.GetNode("HdmiPage", &rootnode) )
	{
		LOGMSG(DBG_LEVEL_E, "failed to Get xml root node %s!!\n", "HdmiPage");
		return;
	}

	CParentClass::ParserXMLNode(&rootnode);
}

void CHdmiPage::OnWindowVisible(
	BOOL bVisible)
{
	CBaseWnd::OnWindowVisible(bVisible);

	LOGMSG(DBG_LEVEL_I, "======CHdmiPage OnWindowVisible=%d======!\n", bVisible);

	if (bVisible)
	{
		if (mHdmiInConnected)
		{
			LOGMSG(DBG_LEVEL_I, "%s:%d, Play hdmi!\n", __PRETTY_FUNCTION__, __LINE__);
			gPlayerCtrl->PlayMain(
				"99999910", //SONGID_HDMIIN
				"hdmiin://", //filepath
				FALSE, //loopplay
				FALSE, //passthrough
				0);
			gMultiMediaCtrl->EnableAudioLineInToLineOut(TRUE);
		}
	}
	else
	{
		if (mHdmiInConnected && gPageManager->GetCurPageType() != Page_Pause)
		{
			gMultiMediaCtrl->EnableAudioLineInToLineOut(FALSE);
			gPlayerCtrl->StopMain();
		}
	}
}

void CHdmiPage::OnMsg(
	UINT32 uType,
	UINT64 wParam,
	UINT64 lParam)
{
	CParentClass::OnMsg(uType, wParam, lParam);

	switch(uType)
	{
	case MSG_HDMIIN_CONNECT:
		mHdmiInConnected = TRUE;
		if (IsWindowVisible())
		{
			LOGMSG(DBG_LEVEL_I, "%s:%d, play hdmi!\n", __PRETTY_FUNCTION__, __LINE__);
			gPlayerCtrl->PlayMain(
				"99999910", //SONGID_HDMIIN
				"hdmiin://", //filepath
				FALSE, //loopplay
				FALSE, //passthrough
				0);
			gMultiMediaCtrl->EnableAudioLineInToLineOut(TRUE);
		}
		break;

	case MSG_HDMIIN_DISCONNECT:
		mHdmiInConnected = FALSE;
		gMultiMediaCtrl->EnableAudioLineInToLineOut(FALSE);
		gPlayerCtrl->StopMain();
		break;

	case MSG_FIRSTAUDIO:
		break;

	default:
		break;
	}
}

void CHdmiPage::PerformHttpCmd_Hdmi()
{
	gPageManager->SetCurrentPage(Page_Hdmi);
}

BOOL CHdmiPage::IsHdmiInConnected()
{
	return mHdmiInConnected;
}
