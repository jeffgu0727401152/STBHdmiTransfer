#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "commfunc.h"
#include "DbgOutput.h"
#include "SimpleString.h"
#include "FileOperator.h"
#include "UrlCodec.h"
#include "HttpCmdClient.h"
#include <signal.h>
#include <json/json.h>
#include <fcgi_stdio.h>

CHttpCmdClient gHttpCmdClient;

static void SendResponseString(CSimpleStringA *pResultString)
{
	FCGI_printf(
		"Content-type: text/html\r\n"
		"Access-Control-Allow-Origin:*\r\n"
		"Access-Control-Allow-Methods:GET,POST\r\n"
		"Access-Control-Allow-Headers:content-type\r\n"
		"\r\n");

	FCGI_puts(pResultString->GetString());
}

static void GenerateErrorString(CSimpleStringA *pResultString)
{
	Json::Value resultJson;
	resultJson["code"] = Json::Value("-1");
	resultJson["codemsg"] = Json::Value("命令发送失败");
	Json::FastWriter fast_writer;
	pResultString->Set(fast_writer.write(resultJson).c_str());
}

void ProcessCommand(
	CPtrCtrl *pArgList)
{
	const char* cCmdType = (const char* )pArgList->GetAt(0);
	if (!cCmdType)
	{
		return;
	}

	CSimpleStringA sResultString;

	/**
	 * Warning: About the cCmdType if you  want to add a new num ,you should check if the num is large than 9 ,
	 * you should put the big action num before the short string num to make the case run in right logic.
	 */
	if (strcmp(cCmdType, "test") == 0)
	{
		sResultString.Set("this is just for test");
		SendResponseString(&sResultString);
	}
	else if (strncasecmp(cCmdType, "action=11", 9) == 0)
	{
		// 关房
		const char* cVideoUrlBuffer = NULL;
		for (int i = 1; i < pArgList->GetCount(); i++)
		{
			const char* cArg = (const char*)pArgList->GetAt(i);
			if (!cArg)
			{
				continue;
			}

			if (strncasecmp(cArg, "video_url=", 10) == 0)
			{
				cVideoUrlBuffer = cArg + 10;
			}
		}

		if (!gHttpCmdClient.SendCloseRoomCmd(
			cVideoUrlBuffer?strlen(cVideoUrlBuffer)+1:0,
			cVideoUrlBuffer,
			&sResultString))
		{
			GenerateErrorString(&sResultString);
		}

		SendResponseString(&sResultString);
	}
	else if (strncasecmp(cCmdType, "action=10", 9) == 0)
	{
		// 画中画
		const char* cVideoUrlBuffer = NULL;
		int left = 943;
		int top = 340;
		int width = 186;
		int height= 186;
		RECT rcPipPosition = {left,top,left+width,top+height};
		for (int i = 1; i < pArgList->GetCount(); i++)
		{
			const char* cArg = (const char*)pArgList->GetAt(i);
			if (!cArg)
			{
				continue;
			}

			if (strncasecmp(cArg, "video_url=", 10) == 0)
			{
				cVideoUrlBuffer = cArg + 10;
			}
			else if (strncasecmp(cArg, "position=", 9) == 0)
			{
				if( '\0' == *(cArg + 9))
				{
					LOGMSG(DBG_LEVEL_I, "Position string is empty , use {943,340,186,186} as default temporarily\n");
				}else
				{
					ParserRectFromString(cArg + 9, &rcPipPosition);
				}
			}
		}

		if (!gHttpCmdClient.SendPipPreviewCmd(
			rcPipPosition,
			cVideoUrlBuffer?strlen(cVideoUrlBuffer)+1:0,
			cVideoUrlBuffer,
			&sResultString))
		{
			GenerateErrorString(&sResultString);
		}

		SendResponseString(&sResultString);
	}
	else if (strncasecmp(cCmdType, "action=9", 8) == 0)
	{
		// 查询盒子状态
		if (!gHttpCmdClient.SendCheckStatusCmd(&sResultString))
		{
			GenerateErrorString(&sResultString);
		}

		SendResponseString(&sResultString);
	}
	else if (strncasecmp(cCmdType, "action=8", 8) == 0)
	{
		// 重启盒子
		if (!gHttpCmdClient.SendRebootCmd(&sResultString))
		{
			GenerateErrorString(&sResultString);
		}

		SendResponseString(&sResultString);
	}
	else if (strncasecmp(cCmdType, "action=6", 8) == 0)
	{
		// 取消暂停
		if (!gHttpCmdClient.SendResumeCmd(&sResultString))
		{
			GenerateErrorString(&sResultString);
		}

		SendResponseString(&sResultString);
	}
	else if (strncasecmp(cCmdType, "action=3", 8) == 0)
	{
		// 暂停
		const char* cImageUrlBuffer = NULL;
		RECT rcImagePosition = {0, 0, 0, 0};
		int nSecondsPerImage = 5;
		for (int i = 1; i < pArgList->GetCount(); i++)
		{
			const char* cArg = (const char*)pArgList->GetAt(i);
			if (!cArg)
			{
				continue;
			}

			if (strncasecmp(cArg, "image_url=", 10) == 0)
			{
				cImageUrlBuffer = cArg + 10;
			}
			else if (strncasecmp(cArg, "position=", 9) == 0)
			{
				ParserRectFromString(cArg + 9, &rcImagePosition);
			}
			else if (strncasecmp(cArg, "timeout=", 8) == 0)
			{
				nSecondsPerImage = atoi(cArg+8);
			}
		}

		if (!gHttpCmdClient.SendPauseCmd(
			nSecondsPerImage,
			rcImagePosition,
			cImageUrlBuffer?strlen(cImageUrlBuffer)+1:0,
			cImageUrlBuffer,
			&sResultString))
		{
			GenerateErrorString(&sResultString);
		}

		SendResponseString(&sResultString);
	}
	else if (strncasecmp(cCmdType, "action=1", 8) == 0)
	{
		// 开房
		const char* cQRCodeString = NULL;
		const char* cVideoUrlBuffer = NULL;
		int left = 943;
		int top = 340;
		int width = 186;
		int height= 186;
		RECT rcQRCodePosition = {left,top,left+width,top+height};
		for (int i = 1; i < pArgList->GetCount(); i++)
		{
			const char* cArg = (const char*)pArgList->GetAt(i);
			if (!cArg)
			{
				continue;
			}

			if (strncasecmp(cArg, "video_url=", 10) == 0)
			{
				cVideoUrlBuffer = cArg + 10;
			}
			else if (strncasecmp(cArg, "position=", 9) == 0)
			{
				if( '\0' == *(cArg + 9))
				{
					LOGMSG(DBG_LEVEL_I, "Position string is empty , use {943,340,186,186} as default temporarily\n");
				}else
				{
					ParserRectFromString(cArg + 9, &rcQRCodePosition);
				}
			}
			else if (strncasecmp(cArg, "qr_url=", 7) == 0)
			{
				cQRCodeString = cArg + 7;
			}
		}

		if (!gHttpCmdClient.SendOpenRoomCmd(
			cQRCodeString,
			rcQRCodePosition,
			cVideoUrlBuffer?strlen(cVideoUrlBuffer)+1:0,
			cVideoUrlBuffer,
			&sResultString))
		{
			GenerateErrorString(&sResultString);
		}

		SendResponseString(&sResultString);
	}
	else if (strncasecmp(cCmdType, "action=4", 8) == 0)
	{
		// 支付回调
		const char* cVideoUrlBuffer = NULL;
		for (int i = 1; i < pArgList->GetCount(); i++)
		{
			const char* cArg = (const char*)pArgList->GetAt(i);
			if (!cArg)
			{
				continue;
			}

			if (strncasecmp(cArg, "video_url=", 10) == 0)
			{
				cVideoUrlBuffer = cArg + 10;
			}
		}

		if (!gHttpCmdClient.SendPayCallbackCmd(
			cVideoUrlBuffer?strlen(cVideoUrlBuffer)+1:0,
			cVideoUrlBuffer,
			&sResultString))
		{
			GenerateErrorString(&sResultString);
		}

		SendResponseString(&sResultString);
	}
	
	else
	{
		sResultString.Set("unknown command");
		SendResponseString(&sResultString);
	}
}

void SignalHandler(
	int sig)
{
	LOGMSG(DBG_LEVEL_E, "Signal %d caught...\n", sig);

	DumpThreadStack();

	exit(0);
}

int main()
{
	setlocale(LC_CTYPE, "zh_CN.UTF-8");

	signal(SIGABRT, &SignalHandler);
	signal(SIGTERM, &SignalHandler);
	signal(SIGFPE, &SignalHandler);
	signal(SIGINT, &SignalHandler);
	signal(SIGSEGV, &SignalHandler);
	signal(SIGKILL, &SignalHandler);

	char cLogFile[MAX_PATH];
	sprintf(cLogFile, "/stb/config/app/Log/STBCGI.log");
	DbgOutputOpenFile(cLogFile, FALSE);

	LOGMSG(DBG_LEVEL_E, "STBCGI Started\n");

	if (!gHttpCmdClient.IsConnect())
	{
		gHttpCmdClient.Create(
			"127.0.0.1",
			HTTPCMD_SOCKETPORT,
			FALSE,
			"FastCGI_ClientSocket");
	}

	LOGMSG(DBG_LEVEL_I, "\n\n");

	DbgFlush();

	// example: http://ip:port/WebSTBRequest?Cmd=Volumeup
	while (FCGI_Accept() >= 0)
	{
		const char *cArgString = getenv("QUERY_STRING");
		//const char *cArgString = "Cmd=Volumeup";
		//const char *cArgString = "Cmd=RequestSingerList&IMEType=Spell&IMEContent=LDH&SingerDBType=大陆男歌星";
		//const char *cArgString = "Cmd=RequestSongList&IMEType=Spell&IMEContent=DSL&LanguageDBType=国语&WordcountDBType=三字歌&SearchType=DBTYPE&SearchContent=儿歌";
		//const char *cArgString = "Cmd=RequestSongList&IMEType=Spell&IMEContent=DSL&SearchType=SINGER&SearchContent=%E5%8D%93%E4%BE%9D%E5%A9%B7";
		//const char *cArgString = "Cmd=RequestPlayerState";

		CSimpleStringA sOutputString;
		DecodeURL(cArgString, &sOutputString);
		cArgString = sOutputString.GetString();
		if (sOutputString.GetLength() == 0)
		{
			continue;
		}

		LOGMSG(DBG_LEVEL_I, "------ARG:%s-------\n", cArgString);

		if (!gHttpCmdClient.IsConnect())
		{
			gHttpCmdClient.Create(
				"127.0.0.1",
				HTTPCMD_SOCKETPORT,
				FALSE,
				"HttpCmd_ClientSocket");
		}

		CPtrArrayCtrl sArgList;
		const char *cDevString = DevideStringByCharListA(
			cArgString,
			-1,
			"&",
			1,
			FALSE,
			&sArgList,
			-1);

		ProcessCommand(&sArgList);

		Internal_DelArrayA(cDevString);

		LOGMSG(DBG_LEVEL_I, "---------------------------\n\n");

		DbgFlush();
	} /* while */

	gHttpCmdClient.Close();

	DbgOutputCloseFile();

	return 0;
}
