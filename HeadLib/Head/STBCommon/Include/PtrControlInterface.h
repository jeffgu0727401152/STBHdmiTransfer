#ifndef __PTRCTRL_INTERFACE_HEADER__
#define __PTRCTRL_INTERFACE_HEADER__

#pragma GCC diagnostic ignored "-Waddress"

#include "Sort.h"

// PS:
// the ptrcontrl is thread safe, not multi-thread safe.
// so, if you want to share ptrcontrl on multi-thread,
// you should make a safety mechanism, such as critical section,
// or other mutex object
//

typedef enum ePTRCONTROLTYPE
{
	PtrList_Control=0,
	PtrArray_Control
} PTRCONTROLTYPE;

#define PTRCTRLDLL_API 

typedef int (*FINDFUNC)(const void* pItem, const void* pData);
/* SAMPLE
int __stdcall SampleFind(const void* pItem, const void* pData)
{
	WCHAR *wszName1 = (WCHAR *)pItem;
	WCHAR *wszName2 = (WCHAR *)pData;

	if ( wcsicmp(wszName1, wszName2) == 0 )
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
CPtrListCtrl a;
a.AddData(L"123456");
a.AddData(L"223456");
a.AddData(L"323456");
a.FindFirst(L"123456", SampleFind);
*/


class CPtrCtrl
{
public:
	virtual ~CPtrCtrl(void){}

	// modify a node
	virtual int	Set(
		int nPos,
		const void* pNewData)=0;

	// add a node, return insert position
	virtual int AddData(
		const void* pData,
		int nPos=-1)=0;

	// add a array, the source array will be copied to current array, 
	// return list member count
	virtual int AddPtrCtrl(
		CPtrCtrl *pPtrCtrl,
		int nPos=-1)=0;

	// copy a list, the source list will be copied to current list
	// return list member count
	virtual int CopyPtrCtrl(
		CPtrCtrl *pPtrCtrl)=0;

	// check if special pos available
	virtual bool IsDataAvailable(
		int nPos)=0;

	// find data at special pos
	// if no data in pos, return NULL,
	// NOTE : sometimes, data is NULL, so you should check if the
	//        data is available
	virtual const void* GetAt(
		int nPos)=0;
	virtual const void* GetHead(void)=0;
	virtual const void* GetTail(void)=0;

	// return -1: not found
	virtual int FindFirst(
		const void* pData,
		FINDFUNC pfn=0)=0;
	virtual int FindNext(
		const void* pData,
		FINDFUNC pfn=0)=0;

	// delete node at special pos
	virtual const void* DeleteAt(
		int nPos,
		int nCount=1)=0;
	virtual const void* DeleteHead(void)=0;
	virtual const void* DeleteTail(void)=0;

	// delete all
	virtual void DeleteAll(void)=0;

	// move data
	// 0 1 2 3 4 5 6 7 8 9
	// MoveData(0, 2, 3)  2 3 0 1 4 5 6 7 8 9
	// MoveData(0, 9, 9)  9 0 1 2 3 4 5 6 7 8
	// MoveData(3, 2, -1) 3 4 0 1 2 5 6 7 8 9
	// MoveData(3, 2, 0)  0 3 4 1 2 5 6 7 8 9
	// MoveData(-1, 0, 2) return false
	// MoveData(0, 3, 2) return false
	virtual bool MoveData(
		int nOldPos,
		int nCount,
		int nNewPos)=0;

	// Quick Sort List
	// nSortStart : Start pos in pPtrCtrl to be sorted
	// nSortEnd : End pos in pPtrCtrl to be sorted
	// pfnCmp : Compare Function
	// lParamSort : extra info for compare function
	// pnQsortSwapCount: swap count for Statistics, NULL if not want to get this value
	// PS: if nSortStart < 0, nSortStart will be set to 0(Start Pos)
	//	   if nSortEnd < 0, nSortEnd will be set to TotalCount-1(End Pos)
	virtual void QuickSort(
		int nSortStart,
		int nSortEnd,
		COMPAREFUNC pfnCmp,
		UINT64 lParamSort,
		UINT64 uUserData,
		int *pnQsortSwapCount)=0;

	virtual int GetCount(void) const=0;
	virtual bool IsEmpty(void)  const=0;

	// class name
	virtual const char* GetClassName(void) const=0;

	virtual void Dump(bool bAsce)=0;
};

// NOTE:
// these macro just used to free the data which add to CPtrCtrl
// and the data must allocated use new/free, 
// otherwise, you should free data with special free function
#define DelArrayList(pPtrCtrl, type)						\
{															\
	if (pPtrCtrl)											\
	{														\
		int nCount = (pPtrCtrl)->GetCount();				\
		int i;												\
		for (i = 0; i < nCount; i++)						\
		{													\
			type *pAarry = (type *)((pPtrCtrl)->GetAt(i));	\
			if (pAarry)										\
			{												\
				delete []pAarry;							\
			}												\
		}													\
		(pPtrCtrl)->DeleteAll();							\
	}														\
}

#define DelNormalList(pPtrCtrl, type)		     			\
{															\
	if (pPtrCtrl)											\
	{														\
		int nCount = (pPtrCtrl)->GetCount();				\
		int i;												\
		for (i = 0; i < nCount; i++)						\
		{													\
			type *pData = (type *)((pPtrCtrl)->GetAt(i));	\
			if (pData)										\
			{												\
				delete pData;								\
			}												\
		}													\
		(pPtrCtrl)->DeleteAll();							\
	}														\
}

#define FreeDataList(pPtrCtrl)							\
{														\
	if (pPtrCtrl)										\
	{													\
		int nCount = (pPtrCtrl)->GetCount();			\
		int i;											\
		for (i = 0; i < nCount; i++)					\
		{												\
			void* pData = (pPtrCtrl)->GetAt(i);			\
			if (pData)									\
			{											\
				free(pData);							\
			}											\
		}												\
		(pPtrCtrl)->DeleteAll();						\
	}													\
}

#endif //__PTRCTRL_INTERFACE_HEADER__
