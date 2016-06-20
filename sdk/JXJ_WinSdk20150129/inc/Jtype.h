/*
 * Jtype.h
 *
 * Copyright (c) Shenzhen Jia Xin Jie Electronic Co.Ltd, 2011 ~ 2012.
 */


#ifndef _JTYPE_H_
#define _JTYPE_H_

#define J_COMMAND_PENDING           0xF0000000
#define J_COMMAND_COMPELTE          0x00000000

#define J_RESULT_SUCCEED            0x00000000   
#define J_RESULT_FAILED             0xFFFFFFFF   // (-1)
#define J_CODEC_CHANGED             0xFFFFFFFE   // (-2)
#define J_BUFFER_INSUFFICIENT       0xFFFFFFFD   // (-3)
#define J_NO_DATA                   0xFFFFFFFC   // (-4)
#define J_END_DATA                  0xFFFFFFFB   // (-5)
#define J_INVALD_TRANSPORT_TYPE     0xFFFFFFFA   // (-6)
#define J_FAILED_RTSP_SETUP         0xFFFFFFF9   // (-7)
#define J_FAILED_SEMAPHORE          0xFFFFFFF8   // (-8)
#define J_SOURCE_OPEN_AGAIN         0xFFFFFFF7   // (-9)
#define J_FAILED_RTSP_OPTION        0xFFFFFFF6   // (-10)
#define J_FAILED_RTSP_DESCRIBE      0xFFFFFFF5   // (-11)
#define J_FAILED_RTSP_PAUSE         0xFFFFFFF4   // (-12)
#define J_FAILED_RTSP_PLAY          0xFFFFFFF3   // (-13)
#define J_FAILED_RTSP_CLOSE         0xFFFFFFF2   // (-14)
#define J_FAILED_RTSP_SET_PARAMETER 0xFFFFFFF1   // (-15)
#define J_FAILED_RTSP_RECORD        0xFFFFFFF0   // (-16)

#define J_DEFAULT_COMMAND           0xFFFFFFEF   // (-17)
#define J_DEFAULT_COMMAND_RESULT    0xFFFFFFEE   // (-18)
#define J_INVALID_SEND_EVENT_HANDLE 0xFFFFFFED   // (-19)
#define J_INVALID_RECV_EVENT_HANDLE 0xFFFFFFEC   // (-20)
#define J_INVALID_SEND_EVENT        0xFFFFFFEB   // (-21)
#define J_INVALID_RECV_EVENT        0xFFFFFFEA   // (-22)
#define J_INVALID_URL               0xFFFFFFE9   // (-23)
#define J_FAILED_CREAT_EVENT_THREAD 0xFFFFFFE8   // (-24)

#define J_CUSSEED_REGISTER_MDS      0x00000000
#define J_FAILED_REGISTER_MDS       0xFFFFFFFF 
#define J_FAILED_PROXY_OFFLINE      0xFFFFFFFE  // 代理掉线

#define J_INVALID_HANDLE            0xFFFFFFFF

#define J_SUCCEED(val)         (((int)val) >= 0)
#define J_FAILED(val)          (((int)val) < 0)

#define J_TRUE   1
#define J_FALSE  0

typedef int   j_result_t;
typedef int   j_handle_t;
typedef int   j_boolean_t;

// 录像类型定义
#define J_REC_TYPE_TIMING        0x00000001 // 定时录像
#define J_REC_TYPE_ALARM         0x00000002 // 报警录像
#define J_REC_TYPE_MOTION_DETECT 0x00000004 // 移动侦测录像
#define J_REC_TYPE_ALL           0xFFFFFFFF // 全部

#define J_REC_VIDEO_MASK         0x00000001
#define J_REC_AUDIO_MASK         0x00000002
#define J_REC_AV_MASK            0x00000003

#define REC_VIDEO_IS_ENABLE(mask) (mask & J_REC_VIDEO_MASK)
#define REC_AUDIO_IS_ENABLE(mask) (mask & J_REC_AUDIO_MASK)

// 
#define FAILED_TO_CREATE_LIVESOURCE            1
#define FAILED_TO_INITIATE_LIVESOURCE          2
#define FAILED_TO_INITATE_SUBSESSIONS          3
#define FAILED_TO_CREATE_RECORD_SOURCE         4
#define FAILED_TO_ALLOCATE_PACKET_POOL         5

// win32环境下，4字节对齐时， 数据推到解码器有崩溃现象。
#ifdef WIN32
#pragma pack(push, 1)
#else
#pragma pack(push, 4)
#endif

/*
 * j_stream_type_t: 码流类型
 */
typedef enum _j_stream_type
{
  //j_unknown_stream = 0,  //rongp comment 13-3-2
  j_primary_stream,
  j_secondary_stream,
  j_third_stream,
  j_fourth_stream,
  j_picture = 100,
} j_stream_type_t;

/*
 * j_codec_type_t: 编码类型
 */
typedef enum _j_codec_type
{
  j_codec_unknown = 0,

  j_video_codec_start = 10,
  j_video_H264,
  j_video_MPEG4,
  j_video_MJPEG,
  j_video_codec_end,

  j_audio_codec_start = 20,
  j_audio_G711A,
  j_audio_G711U,
  j_audio_codec_end,

  j_private_codec_start = 30,
  j_hik_codec,
  j_ahua_codec,
  j_private_codec_end
} j_codec_type_t;

typedef enum _j_frame_type
{
  j_unknown_frame = 0,
  j_video_i_frame = 1,
  j_video_p_frame = 2,
  j_video_b_frame = 3,
  j_audio_frame   = 4,
  j_generic_frame = 5,  
  j_pic_frame     = 6,
  j_va_frame      = 7,
  j_end_frame     = 15    // 用于下载，回放通知客户端完毕
} j_frame_type_t;

/*图片格式*/
enum 
{
  PIC_JPG = 0x01,  // JPG
  PIC_BMP = 0x02   // BMP
};

typedef struct _j_video_frame_spec
{
  unsigned short width;     // 宽度
  unsigned short height;    // 高度
} j_video_frame_spec_t;

typedef struct _j_audio_frame_spec
{
  unsigned short fps;       // 音频帧率
  unsigned short reserved;  // 保留字段,对齐
} j_audio_frame_spec_t;

typedef struct _j_ext_frame_spec
{
  unsigned short fmt;       // 图片格式或视频分析帧格式
  unsigned short revered;
}j_ext_frame_spec_t;

typedef union _j_frame_spec
{
  j_video_frame_spec_t video_spec;
  j_audio_frame_spec_t audio_spec;
  j_ext_frame_spec_t   ext_spec;
} j_frame_spec_t;

typedef struct _j_frame
{
  unsigned long  magic_no;        // 0x0132DCA9 -- 20110505
  unsigned long  frame_num;       // 帧号
  unsigned long  frame_type;      // j_frame_type_t
  unsigned long  codec;           // j_codec_type_t
  j_frame_spec_t spec;         
  long           timestamp_sec;   // 时间戳，秒
  long           timestamp_usec;  // 时间戳，微秒
  long           size;            // 标识data[0]中的数据大小
  char           data[0];
} j_frame_t;


/*
 * j_video_info_t: 视频信息
 */
typedef struct _j_video_info
{
  j_codec_type_t   type;                    /* 视频码流类型，取值范围参考 av_type_t 定义 */
  unsigned short   width;                   /* 视频宽度                                  */
  unsigned short   height;                  /* 视频高度                                  */
  unsigned int     average_bit_per_sec;     /* 码流速率，单位: 位/秒                     */ 
  unsigned int     samples_per_sec;         /* 样本速率，单位: HZ, 如 90000 HZ           */
  unsigned char    average_frames_per_sec;  /* 帧率, 最大 255 帧/秒                      */

 /*
  * According to ITU.T Rec. H.264(05/2003, 03/2005)
  * Baseline profile    --  profile_idc = 66 
  * Main profile        --  profile_idc = 77
  * Extended profile    --  profile_idc = 88
  * High profile        --  profile_idc = 100  
  * High 10 profile     --  profile_idc = 110
  * High 4:2:2          --  profile_idc = 122
  * High 4:4:4 Predictive -- profile_idc = 144
  */
  //unsigned int     profile_idc;

  /*
   * Note:  According to ITU.T Rec. H.264(03/2005), page 206, "the syntax element
   *        level_idc equal to a value of ten times the level number specified in
   *        Table A-1."
   *
   * Chapter A.3 级别
   */
  //unsigned int     level;

  /*
   * For some use
   * extra_size identify the data leng in variable extra_data
   *
   * Scenario A.
   * When delivering H.264 video info, extra_data should be used to store SPS NAL and PPS NAL
   * +--------+--------+--------+--------+
   * |01234567|89012345|67890123|45678901| 
   * +--------+--------+--------+--------+   
   * |         NAL SIZE(4 bytes)         |
   * +--------+--------+--------+--------+
   * |    SPS NAL( without start code)   |
   * +--------+--------+--------+--------+
   * |         NAL SIZE(4 bytes)         |
   * +--------+--------+--------+--------+
   * |    PPS NAL( without start code)   |
   * +--------+--------+--------+--------+   
   *
   * Scenarion B.
   * When delivering MPEG4 video info, it will be .... (to be continued)
   */   
  unsigned long    extra_size;      // extra_data中有效数据的长度  
  unsigned char    extra_data[256];
} j_video_info_t;

/*
 * j_audio_info_t: 音频信息
 */
typedef struct _j_audio_info
{
  j_codec_type_t   type;                    /* 音频码流类型，取值范围参考 av_type_t 定义 */
  unsigned int     average_bit_per_sec;     /* 码流速率，单位: 位/秒                     */ 
  unsigned int     samples_per_sec;         /* 样本速率，单位: HZ, 如 90000 HZ           */
  unsigned short   bits_per_sample;         /* 每个样本的Bit                             */
  unsigned char    channel_num;             /* 音频通道数目, 如 1， 2                    */
  unsigned char    average_frames_per_sec;  /* 帧率，最大 255 fps                        */  
} j_audio_info_t;


/*
 * j_av_info_t: 联合体，音频或视频信息
 */ 
typedef union _j_av_info
{
  j_video_info_t video_info;
  j_audio_info_t audio_info;
} j_av_info_t;

/*
 * j_av_rec_info_t: 录像信息
 */
typedef struct _j_av_rec_info
{
  /* 
   * 掩码:标识音频有效或视频有效，二者可以"或"操作
   * 参考J_REC_XXXX_MASK 定义
   *
   * 0x00000001  视频有效
   * 0x00000002  音频有效
   * 0x00000003  音视频有效
   */
  unsigned int    rec_mask;    
  j_video_info_t  video_info;
  j_audio_info_t  audio_info;
} j_av_rec_info_t;

/*
 *
 */
typedef enum _j_sdp_type
{
  j_unknown_sdp = 0,
  j_sps_sdp,
  j_pps_sdp,
} j_sdp_type_t;

typedef enum j_rtp_transport_type
{
  j_rtp_over_tcp = 0,
  j_rtp_over_udp,
  j_rtp_over_rtsp,
  j_rtp_over_unknown = 0xFFFF
} j_rtp_transport_type_t;

typedef enum _j_video_format
{
  J_AVC1,   // H.264 bitstream without start codes.
  J_H264    // H.264 bitstream with start codes.
} j_video_format_t;

#pragma pack(pop)

#endif

