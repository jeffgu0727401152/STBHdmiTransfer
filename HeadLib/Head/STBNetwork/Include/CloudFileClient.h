/*
 * PlayerCmdServer.h
 *
 *  Created on: 2013-1-18
 *      Author: kyo
 */
#pragma once

#include "HttpFileClient.h"

typedef enum eCLOUDFILETYPE
{
	// 获取数据库信息
	CloudFile_GetDatabase,
	// 获取系统信息
	CloudFile_GetAppPackage,
	// 获取手机版本信息
	CloudFile_GetApkPackage,
	// 获取特定文件
	CloudFile_GetAppFile,
	// 获取特定歌曲
	CloudFile_GetMediaFile
} CLOUDFILETYPE;

void SetCloudServerInfo(
	const char* cServerAddr,
	UINT16 uServerPort);

void SetCloudClientVersion(
	const char* cProductVer,
	const char* cSongVer,
	const char* cDeviceID);

void GetCloudVersions(
	CSimpleStringA* pDBVer,
	CSimpleStringA* pAppVer,
	CSimpleStringA* pApkVer);

void GetCloudOEMID(
	CSimpleStringA* pOEMID);

// return value: TRUE=>cloud server can connect, FALSE=>cloud server cannot connect
// pLicenseInfo: License info for client device ID
BOOL GetCloudState(
	CSimpleStringA* pLicenseInfo);

BOOL IsSongHasDownloadLicense(
	const char* cSongID,
	CSimpleStringA* pLicenseInfo);

BOOL IsSongHasPlayLicense(
	const char* cSongID,
	CSimpleStringA* pLicenseInfo);

void GetCloudPlayFileURL(
	const char* cSongID,
	CSimpleStringA *pURL);

class CCloudFileClient : public CHttpFileClient
{
	typedef CHttpFileClient CParentClass;

public:
	CCloudFileClient();
	virtual ~CCloudFileClient();

public:
	BOOL OpenCloudFile(
		CLOUDFILETYPE eCloudFileType,
		const char *cFileName,
		BOOL bCheckMD5);

	BOOL GetFileMD5(
		BYTE pMD5Value[16]);

	void GetCloudFileURL(
		CSimpleStringA *pURL);

private:
	BOOL mHasMD5Value;
	BYTE mMD5Value[16];

	CSimpleStringA mFileURL;
};

BOOL CloudFileCopyFromServer(
	CCloudFileClient *pCloudFileClient,
	CLOUDFILETYPE eCloudFileType,
	const char *cNetFile,
	const char *cLocalFile,
	UINT64 uTimeout,
	INetFileCopyProgressListener *pListener,
	UINT64 uUserData);
