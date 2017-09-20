#pragma once

#include "types.h"
#include "PtrControl.h"
#include "HashTable.h"
#include "Sort.h"
#include "Song.h"

typedef enum eDB_SORTTYPE
{
	SortType_WordCount_China_Spell = 0,
	SortType_WordCount_Spell = 1,
	SortType_WordCount = 2,
	SortType_Spell = 3,
	SortType_None = 4,//仅配合 order
} DB_SORTTYPE;

void ConvertIDTo8ByteMode(
	char cInputID[9]);

void CopySingerInfo(
	SINGERINFO *pDst,
	const SINGERINFO *pSrc);
void FixSingerInfo(
	SINGERINFO *pSingerInfo,
	BOOL bForceUpdate);
int AddSingerToSingerList(
	CPtrCtrl *pSingerList,
	CHashTable *pSingerIDHashTable,
	CCRCHashTable *pSingerNameHashTable,
	const SINGERINFO *pTobeAdd);
int AddSingerToSingerList_Sort(
	CPtrCtrl *pSingerList,
	CHashTable *pSingerIDHashTable,
	CCRCHashTable *pSingerNameHashTable,
	const SINGERINFO *pTobeAdd,
	DB_SORTTYPE eSortType,
	BOOL bSortWithOrder);
void DelSingerFromSingerListByIndex(
	CPtrCtrl *pSingerList,
	CHashTable *pSingerIDHashTable,
	CCRCHashTable *pSingerNameHashTable,
	int nIndex,
	BOOL bDeleteSingerInfo);
void DelSingerFromSingerListBySingerInfo(
	CPtrCtrl *pSingerList,
	CHashTable *pSingerIDHashTable,
	CCRCHashTable *pSingerNameHashTable,
	const SINGERINFO *pTobeDel,
	BOOL bDeleteSingerInfo);
void DelSingerFromSingerListBySingerFlag(
	CPtrCtrl *pSingerList,
	CHashTable *pSingerIDHashTable,
	CCRCHashTable *pSingerNameHashTable,
	UINT32 uSingerFlag,
	BOOL bDeleteSingerInfo);
SINGERINFO* GetSingerInfoFromSingerListByID(
	CPtrCtrl *pSingerList,
	CHashTable *pSingerIDHashTable,
	const char* cSingerID,
	int nIDLength);
void GetSingersFromSingerListByName(
	CPtrCtrl *pSingerList,
	CCRCHashTable *pSingerNameHashTable,
	const char* cSingerName,
	int nNameLength,
	CPtrCtrl *pResultSingerList);
void SortAllInSingerList(
	CPtrCtrl *pSingerList,
	DB_SORTTYPE eSortType,
	BOOL bSortWithOrder);
void SortOneInSingerList(
	CPtrCtrl *pSingerList,
	const SINGERINFO *pTobeSort,
	DB_SORTTYPE eSortType,
	BOOL bSortWithOrder);

BOOL AddSingerSongsFromSong(
	const SONGINFO *pSongInfo,
	CPtrCtrl *pSingerList,
	CCRCHashTable *pSingerNameHashTable);
void AddSingerSongsFromSongList(
	CPtrCtrl *pSongList,
	CPtrCtrl *pSingerList,
	CCRCHashTable *pSingerNameHashTable);
void DelSingerSongsFromSong(
	const SONGINFO *pSongInfo,
	CPtrCtrl *pSingerList,
	CCRCHashTable *pSingerNameHashTable);

void CopySongInfo(
	SONGINFO *pDst,
	const SONGINFO *pSrc);
void FixSongInfo(
	SONGINFO *pSongInfo,
	BOOL bForceUpdate);
int AddSongToSongList(
	CPtrCtrl *pSongList,
	CHashTable *pSongIDHashTable,
	const SONGINFO *pTobeAdd);
int AddSongToSongList_Sort(
	CPtrCtrl *pSongList,
	CHashTable *pSongIDHashTable,
	const SONGINFO *pTobeAdd,
	DB_SORTTYPE eSortType,
	BOOL bSortWithOrder,
	BOOL bSortWithCloud);
void DelSongFromSongListByIndex(
	CPtrCtrl *pSongList,
	CHashTable *pSongIDHashTable,
	int nIndex,
	BOOL bDeleteSongInfo);
void DelSongFromSongListBySongInfo(
	CPtrCtrl *pSongList,
	CHashTable *pSongIDHashTable,
	const SONGINFO *pTobeDel,
	BOOL bDeleteSongInfo);
void DelSongFromSongListBySongFlag(
	CPtrCtrl *pSongList,
	CHashTable *pSongIDHashTable,
	UINT32 uSongFlag,
	BOOL bDeleteSongInfo);
SONGINFO* GetSongInfoFromSongListByID(
	CPtrCtrl *pSongList,
	CHashTable *pSongIDHashTable,
	const char* cSongID,
	int nIDLength);
SONGINFO* GetSongInfoFromSongListByFilePath(
	CPtrCtrl *pSongList,
	const char* cSongFilePath,
	int nPathLength);
void SortAllInSongList(
	CPtrCtrl *pSongList,
	DB_SORTTYPE eSortType,
	BOOL bSortWithOrder,
	BOOL bSortWithCloud);
void SortOneInSongList(
	CPtrCtrl *pSongList,
	const SONGINFO *pTobeSort,
	DB_SORTTYPE eSortType,
	BOOL bSortWithOrder,
	BOOL bSortWithCloud);

void SaveSingerListToFile(
	CPtrCtrl *pSingerList,
	const char *cFileName);
void LoadSingerListFromFile(
	CPtrCtrl *pSingerList,
	CHashTable *pSingerIDHashTable,
	CCRCHashTable *pSingerNameHashTable,
	const char *cFileName);
void LoadSingerListFromBuffer(
	CPtrCtrl *pSingerList,
	CHashTable *pSingerIDHashTable,
	CCRCHashTable *pSingerNameHashTable,
	const BYTE *pDataBuf,
	int nDataLen);

void SaveSongListToFile(
	CPtrCtrl *pSongList,
	const char *cFileName);
void LoadSongListFromFile(
	CPtrCtrl *pSongList,
	CHashTable *pSongIDHashTable,
	const char *cFileName);
void LoadSongListFromBuffer(
	CPtrCtrl *pSongList,
	CHashTable *pSongIDHashTable,
	const BYTE *pDataBuf,
	int nDataLen);

typedef int (*GETCANUSESONGID_CALLBACK)(UINT64 uUserData) ;
void GetFolderSongList(
	const char* cFolder,
	CPtrCtrl *pFolderSongList,
	GETCANUSESONGID_CALLBACK pfnCallback,
	UINT64 uUserData);

BOOL IsCloudSong(
	const SONGINFO *pSongInfo);

BOOL IsEncryptSong(
	const SONGINFO *pSongInfo,
	const char* cOEMID);
