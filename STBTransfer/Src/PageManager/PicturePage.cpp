#include "PicturePage.h"
#include "XMLParser.h"
#include "BaseApp.h"
#include "qrencode.h"
#include "HttpFileClient.h"
#include "../GlobalUIClass.h"

#define TIMERID_SHOWIMG		1

CPicturePage *gPicturePage=NULL;

CPicturePage::CPicturePage()
{
	gPicturePage = this;

	mShowTimeMS = 5000;
	mCurShowIndex = 0;
	mPictureLoop = FALSE;
}

CPicturePage::~CPicturePage()
{
	LOGMSG(DBG_LEVEL_I, "function %s quit\n", __PRETTY_FUNCTION__);
}

void CPicturePage::Create(
	CE3DCommand *pE3DEngine,
	CBaseWnd *pParent)
{
	LOGMSG(DBG_LEVEL_I, "%s +++\n", __PRETTY_FUNCTION__);

	CParentClass::Create(
		pE3DEngine,
		"PicturePage",
		pParent,
		WINDOWFLAG_DEFAULT,
		WINDOWSTATE_INVISIBLE);

	mPictureWnd.Create(pE3DEngine, this);

	LOGMSG(DBG_LEVEL_I, "%s ---\n", __PRETTY_FUNCTION__);
}

void CPicturePage::OnLoadResource()
{
	CParentClass::OnLoadResource();

	UIRESITEM* pItemData =
		theBaseApp->GetResourceItem("xml/PicturePage");
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
	if ( !parser.GetNode("PicturePage", &rootnode) )
	{
		LOGMSG(DBG_LEVEL_E, "failed to Get xml root node %s!!\n", "PicturePage");
		return;
	}

	CParentClass::ParserXMLNode(&rootnode);
}

void CPicturePage::OnWindowVisible(
	BOOL bVisible)
{
	CBaseWnd::OnWindowVisible(bVisible);

	LOGMSG(DBG_LEVEL_I, "======CPicturePage OnWindowVisible=%d======!\n", bVisible);

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

void CPicturePage::OnTimer(
	int nTimerID)
{
	CParentClass::OnTimer(nTimerID);

	if (TIMERID_SHOWIMG == nTimerID)
	{
		LOGMSG(DBG_LEVEL_I, "Picture OnTimer need to show idx %d, url count %d\n",
			mCurShowIndex, mPictureUrlList.GetCount());

		mLock.Lock();

		const char* cPictureURL = (const char*) mPictureUrlList.GetAt(mCurShowIndex);
		if (cPictureURL)
		{
			char cLocalFile[MAX_PATH];
			if (PictureLocalDownload(cPictureURL, cLocalFile))
			{
				int length = strlen(cPictureURL);
				if(strcasecmp(cPictureURL + length - 4, ".gif") == 0)
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
		else
		{
			gPageManager->SetCurrentPage(Page_Blank);
		}

		if (mPictureLoop)
		{
			mCurShowIndex = (mCurShowIndex+1) % mPictureUrlList.GetCount();
		}
		else
		{
			if (mCurShowIndex < mPictureUrlList.GetCount())
			{
				mCurShowIndex ++;
			}
		}

		mLock.Unlock();
	}
}

void CPicturePage::OnGifWndFrameChange(
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

void CPicturePage::PerformHttpCmd_SetQRCode(
	const char* cQRCodeString,
	RECT rcQRCodePosition)
{
	DelTimer(TIMERID_SHOWIMG);

	CImageBuffer sImageBuffer;
	CreateQRImage(cQRCodeString, &sImageBuffer);

	sImageBuffer.Stretch(
		RECTWIDTH(rcQRCodePosition),
		RECTHEIGHT(rcQRCodePosition),
		DRAWMODE_NONE);

	LOGMSG(DBG_LEVEL_I, "rcQRCodePosition=(%d,%d,%d,%d)\n",
		rcQRCodePosition.left,
		rcQRCodePosition.top,
		rcQRCodePosition.right,
		rcQRCodePosition.bottom);

	mPictureWnd.SetBkgroundTexture(NULL);
	mPictureWnd.MoveWindow(&rcQRCodePosition);
	mPictureWnd.LoadFromImageBuffer(&sImageBuffer);
}

void CPicturePage::PerformHttpCmd_SetPicture(
	const char* cPictureUrlList,
	RECT rcPicturePosition,
	int nSecondsPerImage,
	BOOL bLoop)
{
	DelTimer(TIMERID_SHOWIMG);

	mLock.Lock();

	DelArrayList(&mPictureUrlList, char);
	mCurShowIndex = 0;

	mPictureWnd.SetBkgroundTexture(NULL);
	mPictureWnd.MoveWindow(&rcPicturePosition);

	if (nSecondsPerImage < 1)
	{
		nSecondsPerImage = 1;
	}
	mShowTimeMS = nSecondsPerImage * 1000;

	CPtrArrayCtrl sUrlList;
	const char *cDevString = DevideStringByCharListA(
		cPictureUrlList,
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
	}
	else
	{
		mPictureWnd.SetBkgroundTexture(NULL);
	}
}

void CPicturePage::CreateQRImage(
	const char* cString,
	CImageBuffer* pImageBuffer)
{
	if (!cString)
	{
		LOGMSG(DBG_LEVEL_E, "CreateQRImage cString is NULL!\n");
		return;
	}
	LOGMSG(DBG_LEVEL_I, "CreateQRImage cString=%s!\n", cString);

	QRcode *code = QRcode_encodeString(
		cString, 0, QR_ECLEVEL_L, QR_MODE_8, 1);
	if(!code)
	{
		LOGMSG(DBG_LEVEL_E, "QRcode_encodeString fail!\n");
		return;
	}

	int nQRImageSize = code->width;
	int nQRImageSizeStride = BMP_LINE_WIDTH(nQRImageSize, 24);

	CImageBuffer sImageBuffer;
	sImageBuffer.CreateFromData(NULL, nQRImageSize, nQRImageSize, 3);
	BYTE* pRGBBuffer = (BYTE*)sImageBuffer.GetBuffer();

	BYTE* pSrcLine = code->data;
	BYTE* pDstLine = pRGBBuffer;
	int i, j;
	for ( i = 0; i < nQRImageSize; i++ )
	{
		for ( j = 0; j < nQRImageSize; j++ )
		{
			if (*(pSrcLine + j) & 0x01)
			{
				*(pDstLine + j*3 +0) = 0x00;
				*(pDstLine + j*3 +1) = 0x00;
				*(pDstLine + j*3 +2) = 0x00;
			}
			else
			{
				*(pDstLine + j*3 +0) = 0xFF;
				*(pDstLine + j*3 +1) = 0xFF;
				*(pDstLine + j*3 +2) = 0xFF;
			}
		}

		pDstLine += nQRImageSizeStride;
		pSrcLine += nQRImageSize;
	}

	QRcode_free(code);

	int nMargin = 4;
	int nLengthWithMargin = nQRImageSize+nMargin*2;
	pImageBuffer->CreateFromData(NULL,nLengthWithMargin,nLengthWithMargin, 3);
	RECT rcCopyTo = {nMargin, nMargin, nQRImageSize+nMargin, nQRImageSize+nMargin};
	pImageBuffer->SetByteValue(NULL, 0xFF);
	pImageBuffer->DrawFromImageBuffer(&sImageBuffer, &rcCopyTo, NULL);
	//pImageBuffer->SaveToBmpFile("/stb/config/app/qrcode.bmp");
}

BOOL CPicturePage::PictureLocalDownload(
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
