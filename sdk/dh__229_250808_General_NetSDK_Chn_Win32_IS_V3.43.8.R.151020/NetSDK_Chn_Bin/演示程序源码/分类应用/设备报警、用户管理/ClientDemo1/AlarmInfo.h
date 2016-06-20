// AlarmInfo.h: interface for the CAlarmInfo class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ALARMINFO_H__720FA033_A07C_4017_9730_C5CDD93D14D5__INCLUDED_)
#define AFX_ALARMINFO_H__720FA033_A07C_4017_9730_C5CDD93D14D5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include"dhnetsdk.h"
//Input channel alarm 
typedef WORD                 VIDEO_ALARM_INPUTALARM;
/*
 * VIDEO_ALARM_INPUTALARM Commands
 */
#define VIDEO_AI_CHANNEL0		1
#define VIDEO_AI_CHANNEL1		2
#define VIDEO_AI_CHANNEL2		4
#define VIDEO_AI_CHANNEL3		8
#define VIDEO_AI_CHANNEL4		16
#define VIDEO_AI_CHANNEL5		32
#define VIDEO_AI_CHANNEL6		64
#define VIDEO_AI_CHANNEL7		128
#define VIDEO_AI_CHANNEL8		256
#define VIDEO_AI_CHANNEL9		512
#define VIDEO_AI_CHANNEL10		1024
#define VIDEO_AI_CHANNEL11		2048
#define VIDEO_AI_CHANNEL12		4096
#define VIDEO_AI_CHANNEL13		8192
#define VIDEO_AI_CHANNEL14		16384
#define VIDEO_AI_CHANNEL15		32768

//Video loss alarm 
typedef WORD                 VIDEO_ALARM_VIDEOLOST;
/*
 * VIDEO_ALARM_VIDEOLOST Commands
 */
#define VIDEO_AV_CHANNEL0		1
#define VIDEO_AV_CHANNEL1		2
#define VIDEO_AV_CHANNEL2		4
#define VIDEO_AV_CHANNEL3		8
#define VIDEO_AV_CHANNEL4		16
#define VIDEO_AV_CHANNEL5		32
#define VIDEO_AV_CHANNEL6		64
#define VIDEO_AV_CHANNEL7		128
#define VIDEO_AV_CHANNEL8		256
#define VIDEO_AV_CHANNEL9		512
#define VIDEO_AV_CHANNEL10		1024
#define VIDEO_AV_CHANNEL11		2048
#define VIDEO_AV_CHANNEL12		4096
#define VIDEO_AV_CHANNEL13		8192
#define VIDEO_AV_CHANNEL14		16384
#define VIDEO_AV_CHANNEL15		32768

//Motion detection alarm 
typedef WORD                 VIDEO_ALARM_MOTION;
/*
 * VIDEO_ALARM_MOTION Commands
 */
#define VIDEO_AM_CHANNEL0		1
#define VIDEO_AM_CHANNEL1		2
#define VIDEO_AM_CHANNEL2		4
#define VIDEO_AM_CHANNEL3		8
#define VIDEO_AM_CHANNEL4		16
#define VIDEO_AM_CHANNEL5		32
#define VIDEO_AM_CHANNEL6		64
#define VIDEO_AM_CHANNEL7		128
#define VIDEO_AM_CHANNEL8		256
#define VIDEO_AM_CHANNEL9		512
#define VIDEO_AM_CHANNEL10		1024
#define VIDEO_AM_CHANNEL11		2048
#define VIDEO_AM_CHANNEL12		4096
#define VIDEO_AM_CHANNEL13		8192
#define VIDEO_AM_CHANNEL14		16384
#define VIDEO_AM_CHANNEL15		32768

//Camera masking alarm 
typedef WORD                 VIDEO_ALARM_SHELTER;
/*
 * VIDEO_ALARM_SHELTER Commands
 */
#define VIDEO_AS_CHANNEL0		1
#define VIDEO_AS_CHANNEL1		2
#define VIDEO_AS_CHANNEL2		4
#define VIDEO_AS_CHANNEL3		8
#define VIDEO_AS_CHANNEL4		16
#define VIDEO_AS_CHANNEL5		32
#define VIDEO_AS_CHANNEL6		64
#define VIDEO_AS_CHANNEL7		128
#define VIDEO_AS_CHANNEL8		256
#define VIDEO_AS_CHANNEL9		512
#define VIDEO_AS_CHANNEL10		1024
#define VIDEO_AS_CHANNEL11		2048
#define VIDEO_AS_CHANNEL12		4096
#define VIDEO_AS_CHANNEL13		8192
#define VIDEO_AS_CHANNEL14		16384
#define VIDEO_AS_CHANNEL15		32768

//Audio alarm 
typedef WORD                 VIDEO_ALARM_SOUNDDETECT;
/*
 * VIDEO_ALARM_SOUNDDETECT Commands
 */
#define VIDEO_SD_CHANNEL0		1
#define VIDEO_SD_CHANNEL1		2
#define VIDEO_SD_CHANNEL2		4
#define VIDEO_SD_CHANNEL3		8
#define VIDEO_SD_CHANNEL4		16
#define VIDEO_SD_CHANNEL5		32
#define VIDEO_SD_CHANNEL6		64
#define VIDEO_SD_CHANNEL7		128
#define VIDEO_SD_CHANNEL8		256
#define VIDEO_SD_CHANNEL9		512
#define VIDEO_SD_CHANNEL10		1024
#define VIDEO_SD_CHANNEL11		2048
#define VIDEO_SD_CHANNEL12		4096
#define VIDEO_SD_CHANNEL13		8192
#define VIDEO_SD_CHANNEL14		16384
#define VIDEO_SD_CHANNEL15		32768

//HDD malfunction alarm 
typedef DWORD                 VIDEO_ALARM_DISKERROR;
/*
 * VIDEO_ALARM_DISKERROR Commands
 */
#define VIDEO_DR_DISK0			1
#define VIDEO_DR_DISK1			2
#define VIDEO_DR_DISK2			4
#define VIDEO_DR_DISK3			8
#define VIDEO_DR_DISK4			16
#define VIDEO_DR_DISK5			32
#define VIDEO_DR_DISK6			64
#define VIDEO_DR_DISK7			128
#define VIDEO_DR_DISK8			256
#define VIDEO_DR_DISK9			512
#define VIDEO_DR_DISK10		1024
#define VIDEO_DR_DISK11		2048
#define VIDEO_DR_DISK12		4096
#define VIDEO_DR_DISK13		8192
#define VIDEO_DR_DISK14		16384
#define VIDEO_DR_DISK15		32768
#define VIDEO_DR_DISK16		65536
#define VIDEO_DR_DISK17		131072
#define VIDEO_DR_DISK18		262144
#define VIDEO_DR_DISK19		524288
#define VIDEO_DR_DISK20		1048576
#define VIDEO_DR_DISK21		2097152
#define VIDEO_DR_DISK22		4194304
#define VIDEO_DR_DISK23		8388608
#define VIDEO_DR_DISK24		16777216
#define VIDEO_DR_DISK25		33554432
#define VIDEO_DR_DISK26		67108864
#define VIDEO_DR_DISK27		134217728
#define VIDEO_DR_DISK28		268435456
#define VIDEO_DR_DISK29		536870912
#define VIDEO_DR_DISK30		1073741824
#define VIDEO_DR_DISK31		2147483648

//HDD insufficient capacity alarm 
typedef BOOL                 VIDEO_ALARM_DISKFULL;

typedef enum	{
	//VIDEO_INPUT_ALARM,
	//VIDEO_VIDEOLOST_ALARM,
	VIDEO_COMMON_ALARM,
	VIDEO_VIDEOSHELTER_ALARM,
	//VIDEO_MOTIONDETECT_ALARM,
	VIDEO_SOUNDDETECT_ALARM,
	VIDEO_DISKFULL_ALARM,
	VIDEO_DISKERROR_ALARM,
	VIDEO_OTHER_ALARM,
}EN_DVR_ALARMTYPE;
//New alarm protocol type 
typedef enum 
{
	VIDEO_ALARM_ALARMEX,//External alarm 
	VIDEO_MOTIONDETECT_ALARMEX,//Motion detection alarm 
	VIDEO_VEDIOSHELTER_ALARMEX,//Video loss alarm 
	VIDEO_SHELTER_ALARMEX,//Camera masking alarm 
	VIDEO_SOUNDDETECT_ALARMEX,//Audio detectino alarm
	VIDEO_DISKFULL_ALARMEX,//HDD full alarm 
	VIDEO_DISKERROR_ALARMEX,//HDD malfunction alarm 
	VIDEO_ENCODER_ALARMEX,//Encoder alarm 
	VIDEO_URGENCY_ALARMEX,//Emergency alarm 
	VIDEO_WIRELESS_ALARMEX,//Wireless alarm 
	VIDEO_ALARM_DECODER_ALARMEX,//Alarm decoder alarm 
	VIDEO_STATIC_ALARMEX, // static alarm
	VIDEO_ALARM_ARM_DISARMSTATE,//Alarm arm disarm state 
	VIDEO_ALARM_NONE//No alarm. To initialize.
}EN_DVR_ALARMTYPE_EX;


class CAlarmInfo  
{
// Construction
public:
	CAlarmInfo();
	virtual ~CAlarmInfo();

public:
	//Alarm type 
	EN_DVR_ALARMTYPE m_AlarmCommand;
	//HDD insufficient capacity alarm 
	VIDEO_ALARM_DISKFULL m_DiskFull;
	//HDD malfunction alarm 
	VIDEO_ALARM_DISKERROR m_DiskError;
	//Audio alarm 
	VIDEO_ALARM_SOUNDDETECT m_SoundDetect;
	//Camera masking alarm 
	VIDEO_ALARM_SHELTER m_ShelterAlarm;
	//Motion detection alarm 
	VIDEO_ALARM_MOTION m_MotionDetect;
	//Video loass alarm 
	VIDEO_ALARM_VIDEOLOST m_VideoLost;
	//Input channel alarm 
	VIDEO_ALARM_INPUTALARM m_InputAlarm;
	//DVR alarm input channel amount 
	int m_nAlarmInputCount;
	//DVR video input channel amount 
	int m_nChannelCount;

};
class CAlarmInfoEx
{
public:
	CAlarmInfoEx();
	virtual ~CAlarmInfoEx();
public:
	//Alarm type 
	EN_DVR_ALARMTYPE_EX		m_AlarmCommand;
	BYTE					m_dwAlarm[32];
	DH_NEW_SOUND_ALARM_STATE	m_stuNewSound;
	ALARM_DECODER_ALARM		m_stuAlarmDecoderAlarm;
	//DVR alarm input channel amount 
	int m_nAlarmInputCount;
	//DVR video input channel amount 
	int m_nChannelCount;
	ALARM_ARM_DISARM_STATE_INFO m_stuAlarmArmDisarmstate;
};
#endif // !defined(AFX_ALARMINFO_H__720FA033_A07C_4017_9730_C5CDD93D14D5__INCLUDED_)





















