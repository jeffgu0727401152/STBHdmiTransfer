#include "GlobalUIClass.h"
#include "DbgOutput.h"
#include "CodeConvert.h"
#include "SocketInterface.h"

CHandWriteOperator* gHandWriteOperator=NULL;
CPageManager* gPageManager=NULL;
CPlayerCtrl* gPlayerCtrl=NULL;
CMultiMediaCtrl* gMultiMediaCtrl=NULL;
CHttpCmdClient* gHttpCmdClient=NULL;
CHttpCmdServer* gHttpCmdServer=NULL;

void InitGlobalClass()
{
	LOGMSG(DBG_LEVEL_I, "%s\n", __PRETTY_FUNCTION__);

	gHandWriteOperator = new CHandWriteOperator();
	gPageManager = new CPageManager();
	gPlayerCtrl = new CPlayerCtrl();
	gMultiMediaCtrl = new CMultiMediaCtrl();
	gHttpCmdClient = new CHttpCmdClient();
	gHttpCmdServer = new CHttpCmdServer();
}

void DeInitGlobalClass()
{
	SAFE_DELETE(gHttpCmdClient);
	SAFE_DELETE(gHttpCmdServer);
	SAFE_DELETE(gPlayerCtrl);
	SAFE_DELETE(gMultiMediaCtrl);
	SAFE_DELETE(gPageManager);
	SAFE_DELETE(gHandWriteOperator);
}

void InitDynamicLibs()
{
	InitSysLibCodeConvert();
}

void DeinitDynamicLibs()
{
	DeInitSysLibCodeConvert();
}

// 单位：微妙，default=5fps
BOOL gE3DIsBusy = FALSE;
UINT64 gRefreshDelayTime = 200000;
UINT64 gStatisticsRefreshTime = 0;
UINT64 gLastUpdateTime = 0;
int gStatisticsCount = 0;

void SetE3DBusy(
	BOOL bBusy)
{
	LOGMSG(DBG_LEVEL_I, "SetE3DBusy=%d!!\n", bBusy);

	gE3DIsBusy = bBusy;
}

void UpdateRefreshDelayTime(
	UINT64 uRefreshUsedTime,
	UINT64 uCurTickCountUS)
{
	UINT64 uAvarageRefreshTime = 0;

	gStatisticsRefreshTime += uRefreshUsedTime;
	gStatisticsCount ++;

	// 每1s更新一次
	if ((uCurTickCountUS - gLastUpdateTime) > 1000000)
	{
		uAvarageRefreshTime = gStatisticsRefreshTime / gStatisticsCount;

		UINT64 uRefreshDelayTime = gRefreshDelayTime;
		if (gE3DIsBusy || (uAvarageRefreshTime > 200000))
		{
			// 5 fps
			uRefreshDelayTime = 200000;
		}
#if 1
		// use dynamic fps
		else if (uAvarageRefreshTime > 33333)
		{
			// 30 fps
			uRefreshDelayTime = 33333;
		}
		else if (uAvarageRefreshTime > 28571)
		{
			// 35 fps
			uRefreshDelayTime = 28571;
		}
		else if (uAvarageRefreshTime > 25000)
		{
			// 40 fps
			uRefreshDelayTime = 25000;
		}
		else if (uAvarageRefreshTime > 20000)
		{
			// 50 fps
			uRefreshDelayTime = 20000;
		}
		else
		{
			// 60 fps
			uRefreshDelayTime = 16666;
		}
#else
		// use fixed fps
		else
		{
			// 40 fps
			uRefreshDelayTime = 25000;
		}
#endif

		if (uRefreshDelayTime != gRefreshDelayTime)
		{
			LOGMSG(DBG_LEVEL_I, "change refresh delay time to %lld us\n", uRefreshDelayTime);
			gRefreshDelayTime = uRefreshDelayTime;
		}

		gStatisticsRefreshTime = 0;
		gStatisticsCount = 0;
		gLastUpdateTime = uCurTickCountUS;
	}
}
