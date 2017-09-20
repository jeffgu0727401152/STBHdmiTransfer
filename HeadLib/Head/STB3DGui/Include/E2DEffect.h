#pragma once

#include "types.h"
#include "MsgQueue.h"

class CE2DEffect;
class IE2DEffectListener
{
public:
	virtual ~IE2DEffectListener(void) {}

public:
	virtual void OnEffetStart(
		CE2DEffect *pEffect,
		UINT64 uUserData)
	{
	}

	virtual void OnEffetStep(
		CE2DEffect *pEffect,
		UINT64 uUserData,
		int nCurStep,
		int nTotalStep)
	{
	}

	virtual void OnEffetStop(
		CE2DEffect *pEffect,
		UINT64 uUserData)
	{
	}
};

class CE2DEffect : public IMessageOwner
{
public:
	CE2DEffect();
	virtual ~CE2DEffect();

	// interface
public:
	virtual void OnMsg(
		UINT32 uType,
		UINT64 wParam,
		UINT64 lParam);

public:
	void SetEffectParam(
		IE2DEffectListener *pListener,
		UINT64 uUserData=0,
		UINT64 uEffectMS=1000);

	void StartEffect(
		BOOL bReverse);

	void StopEffect();

protected:
	virtual void OnStart();

	virtual void OnStep(
		int nCurStep,
		int nTotalStep);

	virtual void OnStop();

protected:
	BOOL mEffectStarted;
	BOOL mReverse;

	IE2DEffectListener *mpEffectListener;
	UINT64 mUserData;
	UINT64 mSlideMS;

	int  mSlideCurrentStep;
	int  mSlideTotalSteps;
};
