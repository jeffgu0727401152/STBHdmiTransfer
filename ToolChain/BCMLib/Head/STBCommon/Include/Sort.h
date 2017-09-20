/*
���ߣ�kyo wang
�����ʹ�ò������˴��룬�����뱣����ע�Ͳ���
*/
#ifndef __SORT_HEADER__
#define __SORT_HEADER__

#include "types.h"

#define SORTPARAM_DESC	  0x0000
#define SORTPARAM_ASCE    0x0001
#define SORTPARAM_NOCASE  0x0000
#define SORTPARAM_CASE    0x0001

#define SORTPARAM_ASCE_CASE (SORTPARAM_ASCE|(SORTPARAM_CASE<<16))
#define SORTPARAM_ASCE_NOCASE (SORTPARAM_ASCE|(SORTPARAM_NOCASE<<16))
#define SORTPARAM_DESC_CASE (SORTPARAM_DESC|(SORTPARAM_CASE<<16))
#define SORTPARAM_DESC_NOCASE (SORTPARAM_DESC|(SORTPARAM_NOCASE<<16))

#define IS_SORTPARAM_ASCE(lParamSort) (LOWORD(lParamSort)==SORTPARAM_ASCE)
#define IS_SORTPARAM_DESC(lParamSort) (LOWORD(lParamSort)==SORTPARAM_DESC)
#define IS_SORTPARAM_CASE(lParamSort) (HIWORD(lParamSort)==SORTPARAM_CASE)
#define IS_SORTPARAM_NOCASE(lParamSort) (HIWORD(lParamSort)==SORTPARAM_NOCASE)


// lParam1 : item 1 to be compared
// lParam2 : item 2 to be compared
// lParamSort : extra data for compared
// return : 
// <= 0: remain order 
// > 0: exchange order
typedef int (* COMPAREFUNC)(
	const void* lParam1,
	const void* lParam2,
	const UINT64 lParamSort,
	const UINT64 uUserData) ;

/************************************************************************/
/* sort function                                                        */
/************************************************************************/

	// Quick Sort Buffer
	// pDataPtrArray : Array Contain Pointer of Tobe Sort Data
	// nSortStart : Start pos in buffer to be sorted
	// nSortEnd : End pos in buffer to be sorted
	// pfnCmp : Compare Function
	// lParamSort : extra info for compare function
	// pnQsortSwapCount: swap count for Statistics, NULL if not want to get this value
	// PS: if nSortStart < 0, nSortStart will be set to 0(Start Pos)
	//	   if nSortEnd < 0, nSortEnd will be set to 0
	void QuicksortBuffer(
		void **pDataPtrArray,
		int nSortStart,
		int nSortEnd,
		COMPAREFUNC pfnCmp,
		UINT64 lParamSort,
		UINT64 uUserData,
		int *pnQsortSwapCount);

	// PS :
	// Use CPtrArrayCtrl will be faster than CPtrListCtrl

/************************************************************************/
/* sort function                                                        */
/************************************************************************/
#endif //__SORT_HEADER__
