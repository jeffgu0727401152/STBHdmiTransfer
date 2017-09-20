#pragma once

#include "PtrControl.h"
#include "SimpleString.h"
#include "types.h"

#ifdef _WIN32
#define DIRECTORY_SEPERATE_CHAR '\\'
#else
#define DIRECTORY_SEPERATE_CHAR '/'
#define MAX_PATH 1024
#endif

#ifdef __MACH__
#define ftello64 ftell
#define fseeko64 fseek
#endif

// dir name list
// cFileTypes SHOULD Seperator by ';'
void GetLocalFolderFileList(
	const char *cFolder,
	CPtrCtrl *pFolderList,
	CPtrCtrl *pArcList,
	const char* cFileTypes,
	BOOL bIncludeHide);

// all(include sub-directory) file list, file name relative to cFolder
// cChildFolder: special subfolder, null to get all subfolder
// cFileTypes SHOULD Seperator by ';'
void GetSubFolderFileList(
	const char *cFolderName,
	const char *cSubFolderName,
	CPtrCtrl *pArcList,
	const char* cFileTypes,
	BOOL bIncludeHide,
	BOOL bRecursive);
void FreeFileList(
	CPtrCtrl *pList);

BOOL FindFileInFolder(
	const char *cFolder,
	const char* cFileName,
	BOOL bIncludeHide);

// all(include sub-directory) file list, file name relative to cFolder
// cChildFolder: special subfolder, null to get all subfolder
BOOL FindFileInSubFolder(
	const char *cFolderName,
	const char *cSubFolderName,
	const char* cFileName,
	BOOL bIncludeHide,
	BOOL bRecursive,
	char *cExistSubFolderName);

char* GetProgramName(
	char *buf,
	int count);
char* GetProgramPath(
	char *buf,
	int count);
void FixToPathName(
	char *cPath);
void FixToFileName(
	char *cFile);
BOOL CombinePathName(
	char *cFullName,
	const char *cPath,
	const char *cShortName);
BOOL GetFileParentDir(
	char *cFileParentDir,
	const char *cSrcFileName);
BOOL GetFileShortName(
	char *cFileShortName,
	const char *cSrcFileName);

void SetFileExtName(
	char *cFileName,
	const char *cExtName);

BOOL IsDir(
	const char *cFileName);

BOOL IsFileExist(
	const char *cFileName);

// cExtName : not contain dot, such as "txt" ;
void GetFileNameByNumberA(
	char *cFileName,
	const char *cExtName,
	const char *cBaseText="Temp_",
	int nNumber=0);

void GetFileNameByDateA(
	char *cFileName,
	const char *cExtName,
	const char *cBaseText="Temp_",
	const struct tm *pst=NULL,
	BOOL bIncludeYMD=FALSE,
	BOOL bIncludeMS=FALSE);

// cExtName : not contain dot, such as "txt" ;
void GetFileNameByRandomA(
	char *cFileName,
	const char *cExtName,
	const char *cBaseText="Temp_",
	int nFileNameLen=10);

UINT64 FileSize(
	FILE *fp);
size_t FileRead(
	FILE *fp,
	void *pBuf,
	size_t nSize);
size_t FileWrite(
	FILE *fp,
	const void *pBuf,
	size_t nSize);

UINT64 ReadFileData(
	const char* cFileName,
	BYTE **ppDataBuf);
void WriteFileData(
	const char* cFileName,
	const void *pDataBuf,
	size_t nDataLen,
	BOOL bAppend);
void ReleaseFileData(
	BYTE *pDataBuf);

BOOL IsFileDataEqual(
	const char* cFileName1,
	const char* cFileName2);

BOOL GetDiskFreeSpaceEx(
	const char* lpDirectoryName,
	UINT64 *lpFreeBytesAvailable,
	UINT64 *lpTotalNumberOfBytes,
	UINT64 *lpTotalNumberOfFreeBytes);

//转换文件大小格式
void FormatFileSize(
	UINT64 uSize,
	CSimpleStringA *pSizeString);

class IFileCopyProgressListener
{
public:
	virtual ~IFileCopyProgressListener(void) {}

	virtual void OnFileCopyProgress(
		UINT64 uUserData,
		UINT64 uHasCopySize,
		UINT64 uNeedCopySize)=0;
};

BOOL CopyFile(
	const char* cSrcFileName,
	const char* cDstFileName,
	IFileCopyProgressListener *pListener,
	UINT64 uUserData);

BOOL MoveFile(
	const char* cSrcFileName,
	const char* cDstFileName);

int do_mkdir(
	const char *path,
	mode_t mode);

// cFileTypes SHOULD Seperator by ';'
void RemoveFile(
	const char *cFolderName,
	const char* cFileTypes,
	BOOL bRemoveFolder,
	BOOL bRecursive);
