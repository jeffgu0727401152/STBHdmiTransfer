#pragma once

#include "IPopupWndInterface.h"

class CPopupWnd: public CBaseWnd,
	public IPopupWndInterface
{
	typedef CBaseWnd CParentClass;

public:
	CPopupWnd();
	virtual ~CPopupWnd();

public:
	virtual void Create(
		CE3DCommand *pE3DEngine,
		const char *cClassName,
		CBaseWnd *pParent,
		BOOL bInitShow,
		BOOL bAutoHideWhenInactive);

	virtual void OnWindowActivate(
		BOOL bActivate);

protected:
	virtual BOOL WantFocus();
};
