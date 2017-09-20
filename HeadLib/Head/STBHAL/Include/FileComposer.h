#pragma once

#include "Buffer.h"
#include "PtrControl.h"
#include "HashTable.h"
#include "FileOperator.h"
#include "BaseLock.h"

typedef struct tagCOMPOSEFILEINFO
{
	UINT32 uFileNameLen;
	char *cFileName;
	UINT32 uDataLen;
	UINT32 uFileDataPos;
} COMPOSEFILEINFO;

class CFileComposer
{
public:
	CFileComposer();
	virtual ~CFileComposer();

public:
	void LoadComposeFile(
		const char* cComposeFileName,
		BOOL *pbCancel);
	void UnloadComposeFile();

	void SeperateToFolder(
		const char* cOutputFolder);

	int LoadOneFromFile(
		const char* cFileName,
		BYTE** ppFileBuffer);
	static void ReleaseFileBuffer(
		BYTE *pFileBuffer)
	{
		if (pFileBuffer)
		{
			delete []pFileBuffer;
		}
	}

private:
	CBaseLock mComposeFileOperatorLock;
	CPtrArrayCtrl mComposeFileInfoList;
	CCRCHashTable mComposeFileInfoHashTable;
	FILE *mpComposeFile;
};

void ComposeToFile(
	const char* cComposePath,
	const char* cOutputFileName);
void SeperateToFolder(
	const char* cComposeFile,
	const char* cOutputFolder);
