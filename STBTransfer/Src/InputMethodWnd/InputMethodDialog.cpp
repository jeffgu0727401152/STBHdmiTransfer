#include "InputMethodDialog.h"
#include "BaseApp.h"
#include "XMLParser.h"
#include "../UserMsgDefine.h"


CInputMethodDialog::CInputMethodDialog()
{
}

CInputMethodDialog::~CInputMethodDialog()
{
}

void CInputMethodDialog::Create(
	CE3DCommand *pE3DEngine,
	CBaseWnd *pParent,
	BOOL bInitShow,
	BOOL bAutoHideWhenInactive)
{
	CParentClass::Create(
		pE3DEngine,
		"InputMethodDialog",
		pParent,
		bInitShow,
		bAutoHideWhenInactive);

	mInputMethodBoard.Create(
		pE3DEngine,
		this);
}

void CInputMethodDialog::SetMsgRecvWnd(
	CBaseWnd *pRecvWnd)
{
	mInputMethodBoard.SetMsgRecvWnd(pRecvWnd);
}

void CInputMethodDialog::SetIMEType(
	IMETYPE eType)
{
	mInputMethodBoard.SetIMEType(eType);
}

IMETYPE CInputMethodDialog::GetIMEType()
{
	return mInputMethodBoard.GetIMEType();
}

void CInputMethodDialog::AddIMEType(
	IMETYPE eType)
{
	mInputMethodBoard.AddIMEType(eType);
}

void CInputMethodDialog::DelIMEType(
	IMETYPE eType)
{
	mInputMethodBoard.DelIMEType(eType);
}
