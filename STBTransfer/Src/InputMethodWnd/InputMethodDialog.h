#pragma once

#include "InputMethodBoard.h"

class CInputMethodDialog : public CPopupSlideWnd
{
	typedef CPopupSlideWnd CParentClass;

public:
	CInputMethodDialog();
	virtual ~CInputMethodDialog();

public:
	virtual void Create(
		CE3DCommand *pE3DEngine,
		CBaseWnd *pParent,
		BOOL bInitShow,
		BOOL bAutoHideWhenInactive);

	// interface
public:
	virtual void SetMsgRecvWnd(
		CBaseWnd *pRecvWnd);

public:
	void SetIMEType(
		IMETYPE eType);
	IMETYPE GetIMEType();

	void AddIMEType(
		IMETYPE eType);

	void DelIMEType(
		IMETYPE eType);

private:
	CInputMethodBoard mInputMethodBoard;
};
