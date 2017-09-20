#include "HttpCmdClient.h"
#include "DbgOutput.h"
#include "commfunc.h"
#include <json/json.h>
#include "../GlobalUIClass.h"

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

	while (!mExitThread)
	{
		BOOL bIsOnline = FALSE;

		uActualResultSize = 0;
		do
		{
			if (!PerformHttpGetCommand(
				sURL.GetString(),
				NULL,
				cResultBuffer,
				1024,
				&uActualResultSize))
			{
				break;
			}

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

			int code = root["code"].asInt();
			std::string msg = root["codemsg"].asString();

			LOGMSG(DBG_LEVEL_I, "check online return: code=%d, msg=%s\n",
				code, msg.c_str());

			bIsOnline = code == 0 ? TRUE : FALSE;
		} while (0);

		mIsServerOnline = bIsOnline;

		mExitEvent.Wait(10000);
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
	resultJson["ip"] = Json::Value(cStbIP);
	resultJson["client_ip"] = Json::Value(cVodIP);
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
		return FALSE;
	}

	if (uActualResultSize >= 1024)
	{
		uActualResultSize = 1023;
	}

	cResultBuffer[uActualResultSize] = '\0';

	Json::Reader reader;
	Json::Value root;
	if (!reader.parse((char*)cResultBuffer, root))
	{
		return FALSE;
	}

	if (root["code"].isNull())
	{
		return FALSE;
	}

	if (root["codemsg"].isNull())
	{
		return FALSE;
	}

	int code = root["code"].asInt();
	std::string msg = root["codemsg"].asString();

	LOGMSG(DBG_LEVEL_I, "verify return: code=%d, msg=%s\n",
		code, msg.c_str());

	return code == 0 ? TRUE : FALSE;
}
