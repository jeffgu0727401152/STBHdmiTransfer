#pragma once

#include "types.h"
#include "commfunc.h"
#include "PtrControl.h"
#include "FileOperator.h"
#include "Buffer.h"

// resource 结构

/* resource file header
     tag: 16 bytes
     encrypt: sizeof(BOOL)
     resource time start: sizeof(SYSTEMTIME)
     resource time end: sizeof(SYSTEMTIME)
     used limit time: seconds, 0: forever,
     item data crc: sizeof(UINT32)
     item count: sizeof(int)
     item data length: sizeof(int)
     item data enc ength: sizeof(int)
*/


typedef enum eRESOURCETYPE
{
	restype_image=0,
	restype_xml,
	restype_raw,
} RESOURCETYPE;

typedef struct tagRESOURCEITEMDATA
{
	RESOURCETYPE eItemType;
	char cItemName[MAX_PATH];
	CBuffer sBuffer;
} RESOURCEITEMDATA;

class IResourceLoadListener
{
public:
	virtual ~IResourceLoadListener(void) {}

	virtual void OnItemLoad(
		UINT64 uUserData,
		RESOURCETYPE itemtype,
		const char* cItemName,
		const BYTE *pBuffer,
		int nBufLen)=0;
};

class CResComposer
{
public:
	CResComposer();
	virtual ~CResComposer();

public:
	void SaveResourceFromBuffer(
		RESOURCETYPE eItemType,
		const char *cItemName,
		int nDataLen,
		const BYTE *pDataBuf);

	void SaveResourceFromFile(
		RESOURCETYPE eItemType,
		const char *cFileName,
		const char *cItemName);

	void GetLimitStartEndTime(
		SYSTEMTIME* pStart,
		SYSTEMTIME* pEnd);

	// 单次使用时间
	UINT64 GetLimitTime(void);

public:
	// device id should be <= 32 length
	BOOL LoadResource(
		const char* cResourceFile,
		const BYTE* pResKey,
		int nKeyLength,
		IResourceLoadListener* pLoadItemListener,
		UINT64 uUserData);
	void FreeAllItem();

	BOOL DetectResourceKey(
		const char* cResourceFile,
		const BYTE* pResKey,
		int nKeyLength);
	void ChangeResourceKey(
		const char* cResourceFile,
		const BYTE* pOldResKey,
		int nOldKeyLength,
		const BYTE* pNewResKey,
		int nNewKeyLength);

	void SaveResource(
		const char* cResourceFile,
		SYSTEMTIME* pLimitStart,
		SYSTEMTIME* pLimitEnd,
		UINT64 uLimitSeconds,
		const BYTE* pResKey,
		int nKeyLength);

private:
	int CollectItemData(
		BYTE **ppDataBuf);
	void ParseItemData(
		int nItemCount,
		const BYTE *pDataBuf,
		int nDataLen,
		IResourceLoadListener* pResourceListener,
		UINT64 uUserData);

private:
	BYTE mResourceTag[16];

	SYSTEMTIME mLimitStart;
	SYSTEMTIME mLimitEnd;
	UINT64 mLimitSeconds;

	CPtrArrayCtrl mItemDataList;
	BYTE *mpResourceBuf;
};
