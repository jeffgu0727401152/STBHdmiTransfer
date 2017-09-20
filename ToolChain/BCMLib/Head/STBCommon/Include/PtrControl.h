/*
���ߣ�kyo wang
�����ʹ�ò������˴��룬�����뱣����ע�Ͳ���
*/

#ifndef __PTRCTRL_HEADER__
#define __PTRCTRL_HEADER__

// CPtrArrayCtrl: 适合作为局部变量，或者内容需要频繁变化的情境，或者大量数据存储
// 因为 data 分配是buffer，所以释放的时候不容易引发内存碎片
// 其余情况，请使用 CPtrListCtrl, 可以减少内存占用，但易引发内存碎片

#include "types.h"
#include "PtrControlInterface.h"

typedef struct tagFINDDATA
{
	int	 nStartPos ;
	int	 nLeftFindPos ;
	int	 nRightFindPos ;
} FINDDATA ;

class CPtrListCtrl ;

PTRCTRLDLL_API
CPtrListCtrl operator+(
	CPtrListCtrl &sPtrCtrlAdd1,
	CPtrListCtrl &sPtrCtrlAdd2) ;

class PTRCTRLDLL_API CPtrListCtrl : public CPtrCtrl
{
	typedef struct tagDATALIST
	{
		const void* pData ;
		struct tagDATALIST *next ;
		struct tagDATALIST *pre ;
	} DATALIST, *PDATALIST;

public:
	CPtrListCtrl() ;
	CPtrListCtrl(
		CPtrListCtrl &sListCtrlInit) ;
	CPtrListCtrl(
		CPtrCtrl *pPtrCtrlInit) ;
	virtual ~CPtrListCtrl() ;

public:
	// modify a node
	int Set(
		int nPos,
		const void* pNewData) ;

	// add a node, return insert position
	int AddData(
		const void* pData,
		int nPos=-1) ;

	// add a list, the source list will be copied to current list, 
	// return list member count
	int AddPtrCtrl(
		CPtrCtrl *pPtrCtrl,
		int nPos=-1) ;

	// copy a list, the source list will be copied to current list
	// return list member count
	int CopyPtrCtrl(
		CPtrCtrl *pPtrCtrl) ;

	// check if special pos available
	bool IsDataAvailable(
		int nPos) ;

	// find data at special pos
	// if no data in pos, return NULL,
	// NOTE : sometimes, data is NULL, so you should check if the
	//        data is available
	const void* GetAt(
		int nPos) ;
	const void* GetHead(void) ;
	const void* GetTail(void) ;

	// return -1: not found
	int FindFirst(
		const void* pData,
		FINDFUNC pfn=NULL) ;
	int FindNext(
		const void* pData,
		FINDFUNC pfn=NULL) ;
	void FindAll(
		CPtrCtrl *pPtrCtrl,
		const void* pData,
		FINDFUNC pfn=NULL) ;

	// delete node at special pos
	const void* DeleteAt(
		int nPos,
		int nCount=1) ;
	const void* DeleteHead(void) ;
	const void* DeleteTail(void) ;

	// delete all
	void DeleteAll(void) ;

	// move data
	bool MoveData(
		int nOldPos,
		int nCount,
		int nNewPos) ;

	// Quick Sort List
	// nSortStart : Start pos in pPtrCtrl to be sorted
	// nSortEnd : End pos in pPtrCtrl to be sorted
	// pfnCmp : Compare Function
	// lParamSort : extra info for compare function
	// pnQsortSwapCount: swap count for Statistics, NULL if not want to get this value
	// PS: if nSortStart < 0, nSortStart will be set to 0(Start Pos)
	//	   if nSortEnd < 0, nSortEnd will be set to TotalCount-1(End Pos)
	void QuickSort(
		int nSortStart,
		int nSortEnd,
		COMPAREFUNC pfnCmp,
		UINT64 lParamSort,
		UINT64 uUserData,
		int *pnQsortSwapCount);

	int GetCount(void) const;
	bool IsEmpty(void) const;

	const char* GetClassName() const;

	void Dump(bool bAsce);

	CPtrListCtrl& operator=(
		CPtrCtrl &sPtrCtrlInit) ;
	CPtrListCtrl& operator+=(
		CPtrCtrl &sPtrCtrlAdd) ;
	
private:
	void* DeleteOne(
		int nPos) ;
	PDATALIST SearchToPos(
		int nPos) ;
	void SetCurPos(
		int nPos,
		PDATALIST pCurList) ;
	void SetFindData(
		int nStartPos,
		int nLeftFindPos,
		int nRightFindPos) ;
	bool FindDataAtPos(
		int nFindPos,
		const void* pData,
		FINDFUNC pfn) ;

private:
	DATALIST	m_DataListHeader ;
	PDATALIST	m_pDataListTailer ;
	PDATALIST	m_pDataListCurPtr ;
	
	int			m_nSize ;
	int			m_nCurPos ;
	FINDDATA	m_FindData ;

	int			m_nRefCount ;
};

class CPtrArrayCtrl ;

PTRCTRLDLL_API
CPtrArrayCtrl operator+(
	CPtrArrayCtrl &sPtrCtrlAdd1,
	CPtrArrayCtrl &sPtrCtrlAdd2) ;

class PTRCTRLDLL_API CPtrArrayCtrl : public CPtrCtrl
{
	typedef void* DATAPTR ;

public:
	CPtrArrayCtrl() ;
	CPtrArrayCtrl(
		CPtrArrayCtrl &sArrayCtrlInit) ;
	CPtrArrayCtrl(
		CPtrCtrl *pPtrCtrlInit) ;
	virtual ~CPtrArrayCtrl() ;

public:
	// modify a node
	int Set(
		int nPos,
		const void* pNewData) ;

	// add a data, return insert position
	int AddData(
		const void* pData,
		int nPos=-1) ;

	// add a array, the source array will be copied to current array, 
	// return list member count
	int AddPtrCtrl(
		CPtrCtrl *pPtrCtrl,
		int nPos=-1) ;

	// copy a array, the source list will be copied to current array
	// return list member count
	int CopyPtrCtrl(
		CPtrCtrl *pPtrCtrl) ;

	// check if special pos available
	bool IsDataAvailable(
		int nPos) ;

	// find data at special pos
	// if no data in pos, return NULL,
	// NOTE : sometimes, data is NULL, so you should check if the
	//        data is available
	const void* GetAt(
		int nPos) ;
	const void* GetHead(void) ;
	const void* GetTail(void) ;

	// return -1: not found
	int FindFirst(
		const void* pData,
		FINDFUNC pfn=NULL) ;
	int FindNext(
		const void* pData,
		FINDFUNC pfn=NULL) ;
	void FindAll(
		CPtrCtrl *pPtrCtrl,
		const void* pData,
		FINDFUNC pfn=NULL) ;

	// delete data at special pos
	const void* DeleteAt(
		int nPos,
		int nCount=1) ;
	const void* DeleteHead(void) ;
	const void* DeleteTail(void) ;

	// delete all
	void DeleteAll(void) ;

	// move data
	bool MoveData(
		int nOldPos,
		int nCount,
		int nNewPos) ;

	// Quick Sort List
	// nSortStart : Start pos in pPtrCtrl to be sorted
	// nSortEnd : End pos in pPtrCtrl to be sorted
	// pfnCmp : Compare Function
	// lParamSort : extra info for compare function
	// pnQsortSwapCount: swap count for Statistics, NULL if not want to get this value
	// PS: if nSortStart < 0, nSortStart will be set to 0(Start Pos)
	//	   if nSortEnd < 0, nSortEnd will be set to TotalCount-1(End Pos)
	void QuickSort(
		int nSortStart,
		int nSortEnd,
		COMPAREFUNC pfnCmp,
		UINT64 lParamSort,
		UINT64 uUserData,
		int *pnQsortSwapCount);

	int GetCount(void) const;
	bool IsEmpty(void) const;

	const char* GetClassName() const;

	void Dump(bool bAsce);

	CPtrArrayCtrl& operator=(
		CPtrCtrl &sPtrCtrlInit) ;
	CPtrArrayCtrl& operator+=(
		CPtrCtrl &sPtrCtrlAdd) ;

	int GetCapability(void) ;

private:
	bool OnSizeChange(
		int nNewSize) ;
	int DecreaseCapability(
		int nCapability,
		int nSize) ;
	int IncreaseCapability(
		int nCapability,
		int nSize) ;
	void SetCurPos(
		int nPos) ;
	void SetFindData(
		int nStartPos,
		int nLeftFindPos,
		int nRightFindPos) ;
	bool FindDataAtPos(
		int nFindPos,
		const void* pData,
		FINDFUNC pfn) ;

private:
	DATAPTR *	m_pDataPtrAarry ;
	int			m_nSize ;
	int			m_nCapability ;
	int			m_nCurPos ;
	FINDDATA	m_FindData ;
};

#endif //__PTRCTRL_HEADER__
