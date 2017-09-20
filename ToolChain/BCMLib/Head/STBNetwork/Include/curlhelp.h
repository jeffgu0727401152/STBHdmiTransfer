#pragma once

#include "types.h"
#include "SimpleString.h"
#include "Buffer.h"
#include "curl/curl.h"

typedef struct tagHTTPFILEINFO
{
	CURL* pCURL;
	CSimpleStringA sURL;
	BOOL bUseProxy;
	UINT64 uFileSize;
} HTTPFILEINFO;

class IHttpDataCallback
{
public:
	virtual ~IHttpDataCallback(void) {}

	virtual UINT32 OnHttpDataRecvCallback(
		const BYTE *pHttpData,
		UINT32 uDataSize,
		UINT64 uUserData)=0;

	virtual int OnHttpDataProgressCallback(
		UINT64 uUserData)=0;
};

// "192.168.56.30:80"
void SetCurlProxy(
	const char* cProxy,
	const char* cProxyUsername,
	const char* cProxyPassword,
	const char* cProxyType);

BOOL OpenHttpFile(
	const char* cURL,
	HTTPFILEINFO *pHttpFileInfo);
void CloseHttpFile(
	HTTPFILEINFO *pHttpFileInfo);

UINT32 ReadHttpBody(
	HTTPFILEINFO *pHttpFileInfo,
	UINT64 ulPos,
	void *pBuffer,
	UINT32 uSize,
	UINT64 uTimeout,
	BOOL *pbStop,
	BOOL *pbTimeout);

void ReadHttpBodyWithCustomCallback(
	HTTPFILEINFO *pHttpFileInfo,
	UINT64 ulStartPos,
	UINT64 ulEndPos,
	IHttpDataCallback *pCallback,
	UINT64 uUserData);

double GetHttpDownloadSpeedBPS(
	CURL *pCURL);

BOOL GetHttpFileMD5(
	const char* cURL,
	BYTE pHasMD5Value[16]);

BOOL PerformHttpGetCommand(
	const char* cURL,
	const char* cToken,
	BYTE *pResultBuffer,
	UINT32 uResultBufferSize,
	UINT32 *pActualResultSize);

BOOL PerformHttpPostCommand(
	const char* cURL,
	const char* cToken,
	CBuffer *pPostBuffer,
	BYTE *pResultBuffer,
	UINT32 uResultBufferSize,
	UINT32 *pActualResultSize);
