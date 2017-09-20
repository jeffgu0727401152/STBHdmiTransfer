#pragma once

#include "MsgQueue.h"
#include "TimerEngine.h"
#include "BaseWnd.h"
#include "PopupWndManager.h"
#include "InputManager.h"
#include "UIResource.h"

typedef enum eSYSTEM_TEXTURE
{
	SYSTEM_TEXTURE_MOUSECURSOR,
	SYSTEM_TEXTURE_EDITCURSOR,
	SYSTEM_TEXTURE_COUNT
} SYSTEM_TEXTURE;

typedef struct tagOVERLAYTEXTINFO
{
	char cTag[32];
	CPictureBox sPictureBox;

	BOOL bNeedDelete;
	BOOL bNeedUpdateText;
	wchar_t wszText[4096];
	UINT32 uFontColor;
	int nFontSize;
	int nFontDirect;
	RECT rcOverlay;
} OVERLAYTEXTINFO;

class CBaseEdit;
class CE3DCommand;
class CBaseApp : public IE3DRefreshListener
{
public:
	CBaseApp();
	virtual ~CBaseApp();

	// interface
public:
	virtual void OnRefresh();

public:
	CE3DCommand* GetE3DEngine();
	void InitE3D(
		int nWidth,
		int nHeight,
		int nUIWidth,
		int nUIHeight);

	void Run();
	void Exit();
	void Pause();
	void Resume();

public:
	void SetCalibrationParam(
		int nCalParam[7]);
	void SetInputType(
		INPUTTYPE type);
	INPUTTYPE GetInputType();
	void SetDeviceEventName(
		const char* cDevEventName);
	void SetMonkeyParam(
		UINT64 uInterval);
	void StartInput();
	void StopInput();
	void PauseInput();
	void ResumeInput();
	UINT64 GetLastInputEventTime();
	void InsertTouchInput(
		DEVICETYPE eDeviceType,
		BOOL bPressed,
		int xPos,
		int yPos);
	void InsertKeyInput(
		BOOL bPressed,
		int nKeyValue);

	// 实时刷新
public:
	void ForceShowCursor(
		BOOL bForceShow);
	void EnableDrawCursor(
		BOOL bEnableCursor);
	void ShowCursorFocus(
		BOOL bShowCursorFocus);
	void SetCursorPos(
		int xPos,
		int yPos);
	void UpdateCursor();

	void EnableFPS(
		BOOL bEnableFPS);
	void UpdateFPS();

	void EnableMask(
		BOOL bEnableMask);
	void UpdateMask();

	void ResetLimitStartTime();
	void SetLimitTime(
		UINT64 uSeconds);
	BOOL IsLimitTimeOver();
	void SetLimitPromptText(
		const char* cPromptText);
	void UpdateLimit();

	void AddOverlayText(
		const char* cTag,
		const char* cText,
		UINT32 uFontColor,
		int nFontSize,
		int nFontDirect,
		RECT rcOverlay);
	void AddOverlayText(
		const char* cTag,
		const wchar_t* wszText,
		UINT32 uFontColor,
		int nFontSize,
		int nFontDirect,
		RECT rcOverlay);
	void DelOverlayText(
		const char* cTag);
	void UpdateOverlay();

	void EnableDrawFocus(
		BOOL bEnableDrawFocus);
	void SetFocusParam(
		UINT32 uFocusColor,
		UINT32 uFocusBkColor,
		int uFocusBorder);
	void DrawFocusRect(
		RECT rcRect);
	void UpdateFocus();

public:
	// message
	void PostQuitMsg();

	void PostMsg(
		IMessageOwner *pOwner,
		UINT32 uType,
		UINT64 wParam,
		UINT64 lParam);

	void SendMsg(
		IMessageOwner *pOwner,
		UINT32 uType,
		UINT64 wParam,
		UINT64 lParam);

	void RegisterBroadcastMsg(
		IMessageOwner *pOwner,
		UINT32 uType);
	void UnRegisterBroadcastMsg(
		IMessageOwner *pOwner,
		UINT32 uType);

	void AddBroadcastMsg(
		UINT32 uType,
		UINT64 wParam,
		UINT64 lParam,
		BOOL bOverlap,
		IMessageOwner *pExcludeOwner = NULL);
	void RemoveBroadcastMsg(
		UINT32 uType);

	BOOL GetMsg(
		MESSAGE *pMsg);

	BOOL PeekMsg(
		IMessageOwner *pOwner,
		UINT32 uTypeMin,
		UINT32 uTypeMax,
		UINT32 uFlag,
		MESSAGE *pMsg);

	BOOL HasMsg(
		IMessageOwner *pOwner,
		UINT32 uTypeMin,
		UINT32 uTypeMax);

	void RemoveMsg(
		IMessageOwner *pOwner,
		UINT32 uTypeMin,
		UINT32 uTypeMax);
	void RemoveMsg(
		IMessageOwner *pOwner,
		UINT32 uTypeMin,
		UINT32 uTypeMax,
		UINT64 wParam,
		UINT64 lParam);

	void DispatchMsg(
		MESSAGE *pMsg);

	UINT64 GetMsgDispatchStartTime();

	// timer
	void AddTimer(
		IMessageOwner *pOwner,
		int nTimer, 
		UINT64 uDelayTime);
	void DelTimer(
		IMessageOwner *pOwner,
		int nTimer);
	void ResetTimer(
		IMessageOwner *pOwner,
		int nTimerID);
	void RemoveAllTimerByOwner(
		IMessageOwner *pOwner);

	// window
	CBaseWnd *GetMainWindow();
	void UpdatePopupZorder(
		BOOL bVisibleOnly);
	void UpdateEmbeddedZorder();

	BOOL IsValidWindow(
		CBaseWnd *pWnd);

	void SetCaptureWnd(
		CBaseWnd *pWnd);
	void ReleaseCapture();

	void SetFocusWnd(
		CBaseWnd *pWnd,
		BOOL bFocusChild=TRUE);
	CBaseWnd* GetFocusWnd();

	void BringToTop(
		CBaseWnd *pWnd);

	BOOL HasWndOverlapMe(
		CBaseWnd *pWnd,
		BOOL bPopupWndOnly);

	void AddPopupWnd(
		CBaseWnd *pPopupWnd,
		int nIndex=-1);
	void DelPopupWnd(
		CBaseWnd *pPopupWnd);

	const char* GetLanguage(
		LANGUAGEID id);
	void ChangeLanguage();

	BOOL LoadResource(
		const char *cResourceFolder,
		LANGUAGEID id,
		const BYTE* pResKey,
		int nKeyLength);
	void FreeResource();
	void LoadStringRes();
	void InitSystemRes();
	void LoadSystemRes();
	void LoadLimitRes();
	UIRESITEM* GetResourceItem(
		const char *cItemName);
	BOOL GetResourceImageBuffer(
		const char *cTextureName,
		CImageBuffer *pImageBuffer);
	BOOL GetResourceRawBuffer(
		const char *cRawName,
		CBuffer *pRawBuffer,
		BOOL bCopyNew);
	void GetResourceBtnImageBuffers(
		const char *cTextureNameBase,
		CImageBuffer pImageBuffers[2]);
	BOOL GetResourceTexture(
		const char *cTextureName,
		CTexture *pTexture);
	void GetResourceBtnTexture(
		const char *cTextureNameBase,
		CTexture pTextures[2]);

	void GetSystemTexture(
		SYSTEM_TEXTURE eType,
		CTexture *pTexture);

	const char* GetStringByID(
		const char* cStringID,
		const char* cDefValue="");

	void SetFontFile(
		const char* cFontFile);
	CFontLib* GetFontLib();

private:
	int ProcessTouchMsg(
		UINT32 uType,
		UINT64 wParam,
		UINT64 lParam);

	int ProcessKeyMsg(
		UINT32 uType,
		UINT64 wParam,
		UINT64 lParam);

private:
	CE3DCommand mE3DEngine;

	CBaseWnd    mMainWindow;
	CBaseWnd*   mpLastTouchWnd;
	CBaseWnd*   mpCaptureWnd;
	CBaseWnd*   mpFocusWnd;

	CPopupWndManager mPopupWndManager;

	UINT64 mMsgDispatchStartTime;
	UINT64 mMsgDispatchTotalTime;
	UINT64 mMsgDispatchCount;
	CMsgQueue mMsgQueue;
	CTimerEngine mTimerEngine;
	CInputManager mInputManager;

	BOOL mEnableDrawFocus;
	UINT32 mFocusColor;
	UINT32 mFocusBkColor;
	int mFocusBorder;
	UINT32* mpColorBuffer;
	RECT mFocusRect;
	CPictureBox mFocusPictureBox;

	BOOL mForceShowCursor;
	BOOL mEnableCursor;
	BOOL mShowCursorFocus;
	int mCursorXpos;
	int mCursorYpos;
	CPictureBox mCursorPictureBox;
	CPictureBox mCursorFocusPictureBox;

	BOOL mEnableFPS;
	int mFrameCount;
	CPictureBox mFPSPictureBox;
	UINT64 mLastUpdateTime;

	BOOL mEnableMask;
	CPictureBox mMaskPictureBox;

	BOOL mLimitShown;
	UINT64 	mLimitStartTime;
	UINT64 mLimitTime;
	CPictureBox mLimitPictureBox;

	// list of OVERLAYTEXTINFO
	CPtrListCtrl mOverlayTextInfoList;
	CBaseLock mOverlayTextInfoListLock;

	CUIResource mResource;
	XMLParser mStringParser;
	XMLNode mStringNode;

	// 系统资源
	CTexture mSystemTexture[SYSTEM_TEXTURE_COUNT];
	CFontLib mFontLib;
};

extern CBaseApp *theBaseApp;
void InitBaseApp();
void DeInitBaseApp();
