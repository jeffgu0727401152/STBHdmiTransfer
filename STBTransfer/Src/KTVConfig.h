#pragma once

#include "types.h"
#include "FileOperator.h"
#include "XMLParser.h"
#include "IHALInterface.h"

#define RESOURCE_FOLDER				"Images"
#define FONTS_FOLDER					"Fonts"
#define LOG_FOLDER						"Log"

#define LAYOUT_WIDTH  1280
#define LAYOUT_HEIGHT 720

#define SPECIAL_ROOMNAME_SET_VERIFY       "SET.VERIFY"
#define SPECIAL_ROOMNAME_CLEAN_VERIFY      "CLEAN.VERIFY"

class CKTVConfig
{
public:
	CKTVConfig();
	virtual ~CKTVConfig();

public:
	void LoadConfig(
		const char* cConfigFileName);

	void SetDisplaySize(
		int nWidth,
		int nHeight);
	int GetDisplayWidth();
	int GetDisplayHeight();

	const char* GetProgramFolder();
	const char* GetTempFolderPath();
	BOOL IsMonkeyMode();
	UINT64 GetMonkeyInterval();
	const char* GetFontName();
	PLTFORMAT GetPLTFormat();
	void SetPLTFormat(
		PLTFORMAT ePLTFormat);
	int GetMainVolume();
	void SetMainVolume(
		int nVolume);
	int GetPcmVolume();
	void SetPcmVolume(
		int nVolume);
	int GetMicVolume();
	void SetMicVolume(
		int nVolume);

	const char* GetStbIP();
	void SetStbIP(const char *cDeviceIP);
	const char* GetMacAddr();
	const char* GetNetGate();
	void SetNetGate(const char *cNetGate);
	const char* GetNetMask();
	void SetNetMask(const char *cNetMask);
	const char* GetDNS0();
	void SetDNS0(const char *cDNS);
	const char* GetDNS1();
	void SetDNS1(const char *cDNS);
	const char* GetServerIP();
	void SetServerIP(const char *cServerIP);
	const char* GetVodIP();
	void SetVodIP(const char *cVodIP);
	const char* GetRoomName();
	void SetRoomName(const char *cRoomName);

	int GetServerPort();
	void SetServerPort(int port);

	BOOL IsForceUseSTBStream();

	void SetConfigFileValid(BOOL valid);
	BOOL IsConfigFileValid();

private:
	XMLParser mKTVConfigParser;
	char mConfigFileName[MAX_PATH];

	int mDisplayWidth;
	int mDisplayHeight;

	char mProgramFolder[MAX_PATH];//资源，库等文件
	char mTempFolderPath[MAX_PATH];//临时文件目录

	BOOL mMonkeyMode;//自动化测试模式
	UINT64 mMonkeySeed;//自动化随机初始值
	UINT64 mMonkeyInterval;//自动化运行频率，ms

	char mFontName[32];//字体文件名

	PLTFORMAT mPLTFormat;//电视机制式
	int mMainVolume;//默认主音量
	int mPcmVolume;//默认音频音量
	int mMicVolume;//默认麦克风音量

	char mStbIP[16];//本机IP
	char mMacAddr[13];//本机mac地址
	char mNetGate[16];//本机网关
	char mNetMask[16];//本机子网掩码
	char mDNS0[16];//本机主DNS
	char mDNS1[16];//本机备用DNS
	char mServerIP[16];//服务器IP
	char mVodIP[16];//包厢IP
	char mRoomName[32];//包房名

	int mServerPort;
	// 强制使用 STBStream，网络播放更加优化
	BOOL mForceUseSTBStream;

	BOOL mIsVerified;
};

extern CKTVConfig gKTVConfig;
