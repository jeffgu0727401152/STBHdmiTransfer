/*
 * PlayerCmdServer.h
 *
 *  Created on: 2013-1-18
 *      Author: kyo
 */
#pragma once

#include "TCPSocketClient.h"
#include "NetFileStruct.h"

typedef struct tagNETFILEREQWITHEVENT
{
	int nRequestID;
	CBaseEvent complete;
} NETFILEREQWITHEVENT;

class CSocketFileClient : public CTCPSocketClient,
	public IClientSocketListener
{
	typedef CTCPSocketClient CParentClass;

public:
	CSocketFileClient();
	virtual ~CSocketFileClient();

public:
	BOOL Create(
		const char *cServerAddr,
		UINT16 uPort,
		BOOL bLocalSocket,
		const char* cSocketThreadName);

	// interface:
public:
	virtual void OnClientReceiveTCPData(
		UINT64 uUserData,
		int nSocketFD,
		const void *pBuffer,
		int nBufLen);

	virtual void OnClientDisconnectFromServer(
		UINT64 uUserData,
		int nSocketFD);

public:
	void GetDataFolder(
		SERVER_FOLDER_TYPE eFolderType,
		char cFolderPath[MAX_PATH]);

	BOOL OpenFile(
		const char *cFileName,
		const char *cMode);
	BOOL CloseFile();

	BOOL GetFileMD5(
		const char *cFileName,
		BYTE pMD5Value[16]);

	UINT64 GetFileSize();
	UINT32 ReadFile(
		UINT64 ulPos,
		void *pBuffer,
		UINT32 uSize,
		UINT64 uTimeout);
	void LimitReadSpeed(
		UINT64 uBytesPerSecond);

	BOOL DeleteFile(
		const char *cFileName);
	BOOL RenameFile(
		const char *cOldFileName,
		const char *cNewFileName);
	UINT32 WriteFile(
		UINT64 ulPos,
		void *pBuffer,
		UINT32 uSize,
		UINT64 uTimeout);
	void LimitWriteSpeed(
		UINT64 uBytesPerSecond);

	// foler/file string are seperated by '/'
	void GetFolderList(
		const char* cFolderName,
		CSimpleStringA *pChildFolderString,
		CSimpleStringA *pChildFileString);

	BOOL MakeDirectory(
		const char* cFolderName,
		mode_t mode);
	BOOL RemoveDirectory(
		const char* cFolderName);

private:
	void OnResponseGetDataFolder(
		NETFILERESDATAFOLDER *pResDataFolderParam);
	void OnResponseGetMD5(
		NETFILERESGETMD5 *pResGetMD5Param);
	void OnResponseOpen(
		NETFILERESOPEN *pResOpenParam);
	void OnResponseClose(
		NETFILERESCLOSE *pResCloseParam);
	void OnResponseDelete(
		NETFILERESDELETE *pResDeleteParam);
	void OnResponseRename(
		NETFILERESRENAME *pResRenameParam);
	void OnResponseGetSize(
		NETFILERESGETSIZE *pResGetSizeParam);
	void OnResponseRead(
		NETFILERESREAD *pResReadParam);
	void OnResponseWrite(
		NETFILERESWRITE *pResWriteParam);
	void OnResponseGetFolderList(
		NETFILERESGETFOLDERLIST *pResGetFolderListParam);
	void OnResponseMakeDirectory(
		NETFILERESMKDIR *pResMakeDirectoryParam);
	void OnResponseRemoveDirectory(
		NETFILERESRMDIR *pResRemoveDirectoryParam);

private:
	UINT64 mNetFileFD;

	CBaseLock mRequestWithEventListLock;
	// NETFILEREQWITHEVENT
	CPtrListCtrl mRequestWithEventList;

	int mRequestID;

	UINT64 mLmitReadSpeedBPS;
	UINT64 mLmitWriteSpeedBPS;
};


BOOL SocketFileCopyFromServer(
	CSocketFileClient *pSocketFileClient,
	const char *cNetFile,
	const char *cLocalFile,
	UINT64 uTimeout,
	INetFileCopyProgressListener *pListener,
	UINT64 uUserData);

BOOL SocketFileCopyToServer(
	CSocketFileClient *pSocketFileClient,
	const char *cLocalFile,
	const char *cNetFile,
	UINT64 uTimeout,
	INetFileCopyProgressListener *pListener,
	UINT64 uUserData);

// NOTE, child files & folders in cNetFolder directory will download from cLocalFolder directory
void SocketFolderCopyFromServer(
	CSocketFileClient *pSocketFileClient,
	const char *cNetFolder,
	const char *cLocalFolder,
	UINT64 uTimeout,
	INetFolderCopyProgressListener *pListener,
	UINT64 uUserData);

// NOTE, child files & folders in cLocalFolder directory will upload to cNetFolder directory
void SocketFolderCopyToServer(
	CSocketFileClient *pSocketFileClient,
	const char *cLocalFolder,
	const char *cNetFolder,
	UINT64 uTimeout,
	INetFolderCopyProgressListener *pListener,
	UINT64 uUserData);
