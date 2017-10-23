#include "XMLParser.h"
#include "BaseApp.h"
#include "HttpFileClient.h"
#include "../GlobalUIClass.h"
#include "PausePage.h"

#define TIMERID_SHOWIMG		1

CPausePage *gPausePage=NULL;

CPausePage::CPausePage()
{
	gPausePage = this;

	mShowTimeMS = 5000;
	SetRectXY(&mShowPosition, 0, 0, LAYOUT_WIDTH, LAYOUT_HEIGHT);
	mCurShowIndex = 0;
}

CPausePage::~CPausePage()
{
	LOGMSG(DBG_LEVEL_I, "function %s quit\n", __PRETTY_FUNCTION__);
}

void CPausePage::Create(
	CE3DCommand *pE3DEngine,
	CBaseWnd *pParent)
{
	LOGMSG(DBG_LEVEL_I, "%s +++\n", __PRETTY_FUNCTION__);

	CParentClass::Create(
		pE3DEngine,
		"PausePage",
		pParent,
		WINDOWFLAG_DEFAULT,
		WINDOWSTATE_INVISIBLE);

	mPictureWnd.Create(pE3DEngine, this);
	mPictureWnd.SetGifWndFrameChangeListener(this, 0);

	LOGMSG(DBG_LEVEL_I, "%s ---\n", __PRETTY_FUNCTION__);
}

void CPausePage::OnLoadResource()
{
	CParentClass::OnLoadResource();

	UIRESITEM* pItemData =
		theBaseApp->GetResourceItem("xml/PausePage");
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
	if ( !parser.GetNode("PausePage", &rootnode) )
	{
		LOGMSG(DBG_LEVEL_E, "failed to Get xml root node %s!!\n", "PausePage");
		return;
	}

	CParentClass::ParserXMLNode(&rootnode);
}

void CPausePage::OnWindowVisible(
	BOOL bVisible)
{
	CParentClass::OnWindowVisible(bVisible);

	LOGMSG(DBG_LEVEL_I, "======CPausePage OnWindowVisible=%d======!\n", bVisible);

	if (bVisible)
	{
	}
	else
	{
		DelTimer(TIMERID_SHOWIMG);

		mLock.Lock();
		DelArrayList(&mPictureUrlList, char);
		mCurShowIndex = 0;
		mLock.Unlock();

		mPictureWnd.SetBkgroundTexture(NULL);
	}
}

void CPausePage::OnTimer(
	int nTimerID)
{
	CParentClass::OnTimer(nTimerID);

	if (TIMERID_SHOWIMG == nTimerID)
	{
		LOGMSG(DBG_LEVEL_I, "PausePage OnTimer need to show idx %d, url count %d\n",
			mCurShowIndex, mPictureUrlList.GetCount());

		mLock.Lock();
		char cNetFile[MAX_PATH] = {0};
		if (mPictureUrlList.GetCount() > 0)
		{
			if(mCurShowIndex < mPictureUrlList.GetCount())
			{
				const char* cUrl = (const char*) mPictureUrlList.GetAt(mCurShowIndex);
				SAFE_STRNCPY(cNetFile, cUrl, MAX_PATH);
				mCurShowIndex = mCurShowIndex+1;
			}
			else
			{
				mCurShowIndex = 0;
				mLock.Unlock();
				gPageManager->SetCurrentPage(Page_Hdmi);
				return;
			}
		}
		else
		{
			mCurShowIndex = 0;
			mLock.Unlock();
			gPageManager->SetCurrentPage(Page_Hdmi);
			return;
		}
		mLock.Unlock();

		char cLocalFile[MAX_PATH];
		if (PictureLocalDownload(cNetFile, cLocalFile))
		{
			int length = strlen(cNetFile);
			if(strcasecmp(cNetFile + length - 4, ".gif") == 0)
			{
				mPictureWnd.LoadFromGifFile(cLocalFile);
				DelTimer(TIMERID_SHOWIMG);
			}
			else
			{
				mPictureWnd.LoadFromImageFile(cLocalFile);
				AddTimer(TIMERID_SHOWIMG, mShowTimeMS);
			}
		}
		else
		{
			AddTimer(TIMERID_SHOWIMG, mShowTimeMS);
		}
	}
}

void CPausePage::OnGifWndFrameChange(
	CImageBuffer *pImageBuffer,
	int nCurIndex,
	int nTotalIndex,
	UINT64 uUserData)
{
	if (nTotalIndex <= 1)
	{
		// normal picture, not a gif
		return;
	}

	// gif index 0 indicate the last frame has shown, return to first frame
	if (nCurIndex == 0)
	{
		LOGMSG(DBG_LEVEL_I, "current index = %d, total count = %d\n",nCurIndex,nTotalIndex);
		OnTimer(TIMERID_SHOWIMG);
	}
}

void CPausePage::PerformHttpCmd_Pause(
	int nSecondsPerImage,
	RECT rcImagePosition,
	const char *pImageUrlBuffer)
{
	DelTimer(TIMERID_SHOWIMG);

	mLock.Lock();

	DelArrayList(&mPictureUrlList, char);
	mCurShowIndex = 0;

	mShowPosition = rcImagePosition;
	mPictureWnd.MoveWindow(&mShowPosition);

	if (nSecondsPerImage < 1)
	{
		nSecondsPerImage = 1;
	}
	mShowTimeMS = nSecondsPerImage * 1000;

	CPtrArrayCtrl sUrlList;
	const char *cDevString = DevideStringByCharListA(
		pImageUrlBuffer,
		-1,
		",",
		1,
		FALSE,
		&sUrlList,
		-1);

	for (int i = 0; i < sUrlList.GetCount(); i++)
	{
		const char* cUrl = (const char*)sUrlList.GetAt(i);
		if (cUrl && cUrl[0])
		{
			char* cPicUrl = new char[strlen(cUrl)+1];
			if (cPicUrl)
			{
				strcpy(cPicUrl, cUrl);
				mPictureUrlList.AddData(cPicUrl);
			}
		}
	}

	Internal_DelArrayA(cDevString);

	int nCount = mPictureUrlList.GetCount();
	char cNetFile[MAX_PATH] = {0};
	const char* cUrl = (const char*) mPictureUrlList.GetAt(mCurShowIndex);
	SAFE_STRNCPY(cNetFile, cUrl, MAX_PATH);

	mLock.Unlock();

	// 显示第一张图片
	if (nCount > 0)
	{
		OnTimer(TIMERID_SHOWIMG);
		gPageManager->SetCurrentPage(Page_Pause);
	}
	else
	{
		mPictureWnd.SetBkgroundTexture(NULL);
		gPageManager->SetCurrentPage(Page_Hdmi);
	}
}

BOOL CPausePage::PictureLocalDownload(
	const char *cNetFile,
	char cLocalFile[MAX_PATH])
{
	if (!cNetFile || cNetFile[0] == '\0')
	{
		return FALSE;
	}

	sprintf(cLocalFile, "%s/Pause.jpg", gKTVConfig.GetTempFolderPath());
	unlink(cLocalFile);

	CHttpFileClient sHttpFileClient;
	HttpFileCopyFromServer(
			&sHttpFileClient,
			cNetFile,
			cLocalFile,
			5000,
			NULL,
			0);
	if (IsFileExist(cLocalFile))
	{
		return TRUE;
	}

	return FALSE;
}
