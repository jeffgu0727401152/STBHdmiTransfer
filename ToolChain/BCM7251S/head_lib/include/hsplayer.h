/**
* @file hsplayer.h
* @brief 
* @author lixz
* @version 1.5.0
* @date 2010-09-11
*/
#ifndef __HSPLAYER_H__
#define __HSPLAYER_H__

#include <unistd.h>
#include "hsdef.h"

#define HSPLAYER_CONFIG_FILE 	"/root/.hsconfig"
#define HSPLAYER_AUDIO_VOLUM_MAX  100
#define HSPLAYER_AUDIO_VOLUM_MIN  0
#define HSPLAYER_AUDIO_VOLUM_STEP 5  

#define HSPLAYER_FASTFORWARD_MIN   2
#define HSPLAYER_FASTFORWARD_MAX   32	/*2<<5=32*/
#define HSPLAYER_WMS_FASTFORWARD_MAX 8

#define HSPLAYER_MAX_NUM		3
#define PLAYER_DAEMON_MSG_LENGTH        512
#define HSPLAYER_MAX_URL_LEN 			512


#ifdef __cplusplus
extern "C"{
#endif

extern char *hsplayer_state_str[];
extern char *hsplayer_cmd_str[];

#define GO3C_PLAYER_MAIN    (0x00)
#define GO3C_PLAYER_PIP     (0x01)
#define GO3C_PLAYER_PCM     (0x02)
#define GO3C_PLAYER_MAX     (0x03)

#define GO3C_FILE_STREAM    (0x01)
#define GO3C_BUF_STREAM     (0x02)
#define GO3C_NET_STREAM     (0x03)
#define GO3C_LIVE_STREAM    (0x04)

#define GO3C_SCREEN_VGA_WIDTH    1280
#define GO3C_SCREEN_VGA_HEIGHT   720

typedef enum
{
	HSPLAYER_VOLUME0=0,
	HSPLAYER_VOLUME1,
	HSPLAYER_VOLUME2,
	HSPLAYER_VOLUME3,
	HSPLAYER_VOLUME4,
	HSPLAYER_VOLUME5,
	HSPLAYER_VOLUME6,
	HSPLAYER_VOLUME7,
	HSPLAYER_VOLUME8,
	HSPLAYER_VOLUME9,
	HSPLAYER_VOLUME10,
	HSPLAYER_VOLUME11,
	HSPLAYER_VOLUME12,
	HSPLAYER_VOLUME13,
	HSPLAYER_VOLUME14,
	HSPLAYER_VOLUME15 =100,
}hsplayer_volume_e;

typedef enum
{
    GO3C_STREAM_PLAYBACK_COMPLETE         = 2,
    GO3C_STREAM_FAST_FORWORD_COMPLETE     = 20,   //xKF50974 add for fastforword
    GO3C_STREAM_FAST_BACKWORD_COMPLETE    = 21,   //xKF50974 add for fast backword
    GO3C_STREAM_ERROR                     = 100,
    GO3C_STREAM_PARSE_ERROR				 = 101,
    GO3C_STREAM_SHOW_PIC                  = 200,
}go3c_stream_event_type;


typedef struct _go3c_file_header_buffer_
{
    char *pHeader;
    int   HeaderLen;
}GO3C_FILE_HEADER_BUF_T;

typedef int (*GO3C_STREAM_CALLBACK)(go3c_stream_event_type event);

typedef ssize_t (*GO3C_FILE_READ)(void *fd, void *buf,  size_t length);
typedef off_t (*GO3C_FILE_SEEK)(void *fd, off_t offset, int whence);
typedef int (*GO3C_FILE_BOUNDS)(void *fd, off_t *first, off_t *last);


typedef struct _go3c_stream_io_func_t_
{
    void *fd;

	GO3C_FILE_READ    pReadFunc;
	GO3C_FILE_SEEK    pSeekFunc;
	GO3C_FILE_BOUNDS  pBoundsFunc;
}GO3C_STREAM_IO_FUNC_T;

typedef struct _go3c_stream_param_t_
{
    	GO3C_FILE_HEADER_BUF_T HeaderBuf;
	GO3C_STREAM_IO_FUNC_T  DataFunc;
	GO3C_STREAM_IO_FUNC_T  IndexFunc;
}GO3C_STREAM_PARAM_T;


/* --------------------------------------------------------------------------*/
/**
* @brief player runing fsm states.
*/
/* ----------------------------------------------------------------------------*/
typedef enum
{
	HSPLAYER_STATE_ERROR=-1,
	HSPLAYER_STATE_FRIST=0,
	HSPLAYER_STATE_IDLE=HSPLAYER_STATE_FRIST,
	HSPLAYER_STATE_STARTING,
	HSPLAYER_STATE_PLAYING,
	HSPLAYER_STATE_PAUSE,
	/*HSPLAYER_STATE_SEEK,*/ /* Seek is a short time op, no this state */
	HSPLAYER_STATE_TRICK,
	HSPLAYER_STATE_STREAM_AUTHING,
	HSPLAYER_STATE_STREAM_AUTHED,
	HSPLAYER_STATE_LAST
}hsplayer_state_e;


/* --------------------------------------------------------------------------*/
/**
 * * @brief the running status of the player
 * */
/* ----------------------------------------------------------------------------*/
typedef struct
{
        hsplayer_state_e        state;            /*!< player fsm states  */
        BOOL                    encrypted;        /*!< encrytped */
        int                     current_audio;    /*!< current audio index */
        BOOL                    enable_sub;       /*!< enable subtitle */
        int                     current_sub;      /*!< current subtitle link */
        int                     bitrate;          /*!< bitrate of the stream kbits/s */
        char                    url[256];         /*!< url of the stream */
        unsigned int            position;         /*!< current postion in seconds.*/
        unsigned int            duration;         /*!< total length of the stream in secondes.*/
        //stream_info_t           stream_info;      /*!< stream information */
}hsplayer_running_status;


typedef enum
{
	HSPLAYER_CMD_FIRST,
	HSPLAYER_CMD_START=0,
	HSPLAYER_CMD_STOP,
	HSPLAYER_CMD_PAUSE,
	HSPLAYER_CMD_SEEK,
	HSPLAYER_CMD_TRICK,
	HSPLAYER_CMD_RESUME,
	HSPLAYER_CMD_REC_START,
	HSPLAYER_CMD_REC_PAUSE,
	HSPLAYER_CMD_REC_STOP,
	HSPLAYER_CMD_AUTH,
	HSPLAYER_CMD_VOLUM_UP,
	HSPLAYER_CMD_VOLUM_DOWN,
	HSPLAYER_CMD_AUDIO_MUTE,
	HSPLAYER_CMD_AUDIO_MODE,
	HSPLAYER_CMD_AUDIO_SELECT,
	HSPLAYER_CMD_SUB,
	HSPLAYER_CMD_SUB_SET,		/* can down by API */
	HSPLAYER_CMD_SUB_SELECT,
	HSPLAYER_CMD_STANDBY,
	HSPLAYER_CMD_EXIT,
	HSPLAYER_CMD_SKIP, /*qinjibo added for next/prev*/
	HSPLAYER_CMD_OPEN,
	HSPLAYER_CMD_LAST
}hsplayer_cmd_e;
/*
typedef enum
{
	HSPLAYER_IEVENT_FIST=HSPLAYER_CMD_LAST,
	HSPLAYER_IEVENT_DRM_AUTHED,
	HSPLAYER_IEVENT_DRM_AUTHING,
	HSPLAYER_IEVENT_DRM_AUTH_FAILED,
	HSPLAYER_IEVENT_ECM_KEY,
	HSPLAYER_IEVENT_LINK_DOWN,
	HSPLAYER_IEVENT_LINK_UP,
	HSPLAYER_IEVENT_HDMI_PLUGIN,
 	HSPLAYER_IEVENT_HDMI_PLUGOFF,
	HSPLAYER_IEVENT_LAST,
}hsplayer_ievent_e;
*/
/* --------------------------------------------------------------------------*/
/**
* @brief the command player can receive
*/
/* ----------------------------------------------------------------------------*/
typedef enum
{
 HSPLAYER_IEVENT_FIST=HSPLAYER_CMD_LAST,
 HSPLAYER_IEVENT_DRM_AUTHED,	/*!< drm authed*/
 HSPLAYER_IEVENT_DRM_AUTHING,	/*!< drm authing*/
 HSPLAYER_IEVENT_DRM_AUTH_FAILED,
 HSPLAYER_IEVENT_STREAM_AUTHED,
 HSPLAYER_IEVENT_STREAM_AUTHING,
 HSPLAYER_IEVENT_STREAM_AUTH_FAILED,
 HSPLAYER_IEVENT_ECM_KEY,
 HSPLAYER_IEVENT_LINK_DOWN,
 HSPLAYER_IEVENT_LINK_UP,
 HSPLAYER_IEVENT_HDMI_PLUGIN,
 HSPLAYER_IEVENT_HDMI_PLUGOFF,
 HSPLAYER_IEVENT_NEWSTREAM,
 HSPLAYER_IEVENT_ENDSTREAM,
 HSPLAYER_IEVENT_STREAM_CACHING,
 HSPLAYER_IEVENT_STREAM_CACHED,
 HSPLAYER_IEVENT_STREAM_READ_FIAL,
 HSPLAYER_IEVENT_RESTART,
 HSPLAYER_IEVENT_LAST,
}hsplayer_ievent_e;

typedef enum
{
	HSPLAYER_AUDIO_TRACK_L=0,
	HSPLAYER_AUDIO_TRACK_R,
	HSPLAYER_AUDIO_TRACK_STEREO,
	HSPLAYER_AUDIO_TRACK_MIX_STEREO,
}hsplayer_audio_mode_e;

typedef enum
{
	HSPLAYER_STOP_BLACK,       /*!< ,black      */ 
	HSPLAYER_STOP_LAST_FRAME,  /*!< ,last frame */
}hsplayer_stop_mode_e;


typedef enum
{
        HSPLAYER_SYNC_MODE_STC,
        HSPLAYER_SYNC_MODE_PCR,
        HSPLAYER_SYNC_MODE_AUDIO,
        HSPLAYER_SYNC_MODE_VIDEO,
        HSPLAYER_SYNC_MODE_NONE, 
}hsplayer_sync_mode_e;

typedef enum
{
        HSPLAYER_ERR_DROP_NONE,  /*display mosic*/
        HSPLAYER_ERR_DROP_PICTURE,/*drop error frame*/
        HSPLAYER_ERR_DROP_ALL,	/*drop all frame after error frame untile next I frame*/
}hsplayer_error_drop_mode_e;

typedef enum 
{
	HSPLAYER_PLAYBACK_PAUSE=0,
	HSPLAYER_PLAYBACK_LOOP=1
}hsplayer_playback_mode_e;

typedef struct
{
	hsplayer_sync_mode_e mode;
	unsigned int sync_limit ; /* ms */
}sync_settings_t;
typedef struct
{
	int 	index;/* player index */
	int 	cmd;
	int 	len;
	char 	param[PLAYER_DAEMON_MSG_LENGTH];
}hsplayer_msg_t;

/** @} */


typedef BOOL (*hsplayer_fsm)(int index,hsplayer_cmd_e cmd, void*params, int params_len);

/**********************************************************************
 * The following api provided by hsplayer , called by hsjse or other app 
 * to query player state info, return immediately no block
 * no action happen from player, only return state value
 ***********************************************************************/

/**
* @name player  module init
* @{ */

/* --------------------------------------------------------------------------*/
/**
* @brief Init the media ,include player.
* @returns 0 for OK,return 1 for hsmedia have inited ,other for error
*/
/* ----------------------------------------------------------------------------*/
int hs_media_init(void);


/* --------------------------------------------------------------------------*/
/**
* @brief uninit the media,include player.
*/
/* ----------------------------------------------------------------------------*/
void hs_media_uninit(void);
/* --------------------------------------------------------------------------*/
/**
* @brief init DRM
*
* @returns 0 for OK,other for error  
*/
/* ----------------------------------------------------------------------------*/
int  HsMedia_Init_DRM();
/**  @} */
int hsplayer_init();

/**
* @name player control
* @{ */
/* --------------------------------------------------------------------------*/
/**
 * * @brief start the player with certain url.
 * * - there's 3 decoders on system .
 * *	- hardware decoder0
 * *	- hardware decoder1 (base on platform)
 * *	- ffmepg soft decoder,
 * * . 
 * * - there's 5 windows on system
 * *    - HD main
 * *    - SD main
 * *    - HD sub
 * *    - SD sub
 * *    - ffmpeg graphics window on HD display,auto clone to SD display
 *   .
 * * - there's 2 playpump on system
 * *   - playpump0
 * *   - playpump1
 * * . 
 * * @param url the url to be played
 * * @param index of the player ,if -1 ,will auto select.
 * *
 * * @returns the index of the player ,-1 for error.
 * */
/* ----------------------------------------------------------------------------*/
int  hsplayer_start(int player_id,char*url,int type,hsplayer_playback_mode_e mode);

/**
* @brief stop the player ,return until release all player controled resources,
* 	include playpump,playback,decoder.
*
* @param player_id the index of the player.
* @param freeze stop mode.
*
* @returns 0 for error
*/
/* ----------------------------------------------------------------------------*/
BOOL hsplayer_stop(int player_id,hsplayer_stop_mode_e freeze);
/* --------------------------------------------------------------------------*/
/**
* @brief pause the player.
*
* @param player_id
*
* @returns 0 for error  
*/
/* ----------------------------------------------------------------------------*/
BOOL hsplayer_pause(int player_id);
/* --------------------------------------------------------------------------*/
/**
* @brief resume the player
*
* @param player_id
*
* @returns 0 for error  
*/
/* ----------------------------------------------------------------------------*/
BOOL hsplayer_resume(int player_id);

/* --------------------------------------------------------------------------*/
/**
* @brief set the player trick  
*
* @param player_id
* @param speed 2 -- 32 for fastward, -2 -- -32 for rewind
*
* @returns 0 for error  
*/
/* ----------------------------------------------------------------------------*/
BOOL hsplayer_trick(int player_id,int speed);
/* --------------------------------------------------------------------------*/
/**
* @brief seek to position
*
* @param player_id
* @param pos   seconds.
*
* @returns 0 for error  
*/
/* ----------------------------------------------------------------------------*/
BOOL hsplayer_seek(int player_id,int pos);

/* --------------------------------------------------------------------------*/
/**
* @brief set the player window rect.
*
* @param player_id
* @param window_id 0 for hd,1 for sd
* @param x
* @param y
* @param width
* @param height
*
* @returns 0  for error  
*/
/* ----------------------------------------------------------------------------*/
BOOL hsplayer_set_window_rect(int player_id,int window_id ,int x,int y,int width,int height);

/* --------------------------------------------------------------------------*/
/**
* @brief get the player window rect
*
* @param player_id
* @param window_id 0 for hd,1 for sd
* @param x
* @param y
* @param width
* @param height
*
* @returns true for OK,false for error  
*/
/* ----------------------------------------------------------------------------*/
BOOL hsplayer_get_window_rect(int player_id, int window_id, int *x, int *y, int *width, int *height);

/* --------------------------------------------------------------------------*/
/**
* @brief set the player window visible
*
* @param player_id
* @param window_id
* @param visible 1 for visible,0 for hide.
*
* @returns 0  for error  
*/
/* ----------------------------------------------------------------------------*/
BOOL hsplayer_set_window_visible(int player_id,int window_id ,int visible);
/* --------------------------------------------------------------------------*/
/**^M
 * @todo tobe test
 * * @brief set the player window content
 * *^M
 * * @param player_id
 * * @param window_id
 * * @param content_mode :
 * 	0:zoom   cut content
 * 	1:box    add bars
 * 	2:panscan  16.9 -> 4.3
 * 	3:full	 show all content
 * 	4:noliner 
 * *
 * * @returns 0  for error  ^M
 * */
/* ----------------------------------------------------------------------------*/
BOOL hsplayer_set_window_content(int player_id,int window_id ,int content);

/* --------------------------------------------------------------------------*/
/**
* @brief set the decoder visible .just hide the video render window. other continue.
*
* @param player_id
* @param visible 
*
* @returns 0  for error  
*/
/* ----------------------------------------------------------------------------*/
BOOL hsplayer_set_visible(int player_id,int visible);
/* --------------------------------------------------------------------------*/
/**
* @brief set the player zorder.
*
* @param player_id
* @param zorder 1 - 4.
*
* @returns 0  for error  
*/
/* ----------------------------------------------------------------------------*/
BOOL hsplayer_set_zorder(int player_id,BOOL zorder);

BOOL hsplayer_set_window_front(int index);
BOOL hsplayer_set_mixer(int player_id,BOOL enable);
/* --------------------------------------------------------------------------*/
/**
* @brief set the volume.
*
* @param player_id
* @param volume 0-100
*
* @returns 0 for error  
*/
/* ----------------------------------------------------------------------------*/

BOOL hsplayer_set_pcm_volume(int volume);
BOOL hsplayer_set_volume(int player_id,hsplayer_volume_e volume);
/* --------------------------------------------------------------------------*/
/**
* @brief get the volume
*
* @param player_id
*
* @returns 0  for error  
*/
/* ----------------------------------------------------------------------------*/
int  hsplayer_get_volume(int player_id);
/* --------------------------------------------------------------------------*/
/**
* @brief set the mute
*
* @param player_id
* @param mute  1 for mute,0 for unmute.
*
* @returns 0  for error  
*/
/* ----------------------------------------------------------------------------*/
BOOL hsplayer_set_mute(int player_id,int mute);


/* --------------------------------------------------------------------------*/
/**
* @brief set the audio track
*
* @param player_id
* @param audio_track 
*
* @returns 0  for error  
*/
/* ----------------------------------------------------------------------------*/
BOOL hsplayer_set_audio_track(int player_id,int audio_track);
/* --------------------------------------------------------------------------*/
/**
* @brief get the current audio track
*
* @param player_id
*
* @returns -1 for no audio ,other for the audio track
*/
/* ----------------------------------------------------------------------------*/
int hsplayer_get_audio_track(int player_id);
/* --------------------------------------------------------------------------*/
/**
* @brief set the subtitle track
*
* @param player_id
* @param subtitle_track
*
* @returns 0 for error  
*/
/* ----------------------------------------------------------------------------*/
BOOL hsplayer_set_subtitle_track(int player_id,int subtitle_track);
/* --------------------------------------------------------------------------*/
/**
* @brief get the current subtitle track
*
* @param player_id
*
* @returns -1 for no subtitle ,other for the subtitle track
*/
/* ----------------------------------------------------------------------------*/
int hsplayer_get_subtitle_track(int player_id);
/**  @} */

/* --------------------------------------------------------------------------*/
/**
* @brief set video visible or  invisible
*
* @param player_id
* @param visible : 1 visible 0:invisible
*
* @returns TRUE for OK,FALSE for error  
*/
/* ----------------------------------------------------------------------------*/
BOOL hsplayer_set_video_visible(int player_id,int visible);
BOOL hsplayer_set_trick_speed(int index,int speed);
void ffplayer_audio_callback(void *opaque, unsigned char *stream, int len);

/**
* @name player running info
* @{ */
/* --------------------------------------------------------------------------*/
/**
* @brief get the player running fsm states.
*
* @param player_id
*
* @returns hsplayer_state_e . 
*/
/* ----------------------------------------------------------------------------*/
hsplayer_state_e 	hsplayer_get_player_state(int player_id);
/* ----------------------------------------------------------------------------*/
/* --------------------------------------------------------------------------*/
/**
* @brief return the running status of the player
*
* @param player_id
* @param status	 output value, include running status
*
* @returns 0 for error  
*/
/* ----------------------------------------------------------------------------*/
BOOL hsplayer_get_player_running_status(int player_id,hsplayer_running_status *status);



/**  @} */

/**
 * * @name player  module third stream client
 * * @{ */

/* --------------------------------------------------------------------------*/
/**@todo tobe test
* @brief used by stream client to feed data to player.
*
* @param player_id
*
* @returns sent bytes 
*/
/* ----------------------------------------------------------------------------*/
int     hsplayer_feed_data(int player_id,void * data,int len );

/* --------------------------------------------------------------------------*/
/**
* @brief when in stream open got the stream information ,call this to tell the player.
*
* @returns 0 for OK,other for error  
*/
/* ----------------------------------------------------------------------------*/
int     hsplayer_set_authed(int player_id,int authed);
BOOL 	hsplayer_pump_resume(int player_id);
BOOL 	hsplayer_pump_seek(int player_id,unsigned int pos);
BOOL 	hsplayer_pump_trick(int player_id,int speed);



BOOL 			hsplayer_get_stream_auth_state(int index);
int 			hsplayer_get_playing_pos(int index);
int			hsplayer_get_playing_duration(int index);
int 			hsplayer_get_playing_trick_speed(int index);
int 			hsplayer_get_playing_trick_speed_max(int index);
BOOL			hsplayer_get_playing_sub_state(int index);
int			hsplayer_get_sub_id(int index,int sub_index);
int			hsplayer_get_sub_num(int index);
int			hsplayer_get_sub_type(int index,int sub_index);
int 			hsplayer_get_audio_id(int index,int audio_index);
int			hsplayer_get_audio_num(int index);
hsplayer_audio_mode_e	hsplayer_get_playing_audio_mode(int index);
BOOL			hsplayer_get_playing_audio_mute(int index);
int			hsplayer_get_playing_drm_id();
int			hsplayer_get_playing_drm_num();
BOOL 			hsplayer_get_hdmi_state();
int			hsplayer_get_url(int index,unsigned char *buf,int size);

/* --------------------------------------------------------------------------*/
/**
* @brief get playing video resolution 
*
* @param player_id
* @param width output value playing video width
* @param height output value playing video height
*
* @returns 0 for OK,other for error  
*/
/* ----------------------------------------------------------------------------*/
int hsplayer_get_resolution(int player_id,int *width, int *height);
/* --------------------------------------------------------------------------*/
/**
* @brief get playing video frame rate
*
* @param player_id
*
* @returns frame rate ,-1 for error  
*/
/* ----------------------------------------------------------------------------*/
int hsplayer_get_framerate(int player_id);
/* --------------------------------------------------------------------------*/
/**
* @brief get playing video codec
*
* @param player_id
*
* @returns video codec ,-1 for error  
*/
/* ----------------------------------------------------------------------------*/
int hsplayer_get_vcodec(int player_id);
/* --------------------------------------------------------------------------*/
/**
* @brief get playing audio codec
*
* @param player_id
*
* @returns audio codec,-1 for error  
*/
/* ----------------------------------------------------------------------------*/
int hsplayer_get_acodec(int player_id);
/* --------------------------------------------------------------------------*/
/**
* @brief get playing audio sample rate
*
* @param player_id
*
* @returns audio sample rate,-1 for error  
*/
/* ----------------------------------------------------------------------------*/
int hsplayer_get_samplerate(int player_id);
/* --------------------------------------------------------------------------*/
/**
* @brief get playing audio mode
*
* @param player_id
*
* @returns audio mode :"audio_left","audio_right","audio_both",NULL for error  
*/
/* ----------------------------------------------------------------------------*/
const char *hsplayer_get_amode(int player_id);
/* --------------------------------------------------------------------------*/
/**
* @brief set playing audio mode
*
* @param player_id
* @param mode audio mode :"audio_left","audio_right","audio_both",
*
* @returns 0 for OK,other for error  
*/
/* ----------------------------------------------------------------------------*/
int hsplayer_set_amode(int player_id,const char* mode);


/* --------------------------------------------------------------------------*/
/**
 * @todo :to be tested
* @brief set the player's A/V sync 
*
* @param player_id
* @param settings
*
* @returns 0 for OK,other for error  
*/
/* ----------------------------------------------------------------------------*/
int hsplayer_set_sync_settings(int player_id ,sync_settings_t settings);


/* --------------------------------------------------------------------------*/
/**
 * @todo :to be tested
* @brief set the players drop mode when decode error.
*
* @param player_id
* @param drop_mode
*
* @returns 0 for OK,other for error  
*/
/* ----------------------------------------------------------------------------*/
int hsplayer_set_error_drop_mode(int player_id ,hsplayer_error_drop_mode_e drop_mode);
/* --------------------------------------------------------------------------*/
/**
 *  @todo :to be tested
 * @brief 
 *
 * @param player_id
 *
 * @returns audio bitrate ,-1 for error 
 */
/* ----------------------------------------------------------------------------*/
int hsplayer_get_bitrate(int player_id);

/* --------------------------------------------------------------------------*/
/**
 *  @todo :to be tested
 * @brief 
 *
 * @param player_id
 *
 * @returns true is sync ,false no sync 
 */
/* ----------------------------------------------------------------------------*/
BOOL hsplayer_get_sync(int player_id);

int hsplayer_set_aspect_ratio(int display_id,int aspect_ratio);

/* --------------------------------------------------------------------------*/
/**
* @brief set the display format
*
* @param display  display handle 
* @param mode  output format 
*
* @return 0 for ok,other for error 
*/
/* ----------------------------------------------------------------------------*/
int hsplayer_set_format(int display_id,int format);
/* --------------------------------------------------------------------------*/
/**
* @brief get the display_format
*
* @param display display handle
*
* @return the display format,-1 for error
*/
/* ----------------------------------------------------------------------------*/
int hsplayer_get_format(int display_id);
/* --------------------------------------------------------------------------*/
/**
* @brief get program number from current stream
*
* @param player_id
*
* @return the program number
*/
/* ----------------------------------------------------------------------------*/
int hsplayer_get_program_num(int player_id);
/* --------------------------------------------------------------------------*/
/**
* @brief get the display_format
*
* @param player_id
* @param program index want to decode
*
* @return 0 for ok,-1 for error
*/
/* ----------------------------------------------------------------------------*/
int hsplayer_set_program(int player_id,int nprogram);
/* --------------------------------------------------------------------------*/
/**
* @brief check the playing stream is Live or not 
*
* @param player_id
*
* @return 1 for live stream,0 for not
*/
/* ----------------------------------------------------------------------------*/
int hsplayer_islive(int player_id);
/* --------------------------------------------------------------------------*/
/**
* @brief get the playing audio pid
*
* @param player_id
*
* @return audio pid
*/
/* ----------------------------------------------------------------------------*/
int hsplayer_get_cur_audio(int player_id);
/* --------------------------------------------------------------------------*/
/**
* @brief get the playing subtitle pid
*
* @param player_id
*
* @return subtitle pid
*/
/* ----------------------------------------------------------------------------*/
int hsplayer_get_cur_sub(int player_id);
/* --------------------------------------------------------------------------*/
/**
* @brief get the  playing dvb locked frequency
*
* @param player_id
*
* @return frequency
*/
/* ----------------------------------------------------------------------------*/
int hsplayer_get_playing_freq(int player_id);

BOOL hsplayer_dec_pause(int player_id);
BOOL hsplayer_dec_resume(int player_id);

/**********************************************************************
 * The following api provided by hsplayer , called by hsjse or other app 
 * to set some config info for hsplayer, sometime need hsplayer action to 
 * active this set api 
 ***********************************************************************/
BOOL	hsplayer_set_sub(int index,int pid,int enable);/*enable: 0:disable ,1:enable ,2:toggle*/
BOOL 	hsplayer_set_sub_track(int index,int subpid);
BOOL 	hsplayer_set_audio_mode(hsplayer_audio_mode_e mode);
BOOL 	hsplayer_set_audio_mute(int index,BOOL mute);
BOOL 	hsplayer_set_audio_volum_up(int index);
BOOL 	hsplayer_set_audio_volum_down(int index);
//BOOL 	hsplayer_set_audio_track(int index,int apid);
BOOL 	hsplayer_set_trick_speed_forward(int index);
BOOL 	hsplayer_set_trick_speed_backward(int index);
BOOL 	hsplayer_set_seek_pos(int pos);
int 	hsplayer_get_dlna_url(char *buf,int len);
int 	hsplayer_set_video_full(int player_id);
int 	HsPowerStandby(int status);

BOOL hsplayer_show_video_window(int index,int visible,int overgdi);

BOOL hsplayer_set_video_window(int index,int x, int y, int width, int height);
int hsplayer_set_alpha(int alpha);	
int hsplayer_set_callback(int index, GO3C_STREAM_CALLBACK pCallback);


#ifdef __cplusplus
}
#endif

#endif
