#pragma once

#include "IInputManager.h"
#include "BaseThread.h"

class CMonkeyDevice : CBaseThread,
	public IThreadFuncInterface
{
public:
	CMonkeyDevice(
		IInputManager *pInputManager);
	virtual ~CMonkeyDevice();

	// interface
public:
	virtual BOOL ThreadLoop(
		UINT64 uThreadData);

public:
	void SetMonkeyParam(
		UINT64 uInterval);
	void StartDevice();
	void StopDevice();

private:
	void GetStartPointFromRandomWnd(
		POINT *pt);
	void GenerateClickEvent(
		int xPos,
		int yPos);
	void GenerateDragEvent(
		int xStartPos,
		int yStartPos,
		int xEndPos,
		int yEndPos,
		int nDragTime);

private:
	IInputManager *mpInputManager;

	UINT64 mMonkeyInterval;
	POINT mWndPoint;
	int mStartPosX;
	int mStartPosY;
	int mEndPosX;
	int mEndPosY;
};
