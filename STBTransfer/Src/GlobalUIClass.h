#pragma once

#include "UserMsgDefine.h"
#include "KTVConfig.h"
#include "Version.h"
#include "./PageManager/PageManager.h"
#include "./PlayerCtrl/PlayerCtrl.h"
#include "./HttpCmd/HttpCmdClient.h"
#include "./HttpCmd/HttpCmdServer.h"
#include "./InputMethodWnd/HandWriteOperator.h"

extern CPageManager* gPageManager;
extern CPlayerCtrl* gPlayerCtrl;
extern CMultiMediaCtrl* gMultiMediaCtrl;
extern CHttpCmdClient* gHttpCmdClient;
extern CHttpCmdServer* gHttpCmdServer;
extern CHandWriteOperator* gHandWriteOperator;

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
