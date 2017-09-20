#pragma once

#include "types.h"
#include "PtrControl.h"

BOOL LoadJpegImgFromFile(
	const char* cFileName,
	int* pWidth,
	int* pHeight,
	int* pBytePerPixel,
	BYTE** ppImageData);
BOOL LoadJpegImgFromData(
	const BYTE* pJpgBuffer,
	int nBufLen,
	int* pWidth,
	int* pHeight,
	int* pBytePerPixel,
	BYTE** ppImgData);
BOOL SaveRGB24ToJpegImg(
	const char* cFileName,
	const BYTE* pImgData,
	int nWidth,
	int nHeight,
	int nQuality);

BOOL LoadPngImgFromFile(
	const char* cFileName,
	int* pWidth,
	int* pHeight,
	int* pBytePerPixel,
	BYTE** ppImageData);
BOOL LoadPngImgFromData(
	const BYTE* pPngBuffer,
	int nBufLen,
	int* pWidth,
	int* pHeight,
	int* pBytePerPixel,
	BYTE** ppImgData);
BOOL SaveRGB24ToPngImg(
	const char* cFileName,
	const BYTE* pImgData,
	int nWidth,
	int nHeight);
BOOL SaveRGB32ToPngImg(
	const char* cFileName,
	const BYTE* pImgData,
	int nWidth,
	int nHeight);

int CompressBuffer(
	const BYTE* pInputBuffer,
	unsigned long nInputSize,
	BYTE* pOutputBuffer,
	unsigned long nOutputSize);
int DecompressBuffer(
	const BYTE* pInputBuffer,
	unsigned long nInputSize,
	BYTE* pOutputBuffer,
	unsigned long nOutputSize);
void CompressFile(
	const char* cInputFileName,
	const char* cOutputFileName);
void DecompressFile(
	const char* cInputFileName,
	const char* cOutputFileName);
void CompressFileListCustom(
	const char* cOutputFileName,
	CPtrCtrl *pInputFileList);
void CompressFolderCustom(
	const char* cInputFolderName,
	const char* cOutputFileName);
void DecompressFolderCustom(
	const char* cInputFileName,
	const char* cOutputFolderName);
void CompressFolderAsZip(
	const char* cInputFolderName,
	const char* cOutputFileName);
void DecompressFolderAsZip(
	const char* cInputFileName,
	const char* cOutputFolderName);

// DO NOT free ppImageData, this is just a copy of pointer
BOOL LoadFromMemData(
	int nDataLen,
	const BYTE *pDataBuf,
	int* pWidth,
	int* pHeight,
	int* pBytePerPixel,
	BYTE** ppImageData);
BOOL SaveMemImageToFile(
	const char *cImageFileName,
	int nWidth,
	int nHeight,
	int nBytesPerPixel,
	const BYTE *pImageData);
BOOL LoadImageFile(
	const char* cFileName,
	int* pWidth,
	int* pHeight,
	int* pBytePerPixel,
	BYTE** ppImageData);
BOOL LoadImageData(
	const BYTE* pImageBuffer,
	int nBufLen,
	int* pWidth,
	int* pHeight,
	int* pBytePerPixel,
	BYTE** ppImageData);

BOOL LoadCompressIamge(
	const char* cImageFileName,
	int* pWidth,
	int* pHeight,
	int* pBytePerPixel,
	BYTE** ppImageData);
BOOL SaveCompressIamge(
	const char* cImageFileName,
	int nWidth,
	int nHeight,
	int nBytesPerPixel,
	const BYTE *pImageData);

void FreeImageData(
	BYTE *pImageData);
