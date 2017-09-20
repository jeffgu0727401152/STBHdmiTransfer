#pragma once

#include "types.h"

void WavProcess_Merge2ChannelsTo1Channel_16S(
	const short *c2ChannelBuffer,
	short *c1ChannelBuffer,
	int nSampleCount);
void WavProcess_Cut2ChannelsTo1Channel_16S(
	const short *c2ChannelBuffer,
	short *c1ChannelBuffer,
	int nSampleCount,
	BOOL bCutLeft);


// 前端至少预留4个sample，用来判断双突刺
#define HEAD_RESERVE_COUNT 4
// 末尾至少预留4个sample，用来判断双突刺
#define END_RESERVE_COUNT 4
// SHOCK_WINDOW_SIZE >= (HEAD_RESERVE_COUNT+END_RESERVE_COUNT+1)
#define SHOCK_WINDOW_SIZE 480


// 目前发现的突刺有如下几个特点
// 1. 同一个sample中，左右声道都有突刺
// 2. 同一个sample中，单一声道都有突刺
// 3. 相邻两个sample中，左右声道都有突刺 (双突刺)
// 4. 相邻两个sample中，单一声道都有突刺
// 突刺双向都有可能
// 单突刺
//            *                                          *   *                        **
//  *****  *******  *************  *   ************    ****
//                            *
//        单突刺      反向突刺              双突刺                     双突刺
//

class CWaveShockProcess
{
public:
	CWaveShockProcess();
	virtual ~CWaveShockProcess();

public:
	void Reset();

	int SkipShock(
		short *pInputSample,
		short *pOutputSample,
		int nSampleCount,
		int *pnProcessedSampleCount,
		int *pnShockSampleCount);
	int SmoothShock(
		short *pInOutSample,
		int nSampleCount,
		int *pnProcessedSampleCount,
		int *pnShockSampleCount);
	int DetectShock(
		short *pInputSample,
		int nSampleCount,
		int *pnProcessedSampleCount,
		int *pnShockSampleCount);

	int GetTotalProcessedSampleCount();
	int GetTotalOutputSampleCount();
	int GetTotalShockSampleCount();

private:
	void IsShockSample(
		short *pSamples,
		int *pnLeftShock,
		int *pnRightShock,
		int bStrictMode);

	void GetSampleShockType(
		short curSample,
		short prepreSample,
		short preSample,
		short nextSample,
		short nextnextSample,
		int *pnPreVeryLikeShock,
		int *pnNextVeryLikeShock,
		int bStrictMode);

private:
	int mTotalInputSampleCount;
	int mTotalOutputSampleCount;
	int mTotalShockSampleCount;

};
