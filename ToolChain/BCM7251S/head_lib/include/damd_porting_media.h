/*************************************************************************
                             All Rights Reserved
                                 R&D Dept.
*************************************************************************/


/*************************************************************************

Filename:       damd_porting_media.h

Description:    媒体信息相关定义

Author:         

Date:            

Modify Log:      
 ------------------------------------------------------------------------
1.
 修改人  :                           
 修改时间:
 修改原因:
 修改方法:
 ------------------------------------------------------------------------
2.
 修改人  :                           
 修改时间:
 修改原因:
 修改方法:
 ------------------------------------------------------------------------
*************************************************************************/
#ifndef _WSD_AL_MEDIA_H_
#define _WSD_AL_MEDIA_H_

#ifdef __cplusplus
extern "C" {
#endif

/***********************************************************************
*                                包含头文件
************************************************************************/


/***********************************************************************
*                                常量定义
***********************************************************************/
/******************************************************************
描述: 媒体类型定义

成员:
    MEDIA_TYPE_UNKNOWN_E:
    
    MEDIA_TYPE_ES_E:
    
    MEDIA_TYPE_BES_E:
    
    MEDIA_TYPE_PES_E:
    
    MEDIA_TYPE_TS_E:
    
    MEDIA_TYPE_DSS_ES_E:

    MEDIA_TYPE_DSS_PES_E:
    
    MEDIA_TYPE_VOB_E:
    
    MEDIA_TYPE_ASF_E:
    
    MEDIA_TYPE_AVI_E:
    
    MEDIA_TYPE_MPEG1_E:
    
    MEDIA_TYPE_MP4_E:
    
    MEDIA_TYPE_MKV_E:
    
    MEDIA_TYPE_WAV_E:
    
    MEDIA_TYPE_MP4_FRAGMENT_E:
    
    MEDIA_TYPE_FLV_E:
    
注意: 
******************************************************************/
typedef enum
{
    MEDIA_TYPE_UNKNOWN_E = 0, /**  **/
    MEDIA_TYPE_ES_E,      /**  **/
    MEDIA_TYPE_BES_E,     /**  **/
    MEDIA_TYPE_PES_E,     /**  **/
    MEDIA_TYPE_TS_E,      /**  **/
    MEDIA_TYPE_DSS_ES_E,  /**  **/
    MEDIA_TYPE_DSS_PES_E, /**  **/
    MEDIA_TYPE_VOB_E,     /**  **/
    MEDIA_TYPE_ASF_E,     /**  **/
    MEDIA_TYPE_AVI_E,     /**  **/
    MEDIA_TYPE_MPEG1_E,   /**  **/
    MEDIA_TYPE_MP4_E,     /**  **/
    MEDIA_TYPE_MKV_E,     /**  **/
    MEDIA_TYPE_WAV_E,     /**  **/
    MEDIA_TYPE_MP4_FRAGMENT_E, /**  **/
    MEDIA_TYPE_FLV_E,     /**  **/
    MEDIA_TYPE_MAX_E      /**  **/
}MEDIA_TYPE_E;


/******************************************************************
描述: 视频编码类型定义

成员:
    VIDEO_CODEC_UNKNOWN_E      : Unknow Codec
    
    VIDEO_CODEC_MPEG1_E        : MPEG-1 Video (ISO/IEC 11172-2)
    
    VIDEO_CODEC_MPEG2_E        : MPEG-2 Video (ISO/IEC 13818-2)

    VIDEO_CODEC_MPEG4_PART2_E  : MPEG-4 Part 2 Video

    VIDEO_CODEC_H263_E         : H.263 Video. The value of the enum is not based on PSI standards.

    VIDEO_CODEC_H264_E         : H.264 (ITU-T) or ISO/IEC 14496-10/MPEG-4 AVC

    VIDEO_CODEC_H265_E         : H.265 HEVA for 4kx2k

    VIDEO_CODEC_AVS_E          : AVS coded video

    VIDEO_CODEC_VC1_E          : VC-1 Advanced Profile 

    VIDEO_CODEC_VC1_SM_E       : VC-1 Simple & Main Profile

    VIDEO_CODEC_H263_SORENSON_E: 

    VIDEO_CODEC_VP6_E          : 

    VIDEO_CODEC_DIVX311_E     : DivX 3.11 coded video 
    
注意: 
******************************************************************/
typedef enum
{
    VIDEO_CODEC_UNKNOWN_E       = 0x00 ,
    VIDEO_CODEC_MPEG1_E         = 0x01 ,  /** MPEG-1 Video (ISO/IEC 11172-2) **/
    VIDEO_CODEC_MPEG2_E         = 0x02 ,  /** MPEG-2 Video (ISO/IEC 13818-2) **/
    VIDEO_CODEC_MPEG4_PART2_E   = 0x10 ,  /** MPEG-4 Part 2 Video            **/
    VIDEO_CODEC_H263_E          = 0x1A ,  /** H.263 Video. The value of the enum is not based on PSI standards. **/
    VIDEO_CODEC_H264_E          = 0x1B ,  /** H.264 (ITU-T) or ISO/IEC 14496-10/MPEG-4 AVC                      **/
    VIDEO_CODEC_H265_E          = 0x1C ,  /** H.265 HEVA for 4kx2k**/
    VIDEO_CODEC_AVS_E           = 0x42 ,  /** AVS video                **/
    VIDEO_CODEC_VC1_E           = 0xEA ,  /** VC-1 Advanced Profile    **/
    VIDEO_CODEC_VC1_SM_E        = 0xEB ,  /** VC-1 Simple&Main Profile **/
    VIDEO_CODEC_H263_SORENSON_E = 0xF0 ,
    VIDEO_CODEC_VP6_E           = 0xF1 ,
    VIDEO_CODEC_DIVX311_E       = 0x311,  /** DivX 3.11 coded video    **/
    VIDEO_CODEC_MAX_E
}VIDEO_CODEC_E;


/******************************************************************
描述: 音频频编码类型定义

成员:
    AUDIO_CODEC_UNKNOWN_E      : Unknow Codec
    
    AUDIO_CODEC_MP3_E          : MPEG1/2, layer 3. 

    AUDIO_CODEC_11172_E        : MPEG1/2, layer 1/2. This does not support layer 3 (mp3). 

    AUDIO_CODEC_13818_E        : MPEG1/2, layer 1/2. This does not support layer 3 (mp3). 

    AUDIO_CODEC_AC3_PLUS_E     : Dolby Digital Plus (AC3+ or DDP) audio 

    AUDIO_CODEC_AAC_E          : Advanced audio coding. Part of MPEG-4  

    AUDIO_CODEC_AAC_PLUS_E     : AAC plus SBR. aka MPEG-4 High Efficiency (AAC-HE) 

    AUDIO_CODEC_AAC_PLUS_ADTS_E: AAC plus SBR. aka MPEG-4 High Efficiency (AAC-HE), with ADTS (Audio Data Transport Format) 

    AUDIO_CODEC_AAC_PLUS_LOAS_E: AAC plus SBR. aka MPEG-4 High Efficiency (AAC-HE), with LOAS (Low Overhead Audio Stream) 

    AUDIO_CODEC_AVS_E          : AVS Audio

    AUDIO_CODEC_AMR_E          : AMR Audio

    AUDIO_CODEC_AC3_E          : Dolby Digital AC3 audio            

    AUDIO_CODEC_DTS_E          : Digital Digital Surround sound.    

    AUDIO_CODEC_LPCM_HDDVD_E   : LPCM, HD-DVD mode                  

    AUDIO_CODEC_LPCM_BLURAY_E  : LPCM, Blu-Ray mode                 

    AUDIO_CODEC_DTS_HD_E       : Digital Digital Surround sound, HD 

    AUDIO_CODEC_WMA_STD_E      : WMA Standard                         

    AUDIO_CODEC_WMA_PRO_E      : WMA Professional                     

    AUDIO_CODEC_LPCM_DVD_E     : LPCM, DVD mode                     

    AUDIO_CODEC_PCM_E          : PCM audio - Generally used only with inputs such as SPDIF or HDMI. 

    AUDIO_CODEC_DRA_E          : 

注意: 
******************************************************************/
typedef enum
{
    AUDIO_CODEC_UNKNOWN_E       = 0x00,
    AUDIO_CODEC_MP3_E           = 0x01,  /** MPEG1/2, layer 3. **/
    AUDIO_CODEC_11172_E         = 0x03,  /** MPEG1/2, layer 1/2. This does not support layer 3 (mp3). **/
    AUDIO_CODEC_13818_E         = 0x04,  /** MPEG1/2, layer 1/2. This does not support layer 3 (mp3). **/
    AUDIO_CODEC_AC3_PLUS_E      = 0x06,  /** Dolby Digital Plus (AC3+ or DDP) audio **/
    AUDIO_CODEC_AAC_E           = 0x0F,  /** Advanced audio coding. Part of MPEG-4  **/
    AUDIO_CODEC_AAC_PLUS_E      = 0x11,  /** AAC plus SBR. aka MPEG-4 High Efficiency (AAC-HE) **/
    AUDIO_CODEC_AAC_PLUS_ADTS_E = 0x12,  /** AAC plus SBR. aka MPEG-4 High Efficiency (AAC-HE), with ADTS (Audio Data Transport Format) **/
    AUDIO_CODEC_AAC_PLUS_LOAS_E = 0x11,  /** AAC plus SBR. aka MPEG-4 High Efficiency (AAC-HE), with LOAS (Low Overhead Audio Stream) **/
    AUDIO_CODEC_AVS_E           = 0x43,  /** AVS Audio                          **/
	AUDIO_CODEC_AMR_E			= 0x45,  /** AMR Audio							**/
    AUDIO_CODEC_AC3_E           = 0x81,  /** Dolby Digital AC3 audio            **/
    AUDIO_CODEC_DTS_E           = 0x82,  /** Digital Digital Surround sound.    **/
    AUDIO_CODEC_LPCM_HDDVD_E    = 0x83,  /** LPCM, HD-DVD mode                  **/
    AUDIO_CODEC_LPCM_BLURAY_E   = 0x84,  /** LPCM, Blu-Ray mode                 **/
    AUDIO_CODEC_DTS_HD_E        = 0x85,  /** Digital Digital Surround sound, HD **/
    AUDIO_CODEC_WMA_STD_E       = 0x86,  /** WMA Standard                       **/  
    AUDIO_CODEC_WMA_PRO_E       = 0x87,  /** WMA Professional                   **/  
    AUDIO_CODEC_LPCM_DVD_E      = 0x88,  /** LPCM, DVD mode                     **/
    AUDIO_CODEC_PCM_E           = 0x89,  /** PCM audio - Generally used only with inputs such as SPDIF or HDMI. **/ 
    AUDIO_CODEC_DRA_E           = 0xda,
    AUDIO_CODEC_MAX_E
}AUDIO_CODEC_E;

/***********************************************************************
*                                全局宏定义
***********************************************************************/
#define MAX_AUDIO_STREAM (20) /** 音频流最大数目 **/


/***********************************************************************
*                                全局数据结构定义
***********************************************************************/
/******************************************************************
描述: 视频流信息定义

成员:
    VideoPid: 视频PID信息

    VideoCodec: 视频编码格式

    VideoWidth: 视频宽度

    VideoHeight: 视频高度

    VideoBitrate: 视频码率
    
注意: 
******************************************************************/
typedef struct _video_stream_t_
{
    D_UINT16      VideoPid;   /** 视频PID信息    **/
    VIDEO_CODEC_E VideoCodec; /** 视频编码格式   **/

    D_UINT16      VideoWidth;
    D_UINT16      VideoHeight;
    D_UINT32      VideoBitrate;
}VIDEO_STREAM_T;


/******************************************************************
描述: 音频流信息定义

成员:
    AudioPid: 音频PID信息

    AudioCodec: 音频编码格式
	
	AudioSampleRate: 音频采样率

	AudioSampleSize: 

	AudioBitrate:

注意: 
******************************************************************/
typedef struct _audio_stream_t_
{
    D_UINT16         AudioPid;         /** 音频PID信息         **/
    AUDIO_CODEC_E    AudioCodec;       /** 音频编码格式   **/
	
	D_UINT32         AudioSampleRate;  /* */
	D_UINT32         AudioSampleSize;  /* */
	D_UINT32         AudioBitrate;     /*  */
}AUDIO_STREAM_T;


/******************************************************************
描述: 媒体信息定义

成员:
    MediaType: 媒体类型

    VideoStream: 视频流信息

    AudioStream: 音频流信息

    AudioCount : 音频流数目
    
    duration: 播放总时长

注意: 
******************************************************************/
typedef struct __meida_param_t_
{
    MEDIA_TYPE_E   MediaType;
	
    VIDEO_STREAM_T VideoStream;
	
    AUDIO_STREAM_T AudioStream[MAX_AUDIO_STREAM];
    int            AudioCount;

	D_UINT16       PrcPid;
	D_UINT8        TimeStampEnabled;
	
	unsigned long  duration;
}MEDIA_PARAM_T;


/***********************************************************************
*                                导出函数
***********************************************************************/

                                     
#ifdef __cplusplus
}
#endif

#endif
