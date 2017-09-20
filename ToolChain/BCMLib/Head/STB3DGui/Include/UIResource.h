#pragma once

#include "ResComposer.h"
#include "Texture.h"
#include "ImageBuffer.h"
#include "HashTable.h"

typedef struct tagUIRESITEM
{
	RESOURCETYPE eItemType;
	CImageBuffer sImageBuffer;
	CTexture sImageTexture;
	CBuffer sXmlBuffer;
	CBuffer sRawBuffer;
} UIRESITEM;

class CUIResource : public IResourceLoadListener
{
public:
	CUIResource();
	virtual ~CUIResource();

	// interface
public:
	void OnItemLoad(
		UINT64 uUserData,
		RESOURCETYPE eItemType,
		const char* cItemName,
		const BYTE *pBuffer,
		int nBufLen);

public:
	BOOL LoadResource(
		CE3DCommand *pE3DEngine,
		const char* cResourceFile,
		const BYTE* pResKey,
		int nKeyLength);

	UIRESITEM* GetItem(
		const char *cItemName);

	void GetLimitStartEndTime(
		SYSTEMTIME* pStart,
		SYSTEMTIME* pEnd);

	// 单次使用时间
	UINT64 GetLimitTime(void);

	void FreeAllItem();

private:
	void FreeItem(
		UIRESITEM* pItemData);

private:
	CResComposer mResLoader;
	CPtrArrayCtrl mItemDataList;
	CCRCHashTable mItemDataHashTable;
};
