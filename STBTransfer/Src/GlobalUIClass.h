#pragma once

#include "UserMsgDefine.h"
#include "KTVConfig.h"
#include "Version.h"
#include "./PageManager/PageManager.h"
#include "./PlayerCtrl/PlayerCtrl.h"
#include "./PlayerCtrl/PlayerManager.h"
#include "./HttpCmd/HttpCmdClient.h"
#include "./HttpCmd/HttpCmdServer.h"
#include "./InputMethodWnd/HandWriteOperator.h"

extern CPageManager* gPageManager;
extern CPlayerCtrl* gPlayerCtrl;
extern CPlayerManager* gPlayerManager;
extern CMultiMediaCtrl* gMultiMediaCtrl;
extern CHttpCmdClient* gHttpCmdClient;
extern CHttpCmdServer* gHttpCmdServer;
extern CHandWriteOperator* gHandWriteOperator;

typedef enum eBOOT_MODE
{
	Mode_Network=0,				// 网络启动
	Mode_Local,					// 本机启动
	Mode_Factory,				// 厂测启动
	Mode_Count
} BOOT_MODE;

extern BOOT_MODE gProgramBootMode;

void InitGlobalClass();
void DeInitGlobalClass();

void InitDynamicLibs();
void DeinitDynamicLibs();

extern UINT64 gRefreshDelayTime;
void SetE3DBusy(
	BOOL bBusy);
void UpdateRefreshDelayTime(
	UINT64 uRefreshUsedTime,
	UINT64 uCurTickCountUS);
