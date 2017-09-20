#pragma once

#include "XMLParser.h"

class CBaseWnd;

class IWndEffect
{
public:
	virtual ~IWndEffect(void) {};

public:
	virtual const char* GetEffectName()=0;

	virtual void Create(
		CBaseWnd *pEffectWnd)=0;
	virtual void Delete()=0;

	virtual void ParserFromXmlNode(
		XMLNode *pNode)=0;

	virtual void StartEffect()=0;
	virtual void StopEffect()=0;
};

IWndEffect* CreateWndEffect(
	const char* cEffectName,
	CBaseWnd *pEffectWnd,
	XMLNode *pEffectNode);
void DeleteWndEffect(
	IWndEffect* pWndEffect);
