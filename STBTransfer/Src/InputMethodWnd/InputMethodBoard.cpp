#include "InputMethodBoard.h"
#include "HandWriteOperator.h"
#include "AndroidNdkHelp.h"
#include "BaseApp.h"
#include "XMLParser.h"
#include "../GlobalUIClass.h"

const wchar_t gLetterUpperText[LETTER_COUNT+1] = L"ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const wchar_t gLetterLowerText[LETTER_COUNT+1] = L"abcdefghijklmnopqrstuvwxyz";
const wchar_t gDigitText[DIGIT_COUNT+1] = L"0123456789.";
const wchar_t gSymbolText[SYMBOL_COUNT+1] = L".,?!@\"':;+-*/=~()[]{}<>|_\\^`&#%$";


#define RECOGNIZE_TIMERID 			1
#define RECOGNIZE_DELAY_TIME		300


CLetterDigitInputWnd::CLetterDigitInputWnd()
{
}

CLetterDigitInputWnd::~CLetterDigitInputWnd()
{
	LOGMSG(DBG_LEVEL_D, "function %s quit\n", __PRETTY_FUNCTION__);
}

void CLetterDigitInputWnd::Create(
	CE3DCommand *pE3DEngine,
	CBaseWnd *pParent)
{
	CParentClass::Create(pE3DEngine, "LetterDigitInputWnd", pParent);

	for ( int i = 0; i < LETTER_COUNT; i++ )
	{
		mLetterItemBtn[i].Create(pE3DEngine, this);
		mLetterItemBtn[i].SetOnClickListener(this);
	}

	for ( int i = 0; i < DIGIT_COUNT; i++ )
	{
		mDigitItemBtn[i].Create(pE3DEngine, this);
		mDigitItemBtn[i].SetOnClickListener(this);
	}

	mShiftBtn.Create(pE3DEngine, this, BUTTONTYPE_RADIO);
	mShiftBtn.SetOnClickListener(this);
}

void CLetterDigitInputWnd::ParserXMLNode(
	XMLNode *pNode)
{
	CParentClass::ParserXMLNode(pNode);

	CSimpleStringA sTmpString;
	for ( int i = 0; i < LETTER_COUNT; i++ )
	{
		sTmpString.Format("letter_item%d", i);
		XMLNode itemNode;
		pNode->GetChildNode(sTmpString.GetString(), &itemNode);

		mLetterItemBtn[i].ParserXMLNode(&itemNode);
		XmlLoadBtnTextures(&itemNode, "UpperImg", mLetterUpperTextures[i]);
		XmlLoadBtnTextures(&itemNode, "LowerImg", mLetterLowerTextures[i]);
	}

	for ( int i = 0; i < DIGIT_COUNT; i++ )
	{
		sTmpString.Format("digit_item%d", i);
		mDigitItemBtn[i].ParserChildNode(pNode, sTmpString.GetString());
	}

	mShiftBtn.ParserChildNode(pNode, "ShiftBtn");

	mShiftBtn.SetRadioBtnPressed(FALSE);
	SwitchShift();
}

void CLetterDigitInputWnd::OnClick(
	CBaseWnd *pWnd,
	POINT ptWnd)
{
	if (pWnd == &mShiftBtn)
	{
		SwitchShift();
	}
	else
	{
		for ( int i = 0; i < LETTER_COUNT; i++ )
		{
			if (pWnd == &(mLetterItemBtn[i]))
			{
				if (!mShiftBtn.IsRadioBtnPressed())
				{
					ReportPostMsg(
						INPUTWND_WCHARMSG,
						(UINT64)gLetterUpperText[i],
						0);
				}
				else
				{
					ReportPostMsg(
						INPUTWND_WCHARMSG,
						(UINT64)gLetterLowerText[i],
						0);
				}
				return;
			}
		}

		for ( int i = 0; i < DIGIT_COUNT; i++ )
		{
			if (pWnd == &(mDigitItemBtn[i]))
			{
				ReportPostMsg(
					INPUTWND_WCHARMSG,
					(UINT64)gDigitText[i],
					0);
				return;
			}
		}
	}
}

void CLetterDigitInputWnd::SwitchShift()
{
	for ( int i = 0; i < LETTER_COUNT; i++ )
	{
		if (!mShiftBtn.IsRadioBtnPressed())
		{
			if (mLetterUpperTextures[i][0].HasTexture())
			{
				mLetterItemBtn[i].SetBtnTextures(mLetterUpperTextures[i]);
			}
			else
			{
				wchar_t wszTmpText[2];
				wszTmpText[0] = L'A'+i;
				wszTmpText[1] = '\0';
				ToUpperString(wszTmpText);
				mLetterItemBtn[i].SetWindowTextW(wszTmpText);
			}
		}
		else
		{
			if (mLetterLowerTextures[i][0].HasTexture())
			{
				mLetterItemBtn[i].SetBtnTextures(mLetterLowerTextures[i]);
			}
			else
			{
				wchar_t wszTmpText[2];
				wszTmpText[0] = L'A'+i;
				wszTmpText[1] = '\0';
				ToLowerString(wszTmpText);
				mLetterItemBtn[i].SetWindowTextW(wszTmpText);
			}
		}
	}
}



CStrokeInputWnd::CStrokeInputWnd()
{
}

CStrokeInputWnd::~CStrokeInputWnd()
{
	LOGMSG(DBG_LEVEL_D, "function %s quit\n", __PRETTY_FUNCTION__);
}

void CStrokeInputWnd::Create(
	CE3DCommand *pE3DEngine,
	CBaseWnd *pParent)
{
	CParentClass::Create(pE3DEngine, "StrokeInputWnd", pParent);

	for ( int i = 0; i < STROKE_CHAR_COUNT; i++ )
	{
		mStroketemBtn[i].Create(pE3DEngine, this);
		mStroketemBtn[i].SetOnClickListener(this);
	}
}

void CStrokeInputWnd::ParserXMLNode(
	XMLNode *pNode)
{
	CParentClass::ParserXMLNode(pNode);

	CSimpleStringA sTmpString;
	for ( int i = 0; i < STROKE_CHAR_COUNT; i++ )
	{
		sTmpString.Format("item%d", i);
		mStroketemBtn[i].ParserChildNode(pNode, sTmpString.GetString());
	}
}

void CStrokeInputWnd::OnClick(
	CBaseWnd *pWnd,
	POINT ptWnd)
{
	for ( int i = 0; i < STROKE_CHAR_COUNT; i++ )
	{
		if (pWnd == &(mStroketemBtn[i]))
		{
			ReportPostMsg(INPUTWND_WCHARMSG, (UINT64)STROKE_WCHAR[i], 0);
		}
	}
}



CHandwriteInputWnd::CHandwriteInputWnd()
{
	mLocusCount = 0;
	mLocusIndex = 0;
	mpLocusPoint = NULL;
	mpLocusForRecognize = NULL;
	mLastSelectChar = L'\0';

	mwszCandicateText = NULL;
	mTextCount = 0;
	mCurPage = 0;
	mPageCount = 0;
}

CHandwriteInputWnd::~CHandwriteInputWnd()
{
	LOGMSG(DBG_LEVEL_D, "function %s quit\n", __PRETTY_FUNCTION__);

	SAFE_DELETEARRAY(mpLocusPoint);
	SAFE_DELETEARRAY(mpLocusForRecognize);
	SAFE_DELETEARRAY(mwszCandicateText);
}

void CHandwriteInputWnd::Create(
	CE3DCommand *pE3DEngine,
	CBaseWnd *pParent)
{
	CParentClass::Create(pE3DEngine, "HandWriteInputWnd", pParent);

	mLocusWnd.Create(pE3DEngine, this);
	mLocusWnd.SetOnTouchListener(this);

	mCandicateWnd.CreateStatic(pE3DEngine, this);

	mPrevPageBtn.CreateStatic(pE3DEngine, &mCandicateWnd);
	mPrevPageBtn.SetOnClickListener(this);

	mNextPageBtn.CreateStatic(pE3DEngine, &mCandicateWnd);
	mNextPageBtn.SetOnClickListener(this);

	for (int i = 0; i < CANDICATE_COUNT; i++)
	{
		mCandicateBtn[i].Create(pE3DEngine, &mCandicateWnd);
		mCandicateBtn[i].SetOnClickListener(this);
	}
}

void CHandwriteInputWnd::ParserXMLNode(
	XMLNode *pNode)
{
	CParentClass::ParserXMLNode(pNode);

	CSimpleStringA sTmpString;
	XMLNode childNode;

	pNode->GetChildNode("CandicateWnd", &childNode);
	mCandicateWnd.ParserXMLNode(&childNode);

	mPrevPageBtn.ParserChildNode(&childNode, "PrevPageBtn");
	mNextPageBtn.ParserChildNode(&childNode, "NextPageBtn");

	for (int i = 0; i < CANDICATE_COUNT; i++)
	{
		sTmpString.Format("CandicateBtn%d", i);
		mCandicateBtn[i].ParserChildNode(&childNode, sTmpString.GetString());
	}

	pNode->GetChildNode("LocusWnd", &childNode);
	mLocusWnd.ParserXMLNode(&childNode);

	LOGMSG(DBG_LEVEL_D, "locus count %d\n", mLocusCount);
}

void CHandwriteInputWnd::OnWindowVisible(
	BOOL bVisible)
{
	CParentClass::OnWindowVisible(bVisible);

	if (bVisible)
	{
		int nLocusWidth = RECTWIDTH(mLocusWnd.mWndRect);
		int nLocusHeight = RECTHEIGHT(mLocusWnd.mWndRect);

		mLocusCount = nLocusWidth*nLocusHeight;

		SAFE_DELETEARRAY(mpLocusPoint);
		SAFE_DELETEARRAY(mpLocusForRecognize);

		mpLocusPoint = new short[mLocusCount];
		if (mpLocusPoint)
		{
			memset(mpLocusPoint, 0x00, mLocusCount*sizeof(short));
		}

		mpLocusForRecognize = new short[mLocusCount];
		if (mpLocusForRecognize)
		{
			memset(mpLocusForRecognize, 0x00, mLocusCount*sizeof(short));
		}

		mLocusIndex = 0;
	}
	else
	{
		ClearLocus();

		SAFE_DELETEARRAY(mpLocusPoint);
		SAFE_DELETEARRAY(mpLocusForRecognize);
	}
}

void CHandwriteInputWnd::OnTimer(
	int nTimerID)
{
	CParentClass::OnTimer(nTimerID);

	if (RECOGNIZE_TIMERID == nTimerID)
	{
		DelTimer(RECOGNIZE_TIMERID);
		DoRecognize();
	}
}

void CHandwriteInputWnd::OnClick(
	CBaseWnd *pWnd,
	POINT ptWnd)
{
	if (pWnd == &mPrevPageBtn)
	{
		ShowPage(mCurPage-1);
	}
	else if (pWnd == &mNextPageBtn)
	{
		ShowPage(mCurPage+1);
	}
	else
	{
		for (int i = 0; i < CANDICATE_COUNT; i++)
		{
			if (pWnd == &(mCandicateBtn[i]))
			{
				const wchar_t* wszString = mCandicateBtn[i].GetWindowTextW();
				if (wszString && wcslen(wszString) > 0)
				{
					if (mLastSelectChar != wszString[0])
					{
						mLastSelectChar = wszString[0];
						ReportPostMsg(INPUTWND_BACKMSG, 0, 0);
						ReportPostMsg(INPUTWND_WCHARMSG, (UINT64)wszString[0], 0);
					}
				}

				ClearLocus();
			}
		}
	}
}

void CHandwriteInputWnd::OnTouchDown(
	CBaseWnd *pWnd,
	POINT ptWnd)
{
	if (pWnd != &mLocusWnd)
	{
		return;
	}

	AddPointToLocus(ptWnd);

	DelTimer(RECOGNIZE_TIMERID);
}

void CHandwriteInputWnd::OnTouchMove(
	CBaseWnd *pWnd,
	POINT ptWnd)
{
	if (pWnd != &mLocusWnd)
	{
		return;
	}

	AddPointToLocus(ptWnd);
}

void CHandwriteInputWnd::OnTouchUp(
	CBaseWnd *pWnd,
	POINT ptWnd,
	int xDistance,
	int yDistance,
	UINT64 uUsedTime)
{
	if (pWnd != &mLocusWnd)
	{
		return;
	}

	if (!mpLocusPoint)
	{
		return;
	}

	if (mLocusIndex <= mLocusCount-4)
	{
		mpLocusPoint[mLocusIndex++] = -1;
		mpLocusPoint[mLocusIndex++] = 0;
	}
	else
	{
		LOGMSG(DBG_LEVEL_W, "locus index count %d, out bound\n", mLocusIndex);
	}

	AddTimer(RECOGNIZE_TIMERID, RECOGNIZE_DELAY_TIME);
}

void CHandwriteInputWnd::OnTouchLeave(
	CBaseWnd *pOldTouchWnd,
	CBaseWnd *pNewTouchWnd)
{
	if (pOldTouchWnd != &mLocusWnd)
	{
		return;
	}

	AddTimer(RECOGNIZE_TIMERID, RECOGNIZE_DELAY_TIME);
}

BOOL CHandwriteInputWnd::HasInputLocus()
{
	return mLocusIndex > 0 ? TRUE : FALSE;
}

void CHandwriteInputWnd::BackLocus()
{
	ClearLocus();
}

void CHandwriteInputWnd::ClearLocus()
{
	mLocusIndex = 0;
	mLastSelectChar = L'\0';

	if (mpLocusPoint)
	{
		memset(mpLocusPoint, 0x00, mLocusCount*sizeof(short));
	}
	if (mpLocusForRecognize)
	{
		memset(mpLocusForRecognize, 0x00, mLocusCount*sizeof(short));
	}
	mLocusWnd.Clear(NULL);

	SAFE_DELETEARRAY(mwszCandicateText);
	mTextCount = 0;
	mCurPage = 0;
	mPageCount = 0;

	for(int i = 0; i < CANDICATE_COUNT; i++)
	{
		mCandicateBtn[i].SetWindowTextW(NULL);
	}
}

void CHandwriteInputWnd::DeleteInputText()
{
	if (mLastSelectChar != L'\0')
	{
		ReportPostMsg(INPUTWND_BACKMSG, 0, 0);
		mLastSelectChar = L'\0';
	}
}

void CHandwriteInputWnd::AddPointToLocus(
	POINT pt)
{
	if (mLocusIndex > mLocusCount-4)
	{
		LOGMSG(DBG_LEVEL_W, "locus index count %d, out bound\n", mLocusIndex);
		return;
	}

	if (!mpLocusPoint)
	{
		return;
	}

	mpLocusPoint[mLocusIndex++] = pt.x;
	mpLocusPoint[mLocusIndex++] = pt.y;
}

void CHandwriteInputWnd::DoRecognize()
{
	if (!mpLocusPoint)
	{
		return;
	}

	mTextCount = CANDICATE_COUNT*3;
	unsigned short result[mTextCount];
	memset(result, 0, sizeof(unsigned short)*mTextCount);

	memcpy(mpLocusForRecognize, mpLocusPoint, mLocusIndex*sizeof(short));
	if (mLocusIndex <= mLocusCount-2)
	{
		mpLocusForRecognize[mLocusIndex] = -1;
		mpLocusForRecognize[mLocusIndex+1] = -1;
	}
	else
	{
		mpLocusForRecognize[mLocusCount-2] = -1;
		mpLocusForRecognize[mLocusCount-1] = -1;
	}

	if(0) //(gKTVConfig.GetLanguageID() == LanguageID_CHT)
	{
		mTextCount = gHandWriteOperator->Recognize(
			mpLocusForRecognize,
			result,
			mTextCount,
			WWHW_RANGE_BIG5 | WWHW_RANGE_NUMBER | WWHW_RANGE_LOWER_CHAR | WWHW_RANGE_UPPER_CHAR);
	}
	else
	{
		mTextCount = gHandWriteOperator->Recognize(
			mpLocusForRecognize,
			result,
			mTextCount,
			WWHW_RANGE_GB2312 | WWHW_RANGE_NUMBER | WWHW_RANGE_LOWER_CHAR | WWHW_RANGE_UPPER_CHAR);
	}

	mPageCount = (mTextCount+CANDICATE_COUNT-1) / CANDICATE_COUNT;

	SAFE_DELETEARRAY(mwszCandicateText);

	if (mTextCount > 0)
	{
		mwszCandicateText = new wchar_t[mTextCount];

		for(int i = 0; i < mTextCount; i++)
		{
			mwszCandicateText[i] = result[i];
		}

		if (mLastSelectChar != mwszCandicateText[0])
		{
			if (mLastSelectChar != L'\0')
			{
				ReportPostMsg(INPUTWND_BACKMSG, 0, 0);
			}

			ReportPostMsg(INPUTWND_WCHARMSG, (UINT64)mwszCandicateText[0], 0);
			mLastSelectChar = mwszCandicateText[0];
		}
	}

	ShowPage(0);
}

void CHandwriteInputWnd::ShowPage(
	int nPageIndex)
{
	if (nPageIndex < 0 || nPageIndex >= mPageCount)
	{
		return;
	}

	mCurPage = nPageIndex;
	for(int i = 0; i < CANDICATE_COUNT; i++)
	{
		if ((mCurPage*CANDICATE_COUNT+i) < mTextCount)
		{
			wchar_t wszText[2];
			wszText[0] = mwszCandicateText[mCurPage*CANDICATE_COUNT+i];
			wszText[1] = L'\0';
			mCandicateBtn[i].SetWindowTextW(wszText);
		}
		else
		{
			mCandicateBtn[i].SetWindowTextW(NULL);
		}
	}
}



CSymbolInputWnd::CSymbolInputWnd()
{
}

CSymbolInputWnd::~CSymbolInputWnd()
{
	LOGMSG(DBG_LEVEL_D, "function %s quit\n", __PRETTY_FUNCTION__);
}

void CSymbolInputWnd::Create(
	CE3DCommand *pE3DEngine,
	CBaseWnd *pParent)
{
	CParentClass::Create(pE3DEngine, "SymbolInputWnd", pParent);

	for ( int i = 0; i < SYMBOL_COUNT; i++ )
	{
		mSymbolItemBtn[i].Create(pE3DEngine, this);
		mSymbolItemBtn[i].SetOnClickListener(this);
	}

	mSpaceBtn.Create(pE3DEngine, this);
	mSpaceBtn.SetOnClickListener(this);
}

void CSymbolInputWnd::ParserXMLNode(
	XMLNode *pNode)
{
	CParentClass::ParserXMLNode(pNode);

	CSimpleStringA sTmpString;
	for ( int i = 0; i < SYMBOL_COUNT; i++ )
	{
		sTmpString.Format("symbol_item%d", i);
		mSymbolItemBtn[i].ParserChildNode(pNode, sTmpString.GetString());
	}

	mSpaceBtn.ParserChildNode(pNode, "SpaceBtn");
}

void CSymbolInputWnd::OnClick(
	CBaseWnd *pWnd,
	POINT ptWnd)
{
	if (pWnd == &mSpaceBtn)
	{
		ReportPostMsg(INPUTWND_WCHARMSG, (UINT64)L' ', 0);
	}
	else
	{
		for ( int i = 0; i < SYMBOL_COUNT; i++ )
		{
			if (pWnd == &(mSymbolItemBtn[i]))
			{
				ReportPostMsg(
					INPUTWND_WCHARMSG,
					(UINT64)gSymbolText[i],
					0);
			}
		}
	}
}



CChineseInputWnd::CChineseInputWnd()
{
	mwszCandicateText = NULL;
	mTextCount = 0;
	mCurPage = 0;
	mPageCount = 0;
}

CChineseInputWnd::~CChineseInputWnd()
{
	LOGMSG(DBG_LEVEL_D, "function %s quit\n", __PRETTY_FUNCTION__);

	SAFE_DELETEARRAY(mwszCandicateText);
}

void CChineseInputWnd::Create(
	CE3DCommand *pE3DEngine,
	CBaseWnd *pParent)
{
	CParentClass::Create(pE3DEngine, "ChineseInputWnd", pParent);

	mChineseTextEdit.Create(pE3DEngine, this, 0, WINDOWSTATE_DISABLED);
	mChineseTextEdit.EnableCursor(FALSE);

	mCandicateWnd.CreateStatic(pE3DEngine, this);

	mPrevPageBtn.CreateStatic(pE3DEngine, &mCandicateWnd);
	mPrevPageBtn.SetOnClickListener(this);

	mNextPageBtn.CreateStatic(pE3DEngine, &mCandicateWnd);
	mNextPageBtn.SetOnClickListener(this);

	for (int i = 0; i < CANDICATE_COUNT; i++)
	{
		mCandicateBtn[i].Create(pE3DEngine, &mCandicateWnd);
		mCandicateBtn[i].SetOnClickListener(this);
	}

	for ( int i = 0; i < LETTER_COUNT; i++ )
	{
		mLetterItemBtn[i].Create(pE3DEngine, this);
		mLetterItemBtn[i].SetOnClickListener(this);
	}
}

void CChineseInputWnd::ParserXMLNode(
	XMLNode *pNode)
{
	CParentClass::ParserXMLNode(pNode);

	mChineseTextEdit.ParserChildNode(pNode, "ChineseTextEdit");

	CSimpleStringA sTmpString;
	XMLNode childNode;

	pNode->GetChildNode("CandicateWnd", &childNode);
	mCandicateWnd.ParserXMLNode(&childNode);

	mPrevPageBtn.ParserChildNode(&childNode, "PrevPageBtn");
	mNextPageBtn.ParserChildNode(&childNode, "NextPageBtn");

	for (int i = 0; i < CANDICATE_COUNT; i++)
	{
		sTmpString.Format("CandicateBtn%d", i);
		mCandicateBtn[i].ParserChildNode(&childNode, sTmpString.GetString());
	}

	for ( int i = 0; i < LETTER_COUNT; i++ )
	{
		sTmpString.Format("letter_item%d", i);
		mLetterItemBtn[i].ParserChildNode(pNode, sTmpString.GetString());
	}
}

void CChineseInputWnd::OnClick(
	CBaseWnd *pWnd,
	POINT ptWnd)
{
	if (pWnd == &mPrevPageBtn)
	{
		ShowPage(mCurPage-1);
	}
	else if (pWnd == &mNextPageBtn)
	{
		ShowPage(mCurPage+1);
	}
	else
	{
		for (int i = 0; i < CANDICATE_COUNT; i++)
		{
			if (pWnd == &(mCandicateBtn[i]))
			{
				const wchar_t* wszString = mCandicateBtn[i].GetWindowTextW();
				if (wszString && wcslen(wszString) > 0)
				{
					ReportPostMsg(INPUTWND_WCHARMSG, (UINT64)wszString[0], 0);
				}

				mChineseTextEdit.ClearText();
				return;
			}
		}

		for ( int i = 0; i < LETTER_COUNT; i++ )
		{
			if (pWnd == &(mLetterItemBtn[i]))
			{
				wchar_t wChar = L'A'+i;
				mChineseTextEdit.AddChar(wChar);
				RecognizeChinese();
				return;
			}
		}
	}
}

BOOL CChineseInputWnd::HasInputText()
{
	const wchar_t *wszInputText = mChineseTextEdit.GetWindowTextW();
	if (wszInputText && wcslen(wszInputText))
	{
		return TRUE;
	}

	return FALSE;
}

void CChineseInputWnd::BackInput()
{
	mChineseTextEdit.BackChar();
	RecognizeChinese();
}

void CChineseInputWnd::ClearInput()
{
	mChineseTextEdit.ClearText();
}

void CChineseInputWnd::RecognizeChinese()
{
	const wchar_t* wszChinese = pinyin_to_GB2312(mChineseTextEdit.GetWindowTextW());
	mTextCount = wcslen(wszChinese);

	SAFE_DELETEARRAY(mwszCandicateText);

	if (mTextCount > 0)
	{
		mPageCount = (mTextCount+CANDICATE_COUNT-1) / CANDICATE_COUNT;
		mwszCandicateText = new wchar_t[mTextCount];
		for(int i = 0; i < mTextCount; i++)
		{
			mwszCandicateText[i] = wszChinese[i];
		}

		for(int i = 0; i < CANDICATE_COUNT; i++)
		{
			mCandicateBtn[i].SetWindowTextW(NULL);
		}
	}

	mCandicateWnd.SetWindowVisible(TRUE);
	ShowPage(0);
}

void CChineseInputWnd::ShowPage(
	int nPageIndex)
{
	if (nPageIndex < 0 || nPageIndex >= mPageCount)
	{
		return;
	}

	mCurPage = nPageIndex;
	for(int i = 0; i < CANDICATE_COUNT; i++)
	{
		if ((mCurPage*CANDICATE_COUNT+i) < mTextCount)
		{
			wchar_t wszText[2];
			wszText[0] = mwszCandicateText[mCurPage*CANDICATE_COUNT+i];
			wszText[1] = L'\0';
			mCandicateBtn[i].SetWindowTextW(wszText);
		}
		else
		{
			mCandicateBtn[i].SetWindowTextW(NULL);
		}
	}
}




CSpeechInputWnd::CSpeechInputWnd()
{
}

CSpeechInputWnd::~CSpeechInputWnd()
{
	LOGMSG(DBG_LEVEL_D, "function %s quit\n", __PRETTY_FUNCTION__);
}

void CSpeechInputWnd::Create(
	CE3DCommand *pE3DEngine,
	CBaseWnd *pParent)
{
	CParentClass::Create(pE3DEngine, "SpeechInputWnd", pParent);

	mSpeechPromptWnd.CreateStatic(pE3DEngine, this);
	mSpeechPromptWnd.SetFontAutoMultiline(TRUE);

	mStartSpeechBtn.Create(pE3DEngine, this, BUTTONTYPE_RADIO);
	mStartSpeechBtn.SetOnClickListener(this);

	mSpeechStateWnd.CreateStatic(pE3DEngine, this);
	mSpeechStateWnd.SetFontAutoMultiline(TRUE);
}

void CSpeechInputWnd::ParserXMLNode(
	XMLNode *pNode)
{
	CParentClass::ParserXMLNode(pNode);

	mSpeechPromptWnd.ParserChildNode(pNode, "SpeechPromptWnd");
	mStartSpeechBtn.ParserChildNode(pNode, "StartSpeechBtn");
	mSpeechStateWnd.ParserChildNode(pNode, "SpeechStateWnd");
}

void CSpeechInputWnd::OnWindowVisible(
	BOOL bVisible)
{
	CParentClass::OnWindowVisible(bVisible);

	if (!bVisible)
	{
		NativeCommand("STT,STOP");
		mStartSpeechBtn.SetRadioBtnPressed(FALSE);
	}
}

void CSpeechInputWnd::OnClick(
	CBaseWnd *pWnd,
	POINT ptWnd)
{
	if (pWnd == &mStartSpeechBtn)
	{
		if (mStartSpeechBtn.IsRadioBtnPressed())
		{
			mSpeechStateWnd.SetWindowTextA(NULL);

			CSimpleStringA sTmp;
			sTmp.Format("STT,START,%p", (ISpeechRecvListener *)this);
			NativeCommand(sTmp.GetString());
		}
		else
		{
			NativeCommand("STT,STOP");
			mStartSpeechBtn.SetRadioBtnPressed(FALSE);
		}
	}
}

void CSpeechInputWnd::OnSpeechResult(
	const char* cResultString)
{
	if (cResultString && strlen(cResultString) > 0)
	{
		LOGMSG(DBG_LEVEL_I, "%s:%s\n", __PRETTY_FUNCTION__, cResultString);
		CSimpleStringW *pTmpString = new CSimpleStringW;
		pTmpString->Set(cResultString);
		ReportPostMsg(INPUTWND_WSTRINGMSG, (UINT64)pTmpString, 0);
	}
}

void CSpeechInputWnd::OnSpeechState(
	const char* cStateString)
{
	mSpeechStateWnd.SetWindowTextA(cStateString);
}

void CSpeechInputWnd::OnSpeechEnd()
{
	mStartSpeechBtn.SetRadioBtnPressed(FALSE);
}




CInputMethodBoard::CInputMethodBoard()
{
	SetRectXY(&mTypeBoundPosition, 0, 0, 0, 0);
	mTypeBtnSize.cx = mTypeBtnSize.cy = 0;
	mFirstShowBtnIndex = 0;
	mIMEType = IMETYPE_LETTER;
}

CInputMethodBoard::~CInputMethodBoard()
{
}

void CInputMethodBoard::Create(
	CE3DCommand *pE3DEngine,
	CBaseWnd *pParent)
{
	CParentClass::Create(pE3DEngine, "InputMethodBoard", pParent);

	mPrevTypeBtn.Create(pE3DEngine, this);
	mPrevTypeBtn.SetOnClickListener(this);

	mNextTypeBtn.Create(pE3DEngine, this);
	mNextTypeBtn.SetOnClickListener(this);

	mLetterBtn.Create(pE3DEngine, this, BUTTONTYPE_RADIO);
	mLetterBtn.SetOnClickListener(this);
	mInputBtnGroup.AddToGroup(&mLetterBtn);

	mStrokeBtn.Create(pE3DEngine, this, BUTTONTYPE_RADIO);
	mStrokeBtn.SetOnClickListener(this);
	mInputBtnGroup.AddToGroup(&mStrokeBtn);

	mHandwriteBtn.Create(pE3DEngine, this, BUTTONTYPE_RADIO);
	mHandwriteBtn.SetOnClickListener(this);
	mInputBtnGroup.AddToGroup(&mHandwriteBtn);

	mSymbolBtn.Create(pE3DEngine, this, BUTTONTYPE_RADIO);
	mSymbolBtn.SetOnClickListener(this);
	mInputBtnGroup.AddToGroup(&mSymbolBtn);

	mChineseBtn.Create(pE3DEngine, this, BUTTONTYPE_RADIO);
	mChineseBtn.SetOnClickListener(this);
	mInputBtnGroup.AddToGroup(&mChineseBtn);

	mSpeechBtn.Create(pE3DEngine, this, BUTTONTYPE_RADIO);
	mSpeechBtn.SetOnClickListener(this);
	mInputBtnGroup.AddToGroup(&mSpeechBtn);

	mBackBtn.Create(pE3DEngine, this);
	mBackBtn.SetOnClickListener(this);

	mClearBtn.Create(pE3DEngine, this);
	mClearBtn.SetOnClickListener(this);

	mLetterDigitInputWnd.Create(pE3DEngine, this);
	mLetterDigitInputWnd.SetWindowVisible(FALSE);
	mLetterDigitInputWnd.SetMsgRecvWnd(this);

	mStrokeInputWnd.Create(pE3DEngine, this);
	mStrokeInputWnd.SetWindowVisible(FALSE);
	mStrokeInputWnd.SetMsgRecvWnd(this);

	mHandwriteInputWnd.Create(pE3DEngine, this);
	mHandwriteInputWnd.SetWindowVisible(FALSE);
	mHandwriteInputWnd.SetMsgRecvWnd(this);

	mSymbolInputWnd.Create(pE3DEngine, this);
	mSymbolInputWnd.SetWindowVisible(FALSE);
	mSymbolInputWnd.SetMsgRecvWnd(this);

	mChineseInputWnd.Create(pE3DEngine, this);
	mChineseInputWnd.SetWindowVisible(FALSE);
	mChineseInputWnd.SetMsgRecvWnd(this);

	mSpeechInputWnd.Create(pE3DEngine, this);
	mSpeechInputWnd.SetWindowVisible(FALSE);
	mSpeechInputWnd.SetMsgRecvWnd(this);
}

void CInputMethodBoard::OnLoadResource()
{
	CParentClass::OnLoadResource();

	UIRESITEM* pItemData =
		theBaseApp->GetResourceItem("xml/InputMethodBoard");
	if (!pItemData)
	{
		LOGMSG(DBG_LEVEL_E, "failed to get item, file=%s!!\n", __FILE__);
		return;
	}

	XMLParser parser;
	if(!parser.LoadFromBuffer(&(pItemData->sXmlBuffer)))
	{
		LOGMSG(DBG_LEVEL_E, "failed to load xml buffer, file=%s!!\n", __FILE__);
		return;
	}

	// read from xml
	XMLNode rootnode;
	if ( !parser.GetNode("InputMethodBoard", &rootnode) )
	{
		LOGMSG(DBG_LEVEL_E, "failed to Get xml root node %s!!\n", "InputMethodBoard");
		return;
	}

	CParentClass::ParserXMLNode(&rootnode);

	XmlNodeLoadRect(&rootnode, "TypeBoundPosition", &mTypeBoundPosition);
	XmlNodeLoadSize(&rootnode, "TypeBtnSize", &mTypeBtnSize);

	mPrevTypeBtn.ParserChildNode(&rootnode, "PrevTypeBtn");
	mNextTypeBtn.ParserChildNode(&rootnode, "NextTypeBtn");

	mLetterBtn.ParserChildNode(&rootnode, "LetterBtn");
	mStrokeBtn.ParserChildNode(&rootnode, "StrokeBtn");
	mHandwriteBtn.ParserChildNode(&rootnode, "HandwriteBtn");
	mSymbolBtn.ParserChildNode(&rootnode, "SymbolBtn");
	mChineseBtn.ParserChildNode(&rootnode, "ChineseBtn");
	mSpeechBtn.ParserChildNode(&rootnode, "SpeechBtn");

	mBackBtn.ParserChildNode(&rootnode, "BackBtn");
	mClearBtn.ParserChildNode(&rootnode, "ClearBtn");

	mLetterDigitInputWnd.ParserChildNode(&rootnode, "LetterDigitInputWnd");
	mStrokeInputWnd.ParserChildNode(&rootnode, "StrokeInputWnd");
	mHandwriteInputWnd.ParserChildNode(&rootnode, "HandwriteInputWnd");
	mSymbolInputWnd.ParserChildNode(&rootnode, "SymbolInputWnd");
	mChineseInputWnd.ParserChildNode(&rootnode, "ChineseInputWnd");
	mSpeechInputWnd.ParserChildNode(&rootnode, "SpeechInputWnd");

	RelayoutTypeBtns();
	//OnDBTypeChanged();
}

void CInputMethodBoard::OnMsg(
	UINT32 uType,
	UINT64 wParam,
	UINT64 lParam)
{
	CParentClass::OnMsg(uType, wParam, lParam);

	switch(uType)
	{
	case DBTYPE_CHANGED_MSG:
		//OnDBTypeChanged();
		break;

	default:
		ReportPostMsg(uType, wParam, lParam);
		break;
	}
}

void CInputMethodBoard::OnClick(
	CBaseWnd *pWnd,
	POINT ptWnd)
{
	if (pWnd == &mPrevTypeBtn)
	{
		if (mFirstShowBtnIndex > 0)
		{
			mFirstShowBtnIndex--;
			RelayoutTypeBtns();
		}
	}
	else if (pWnd == &mNextTypeBtn)
	{
		int nCanShowCount = RECTWIDTH(mTypeBoundPosition)/mTypeBtnSize.cx;
		if ((mFirstShowBtnIndex+nCanShowCount) < mTypeBtnList.GetCount() )
		{
			mFirstShowBtnIndex++;
			RelayoutTypeBtns();
		}
	}
	else if (pWnd == &mLetterBtn)
	{
		OnRadioButtonClick(&mLetterBtn, TRUE);
	}
	else if (pWnd == &mStrokeBtn)
	{
		OnRadioButtonClick(&mStrokeBtn, TRUE);
	}
	else if (pWnd == &mHandwriteBtn)
	{
		OnRadioButtonClick(&mHandwriteBtn, TRUE);
	}
	else if (pWnd == &mSymbolBtn)
	{
		OnRadioButtonClick(&mSymbolBtn, TRUE);
	}
	else if (pWnd == &mChineseBtn)
	{
		OnRadioButtonClick(&mChineseBtn, TRUE);
	}
	else if (pWnd == &mSpeechBtn)
	{
		OnRadioButtonClick(&mSpeechBtn, TRUE);
	}
	else if (pWnd == &mBackBtn)
	{
		BOOL bNeedBackText = TRUE;
		CBaseButton *pButton = mInputBtnGroup.GetSelectButton();
		if (pButton == &mChineseBtn)
		{
			if (mChineseInputWnd.HasInputText())
			{
				mChineseInputWnd.BackInput();
				bNeedBackText = FALSE;
			}
		}
		else if (pButton == &mHandwriteBtn)
		{
			if (mHandwriteInputWnd.HasInputLocus())
			{
				mHandwriteInputWnd.DeleteInputText();
				mHandwriteInputWnd.BackLocus();
				bNeedBackText = FALSE;
			}
		}

		if (bNeedBackText)
		{
			ReportPostMsg(INPUTWND_BACKMSG, 0, 0);
		}
	}
	else if (pWnd == &mClearBtn)
	{
		BOOL bNeedClearText = TRUE;
		CBaseButton *pButton = mInputBtnGroup.GetSelectButton();
		if (pButton == &mChineseBtn)
		{
			if (mChineseInputWnd.HasInputText())
			{
				mChineseInputWnd.ClearInput();
				bNeedClearText = FALSE;
			}
		}
		else if (pButton == &mHandwriteBtn)
		{
			if (mHandwriteInputWnd.HasInputLocus())
			{
				mHandwriteInputWnd.DeleteInputText();
				mHandwriteInputWnd.ClearLocus();
				bNeedClearText = FALSE;
			}
		}

		if (bNeedClearText)
		{
			ReportPostMsg(INPUTWND_CLEARMSG, 0, 0);
		}
	}
}

void CInputMethodBoard::SetIMEType(
	IMETYPE eType)
{
	CBaseButton *pIMEButton = NULL;

	switch (eType)
	{
	case IMETYPE_LETTER:
		pIMEButton = &mLetterBtn;
		break;

	case IMETYPE_STROKE:
		pIMEButton = &mStrokeBtn;
		break;

	case IMETYPE_HANDWRITE:
		pIMEButton = &mHandwriteBtn;
		break;

	case IMETYPE_SYMBOL:
		pIMEButton = &mSymbolBtn;
		break;

	case IMETYPE_CHINESE:
		pIMEButton = &mChineseBtn;
		break;

	case IMETYPE_SPEECH:
		pIMEButton = &mSpeechBtn;
		break;

	default:
		break;
	}

	if (!mTypeBtnList.FindFirst(pIMEButton, NULL))
	{
		pIMEButton = (CBaseButton*)mTypeBtnList.GetAt(0);
	}

	if (pIMEButton)
	{
		OnRadioButtonClick(pIMEButton, FALSE);
	}
}

IMETYPE CInputMethodBoard::GetIMEType()
{
	return mIMEType;
}

void CInputMethodBoard::AddIMEType(
	IMETYPE eType)
{
	switch (eType)
	{
	case IMETYPE_LETTER:
		if (mTypeBtnList.FindFirst(&mLetterBtn, NULL) < 0)
		{
			mTypeBtnList.AddData(&mLetterBtn);
		}
		break;

	case IMETYPE_STROKE:
		if (mTypeBtnList.FindFirst(&mStrokeBtn, NULL) < 0)
		{
			mTypeBtnList.AddData(&mStrokeBtn);
		}
		break;

	case IMETYPE_HANDWRITE:
		if (mTypeBtnList.FindFirst(&mHandwriteBtn, NULL) < 0)
		{
			mTypeBtnList.AddData(&mHandwriteBtn);
		}
		break;

	case IMETYPE_SYMBOL:
		if (mTypeBtnList.FindFirst(&mSymbolBtn, NULL) < 0)
		{
			mTypeBtnList.AddData(&mSymbolBtn);
		}
		break;

	case IMETYPE_CHINESE:
		if (mTypeBtnList.FindFirst(&mChineseBtn, NULL) < 0)
		{
			mTypeBtnList.AddData(&mChineseBtn);
		}
		break;

	case IMETYPE_SPEECH:
		if (mTypeBtnList.FindFirst(&mSpeechBtn, NULL) < 0)
		{
			mTypeBtnList.AddData(&mSpeechBtn);
		}
		break;

	default:
		break;
	}

	RelayoutTypeBtns();
}

void CInputMethodBoard::DelIMEType(
	IMETYPE eType)
{
	switch (eType)
	{
	case IMETYPE_LETTER:
		mTypeBtnList.DeleteAt(mTypeBtnList.FindFirst(&mLetterBtn, NULL));
		break;

	case IMETYPE_STROKE:
		mTypeBtnList.DeleteAt(mTypeBtnList.FindFirst(&mStrokeBtn, NULL));
		break;

	case IMETYPE_HANDWRITE:
		mTypeBtnList.DeleteAt(mTypeBtnList.FindFirst(&mHandwriteBtn, NULL));
		break;

	case IMETYPE_SYMBOL:
		mTypeBtnList.DeleteAt(mTypeBtnList.FindFirst(&mSymbolBtn, NULL));
		break;

	case IMETYPE_CHINESE:
		mTypeBtnList.DeleteAt(mTypeBtnList.FindFirst(&mChineseBtn, NULL));
		break;

	case IMETYPE_SPEECH:
		mTypeBtnList.DeleteAt(mTypeBtnList.FindFirst(&mSpeechBtn, NULL));
		break;

	default:
		break;
	}

	RelayoutTypeBtns();
}


void CInputMethodBoard::OnRadioButtonClick(
	CBaseButton *pButton,
	BOOL bNeedSendIMESwitchMsg)
{
	if (pButton == &mLetterBtn)
	{
		mChineseInputWnd.ClearInput();
		mInputBtnGroup.SetSelectButton(&mLetterBtn);

		mLetterDigitInputWnd.SetWindowVisible(TRUE);
		mHandwriteInputWnd.SetWindowVisible(FALSE);
		mStrokeInputWnd.SetWindowVisible(FALSE);
		mSymbolInputWnd.SetWindowVisible(FALSE);
		mChineseInputWnd.SetWindowVisible(FALSE);
		mSpeechInputWnd.SetWindowVisible(FALSE);

		mIMEType = IMETYPE_LETTER;
	}
	else if (pButton == &mStrokeBtn)
	{
		mInputBtnGroup.SetSelectButton(&mStrokeBtn);

		mStrokeInputWnd.SetWindowVisible(TRUE);
		mLetterDigitInputWnd.SetWindowVisible(FALSE);
		mHandwriteInputWnd.SetWindowVisible(FALSE);
		mSymbolInputWnd.SetWindowVisible(FALSE);
		mChineseInputWnd.SetWindowVisible(FALSE);
		mSpeechInputWnd.SetWindowVisible(FALSE);

		mIMEType = IMETYPE_STROKE;
	}
	else if (pButton == &mHandwriteBtn)
	{
		mInputBtnGroup.SetSelectButton(&mHandwriteBtn);

		mHandwriteInputWnd.SetWindowVisible(TRUE);
		mLetterDigitInputWnd.SetWindowVisible(FALSE);
		mStrokeInputWnd.SetWindowVisible(FALSE);
		mSymbolInputWnd.SetWindowVisible(FALSE);
		mChineseInputWnd.SetWindowVisible(FALSE);
		mSpeechInputWnd.SetWindowVisible(FALSE);

		mIMEType = IMETYPE_HANDWRITE;
		mHandwriteInputWnd.ClearLocus();
	}
	else if (pButton == &mSymbolBtn)
	{
		mInputBtnGroup.SetSelectButton(&mSymbolBtn);

		mSymbolInputWnd.SetWindowVisible(TRUE);
		mLetterDigitInputWnd.SetWindowVisible(FALSE);
		mStrokeInputWnd.SetWindowVisible(FALSE);
		mHandwriteInputWnd.SetWindowVisible(FALSE);
		mChineseInputWnd.SetWindowVisible(FALSE);
		mSpeechInputWnd.SetWindowVisible(FALSE);

		mIMEType = IMETYPE_SYMBOL;
	}
	else if (pButton == &mChineseBtn)
	{
		mInputBtnGroup.SetSelectButton(&mChineseBtn);

		mChineseInputWnd.SetWindowVisible(TRUE);
		mLetterDigitInputWnd.SetWindowVisible(FALSE);
		mStrokeInputWnd.SetWindowVisible(FALSE);
		mHandwriteInputWnd.SetWindowVisible(FALSE);
		mSymbolInputWnd.SetWindowVisible(FALSE);
		mSpeechInputWnd.SetWindowVisible(FALSE);

		mIMEType = IMETYPE_CHINESE;
		mChineseInputWnd.ClearInput();
	}
	else if (pButton == &mSpeechBtn)
	{
		mInputBtnGroup.SetSelectButton(&mSpeechBtn);

		mSpeechInputWnd.SetWindowVisible(TRUE);
		mLetterDigitInputWnd.SetWindowVisible(FALSE);
		mStrokeInputWnd.SetWindowVisible(FALSE);
		mHandwriteInputWnd.SetWindowVisible(FALSE);
		mSymbolInputWnd.SetWindowVisible(FALSE);
		mChineseInputWnd.SetWindowVisible(FALSE);

		mIMEType = IMETYPE_SPEECH;
	}

	if (bNeedSendIMESwitchMsg)
	{
		ReportPostMsg(INPUTWND_SWITCHIME, 0, 0);
	}
}

void CInputMethodBoard::RelayoutTypeBtns()
{
	if (mTypeBtnSize.cx == 0)
	{
		return;
	}

	RECT rcTypeBtn;

	SetRectXY(
		&rcTypeBtn,
		mTypeBoundPosition.left,
		mTypeBoundPosition.top,
		mTypeBtnSize.cx,
		mTypeBtnSize.cy);

	mLetterBtn.SetWindowVisible(FALSE);
	mStrokeBtn.SetWindowVisible(FALSE);
	mHandwriteBtn.SetWindowVisible(FALSE);
	mSymbolBtn.SetWindowVisible(FALSE);
	mChineseBtn.SetWindowVisible(FALSE);
	mSpeechBtn.SetWindowVisible(FALSE);

	int nCanShowCount = RECTWIDTH(mTypeBoundPosition)/mTypeBtnSize.cx;
	if ((mFirstShowBtnIndex+nCanShowCount) > mTypeBtnList.GetCount() )
	{
		mFirstShowBtnIndex = mTypeBtnList.GetCount() - nCanShowCount;
	}

	if (mFirstShowBtnIndex < 0)
	{
		mFirstShowBtnIndex = 0;
	}

	for (int i = 0; i < nCanShowCount; i++)
	{
		CBaseButton *pButton = (CBaseButton*)mTypeBtnList.GetAt(i+mFirstShowBtnIndex);
		if (pButton)
		{
			pButton->MoveWindow(&rcTypeBtn);
			pButton->SetWindowVisible(TRUE);
		}

		rcTypeBtn.left += mTypeBtnSize.cx;
		rcTypeBtn.right += mTypeBtnSize.cx;
	}
}

