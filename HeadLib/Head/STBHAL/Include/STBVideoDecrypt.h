#pragma once

#include "types.h"

// ENCTYPE AAAA 加密类型：尾部20个字节为密码保存区域，
// 其中，0~3:AAAA，4~19:与文件尾16个字节异或结果
//
// ENCTYPE BBBB 加密类型：尾部36个字节为密码保存区域，
// 其中，0~15:OEMID, 16~19:BBBB, 20~35:与文件尾16个字节异或结果

typedef enum eSTBENCRYPTTYPE
{
	STBENCRYPTTYPE_NONE=0,
	STBENCRYPTTYPE_AAAA,
	STBENCRYPTTYPE_BBBB
} STBENCRYPTTYPE;

class CSTBVideoDecrypt
{
public:
	CSTBVideoDecrypt();
	virtual ~CSTBVideoDecrypt();

public:
	 void ResetEncryptType();
	 void DetectLocalFileEncryptType(
		const char* cFileName,
		const char* cOEMID);
	 void DetectHttpFileEncryptType(
		const char* cHttpUrl,
		const char* cOEMID);
	 void DetectBufferEncryptType(
		const BYTE pFileEndData[4096],
		const char* cOEMID);
	 STBENCRYPTTYPE GetEncryptType();

	 size_t DecryptBuffer(
		BYTE* pInOutBuf,
		size_t nBufSize,
		UINT64 uBufStartPos);

private:
	 size_t DecryptVideoBuffer(
		BYTE* pInOutBuf,
		size_t nBufSize,
		UINT64 uBufStartPos);

private:
	 STBENCRYPTTYPE mEncryptType;
	 BYTE mEncTypePassword[16];
};

void DecryptSTBVideoFile(
	const char* cInputFileName,
	const char* cOutputFileName,
	const char* cOEMID);
