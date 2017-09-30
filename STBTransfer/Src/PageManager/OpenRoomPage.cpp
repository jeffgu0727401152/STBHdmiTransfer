#include "XMLParser.h"
#include "BaseApp.h"
#include "qrencode.h"
#include "../GlobalUIClass.h"
#include "OpenRoomPage.h"

COpenRoomPage *gOpenRoomPage=NULL;

COpenRoomPage::COpenRoomPage()
{
	gOpenRoomPage = this;

	mCurPlayIndex = 0;
}

COpenRoomPage::~COpenRoomPage()
{
	LOGMSG(DBG_LEVEL_I, "function %s quit\n", __PRETTY_FUNCTION__);
}

void COpenRoomPage::Create(
	CE3DCommand *pE3DEngine,
	CBaseWnd *pParent)
{
	LOGMSG(DBG_LEVEL_I, "%s +++\n", __PRETTY_FUNCTION__);

	CParentClass::Create(
		pE3DEngine,
		"OpenRoomPage",
		pParent,
		WINDOWFLAG_DEFAULT,
		WINDOWSTATE_INVISIBLE);

	mPictureWnd.CreateStatic(pE3DEngine, this);

	LOGMSG(DBG_LEVEL_I, "%s ---\n", __PRETTY_FUNCTION__);
}

void COpenRoomPage::OnLoadResource()
{
	CParentClass::OnLoadResource();

	UIRESITEM* pItemData =
		theBaseApp->GetResourceItem("xml/OpenRoomPage");
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
	if ( !parser.GetNode("OpenRoomPage", &rootnode) )
	{
		LOGMSG(DBG_LEVEL_E, "failed to Get xml root node %s!!\n", "OpenRoomPage");
		return;
	}

	CParentClass::ParserXMLNode(&rootnode);
}

void COpenRoomPage::OnWindowVisible(
	BOOL bVisible)
{
	CBaseWnd::OnWindowVisible(bVisible);

	LOGMSG(DBG_LEVEL_I, "======COpenRoomPage OnWindowVisible=%d======!\n", bVisible);

	if (bVisible)
	{
	}
	else
	{
		UnRegisterBroadcastMsg(MSG_PLAYER_COMPLETE);

		gPlayerCtrl->StopMain();

		mLock.Lock();
		DelArrayList(&mVideoUrlList, char);
		mCurPlayIndex = 0;
		mLock.Unlock();
	}
}

void COpenRoomPage::OnMsg(
	UINT32 uType,
	UINT64 wParam,
	UINT64 lParam)
{
	CParentClass::OnMsg(uType, wParam, lParam);

	switch(uType)
	{
	case MSG_PLAYER_COMPLETE:
		if (IsWindowVisible())
		{
			LOGMSG(DBG_LEVEL_I, "COpenRoomPage::OnMsg MSG_PLAYER_COMPLETE!\n");

			if (lParam == PlayComplete_ReasonType_StartError)
			{
				LOGMSG(DBG_LEVEL_E, "COpenRoomPage, play failed, idx = %d, total video = %d!\n",
						mCurPlayIndex, mVideoUrlList.GetCount());
				mLock.Lock();
				mVideoUrlList.DeleteAt(mCurPlayIndex);
				mCurPlayIndex--;
				mLock.Unlock();
			}

			char cVideoUrlLocal[MAX_PATH] = {0};

			mLock.Lock();
			int nCount = mVideoUrlList.GetCount();
			if (nCount > 0)
			{
				mCurPlayIndex = (mCurPlayIndex+1) % nCount;
				// 播放下一个视频
				const char* cVideoUrl = (const char*)mVideoUrlList.GetAt(mCurPlayIndex);
				SAFE_STRNCPY(cVideoUrlLocal, cVideoUrl, MAX_PATH);
			}
			mLock.Unlock();

			if (cVideoUrlLocal[0])
			{
				LOGMSG(DBG_LEVEL_I, "%s:%d, PlayMain!\n", __PRETTY_FUNCTION__, __LINE__);
				gPlayerCtrl->PlayMain(
					"90000000", //SONGID_USER_START
					cVideoUrlLocal, //filepath
					FALSE, //loopplay
					FALSE, //passthrough
					0);
			}
			else
			{
				LOGMSG(DBG_LEVEL_I, "%s:%d, mVideoUrlList empty,show hdmi page!\n", __PRETTY_FUNCTION__, __LINE__);
				gPageManager->SetCurrentPage(Page_Hdmi);
			}
		}
		break;

	default:
		break;
	}
}

void COpenRoomPage::PerformHttpCmd_OpenRoom(
	const char* cQRCodeString,
	RECT rcQRCodePosition,
	const char *cVideoUrlBuffer)
{
	CreateQRImage(rcQRCodePosition, cQRCodeString);

	mLock.Lock();

	DelArrayList(&mVideoUrlList, char);
	mCurPlayIndex = 0;

	CPtrArrayCtrl sUrlList;
	const char *cDevString = DevideStringByCharListA(
		cVideoUrlBuffer,
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
			char* cVideoUrl = new char[strlen(cUrl)+1];
			if (cVideoUrl)
			{
				strcpy(cVideoUrl, cUrl);
				mVideoUrlList.AddData(cVideoUrl);
			}
		}
	}

	Internal_DelArrayA(cDevString);

	int nCount = mVideoUrlList.GetCount();

	char cVideoUrlLocal[MAX_PATH] = {0};
	const char* cVideoUrl = (const char*)mVideoUrlList.GetAt(0);
	SAFE_STRNCPY(cVideoUrlLocal, cVideoUrl, MAX_PATH);

	mLock.Unlock();

	// 播放第一个视频
	if (nCount  > 0 && cVideoUrlLocal[0])
	{
		RegisterBroadcastMsg(MSG_PLAYER_COMPLETE);
		gPageManager->SetCurrentPage(Page_OpenRoom);

		LOGMSG(DBG_LEVEL_I, "%s:%d, PlayMain!\n", __PRETTY_FUNCTION__, __LINE__);
		gPlayerCtrl->PlayMain(
			"90000000", //SONGID_USER_START
			cVideoUrlLocal, //filepath
			FALSE, //loopplay
			FALSE, //passthrough
			0);
	}
	else
	{
		LOGMSG(DBG_LEVEL_I, "%s:%d, mVideoUrlList empty,show hdmi page!\n", __PRETTY_FUNCTION__, __LINE__);
		gPageManager->SetCurrentPage(Page_Hdmi);
	}
}

void COpenRoomPage::CreateQRImage(
	RECT rcQRCodePosition,
	const char* cString)
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

	BYTE *pRGBBuffer = new BYTE[nQRImageSizeStride*nQRImageSize];

	BYTE *pSrcLine = code->data;
	BYTE *pDstLine = pRGBBuffer;
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

	mPictureWnd.MoveWindow(&rcQRCodePosition);

	CImageBuffer sImageBuffer;
	sImageBuffer.BindBuffer(pRGBBuffer, nQRImageSize, nQRImageSize, 3);

	int nMargin = 4;
	int nLengthWithMargin = nQRImageSize+nMargin*2;
	CImageBuffer sImageBufferWithMargin;
	sImageBufferWithMargin.CreateFromData(NULL,nLengthWithMargin,nLengthWithMargin, 3);
	RECT rcCopyTo = {nMargin, nMargin, nQRImageSize+nMargin, nQRImageSize+nMargin};
	sImageBufferWithMargin.SetByteValue(NULL, 0xFF);
	sImageBufferWithMargin.DrawFromImageBuffer(&sImageBuffer, &rcCopyTo, NULL);
	//sImageBufferWithMargin.SaveToBmpFile("/home/kyo/qrcode.bmp");

	sImageBufferWithMargin.Stretch(
		RECTWIDTH(rcQRCodePosition),
		RECTHEIGHT(rcQRCodePosition),
		DRAWMODE_NONE);

	mPictureWnd.SetBkgroundImageBuffer(&sImageBufferWithMargin, NULL);

	delete []pRGBBuffer;
	QRcode_free(code);
}
