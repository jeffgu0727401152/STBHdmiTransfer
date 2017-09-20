// use hash table with a list control 
// will be fast when get data at special pos
// such as:
// CPtrListCtrl aList;
// CHashTable aHash;
// aList.AddData(pData);
// aHash.AddData(1234, pData);
// ...
// when find a data, you can use
// aHash.FindFirstData(1234);
// when get data at a pos, you can use
// aList.GetAt(nPos);
//

#ifndef __HASH_TABLE_HEADER__
#define __HASH_TABLE_HEADER__

#include "types.h"
#include "PtrControl.h"

#define DEFAULT_HASH_TABLE_SIZE		4096

typedef struct tagHASHPOSITION
{
	int nNodeIndex;
	int nListIndex;
} HASHPOSITION;

class CHashTable
{
	typedef void* DATAPTR;

public:
	CHashTable(
		int nSize=DEFAULT_HASH_TABLE_SIZE);
	virtual ~CHashTable();

public:
	// add special data by hash index
	// shoud detect if this index has already exist!
	void AddData(
		int nHashIndex,
		const void *pData);

	// set special data by hash index
	void SetData(
		int nHashIndex,
		const void *pData);

	// get data by position
	// NOTE : DONOT delete item when enum hash position,
	//        the HASHPOSITION will be dirty
	BOOL GetHeadPosition(
		HASHPOSITION& sEnumKey);
	BOOL MoveHashPositionNext(
		HASHPOSITION& sEnumKey);
	BOOL IsDataAvailable(
		HASHPOSITION sEnumKey);
	const void *GetDataAt(
		HASHPOSITION sEnumKey);

	// if no data in pos, return NULL,
	// NOTE : sometimes, data is NULL, so you should check if the
	//        data is available
	const void *FindFirstData(
		int nHashIndex);
	const void *FindNextData(
		int nHashIndex);
	const void FindAllHashData(
		CPtrCtrl *pResultList,
		int nHashIndex);

	// delete special data by hash index
	// NOTE : sometimes, data is NULL, so you should check if the
	//        data is available
	const void *DeleteFirstData(
		int nHashIndex);
	const void *DeleteNextData(
		int nHashIndex);
	const void DeleteAllData(
		int nHashIndex);

	// delete all data
	void DeleteAll();

	// check if Index is available
	BOOL IsDataAvailable(
		int nHashIndex);

	// get count
	int GetCount();

private:
	void InitHashTable();

private:
	DATAPTR *m_pHashData;
	int	m_nHashSize;
	int	m_nSize;
};

class CCRCHashTable
{
	typedef void* DATAPTR;

public:
	CCRCHashTable(
		int nSize=DEFAULT_HASH_TABLE_SIZE);
	virtual ~CCRCHashTable();

public:
	// add special data by hash index
	// shoud detect if this index has already exist!
	void AddData(
		const void* pIndexData,
		int nIndexLen,
		const void *pData);

	// set special data by hash index
	void SetData(
		const void* pIndexData,
		int nIndexLen,
		const void *pData);

	// get data by position
	// NOTE : DONOT delete item when enum hash position,
	//        the HASHPOSITION will be dirty
	BOOL GetHeadPosition(
		HASHPOSITION& sEnumKey);
	BOOL MoveHashPositionNext(
		HASHPOSITION& sEnumKey);
	BOOL IsDataAvailable(
		HASHPOSITION sEnumKey);
	const void *GetDataAt(
		HASHPOSITION sEnumKey);

	// if no data in pos, return NULL,
	// NOTE : sometimes, data is NULL, so you should check if the
	//        data is available
	const void *FindFirstData(
		const void* pIndexData,
		int nIndexLen);
	const void *FindNextData(
		const void* pIndexData,
		int nIndexLen);
	const void FindAllCRCHashData(
		CPtrCtrl *pResultList,
		const void* pIndexData,
		int nIndexLen);

	// delete special data by hash index
	// NOTE : sometimes, data is NULL, so you should check if the
	//        data is available
	const void *DeleteFirstData(
		const void* pIndexData,
		int nIndexLen);
	const void *DeleteNextData(
		const void* pIndexData,
		int nIndexLen);
	const void DeleteAllData(
		const void* pIndexData,
		int nIndexLen);

	// delete all data
	void DeleteAll();

	// check if Index is available
	BOOL IsDataAvailable(
		const void* pIndexData,
		int nIndexLen);

	// get count
	int GetCount();
	
private:
	void InitCRCHashTable();

private:
	DATAPTR *m_pCRCHashData;
	int	m_nCRCHashSize;
	int	m_nSize;
};


// NOTE:
// these macro just used to free the data which add to CPtrCtrl
// and the data must allocated use new/free,
// otherwise, you should free data with special free function
#define DelArrayHash(pHashTable, type)									\
{																		\
	if (pHashTable)														\
	{																	\
		HASHPOSITION sEnumKey;											\
		(pHashTable)->GetHeadPosition(sEnumKey);						\
		while ((pHashTable)->IsDataAvailable(sEnumKey))					\
		{																\
			type *pAarry = (type *)((pHashTable)->GetDataAt(sEnumKey));	\
			if (pAarry)													\
			{															\
				delete []pAarry;										\
			}															\
			(pHashTable)->MoveHashPositionNext(sEnumKey);				\
		}																\
		(pHashTable)->DeleteAll() ;										\
	}																	\
}

#define DelNormalHash(pHashTable, type)			     				\
{																		\
	if (pHashTable)														\
	{																	\
		HASHPOSITION sEnumKey;											\
		(pHashTable)->GetHeadPosition(sEnumKey);						\
		while ((pHashTable)->IsDataAvailable(sEnumKey))					\
		{																\
			type *pData = (type *)((pHashTable)->GetDataAt(sEnumKey));	\
			if (pData)													\
			{															\
				delete pData;											\
			}															\
			(pHashTable)->MoveHashPositionNext(sEnumKey);				\
		}																\
		(pHashTable)->DeleteAll() ;										\
	}																	\
}

#define FreeDataHash(pHashTable)										\
{																		\
	if (pHashTable)														\
	{																	\
		HASHPOSITION sEnumKey;											\
		(pHashTable)->GetHeadPosition(sEnumKey);						\
		while ((pHashTable)->IsDataAvailable(sEnumKey))					\
		{																\
			type *pData = (type *)((pHashTable)->GetDataAt(sEnumKey));	\
			if (pData)													\
			{															\
				free(pData);											\
			}															\
			(pHashTable)->MoveHashPositionNext(sEnumKey);				\
		}																\
		(pHashTable)->DeleteAll() ;										\
	}																	\
}


#endif //__HASH_TABLE_HEADER__
