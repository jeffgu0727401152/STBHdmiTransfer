#pragma once

#include "BaseWnd.h"

class CBaseEdit: public CBaseWnd
{
	typedef CBaseWnd CParentClass;

public:
	CBaseEdit();
	virtual ~CBaseEdit();

public:
	void Create(
		CE3DCommand *pE3DEngine,
		CBaseWnd *pParent,
		UINT32 uFlag=WINDOWFLAG_DEFAULT,
		UINT32 uState=WINDOWSTATE_DEFAULT);

	virtual void ParserXMLNode(
		XMLNode *pNode);

	virtual void OnWindowVisible(
		BOOL bVisible);

	virtual void OnWindowFocus(
		BOOL bFocus);

	virtual void OnTimer(
		int nTimerID);

	virtual void SetWindowTextA(
		const char *cText);
	virtual void SetWindowTextW(
		const wchar_t *wszText);
	virtual const wchar_t* GetWindowTextW();

	virtual void SetFontColor(
		UINT32 uARGB);

	virtual void SetBkgroundTexture(
		CTexture *pTexture);
	virtual void SetBkgroundImageBuffer(
		CImageBuffer *pImageBuffer,
		RECT  *prcUpdate);

protected:
	virtual BOOL WantFocus();

public:
	BOOL IsInputMode();

	void SetPasswordMode(
		BOOL bPasswordMode);
	void SetTextMaxLength(
		int nTextMaxLength);
	void AddChar(
		const char cChar);
	void AddChar(
		const wchar_t wszChar);
	void AddString(
		const char* cString);
	void AddString(
		const wchar_t* wszString);
	void BackChar();
	void ClearText();
	BOOL IsEmpty();

	void SetPromptText(
		const char* cPromptText,
		UINT32 uPromptFontColor);
	void SetPromptText(
		const wchar_t* wszPromptText,
		UINT32 uPromptFontColor);
	void SetPromptTexture(
		CTexture *pPromptTexture);

	void EnableCursor(
		BOOL bEnable);

private:
	void UpdateText();
	void ShowCursor(
		BOOL bShow);
	void UpdateCursorPosition();

public:
	static CBaseEdit* GetActiveEditWnd();

private:
	int mTextMaxLength;

	CSimpleStringW mPromptText;

	UINT32 mPromptFontColor;
	UINT32 mOriginalColor;

	CTexture mPromptTexture;
	CTexture mOriginalTexture;

	CBaseWnd mCursorWnd;
	BOOL mCursorEnable;
	BOOL mCursorShow;

	CSimpleStringW mTextString;
	BOOL mShowLastChar;
	BOOL mPasswordMode;
};
