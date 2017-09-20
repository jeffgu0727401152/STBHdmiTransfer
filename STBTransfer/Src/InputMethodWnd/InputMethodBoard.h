#pragma once

#include "PopupSlideWnd.h"
#include "BaseComboBox.h"
#include "BaseButton.h"
#include "BaseEdit.h"
#include "LineWnd.h"
#include "BaseWnd.h"
#include "stroke.h"
#include "pinyin.h"

typedef enum eIMETYPE
{
	IMETYPE_LETTER=0,
	IMETYPE_STROKE,
	IMETYPE_HANDWRITE,
	IMETYPE_SYMBOL,
	IMETYPE_CHINESE,
	IMETYPE_SPEECH
} IMETYPE;

#define CANDICATE_COUNT		5

#define LETTER_COUNT		26
#define DIGIT_COUNT			12
#define SYMBOL_COUNT		32

void SwitchHWToTraditional(
	BOOL bTraditional);

class CLetterDigitInputWnd : public CBaseWnd,
	public IClickEventListener,
	public IMsgRecvWndInterface
{
	typedef CBaseWnd CParentClass;

public:
	CLetterDigitInputWnd();
	virtual ~CLetterDigitInputWnd();

public:
	virtual void Create(
		CE3DCommand *pE3DEngine,
		CBaseWnd *pParent);

	virtual void ParserXMLNode(
		XMLNode *pNode);

	// interface
public:
	virtual void OnClick(
		CBaseWnd *pWnd,
		POINT ptWnd);

private:
	void SwitchShift();

private:
	CBaseButton mLetterItemBtn[LETTER_COUNT];
	CBaseButton mDigitItemBtn[DIGIT_COUNT];
	CBaseButton mShiftBtn;

	CTexture mLetterUpperTextures[LETTER_COUNT][2];
	CTexture mLetterLowerTextures[LETTER_COUNT][2];
};

class CStrokeInputWnd : public CBaseWnd,
	public IClickEventListener,
	public IMsgRecvWndInterface
{
	typedef CBaseWnd CParentClass;

public:
	CStrokeInputWnd();
	virtual ~CStrokeInputWnd();

public:
	virtual void Create(
		CE3DCommand *pE3DEngine,
		CBaseWnd *pParent);

	virtual void ParserXMLNode(
		XMLNode *pNode);

	// interface
public:
	virtual void OnClick(
		CBaseWnd *pWnd,
		POINT ptWnd);

private:
	CBaseButton mStroketemBtn[STROKE_CHAR_COUNT];
};

class CHandwriteInputWnd : public CBaseWnd,
	public IClickEventListener,
	public ITouchEventListener,
	public IMsgRecvWndInterface
{
	typedef CBaseWnd CParentClass;

public:
	CHandwriteInputWnd();
	virtual ~CHandwriteInputWnd();

public:
	virtual void Create(
		CE3DCommand *pE3DEngine,
		CBaseWnd *pParent);

	virtual void ParserXMLNode(
		XMLNode *pNode);

	virtual void OnWindowVisible(
		BOOL bVisible);

	virtual void OnTimer(
		int nTimerID);

	// interface
public:
	virtual void OnClick(
		CBaseWnd *pWnd,
		POINT ptWnd);

	virtual void OnTouchDown(
		CBaseWnd *pWnd,
		POINT ptWnd);
	virtual void OnTouchMove(
		CBaseWnd *pWnd,
		POINT ptWnd);
	virtual void OnTouchUp(
		CBaseWnd *pWnd,
		POINT ptWnd,
		int xDistance,
		int yDistance,
		UINT64 uUsedTime);
	virtual void OnTouchLeave(
		CBaseWnd *pOldTouchWnd,
		CBaseWnd *pNewTouchWnd);

public:
	BOOL HasInputLocus();
	void BackLocus();
	void ClearLocus();
	void DeleteInputText();

private:
	void AddPointToLocus(
		POINT pt);

	void DoRecognize();

	void ShowPage(
		int nPageIndex);

private:
	CBaseWnd mCandicateWnd;
	CBaseButton mPrevPageBtn;
	CBaseButton mNextPageBtn;
	CBaseButton mCandicateBtn[CANDICATE_COUNT];
	CLineWnd mLocusWnd;

	int mLocusCount;
	int mLocusIndex;
	short *mpLocusPoint;
	short *mpLocusForRecognize;
	wchar_t mLastSelectChar;

	wchar_t* mwszCandicateText;
	int mTextCount;
	int mCurPage;
	int mPageCount;
};

class CSymbolInputWnd : public CBaseWnd,
	public IClickEventListener,
	public IMsgRecvWndInterface
{
	typedef CBaseWnd CParentClass;

public:
	CSymbolInputWnd();
	virtual ~CSymbolInputWnd();

public:
	virtual void Create(
		CE3DCommand *pE3DEngine,
		CBaseWnd *pParent);

	virtual void ParserXMLNode(
		XMLNode *pNode);

	// interface
public:
	virtual void OnClick(
		CBaseWnd *pWnd,
		POINT ptWnd);

private:
	CBaseButton mSymbolItemBtn[SYMBOL_COUNT];

	CBaseButton mSpaceBtn;
};

class CChineseInputWnd : public CBaseWnd,
	public IClickEventListener,
	public IMsgRecvWndInterface
{
	typedef CBaseWnd CParentClass;

public:
	CChineseInputWnd();
	virtual ~CChineseInputWnd();

public:
	virtual void Create(
		CE3DCommand *pE3DEngine,
		CBaseWnd *pParent);

	virtual void ParserXMLNode(
		XMLNode *pNode);

	// interface
public:
	virtual void OnClick(
		CBaseWnd *pWnd,
		POINT ptWnd);

public:
	BOOL HasInputText();
	void BackInput();
	void ClearInput();

private:
	void RecognizeChinese();

	void ShowPage(
		int nPageIndex);

private:
	CBaseEdit mChineseTextEdit;
	CBaseWnd mCandicateWnd;
	CBaseButton mPrevPageBtn;
	CBaseButton mNextPageBtn;
	CBaseButton mCandicateBtn[CANDICATE_COUNT];
	CBaseButton mLetterItemBtn[LETTER_COUNT];

	wchar_t* mwszCandicateText;
	int mTextCount;
	int mCurPage;
	int mPageCount;
};

class ISpeechRecvListener
{
public:
	virtual ~ISpeechRecvListener(void) {}

public:
	virtual void OnSpeechResult(
		const char* cResultString)=0;

	virtual void OnSpeechState(
		const char* cStateString)=0;

	virtual void OnSpeechEnd()=0;
};

class CSpeechInputWnd : public CBaseWnd,
	public IClickEventListener,
	public IMsgRecvWndInterface,
	public ISpeechRecvListener
{
	typedef CBaseWnd CParentClass;

public:
	CSpeechInputWnd();
	virtual ~CSpeechInputWnd();

public:
	virtual void Create(
		CE3DCommand *pE3DEngine,
		CBaseWnd *pParent);

	virtual void ParserXMLNode(
		XMLNode *pNode);

	virtual void OnWindowVisible(
		BOOL bVisible);

	// interface
public:
	virtual void OnClick(
		CBaseWnd *pWnd,
		POINT ptWnd);

	virtual void OnSpeechResult(
		const char* cResultString);

	virtual void OnSpeechState(
		const char* cStateString);

	virtual void OnSpeechEnd();

private:
	CBaseWnd mSpeechPromptWnd;
	CBaseButton mStartSpeechBtn;
	CBaseWnd mSpeechStateWnd;
};


class CInputMethodBoard : public CBaseWnd,
	public IClickEventListener,
	public IMsgRecvWndInterface,
	public IComboBoxSelectListener
{
	typedef CBaseWnd CParentClass;

public:
	CInputMethodBoard();
	virtual ~CInputMethodBoard();

public:
	virtual void Create(
		CE3DCommand *pE3DEngine,
		CBaseWnd *pParent);

	virtual void OnLoadResource();

	// interface
public:
	virtual void OnMsg(
		UINT32 uType,
		UINT64 wParam,
		UINT64 lParam);

	virtual void OnClick(
		CBaseWnd *pWnd,
		POINT ptWnd);

public:
	void SetShowHideStartPos(
		POINT ptShow,
		POINT ptHide);

	void SetIMEType(
		IMETYPE eType);
	IMETYPE GetIMEType();

	void AddIMEType(
		IMETYPE eType);

	void DelIMEType(
		IMETYPE eType);

private:
	void OnRadioButtonClick(
		CBaseButton *pButton,
		BOOL bNeedSendIMESwitchMsg);

	void RelayoutTypeBtns();

	//void OnDBTypeChanged();

private:
	CBaseButton mPrevTypeBtn;
	CBaseButton mNextTypeBtn;

	CBaseButton mLetterBtn;
	CBaseButton mStrokeBtn;
	CBaseButton mHandwriteBtn;
	CBaseButton mSymbolBtn;
	CBaseButton mChineseBtn;
	CBaseButton mSpeechBtn;
	CRadioButtonGroup mInputBtnGroup;

	CBaseButton mBackBtn;
	CBaseButton mClearBtn;

	CLetterDigitInputWnd mLetterDigitInputWnd;
	CStrokeInputWnd mStrokeInputWnd;
	CHandwriteInputWnd mHandwriteInputWnd;
	CSymbolInputWnd mSymbolInputWnd;
	CChineseInputWnd mChineseInputWnd;
	CSpeechInputWnd mSpeechInputWnd;

	// CBaseButton
	CPtrListCtrl mTypeBtnList;
	int mFirstShowBtnIndex;
	IMETYPE mIMEType;

	RECT mTypeBoundPosition;
	SIZE mTypeBtnSize;
};
