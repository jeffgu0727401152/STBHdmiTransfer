#pragma once

#include "types.h"

class CWavFile
{
public:
	CWavFile();
	virtual ~CWavFile();

	BOOL Open(
		const char *cFileName,
		int nSampleRate,
		int nBitDepth,
		int nChannels);
	void Write(
		const BYTE *pData,
		int nSize);
	void Close(void);

private:
	int mSampleRate;
	int mBitDepth;
	int mChannels;
	FILE *mRecordFile;
};

void WavProcess_Merge2ChannelsTo1Channel_16S(
	const short *c2ChannelBuffer,
	short *c1ChannelBuffer,
	int nSampleCount);
void WavProcess_Cut2ChannelsTo1Channel_16S(
	const short *c2ChannelBuffer,
	short *c1ChannelBuffer,
	int nSampleCount,
	BOOL bCutLeft);
