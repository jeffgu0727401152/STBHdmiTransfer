#include "InputMethodWnd.h"
#include "BaseApp.h"
#include "XMLParser.h"
#include "../UserMsgDefine.h"


CInputMethodWnd::CInputMethodWnd()
{
}

CInputMethodWnd::~CInputMethodWnd()
{
}

void CInputMethodWnd::Create(
	CE3DCommand *pE3DEngine,
	CBaseWnd *pParent)
{
	CParentClass::Create(pE3DEngine, "InputMethodWnd", pParent);

	mInputMethodBoard.Create(
		pE3DEngine,
		this);
}

void CInputMethodWnd::SetMsgRecvWnd(
	CBaseWnd *pRecvWnd)
{
	mInputMethodBoard.SetMsgRecvWnd(pRecvWnd);
}

void CInputMethodWnd::SetIMEType(
	IMETYPE eType)
{
	mInputMethodBoard.SetIMEType(eType);
}

IMETYPE CInputMethodWnd::GetIMEType()
{
	return mInputMethodBoard.GetIMEType();
}

void CInputMethodWnd::AddIMEType(
	IMETYPE eType)
{
	mInputMethodBoard.AddIMEType(eType);
}

void CInputMethodWnd::DelIMEType(
	IMETYPE eType)
{
	mInputMethodBoard.DelIMEType(eType);
}
