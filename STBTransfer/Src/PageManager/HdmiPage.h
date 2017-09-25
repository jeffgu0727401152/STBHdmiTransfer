#pragma once

#include "BaseWnd.h"

class CHdmiPage: public CBaseWnd
{
	typedef CBaseWnd CParentClass;

public:
	CHdmiPage();
	virtual ~CHdmiPage();

public:
	virtual void Create(
		CE3DCommand *pE3DEngine,
		CBaseWnd *pParent);

	virtual void OnLoadResource();

	virtual void OnWindowVisible(
		BOOL bVisible);

	// interface
public:
	virtual void OnMsg(
		UINT32 uType,
		UINT64 wParam,
		UINT64 lParam);

public:
	void PerformHttpCmd_Hdmi();

	BOOL IsHdmiInConnected();

private:
	CBaseWnd mPictureWnd;

	BOOL mHdmiInConnected;
};

extern CHdmiPage *gHdmiPage;
