#include "KTVConfig.h"
#include "FileOperator.h"
#include "DbgOutput.h"
#include "commfunc.h"
#include "SocketInterface.h"

CKTVConfig gKTVConfig;

CKTVConfig::CKTVConfig()
{
	mConfigFileName[0] = '\0';

	mDisplayWidth = 1280;
	mDisplayHeight = 720;

	mProgramFolder[0] = '\0';
	mTempFolderPath[0] = '\0';

	mMonkeyMode = FALSE;
	mMonkeySeed = GetTickCount();
	mMonkeyInterval = 500;

	SAFE_STRNCPY(mFontName, "default.ttf", 32);

	mPLTFormat = PLTFORMAT_1080P_E;
	mMainVolume = (MAIN_VOLUME_MAX+1)/2;
	mPcmVolume = (PCM_VOLUME_MAX+1)/2;
	mMicVolume = (MIC_VOLUME_MAX+1)/2;

	mStbIP[0] = '\0';
	mMacAddr[0] = '\0';
	mNetGate[0] = '\0';
	mNetMask[0] = '\0';
	mDNS0[0] = '\0';
	mDNS1[0] = '\0';
	mServerIP[0] = '\0';
	mVodIP[0] = '\0';
	mRoomName[0] = '\0';

	mServerPort = 8080;

	mForceUseSTBStream = TRUE;
	mIsVerified = FALSE;
}

CKTVConfig::~CKTVConfig()
{}

void CKTVConfig::LoadConfig(
	const char* cConfigFileName)
{
	LOGMSG(DBG_LEVEL_I, "LoadConfig from %s!!\n", cConfigFileName);

	CSimpleStringA sMacID;
	GetEthMacAddress(&sMacID);
	SAFE_STRNCPY(mMacAddr, sMacID.GetString(),13);
	LOGMSG(DBG_LEVEL_I, "Mac addr is=%s!!\n", mMacAddr);

	SAFE_STRNCPY(mConfigFileName, cConfigFileName, MAX_PATH);

	mKTVConfigParser.LoadFromFile(mConfigFileName);
	XMLNode rootnode;
	mKTVConfigParser.GetNode("STBCfg", &rootnode);

	rootnode.GetAttrUInt32Value("DISPLAYWIDTH", &mDisplayWidth);
	LOGMSG(DBG_LEVEL_I, "DISPLAYWIDTH %d!!\n", mDisplayWidth);

	rootnode.GetAttrUInt32Value("DISPLAYHEIGHT", &mDisplayHeight);
	LOGMSG(DBG_LEVEL_I, "DISPLAYHEIGHT %d!!\n", mDisplayHeight);

	SAFE_STRNCPY(mProgramFolder, rootnode.GetAttrStrValue("PROGRAMFOLDER", mProgramFolder), MAX_PATH);
	LOGMSG(DBG_LEVEL_I, "Program Folder is=%s!!\n", mProgramFolder);

	SAFE_STRNCPY(mTempFolderPath, rootnode.GetAttrStrValue("TEMPFOLDERPATH", "/tmp"), MAX_PATH);
	LOGMSG(DBG_LEVEL_I, "Temp Folder Path is=%s!!\n", mTempFolderPath);

	rootnode.GetAttrUInt32Value("MONKEYMODE", &mMonkeyMode);
	LOGMSG(DBG_LEVEL_I, "monkey mode is %s!!\n", mMonkeyMode?"TRUE":"FALSE");

	rootnode.GetAttrUInt64Value("MONKEYSEED", &(mMonkeySeed));
	LOGMSG(DBG_LEVEL_I, "monkey seed is %llu!!\n", mMonkeySeed);

	rootnode.GetAttrUInt64Value("MONKEYINTERVAL", &mMonkeyInterval);
	LOGMSG(DBG_LEVEL_I, "monkey interval is %llu!!\n", mMonkeyInterval);

	SAFE_STRNCPY(mFontName, rootnode.GetAttrStrValue("FONTNAME", mFontName), 32);
	LOGMSG(DBG_LEVEL_I, "Font Name is %s!!\n", mFontName);

	rootnode.GetAttrUInt32Value("PLTFORMAT", &mPLTFormat);
	LOGMSG(DBG_LEVEL_I, "PLT Format is %d!!\n", mPLTFormat);

	rootnode.GetAttrUInt32Value("MAINVOLUME", &mMainVolume);
	LOGMSG(DBG_LEVEL_I, "main volume is %d!!\n", mMainVolume);

	rootnode.GetAttrUInt32Value("PCMVOLUME", &mPcmVolume);
	LOGMSG(DBG_LEVEL_I, "pcm volume is %d!!\n", mPcmVolume);

	rootnode.GetAttrUInt32Value("MICVOLUME", &mMicVolume);
	LOGMSG(DBG_LEVEL_I, "mic volume is %d!!\n", mMicVolume);

	SAFE_STRNCPY(mStbIP, rootnode.GetAttrStrValue("STBIP", mStbIP), 16);
	LOGMSG(DBG_LEVEL_I, "STB IP is %s!!\n", mStbIP);

	SAFE_STRNCPY(mNetGate, rootnode.GetAttrStrValue("NETGATE", mNetGate), 16);
	LOGMSG(DBG_LEVEL_I, "Device net gate is %s!!\n", mNetGate);

	SAFE_STRNCPY(mNetMask, rootnode.GetAttrStrValue("NETMASK", mNetMask), 16);
	LOGMSG(DBG_LEVEL_I, "Device net mask is %s!!\n", mNetMask);

	SAFE_STRNCPY(mDNS0, rootnode.GetAttrStrValue("DNS0", mDNS0), 16);
	LOGMSG(DBG_LEVEL_I, "Device DNS0 is %s!!\n", mDNS0);

	SAFE_STRNCPY(mDNS1, rootnode.GetAttrStrValue("DNS1", mDNS1), 16);
	LOGMSG(DBG_LEVEL_I, "Device DNS1 is %s!!\n", mDNS1);

	SAFE_STRNCPY(mServerIP, rootnode.GetAttrStrValue("SERVERIP", mServerIP), 16);
	LOGMSG(DBG_LEVEL_I, "Server IP is %s!!\n", mServerIP);

	SAFE_STRNCPY(mVodIP, rootnode.GetAttrStrValue("VODIP", mVodIP), 16);
	LOGMSG(DBG_LEVEL_I, "VOD IP is %s!!\n", mVodIP);

	SAFE_STRNCPY(mRoomName, rootnode.GetAttrStrValue("ROOMNAME", mRoomName), 32);
	LOGMSG(DBG_LEVEL_I, "Room name is %s!!\n", mRoomName);

	rootnode.GetAttrUInt32Value("SERVERPORT", &mServerPort);
	LOGMSG(DBG_LEVEL_I, "Server Port is %d!!\n", mServerPort);

	rootnode.GetAttrUInt32Value("FORCEUSESTBSTREAM", &mForceUseSTBStream);
	LOGMSG(DBG_LEVEL_I, "Force use STBStream play is %s!!\n", mForceUseSTBStream?"TRUE":"FALSE");

	rootnode.GetAttrUInt32Value("ISVERIFIED", &mIsVerified);
	LOGMSG(DBG_LEVEL_I, "config file vaild is %s!!\n", mIsVerified?"TRUE":"FALSE");

	// 初始化随机数
	if (mMonkeyMode)
	{
		srand(mMonkeySeed);
	}
	else
	{
		srand(GetTickCount());
	}
}

void CKTVConfig::SetDisplaySize(
	int nWidth,
	int nHeight)
{
	mDisplayWidth = nWidth;
	mDisplayHeight = nHeight;
}

int CKTVConfig::GetDisplayWidth()
{
	return mDisplayWidth;
}

int CKTVConfig::GetDisplayHeight()
{
	return mDisplayHeight;
}

const char* CKTVConfig::GetProgramFolder()
{
	return mProgramFolder;
}

const char* CKTVConfig::GetTempFolderPath()
{
	return mTempFolderPath;
}

BOOL CKTVConfig::IsMonkeyMode()
{
	return mMonkeyMode;
}

UINT64 CKTVConfig::GetMonkeyInterval()
{
	return mMonkeyInterval;
}

const char* CKTVConfig::GetFontName()
{
	return mFontName;
}

PLTFORMAT CKTVConfig::GetPLTFormat()
{
	return mPLTFormat;
}

void CKTVConfig::SetPLTFormat(
	PLTFORMAT ePLTFormat)
{
	if (ePLTFormat == mPLTFormat)
	{
		return;
	}

	mPLTFormat = ePLTFormat;

	if (!mMonkeyMode)
	{
		XMLNode rootnode;
		mKTVConfigParser.GetNode("STBCfg", &rootnode);
		rootnode.AddIntAttribute("PLTFORMAT", mPLTFormat);
		mKTVConfigParser.SaveToFile(mConfigFileName);
	}
}

int CKTVConfig::GetMainVolume()
{
	return mMainVolume;
}

void CKTVConfig::SetMainVolume(
	int nVolume)
{
	if (nVolume == mMainVolume)
	{
		return;
	}

	mMainVolume = nVolume;

	if (!mMonkeyMode)
	{
		XMLNode rootnode;
		mKTVConfigParser.GetNode("STBCfg", &rootnode);
		rootnode.AddIntAttribute("MAINVOLUME", mMainVolume);
		mKTVConfigParser.SaveToFile(mConfigFileName);
	}
}

int CKTVConfig::GetPcmVolume()
{
	return mPcmVolume;
}

void CKTVConfig::SetPcmVolume(
	int nVolume)
{
	if (nVolume == mPcmVolume)
	{
		return;
	}

	mPcmVolume = nVolume;

	if (!mMonkeyMode)
	{
		XMLNode rootnode;
		mKTVConfigParser.GetNode("STBCfg", &rootnode);
		rootnode.AddIntAttribute("PCMVOLUME", mPcmVolume);
		mKTVConfigParser.SaveToFile(mConfigFileName);
	}
}

int CKTVConfig::GetMicVolume()
{
	return mMicVolume;
}

void CKTVConfig::SetMicVolume(
	int nVolume)
{
	if (nVolume == mMicVolume)
	{
		return;
	}

	mMicVolume = nVolume;

	if (!mMonkeyMode)
	{
		XMLNode rootnode;
		mKTVConfigParser.GetNode("STBCfg", &rootnode);
		rootnode.AddIntAttribute("MICVOLUME", mMicVolume);
		mKTVConfigParser.SaveToFile(mConfigFileName);
	}
}

const char* CKTVConfig::GetStbIP()
{
	return mStbIP;
}

void CKTVConfig::SetStbIP(
	const char *cStbIP)
{
	if (!cStbIP)
	{
		return;
	}

	if (strncmp(mStbIP, cStbIP, 15) == 0)
	{
		return;
	}

	SAFE_STRNCPY(mStbIP, cStbIP, 16);

	if (!mMonkeyMode)
	{
		XMLNode rootnode;
		mKTVConfigParser.GetNode("STBCfg", &rootnode);
		rootnode.AddStringAttribute("STBIP", mStbIP);
		mKTVConfigParser.SaveToFile(mConfigFileName);
	}
}

const char* CKTVConfig::GetMacAddr()
{
	return mMacAddr;
}

const char* CKTVConfig::GetNetGate()
{
	return mNetGate;
}

void CKTVConfig::SetNetGate(
	const char *cNetGate)
{
	if (!cNetGate)
	{
		return;
	}

	if (strncmp(mNetGate, cNetGate, 15) == 0)
	{
		return;
	}

	SAFE_STRNCPY(mNetGate, cNetGate, 16);

	if (!mMonkeyMode)
	{
		XMLNode rootnode;
		mKTVConfigParser.GetNode("STBCfg", &rootnode);
		rootnode.AddStringAttribute("NETGATE", mNetGate);
		mKTVConfigParser.SaveToFile(mConfigFileName);
	}
}

const char* CKTVConfig::GetNetMask()
{
	return mNetMask;
}

void CKTVConfig::SetNetMask(
	const char *cNetMask)
{
	if (!cNetMask)
	{
		return;
	}

	if (strncmp(mNetMask, cNetMask, 15) == 0)
	{
		return;
	}

	SAFE_STRNCPY(mNetMask, cNetMask, 16);

	if (!mMonkeyMode)
	{
		XMLNode rootnode;
		mKTVConfigParser.GetNode("STBCfg", &rootnode);
		rootnode.AddStringAttribute("NETMASK", mNetMask);
		mKTVConfigParser.SaveToFile(mConfigFileName);
	}
}


const char* CKTVConfig::GetDNS0()
{
	return mDNS0;
}

void CKTVConfig::SetDNS0(
	const char *cDNS)
{
	if (!cDNS)
	{
		return;
	}

	if (strncmp(mDNS0, cDNS, 15) == 0)
	{
		return;
	}

	SAFE_STRNCPY(mDNS0, cDNS, 16);

	if (!mMonkeyMode)
	{
		XMLNode rootnode;
		mKTVConfigParser.GetNode("STBCfg", &rootnode);
		rootnode.AddStringAttribute("DNS0", mDNS0);
		mKTVConfigParser.SaveToFile(mConfigFileName);
	}
}

const char* CKTVConfig::GetDNS1()
{
	return mDNS1;
}

void CKTVConfig::SetDNS1(
	const char *cDNS)
{
	if (!cDNS)
	{
		return;
	}

	if (strncmp(mDNS1, cDNS, 15) == 0)
	{
		return;
	}

	SAFE_STRNCPY(mDNS1, cDNS, 16);

	if (!mMonkeyMode)
	{
		XMLNode rootnode;
		mKTVConfigParser.GetNode("STBCfg", &rootnode);
		rootnode.AddStringAttribute("DNS1", mDNS1);
		mKTVConfigParser.SaveToFile(mConfigFileName);
	}
}


const char* CKTVConfig::GetServerIP()
{
	return mServerIP;
}

void CKTVConfig::SetServerIP(
	const char *cServerIP)
{
	if (!cServerIP)
	{
		return;
	}

	if (strncmp(mServerIP, cServerIP, 15) == 0)
	{
		return;
	}

	SAFE_STRNCPY(mServerIP, cServerIP, 16);

	if (!mMonkeyMode)
	{
		XMLNode rootnode;
		mKTVConfigParser.GetNode("STBCfg", &rootnode);
		rootnode.AddStringAttribute("SERVERIP", mServerIP);
		mKTVConfigParser.SaveToFile(mConfigFileName);
	}
}

const char* CKTVConfig::GetVodIP()
{
	return mVodIP;
}

void CKTVConfig::SetVodIP(
	const char *cVodIP)
{
	if (!cVodIP)
	{
		return;
	}

	if (strncmp(mVodIP, cVodIP, 15) == 0)
	{
		return;
	}

	SAFE_STRNCPY(mVodIP, cVodIP, 16);

	if (!mMonkeyMode)
	{
		XMLNode rootnode;
		mKTVConfigParser.GetNode("STBCfg", &rootnode);
		rootnode.AddStringAttribute("VODIP", mVodIP);
		mKTVConfigParser.SaveToFile(mConfigFileName);
	}
}

const char* CKTVConfig::GetRoomName()
{
	return mRoomName;
}

void CKTVConfig::SetRoomName(
	const char *cRoomName)
{
	if (!cRoomName)
	{
		return;
	}

	if (strncmp(mRoomName, cRoomName, 31) == 0)
	{
		return;
	}

	SAFE_STRNCPY(mRoomName, cRoomName, 32);

	if (!mMonkeyMode)
	{
		XMLNode rootnode;
		mKTVConfigParser.GetNode("STBCfg", &rootnode);
		rootnode.AddStringAttribute("ROOMNAME", mRoomName);
		mKTVConfigParser.SaveToFile(mConfigFileName);
	}
}

int CKTVConfig::GetServerPort()
{
	return mServerPort;
}

void CKTVConfig::SetServerPort(int port)
{
	mServerPort = port;
	if (!mMonkeyMode)
	{
		XMLNode rootnode;
		mKTVConfigParser.GetNode("STBCfg", &rootnode);
		rootnode.AddIntAttribute("SERVERPORT", mServerPort);
		mKTVConfigParser.SaveToFile(mConfigFileName);
	}
}

BOOL CKTVConfig::IsForceUseSTBStream()
{
	return mForceUseSTBStream;
}

void CKTVConfig::SetConfigFileValid(BOOL valid)
{
	mIsVerified = valid;
	if (!mMonkeyMode)
	{
		XMLNode rootnode;
		mKTVConfigParser.GetNode("STBCfg", &rootnode);
		rootnode.AddIntAttribute("ISVERIFIED", mIsVerified);
		mKTVConfigParser.SaveToFile(mConfigFileName);
	}
}

BOOL CKTVConfig::IsConfigFileValid()
{
	return mIsVerified;
}
