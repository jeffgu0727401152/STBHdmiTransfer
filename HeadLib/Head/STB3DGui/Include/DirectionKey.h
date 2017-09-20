#pragma once

#include "types.h"
#include "MsgQueue.h"
#include "IInputManager.h"

class CDirectionKey : public IMessageOwner
{
public:
	CDirectionKey(
		IInputManager *pInputManager);
	virtual ~CDirectionKey();

	// interface
public:
	virtual void OnMsg(
		UINT32 uType,
		UINT64 wParam,
		UINT64 lParam);

public:
	void StartDevice();
	void StopDevice();

	BOOL IsDirectionKey(
		int nKeyValue);
	BOOL OnDirectionKey(
		BOOL bPressed,
		int nKeyValue);

private:
	void StartMove(
		int nKeyValue);
	void StopMove();

private:
	IInputManager *mpInputManager;

	int mCurScale;
	int mCurPressedKey;
	UINT64 mPressedTime;
};
