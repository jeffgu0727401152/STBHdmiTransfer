#include "HttpCmdClient.h"
#include "commfunc.h"
#include "DbgOutput.h"
#include <errno.h>

CHttpCmdClient::CHttpCmdClient()
{
	mRequestID = 0;
}

CHttpCmdClient::~CHttpCmdClient()
{

}

BOOL CHttpCmdClient::Create(
	const char *cServerAddr,
	UINT16 uPort,
	BOOL bLocalSocket,
	const char* cSocketThreadName)
{
	return CParentClass::Create(
		cServerAddr,
		uPort,
		bLocalSocket,
		FALSE,
		TRUE,
		this,
		0,
		cSocketThreadName);
}

void CHttpCmdClient::OnClientReceiveTCPData(
	UINT64 uUserData,
	int nSocketFD,
	const void *pBuffer,
	int nBufLen)
{
	HTTPCMDHEADER *phdr = (HTTPCMDHEADER *)pBuffer;
	if (phdr->nHttpCmdVer != HTTPCMD_VER)
	{
		LOGMSG(DBG_LEVEL_I, "%s: Data Provider Version NOT MATCH\n", __PRETTY_FUNCTION__);
		return;
	}

	LOGMSG(DBG_LEVEL_I, "%s: res:nRequestID=%d\n", __PRETTY_FUNCTION__, phdr->nRequestID);

	mRequestWithEventListLock.Lock();

	int nRequestCount = mRequestWithEventList.GetCount();
	int i;
	for (i = 0; i < nRequestCount; i++)
	{
		HTTPCMDREQWITHEVENT* pRequestWithEvent = (HTTPCMDREQWITHEVENT*)mRequestWithEventList.GetAt(i);
		if (pRequestWithEvent->nRequestID == phdr->nRequestID)
		{
			switch (phdr->nCommandType)
			{
			case HTTPCMD_RES_REBOOT:
				OnResponseRebootCmd((HTTPCMDRESREBOOTCMD *)phdr);
				break;

			case HTTPCMD_RES_PAUSE:
				OnResponsePauseCmd((HTTPCMDRESPAUSECMD *)phdr);
				break;

			case HTTPCMD_RES_RESUME:
				OnResponseResumeCmd((HTTPCMDRESRESUMECMD *)phdr);
				break;

			case HTTPCMD_RES_CLOSEROOM:
				OnResponseCloseRoomCmd((HTTPCMDRESCLOSEROOMCMD *)phdr);
				break;

			case HTTPCMD_RES_OPENROOM:
				OnResponseOpenRoomCmd((HTTPCMDRESOPENROOMCMD *)phdr);
				break;

			case HTTPCMD_RES_CHECKSTATUS:
				OnResponseCheckStatusCmd((HTTPCMDRESCHECKSTATUSCMD *)phdr);
				break;

			case HTTPCMD_RES_PAYCALLBACK:
				OnResponsePayCallbackCmd((HTTPCMDRESPAYCALLBACKCMD *)phdr);
				break;

			case HTTPCMD_RES_PIPPREVIEW:
				OnResponsePipPreviewCmd((HTTPCMDRESPIPPREVIEWCMD *)phdr);
				break;

			default:
				break;
			}

			pRequestWithEvent->complete.Set();

			break;
		}
	}

	mRequestWithEventListLock.Unlock();
}

void CHttpCmdClient::OnClientDisconnectFromServer(
	UINT64 uUserData,
	int nSocketFD)
{
	LOGMSG(DBG_LEVEL_I, "Client Socket(%d) Disconnect\n", nSocketFD);

	mRequestWithEventListLock.Lock();

	int nRequestCount = mRequestWithEventList.GetCount();
	int i;
	for (i = 0; i < nRequestCount; i++)
	{
		HTTPCMDREQWITHEVENT* pRequestWithEvent = (HTTPCMDREQWITHEVENT*)mRequestWithEventList.GetAt(i);
		if (pRequestWithEvent)
		{
			pRequestWithEvent->complete.Set();
		}
	}

	mRequestWithEventListLock.Unlock();
}

BOOL CHttpCmdClient::SendCheckStatusCmd(
	CSimpleStringA *pResultString)
{
	if (!IsConnect())
	{
		LOGMSG(DBG_LEVEL_I, "%s: HttpCmdServer NOT Started\n", __PRETTY_FUNCTION__);

		return FALSE;
	}

	BOOL bSendOK = FALSE;

	HTTPCMDREQCHECKSTATUSCMD request;
	request.nHttpCmdVer = HTTPCMD_VER;
	request.nRequestID = mRequestID++;
	request.nCommandType = HTTPCMD_REQ_CHECKSTATUS;
	request.uPrivData = (UINT64)pResultString;

	HTTPCMDREQWITHEVENT requestWithEvent;
	requestWithEvent.nRequestID = request.nRequestID;
	mRequestWithEventListLock.Lock();
	mRequestWithEventList.AddData(&requestWithEvent);
	mRequestWithEventListLock.Unlock();

	LOGMSG(DBG_LEVEL_I, "%s: req:nRequestID=%d\n", __PRETTY_FUNCTION__, request.nRequestID);
	if (SendData(MSG_TO_SERVERSOCKET, &request, sizeof(HTTPCMDREQCHECKSTATUSCMD)))
	{
		if (!requestWithEvent.complete.Wait(5000))
		{
			LOGMSG(DBG_LEVEL_I, "%s: wait response timeout\n", __PRETTY_FUNCTION__);
		}
		else
		{
			bSendOK = TRUE;
		}
	}
	else
	{
		LOGMSG(DBG_LEVEL_I, "%s: SendData Failed\n", __PRETTY_FUNCTION__);
	}

	mRequestWithEventListLock.Lock();
	mRequestWithEventList.DeleteAt(mRequestWithEventList.FindFirst(&requestWithEvent));
	mRequestWithEventListLock.Unlock();

	return bSendOK;
}

void CHttpCmdClient::OnResponseCheckStatusCmd(
	HTTPCMDRESCHECKSTATUSCMD *pResCheckStatusCmdParam)
{
	CSimpleStringA *pResultString = (CSimpleStringA *)pResCheckStatusCmdParam->uPrivData;
	if (pResCheckStatusCmdParam->uSize > 0)
	{
		const char *pReadBuf = ((const char *)pResCheckStatusCmdParam)+sizeof(HTTPCMDRESCHECKSTATUSCMD);
		pResultString->Set(pReadBuf, pResCheckStatusCmdParam->uSize);
	}
}

BOOL CHttpCmdClient::SendRebootCmd(
	CSimpleStringA *pResultString)
{
	if (!IsConnect())
	{
		LOGMSG(DBG_LEVEL_I, "%s: HttpCmdServer NOT Started\n", __PRETTY_FUNCTION__);

		return FALSE;
	}

	BOOL bSendOK = FALSE;

	HTTPCMDREQREBOOTCMD request;
	request.nHttpCmdVer = HTTPCMD_VER;
	request.nRequestID = mRequestID++;
	request.nCommandType = HTTPCMD_REQ_REBOOT;
	request.uPrivData = (UINT64)pResultString;

	HTTPCMDREQWITHEVENT requestWithEvent;
	requestWithEvent.nRequestID = request.nRequestID;
	mRequestWithEventListLock.Lock();
	mRequestWithEventList.AddData(&requestWithEvent);
	mRequestWithEventListLock.Unlock();

	LOGMSG(DBG_LEVEL_I, "%s: req:nRequestID=%d\n", __PRETTY_FUNCTION__, request.nRequestID);
	if (SendData(MSG_TO_SERVERSOCKET, &request, sizeof(HTTPCMDREQREBOOTCMD)))
	{
		if (!requestWithEvent.complete.Wait(5000))
		{
			LOGMSG(DBG_LEVEL_I, "%s: wait response timeout\n", __PRETTY_FUNCTION__);
		}
		else
		{
			bSendOK = TRUE;
		}
	}
	else
	{
		LOGMSG(DBG_LEVEL_I, "%s: SendData Failed\n", __PRETTY_FUNCTION__);
	}

	mRequestWithEventListLock.Lock();
	mRequestWithEventList.DeleteAt(mRequestWithEventList.FindFirst(&requestWithEvent));
	mRequestWithEventListLock.Unlock();

	return bSendOK;
}

void CHttpCmdClient::OnResponseRebootCmd(
	HTTPCMDRESREBOOTCMD *pResRebootCmdParam)
{
	CSimpleStringA *pResultString = (CSimpleStringA *)pResRebootCmdParam->uPrivData;
	if (pResRebootCmdParam->uSize > 0)
	{
		const char *pReadBuf = ((const char *)pResRebootCmdParam)+sizeof(HTTPCMDRESREBOOTCMD);
		pResultString->Set(pReadBuf, pResRebootCmdParam->uSize);
	}
}

BOOL CHttpCmdClient::SendPauseCmd(
	int nSecondsPerImage,
	RECT rcImagePosition,
	int nImageUrlBufLength,
	const char *cImageUrlBuffer,
	CSimpleStringA *pResultString)
{
	if (!IsConnect())
	{
		LOGMSG(DBG_LEVEL_I, "%s: HttpCmdServer NOT Started\n", __PRETTY_FUNCTION__);

		return FALSE;
	}

	BOOL bSendOK = FALSE;

	HTTPCMDREQPAUSECMD request;
	request.nHttpCmdVer = HTTPCMD_VER;
	request.nRequestID = mRequestID++;
	request.nCommandType = HTTPCMD_REQ_PAUSE;
	request.uPrivData = (UINT64)pResultString;

	request.nSecondsPerImage = nSecondsPerImage;
	request.rcImagePosition = rcImagePosition;
	request.nImageUrlBufLength = nImageUrlBufLength;

	UINT32 uSendBufSize = sizeof(HTTPCMDREQPAUSECMD) + nImageUrlBufLength;
	BYTE *pSendBuffer = new BYTE[uSendBufSize];
	if (!pSendBuffer)
	{
		return FALSE;
	}

	memcpy(pSendBuffer, &request, sizeof(HTTPCMDREQPAUSECMD));
	if (nImageUrlBufLength > 0)
	{
		memcpy(pSendBuffer+sizeof(HTTPCMDREQPAUSECMD), cImageUrlBuffer, nImageUrlBufLength);
	}

	HTTPCMDREQWITHEVENT requestWithEvent;
	requestWithEvent.nRequestID = request.nRequestID;
	mRequestWithEventListLock.Lock();
	mRequestWithEventList.AddData(&requestWithEvent);
	mRequestWithEventListLock.Unlock();

	LOGMSG(DBG_LEVEL_I, "%s: req:nRequestID=%d\n", __PRETTY_FUNCTION__, request.nRequestID);
	if (SendData(MSG_TO_SERVERSOCKET, pSendBuffer, uSendBufSize))
	{
		if (!requestWithEvent.complete.Wait(5000))
		{
			LOGMSG(DBG_LEVEL_I, "%s: wait response timeout\n", __PRETTY_FUNCTION__);
		}
		else
		{
			bSendOK = TRUE;
		}
	}
	else
	{
		LOGMSG(DBG_LEVEL_I, "%s: SendData Failed\n", __PRETTY_FUNCTION__);
	}

	mRequestWithEventListLock.Lock();
	mRequestWithEventList.DeleteAt(mRequestWithEventList.FindFirst(&requestWithEvent));
	mRequestWithEventListLock.Unlock();

	delete []pSendBuffer;

	return bSendOK;
}

void CHttpCmdClient::OnResponsePauseCmd(
	HTTPCMDRESPAUSECMD *pResPauseCmdParam)
{
	CSimpleStringA *pResultString = (CSimpleStringA *)pResPauseCmdParam->uPrivData;
	if (pResPauseCmdParam->uSize > 0)
	{
		const char *pReadBuf = ((const char *)pResPauseCmdParam)+sizeof(HTTPCMDRESPAUSECMD);
		pResultString->Set(pReadBuf, pResPauseCmdParam->uSize);
	}
}

BOOL CHttpCmdClient::SendResumeCmd(
	CSimpleStringA *pResultString)
{
	if (!IsConnect())
	{
		LOGMSG(DBG_LEVEL_I, "%s: HttpCmdServer NOT Started\n", __PRETTY_FUNCTION__);

		return FALSE;
	}

	BOOL bSendOK = FALSE;

	HTTPCMDREQRESUMECMD request;
	request.nHttpCmdVer = HTTPCMD_VER;
	request.nRequestID = mRequestID++;
	request.nCommandType = HTTPCMD_REQ_RESUME;
	request.uPrivData = (UINT64)pResultString;

	HTTPCMDREQWITHEVENT requestWithEvent;
	requestWithEvent.nRequestID = request.nRequestID;
	mRequestWithEventListLock.Lock();
	mRequestWithEventList.AddData(&requestWithEvent);
	mRequestWithEventListLock.Unlock();

	LOGMSG(DBG_LEVEL_I, "%s: req:nRequestID=%d\n", __PRETTY_FUNCTION__, request.nRequestID);
	if (SendData(MSG_TO_SERVERSOCKET, &request, sizeof(HTTPCMDREQRESUMECMD)))
	{
		if (!requestWithEvent.complete.Wait(5000))
		{
			LOGMSG(DBG_LEVEL_I, "%s: wait response timeout\n", __PRETTY_FUNCTION__);
		}
		else
		{
			bSendOK = TRUE;
		}
	}
	else
	{
		LOGMSG(DBG_LEVEL_I, "%s: SendData Failed\n", __PRETTY_FUNCTION__);
	}

	mRequestWithEventListLock.Lock();
	mRequestWithEventList.DeleteAt(mRequestWithEventList.FindFirst(&requestWithEvent));
	mRequestWithEventListLock.Unlock();

	return bSendOK;
}

void CHttpCmdClient::OnResponseResumeCmd(
	HTTPCMDRESRESUMECMD *pResResumeCmdParam)
{
	CSimpleStringA *pResultString = (CSimpleStringA *)pResResumeCmdParam->uPrivData;
	if (pResResumeCmdParam->uSize > 0)
	{
		const char *pReadBuf = ((const char *)pResResumeCmdParam)+sizeof(HTTPCMDRESRESUMECMD);
		pResultString->Set(pReadBuf, pResResumeCmdParam->uSize);
	}
}

BOOL CHttpCmdClient::SendOpenRoomCmd(
	const char* cQRCodeString,
	RECT rcQRCodePosition,
	int nVideoUrlBufLength,
	const char *cVideoUrlBuffer,
	CSimpleStringA *pResultString)
{
	if (!IsConnect())
	{
		LOGMSG(DBG_LEVEL_I, "%s: HttpCmdServer NOT Started\n", __PRETTY_FUNCTION__);

		return FALSE;
	}

	BOOL bSendOK = FALSE;

	HTTPCMDREQOPENROOMCMD request;
	request.nHttpCmdVer = HTTPCMD_VER;
	request.nRequestID = mRequestID++;
	request.nCommandType = HTTPCMD_REQ_OPENROOM;
	request.uPrivData = (UINT64)pResultString;

	SAFE_STRNCPY(request.cQRCodeString, cQRCodeString, 1024);
	request.rcQRCodePosition = rcQRCodePosition;
	request.nVideoUrlBufLength = nVideoUrlBufLength;

	UINT32 uSendBufSize = sizeof(HTTPCMDREQOPENROOMCMD) + nVideoUrlBufLength;
	BYTE *pSendBuffer = new BYTE[uSendBufSize];
	if (!pSendBuffer)
	{
		return FALSE;
	}

	memcpy(pSendBuffer, &request, sizeof(HTTPCMDREQOPENROOMCMD));
	if (nVideoUrlBufLength > 0)
	{
		memcpy(pSendBuffer+sizeof(HTTPCMDREQOPENROOMCMD), cVideoUrlBuffer, nVideoUrlBufLength);
	}

	HTTPCMDREQWITHEVENT requestWithEvent;
	requestWithEvent.nRequestID = request.nRequestID;
	mRequestWithEventListLock.Lock();
	mRequestWithEventList.AddData(&requestWithEvent);
	mRequestWithEventListLock.Unlock();

	LOGMSG(DBG_LEVEL_I, "%s: req:nRequestID=%d\n", __PRETTY_FUNCTION__, request.nRequestID);
	if (SendData(MSG_TO_SERVERSOCKET, pSendBuffer, uSendBufSize))
	{
		if (!requestWithEvent.complete.Wait(5000))
		{
			LOGMSG(DBG_LEVEL_I, "%s: wait response timeout\n", __PRETTY_FUNCTION__);
		}
		else
		{
			bSendOK = TRUE;
		}
	}
	else
	{
		LOGMSG(DBG_LEVEL_I, "%s: SendData Failed\n", __PRETTY_FUNCTION__);
	}

	mRequestWithEventListLock.Lock();
	mRequestWithEventList.DeleteAt(mRequestWithEventList.FindFirst(&requestWithEvent));
	mRequestWithEventListLock.Unlock();

	delete []pSendBuffer;

	return bSendOK;
}

void CHttpCmdClient::OnResponseOpenRoomCmd(
	HTTPCMDRESOPENROOMCMD *pResOpenRoomCmdParam)
{
	CSimpleStringA *pResultString = (CSimpleStringA *)pResOpenRoomCmdParam->uPrivData;
	if (pResOpenRoomCmdParam->uSize > 0)
	{
		const char *pReadBuf = ((const char *)pResOpenRoomCmdParam)+sizeof(HTTPCMDRESOPENROOMCMD);
		pResultString->Set(pReadBuf, pResOpenRoomCmdParam->uSize);
	}
}

BOOL CHttpCmdClient::SendPipPreviewCmd(
	RECT rcPipPosition,
	int nVideoUrlBufLength,
	const char *cVideoUrlBuffer,
	CSimpleStringA *pResultString)
{
	if (!IsConnect())
	{
		LOGMSG(DBG_LEVEL_I, "%s: HttpCmdServer NOT Started\n", __PRETTY_FUNCTION__);

		return FALSE;
	}

	BOOL bSendOK = FALSE;

	HTTPCMDREQPIPPREVIEWCMD request;
	request.nHttpCmdVer = HTTPCMD_VER;
	request.nRequestID = mRequestID++;
	request.nCommandType = HTTPCMD_REQ_PIPPREVIEW;
	request.uPrivData = (UINT64)pResultString;

	request.rcPipPosition = rcPipPosition;
	request.nVideoUrlBufLength = nVideoUrlBufLength;

	UINT32 uSendBufSize = sizeof(HTTPCMDREQPIPPREVIEWCMD) + nVideoUrlBufLength;
	BYTE *pSendBuffer = new BYTE[uSendBufSize];
	if (!pSendBuffer)
	{
		return FALSE;
	}

	memcpy(pSendBuffer, &request, sizeof(HTTPCMDREQPIPPREVIEWCMD));
	if (nVideoUrlBufLength > 0)
	{
		memcpy(pSendBuffer+sizeof(HTTPCMDREQPIPPREVIEWCMD), cVideoUrlBuffer, nVideoUrlBufLength);
	}

	HTTPCMDREQWITHEVENT requestWithEvent;
	requestWithEvent.nRequestID = request.nRequestID;
	mRequestWithEventListLock.Lock();
	mRequestWithEventList.AddData(&requestWithEvent);
	mRequestWithEventListLock.Unlock();

	LOGMSG(DBG_LEVEL_I, "%s: req:nRequestID=%d\n", __PRETTY_FUNCTION__, request.nRequestID);
	if (SendData(MSG_TO_SERVERSOCKET, pSendBuffer, uSendBufSize))
	{
		if (!requestWithEvent.complete.Wait(5000))
		{
			LOGMSG(DBG_LEVEL_I, "%s: wait response timeout\n", __PRETTY_FUNCTION__);
		}
		else
		{
			bSendOK = TRUE;
		}
	}
	else
	{
		LOGMSG(DBG_LEVEL_I, "%s: SendData Failed\n", __PRETTY_FUNCTION__);
	}

	mRequestWithEventListLock.Lock();
	mRequestWithEventList.DeleteAt(mRequestWithEventList.FindFirst(&requestWithEvent));
	mRequestWithEventListLock.Unlock();

	delete []pSendBuffer;

	return bSendOK;
}

void CHttpCmdClient::OnResponsePipPreviewCmd(
		HTTPCMDRESPIPPREVIEWCMD *pResPipPreviewCmdParam)
{
	CSimpleStringA *pResultString = (CSimpleStringA *)pResPipPreviewCmdParam->uPrivData;
	if (pResPipPreviewCmdParam->uSize > 0)
	{
		const char *pReadBuf = ((const char *)pResPipPreviewCmdParam)+sizeof(HTTPCMDRESPIPPREVIEWCMD);
		pResultString->Set(pReadBuf, pResPipPreviewCmdParam->uSize);
	}
}

BOOL CHttpCmdClient::SendCloseRoomCmd(
	int nVideoUrlBufLength,
	const char *cVideoUrlBuffer,
	CSimpleStringA *pResultString)
{
	if (!IsConnect())
	{
		LOGMSG(DBG_LEVEL_I, "%s: HttpCmdServer NOT Started\n", __PRETTY_FUNCTION__);

		return FALSE;
	}

	BOOL bSendOK = FALSE;

	HTTPCMDREQCLOSEROOMCMD request;
	request.nHttpCmdVer = HTTPCMD_VER;
	request.nRequestID = mRequestID++;
	request.nCommandType = HTTPCMD_REQ_CLOSEROOM;
	request.uPrivData = (UINT64)pResultString;

	request.nVideoUrlBufLength = nVideoUrlBufLength;

	UINT32 uSendBufSize = sizeof(HTTPCMDREQCLOSEROOMCMD) + nVideoUrlBufLength;
	BYTE *pSendBuffer = new BYTE[uSendBufSize];
	if (!pSendBuffer)
	{
		return FALSE;
	}

	memcpy(pSendBuffer, &request, sizeof(HTTPCMDREQCLOSEROOMCMD));
	if (nVideoUrlBufLength > 0)
	{
		memcpy(pSendBuffer+sizeof(HTTPCMDREQCLOSEROOMCMD), cVideoUrlBuffer, nVideoUrlBufLength);
	}

	HTTPCMDREQWITHEVENT requestWithEvent;
	requestWithEvent.nRequestID = request.nRequestID;
	mRequestWithEventListLock.Lock();
	mRequestWithEventList.AddData(&requestWithEvent);
	mRequestWithEventListLock.Unlock();

	LOGMSG(DBG_LEVEL_I, "%s: req:nRequestID=%d\n", __PRETTY_FUNCTION__, request.nRequestID);
	if (SendData(MSG_TO_SERVERSOCKET, pSendBuffer, uSendBufSize))
	{
		if (!requestWithEvent.complete.Wait(5000))
		{
			LOGMSG(DBG_LEVEL_I, "%s: wait response timeout\n", __PRETTY_FUNCTION__);
		}
		else
		{
			bSendOK = TRUE;
		}
	}
	else
	{
		LOGMSG(DBG_LEVEL_I, "%s: SendData Failed\n", __PRETTY_FUNCTION__);
	}

	mRequestWithEventListLock.Lock();
	mRequestWithEventList.DeleteAt(mRequestWithEventList.FindFirst(&requestWithEvent));
	mRequestWithEventListLock.Unlock();

	delete []pSendBuffer;

	return bSendOK;
}

void CHttpCmdClient::OnResponseCloseRoomCmd(
	HTTPCMDRESCLOSEROOMCMD *pResCloseRoomCmdParam)
{
	CSimpleStringA *pResultString = (CSimpleStringA *)pResCloseRoomCmdParam->uPrivData;
	if (pResCloseRoomCmdParam->uSize > 0)
	{
		const char *pReadBuf = ((const char *)pResCloseRoomCmdParam)+sizeof(HTTPCMDRESCLOSEROOMCMD);
		pResultString->Set(pReadBuf, pResCloseRoomCmdParam->uSize);
	}
}

BOOL CHttpCmdClient::SendPayCallbackCmd(
	int nVideoUrlBufLength,
	const char *cVideoUrlBuffer,
	CSimpleStringA *pResultString)
{
	if (!IsConnect())
	{
		LOGMSG(DBG_LEVEL_I, "%s: HttpCmdServer NOT Started\n", __PRETTY_FUNCTION__);

		return FALSE;
	}

	BOOL bSendOK = FALSE;

	HTTPCMDREQPAYCALLBACKCMD request;
	request.nHttpCmdVer = HTTPCMD_VER;
	request.nRequestID = mRequestID++;
	request.nCommandType = HTTPCMD_REQ_PAYCALLBACK;
	request.uPrivData = (UINT64)pResultString;

	request.nVideoUrlBufLength = nVideoUrlBufLength;

	UINT32 uSendBufSize = sizeof(HTTPCMDREQPAYCALLBACKCMD) + nVideoUrlBufLength;
	BYTE *pSendBuffer = new BYTE[uSendBufSize];
	if (!pSendBuffer)
	{
		return FALSE;
	}

	memcpy(pSendBuffer, &request, sizeof(HTTPCMDREQPAYCALLBACKCMD));
	if (nVideoUrlBufLength > 0)
	{
		memcpy(pSendBuffer+sizeof(HTTPCMDREQPAYCALLBACKCMD), cVideoUrlBuffer, nVideoUrlBufLength);
	}

	HTTPCMDREQWITHEVENT requestWithEvent;
	requestWithEvent.nRequestID = request.nRequestID;
	mRequestWithEventListLock.Lock();
	mRequestWithEventList.AddData(&requestWithEvent);
	mRequestWithEventListLock.Unlock();

	LOGMSG(DBG_LEVEL_I, "%s: req:nRequestID=%d\n", __PRETTY_FUNCTION__, request.nRequestID);
	if (SendData(MSG_TO_SERVERSOCKET, pSendBuffer, uSendBufSize))
	{
		if (!requestWithEvent.complete.Wait(5000))
		{
			LOGMSG(DBG_LEVEL_I, "%s: wait response timeout\n", __PRETTY_FUNCTION__);
		}
		else
		{
			bSendOK = TRUE;
		}
	}
	else
	{
		LOGMSG(DBG_LEVEL_I, "%s: SendData Failed\n", __PRETTY_FUNCTION__);
	}

	mRequestWithEventListLock.Lock();
	mRequestWithEventList.DeleteAt(mRequestWithEventList.FindFirst(&requestWithEvent));
	mRequestWithEventListLock.Unlock();

	delete []pSendBuffer;

	return bSendOK;
}

void CHttpCmdClient::OnResponsePayCallbackCmd(
	HTTPCMDRESPAYCALLBACKCMD *pResPayCallbackCmdParam)
{
	CSimpleStringA *pResultString = (CSimpleStringA *)pResPayCallbackCmdParam->uPrivData;
	if (pResPayCallbackCmdParam->uSize > 0)
	{
		const char *pReadBuf = ((const char *)pResPayCallbackCmdParam)+sizeof(HTTPCMDRESPAYCALLBACKCMD);
		pResultString->Set(pReadBuf, pResPayCallbackCmdParam->uSize);
	}
}
