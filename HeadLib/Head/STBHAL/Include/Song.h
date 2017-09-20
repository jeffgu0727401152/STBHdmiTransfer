#pragma once

#include "types.h"
#include "SimpleString.h"

#define KTV_ID_LENGTH				9

#define SINGERFLAG_USERSINGER	0x10000000
#define SINGERFLAG_DELETED		0x00020000


#define SONGFLAG_NEWSONG				0x00000001
#define SONGFLAG_MOVIE						0x00000002
#define SONGFLAG_NOFILE						0x00000004
#define SONGFLAG_HDISKSONG				0x00000008
#define SONGFLAG_HD								0x00000010
#define SONGFLAG_USERSONG				0x10000000
#define SONGFLAG_UDISKSONG				0x20000000
#define SONGFLAG_CLOUDSONG			0x80000000
#define SONGFLAG_URLSONG					0x01000000
#define SONGFLAG_EXTERNALSONG		0x02000000
#define SONGFLAG_RECORDSONG			0x04000000
#define SONGFLAG_INVISIBLE				0x00010000
#define SONGFLAG_DELETED					0x00020000
#define SONGFLAG_DOWNLOADING		0x00040000


// 用户可以编辑的歌星范围
#define SINGERID_USER_START		90000000
#define SINGERID_USER_END		99990000

// 用户可以编辑的歌曲范围
#define SONGID_USER_START		90000000
#define SONGID_USER_END			99990000

// URL歌曲 SONGID 范围
#define SONGID_URL_START		99990001
#define SONGID_URL_END			99994900

// Record歌曲 SONGID 范围
#define SONGID_RECORD_START	99994901
#define SONGID_RECORD_END	99999900

#define SONGID_HDMIIN				99999910

#define SONG_FILE_TYPE ".mov;.mkv;.mpg;.mp4;.avi;.wmv;.3gp;.ts;.m2ts;.mp3;.wav;.vob;.dat;.T4AF"

// 特别注意：分割符有如下几种：',' '/' '+'
#define DBDATA_SEPERATOR	",/+"
#define DBDATA_SEPERATOR_LENGTH	3

#pragma pack(push)
#pragma pack(1)

typedef struct tagSONGINFO
{
	//歌曲ID
	char  cSongID[KTV_ID_LENGTH];

	// 歌曲属性
	UINT32 uSongFlag;

	//歌曲名字数
	short wWdCnt;

	//伴唱音轨
	// 1: 伴唱在音轨0或者左声道
	// 2: 伴唱在音轨1或者右声道
	short wMusicTrack;

	//默认音量
	short wVol;

	//最大音量
	short wMaxVol;

	//最小音量
	short wMinVol;

	// 歌曲点击率
	UINT32 uOrderTimes;

	// 奥斯卡解密需要使用, 目前已经不使用了
	short wUnused;

	// 文件长度
	UINT64 lFileSize;

	// 补齐内存按4对齐
	char unused[3];

	//歌曲名
	CSimpleStringA sSongName;

	//歌星名
	CSimpleStringA sSingerName;

	// 歌曲附加信息
	CSimpleStringA sExtraInfo;

	//文件路径
	CSimpleStringA sFilePath;

	// 字幕路径, V1.5 新增
	CSimpleStringA sSubtitlePath;

	//歌曲类型
	CSimpleStringA sSongType;

	//语种
	CSimpleStringA sLanguageType;

	//首字母
	CSimpleStringA sSpell;

	//首笔划
	CSimpleStringA sStroke;

	// extra info, 不保存在歌曲数据库中

	// 歌词
	CSimpleStringA sLyrics;
} SONGINFO;


typedef struct tagSINGERINFO
{
	//歌手ID
	char  cSingerID[KTV_ID_LENGTH];

	// 歌星属性
	UINT32 uSingerFlag;

	//歌星名字数
	short wWdCnt;

	//歌曲数量
	short wSongsCount;

	// 歌星点击率
	UINT32 uOrderTimes;

	// 补齐内存按4对齐
	char unused[3];

	//歌手名
	CSimpleStringA sSingerName;

	//歌手类型(港台/大陆，，，)
	CSimpleStringA sSingerType;

	//国家
	CSimpleStringA sNationality;

	//首字母
	CSimpleStringA sSpell;

	//首笔划
	CSimpleStringA sStroke;

	// 该歌星的歌曲列表
	CSimpleStringA sSongsID;
} SINGERINFO;

#pragma pack(pop)
