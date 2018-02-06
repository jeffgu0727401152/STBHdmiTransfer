/*
 * PlayerCmdServer.h
 *
 *  Created on: 2013-1-18
 *      Author: kyo
 */

#pragma once

#include "TCPSocketServer.h"
#include "NetFileStruct.h"

typedef struct tagCLIENTOPENFILEINFO
{
	int nSocketFD;
	FILE* fpOpen;
} CLIENTOPENFILEINFO;

class CSocketFileServer : public CTCPSocketServer,
	public IServerSocketListener
{
	typedef CTCPSocketServer CParentClass;

public:
	CSocketFileServer();
	virtual ~CSocketFileServer();

public:
	BOOL Create(
		UINT16 uServerPort,
		BOOL bLocalSocket,
		const char* cSocketThreadName);

	void SetDataFolder(
		SERVER_FOLDER_TYPE eFolderType,
		const char* cFolderPath);

	// interface:
public:
	virtual void OnServerReceiveData(
		UINT64 uUserData,
		int nSocketFD,
		const void *pBuffer,
		int nBufLen);

	virtual void OnServerCloseClient(
		UINT64 uUserData,
		int nSocketFD);

private:
	void OnRequestDataFolder(
		int nSocketFD,
		NETFILEREQDATAFOLDER *pReqDataFolderParam);
	void OnRequestOpen(
		int nSocketFD,
		NETFILEREQOPEN *pReqOpenParam);
	void OnRequestClose(
		int nSocketFD,
		NETFILEREQCLOSE *pReqCloseParam);
	void OnRequestDelete(
		int nSocketFD,
		NETFILEREQDELETE *pReqDeleteParam);
	void OnRequestRename(
		int nSocketFD,
		NETFILEREQRENAME *pReqRenameParam);
	void OnRequestGetMD5(
		int nSocketFD,
		NETFILEREQGETMD5 *pReqGetMD5Param);
	void OnRequestGetSize(
		int nSocketFD,
		NETFILEREQGETSIZE *pReqGetSizeParam);
	void OnRequestRead(
		int nSocketFD,
		NETFILEREQREAD *pReqReadParam);
	void OnRequestWrite(
		int nSocketFD,
		NETFILEREQWRITE *pReqWriteParam);
	void OnRequestGetFolderList(
		int nSocketFD,
		NETFILEREQGETFOLDERLIST *pReqGetFolderListParam);
	void OnRequestMakeDirectory(
		int nSocketFD,
		NETFILEREQMKDIR *pReqMakeDirectoryParam);
	void OnRequestRemoveDirectory(
		int nSocketFD,
		NETFILEREQRMDIR *pReqRemoveDirectoryParam);

private:
	void AddClientOpenFileToList(
		int nSocketFD,
		FILE* fpOpen);
	void DelClientOpenFileFromList(
		int nSocketFD,
		FILE* fpOpen);
	void CloseAllClientOpenFile(
		int nSocketFD);
	CBaseLock mClientOpenFileListLock;
	CPtrListCtrl mClientOpenFileList;

private:
	char mFolderPath[SERVER_FOLDER_TYPE_COUNT][MAX_PATH];
};
