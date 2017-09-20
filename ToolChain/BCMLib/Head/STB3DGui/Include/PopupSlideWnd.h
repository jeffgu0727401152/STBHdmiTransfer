#pragma once

#include "IPopupWndInterface.h"
#include "SlideWnd.h"

class CPopupSlideWnd: public CSlideWnd,
	public IPopupWndInterface
{
	typedef CSlideWnd CParentClass;

public:
	CPopupSlideWnd();
	virtual ~CPopupSlideWnd();

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
