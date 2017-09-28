#include "HttpCmdServer.h"
#include "DbgOutput.h"
#include "commfunc.h"
#include <json/json.h>
#include "../GlobalUIClass.h"

CHttpCmdServer::CHttpCmdServer()
{
}

CHttpCmdServer::~CHttpCmdServer()
{
}

BOOL CHttpCmdServer::Create(
	UINT16 uServerPort,
	BOOL bLocalSocket,
	const char* cSocketThreadName)
{
	return CParentClass::Create(
		uServerPort,
		bLocalSocket,
		FALSE,
		TRUE,
		this,
		0,
		cSocketThreadName);
}

void CHttpCmdServer::OnServerReceiveTCPData(
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

	switch (phdr->nCommandType)
	{
	case HTTPCMD_REQ_REBOOT:
		OnRequestRebootCmd(nSocketFD, (HTTPCMDREQREBOOTCMD *)phdr);
		break;

	case HTTPCMD_REQ_PAUSE:
		OnRequestPauseCmd(nSocketFD, (HTTPCMDREQPAUSECMD *)phdr);
		break;

	case HTTPCMD_REQ_RESUME:
		OnRequestResumeCmd(nSocketFD, (HTTPCMDREQRESUMECMD *)phdr);
		break;

	case HTTPCMD_REQ_OPENROOM:
		OnRequestOpenRoomCmd(nSocketFD, (HTTPCMDREQOPENROOMCMD *)phdr);
		break;

	case HTTPCMD_REQ_CLOSEROOM:
		OnRequestCloseRoomCmd(nSocketFD, (HTTPCMDREQCLOSEROOMCMD *)phdr);
		break;

	case HTTPCMD_REQ_CHECKSTATUS:
		OnRequestCheckStatusCmd(nSocketFD, (HTTPCMDREQCHECKSTATUSCMD *)phdr);
		break;

	default:
		break;
	}
}

void CHttpCmdServer::OnRequestRebootCmd(
	int nSocketFD,
	HTTPCMDREQREBOOTCMD *pReqRebootCmd)
{
	LOGMSG(DBG_LEVEL_I, "%s:\n", __PRETTY_FUNCTION__);

	CSimpleStringA sResponseStateString;

	Json::Value resultJson;
	resultJson["code"] = Json::Value("0");
	resultJson["codemsg"] = Json::Value("请求成功");
	Json::FastWriter fast_writer;
	sResponseStateString.Set(fast_writer.write(resultJson).c_str());

	mOperatorLock.Lock();

	HTTPCMDRESREBOOTCMD response;
	response.nHttpCmdVer = HTTPCMD_VER;
	response.nRequestID = pReqRebootCmd->nRequestID;
	response.nCommandType = HTTPCMD_RES_REBOOT;
	response.uPrivData = pReqRebootCmd->uPrivData;
	response.uSize = sResponseStateString.GetLength();

	UINT32 uSendBufSize = sizeof(HTTPCMDRESREBOOTCMD) + response.uSize;
	BYTE *pSendBuffer = new BYTE[uSendBufSize];
	if (pSendBuffer)
	{
		int nBufPos = 0;

		memcpy(pSendBuffer+nBufPos, &response, sizeof(HTTPCMDRESREBOOTCMD));
		nBufPos += sizeof(HTTPCMDRESREBOOTCMD);

		memcpy(pSendBuffer+nBufPos, sResponseStateString.GetString(), response.uSize);
		nBufPos += response.uSize;
		SendData(nSocketFD, pSendBuffer, uSendBufSize);

		delete []pSendBuffer;

		Sleep(1000);
		system("reboot");
	}
	else
	{
		response.uSize = 0;
		SendData(nSocketFD, &response, sizeof(HTTPCMDRESREBOOTCMD));
	}

	mOperatorLock.Unlock();
}

void CHttpCmdServer::OnRequestPauseCmd(
	int nSocketFD,
	HTTPCMDREQPAUSECMD *pReqPauseCmd)
{
	LOGMSG(DBG_LEVEL_I, "%s:\n", __PRETTY_FUNCTION__);

	CSimpleStringA sResponseStateString;

	Json::Value resultJson;
	resultJson["code"] = Json::Value("0");
	resultJson["codemsg"] = Json::Value("请求成功");
	Json::FastWriter fast_writer;
	sResponseStateString.Set(fast_writer.write(resultJson).c_str());

	mOperatorLock.Lock();

	HTTPCMDRESPAUSECMD response;
	response.nHttpCmdVer = HTTPCMD_VER;
	response.nRequestID = pReqPauseCmd->nRequestID;
	response.nCommandType = HTTPCMD_RES_PAUSE;
	response.uPrivData = pReqPauseCmd->uPrivData;
	response.uSize = sResponseStateString.GetLength();

	UINT32 uSendBufSize = sizeof(HTTPCMDRESPAUSECMD) + response.uSize;
	BYTE *pSendBuffer = new BYTE[uSendBufSize];
	if (pSendBuffer)
	{
		int nBufPos = 0;

		memcpy(pSendBuffer+nBufPos, &response, sizeof(HTTPCMDRESPAUSECMD));
		nBufPos += sizeof(HTTPCMDRESPAUSECMD);

		memcpy(pSendBuffer+nBufPos, sResponseStateString.GetString(), response.uSize);
		nBufPos += response.uSize;
		SendData(nSocketFD, pSendBuffer, uSendBufSize);

		delete []pSendBuffer;

		if ( (gPageManager->GetCurPageType() == Page_SettingModify) ||
			 (gPageManager->GetCurPageType() == Page_SettingInfo) )
		{
			LOGMSG(DBG_LEVEL_I, "%s: in setting Page, we ignore this request!\n", __PRETTY_FUNCTION__);
		}
		else
		{
			const char* cImageUrlBuffer = NULL;
			if (pReqPauseCmd->nImageUrlBufLength)
			{
				cImageUrlBuffer = ((const char*)pReqPauseCmd) + sizeof(HTTPCMDREQPAUSECMD);
			}
			gPausePage->PerformHttpCmd_Pause(
				pReqPauseCmd->nSecondsPerImage,
				pReqPauseCmd->rcImagePosition,
				cImageUrlBuffer);
		}
	}
	else
	{
		response.uSize = 0;
		SendData(nSocketFD, &response, sizeof(HTTPCMDRESPAUSECMD));
	}

	mOperatorLock.Unlock();
}

void CHttpCmdServer::OnRequestResumeCmd(
	int nSocketFD,
	HTTPCMDREQRESUMECMD *pReqResumeCmd)
{
	LOGMSG(DBG_LEVEL_I, "%s:\n", __PRETTY_FUNCTION__);

	CSimpleStringA sResponseStateString;

	Json::Value resultJson;
	resultJson["code"] = Json::Value("0");
	resultJson["codemsg"] = Json::Value("请求成功");
	Json::FastWriter fast_writer;
	sResponseStateString.Set(fast_writer.write(resultJson).c_str());

	mOperatorLock.Lock();

	HTTPCMDRESRESUMECMD response;
	response.nHttpCmdVer = HTTPCMD_VER;
	response.nRequestID = pReqResumeCmd->nRequestID;
	response.nCommandType = HTTPCMD_RES_RESUME;
	response.uPrivData = pReqResumeCmd->uPrivData;
	response.uSize = sResponseStateString.GetLength();

	UINT32 uSendBufSize = sizeof(HTTPCMDRESRESUMECMD) + response.uSize;
	BYTE *pSendBuffer = new BYTE[uSendBufSize];
	if (pSendBuffer)
	{
		int nBufPos = 0;

		memcpy(pSendBuffer+nBufPos, &response, sizeof(HTTPCMDRESRESUMECMD));
		nBufPos += sizeof(HTTPCMDRESRESUMECMD);

		memcpy(pSendBuffer+nBufPos, sResponseStateString.GetString(), response.uSize);
		nBufPos += response.uSize;
		SendData(nSocketFD, pSendBuffer, uSendBufSize);

		delete []pSendBuffer;

		if ( (gPageManager->GetCurPageType() == Page_SettingModify) ||
			 (gPageManager->GetCurPageType() == Page_SettingInfo) )
		{
			LOGMSG(DBG_LEVEL_I, "%s: in setting Page, we ignore this request!\n", __PRETTY_FUNCTION__);
		}
		else
		{
			gPageManager->SetCurrentPage(Page_Hdmi);
		}
	}
	else
	{
		response.uSize = 0;
		SendData(nSocketFD, &response, sizeof(HTTPCMDRESRESUMECMD));
	}

	mOperatorLock.Unlock();
}

void CHttpCmdServer::OnRequestOpenRoomCmd(
	int nSocketFD,
	HTTPCMDREQOPENROOMCMD *pReqOpenRoomCmd)
{
	LOGMSG(DBG_LEVEL_I, "%s:\n", __PRETTY_FUNCTION__);

	CSimpleStringA sResponseStateString;

	Json::Value resultJson;
	resultJson["code"] = Json::Value("0");
	resultJson["codemsg"] = Json::Value("请求成功");
	Json::FastWriter fast_writer;
	sResponseStateString.Set(fast_writer.write(resultJson).c_str());

	mOperatorLock.Lock();

	HTTPCMDRESOPENROOMCMD response;
	response.nHttpCmdVer = HTTPCMD_VER;
	response.nRequestID = pReqOpenRoomCmd->nRequestID;
	response.nCommandType = HTTPCMD_RES_OPENROOM;
	response.uPrivData = pReqOpenRoomCmd->uPrivData;
	response.uSize = sResponseStateString.GetLength();

	UINT32 uSendBufSize = sizeof(HTTPCMDRESOPENROOMCMD) + response.uSize;
	BYTE *pSendBuffer = new BYTE[uSendBufSize];
	if (pSendBuffer)
	{
		int nBufPos = 0;

		memcpy(pSendBuffer+nBufPos, &response, sizeof(HTTPCMDRESOPENROOMCMD));
		nBufPos += sizeof(HTTPCMDRESOPENROOMCMD);

		memcpy(pSendBuffer+nBufPos, sResponseStateString.GetString(), response.uSize);
		nBufPos += response.uSize;
		SendData(nSocketFD, pSendBuffer, uSendBufSize);

		delete []pSendBuffer;

		if ( (gPageManager->GetCurPageType() == Page_SettingModify) ||
			 (gPageManager->GetCurPageType() == Page_SettingInfo) )
		{
			LOGMSG(DBG_LEVEL_I, "%s: in setting Page, we ignore this request!\n", __PRETTY_FUNCTION__);
		}
		else
		{
			const char* cVideoUrlBuffer = NULL;
			if (pReqOpenRoomCmd->nVideoUrlBufLength)
			{
				cVideoUrlBuffer = ((const char*)pReqOpenRoomCmd) + sizeof(HTTPCMDREQOPENROOMCMD);
			}
			gOpenRoomPage->PerformHttpCmd_OpenRoom(
				pReqOpenRoomCmd->cQRCodeString,
				pReqOpenRoomCmd->rcQRCodePosition,
				cVideoUrlBuffer);
		}
	}
	else
	{
		response.uSize = 0;
		SendData(nSocketFD, &response, sizeof(HTTPCMDRESOPENROOMCMD));
	}

	mOperatorLock.Unlock();
}

void CHttpCmdServer::OnRequestCloseRoomCmd(
	int nSocketFD,
	HTTPCMDREQCLOSEROOMCMD *pReqCloseRoomCmd)
{
	LOGMSG(DBG_LEVEL_I, "%s:\n", __PRETTY_FUNCTION__);

	CSimpleStringA sResponseStateString;

	Json::Value resultJson;
	resultJson["code"] = Json::Value("0");
	resultJson["codemsg"] = Json::Value("请求成功");
	Json::FastWriter fast_writer;
	sResponseStateString.Set(fast_writer.write(resultJson).c_str());

	mOperatorLock.Lock();

	HTTPCMDRESCLOSEROOMCMD response;
	response.nHttpCmdVer = HTTPCMD_VER;
	response.nRequestID = pReqCloseRoomCmd->nRequestID;
	response.nCommandType = HTTPCMD_RES_CLOSEROOM;
	response.uPrivData = pReqCloseRoomCmd->uPrivData;
	response.uSize = sResponseStateString.GetLength();

	UINT32 uSendBufSize = sizeof(HTTPCMDRESCLOSEROOMCMD) + response.uSize;
	BYTE *pSendBuffer = new BYTE[uSendBufSize];
	if (pSendBuffer)
	{
		int nBufPos = 0;

		memcpy(pSendBuffer+nBufPos, &response, sizeof(HTTPCMDRESCLOSEROOMCMD));
		nBufPos += sizeof(HTTPCMDRESCLOSEROOMCMD);

		memcpy(pSendBuffer+nBufPos, sResponseStateString.GetString(), response.uSize);
		nBufPos += response.uSize;
		SendData(nSocketFD, pSendBuffer, uSendBufSize);

		delete []pSendBuffer;

		if ( (gPageManager->GetCurPageType() == Page_SettingModify) ||
			 (gPageManager->GetCurPageType() == Page_SettingInfo) )
		{
			LOGMSG(DBG_LEVEL_I, "%s: in setting Page, we ignore this request!\n", __PRETTY_FUNCTION__);
		}
		else
		{
			const char* cVideoUrlBuffer = NULL;
			if (pReqCloseRoomCmd->nVideoUrlBufLength)
			{
				cVideoUrlBuffer = ((const char*)pReqCloseRoomCmd) + sizeof(HTTPCMDREQCLOSEROOMCMD);
			}
			gCloseRoomPage->PerformHttpCmd_CloseRoom(cVideoUrlBuffer);
		}
	}
	else
	{
		response.uSize = 0;
		SendData(nSocketFD, &response, sizeof(HTTPCMDRESCLOSEROOMCMD));
	}

	mOperatorLock.Unlock();
}

void CHttpCmdServer::OnRequestCheckStatusCmd(
	int nSocketFD,
	HTTPCMDREQCHECKSTATUSCMD *pReqCheckStatusCmd)
{
	LOGMSG(DBG_LEVEL_I, "%s:\n", __PRETTY_FUNCTION__);

	CSimpleStringA sResponseStateString;

	Json::Value resultJson;
	if(!IsFileExist("/networkflag.txt"))
	{
		resultJson["code"] = Json::Value("1");
		resultJson["codemsg"] = Json::Value("程序不是从网络启动");
	}
	else
	{
		resultJson["code"] = Json::Value("0");
		resultJson["codemsg"] = Json::Value("在线");
	}

	Json::FastWriter fast_writer;
	sResponseStateString.Set(fast_writer.write(resultJson).c_str());

	mOperatorLock.Lock();

	HTTPCMDRESCHECKSTATUSCMD response;
	response.nHttpCmdVer = HTTPCMD_VER;
	response.nRequestID = pReqCheckStatusCmd->nRequestID;
	response.nCommandType = HTTPCMD_RES_CHECKSTATUS;
	response.uPrivData = pReqCheckStatusCmd->uPrivData;
	response.uSize = sResponseStateString.GetLength();

	UINT32 uSendBufSize = sizeof(HTTPCMDRESCHECKSTATUSCMD) + response.uSize;
	BYTE *pSendBuffer = new BYTE[uSendBufSize];
	if (pSendBuffer)
	{
		int nBufPos = 0;

		memcpy(pSendBuffer+nBufPos, &response, sizeof(HTTPCMDRESCHECKSTATUSCMD));
		nBufPos += sizeof(HTTPCMDRESCHECKSTATUSCMD);

		memcpy(pSendBuffer+nBufPos, sResponseStateString.GetString(), response.uSize);
		nBufPos += response.uSize;
		SendData(nSocketFD, pSendBuffer, uSendBufSize);

		delete []pSendBuffer;
	}
	else
	{
		response.uSize = 0;
		SendData(nSocketFD, &response, sizeof(HTTPCMDRESCHECKSTATUSCMD));
	}

	mOperatorLock.Unlock();
}
