#include "HttpCmdClient.h"
#include "DbgOutput.h"
#include "commfunc.h"
#include <json/json.h>
#include "../GlobalUIClass.h"

#define HEART_BEAT_LOST_THRESHOLD 2

CHttpCmdClient::CHttpCmdClient()
{
	mServerIP[0] = '\0';
	mServerPort = 0;

	mIsServerOnline = FALSE;

	mExitThread = FALSE;
}

CHttpCmdClient::~CHttpCmdClient()
{
}

void CHttpCmdClient::Start(
	const char* cServerIP,
	int nServerPort)
{
	SAFE_STRNCPY(mServerIP, cServerIP, 16);
	mServerPort = nServerPort;

	mExitThread = FALSE;
	mExitEvent.Reset();
	mCheckOnlineThread.StartThread("CheckOnlineThread", this, 0, STACKSIZE_MIN);
}

void CHttpCmdClient::Stop()
{
	mExitThread = TRUE;

	mExitEvent.Set();
	mCheckOnlineThread.StopThread();
}

BOOL CHttpCmdClient::ThreadLoop(
	UINT64 uThreadData)
{
	CSimpleStringA sURL;
	sURL.Format("http://%s:%d/ads/api/check", mServerIP, mServerPort);

	BYTE cResultBuffer[1024];
	UINT32 uActualResultSize = 0;
	UINT32 heartBeatLostCount = 0;

	while (!mExitThread)
	{
		BOOL bIsOnline = FALSE;

		uActualResultSize = 0;
		do
		{
			if (heartBeatLostCount)
			{
				LOGMSG(DBG_LEVEL_I, "check online fail count = %d\n",heartBeatLostCount);
			}

			if (!PerformHttpGetCommand(
				sURL.GetString(),
				NULL,
				cResultBuffer,
				1024,
				&uActualResultSize))
			{
				if (gProgramBootMode == Mode_Factory)
				{
					LOGMSG(DBG_LEVEL_W, "check online failed, but gProgramBootMode is Mode_Factory, so do nothing!\n");
					break;
				}

				heartBeatLostCount++;
				if (heartBeatLostCount > HEART_BEAT_LOST_THRESHOLD)
				{
					PAGE_TYPE currentPage  = gPageManager->GetCurPageType();
					if (!(Page_Blank ==  currentPage || Page_SettingModify == currentPage || Page_SettingInfo == currentPage))
					{
						LOGMSG(DBG_LEVEL_W, "check online failed, SetCurrentPage to Blank\n");
						gPageManager->SetCurrentPage(Page_Blank);
					}
					heartBeatLostCount = 0;
				}
				break;
			}

			heartBeatLostCount = 0;

			if (uActualResultSize >= 1024)
			{
				uActualResultSize = 1023;
			}

			cResultBuffer[uActualResultSize] = '\0';

			Json::Reader reader;
			Json::Value root;
			if (!reader.parse((char*)cResultBuffer, root))
			{
				break;
			}

			if (root["code"].isNull())
			{
				break;
			}

			if (root["codemsg"].isNull())
			{
				break;
			}

			int code = 1;
			std::string msg;
			if (root["code"].isInt())
			{
				code = root["code"].asInt();
			}
			else if (root["code"].isString() )
			{
				code = atoi(root["code"].asString().c_str());
			}


			if (root["codemsg"].isString() )
			{
				msg = root["codemsg"].asString();
			}

			LOGMSG(DBG_LEVEL_I, "check online return: code=%d, msg=%s\n",
				code, msg.c_str());

			bIsOnline = code == 0 ? TRUE : FALSE;
		} while (0);

		mIsServerOnline = bIsOnline;

		mExitEvent.Wait(5000);
	}

	return FALSE;
}

BOOL CHttpCmdClient::GetIsServerOnline()
{
	return mIsServerOnline;
}

BOOL CHttpCmdClient::ClientVerify(
	const char* cMac,
	const char* cStbIP,
	const char* cVodIP,
	const char* cRoomID)
{
	CSimpleStringA sURL;
	sURL.Format("http://%s:%d/ads/api/auth", mServerIP, mServerPort);

	CSimpleStringA sData;
	Json::Value resultJson;
	resultJson["mac"] = Json::Value(cMac);
	resultJson["client_ip"] = Json::Value(cStbIP);
	resultJson["room_ip"] = Json::Value(cVodIP);
	resultJson["room_id"] = Json::Value(cRoomID);
	Json::FastWriter fast_writer;
	sData.Set(fast_writer.write(resultJson).c_str());

	CBuffer sBuffer;
	sBuffer.BindBuffer(sData.GetString(), sData.GetLength());

	BYTE cResultBuffer[1024];
	UINT32 uActualResultSize = 0;

	if (!PerformHttpPostCommand(
		sURL.GetString(),
		NULL,
		&sBuffer,
		cResultBuffer,
		1024,
		&uActualResultSize))
	{
		LOGMSG(DBG_LEVEL_E, "ClientVerify return: PerformHttpPostCommand error\n");
		return FALSE;
	}

	if (uActualResultSize >= 1024)
	{
		uActualResultSize = 1023;
	}

	cResultBuffer[uActualResultSize] = '\0';

	LOGMSG(DBG_LEVEL_I, "ClientVerify return: raw result buffer=%s\n",cResultBuffer);

	Json::Reader reader;
	Json::Value root;
	if (!reader.parse((char*)cResultBuffer, root))
	{
		LOGMSG(DBG_LEVEL_E, "ClientVerify return: reader parse no root)\n");
		return FALSE;
	}

	if (root["code"].isNull())
	{
		LOGMSG(DBG_LEVEL_E, "ClientVerify return: code is Null)\n");
		return FALSE;
	}

	if (root["codemsg"].isNull())
	{
		LOGMSG(DBG_LEVEL_E, "ClientVerify return: codemsg is Null)\n");
		return FALSE;
	}

	int code = 1;
	std::string msg;
	if (root["code"].isInt())
	{
		code = root["code"].asInt();
	}
	else if (root["code"].isString() )
	{
		code = atoi(root["code"].asString().c_str());
	}


	if (root["codemsg"].isString() )
	{
		msg = root["codemsg"].asString();
	}

	LOGMSG(DBG_LEVEL_I, "verify return: code=%d, msg=%s\n",
		code, msg.c_str());

	return code == 0 ? TRUE : FALSE;
}

BOOL CHttpCmdClient::ClientOpen(
	const char* cVodIP,
	CSimpleStringA *pResultUrlString)
{
	CSimpleStringA sURL;
	sURL.Format("http://%s:%d/ads/api/open?room_ip=%s", mServerIP, mServerPort,cVodIP);

	BYTE cResultBuffer[1024];
	UINT32 uActualResultSize = 0;

	if (!PerformHttpGetCommand(
		sURL.GetString(),
		NULL,
		cResultBuffer,
		1024,
		&uActualResultSize))
	{
		LOGMSG(DBG_LEVEL_E, "ClientOpen return: PerformHttpGetCommand error\n");
		return FALSE;
	}

	if (uActualResultSize >= 1024)
	{
		uActualResultSize = 1023;
	}

	cResultBuffer[uActualResultSize] = '\0';

	LOGMSG(DBG_LEVEL_I, "ClientOpen return: raw result buffer=%s\n",cResultBuffer);

	Json::Reader reader;
	Json::Value root;
	if (!reader.parse((char*)cResultBuffer, root))
	{
		LOGMSG(DBG_LEVEL_E, "ClientOpen return: reader parse no root\n");
		return FALSE;
	}

	if (root["code"].isNull())
	{
		LOGMSG(DBG_LEVEL_E, "ClientOpen return: code is Null\n");
		return FALSE;
	}

	if (root["codemsg"].isNull())
	{
		LOGMSG(DBG_LEVEL_E, "ClientOpen return: codemsg is Null\n");
		return FALSE;
	}

	if (root["video_url"].isNull())
	{
		LOGMSG(DBG_LEVEL_W, "ClientOpen return: video_url is Null\n");
		//return FALSE;
	}

	int code = 1;
	std::string msg;
	std::string url;
	if (root["code"].isInt())
	{
		code = root["code"].asInt();
	}
	else if (root["code"].isString() )
	{
		code = atoi(root["code"].asString().c_str());
	}


	if (root["codemsg"].isString() )
	{
		msg = root["codemsg"].asString();
	}

	if (!root["video_url"].isNull() && root["video_url"].isString())
	{
		url = root["video_url"].asString();
		pResultUrlString->Set(url.c_str());
	}

	LOGMSG(DBG_LEVEL_I, "ClientOpen return: code=%d, msg=%s, video_url=%s\n",
		code, msg.c_str(), url.c_str());


	return code == 0 ? TRUE : FALSE;
}
