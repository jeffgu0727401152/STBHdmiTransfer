#pragma once

#include "commfunc.h"
#include "SimpleString.h"
#include "DbgOutput.h"
#include "XMLParser.h"
#include "MsgQueue.h"
#include "TimerEngine.h"
#include "define.h"
#include "PictureBox.h"
#include "E3DCommand.h"
#include "ImageBuffer.h"

#define LOAD_RES_WHEN_NEED

class CBaseWnd;

typedef enum eLANGUAGEID
{
	LanguageID_CHS=0,
	LanguageID_CHT,
	LanguageID_ENG,
	LanguageID_JAP,
	LanguageID_KOR,
	LanguageID_MM,
	LanguageID_Count
} LANGUAGEID;

// return FALSE to stop Enum windows
typedef BOOL (*ENUMCHILDWNDFUNC)(
	CBaseWnd *pChildWnd, 
	UINT64 uUserData);

class IMsgRecvWndInterface
{
public:
	IMsgRecvWndInterface();
	virtual ~IMsgRecvWndInterface(void) {}

public:
	virtual void SetMsgRecvWnd(
		CBaseWnd *pRecvWnd);

	void ReportPostMsg(
		UINT32 uType,
		UINT64 wParam,
		UINT64 lParam);

	void ReportSendMsg(
		UINT32 uType,
		UINT64 wParam,
		UINT64 lParam);

private:
	CBaseWnd* mpMsgRecvWnd;
};

class ICustomFocusListener
{
public:
	virtual ~ICustomFocusListener(void) {}

	// return TRUE if want to prevent other process
	virtual BOOL OnCustomDrawFocus()=0;
	virtual void OnCustomClearFocus()=0;
};

class ITouchEventListener
{
public:
	virtual ~ITouchEventListener(void) {}

	virtual void OnTouchDown(
		CBaseWnd *pWnd,
		POINT ptWnd)
	{}

	virtual void OnTouchMove(
		CBaseWnd *pWnd,
		POINT ptWnd)
	{}

	virtual void OnTouchUp(
		CBaseWnd *pWnd,
		POINT ptWnd,
		int xDistance,
		int yDistance,
		UINT64 uUsedTime)
	{}

	virtual void OnTouchLeave(
		CBaseWnd *pOldTouchWnd,
		CBaseWnd *pNewTouchWnd)
	{}
};

class IKeyEventListener
{
public:
	virtual ~IKeyEventListener(void) {}

	// return TRUE if want to prevent other process
	virtual BOOL OnKeyEvent(
		BOOL bPressed,
		int nKeyValue)=0;
};

class IClickEventListener
{
public:
	virtual ~IClickEventListener(void) {}

	virtual void OnClick(
		CBaseWnd *pWnd,
		POINT ptWnd)=0;
};

class CE3DCommand;
class CBaseWnd :
	public IMessageOwner
{
public:
	CBaseWnd();
	virtual ~CBaseWnd();

	// window properties
public:
	virtual void Create(
		CE3DCommand *pE3DEngine,
		const char *cClassName,
		CBaseWnd *pParent,
		UINT32 uFlag=WINDOWFLAG_DEFAULT,
		UINT32 uState=WINDOWSTATE_DEFAULT);
	virtual void CreateStatic(
		CE3DCommand *pE3DEngine,
		CBaseWnd *pParent,
		UINT32 uFlag=WINDOWFLAG_DEFAULT,
		UINT32 uState=WINDOWSTATE_DEFAULT);
	virtual void OnCreate();
	CE3DCommand* GetE3DEngine();

	void LoadResource();

	virtual void OnLoadResource();
	virtual void OnChildLoadResourceComplete();
	virtual void ParserXMLNode(
		XMLNode *pNode);
	virtual void ParserChildNode(
		XMLNode *pParentNode,
		const char *cChildNodeName);

public:
	// flag
	char* GetClassName();
	UINT32 GetWndState();
	UINT32 GetWndFlag();
	BOOL  IsWindow();
	BOOL  IsPopupWindow();

	// position
	void GetWndRect(
		RECT *prc);
	void GetScreenRect(
		RECT *prc);
	void GetWndRelativeToParentRect(
		RECT *prc);
	void MoveWindow(
		RECT *prcRelativeToParent,
		BOOL bRecreateFont=TRUE);
	virtual void OnWindowSizeChange(
		RECT rcOldRelative,
		RECT rcNewRelative);

	virtual void SetWindowTextA(
		const char *cText);
	virtual void SetWindowTextW(
		const wchar_t *wszText);
	virtual const wchar_t* GetWindowTextW();
	virtual void OnWindowTextChange(
		const wchar_t *wszOldText,
		const wchar_t *wszNewText);

	virtual void SetFontRect(
		RECT *prcFontRect);
	virtual void SetFontSize(
		int nFontSize);
	virtual void SetFontAutoMultiline(
		BOOL bAutoMultiline);
	virtual void SetFontNeedDotIfOutofBound(
		BOOL bNeedDotIfOutofBound);
	virtual void SetFontDirect(
		int nFontDirect);
	virtual void SetFontSpace(
		int nFontXSpace,
		int nFontYSpace);
	virtual void SetFontColor(
		UINT32 uARGB);
	virtual void GetFontRect(
		RECT *prcRect);
	virtual int GetFontSize();
	virtual BOOL GetFontAutoMultiline();
	virtual BOOL GetFontNeedDotIfOutofBound();
	virtual int GetFontDirect();
	virtual int GetFontXSpace();
	virtual int GetFontYSpace();
	virtual UINT32 GetFontColor();
	virtual void GetFontTexture(
		CTexture *pFontTexture);
	virtual float GetFontZorder();

	virtual void SetWindowData(
		UINT64 uData);
	UINT64 GetWindowData();

	virtual void EnableWindow(
		BOOL bEnable);
	BOOL IsWindowEnable();
	virtual void OnWindowEnable(
		BOOL bEnable);

	virtual void SetWindowVisible(
		BOOL bVisible);
	BOOL IsWindowVisible();
	virtual void OnWindowVisible(
		BOOL bVisible);

	virtual void OnWindowFocus(
		BOOL bFocus);
	void DrawFocus();
	void ClearFocus();
	void SetWindowCanFocus(
		BOOL bCanFocus);
	BOOL IsWindowCanFocus();
	// 注意：
	// SetWindowCanFocus 设置为 NOFOCUS后，
	// 会被子窗口设置 OnTouch/OnClick/OnKey 事件重置为 CANFOCUS；
	// 所以，最好是在父子窗口都设置好监听事件后，再从子窗口到父窗口顺序，设置 CANFOCUS

	// 只有popup window会被调用
	virtual void OnWindowActivate(
		BOOL bActivate);

	virtual void SetWindowNeedClip(
		BOOL bNeedClip);
	BOOL IsWindowNeedClip();

	void RePositionWindow();

	void SetBkgroundRect(
		RECT *prcRect);
	void GetBkgroundRect(
		RECT *prcRect);
	virtual void SetBkgroundTexture(
		CTexture *pTexture);
	// when update texture, must set prcUpdate, otherwise, it will use new texture
	virtual void SetBkgroundImageBuffer(
		CImageBuffer *pImageBuffer,
		RECT  *prcUpdate);
	void GetBkgroundTexture(
		CTexture *pTexture);
	float GetBkgroundZorder();
	void SetBkgroundAlphaColor(
		UINT32 uColor);
	UINT32 GetBkgroundAlphaColor();
	void SetBkgroundAngle(
		int nAngle);
	int GetBkgroundAngle();

	// return FALSE to stop Enum windows
	BOOL EnumChildWindows(
		BOOL bParentToChildOrder,
		BOOL bEmbeddedOnly,
		BOOL bVisibleOnly,
		ENUMCHILDWNDFUNC pfn,
		UINT64 uUserData);

	void GetChildWindowsCount(
		BOOL bIncludeInvisible,
		BOOL bParentPopup,
		int *pnPopupWndCount,
		int *pnEmbeddedWndCount);

protected:
	virtual BOOL WantFocus();

private:
	void RecreateFont();

	void RefreshWindowEnable(
		BOOL bParentEnable);
	BOOL RefreshChildEnable(
		BOOL bParentEnable);

	void RefreshWindowVisible(
		BOOL bParentVisible);
	BOOL RefreshChildVisible(
		BOOL bParentVisible);

private:
	CE3DCommand *mE3DEngine;

public:
	RECT  mWndRect;
	RECT  mRectRelativeToParent;

protected:
	char  mClassName[CLASSNAME_MAXLEN];
	BOOL  mWndCreated;
	UINT32 mWndFlag;
	UINT32 mWndState;
	UINT64 mWndData;

	BOOL mWindowEnable;
	BOOL mWindowVisible;

	CPictureBox mBkgroundPictureBox;
	RECT mBkgroundRect;

	CPictureBox mTextPictureBox;
	CSimpleStringW mWndTextString;
	RECT mFontRect;
	int mFontSize;
	int mFontDirect;
	int mFontXSpace;
	int mFontYSpace;
	UINT32 mFontColor;
	BOOL mAutoMultiline;
	BOOL mNeedDotIfOutofBound;
	POINT mFontStartTopPos;
	POINT mFontStartBottomPos;
	POINT mFontEndTopPos;
	POINT mFontEndBottomPos;

public:
	void PostMsg(
		UINT32 uType,
		UINT64 wParam,
		UINT64 lParam);
	void SendMsg(
		UINT32 uType,
		UINT64 wParam,
		UINT64 lParam);

	void RegisterBroadcastMsg(
		UINT32 uType);
	void UnRegisterBroadcastMsg(
		UINT32 uType);

	BOOL PeekMsg(
		UINT32 nTypeMin,
		UINT32 nTypeMax,
		UINT32 uFlag,
		MESSAGE *pMsg);

	void RemoveMsg(
		UINT32 uTypeMin,
		UINT32 uTypeMax,
		UINT64 wParam=0,
		UINT64 lParam=0,
		UINT32 uRemoveFlag=MSG_REMOVE_FLAG_CMP_NONE);

	BOOL HasMsg(
		UINT32 uTypeMin,
		UINT32 uTypeMax);

	// timer
	void AddTimer(
		int nTimerID,
		UINT64 uDelayTime);
	void DelTimer(
		int nTimerID);
	void ResetTimer(
		int nTimerID);
	void RemoveAllTimer();

public:
	void ProcessTouchDownMsg(
		POINT ptScreen);
	void ProcessTouchUpMsg(
		POINT ptScreen);
	void ProcessTouchMoveMsg(
		POINT ptScreen);
	void ProcessTouchLeaveMsg(
		CBaseWnd *pNewTouchWnd);

	// return TRUE: indicate this key was process by window
	// return FALSE: indicate this key is not handled
	BOOL ProcessKeyMsg(
		BOOL bPressed,
		int nKeyValue);

	void ProcessDestroyMsg();
	virtual void OnDestroy();

	int ProcessTimerMsg(
		UINT64 wParam,
		UINT64 lParam);

public:
	void SetCustomFocusListener(
		ICustomFocusListener *pCustomFocusListener);
	void SetOnTouchListener(
		ITouchEventListener *pOnTouchListener);
	void SetOnClickListener(
		IClickEventListener *pOnClickListener,
		UINT64 uClickDelayTime=100);
	void SetOnKeyListener(
		IKeyEventListener *pOnKeyListener);

protected:
	virtual void OnSubclassTouchDown(
		CBaseWnd *pWnd,
		POINT ptWnd);
	virtual void OnSubclassTouchUp(
		CBaseWnd *pWnd,
		POINT ptWnd,
		int xDistance,
		int yDistance,
		UINT64 uUsedTime);
	virtual void OnSubclassTouchMove(
		CBaseWnd *pWnd,
		POINT ptWnd);
	virtual void OnSubclassTouchLeave(
		CBaseWnd *pOldTouchWnd,
		CBaseWnd *pNewTouchWnd);

	virtual void OnSubclassClick(
		CBaseWnd *pWnd,
		POINT ptWnd);

private:
	ICustomFocusListener *mpCustomFocusListener;
	ITouchEventListener *mpOnTouchListener;
	IClickEventListener *mpOnClickListener;
	IKeyEventListener *mpOnKeyListener;
	UINT64 mLastClickTime;
	UINT64 mClickDelayTime;

protected:
	UINT64 mPressedTime;
	BOOL  mWndPressed;
	POINT mPressedScreenPoint;
	POINT mLastDragScreenPoint;

public:
	virtual BOOL CanDispatchMsg();

	virtual void OnMsg(
		UINT32 uType,
		UINT64 wParam,
		UINT64 lParam);

	virtual void OnUpdateZorder();
	virtual void OnRedraw();
	virtual void OnRedrawBkground();
	virtual void OnRedrawText();

	virtual void OnTimer(
		int nTimerID);

	// child windows
public:
	BOOL IsPointOnMe(
		POINT ptScreen);
	CBaseWnd* FindWndByPoint(
		POINT ptScreen,
		float fMinZorder,
		float fMaxZorder);
	CBaseWnd* FindWndByRect(
		RECT rcScreen,
		float fMinZorder,
		float fMaxZorder);
	CBaseWnd *GetChildWnd(
		int nIndex);
	CBaseWnd* FindFirstCanFocusWnd();
	CBaseWnd* FindFirstWantFocusPopupWnd();
	CBaseWnd* FindFirstCanFocusPopupWnd();
	CBaseWnd* FindFirstWantFocusEmbeddedWnd();
	CBaseWnd* FindFirstCanFocusEmbeddedWnd();
	BOOL IsMyParent(
		CBaseWnd* pWnd);
	CBaseWnd* GetParentWnd();
	CBaseWnd* GetPopupParentWnd();
	CBaseWnd* GetBestFocusBrotherWnd(
		CBaseWnd* pTobeFindBrotherWnd,
		RECT rcFocus,
		int nDirection);
	CBaseWnd* FindBestFocusWndByDirection(
		CBaseWnd* pWnd,
		RECT rcFocus,
		int nDirection,//nDirection: 0-left, 1-up, 2-right, 3-down
		int *pnWeight);
	BOOL IsBetterFocusWndByDirection(
		RECT rcFocus,
		int nDirection,
		int *pnWeight);
	void ConvertWndPointToScreenPoint(
		POINT *ptScreen, 
		POINT ptWnd);
	void ConvertWndRectToScreenRect(
		RECT *prcScreen,
		RECT rcWnd);
	void ConvertScreenPointToWndPoint(
		POINT *ptWnd, 
		POINT ptScreen);
	void ConvertScreenRectToWndRect(
		RECT *prcWnd,
		RECT rcScreen);

	void UpdateChildZorder(
		float *pfZorder,
		float fZorderDelta);
	float GetZorder();
	void GetUserZorder(
		float *pZorderStart,
		float *pZorderEnd);

private:
	void AddChild(
		CBaseWnd* pChild);
	void DelChild(
		CBaseWnd* pChild);

private:
	CBaseWnd *mpParentWnd;
	// tail window will be show at top
	CPtrListCtrl mChildWndList;
	CBaseLock	 mChildWndListLock;
	int			 mLastGetChildIndex;
	float    	 mZorderNumber;
	float		 mZorderDelta;
};

BOOL XmlLoadImageBuffer(
	XMLNode *pNode,
	const char *elementName,
	CImageBuffer *pImageBuffer);
BOOL XmlLoadRawBuffer(
	XMLNode *pNode,
	const char *elementName,
	CBuffer *pRawBuffer,
	BOOL bCopyNew);
BOOL XmlLoadBtnImageBuffers(
	XMLNode *pNode,
	const char *elementName,
	CImageBuffer pImageBuffer[2]);
BOOL XmlLoadTexture(
	XMLNode *pNode,
	const char *elementName,
	CTexture *pTexture);
BOOL XmlLoadBtnTextures(
	XMLNode *pNode,
	const char *elementName,
	CTexture pTextures[2]);
const char* XmlLoadString(
	const char* cStringID);
