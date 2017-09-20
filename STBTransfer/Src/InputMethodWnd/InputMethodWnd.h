#pragma once

#include "InputMethodBoard.h"

class CInputMethodWnd : public CBaseWnd
{
	typedef CBaseWnd CParentClass;

public:
	CInputMethodWnd();
	virtual ~CInputMethodWnd();

public:
	virtual void Create(
		CE3DCommand *pE3DEngine,
		CBaseWnd *pParent);

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
