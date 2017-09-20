//============================================================================
// Name        : KTVSample.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

//#include <iostream>
//using namespace std;

#include <signal.h>
#include "BaseApp.h"
#include "Song.h"
#include "GlobalUIClass.h"

void UnregisterSigHandler()
{
	LOGMSG(DBG_LEVEL_W, "unregister signal ++++++\n");

	signal(SIGTERM, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGSEGV, SIG_DFL);
	signal(SIGUSR2, SIG_DFL);

	LOGMSG(DBG_LEVEL_W, "unregister signal ------\n");
}

void SignalHandler(
	int sig)
{
	LOGMSG(DBG_LEVEL_E, "Signal %d caught...\n", sig);

	if (sig == SIGUSR2)
	{
		LOGMSG(DBG_LEVEL_W, "signal SIGUSR2 ++++++\n");

		DumpAllThreadsStackBySignal(-1);
	}
	else
	{
		LOGMSG(DBG_LEVEL_W, "signal, need to exit! ++++++\n");

		UnregisterSigHandler();

		DumpThreadStack();

		DumpAllThreadsStackBySignal(getlwpid());

		// 异常后，消息线程可能无法在处理消息，直接退出程序
		theBaseApp->PostQuitMsg();
		//exit(0);
	}

	do_syscmd(NULL, "sync");

	LOGMSG(DBG_LEVEL_E, "Signal %d Process End\n", sig);
}

void RegisterSigHandler()
{
	LOGMSG(DBG_LEVEL_W, "register signal ++++++\n");

	signal(SIGTERM, &SignalHandler);
	signal(SIGSEGV, &SignalHandler);
	signal(SIGABRT, &SignalHandler);
	signal(SIGHUP, &SignalHandler);

	signal(SIGQUIT, &SignalHandler);
	signal(SIGUSR2, &SignalHandler);

	signal(SIGUSR1, &thread_callstack_sighandler);

	LOGMSG(DBG_LEVEL_W, "register signal, SIGUSR1=%d, SIGUSR2=%d ------\n", SIGUSR1, SIGUSR2);
}

void PrintMachineInfo()
{
#if defined(PC_VERSION)
#pragma message ("This is PC Version!")
	LOGMSG(DBG_LEVEL_I, "This is PC Version\n");
#else
#pragma message ("This is Embedded Version!")
	LOGMSG(DBG_LEVEL_I, "This is Embedded Version\n");
#endif

	LOGMSG(DBG_LEVEL_W, "sizeof(BYTE *) = %d, expect=4(32bit machine), 8(64bit machine)\n", sizeof(BYTE *));
	LOGMSG(DBG_LEVEL_W, "sizeof(int) = %d, expect=4\n", sizeof(int));
	LOGMSG(DBG_LEVEL_W, "sizeof(size_t) = %d, expect=4(32bit machine), 8(64bit machine)\n", sizeof(size_t));
	LOGMSG(DBG_LEVEL_W, "sizeof(long) = %d, expect=4(32bit machine), 8(64bit machine)\n", sizeof(long));
	LOGMSG(DBG_LEVEL_W, "sizeof(wchar_t) = %d, expect=4\n", sizeof(wchar_t));
	LOGMSG(DBG_LEVEL_W, "sizeof(UINT16) = %d, expect=2\n", sizeof(UINT16));
	LOGMSG(DBG_LEVEL_W, "sizeof(UINT32) = %d, expect=4\n", sizeof(UINT32));
	LOGMSG(DBG_LEVEL_W, "sizeof(UINT64) = %d, expect=8\n", sizeof(UINT64));
	LOGMSG(DBG_LEVEL_W, "sizeof(UUID) = %d, expect=16\n", sizeof(UUID));
	LOGMSG(DBG_LEVEL_W, "sizeof(__time_t) = %d, expect=4(32bit machine), 8(64bit machine)\n", sizeof(__time_t));
	LOGMSG(DBG_LEVEL_W, "sizeof(__suseconds_t) = %d, expect=4(32bit machine), 8(64bit machine)\n", sizeof(__suseconds_t));
}


BOOL gMainLoopExit = FALSE;
BOOL gInitUIComplete = FALSE;

void InitUI()
{
	LOGMSG(DBG_LEVEL_W, "Start...\n");

	theBaseApp->ForceShowCursor(TRUE);

	theBaseApp->SetInputType(INPUTTYPE_DEVICE);

	// 先加载资源文件
	theBaseApp->InitSystemRes();
	theBaseApp->Run();

	BYTE pResKey[16]={0};
	char cResourceFolder[MAX_PATH];
	CombinePathName(cResourceFolder, gKTVConfig.GetProgramFolder(), RESOURCE_FOLDER);
	if (theBaseApp->LoadResource(cResourceFolder, LanguageID_CHS, pResKey, 16))
	{
		theBaseApp->LoadLimitRes();
		theBaseApp->SetLimitTime(0);
	}

	gHandWriteOperator->Init( FALSE);

	// 创建窗口
	LOGMSG(DBG_LEVEL_I, "Create page manager\n");
	gPageManager->Create(theBaseApp->GetE3DEngine(), theBaseApp->GetMainWindow());

	theBaseApp->UpdatePopupZorder(FALSE);
	theBaseApp->UpdateEmbeddedZorder();

	// 加载窗口资源
	theBaseApp->ChangeLanguage();
	theBaseApp->FreeResource();

	theBaseApp->StartInput();
	gInitUIComplete = TRUE;

	if(IsFileExist("/networkflag.txt"))
	{
		LOGMSG(DBG_LEVEL_W, "mount remote failed, so boot is from board!!!\n");
	}

	if (!gKTVConfig.IsConfigFileValid())
	{//本地没有经过认证的配置,认定为首次启动,直接进入设置页面
		LOGMSG(DBG_LEVEL_I, "configure file not verified,show modify page\n");
		gPageManager->SetCurrentPage(Page_SettingModify);
	}
	else
	{//本地有经过认证的配置,平时正常情况走这边
		LOGMSG(DBG_LEVEL_I, "configure file verified,set ip and show hdmi page\n");
		CSimpleStringA sInterfaceName;
		GetAvailbalEthNetworkInterface(&sInterfaceName);

		SetIPInfo(sInterfaceName.GetString(),
			gKTVConfig.GetStbIP(),
			gKTVConfig.GetNetMask(),
			gKTVConfig.GetNetGate());

#ifndef PC_VERSION
// PC 机器，请不要设置 DNS，否则可能导致无法上网
			SetDNS(gKTVConfig.GetDNS0());
			SetDNS(gKTVConfig.GetDNS1());
#endif

			gPageManager->SetCurrentPage(Page_Hdmi);
	}
}

void DeInitUI()
{
	LOGMSG(DBG_LEVEL_W, "Stop...\n");

	// force sync to make database stability
	do_syscmd(NULL, "sync");

	theBaseApp->Exit();
	theBaseApp->FreeResource();

	gInitUIComplete = FALSE;
}

void NativeMainLoop()
{
	LOGMSG(DBG_LEVEL_I, "function %s enter\n", __PRETTY_FUNCTION__);

	InitUI();

	MESSAGE msg;
	while (theBaseApp->GetMsg(&msg))
	{
		LOGMSG(DBG_LEVEL_D, "get window message, pOwner=0x%08x, type=%u, wparam=%llu, lparam=%llu\n",
			msg.pOwner, msg.uType, msg.wParam, msg.lParam);

		//Process Msg
		theBaseApp->DispatchMsg(&msg);

		LOGMSG(DBG_LEVEL_D, "window message Process End, pOwner=0x%08x, type=%u, wparam=%llu, lparam=%llu\n",
			msg.pOwner, msg.uType, msg.wParam, msg.lParam);
	}

	DeInitUI();
	gMainLoopExit = TRUE;

	LOGMSG(DBG_LEVEL_I, "function %s leave\n", __PRETTY_FUNCTION__);
}

class CMainLoopThread : public CBaseThread,
	public IThreadFuncInterface
{
public:
	CMainLoopThread(){}
	~CMainLoopThread(){}

public:
	virtual BOOL ThreadLoop(
		UINT64 uThreadData)
	{
		NativeMainLoop();
		return FALSE;
	}
};
CMainLoopThread gMainLoopThread;


void NativeStart(
	int nDispWidth,
	int nDispHeight)
{
	LOGMSG(DBG_LEVEL_I, "function %s ...\n", __PRETTY_FUNCTION__);
	gKTVConfig.SetDisplaySize(nDispWidth, nDispHeight);

	PrintMachineInfo();

	InitDynamicLibs();

	SetSocketMatchCode(FALSE);

	InitGlobalClass();
	InitBaseApp();

	char cFontFileName[MAX_PATH];
	sprintf(cFontFileName, "%s/%s/%s",
		gKTVConfig.GetProgramFolder(),
		FONTS_FOLDER,
		gKTVConfig.GetFontName());
	theBaseApp->SetFontFile(cFontFileName);

	gMainLoopExit = FALSE;

	// 必须先初始化 bcm driver，否则 opengl 无法创建
	gPlayerCtrl->Start();
	gMultiMediaCtrl->Start();
	gHttpCmdClient->Start(gKTVConfig.GetServerIP(), gKTVConfig.GetServerPort());
	gHttpCmdServer->Create(HTTPCMD_SOCKETPORT, FALSE, "HttpCmd_ServerSocket");

	theBaseApp->InitE3D(nDispWidth, nDispHeight, LAYOUT_WIDTH, LAYOUT_HEIGHT);

	gMainLoopThread.StartThread(
		"MainLoopThread",
		&gMainLoopThread,
		0,
		STACKSIZE_HEAVY);
}

void NativeOnStep()
{
	UINT64 uTime1 = GetTickCountUS();

	theBaseApp->GetE3DEngine()->Refresh();

	UINT64 uTime2 = GetTickCountUS();

	UINT64 uProcessTime = 0;
	if ((uTime2-uTime1) < 16666)
	{
		uProcessTime = 16666-(uTime2-uTime1);
	}
	theBaseApp->GetE3DEngine()->ProcessCommands(uProcessTime);
}

void NativeStop()
{
	theBaseApp->GetE3DEngine()->ProcessCommands(0);
	NativeOnStep();

	gMainLoopThread.StopThread();

	do_syscmd(NULL, "sync");

	gHttpCmdServer->Close();
	gPlayerCtrl->Stop();
	gMultiMediaCtrl->Stop();

	// 一定要在 DeInitE3DEngine之前调用，
	// 否则E3D结束后，不会处理其他E3D控件销毁
	DeInitGlobalClass();
	DeInitBaseApp();
}

int main()
{
	LOGMSG(DBG_LEVEL_I, "function %s ...\n", __PRETTY_FUNCTION__);

	setlocale(LC_CTYPE, "zh_CN.UTF-8");

	RegisterSigHandler();

	char cProgramFolder[MAX_PATH];
	char cConfigFileName[MAX_PATH];
	GetProgramPath(cProgramFolder, MAX_PATH);

#ifdef PC_VERSION
    // PC运行的程序，需要准备一个STBCfg.xml在程序的上层目录
	GetFileParentDir(cProgramFolder, cProgramFolder);
	CombinePathName(cConfigFileName, cProgramFolder, "STBCfg.xml");
#else
	// 板上运行的程序,STBCfg的位置必须定死
    strcpy(cConfigFileName, "/stb/config/app/STBCfg.xml");
#endif

	LOGMSG(DBG_LEVEL_I, "cProgramFolder=%s, cConfigFileName=%s\n", cProgramFolder, cConfigFileName);
	gKTVConfig.LoadConfig(cConfigFileName);

	{
		NativeStart(
			gKTVConfig.GetDisplayWidth(),
			gKTVConfig.GetDisplayHeight());

		while (!gMainLoopExit)
		{
			NativeOnStep();
		}

		NativeStop();
	}

	UnregisterSigHandler();

	LOGMSG(DBG_LEVEL_I, "Main Function return...\n");

#if defined(PC_VERSION)
	// 台式机必须要正常释放资源
	return 0;
#else
	// 机顶盒上，为了加快关机速度，不释放资源了；资源释放有时候需要 10s 左右
	_exit(0);
#endif
}
