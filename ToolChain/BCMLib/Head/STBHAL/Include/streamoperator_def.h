/*************************************************************************
                             All Rights Reserved
                                 R&D Dept.
*************************************************************************/

/*************************************************************************
  使用说明：
  功能：使用自定义数据读取接口
  使用方法：实现一个dll， 定义 STREAMOPERATOR_INFO g_DataStreamOperator_Entry 和
  g_IndexStreamOperator_Entry 变量，并定义变量中的函数
*************************************************************************/

#pragma once

// return NULL: not supported protocol
// 函数名必须为 "StreamOperator_CheckFileProtocol"
typedef const char* (*STREAMOPERATOR_CHECKFILEPROTOCOL)(
	const char* cFileName);

// 打开数据文件
// cFileName: 文件名称
// nPlayerIndex: 播放类型
// cSTBDecryptOEMID: 自定义加密ID
// return stream operator Handle
typedef void *  (*STREAMOPERATOR_ACCESS_OPEN)(
	const char* cFileName,
	int nPlayerIndex,
	const char* cSTBDecryptOEMID);

// 准备停止，一般对网络读取有效，调用后，当前和之后的读取函数都无法读取数据
typedef void (*STREAMOPERATOR_ACCESS_PREPARECLOSE)(
	void* pHandle);

// 关闭数据文件
typedef void (*STREAMOPERATOR_ACCESS_CLOSE)(
	void* pHandle);

// 获取每个缓存数据块大小
typedef unsigned int (*STREAMOPERATOR_ACCESS_GETBLOCKSIZE)(
	void* pHandle);

// 返回缓存数据块个数
typedef unsigned int (*STREAMOPERATOR_ACCESS_GETCACHEBLOCKCOUNT)(
	void* pHandle);

// 返回预留数据块个数
typedef unsigned int (*STREAMOPERATOR_ACCESS_GETRETAINBLOCKCOUNT)(
	void* pHandle);

// 获取数据文件长度
typedef unsigned long long (*STREAMOPERATOR_ACCESS_GETFILESIZE)(
	void* pHandle);

// 随即位置读取数据文件
typedef size_t (*STREAMOPERATOR_ACCESS_READBUFFER)(
	void* pHandle,
	unsigned long long uFromPos,
	unsigned char *pBuffer,
	size_t nBufLen,
	unsigned long long uTimeout,
	int bUseContinueRead);

// 读取指定block数据文件
typedef unsigned int (*STREAMOPERATOR_ACCESS_READONEBLOCK)(
	void* pHandle,
	unsigned char **ppWorkingBuffer,
	unsigned int uBlockIndex,
	unsigned int uBlockSize,
	int bLastBlock,
	unsigned long long uTimeout,
	int bUseContinueRead);

// 是否支持任意读取
typedef int (*STREAMOPERATOR_ACCESS_SUPPORTREADRANDOM)(
	void* pHandle);

// 取消当下的读取，一般对网络读取有效
typedef void (*STREAMOPERATOR_ACCESS_CANCELREAD)(
	void* pHandle);

// 是否慢读取：一般对本地磁盘访问有效，避免高速访问造成系统IO卡顿
typedef void (*STREAMOPERATOR_ACCESS_ENABLESNOWREAD)(
	void* pHandle,
	int bEnableSlowRead);

// 获取数据读取速度,
typedef float (*STREAMOPERATOR_ACCESS_GETREADSPEEDKBPS)(
	void* pHandle);

// 初始化 process 私有数据
// 返回用户私有数据
typedef void* (*STREAMOPERATOR_PROCESS_INIT)(
	void* pHandle);
// 销毁 process 私有数据
typedef void (*STREAMOPERATOR_PROCESS_DEINIT)(
	void* pHandle,
	void *pUserData);
// 数据后处理，一般用来做数据解密
typedef void (*STREAMOPERATOR_PROCESS_BUFFERPOSTCALLBACK)(
	void* pHandle,
	void *pUserData,
	unsigned long long uDataPos,
	unsigned char *pBuffer,
	unsigned int nBufLen);

typedef struct tagSTREAMOPERATOR_ACCESS_INFO
{
	// 这些函数必须都为空或者都不为空，不能只定义部分实现
	STREAMOPERATOR_ACCESS_OPEN pfn_SO_A_Open;
	STREAMOPERATOR_ACCESS_PREPARECLOSE pfn_SO_A_PrepareClose;
	STREAMOPERATOR_ACCESS_CLOSE pfn_SO_A_Close;
	STREAMOPERATOR_ACCESS_GETBLOCKSIZE pfn_SO_A_GetBlockSize;
	STREAMOPERATOR_ACCESS_GETCACHEBLOCKCOUNT pfn_SO_A_GetCacheBlockCount;
	STREAMOPERATOR_ACCESS_GETRETAINBLOCKCOUNT pfn_SO_A_GetRetainBlockCount;
	STREAMOPERATOR_ACCESS_GETFILESIZE pfn_SO_A_GetFileSize;
	STREAMOPERATOR_ACCESS_READBUFFER pfn_SO_A_ReadBuffer;
	STREAMOPERATOR_ACCESS_READONEBLOCK pfn_SO_A_ReadOneBlock;
	STREAMOPERATOR_ACCESS_SUPPORTREADRANDOM pfn_SO_A_SupportReadRandom;
	STREAMOPERATOR_ACCESS_CANCELREAD pfn_SO_A_CancelRead;
	STREAMOPERATOR_ACCESS_ENABLESNOWREAD pfn_SO_A_EnableSlowRead;
	STREAMOPERATOR_ACCESS_GETREADSPEEDKBPS pfn_SO_A_GetReadSpeedKBPS;
} STREAMOPERATOR_ACCESS_INFO;

typedef struct tagSTREAMOPERATOR_PROCESS_INFO
{
	STREAMOPERATOR_PROCESS_INIT pfn_SO_P_Init;
	STREAMOPERATOR_PROCESS_DEINIT pfn_SO_P_Deinit;
	STREAMOPERATOR_PROCESS_BUFFERPOSTCALLBACK pfn_SO_P_BufferPostCallback;
} STREAMOPERATOR_PROCESS_INFO;

typedef struct tagSTREAMOPERATOR_ENTRY
{
	STREAMOPERATOR_ACCESS_INFO sAccessInfo;
	STREAMOPERATOR_PROCESS_INFO sProcessInfo;
} STREAMOPERATOR_ENTRY;
