/*
 * NetFileStruct.h
 *
 *  Created on: 2013-3-26
 *      Author: kyo
 */

#ifndef NETFILESTRUCT_H_
#define NETFILESTRUCT_H_

#include "FileOperator.h"

#define NETFILE_BUFFER_LENGTH	(SIZE_1K*512)

#define NETFILE_VER	(int)0x10000003

class INetFileCopyProgressListener
{
public:
	virtual ~INetFileCopyProgressListener(void) {}

	// fCurSpeedKBPS: K-Bytes per second
	virtual void OnNetFileCopyProgress(
		UINT64 uUserData,
		UINT64 uHasCopySize,
		UINT64 uNeedCopySize,
		float fCurSpeedKBPS,
		UINT64 *puLimitSpeedBPS)=0;
};

class INetFolderCopyProgressListener : public INetFileCopyProgressListener
{
public:
	virtual ~INetFolderCopyProgressListener(void) {}

	virtual void OnNetFolderCreate(
		UINT64 uUserData,
		const char* cFolderName)=0;
	virtual void OnNetFileCopyStart(
		UINT64 uUserData,
		const char* cNetFileName,
		const char* cLocalFileName)=0;
};

#pragma pack(push)
#pragma pack(1)

typedef struct tagNETFILEHEADER
{
	int nNetFileVer;
	int nRequestID;
	int nCommandType;
	UINT64 uPrivData;
} NETFILEHEADER;

typedef enum eSERVER_FOLDER_TYPE
{
	SERVER_FOLDER_TYPE_DATAFOLDER=0,
	SERVER_FOLDER_TYPE_PRIVATE,
	SERVER_FOLDER_TYPE_TEMP,
	SERVER_FOLDER_TYPE_UDISK,
	SERVER_FOLDER_TYPE_UDISKSONG,
	SERVER_FOLDER_TYPE_CLOUDSONG,
	SERVER_FOLDER_TYPE_MEDIASONG,
	SERVER_FOLDER_TYPE_COUNT
}SERVER_FOLDER_TYPE;

// GET DATAFOLDER
#define NETFILE_REQ_DATAFOLDER	1
#define NETFILE_RES_DATAFOLDER	2
typedef struct tagNETFILEREQDATAFOLDER : public NETFILEHEADER
{
	SERVER_FOLDER_TYPE eFolderType;
} NETFILEREQDATAFOLDER;
typedef struct tagNETFILERESDATAFOLDER : public NETFILEHEADER
{
	char cFolderPath[MAX_PATH];
} NETFILERESDATAFOLDER;

// OPEN
#define NETFILE_REQ_OPEN	3
#define NETFILE_RES_OPEN	4
typedef struct tagNETFILEREQOPEN : public NETFILEHEADER
{
	char cFileName[MAX_PATH];
	char cMode[16];
} NETFILEREQOPEN;
typedef struct tagNETFILERESOPEN : public NETFILEHEADER
{
	UINT64 fp;
} NETFILERESOPEN;

// CLOSE
#define NETFILE_REQ_CLOSE	5
#define NETFILE_RES_CLOSE	6
typedef struct tagNETFILEREQCLOSE : public NETFILEHEADER
{
	UINT64 fp;
} NETFILEREQCLOSE;
typedef struct tagNETFILERESCLOSE : public NETFILEHEADER
{
	BOOL bClosed;
} NETFILERESCLOSE;

// DELETE
#define NETFILE_REQ_DELETE	7
#define NETFILE_RES_DELETE	8
typedef struct tagNETFILEREQDELETE : public NETFILEHEADER
{
	char cFileName[MAX_PATH];
} NETFILEREQDELETE;
typedef struct tagNETFILERESDELETE : public NETFILEHEADER
{
	BOOL bDeleted;
} NETFILERESDELETE;

// RENAME
#define NETFILE_REQ_RENAME	9
#define NETFILE_RES_RENAME	10
typedef struct tagNETFILEREQRENAME : public NETFILEHEADER
{
	char cOldFileName[MAX_PATH];
	char cNewFileName[MAX_PATH];
} NETFILEREQRENAME;
typedef struct tagNETFILERESRENAME : public NETFILEHEADER
{
	BOOL bRenamed;
} NETFILERESRENAME;

// Get SIZE
#define NETFILE_REQ_GETSIZE	11
#define NETFILE_RES_GETSIZE	12
typedef struct tagNETFILEREQGETSIZE : public NETFILEHEADER
{
	UINT64 fp;
} NETFILEREQGETSIZE;
typedef struct tagNETFILERESGETSIZE : public NETFILEHEADER
{
	UINT64 uSize;
} NETFILERESGETSIZE;

// READ
#define NETFILE_REQ_READ	13
#define NETFILE_RES_READ	14
typedef struct tagNETFILEREQREAD : public NETFILEHEADER
{
	UINT64 fp;
	UINT64 ulPos;
	UINT32 uSize;
} NETFILEREQREAD;
typedef struct tagNETFILERESREAD : public NETFILEHEADER
{
	UINT32 uSize;
} NETFILERESREAD;

// WRITE
#define NETFILE_REQ_WRITE	15
#define NETFILE_RES_WRITE	16
typedef struct tagNETFILEREQWRITE : public NETFILEHEADER
{
	UINT64 fp;
	UINT64 ulPos;
	UINT64 uSize;
} NETFILEREQWRITE;
typedef struct tagNETFILERESWRITE : public NETFILEHEADER
{
	UINT32 uSize;
} NETFILERESWRITE;

// GET MD5
#define NETFILE_REQ_GETMD5	17
#define NETFILE_RES_GETMD5	18
typedef struct tagNETFILEREQGETMD5 : public NETFILEHEADER
{
	char cFileName[MAX_PATH];
} NETFILEREQGETMD5;
typedef struct tagNETFILERESGETMD5 : public NETFILEHEADER
{
	BYTE pMD5Value[16];
} NETFILERESGETMD5;

// GET FOLDER LIST
#define NETFILE_REQ_GETFOLDERLIST	19
#define NETFILE_RES_GETFOLDERLIST	20
typedef struct tagNETFILEREQGETFOLDERLIST : public NETFILEHEADER
{
	char cFolderName[MAX_PATH];
} NETFILEREQGETFOLDERLIST;
typedef struct tagNETFILERESGETFOLDERLIST : public NETFILEHEADER
{
	int nChildFolderDataSize;
	int nChildFileDataSize;
} NETFILERESGETFOLDERLIST;

// MAKE DIRECTORY
#define NETFILE_REQ_MKDIR	21
#define NETFILE_RES_MKDIR	22
typedef struct tagNETFILEREQMKDIR : public NETFILEHEADER
{
	char cFolderName[MAX_PATH];
	mode_t mode;
} NETFILEREQMKDIR;
typedef struct tagNETFILERESMKDIR : public NETFILEHEADER
{
	BOOL bMakeSuccess;
} NETFILERESMKDIR;

// MAKE DIRECTORY
#define NETFILE_REQ_RMDIR	23
#define NETFILE_RES_RMDIR	24
typedef struct tagNETFILEREQRMDIR : public NETFILEHEADER
{
	char cFolderName[MAX_PATH];
} NETFILEREQRMDIR;
typedef struct tagNETFILERESRMDIR : public NETFILEHEADER
{
	BOOL bRemoveSuccess;
} NETFILERESRMDIR;

#pragma pack(pop)

#endif /* NETFILESTRUCT_H_ */
