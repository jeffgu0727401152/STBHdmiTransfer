#pragma once

#include "BaseWnd.h"

class CBlankPage: public CBaseWnd
{
	typedef CBaseWnd CParentClass;

public:
	CBlankPage();
	virtual ~CBlankPage();

public:
	virtual void Create(
		CE3DCommand *pE3DEngine,
		CBaseWnd *pParent);

	virtual void OnLoadResource();

	virtual void OnWindowVisible(
		BOOL bVisible);
};
