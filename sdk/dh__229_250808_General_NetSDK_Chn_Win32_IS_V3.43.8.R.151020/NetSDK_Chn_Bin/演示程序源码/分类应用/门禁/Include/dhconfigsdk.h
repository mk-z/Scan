
#ifndef DHCONFIGSDK_H
#define DHCONFIGSDK_H

#include "avglobal.h"
#if (defined(WIN32) || defined(WIN64))
#include <windows.h>
#ifdef CONFIGSDK_EXPORTS

#ifndef CLIENT_API
#define CLIENT_API  __declspec(dllexport) 
#endif

#else

#ifndef CLIENT_API
#define CLIENT_API  __declspec(dllimport)
#endif

#endif

#define CALLBACK __stdcall
#define CALL_METHOD  __stdcall  //__cdecl

#ifndef LLONG
#if (defined(WIN32) || defined(WIN64))
#ifdef WIN64
#define LLONG __int64
#else //WIN32 
#define LLONG LONG
#endif
#else	//linux
#define LLONG long 
#endif
#endif

#ifndef LDWORD
#if (defined(WIN32) || defined(WIN64))
#ifdef WIN64
#define LDWORD __int64
#else //WIN32 
#define LDWORD DWORD
#endif
#else	//linux
#define LDWORD long 
#endif
#endif

#else	//linux

#ifndef INTERNAL_COMPILE
#define CFG_RELEASE_HEADER //发布头文件
#endif

#ifndef CFG_RELEASE_HEADER 
#include "../Platform/platform.h"
#endif

#define CLIENT_API	extern "C"
#define CALL_METHOD
#define CALLBACK

#endif


#ifdef __cplusplus
extern "C" {
#endif

/************************************************************************
 ** 常量定义
 ***********************************************************************/

#define MAX_CHANNEL_COUNT		16
#define MAX_VIDEO_CHANNEL_NUM	256					// 最大通道数256
#define MAX_CHANNELNAME_LEN		64					// 最大通道名称长度
#define MAX_VIDEOSTREAM_NUM		3					// 最大码流个数
#define MAX_VIDEO_COVER_NUM		16					// 最大遮挡区域个数
#define WEEK_DAY_NUM			7					// 一周的天数
#define MAX_REC_TSECT			6					// 录像时间段个数
#define MAX_REC_TSECT_EX		10					// 录像时间段扩展个数
#define MAX_WATERMARK_LEN		4096				// 数字水印数据最大长度
#define MAX_MOTION_ROW			32					// 动态检测区域的行数
#define MAX_MOTION_COL			32					// 动态检测区域的列数
#define MAX_IMAGESIZE_NUM		256					// 最大支持的分辨率个数
#define MAX_FPS_NUM				1024				// 最大支持的帧率个数
#define MAX_QUALITY_NUM			32					// 最大支持的画质个数
#define MAX_ADDRESS_LEN			256					// 最大的地址长度
#define MAX_USERNAME_LEN		64					// 最大用户名长度
#define MAX_PASSWORD_LEN		64					// 最大密码长度
#define MAX_DIRECTORY_LEN		256					// 文件夹名字字符串长度
#define MAX_NAS_TIME_SECTION	2					// 网络存储时间段个数
#define MAX_NAME_LEN			128					// 通用名字字符串长度
#define MAX_DECPRO_LIST_SIZE	100					// 解码器协议列表个数上限
#define MAX_SCENE_LIST_SIZE		32					// 视频分析设备支持的场景类型列表个数上限
#define MAX_OBJECT_LIST_SIZE	16					// 视频分析设备支持的检测物体类型列表个数上限
#define MAX_RULE_LIST_SIZE		128					// 视频分析设备支持的规则列表个数上限
#define MAX_ANALYSE_MODULE_NUM	16					// 视频分析设备最大检测模块个数
#define MAX_ANALYSE_RULE_NUM	32					// 视频分析设备最大规则个数
#define MAX_POLYGON_NUM			20					// 视频分析设备区域顶点个数上限
#define MAX_POLYLINE_NUM		20					// 视频分析设备折线顶点个数上限
#define MAX_TEMPLATEREGION_NUM  32                  // 视频分析设备模拟区域信息点对个数上限
#define POINT_PAIR_NUM          2                   // 视频分析设备模拟区域点对包含的点个数
#define MAX_VEHICLE_SIZE_LIST	4					// 视频分析设备车辆大小个数上限
#define MAX_VEHICLE_TYPE_LIST	4					// 视频分析设备车辆类型个数上限
#define MAX_PLATE_TYPE_LIST		32					// 视频分析设备车牌类型个数上限
#define MAX_LANE_NUM            8                   // 视频分析设备每个通道对应车道数上限
#define MAX_STAFF_NUM           20                  // 视频分析设备每个通道对应的标尺数上限
#define MAX_CALIBRATEAREA_NUM   20					// 视频分析设备标定区域的上限
#define MAX_EXCLUDEREGION_NUM   10                  // 智能分析检测区域中需要排除的区域个数上限 
#define MAX_CALIBRATEBOX_NUM    10                  // 智能分析校准框个数上限
#define MAX_SPECIALDETECT_NUM    10                  // 智能分析特殊检测区域上限
#define MAX_HUMANFACE_LIST_SIZE	8					// 视频分析设备支持的人脸检测类型列表个数上限
#define	MAX_SEVER_NUM           16                  // 服务类型上限
#define MAX_SERVER_NAME_LEN     16                  // 服务名称字符串大小
#define MAX_POWER_NUM           8                   // 电源个数上限
#define MAX_FUN_NUM             8                   // 风扇个数上限
#define MAX_CPU_NUM             8                   // cpu个数上限
#define MAX_HARDDISK_NUM        32                  // 硬盘上限
#define MAX_TANK_NUM            16                  // 最大存储柜上限
#define MAX_CHAN_NUM            256                 // 最大通道数上限
#define MAX_RAID_NUM            16                  // 最大磁盘阵列上限
#define MAX_DEV_NUM             16                  // 最大设备上限
#define MAX_STORAGEPOOL_NUM     16                  // 最大存储池上限
#define MAX_STRORAGEPOS_NUM     16                  // 最大存储位置上限
#define	MAX_VIDEODEV_NUM        256                 // 前端设备上限
#define MAX_REMOTEDEVICENAME_LEN 32					// 最大远程设备名字长度
#define	MAX_REMOTE_DEV_NUM       256                 // 最大远程设备数量
#define MAX_PLATEHINT_NUM       8                   // 车牌字符暗示个数上限
#define MAX_LIGHT_NUM           8                   // 交通灯个数上限
#define MAX_LIGHTGROUP_NUM      8                   // 交通灯组个数上限
#define MAX_LIGHT_TYPE          8                   // 交通灯类型上限
#define MAX_LIGHT_DIRECTION     8                   // 交通灯指示方向数上限
#define MAX_TRIGGERMODE_NUM     32                  // 交通路口规则触发模式上限 
#define MAX_VIOLATIONCODE       16                  // 智能交通违章代码长度上限
#define MAX_DETECTOR            6                   // 智能交通车检器配置上限
#define MAX_COILCONFIG          3                   // 智能交通车检器线圈配置上限
#define MAX_DEVICE_ADDRESS      256                 // TrafficSnapshot智能交通设备地址
#define MAX_DEPARTMENT          256                 // Department智能交通设备所属单位
#define MAX_ROADWAYNO           128                 // 道路编号	由32个数字和字母构成
#define MAX_VIOLATIONCODE_DESCRIPT    64            // 智能交通违章代码长度上限
#define MAX_DRIVINGDIRECTION          256           // 行驶方向字符串长度
#define MAX_ACTIVEUSER_NUM            64            // 最大活动用户信息数
#define MAX_POLYGON_NUM10			10				// 视频分析设备区域顶点个数上限
#define MAX_VIDEODIAGNOSIS_DETECT_TYPE 11           // 视频诊断类型个数上限
#define MAX_ACTION_LIST_SIZE	16					// 视频分析设备支持的规则的动作类型列表个数上限
#define MAX_STORAGEGROUPNAME_LEN 32                 // 存储组名称缓冲区上限
#define MAX_CALIBRATEAREA_TYPE_NUM 4                // 标定区域类型上限
#define MAX_PROTOCOL_NAME_LEN	32					// 协议名称长度
#define	MAX_COMM_NUM			16					// 最大串口数量
#define MAX_DNS_SERVER_NUM		2					// DNS最大数量
#define MAX_NETWORK_INTERFACE_NUM	32				// 最大网卡数量
#define	MAX_NAS_NUM				16					// 网络存储服务器最大数量
#define MAX_STORAGEPOINT_NUM        32              // 录像存储点映射最大数量
#define MAX_TRACKSCENE_NUM          10              // 智能跟踪场景最大数量
#define MAX_STATUS_NUM          16                  // 交通设备状态最大个数
#define MAX_SERVICE_NUM         128                 // 服务器支持的最大服务数
#define MAX_DBKEY_NUM           64                  // 数据库关键字最大值
#define MAX_SUMMARY_LEN         1024                // 叠加到JPEG图片的摘要信息最大长度
#define MAX_MOTION_WINDOW       10                  // 动检支持的视频窗口值
#define MAX_OSD_SUMMARY_LEN     256                 // osd叠加内容最大长度    
#define MAX_OSD_TITLE_LEN       128                 // osd叠加标题最大长度
#define MAX_CUSTOMCASE_NUM      16                  // 自定义司法案件最大个数
#define MAX_GLOBAL_MSTERSLAVE_NUM   64              //主从式跟踪器最大全局配置数
#define MAX_OBJECT_ATTRIBUTES_SIZE	16			    // 视频分析设备支持的检测物体属性类型列表个数上限
#define MAX_MODEL_LEN			32					// 设备型号长度
#define MAX_BURNING_DEV_NUM		32			        // 最大刻录设备个数
#define MAX_NET_TYPE_NUM        8                   // 最大网络类型个数
#define MAX_NET_TYPE_LEN        64                  // 网络类型字符串长度 
#define MAX_DEVICE_NAME_LEN		64			        // 机器名称
#define MAX_DEV_ID_LEN_EX		128		            // 设备ID最大长度
#define MONTH_OF_YEAR			12					// 一年中月份数
#define MAX_SERVER_NUM          10                  // 服务器最大个数
#define MAX_REGISTER_NUM        10                  // 主动注册配置最大个数 
#define MAX_VIDEO_IN_ZOOM       32                  // 单通道最大变速配置个数
#define	MAX_ANALYSE_SCENE_NUM	32					// 视频分析全局配置场景最大数量
#define	MAX_CONFIG_NUM			32					// 每个云台的最大配置数
#define	MAX_PTZ_PRESET_NAME_LEN 64                  // 云台预置点名称长度
#define CFG_COMMON_STRING_16    16                  // 通用字符串长度16
#define CFG_COMMON_STRING_32    32                  // 通用字符串长度32
#define CFG_COMMON_STRING_64    64                  // 通用字符串长度64
#define CFG_COMMON_STRING_128   128                 // 通用字符串长度128
#define CFG_COMMON_STRING_256   256                 // 通用字符串长度256
#define CFG_COMMON_STRING_512   512                 // 通用字符串长度512
#define AV_CFG_Channel_Name_Len				64			// 通道名称长度
#define AV_CFG_Weekday_Num					7			// 一周天数
#define AV_CFG_Max_TimeSection				6			// 时间段数量
#define AV_CFG_Device_ID_Len				64			// 设备ID长度
#define AV_CFG_IP_Address_Len				32			// ip长度
#define AV_CFG_User_Name_Len				64			// 用户名长度
#define AV_CFG_Password_Len					64			// 密码长度
#define AV_CFG_Protocol_Len					32			// 协议名长度
#define AV_CFG_Serial_Len					32			// 序列号长度
#define AV_CFG_Device_Class_Len				16			// 设备类型长度
#define AV_CFG_Device_Type_Len				32			// 设备具体型号长度
#define AV_CFG_Device_Name_Len				64			// 机器名称
#define AV_CFG_Address_Len					128			// 机器部署地点
#define AV_CFG_Max_Path						260			// 路径长度
#define AV_CFG_Max_Split_Window				128			// 最大分割窗口数量
#define	AV_CFG_Monitor_Favorite_In_Channel	64			// 每个输出通道的最大轮训画面收藏数量
#define AV_CFG_Monitor_Favorite_Name_Len	64			// 画面收藏名称长度
#define AV_CFG_Max_Monitor_Favorite_Window	64			// 画面收藏的最大窗口数量
#define AV_CFG_Max_Split_Group				64			// 分割最大分组数量
#define AV_CFG_Max_Split_Mode				32			// 分割模式最大数量
#define AV_CFG_Raid_Name_Len				64			// RAID名称长度
#define AV_CFG_Max_Rail_Member				32			// 单个RAID包含磁盘数
#define AV_CFG_Max_Encode_Main_Format		3			// 主码流编码类型数
#define AV_CFG_Max_Encode_Extra_Format		3			// 辅码流编码类型数
#define	AV_CFG_Max_Encode_Snap_Format		3			// 抓图编码类型数
#define AV_CFG_Max_VideoColor				24			// 每个通道最大视频输入颜色配置数量
#define AV_CFG_Custom_Title_Len				256			// 自定义标题名称长度
#define AV_CFG_Custom_TitleType_Len         32          // 自定义标题类型长度
#define AV_CFG_Max_Video_Widget_Cover		16			// 编码区域覆盖最大数量
#define AV_CFG_Max_Video_Widget_Custom_Title 8			// 编码物件自定义标题最大数量
#define AV_CFG_Max_Video_Widget_Sensor_Info	2			// 编码物件叠加传感器信息的最大数目
#define AV_CFG_Max_Description_Num			4			// 叠加区域描述信息的最大个数
#define AV_CFG_Group_Name_Len				64			// 分组名称长度
#define AV_CFG_DeviceNo_Len					32			// 设备编号长度
#define AV_CFG_Group_Memo_Len				128			// 分组说明长度
#define AV_CFG_Max_Channel_Num				1024		// 最大通道数量
#define AV_CFG_Time_Format_Len				32			// 时间格式长度
#define AV_CFG_Max_White_List				1024		// 白名单数量
#define AV_CFG_Max_Black_List				1024		// 黑名单数量
#define AV_CFG_Filter_IP_Len				96			// 过滤IP最大长度
#define AV_CFG_Max_ChannelRule				32			// 通道存储规则最大长度, 仅通道部分
#define AV_CFG_Max_DBKey_Num				64			// 事件关键字数量
#define AV_CFG_DBKey_Len					32			// 事件关键字长度
#define AV_CFG_Max_Summary_Len				1024		// 摘要长度
#define AV_CFG_Max_Event_Title_Num			32			// 事件标题最大数量
#define AV_CFG_Max_Tour_Link_Num			128			// 联动轮巡最大数量
#define AV_CFG_PIP_BASE						1000		// 画中画分割模式基础值
#define DES_KEY_LEN							8			// DES密钥的字节长度
#define DES_KEY_NUM							3			// 3DES密钥的个数
#define AES_KEY_LEN							32			// AES密钥的字节长度
#define MAX_TIME_SCHEDULE_NUM				8			// 时间表元素个数
#define MAX_SCENE_SUBTYPE_LEN               64          // 场景子类型字符串长度
#define MAX_SCENE_SUBTYPE_NUM               32          // 场景子类型最大个数    
#define MAX_VIDEO_IN_FOCUS                  32          // 单通道最大聚焦配置个数
#define MAX_TIMESPEEDLIMIT_NUM				16			// 最大时间段限速配置个数
#define MAX_VOICEALERT_NUM					64			// 最大语音提示配置个数
#define CFG_MAX_LOWER_MATRIX_NUM			16			// 最大下位矩阵数量
#define CFG_MAX_LOWER_MATRIX_INPUT			64			// 最大下位矩阵输入通道数
#define CFG_MAX_LOWER_MATRIX_OUTPUT			32			// 最大下位矩阵输出通道数
#define CFG_MAX_INFRARED_BOARD_TEMPLATE_NUM 16			// 最大红外面板模板数量
#define	CFG_MAX_INFRARED_KEY_NUM			128			// 最大红外面板按键数量
#define	CFG_MAX_INFRARED_BOARD_NUM			16			// 最大红外面板数量
#define MAX_PHONE_NUMBER_LEN				32			// 电话号码最大长度
#define MAX_AUDIO_OUTPUT_NUM				16			// 音频输出最大通道数
#define MAX_PSTN_SERVER_NUM					8			// 最大报警电话服务器数
#define MAX_ALARM_CHANNEL_NUM				32			// 最大报警通道数
#define MAX_ALARM_DEFENCE_TYPE_NUM			8			// 最大报警防区类型数
#define MAX_ALARM_SENSE_METHOD_NUM			16			// 最大报警感应器方式数
#define MAX_EXALARMBOX_PROTOCOL_NUM  		8			// 最大支持扩展报警盒协议数
#define MAX_EXALARM_CHANNEL_NUM				256			// 最大报警通道数
#define MAX_EXALARMBOX_NUM					8			// 最大报警盒子数
#define MAX_MAILTITLE_LEN                   256         // 最大邮件标题长度
#define MAX_DEVICE_ID_LEN                   48          // 最大设备编码长度
#define MAX_DEVICE_MARK_LEN                 64          // 最大设备描述长度
#define MAX_BRAND_NAME_LEN                  64          // 最大设备品牌长度
#define MAX_ADDRESS_NUM                     16          // 最大串口地址个数
#define MAX_AIRCONDITION_NUM                16          // 最大空调设备个数
#define CFG_MAX_COLLECTION_NUM              64          // 最大预案数
#define MAX_FLOOR_NUM                       128         // 最大楼层数
#define MAX_SEAT_NUM                        8           // 最大座位数
#define AV_CFG_Local_Device_ID				"Local"		// 本地设备ID
#define AV_CFG_Remote_Devce_ID				"Remote"	// 远程设备ID   
#define MAX_LANE_CONFIG_NUMBER               32         // 车道最大个数
#define MAX_PRIORITY_NUMBER                 256         // 违章优先级包含违章最大个数
#define MAX_CATEGORY_TYPE_NUMBER            128         // 子类别类型数
#define MAX_TRIGGER_MODE_NUMBER             64          // 触发模式个数
#define MAX_ABNORMAL_DETECT_TYPE            32          // 异常检测类型数

/************************************************************************
 ** 配置命令 对应CLIENT_GetNewDevConfig和CLIENT_SetNewDevConfig接口
 ***********************************************************************/

#define CFG_CMD_ENCODE			"Encode"			// 图像通道属性配置(对应CFG_ENCODE_INFO)
#define CFG_CMD_RECORD			"Record"			// 定时录像配置(对应CFG_RECORD_INFO)
#define CFG_CMD_ALARMINPUT		"Alarm"				// 外部输入报警配置(对应CFG_ALARMIN_INFO)
#define CFG_CMD_NETALARMINPUT	"NetAlarm"			// 网络报警配置(对应CFG_NETALARMIN_INFO)
#define CFG_CMD_MOTIONDETECT	"MotionDetect"		// 动态检测报警配置(对应CFG_MOTION_INFO)
#define CFG_CMD_VIDEOLOST		"LossDetect"		// 视频丢失报警配置(对应CFG_VIDEOLOST_INFO)
#define CFG_CMD_VIDEOBLIND		"BlindDetect"		// 视频遮挡报警配置(对应CFG_SHELTER_INFO)
#define CFG_CMD_STORAGENOEXIST	"StorageNotExist"	// 无存储设备报警配置(对应CFG_STORAGENOEXIST_INFO)
#define CFG_CMD_STORAGEFAILURE	"StorageFailure"	// 存储设备访问出错报警配置(对应CFG_STORAGEFAILURE_INFO)
#define CFG_CMD_STORAGELOWSAPCE	"StorageLowSpace"	// 存储设备空间不足报警配置(对应CFG_STORAGELOWSAPCE_INFO)
#define CFG_CMD_NETABORT		"NetAbort"			// 网络断开报警配置(对应CFG_NETABORT_INFO)	
#define CFG_CMD_IPCONFLICT		"IPConflict"		// IP冲突报警配置(对应CFG_IPCONFLICT_INFO)
#define CFG_CMD_SNAPCAPINFO		"SnapInfo"			// 抓图能力查询(对应CFG_SNAPCAPINFO_INFO)
#define CFG_CMD_NAS				"NAS"				// 网络存储服务器配置(对应CFG_NAS_INFO)
#define CFG_CMD_PTZ				"Ptz"				// 云台配置(对应CFG_PTZ_INFO)
#define	CFG_CMD_PTZ_AUTO_MOVEMENT "PtzAutoMovement" // 云台定时动作配置(对应CFG_PTZ_AUTOMOVE_INFO)
#define CFG_CMD_WATERMARK		"WaterMark"			// 视频水印配置(对应CFG_WATERMARK_INFO)
#define CFG_CMD_ANALYSEGLOBAL	"VideoAnalyseGlobal"// 视频分析全局配置(对应CFG_ANALYSEGLOBAL_INFO)
#define CFG_CMD_ANALYSEMODULE	"VideoAnalyseModule"// 物体的检测模块配置(对应CFG_ANALYSEMODULES_INFO)
#define CFG_CMD_ANALYSERULE		"VideoAnalyseRule"	// 视频分析规则配置(对应CFG_ANALYSERULES_INFO)
#define CFG_CMD_ANALYSESOURCE	"VideoAnalyseSource"// 视频分析资源配置(对应CFG_ANALYSESOURCE_INFO)
#define CFG_CMD_RAINBRUSH       "RainBrush"         // 雨刷配置(对应CFG_RAINBRUSH_INFO)
#define CFG_CMD_INTELLECTIVETRAFFIC "TrafficSnapshot" // 智能交通抓拍(CFG_TRAFFICSNAPSHOT_INFO只为兼容老协议；请使用CFG_CMD_TRAFFICSNAPSHOT_MULTI)
#define CFG_CMD_TRAFFICGLOBAL   "TrafficGlobal"     // 智能交通全局配置(CFG_TRAFFICGLOBAL_INFO)
#define CFG_CMD_DEV_GENERRAL    "General"           // 普通配置 (CFG_DEV_DISPOSITION_INFO)
#define CFG_CMD_ATMMOTION		"FetchMoneyOverTime"// ATM取款超时配置(对应CFG_ATMMOTION_INFO)
#define CFG_CMD_DEVICESTATUS    "DeviceStatus"      // 设备状态信息(对应CFG_DEVICESTATUS_INFO)
#define CFG_CMD_HARDDISKTANK    "HardDiskTank"      // 扩展柜信息(对应CFG_HARDISKTANKGROUP_INFO)
#define CFG_CMD_RAIDGROUP       "RaidGroup"         // Raid组信息(对应CFG_RAIDGROUP_INFO)
#define CFG_CMD_STORAGEPOOLGROUP "StoragePoolGroup" // 存储池组信息(对应CFG_STORAGEPOOLGROUP_INFO)
#define CFG_CMD_STORAGEPOSITIONGROUP  "StoragePositionGroup"  // 文件系统组信息(对应CFG_STORAGEPOSITIONGROUP_INFO)
#define CFG_CMD_VIDEOINDEVGROUP "VideoInDevGroup"   // 前端设备组信息(对应CFG_VIDEOINDEVGROUP_INFO)
#define CFG_CMD_DEVRECORDGROUP  "DevRecordGroup"    // 通道录像组状态(对应CFG_DEVRECORDGROUP_INFO)
#define CFG_CMD_IPSSERVER       "IpsServer"         // 服务状态(对应CFG_IPSERVER_STATUS)
#define CFG_CMD_SNAPSOURCE		"SnapSource"		// 抓图源配置(对应CFG_SNAPSOURCE_INFO)
#define CFG_CMD_DHRADER         "DahuaRadar"        // 大华雷达配置
#define CFG_CMD_TRANSRADER       "TransRadar"       // 川苏雷达配置
#define CFG_CMD_LANDUNRADER      "LanDunRadar"      // 蓝盾雷达配置
#define CFG_CMD_LANDUNCOILS      "LanDunCoils"      // 蓝盾线圈配置
#define CFG_CMD_MATRIX_SPOT      "SpotMatrix"       // Spot视屏矩阵(对应CFG_VIDEO_MATRIX)
#define CFG_CMD_HDVR_DSP         "DspEncodeCap"     // HDVR传每个数字通道的dsp信息 数字通道可以连IPC或DVR 也就是IPC或DVR的能力(对应CFG_DSPENCODECAP_INFO)
#define CFG_CMD_HDVR_ATTR_CFG    "SystemAttr"       // HDVR传每个数字通道的所连设备的信息
#define CFG_CMD_CHANNEL_HOLIDAY  "HolidaySchedule"  // 假期录像计划(对应结构体CFG_HOLIDAY_SCHEDULE数组)
#define CFG_CMD_HEALTH_MAIL      "HealthMail"       // 健康邮件
#define CFG_CMD_CAMERAMOVE       "IntelliMoveDetect"      // 摄像机移位侦测联动 
#define CFG_CMD_SPLITTOUR        "SplitTour"        // 视频分割轮巡配置(对应CFG_VIDEO_MATRIX)
#define CFG_CMD_VIDEOENCODEROI   "VideoEncodeROI"   // 视频编码ROI(Region of Intrest)配置
#define CFG_CMD_VIDEO_INMETERING "VideoInMetering"  // 测光配置(对应CFG_VIDEO_INMETERING_INFO)
#define CFG_CMD_TRAFFIC_FLOWSTAT "TrafficFlowStat"  // 交通流量统计配置(对应CFG_TRAFFIC_FLOWSTAT_INFO)
#define CFG_CMD_HDMIMATRIX        "HDMIMatrix"      // HDMI视频矩阵配置
#define CFG_CMD_VIDEOINOPTIONS	 "VideoInOptions"	// 视频输入前端选项(对应CFG_VIDEO_IN_OPTIONS)
#define CFG_CMD_RTSP             "RTSP"             // RTSP的配置( 对应CFG_RTSP_INFO_IN和CFG_RTSP_INFO_OUT )
#define CFG_CMD_TRAFFICSNAPSHOT  "TrafficSnapshotNew"// 智能交通抓拍(CFG_TRAFFICSNAPSHOT_INFO 废除，请使用CFG_CMD_TRAFFICSNAPSHOT_MULTI)
#define CFG_CMD_TRAFFICSNAPSHOT_MULTI  "TrafficSnapshotNew"// 智能交通抓拍(CFG_TRAFFICSNAPSHOT_NEW_INFO)
#define CFG_CMD_MULTICAST        "Multicast"         // 组播的相关配置(对应CFG_MULTICASTS_INFO_IN和CFG_MULTICASTS_INFO_OUT)
#define CFG_CMD_VIDEODIAGNOSIS_PROFILE   "VideoDiagnosisProfile"		// 视频诊断参数表(CFG_VIDEODIAGNOSIS_PROFILE)
#define CFG_CMD_VIDEODIAGNOSIS_TASK	      "VideoDiagnosisTask"			// 视频诊断任务表(CFG_VIDEODIAGNOSIS_TASK)
#define CFG_CMD_VIDEODIAGNOSIS_PROJECT    "VideoDiagnosisProject"		// 视频诊断计划表(CFG_VIDEODIAGNOSIS_PROJECT)
#define CFG_CMD_VIDEODIAGNOSIS_REALPROJECT    "VideoDiagnosisRealProject" // 视频诊断实时计划表(CFG_VIDEODIAGNOSIS_REALPROJECT)
#define CFG_CMD_VIDEODIAGNOSIS_GLOBAL     "VideoDiagnosisGlobal"		// 视频诊断全局表(CFG_VIDEODIAGNOSIS_GLOBAL)
#define CFG_CMD_VIDEODIAGNOSIS_TASK_ONE   "VideoDiagnosisTask.x"	    // 视频诊断任务表(CFG_VIDEODIAGNOSIS_TASK)
#define CFG_CMD_TRAFFIC_WORKSTATE         "WorkState"                   // 设备工作状态相关配置(对应CFG_TRAFFIC_WORKSTATE_INFO)
#define CFG_CMD_STORAGEDEVGROUP           "StorageDevGroup"             // 磁盘存储组配置(对应CFG_STORAGEGROUP_INFO)
#define CFG_CMD_RECORDTOGROUP             "RecordToGroup"               // 录像存放的存储组配置(对应CFG_RECORDTOGROUP_INFO)
#define CFG_CMD_INTELLITRACKSCENE         "IntelliTrackScene"           // 智能跟踪场景配置(CFG_INTELLITRACKSCENE_INFO) 
#define CFG_CMD_IVSFRAM_RULE              "IVSFramRule"                 // 智能帧规则配置(对应CFG_ANALYSERULES_INFO)
#define CFG_CMD_RECORD_STORAGEPOINT       "RecordStoragePoint"          //录像存储点映射配置(对应CFG_RECORDTOSTORAGEPOINT_INFO)
#define CFG_CMD_MD_SERVER		          "MetaDataServer"	            //元数据服务器配置(对应CFG_METADATA_SERVER结构体)
#define CFG_CMD_CHANNELTITLE	"ChannelTitle"		// 通道名称(对应AV_CFG_ChannelName)
#define	CFG_CMD_RECORDMODE		"RecordMode"		// 录像模式(对应AV_CFG_RecordMode)
#define CFG_CMD_VIDEOOUT		"VideoOut"			// 视频输出属性(对应AV_CFG_VideoOutAttr)
#define CFG_CMD_REMOTEDEVICE    "RemoteDevice"		// 远程设备信息(对应AV_CFG_RemoteDevice数组, 通道无关)
#define CFG_CMD_REMOTECHANNEL	"RemoteChannel"		// 远程通道(对应AV_CFG_RemoteChannel)
#define CFG_CMD_MONITORTOUR		"MonitorTour"		// 画面轮训配置(对应AV_CFG_MonitorTour)
#define CFG_CMD_MONITORCOLLECTION	"MonitorCollection"	// 画面收藏配置(对应AV_CFG_MonitorCollection)
#define CFG_CMD_DISPLAYSOURCE	"DisplaySource"		// 画面分割显示源配置(对应AV_CFG_ChannelDisplaySource)(废除，不建议使用)
#define CFG_CMD_RAID			"Raid"				// 存储卷组配置(对应AV_CFG_Raid数组, 通道无关)
#define CFG_CMD_RECORDSOURCE	"RecordSource"		// 录像源配置(对应AV_CFG_RecordSource)
#define CFG_CMD_VIDEOCOLOR		"VideoColor"		// 视频输入颜色配置(对应AV_CFG_ChannelVideoColor)
#define CFG_CMD_VIDEOWIDGET		"VideoWidget"		// 视频编码物件配置(对应AV_CFG_VideoWidget)
#define CFG_CMD_STORAGEGROUP	"StorageGroup"		// 存储组信息(对应AV_CFG_StorageGroup数组, 通道无关)
#define CFG_CMD_LOCALS			"Locales"			// 区域配置(对应AV_CFG_Locales)
#define CFG_CMD_LANGUAGE		"Language"			// 语言选择(对应AV_CFG_Language)
#define CFG_CMD_ACCESSFILTER	"AccessFilter"		// 访问地址过滤(对应AV_CFG_AccessFilter)
#define CFG_CMD_AUTOMAINTAIN	"AutoMaintain"		// 自动维护(对应AV_CFG_AutoMaintain)
#define CFG_CMD_REMOTEEVENT		"RemoteEvent"		// 远程设备事件处理(对应AV_CFG_RemoteEvent数组)
#define CFG_CMD_MONITORWALL		"MonitorWall"		// 电视墙配置(对应AV_CFG_MonitorWall数组, 通道无关)
#define	CFG_CMD_SPLICESCREEN	"VideoOutputComposite"		// 融合屏配置(对应AV_CFG_SpliceScreen数组, 通道无关)
#define CFG_CMD_TEMPERATUREALARM	"TemperatureAlarm"		// 温度报警配置(对应AV_CFG_TemperatureAlarm, 通道无关)
#define	CFG_CMD_FANSPEEDALARM		"FanSpeedAlarm"			// 风扇转速报警配置(对应AV_CFG_FanSpeedAlarm, 通道无关)
#define CFG_CMD_RECORDBACKUP		"RecordBackupRestore"	// 录像回传配置(对应AV_CFG_RecordBackup, 通道无关)
#define CFG_CMD_COMM			    "Comm"				// 串口配置(对应CFG_COMMGROUP_INFO)
#define	CFG_CMD_NETWORK			    "Network"			// 网络配置(对应CFG_NETWORK_INFO)
#define CFG_CMD_NASEX			    "NAS"				// 网络存储服务器配置, 多服务器(对应CFG_NAS_INFO_EX)
#define CFG_CMD_LDAP                "LDAP"              // LDAP配置
#define CFG_CMD_ACTIVE_DIR          "ActiveDirectory"   // 活动目录配置
#define CFG_CMD_FLASH               "FlashLight"        // 补光灯配置(对应 CFG_FLASH_LIGHT)
#define CFG_CMD_AUDIO_ANALYSERULE   "AudioAnalyseRule"  // 音频分析规则配置(对应 CFG_ANALYSERULES_INFO)
#define CFG_CMD_JUDICATURE          "Judicature"        // 司法刻录配置(对应CFG_JUDICATURE_INFO)
#define CFG_CMD_GOODS_WEIGHT		"CQDTSet"			// 车载货重配置(对应CFG_GOOD_WEIGHT_INFO)
#define CFG_CMD_VIDEOIN				"VideoIn"			// 输入通道配置(对应CFG_VIDEO_IN_INFO)
#define CFG_CMD_ENCODEPLAN          "EncodePlan"        // 刻录光盘编码计划(对应 CFG_ENCODE_PLAN_INFO)
#define CFG_CMD_PICINPIC            "PicInPic"          // 司法审讯画中画(对应 CFG_PICINPIC_INFO)改为数组方式，兼容以前单个配置，根据长度区分
#define CFG_CMD_BURNFULL            "BurnFull"          // 刻录满事件配置(对应 CFG_BURNFULL_INFO)
#define CFG_CMD_MASTERSLAVE_GLOBAL  "MasterSlaveTrackerGlobal"   //主从式全局配置（对应）
#define CFG_CMD_ANALYSEWHOLE	"VideoAnalyseWhole"  // 视频分析整体配置(对应CFG_ANALYSEWHOLE_INFO)
#define CFG_CMD_VIDEO_IN_BOUNDARY	"VideoInBoundary"	// 视频输入边界配置(对应CFG_VIDEO_IN_BOUNDARY)
#define	CFG_CMD_MONITORWALL_COLLECTION	"MonitorWallCollection"	// 电视墙预案(对应CFG_MONITORWALL_COLLECTION数组)
#define CFG_CMD_ANALOGMATRIX		"AnalogMatrix"		// 模拟矩阵(对应CFG_ANALOG_MATRIX_INFO)
#define CFG_CMD_ANALOG_MATRIX_PROTOCOL	"AnalogMatrixProtocol"	// 模拟矩阵协议配置(对应CFG_ANALOG_MATRIX_PROTOCOL数组)
#define	CFG_CMD_VIDEO_OUT_TITLE		"VideoOutputTitle"		// 视频输出标题(对应CFG_VIDEO_OUT_TITLE)
#define CFG_CMD_DISK_FLUX_ALARM		"DiskFluxAlarm"		// 硬盘数据流量报警配置(对应CFG_DISK_FLUX_INFO)
#define CFG_CMD_NET_FLUX_ALARM		"NetFluxAlarm"		// 网络数据流量报警配置(对应CFG_NET_FLUX_INFO)
#define CFG_CMD_DVRIP               "DVRIP"             // 网络协议配置(对应CFG_DVRIP_INFO)
#define CFG_CMD_PARKINGSPACE_SCREEN "ParkingSpaceScreen"// 和相机对接的区域屏配置(对应 CFG_PARKINGSPACE_SCREEN_INFO ,是数组，元素最大值是DH_PRODUCTION_DEFNITION.nMaxParkingSpaceScreen)
#define CFG_CMD_PARKINGSPACE_STATUS "ParkingSpaceCellStatus"// 车位设置(专有车位和普通车位设置)(对应 CFG_PARKINGSPACE_STATUS_INFO ，是数组，元素最大值是DH_PRODUCTION_DEFNITION.nMaxRoadWays)
#define CFG_CMD_CLIENT_CUSTOM_DATA  "ClientCustomData"  // 平台自定义信息(对应 CFG_CLIENT_CUSTOM_INFO)
#define CFG_CMD_BURN_RECORD_FORMAT  "BurnRecordFormat"  // 刻录格式配置(对应 CFG_BURN_RECORD_FORMAT)
#define CFG_CMD_MULTIBURN           "MultiBurn"         // 多光盘同步刻录(对应 CFG_MULTIBURN_INFO)是一个数组，每一个元素表示一组多光盘同步刻录及校验
#define	CFG_CMD_ENCODE_ENCRYPT		"EncodeEncrypt"		// 编码加密配置信息( CFG_ENCODE_ENCRYPT_CHN_INFO )
#define CFG_CMD_VIDEO_IN_ZOOM       "VideoInZoom"       // 云台通道变倍配置(对应 CFG_VIDEO_IN_ZOOM)
#define CFG_CMD_SNAP				"Snap"				// 抓图配置(对应 CFG_SNAP_INFO)
#define CFG_CMD_REMOTE_STORAGE_LIMIT    "RemoteStorageLimit"    // 网络存储服务器限制配置(对应 CFG_REMOTE_STORAGELIMIT_GROUP)
#define CFG_CMD_SPECIAL_DIR			"SpecialDirectoryDefine"	// 特殊用途目录定义(对应 CFG_SPECIAL_DIR_INFO)
#define CFG_CMD_AUTO_STARTUP_DELAY	"AutoStartupDelay"			// 关机后延时自动开机配置(对应 CFG_AUTO_STARTUP_DELAY_INFO)
#define CFG_CMD_CANFILTER			"CANFilter"			// CAN透传配置(对应 CFG_CANFILTER_LIST)
#define CFG_CMD_VIDEOIN_FOCUS       "VideoInFocus"      // 聚焦设置(对应 CFG_VIDEO_IN_FOCUS)
#define CFG_CMD_ENCODE_ADAPT		"EncodeAdapt"		// 编码自适应配置(对应 CFG_ENCODE_ADAPT_INFO)
#define CFG_CMD_VIDEOANALYSE_CALIBRATE  "VideoAnalyseCalibrate"  // 视频分析标定配置(对应CFG_VIDEO_ANALYSE_CALIBRATEAREA)
#define CFG_CMD_PTZ_PRESET           "PtzPreset"        // 云台预置点配置(对应结构PTZ_PRESET_INFO)
#define CFG_CMD_TIMESPEEDLIMIT		"TimeSpeedLimit"	// 时间段限速值配置(对应结构体 CFG_TIMESPEEDLIMIT_LIST)
#define CFG_CMD_VOICEALERT			"VoiceAlert"		// 语音提示配置(对应结构体 CFG_VOICEALERT_LIST)
#define CFG_CMD_DEVICEKEEPALIVE		"DeviceKeepAlive"	// 设备保活配置(对应结构体 CFG_DEVICEKEEPALIVELIST)

#define CFG_CMD_AUDIO_SPIRIT		"AudioSpirit"		// 语音激励(对应 CFG_AUDIO_SPIRIT)
#define CFG_CMD_COMPOSE_CHANNEL		"ComposeChannel"	// 合成通道配置(对应 CFG_COMPOSE_CHANNEL)
#define CFG_CMD_LOWER_MATRIX		"LowerMatrix"		// 下位矩阵配置(对应 CFG_LOWER_MATRIX_LIST) 
#define CFG_CMD_INFRARED_BOARD_TEMPLATE	"InfraredBoardTemplate"	// 红外面板模板(对应 CFG_INFRARED_BOARD_TEMPLATE_GROUP)
#define CFG_CMD_INFRARED_BOARD		"InfraredBoard"	// 红外面板模板(对应 CFG_INFRARED_BOARD_GROUP)
#define CFG_CMD_VIDEOIN_EXPOSURE    "VideoInExposure"   // 曝光设置(对应CFG_VIDEOIN_EXPOSURE_INFO)

#define CFG_CMD_ACCESS_GENERAL      "AccessControlGeneral" // 门禁基本配置(对应 CFG_ACCESS_GENERAL_INFO)
#define CFG_CMD_ACCESS_EVENT        "AccessControl"        // 门禁事件配置(对应 CFG_ACCESS_EVENT_INFO 数组)     
#define CFG_CMD_WIRELESS			"Wireless"			// 无线网络连接设置(对应 CFG_WIRELESS_INFO)
#define CFG_CMD_ALARMSERVER			"AlarmServer"		// 报警服务器配置(对应CFG_ALARMCENTER_INFO)
#define CFG_CMD_COMMGLOBAL			"CommGlobal"		// 报警全局配置(对应CFG_COMMGLOBAL_INFO)
#define CFG_CMD_ANALOGALARM			"AnalogAlarm"		// 模拟量报警通道配置(对应CFG_ANALOGALARM_INFO)
#define CFG_CMD_ALARMOUT			"AlarmOut"			// 报警输出通道配置(对应CFG_ALARMOUT_INFO)
#define CFG_CMD_NTP					"NTP"				// 时间同步服务器(对应CFG_NTP_INFO)
#define CFG_CMD_ALARMBELL			"AlarmBell"			// 警号配置(对应CFG_ALARMBELL_INFO)
#define CFG_CMD_MOBILE				"Mobile"			// 移动相关业务配置(对应CFG_MOBILE_INFO)
#define CFG_CMD_PHONEEVENTNOTIFY	"PhoneEventNotify"	// (对应CFG_PHONEEVENTNOTIFY_INFO)
#define CFG_CMD_PSTN_ALARM_SERVER	"PSTNAlarmServer"	// 电话报警中心配置(CFG_PSTN_ALARM_CENTER_INFO)
#define CFG_CMD_AUDIO_OUTPUT_VOLUME	"AudioOutputVolume"	// 音频输出音量(CFG_AUDIO_OUTPUT_VOLUME)
#define CFG_CMD_ALARMKEYBOARD		"AlarmKeyboard"		// 报警键盘配置(CFG_ALARMKEYBOARD_INFO)
#define CFG_CMD_POWERFAULT			"PowerFault"		// 电源故障配置(CFG_POWERFAULT_INFO)
#define CFG_CMD_CHASSISINTRUSION	"ChassisIntrusion"	// 机箱入侵报警(防拆报警)配置(CFG_CHASSISINTRUSION_INFO)
#define CFG_CMD_EXALARMBOX			"ExAlarmBox"		// 扩展报警盒配置 (CFG_EXALARMBOX_INFO)
#define CFG_CMD_EXALARMOUTPUT		"ExAlarmOut"		// 扩展报警输出配置(CFG_EXALARMOUTPUT_INFO)
#define CFG_CMD_EXALARMINPUT		"ExAlarm"			// 扩展报警输入配置(CFG_EXALARMINPUT_INFO)
#define CFG_CMD_ACCESSTIMESCHEDULE	"AccessTimeSchedule"// 门禁刷卡时间段(CFG_ACCESS_TIMESCHEDULE_INFO)
#define CFG_CMD_URGENCY				"Emergency"			// 紧急事件配置(CFG_URGENCY_INFO)
#define CFG_CMD_SENSORSAMPLING		"SensorSampling"	// 传感器采样(CFG_SENSORSAMPLING_INFO)
#define CFG_CMD_STP					"STP"				// 环网配置(CFG_STP_INFO)
#define CFG_CMD_ALARM_SUBSYSTEM		"AlarmSubSystem"	// 报警子系统配置(CFG_ALARM_SUBSYSTEM_INFO)
#define CFG_CMD_BATTERY_LOW_POWER	"BatteryLowPowerAlarm"	// 电池电量低配置(CFG_BATTERY_LOW_POWER_INFO)
#define CFG_CMD_SNAPLIKAGE          "SnapLinkage"       // 抓图通道联动外设配置(CFG_SNAPLINKAGE_INFO)
#define CFG_CMD_AUDIOINPUT          "AudioInput"        // 音频输入配置(CFG_AUDIO_INPUT)
#define CFG_CMD_EMAIL				"Email"				// 邮件发送配置(CFG_EMAIL_INFO)
#define CFG_CMD_TRAFFIC_TRANSFER_OFFLINE "TrafficTransferOffline"    // 传输离线文件配置(TRAFFIC_TRANSFER_OFFLINE_INFO)
#define CFG_CMD_COMMSUBSCRIBE		"CommSubscribe"		// 订阅串口数据配置(CFG_DEVCOMM_SUBSCRIBE)
#define CFG_CMD_PARKINGSPACE_LIGHT_STATE "ParkingSpaceLightState"    // 车位状态对应的车位指示灯(CFG_PARKINGSPACE_LIGHT_STATE)
#define CFG_CMD_AIRCONDITION		"AirCondition"		// 空调设备配置(CFG_AIRCONDITION_INFO)
#define CFG_CMD_COMPRESS_PLAY       "CompressPlay"      //压缩回放配置(CFG_COMPRESS_PLAY_INFO)
#define CFG_CMD_BUILDING            "Building"          // VTO楼层配置(CFG_BUILDING_INFO)
#define CFG_CMD_BUILDING_EXTERNAL   "BuildingExternal"  // VTO楼层扩展配置(CFG_BUILDING_EXTERNAL_INFO)
#define CFG_CMD_DIALRULE            "DialRule"          // 拨号规则(CFG_DIALRULE_INFO)
#define CFG_CMD_OIL_MASS_INFO       "OilMassInfo"       // 车辆油箱配置(CFG_OIL_MASS_INFO)
#define CFG_CMD_FISHEYE_INFO        "FishEye"           // 鱼眼详细信息配置(CFG_FISHEYE_DETAIL_INFO)
#define CFG_CMD_VTNOANSWER_FORWARD  "VTNoAnswerForward" // 平台下发呼叫无应答转移配置列表(CFG_VT_NOANSWER_FORWARD_INFO)
#define CFG_CMD_VTO_CALL            "VTOCall"           // VTO呼叫配置(CFG_VTO_CALL_INFO)
#define CFG_CMD_MACCONFLICT         "MacConflict"       // MAC冲突报警配置(CFG_MACCONFLICT_INFO)
#define CFG_CMD_IDLEMOTION_INFO     "IdleMotion"        // 空闲动作配置(CFG_IDLE_MOTION_INFO)
#define CFG_CMD_MONITORWALL_COLL_TOUR "MonitorWallCollectionTour"   // 电视墙预案轮巡配置(CFG_MONITORWALL_COLLECTION_TOUR_INFO)
#define CFG_CMD_PSTN_BREAK_LINE     "PSTNBreakLine"     // PSTN断线事件配置(CFG_PSTN_BREAK_LINE_INFO)
#define CFG_CMD_NET_COLLECTION      "NetCollection"	    // 网络采集设备配置(CFG_NET_COLLECTION_INFO)
#define CFG_CMD_ALARM_SLOT_BOND     "AlarmSlotBond"     // 虚拟Slot节点与具体物理设备的对应关系(CFG_ALARM_SLOT_BOND_INFO)
#define CFG_CMD_TRAFFICSTROBE       "TrafficStrobe"     // 道闸配置(CFG_TRAFFICSTROBE_INFO)
#define CFG_CMD_TRAFFICVOICE        "TrafficVoiceBroadcast"         // 智能交通语音播报配置(CFG_TRAFFICVOICE_BROADCAST)
#define CFG_CMD_STANDING_TIME       "StandingTime"      // 停车时间配置(CFG_STANDING_TIME_INFO)
#define CFG_CMD_ENCLOSURE_TIME_SCHEDULE  "EnclosureTimeSchedule"     // 电子围栏报警时间段配置(CFG_ENCLOSURE_TIME_SCHEDULE_INFO)
#define CFG_CMD_ECKCONFIG			"ECKConfig"			// 停车场出入口控制器配置(CFG_ECKCONFIG_INFO)
#define CFG_CMD_PARKING_CARD        "ParkingCard"       // 停车场出入口刷卡报警事件配置(CFG_PARKING_CARD_INFO)
#define CFG_CMD_RCEMERGENCY_CALL     "RCEmergencyCall"  // 紧急呼叫报警事件配置(CFG_RCEMERGENCY_CALL_INFO)
#define CFG_CMD_LANES_STATE_REPORT   "LanesStateReport" // 车道信息上报配置(CFG_LANES_STATE_REPORT)
#define CFG_CMD_OPEN_DOOR_GROUP     "OpenDoorGroup"     // 多人多开门方式组合配置(CFG_OPEN_DOOR_GROUP_INFO)
#define CFG_CMD_OPEN_DOOR_ROUTE     "OpenDoorRoute"     // 开门路线集合，或称防反潜路线配置(CFG_OPEN_DOOR_ROUTE_INFO)
#define CFG_CMD_BURNPLAN            "BurnPlan"          // 刻录计划配置(对应CFG_BURNPLAN_INFO)
#define CFG_CMD_SCADA_DEV           "SCADADev"          // 检测采集设备配置(CFG_SCADA_DEV_INFO)
#define CFG_CMD_VSP_GAYS            "VSP_GAYS"          // 公安一所平台接入配置(CFG_VSP_GAYS_INFO)
#define CFG_CMD_AUDIODETECT         "AudioDetect"       // 音频检测报警配置(CFG_AUDIO_DETECT_INFO数组)
#define CFG_CMD_GUIDESCREEN         "GuideScreen"       // 诱导屏系统配置(CFG_GUIDESCREEN_INFO)
#define CFG_CMD_VTS_CALL_INFO       "VTSCallInfo"       // VTS呼叫配置(CFG_VTS_CALL_INFO)
#define CFG_CMD_DEV_LIST            "DevList"           // 设备列表配置(CFG_DEV_LIST_INFO)
#define CFG_CMD_CALIBRATE_MATRIX    "CalibrateMatrix"   // 主从式跟踪器标定矩阵配置(CFG_CALIBRATE_MATRIX_INFO)
#define CFG_CMD_DEFENCE_AREA_DELAY  "DefenceAreaDelay"  // 防区延时配置(CFG_DEFENCE_AREA_DELAY_INFO)
#define CFG_CMD_LIGHTING            "Lighting"          // 灯光设置(CFG_LIGHTING_INFO)
#define CFG_CMD_RAINBRUSHMODE           "RainBrushMode"         // 雨刷模式相关配置(对应CFG_RAINBRUSHMODE_INFO数组)
#define CFG_CMD_EMERGENCY_RECORD_FOR_PULL   "EmergencyRecordForPull"    // 紧急录像存储配置，用于客户端主动拉的方式。在客户端拉流存储异常之后，进行紧急录像存储(CFG_EMERGENCY_RECORD_FOR_PULL_INFO)
#define CFG_CMD_ALARM_SHIELD_RULE   "AlarmShieldRule"   // 告警屏蔽规则(CFG_ALARM_SHIELD_RULE_INFO)
#define CFG_CMD_VIDEOIN_ANALYSERULE "VideoInAnalyseRule"        // 视频通道智能规则配置(CFG_VIDEOIN_ANALYSE_RULE_INFO)
#define CFG_CMD_ACCESS_WORK_MODE   "AccessWorkMode"   // 门锁工作模式(对应 CFG_ACCESS_WORK_MODE_INFO 数组)


 /************************************************************************
 ** 能力集命令  对应CLIENT_QueryNewSystemInfo
 ***********************************************************************/

#define CFG_CAP_CMD_VIDEOANALYSE "devVideoAnalyse.getCaps"			// 视频分析能力集(对应CFG_CAP_ANALYSE_INFO)
#define CFG_NETAPP_REMOTEDEVICE	 "netApp.getRemoteDeviceStatus"		// 获取后端设备的的在线状态(对应CFG_REMOTE_DEVICE_STATUS)
#define CFG_CAP_CMD_PRODUCTDEFINITION "magicBox.getProductDefinition"	// 接入设备信息
#define CFG_DEVICE_CAP_CMD_VIDEOANALYSE "intelli.getVideoAnalyseDeviceChannels"   // 设备智能分析能力(对应CFG_CAP_DEVICE_ANALYSE_INFO)兼容老设备
#define CFG_DEVICE_CAP_NEW_CMD_VIDEOANALYSE "devVideoAnalyse.factory.getCollect"  // 设备智能分析能力(对应CFG_CAP_DEVICE_ANALYSE_INFO)
#define CFG_CAP_CMD_CPU_COUNT  "magicBox.getCPUCount"               // 获得CPU个数
#define CFG_CAP_CMD_CPU_USAGE  "magicBox.getCPUUsage"               // 获取CPU占用率
#define CFG_CAP_CMD_MEMORY_INFO  "magicBox.getMemoryInfo"           // 获得内存容量
#define CFG_CAP_CMD_DEVICE_STATE "trafficSnap.getDeviceStatus"      // 获取设备状态信息 (对应CFG_CAP_TRAFFIC_DEVICE_STATUS)
#define CFG_CAP_CMD_VIDEOINPUT "devVideoInput.getCaps"              // 视频输入能力集(对应CFG_CAP_VIDEOINPUT_INFO)
#define CFG_USERMANAGER_ACTIVEUSER    "userManager.getActiveUserInfoAll"      // 得到所有活动的用户信息(对应CFG_ACTIVEUSER_INFO)
#define CFG_CAP_VIDEOSTAT_SUMMARY     "videoStatServer.getSummary"            // 获取视频统计摘要信息(对应CFG_VIDEOSATA_SUMMARY_INFO)
#define CFG_CAP_CMD_VIDEODIAGNOSIS_SERVER "videoDiagnosisServer.getCaps"			// 获取视频诊断服务能力(CFG_VIDEODIAGNOSIS_CAPS_INFO)
#define CFG_CMD_VIDEODIAGNOSIS_GETCOLLECT          "videoDiagnosisServer.factory.getCollect"             // 获取视频诊断通道数目(CFG_VIDEODIAGNOSIS_GETCOLLECT_INFO)
#define CFG_CMD_VIDEODIAGNOSIS_GETSTATE            "videoDiagnosisServer.getState"                       // 获取视频诊断进行状态(CFG_VIDEODIAGNOSIS_STATE_INFO)
#define CFG_CAP_CMD_SERVICE_LIST                   "system.listService"        //获取服务器上支持的服务列表(CFG_DEV_SERVICE_LIST)
#define CFG_CAP_CMD_EVENTHANDLER    "capsManager.get&EventManagerEventHandler"       // 获取服务器报警联动能力集(CFG_CAP_EVENTHANDLER_INFO)
#define CFG_CAP_ALARM               "alarm.getAlarmCaps"                             // 获取报警能力集(CFG_CAP_ALARM_INFO)
#define CFG_CAP_CMD_AUDIO_ANALYSE   "devAudioAnalyse.getCaps"                        // 获取音频分析能力集(CFG_CAP_AUDIO_ANALYSE_INFO)
#define CFG_CMD_MASTERSLAVE_GETCOLLECT        "masterSlaveTracker.factory.getCollect"    // 获取主从式跟踪器通道数目(对应结构体CFG_MASTERSLAVETRACKER_INFO)
#define CFG_CAP_CMD_MASTERSLAVE               "capsManager.get&MasterSlaveTracker"       // 获取主从式设备能力集(CFG_CAP_MASTERSLAVE_INFO)
#define CFG_CAP_CMD_FOCUS_STATE		"devVideoInput.getFocusStatus"						// 获取镜头聚焦状态信息 (对应CFG_CAP_FOCUS_STATUS)
#define CFG_CAP_CMD_NETAPP          "netApp.getCaps"                                    // 获取网络应用能力集(对应CFG_CAP_NETAPP)
#define CFG_CAP_CMD_PTZ_ENABLE  	"ptz.factory.instance"					// 获取云台支持信息(CFG_CAP_PTZ_ENABLEINFO )
#define CFG_CAP_CMD_RECORD			"recordManager.getCaps"                 // 获取录像能力集(CFG_CAP_RECORD_INFO)
#define CFG_CAP_CMD_BURN_MANAGER    "BurnManager.getCaps"                   // 获取刻录管理能力集( CFG_CAP_BURN_MANAGER)
#define CFG_CAP_CMD_PTZ     		"ptz.getCurrentProtocolCaps"			// 获取云台能力集(CFG_PTZ_PROTOCOL_CAPS_INFO)
#define CFG_CMD_ENCODE_GETCAPS      "encode.getCaps"                        // 获取编码能力集(CFG_ENCODECAP)
#define CFG_CAP_CMD_VIDEOINPUT_EX   "devVideoInput.getCapsEx"               // 视频输入能力集扩展(对应CFG_CAP_VIDEOINPUT_INFO_EX)
#define CFG_CAP_CMD_ANALYSE_MODE    "intelli.getCaps.AnalyseMode"           // 获取设备智能分析模式(对应 CFG_ANALYSE_MODE)
#define CFG_CAP_CMD_EVENTMANAGER    "eventManager.getCaps"			// 获取设备报警联动能力,老协议已废除,新开发请使用该字段(CFG_CAP_EVENTMANAGER_INFO)
#define CFG_CAP_CMD_FILEMANAGER		"FileManager.getCaps"			// 获取文件能力(CFG_CAP_FILEMANAGER)
#define	CFG_CAP_CMD_LOG				"log.getCaps"					// 获取日志服务能力(CFG_CAP_LOG)
#define CFG_CAP_CMD_SPEAK			"speak.getCaps"					// 扬声器播放能力(CFG_CAP_SPEAK)
#define CFG_CAP_CMD_ACCESSCONTROLMANAGER	"accessControlManager.getCaps"	// 门禁能力(CFG_CAP_ACCESSCONTROL)
#define CFG_CAP_CMD_EXALARM			"alarm.getExAlarmCaps"					// 获取扩展报警能力集, (对应结构体 CFG_CAP_EXALARM_INFO)
#define CFG_CAP_CMD_EXALARMBOX		"alarm.getExAlarmBoxCaps"				// 获取扩展报警盒能力集, (对应结构体 CFG_CAP_EXALARMBOX_INFO)
#define CFG_CAP_CMD_RECORDFINDER	"RecordFinder.getCaps"					// 获取查询记录能力集, (对应结构体 CFG_CAP_RECORDFINDER_INFO)
#define CFG_CAP_CMD_ANALOGALARM		"AnalogAlarm.getCaps"			// 模拟量报警输入通道能力(对应结构体 CFG_CAP_ANALOGALARM)
#define CFG_CAP_CMD_LOWRATEWPAN		"LowRateWPAN.getCaps"			// 获取LowRateWPAN能力(对应的结构体 CFG_CAP_LOWRATEWPAN)

// 日志能力
typedef struct tagCFG_CAP_LOG
{
	DWORD		dwMaxLogItems;		// 最大日志条数
	DWORD		dwMaxPageItems;		// 每个分页的最大日志条数
	BOOL		bSupportStartNo;	// 查询条件是否支持起始序号
	BOOL		bSupportTypeFilter;	// 查询条件是否支持类型过滤
	BOOL		bSupportTimeFilter;	// 查询条件是否支持时间过滤
}CFG_CAP_LOG;


#define MAX_AUDIO_PROPERTY_NUM       32          // 音频属性最大个数  
#define MAX_AUDIO_FORMAT_NUM         16          // 音频格式最大个数 

// 音频编码压缩格式
enum EM_TALK_AUDIO_TYPE
{
	EM_TALK_AUDIO_PCM,
	EM_TALK_AUDIO_ADPCM, 
	EM_TALK_AUDIO_G711A, 
	EM_TALK_AUDIO_G711Mu, 
	EM_TALK_AUDIO_G726, 
	EM_TALK_AUDIO_G729, 
	EM_TALK_AUDIO_MPEG2, 
	EM_TALK_AUDIO_AMR, 
	EM_TALK_AUDIO_AAC, 
};

// 音频属性
typedef struct CFG_AUDIO_PROPERTY
{
	int            nBitRate;               // 码流大小，单位:kbps，比如192kbps
	int            nSampleBit;             // 采样的位深，如8或16
	int            nSampleRate;            // 采样率，单位:Hz，比如44100Hz
}CFG_AUDIO_PROPERTY;

// 支持的音频格式
typedef struct CFG_CAP_AUDIO_FORMAT
{
	EM_TALK_AUDIO_TYPE  emCompression;          // 音频压缩格式，具体见枚举AV_Talk_Audio_Type
	int		            nPropertyNum;           // 音频属性个数
	CFG_AUDIO_PROPERTY  stuProperty[MAX_AUDIO_PROPERTY_NUM]; // 音频属性
}CFG_CAP_AUDIO_FORMAT;

// 扬声器能力
typedef struct CFG_CAP_SPEAK
{
	int						nAudioCapNum;           // 支持的音频格式个数
	CFG_CAP_AUDIO_FORMAT	stuAudioCap[MAX_AUDIO_FORMAT_NUM]; // 支持的音频格式 
}CFG_CAP_SPEAK;

// 门禁控制能力
typedef struct tagCFG_CAP_ACCESSCONTROL
{
	int		nAccessControlGroups;	// 门禁组数
}CFG_CAP_ACCESSCONTROL;

// 传感器感应方式枚举类型
typedef enum tagEM_SENSE_METHOD
{
    EM_SENSE_UNKNOWN = -1,   //未知类型
	EM_SENSE_DOOR=0,         //门磁
	EM_SENSE_PASSIVEINFRA,   //被动红外
	EM_SENSE_GAS,            //气感
	EM_SENSE_SMOKING,        //烟感
	EM_SENSE_WATER,          //水感
	EM_SENSE_ACTIVEFRA,      //主动红外
	EM_SENSE_GLASS,			 //玻璃破碎
	EM_SENSE_EMERGENCYSWITCH,//紧急开关
	EM_SENSE_SHOCK,			 //震动
	EM_SENSE_DOUBLEMETHOD,	 //双鉴(红外+微波)
	EM_SENSE_THREEMETHOD,	 //三技术
	EM_SENSE_TEMP,			 //温度
	EM_SENSE_HUMIDITY,		 //湿度
    EM_SENSE_WIND,           //风速
	EM_SENSE_CALLBUTTON,	 //呼叫按钮
	EM_SENSE_GASPRESSURE,	 //气体压力
	EM_SENSE_GASCONCENTRATION,//燃气浓度
	EM_SENSE_GASFLOW,		 //气体流量
    EM_SENSE_OIL,            //油量检测
    EM_SENSE_MILEAGE,        //里程数检测
	EM_SENSE_OTHER,			 //其他
	EM_SENSE_NUM             //枚举类型总数
}EM_SENSE_METHOD;

// 传感器报警方式
typedef struct tagCFG_EXALARM_SENSE_METHOD
{
	int                 nSupportSenseMethodNum;								// 支持的传感器方式数
	EM_SENSE_METHOD     emSupportSenseMethod[MAX_ALARM_SENSE_METHOD_NUM];   // 支持的传感器方式
}CFG_EXALARM_SENSE_METHOD;

// 模拟量报警输入通道能力
typedef struct tagCFG_CAP_ANALOGALARM 
{
	DWORD						dwLocalNum;										// 本地模拟量报警输入通道数
	DWORD						dwExLocalNum;									// 扩展模拟量报警输入通道数
	int							nAnalogAlarmChannelNum;							// 模拟量报警通道数, 此为0时表示每个通道支持所有类型的传感器
	CFG_EXALARM_SENSE_METHOD	stuAnalogAlarmChannel[MAX_EXALARM_CHANNEL_NUM];	// 报警通道集合
}CFG_CAP_ANALOGALARM;

// 获取LowRateWPAN能力结构体
typedef struct tagCFG_CAP_LOWRATEWPAN
{
	int			nMaxPageSize;			// 最大分页查询的对码条数
}CFG_CAP_LOWRATEWPAN;


 /************************************************************************
 ** fAnalyzerData回调函数dwDataType类型定义
 ***********************************************************************/
#define    TYPE_CB_VIDEOSTAT       0x1000000      // 回调解析视频信息摘要类型，对应结构体为CFG_VIDEOSATA_SUMMARY_INFO 
#define    TYPE_CB_ANARULES        0x1000001      // 回调解析视频输入通道对应的所有事件规则类型，对应结构体为CFG_ANALYSERULES_INFO
#define    TYPE_CB_VIDEOSYNOPSIS   0x1000002	  // 回调解析浓缩视频的智能帧，对应结构体DH_MSG_OBJECT
#define	   TYPE_CB_TRAFFICFLOWINFO 0x1000003	  // 回调解析交通流量信息，对应结构体DEV_EVENT_TRAFFIC_FLOWSTAT_INFO	
#define    TYPE_CB_TRAFFICFLOWRULE 0x1000004      // 回调解析交通流量规则信息，对应结构体 CFG_TRAFFIC_FLOWSTAT_INFO 	
/************************************************************************
 ** 配置信息(每个结构体都有能力信息，以区分不同设备程序版本和不同型号设备)
 ***********************************************************************/
// 协议版本信息
enum 
{
	CFG_PROTOCOL_VERSION_2 = 2,						// 二代协议
	CFG_PROTOCOL_VERSION_3 = 3						// 三代协议
};

// 视频输入通道
struct CFG_RemoteDeviceVideoInput 
{
	BOOL			bEnable;
	char			szName[MAX_DEVICE_NAME_LEN];
	char			szControlID[MAX_DEV_ID_LEN_EX];
	char			szMainUrl[MAX_PATH];			// 主码流url地址
	char			szExtraUrl[MAX_PATH];			// 辅码流url地址
	int				nServiceType;					// 服务类型, 0-TCP, 1-UDP, 2-MCAST, -1-AUTO
};

// 远程设备
struct AV_CFG_RemoteDevice 
{
	AV_int32			nStructSize;
	AV_BOOL				bEnable;						// 使能
	char				szID[AV_CFG_Device_ID_Len];		// 设备ID
	char				szIP[AV_CFG_IP_Address_Len];	// 设备IP
	AV_int32			nPort;							// 端口
	char				szProtocol[AV_CFG_Protocol_Len];// 协议类型
	char				szUser[AV_CFG_User_Name_Len];	// 用户名
	char				szPassword[AV_CFG_Password_Len];// 密码
	char				szSerial[AV_CFG_Serial_Len];	// 设备序列号
	char				szDevClass[AV_CFG_Device_Class_Len];// 设备类型
	char				szDevType[AV_CFG_Device_Type_Len];	// 设备型号
	char				szName[AV_CFG_Device_Name_Len];	// 机器名称
	char				szAddress[AV_CFG_Address_Len];	// 机器部署地点
	char				szGroup[AV_CFG_Group_Name_Len];	// 机器分组
	AV_int32			nDefinition;					// 清晰度, 0-标清, 1-高清
	AV_int32			nVideoChannel;					// 视频输入通道数
	AV_int32			nAudioChannel;					// 音频输入通道数
	AV_int32            nRtspPort;                      // Rtsp端口号
	char                szVendor[MAX_PATH];             // 设备接入类型
	CFG_RemoteDeviceVideoInput *pVideoInput;            // 视频输入通道，用户申请nMaxVideoInputs个CFG_RemoteDeviceVideoInput空间
	int                 nMaxVideoInputs;
	int                 nRetVideoInputs;
	int					nHttpPort;						// http端口号
														// 以下3项为国际接入方式相关
	AV_BOOL				bGB28181;						// 是否有国际接入方式
	int					nDevLocalPort;					// 设备本地端口
	char				szDeviceNo[AV_CFG_DeviceNo_Len];// 设备编号
};

//-----------------------------图像通道属性-------------------------------

// 画质
typedef enum tagCFG_IMAGE_QUALITY
{
	IMAGE_QUALITY_Q10 = 1,							// 图像质量10%
	IMAGE_QUALITY_Q30,								// 图像质量30%
	IMAGE_QUALITY_Q50,								// 图像质量50%
	IMAGE_QUALITY_Q60,								// 图像质量60%
	IMAGE_QUALITY_Q80,								// 图像质量80%
	IMAGE_QUALITY_Q100,								// 图像质量100%
} CFG_IMAGE_QUALITY;

// 视频压缩格式
typedef enum tagCFG_VIDEO_COMPRESSION
{
	VIDEO_FORMAT_MPEG4,								// MPEG4
	VIDEO_FORMAT_MS_MPEG4,							// MS-MPEG4
	VIDEO_FORMAT_MPEG2,								// MPEG2
	VIDEO_FORMAT_MPEG1,								// MPEG1
	VIDEO_FORMAT_H263,								// H.263
	VIDEO_FORMAT_MJPG,								// MJPG
	VIDEO_FORMAT_FCC_MPEG4,							// FCC-MPEG4
	VIDEO_FORMAT_H264,								// H.264
    VIDEO_FORMAT_H265,								// H.265
} CFG_VIDEO_COMPRESSION;
// 音频编码模式
typedef enum tatCFG_AUDIO_FORAMT
{
	AUDIO_FORMAT_G711A,                              // G711a
    AUDIO_FORMAT_PCM,                                // PCM
    AUDIO_FORMAT_G711U,                              // G711u
    AUDIO_FORMAT_AMR,                                // AMR
    AUDIO_FORMAT_AAC,                                // AAC
} CFG_AUDIO_FORMAT;

// 码流控制模式
typedef enum tagCFG_BITRATE_CONTROL
{
	BITRATE_CBR,									// 固定码流
	BITRATE_VBR,									// 可变码流
} CFG_BITRATE_CONTROL;

// H264 编码级别
typedef enum tagCFG_H264_PROFILE_RANK
{
	PROFILE_BASELINE = 1,                       // 提供I/P帧，仅支持progressive(逐行扫描)和CAVLC
	PROFILE_MAIN,                               // 提供I/P/B帧，支持progressiv和interlaced，提供CAVLC或CABAC
	PROFILE_EXTENDED,                           // 提供I/P/B/SP/SI帧，仅支持progressive(逐行扫描)和CAVLC
	PROFILE_HIGH,                               // 即FRExt，Main_Profile基础上新增：8x8 intra prediction(8x8 帧内预测), custom 
												// quant(自定义量化), lossless video coding(无损视频编码), 更多的yuv格式
}CFG_H264_PROFILE_RANK;

// 分辨率枚举
typedef enum tagCFG_CAPTURE_SIZE
{
	IMAGE_SIZE_D1,								// 704*576(PAL)  704*480(NTSC)
	IMAGE_SIZE_HD1,								// 352*576(PAL)  352*480(NTSC)
	IMAGE_SIZE_BCIF,							// 704*288(PAL)  704*240(NTSC)
	IMAGE_SIZE_CIF,								// 352*288(PAL)  352*240(NTSC)
	IMAGE_SIZE_QCIF,							// 176*144(PAL)  176*120(NTSC)
	IMAGE_SIZE_VGA,								// 640*480
	IMAGE_SIZE_QVGA,							// 320*240
	IMAGE_SIZE_SVCD,							// 480*480
	IMAGE_SIZE_QQVGA,							// 160*128
	IMAGE_SIZE_SVGA,							// 800*592
	IMAGE_SIZE_XVGA,							// 1024*768
	IMAGE_SIZE_WXGA,							// 1280*800
	IMAGE_SIZE_SXGA,							// 1280*1024  
	IMAGE_SIZE_WSXGA,							// 1600*1024  
	IMAGE_SIZE_UXGA,							// 1600*1200
	IMAGE_SIZE_WUXGA,							// 1920*1200
	IMAGE_SIZE_LTF,								// 240*192
	IMAGE_SIZE_720,								// 1280*720
	IMAGE_SIZE_1080,							// 1920*1080
	IMAGE_SIZE_1_3M,							// 1280*960
	IMAGE_SIZE_2M,							    // 1872*1408
	IMAGE_SIZE_5M,						   	    // 3744*1408
	IMAGE_SIZE_3M,							    // 2048*1536
	IMAGE_SIZE_5_0M,                            // 2432*2050
	IMAGE_SIZE_1_2M,							// 1216*1024
	IMAGE_SIZE_1408_1024,                       // 1408*1024
	IMAGE_SIZE_8M,                              // 3296*2472
	IMAGE_SIZE_2560_1920,                       // 2560*1920(5M)
	IMAGE_SIZE_960H,                            // 960*576(PAL) 960*480(NTSC)
	IMAGE_SIZE_960_720,                         // 960*720
	IMAGE_SIZE_NHD,							    // 640*360
	IMAGE_SIZE_QNHD,							// 320*180
	IMAGE_SIZE_QQNHD,							// 160*90
	IMAGE_SIZE_NR  
} CFG_CAPTURE_SIZE;

// 视频格式
typedef struct tagCFG_VIDEO_FORMAT
{
	// 能力
	bool				abCompression;
	bool				abWidth;
	bool				abHeight;
	bool				abBitRateControl;
	bool				abBitRate;
	bool				abFrameRate;
	bool				abIFrameInterval;
	bool				abImageQuality;
	bool				abFrameType;
	bool				abProfile;

	// 信息
	CFG_VIDEO_COMPRESSION emCompression;			// 视频压缩格式
	int					nWidth;						// 视频宽度
	int					nHeight;					// 视频高度
	CFG_BITRATE_CONTROL	emBitRateControl;			// 码流控制模式
	int					nBitRate;					// 视频码流(kbps)
	float				nFrameRate;					// 视频帧率
	int					nIFrameInterval;			// I帧间隔(1-100)，比如50表示每49个B帧或P帧，设置一个I帧。
	CFG_IMAGE_QUALITY	emImageQuality;				// 图像质量
	int					nFrameType;					// 打包模式，0－DHAV，1－"PS"
    CFG_H264_PROFILE_RANK emProfile;                // H.264编码级别
} CFG_VIDEO_FORMAT;

// 音频格式
typedef struct tagCFG_AUDIO_FORMAT 
{
	// 能力
	bool				abCompression;
	bool				abDepth;
	bool				abFrequency;
	bool				abMode;
	bool				abFrameType;
	bool				abPacketPeriod;

	// 信息
	CFG_AUDIO_FORMAT	emCompression;				// 音频压缩模式
	AV_int32			nDepth;						// 音频采样深度
	AV_int32			nFrequency;					// 音频采样频率
	AV_int32			nMode;						// 音频编码模式
	AV_int32			nFrameType;					// 音频打包模式, 0-DHAV, 1-PS
	AV_int32			nPacketPeriod;				// 音频打包周期, ms
} CFG_AUDIO_ENCODE_FORMAT;

// 视频编码参数
typedef struct tagCFG_VIDEOENC_OPT
{
	// 能力
	bool				abVideoEnable;
	bool				abAudioEnable;
	bool				abSnapEnable;
	bool                abAudioAdd;                 // 音频叠加能力
	bool				abAudioFormat;

	// 信息
	BOOL				bVideoEnable;				// 视频使能
	CFG_VIDEO_FORMAT	stuVideoFormat;				// 视频格式
	BOOL				bAudioEnable;				// 音频使能
	BOOL				bSnapEnable;				// 定时抓图使能
	BOOL                bAudioAddEnable;            // 音频叠加使能
	CFG_AUDIO_ENCODE_FORMAT	stuAudioFormat;			// 音频格式
} CFG_VIDEOENC_OPT;

// RGBA信息
typedef struct tagCFG_RGBA
{
	int					nRed;
	int					nGreen;
	int					nBlue;
	int					nAlpha;
} CFG_RGBA;

// 区域信息
typedef struct tagCFG_RECT
{
	int					nLeft;
	int					nTop;
    int					nRight;
    int					nBottom;				
} CFG_RECT;

// 区域顶点信息
typedef struct tagCFG_POLYGON
{
	int					nX; //0~8191
	int					nY;		
} CFG_POLYGON;

// 区域信息
typedef struct tagCFG_REGION
{
	int         nPointNum;
	CFG_POLYGON stuPolygon[MAX_POLYGON_NUM];
}CFG_REGION;

// 折线的端点信息
typedef struct tagCFG_POLYLINE
{
	int					nX; //0~8191
	int					nY;		
} CFG_POLYLINE;

typedef enum tagCFG_FLOWSTAT_DIRECTION
{
	CFG_DRIVING_DIR_APPROACH ,		//上行，即车辆离设备部署点越来越近
	CFG_DRIVING_DIR_LEAVE ,				//下行，即车辆离设备部署点越来越远
}CFG_FLOWSTAT_DIRECTION;

#define  CFG_FLOWSTAT_ADDR_NAME			16						//上下行地点名长
//车辆流量统计车道方向信息 
typedef struct tagCFG_TRAFFIC_FLOWSTAT_DIR_INFO
{
	CFG_FLOWSTAT_DIRECTION		emDrivingDir;							//行驶方向
	char						szUpGoing[CFG_FLOWSTAT_ADDR_NAME];			//上行地点 
	char						szDownGoing[CFG_FLOWSTAT_ADDR_NAME];		//下行地点 
}CFG_TRAFFIC_FLOWSTAT_DIR_INFO;

// 车道信息
typedef struct tagCFG_LANE
{
	int                nLaneId;                           // 车道编号
	int                nDirection;                        // 车道方向(车开往的方向),0-北 1-东北 2-东 3-东南 4-南 5-西南 6-西 7-西北
	CFG_POLYLINE       stuLeftLine[MAX_POLYLINE_NUM];     // 左车道线，车道线的方向表示车道方向，沿车道方向左边的称为左车道线
	int                nLeftLineNum;                      // 左车道线顶点数
	CFG_POLYLINE       stuRightLine[MAX_POLYLINE_NUM];    // 右车道线，车道线的方向表示车道方向，沿车道方向右边的称为右车道线
	int                nRightLineNum;                     // 右车道线顶点数
	int                nLeftLineType;                     // 左车道线属性，1-表示白实线，2- 白虚线，3- 黄线
	int                nRightLineType;                    // 右车道线属性，1-表示白实线，2- 白虚线，3- 黄线
	BOOL               bDriveDirectionEnable;             // 车道行驶方向使能
	int                nDriveDirectionNum;                     // 车道行驶方向数 
	char               szDriveDirection[MAX_LIGHT_DIRECTION][MAX_NAME_LEN];  // 车道行驶方向，"Straight" 直行，"TurnLeft" 左转，"TurnRight" 右转,"U-Turn":掉头
	int                nStopLineNum;                      // 车道对应停止线顶点数
	CFG_POLYLINE       stuStopLine[MAX_POLYLINE_NUM];     // 车道对应停止线
	int                nTrafficLightNumber;               // 车道对应的红绿灯组编号

	bool               abDetectLine;                      // 对应能力集
	bool               abPreLine;
	bool               abPostLine;
	BYTE               byReserved[1];

	int                nDetectLine;
	CFG_POLYLINE       stuDetectLine[MAX_POLYLINE_NUM];   // 车道对应的检测线
	int                nPreLine;
	CFG_POLYLINE       stuPreLine[MAX_POLYLINE_NUM];      // 车道对应的前置线
	int                nPostLine;
	CFG_POLYLINE       stuPostLine[MAX_POLYLINE_NUM];     // 车道对应的后置线
	CFG_TRAFFIC_FLOWSTAT_DIR_INFO stuTrafficFlowDir;	  // 车道流量信息
}CFG_LANE;

// 交通灯属性
typedef struct tagCFG_LIGHTATTRIBUTE
{
	BOOL             bEnable;                           // 当前交通灯是否有效，与车辆通行无关的交通需要设置无效
	int              nTypeNum; 
	char		     szLightType[MAX_LIGHT_TYPE][MAX_NAME_LEN];      // 当前交通灯显现内容（包括:红-Red,黄-Yellow,绿-Green,倒计时-Countdown），如某交通灯可以显示红黄绿三种颜色，某交通灯只显示倒计时
	int              nDirectionNum;
	char             szDirection[MAX_LIGHT_DIRECTION][MAX_NAME_LEN];      // 交通灯指示的行车方向,"Straight": 直行，"TurnLeft":左转，"TurnRight":右转，"U-Turn": 掉头
	int              nYellowTime;                       // 黄灯亮时间
}CFG_LIGHTATTRIBUTE;

// 交通灯组配置信息 
typedef struct tagCFG_LIGHTGROUPS
{
	int                nLightGroupId;                     // 灯组编号
	CFG_RECT           stuLightLocation;                  // 灯组坐标
	int                nDirection;                        // 灯组的方向,1- 灯组水平向,2- 灯组垂直向
	BOOL               bExternalDetection;                // 是否为外接红绿灯信号,当外接红绿灯时，以外界信号为判断依据。外界信号每次跳变时通知
	BOOL               bSwingDetection;                   // 是否支持自适应灯组摇摆检测,在风吹或者容易震动的场景下，位置会进行一定的浮动偏差。如果由算法自行检测，会增加检测时间
	int                nLightNum;                         // 灯组中交通灯的数量
	CFG_LIGHTATTRIBUTE stuLightAtrributes[MAX_LIGHT_NUM]; // 灯组中各交通灯的属性

}CFG_LIGHTGROUPS;

enum EM_STAFF_TYPE
{
	EM_STAFF_TYPE_ERR,
		EM_STAFF_TYPE_HORIZONTAL,     // "Horizontal" 水平线段
		EM_STAFF_TYPE_VERTICAL,       // "Vertical" 垂直线段
		EM_STAFF_TYPE_ANY,            // "Any" 任意线段
		EM_STAFF_TYPE_CROSS,          // "Cross" 垂直面交线段
};

enum EM_CALIBRATEAREA_TYPE
{
	EM_CALIBRATEAREA_TYPE_ERR,
		EM_CALIBRATEAREA_TYPE_GROUD,                         // "Groud" : 地面，需要N条竖直线段+M条水平线段（（N=3，M=1）；（N=2，M=2）；今后扩展）。
		EM_CALIBRATEAREA_TYPE_HORIZONTAL,                    // "Horizontal"  : 水平面，需要水平面上一点到地面点的投影垂直线段。		
		EM_CALIBRATEAREA_TYPE_VERTICAL,                      // "Vertical" : 垂直面，需要垂直面与地面的交线。
		EM_CALIBRATEAREA_TYPE_ANY,                           // "Any" 任意平面，N条竖直线段，及每条长度（N=3，及今后扩展）。
};

// 特殊区域的属性类型
enum EM_SEPCIALREGION_PROPERTY_TYPE
{
	EM_SEPCIALREGION_PROPERTY_TYPE_HIGHLIGHT = 1,            // 高亮，键盘检测区域具有此特性
	EM_SEPCIALREGION_PROPERTY_TYPE_REGULARBLINK,             // 规律的闪烁，插卡区域具有此特性
	EM_SEPCIALREGION_PROPERTY_TYPE_IREGULARBLINK,            // 不规律的闪烁，屏幕区域具有此特性
	EM_SEPCIALREGION_PROPERTY_TYPE_NUM,
};


// 人脸检测类型
enum EM_FACEDETECTION_TYPE
{
	EM_FACEDETECTION_TYPE_ERR,
	EM_FACEDETECTION_TYPE_SMALLFACE,						//小脸类型，人脸在视频中的比重大概17%
	EM_FACEDETECTION_TYPE_LARGEFACE,						//大脸类型，人脸在视频中的比重大概33%
	EM_FACEDETECTION_TYPE_BOTH,								//检测类型
}; 

typedef struct tagCFG_STAFF
{
	CFG_POLYLINE       stuStartLocation;      // 起始坐标点
	CFG_POLYLINE       stuEndLocation;        // 终止坐标点
	float                nLenth;              // 实际长度,单位米
	EM_STAFF_TYPE	   emType;                // 标尺类型
}CFG_STAFF;

// Size
typedef struct tagCFG_SIZE
{
	union
	{
		float				nWidth;			// 宽
		float				nArea;			// 面积
	};
	float					nHeight;		// 高
	
} CFG_SIZE;

// 遮挡信息
typedef struct tagCFG_COVER_INFO
{
	// 能力
	bool				abBlockType;
	bool				abEncodeBlend;
	bool				abPreviewBlend;

	// 信息
	CFG_RECT			stuRect;					// 覆盖的区域坐标
	CFG_RGBA			stuColor;					// 覆盖的颜色
	int					nBlockType;					// 覆盖方式；0－黑块，1－马赛克
	int					nEncodeBlend;				// 编码级遮挡；1－生效，0－不生效
	int					nPreviewBlend;				// 预览遮挡；1－生效，0－不生效
} CFG_COVER_INFO;

// 多区域遮挡配置
typedef struct tagCFG_VIDEO_COVER
{
	int                 nTotalBlocks;						// 支持的遮挡块数
	int					nCurBlocks;							// 已设置的块数
	CFG_COVER_INFO		stuCoverBlock[MAX_VIDEO_COVER_NUM];	// 覆盖的区域	
} CFG_VIDEO_COVER;

// OSD信息
typedef struct tagCFG_OSD_INFO
{
	// 能力
	bool				abShowEnable;

	// 信息
	CFG_RGBA			stuFrontColor;				// 前景颜色
	CFG_RGBA			stuBackColor;				// 背景颜色
	CFG_RECT			stuRect;					// 矩形区域
	BOOL				bShowEnable;				// 显示使能
} CFG_OSD_INFO;

// 画面颜色属性
typedef struct tagCFG_COLOR_INFO
{
	int					nBrightness;				// 亮度(0-100)
	int					nContrast;					// 对比度(0-100)
	int					nSaturation;				// 饱和度(0-100)
	int					nHue;						// 色度(0-100)
	int					nGain;						// 增益(0-100)
	BOOL				bGainEn;					// 增益使能
} CFG_COLOR_INFO;

// 图像通道属性信息
typedef struct tagCFG_ENCODE_INFO
{
	int                 nChannelID;							// 通道号(0开始)
	char				szChnName[MAX_CHANNELNAME_LEN];		// 通道名称
	CFG_VIDEOENC_OPT	stuMainStream[MAX_VIDEOSTREAM_NUM];	// 主码流，0－普通录像，1-动检录像，2－报警录像
	CFG_VIDEOENC_OPT	stuExtraStream[MAX_VIDEOSTREAM_NUM];// 辅码流，0－辅码流1，1－辅码流2，2－辅码流3
	CFG_VIDEOENC_OPT	stuSnapFormat[MAX_VIDEOSTREAM_NUM];	// 抓图，0－普通抓图，1－动检抓图，2－报警抓图
	DWORD				dwCoverAbilityMask;					// 区域遮盖能力掩码，按位分别是本地预览、录像及网络监视
	DWORD				dwCoverEnableMask;					// 区域遮盖使能掩码，按位分别是本地预览、录像及网络监视
	CFG_VIDEO_COVER		stuVideoCover;						// 区域覆盖
	CFG_OSD_INFO		stuChnTitle;						// 通道标题
	CFG_OSD_INFO		stuTimeTitle;						// 时间标题
	CFG_COLOR_INFO		stuVideoColor;						// 画面颜色
	CFG_AUDIO_FORMAT    emAudioFormat;                      // 音频格式: 0:G711A,1:PCM,2:G711U,3:AMR,4:AAC
	int					nProtocolVer;						// 协议版本号, 只读
} CFG_ENCODE_INFO;

// 视频输入前端能力集
typedef struct tagCFG_VIDEO_ENCODECAP
{
	int		nMaxCIFFrame;			// CIF P帧最大值 单位Kbits, 默认值40
	int		nMinCIFFrame;			// CIF P帧最小值 单位Kbits, 默认值7
}CFG_VIDEO_ENCODECAP;

// 多画面预览工作模式
typedef enum tagCFG_EM_PREVIEW_MODE
{
    CFG_EM_PREVIEW_MODE_UNKNOWN = 0,        // 
    CFG_EM_PREVIEW_MODE_SNAPSHOT,           // 快照方式
    CFG_EM_PREVIEW_MODE_SPLITENCODE,        // 分割编码方式
    CFG_EM_PREVIEW_MODE_SPLITSNAP,          // 分割快照方式
}CFG_EM_PREVIEW_MODE;

#define MAX_PREVIEW_MODE_SPLIT_TYPE_NUM     8                           // 最大多画面预览窗口分割种类数

// 编码能力集
typedef struct tagCFG_ENCODECAP
{
	int                     nChannelNum;                                // 实际通道数
	CFG_VIDEO_ENCODECAP     stuVideoEncodeCap[MAX_VIDEO_CHANNEL_NUM];	// 各通道编码能力信息数组
    CFG_EM_PREVIEW_MODE     emPreviewMode;                              // 多画面预览工作模式
    int                     nSplitModeNum;                              // 有效的多画面预览窗口分割种类数
    int                     anSplitMode[MAX_PREVIEW_MODE_SPLIT_TYPE_NUM];// 多画面预览窗口分割数信息, 可以为1, 4, 6, 8, 9, 16, 25, 36...
                                                                        // -1表示默认[1, 4, 8, 9, 16, …模拟通道数量], 为小于模拟通道数的N的平方数, 如果模拟通道大于8, 也包含8
}CFG_ENCODECAP;

// 水印配置
typedef struct tagCFG_WATERMARK_INFO 
{
	int                 nChannelID;					// 通道号(0开始)
	BOOL				bEnable;					// 使能开关
	int					nStreamType;				// 码流类型(1～n)，0－所有码流
	int					nDataType;					// 数据类型，1－文字，2－图片
	char				pData[MAX_WATERMARK_LEN];	// 字符串水印数据
} CFG_WATERMARK_INFO;

// dsp配置
typedef struct tagCFG_DSPENCODECAP_INFO{
	DWORD				dwVideoStandardMask;	// 视频制式掩码，按位表示设备能够支持的视频制式
	DWORD				dwImageSizeMask;		// 分辨率掩码，按位表示设备能够支持的分辨率
	DWORD				dwEncodeModeMask;		// 编码模式掩码，按位表示设备能够支持的编码模式
	DWORD				dwStreamCap;			// 按位表示设备支持的多媒体功能，
                                             	// 第一位表示支持主码流
	                                         	// 第二位表示支持辅码流1
	                                         	// 第三位表示支持辅码流2
	                                         	// 第五位表示支持jpg抓图
	DWORD				dwImageSizeMask_Assi[32];// 表示主码流为各分辨率时，支持的辅码流分辨率掩码。
	DWORD				dwMaxEncodePower;		// DSP支持的最高编码能力 
	WORD				wMaxSupportChannel;		// 每块DSP支持最多输入视频通道数 
	WORD				wChannelMaxSetSync;		// DSP每通道的最大编码设置是否同步；0：不同步，1：同步
	BYTE				bMaxFrameOfImageSize[256];// 不同分辨率下的最大采集帧率，与dwVideoStandardMask按位对应
	BYTE				bEncodeCap;				// 标志，配置时要求符合下面条件，否则配置不能生效；
	                                         	// 0：主码流的编码能力+辅码流的编码能力 <= 设备的编码能力，
	                                         	// 1：主码流的编码能力+辅码流的编码能力 <= 设备的编码能力，
	                                         	// 辅码流的编码能力 <= 主码流的编码能力，
	                                         	// 辅码流的分辨率 <= 主码流的分辨率，
	                                         	// 主码流和辅码流的帧率 <= 前端视频采集帧率
	                                         	// 2：N5的计算方法
	                                         	// 辅码流的分辨率 <= 主码流的分辨率
												// 查询支持的分辨率和相应最大帧率
	BYTE				byResolutionNum;			// bResolution的长度
	BYTE				byResolutionNum_1;		// bResolution_1的长度
	BYTE				byReserved;
	BYTE				byResolution[256];		//主码流,按照分辨率进行索引，如果支持该分辨率，则bResolution[n]等于支持的最大帧率.否则为0.							
	BYTE				byResolution_1[256];		//辅助码流1,同主码流说明.
	char				reserved[28];
	BYTE				byImageSize[256];		// 支持的分辨率数组,参见enum CAPTURE_SIZE
	BYTE				byImageSize_Assi[256][256]; //表示主码流为各分辨率时，支持的辅码流分辨率，数组下标表示主码流所支持的分辨率值。
}CFG_DSPENCODECAP_INFO;


//-------------------------------录象配置---------------------------------

// 时间段信息
typedef struct tagCFG_TIME_SECTION 
{
	DWORD				dwRecordMask;						// 录像掩码，按位分别为动态检测录像、报警录像、定时录像、Bit3~Bit15保留、Bit16动态检测抓图、Bit17报警抓图、Bit18定时抓图
	int					nBeginHour;
	int					nBeginMin;
	int					nBeginSec;
	int					nEndHour;
	int					nEndMin;
	int					nEndSec;
} CFG_TIME_SECTION;

// 时间表信息
typedef struct tagCFG_TIME_SCHEDULE
{
	CFG_TIME_SECTION	stuTimeSection[MAX_TIME_SCHEDULE_NUM][MAX_REC_TSECT]; // 第一维前7个元素对应每周7天，第8个元素对应节假日，每天最多6个时间段
} CFG_TIME_SCHEDULE;

// 定时录像配置信息
typedef struct tagCFG_RECORD_INFO
{
	int                 nChannelID;					// 通道号(0开始)
	CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT]; // 时间表
	int					nPreRecTime;				// 预录时间，为零时表示关闭(0~300)
	BOOL				bRedundancyEn;				// 录像冗余开关
	int					nStreamType;				// 0－主码流，1－辅码流1，2－辅码流2，3－辅码流3
	int					nProtocolVer;				// 协议版本号, 只读

	// 能力
	BOOL				abHolidaySchedule;          // 为true时有假日配置信息，bHolidayEn、stuHolTimeSection才有效;
    BOOL                bHolidayEn;                 // 假日录像使能TRUE:使能,FALSE:未使能
    CFG_TIME_SECTION    stuHolTimeSection[MAX_REC_TSECT];          // 假日录像时间表
} CFG_RECORD_INFO;

//-------------------------------报警配置---------------------------------

// 云台联动类型
typedef enum tagCFG_LINK_TYPE
{
	LINK_TYPE_NONE,						    		// 无联动
	LINK_TYPE_PRESET,								// 联动预置点
	LINK_TYPE_TOUR,									// 联动巡航
	LINK_TYPE_PATTERN,								// 联动轨迹
} CFG_LINK_TYPE;

// 联动云台信息
typedef struct tagCFG_PTZ_LINK
{
	CFG_LINK_TYPE		emType;						// 联动类型
	int					nValue;						// 联动取值分别对应预置点号，巡航号等等
} CFG_PTZ_LINK;

// 联动云台信息扩展
typedef struct tagCFG_PTZ_LINK_EX
{
	CFG_LINK_TYPE	emType;				// 联动类型 
	int			    nParam1;			// 联动参数1
	int			    nParam2;            // 联动参数2
	int			    nParam3;            // 联动参数3
	int			    nChannelID;         // 所联动云台通道
} CFG_PTZ_LINK_EX;

// 事件标题内容结构体
typedef struct tagCFG_EVENT_TITLE
{
	char				szText[MAX_CHANNELNAME_LEN];
	CFG_POLYGON			stuPoint;			// 标题左上角坐标, 采用0-8191相对坐标系
	CFG_SIZE     		stuSize;			// 标题的宽度和高度,采用0-8191相对坐标系，某项或者两项为0表示按照字体自适应宽高
    CFG_RGBA			stuFrontColor;		// 前景颜色
    CFG_RGBA			stuBackColor;		// 背景颜色
} CFG_EVENT_TITLE;

// 邮件附件类型
typedef enum tagCFG_ATTACHMENT_TYPE
{
		ATTACHMENT_TYPE_PIC,							// 图片附件
		ATTACHMENT_TYPE_VIDEO,							// 视频附件
		ATTACHMENT_TYPE_NUM,							// 附件类型总数
} CFG_ATTACHMENT_TYPE;
// 邮件详细内容
typedef struct tagCFG_MAIL_DETAIL
{
	   CFG_ATTACHMENT_TYPE emAttachType;                 // 附件类型
       int                 nMaxSize;                     // 文件大小上限，单位kB
       int                 nMaxTimeLength;               // 最大录像时间长度，单位秒，对video有效
}CFG_MAIL_DETAIL;

// 分割模式
typedef enum tagCFG_SPLITMODE
{
	    SPLITMODE_1 = 1,						// 1画面
	    SPLITMODE_2 = 2,						// 2画面
	    SPLITMODE_4 = 4,						// 4画面
		SPLITMODE_6 = 6,						// 6画面
		SPLITMODE_8 = 8,						// 8画面
		SPLITMODE_9 = 9,						// 9画面
		SPLITMODE_12 = 12,				    	// 12画面
		SPLITMODE_16 = 16,				    	// 16画面
		SPLITMODE_20 = 20,				    	// 20画面
		SPLITMODE_25 = 25,					    // 25画面
		SPLITMODE_36 = 36,					    // 36画面
		SPLITMODE_64 = 64,					    // 64画面
		SPLITMODE_144 = 144,					// 144画面
		SPLITMODE_PIP = 1000,                   // 画中画分割模式基础值
		SPLITMODE_PIP1 = SPLITMODE_PIP + 1,		// 画中画模式, 1个全屏大画面+1个小画面窗口
		SPLITMODE_PIP3 = SPLITMODE_PIP + 3,		// 画中画模式, 1个全屏大画面+3个小画面窗口
		SPLITMODE_FREE = SPLITMODE_PIP * 2,	// 自由开窗模式，可以自由创建、关闭窗口，自由设置窗口位置和Z轴次序
		SPLITMODE_COMPOSITE_1 = SPLITMODE_PIP * 3 + 1,	// 融合屏成员1分割
		SPLITMODE_COMPOSITE_4 = SPLITMODE_PIP * 3 + 4,	// 融合屏成员4分割
		SPLITMODE_EOF,                          // 结束标识
} CFG_SPLITMODE;

// 轮巡联动配置
typedef struct tagCFG_TOURLINK
{
	BOOL				bEnable;			             // 轮巡使能
	CFG_SPLITMODE	    emSplitMode;		             // 轮巡时的分割模式
	int			        nChannels[MAX_VIDEO_CHANNEL_NUM];  // 轮巡通道号列表
	int			        nChannelCount;		             // 轮巡通道数量
} CFG_TOURLINK;

// 门禁操作类型
enum EM_CFG_ACCESSCONTROLTYPE
{
	EM_CFG_ACCESSCONTROLTYPE_NULL = 0,					// 不做操作
	EM_CFG_ACCESSCONTROLTYPE_AUTO,						// 自动
	EM_CFG_ACCESSCONTROLTYPE_OPEN,						// 开门
	EM_CFG_ACCESSCONTROLTYPE_CLOSE,						// 关门
	EM_CFG_ACCESSCONTROLTYPE_OPENALWAYS,				// 永远开启
	EM_CFG_ACCESSCONTROLTYPE_CLOSEALWAYS,				// 永远关闭
};

// 门禁联动操作的组合

#define MAX_ACCESSCONTROL_NUM	8						// 最大门禁操作的组合数


// 语音呼叫发起方
typedef enum
{
	EM_CALLER_DEVICE = 0,								// 设备发起
}EM_CALLER_TYPE;

// 呼叫协议
typedef enum
{
	EM_CALLER_PROTOCOL_CELLULAR = 0,					// 手机方式
}EM_CALLER_PROTOCOL_TYPE;


// 语音呼叫联动信息
typedef struct tagCFG_TALKBACK_INFO
{
	BOOL				bCallEnable;					// 语音呼叫使能
	EM_CALLER_TYPE		emCallerType;					// 语音呼叫发起方
	EM_CALLER_PROTOCOL_TYPE	emCallerProtocol;			// 语音呼叫协议
}CFG_TALKBACK_INFO;

// 电话报警中心联动信息
typedef struct tagCFG_PSTN_ALARM_SERVER
{
	BOOL				bNeedReport;						// 是否上报至电话报警中心
	int					nServerCount;						// 电话报警服务器个数					
	BYTE 				byDestination[MAX_PSTN_SERVER_NUM];	// 上报的报警中心下标,详见配置CFG_PSTN_ALARM_CENTER_INFO
}CFG_PSTN_ALARM_SERVER;

// 报警联动信息
typedef struct tagCFG_ALARM_MSG_HANDLE
{
	//能力
	bool				abRecordMask;
	bool				abRecordEnable;
	bool				abRecordLatch;
	bool				abAlarmOutMask;
	bool				abAlarmOutEn;
	bool				abAlarmOutLatch;	
	bool				abExAlarmOutMask;
	bool				abExAlarmOutEn;
	bool				abPtzLinkEn;
	bool				abTourMask;
	bool				abTourEnable;
	bool				abSnapshot;
	bool				abSnapshotEn;
	bool				abSnapshotPeriod;
	bool				abSnapshotTimes;
	bool				abTipEnable;
	bool				abMailEnable;
	bool				abMessageEnable;
	bool				abBeepEnable;
	bool				abVoiceEnable;
	bool				abMatrixMask;
	bool				abMatrixEnable;
	bool				abEventLatch;
	bool				abLogEnable;
	bool				abDelay;
	bool				abVideoMessageEn;
	bool				abMMSEnable;
	bool				abMessageToNetEn;
	bool				abTourSplit;
	bool				abSnapshotTitleEn;

    bool                abChannelCount;
	bool                abAlarmOutCount;
	bool                abPtzLinkEx;
	bool                abSnapshotTitle;
	bool                abMailDetail;
	bool                abVideoTitleEn;
	bool                abVideoTitle;
	bool                abTour;
	bool                abDBKeys;
	bool                abJpegSummary;
	bool                abFlashEn;
	bool                abFlashLatch;
	


	//信息
	int					nChannelCount;								 // 设备的视频通道数
	int					nAlarmOutCount;								 // 设备的报警输出个数
	DWORD				dwRecordMask[MAX_CHANNEL_COUNT];			 // 录像通道掩码(按位)
	BOOL				bRecordEnable;								 // 录像使能
	int					nRecordLatch;								 // 录像延时时间(秒)
	DWORD				dwAlarmOutMask[MAX_CHANNEL_COUNT];			 // 报警输出通道掩码
	BOOL				bAlarmOutEn;								 // 报警输出使能
	int					nAlarmOutLatch;								 // 报警输出延时时间(秒)
	DWORD				dwExAlarmOutMask[MAX_CHANNEL_COUNT];		 // 扩展报警输出通道掩码
	BOOL				bExAlarmOutEn;								 // 扩展报警输出使能
	CFG_PTZ_LINK		stuPtzLink[MAX_VIDEO_CHANNEL_NUM];			 // 云台联动项
	BOOL				bPtzLinkEn;									 // 云台联动使能
	DWORD				dwTourMask[MAX_CHANNEL_COUNT];				 // 轮询通道掩码
	BOOL				bTourEnable;								 // 轮询使能
	DWORD				dwSnapshot[MAX_CHANNEL_COUNT];				 // 快照通道号掩码
	BOOL				bSnapshotEn;								 // 快照使能
	int					nSnapshotPeriod;							 // 连拍周期(秒)
	int					nSnapshotTimes;								 // 连拍次数
	BOOL				bTipEnable;									 // 本地消息框提示
	BOOL				bMailEnable;								 // 发送邮件，如果有图片，作为附件
	BOOL				bMessageEnable;								  // 上传到报警服务器
	BOOL				bBeepEnable;							 	  // 蜂鸣
	BOOL				bVoiceEnable;								  // 语音提示
	DWORD				dwMatrixMask[MAX_CHANNEL_COUNT];			  // 联动视频矩阵通道掩码
	BOOL				bMatrixEnable;								  // 联动视频矩阵
	int					nEventLatch;								  // 联动开始延时时间(秒)，0－15
	BOOL				bLogEnable;									  // 是否记录日志
	int					nDelay;										  // 设置时先延时再生效，单位为秒
	BOOL				bVideoMessageEn;							  // 叠加提示字幕到视频。叠加的字幕包括事件类型，通道号，秒计时。
	BOOL				bMMSEnable;									  // 发送彩信使能
	BOOL				bMessageToNetEn;							  // 消息上传给网络使能
	int					nTourSplit;									  // 轮巡时的分割模式 0: 1画面; 1: 8画面
	BOOL				bSnapshotTitleEn;							  // 是否叠加图片标题
	int                 nPtzLinkExNum;                                // 云台配置数
	CFG_PTZ_LINK_EX     stuPtzLinkEx[MAX_VIDEO_CHANNEL_NUM];          // 扩展云台信息
	int                 nSnapTitleNum;                                // 图片标题内容数
	CFG_EVENT_TITLE     stuSnapshotTitle[MAX_VIDEO_CHANNEL_NUM];      // 图片标题内容
	CFG_MAIL_DETAIL     stuMailDetail;                                // 邮件详细内容
	BOOL                bVideoTitleEn;                                // 是否叠加视频标题，主要指主码流
    int                 nVideoTitleNum;                               // 视频标题内容数目
	CFG_EVENT_TITLE     stuVideoTitle[MAX_VIDEO_CHANNEL_NUM];         // 视频标题内容
	int                 nTourNum;                                     // 轮询联动数目
	CFG_TOURLINK        stuTour[MAX_VIDEO_CHANNEL_NUM];               // 轮询联动配置
	int                 nDBKeysNum;			                          // 指定数据库关键字的有效数
	char                szDBKeys[MAX_DBKEY_NUM][MAX_CHANNELNAME_LEN]; // 指定事件详细信息里需要写到数据库的关键字
	BYTE                byJpegSummary[MAX_SUMMARY_LEN];               // 叠加到JPEG图片的摘要信息
	BOOL                bFlashEnable;                                 // 是否使能补光灯
	int                 nFlashLatch;                                  // 补光灯延时时间(秒),延时时间范围：[10,300]
	
	bool				abAudioFileName;
	bool				abAlarmBellEn;
	bool				abAccessControlEn;
	bool				abAccessControl;

	char				szAudioFileName[MAX_PATH];					// 联动语音文件绝对路径
	BOOL				bAlarmBellEn;								// 警号使能
	BOOL				bAccessControlEn;							// 门禁使能

	DWORD				dwAccessControl;							// 门禁组数
	EM_CFG_ACCESSCONTROLTYPE	emAccessControlType[MAX_ACCESSCONTROL_NUM];	// 门禁联动操作信息
	
	bool				abTalkBack;	
	CFG_TALKBACK_INFO	stuTalkback;								// 语音呼叫联动信息

	bool				abPSTNAlarmServer;
	CFG_PSTN_ALARM_SERVER	stuPSTNAlarmServer;						// 电话报警中心联动信息
    CFG_TIME_SCHEDULE       stuTimeSection;                         // 事件响应时间表
	bool				abAlarmBellLatch;
	int					nAlarmBellLatch;							// 警号输出延时时间(10-300秒)

} CFG_ALARM_MSG_HANDLE;



// 报警使能控制方式枚举类型
typedef enum tagEM_CTRL_ENABLE
{
	EM_CTRL_NORMAL=0,   //不控制使能
	EM_CTRL_ALWAYS_EN,  //总是使能
	EM_CTRL_ONCE_DIS,   //旁路
	EM_CTRL_ALWAYS_DIS, //移除
	EM_CTRL_NUM         //枚举类型总数
}EM_CTRL_ENABLE;


// 防区类型
typedef enum tagEM_CFG_DEFENCEAREATYPE
{
	EM_CFG_DefenceAreaType_Unknown = 0,     // 未知类型
	EM_CFG_DefenceAreaType_InTime,          // 即时防区 
	EM_CFG_DefenceAreaType_Delay,           // 延时防区
	EM_CFG_DefenceAreaType_FullDay,         // 24小时防区
    EM_CFG_DefenceAreaType_Fire,            // 火警防区
    EM_CFG_DefenceAreaType_FullDaySound,    // 24小时有声防区
    EM_CFG_DefenceAreaType_FullDaySlient,   // 24小时无声防区
    EM_CFG_DefenceAreaType_Entrance1,       // 出入防区1
    EM_CFG_DefenceAreaType_Entrance2,       // 出入防区2
    EM_CFG_DefenceAreaType_InSide,          // 内部防区
    EM_CFG_DefenceAreaType_OutSide,         // 外部防区
}EM_CFG_DEFENCEAREATYPE;

// 外部报警配置
typedef struct tagCFG_ALARMIN_INFO
{
	int					nChannelID;									// 报警通道号(0开始)
	BOOL				bEnable;									// 使能开关
	char				szChnName[MAX_CHANNELNAME_LEN];				// 报警通道名称
	int					nAlarmType;									// 报警器类型，0：常闭，1：常开
	CFG_ALARM_MSG_HANDLE stuEventHandler;							// 报警联动
	CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT];// 事件响应时间段
	BOOL				abDevID;									// 
	char				szDevID[MAX_NAME_LEN];						// 设备ID
	int                 nPole;                                      // 传感器触发模式, 0:高有效，1低有效；
	                                                                // 具体表现为传感器接地or电源，与nAlarmType组合使用
	EM_SENSE_METHOD     emSense;                                    // 传感器感应方式
	EM_CTRL_ENABLE      emCtrl;                                     // 报警使能控制方式
	int                 nDisDelay;                                  // 延时撤防时间,防区类型为"Delay"(延时防区)时才有效, 单位: 秒, 最大时间通过查询能力获得
	                                                                //emCtrl值为EM_CTRL_NORMAL或EM_CTRL_ALWAYS_EN 时有效。

	EM_CFG_DEFENCEAREATYPE emDefenceAreaType;						// 防区类型, 具体支持的类型通过查询能力获得
	int					nEnableDelay;								// 延时布防时间, 防区类型为"Delay"(延时防区)时才有效, 单位: 秒, 最大时间通过查询能力获得    
    int                 nSlot;                                      // 根地址, -1表示无效, 0表示本地通道, 1表示连接在第一个串口上的扩展通道, 2、3...以此类推
    int                 nLevel1;                                    // 第一级级联地址, 表示连接在第nSlot串口上的第nLevel1个探测器或仪表, -1表示无效, 从0开始
    bool                abLevel2;                                   // 表示nLevel2字段是否存在
    int                 nLevel2;                                    // 第二级级联地址, 表示连接在第nLevel1个的仪表上的探测器序号, -1表示无效, 从0开始
} CFG_ALARMIN_INFO;

// 网络输入报警配置
typedef struct tagCFG_NETALARMIN_INFO 
{
	int					nChannelID;									// 报警通道号(0开始)
	BOOL				bEnable;									// 使能开关
	char				szChnName[MAX_CHANNELNAME_LEN];				// 报警通道名称
	int					nAlarmType;									// 报警器类型，0：常闭，1：常开
	CFG_ALARM_MSG_HANDLE stuEventHandler;							// 报警联动
	CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT];// 事件响应时间段
} CFG_NETALARMIN_INFO;


// 动检支持的视频窗口配置
typedef struct tagCFG_MOTION_WINDOW
{
	int                  nThreshold;           // 面积阀值，取值[0, 100]
	int                  nSensitive;           // 灵敏度，取值[0, 100]
	CFG_RECT             stuWindow;            // 动检窗口区域, 坐标位置取值[0, 8192)
}CFG_MOTION_WINDOW;

typedef struct tagCFG_DETECT_REGION
{
    int				     nRegionID;									    // 区域ID
    char                 szRegionName[CFG_COMMON_STRING_64];            // 动态窗口名称
    int                  nThreshold;                                    // 面积阀值，取值[0, 100]
	int					 nSenseLevel;								    // 灵敏度1～6
	int					 nMotionRow;									// 动态检测区域的行数
	int					 nMotionCol;									// 动态检测区域的列数
	BYTE				 byRegion[MAX_MOTION_ROW][MAX_MOTION_COL];	    // 检测区域，最多32*32块区域 
}CFG_DETECT_REGION;

// 动态检测报警配置
typedef struct tagCFG_MOTION_INFO 
{
	int					 nChannelID;									// 报警通道号(0开始), nVersion=1时，此字段无效
	BOOL				 bEnable;									    // 使能开关
	int					 nSenseLevel;								    // 灵敏度1～6
	int					 nMotionRow;									// 一代动态检测区域的行数
	int					 nMotionCol;									// 一代动态检测区域的列数
	BYTE				 byRegion[MAX_MOTION_ROW][MAX_MOTION_COL];	    // 一代检测区域，最多32*32块区域
	CFG_ALARM_MSG_HANDLE stuEventHandler;							    // 报警联动
	CFG_TIME_SECTION	 stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT];   // 事件响应时间段
	int			         nVersion;                                      // 0, 1, 由能力集确定, 只读, 等于1时以下字段有效
	BOOL                 bSenseLevelEn;                                 // 只读，决定nSenseLevel是否有效
	BOOL                 bVRatioEn;                                     // 只读，面积占用比使能， 决定nVolumeRatio是否有效
	int                  nVolumeRatio;                                  // 面积占用比,1-100
	BOOL                 bSRatioEn;                                     // 只读，灵敏度使能，决定nSubRatio值是否有效
	int                  nSubRatio;                                     // 动检的残差阈值, 1-100
	BOOL                 abWindow;                                      // 此字段及以下两个字段已废弃
	int                  nWindowCount;                                  // 视频窗口个数
	CFG_MOTION_WINDOW    stuWindows[MAX_MOTION_WINDOW];                 // 视频窗口数组
	BOOL                 abDetectRegion;                                // 只读，1：nRegionCount，stuRegion有效
                                                                        //       0：nMotionRow，nMotionCol，byRegion有效
	int                  nRegionCount;                                  // 三代动态检测区域个数
	CFG_DETECT_REGION    stuRegion[MAX_MOTION_WINDOW];                  // 三代动态检测区域
} CFG_MOTION_INFO;

// 视频丢失报警配置
typedef struct tagCFG_VIDEOLOST_INFO 
{
	int					nChannelID;									// 报警通道号(0开始)
	BOOL				bEnable;									// 使能开关
	CFG_ALARM_MSG_HANDLE stuEventHandler;							// 报警联动
	CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT];// 事件响应时间段
} CFG_VIDEOLOST_INFO;

// 视频遮挡报警配置
typedef struct tagCFG_SHELTER_INFO 
{
	int					nChannelID;									// 报警通道号(0开始)
	BOOL				bEnable;									// 使能开关
	int					nSenseLevel;								// 灵敏度
	CFG_ALARM_MSG_HANDLE stuEventHandler;							// 报警联动
	CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT];// 事件响应时间段
} CFG_SHELTER_INFO;

// 无存储设备报警配置
typedef struct tagCFG_STORAGENOEXIST_INFO 
{
	BOOL				bEnable;						// 使能开关
	CFG_ALARM_MSG_HANDLE stuEventHandler;				// 报警联动
} CFG_STORAGENOEXIST_INFO;

// 存储设备访问出错报警配置
typedef struct tagCFG_STORAGEFAILURE_INFO 
{
	BOOL				bEnable;						// 使能开关
	CFG_ALARM_MSG_HANDLE stuEventHandler;				// 报警联动
} CFG_STORAGEFAILURE_INFO;

// 存储设备空间不足报警配置
typedef struct tagCFG_STORAGELOWSAPCE_INFO 
{
	BOOL				bEnable;						// 使能开关
	int					nLowerLimit;					// 硬盘剩余容量下限，百分数(0~99)
	CFG_ALARM_MSG_HANDLE stuEventHandler;				// 报警联动
} CFG_STORAGELOWSAPCE_INFO;

// 网络断开报警配置
typedef struct tagCFG_NETABORT_INFO 
{
	BOOL				bEnable;						// 使能开关
	CFG_ALARM_MSG_HANDLE stuEventHandler;				// 报警联动
} CFG_NETABORT_INFO;

// IP冲突报警配置
typedef struct tagCFG_IPCONFLICT_INFO 
{
	BOOL				bEnable;						// 使能开关
	CFG_ALARM_MSG_HANDLE stuEventHandler;				// 报警联动
} CFG_IPCONFLICT_INFO;

// CLIENT_QueryNewSystemInfo 接口的命令 CFG_CAP_ALARM (获取报警能力集)对应结构体

// 传感器报警方式
typedef struct tagCFG_ALARM_SENSE_METHOD
{
	int                 nSupportSenseMethodNum;								// 支持的传感器方式数
	EM_SENSE_METHOD     emSupportSenseMethod[MAX_ALARM_SENSE_METHOD_NUM];   // 支持的传感器方式
}CFG_ALARM_SENSE_METHOD;

typedef struct tagCFG_CAP_ALARM_INFO
{
	BOOL                 bAlarmPir;									// 设备是否支持PIR(人体热式感应器)报警,外部报警的一种
	BOOL                 bFlashLight;								// 设备是否支持补光灯
	int					 nDefenceAreaTypeNum;						// 防区类型种类数,为0表示无此字段时报警输入不作为防区使用。
	EM_CFG_DEFENCEAREATYPE	emDefenceAreaType[MAX_ALARM_DEFENCE_TYPE_NUM];			// 支持防区类型 
	int				 	 nMaxDelay;									// 延时防区的最大延时时间,单位为秒，只有支持延时防区时此字段才有效。
	int					 nAlarmChannelNum;							// 报警通道数,为了保持兼容性,此为0时表示每个通道支持所有类型的传感器
	CFG_ALARM_SENSE_METHOD stuAlarmChannel[MAX_ALARM_CHANNEL_NUM];	// 报警通道集合
	int					 nAlarmBellCount;							// 警号个数
	int					 nMaxBackupAlarmServer;						// 最大备用报警中心数,无此字段时默认为0,0表示不支持备用报警中心
	int					 nMaxPSTNAlarmServer;						// 最大电话报警中心数, 无此字段时默认为0,0表示不支持电话报警中心。
}CFG_CAP_ALARM_INFO;

// 补光灯配置
typedef struct tagCFG_FLASH_LIGHT
{
	BOOL                bEnable;                        // 使能开关
	int                 nBrightness;                    // 亮度 0~100
	CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT];// 补光灯工作时间段
}CFG_FLASH_LIGHT;

typedef struct tagCFG_CUSTOMCASE
{
	char                szCaseTitle[MAX_OSD_TITLE_LEN];    // 案件名称
	char                szCaseContent[MAX_OSD_SUMMARY_LEN];  // 案件名称
	BOOL                bCaseNoOsdEn;                        // 案件编号叠加使能
}CFG_CUSTOMCASE;

// 时间
typedef struct tagCFG_NET_TIME
{
    int                 nStructSize;
    DWORD				dwYear;					// 年
    DWORD				dwMonth;				// 月
    DWORD				dwDay;					// 日
    DWORD				dwHour;					// 时
    DWORD				dwMinute;				// 分
    DWORD				dwSecond;				// 秒
} CFG_NET_TIME;

// 司法刻录配置
typedef struct tagCFG_JUDICATURE_INFO
{
	char                szDiskPassword[MAX_PASSWORD_LEN];  // 光盘密码(废弃, 使用szPassword和nPasswordLen)
	char                szCaseNo[MAX_OSD_SUMMARY_LEN];     // 案件编号
	BOOL                bCaseNoOsdEn;                      // 案件编号叠加使能
	char                szCaseTitle[MAX_OSD_SUMMARY_LEN];  // 案件名称
	BOOL                bCaseTitleOsdEn;                   // 案件名称叠加使能
	char                szOfficer[MAX_OSD_SUMMARY_LEN];    // 办案人员
	BOOL                bOfficerOsdEn;                     // 办案人员叠加使能
	char                szLocation[MAX_OSD_SUMMARY_LEN];   // 办案地点
	BOOL                bLocationOsdEn;                    // 办案地点叠加使能
	char                szRelatedMan[MAX_OSD_SUMMARY_LEN]; // 涉案人员
	BOOL                bRelatedManOsdEn;                  // 涉案人员叠加使能
	char                szDiskNo[MAX_OSD_SUMMARY_LEN];     // 光盘编号
	BOOL                bDiskNoOsdEn;                      // 光盘编号叠加使能

	BOOL                bCustomCase;                       // TRUE:自定义司法案件信息,FALSE: 上边szCaseNo等字段有效
	int                 nCustomCase;                       // 实际CFG_CUSTOMCASE个数
	CFG_CUSTOMCASE      stuCustomCases[MAX_CUSTOMCASE_NUM];// 自定义司法案件信息

	BOOL                bDataCheckOsdEn;                   // 光盘刻录数据校验配置 叠加使能
	BOOL                bAttachFileEn;                     // 附件上传使能
    char                szPassword[MAX_PASSWORD_LEN];      // 密码, 刻录光盘时、配置读保护密码
    int                 nPasswordLen;                      // 密码长度
    CFG_NET_TIME        stuStartTime;                      // 片头信息叠加开始时间
    int                 nPeriod;                           // 片头信息叠加时间长度，单位：分钟
}CFG_JUDICATURE_INFO;

// 刻录满事件配置
typedef struct tagCFG_BURNFULL_ONE
{
	char                szBurnDisk[MAX_NAME_LEN];          // 刻录设备
	BOOL                bEnable;                           // 使能开关
	unsigned int        nLowerLimit;                       // 光盘剩余容量下限	单位：M
	BOOL                bBurnStop;                         // 刻录停止使能
	CFG_ALARM_MSG_HANDLE stuEventHandler;							// 报警联动
	CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT];// 事件响应时间段
}CFG_BURNFULL_ONE;

typedef struct tagCFG_BURNFULL_INFO
{
	unsigned int        nBurnDev;                          // 实际刻录设备个数
	CFG_BURNFULL_ONE    stuBurns[MAX_BURNING_DEV_NUM];     // 每个元素对应一个刻录设备
}CFG_BURNFULL_INFO;

//-------------------------------抓图配置能力---------------------------------
// 抓图配置能力
typedef struct tagCFG_SNAPCAPINFO_INFO  
{
	int					nChannelID;						// 抓图通道号(0开始)
	DWORD				dwIMageSizeNum;					// 支持的分别率信息
	CFG_CAPTURE_SIZE	emIMageSizeList[MAX_IMAGESIZE_NUM];
	DWORD				dwFramesPerSecNum;				// 支持的帧率信息
	int					nFramesPerSecList[MAX_FPS_NUM];
	DWORD				dwQualityMun;					// 支持的画质信息
	CFG_IMAGE_QUALITY	emQualityList[MAX_QUALITY_NUM];

	DWORD               dwMode;							// 模式,按位：第一位：定时；第二位：手动。
	DWORD               dwFormat;						// 图片格式模式,按位：第一位：bmp；第二位：jpg。
} CFG_SNAPCAPINFO_INFO;


//-------------------------------网络存储服务器配置---------------------------------
// 网络存储服务器配置
typedef struct tagCFG_CHANNEL_TIME_SECTION 
{
	CFG_TIME_SECTION stuTimeSection[WEEK_DAY_NUM][MAX_NAS_TIME_SECTION];//存储时间段
} CFG_CHANNEL_TIME_SECTION;

typedef struct tagCFG_NAS_INFO
{
	BOOL						bEnable;									// 使能开关
	int							nVersion;									// 网络存储服务器版本0=老的FTP，1=NAS存储
	int							nProtocol;									// 协议类型0=FTP 1=SMB
	char						szAddress[MAX_ADDRESS_LEN];					// IP地址或网络名
	int							nPort;										// 端口号
	char						szUserName[MAX_USERNAME_LEN];				// 帐户名
	char						szPassword[MAX_PASSWORD_LEN];				// 密码
	char						szDirectory[MAX_DIRECTORY_LEN];				// 共享的目录名
	int							nFileLen;									// 文件长度
	int							nInterval;									// 相邻文件时间间隔
	CFG_CHANNEL_TIME_SECTION	stuChnTime[MAX_VIDEO_CHANNEL_NUM];			// 存储时间段
	int                         nChnTimeCount;                              // 有效的存储时间段数
} CFG_NAS_INFO;

//------------------------------云台配置--------------------------------------------
// 协议名
typedef struct tagCFG_PRONAME
{
	char				name[MAX_NAME_LEN];			// 协议名
} CFG_PRONAME;

// 串口基本属性
typedef struct tagCFG_COMM_PROP
{
	BYTE				byDataBit;					// 数据位；0：5，1：6，2：7，3：8
	BYTE				byStopBit;					// 停止位；0：1位，1：1.5位，2：2位
	BYTE				byParity;					// 校验位；0：无校验，1：奇校验；2：偶校验
	BYTE				byBaudRate;					// 波特率；0：300，1：600，2：1200，3：2400，4：4800，													
	                                                // 5：9600，6：19200，7：38400，8：57600，9：115200
} CFG_COMM_PROP;

// 归位预置点配置
typedef struct tagCFG_PRESET_HOMING
{
	int          nPtzPresetId;   //云台预置点编号	0~65535
 //-1表示无效
	int          nFreeSec;       //空闲的时间，单位为秒
}CFG_PRESET_HOMING;

// 云台配置
typedef struct tagCFG_PTZ_INFO
{
	// 能力
	bool				abMartixID;
	bool				abCamID;
	bool				abPTZType;

	// 信息
	int					nChannelID;								// 通道号(0开始)
	BOOL                bEnable;                                // 使能开关
	char                szProName[MAX_NAME_LEN];                // 协议名称
	int					nDecoderAddress;						// 解码器地址；0 - 255
	CFG_COMM_PROP		struComm;
	int					nMartixID;								// 矩阵号
	int					nPTZType;								// 云台类型0-兼容，本地云台 1-远程网络云台
	int					nCamID;									// 摄像头ID
	int                 nPort;                                  // 使用的串口端口号
	CFG_PRESET_HOMING   stuPresetHoming;                        // 一段时间不操作云台，自动归位到某个预置点
	int                 nControlMode;                           // 控制模式, 0:"RS485"串口控制(默认);1:"Coaxial" 同轴口控制
} CFG_PTZ_INFO;  

//定时功能类型
typedef enum tagCFG_PTZ_FUNC_TYPE
{
	FUNC_TYPE_TOUR = 0 ,		//巡航
	FUNC_TYPE_PATTERN  ,		//自动巡迹
	FUNC_TYPE_PRE	   ,		//预置点
	FUNC_TYPE_SCAN	   ,		//自动线扫
	FUNC_TYPE_MAX	   ,		
}CFG_PTZ_FUNC_TYPE;


//自动归位
typedef struct tagCFG_AUTO_HOMING
{
	BOOL	bEnable;		// 自动归位开关
	int		nTime;			// 空闲时间,表示空闲的时间，单位为秒
}CFG_AUTO_HOMING;

//定时动作配置
typedef struct tagCFG_PTZ_PER_AUTOMOVE_INFO
{
	BOOL				bEnable;				//	定时动作开关标志 TRUE 开，FALSE 关
	CFG_TIME_SCHEDULE	stTimeSchedule;			//  时间表类型
	CFG_PTZ_FUNC_TYPE	emFuncType;				//  定时功能
	int					nTourId;				// 	巡航编号,		范围参照CFG_PTZ_PROTOCOL_CAPS_INFO的wTourMin和wTourMax
	int					nPatternId;				// 	自动巡迹编号,	范围参照CFG_PTZ_PROTOCOL_CAPS_INFO的wPatternMin和wPatternMax
	int					nPresetId;				//  预置点编号,		范围参照CFG_PTZ_PROTOCOL_CAPS_INFO的wPresetMin和wPresetMax
	int					nScanId;				//	自动线扫编号,	范围参照CFG_PTZ_PROTOCOL_CAPS_INFO的wAutoScanMin和wAutoScanMax
	CFG_AUTO_HOMING		stAutoHoming;			//  自动归位,一段时间不操作云台，自动归位到该时间段内的动作
	BOOL				bSnapshotEnable;		//	预置点快照使能,只有当emFuncType为FUNC_TYPE_PRE时才有效
	int					nSnapshortDelayTime;	//	预置点抓拍延时时间,单位秒,只有当emFuncType为FUNC_TYPE_PRE时才有效
}CFG_PTZ_PER_AUTOMOVE_INFO;

typedef struct tagCFG_PTZ_ALL_AUTOMOVE_INFO
{
	CFG_PTZ_PER_AUTOMOVE_INFO stPTZPerInfo[MAX_CONFIG_NUM];		//配置信息
	int						  nCfgNum;							//获取到的配置个数
}CFG_PTZ_ALL_AUTOMOVE_INFO;

//云台定时动作配置，注意，此结构针对设备
typedef struct tagCFG_PTZ_AUTOMOVE_INFO
{
	CFG_PTZ_ALL_AUTOMOVE_INFO *pstPTZAutoConfig;				//云台的配置信息
	int						   nMaxPTZNum;						//结构体申请的云台个数(对于多通道查询，申请不小于设备通数，对于单通道查询，一个就够了)
	int						   nReturnPTZNum;					//设备返回的云台个数(一般为设备通道数)
}CFG_PTZ_AUTOMOVE_INFO;

//----------------------------------视频分析设备配置------------------------------------------
// 场景支持的规则
typedef struct
{
	DWORD             dwSupportedRule;                                         // 规则类型
	int               nSupportedObjectTypeNum;                                 // 支持的检测物体类型个数
	char              szObjectTypeName[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];	   // 支持的检测物体类型列表
	int               nSupportedActionsNum;                                    // 支持的检测物体动作个数
	char              szSupportedActions[MAX_ACTION_LIST_SIZE][MAX_NAME_LEN];  // 支持的检测物体动作列表
	int               nSupportedDetectTypeNum;                                 // 支持的检测类型个数
	char              szSupportedDetectTypes[MAX_ACTION_LIST_SIZE][MAX_NAME_LEN];// 支持的检测类型列表
	int               nSupportFaceTypeNum;                                       // 支持的人脸检测类型个数
	char              szSupportFaceTypes[MAX_HUMANFACE_LIST_SIZE][MAX_NAME_LEN]; // 支持的人脸检测类型列表
	BOOL              bTriggerPosition;                                        // 是否支持触发报警位置
}SCENE_SUPPORT_RULE;

// 标定区域能力信息
typedef struct tagCFG_CAP_CELIBRATE_AREA
{
	EM_CALIBRATEAREA_TYPE  emType;												 // 标定区域类型
	BYTE                   byMaxHorizontalStaffNum;                              // 支持的水平标尺最大个数
	BYTE                   byMinHorizontalStaffNum;                              // 支持的水平标尺最小个数
	BYTE                   byMaxVerticalStaffNum;                                // 支持的垂直标尺最大个数
	BYTE                   byMinVerticalStaffNum;                                // 支持的垂直标尺最小个数
}CFG_CAP_CELIBRATE_AREA;

// 场景能力
typedef struct tagCFG_CAP_SCENE
{
	char               szSceneName[MAX_PATH];                                   // 场景名称
	int                nSupportedObjectTypeNum;                                 // 当前规则类型支持的检测物体类型个数
	char               szObjectTypeName[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];	// 当前规则类型支持的检测物体类型列表
	int                nSupportRules;                                           // 支持的规则个数
	SCENE_SUPPORT_RULE stSpportRules[MAX_RULE_LIST_SIZE];                       // 支持的规则列表

	//支持的模块参数
	bool               bDisturbance;                                            // 是否支持扰动强度设置
	bool               bAntiDisturbance;                                        // 是否支持去扰动处理
	bool               bBacklight;                                              // 是否支持逆光处理
	bool               bShadow;                                                 // 是否支持阴影处理
	bool               bAccuracy;                                               // 是否支持检测精度
	bool               bMovingStep;												// 是否支持检测步长
	bool               bScalingFactor;                                          // 是否支持检测缩放
	bool               bThresholdY;                                             // 是否支持Y分量判定阈值
	bool               bThresholdUV;                                            // 是否支持UV分量判定阈值
	bool               bThresholdEdge;                                          // 是否支持边缘检测判定阈值
	bool               bDetectBalance;                                          // 是否支持检测平衡
	bool               bAlgorithmIndex;                                         // 是否支持算法序号
	bool               bHighlight;                                              // 是否支持高光处理，即Backgroud参数 
	bool               bSnapshot;                                               // 是否支持物体抓图
	bool               bDetectRegion;                                           // 是否支持检测区域配置
	bool               bExcludeRegion;                                          // 是否支持排除区域配置
	bool               bContourAssistantTrack;                                  // 是否支持轮廓辅助跟踪

	//支持的场景参数
	bool               bCameraAspect;                                            // 是否摄像头位置参数
	bool               bJitter;                                                  // 是否支持抖动参数
	bool               bDejitter;                                                // 是否支持去抖动处理参数

	// 支持的标定能力集
	int               nMaxCalibrateAreaNum;                                      // 最大标定区域个数
	int               nCalibrateAreaNum;                                         // 标定区域能力信息个数
	CFG_CAP_CELIBRATE_AREA stCalibrateAreaCap[MAX_CALIBRATEAREA_TYPE_NUM];       // 标定区域能力信息

	// 尺寸过滤器计量方式
	bool              bPixel;                                                    // 是否支持像素计量方式
	bool              bMetric;                                                   // 是否支持实际长度计量方式
	bool              bCalibratedPixel;                                          // 是否支持远端近端标定后的像素计量方式

	char              szSubType[MAX_SCENE_SUBTYPE_NUM][MAX_SCENE_SUBTYPE_LEN];  // 当前场景下支持的子场景类型
	int               nSubTypeNum;                                              // 子场景类型个数
}CFG_CAP_SCENE;

// 场景列表
typedef struct tagCFG_VACAP_SUPPORTEDSCENES
{
	int                nScenes;													   // 支持的场景个数
	CFG_CAP_SCENE      stScenes[MAX_SCENE_LIST_SIZE];                              // 支持的场景列表
}CFG_VACAP_SUPPORTEDSCENES;

#define CFG_DEVICE_ANALYSE_INFO CFG_CAP_DEVICE_ANALYSE_INFO
//视频分析设备能力信息
typedef struct tagCFG_CAP_DEVICE_ANALYSE_INFO
{
	int                nMaxChannels;											 // 支持智能分析的最大通道数
}CFG_CAP_DEVICE_ANALYSE_INFO;

// 某个规则支持的物体类型
typedef struct
{
	DWORD               dwRuleType;                                             // 当前规则类型
	int					nSupportedObjectTypeNum;								// 当前规则类型支持的检测物体类型个数
	char				szObjectTypeName[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];	// 当前规则类型支持的检测物体类型列表
}RULE_SUPPORTED_OBJECT_TYPE;

// 视频分析能力集
typedef struct tagCFG_CAP_ANALYSE_INFO
{
	int					nSupportedSceneNum;										// 支持的场景个数
	char				szSceneName[MAX_SCENE_LIST_SIZE][MAX_NAME_LEN];			// 支持的场景列表
	int					nMaxMoudles;											// 每通道支持最大分析模块数
	int					nSupportedObjectTypeNum;								// 支持的检测物体类型个数
	char				szObjectTypeName[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];	// 支持的检测物体类型列表
	int					nMaxRules;												// 每通道支持最大规则条数
	int					nSupportedRulesNum;										// 支持的事件类型规则个数
	DWORD				dwRulesType[MAX_RULE_LIST_SIZE];	             		// 支持的事件类型规则列表，事件类型，详见dhnetsdk.h中"智能分析事件类型"
	int					nMaxStaffs;												// 支持的最大标尺个数
	int					nMaxPointOfLine;										// 折线最大顶点数
	int					nMaxPointOfRegion;										// 区域最大顶点数
	int                 nMaxInternalOptions;                                    // 最大内部选项个数
	bool                bComplexSizeFilter;                                     // 是否支持复杂尺寸过滤器	复杂尺寸过滤器使用独立的面积过滤和宽高比过滤参数。      
	bool                bSpecifiedObjectFilter;                                 // 是否支持特定的物体过滤器
	int                 nMaxExcludeRegionNum;                                   // 支持模块中的最大排除区域个数
	int                 nMaxCalibrateBoxNum;                                    // 支持的模块中的最大校准框个数
	int                 nMinCalibrateBoxNum;                                    // 模块中至少需要设置的校准框个数
	int                 nMaxSepcialDetectRegions;                               // 模块中支持的最大特殊区域检测个数
	int                 nSupportedTimeSectionNum;                               // 支持的每天的时间段个数 
	int                 nSpecialDetectPropertyNum;                              // 支持的特殊检测区属性个数
	int			        nSupportedSpecialDetectPropertys[EM_SEPCIALREGION_PROPERTY_TYPE_NUM]; // 支持的特殊检测区属性
	DWORD				nSupportedVideoChannelType;								// 支持的视频通道类型选择   第0位为1表示支持数字类型,第1位为1表示支持模拟类型,第2为1表示支持混合(数字和模拟)				
	bool				bSupportMultiSceneSwitch;								// 是否支持多场景切换
	CFG_VACAP_SUPPORTEDSCENES  stSupportScenes;                                 // 支持的场景能力集
} CFG_CAP_ANALYSE_INFO;

// 校准框信息
typedef struct tagCFG_CALIBRATEBOX_INFO
{
	CFG_POLYGON         stuCenterPoint;                       // 校准框中心点坐标(点的坐标归一化到[0,8191]区间)
	float               fRatio;                               // 相对基准校准框的比率(比如1表示基准框大小，0.5表示基准框大小的一半)
}CFG_CALIBRATEBOX_INFO;

// 标定区域,普通场景使用
typedef struct tagCFG_CALIBRATEAREA_INFO
{
	int               nLinePoint;                             // 水平方向标尺线顶点数
	CFG_POLYGON       stuLine[MAX_POLYLINE_NUM];              // 水平方向标尺线
	float             fLenth;                                 // 实际长度
	CFG_REGION        stuArea;                                // 区域
	int                 nStaffNum;                            // 垂直标尺数
	CFG_STAFF           stuStaffs[MAX_STAFF_NUM];             // 垂直标尺         
	EM_CALIBRATEAREA_TYPE emType;							  // 区域类型
}CFG_CALIBRATEAREA_INFO;

// 人脸识别场景
typedef struct tagCFG_FACERECOGNITION_SCENCE_INFO
{
	double				dbCameraHeight;							// 摄像头离地高度 单位：米
	double				dbCameraDistance;						// 摄像头离地面检测区域中心的水平距离 单位：米
	int                 nMainDirection;                         // 人流主要方向顶点数
	CFG_POLYGON         stuMainDirection[MAX_POLYLINE_NUM];     // 人流主要方向，第一个点是起始点，第二个点是终止点
	char                byFaceAngleDown;                        // 需要检测的人脸向下最大偏角, 单位度，-45~45，负数表示人脸向画面上边，正数表示人脸向画面下边，0表示人脸垂直方向上正对着摄像头。
	char                byFaceAngleUp;                          // 需要检测的人脸向上最大偏角,单位度，-45~45，负数表示人脸向画面上边，正数表示人脸向画面下边，0表示人脸垂直方向上正对着摄像头。
 	char                byFaceAngleLeft;                        // 需要检测的人脸向左最大偏角,单位度，-45~45，负数表示人脸向画面左边，正数表示人脸向画面右边，0表示人脸水平方向上正对着摄像头
	char                byFaceAngleRight;                       // 需要检测的人脸向右最大偏角,单位度，-45~45，负数表示人脸向画面左边，正数表示人脸向画面右边，0表示人脸水平方向上正对着摄像头
	EM_FACEDETECTION_TYPE	emDetectType;						// 人脸检测类型
}CFG_FACERECOGNITION_SCENCE_INFO;

// 人脸检测场景
typedef struct tagCFG_FACEDETECTION_SCENCE_INFO
{
	double				dbCameraHeight;							// 摄像头离地高度 单位：米
	double				dbCameraDistance;						// 摄像头离地面检测区域中心的水平距离 单位：米
	int                 nMainDirection;                         // 人流主要方向顶点数
	CFG_POLYGON         stuMainDirection[MAX_POLYLINE_NUM];     // 人流主要方向，第一个点是起始点，第二个点是终止点
	char                byFaceAngleDown;                        // 需要检测的人脸向下最大偏角, 单位度，-45~45，负数表示人脸向画面上边，正数表示人脸向画面下边，0表示人脸垂直方向上正对着摄像头。
	char                byFaceAngleUp;                          // 需要检测的人脸向上最大偏角,单位度，-45~45，负数表示人脸向画面上边，正数表示人脸向画面下边，0表示人脸垂直方向上正对着摄像头。
	char                byFaceAngleLeft;                        // 需要检测的人脸向左最大偏角,单位度，-45~45，负数表示人脸向画面左边，正数表示人脸向画面右边，0表示人脸水平方向上正对着摄像头
	char                byFaceAngleRight;                       // 需要检测的人脸向右最大偏角,单位度，-45~45，负数表示人脸向画面左边，正数表示人脸向画面右边，0表示人脸水平方向上正对着摄像头
	EM_FACEDETECTION_TYPE	emDetectType;						// 人脸检测类型
}CFG_FACEDETECTION_SCENCE_INFO;

// 交通场景
typedef struct tagCFG_TRAFFIC_SCENE_INFO 
{
	BOOL                abCompatibleMode;	
	int                 nCompatibleMode;                        // 0:"OldTrafficRule" : 交通老规则兼容模式;1:"NewTrafficRule" :  交通新规则兼容模式;-1:字符串错误
	float				fCameraHeight;							// 摄像头离地高度	单位：米
	float				fCameraDistance;						// 摄像头离地面检测区域中心的水平距离	单位：米
	char                szSubType[MAX_NAME_LEN];                // 交通场景的子类型,"Gate" 卡口类型,"Junction" 路口类型 
																// "Tunnel"隧道类型 , "ParkingSpace"车位检测类型
																// "Bridge"桥梁类型
																// "Freeway"高速公路类型                 
	CFG_POLYGON         stuNearDetectPoint;                     // 近景检测点
	CFG_POLYGON         stuFarDectectPoint;                     // 远景检测点
	int                 nNearDistance;                          // NearDetectPoint,转换到实际场景中时,离摄像头垂直线的水平距离
	int                 nFarDistance;                           // FarDectectPoint,转换到实际场景中时,离摄像头垂直线的水平距离
	int                 nPlateHintNum;                          // 车牌字符暗示个数
	char                szPlateHints[MAX_PLATEHINT_NUM][MAX_NAME_LEN]; // 车牌字符暗示数组，在拍摄图片质量较差车牌识别不确定时，根据此数组中的字符进行匹配，数组下标越小，匹配优先级越高
	int                 nLaneNum;                               // 车道数
	CFG_LANE            stuLanes[MAX_LANE_NUM];                 // 车道信息
} CFG_TRAFFIC_SCENE_INFO;

// 普遍场景
typedef struct tagCFG_NORMAL_SCENE_INFO
{
	float				fCameraHeight;							// 摄像头离地高度	单位：米
	float				fCameraAngle;							// 摄像头与垂方向的夹角	单位度，0~90，
	float				fCameraDistance;						// 摄像头离地面检测区域中心的水平距离	单位：米
	CFG_POLYGON			stuLandLineStart;						// 地平线线段起始点(点的坐标坐标归一化到[0,8192)区间。)
	CFG_POLYGON			stuLandLineEnd;							// 地平线线段终止点(点的坐标坐标归一化到[0,8192)区间。)
} CFG_NORMAL_SCENE_INFO;

// 交通巡视场景
typedef struct tagCFG_TRAFFIC_TOUR_SCENE_INFO 
{
	int                 nPlateHintNum;                          // 车牌字符暗示个数
	char                szPlateHints[MAX_PLATEHINT_NUM][MAX_NAME_LEN]; // 车牌字符暗示数组，在拍摄图片质量较差车牌识别不确定时，根据此数组中的字符进行匹配，数组下标越小，匹配优先级越高
} CFG_TRAFFIC_TOUR_SCENE_INFO;

// 视频分析全局配置场景
typedef struct tagCFG_ANALYSEGLOBAL_SCENE
{
	char				szSceneType[MAX_NAME_LEN];				// 应用场景,详见"支持的场景列表"

	// 以下为场景具体信息, 根据szSceneType决定哪个场景有效
	union
	{
		CFG_FACEDETECTION_SCENCE_INFO	stuFaceDetectionScene;	// 人脸检测场景/人脸识别检查
		CFG_TRAFFIC_SCENE_INFO			stuTrafficScene;		// 交通场景
		CFG_NORMAL_SCENE_INFO			stuNormalScene;			// 普通场景/远景场景/中景场景/近景场景/室内场景/人数统计场景
		CFG_TRAFFIC_TOUR_SCENE_INFO		stuTrafficTourScene;	// 交通巡视场景
	};
} CFG_ANALYSEGLOBAL_SCENE;

typedef struct tagCFG_TIME
{
	DWORD				dwHour;					// 时
	DWORD				dwMinute;				// 分
	DWORD				dwSecond;				// 秒
}CFG_TIME;

typedef struct tagCFG_TIME_PERIOD
{
	CFG_TIME	stuStartTime;				
	CFG_TIME	stuEndTime;			
}CFG_TIME_PERIOD;

// 多场景标定区域配置基本单元
typedef struct tagCFG_CALIBRATEAREA_SCENE_UNIT
{
	unsigned int           nCalibrateAreaNum;                                // 此场景内标定区域数
	CFG_CALIBRATEAREA_INFO stuCalibrateArea[MAX_CALIBRATEBOX_NUM];           // 标定区域(若该字段不存在，则以整幅场景为标定区域)
}
CFG_CALIBRATEAREA_SCENE_UNIT;

// 多场景标定区域配置
typedef struct tagCFG_CALIBRATEAREA_SCENE_INFO
{
	DWORD                        dwMaxSceneCalibrateAreaNum;                 // 多场景标定区域最大个数(需要申请此大小内存)
	DWORD                        dwRetSceneCalibrateAreaNum;                 // 实际包含多场景标定区域个数
	CFG_CALIBRATEAREA_SCENE_UNIT *pstuCalibrateArea;                         // 多场景标定区域单元
}
CFG_CALIBRATEAREA_SCENE_INFO;

// 云台控制坐标单元
typedef struct tagCFG_PTZ_SPACE_UNIT
{
	int                    nPositionX;           //云台水平运动位置，有效范围：[0,3600]
	int                    nPositionY;           //云台垂直运动位置，有效范围：[-1800,1800]
	int                    nZoom;                //云台光圈变动位置，有效范围：[0,128]
}CFG_PTZ_SPACE_UNIT;

// 标定区域配置
typedef struct tagCFG_CALIBRATEAREA_UNIT
{
	int                          nSceneID;                                 // 场景编号
	int                          nPtzPresetID;                             // 预置点编号
	BOOL                         abCalibrateArea;                          // 标定区域是否存在
	CFG_CALIBRATEAREA_SCENE_UNIT stuCalibrateArea;                         // 标定区域
	CFG_PTZ_SPACE_UNIT           stuPtzPosition;                           // 标定的云台位置
}
CFG_VIDEO_ANALYSE_CALIBRATEAREA_UNIT;

// 标定区域配置
typedef struct tagCFG_VIDEO_ANALYSE_CALIBRATEAREA
{

	DWORD                                dwMaxSceneCalibrateNum;           // 多场景标定区域最大个数(需要申请此大小内存)
	DWORD                                dwRetSceneCalibrateNum;           // 实际包含多场景标定区域个数
	CFG_VIDEO_ANALYSE_CALIBRATEAREA_UNIT *pstuCalibrateAreaUnit;           // 标定区域
}
CFG_VIDEO_ANALYSE_CALIBRATEAREA;

// 昼夜算法切换模式
typedef enum tagCFG_TIMEPERIOD_SWITCH_MODE
{
	CFG_TIMEPERIOD_SWITCH_MODE_UNKNOWN,                                     // 未知
	CFG_TIMEPERIOD_SWITCH_MODE_BYCOLOR,                                    // 通过色彩切换                     
	CFG_TIMEPERIOD_SWITCH_MODE_BYBRIGHTNESS,                               // 通过亮度切换
}CFG_TIMEPERIOD_SWITCH_MODE;

// 多场景标定白天和黑夜配置基本单元
typedef struct tagCFG_TIME_PERIOD_SCENE_UNIT
{
	CFG_TIME_PERIOD        stuDayTimePeriod;								 // 标定白天的时间段.(8,20),表示从8点到晚上20点为白天
	CFG_TIME_PERIOD        stuNightTimePeriod;								 // 标定黑夜的时间段.(20,7)，表示从晚8点到凌晨7点为黑夜
	CFG_TIMEPERIOD_SWITCH_MODE emSwitchMode;                                  // 昼夜算法切换模式，详见CFG_TIMEPERIOD_SWITCH_MODE
}
CFG_TIME_PERIOD_SCENE_UNIT;

// 多场景标定白天和黑夜配置
typedef struct tagCFG_TIME_PERIOD_SCENE_INFO
{
	DWORD                        dwMaxTimePeriodSceneNum;                    // 多场景标定白天和黑夜配置最大个数(需要申请此大小内存)
	DWORD                        dwRetTimePeriodSceneNum;                    // 实际包含多场景标定白天和黑夜配置个数
	CFG_TIME_PERIOD_SCENE_UNIT   *pstuTimePeriodScene;                       // 多场景标白天和黑夜配置域单元
}
CFG_TIME_PERIOD_SCENE_INFO;

// 视频分析全局配置
typedef struct tagCFG_ANALYSEGLOBAL_INFO
{
	// 信息
	char				szSceneType[MAX_NAME_LEN];				// 应用场景,详见"支持的场景列表"

	//交通场景信息
	double				CameraHeight;							// 摄像头离地高度	单位：米
	double				CameraDistance;							// 摄像头离地面检测区域中心的水平距离	单位：米
	CFG_POLYGON         stuNearDetectPoint;                     // 近景检测点
	CFG_POLYGON         stuFarDectectPoint;                     // 远景检测点
	int                 nNearDistance;                          // NearDetectPoint,转换到实际场景中时,离摄像头垂直线的水平距离
	int                 nFarDistance;                           // FarDectectPoint,转换到实际场景中时,离摄像头垂直线的水平距离
	char                szSubType[MAX_NAME_LEN];                // 交通场景的子类型,"Gate",卡口类型,"Junction" 路口类型                            
	int                 nLaneNum;                               // 车道数
	CFG_LANE            stuLanes[MAX_LANE_NUM];                 // 车道信息
	int                 nPlateHintNum;                          // 车牌字符暗示个数
	char                szPlateHints[MAX_PLATEHINT_NUM][MAX_NAME_LEN]; // 车牌字符暗示数组，在拍摄图片质量较差车牌识别不确定时，根据此数组中的字符进行匹配，数组下标越小，匹配优先级越高
	int                 nLightGroupNum;                         // 灯组数
	CFG_LIGHTGROUPS     stLightGroups[MAX_LIGHTGROUP_NUM];      // 灯组配置信息

	// 一般场景信息 
	int                 nStaffNum;                              // 标尺数
	CFG_STAFF           stuStaffs[MAX_STAFF_NUM];               // 标尺

	unsigned int        nCalibrateAreaNum;                         // 标定区域数
	CFG_CALIBRATEAREA_INFO stuCalibrateArea[MAX_CALIBRATEBOX_NUM]; // 标定区域(若该字段不存在，则以整幅场景为标定区域)

	BOOL                bFaceRecognition;                          // 人脸识别场景是否有效
	CFG_FACERECOGNITION_SCENCE_INFO stuFaceRecognitionScene;       // 人脸识别场景
		
	bool                abJitter;
	bool                abDejitter;	
	BYTE                bReserved[2];                           // 保留字段

	int					nJitter;								// 摄像机抖动率 : 摄像机抖动率，取值0-100，反应静止摄像机抖动程度，抖动越厉害，值越大。
	BOOL                bDejitter;                              // 是否开启去抖动模块 目前不实现

	BOOL                abCompatibleMode;	
	int                 nCompatibleMode;                        // 0:"OldTrafficRule" : 交通老规则兼容模式;1:"NewTrafficRule" :  交通新规则兼容模式;-1:字符串错误

	int                 nCustomDataLen;                         // 实际数据长度，不能大于1024
	BYTE                byCustomData[1024];                     // 第三方自定义配置数据
	double				CameraAngle;							// 摄像头与垂方向的夹角
	CFG_POLYGON			stuLandLineStart;						// 地平线线段起始点(点的坐标坐标归一化到[0,8192)区间。)
	CFG_POLYGON			stuLandLineEnd;							// 地平线线段终止点(点的坐标坐标归一化到[0,8192)区间。)

	BOOL				bFaceDetection;							// 人脸检测场景是否有效
	CFG_FACEDETECTION_SCENCE_INFO	stuFaceDetectionScene;		// 人脸检测场景
	CFG_TIME_PERIOD		stuDayTimePeriod;						// 标定白天的时间段.(8,20),表示从8点到晚上20点为白天
	CFG_TIME_PERIOD		stuNightTimePeriod;						// 标定黑夜的时间段.(20,7)，表示从晚8点到凌晨7点为黑夜
	CFG_TIME_PERIOD_SCENE_INFO      stuTimePeriodSceneInfo;     // 多场景标定白天和黑夜时间段
	CFG_CALIBRATEAREA_SCENE_INFO    stuCalibrateAreaSceneInfo;  // 多场景标定区域配置信息
	CFG_TIMEPERIOD_SWITCH_MODE emSwitchMode;                    // 昼夜算法切换模式,详见CFG_TIMEPERIOD_SWITCH_MODE
	BYTE                bReserved2[2812];                       // 保留字段 用于扩展

	int					nSceneNum;									// 场景数, >0时表示支持多场景, stuMultiScene有效
	CFG_ANALYSEGLOBAL_SCENE	stuMultiScene[MAX_ANALYSE_SCENE_NUM];	// 多场景配置
} CFG_ANALYSEGLOBAL_INFO;

// 尺寸过滤器
typedef struct tagCFG_SIZEFILTER_INFO
{
	int                   nCalibrateBoxNum;                       // 校准框个数
	CFG_CALIBRATEBOX_INFO stuCalibrateBoxs[MAX_CALIBRATEBOX_NUM]; // 校准框(远端近端标定模式下有效)
	bool                bMeasureModeEnable;                       // 计量方式参数是否有效
	BYTE                bMeasureMode;                             // 计量方式,0-像素，不需要远端、近端标定, 1-实际长度，单位：米, 2-远端近端标定后的像素
	bool                bFilterTypeEnable;                        // 过滤类型参数是否有效
	// ByArea,ByRatio仅作兼容，使用独立的ByArea和ByRatio选项代替 2012/03/06
	BYTE				bFilterType;			 				  // 过滤类型:0:"ByLength",1:"ByArea", 2"ByWidthHeight"
	BYTE                bReserved[2];                             // 保留字段
	bool                bFilterMinSizeEnable;                     // 物体最小尺寸参数是否有效
	bool                bFilterMaxSizeEnable;                     // 物体最大尺寸参数是否有效
	CFG_SIZE			stuFilterMinSize;						  // 物体最小尺寸 "ByLength"模式下表示宽高的尺寸，"ByArea"模式下宽表示面积，高无效(远端近端标定模式下表示基准框的宽高尺寸)。
	CFG_SIZE			stuFilterMaxSize;				          // 物体最大尺寸 "ByLength"模式下表示宽高的尺寸，"ByArea"模式下宽表示面积，高无效(远端近端标定模式下表示基准框的宽高尺寸)。
	
	bool                abByArea;
	bool                abMinArea;
	bool                abMaxArea;
	bool                abMinAreaSize;
	bool                abMaxAreaSize;
	bool                bByArea;                                  // 是否按面积过滤 通过能力ComplexSizeFilter判断是否可用
	bool                bReserved1[2];
	float               nMinArea;                                 // 最小面积
	float               nMaxArea;                                 // 最大面积
	CFG_SIZE            stuMinAreaSize;                           // 最小面积矩形框尺寸 "计量方式"为"像素"时，表示最小面积矩形框的宽高尺寸；"计量方式"为"远端近端标定模式"时，表示基准框的最小宽高尺寸；
	CFG_SIZE            stuMaxAreaSize;                           // 最大面积矩形框尺寸, 同上
	
	bool                abByRatio;
	bool                abMinRatio;
	bool                abMaxRatio;
	bool                abMinRatioSize;
	bool                abMaxRatioSize;
	bool                bByRatio;                                 // 是否按宽高比过滤 通过能力ComplexSizeFilter判断是否可用
	bool                bReserved2[2];
	double              dMinRatio;                                // 最小宽高比
	double              dMaxRatio;                                // 最大宽高比
	CFG_SIZE            stuMinRatioSize;                          // 最小宽高比矩形框尺寸，最小宽高比对应矩形框的宽高尺寸。
	CFG_SIZE            stuMaxRatioSize;                          // 最大宽高比矩形框尺寸，同上
	
	int                 nAreaCalibrateBoxNum;                     // 面积校准框个数
	CFG_CALIBRATEBOX_INFO stuAreaCalibrateBoxs[MAX_CALIBRATEBOX_NUM];// 面积校准框
	int                 nRatioCalibrateBoxs;                      // 宽高校准框个数
	CFG_CALIBRATEBOX_INFO stuRatioCalibrateBoxs[MAX_CALIBRATEBOX_NUM];// 宽高校准框
	
	bool                abBySize;                                 // 长宽过滤使能参数是否有效
	bool                bBySize;                                  // 长宽过滤使能
}CFG_SIZEFILTER_INFO;

// 各种物体特定的过滤器
typedef struct tagCFG_OBJECT_SIZEFILTER_INFO
{
	char				szObjectType[MAX_NAME_LEN];              // 物体类型
	CFG_SIZEFILTER_INFO stSizeFilter;                            // 对应的尺寸过滤器
}CFG_OBJECT_SIZEFILTER_INFO;

// 特殊检测区，是指从检测区中区分出来，有特殊检测属性的区域
typedef struct tagCFG_SPECIALDETECTREGION_INFO
{
	int                nDetectNum;                              // 检测区域顶点数
	CFG_POLYGON        stDetectRegion[MAX_POLYGON_NUM];         // 检测区域
	int                nPropertyNum;                            // 特殊检测区属性个数
	int                nPropertys[EM_SEPCIALREGION_PROPERTY_TYPE_NUM];      // 特殊检测区属性
}CFG_SPECIALDETECT_INFO;

//各类物体的子类型
typedef enum tagCFG_CATEGORY_TYPE
{
    CFG_CATEGORY_TYPE_UNKNOW,                            // 未知类型
    //车型相关子类别
    CFG_CATEGORY_VEHICLE_TYPE_MOTOR,                     // "Motor" 机动车           
    CFG_CATEGORY_VEHICLE_TYPE_NON_MOTOR,                 // "Non-Motor"非机动车        
    CFG_CATEGORY_VEHICLE_TYPE_BUS,                       // "Bus"公交车        
    CFG_CATEGORY_VEHICLE_TYPE_BICYCLE,                   // "Bicycle" 自行车        
    CFG_CATEGORY_VEHICLE_TYPE_MOTORCYCLE,                // "Motorcycle"摩托车        
    CFG_CATEGORY_VEHICLE_TYPE_UNLICENSEDMOTOR,           // "UnlicensedMotor": 无牌机动车
    CFG_CATEGORY_VEHICLE_TYPE_LARGECAR,                  // "LargeCar"  大型汽车
    CFG_CATEGORY_VEHICLE_TYPE_MICROCAR,                  // "MicroCar" 小型汽车
    CFG_CATEGORY_VEHICLE_TYPE_EMBASSYCAR,                // "EmbassyCar" 使馆汽车
    CFG_CATEGORY_VEHICLE_TYPE_MARGINALCAR,               // "MarginalCar" 领馆汽车
    CFG_CATEGORY_VEHICLE_TYPE_AREAOUTCAR,                // "AreaoutCar" 境外汽车
    CFG_CATEGORY_VEHICLE_TYPE_FOREIGNCAR,                // "ForeignCar" 外籍汽车
    CFG_CATEGORY_VEHICLE_TYPE_DUALTRIWHEELMOTORCYCLE,    // "DualTriWheelMotorcycle"两、三轮摩托车
    CFG_CATEGORY_VEHICLE_TYPE_LIGHTMOTORCYCLE,           // "LightMotorcycle" 轻便摩托车
    CFG_CATEGORY_VEHICLE_TYPE_EMBASSYMOTORCYCLE,         // "EmbassyMotorcycle "使馆摩托车
    CFG_CATEGORY_VEHICLE_TYPE_MARGINALMOTORCYCLE,        // "MarginalMotorcycle "领馆摩托车
    CFG_CATEGORY_VEHICLE_TYPE_AREAOUTMOTORCYCLE,         // "AreaoutMotorcycle "境外摩托车
    CFG_CATEGORY_VEHICLE_TYPE_FOREIGNMOTORCYCLE,         // "ForeignMotorcycle "外籍摩托车
    CFG_CATEGORY_VEHICLE_TYPE_FARMTRANSMITCAR,           // "FarmTransmitCar" 农用运输车
    CFG_CATEGORY_VEHICLE_TYPE_TRACTOR,                   // "Tractor" 拖拉机
    CFG_CATEGORY_VEHICLE_TYPE_TRAILER,                   // "Trailer"  挂车
    CFG_CATEGORY_VEHICLE_TYPE_COACHCAR,                  // "CoachCar"教练汽车
    CFG_CATEGORY_VEHICLE_TYPE_COACHMOTORCYCLE,           // "CoachMotorcycle "教练摩托车
    CFG_CATEGORY_VEHICLE_TYPE_TRIALCAR,                  // "TrialCar" 试验汽车
    CFG_CATEGORY_VEHICLE_TYPE_TRIALMOTORCYCLE,           // "TrialMotorcycle "试验摩托车
    CFG_CATEGORY_VEHICLE_TYPE_TEMPORARYENTRYCAR,         // "TemporaryEntryCar"临时入境汽车
    CFG_CATEGORY_VEHICLE_TYPE_TEMPORARYENTRYMOTORCYCLE,  // "TemporaryEntryMotorcycle"临时入境摩托车
    CFG_CATEGORY_VEHICLE_TYPE_TEMPORARYSTEERCAR,         // "TemporarySteerCar"临时行驶车
    CFG_CATEGORY_VEHICLE_TYPE_PASSENGERCAR,              // "PassengerCar" 客车
    CFG_CATEGORY_VEHICLE_TYPE_LARGETRUCK,                // "LargeTruck" 大货车
    CFG_CATEGORY_VEHICLE_TYPE_MIDTRUCK,                  // "MidTruck" 中货车
    CFG_CATEGORY_VEHICLE_TYPE_SALOONCAR,                 // "SaloonCar" 轿车
    CFG_CATEGORY_VEHICLE_TYPE_MICROBUS,                  // "Microbus"面包车
    CFG_CATEGORY_VEHICLE_TYPE_MICROTRUCK,                // "MicroTruck"小货车
    CFG_CATEGORY_VEHICLE_TYPE_TRICYCLE,                  // "Tricycle"三轮车
    CFG_CATEGORY_VEHICLE_TYPE_PASSERBY,                  // "Passerby" 行人

    //车牌相关子类别
    CFG_CATEGORY_PLATE_TYPE_NORMAL,                      // "Normal" 蓝牌黑字
    CFG_CATEGORY_PLATE_TYPE_YELLOW,                      // "Yellow" 黄牌
    CFG_CATEGORY_PLATE_TYPE_DOUBLEYELLOW,                // "DoubleYellow" 双层黄尾牌
    CFG_CATEGORY_PLATE_TYPE_POLICE,                      // "Police" 警牌
    CFG_CATEGORY_PLATE_TYPE_ARMED,                       // "Armed" 武警牌
    CFG_CATEGORY_PLATE_TYPE_MILITARY,                    // "Military" 部队号牌
    CFG_CATEGORY_PLATE_TYPE_DOUBLEMILITARY,              // "DoubleMilitary" 部队双层
    CFG_CATEGORY_PLATE_TYPE_SAR,                         // "SAR" 港澳特区号牌    
    CFG_CATEGORY_PLATE_TYPE_TRAINNING,                   // "Trainning" 教练车号牌
    CFG_CATEGORY_PLATE_TYPE_PERSONAL,                    // "Personal" 个性号牌
    CFG_CATEGORY_PLATE_TYPE_AGRI,                        // "Agri" 农用牌
    CFG_CATEGORY_PLATE_TYPE_EMBASSY,                     // "Embassy" 使馆号牌
    CFG_CATEGORY_PLATE_TYPE_MOTO,                        // "Moto" 摩托车号牌
    CFG_CATEGORY_PLATE_TYPE_TRACTOR,                     // "Tractor" 拖拉机号牌
    CFG_CATEGORY_PLATE_TYPE_OFFICIALCAR,                 // "OfficialCar " 公务车
    CFG_CATEGORY_PLATE_TYPE_PERSONALCAR,                 // "PersonalCar" 私家车
    CFG_CATEGORY_PLATE_TYPE_WARCAR,                      // "WarCar"  军用
    CFG_CATEGORY_PLATE_TYPE_OTHER,                       // "Other" 其他号牌
    CFG_CATEGORY_PLATE_TYPE_CIVILAVIATION,               // "Civilaviation" 民航号牌
    CFG_CATEGORY_PLATE_TYPE_BLACK,                       // "Black" 黑牌
}CFG_CATEGORY_TYPE;

// 不同区域各种类型物体的检测模块配置
typedef struct tagCFG_MODULE_INFO
{
	// 信息
	char				szObjectType[MAX_NAME_LEN];				// 默认物体类型,详见"支持的检测物体类型列表"
	bool				bSnapShot;								// 是否对识别物体抓图
	BYTE                bSensitivity;                           // 灵敏度,取值1-10，值越小灵敏度越低
	bool                bMeasureModeEnable;                     // 计量方式参数是否有效
	BYTE                bMeasureMode;                           // 计量方式,0-像素，不需要远端、近端标定, 1-实际长度，单位：米, 2-远端近端标定后的像素
	int					nDetectRegionPoint;						// 检测区域顶点数
	CFG_POLYGON			stuDetectRegion[MAX_POLYGON_NUM];		// 检测区域
	int					nTrackRegionPoint;						// 跟踪区域顶点数
	CFG_POLYGON			stuTrackRegion[MAX_POLYGON_NUM];		// 跟踪区域
	bool                bFilterTypeEnable;                      // 过滤类型参数是否有效
	// ByArea,ByRatio仅作兼容，使用独立的ByArea和ByRatio选项代替 2012/03/06
	BYTE				nFilterType;							// 过滤类型:0:"ByLength",1:"ByArea", 2:"ByWidthHeight", 3:"ByRatio": 按照宽高比，宽度除以高度的结果小于某个值或者大于某个值的问题将被过滤掉。
	bool                bBackgroudEnable;                       // 区域的背景类型参数是否有效
	BYTE                bBackgroud;                             // 区域的背景类型, 0-普通类型, 1-高光类型
	bool                abBySize;                               // 长宽过滤使能参数是否有效
	bool                bBySize;                                // 长宽过滤使能
	bool                bFilterMinSizeEnable;                   // 物体最小尺寸参数是否有效
	bool                bFilterMaxSizeEnable;                   // 物体最大尺寸参数是否有效
	CFG_SIZE			stuFilterMinSize;						// 物体最小尺寸 "ByLength"模式下表示宽高的尺寸，"ByArea"模式下宽表示面积，高无效。
	CFG_SIZE			stuFilterMaxSize;						// 物体最大尺寸 "ByLength"模式下表示宽高的尺寸，"ByArea"模式下宽表示面积，高无效。
	int                 nExcludeRegionNum;                      // 排除区域数
	CFG_REGION          stuExcludeRegion[MAX_EXCLUDEREGION_NUM];// 排除区域
	int                 nCalibrateBoxNum;                       // 校准框个数
	CFG_CALIBRATEBOX_INFO stuCalibrateBoxs[MAX_CALIBRATEBOX_NUM];// 校准框(远端近端标定模式下有效)
	bool                bAccuracy;                               // 检测精度是否有效
	BYTE                byAccuracy;                              // 检测精度
	bool                bMovingStep;                             // 算法移动步长是否有效                        
	BYTE                byMovingStep;                            // 算法移动步长
	bool                bScalingFactor;							 // 算法缩放因子是否有效
	BYTE                byScalingFactor;						 // 算法缩放因子

	BYTE                bReserved2[1];                           // 保留字段
	bool                abDetectBalance;						 // 漏检和误检平衡参数是否有效
	int					nDetectBalance;							 // 漏检和误检平衡	0-折中模式(默认)1-漏检更少2-误检更少
	
	bool                abByRatio;
	bool                abMinRatio;
	bool                abMaxRatio;
	bool                abMinAreaSize;
	bool                abMaxAreaSize;
	bool                bByRatio;                                // 是否按宽高比过滤 通过能力ComplexSizeFilter判断是否可用 可以和nFilterType复用
	bool                bReserved1[2];
	double              dMinRatio;                               // 最小宽高比
	double              dMaxRatio;                               // 最大宽高比
	CFG_SIZE            stuMinAreaSize;                           // 最小面积矩形框尺寸 "计量方式"为"像素"时，表示最小面积矩形框的宽高尺寸；"计量方式"为"远端近端标定模式"时，表示基准框的最小宽高尺寸；
	CFG_SIZE            stuMaxAreaSize;                           // 最大面积矩形框尺寸, 同上
	
	bool                abByArea;
	bool                abMinArea;
	bool                abMaxArea;
	bool                abMinRatioSize;
	bool                abMaxRatioSize;
	bool                bByArea;                                 // 是否按面积过滤 通过能力ComplexSizeFilter判断是否可用  可以和nFilterType复用
	bool                bReserved3[2];
	float               nMinArea;                                // 最小面积
	float               nMaxArea;                                // 最大面积
	CFG_SIZE            stuMinRatioSize;                          // 最小宽高比矩形框尺寸，最小宽高比对应矩形框的宽高尺寸。
	CFG_SIZE            stuMaxRatioSize;                          // 最大宽高比矩形框尺寸，同上
	
	int                 nAreaCalibrateBoxNum;                    // 面积校准框个数
	CFG_CALIBRATEBOX_INFO stuAreaCalibrateBoxs[MAX_CALIBRATEBOX_NUM];// 面积校准框
	int                 nRatioCalibrateBoxs;                      // 比例校准框个数
	CFG_CALIBRATEBOX_INFO stuRatioCalibrateBoxs[MAX_CALIBRATEBOX_NUM];// 比例校准框个数

	bool                bAntiDisturbance;                        // 是否开启去扰动模块
	bool                bBacklight;                              // 是否有逆光
	bool                bShadow;                                 // 是否有阴影
	bool                bContourAssistantTrack;                  // 是否开启轮廓辅助跟踪，例：在人脸识别时可以通过跟踪人体来辅助识别人脸
	int                 nPtzPresetId;                            // 云台预置点，0~255，0表示固定场景，忽略预置点。大于0表示在此预置点时模块有效

	int                 nObjectFilterNum;                        // 物体特定的过滤器个数
	CFG_OBJECT_SIZEFILTER_INFO stObjectFilter[MAX_OBJECT_LIST_SIZE]; // 物体特定的过滤器信息

	BOOL                abObjectImageSize;                        
	CFG_SIZE            stObjectImageSize;                       // 保证物体图像尺寸相同,单位是像素,不支持小数，取值：>=0,  0 表示自动调整大小

	int                 nSpecailDetectNum;                                // 特殊检测区域个数
	CFG_SPECIALDETECT_INFO stSpecialDetectRegions[MAX_SPECIALDETECT_NUM];  // 特殊检测区信息

	unsigned int        nAttribute;                              // 需要识别物体的属性个数
	char                szAttributes[MAX_OBJECT_ATTRIBUTES_SIZE][MAX_NAME_LEN];   // 需要识别物体的属性列表，“Category” 物体子类；“Size” 物体大小；“Color” 物体颜色；“Speed” 物体速度；“Sign” 物体标志，对车辆而言，指车标；“Action” 物体动作
	
	BOOL                abPlateAnalyseMode;                      // nPlateAnalyseMode是否有效
	int                 nPlateAnalyseMode;                       // 车牌识别模式，0-只识别车头牌照 1-只识别车尾牌照 2-车头牌照优先（场景中大部分车均是车头牌照）3-车尾牌照优先（场景中大部分车均是车尾牌照）

    //szAttributes属性存在"Category"时生效
    unsigned int        nCategoryNum;                            // 需要识别物体的子类型总数
    CFG_CATEGORY_TYPE   emCategoryType[MAX_CATEGORY_TYPE_NUMBER]; // 子类型信息

} CFG_MODULE_INFO;

typedef struct tagCFG_ANALYSEMODULES_INFO
{
	int					nMoudlesNum;							// 检测模块数
	CFG_MODULE_INFO     stuModuleInfo[MAX_ANALYSE_MODULE_NUM];			// 每个视频输入通道对应的各种类型物体的检测模块配置

} CFG_ANALYSEMODULES_INFO;

// 视频分析事件规则配置相关结构体定义
enum CFG_EM_DETECTMODE_T{
	CFG_EM_DETECTMODE_NONE,            // 无此字段
	CFG_EM_DETECTMODE_BY_VIDEO,        // 视频检测模式
	CFG_EM_DETECTMODE_BY_BYAUDIO,      // 音频检测模式
	CFG_EM_DETECTMODE_BY_BOTH,         // 音视频联合检测模式
	CFG_EM_DETECTMODE_ERR=255          // 字段数据错误
};

// 视频分析事件规则配置
// 事件类型EVENT_IVS_CROSSLINEDETECTION(警戒线事件)对应的规则配置
typedef struct tagCFG_CROSSLINE_INFO
{
	// 信息
	char				szRuleName[MAX_NAME_LEN];								// 规则名称,不同规则不能重名
	bool				bRuleEnable;											// 规则使能
	BYTE                bReserved[3];                                           // 保留字段 
	int					nObjectTypeNum;											// 相应物体类型个数
	char				szObjectTypes[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];		// 相应物体类型列表
	int					nDirection;												// 检测方向:0:由左至右;1:由右至左;2:两者都可以
	int					nDetectLinePoint;										// 警戒线顶点数
	CFG_POLYLINE		stuDetectLine[MAX_POLYLINE_NUM];						// 警戒线
	CFG_ALARM_MSG_HANDLE stuEventHandler;										// 报警联动
	
	CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT_EX];			// 事件响应时间段
 	BOOL                bDisableTimeSection;                                    // stuTimeSection字段是否禁用，默认FALSE：不禁用，TRUE：禁用，用户控制

	int                 nPtzPresetId;											// 云台预置点编号	0~65535
	BOOL                bSizeFileter;                                           // 规则特定的尺寸过滤器是否有效
	CFG_SIZEFILTER_INFO stuSizeFileter;                                         // 规则特定的尺寸过滤器
	int                 nTriggerPosition;                                       // 触发报警位置数
	BYTE                bTriggerPosition[8];                                    // 触发报警位置,0-目标外接框中心, 1-目标外接框左端中心, 2-目标外接框顶端中心, 3-目标外接框右端中心, 4-目标外接框底端中心

} CFG_CROSSLINE_INFO;

//事件类型EVENT_IVS_CROSSFENCEDETECTION(翻越围栏规则)对应的规则配置
typedef struct tagCFG_CROSSFENCEDETECTION_INFO
{
	// 信息
	char				szRuleName[MAX_NAME_LEN];								// 规则名称,不同规则不能重名
	bool				bRuleEnable;											// 规则使能
	BYTE                bReserved[3];                                           // 保留字段 
	int					nObjectTypeNum;											// 相应物体类型个数
	char				szObjectTypes[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];		// 相应物体类型列表
	int                 nPtzPresetId;											// 云台预置点编号	0~65535
	int					nDirection;												// 翻越围栏方向:0:由左至右;1:由右至左;2:两者都可以
	int					nUpstairsLinePointNumber;								// 围栏上线顶点数
	CFG_POLYLINE		stuUpstairsLine[MAX_POLYLINE_NUM];						// 围栏上线
	int					nDownstairsLinePointNumber;								// 围栏下线顶点数
	CFG_POLYLINE		stuDownstairsLine[MAX_POLYLINE_NUM];					// 围栏下线
	BOOL                bSizeFileter;                                           // 规则特定的尺寸过滤器是否有效
	CFG_SIZEFILTER_INFO stuSizeFileter;                                         // 规则特定的尺寸过滤器
	int                 nTriggerPosition;                                       // 触发报警位置数
	BYTE                bTriggerPosition[8];                                    // 触发报警位置,0-目标外接框中心, 1-目标外接框左端中心, 2-目标外接框顶端中心, 3-目标外接框右端中心, 4-目标外接框底端中心
	CFG_ALARM_MSG_HANDLE stuEventHandler;										// 报警联动
	CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT_EX];			// 事件响应时间段
	
} CFG_CROSSFENCEDETECTION_INFO;

// 事件类型EVENT_IVS_CROSSREGIONDETECTION(警戒区事件)对应的规则配置
typedef struct tagCFG_CROSSREGION_INFO
{
	// 信息
	char				szRuleName[MAX_NAME_LEN];								// 规则名称,不同规则不能重名
	bool				bRuleEnable;											// 规则使能
	BYTE                bReserved[3];                                           // 保留字段
	int					nObjectTypeNum;											// 相应物体类型个数
	char				szObjectTypes[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];		// 相应物体类型列表
	int					nDirection;												// 检测方向:0:Enter;1:Leave;2:Both
	int					nDetectRegionPoint;										// 警戒区顶点数
	CFG_POLYGON			stuDetectRegion[MAX_POLYGON_NUM];						// 警戒区
	CFG_ALARM_MSG_HANDLE stuEventHandler;										// 报警联动

	CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT_EX];			// 事件响应时间段
 	BOOL                bDisableTimeSection;                                    // stuTimeSection字段是否禁用，默认FALSE：不禁用，TRUE：禁用，用户控制

	int                 nPtzPresetId;											// 云台预置点编号	0~65535
	BOOL                bSizeFileter;                                           // 规则特定的尺寸过滤器是否有效
	CFG_SIZEFILTER_INFO stuSizeFileter;                                         // 规则特定的尺寸过滤器
	int                 nActionType;                                            // 检测动作数
	BYTE                bActionType[4];                                         // 检测动作列表,0-出现 1-消失 2-在区域内 3-穿越区域
	int                 nMinTargets;                                            // 最小目标个数(当bActionType中包含"2-在区域内"时有效)
	int                 nMaxTargets;                                            // 最大目标个数(当bActionType中包含"2-在区域内"时有效)
	int                 nMinDuration;                                           // 最短持续时间， 单位秒(当bActionType中包含"2-在区域内"时有效)
	int                 nReportInterval;                                        // 报告时间间隔， 单位秒(当bActionType中包含"2-在区域内"时有效)
		
} CFG_CROSSREGION_INFO;

// 事件类型EVENT_IVS_PASTEDETECTION(ATM贴条事件)对应的规则配置
typedef struct tagCFG_PASTE_INFO
{
	// 信息
	char				szRuleName[MAX_NAME_LEN];								// 规则名称,不同规则不能重名
	bool				bRuleEnable;											// 规则使能
	BYTE                bReserved[3];                                           // 保留字段
	int					nObjectTypeNum;											// 相应物体类型个数
	char				szObjectTypes[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];		// 相应物体类型列表
	int					nMinDuration;											// 最短持续时间	单位：秒，0~65535
	int					nDetectRegionPoint;										// 检测区域顶点数
	CFG_POLYGON			stuDetectRegion[MAX_POLYGON_NUM];						// 检测区域
	CFG_ALARM_MSG_HANDLE stuEventHandler;										// 报警联动
	CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT_EX];			// 事件响应时间段
	int                 nPtzPresetId;											// 云台预置点编号	0~65535
		
} CFG_PASTE_INFO;

// 事件类型EVENT_IVS_LEFTDETECTION(物品遗留事件)对应的规则配置
typedef struct tagCFG_LEFT_INFO 
{
	// 信息
	char				szRuleName[MAX_NAME_LEN];								// 规则名称,不同规则不能重名
	bool				bRuleEnable;											// 规则使能
	BYTE                bReserved[3];                                           // 保留字段
	int					nObjectTypeNum;											// 相应物体类型个数
	char				szObjectTypes[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];		// 相应物体类型列表
	int					nMinDuration;											// 最短持续时间	单位：秒，0~65535
	int					nDetectRegionPoint;										// 检测区域顶点数
	CFG_POLYGON			stuDetectRegion[MAX_POLYGON_NUM];						// 检测区域
	CFG_ALARM_MSG_HANDLE stuEventHandler;										// 报警联动
	CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT_EX];			// 事件响应时间段
	int                 nPtzPresetId;											// 云台预置点编号	0~65535
	int                 nTriggerPosition;                                       // 触发报警位置数
	BYTE                bTriggerPosition[8];                                    // 触发报警位置,0-目标外接框中心, 1-目标外接框左端中心, 2-目标外接框顶端中心, 3-目标外接框右端中心, 4-目标外接框底端中心
	BOOL                bSizeFileter;                                           // 规则特定的尺寸过滤器是否有效
	CFG_SIZEFILTER_INFO stuSizeFileter;                                         // 规则特定的尺寸过滤器

} CFG_LEFT_INFO;

// 事件类型EVENT_IVS_TAKENAWAYDETECTION(物品搬移规则配置)对应的规则配置
typedef struct tagCFG_TAKENAWAYDETECTION_INFO 
{
	// 信息
	char				szRuleName[MAX_NAME_LEN];								// 规则名称,不同规则不能重名
	bool				bRuleEnable;											// 规则使能
	BYTE                bReserved[3];                                           // 保留字段
	int					nObjectTypeNum;											// 相应物体类型个数
	char				szObjectTypes[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];		// 相应物体类型列表
	int					nMinDuration;											// 最短持续时间	单位：秒，0~65535
	int					nDetectRegionPoint;										// 检测区域顶点数
	CFG_POLYGON			stuDetectRegion[MAX_POLYGON_NUM];						// 检测区域
	CFG_ALARM_MSG_HANDLE stuEventHandler;										// 报警联动
	CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT_EX];			// 事件响应时间段
	int                 nPtzPresetId;											// 云台预置点编号	0~65535
	int                 nTriggerPosition;                                       // 触发报警位置数
	BYTE                bTriggerPosition[8];                                    // 触发报警位置,0-目标外接框中心, 1-目标外接框左端中心, 2-目标外接框顶端中心, 3-目标外接框右端中心, 4-目标外接框底端中心
	BOOL                bSizeFileter;                                           // 规则特定的尺寸过滤器是否有效
	CFG_SIZEFILTER_INFO stuSizeFileter;                                         // 规则特定的尺寸过滤器

} CFG_TAKENAWAYDETECTION_INFO;

// 事件类型EVENT_IVS_PARKINGDETECTION (非法停车)对应的规则配置
typedef struct tagCFG_PARKINGDETECTION_INFO 
{
	// 信息
	char				szRuleName[MAX_NAME_LEN];								// 规则名称,不同规则不能重名
	bool				bRuleEnable;											// 规则使能
	BYTE                bReserved[3];                                           // 保留字段
	int					nObjectTypeNum;											// 相应物体类型个数
	char				szObjectTypes[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];		// 相应物体类型列表
	int					nMinDuration;											// 最短持续时间	单位：秒，0~65535
	int					nDetectRegionPoint;										// 检测区域顶点数
	CFG_POLYGON			stuDetectRegion[MAX_POLYGON_NUM];						// 检测区域
	CFG_ALARM_MSG_HANDLE stuEventHandler;										// 报警联动
	CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT_EX];			// 事件响应时间段
	int                 nPtzPresetId;											// 云台预置点编号	0~65535
	int                 nTriggerPosition;                                       // 触发报警位置数
	BYTE                bTriggerPosition[8];                                    // 触发报警位置,0-目标外接框中心, 1-目标外接框左端中心, 2-目标外接框顶端中心, 3-目标外接框右端中心, 4-目标外接框底端中心
	BOOL                bSizeFileter;                                           // 规则特定的尺寸过滤器是否有效
	CFG_SIZEFILTER_INFO stuSizeFileter;                                         // 规则特定的尺寸过滤器

} CFG_PARKINGDETECTION_INFO;

// 事件类型EVENT_IVS_PRESERVATION(物品保全事件)对应的规则配置
typedef struct tagCFG_PRESERVATION_INFO 
{
	// 信息
	char				szRuleName[MAX_NAME_LEN];								// 规则名称,不同规则不能重名
	bool				bRuleEnable;											// 规则使能
	BYTE                bReserved[3];                                           // 保留字段
	int					nObjectTypeNum;											// 相应物体类型个数
	char				szObjectTypes[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];		// 相应物体类型列表
	int					nMinDuration;											// 最短持续时间	单位：秒，0~65535
	int					nDetectRegionPoint;										// 检测区域顶点数
	CFG_POLYGON			stuDetectRegion[MAX_POLYGON_NUM];						// 检测区域
	CFG_ALARM_MSG_HANDLE stuEventHandler;										// 报警联动
	CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT_EX];			// 事件响应时间段
	int                 nPtzPresetId;											// 云台预置点编号	0~65535

} CFG_PRESERVATION_INFO;

// 事件类型EVENT_IVS_STAYDETECTION(停留事件/滞留)对应的规则配置
typedef struct tagCFG_STAY_INFO 
{
	// 信息
	char				szRuleName[MAX_NAME_LEN];								// 规则名称,不同规则不能重名
	bool				bRuleEnable;											// 规则使能
	BYTE                bReserved[3];                                           // 保留字段
	int					nObjectTypeNum;											// 相应物体类型个数
	char				szObjectTypes[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];		// 相应物体类型列表
	int					nMinDuration;											// 最短持续时间	单位：秒，0~65535
	int					nDetectRegionPoint;										// 检测区域顶点数
	CFG_POLYGON			stuDetectRegion[MAX_POLYGON_NUM];						// 检测区域
	CFG_ALARM_MSG_HANDLE stuEventHandler;										// 报警联动
	CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT_EX];			// 事件响应时间段
	int                 nPtzPresetId;											// 云台预置点编号	0~65535
	int                 nTriggerPosition;                                       // 触发报警位置数
	BYTE                bTriggerPosition[8];                                    // 触发报警位置,0-目标外接框中心, 1-目标外接框左端中心, 2-目标外接框顶端中心, 3-目标外接框右端中心, 4-目标外接框底端中心
	int                 nTriggerTargetsNumber;                                  // 触发报警的徘徊或滞留人数
	int                 nReportInterval;                                        // 报告时间间隔,单位秒
	BOOL                bSizeFileter;                                           // 规则特定的尺寸过滤器是否有效
	CFG_SIZEFILTER_INFO stuSizeFileter;                                         // 规则特定的尺寸过滤器
	
} CFG_STAY_INFO;

// 事件类型EVENT_IVS_WANDERDETECTION(徘徊事件)对应的规则配置
typedef struct tagCFG_WANDER_INFO 
{
	// 信息
	char				szRuleName[MAX_NAME_LEN];								// 规则名称,不同规则不能重名
	bool				bRuleEnable;											// 规则使能
	BYTE                bReserved[3];                                           // 保留字段
	int					nObjectTypeNum;											// 相应物体类型个数
	char				szObjectTypes[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];		// 相应物体类型列表
	int					nMinDuration;											// 最短持续时间	单位：秒，0~65535
	int					nDetectRegionPoint;										// 检测区域顶点数
	CFG_POLYGON			stuDetectRegion[MAX_POLYGON_NUM];						// 检测区域
	CFG_ALARM_MSG_HANDLE stuEventHandler;										// 报警联动
	CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT_EX];			// 事件响应时间段
	int                 nPtzPresetId;											// 云台预置点编号	0~65535
	int                 nTriggerPosition;                                       // 触发报警位置数
	BYTE                bTriggerPosition[8];                                    // 触发报警位置,0-目标外接框中心, 1-目标外接框左端中心, 2-目标外接框顶端中心, 3-目标外接框右端中心, 4-目标外接框底端中心
	int                 nTriggerTargetsNumber;                                  // 触发报警的徘徊或滞留人数
	int                 nReportInterval;                                        // 报告时间间隔,单位秒
	BOOL                bSizeFileter;                                           // 规则特定的尺寸过滤器是否有效
	CFG_SIZEFILTER_INFO stuSizeFileter;                                         // 规则特定的尺寸过滤器

} CFG_WANDER_INFO;

// 事件类型EVENT_IVS_MOVEDETECTION(移动事件/运动检测)对应的规则配置
typedef struct tagCFG_MOVE_INFO 
{
	// 信息
	char				szRuleName[MAX_NAME_LEN];								// 规则名称,不同规则不能重名
	bool				bRuleEnable;											// 规则使能
	BYTE                bSensitivity;                                           // 灵敏度，取值1-10，值越小灵敏度越低
	BYTE                bReserved[2];                                           // 保留字段
	int					nObjectTypeNum;											// 相应物体类型个数
	char				szObjectTypes[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];		// 相应物体类型列表
	int					nMinDuration;											// 最短持续时间	单位：秒，0~65535
	int					nDetectRegionPoint;										// 检测区域顶点数
	CFG_POLYGON			stuDetectRegion[MAX_POLYGON_NUM];						// 检测区域
	CFG_ALARM_MSG_HANDLE stuEventHandler;										// 报警联动
	CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT_EX];			// 事件响应时间段
	int                 nPtzPresetId;											// 云台预置点编号	0~65535
	int                 nTriggerSpeed;                                          // 触发速度，km/h
	int                 nTriggerPosition;                                       // 触发报警位置数
	BYTE                bTriggerPosition[8];                                    // 触发报警位置,0-目标外接框中心, 1-目标外接框左端中心, 2-目标外接框顶端中心, 3-目标外接框右端中心, 4-目标外接框底端中心
	BOOL                bSizeFileter;                                           // 规则特定的尺寸过滤器是否有效
	CFG_SIZEFILTER_INFO stuSizeFileter;                                         // 规则特定的尺寸过滤器	
	int                 nTypeNumber;                                            // 检测类型数
	BYTE                bDetectType[4];                                         // 检测动作列表,0-快速运动 1-突然加速 2-突然减速

} CFG_MOVE_INFO;

// 事件类型EVENT_IVS_TAILDETECTION(尾随事件)对应的规则配置
typedef struct tagCFG_TAIL_INFO 
{
	// 信息
	char				szRuleName[MAX_NAME_LEN];								// 规则名称,不同规则不能重名
	bool				bRuleEnable;											// 规则使能
	BYTE                bReserved[3];                                           // 保留字段
	int					nObjectTypeNum;											// 相应物体类型个数
	char				szObjectTypes[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];		// 相应物体类型列表
	int					nMinDuration;											// 最短持续时间	单位：秒，0~65535
	int					nDetectRegionPoint;										// 检测区域顶点数
	CFG_POLYGON			stuDetectRegion[MAX_POLYGON_NUM];						// 检测区域
	CFG_ALARM_MSG_HANDLE stuEventHandler;										// 报警联动
	CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT_EX];			// 事件响应时间段
	int                 nPtzPresetId;											// 云台预置点编号	0~65535

} CFG_TAIL_INFO;

// 事件类型EVENT_IVS_RIOTERDETECTION(聚众事件)对应的规则配置
typedef struct tagCFG_RIOTER_INFO 
{
	// 信息
	char				szRuleName[MAX_NAME_LEN];								// 规则名称,不同规则不能重名
	bool				bRuleEnable;											// 规则使能
	BYTE                bAreaPercent;                                           // 聚集所占区域面积百分比
	BYTE                bSensitivity;                                           // 灵敏度，取值1-10，值越小灵敏度越低，对应人群的密集程度越高(取代bAreaPercent)
	BYTE                bReserved;												// 保留字段
	int					nObjectTypeNum;											// 相应物体类型个数
	char				szObjectTypes[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];		// 相应物体类型列表
	int					nMinDuration;											// 最短持续时间	单位：秒，0~65535
	int					nDetectRegionPoint;										// 检测区域顶点数
	CFG_POLYGON			stuDetectRegion[MAX_POLYGON_NUM];						// 检测区域
	CFG_ALARM_MSG_HANDLE stuEventHandler;										// 报警联动
	CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT_EX];			// 事件响应时间段
	int                 nPtzPresetId;											// 云台预置点编号	0~65535

	int                 nReportInterval;                                        // 报告时间间隔,单位秒 [1,600] 默认0表示不重复报警
	CFG_POLYGON         stuMinDetectRect[2];                                    // 最小聚集区域矩形框，分别对应矩形框的左上和右下点，矩形框的实际面积表示触发报警的最小人群聚集面积
} CFG_RIOTER_INFO;

// 事件类型EVENT_IVS_DENSITYDETECTION(人群密度检测事件)对应的规则配置
typedef struct tagCFG_DENSITYDETECTION_INFO 
{
	// 信息
	char				szRuleName[MAX_NAME_LEN];								// 规则名称,不同规则不能重名
	bool				bRuleEnable;											// 规则使能
	BYTE                bReserved1;                                             // 保留字段
	BYTE                bSensitivity;                                           // 灵敏度(取值1-10，值越小灵敏度越低，对应人群的密集程度越高)
	BYTE                bReserved2;                                             // 保留字段
	int					nObjectTypeNum;											// 相应物体类型个数
	char				szObjectTypes[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];		// 相应物体类型列表
	int					nMinDuration;											// 最短持续时间	单位：秒，0~65535
	int					nDetectRegionPoint;										// 检测区域顶点数
	CFG_POLYGON			stuDetectRegion[MAX_POLYGON_NUM];						// 检测区域
	CFG_ALARM_MSG_HANDLE stuEventHandler;										// 报警联动
	CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT_EX];			// 事件响应时间段
	int                 nPtzPresetId;											// 云台预置点编号	0~65535
	
} CFG_DENSITYDETECTION_INFO;


// 事件类型EVENT_IVS_FIGHTDETECTION(斗殴事件)对应的规则配置
typedef struct tagCFG_FIGHT_INFO 
{
	// 信息
	char				szRuleName[MAX_NAME_LEN];								// 规则名称,不同规则不能重名
	bool				bRuleEnable;											// 规则使能
	BYTE                bReserved[3];                                           // 保留字段
	int					nObjectTypeNum;											// 相应物体类型个数
	char				szObjectTypes[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];		// 相应物体类型列表
	int					nMinDuration;											// 最短持续时间	单位：秒，0~65535
	int					nDetectRegionPoint;										// 检测区域顶点数
	CFG_POLYGON			stuDetectRegion[MAX_POLYGON_NUM];						// 检测区域
	CFG_ALARM_MSG_HANDLE stuEventHandler;										// 报警联动
	CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT_EX];			// 事件响应时间段
	int                 nPtzPresetId;											// 云台预置点编号	0~65535
	int					nSensitivity;											// 灵敏度, 1-10
    CFG_EM_DETECTMODE_T emDetectMode;                                           // 检测模式

} CFG_FIGHT_INFO;

// 事件类型EVENT_IVS_FIREDETECTION(火警事件/火焰检测)对应的规则配置
typedef struct tagCFG_FIRE_INFO 
{
	// 信息
	char				szRuleName[MAX_NAME_LEN];								// 规则名称,不同规则不能重名
	bool				bRuleEnable;											// 规则使能
	BYTE                bReserved[3];                                           // 保留字段
	int					nObjectTypeNum;											// 相应物体类型个数
	char				szObjectTypes[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];		// 相应物体类型列表
	int					nMinDuration;											// 最短持续时间	单位：秒，0~65535
	int					nDetectRegionPoint;										// 检测区域顶点数
	CFG_POLYGON			stuDetectRegion[MAX_POLYGON_NUM];						// 检测区域
	CFG_ALARM_MSG_HANDLE stuEventHandler;										// 报警联动
	CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT_EX];			// 事件响应时间段
	int                 nPtzPresetId;											// 云台预置点编号	0~65535
	int					nSensitivity;											// 灵敏度 1~10
} CFG_FIRE_INFO;

// 事件类型EVENT_IVS_ELECTROSPARKDETECTION(电火花事件)对应的规则配置
typedef struct tagCFG_ELECTROSPARK_INFO 
{
	// 信息
	char				szRuleName[MAX_NAME_LEN];								// 规则名称,不同规则不能重名
	bool				bRuleEnable;											// 规则使能
	BYTE                bReserved[3];                                           // 保留字段
	int					nObjectTypeNum;											// 相应物体类型个数
	char				szObjectTypes[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];		// 相应物体类型列表
	int					nMinDuration;											// 最短持续时间	单位：秒，0~65535
	int					nDetectRegionPoint;										// 检测区域顶点数
	CFG_POLYGON			stuDetectRegion[MAX_POLYGON_NUM];						// 检测区域
	CFG_ALARM_MSG_HANDLE stuEventHandler;										// 报警联动
	CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT_EX];			// 事件响应时间段
	int                 nPtzPresetId;											// 云台预置点编号	0~65535
	
} CFG_ELECTROSPARK_INFO;

// 事件类型EVENT_IVS_SMOKEDETECTION(烟雾报警事件)对应的规则配置
typedef struct tagCFG_SMOKE_INFO 
{
	// 信息
	char				szRuleName[MAX_NAME_LEN];								// 规则名称,不同规则不能重名
	bool				bRuleEnable;											// 规则使能
	BYTE                bReserved[3];                                           // 保留字段
	int					nObjectTypeNum;											// 相应物体类型个数
	char				szObjectTypes[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];		// 相应物体类型列表
	int					nMinDuration;											// 最短持续时间	单位：秒，0~65535
	int					nDetectRegionPoint;										// 检测区域顶点数
	CFG_POLYGON			stuDetectRegion[MAX_POLYGON_NUM];						// 检测区域
	CFG_ALARM_MSG_HANDLE stuEventHandler;										// 报警联动
	CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT_EX];			// 事件响应时间段
	int                 nPtzPresetId;											// 云台预置点编号	0~65535
	int					nSensitivity;											// 灵敏度 1~10
} CFG_SMOKE_INFO;

// 事件类型EVENT_IVS_FLOWSTAT(流量统计事件)对应的规则配置
typedef struct tagCFG_FLOWSTAT_INFO
{
	// 信息
	char				szRuleName[MAX_NAME_LEN];								// 规则名称,不同规则不能重名
	bool				bRuleEnable;											// 规则使能
	BYTE                bReserved[3];                                           // 保留字段
	int					nObjectTypeNum;											// 相应物体类型个数
	char				szObjectTypes[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];		// 相应物体类型列表
	int					nUpperLimit;											// 流量上限	单位：个/秒，1~65535
	int					nPeriod;												// 上报周期	单位：秒，1~65535
	int					nDetectLinePoint;										// 检测线顶点数
	CFG_POLYLINE		stuDetectLine[MAX_POLYLINE_NUM];						// 检测线
	CFG_ALARM_MSG_HANDLE stuEventHandler;										// 报警联动
	CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT_EX];			// 事件响应时间段
	int                 nPtzPresetId;											// 云台预置点编号	0~65535
		
} CFG_FLOWSTAT_INFO;

enum NET_NUMBERSTAT_TYPE
{
	NET_EM_NUMSTAT_TYPE_REGION,                  // "Region" 区域类型
		NET_EM_NUMSTAT_TYPE_ENTRANCE,            // "Entrance" 出入口类型
		NET_EM_NUMSTAT_TYPE_OTHER,               // other
};
// 事件类型EVENT_IVS_NUMBERSTAT(数量统计事件)对应的规则配置
typedef struct tagCFG_NUMBERSTAT_INFO
{
	// 信息
	char				szRuleName[MAX_NAME_LEN];								// 规则名称,不同规则不能重名
	bool				bRuleEnable;											// 规则使能
	BYTE                bReserved[3];                                           // 保留字段
	int					nObjectTypeNum;											// 相应物体类型个数
	char				szObjectTypes[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];		// 相应物体类型列表
	int					nUpperLimit;											// 数量上限 单位：个，1~65535
	int					nPeriod;												// 上报周期	单位：秒，1~65535
	int					nDetectRegionPoint;										// 检测区顶点数
	CFG_POLYGON			stuDetectRegion[MAX_POLYGON_NUM];						// 检测区
	CFG_ALARM_MSG_HANDLE stuEventHandler;										// 报警联动
	CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT_EX];			// 事件响应时间段
	int                 nPtzPresetId;											// 云台预置点编号	0~65535
	NET_NUMBERSTAT_TYPE emType;                                                 // 数量统计类型	支持："Region" 区域类型 "Entrance" 出入口类型
	CFG_POLYGON         stDirection[2];                                         // 正常运动方向, 按照此方向行驶是正向，反过来是逆行	只对出入口类型有效。第一个点是起点，第二个点是终点，点的坐标归一化到[0,8191]区间。
    int                 nRecordInterval;                                        // 记录周期，单位：分钟，1~10
} CFG_NUMBERSTAT_INFO;

//事件类型EVENT_IVS_RETROGRADEDETECTION(人员逆行事件)对应的规则配置
typedef struct tagCFG_RETROGRADEDETECTION_INFO
{
	// 信息
	char				szRuleName[MAX_NAME_LEN];								// 规则名称,不同规则不能重名
	bool				bRuleEnable;											// 规则使能
	BYTE                bSensitivity;                                           // 灵敏度, 取值1-10，值越小灵敏度越低
	BYTE                bReserved[2];                                           // 保留字段 
	int					nObjectTypeNum;											// 相应物体类型个数
	char				szObjectTypes[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];		// 相应物体类型列表
	int                 nPtzPresetId;											// 云台预置点编号	0~65535
	int					nDetectRegionPoint;										// 检测区域顶点数
	CFG_POLYGON			stuDetectRegion[MAX_POLYGON_NUM];						// 检测区域
	int                 nDirectionPoint;                                        // 正常行驶方向顶点数
	CFG_POLYGON			stuDirection[MAX_POLYLINE_NUM];					      	// 正常行驶方向, 按照此方向行驶是正向，反过来是逆行(第一个点是起点，第二个点是终点，点的坐标归一化到[0,8191]区间)
	BOOL                bSizeFileter;                                           // 规则特定的尺寸过滤器是否有效
	CFG_SIZEFILTER_INFO stuSizeFileter;                                         // 规则特定的尺寸过滤器
	int                 nTriggerPosition;                                       // 触发报警位置数
	BYTE                bTriggerPosition[8];                                    // 触发报警位置,0-目标外接框中心, 1-目标外接框左端中心, 2-目标外接框顶端中心, 3-目标外接框右端中心, 4-目标外接框底端中心
	CFG_ALARM_MSG_HANDLE stuEventHandler;										// 报警联动
	CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT_EX];			// 事件响应时间段
	
} CFG_RETROGRADEDETECTION_INFO;

//事件类型EVENT_IVS_ABNORMALRUNDETECTION(异常奔跑事件)对应的规则配置
typedef struct tagCFG_ABNORMALRUNDETECTION_INFO
{
	// 信息
	char				szRuleName[MAX_NAME_LEN];								// 规则名称,不同规则不能重名
	bool				bRuleEnable;											// 规则使能
	BYTE                bSensitivity;                                           // 灵敏度, 取值1-10，值越小灵敏度越低
	BYTE                bReserved[2];                                           // 保留字段 
	int					nObjectTypeNum;											// 相应物体类型个数
	char				szObjectTypes[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];		// 相应物体类型列表
	int                 nPtzPresetId;											// 云台预置点编号	0~65535
	int					nDetectRegionPoint;										// 检测区域顶点数
	CFG_POLYGON			stuDetectRegion[MAX_POLYGON_NUM];						// 检测区域
	BOOL                bSizeFileter;                                           // 规则特定的尺寸过滤器是否有效
	CFG_SIZEFILTER_INFO stuSizeFileter;                                         // 规则特定的尺寸过滤器
	int                 nTriggerPosition;                                       // 触发报警位置数
	BYTE                bTriggerPosition[8];                                    // 触发报警位置,0-目标外接框中心, 1-目标外接框左端中心, 2-目标外接框顶端中心, 3-目标外接框右端中心, 4-目标外接框底端中心
	int                 nDetectType;                                            // 检测类型数
	BYTE                bDetectType[4];                                         // 检测类型,0-快速奔跑, 1-突然加速, 2-突然减速
	int                 nTriggerSpeed;                                          // 触发速度，大于该速度报警	单位：km/h
	int                 nMinDuration;                                           // 最短持续时间	单位：秒，0~65535
	CFG_ALARM_MSG_HANDLE stuEventHandler;										// 报警联动
	CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT_EX];			// 事件响应时间段
	
} CFG_ABNORMALRUNDETECTION_INFO;

//事件类型EVENT_IVS_VIDEOABNORMALDETECTION(视频异常)对应的规则配置
typedef struct tagCFG_VIDEOABNORMALDETECTION_INFO
{
	// 信息
	char				szRuleName[MAX_NAME_LEN];								// 规则名称,不同规则不能重名
	bool				bRuleEnable;											// 规则使能
	BYTE                bSensitivity;                                           // 灵敏度, 取值1-10，值越小灵敏度越低(只对检测类型视频遮挡，过亮，过暗，场景变化有效)
	BYTE                bReserved[2];                                           // 保留字段 
	int					nObjectTypeNum;											// 相应物体类型个数
	char				szObjectTypes[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];		// 相应物体类型列表
	int                 nPtzPresetId;											// 云台预置点编号	0~65535
	int                 nDetectType;                                            // 检测类型数
	BYTE                bDetectType[MAX_ABNORMAL_DETECT_TYPE];                  // 检测类型,0-视频丢失, 1-视频遮挡, 2-画面冻结, 3-过亮, 4-过暗, 5-场景变化
                                                                                // 6-条纹检测 , 7-噪声检测 , 8-偏色检测 , 9-视频模糊检测 , 10-对比度异常检测
                                                                                // 11-视频运动 , 12-视频闪烁 , 13-视频颜色 , 14-虚焦检测 , 15-过曝检测
	int					nMinDuration;											// 最短持续时间	单位：秒，0~65535
	CFG_ALARM_MSG_HANDLE stuEventHandler;										// 报警联动
	CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT_EX];			// 事件响应时间段
	int					nDetectRegionPoint;										// 检测区顶点数
	CFG_POLYGON			stuDetectRegion[MAX_POLYGON_NUM];						// 检测区
	
} CFG_VIDEOABNORMALDETECTION_INFO;

// 事件类型EVENT_IVS_FACERECOGNITION(人脸识别)对应的规则配置
typedef struct tagCFG_FACERECOGNITION_INFO
{
	// 信息
	char				szRuleName[MAX_NAME_LEN];								// 规则名称,不同规则不能重名
	bool				bRuleEnable;											// 规则使能
	BYTE                bReserved[2];                                           // 保留字段 
	int					nObjectTypeNum;											// 相应物体类型个数
	char				szObjectTypes[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];		// 相应物体类型列表
	int                 nPtzPresetId;											// 云台预置点编号	0~65535
	BYTE                 bySimilarity;                                          // 相似度，必须大于该相识度才报告(1~100)
	BYTE                 byAccuracy;                                            // 识别精度(取值1~10，随着值增大，检测精度提高，检测速度下降。最小值为1 表示检测速度优先，最大值为10表示检测精度优先)
	BYTE                 byMode;                                                // 对比模式, 0-正常, 1-指定人脸区域组合, 2-智能模式(算法根据人脸各个区域情况自动选取组合)
	BYTE                 byImportantRank;                                       // 查询重要等级大于等于此等级的人员(1~10,数值越高越重要)
	int                  nAreaNum;                                              // 区域数  
	BYTE                 byAreas[8];                                            // 人脸区域组合, 0-眉毛，1-眼睛，2-鼻子，3-嘴巴，4-脸颊(此参数在对比模式为1时有效)
	int                  nMaxCandidate;                                         // 报告的最大匹配图片个数
	CFG_ALARM_MSG_HANDLE stuEventHandler;										// 报警联动
	CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT_EX];			// 事件响应时间段
	
} CFG_FACERECOGNITION_INFO;


// 事件类型EVENT_IVS_TRAFFICCONTROL(交通管制事件)对应的规则配置
typedef struct tagCFG_TRAFFICCONTROL_INFO 
{
	// 信息
	char				szRuleName[MAX_NAME_LEN];									// 规则名称,不同规则不能重名
	bool				bRuleEnable;												// 规则使能
	BYTE                bReserved[3];                                               // 保留字段
	int					nObjectTypeNum;												// 相应物体类型个数
	char				szObjectTypes[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];			// 相应物体类型列表
	int					nDetectLinePoint;							            	// 检测线顶点数
	CFG_POLYLINE		stuDetectLine[MAX_POLYLINE_NUM];			            	// 检测线
	CFG_TIME_SECTION	stuTimeSchedule[WEEK_DAY_NUM][MAX_REC_TSECT];           	// 限行时间表
	int					nVehicleSizeNum;							            	// 车辆大小类型个数
	char				szVehicleSizeList[MAX_VEHICLE_SIZE_LIST][MAX_NAME_LEN];		// 车辆大小类型列表"Light-duty":小型车;	"Medium":中型车; "Oversize":大型车
	int					nPlateTypeNum;												// 车牌类型个数
	char				szPlateTypesList[MAX_PLATE_TYPE_LIST][MAX_NAME_LEN];		// 车牌类型列表"Unknown" 未知; "Normal" 蓝牌黑牌; "Yellow" 黄牌; "DoubleYellow" 双层黄尾牌
																					// "Police" 警牌; "Armed" 武警牌; "Military" 部队号牌; "DoubleMilitary" 部队双层
																					// "SAR" 港澳特区号牌; "Trainning" 教练车号牌; "Personal" 个性号牌; "Agri" 农用牌
																					// "Embassy" 使馆号牌; "Moto" 摩托车号牌; "Tractor" 拖拉机号牌; "Other" 其他号牌
	int					nPlateNumber;												// 车牌单双号 0:单号; 1:双号; 2:单双号;	
	CFG_ALARM_MSG_HANDLE stuEventHandler;											// 报警联动
	CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT_EX];				// 事件响应时间段
	int                 nPtzPresetId;												// 云台预置点编号	0~65535
} CFG_TRAFFICCONTROL_INFO;

// 事件类型EVENT_IVS_TRAFFICACCIDENT(交通事故事件)对应的规则配置
typedef struct tagCFG_TRAACCIDENT_INFO
{
	// 信息
	char				szRuleName[MAX_NAME_LEN];								// 规则名称,不同规则不能重名
	bool				bRuleEnable;											// 规则使能
	BYTE                bReserved[3];                                           // 保留字段
	int					nObjectTypeNum;											// 相应物体类型个数
	char				szObjectTypes[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];		// 相应物体类型列表
	int					nDetectRegionPoint;										// 检测区顶点数
	CFG_POLYGON			stuDetectRegion[MAX_POLYGON_NUM];						// 检测区
	CFG_ALARM_MSG_HANDLE stuEventHandler;										// 报警联动
	CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT_EX];			// 事件响应时间段
	int                 nPtzPresetId;											// 云台预置点编号	0~65535
	
} CFG_TRAACCIDENT_INFO;

// 事件类型EVENT_IVS_TRAFFICJUNCTION(交通路口老规则事件)对应的规则配置
typedef struct tagCFG_TRAJUNCTION_INFO
{
	// 信息
	char				szRuleName[MAX_NAME_LEN];				// 规则名称,不同规则不能重名
	bool				bRuleEnable;							// 规则使能
	int					nObjectTypeNum;							// 相应物体类型个数
	char				szObjectTypes[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];		// 相应物体类型列表
	int					nLane;									// 车道编号
	int                 nDirection;                             // 车道方向(车开往的方向),0-北 1-东北 2-东 3-东南 4-南 5-西南 6-西 7-西北
	int					nPreLinePoint;							// 前置检测线顶点数
	CFG_POLYLINE		stuPreLine[MAX_POLYLINE_NUM];			// 前置检测线
	int					nMiddleLinePoint;						// 中间检测线顶点数
	CFG_POLYLINE		stuMiddleLine[MAX_POLYLINE_NUM];		// 中间检测线
	int					nPostLinePoint;							// 后置检测线顶点数
	CFG_POLYLINE		stuPostLine[MAX_POLYLINE_NUM];			// 后置检测线
	int                 nFlowLimit;                             // 流量上限，单位辆/秒
	int                 nSpeedDownLimit;                        // 速度下限，若为0，则表示不设下限，km/h
	int                 nSpeedUpLimit;                          // 速度上限，若为0，则表示不设上限，km/h
	int                 nTriggerModeNum;                        // 触发模式个数
	char                szTriggerMode[MAX_TRIGGERMODE_NUM][MAX_NAME_LEN];  // 触发模式，"Passing" : 穿过路口(以中间检测线为准，只能单独使用),"RunRedLight" : 闯红灯
																// "Overline":压白车道线,"OverYellowLine": 压黄线, "Retrograde":逆行
																// "TurnLeft":违章左转, "TurnRight":违章右转, "CrossLane":违章变道
																// "U-Turn" 违章掉头, "Parking":违章停车, "WaitingArea" 违章进入待行区
																// "OverSpeed": 超速,"UnderSpeed":欠速,"Overflow" : 流量过大
																// "Human":行人,"NoMotor":非机动车

	CFG_ALARM_MSG_HANDLE stuEventHandler;							// 报警联动
	CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT_EX];// 事件响应时间段
	int                 nPtzPresetId;											// 云台预置点编号	0~65535
	BOOL                bMaskRetrograde;         	             // 是否屏蔽逆行，即将逆行当作正常处理
			
} CFG_TRAJUNCTION_INFO;

// 事件类型EVENT_IVS_TRAFFICGATE(交通卡口老规则事件)对应的规则配置
typedef struct tagCFG_TRAFFICGATE_INFO
{
	// 信息
	char				szRuleName[MAX_NAME_LEN];								// 规则名称,不同规则不能重名
	bool				bRuleEnable;											// 规则使能
	BYTE                bReserved[3];                                           // 保留字段
	int					nObjectTypeNum;											// 相应物体类型个数
	char				szObjectTypes[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];		// 相应物体类型列表
	int					nLane;													// 车道编号
	int					nDetectLinePoint1;										// 检测线(虚拟线圈)1顶点数
	CFG_POLYLINE		stuDetectLine1[MAX_POLYLINE_NUM];						// 检测线1
	int					nDetectLinePoint2;										// 检测线(虚拟线圈)2顶点数
	CFG_POLYLINE		stuDetectLine2[MAX_POLYLINE_NUM];						// 检测线2
	int					nLeftLinePoint;											// 左车道线顶点数
	CFG_POLYLINE		stuLeftLine[MAX_POLYLINE_NUM];							// 左车道线
	int					nRightLinePoint;										// 右车道线顶点数
	CFG_POLYLINE		stuRightLine[MAX_POLYLINE_NUM];							// 右车道线
	int					nSpeedWeight;											// 速度权重系数(最终车速=测量车速*权重系数)
	double				MetricDistance;											// 两条检测线实际距离,单位：米
	int					nSpeedUpperLimit;										// 速度上限 0表示不限上限 单位：km/h
	int					nSpeedLowerLimit;										// 速度下限 0表示不限下限 单位：km/h
	CFG_ALARM_MSG_HANDLE stuEventHandler;										// 报警联动
	CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT_EX];			// 事件响应时间段
	int                 nDirection;                                             // 车道方向(车开往的方向)，0-北 1-东北 2-东 3-东南 4-南 5-西南 6-西 7-西北
	int                 nTriggerModeNum;                                        // 触发模式个数
	char                szTriggerMode[MAX_TRIGGERMODE_NUM][MAX_NAME_LEN];       // 触发模式，"OverLine":压线,"Retrograde":逆行,"OverSpeed":超速,"UnderSpeed":欠速
	                                                                            // "Passing":穿过路口，属正常抓拍, "WrongRunningRoute":有车占道(单独使用),"YellowVehicleInRoute": 黄牌占道
	                                                                            // "OverYellowLine":压黄线
	int                 nPtzPresetId;											// 云台预置点编号	0~65535
	BOOL                bMaskRetrograde;         	             // 是否屏蔽逆行，即将逆行当作正常处理
} CFG_TRAFFICGATE_INFO;

// 事件类型EVENT_IVS_TRAFFIC_TOLLGATE(交通卡口新规则事件)对应的规则配置
typedef struct tagCFG_TRAFFICTOLLGATE_INFO
{
	char				szRuleName[MAX_NAME_LEN];								// 规则名称,不同规则不能重名
	bool				bRuleEnable;											// 规则使能
	BYTE                bReserved[3];                                           // 保留字段
	int					nObjectTypeNum;											// 相应物体类型个数
	char				szObjectTypes[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];		// 相应物体类型列表
	int                 nPtzPresetId;											// 云台预置点编号	0~65535

	int					nLane;													// 车道编号
	int					nDetectLinePoint;										// 卡口报警线顶点数
	CFG_POLYLINE		stuDetectLine[MAX_POLYLINE_NUM];						// 卡口报警线

	CFG_ALARM_MSG_HANDLE stuEventHandler;										// 报警联动
	CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT_EX];			// 事件响应时间段
} CFG_TRAFFICTOLLGATE_INFO;

// 事件类型EVENT_IVS_FACEDETECT(人脸检测事件)对应的规则配置
typedef struct tagCFG_FACEDETECT_INFO
{
	char				szRuleName[MAX_NAME_LEN];								// 规则名称,不同规则不能重名
	bool				bRuleEnable;											// 规则使能
	BYTE                bReserved[3];                                           // 保留字段
	int					nObjectTypeNum;											// 相应物体类型个数
	char				szObjectTypes[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];		// 相应物体类型列表
	int					nDetectRegionPoint;										// 检测区顶点数
	CFG_POLYGON			stuDetectRegion[MAX_POLYGON_NUM];						// 检测区
	int                 nHumanFaceTypeCount;                                    // 触发事件的人脸类型个数
	char                szHumanFaceType[MAX_HUMANFACE_LIST_SIZE][MAX_NAME_LEN]; // 触发事件的人脸类型
	CFG_ALARM_MSG_HANDLE stuEventHandler;										// 报警联动
	CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT_EX];			// 事件响应时间段
	int                 nPtzPresetId;											// 云台预置点编号	0~65535
	int                 nMinDuration;                                           // 最短触发时间,单位：秒 
}CFG_FACEDETECT_INFO;

//事件类型EVENT_IVS_TRAFFIC_NOPASSING(交通违章-禁止通行事件)对应的数据块描述信息
typedef struct tagCFG_NOPASSING_INFO
{
	char				szRuleName[MAX_NAME_LEN];								// 规则名称,不同规则不能重名
	bool				bRuleEnable;											// 规则使能
	BYTE                bReserved[3];                                           // 保留字段
}CFG_NOPASSING_INFO;

// 事件类型EVENT_IVS_TRAFFICJAM (交通拥堵事件)对应的规则配置
typedef struct tagCFG_TRAFFICJAM_INFO
{
	char				szRuleName[MAX_NAME_LEN];								// 规则名称,不同规则不能重名
	bool				bRuleEnable;											// 规则使能
    BYTE                bJamLineMargin;                                         // 占线限值，拥堵长度占车道比例限值，0-100
	BYTE                bReserved[2];                                           // 保留字段
	int					nObjectTypeNum;											// 相应物体类型个数
	char				szObjectTypes[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];		// 相应物体类型列表
	int                 nPtzPresetId;											// 云台预置点编号	0~65535
	int					nLane;													// 车道编号
	int                 nDelayTime;                                             // 检测到报警发生到开始上报的时间, 单位：秒，范围1~65535
	int                 nIntervalTime;                                          // 报警间隔时间, 单位：秒，范围1~65535
	int                 nReportTimes;                                           // 上报次数, 1~255
	CFG_ALARM_MSG_HANDLE stuEventHandler;										// 报警联动
	CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT_EX];			// 事件响应时间段
	int		            nDetectRegionPoint;                                     // 检测区顶点数
	CFG_POLYGON         stuDetectRegion[MAX_POLYGON_NUM];                       // 检测区域
}CFG_TRAFFICJAM_INFO;

// 事件类型EVENT_IVS_TRAFFIC_IDLE (交通空闲事件)对应的规则配置
typedef struct tagCFG_TRAFFIC_IDLE_INFO
{
	char				szRuleName[MAX_NAME_LEN];								// 规则名称,不同规则不能重名
	bool				bRuleEnable;											// 规则使能
    BYTE                bJamLineMargin;                                         // 占线限值，拥堵长度占车道比例限值，0-100
	BYTE                bReserved[2];                                           // 保留字段
	int					nObjectTypeNum;											// 相应物体类型个数
	char				szObjectTypes[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];		// 相应物体类型列表
	int                 nPtzPresetId;											// 云台预置点编号	0~65535
	int					nLane;													// 车道编号
	int                 nDelayTime;                                             // 检测到报警发生到开始上报的时间, 单位：秒，范围1~65535
	int                 nIntervalTime;                                          // 报警间隔时间, 单位：秒，范围1~65535
	int                 nReportTimes;                                           // 上报次数, 1~255
	CFG_ALARM_MSG_HANDLE stuEventHandler;										// 报警联动
	CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT_EX];			// 事件响应时间段
	int		            nDetectRegionPoint;                                     // 检测区顶点数
	CFG_POLYGON         stuDetectRegion[MAX_POLYGON_NUM];                       // 检测区域
}CFG_TRAFFIC_IDLE_INFO;


// 事件类型EVENT_IVS_TRAFFIC_PARKING (交通违章停车事件)对应的规则配置
typedef struct tagCFG_TRAFFIC_PARKING_INFO
{
	char				szRuleName[MAX_NAME_LEN];								// 规则名称,不同规则不能重名
	bool				bRuleEnable;											// 规则使能
	BYTE                bReserved[3];                                           // 保留字段
	int					nObjectTypeNum;											// 相应物体类型个数
	char				szObjectTypes[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];		// 相应物体类型列表
	int                 nPtzPresetId;											// 云台预置点编号	0~65535
	int					nLane;													// 车道编号
	int                 nDelayTime;                                             // 检测到报警发生到开始上报的时间, 单位：秒，范围1~65535
	int                 nParkingAllowedTime;                                    // 允许停车时间, 单位：秒，范围1~65535
	int                 nReportTimes;                                           // 上报次数, 1~255
	CFG_ALARM_MSG_HANDLE stuEventHandler;										// 报警联动
	CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT_EX];			// 事件响应时间段
		
	int					nDetectRegionPoint;										// 检测区域顶点数
	CFG_POLYGON			stuDetectRegion[MAX_POLYGON_NUM];						// 检测区域
	
	
}CFG_TRAFFIC_PARKING_INFO;

// 事件类型 EVENT_IVS_TRAFFIC_RUNREDLIGHT (交通违章-闯红灯事件)对应的规则配置
typedef struct tagCFG_TRAFFIC_RUNREDLIGHT_INFO
{
	char				szRuleName[MAX_NAME_LEN];								// 规则名称,不同规则不能重名
	bool				bRuleEnable;											// 规则使能
	BYTE                bReserved[3];                                           // 保留字段
	int					nObjectTypeNum;											// 相应物体类型个数
	char				szObjectTypes[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];		// 相应物体类型列表
	int                 nPtzPresetId;											// 云台预置点编号	0~65535
	int					nLane;													// 车道编号
	int                 nDirection;                                             // 车道方向(车开往的方向)，0-北 1-东北 2-东 3-东南 4-南 5-西南 6-西 7-西北
	int					nPreLinePoint;							                // 前置检测线顶点数
	CFG_POLYLINE		stuPreLine[MAX_POLYLINE_NUM];			                // 前置检测线
	int					nMiddleLinePoint;						                // 中间检测线顶点数
	CFG_POLYLINE		stuMiddleLine[MAX_POLYLINE_NUM];		                // 中间检测线
	int					nPostLinePoint;							                // 后置检测线顶点数
	CFG_POLYLINE		stuPostLine[MAX_POLYLINE_NUM];			                // 后置检测线
	CFG_ALARM_MSG_HANDLE stuEventHandler;										// 报警联动
	CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT_EX];			// 事件响应时间段
	
}CFG_TRAFFIC_RUNREDLIGHT_INFO;

// 事件类型 EVENT_IVS_TRAFFIC_WRONGROUTE (交通违章-不按车道行驶事件)对应的规则配置
typedef struct tagCFG_TRAFFIC_WRONGROUTE_INFO
{
    char				szRuleName[MAX_NAME_LEN];								// 规则名称,不同规则不能重名
    bool				bRuleEnable;											// 规则使能
    BYTE                bSensitivity;                                           // 灵敏度，取值1-10，数值越大代表灵敏度越高
    BYTE                bReserved[2];                                           // 保留字段
    int					nObjectTypeNum;											// 相应物体类型个数
    char				szObjectTypes[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];		// 相应物体类型列表
    int                 nPtzPresetId;											// 云台预置点编号	0~65535
    int					nLane;													// 车道编号 
    CFG_ALARM_MSG_HANDLE stuEventHandler;										// 报警联动
    CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT_EX];			// 事件响应时间段
    
    int                 nDetectRegionPoint;                                     // 检测区顶点数
    CFG_POLYGON         stuDetectRegion[MAX_POLYGON_NUM];                       // 检测区
    int                 nDirectionLinPoint;                                     // 正常行驶方向顶点数
    CFG_POLYLINE		stuDirectionLine[MAX_POLYLINE_NUM];						// 正常行驶方向，第一个点是起点，最后一个点是终点
	
}CFG_TRAFFIC_WRONGROUTE_INFO;

// 事件类型 EVENT_IVS_TRAFFIC_CROSSLANE (交通违章-违章变道)对应的规则配置
typedef struct tagCFG_TRAFFIC_CROSSLANE_INFO
{
    char				szRuleName[MAX_NAME_LEN];								// 规则名称,不同规则不能重名
    bool				bRuleEnable;											// 规则使能
    BYTE                bSensitivity;                                           // 灵敏度，取值1-10，数值越大代表灵敏度越高
    BYTE                bReserved[2];                                           // 保留字段
    int					nObjectTypeNum;											// 相应物体类型个数
    char				szObjectTypes[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];		// 相应物体类型列表
    int                 nPtzPresetId;											// 云台预置点编号	0~65535
    int					nLane;													// 车道编号 
    CFG_ALARM_MSG_HANDLE stuEventHandler;										// 报警联动
    CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT_EX];			// 事件响应时间段
    
    int                 nDetectRegionPoint;                                     // 检测区顶点数
    CFG_POLYGON         stuDetectRegion[MAX_POLYGON_NUM];                       // 检测区
    int                 nDirectionLinPoint;                                     // 正常行驶方向顶点数
    CFG_POLYLINE		stuDirectionLine[MAX_POLYLINE_NUM];						// 正常行驶方向，第一个点是起点，最后一个点是终点
	
}CFG_TRAFFIC_CROSSLANE_INFO;

// 事件类型 EVENT_IVS_TRAFFIC_OVERLINE (交通违章-压车道线)对应的规则配置
typedef struct tagCFG_TRAFFIC_OVERLINE_INFO
{
    char				szRuleName[MAX_NAME_LEN];								// 规则名称,不同规则不能重名
    bool				bRuleEnable;											// 规则使能
    BYTE                bSensitivity;                                           // 灵敏度，取值1-10，数值越大代表灵敏度越高
    BYTE                bReserved[2];                                           // 保留字段
    int					nObjectTypeNum;											// 相应物体类型个数
    char				szObjectTypes[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];		// 相应物体类型列表
    int                 nPtzPresetId;											// 云台预置点编号	0~65535
    int					nLane;													// 车道编号 
    CFG_ALARM_MSG_HANDLE stuEventHandler;										// 报警联动
    CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT_EX];			// 事件响应时间段
    
    int                 nDetectRegionPoint;                                     // 检测区顶点数
    CFG_POLYGON         stuDetectRegion[MAX_POLYGON_NUM];                       // 检测区
    int                 nDirectionLinPoint;                                     // 正常行驶方向顶点数
    CFG_POLYLINE		stuDirectionLine[MAX_POLYLINE_NUM];						// 正常行驶方向，第一个点是起点，最后一个点是终点

	
}CFG_TRAFFIC_OVERLINE_INFO;

// 事件类型 EVENT_IVS_TRAFFIC_OVERYELLOWLINE (交通违章-压黄线)对应的规则配置
typedef struct tagCFG_TRAFFIC_OVERYELLOWLINE_INFO
{
	char				szRuleName[MAX_NAME_LEN];								// 规则名称,不同规则不能重名
	bool				bRuleEnable;											// 规则使能
	BYTE                bReserved[3];                                           // 保留字段
	int					nObjectTypeNum;											// 相应物体类型个数
	char				szObjectTypes[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];		// 相应物体类型列表
	int                 nPtzPresetId;											// 云台预置点编号	0~65535
	int					nLane;													// 车道编号
	CFG_ALARM_MSG_HANDLE stuEventHandler;										// 报警联动
	CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT_EX];			// 事件响应时间段

	int					nDetectRegionPoint;										// 检测区域顶点数
	CFG_POLYGON			stuDetectRegion[MAX_POLYGON_NUM];						// 检测区域

}CFG_TRAFFIC_OVERYELLOWLINE_INFO;

// 事件类型 EVENT_IVS_TRAFFIC_RETROGRADE (交通违章-逆行事件)对应的规则配置
typedef struct tagCFG_TRAFFIC_RETROGRADE_INFO
{
	char				szRuleName[MAX_NAME_LEN];								// 规则名称,不同规则不能重名
	bool				bRuleEnable;											// 规则使能
	BYTE                bReserved[3];                                           // 保留字段
	int					nObjectTypeNum;											// 相应物体类型个数
	char				szObjectTypes[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];		// 相应物体类型列表
	int                 nPtzPresetId;											// 云台预置点编号	0~65535
	int					nLane;													// 车道编号
	BOOL                bLegal;                                                 // TRUE: 逆行合法;FALSE:逆行不合法
	CFG_ALARM_MSG_HANDLE stuEventHandler;										// 报警联动
	CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT_EX];			// 事件响应时间段

	int					nDetectRegionPoint;										// 检测区域顶点数
	CFG_POLYGON			stuDetectRegion[MAX_POLYGON_NUM];						// 检测区域
	int                 nDirectionLinPoint;                                     // 正常行驶方向顶点数
	CFG_POLYLINE		stuDirectionLine[MAX_POLYLINE_NUM];						// 正常行驶方向，第一个点是起点，最后一个点是终点
	int					nMinDuration;											// 最短触发时间	单位：秒
}CFG_TRAFFIC_RETROGRADE_INFO;

// 事件类型 EVENT_IVS_TRAFFIC_TURNLEFT (交通违章-违章左转事件)对应的规则配置
typedef struct tagCFG_TRAFFIC_TURNLEFT_INFO
{
    char				szRuleName[MAX_NAME_LEN];								// 规则名称,不同规则不能重名
    bool				bRuleEnable;											// 规则使能
    BYTE                bSensitivity;                                           // 灵敏度，取值1-10，数值越大代表灵敏度越高
    BYTE                bReserved[2];                                           // 保留字段
    int					nObjectTypeNum;											// 相应物体类型个数
    char				szObjectTypes[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];		// 相应物体类型列表
    int                 nPtzPresetId;											// 云台预置点编号	0~65535
    int					nLane;													// 车道编号 
    CFG_ALARM_MSG_HANDLE stuEventHandler;										// 报警联动
    CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT_EX];			// 事件响应时间段
    
    int                 nDetectRegionPoint;                                     // 检测区顶点数
    CFG_POLYGON         stuDetectRegion[MAX_POLYGON_NUM];                       // 检测区
    int                 nDirectionLinPoint;                                     // 正常行驶方向顶点数
    CFG_POLYLINE		stuDirectionLine[MAX_POLYLINE_NUM];						// 正常行驶方向，第一个点是起点，最后一个点是终点

	
}CFG_TRAFFIC_TURNLEFT_INFO;

// 事件类型 EVENT_IVS_TRAFFIC_TURNRIGHT (交通违章-违章右转)对应的规则配置
typedef struct tagCFG_TRAFFIC_TURNRIGHT_INFO
{
    char				szRuleName[MAX_NAME_LEN];								// 规则名称,不同规则不能重名
    bool				bRuleEnable;											// 规则使能
    BYTE                bSensitivity;                                           // 灵敏度，取值1-10，数值越大代表灵敏度越高
    BYTE                bReserved[2];                                           // 保留字段
    int					nObjectTypeNum;											// 相应物体类型个数
    char				szObjectTypes[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];		// 相应物体类型列表
    int                 nPtzPresetId;											// 云台预置点编号	0~65535
    int					nLane;													// 车道编号 
    CFG_ALARM_MSG_HANDLE stuEventHandler;										// 报警联动
    CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT_EX];			// 事件响应时间段
    
    int                 nDetectRegionPoint;                                     // 检测区顶点数
    CFG_POLYGON         stuDetectRegion[MAX_POLYGON_NUM];                       // 检测区
    int                 nDirectionLinPoint;                                     // 正常行驶方向顶点数
    CFG_POLYLINE		stuDirectionLine[MAX_POLYLINE_NUM];						// 正常行驶方向，第一个点是起点，最后一个点是终点
}CFG_TRAFFIC_TURNRIGHT_INFO;

// 事件类型 EVENT_IVS_TRAFFIC_UTURN (交通违章-违章掉头)对应的规则配置
typedef struct tagCFG_TRAFFIC_UTURN_INFO
{
	char				szRuleName[MAX_NAME_LEN];								// 规则名称,不同规则不能重名
	bool				bRuleEnable;											// 规则使能
	BYTE                bReserved[3];                                           // 保留字段
	int					nObjectTypeNum;											// 相应物体类型个数
	char				szObjectTypes[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];		// 相应物体类型列表
	int                 nPtzPresetId;											// 云台预置点编号	0~65535
	int					nLane;													// 车道编号
	CFG_ALARM_MSG_HANDLE stuEventHandler;										// 报警联动
	CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT_EX];			// 事件响应时间段


	int					nDetectRegionPoint;										// 检测区域顶点数
	CFG_POLYGON			stuDetectRegion[MAX_POLYGON_NUM];						// 检测区域
	int					nTriggerAngle;											// 掉头触发角度,取值范围(90,180)，目标调头前后的运动夹角
	BOOL                abSizeFileter;                                           // 规则特定的尺寸过滤器是否有效
	CFG_SIZEFILTER_INFO stuSizeFileter;                                         // 规则特定的尺寸过滤器
	
}CFG_TRAFFIC_UTURN_INFO;

// 事件类型 EVENT_IVS_TRAFFIC_OVERSPEED (交通违章-超速)对应的规则配置
typedef struct tagCFG_TRAFFIC_OVERSPEED_INFO
{
	char				szRuleName[MAX_NAME_LEN];								// 规则名称,不同规则不能重名
	bool				bRuleEnable;											// 规则使能
	BYTE                bReserved[3];                                           // 保留字段
	int					nObjectTypeNum;											// 相应物体类型个数
	char				szObjectTypes[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];		// 相应物体类型列表
	int                 nPtzPresetId;											// 云台预置点编号	0~65535
	int					nLane;													// 车道编号
	int                 nSpeedUpperLimit;                                       // 速度上限
	int                 nSpeedLowerLimit;                                       // 速度下限
	int					nMinDuration;											// 最短触发时间	单位：秒
	CFG_ALARM_MSG_HANDLE stuEventHandler;										// 报警联动
	CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT_EX];			// 事件响应时间段
	
}CFG_TRAFFIC_OVERSPEED_INFO;

// 事件类型 EVENT_IVS_TRAFFIC_UNDERSPEED (交通违章-欠速)对应的规则配置
typedef struct tagCFG_TRAFFIC_UNDERSPEED_INFO
{
	char				szRuleName[MAX_NAME_LEN];								// 规则名称,不同规则不能重名
	bool				bRuleEnable;											// 规则使能
	BYTE                bReserved[3];                                           // 保留字段
	int					nObjectTypeNum;											// 相应物体类型个数
	char				szObjectTypes[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];		// 相应物体类型列表
	int                 nPtzPresetId;											// 云台预置点编号	0~65535
	int					nLane;													// 车道编号
	int                 nSpeedUpperLimit;                                       // 速度上限
	int                 nSpeedLowerLimit;                                       // 速度下限
	int					nMinDuration;											// 最短触发时间	单位：秒
	CFG_ALARM_MSG_HANDLE stuEventHandler;										// 报警联动
	CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT_EX];			// 事件响应时间段
	
}CFG_TRAFFIC_UNDERSPEED_INFO;

// 事件类型 EVENT_IVS_TRAFFIC_YELLOWPLATEINLANE (交通违章-黄牌车占道事件)对应的规则配置
typedef struct tagCFG_TRAFFIC_YELLOWPLATEINLANE_INFO
{
    char				szRuleName[MAX_NAME_LEN];								// 规则名称,不同规则不能重名
    bool				bRuleEnable;											// 规则使能
    BYTE                bSensitivity;                                           // 灵敏度，取值1-10，数值越大代表灵敏度越高
    BYTE                bReserved[2];                                           // 保留字段
    int					nObjectTypeNum;											// 相应物体类型个数
    char				szObjectTypes[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];		// 相应物体类型列表
    int                 nPtzPresetId;											// 云台预置点编号	0~65535
    int					nLane;													// 车道编号 
    CFG_ALARM_MSG_HANDLE stuEventHandler;										// 报警联动
    CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT_EX];			// 事件响应时间段
    
    int                 nDetectRegionPoint;                                     // 检测区顶点数
    CFG_POLYGON         stuDetectRegion[MAX_POLYGON_NUM];                       // 检测区
    int                 nDirectionLinPoint;                                     // 正常行驶方向顶点数
    CFG_POLYLINE		stuDirectionLine[MAX_POLYLINE_NUM];						// 正常行驶方向，第一个点是起点，最后一个点是终点

}CFG_TRAFFIC_YELLOWPLATEINLANE_INFO;

// 事件类型 EVENT_IVS_TRAFFIC_VEHICLEINROUTE (交通违章-有车占道事件)对应的规则配置
typedef struct tagCFG_TRAFFIC_VEHICLEINROUTE_INFO
{
	char				szRuleName[MAX_NAME_LEN];								// 规则名称,不同规则不能重名
    bool				bRuleEnable;											// 规则使能
    BYTE                bSensitivity;                                           // 灵敏度，取值1-10，数值越大代表灵敏度越高
    BYTE                bReserved[2];                                           // 保留字段
    int					nObjectTypeNum;											// 相应物体类型个数
    char				szObjectTypes[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];		// 相应物体类型列表
    int                 nPtzPresetId;											// 云台预置点编号	0~65535
    int					nLane;													// 车道编号 
    CFG_ALARM_MSG_HANDLE stuEventHandler;										// 报警联动
    CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT_EX];			// 事件响应时间段
    
    int                 nDetectRegionPoint;                                     // 检测区顶点数
    CFG_POLYGON         stuDetectRegion[MAX_POLYGON_NUM];                       // 检测区
    int                 nDirectionLinPoint;                                     // 正常行驶方向顶点数
    CFG_POLYLINE		stuDirectionLine[MAX_POLYLINE_NUM];						// 正常行驶方向，第一个点是起点，最后一个点是终点
	
}CFG_TRAFFIC_VEHICLEINROUTE_INFO;

// 事件类型 EVENT_IVS_PRISONERRISEDETECTION (看守所起身检测事件)对应的规则配置
typedef struct tagCFG_PRISONRISEDETECTION_INFO
{
	char				szRuleName[MAX_NAME_LEN];								// 规则名称,不同规则不能重名
	bool				bRuleEnable;											// 规则使能
	BYTE                bReserved[3];                                           // 保留字段
	int					nObjectTypeNum;											// 相应物体类型个数
	char				szObjectTypes[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];		// 相应物体类型列表
	int                 nPtzPresetId;											// 云台预置点编号	0~65535
	int					nDetectRegionPoint;										// 警戒区顶点数
	CFG_POLYGON			stuDetectRegion[MAX_POLYGON_NUM10];						// 警戒区
	CFG_POLYGON			stDirection[2];											// 人睡觉方向	第一个点是起点，第二个点是终点，点的坐标归一化到[0,8191]区间
	CFG_POLYGON			stBedMiddleLine[2];										// 床铺中线	点的坐标归一化到[0,8191]区间
	int					nBedSide;												// 床铺的方位	1左边铺位,2右边铺位
	int					nMinDuration;											// 最短触发时间	单位：秒
	int					nReportInterval;										// 重复报警间隔	单位：秒
	BOOL                bSizeFileter;                                           // 规则特定的尺寸过滤器是否有效
	CFG_SIZEFILTER_INFO stuSizeFileter;                                         // 规则特定的尺寸过滤器
	CFG_ALARM_MSG_HANDLE stuEventHandler;										// 报警联动
	CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT_EX];			// 事件响应时间段
}CFG_PRISONRISEDETECTION_INFO;

// 事件类型 EVENT_IVS_TRAFFIC_PEDESTRAINPRIORITY (斑马线行人优先事件)对应的规则配置
typedef struct tagCFG_TRAFFIC_PEDESTRAINPRIORITY_INFO
{
	char                szRuleName[MAX_NAME_LEN];                               // 规则名称,不同规则不能重名
	bool                bRuleEnable;                                            // 规则使能
	BYTE                bReserved[3];                                           // 保留字段
	int                 nObjectTypeNum;                                         // 相应物体类型个数
	char                szObjectTypes[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];      // 相应物体类型列表
	int                 nPtzPresetId;                                           // 云台预置点编号	0~65535
	int                 nLane;                                                  // 车道编号
	CFG_ALARM_MSG_HANDLE stuEventHandler;                                       // 报警联动
	CFG_TIME_SECTION    stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT_EX];            // 事件响应时间段
}CFG_TRAFFIC_PEDESTRAINPRIORITY_INFO;

// 事件类型 EVENT_IVS_QUEUEDETECTION (排队检测事件)对应的规则配置
typedef struct tagCFG_IVS_QUEUEDETECTION_INFO
{
	char				szRuleName[MAX_NAME_LEN];								// 规则名称,不同规则不能重名
	bool				bRuleEnable;											// 规则使能
	BYTE                bReserved[3];                                           // 保留字段
	int					nObjectTypeNum;											// 相应物体类型个数
	char				szObjectTypes[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];		// 相应物体类型列表
	int                 nPtzPresetId;											// 云台预置点编号	0~65535
	CFG_ALARM_MSG_HANDLE stuEventHandler;										// 报警联动
	CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT_EX];			// 事件响应时间段
	
	CFG_POLYLINE		stuDetectLine[2];						                // 警戒线
	int                 nOccupyLineMargin;                                      // 占线限值，队伍长度占线比例限值
	int                 nTriggerTime;                                           // 单位秒，排队检测报警时间，排队超过阈值的状态维持了"排队检测报警时间"以后报警
}CFG_IVS_QUEUEDETECTION_INFO;

// 事件类型 EVENT_IVS_CLIMBDETECTION (攀高检测事件)对应的规则配置
typedef struct tagCFG_IVS_CLIMBDETECTION_INFO
{
	char				szRuleName[MAX_NAME_LEN];								// 规则名称,不同规则不能重名
	bool				bRuleEnable;											// 规则使能
	BYTE                bReserved[3];                                           // 保留字段
	int					nObjectTypeNum;											// 相应物体类型个数
	char				szObjectTypes[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];		// 相应物体类型列表
	int                 nPtzPresetId;											// 云台预置点编号	0~65535
	CFG_ALARM_MSG_HANDLE stuEventHandler;										// 报警联动
	CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT_EX];			// 事件响应时间段

	int                 nDetectLine;                                            // 检测线顶点个数
	CFG_POLYLINE        stuDetectLine[MAX_POLYLINE_NUM];                        // 对应的检测折线,[0,8192)
	BOOL                bSizeFileter;                                           // 规则特定的尺寸过滤器是否有效
	CFG_SIZEFILTER_INFO stuSizeFileter;                                         // 规则特定的尺寸过滤器
}CFG_IVS_CLIMBDETECTION_INFO;

// 事件类型 EVENT_IVS_LEAVEDETECTION (离岗检测事件)对应的规则配置
enum CFG_EM_LEAVEDETECTION_MODE{
	CFG_EM_LEAVEDETECTION_MODE_NONE,
	CFG_EM_LEAVEDETECTION_MODE_PATROL,    // 巡逻模式
	CFG_EM_LEAVEDETECTION_MODE_SENTRY,    // 岗哨模式
	CFG_EM_LEAVEDETECTION_MODE_ERR=255
};

typedef enum EM_CFG_LEAVEDETECTION_TRIGGERMODE{
    CFG_LEAVEDETECTION_TRIGGERMODE_UNKNOWN,
    CFG_LEAVEDETECTION_TRIGGERMODE_NOPERSON,
    CFG_LEAVEDETECTION_TRIGGERMODE_LEAVE,
    CFG_LEAVEDETECTION_TRIGGERMODE_STATIC,
}CFG_LEAVEDETECTION_TRIGGERMODE;

typedef struct tagCFG_IVS_LEAVEDETECTION_INFO
{
	char				szRuleName[MAX_NAME_LEN];								// 规则名称,不同规则不能重名
	bool				bRuleEnable;											// 规则使能
	BYTE                bReserved[3];                                           // 保留字段
	int					nObjectTypeNum;											// 相应物体类型个数
	char				szObjectTypes[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];		// 相应物体类型列表
	int                 nPtzPresetId;											// 云台预置点编号	0~65535
	CFG_ALARM_MSG_HANDLE stuEventHandler;										// 报警联动
	CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT_EX];			// 事件响应时间段

	CFG_EM_LEAVEDETECTION_MODE emMode;                                          // 检测模式
	unsigned int        nMinDuration;                                           // 最短持续时间,单位：秒
	unsigned int        nReportInterval;                                        // 报告时间间隔,单位：秒
	BOOL                bSizeFileter;                                           // 规则特定的尺寸过滤器是否有效
	CFG_SIZEFILTER_INFO stuSizeFileter;                                         // 规则特定的尺寸过滤器

	int					nDetectRegionPoint;										// 检测区顶点数
	CFG_POLYGON			stuDetectRegion[MAX_POLYGON_NUM];						// 检测区
    int                 nTriggerModeCount;										// 触发模式数组有效个数
    CFG_LEAVEDETECTION_TRIGGERMODE  emTriggerMode[MAX_TRIGGER_MODE_NUMBER];                              // 触发模式数组
}CFG_IVS_LEAVEDETECTION_INFO;

//事件类型	EVENT_IVS_TRAFFIC_PARKINGONYELLOWBOX(黄网格线抓拍事件)对应的规则配置
typedef struct tagCFG_TRAFFIC_PARKINGONYELLOWBOX_INFO
{
	char				szRuleName[MAX_NAME_LEN];								// 规则名称,不同规则不能重名
	bool				bRuleEnable;											// 规则使能
	BYTE                bReserved[3];                                           // 保留字段
	int					nObjectTypeNum;											// 相应物体类型个数
	char				szObjectTypes[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];		// 相应物体类型列表
	int                 nPtzPresetId;											// 云台预置点编号	0~65535
	CFG_ALARM_MSG_HANDLE stuEventHandler;										// 报警联动
	CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT_EX];			// 事件响应时间段

	int					nLane;													// 车道号
	int					nInterval1;												// 第二张和第一张的延时时间，单位秒
	int					nInterval2;												// 第三张和第二张的延时时间，单位秒
	int					nFollowTime;											// 跟随时间，如果一辆车与前一辆车进入黄网格的时间差小于此值，就认为是跟车进入，跟车进入情况下如果停车则不算违章

}CFG_TRAFFIC_PARKINGONYELLOWBOX_INFO;

//事件类型	EVENT_IVS_TRAFFIC_PARKINGSPACEPARKING(车位有车事件)对应的规则配置
typedef struct tagCFG_TRAFFIC_PARKINGSPACEPARKING_INFO
{
	char				szRuleName[MAX_NAME_LEN];								// 规则名称,不同规则不能重名
	bool				bRuleEnable;											// 规则使能
	BYTE                bReserved[3];                                           // 保留字段
	int					nObjectTypeNum;											// 相应物体类型个数
	char				szObjectTypes[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];		// 相应物体类型列表
	int                 nPtzPresetId;											// 云台预置点编号	0~65535
	CFG_ALARM_MSG_HANDLE stuEventHandler;										// 报警联动
	CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT_EX];			// 事件响应时间段
	
	int					nLane;													// 车位号
	int                 nDelayTime;                                             // 检测到报警发生到开始上报的时间, 单位：秒，范围1~65535
	int					nDetectRegionPoint;										// 检测区域顶点数
	CFG_POLYGON			stuDetectRegion[MAX_POLYGON_NUM];						// 检测区域
}CFG_TRAFFIC_PARKINGSPACEPARKING_INFO;

//事件类型	EVENT_IVS_TRAFFIC_PARKINGSPACENOPARKING(车位无车事件)对应的规则配置
typedef struct tagCFG_TRAFFIC_PARKINGSPACENOPARKING_INFO
{
	char				szRuleName[MAX_NAME_LEN];								// 规则名称,不同规则不能重名
	bool				bRuleEnable;											// 规则使能
	BYTE                bReserved[3];                                           // 保留字段
	int					nObjectTypeNum;											// 相应物体类型个数
	char				szObjectTypes[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];		// 相应物体类型列表
	int                 nPtzPresetId;											// 云台预置点编号	0~65535
	CFG_ALARM_MSG_HANDLE stuEventHandler;										// 报警联动
	CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT_EX];			// 事件响应时间段
	
	int					nLane;													// 车位号
	int                 nDelayTime;                                             // 检测到报警发生到开始上报的时间, 单位：秒，范围1~65535
	int					nDetectRegionPoint;										// 检测区域顶点数
	CFG_POLYGON			stuDetectRegion[MAX_POLYGON_NUM];						// 检测区域
}CFG_TRAFFIC_PARKINGSPACENOPARKING_INFO;

//事件类型EVENT_IVS_TRAFFIC_PARKINGSPACEOVERLINE(车位压线事件)对应的规则配置
typedef struct tagCFG_TRAFFIC_PARKINGSPACEOVERLINE_INFO
{
	char				szRuleName[MAX_NAME_LEN];								// 规则名称,不同规则不能重名
	bool				bRuleEnable;											// 规则使能
	bool                bAllowParkingSpaceParkingSnap;                          // 是否允许车位有车上传抓拍，true-表示允许(默认不允许)
	BYTE                byReserved[2];                                           // 保留字段
	int					nObjectTypeNum;											// 相应物体类型个数
	char				szObjectTypes[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];		// 相应物体类型列表
	int                 nPtzPresetId;											// 云台预置点编号	0~65535
	CFG_ALARM_MSG_HANDLE stuEventHandler;										// 报警联动
	CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT_EX];			// 事件响应时间段
	
	int					nLane;													// 车位号
}CFG_TRAFFIC_PARKINGSPACEOVERLINE_INFO;

//事件类型 EVENT_IVS_TRAFFIC_PEDESTRAIN (交通行人事件)对应的规则配置
typedef struct tagCFG_TRAFFIC_PEDESTRAIN_INFO
{
    char                szRuleName[MAX_NAME_LEN];                               // 规则名称,不同规则不能重名
    bool                bRuleEnable;                                            // 规则使能
    BYTE                bReserved[3];                                           // 保留字段
    int                 nObjectTypeNum;                                         // 相应物体类型个数
    char                szObjectTypes[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];      // 相应物体类型列表
    int                 nPtzPresetId;                                           // 云台预置点编号 0~65535
    CFG_ALARM_MSG_HANDLE stuEventHandler;                                       // 报警联动
    CFG_TIME_SECTION    stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT_EX];         // 事件响应时间段
    
    int                 nLane;                                                  // 车道编号
    int                 nDetectRegionPoint;                                     // 检测区顶点数
    CFG_POLYGON         stuDetectRegion[MAX_POLYGON_NUM];                       // 检测区
    int                 nMinDuration;                                           // 最短触发时间，单位：秒
}CFG_TRAFFIC_PEDESTRAIN_INFO;

//事件类型 EVENT_IVS_TRAFFIC_THROW (交通抛洒事件)对应的规则配置
typedef struct tagCFG_TRAFFIC_THROW_INFO
{
    char                szRuleName[MAX_NAME_LEN];                               // 规则名称,不同规则不能重名
    bool                bRuleEnable;                                            // 规则使能
    BYTE                bReserved[3];                                           // 保留字段
    int                 nObjectTypeNum;                                         // 相应物体类型个数
    char                szObjectTypes[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];      // 相应物体类型列表
    int                 nPtzPresetId;                                           // 云台预置点编号 0~65535
    CFG_ALARM_MSG_HANDLE stuEventHandler;                                       // 报警联动
    CFG_TIME_SECTION    stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT_EX];         // 事件响应时间段
    
    int                 nLane;                                                  // 车道编号
    int                 nDetectRegionPoint;                                     // 检测区顶点数
    CFG_POLYGON         stuDetectRegion[MAX_POLYGON_NUM];                       // 检测区
    int                 nMinDuration;                                           // 最短触发时间，单位：秒
}CFG_TRAFFIC_THROW_INFO;

// 事件类型 EVENT_IVS_TRAFFIC_BACKING (违章倒车事件)对应的规则配置
typedef struct tagCFG_TRAFFIC_BACKING_INFO
{
    char				szRuleName[MAX_NAME_LEN];								// 规则名称,不同规则不能重名
    bool				bRuleEnable;											// 规则使能
    BYTE                bSensitivity;                                           // 灵敏度，取值1-10，数值越大代表灵敏度越高
    BYTE                bReserved[2];                                           // 保留字段
    int					nObjectTypeNum;											// 相应物体类型个数
    char				szObjectTypes[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];		// 相应物体类型列表
    int                 nPtzPresetId;											// 云台预置点编号	0~65535
    int					nLane;													// 车道编号 
    CFG_ALARM_MSG_HANDLE stuEventHandler;										// 报警联动
	CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT_EX];			// 事件响应时间段

    int                 nDetectRegionPoint;                                     // 检测区顶点数
    CFG_POLYGON         stuDetectRegion[MAX_POLYGON_NUM];                       // 检测区
    int                 nDirectionLinPoint;                                     // 正常行驶方向顶点数
    CFG_POLYLINE		stuDirectionLine[MAX_POLYLINE_NUM];						// 正常行驶方向，第一个点是起点，最后一个点是终点

}CFG_TRAFFIC_BACKING_INFO;

// 事件类型 EVENT_IVS_TRAFFIC_VEHICLEINBUSROUTE(占用公交车道事件)对应规则配置
typedef struct tagCFG_TRAFFIC_VEHICLEINBUSROUTE_INFO
{
    char				szRuleName[MAX_NAME_LEN];								// 规则名称,不同规则不能重名
    bool				bRuleEnable;											// 规则使能
    BYTE                byCarType;                                              // 抓拍车辆类型，0：非黄牌车 1：蓝牌车 2：非大客车
    BYTE                bSensitivity;                                           // 灵敏度，取值1-10，数值越大代表灵敏度越高
    BYTE                bReserved[2];                                           // 保留字段
    int					nObjectTypeNum;											// 相应物体类型个数
    char				szObjectTypes[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];		// 相应物体类型列表
    int                 nPtzPresetId;											// 云台预置点编号	0~65535
    int					nLane;													// 车道编号 
    int                 nDetectRegionPoint;                                     // 检测区顶点数
    CFG_POLYGON         stuDetectRegion[MAX_POLYGON_NUM];                       // 检测区
    CFG_ALARM_MSG_HANDLE stuEventHandler;										// 报警联动
	CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT_EX];			// 事件响应时间段
}CFG_TRAFFIC_VEHICLEINBUSROUTE_INFO;

typedef enum tagCFG_SAFEBELT_SEAT
{
    CSS_UNKNOW ,
    CSS_MAIN_SEAT     ,         //主驾驶座位
    CSS_SLAVE_SEAT    ,         //副驾驶座位
}CFG_SAFEBELT_SEAT;

// 事件类型 EVENT_IVS_TRAFFIC_WITHOUT_SAFEBELT(交通未系安全带事件)对应规则配置
typedef struct tagCFG_TRAFFIC_WITHOUT_SAFEBELT
{
    char                szRuleName[MAX_NAME_LEN];                               // 规则名称,不同规则不能重名
    bool                bRuleEnable;                                            // 规则使能
    BYTE                bReserved[3];                                           // 保留字段
    int                 nObjectTypeNum;                                         // 相应物体类型个数
    char                szObjectTypes[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];      // 相应物体类型列表
    int                 nPtzPresetId;                                           // 云台预置点编号 0~65535
    CFG_ALARM_MSG_HANDLE stuEventHandler;                                       // 报警联动
    CFG_TIME_SECTION    stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT_EX];         // 事件响应时间段

    int                 nLane;                                                  // 车道编号
    int                 nSeatNum;                                               // 获取的座位数
    CFG_SAFEBELT_SEAT   emSnapSeat[MAX_SEAT_NUM];                               // 需要抓拍的驾驶座座位
}CFG_TRAFFIC_WITHOUT_SAFEBELT;

// 事件类型 EVENT_IVS_GETOUTBEDDETECTION(看守所下床事件)对应规则配置
typedef struct tagCFG_IVS_GETOUTBEDDETECTION_INFO
{
    char				szRuleName[MAX_NAME_LEN];								// 规则名称,不同规则不能重名
    bool				bRuleEnable;											// 规则使能
    BYTE                bReserved[3];                                           // 保留字段
    int					nObjectTypeNum;											// 相应物体类型个数
    char				szObjectTypes[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];		// 相应物体类型列表
    int                 nPtzPresetId;											// 云台预置点编号	0~65535
    CFG_ALARM_MSG_HANDLE stuEventHandler;										// 报警联动
    CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT_EX];			// 事件响应时间段

    int					nDetectRegionPoint;										// 检测区顶点数
    CFG_POLYGON			stuDetectRegion[MAX_POLYGON_NUM];						// 检测区,多边形类型，多边形中每个顶点的坐标归一化到[0,8192)区间
    unsigned int        nMinDuration;                                           // 最短持续时间,单位：秒
    unsigned int        nReportInterval;                                        // 报告时间间隔,单位：秒
    int                 nAssisDectLinePointNum;                                 // 辅助检测线点数
    CFG_POLYLINE        stuAssisDectLine[MAX_POLYLINE_NUM];                     // 辅助检测线
}CFG_IVS_GETOUTBEDDETECTION_INFO;

// 事件类型 EVENT_IVS_PATROLDETECTION(巡逻检测事件)对应规则配置
typedef struct tagCFG_IVS_PATROLDETECTION_INFO
{
    char				szRuleName[MAX_NAME_LEN];								// 规则名称,不同规则不能重名
    bool				bRuleEnable;											// 规则使能
    BYTE                bReserved[3];                                           // 保留字段
    int					nObjectTypeNum;											// 相应物体类型个数
    char				szObjectTypes[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];		// 相应物体类型列表
    int                 nPtzPresetId;											// 云台预置点编号	0~65535
    CFG_ALARM_MSG_HANDLE stuEventHandler;										// 报警联动
    CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT_EX];			// 事件响应时间段
    
    int					nDetectRegionPoint;										// 警戒区顶点数
    CFG_POLYGON			stuDetectRegion[MAX_POLYGON_NUM];						// 警戒区,多边形类型，多边形中每个顶点的坐标归一化到[0,8192)区间
    unsigned int        nMinDuration;                                           // 最短持续时间,单位：秒
    unsigned int        nReportInterval;                                        // 报告时间间隔,单位：秒
    unsigned int        nPatrolTime;                                            // 巡逻时间,单位：秒
	BOOL                bSizeFileter;                                           // 规则特定的尺寸过滤器是否有效
	CFG_SIZEFILTER_INFO stuSizeFileter;                                         // 规则特定的尺寸过滤器
}CFG_IVS_PATROLDETECTION_INFO;

// 事件类型 EVENT_IVS_ONDUTYDETECTION(站岗检测事件)对应规则配置
typedef struct tagCFG_IVS_ONDUTYDETECTION_INFO
{
    char				szRuleName[MAX_NAME_LEN];								// 规则名称,不同规则不能重名
    bool				bRuleEnable;											// 规则使能
    BYTE                bReserved[3];                                           // 保留字段
    int					nObjectTypeNum;											// 相应物体类型个数
    char				szObjectTypes[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];		// 相应物体类型列表
    int                 nPtzPresetId;											// 云台预置点编号	0~65535
    CFG_ALARM_MSG_HANDLE stuEventHandler;										// 报警联动
    CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT_EX];			// 事件响应时间段
    
    int					nDetectRegionPoint;										// 警戒区顶点数
    CFG_POLYGON			stuDetectRegion[MAX_POLYGON_NUM];						// 警戒区,多边形类型，多边形中每个顶点的坐标归一化到[0,8192)区间
    unsigned int        nMinDuration;                                           // 最短持续时间,单位：秒
    unsigned int        nReportInterval;                                        // 报告时间间隔,单位：秒
    int                 nTemplateRegionPointPairNum;                            // 模板区域信息点对个数
    CFG_POLYGON         stuTemplateRegion[MAX_TEMPLATEREGION_NUM][POINT_PAIR_NUM];  // 模板区域信息,个数对应于模板图片个数
}CFG_IVS_ONDUTYDETECTION_INFO;

// 事件类型 EVENT_IVS_TRAFFIC_DRIVER_SMOKING(驾驶员抽烟事件)对应规则配置
typedef struct tagCFG_TRAFFIC_DRIVER_SMOKING
{
    char                szRuleName[MAX_NAME_LEN];                               // 规则名称,不同规则不能重名
    bool                bRuleEnable;                                            // 规则使能
    BYTE                bReserved[3];                                           // 保留字段
    int                 nObjectTypeNum;                                         // 相应物体类型个数
    char                szObjectTypes[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];      // 相应物体类型列表
    int                 nPtzPresetId;                                           // 云台预置点编号 0~65535
    CFG_ALARM_MSG_HANDLE stuEventHandler;                                       // 报警联动
    CFG_TIME_SECTION    stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT_EX];         // 事件响应时间段
    
    int                 nLane;                                                  // 车道编号
}CFG_TRAFFIC_DRIVER_SMOKING;

// 事件类型 EVNET_IVS_TRAFFIC_DRIVER_CALLING(驾驶员打电话事件)对应规则配置
typedef struct tagCFG_TRAFFIC_DRIVER_CALLING
{
    char                szRuleName[MAX_NAME_LEN];                               // 规则名称,不同规则不能重名
    bool                bRuleEnable;                                            // 规则使能
    BYTE                bReserved[3];                                           // 保留字段
    int                 nObjectTypeNum;                                         // 相应物体类型个数
    char                szObjectTypes[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];      // 相应物体类型列表
    int                 nPtzPresetId;                                           // 云台预置点编号 0~65535
    CFG_ALARM_MSG_HANDLE stuEventHandler;                                       // 报警联动
    CFG_TIME_SECTION    stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT_EX];         // 事件响应时间段
    
    int                 nLane;                                                  // 车道编号
}CFG_TRAFFIC_DRIVER_CALLING;

typedef struct tagCFG_RULE_INFO
{
	DWORD				dwRuleType;							// 事件类型，详见dhnetsdk.h中"智能分析事件类型"
	int					nRuleSize;							// 该事件类型规则配置结构体大小
} CFG_RULE_INFO;

// 每个视频输入通道对应的所有事件规则：缓冲区pRuleBuf填充多个事件规则信息，每个事件规则信息内容为CFG_RULE_INFO+"事件类型对应的规则配置结构体"。
typedef struct tagCFG_ANALYSERULES_INFO
{
	int					nRuleCount;							// 事件规则个数
	char*				pRuleBuf;							// 每个视频输入通道对应的视频分析事件规则配置缓冲
	int					nRuleLen;							// 缓冲大小

} CFG_ANALYSERULES_INFO;

// 视频分析资源类型
typedef enum tagCFG_VIDEO_SOURCE_TYPE
{
	CFG_VIDEO_SOURCE_REALSTREAM,                            // 实时流
	CFG_VIDEO_SOURCE_FILESTREAM,                            // 文件流
}CFG_VIDEO_SOURCE_TYPE;

// 分析源文件类型
typedef enum tagCFG_SOURCE_FILE_TYPE
{
	CFG_SOURCE_FILE_UNKNOWN,                                // 未知类型
	CFG_SOURCE_FILE_RECORD,                                 // 录像文件
	CFG_SOURCE_FILE_PICTURE,                                    // 图片文件
}CFG_SOURCE_FILE_TYPE;

// 视频分析源文件信息
typedef struct tagCFG_SOURCE_FILE_INFO
{
	char                szFilePath[MAX_PATH];               // 文件路径
	CFG_SOURCE_FILE_TYPE emFileType;                        // 文件类型，详见CFG_SOURCE_FILE_TYPE
}CFG_SOURCE_FILE_INFO;

// 每个视频输入通道对应的视频分析资源配置信息
typedef struct tagCFG_ANALYSESOURCE_INFO
{
	bool				bEnable;								// 视频分析使能
	BYTE				bReserved[3];							// 保留对齐
	int					nChannelID;								// 智能分析的前端视频通道号
	int					nStreamType;							// 智能分析的前端视频码流类型，0:抓图码流; 1:主码流; 2:子码流1; 3:子码流2; 4:子码流3; 5:物体流
	char				szRemoteDevice[MAX_NAME_LEN];			// 设备名
	BOOL				abDeviceInfo;				        	// 设备信息是否有效
	AV_CFG_RemoteDevice stuDeviceInfo;					        // 设备信息
	CFG_VIDEO_SOURCE_TYPE emSourceType;                         // 视频分析源类型，详见CFG_VIDEO_SOURCE_TYPE
	CFG_SOURCE_FILE_INFO stuSourceFile;                          // 当视频分析源类型为CFG_VIDEO_SOURCE_FILESTREAM时，有效
} CFG_ANALYSESOURCE_INFO;

//视频分析整体配置，影响设备或服务器整体行为
typedef struct tagCFG_ANALYSEWHOLE_INFO
{	
	unsigned  int nVideoChannelType;		// 视频通道类型选择 0:数字，1;模拟，2:数字和模拟
	
}CFG_ANALYSEWHOLE_INFO;




typedef struct tagCFG_RAINBRUSH_INFO
{
	bool                bEnable;                                 // 雨刷使能
	BYTE                bSpeedRate;                              // 雨刷速度,1:快速;2:中速;3:慢速
	BYTE                bReserved[2];                            // 保留对齐
	CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT];// 事件响应时间段

}CFG_RAINBRUSH_INFO;

// BreakingSnapTimes
typedef struct tagBREAKINGSNAPTIMES_INFO
{
	int               nNormal;                          // 正常
	int               nRunRedLight;                     // 闯红灯
	int			      nOverLine;						// 压线
	int				  nOverYellowLine;			  	    // 压黄线
	int				  nRetrograde;			    	    // 逆向
	int				  nUnderSpeed;					    // 欠速
    int				  nOverSpeed;						// 超速
	int			      nWrongRunningRoute;				// 有车占道
	int			      nYellowInRoute;					// 黄牌占道
	int		    	  nSpecialRetrograde;				// 特殊逆行
	int			      nTurnLeft;						// 违章左转
	int			      nTurnRight;						// 违章右转
	int			      nCrossLane;						// 违章变道
	int			      nU_Turn;						    // 违章调头
	int			      nParking;						    // 违章停车
	int               nWaitingArea;						// 违章进入待行区
	int			      nWrongRoute;					    // 不按车道行驶		
	int               nParkingSpaceParking;             // 车位有车
	int               nParkingSpaceNoParking;           // 车位无车

	int               nRunYellowLight;					// 闯黄灯
	int               nStay;							// 违章停留
	int               nPedestrainPriority;	            // 斑马线行人优先违章
	int               nVehicleInBusRoute;               // 违章占道
	int               nBacking;                         // 违章倒车
	int				  nOverStopLine;					// 压停止线
	int               nParkingOnYellowBox;           	// 黄网格线停车	
	int               nRestrictedPlate;					// 受限车牌	
	int               nNoPassing;						// 禁行	
    int               nWithoutSafeBelt;                 // 不系安全带
    int               nDriverSmoking;                   // 驾驶员抽烟
    int               nDriverCalling;                   // 驾驶员打电话
}BREAKINGSNAPTIMES_INFO;


//OSD黑边
typedef struct tagBLACK_REGION_INFO
{
	int nHeight;			//黑边高度 取值范围：0 ~ ( 8192-原图片高度)
	int nOSDPosition;		//黑边位置 0=未知 , 1=顶部 , 2=底部
}BLACK_REGION_INFO;

#define MAX_OSD_CUSTOM_SORT_NUM       8
#define MAX_OSD_CUSTOM_SORT_ELEM_NUM  8
#define MAX_OSD_ITEM_ATTR_NUM         8 
#define MAX_PRE_POX_STR_LEN           32
#define MAX_OSD_CUSTOM_NAME_LEN       32
#define MAX_OSD_CUSTOM_VALUE_LEN      256

//全体OSD项共用属性
typedef struct tagOSD_WHOLE_ATTR
{
    BOOL        bPositionAsBlackRegion;     //位置是否同黑边相同,true时，下面的Position无效
    CFG_RECT    stPostion;                  //位置,不能超过图片范围
    BOOL        bNewLine;                   //超出矩形范围是否换行,bPositionAsBlackRegion为true时有效
    BOOL        bLoneVehicle;                //车辆信息独立显示,true 一行显示一辆车信息,false 允许多辆车信息显示在一行
}OSD_WHOLE_ATTR;

typedef union tagOSD_ATTR_SCHEME
{
    OSD_WHOLE_ATTR stWholeAttr;
}OSD_ATTR_SCHEME;

//OSD具体叠加元素
typedef struct tagOSD_CUSTOM_ELEMENT
{
    int  nNameType;                          //名称类型,	0:szName字段含义参照szOSDOrder字段定义的项
                                             //             1:"Name"字段表示自定义项，无需解析
    char szName[MAX_OSD_CUSTOM_VALUE_LEN];                           // 该项名称
    char szPrefix[MAX_PRE_POX_STR_LEN];      // 叠加前缀字符串	
    char szPostfix[MAX_PRE_POX_STR_LEN];     //叠加后缀字符串
    int  nSeperaterCount;                    //后面添加分隔符个数
    
}OSD_CUSTOM_ELEMENT;

//OSD叠加内容自定义排序
typedef struct tagOSD_CUSTOM_SORT
{
    OSD_CUSTOM_ELEMENT   stElements[MAX_OSD_CUSTOM_SORT_ELEM_NUM];     //具体叠加元素
    int                  nElementNum;
}OSD_CUSTOM_SORT;

#define  MAX_CONF_CHAR 256
//OSD属性
typedef struct tagOSD_INFO
{
	BLACK_REGION_INFO	stBackRegionInfo;		//OSD黑边属性
	int					nOSDAttrScheme;		    //OSD属性配置方案 0=未知 , 1=全体OSD项共用属性 , 2=每个OSD项一个属性
	OSD_ATTR_SCHEME		stOSDAttrScheme;		//OSD属性配置方案内容
    OSD_CUSTOM_SORT     stOSDCustomSorts[MAX_OSD_CUSTOM_SORT_NUM];    //OSD叠加内容自定义排序
    int                 nOSDCustomSortNum;
    int                 nRedLightTimeDisplay;   //OSD红灯时间配置 0=未知,1=违法最后一张,2=所有张
    char                cSeperater;             //OSD不同项之间的分隔符
    BYTE		        bReserved[3];           //字节对齐
    char                szOSDOrder[MAX_CONF_CHAR];    
    int                 nOSDContentScheme;      //0=未知, 1=Mask , 2=CustomizeSort
}OSD_INFO;

// Detector -- BEGIN
// CoilConfig
typedef struct tagCOILCONFIG_INFO
{
    int               nDelayFlashID;                 // 延时闪光灯序号	每个线圈对应的延时闪关灯序号，范围0~5，0表示不延时任何闪光灯
    int               nFlashSerialNum;               // 闪光灯序号	范围0~5，0表示不打开闪光灯（鄞州项目用）
    int               nRedDirection;                 // 红灯方向	每个线圈对应的红灯方向：0-不关联,1-左转红灯,2-直行红灯,3-右转红灯,4-待左,5-待直,6-待右, 只在电警中有效
    int               nTriggerMode ;                 // 线圈触发模式	触发模式：0-入线圈触发1-出线圈触发（鄞州项目用）
    int				  nFlashSerialNum2;				 //多抓第二张对应闪光灯序号 范围0~5，0表示不打开闪光灯
    int				  nFlashSerialNum3;				 //多抓第三张对应闪光灯序号 范围0~5，0表示不打开闪光灯
}COILCONFIG_INFO;

typedef struct tagDETECTOR_INFO
{
    int                nDetectBreaking;                  // 违章类型掩码	从低位到高位依次是：0-正常1-闯红灯2-压线3-逆行4-欠速5-超速6-有车占道
                                                         // 7-黄牌占道 8-闯黄灯 9-违章占公交车道 10-不系安全带 11-驾驶员抽烟 12-驾驶员打电话

	COILCONFIG_INFO    arstCoilCfg[MAX_COILCONFIG];      // 线圈配置数组
	int				   nRoadwayNumber;				     // 车道号	1-16 ; 0表示不启用
	int                nRoadwayDirection;                // 车道方向（车开往的方向）	0-南向北 1-西南向东北 2-东 3-西北向东南 4-北向南 5-东北向西南 6-东向西 7-东南向西北 8-忽略
	int                nRedLightCardNum;                 // 卡口图片序号	表示将电警中的某一张图片作为卡口图片（共三张），0表示不采用，1~3,表示采用对应序号的图片
	int                nCoilsNumber;                     // 线圈个数	1-3
	int                nOperationType;                   // 业务模式	0-卡口电警1-电警2-卡口
	int                arnCoilsDistance[3];              // 两两线圈的间隔	范围0-1000，单位为厘米
	int                nCoilsWidth;                      // 每个线圈的宽度	0~200cm
	int                arnSmallCarSpeedLimit[2];         // 小型车辆速度下限和上限	0~255km/h，不启用大小车限速时作为普通车辆限速
	int				   arnBigCarSpeedLimit[2];           // 大型车辆速度下限和上限	0~255km/h，启用大小车限速时有效
	int				   nOverSpeedMargin;			     // 限高速宽限值	单位：km/h
	int                nBigCarOverSpeedMargin;           // 大车限高速宽限值	单位：km/h，启用大小车限速时有效
	int				   nUnderSpeedMargin;			     // 限低速宽限值	单位：km/h
	int                nBigCarUnderSpeedMargin;          // 大车限低速宽限值	单位：km/h，启用大小车限速时有效
	bool               bSpeedLimitForSize;               // 是否启用大小车限速
	bool			   bMaskRetrograde;				     // 逆行是否视为违章行为
	BYTE               byReserved[2];                    // 保留对齐
	char               szDrivingDirection[3][MAX_DRIVINGDIRECTION]; //
													     // "DrivingDirection" : ["Approach", "上海", "杭州"],行驶方向
													     // "Approach"-上行，即车辆离设备部署点越来越近；"Leave"-下行，
														 // 即车辆离设备部署点越来越远，第二和第三个参数分别代表上行和
														 // 下行的两个地点，UTF-8编码
	int                nOverPercentage;                  // 超速百分比，超过限速百分比后抓拍
	int                nCarScheme;                       // 具体的方案Index,具体方案含义参参考打包环境local.png;根据CFG_TRAFFICSNAPSHOT_INFO.abSchemeRange字段区分作用范围
	int                nSigScheme;                       // 同上，非卡口使用
	BOOL               bEnable;                          // 车道是否有效，只有有效时才抓拍

	int				   nYellowSpeedLimit[2];			 //黄牌车限速上限和下限 范围0~255km/h
	int				   nRoadType;						 //工作路段 0 普通公路 1 高速公路
	int				   nSnapMode;						 //抓拍模式 0-全部抓拍 1-超速抓拍 2-逆向抓拍（鄞州项目用）
    int                nDelayMode;						 //延时抓拍方案 0-使DelaySnapshotDistance，1-使用DelayTime
	int                nDelayTime;						 //延时抓拍时间 闯红灯第三张抓拍位置距离最后一个线圈的时间，单位毫秒
	int				   nTriggerMode;					 //触发模式 0-入线圈触发 1-出线圈触发 2-出入都抓拍 3-关闭
	int			       nErrorRange;						 //速度误差值，进线圈2与进线圈3之间的速度误差值，若实际误差大于或等于该值，视速度无效，否则取平均速度 0-20
	double			   dSpeedCorrection;				 //速度校正系数，即速度值为测出的值乘以该系数 
    int                nDirection[2];                    //相对车道方向需要上报车辆行驶方向,nDirection[0] 0--空 1--正向 ; nDirection[1] 0--空 1--反向	
    char               szCustomParkNo[CFG_COMMON_STRING_32 + 1]; // 自定义车位号（停车场用）
    BYTE               btReserved[3];
}DETECTOR_INFO;
// Detector -- END

typedef struct tagRADAR_INFO
{
    int     nAngle;                 //角度,用于修正雷达探头安装的角度造成的速度误差,范围[0,90]
    int     nAntiJammingValue;      //抗干扰门槛值
    int     nComeInValue;           //来向进入门槛值,取值范围[0,65535]
    int     nComeOutValue;          //来向离开门槛值
    int     nDelayTime;             //雷达延时,单位ms，范围[0,255]
    DWORD   nDetectBreaking;        //违章类型掩码,从低位到高位依次是:
                                    //0-正常,1-闯红灯, 2-压线, 3-逆行,4-欠速
                                    //5-超速,6-有车占道,7-黄牌占道,8-闯黄灯,9-违章占公交车道
    int     nDetectMode;            //检测模式  0-车头检测 1-车尾检测 2-双向检测
    int     nInstallMode;           //雷达安装方式  0-侧面安装 1-上方安装
    int     nLevel;                 //灵敏度,0级灵敏度最高,范围[0,5]
    int     nMultiTargetFilter;     //多目标过滤模式,0-正常 1-过滤
    int     nWentEndValue;          //去向信号结束门槛值
    int     nWentInValue;           //去向进入门槛值
    int     nWentOutValue;          //去向离开门槛值
}RADAR_INFO;

// CFG_CMD_INTELLECTIVETRAFFIC
typedef struct tagCFG_TRAFFICSNAPSHOT_INFO
{
	char                     szDeviceAddress[MAX_DEVICE_ADDRESS];  // 设备地址	UTF-8编码，256字节
	DWORD                    nVideoTitleMask;                      // OSD叠加类型掩码	从低位到高位分别表示：0-时间 1-地点 2-车牌3-车长 4-车速 5-限速6-大车限速 7-小车限速8-超速 9-违法代码10-车道号 11-车身颜色 12-车牌类型 13-车牌颜色14-红灯点亮时间 15-违章类型 16-雷达方向 17-设备编号 18-标定到期时间 19-车型 20-行驶方向
	int                      nRedLightMargin;                      // 红灯冗余间隔时间	红灯开始的一段时间内，车辆通行不算闯红灯，单位：秒
	float				     fLongVehicleLengthLevel;              // 超长车长度最小阈值	单位：米，包含
	float					 arfLargeVehicleLengthLevel[2];        // 大车长度阈值	单位：米，包含小值
	float					 arfMediumVehicleLengthLevel[2];       // 中型车长度阈值	单位：米，包含小值
	float					 arfSmallVehicleLengthLevel[2];        // 小车长度阈值	单位：米，包含小值
	float					 fMotoVehicleLengthLevel;              // 摩托车长度最大阈值	单位：米，不包含
	BREAKINGSNAPTIMES_INFO   stBreakingSnapTimes;                  // 违章抓拍张数
	DETECTOR_INFO            arstDetector[MAX_DETECTOR];           // 车检器配置，下标是车道号
	int 					 nCarType;			               	   // 抓拍车辆类型	0-大小车都抓拍1-抓拍小车2-抓拍大车3-大小车都不抓拍
	int						 nMaxSpeed;			               	   // 当测得的速度超过最大速度时，则以最大速度计	0~255km/h
	int						 nFrameMode;		               	   // 帧间隔模式	1-速度自适应（超过速度上限取0间隔，低于速度下限取2间隔，中间取1间隔）2-由联动参数决定
	int                      arnAdaptiveSpeed[2];                  // 速度自适应下限和上限
	CFG_ALARM_MSG_HANDLE     stuEventHandler;	                   // 交通抓拍联动参数
	BOOL                     abSchemeRange;                        // TRUE:方案针对相机,以车到0的值为准;FALSE:方案针对车道。不可以修改此字段数据, 只内部使用

    DWORD                    nVideoTitleMask1;					   // 从低位到高位分别表示：0-车标 1-红灯结束时间 2-设备制造厂商 3-小车低限速 4-大车低限速 5-小车高限速 6-大车高限速 7-设备工作模式 8-通用自定义 9-车道自定义 10-抓拍触发源 11-停车场区域12-车辆类型(面包车、轿车等等) 13-中车低限速 14-中车高限速 15-道路方向 16-GPS信息
    DWORD				     nMergeVideoTitleMask;                 // 合成图片OSD叠加类型掩码	参照nVideoTitleMask字段
    DWORD				     nMergeVideoTitleMask1;				   // 合成图片OSD叠加类型掩码	参照nVideoTitleMask1字段
    int                      nTriggerSource;					   // 触发源掩码 0-RS232 1-RS485 2-IO 3-Video 4-Net
    int						 nSnapMode;							   // 抓拍模式 0-全部抓拍 1-超速抓拍 2-逆向抓拍 3-PK模式
    int                      nWorkMode;							   // 工作模式 0-自动模式，1-线圈抓拍模式，2-线圈抓拍识别，3-视频抓拍，4-视频识别, 5-混合抓拍（带识别）
    int                      nCarThreShold;						   // 车长阈值  区分大小车长的阈值，单位: cm
    int                      nSnapType;							   // 抓拍或抓录选择 0-正常抓拍模式 1-视频抓拍模式 2-黑屏快抓模式
    int                      nCustomFrameInterval[3];			   // 自定义抓拍帧间隔 第一个元素指车速小于速度自适应下限时的抓拍帧间隔，依次类推
    int                      nKeepAlive;				           // 与雷达、车检器的默认保活周期 单位秒
    OSD_INFO				 stOSD;								   // 原始图片OSD参数配置
    OSD_INFO                 stMergeOSD;                           // 合成图片OSD参数配置
    CFG_NET_TIME             stValidUntilTime;					   // 标定到期时间，指该时间点之前抓拍照片有效
    RADAR_INFO               stRadar;

}CFG_TRAFFICSNAPSHOT_INFO;

typedef struct tagCFG_TRAFFICSNAPSHOT_NEW_INFO
{
	int							nCount;								// 有效成员个数
	CFG_TRAFFICSNAPSHOT_INFO	stInfo[8];							// 交通抓拍表数组

}CFG_TRAFFICSNAPSHOT_NEW_INFO;

// 普通配置 (CFG_CMD_DEV_GENERRAL) General 
typedef struct tagCFG_DEV_DISPOSITION_INFO
{
	int                      nLocalNo;              // 本机编号，主要用于遥控器区分不同设备	0~998
	char                     szMachineName[256];    // 机器名称或编号
	char                     szMachineAddress[256]; // 机器部署地点即道路编码
	char                     szMachineGroup[256];   // 机器分组或叫设备所属单位	默认为空，用户可以将不同的设备编为一组，便于管理，可重复。
	char					 szMachineID[64];		// 机器编号, 联网平台内唯一
	
	BYTE		             bReserved[960];        // 保留字节
}CFG_DEV_DISPOSITION_INFO;

typedef struct tagOVERSPEED_INFO
{
	int                      nSpeedingPercentage[2];                        // 超速百分比区间要求区间不能重叠。有效值为0,正数,-1，-1表示无穷大值
	                                                                        // 如果是欠速：要求区间不能重叠。有效值为0,正数,-1，-1表示无穷大值，欠速百分比的计算方式：限低速-实际车速/限低速
	char                     szCode[MAX_VIOLATIONCODE];                     // 违章代码
	char                     szDescription[MAX_VIOLATIONCODE_DESCRIPT];     // 违章描述

}CFG_OVERSPEED_INFO;

typedef CFG_OVERSPEED_INFO CFG_OVERSPEED_HIGHWAY_INFO;
typedef CFG_OVERSPEED_INFO CFG_UNDERSPEED_INFO;

//ViolationCode 违章代码配置表
typedef struct tagVIOLATIONCODE_INFO
{
    char                szRetrograde[MAX_VIOLATIONCODE];			// 逆行
	char                szRetrogradeDesc[MAX_VIOLATIONCODE_DESCRIPT];              // 违章描述信息

	char				szRetrogradeHighway[MAX_VIOLATIONCODE];		// 逆行-高速公路
	char				szRetrogradeHighwayDesc[MAX_VIOLATIONCODE_DESCRIPT];		// 违章描述信息

	char                szRunRedLight[MAX_VIOLATIONCODE];			// 闯红灯
	char                szRunRedLightDesc[MAX_VIOLATIONCODE_DESCRIPT];			   // 违章描述信息

	char                szCrossLane[MAX_VIOLATIONCODE];				// 违章变道
	char                szCrossLaneDesc[MAX_VIOLATIONCODE_DESCRIPT];			   // 违章描述信息

	char                szTurnLeft[MAX_VIOLATIONCODE];				// 违章左转
	char                szTurnLeftDesc[MAX_VIOLATIONCODE_DESCRIPT];				   // 违章描述信息

	char                szTurnRight[MAX_VIOLATIONCODE];				// 违章右转
	char                szTurnRightDesc[MAX_VIOLATIONCODE_DESCRIPT];				// 违章描述信息

	char                szU_Turn[MAX_VIOLATIONCODE];				// 违章掉头
	char                szU_TurnDesc[MAX_VIOLATIONCODE_DESCRIPT];				   // 违章描述信息

	char                szJam[MAX_VIOLATIONCODE];					// 交通拥堵
	char                szJamDesc[MAX_VIOLATIONCODE_DESCRIPT];					   // 违章描述信息

	char                szParking[MAX_VIOLATIONCODE];				// 违章停车
	char                szParkingDesc[MAX_VIOLATIONCODE_DESCRIPT];			      	// 违章描述信息

	// 超速 和 超速比例 只需且必须有一个配置
	char                szOverSpeed[MAX_VIOLATIONCODE];				// 超速
	char                szOverSpeedDesc[MAX_VIOLATIONCODE_DESCRIPT];				// 违章描述信息
	CFG_OVERSPEED_INFO  stOverSpeedConfig[5];                       // 超速比例代码

	// 超速(高速公路) 和 超速比例(高速公路) 只需且必须有一个配置
	char                szOverSpeedHighway[MAX_VIOLATIONCODE];		// 超速-高速公路
	char                szOverSpeedHighwayDesc[MAX_VIOLATIONCODE_DESCRIPT];	      	// 超速-违章描述信息
	CFG_OVERSPEED_HIGHWAY_INFO stOverSpeedHighwayConfig[5];         // 超速比例代码

	// 欠速 和 欠速比例 只需且必须有一个配置
	char                szUnderSpeed[MAX_VIOLATIONCODE];	        // 欠速
	char                szUnderSpeedDesc[MAX_VIOLATIONCODE_DESCRIPT];	            // 违章描述信息
	CFG_UNDERSPEED_INFO stUnderSpeedConfig[5];                            // 欠速配置信息	是一个数组，不同的欠速比违章代码不同，为空表示违章代码不区分超速比

	char                szOverLine[MAX_VIOLATIONCODE];				// 压线
	char                szOverLineDesc[MAX_VIOLATIONCODE_DESCRIPT];			    	// 违章描述信息

	char                szOverYellowLine[MAX_VIOLATIONCODE];	    // 压黄线
	char                szOverYellowLineDesc[MAX_VIOLATIONCODE_DESCRIPT];	    	// 违章描述信息

	char                szYellowInRoute[MAX_VIOLATIONCODE];			// 黄牌占道
	char                szYellowInRouteDesc[MAX_VIOLATIONCODE_DESCRIPT];			// 违章描述信息

	char                szWrongRoute[MAX_VIOLATIONCODE];			// 不按车道行驶
	char                szWrongRouteDesc[MAX_VIOLATIONCODE_DESCRIPT];				// 违章描述信息

	char                szDrivingOnShoulder[MAX_VIOLATIONCODE];		// 路肩行驶
	char                szDrivingOnShoulderDesc[MAX_VIOLATIONCODE_DESCRIPT];		// 违章描述信息

	char                szPassing[MAX_VIOLATIONCODE];               // 正常行驶
	char                szPassingDesc[MAX_VIOLATIONCODE_DESCRIPT];               	// 违章描述信息

	char                szNoPassing[MAX_VIOLATIONCODE];             // 禁止行驶
	char                szNoPassingDesc[MAX_VIOLATIONCODE_DESCRIPT]; 				// 违章描述信息

	char                szFakePlate[MAX_VIOLATIONCODE];              // 套牌
	char                szFakePlateDesc[MAX_VIOLATIONCODE_DESCRIPT]; 				// 违章描述信息
	
	char                szParkingSpaceParking[MAX_VIOLATIONCODE];              // 车位有车
	char                szParkingSpaceParkingDesc[MAX_VIOLATIONCODE_DESCRIPT]; 				// 违章描述信息

	char                szParkingSpaceNoParking[MAX_VIOLATIONCODE];              // 车位无车
	char                szParkingSpaceNoParkingDesc[MAX_VIOLATIONCODE_DESCRIPT]; 				// 违章描述信息

    char                szWithoutSafeBelt[MAX_VIOLATIONCODE];                       // 不系安全带
    char                szWithoutSafeBeltShowName[MAX_VIOLATIONCODE_DESCRIPT];      //不系安全带显示名称
    char                szWithoutSafeBeltDesc[MAX_VIOLATIONCODE_DESCRIPT]; 	         // 不系安全带违章描述信息

    char                szDriverSmoking[MAX_VIOLATIONCODE];                          // 驾驶员抽烟
    char                szDriverSmokingShowName[MAX_VIOLATIONCODE_DESCRIPT];         //驾驶员抽烟显示名称
    char                szDriverSmokingDesc[MAX_VIOLATIONCODE_DESCRIPT]; 	         // 驾驶员抽烟带违章描述信息

    char                szDriverCalling[MAX_VIOLATIONCODE];                         // 驾驶员打电话
    char                szDriverCallingShowName[MAX_VIOLATIONCODE_DESCRIPT];        //  驾驶员打电话显示名称
    char                szDriverCallingDesc[MAX_VIOLATIONCODE_DESCRIPT]; 	        // 驾驶员打电话违章描述信息

	BYTE		        bReserved[432];
}VIOLATIONCODE_INFO;

// 车道检测类型
typedef enum tagEmCheckType
{
    EM_CHECK_TYPE_UNKNOWN,             // 不识别的检测类型
    EM_CHECK_TYPE_PHYSICAL,            // 物理检测
    EM_CHECK_TYPE_VIDEO,               // 视频检测
}EM_CHECK_TYPE;

typedef struct tagTrafficEventCheckInfo
{
    BOOL                abTrafficGate;                  // 是否携带交通卡口信息
    EM_CHECK_TYPE       emTrafficGate;                  // 交通卡口检测类型

    BOOL                abTrafficJunction;              // 是否携带交通路口信息
    EM_CHECK_TYPE       emTrafficJunction;              // 交通路口检测类型

    BOOL                abTrafficTollGate;              // 是否携带新交通卡口信息
    EM_CHECK_TYPE       emTrafficTollGate;              // 新交通卡口检测类型

    BOOL                abTrafficRunRedLight;           // 是否携带交通闯红灯信息
    EM_CHECK_TYPE       emTrafficRunRedLight;           // 交通闯红灯检测类型
    
    BOOL                abTrafficRunYellowLight;        // 是否携带交通闯黄灯信息
    EM_CHECK_TYPE       emTrafficRunYellowLight;        // 交通闯黄灯检测类型

    BOOL                abTrafficOverLine;              // 是否携带交通压线信息
    EM_CHECK_TYPE       emTrafficOverLine;              // 交通压线检测类型

    BOOL                abTrafficOverYellowLine;        // 是否携带交通压黄线信息
    EM_CHECK_TYPE       emTrafficOverYellowLine;        // 交通压黄线检测类型

    BOOL                abTrafficRetrograde;            // 是否携带交通逆行信息
    EM_CHECK_TYPE       emTrafficRetrograde;            // 交通逆行检测类型

    BOOL                abTrafficTurnLeft;              // 是否携带交通违章左转信息
    EM_CHECK_TYPE       emTrafficTurnLeft;              // 交通违章左转检测类型

    BOOL                abTrafficTurnRight;             // 是否携带交通违章右转信息
    EM_CHECK_TYPE       emTrafficTurnRight;             // 交通路口违章右转类型

    BOOL                abTrafficU_Turn;                // 是否携带交通违章掉头信息
    EM_CHECK_TYPE       emTrafficU_Turn;                // 交通违章掉头检测类型

    BOOL                abTrafficCrossLane;             // 是否携带交通违章变道信息
    EM_CHECK_TYPE       emTrafficCrossLane;             // 交通违章变道检测类型

    BOOL                abTrafficParking;               // 是否携带交通违章停车信息
    EM_CHECK_TYPE       emTrafficParking;               // 交通违章停车检测类型

    BOOL                abTrafficJam;                   // 是否携带交通拥堵信息
    EM_CHECK_TYPE       emTrafficJam;                   // 交通拥堵检测类型

    BOOL                abTrafficIdle;                  // 是否携带交通交通空闲信息
    EM_CHECK_TYPE       emTrafficIdle;                  // 交通交通空闲检测类型

    BOOL                abTrafficWaitingArea;           // 是否携带交通违章驶入待行区信息
    EM_CHECK_TYPE       emTrafficWaitingArea;           // 交通违章驶入待行区检测类型

    BOOL                abTrafficUnderSpeed;            // 是否携带交通欠速信息
    EM_CHECK_TYPE       emTrafficUnderSpeed;            // 交通欠速检测类型

    BOOL                abTrafficOverSpeed;             // 是否携带交通超速信息
    EM_CHECK_TYPE       emTrafficOverSpeed;             // 交通超速检测类型

    BOOL                abTrafficWrongRoute;            // 是否携带交通不按车道行驶信息
    EM_CHECK_TYPE       emTrafficWrongRoute;            // 交通不按车道行驶检测类型

    BOOL                abTrafficYellowInRoute;         // 是否携带交通黄牌占道信息
    EM_CHECK_TYPE       emTrafficYellowInRoute;         // 交通黄牌占道检测类型

    BOOL                abTrafficVehicleInRoute;        // 是否携带交通有车占道信息
    EM_CHECK_TYPE       emTrafficVehicleInRoute;        // 交通有车占道检测类型

    BOOL                abTrafficControl;               // 是否携带交通交通管制信息
    EM_CHECK_TYPE       emTrafficControl;               // 交通交通管制检测类型

    BOOL                abTrafficObjectAlarm;           // 是否携带交通指定类型抓拍信息
    EM_CHECK_TYPE       emTrafficObjectAlarm;           // 交通指定类型抓拍检测类型

    BOOL                abTrafficAccident;              // 是否携带交通交通事故信息
    EM_CHECK_TYPE       emTrafficAccident;              // 交通交通事故检测类型

    BOOL                abTrafficStay;                  // 是否携带交通交通停留/滞留信息
    EM_CHECK_TYPE       emTrafficStay;                  // 交通交通停留/滞留检测类型

    BOOL                abTrafficPedestrainPriority;    // 是否携带交通斑马线行人优先信息
    EM_CHECK_TYPE       emTrafficPedestrainPriority;    // 交通斑马线行人优先检测类型

    BOOL                abTrafficPedestrain;            // 是否携带交通交通行人事件信息
    EM_CHECK_TYPE       emTrafficPedestrain;            // 交通交通行人事件检测类型

    BOOL                abTrafficThrow;                 // 是否携带交通交通抛洒物品事件信息
    EM_CHECK_TYPE       emTrafficThrow;                 // 交通交通抛洒物品事件检测类型

    BOOL                abTrafficVehicleInBusRoute;     // 是否携带交通违章占道信息
    EM_CHECK_TYPE       emTrafficVehicleInBusRoute;     // 交通违章占道检测类型

    BOOL                abTrafficBacking;               // 是否携带交通违章倒车信息
    EM_CHECK_TYPE       emTrafficBacking;               // 交通违章倒车检测类型

    BOOL                abTrafficOverStopLine;          // 是否携带交通压停止线信息
    EM_CHECK_TYPE       emTrafficOverStopLine;          // 交通压停止线检测类型

    BOOL                abTrafficParkingOnYellowBox;    // 是否携带交通黄网格线抓拍信息
    EM_CHECK_TYPE       emTrafficParkingOnYellowBox;    // 交通黄网格线抓拍检测类型

    BOOL                abTrafficParkingSpaceParking;   // 是否携带交通车位有车信息
    EM_CHECK_TYPE       emTrafficParkingSpaceParking;   // 交通车位有车检测类型

    BOOL                abTrafficParkingSpaceNoParking; // 是否携带交通车位无车信息
    EM_CHECK_TYPE       emTrafficParkingSpaceNoParking; // 交通车位无车检测类型

    BOOL                abTrafficParkingSpaceOverLine;  // 是否携带交通车位有车压线信息
    EM_CHECK_TYPE       emTrafficParkingSpaceOverLine;  // 交通车位有车压线检测类型

    BOOL                abParkingSpaceDetection;        // 是否携带交通多停车位状态检测信息
    EM_CHECK_TYPE       emParkingSpaceDetection;        // 交通多停车位状态检测检测类型

    BOOL                abTrafficRestrictedPlate;       // 是否携带交通受限车牌信息
    EM_CHECK_TYPE       emTrafficRestrictedPlate;       // 交通受限车牌检测类型

    BOOL                abTrafficWithoutSafeBelt;       // 是否携带交通不系安全带信息
    EM_CHECK_TYPE       emTrafficWithoutSafeBelt;       // 交通不系安全带检测类型

    BOOL                abTrafficNoPassing;             // 是否携带交通禁行信息
    EM_CHECK_TYPE       emTrafficNoPassing;             // 交通禁行检测类型

    BOOL                abVehicleAnalyse;               // 是否携带交通车辆特征检测分析信息
    EM_CHECK_TYPE       emVehicleAnalyse;               // 交通车辆特征检测类型

    BOOL                abCrossLineDetection;           // 是否携带交通警戒线信息
    EM_CHECK_TYPE       emCrossLineDetection;           // 交通警戒线检测类型

    BOOL                abCrossFenceDetection;          // 是否携带交通穿越围栏信息
    EM_CHECK_TYPE       emCrossFenceDetection;          // 交通穿越围栏检测类型

    BOOL                abCrossRegionDetection;         // 是否携带交通警戒区信息
    EM_CHECK_TYPE       emCrossRegionDetection;         // 交通警戒区检测类型

    BOOL                abPasteDetection;               // 是否携带交通ATM贴条信息
    EM_CHECK_TYPE       emPasteDetection;               // 交通ATM贴条检测类型

    BOOL                abLeftDetection;                // 是否携带交通物品遗留信息
    EM_CHECK_TYPE       emLeftDetection;                // 交通物品遗留检测类型

    BOOL                abPreservation;                 // 是否携带交通物品保全信息
    EM_CHECK_TYPE       emPreservation;                 // 交通物品保全检测类型

    BOOL                abTakenAwayDetection;           // 是否携带交通物品搬移信息
    EM_CHECK_TYPE       emTakenAwayDetection;           // 交通物品搬移检测类型

    BOOL                abStayDetection;                // 是否携带交通停留/滞留信息
    EM_CHECK_TYPE       emStayDetection;                // 交通停留/滞留检测类型

    BOOL                abParkingDetection;             // 是否携带交通非法停车信息
    EM_CHECK_TYPE       emParkingDetection;             // 交通非法停车检测类型

    BOOL                abWanderDetection;              // 是否携带交通徘徊信息
    EM_CHECK_TYPE       emWanderDetection;              // 交通徘徊检测类型

    BOOL                abMoveDetection;                // 是否携带交通运动信息
    EM_CHECK_TYPE       emMoveDetection;                // 交通运动检测类型

    BOOL                abTailDetection;                // 是否携带交通尾随信息
    EM_CHECK_TYPE       emTailDetection;                // 交通尾随检测类型

    BOOL                abRioterDetection;              // 是否携带交通聚集信息
    EM_CHECK_TYPE       emRioterDetection;              // 交通聚集检测类型

    BOOL                abFightDetection;               // 是否携带交通打架信息
    EM_CHECK_TYPE       emFightDetection;               // 交通打架检测类型

    BOOL                abRetrogradeDetection;          // 是否携带交通逆行信息
    EM_CHECK_TYPE       emRetrogradeDetection;          // 交通逆行检测类型

    BOOL                abFireDetection;                // 是否携带交通火焰信息
    EM_CHECK_TYPE       emFireDetection;                // 交通火焰检测类型

    BOOL                abSmokeDetection;               // 是否携带交通烟雾信息
    EM_CHECK_TYPE       emSmokeDetection;               // 交通烟雾检测类型

    BOOL                abNumberStat;                   // 是否携带交通数量统计信息
    EM_CHECK_TYPE       emNumberStat;                   // 交通数量统计检测类型

    BOOL                abVideoAbnormalDetection;       // 是否携带交通视频异常信息
    EM_CHECK_TYPE       emVideoAbnormalDetection;       // 交通视频异常检测类型

    BOOL                abPrisonerRiseDetection;        // 是否携带看守所囚犯起身检测信息
    EM_CHECK_TYPE       emPrisonerRiseDetection;        // 看守所囚犯起身检测检测类型

    BOOL                abFaceDetection;                // 是否携带人脸检测信息
    EM_CHECK_TYPE       emFaceDetection;                // 人脸检测检测类型

    BOOL                abFaceRecognition;              // 是否携带人脸识别信息
    EM_CHECK_TYPE       emFaceRecognition;              // 人脸识别检测类型

    BOOL                abDensityDetection;             // 是否携带密集度检测信息
    EM_CHECK_TYPE       emDensityDetection;             // 密集度检测检测类型

    BOOL                abQueueDetection;               // 是否携带排队检测信息
    EM_CHECK_TYPE       emQueueDetection;               // 排队检测检测类型

    BOOL                abClimbDetection;               // 是否携带攀高检测信息
    EM_CHECK_TYPE       emClimbDetection;               // 攀高检测类型

    BOOL                abLeaveDetection;               // 是否携带离岗检测信息
    EM_CHECK_TYPE       emLeaveDetection;               // 离岗检测类型

    BOOL                abVehicleOnPoliceCar;           // 是否携带车载警车信息
    EM_CHECK_TYPE       emVehicleOnPoliceCar;           // 车载警车检测类型

    BOOL                abVehicleOnBus;                 // 是否携带车载公交信息
    EM_CHECK_TYPE       emVehicleOnBus;                 // 车载公交检测类型

    BOOL                abVehicleOnSchoolBus;           // 是否携带车载校车信息
    EM_CHECK_TYPE       emVehicleOnSchoolBus;           // 车载校车检测类型  

}TRAFFIC_EVENT_CHECK_INFO;  

typedef struct tagTrafficEventCheckMask
{
    BOOL                abTrafficGate;                  // 是否携带交通卡口信息
    int                 nTrafficGate;                   // 交通卡口检测模式掩码

    BOOL                abTrafficJunction;              // 是否携带交通路口信息
    int                 nTrafficJunction;               // 交通路口检测模式掩码

    BOOL                abTrafficTollGate;              // 是否携带新交通卡口信息
    int                 nTrafficTollGate;               // 新交通卡口检测模式掩码

    BOOL                abTrafficRunRedLight;           // 是否携带交通闯红灯信息
    int                 nTrafficRunRedLight;            // 交通闯红灯检测模式掩码
    
    BOOL                abTrafficRunYellowLight;        // 是否携带交通闯黄灯信息
    int                 nTrafficRunYellowLight;         // 交通闯黄灯检测模式掩码

    BOOL                abTrafficOverLine;              // 是否携带交通压线信息
    int                 nTrafficOverLine;               // 交通压线检测模式掩码

    BOOL                abTrafficOverYellowLine;        // 是否携带交通压黄线信息
    int                 nTrafficOverYellowLine;         // 交通压黄线检测模式掩码

    BOOL                abTrafficRetrograde;            // 是否携带交通逆行信息
    int                 nTrafficRetrograde;             // 交通逆行检测模式掩码

    BOOL                abTrafficTurnLeft;              // 是否携带交通违章左转信息
    int                 nTrafficTurnLeft;               // 交通违章左转检测模式掩码

    BOOL                abTrafficTurnRight;             // 是否携带交通违章右转信息
    int                 nTrafficTurnRight;              // 交通路口违章右转类型

    BOOL                abTrafficU_Turn;                // 是否携带交通违章掉头信息
    int                 nTrafficU_Turn;                 // 交通违章掉头检测模式掩码

    BOOL                abTrafficCrossLane;             // 是否携带交通违章变道信息
    int                 nTrafficCrossLane;              // 交通违章变道检测模式掩码

    BOOL                abTrafficParking;               // 是否携带交通违章停车信息
    int                 nTrafficParking;                // 交通违章停车检测模式掩码

    BOOL                abTrafficJam;                   // 是否携带交通拥堵信息
    int                 nTrafficJam;                    // 交通拥堵检测模式掩码

    BOOL                abTrafficIdle;                  // 是否携带交通交通空闲信息
    int                 nTrafficIdle;                   // 交通交通空闲检测模式掩码

    BOOL                abTrafficWaitingArea;           // 是否携带交通违章驶入待行区信息
    int                 nTrafficWaitingArea;            // 交通违章驶入待行区检测模式掩码

    BOOL                abTrafficUnderSpeed;            // 是否携带交通欠速信息
    int                 nTrafficUnderSpeed;             // 交通欠速检测模式掩码

    BOOL                abTrafficOverSpeed;             // 是否携带交通超速信息
    int                 nTrafficOverSpeed;              // 交通超速检测模式掩码

    BOOL                abTrafficWrongRoute;            // 是否携带交通不按车道行驶信息
    int                 nTrafficWrongRoute;             // 交通不按车道行驶检测模式掩码

    BOOL                abTrafficYellowInRoute;         // 是否携带交通黄牌占道信息
    int                 nTrafficYellowInRoute;          // 交通黄牌占道检测模式掩码

    BOOL                abTrafficVehicleInRoute;        // 是否携带交通有车占道信息
    int                 nTrafficVehicleInRoute;         // 交通有车占道检测模式掩码

    BOOL                abTrafficControl;               // 是否携带交通交通管制信息
    int                 nTrafficControl;                // 交通交通管制检测模式掩码

    BOOL                abTrafficObjectAlarm;           // 是否携带交通指定类型抓拍信息
    int                 nTrafficObjectAlarm;            // 交通指定类型抓拍检测模式掩码

    BOOL                abTrafficAccident;              // 是否携带交通交通事故信息
    int                 nTrafficAccident;               // 交通交通事故检测模式掩码

    BOOL                abTrafficStay;                  // 是否携带交通交通停留/滞留信息
    int                 nTrafficStay;                   // 交通交通停留/滞留检测模式掩码

    BOOL                abTrafficPedestrainPriority;    // 是否携带交通斑马线行人优先信息
    int                 nTrafficPedestrainPriority;     // 交通斑马线行人优先检测模式掩码

    BOOL                abTrafficPedestrain;            // 是否携带交通交通行人事件信息
    int                 nTrafficPedestrain;             // 交通交通行人事件检测模式掩码

    BOOL                abTrafficThrow;                 // 是否携带交通交通抛洒物品事件信息
    int                 nTrafficThrow;                  // 交通交通抛洒物品事件检测模式掩码

    BOOL                abTrafficVehicleInBusRoute;     // 是否携带交通违章占道信息
    int                 nTrafficVehicleInBusRoute;      // 交通违章占道检测模式掩码

    BOOL                abTrafficBacking;               // 是否携带交通违章倒车信息
    int                 nTrafficBacking;                // 交通违章倒车检测模式掩码

    BOOL                abTrafficOverStopLine;          // 是否携带交通压停止线信息
    int                 nTrafficOverStopLine;           // 交通压停止线检测模式掩码

    BOOL                abTrafficParkingOnYellowBox;    // 是否携带交通黄网格线抓拍信息
    int                 nTrafficParkingOnYellowBox;     // 交通黄网格线抓拍检测模式掩码

    BOOL                abTrafficParkingSpaceParking;   // 是否携带交通车位有车信息
    int                 nTrafficParkingSpaceParking;    // 交通车位有车检测模式掩码

    BOOL                abTrafficParkingSpaceNoParking; // 是否携带交通车位无车信息
    int                 nTrafficParkingSpaceNoParking;  // 交通车位无车检测模式掩码

    BOOL                abTrafficParkingSpaceOverLine;  // 是否携带交通车位有车压线信息
    int                 nTrafficParkingSpaceOverLine;   // 交通车位有车压线检测模式掩码

    BOOL                abParkingSpaceDetection;        // 是否携带交通多停车位状态检测信息
    int                 nParkingSpaceDetection;         // 交通多停车位状态检测检测模式掩码

    BOOL                abTrafficRestrictedPlate;       // 是否携带交通受限车牌信息
    int                 nTrafficRestrictedPlate;        // 交通受限车牌检测模式掩码

    BOOL                abTrafficWithoutSafeBelt;       // 是否携带交通不系安全带信息
    int                 nTrafficWithoutSafeBelt;        // 交通不系安全带检测模式掩码

    BOOL                abTrafficNoPassing;             // 是否携带交通禁行信息
    int                 nTrafficNoPassing;              // 交通禁行检测模式掩码

    BOOL                abVehicleAnalyse;               // 是否携带交通车辆特征检测分析信息
    int                 nVehicleAnalyse;                // 交通车辆特征检测模式掩码

    BOOL                abCrossLineDetection;           // 是否携带交通警戒线信息
    int                 nCrossLineDetection;            // 交通警戒线检测模式掩码

    BOOL                abCrossFenceDetection;          // 是否携带交通穿越围栏信息
    int                 nCrossFenceDetection;           // 交通穿越围栏检测模式掩码

    BOOL                abCrossRegionDetection;         // 是否携带交通警戒区信息
    int                 nCrossRegionDetection;          // 交通警戒区检测模式掩码

    BOOL                abPasteDetection;               // 是否携带交通ATM贴条信息
    int                 nPasteDetection;                // 交通ATM贴条检测模式掩码

    BOOL                abLeftDetection;                // 是否携带交通物品遗留信息
    int                 nLeftDetection;                 // 交通物品遗留检测模式掩码

    BOOL                abPreservation;                 // 是否携带交通物品保全信息
    int                 nPreservation;                  // 交通物品保全检测模式掩码

    BOOL                abTakenAwayDetection;           // 是否携带交通物品搬移信息
    int                 nTakenAwayDetection;            // 交通物品搬移检测模式掩码

    BOOL                abStayDetection;                // 是否携带交通停留/滞留信息
    int                 nStayDetection;                 // 交通停留/滞留检测模式掩码

    BOOL                abParkingDetection;             // 是否携带交通非法停车信息
    int                 nParkingDetection;              // 交通非法停车检测模式掩码

    BOOL                abWanderDetection;              // 是否携带交通徘徊信息
    int                 nWanderDetection;               // 交通徘徊检测模式掩码

    BOOL                abMoveDetection;                // 是否携带交通运动信息
    int                 nMoveDetection;                 // 交通运动检测模式掩码

    BOOL                abTailDetection;                // 是否携带交通尾随信息
    int                 nTailDetection;                 // 交通尾随检测模式掩码

    BOOL                abRioterDetection;              // 是否携带交通聚集信息
    int                 nRioterDetection;               // 交通聚集检测模式掩码

    BOOL                abFightDetection;               // 是否携带交通打架信息
    int                 nFightDetection;                // 交通打架检测模式掩码

    BOOL                abRetrogradeDetection;          // 是否携带交通逆行信息
    int                 nRetrogradeDetection;           // 交通逆行检测模式掩码

    BOOL                abFireDetection;                // 是否携带交通火焰信息
    int                 nFireDetection;                 // 交通火焰检测模式掩码

    BOOL                abSmokeDetection;               // 是否携带交通烟雾信息
    int                 nSmokeDetection;                // 交通烟雾检测模式掩码

    BOOL                abNumberStat;                   // 是否携带交通数量统计信息
    int                 nNumberStat;                    // 交通数量统计检测模式掩码

    BOOL                abVideoAbnormalDetection;       // 是否携带交通视频异常信息
    int                 nVideoAbnormalDetection;        // 交通视频异常检测模式掩码

    BOOL                abPrisonerRiseDetection;        // 是否携带看守所囚犯起身检测信息
    int                 nPrisonerRiseDetection;         // 看守所囚犯起身检测检测模式掩码

    BOOL                abFaceDetection;                // 是否携带人脸检测信息
    int                 nFaceDetection;                 // 人脸检测检测模式掩码

    BOOL                abFaceRecognition;              // 是否携带人脸识别信息
    int                 nFaceRecognition;               // 人脸识别检测模式掩码

    BOOL                abDensityDetection;             // 是否携带密集度检测信息
    int                 nDensityDetection;              // 密集度检测检测模式掩码

    BOOL                abQueueDetection;               // 是否携带排队检测信息
    int                 nQueueDetection;                // 排队检测检测模式掩码

    BOOL                abClimbDetection;               // 是否携带攀高检测信息
    int                 nClimbDetection;                // 攀高检测模式掩码

    BOOL                abLeaveDetection;               // 是否携带离岗检测信息
    int                 nLeaveDetection;                // 离岗检测模式掩码

    BOOL                abVehicleOnPoliceCar;           // 是否携带车载警车信息
    int                 nVehicleOnPoliceCar;            // 车载警车检测模式掩码

    BOOL                abVehicleOnBus;                 // 是否携带车载公交信息
    int                 nVehicleOnBus;                  // 车载公交检测模式掩码

    BOOL                abVehicleOnSchoolBus;           // 是否携带车载校车信息
    int                 nVehicleOnSchoolBus;            // 车载校车检测模式掩码  

}TRAFFIC_EVENT_CHECK_MASK;  

// 违章抓拍时间配置表
typedef struct tagTimeScheduleInfo
{
    BOOL                bEnable;                                              // 是否启用时间表
    CFG_TIME_SECTION    stuTimeSchedule[WEEK_DAY_NUM][MAX_REC_TSECT];         // 时间表
}TIME_SCHEDULE_INFO;

// 违章抓拍自定义时间配置
typedef struct tagViolationTimeSchedule
{
    BOOL                abTrafficGate;                  // 是否携带交通卡口信息
    TIME_SCHEDULE_INFO  stTrafficGate;                  // 交通卡口时间配置

    BOOL                abTrafficJunction;              // 是否携带交通路口信息
    TIME_SCHEDULE_INFO  stTrafficJunction;              // 交通路口时间配置

    BOOL                abTrafficTollGate;              // 是否携带新交通卡口信息
    TIME_SCHEDULE_INFO  stTrafficTollGate;              // 新交通卡口时间配置

    BOOL                abTrafficRunRedLight;           // 是否携带交通闯红灯信息
    TIME_SCHEDULE_INFO  stTrafficRunRedLight;           // 交通闯红灯时间配置
    
    BOOL                abTrafficRunYellowLight;        // 是否携带交通闯黄灯信息
    TIME_SCHEDULE_INFO  stTrafficRunYellowLight;        // 交通闯黄灯时间配置

    BOOL                abTrafficOverLine;              // 是否携带交通压线信息
    TIME_SCHEDULE_INFO  stTrafficOverLine;              // 交通压线时间配置

    BOOL                abTrafficOverYellowLine;        // 是否携带交通压黄线信息
    TIME_SCHEDULE_INFO  stTrafficOverYellowLine;        // 交通压黄线时间配置

    BOOL                abTrafficRetrograde;            // 是否携带交通逆行信息
    TIME_SCHEDULE_INFO  stTrafficRetrograde;            // 交通逆行时间配置

    BOOL                abTrafficTurnLeft;              // 是否携带交通违章左转信息
    TIME_SCHEDULE_INFO  stTrafficTurnLeft;              // 交通违章左转时间配置

    BOOL                abTrafficTurnRight;             // 是否携带交通违章右转信息
    TIME_SCHEDULE_INFO  stTrafficTurnRight;             // 交通路口违章右转类型

    BOOL                abTrafficU_Turn;                // 是否携带交通违章掉头信息
    TIME_SCHEDULE_INFO  stTrafficU_Turn;                // 交通违章掉头时间配置

    BOOL                abTrafficCrossLane;             // 是否携带交通违章变道信息
    TIME_SCHEDULE_INFO  stTrafficCrossLane;             // 交通违章变道时间配置

    BOOL                abTrafficParking;               // 是否携带交通违章停车信息
    TIME_SCHEDULE_INFO  stTrafficParking;               // 交通违章停车时间配置

    BOOL                abTrafficJam;                   // 是否携带交通拥堵信息
    TIME_SCHEDULE_INFO  stTrafficJam;                   // 交通拥堵时间配置

    BOOL                abTrafficIdle;                  // 是否携带交通交通空闲信息
    TIME_SCHEDULE_INFO  stTrafficIdle;                  // 交通交通空闲时间配置

    BOOL                abTrafficWaitingArea;           // 是否携带交通违章驶入待行区信息
    TIME_SCHEDULE_INFO  stTrafficWaitingArea;           // 交通违章驶入待行区时间配置

    BOOL                abTrafficUnderSpeed;            // 是否携带交通欠速信息
    TIME_SCHEDULE_INFO  stTrafficUnderSpeed;            // 交通欠速时间配置

    BOOL                abTrafficOverSpeed;             // 是否携带交通超速信息
    TIME_SCHEDULE_INFO  stTrafficOverSpeed;             // 交通超速时间配置

    BOOL                abTrafficWrongRoute;            // 是否携带交通不按车道行驶信息
    TIME_SCHEDULE_INFO  stTrafficWrongRoute;            // 交通不按车道行驶时间配置

    BOOL                abTrafficYellowInRoute;         // 是否携带交通黄牌占道信息
    TIME_SCHEDULE_INFO  stTrafficYellowInRoute;         // 交通黄牌占道时间配置

    BOOL                abTrafficVehicleInRoute;        // 是否携带交通有车占道信息
    TIME_SCHEDULE_INFO  stTrafficVehicleInRoute;        // 交通有车占道时间配置

    BOOL                abTrafficControl;               // 是否携带交通交通管制信息
    TIME_SCHEDULE_INFO  stTrafficControl;               // 交通交通管制时间配置

    BOOL                abTrafficObjectAlarm;           // 是否携带交通指定类型抓拍信息
    TIME_SCHEDULE_INFO  stTrafficObjectAlarm;           // 交通指定类型抓拍时间配置

    BOOL                abTrafficAccident;              // 是否携带交通交通事故信息
    TIME_SCHEDULE_INFO  stTrafficAccident;              // 交通交通事故时间配置

    BOOL                abTrafficStay;                  // 是否携带交通交通停留/滞留信息
    TIME_SCHEDULE_INFO  stTrafficStay;                  // 交通交通停留/滞留时间配置

    BOOL                abTrafficPedestrainPriority;    // 是否携带交通斑马线行人优先信息
    TIME_SCHEDULE_INFO  stTrafficPedestrainPriority;    // 交通斑马线行人优先时间配置

    BOOL                abTrafficPedestrain;            // 是否携带交通交通行人事件信息
    TIME_SCHEDULE_INFO  stTrafficPedestrain;            // 交通交通行人事件时间配置

    BOOL                abTrafficThrow;                 // 是否携带交通交通抛洒物品事件信息
    TIME_SCHEDULE_INFO  stTrafficThrow;                 // 交通交通抛洒物品事件时间配置

    BOOL                abTrafficVehicleInBusRoute;     // 是否携带交通违章占道信息
    TIME_SCHEDULE_INFO  stTrafficVehicleInBusRoute;     // 交通违章占道时间配置

    BOOL                abTrafficBacking;               // 是否携带交通违章倒车信息
    TIME_SCHEDULE_INFO  stTrafficBacking;               // 交通违章倒车时间配置

    BOOL                abTrafficOverStopLine;          // 是否携带交通压停止线信息
    TIME_SCHEDULE_INFO  stTrafficOverStopLine;          // 交通压停止线时间配置

    BOOL                abTrafficParkingOnYellowBox;    // 是否携带交通黄网格线抓拍信息
    TIME_SCHEDULE_INFO  stTrafficParkingOnYellowBox;    // 交通黄网格线抓拍时间配置

    BOOL                abTrafficParkingSpaceParking;   // 是否携带交通车位有车信息
    TIME_SCHEDULE_INFO  stTrafficParkingSpaceParking;   // 交通车位有车时间配置

    BOOL                abTrafficParkingSpaceNoParking; // 是否携带交通车位无车信息
    TIME_SCHEDULE_INFO  stTrafficParkingSpaceNoParking; // 交通车位无车时间配置

    BOOL                abTrafficParkingSpaceOverLine;  // 是否携带交通车位有车压线信息
    TIME_SCHEDULE_INFO  stTrafficParkingSpaceOverLine;  // 交通车位有车压线时间配置

    BOOL                abParkingSpaceDetection;        // 是否携带交通多停车位状态检测信息
    TIME_SCHEDULE_INFO  stParkingSpaceDetection;        // 交通多停车位状态检测时间配置

    BOOL                abTrafficRestrictedPlate;       // 是否携带交通受限车牌信息
    TIME_SCHEDULE_INFO  stTrafficRestrictedPlate;       // 交通受限车牌时间配置

    BOOL                abTrafficWithoutSafeBelt;       // 是否携带交通不系安全带信息
    TIME_SCHEDULE_INFO  stTrafficWithoutSafeBelt;       // 交通不系安全带时间配置

    BOOL                abTrafficNoPassing;             // 是否携带交通禁行信息
    TIME_SCHEDULE_INFO  stTrafficNoPassing;             // 交通禁行时间配置

    BOOL                abVehicleAnalyse;               // 是否携带交通车辆特征检测分析信息
    TIME_SCHEDULE_INFO  stVehicleAnalyse;               // 交通车辆特征时间配置

    BOOL                abCrossLineDetection;           // 是否携带交通警戒线信息
    TIME_SCHEDULE_INFO  stCrossLineDetection;           // 交通警戒线时间配置

    BOOL                abCrossFenceDetection;          // 是否携带交通穿越围栏信息
    TIME_SCHEDULE_INFO  stCrossFenceDetection;          // 交通穿越围栏时间配置

    BOOL                abCrossRegionDetection;         // 是否携带交通警戒区信息
    TIME_SCHEDULE_INFO  stCrossRegionDetection;         // 交通警戒区时间配置

    BOOL                abPasteDetection;               // 是否携带交通ATM贴条信息
    TIME_SCHEDULE_INFO  stPasteDetection;               // 交通ATM贴条时间配置

    BOOL                abLeftDetection;                // 是否携带交通物品遗留信息
    TIME_SCHEDULE_INFO  stLeftDetection;                // 交通物品遗留时间配置

    BOOL                abPreservation;                 // 是否携带交通物品保全信息
    TIME_SCHEDULE_INFO  stPreservation;                 // 交通物品保全时间配置

    BOOL                abTakenAwayDetection;           // 是否携带交通物品搬移信息
    TIME_SCHEDULE_INFO  stTakenAwayDetection;           // 交通物品搬移时间配置

    BOOL                abStayDetection;                // 是否携带交通停留/滞留信息
    TIME_SCHEDULE_INFO  stStayDetection;                // 交通停留/滞留时间配置

    BOOL                abParkingDetection;             // 是否携带交通非法停车信息
    TIME_SCHEDULE_INFO  stParkingDetection;             // 交通非法停车时间配置

    BOOL                abWanderDetection;              // 是否携带交通徘徊信息
    TIME_SCHEDULE_INFO  stWanderDetection;              // 交通徘徊时间配置

    BOOL                abMoveDetection;                // 是否携带交通运动信息
    TIME_SCHEDULE_INFO  stMoveDetection;                // 交通运动时间配置

    BOOL                abTailDetection;                // 是否携带交通尾随信息
    TIME_SCHEDULE_INFO  stTailDetection;                // 交通尾随时间配置

    BOOL                abRioterDetection;              // 是否携带交通聚集信息
    TIME_SCHEDULE_INFO  stRioterDetection;              // 交通聚集时间配置

    BOOL                abFightDetection;               // 是否携带交通打架信息
    TIME_SCHEDULE_INFO  stFightDetection;               // 交通打架时间配置

    BOOL                abRetrogradeDetection;          // 是否携带交通逆行信息
    TIME_SCHEDULE_INFO  stRetrogradeDetection;          // 交通逆行时间配置

    BOOL                abFireDetection;                // 是否携带交通火焰信息
    TIME_SCHEDULE_INFO  stFireDetection;                // 交通火焰时间配置

    BOOL                abSmokeDetection;               // 是否携带交通烟雾信息
    TIME_SCHEDULE_INFO  stSmokeDetection;               // 交通烟雾时间配置

    BOOL                abNumberStat;                   // 是否携带交通数量统计信息
    TIME_SCHEDULE_INFO  stNumberStat;                   // 交通数量统计时间配置

    BOOL                abVideoAbnormalDetection;       // 是否携带交通视频异常信息
    TIME_SCHEDULE_INFO  stVideoAbnormalDetection;       // 交通视频异常时间配置

    BOOL                abPrisonerRiseDetection;        // 是否携带看守所囚犯起身检测信息
    TIME_SCHEDULE_INFO  stPrisonerRiseDetection;        // 看守所囚犯起身检测时间配置

    BOOL                abFaceDetection;                // 是否携带人脸检测信息
    TIME_SCHEDULE_INFO  stFaceDetection;                // 人脸检测时间配置

    BOOL                abFaceRecognition;              // 是否携带人脸识别信息
    TIME_SCHEDULE_INFO  stFaceRecognition;              // 人脸识别时间配置

    BOOL                abDensityDetection;             // 是否携带密集度检测信息
    TIME_SCHEDULE_INFO  stDensityDetection;             // 密集度检测时间配置

    BOOL                abQueueDetection;               // 是否携带排队检测信息
    TIME_SCHEDULE_INFO  stQueueDetection;               // 排队检测时间配置

    BOOL                abClimbDetection;               // 是否携带攀高检测信息
    TIME_SCHEDULE_INFO  stClimbDetection;               // 攀高时间配置

    BOOL                abLeaveDetection;               // 是否携带离岗检测信息
    TIME_SCHEDULE_INFO  stLeaveDetection;               // 离岗时间配置

    BOOL                abVehicleOnPoliceCar;           // 是否携带车载警车信息
    TIME_SCHEDULE_INFO  stVehicleOnPoliceCar;           // 车载警车时间配置

    BOOL                abVehicleOnBus;                 // 是否携带车载公交信息
    TIME_SCHEDULE_INFO  stVehicleOnBus;                 // 车载公交时间配置

    BOOL                abVehicleOnSchoolBus;           // 是否携带车载校车信息
    TIME_SCHEDULE_INFO  stVehicleOnSchoolBus;           // 车载校车时间配置  
}VIOLATION_TIME_SCHEDULE;

// MixModeConfig中关于车道配置信息
typedef struct tagMixModeLaneInfo
{
    unsigned int                nLaneNum;                           // 车道配置个数
    TRAFFIC_EVENT_CHECK_INFO    stCheckInfo[MAX_LANE_CONFIG_NUMBER];     // 车道配置对应事件检测信息
}MIX_MODE_LANE_INFO;

// MixModeConfig 混合模式违章配置
typedef struct tagMIX_MODE_CONFIG
{
	BOOL                        bLaneDiffEnable;                    // 是否按车道区分
	MIX_MODE_LANE_INFO          stLaneInfo;
    TRAFFIC_EVENT_CHECK_INFO    stCheckInfo;
}MIX_MODE_CONFIG;

typedef struct tagPeriodOfValidity
{
    CFG_NET_TIME            stBeginTime;                    // 标定开始时间 
    CFG_NET_TIME            stEndTime;                      // 标定到期时间
}PERIOD_OF_VALIDITY;

// 交通全局配置对应标定相关配置
typedef struct tagTrafficCalibrationInfo
{
    char                    szUnit[CFG_COMMON_STRING_256];              // 标定单位
    char                    szCertificate[CFG_COMMON_STRING_256];       // 标定证书
    PERIOD_OF_VALIDITY      stPeriodOfValidity;                         // 标定有效期
}TRAFFIC_CALIBRATION_INFO;

// 交通配置对应传输策略
typedef enum tagEmTransferPolicy
{
    EM_TRAFFIC_TRANSFER_UNKNOWN,            // 未知策略
    EM_TRAFFIC_TRANSFER_REALTIME,           // "RealtimePriority" 实时优先
    EM_TRAFFIC_TRANSFER_SEQUENCE,           // "SequencePriority" 顺序优先

}EM_TRANSFER_POLICY;

// 交通全局配置对应图片命名格式参数配置
typedef struct tagTrafficNamingFormat
{
    char                    szFormat[CFG_COMMON_STRING_256];            // 图片格式
}TRAFFIC_NAMING_FORMAT;

// 交通全局配置对应灯组状态配置
typedef struct tagEnableLightStateInfo
{
    BOOL                    bEnable;      // 是否启动应用层收到的灯组状态给底层
}ENABLE_LIGHT_STATE_INFO;

// CFG_CMD_TRAFFICGLOBAL 交通全局配置配置表
typedef struct tagCFG_TRAFFICGLOBAL_INFO
{
	VIOLATIONCODE_INFO      stViolationCode;                            // 违章代码配置表                          
    BOOL                    bEnableRedList;                             // 使能红名单检测，使能后，名单内车辆违章不上报

    BOOL                    abViolationTimeSchedule;                    // 是否携带违章抓拍自定义时间配置
    VIOLATION_TIME_SCHEDULE stViolationTimeSchedule;                    // 违章抓拍自定义时间配置
    
    BOOL                    abEnableBlackList;                          // 是否携带使能黑名单检测信息
    BOOL                    bEnableBlackList;                           // 使能黑名单检测

    BOOL                    abPriority;                                 // 是否携带违章优先级参数
    unsigned int            nPriority;                                  // 违章优先级个数
    char                    szPriority[MAX_PRIORITY_NUMBER][CFG_COMMON_STRING_256]; // 违章优先级, 0为最高优先级    

    BOOL                    abNamingFormat;                             // 是否携带图片命名格式参数
    TRAFFIC_NAMING_FORMAT   stNamingFormat;                             // 图片命名格式参数配置

    BOOL                    abVideoNamingFormat;                        // 是否携带录像命名格式参数
    TRAFFIC_NAMING_FORMAT   stVideoNamingFormat;                        // 录像命名格式参数配置

    BOOL                    abCalibration;                              // 是否携带标定信息
    TRAFFIC_CALIBRATION_INFO stCalibration;                             // 标定信息
    
    BOOL                    abAddress;                                  // 是否携带查询地址参数
    char                    szAddress[CFG_COMMON_STRING_256];           // 查询地址，UTF-8编码

    BOOL                    abTransferPolicy;                           // 是否携带传输策略参数
    EM_TRANSFER_POLICY      emTransferPolicy;                           // 传输策略

    BOOL                    abSupportModeMaskConfig;                    // 是否携带违章掩码 
    TRAFFIC_EVENT_CHECK_MASK stSupportModeMaskConfig;                   // 违章类型支持的检测模式掩码配置

    BOOL                    abIsEnableLightState;                       // 是否携带灯组状态
    ENABLE_LIGHT_STATE_INFO stIsEnableLightState;                       // 交通全局配置对应图片命名格式参数配置
    
    BOOL                    abMixModeInfo;                              // 是否含有混合模式配置
    MIX_MODE_CONFIG         stMixModeInfo;                              // 混合模式配置
}CFG_TRAFFICGLOBAL_INFO;

// CFG_CMD_VIDEOENCODEROI 视频编码ROI(Region of Intrest)配置
#define DH_MAX_QUALITY_REGION_NUM 8
typedef struct tagCFG_VIDEOENCODEROI_INFO
{
	int      nRegionNum;                               // 优化区域个数
	CFG_RECT stRegions[DH_MAX_QUALITY_REGION_NUM];     // 优化区域 支持多个优化区域，使用相对坐标体系，取值均为0~8191
	BYTE     byQuality;        // 图像质量 取值1~6，值越大，图像质量越好
	bool     bMain;            // 优化主码流视频编码
	bool     bExtra1;          // 优化辅码流1视频编码	
	bool     bExtra2;          // 优化辅码流2视频编码
	bool     bExtra3;          // 优化辅码流3视频编码
	bool     bSnapshot;        // 优化抓图编码
	BYTE     byReserved2[2];   // 对齐
}CFG_VIDEOENCODEROI_INFO;

// ATM取款超时配置
typedef struct tagCFG_ATMMOTION_INFO
{
	int nTimeLimit;            // 取款超时时间,单位:秒
}CFG_ATMMOTION_INFO;

typedef struct tagCFG_SNAPSOURCE_INFO_SINGLE_CHANNEL
{
	bool		bEnable;			// 使能
	BYTE		bReserved1[3];		// 保留字段，对齐
	BYTE		bDevice[64];		// 设备名
	DWORD		dwChannel;			// 视频通道号
	DWORD		dwLinkVideoChannel; // 抓图通道对应的视频通道号
	BYTE		bReserved[512];		// 保留字段
}SNAPSOURCE_INFO_SINGLE_CHANNEL;

typedef struct tagCFG_SNAPSOURCE_INFO
{
	DWORD dwCount;												//要配置的通道的个数
	SNAPSOURCE_INFO_SINGLE_CHANNEL singleChnSanpInfo[MAX_VIDEO_CHANNEL_NUM];	//SNAPSOURCE_INFO_SINGLE_CHANNEL数组的地址
}CFG_SNAPSOURCE_INFO;

typedef struct tagDEVICE_STATUS
{
	char	szDeviceName[MAX_REMOTEDEVICENAME_LEN];	//远程设备的名字
	BYTE	bDeviceStatus;							//远程设备的状态 0：断线 1：在线
	BYTE	bReserved[63];							//保留字节
}DEVICE_STATUS;

typedef struct tagCFG_REMOTE_DEVICE_STATUS
{
	DEVICE_STATUS devStatus[MAX_REMOTE_DEV_NUM]; //设备状态
	DWORD		  dwDevCount;					 //设备数量
	BYTE		  bReserved[1024];				 //保留字节
}CFG_REMOTE_DEVICE_STATUS;

//-----------------------------音频分析相关配置------------------------------
// 事件类型 EVENT_IVS_AUDIO_ABNORMALDETECTION (声音异常检测事件)对应规则配置
typedef struct tagCFG_IVS_AUDIO_ABNORMALDETECTION_INFO
{
	char				szRuleName[MAX_NAME_LEN];								// 规则名称,不同规则不能重名
	bool				bRuleEnable;											// 规则使能
	BYTE                bReserved[3];                                           // 保留字段
	int                 nDecibel;                                               // 声音强度，单位 db
	int                 nFrequency;                                             // 声音频率, 单位 Hz
	int                 nMinDuration;                                           // 最短持续时间, 单位 s
	CFG_ALARM_MSG_HANDLE stuEventHandler;										// 报警联动
	CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT_EX];			// 事件响应时间段
}CFG_IVS_AUDIO_ABNORMALDETECTION_INFO;

typedef struct tagCFG_CAP_AUDIO_ANALYSE_INFO
{
	int                 nSupportedRuleNum;                                      // 支持的规则类型数
	DWORD               dwSupportedRules[MAX_RULE_LIST_SIZE];                   // 具体支持的规则类型
}CFG_CAP_AUDIO_ANALYSE_INFO;

//-------------------------IPS && SVR------------------------------

// 设备状态信息
typedef struct tagCFG_DEVICESTATUS_INFO
{
	int                 nPowerNum;                               // 电源个数
	BYTE                byPowerStatus[MAX_POWER_NUM];            // 电源状态，1:正常 2:异常 3:未知
	int                 nCPUNum;                                 // CPU个数
	int                 nCPUTemperature[MAX_CPU_NUM];            // CPU温度
	int                 nFanNum;                                 // 风扇个数
	int                 nRotatoSpeed[MAX_FUN_NUM];               // 风扇转速
}CFG_DEVICESTATUS_INFO;

// 扩展柜信息
typedef struct tagCFG_HARDDISK_INFO 
{
	int                     nChannel;                        // 通道号
	int                     nCapacity;                       // 硬盘容量 
	BYTE                    byStatus;                        // 硬盘状态，0:unknown 1:running 2:fail 3.spare热备
															 // 4.sync同步 5.faulty失效 6.rebuilding重建 7.remove移除 8.sleep休眠
	BYTE                    byUsedStatus;                    // 使用状态，1.空闲 2.在用 3.未知
    BYTE                    byHotBack;                       // 是否是热备盘，0:热备盘 1:非热备盘
	BYTE                    byReserved;                      // 字节对齐
	char                    szRaidName[MAX_NAME_LEN];        // 所在Raid(磁盘组)的名称	"RaidName" : "Raid0",
															 // 所在Raid(磁盘组)的名称。如不属于任何Raid，则字段为null。
															 // 比如热备盘，属于全局热备盘的，则传null。
	char                    szType[32];                      // 硬盘型号
	int                     nTank;                           // 扩展柜, 0:主机;1:扩展柜1; 2:扩展柜2	……
	int						nRemainSpace;					 // 剩余容量，单位M
}CFG_HARDDISK_INFO;

typedef struct tagCFG_HARDDISKTANK_INFO
{
	char                    szTankName[MAX_NAME_LEN];           // 存储柜名称
	int                     nHardDiskNum;                       // 硬盘个数
	CFG_HARDDISK_INFO       stuHarddiskInfo[MAX_HARDDISK_NUM];  // 硬盘信息
}CFG_HARDDISKTANK_INFO;

typedef struct tagCFG_HARDISKTANKGROUP_INFO
{
	int                      nTankNum;                       // 硬盘存储柜个数
	CFG_HARDDISKTANK_INFO    stuHarddisktank[MAX_TANK_NUM];  // 硬盘存储柜数组
}CFG_HARDISKTANKGROUP_INFO;

// Raid组信息
typedef struct tagCFG_RAID_INFO
{
	char                    szRaidName[MAX_NAME_LEN];         // Raid名称
	BYTE                    byType;                           // 类型 1:Jbob, 2:Raid0, 3:Raid1, 4:Raid5
	BYTE                    byStatus;                         // 状态  0:unknown, 1:active, 2:degraded, 3:inactive, 4: Resyncing
															  // 5.Clean 6.Unknow 7.Recovering 8.Reshaping 9.Checking 10.NotStarted
	BYTE                    byStatusCount;                    // 状态数量, 状态数>=1时, 用byStatusGroup表示状态
	BYTE                    byReserved;						  // 字节对齐
	int                     nMember[MAX_CHAN_NUM];            // 组成磁盘通道
	int                     nDiskNUM;                         // 磁盘个数
	int                     nCapacity;                        // 容量
	int                     nTank;                            // 扩展柜
	int						nRemainSpace;					  // 剩余容量，单位M
	BYTE					byStatusGroup[MAX_STATUS_NUM];	  // 状态数组, 参数值同byStatus
}CFG_RAID_INFO;

typedef struct tagCFG_RAIDGROUP_INFO
{
	int                     nRaidNum;                         // Raid个数
	CFG_RAID_INFO           stuRaidInfo[MAX_RAID_NUM];        // Raid组信息
}CFG_RAIDGROUP_INFO;

// 存储池组信息
typedef struct tagCFG_STORAGEPOOL_INFO
{
	char                   szName[MAX_NAME_LEN];               // 存储池名称
	int                    nMemberNum;                         // 设备数量
	char                   szMember[MAX_DEV_NUM][MAX_NAME_LEN];// 组成设备
	int                    nUsed;                              // 已用容量
    int                    nCapacity;                          // 总容量
    int                    nStatus;                            // 状态	0:unknown 1:active 2:degraded 3:inactive
    int                    nTank;                              // 扩展柜	0:主机, 1:扩展柜1, 2:扩展柜2 ……
}CFG_STORAGEPOOL_INFO;

typedef struct tagCFG_STORAGEPOOLGROUP_INFO
{
	int                     nStroagePoolNum;                           // 存储池个数
	CFG_STORAGEPOOL_INFO    stuStoragePoolInfo[MAX_STORAGEPOOL_NUM];   // 存储池信息
}CFG_STORAGEPOOLGROUP_INFO;

// 文件系统组信息
typedef struct tagCFG_STORAGEPOSITION_INFO
{
	char                   szName[MAX_NAME_LEN];               // 存储位置名称	
    char                   szStoragePoolName[MAX_NAME_LEN];    // 存储池名称	
    int                    nUsedCapacity;                      // 已用容量,单位G	
    int                    nTotalCapacity;                     // 容量,单位G	
	BYTE                   byStatus;                           // 状态 0.未知 1.正常 2.配置异常 3.挂载异常
    BYTE                   byReserved[3];                      // 字节对齐
}CFG_STORAGEPOSITION_INFO;

typedef struct tafCFG_STORAGEPOSITIONGROUP_INFO
{
	int                      nStoragePositionNum;                         // 存储信息个数
	CFG_STORAGEPOSITION_INFO stuStoragePositionInfo[MAX_STRORAGEPOS_NUM]; // 文件系统组信息      
}CFG_STORAGEPOSITIONGROUP_INFO;

// 前端设备组信息
typedef struct tagCFG_VIDEOINDEV_INFO
{
	char                   szDevName[MAX_NAME_LEN];             // 前端设备名称	
    char                   szDevID[MAX_NAME_LEN];               // 设备ID	
    char                   szDevType[MAX_NAME_LEN];             // 设备类型
    int                    nTotalChan;                          // 总通道数
	int                    nTotalAlarmChan;                     // 报警通道总数
    char                   szIP[MAX_ADDRESS_LEN];               // 设备IP
	BYTE                   byStatus;                            // 状态 0:未知 1:在线 2:离线
	BYTE                   byReserved[3];                       // 字节对齐
}CFG_VIDEOINDEV_INFO;

typedef struct tafCFG_VIDEOINDEVGROUP_INFO
{
	int                    nVideoDevNum;                              // 前端设备个数
	CFG_VIDEOINDEV_INFO    stuVideoInDevInfo[MAX_VIDEODEV_NUM];       // 前端设备组信息      
}CFG_VIDEOINDEVGROUP_INFO;

// 通道录像组状态
typedef struct tagCFG_DEVRECORD_INFO
{
	char                   szDevName[MAX_NAME_LEN];               // 设备名称
	char                   szIP[MAX_ADDRESS_LEN];                 // 设备IP	
	char                   szChannel[MAX_NAME_LEN];               // 通道号
    char                   szChannelName[MAX_NAME_LEN];           // 通道名称	
    char                   szStoragePosition[MAX_NAME_LEN];       // 存储位置信息
	BYTE                   byStatus;                              // 状态 0:未知 1:录像 2:停止
	BYTE                   byReserved[3];                         // 字节对齐
}CFG_DEVRECORD_INFO;

typedef struct tagCFG_DEVRECORDGROUP_INFO
{
	int                    nChannelNum;                          // 通道个数
	CFG_DEVRECORD_INFO     stuDevRecordInfo[MAX_CHAN_NUM];       // 通道录像状态信息
}CFG_DEVRECORDGROUP_INFO;

#define byDahuaII byPrivateII
#define byDahuaIId byPrivateIId

// 服务状态
typedef struct tagCFG_IPSERVER_STATUS
{
	int                    nSupportedServerNum;                  // 提供的服务个数
	char                   szSupportServer[MAX_SEVER_NUM][MAX_NAME_LEN];  // 提供的服务名称 Svr Svrd(SVR守护服务) DataBase DataBased(DataBase守护服务) NtpServer NtpServerd(NtpServer守护服务) DahuaII DahuaIId(DahuaII守护服务) Samba Nfs Ftp iScsi 
	int                    nSvrSuppSubServerNum;                          // Svr提供的子服务信息个数
	char                   szSvrSuppSubServer[MAX_SEVER_NUM][MAX_NAME_LEN];           // Svr提供的子服务信息 CMS DMS	MTS	SS RMS DBR
	BYTE                   byCMS;                                // 0:未知 1:运行 2:未运行
	BYTE                   byDMS;                                // 0:未知 1:运行 2:未运行
	BYTE                   byMTS;                                // 0:未知 1:运行 2:未运行
	BYTE                   bySS;                                 // 0:未知 1:运行 2:未运行
	BYTE                   byRMS;                                // 0:未知 1:运行 2:未运行
	BYTE                   byDBR;                                // 0:未知 1:运行 2:未运行
	BYTE                   bySvrd;                               // 0:未知 1:运行 2:未运行
	BYTE                   byDataBase;                           // 0:未知 1:运行 2:未运行
	BYTE                   byDataBased;                          // 0:未知 1:运行 2:未运行
	BYTE                   byNtpServer;                          // 0:未知 1:运行 2:未运行
	BYTE                   byNtpServerd;                         // 0:未知 1:运行 2:未运行
	BYTE                   byPrivateII;                          // 0:未知 1:运行 2:未运行
	BYTE                   byPrivateIId;                         // 0:未知 1:运行 2:未运行
	BYTE                   bySAMBA;                              // 0:未知 1:运行 2:未运行
	BYTE                   byNFS;                                // 0:未知 1:运行 2:未运行
	BYTE                   byFTP;                                // 0:未知 1:运行 2:未运行
	BYTE                   byISCSI;                              // 0:未知 1:运行 2:未运行
	BYTE                   byReserved[3];                        // 字节对齐
}CFG_IPSERVER_STATUS;

//---------------------------视频矩阵-----------------------------------
#define MAX_SUPPORT_SPLIT_MODE_NUM    16             // 支持的画面分割的能力最大数
#define MAX_MATRIX_PLAN               4              // 最大矩阵方案数
#define MAX_TOUR_MODE                 16             // 最大轮巡队列数

typedef enum tagMATRIX_VIEW_SPLITMODE
{
	MATRIX_VIEW_SPLIT1 = 0,
	MATRIX_VIEW_SPLIT2,	
	MATRIX_VIEW_SPLIT4,
	MATRIX_VIEW_SPLIT8,
	MATRIX_VIEW_SPLIT9,	
	MATRIX_VIEW_SPLIT16,
	MATRIX_VIEW_SPLITPIP,
	MATRIX_VIEW_SPLIT6,
	MATRIX_VIEW_SPLIT12,
	MATRIX_VIEW_SPLIT25,
	MATRIX_VIEW_SPLIT36,
	MATRIX_VIEW_SPLIT_NR,
}MATRIX_VIEW_SPLITMODE;

// 轮巡模式
typedef struct tagCFG_TOUR_MODE
{
	int               nViewMode;                                    // 画面分割模式,参考枚举类型MATRIX_VIEW_SPLITMODE
	unsigned int      dwViewSplitMask;                     // 表示ViewMode指定模式下,使能的几个分隔方法,使用掩码表达方式
													       // 例如:0x00000007:表示模式3(SPLIT8)的分隔1,2,3使能开启,其他未使能,0x0000000F表示分隔1,2,3,4使能
}CFG_TOUR_MODE;

// SPOT视频矩阵方案
typedef struct tagCFG_VIDEO_MATRIX_PLAN
{
	BOOL            bEnable;                                          // 矩阵配置方案使能
	int             nTourPeriod;                                      // 矩阵轮巡间隔,单位秒,>=1
	int             nTourModeNum;                                     // 轮巡队列个数
	CFG_TOUR_MODE   stuTourMode[MAX_TOUR_MODE];                       // 轮巡队列
}CFG_VIDEO_MATRIX_PLAN;

// SPOT矩阵配置
typedef struct tagCFG_VIDEO_MATRIX
{
	int                         nSupportSplitModeNumber;         // 支持的画面分割的能力数
	BYTE                        bySupportSplitMode[MAX_SUPPORT_SPLIT_MODE_NUM];          // 支持的画面分割的能力
	int                         nMatrixPlanNumber;               // 矩阵方案数
	CFG_VIDEO_MATRIX_PLAN       stuMatrixPlan[MAX_MATRIX_PLAN];                // 矩阵方案
}CFG_VIDEO_MATRIX;

///////////////////////////////////视频诊断配置///////////////////////////////////////
// 视频抖动检测
typedef struct tagCFG_VIDEO_DITHER_DETECTION
{
	BOOL							bEnable;									// 使能配置
	int								nMinDuration;								// 最短持续时间 单位：秒 0~65535
	BYTE							byThrehold1;								// 预警阀值 取值1-100
	BYTE							byThrehold2;								// 报警阀值 取值1-100
}CFG_VIDEO_DITHER_DETECTION;
// 条纹检测
typedef struct tagCFG_VIDEO_STRIATION_DETECTION 
{
	BOOL							bEnable;									// 使能配置
	int								nMinDuration;								// 最短持续时间 单位：秒 0~65535
	BYTE							byThrehold1;								// 预警阀值 取值1-100
	BYTE							byThrehold2;								// 报警阀值 取值1-100
	BYTE							byReserved1[2];								// 字节对齐
	BOOL							bUVDetection;								// UV分量是否检测					
}CFG_VIDEO_STRIATION_DETECTION;
// 视频丢失检测
typedef struct tagCFG_VIDEO_LOSS_DETECTION
{
	BOOL							bEnable;									// 使能配置
	int								nMinDuration;								// 最短持续时间 单位：秒 0~65535
}CFG_VIDEO_LOSS_DETECTION;
// 视频遮挡检测
typedef struct tagCFG_VIDEO_COVER_DETECTION
{
	BOOL							bEnable;									// 使能配置
	int								nMinDuration;								// 最短持续时间 单位：秒 0~65535
	BYTE							byThrehold1;								// 预警阀值 取值1-100
	BYTE							byThrehold2;								// 报警阀值 取值1-100
}CFG_VIDEO_COVER_DETECTION;
// 画面冻结检测
typedef struct tagCFG_VIDEO_FROZEN_DETECTION
{
	BOOL							bEnable;									// 使能配置
	int								nMinDuration;								// 最短持续时间 单位：秒 0~65535
}CFG_VIDEO_FROZEN_DETECTION;
// 亮度异常检测
typedef struct tagCFG_VIDEO_BRIGHTNESS_DETECTION
{	
	BOOL							bEnable;									// 使能配置
	int								nMinDuration;								// 最短持续时间 单位：秒 0~65535
	BYTE							bylowerThrehold1;							// 预警阀值 取值1-100
	BYTE							bylowerThrehold2;							// 报警阀值 取值1-100
	BYTE							byUpperThrehold1;							// 预警阀值 取值1-100
	BYTE							byUpperThrehold2;							// 报警阀值 取值1-100
}CFG_VIDEO_BRIGHTNESS_DETECTION;
// 对比度异常检测
typedef struct tagCFG_VIDEO_CONTRAST_DETECTION
{	
	BOOL							bEnable;									// 使能配置
	int								nMinDuration;								// 最短持续时间 单位：秒 0~65535
	BYTE							bylowerThrehold1;							// 预警阀值 取值1-100
	BYTE							bylowerThrehold2;							// 报警阀值 取值1-100
	BYTE							byUpperThrehold1;							// 预警阀值 取值1-100
	BYTE							byUpperThrehold2;							// 报警阀值 取值1-100
}CFG_VIDEO_CONTRAST_DETECTION;
// 偏色检测
typedef struct tagCFG_VIDEO_UNBALANCE_DETECTION
{	
	BOOL							bEnable;									// 使能配置
	int								nMinDuration;								// 最短持续时间 单位：秒 0~65535
	BYTE							byThrehold1;								// 预警阀值 取值1-100
	BYTE							byThrehold2;								// 报警阀值 取值1-100
}CFG_VIDEO_UNBALANCE_DETECTION;
// 噪声检测
typedef struct tagCFG_VIDEO_NOISE_DETECTION
{	
	BOOL							bEnable;									// 使能配置
	int								nMinDuration;								// 最短持续时间 单位：秒 0~65535
	BYTE							byThrehold1;								// 预警阀值 取值1-100
	BYTE							byThrehold2;								// 报警阀值 取值1-100
}CFG_VIDEO_NOISE_DETECTION;
// 模糊检测
typedef struct tagCFG_VIDEO_BLUR_DETECTION
{
	BOOL							bEnable;									// 使能配置
	int								nMinDuration;								// 最短持续时间 单位：秒 0~65535
	BYTE							byThrehold1;								// 预警阀值 取值1-100
	BYTE							byThrehold2;								// 报警阀值 取值1-100
}CFG_VIDEO_BLUR_DETECTION;
// 场景变化检测
typedef struct tagCFG_VIDEO_SCENECHANGE_DETECTION
{	
	BOOL							bEnable;									// 使能配置
	int								nMinDuration;								// 最短持续时间 单位：秒 0~65535
	BYTE							byThrehold1;								// 预警阀值 取值1-100
	BYTE							byThrehold2;								// 报警阀值 取值1-100
}CFG_VIDEO_SCENECHANGE_DETECTION;
typedef struct tagCFG_VIDEO_DIAGNOSIS_PROFILE
{
	char							szName[MAX_PATH];							// 名称Ansi编码

	CFG_VIDEO_DITHER_DETECTION*		pstDither;									// 视频抖动检测
	CFG_VIDEO_STRIATION_DETECTION*	pstStriation;								// 视频条纹检测
	CFG_VIDEO_LOSS_DETECTION*		pstLoss;									// 视频丢失检测
	CFG_VIDEO_COVER_DETECTION*		pstCover;									// 视频遮挡检测
	CFG_VIDEO_FROZEN_DETECTION*		pstFrozen;									// 视频冻结检测
	CFG_VIDEO_BRIGHTNESS_DETECTION*	pstBrightness;								// 视频亮度异常检测
	CFG_VIDEO_CONTRAST_DETECTION*	pstContrast;								// 对比度异常检测
	CFG_VIDEO_UNBALANCE_DETECTION*	pstUnbalance;								// 偏色异常检测
	CFG_VIDEO_NOISE_DETECTION*		pstNoise;									// 噪声检测
	CFG_VIDEO_BLUR_DETECTION*		pstBlur;									// 模糊检测
	CFG_VIDEO_SCENECHANGE_DETECTION* pstSceneChange;							// 场景变化检测
}CFG_VIDEO_DIAGNOSIS_PROFILE;
// 视频诊断参数表(CFG_CMD_VIDEODIAGNOSIS_PROFILE)，支持多种参数表，用表名称来索引   调用者申请内存并初始化
typedef struct tagCFG_VIDEODIAGNOSIS_PROFILE
{
	int								nTotalProfileNum;							// 调用者分配参数表数 根据能力集获取
	int								nReturnProfileNum;							// 返回的实际参数表数
	CFG_VIDEO_DIAGNOSIS_PROFILE*	pstProfiles;								// 调用者分配nProfileCount个VIDEO_DIAGNOSIS_PROFILE
}CFG_VIDEODIAGNOSIS_PROFILE;

///// 视频诊断任务
enum CFG_EM_STREAM_TYPE
{
	CFG_EM_STREAM_ERR,                  // 其它
	CFG_EM_STREAM_MAIN,					// "Main"-主码流
	CFG_EM_STREAM_EXTRA_1,				// "Extra1"-辅码流1
	CFG_EM_STREAM_EXTRA_2,				// "Extra2"-辅码流2
	CFG_EM_STREAM_EXTRA_3,				// "Extra3"-辅码流3
	CFG_EM_STREAM_SNAPSHOT,				// "Snapshot"-抓图码流
	CFG_EM_STREAM_OBJECT,				// "Object"-物体流
};

// 设备详细信息
typedef struct tagCFG_TASK_REMOTEDEVICE
{
	char                            szAddress[MAX_PATH];                        // 设备地址或域名
	unsigned int                    dwPort;                                     // 端口号
	char                            szUserName[MAX_PATH];                       // 用户名
	char                            szPassword[MAX_PATH];                       // 密码明文
	char                            szProtocolType[MAX_PATH];                   // 连接设备的协议类型
	CFG_RemoteDeviceVideoInput      *pVideoInput;                               // 视频输入通道，用户申请nMaxVideoInputs个CFG_RemoteDeviceVideoInput空间
	int				                nMaxVideoInputs;					        // 视频输入通道最大数
	int				                nRetVideoInputs;					        // 返回的视频输入通道数
}CFG_TASK_REMOTEDEVICE;

typedef struct tagCFG_TAST_SOURCES
{
	// 能力
	bool							abDeviceID;                                 // abDeviceID(使用szDeviceID) 和 abRemoteDevice(使用stRemoteDevice) 必须有一个为true，否则Sources是null
	bool							abRemoteDevice;

	char							szDeviceID[MAX_PATH];						// 设备ID
	CFG_TASK_REMOTEDEVICE           stRemoteDevice;                             // 设备详细信息
	int								nVideoChannel;								// 视频通道号
	CFG_EM_STREAM_TYPE				emVideoStream;								// 视频码流类型
	int								nDuration;									// 持续诊断时间
}CFG_TAST_SOURCES;
typedef struct tagCFG_DIAGNOSIS_TASK
{
	char							szTaskName[MAX_PATH];						// 任务名称Ansi编码
	char							szProfileName[MAX_PATH]; 					// 本任务使用的诊断参数表名Ansi编码
	int								nTotalSourceNum;						    // 调用者分配任务数据源的个数  根据能力集获取
	int								nReturnSourceNum;							// 返回实际任务数据源的个数
	CFG_TAST_SOURCES*				pstSources;									// 任务数据源 调用者分配内存nTotalSourceNum个
}CFG_DIAGNOSIS_TASK;
// 视频诊断任务表(CFG_CMD_VIDEODIAGNOSIS_TASK),不同的任务通过名子索引  调用者申请内存并初始化
typedef struct tagCFG_VIDEODIAGNOSIS_TASK
{
	int								nTotalTaskNum; 								// 调用者分配任务个数  根据能力集获取
	int								nReturnTaskNum; 							// 返回实际任务个数
	CFG_DIAGNOSIS_TASK*				pstTasks;									// 任务配置 调用者分配内存nTotalTaskNum个
}CFG_VIDEODIAGNOSIS_TASK;

// 视频诊断计划
typedef struct tagPROJECT_TASK
{
	BOOL							bEnable;									// 任务是否使能
	char							szTaskName[MAX_PATH];						// 任务名称Ansi编码
	CFG_TIME_SECTION				stTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT];	// 任务时间段
	BOOL                            bIsCycle;                                   // 任务是否循环,TRUE表示循环,FALSE表示不循环
}CFG_PROJECT_TASK;

typedef struct tagDIAGNOSIS_PROJECT
{
	char							szProjectName[MAX_PATH];					// 计划名称Ansi编码
	int								nTotalTaskNum;								// 调用者分配任务列表个数  根据能力集获取
	int								nReturnTaskNum;					    		// 返回实际任务列表个数
	CFG_PROJECT_TASK*				pstProjectTasks;								// 任务列表 调用者分配内存nTotalTaskNum个
}CFG_DIAGNOSIS_PROJECT;
// 频诊断计划表(CFG_CMD_VIDEODIAGNOSIS_PROJECT),不同的计划通过名字索引 调用者申请内存并初始化
typedef struct tagCFG_VIDEODIAGNOSIS_PROJECT
{
	int								nTotalProjectNum;							// 调用者分配计划个数  根据能力集获取
	int								nReturnProjectNum;							// 返回实际计划个数
	CFG_DIAGNOSIS_PROJECT*			pstProjects;									// 计划配置 调用者分配内存nTotalProjectNum个
}CFG_VIDEODIAGNOSIS_PROJECT;

// 实时计划相关信息
typedef struct tagCFG_DIAGNOSIS_REALPROJECT
{
	char							szProjectName[MAX_PATH];					// 计划名称Ansi编码
	CFG_DIAGNOSIS_TASK			    stProjectTask;							    // 任务信息
}CFG_DIAGNOSIS_REALPROJECT;

// 视频诊断实时计划表
typedef struct tagCFG_VIDEODIAGNOSIS_REALPROJECT 
{
	int								nProjectNum;							    // 实时计划个数
	CFG_DIAGNOSIS_REALPROJECT*		pstProjects;							    // 计划配置 调用者分配内存nProjectNum个
}CFG_VIDEODIAGNOSIS_REALPROJECT;

// 视频诊断全局表(CFG_CMD_VIDEODIAGNOSIS_GLOBAL),每个通道支持一个诊断配置 
typedef struct tagCFG_VIDEODIAGNOSIS_GLOBAL_CHNNL
{
	BOOL                            abProjectName;                              // 计划名称是否有效 
	char							szProjectName[MAX_PATH];					// 计划名称，Ansi编码
	BOOL                            abRealProjectName;                          // 实时计划名称是否有效
	char                            szRealProjectName[MAX_PATH];                // 实时计划名称，Ansi编码   
}CFG_VIDEODIAGNOSIS_GLOBAL_CHNNL;

typedef struct tagCFG_VIDEODIAGNOSIS_GLOBAL
{
	int								nTotalGlobalNum;							// 调用者分配全局配置个数  根据能力集获取
	int								nReturnGlobalNum;							// 返回实际全局配置个数
	CFG_VIDEODIAGNOSIS_GLOBAL_CHNNL	*pstGlobals;								// 视频诊断全局配置 调用者分配内存nGlobalCount个CFG_VIDEODIAGNOSIS_GLOBAL_CHNNL
}CFG_VIDEODIAGNOSIS_GLOBAL;

// 视频诊断服务能力集(CFG_CAP_CMD_VIDEODIAGNOSIS_SERVER)
typedef struct tagCFG_VIDEODIAGNOSIS_CAPS_INFO
{
	int								nTypeCount;									// 支持的视频诊断类型 个数
	char						    szSupportedType[MAX_VIDEODIAGNOSIS_DETECT_TYPE][MAX_PATH];// 支持的视频诊断类型
	int								nMaxProfiles;								// 最大参数表个数
	int								nMaxTasks;									// 最大任务个数
	int								nMaxSourcesOfTask;							// 最大单个任务的视频源个数
	int								nMaxProjects;								// 最大方案个数
}CFG_VIDEODIAGNOSIS_CAPS_INFO;

// 获取视频诊断通道数目( CFG_CMD_VIDEODIAGNOSIS_GETCOLLECT )对应结构体
typedef struct tagCFG_VIDEODIAGNOSIS_COLLECT_INFO
{
	int                             nDiagnosisChannels;                                   // 视频诊断通道数目
}CFG_VIDEODIAGNOSIS_COLLECT_INFO;

// 获取视频诊断进行状态( CFG_CMD_VIDEODIAGNOSIS_GETSTATE )对应结构体
typedef struct tagCFG_VIDEODIAGNOSIS_STATE_INFO
{
	BOOL                            bEnable;                                     // 是否使能
	BOOL                            bRunning;                                    // 是否正在运行	使能开启，并且当前有工作任务正在进行，没有错误发生。
	char                            szCurrentProject[MAX_PATH];                  // 当前计划名称
	char                            szCurrentTask[MAX_PATH];                     // 当前任务名称
	char                            szCurrentProfile[MAX_PATH];                  // 当前任务配置参数表名称
	int                             nCurrentSourceCount;                         // 当前任务轮训视频源个数
	int                             nCurrentSourceIndex;                         // 当前任务当前视频源序号	从0开始
	CFG_TIME_SECTION                stCurrentTimeSection;                        // 当前计划时间段
	int                             nTaskCountOfProject;                         // 当前计划总任务数
	int                             nIndexOfCurrentTask;                         // 当前任务序号 从0开始
}CFG_VIDEODIAGNOSIS_STATE_INFO;

// 服务器支持的服务列表
typedef struct tagCFG_DEV_SERVICE_LIST
{
	int                             nServiceNum;                                 // 支持的服务数
	char                            szService[MAX_SERVICE_NUM][MAX_NAME_LEN];    // 服务器支持具体的服务项
}CFG_DEV_SERVICE_LIST;

//获取主从式跟踪器数目
typedef struct tagCFG_MASTERSLAVETRACKER_INFO
{
        int                nStructSize;
	    int                nChannels;	//主从式跟踪器通道数目
}CFG_MASTERSLAVETRACKER_INFO;

#define  MAX_CAMERA_TYPE	64
#define	 MAX_TYPE_STRING	64

typedef struct tagCFG_CAMERA_PER_TYPE_INFO
{
	char				szCameraType[MAX_TYPE_STRING];	//相机型号
	char				szLensType[MAX_TYPE_STRING];	//相机镜头型号	镜头型号和相机型号相关，可以为空值
}CFG_CAMERA_PER_TYPE_INFO;

typedef struct tagCFG_CAMERA_TYPE_INFO
{
	int							nCameraTypeNum;						//该类型的相机所具有的不同型号数
	CFG_CAMERA_PER_TYPE_INFO	stCameraTypeInfos[MAX_CAMERA_TYPE]; //具体的型号信息
}CFG_CAMERA_TYPE_INFO;

// 变倍类型
typedef enum tagCFG_ZOOM_TYPE
{
	ZOOM_TYPE_EXPECTMULTIPLE =0,     // 固定期望倍数变倍
	ZOOM_TYPE_IVSADAPTIVE,           // 根据智能设备输出自适应变倍
	ZOOM_TYPE_MULTIPLEADAPTIVE,      // 自适应变倍
	ZOOM_TYPE_NUM
}CFG_ZOOM_TYPE;

// 跟踪模式
typedef enum tagCFG_TRACKING_MODE
{
    TRACKING_MODE_ALARM=0,        // 报警跟踪
	TRACKING_MODE_MANUALOBJECT,   // 手动选定物体跟踪
	TRACKING_MODE_AUTOOBJECT,     // 自动选定物体跟踪
	TRACKING_MODE_SELECTPOINT,    // 定点跟踪
	TRACKING_MODE_MIX,            // 混合跟踪(以上四种跟踪模式同时支持)
	TRACKING_MODE_SLAVESELF,      // 球机自主控制（主要用于用户对球机控制）
	TRACKING_MODE_NUM
}CFG_TRACKING_MODE;


// 主从式跟踪器全局配置基本结构体
typedef struct tagCFG_MASTERSLAVE_GLOBAL_INFO
{
	int						nStructSize;
	float					fMaxZoom;						// 最大变倍倍数
	float					fMinZoom;						// 最小变倍倍数
	float					fExpectMultiple;				// 期望倍数（基准倍数），最小变倍倍数<期望倍数<最大变倍倍数
	float					fPollTrackTime;					// 轮询跟踪时长，单位：秒；>0.0
	float					fPointTrackTime;				// 定点跟踪时长,单位：秒；>0.0在报警跟踪、自动选定物体跟踪、混合跟踪模式下有效
    float					fObjectTrackTime;				// 手动选定物体跟踪时长, 单位：秒；>0.0在报警跟踪、自动选定物体跟踪、混合跟踪模式下有效
	float					fExpectAngleX;					// 期望倍数对应球机角度x(水平)
    float					fExpectAngleY;					// 期望倍数对应球机角度y(垂直)
	CFG_SIZE				stTargetFaceSize;				// 靶面尺寸(单位：毫米), 球机设备参数，与球机有关
	float					fMinFocus;						// 最小焦距(单位：毫米)
	float					fMaxFocus;						// 最大焦距(单位：毫米)
	CFG_ZOOM_TYPE			emZoomType;						// 变倍类型
	CFG_TRACKING_MODE		emTrackingMode;					// 跟踪模式
	CFG_CAMERA_TYPE_INFO	stCameraInfo;					// 枪式摄像机
	CFG_CAMERA_TYPE_INFO	stDomeInfo;						// 球式摄像机
	int						nTrackZoomLevel;				// 跟踪倍数等级	-5<= TrackZoomLevel <=5 0表示用默认算法方式
	BOOL					bReturnPtzPreset;				// TRUE，跟踪后返回预置点 , FALSE，跟踪后不返回预置点
}CFG_MASTERSLAVE_GLOBAL_INFO;
	
// 获取主从式设备能力集
typedef struct tagCFG_CAP_MASTERSLAVE_INFO
{
	int                     nStructSize;
	BYTE                    byTrackingMode[TRACKING_MODE_NUM]; // 数组下标表示CFG_TRACKING_MODE枚举相对应模式，1表示支持
	CFG_CAMERA_TYPE_INFO	stCameraInfo;  // 枪式摄像机
	CFG_CAMERA_TYPE_INFO	stDomeInfo;	   // 球式摄像机
}CFG_CAP_MASTERSLAVE_INFO;


// 获取服务器报警联动能力集
typedef struct tagCFG_CAP_EVENTHANDLER_INFO
{
	BOOL				bTimeSectionEnable;                                      // 
	BOOL				bRecordEnable;                                           // 是否支持录像
	BOOL				bAlarmOutEnable;                                         // 是否支持报警输出
	BOOL				bPtzLinkEnable;                                          // 是否支持报警输出
	BOOL				bSnapshotEnable;                                         // 是否支持快照
	BOOL				bMailEnable;                                             // 是否支持发送邮件
	BOOL				bBeepEnable;                                             // 是否支持蜂鸣
	BOOL				bDejitterEnable;                                         // 是否支持去抖动
	BOOL                bTipEnable;                                              // 是否支持本地消息框提示
	BOOL                bMonitorTourEnable;                                      // 是否支持轮询联动配置
}CFG_CAP_EVENTHANDLER_INFO;

//----------------------------------视频输入配置------------------------------------------
#define DH_MAX_INMETERING_REGION_NUM 8

typedef struct tagVIDEO_INMETERING_INFO_CHANNEL
{
	// 能力
	bool            bRegion;
	bool            bMode;
	BYTE			bReserved1[2];					         // 保留字段1
	
	int				nRegionNum;                                 // 测光区域个数
	CFG_RECT    	stuRegions[DH_MAX_INMETERING_REGION_NUM];   // 测光区域, 局部测光使用，支持多个测光区域，使用相对坐标体系，取值均为0~8191
	BYTE  			byMode;				                     // 测光模式,0:平均测光,1:局部测光
	BYTE  			bReserved2[3];				             // 保留字段2
	BYTE			bReserved3[32];					         // 保留字段3
}VIDEO_INMETERING_INFO_CHANNEL;

// 测光配置(CFG_CMD_VIDEO_INMETERING)是一个数组，每个视频输入通道一个配置
typedef struct tagCFG_VIDEO_INMETERING_INFO
{
	int				nChannelNum; // 通道数
	VIDEO_INMETERING_INFO_CHANNEL	stuMeteringMode[MAX_VIDEO_CHANNEL_NUM]; // 每个通道的测光信息，下标对应通道号
}CFG_VIDEO_INMETERING_INFO;

// 视频输入能力集(CFG_CAP_CMD_VIDEOINPUT)配置
typedef struct tagCFG_CAP_VIDEOINPUT_INFO
{
	int				nMeteringRegionCount;                   // 最大测光区域个数
	BOOL            bFishEye;                               // 是否支持鱼眼
	BOOL			bElectricFocus;							// 是否支持电动调焦
	DWORD			dwExposureMode;							// 支持的自动曝光模式掩码  从低位到高位依次表示，0-自动曝光，1-低噪声（增益）优先，2-弱拖影（快门）优先， 3-50HZ防闪烁，4-60HZ防闪烁
	int             nWideDynamicRange;						// 是否支持宽动态 0-不支持，1-支持数字宽动态
	int			    nGlareInhibition;						// 是否支持强光抑制 0-不支持，1-支持
}CFG_CAP_VIDEOINPUT_INFO;

// 流量统计报警信息配置
typedef struct tagCFG_TRAFFIC_FLOWSTAT_ALARM_INFO
{
	bool                            bEnable;                              // 是否使能
	int                             nPeriod;                              // 统计周期，单位：分钟
	int                             nLimit;                               // 统计周期内车辆数上下限，单位：辆
	int                             nRestore;                             // 统计周期内报警恢复车辆数，单位：辆 
    int                             nDelay;                               // 检测到报警发生到开始上报的时间, 单位:秒,范围1~65535
	int                             nInterval;                            // 报警间隔时间, 单位:秒, 范围1~65535
	int                             nReportTimes;                         // 上报次数,1~255
	CFG_TIME_SECTION                stCurrentTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT_EX]; // 当前计划时间段
	CFG_ALARM_MSG_HANDLE            stuEventHandler;					  // 报警联动
}CFG_TRAFFIC_FLOWSTAT_ALARM_INFO;

typedef struct tagCFG_TRAFFIC_FLOWSTAT_INFO_CHNL
{
	// 能力
	bool	                		 abEnable;

	bool			                 bEnable;								// 是否使能
	CFG_TRAFFIC_FLOWSTAT_ALARM_INFO  stuAlarmUpperInfo;                     // 报警上线参数
	CFG_TRAFFIC_FLOWSTAT_ALARM_INFO  stuAlarmLowInfo;                       // 报警下线参数
    int                              nDetectRegionPoint;                    // 检测区顶点数
    CFG_POLYGON                      stuDetectRegion[MAX_POLYGON_NUM];      // 检测区域
	char                             szName[MAX_NAME_LEN];                  // 当前车道规则名称，不同规则不能重名
	int								 nPresetID;								// 云台所在预置点编号(仅球机有效)
}CFG_TRAFFIC_FLOWSTAT_INFO_LANE;

// 交通流量统计配置(CFG_CMD_TRAFFIC_FLOWSTAT)
typedef struct tagCFG_TRAFFIC_FLOWSTAT_INFO
{
	// 能力
	bool							abPeriod;
	BYTE							bReserved1[3];						        // 保留字段1

	int								nPeriod;									// 统计周期，单位分钟
	int								nLaneNum;									// 车道数
	CFG_TRAFFIC_FLOWSTAT_INFO_LANE	stuTrafficFlowstat[MAX_LANE_NUM];			// 每个车道的流量配置，下标对应车道号
	DWORD                           dwLaneExtraMaxNum;                           // 车道数扩充最大值(用于申请内存),多场景应用多余的车道信息需要
	DWORD                           dwLaneExtraRetNum;                           // 多场景应用多余的车道数实际个数
	CFG_TRAFFIC_FLOWSTAT_INFO_LANE  *pstuTrafficFlowstat;                       // 多场景的车道数, stuTrafficFlowstat数组放不开的车道在这里继续保存，序号从车道MAX_LANE_NUM+1开始
}CFG_TRAFFIC_FLOWSTAT_INFO;

//-----------------------------------视频输入前端选项-------------------------------------------

// 视频输入夜晚特殊配置选项，在晚上光线较暗时自动切换到夜晚的配置参数
typedef struct tagCFG_VIDEO_IN_NIGHT_OPTIONS
{
	BYTE				bySwitchMode;			//已废弃,使用CFG_VIDEO_IN_OPTIONS里面的bySwitchMode
                                                //0-不切换，总是使用白天配置；1-根据亮度切换；2-根据时间切换；3-不切换，总是使用夜晚配置；4-使用普通配置
	BYTE				byProfile;				// 当前使用的配置文件.
												// 0-白天
												// 1-晚上
												// 2-Normal
												// 0，1,2都为临时配置，使图像生效，便于查看图像调试效果，不点击确定，离开页面不保存至设备。
												///3-非临时配置，点击确定后保存至设备，与SwitchMode结合使用，根据SwitchMode决定最终生效的配置。
												// SwitchMode=0，Profile=3，设置白天配置到设备；
												// SwitchMode=1，Profile=3，则设置夜晚配置到设备
												// SwitchMode=2，Profile=3，根据日出日落时间段切换，白天时间段使用白天配置，夜晚时间段使用夜晚配置，保存至设备；
												// SwitchMode=4，Profile=3；使用普通配置，保存至设备
	BYTE				byBrightnessThreshold ;	// 亮度阈值 0~100	
	BYTE				bySunriseHour;			// 大致日出和日落时间，日落之后日出之前，将采用夜晚特殊的配置。
	BYTE				bySunriseMinute;		// 00:00:00 ~ 23:59:59
	BYTE				bySunriseSecond;
	BYTE				bySunsetHour;
	BYTE				bySunsetMinute;
	BYTE				bySunsetSecond;  
	BYTE				byGainRed;				// 红色增益调节，白平衡为"Custom"模式下有效 0~100
	BYTE				byGainBlue;				// 绿色增益调节，白平衡为"Custom"模式下有效 0~100
	BYTE				byGainGreen;			// 蓝色增益调节，白平衡为"Custom"模式下有效 0~100
	BYTE				byExposure;				// 曝光模式；取值范围取决于设备能力集：0-自动曝光，1-曝光等级1，2-曝光等级2…n-1最大曝光等级数 n带时间上下限的自动曝光 n+1自定义时间手动曝光 (n==byExposureEn）
	float				fExposureValue1;		// 自动曝光时间下限或者手动曝光自定义时间,毫秒为单位，取值0.1ms~80ms
	float				fExposureValue2;		// 自动曝光时间上限,毫秒为单位，取值0.1ms~80ms	
	BYTE				byWhiteBalance ;		// 白平衡, 0-"Disable", 1-"Auto", 2-"Custom", 3-"Sunny", 4-"Cloudy", 5-"Home", 6-"Office", 7-"Night", 8-"HighColorTemperature", 9-"LowColorTemperature", 10-"AutoColorTemperature", 11-"CustomColorTemperature"
	BYTE				byGain;					// 0~100, GainAuto为true时表示自动增益的上限，否则表示固定的增益值
	bool				bGainAuto;				// 自动增益
	bool				bIrisAuto;				// 自动光圈
	float               fExternalSyncPhase;     // 外同步的相位设置 0~360
	BYTE				byGainMin;				// 增益下限
	BYTE				byGainMax;				// 增益上限
	BYTE				byBacklight;			// 背光补偿：取值范围取决于设备能力集：0-关闭1-启用2-指定区域背光补偿
	BYTE				byAntiFlicker;			// 防闪烁模式 0-Outdoor 1-50Hz防闪烁 2-60Hz防闪烁
	BYTE				byDayNightColor;		// 日/夜模式；0-总是彩色，1-根据亮度自动切换，2-总是黑白
	BYTE				byExposureMode;         // 曝光模式调节 曝光等级为自动曝光时有效，取值：0-默认自动，1-增益优先，2-快门优先
	BYTE				byRotate90;				// 0-不旋转，1-顺时针90°，2-逆时针90°
	bool				bMirror;				// 镜像
	BYTE                byWideDynamicRange;     // 宽动态值 0-关闭，1~100-为真实范围值
	BYTE                byGlareInhibition;		// 强光抑制 0-关闭， 1~100为范围值
	CFG_RECT			stuBacklightRegion;     // 背光补偿区域
	BYTE                byFocusMode;            // 0-关闭，1-辅助聚焦，2-自动聚焦
	bool				bFlip;					// 翻转
	BYTE				reserved[74];			// 保留
} CFG_VIDEO_IN_NIGHT_OPTIONS;

typedef struct tagCFG_VIDEO_IN_NORMAL_OPTIONS
{
	BYTE				byGainRed;				// 红色增益调节，白平衡为"Custom"模式下有效 0~100
	BYTE				byGainBlue;				// 绿色增益调节，白平衡为"Custom"模式下有效 0~100
	BYTE				byGainGreen;			// 蓝色增益调节，白平衡为"Custom"模式下有效 0~100
	BYTE				byExposure;				// 曝光模式；取值范围取决于设备能力集：0-自动曝光，1-曝光等级1，2-曝光等级2…n-1最大曝光等级数 n带时间上下限的自动曝光 n+1自定义时间手动曝光 (n==byExposureEn）
	float				fExposureValue1;		// 自动曝光时间下限或者手动曝光自定义时间,毫秒为单位，取值0.1ms~80ms
	float				fExposureValue2;		// 自动曝光时间上限,毫秒为单位，取值0.1ms~80ms	
	BYTE				byWhiteBalance ;		// 白平衡, 0-"Disable", 1-"Auto", 2-"Custom", 3-"Sunny", 4-"Cloudy", 5-"Home", 6-"Office", 7-"Night", 8-"HighColorTemperature", 9-"LowColorTemperature", 10-"AutoColorTemperature", 11-"CustomColorTemperature"
	BYTE				byGain;					// 0~100, GainAuto为true时表示自动增益的上限，否则表示固定的增益值
	bool				bGainAuto;				// 自动增益
	bool				bIrisAuto;				// 自动光圈
	float               fExternalSyncPhase;     // 外同步的相位设置 0~360
	BYTE				byGainMin;				// 增益下限
	BYTE				byGainMax;				// 增益上限
	BYTE				byBacklight;			// 背光补偿：取值范围取决于设备能力集：0-关闭1-启用2-指定区域背光补偿
	BYTE				byAntiFlicker;			// 防闪烁模式 0-Outdoor 1-50Hz防闪烁 2-60Hz防闪烁
	BYTE				byDayNightColor;		// 日/夜模式；0-总是彩色，1-根据亮度自动切换，2-总是黑白
	BYTE				byExposureMode;         // 曝光模式调节 曝光等级为自动曝光时有效，取值：0-默认自动，1-增益优先，2-快门优先
	BYTE				byRotate90;				// 0-不旋转，1-顺时针90°，2-逆时针90°
	bool				bMirror;				// 镜像
	BYTE                byWideDynamicRange;     // 宽动态值 0-关闭，1~100-为真实范围值
	BYTE                byGlareInhibition;		// 强光抑制 0-关闭， 1~100为范围值
	CFG_RECT			stuBacklightRegion;     // 背光补偿区域
	BYTE                byFocusMode;            // 0-关闭，1-辅助聚焦，2-自动聚焦
	bool				bFlip;					// 翻转
	BYTE				reserved[74];			// 保留
}CFG_VIDEO_IN_NORMAL_OPTIONS;



// 闪光灯配置
typedef struct tagCFG_FLASH_CONTROL
{
	BYTE				byMode;					// 工作模式，0-禁止闪光，1-始终闪光，2-自动闪光
	BYTE				byValue;				// 工作值, 0-0us, 1-64us, 2-128us, 3-192...15-960us
	BYTE				byPole;					// 触发模式, 0-低电平 1-高电平 2-上升沿 3-下降沿
	BYTE                byPreValue;				// 亮度预设值  区间0~100
	BYTE				byDutyCycle;			// 占空比, 0~100
	BYTE				byFreqMultiple;			// 倍频, 0~10
	BYTE				reserved[122];			// 保留
}CFG_FLASH_CONTROL;

// 抓拍参数特殊配置
typedef struct tagCFG_VIDEO_IN_SNAPSHOT_OPTIONS
{
	BYTE				byGainRed;				// 红色增益调节，白平衡为"Custom"模式下有效 0~100
	BYTE				byGainBlue;				// 绿色增益调节，白平衡为"Custom"模式下有效 0~100
	BYTE				byGainGreen;			// 蓝色增益调节，白平衡为"Custom"模式下有效 0~100
	BYTE				byExposure;				// 曝光模式；取值范围取决于设备能力集：0-自动曝光，1-曝光等级1，2-曝光等级2…n-1最大曝光等级数 n带时间上下限的自动曝光 n+1自定义时间手动曝光 (n==byExposureEn）
	float				fExposureValue1;		// 自动曝光时间下限或者手动曝光自定义时间,毫秒为单位，取值0.1ms~80ms
	float				fExposureValue2;		// 自动曝光时间上限,毫秒为单位，取值0.1ms~80ms	
	BYTE				byWhiteBalance;			// 白平衡, 0-"Disable", 1-"Auto", 2-"Custom", 3-"Sunny", 4-"Cloudy", 5-"Home", 6-"Office", 7-"Night", 8-"HighColorTemperature", 9-"LowColorTemperature", 10-"AutoColorTemperature", 11-"CustomColorTemperature"
	BYTE				byColorTemperature;		// 色温等级, 白平衡为"CustomColorTemperature"模式下有效
	bool				bGainAuto;				// 自动增益
	BYTE				byGain;					// 增益调节, GainAuto为true时表示自动增益的上限，否则表示固定的增益值
	BYTE				reversed[112];			// 保留
} CFG_VIDEO_IN_SNAPSHOT_OPTIONS;

// 鱼眼矫正模式
typedef enum
{
    CFG_CALIBRATE_MODE_UNKOWN,                  // 未知模式 
    CFG_CALIBRATE_MODE_ORIGIAL,                 // 原始图像模式
    CFG_CALIBRATE_MODE_CONFIG,                  // 配置模式
    CFG_CALIBRATE_MODE_PANORAMA,                // 全景模式
    CFG_CALIBRATE_MODE_DOUBLEPANORAMA,          // 双全景模式
    CFG_CALIBRATE_MODE_ORIGIALPLUSTHREEEPTZREGION, // 1+3模式（一个原始鱼眼图像加3个EPtz图像）
    CFG_CALIBRATE_MODE_SINGLE,                  // 单画面EPtz模式（只有一个EPtz画面）
    CFG_CALIBRATE_MODE_FOUREPTZREGION,          // 4画面模式（4个EPtz控制画面）
    CFG_CALIBRATE_MODE_NORMAL,                  // 普通模式
}CFG_CALIBRATE_MODE;

// 鱼眼镜头配置
typedef struct tagCFG_FISH_EYE
{
    CFG_POLYGON         stuCenterPoint;         // 鱼眼圆心坐标,范围[0,8192]
	unsigned int        nRadius;                // 鱼眼半径大小,范围[0,8192]
	float               fDirection;             // 镜头旋转方向,旋转角度[0,360.0]
	BYTE                byPlaceHolder;          // 镜头安装方式	1顶装，2壁装；3地装,默认1
    BYTE                byCalibrateMode;        // 鱼眼矫正模式,详见CFG_CALIBRATE_MODE枚举值
	BYTE				reversed[31];			// 保留
}CFG_FISH_EYE;
// 视频输入前端选项
typedef struct tagCFG_VIDEO_IN_OPTIONS
{
	BYTE				byBacklight;			// 背光补偿：取值范围取决于设备能力集：0-关闭1-启用2-指定区域背光补偿
	BYTE				byDayNightColor;		// 日/夜模式；0-总是彩色，1-根据亮度自动切换，2-总是黑白
	BYTE				byWhiteBalance;			// 白平衡, 0-"Disable", 1-"Auto", 2-"Custom", 3-"Sunny", 4-"Cloudy", 5-"Home", 6-"Office", 7-"Night", 8-"HighColorTemperature", 9-"LowColorTemperature", 10-"AutoColorTemperature", 11-"CustomColorTemperature"
	BYTE				byColorTemperature;		// 色温等级, 白平衡为"CustomColorTemperature"模式下有效
	bool				bMirror;				// 镜像
	bool				bFlip;					// 翻转
	bool				bIrisAuto;				// 自动光圈
	bool				bInfraRed;				// 根据环境光自动开启红外补偿灯	
	BYTE				byGainRed;				// 红色增益调节，白平衡为"Custom"模式下有效 0~100
	BYTE				byGainBlue;				// 绿色增益调节，白平衡为"Custom"模式下有效 0~100
	BYTE				byGainGreen;			// 蓝色增益调节，白平衡为"Custom"模式下有效 0~100
	BYTE				byExposure;				// 曝光模式；取值范围取决于设备能力集：0-自动曝光，1-曝光等级1，2-曝光等级2…n-1最大曝光等级数 n带时间上下限的自动曝光 n+1自定义时间手动曝光 (n==byExposureEn）
	float				fExposureValue1;		// 自动曝光时间下限或者手动曝光自定义时间,毫秒为单位，取值0.1ms~80ms
	float				fExposureValue2;		// 自动曝光时间上限,毫秒为单位，取值0.1ms~80ms	
	bool				bGainAuto;				// 自动增益
	BYTE				byGain;					// 增益调节, GainAuto为true时表示自动增益的上限，否则表示固定的增益值
	BYTE				bySignalFormat;			// 信号格式, 0-Inside(内部输入) 1-BT656 2-720p 3-1080p  4-1080i  5-1080sF
	BYTE				byRotate90;				// 0-不旋转，1-顺时针90°，2-逆时针90°	
	float               fExternalSyncPhase;		// 外同步的相位设置 0~360	
	BYTE                byExternalSync;			// 外部同步信号输入,0-内部同步 1-外部同步
	BYTE				bySwitchMode;			//0-不切换，总是使用白天配置；1-根据亮度切换；2-根据时间切换；3-不切换，总是使用夜晚配置；4-使用普通配置
	BYTE				byDoubleExposure;		// 双快门, 0-不启用，1-双快门全帧率，即图像和视频只有快门参数不同，2-双快门半帧率，即图像和视频快门及白平衡参数均不同
	BYTE                byWideDynamicRange;     // 宽动态值
	CFG_VIDEO_IN_NIGHT_OPTIONS stuNightOptions;	// 夜晚参数
	CFG_FLASH_CONTROL	stuFlash;				// 闪光灯配置
	CFG_VIDEO_IN_SNAPSHOT_OPTIONS stuSnapshot;	// 抓拍参数, 双快门时有效
	CFG_FISH_EYE        stuFishEye;             // 鱼眼镜头
	BYTE                byFocusMode;            // 0-关闭，1-辅助聚焦，2-自动聚焦
	BYTE                reserved[28];           // 保留
	BYTE				byGainMin;				// 增益下限
	BYTE				byGainMax;				// 增益上限
	BYTE				byAntiFlicker;			// 防闪烁模式 0-Outdoor 1-50Hz防闪烁 2-60Hz防闪烁
	BYTE				byExposureMode;         // 曝光模式调节 曝光等级为自动曝光时有效，取值：0-默认自动，1-增益优先，2-快门优先,4-手动
	BYTE                byGlareInhibition;		// 强光抑制 0-关闭， 1~100为范围值
	CFG_RECT			stuBacklightRegion;     // 背光补偿区域            
	CFG_VIDEO_IN_NORMAL_OPTIONS stuNormalOptions;//普通参数
} CFG_VIDEO_IN_OPTIONS;

// RTSP输入参数和输出参数配置结构体
typedef struct tagCFG_MULTICAST_INFO
{
	int  nStructSize;
	bool abStreamType;
	BYTE byReserved[3];
	BOOL bEnable;      // 是否使能
	char szMulticastAddr[MAX_ADDRESS_LEN]; //组播地址
	int  nPort;        //组播端口
	char szLocalAddr[MAX_ADDRESS_LEN];   //单播地址，用于组播指定详细网卡
	int  nChannelID;   // 通道号
	int  nStreamType;  // 码流类型 0-主码流, 1-辅码流1,2-辅码流2,3-辅码流3
}CFG_MULTICAST_INFO;

typedef struct tagCFG_MULTICASTS_INFO
{
	int nStructSize;
	CFG_MULTICAST_INFO stuMultiInfo[MAX_CHAN_NUM]; //最大组播配置
	int nCount;                                    //有效数组个数
}CFG_MULTICASTS_INFO;

typedef struct tagCFG_RTSP_INFO_IN
{
	int         nStructSize;
	BOOL        bEnable;       // 整个功能是否使能
	int         nPort;         // RTSP服务端口
	int         nRtpStartPort; // RTP起始端口
	int         nRtpEndPort;   // RTP结束端口
	BOOL        bHttpEnable;   // RtspOverHttp使能
	int         nHttpPort;     // RtspOverHttp端口
}CFG_RTSP_INFO_IN;

typedef struct tagCFG_RTSP_INFO_OUT
{
	int         nStructSize;
	BOOL        bEnable;       // 整个功能是否使能
	int         nPort;         // RTSP服务端口
	int         nRtpStartPort; // RTP起始端口
	int         nRtpEndPort;   // RTP结束端口
	BOOL        bHttpEnable;   // RtspOverHttp使能
	int         nHttpPort;     // RtspOverHttp端口
}CFG_RTSP_INFO_OUT;

typedef struct tagCFG_MULTICASTS_INFO_IN
{
	int                  nStructSize;
	CFG_MULTICAST_INFO   *pTSMulticast;   //TS的组播配置
	int                  nTSCount;        //有效TS数组个数
	CFG_MULTICAST_INFO   *pRTPMulticast;  //RTP的组播配置
	int                  nRTPCount;       //有效RTP数组个数
	CFG_MULTICAST_INFO   *pDHIIMulticast; //DHII的组播配置
	int                  nDHIICount;      //有效DHII数组个数
}CFG_MULTICASTS_INFO_IN;

typedef struct tagCFG_MULTICASTS_INFO_OUT
{
	int                  nStructSize;
	CFG_MULTICASTS_INFO  stuTSMulticast;   //TS的组播配置
	CFG_MULTICASTS_INFO  stuRTPMulticast;  //RTP的组播配置
	CFG_MULTICASTS_INFO  stuDHIIMulticast; //DHII的组播配置
}CFG_MULTICASTS_INFO_OUT;

typedef struct tagCFG_ACTIVEUSER_INFO
{
	int nStructSize;
	int nUserID;                         //活动用户ID，一般是会话ID
	char szUser[MAX_USERNAME_LEN];       // 用户名
	char szGroupName[MAX_USERNAME_LEN];  // 用户所在组名
	int  nGroupLevel;                    // 用户所在组等级
	char szClientType[MAX_USERNAME_LEN]; // 客户端类型
	char szClientAddr[MAX_ADDRESS_LEN];  // 客户端IP地址
	CFG_NET_TIME  stuLoginTime;              // 用户登入时间
}CFG_ACTIVEUSER_INFO;

typedef struct tagCFG_ACTIVEALLUSER_INFO
{
	int nStructSize;
	int nCount;                                                //有效数组个数
	CFG_ACTIVEUSER_INFO stuActiveUserInfo[MAX_ACTIVEUSER_NUM]; //  最大活动用户列表
}CFG_ACTIVEALLUSER_INFO;

typedef struct tagCFG_NET_TIME_EX
{
	DWORD				dwYear;					// 年
	DWORD				dwMonth;				// 月
	DWORD				dwDay;					// 日
	DWORD				dwHour;					// 时
	DWORD				dwMinute;				// 分
	DWORD				dwSecond;				// 秒
	DWORD               dwMillisecond;          // 毫秒
	DWORD               dwReserved[2];          // 保留字段
} CFG_NET_TIME_EX;

//获取视频统计摘要信息结构体
typedef struct tagCFG_CFG_VIDEOSATA_SUMMARY_INFO
{
	int         nStructSize;
	int         nChannelID;               //统计通道号
	char        szRuleName[MAX_NAME_LEN]; //规则名称
	CFG_NET_TIME_EX stuStatTime;          // 统计时间，转换到UTC
	int         nEnteredTotal;            //进入总计
	int         nEnteredToday;            //今天进入总计
	int         nEnteredMonth;            //本月进入总计
	int         nEnteredYear;             //今年进入总计
	int         nEnteredDaily;            //每日最大进入总计
	int         nExitedTotal;             //出去总计
	int         nExitedToday;             //今天出去总计
	int         nExitedMonth;             //本月出去总计
	int         nExitedYear;              //今年出去总计
	int         nExitedDaily;             //每日最大出去总计
	int         nAvgTotal;                //平均所有保有统计(除去零值)
	int         nAvgToday;                //平均今天保有统计
	int         nAvgMonth;                //平均本月保有统计
	int         nAvgYear;                 //平均今年保有统计         
	int         nMaxTotal;                //最大所有保有统计(除去零值)
	int         nMaxToday;                //最大今天保有统计
	int         nMaxMonth;                //最大本月保有统计
	int         nMaxYear;                 //最大今年保有统计
}CFG_VIDEOSATA_SUMMARY_INFO;

// 单场景跟踪结构体
typedef struct tagCFG_SINGLESCENE
{
	int                 nStructSize;
	int					nSingleAlarmDelay;					//报警延时:1~600秒
	int					nSinglePresetID;					//预置点编号：1~255(-1代表无定义)
}CFG_SINGLESCENE;
// 巡航路径结构体
typedef struct tagCFG_TOURPATH
{
	int                 nStructSize;
	int					nMultiPresetID;						//场景预置点编号
	int					nMultiDuration;						//停留时间30~900秒
}CFG_TOURPATH;
// 多场景跟踪结构体
typedef struct tagCFG_MULTISCENE
{
	int                 nStructSize;
	int					nMultiAlarmDelay;					    //报警延时：1~600秒
	int					nTourPathCount;						    //巡航路径个数
	CFG_TOURPATH	    stuMultiTourPath[MAX_TRACKSCENE_NUM];   //巡航路径
}CFG_MULTISCENE;
// 全场景跟踪结构体
typedef struct tagCFG_FULLSCENE
{
	int                 nStructSize;
	int					nFullAlarmDelay;					//报警延时：1~600秒
	int					nFullPresetID;						//预置点编号,全景跟踪预置点固定为0，用户不可设置
	int					nFullDuration;						//全景跟踪持续时间,0秒: 一直跟踪;1~300:跟踪持续时间
}CFG_FULLSCENE;
// 限位参数结构体
typedef struct tag_CFG_POSITION_LIMIT
{
	int                 nStructSize;
	BOOL				bEnable;							//启用限位参数
	int					nType;								//限位值表述方式：0: 由云台在限位设置操作时保存数据，限位值数据无意义
	                                                        //1：限位值用角度(单位0.1度)表示，用该值设置该场景的限位
	int					nTop;								//上限位值, 0~900:（单位0.1度）
	int					nBottom;							//下限位值：0~900:（单位0.1度）
	int					nLeft;								//左限位值：0~3600:（单位0.1度）
	int					nRight;								//右限位值：0~3600:（单位0.1度）
}CFG_POSITION_LIMIT;
// 场景信息结构体
typedef struct tagCFG_SCENE
{
	int                    nStructSize;
	int					   nScenePresetID;						//场景预置点，1~255，通过预置点编号关联到对应规则上
	char			       szSceneName[MAX_NAME_LEN];		    //场景名
	int					   nSceneDuration;						//跟踪持续时间:0秒: 一直跟踪;1~300:跟踪持续时间
	double		           dSceneMaxZoom;					    //归一化到0~1;为null表示使用全局MaxZoom值
	CFG_POSITION_LIMIT	   stuPositionLimit;                    //限位参数
    int                    nSceneRegression;                    //归位时间，1~10秒:跟踪丢失后回到原场景的时间
}CFG_SCENE;
// 智能跟踪场景配置结构体
typedef struct tagCFG_INTELLITRACKSCENE_INFO
{
	int               nStructSize;
	BOOL		      bEnableTrack;				         //启用智能跟踪
	int				  nTrackType;						 //0,报警跟踪；1，手动跟踪
	double			  dMaxZoom;							 //最大跟踪倍率，归一化到0~1，为null表示无限制
	char			  szCategory[MAX_NAME_LEN];		     //当前跟踪类型，"SingleScene"：单场景跟踪；"MultiScene"：多场景跟踪；"FullScene"：全景跟踪
	CFG_SINGLESCENE   stuSingleTrack;					 //单场景跟踪
	CFG_MULTISCENE	  stuMultiTrack;	                 //多场景跟踪
	CFG_FULLSCENE	  stuFullTrack;						 //全景跟踪
	int				  nSceneCount;						 //支持的场景个数
	CFG_SCENE		  stuScene[MAX_TRACKSCENE_NUM];	     //场景列表
}CFG_INTELLITRACKSCENE_INFO;

// 鱼眼详细配置

#define   CFG_MAX_FISHEYE_WINDOW_NUM               8         // 最大鱼眼窗口数
#define   CFG_MAX_FISHEYE_MODE_NUM                 8         // 最大鱼眼模式数   
// 鱼眼窗口位置信息
typedef struct tagCFG_FISHEYE_WINDOW_INFO
{
    DWORD             dwWindowID;                        // 窗口ID
    int               nFocusX;                           // EPtz（电子云台）的焦点横坐标
    int               nFocusY;                           // EPtz (电子云台）的焦点纵坐标   
    int               nHorizontalAngle;                  // EPtz的水平角度
    int               nVerticalAngle;                    // EPtz的垂直角度
}CFG_FISHEYE_WINDOW_INFO;

// 鱼眼各模式的窗口位置信息
typedef struct tagCFG_FISHEYE_MODE_INFO
{
    int                nModeType;                        // 模式类型，详见 CFG_CALIBRATE_MODE
    int                nWindowNum;                       // 当前模式下的窗口数
    CFG_FISHEYE_WINDOW_INFO stuWindwos[CFG_MAX_FISHEYE_WINDOW_NUM]; // 具体窗口信息 
}CFG_FISHEYE_MODE_INFO;

typedef struct tagCFG_FISHEYE_DETAIL_INFO
{
    int                nModeNum;                         // 模块数
    CFG_FISHEYE_MODE_INFO stuModes[CFG_MAX_FISHEYE_MODE_NUM]; // 具体模块信息  
}CFG_FISHEYE_DETAIL_INFO;

// 平台下发呼叫无应答转移配置列表
#define   CFG_MAX_NOANSWER_FORWARD_GROUP_NUM                    32         // 最大无应答前转列表个数
#define   CFG_MAX_FORWARD_NUMBERS_NUM                           32         // 最大无应答转移号码个数

// 无应答转移配置
typedef struct tagCFG_VT_NOANSWER_FORWARD_GROUP
{
    char                    szRoomNumber[CFG_COMMON_STRING_32];          // 被呼叫号码
    int                     nForwardNumbersNum;                          // 无应答转移号码个数
    char                    szForwardNumbers[CFG_MAX_FORWARD_NUMBERS_NUM][CFG_COMMON_STRING_64]; // 无应答转移号码列表  
}CFG_VT_NOANSWER_FORWARD_GROUP;

// 平台下发呼叫无应答转移配置列表信息
typedef struct tagCFG_VT_NOANSWER_FORWARD_INFO
{
    BOOL                            bEnable;                                        // 无应答转移使能
    int                             nGroupNum;                                      // 无应答转移配置列表有效个数，范围：0 ~ CFG_MAX_NOANSWER_FORWARD_GROUP_NUM
    CFG_VT_NOANSWER_FORWARD_GROUP   stuGroups[CFG_MAX_NOANSWER_FORWARD_GROUP_NUM];  // 无应答转移配置列表  
}CFG_VT_NOANSWER_FORWARD_INFO;

// VTO呼叫配置
typedef struct tagCFG_VTO_CALL_INFO
{
    BOOL                            bAreaEnable;                                        // 跨区域联网使能
    char                            szAreaNumber[CFG_COMMON_STRING_32];                  // 区域编码
    BOOL                            bMiddleNumberCallEnable;                            // 中号呼叫开关
    char                            szVTHMiddleNumberPrefix[CFG_COMMON_STRING_16];       // VTH中号前缀，固定长度4位
    char                            szVTHLongNumberPrefix[CFG_COMMON_STRING_32];         // VTH长号前缀，固定长度8位
    char                            szVTOShortNumber[CFG_COMMON_STRING_16];              // VTO短号，固定长度4位
    char                            szVTOMiddleNumberPrefix[CFG_COMMON_STRING_16];       // VTO中号前缀，固定长度4位
    char                            szVTOLongNumbrPrefix[CFG_COMMON_STRING_32];          // VTO长号前缀，固定长度12位
    char                            szVTSLongNumber[CFG_COMMON_STRING_32];               // VTS长号，固定长度18位
    char                            szVillaCallVTHNum[CFG_COMMON_STRING_32];             // 别墅机呼叫号码
}CFG_VTO_CALL_INFO;

/************************工作状态配置**********************************/

// 抓拍模式
typedef enum tagCFG_TRAFFIC_SNAP_MODE
{
	TRAFFIC_SNAP_MODE_AUTO = 0,				       // 自动抓拍
	TRAFFIC_SNAP_MODE_COIL,				           // 线圈抓拍
	TRAFFIC_SNAP_MODE_COIL_PICANALYSIS,		       // 线圈抓拍, 图片分析
	TRAFFIC_SNAP_MODE_STREAM,				       // 视频抓拍
	TRAFFIC_SNAP_MODE_STREAM_IDENTIFY,		       // 视频抓拍, 并且识别
	TRAFFIC_SNAP_MODE_MIX_IDENTIFY,		           // 混合抓拍, 并且识别
} CFG_TRAFFIC_SNAP_MODE;

// 设备工作状态信息
typedef struct tagCFG_TRAFFIC_WORKSTATE_INFO
{
	int                     nChannelID;  // 通道号
	CFG_TRAFFIC_SNAP_MODE   emSnapMode;  // 抓拍模式
	int                     nMatchMode;  // 抓拍匹配模式: 0-非实时匹配方式，先报警后抓拍，抓拍帧不是报警帧;  1-实时匹配模式，报警帧和抓拍帧是同一帧 
}CFG_TRAFFIC_WORKSTATE_INFO;

// 获取设备工作状态是否正常(CFG_CAP_CMD_DEVICE_STATE 对应的结构体)
typedef struct tagCFG_TRAFFIC_DEVICE_STATUS
{
	char                 szType[MAX_PATH];          // 设备类型	支持："Radar","Detector","SigDetector"
	char                 szSerialNo[MAX_PATH];      // 设备编号
	char                 szVendor[MAX_PATH];        // 生产厂商
	int                  nWokingState;              // 工作状态	0-故障,1-正常工作
}CFG_TRAFFIC_DEVICE_STATUS;

typedef struct tagCFG_CAP_TRAFFIC_DEVICE_STATUS
{
	int                        nStatus;             // stuStatus 实际个数
	CFG_TRAFFIC_DEVICE_STATUS  stuStatus[MAX_STATUS_NUM];
}CFG_CAP_TRAFFIC_DEVICE_STATUS;

/************************录像盘组配置**********************************/

// 存储组信息
typedef struct tagCFG_STORAGEGROUP_INFO
{
	char                  szGroupName[MAX_STORAGEGROUPNAME_LEN];   // 存储组名称
	BYTE*                 byDisks;                                 // 物理磁盘序号缓冲区
	int                   nBufSize;                                // 缓冲区byDisks的长度
	int                   nDiskNum;                                // 存储组中的磁盘数
	int                   nGroupIndex;                             // 存储组序号(1~最大硬盘数)
}CFG_STORAGEGROUP_INFO;

// 录像-存储组 对应信息
typedef struct tagCFG_RECORDTOGROUP_INFO
{
	int                   nChannelID;                               // 通道号
	BOOL                  bEnable;                                  // 使能                       
	char                  szGroupName[MAX_STORAGEGROUPNAME_LEN];    // 存储组名称, 只读
	int                   nGroupIndex;                              // 存储组序号(1~最大盘组, 0则表示无对应盘组)，通过此参数与CFG_STORAGE_GROUP_INFO关联
}CFG_RECORDTOGROUP_INFO;

enum EM_STORAGEPOINT_TYPE
{
       	EM_STORAGE_TIMINGRECORD,        //定时录像存储点类型
		EM_STORAGE_MANUALRECORD,        //手动录像存储点类型
		EM_STORAGE_VIDEODETECTRECORD,   //视频检测录像存储点类型
		EM_STORAGE_ALARMRECORD,         //报警录像存储点类型
		EM_STORAGE_CARDRECORD,          //卡号录像存储点类型
		EM_STORAGE_EVENTRECORD,         // 其他事件录像存储点类型                
		EM_STORAGE_TIMINGSNAPSHOT,      // 定时抓图存储点类型
		EM_STORAGE_MANUALSNAPSHOT,      // 手动抓图存储点类型
		EM_STORAGE_VIDEODETECTSNAPSHOT, // 视频检测抓图存储点类型
		EM_STORAGE_ALARMSNAPSHOT,       // 报警抓图存储点类型
		EM_STORAGE_CARDSNAPSHOT,        // 卡号抓图存储点类型
		EM_STORAGE_EVENTSNAPSHOT,       // 其他事件抓图存储点类型
};
// 存储点配置信息
typedef struct tagCFG_STORAGEPOINT_INFO
{
	DWORD dwSize;
	EM_STORAGEPOINT_TYPE emStoragePointType;// 存储点类型
	char nLocalDir;                         //本地工作目录组名称, 空表示不录到本地
	char szCompressDir[MAX_DIRECTORY_LEN];  //实时压缩存储目录组，空表示不使用实时压缩存储。
	char szRedundantDir[MAX_DIRECTORY_LEN]; //冗余工作目录组名称,空表示没有冗余录像。
	char szRemoteDir[MAX_DIRECTORY_LEN];   //远程工作目录组名称,空表示不录到远程。
	BOOL bAutoSync;                         //远程存储网络故障恢复后，是否自动将本地存储的数据同步到远程存储。
	UINT nAutoSyncRange;                    //从网络恢复的时刻开始，需要往前同步的数据时间范围，小时为单位，0表示同步所有数据。
	BOOL bLocalEmergency;                   //远程目录无法访问时，是否保存到本地目录。
	UINT nCompressBefore;                   //设置将多少天之前的录像文件进行压缩。
}CFG_STORAGEPOINT_INFO;

// 录像存储点映射配置信息
typedef struct tagCFG_RECORDTOSTORAGEPOINT_INFO
{
	int	nStoragePointNum;                                        //存储点数目
	CFG_STORAGEPOINT_INFO stStoragePoints[MAX_STORAGEPOINT_NUM]; // 存储点配置信息
}CFG_RECORDTOSTORAGEPOINT_INFO;

//iscsi直存，元数据服务器配置接口
typedef struct __tagCFG_METADATA_SERVER
{
	DWORD       nStructSize;
	BOOL        bEnable;                              //使能开关
	char        szAddress[MAX_ADDRESS_LEN];           //IP地址或网络名
	DWORD       dwPort;                               //端口号
	char        szUserName[MAX_USERNAME_LEN];         //帐户名  
	char        szPassword[MAX_PASSWORD_LEN];         //密码
	char        szDeviceID[MAX_REMOTEDEVICENAME_LEN]; //为使用元数据服务器的设备统一分配的ID，设备以此ID标识自己
}CFG_METADATA_SERVER;

// 车载货重配置
typedef struct __tagCFG_GOOD_WEIGHT_INFO
{
	DWORD		dwMaxGoodsWeight;					// 最大货重(kg)
	DWORD		dwMinGoodsWeight;					// 最小货重(kg)
	DWORD		dwSelfWeight;						// 自重(kg)
	DWORD		dwStandardWeight;					// 核重(kg)
	DWORD		dwAlarmWeight;						// 报警阈值(kg)
	int			nCheckTime;							// 静止采集时间(s)
} CFG_GOOD_WEIGHT_INFO;

//镜头聚焦状态信息
typedef struct tagCFG_CAP_FOCUS_STATUS
{
	int					nAutofocusPeak;							// 当前AF峰值	辅助聚焦模式下有效
	double		        dFocus;									// 聚焦位置	归一化到0~1
	double		        dZoom;									// 放大倍数	归一化到0~1
	int					nStatus;								// 聚焦状态, 0 正常状态 1 正在自动聚焦
}CFG_CAP_FOCUS_STATUS;

//云台支持能力信息
typedef struct tagCFG_CAP_PTZ_ENABLEINFO 
{
	BOOL bEnable;												//该通道是否支持云台
	
}CFG_CAP_PTZ_ENABLEINFO;


// 网络应用能力集
typedef struct tagCFG_CAP_NETAPP
{
	int                nNetCardCount;                           // 网卡数量
	int                nNetTypeNumber;                          // 网络类型个数
	char               szNetType[MAX_NET_TYPE_NUM][MAX_NET_TYPE_LEN]; // 具体网络类型, "PPPoE"，"WIFI"，"3G"，"LAN"
}CFG_CAP_NETAPP;



///////////////////////////////////三代协议新增///////////////////////////////////////
// 录像模式
struct AV_CFG_RecordMode
{
	AV_int32			nStructSize;
	AV_int32			nMode;							// 录像模式, 0-自动录像，1-手动录像，2-关闭录像
};

// 通道名称
struct AV_CFG_ChannelName
{
	AV_int32			nStructSize;
	AV_int32			nSerial;						// 摄像头唯一编号
	char				szName[AV_CFG_Channel_Name_Len];// 通道名
};

// 视频输出属性
struct AV_CFG_VideoOutAttr
{
	AV_int32			nStructSize;
	AV_int32			nMarginLeft;					// 左边距, 比率, 0~100
	AV_int32			nMarginTop;						// 上边距, 比率, 0~100
	AV_int32			nMarginRight;					// 右边距, 比率, 0~100
	AV_int32			nMarginBottom;					// 下边距, 比率, 0~100
	AV_int32			nBrightness;					// 亮度, 0~100
	AV_int32			nContrast;						// 对比度, 0~100
	AV_int32			nSaturation;					// 饱和度, 0~100
	AV_int32			nHue;							// 色调, 0~100
	AV_int32			nWidth;							// 水平分辨率
	AV_int32			nHeight;						// 垂直分辨率
	AV_int32			nBPP;							// 颜色深度
	AV_int32			nFormat;						// 0-Auto, 1-TV, 2-VGA, 3-DVI
	AV_int32			nRefreshRate;					// 刷新频率
	AV_BOOL				bIQIMode;						// 输出图像增强
	AV_int32			nScanFormat;					// 扫描模式, 0-逐行, 1-隔行
};

// 时间段
struct AV_CFG_TimeSection
{
	AV_int32			nStructSize;
	AV_int32			nMask;							// 掩码
	AV_int32			nBeginHour;						// 开始时间
	AV_int32			nBeginMinute;
	AV_int32			nBeginSecond;
	AV_int32			nEndHour;						// 结束时间
	AV_int32			nEndMinute;
	AV_int32			nEndSecond;
};

// 远程通道
struct AV_CFG_RemoteChannel 
{
	AV_int32			nStructSize;
	AV_BOOL				bEnable;						// 使能
	char				szDeviceID[AV_CFG_Device_ID_Len];	// 设备ID
	AV_int32			nChannel;						// 通道号
};

// 显示源
struct AV_CFG_DisplaySource 
{
	AV_int32			nStructSize;
	AV_int32			nWindowID;						// 窗口ID
	AV_BOOL				bEnable;						// 使能
	char				szDeviceID[AV_CFG_Device_ID_Len];// 设备ID
	AV_int32			nVideoChannel;					// 视频通道号
	AV_int32			nVideoStream;					// 视频码流
	AV_int32			nAudioChannle;					// 音频通道号
	AV_int32			nAudioStream;					// 音频码流
	AV_BOOL				bVideoEnable;			        // 表示该窗口是否有视频源
};

// 通道分割显示源
struct AV_CFG_ChannelDisplaySource 
{
	AV_int32			nStructSize;
	AV_int32			nWindowNum;						// 分割窗口数量
	AV_CFG_DisplaySource stuSource[AV_CFG_Max_Split_Window];// 分割窗口显示源
};

// 画面轮训下分割模式的分组使能状态
struct AV_CFG_MonitorTourMask
{
	AV_int32			nStructSize;
	CFG_SPLITMODE		emSplitMode;					// 分割模式
	AV_int32			nGroupNum;						// 分组数量
	AV_int32			nGroup[AV_CFG_Max_Split_Group];	// 该分割模式下加入轮训的分组
};

// 画面轮训
struct AV_CFG_MonitorTour 
{
	AV_int32			nStructSize;
	AV_BOOL				bEnable;						// 使能
	AV_int32			nInterval;						// 时间间隔, 5~120s
	AV_int32			nSplitMaskNum;					// 分割分组使能数量
	AV_CFG_MonitorTourMask	stuSplitMask[AV_CFG_Max_Split_Mode];// 各分割模式对应的分组使能状态
	AV_int32			nCollectionNum;					// 收藏数量
	char				szCollection[AV_CFG_Monitor_Favorite_In_Channel][AV_CFG_Monitor_Favorite_Name_Len];// 画面收藏名称
};

// 监视画面收藏
struct AV_CFG_MonitorFavorite 
{
	AV_int32			nStructSize;
	AV_BOOL				bDir;										// 是否为目录	
	char				szName[AV_CFG_Monitor_Favorite_Name_Len];	// 名称
	char				szPath[AV_CFG_Max_Path];					// 目录路径, 格式如下: .name1.name2.name3
	CFG_SPLITMODE		emMode;										// 分割模式
	AV_int32			nWindowNum;									// 窗口数量
	AV_CFG_DisplaySource stuWindow[AV_CFG_Max_Monitor_Favorite_Window];	// 窗口显示源配置
};

// 监视画面收藏集合
struct AV_CFG_MonitorCollection 
{
	AV_int32			nStructSize;
	AV_CFG_MonitorFavorite*	pstuFavorite;				// 画面收藏数组
	AV_int32			nMaxCount;						// 画面收藏数组大小
	AV_int32			nRetCount;						// 返回的画面收藏数量
};

// Raid信息
struct AV_CFG_Raid 
{
	AV_int32			nStructSize;
	char				szName[AV_CFG_Raid_Name_Len];	// 名称
	AV_int32			nLevel;							// 等级
	AV_int32			nMemberNum;						// 磁盘成员数量
	char				szMembers[AV_CFG_Max_Rail_Member][AV_CFG_Max_Path];	// 磁盘成员
};

// 录像源
struct AV_CFG_RecordSource
{
	AV_int32			nStructSize;
	AV_BOOL				bEnable;						// 使能
	char				szDeviceID[AV_CFG_Device_ID_Len];// 设备ID
	AV_int32			nVideoChannel;					// 视频通道号
	AV_int32			nVideoStream;					// 视频码流
	AV_int32			nAudioChannle;					// 音频通道号
	AV_int32			nAudioStream;					// 音频码流
};

// 编码格式, 包括音频和视频
struct AV_CFG_EncodeFormat
{
	AV_int32			nStructSize;
	AV_BOOL				bAudioEnable;					// 音频使能
	AV_int32			nAudioBitRate;					// 音频比特率
	CFG_AUDIO_FORMAT	emAudioCompression;				// 音频压缩模式
	AV_int32			nAudioDepth;					// 音频采样深度
	AV_int32			nAudioFrequency;				// 音频采样频率
	AV_int32			nAudioMode;						// 音频编码模式
	AV_int32			nAudioPack;						// 音频打包模式, 0-DHAV, 1-PS

	AV_BOOL				bVideoEnable;					// 视频使能
	AV_int32			nVideoBitRate;					// 视频比特率
	CFG_BITRATE_CONTROL	emVideoBitRateControl;			// 码流控制模式
	CFG_VIDEO_COMPRESSION emVideoCompression;			// 视频压缩模式
	AV_int32			nVideoFPS;						// 视频帧率
	AV_int32			nVideoGOP;						// 视频I帧间隔
	AV_int32			nVideoWidth;					// 视频宽度
	AV_int32			nVideoHeight;					// 视频高度
	CFG_IMAGE_QUALITY	emVideoQuality;					// 视频图像质量
	AV_int32			nVideoPack;						// 视频打包模式, 0-DHAV, 1-PS	
};

// 编码配置
struct AV_CFG_Encode 
{
	AV_int32			nStructSize;
	AV_CFG_EncodeFormat stuMainFormat[AV_CFG_Max_Encode_Main_Format];	// 主码流, 包括普通编码, 动检编码, 报警编码
	AV_CFG_EncodeFormat	stuExtraFormat[AV_CFG_Max_Encode_Extra_Format];	// 辅码流, 包括辅码流1, 辅码流2, 辅码流3
	AV_CFG_EncodeFormat	stuSnapFormat[AV_CFG_Max_Encode_Snap_Format];	// 抓图, 包括普通抓图, 动检抓图, 报警抓图
};

// 视频输入颜色配置, 每个视频输入通道对应多个颜色配置
struct AV_CFG_VideoColor 
{
	AV_int32			nStructSize;
	AV_CFG_TimeSection	stuTimeSection;					// 时间段
	AV_int32			nBrightness;					// 亮度, 0~100
	AV_int32			nContrast;						// 对比度, 0~100
	AV_int32			nSaturation;					// 饱和度, 0~100
	AV_int32			nHue;							// 色调, 0~100
	AV_int32			nGamma;							// 增益, 0~100
};


// 通道视频输入颜色配置
struct AV_CFG_ChannelVideoColor 
{
	AV_int32			nStructSize;
	AV_int32			nColorNum;						// 通道颜色配置数
	AV_CFG_VideoColor	stuColor[AV_CFG_Max_VideoColor];// 通道颜色配置, 每个通道对应多个颜色配置
};

// 颜色
struct AV_CFG_Color
{
	AV_int32			nStructSize;
	AV_int32			nRed;							// 红
	AV_int32			nGreen;							// 绿
	AV_int32			nBlue;							// 蓝
	AV_int32			nAlpha;							// 透明
};

// 区域
struct AV_CFG_Rect 
{
	AV_int32			nStructSize;
	AV_int32			nLeft;
	AV_int32			nTop;
	AV_int32			nRight;
	AV_int32			nBottom;	
};

// 编码物件-区域覆盖配置
struct AV_CFG_VideoWidgetCover 
{
	AV_int32			nStructSize;	
	AV_BOOL				bEncodeBlend;					// 叠加到主码流
	AV_BOOL				bEncodeBlendExtra1;				// 叠加到辅码流1
	AV_BOOL				bEncodeBlendExtra2;				// 叠加到辅码流2
	AV_BOOL				bEncodeBlendExtra3;				// 叠加到辅码流3
	AV_BOOL				bEncodeBlendSnapshot;			// 叠加到抓图
	AV_CFG_Color		stuFrontColor;					// 前景色
	AV_CFG_Color		stuBackColor;					// 背景色
	AV_CFG_Rect			stuRect;						// 区域, 坐标取值0~8191
	AV_BOOL				bPreviewBlend;					// 叠加到预览视频
};

// 通道标题对齐信息
typedef enum tagEM_TITLE_TEXT_ALIGN
{
    EM_TEXT_ALIGN_INVALID,                              // 无效的对齐方式
    EM_TEXT_ALIGN_LEFT,                                 // 左对齐
    EM_TEXT_ALIGN_XCENTER,                              // X坐标中对齐
    EM_TEXT_ALIGN_YCENTER,                              // Y坐标中对齐
    EM_TEXT_ALIGN_CENTER,                               // 居中
    EM_TEXT_ALIGN_RIGHT,                                // 右对齐
    EM_TEXT_ALIGN_TOP,                                  // 按照顶部对齐
    EM_TEXT_ALIGN_BOTTOM,                               // 按照底部对齐
    EM_TEXT_ALIGN_LEFTTOP,                              // 按照左上角对齐
    EM_TEXT_ALIGN_CHANGELINE,                           // 换行对齐
}EM_TITLE_TEXT_ALIGN;

// 编码物件-通道标题
struct AV_CFG_VideoWidgetChannelTitle
{
	AV_int32			nStructSize;
	AV_BOOL				bEncodeBlend;					// 叠加到主码流
	AV_BOOL				bEncodeBlendExtra1;				// 叠加到辅码流1
	AV_BOOL				bEncodeBlendExtra2;				// 叠加到辅码流2
	AV_BOOL				bEncodeBlendExtra3;				// 叠加到辅码流3
	AV_BOOL				bEncodeBlendSnapshot;			// 叠加到抓图
	AV_CFG_Color		stuFrontColor;					// 前景色
	AV_CFG_Color		stuBackColor;					// 背景色
	AV_CFG_Rect			stuRect;						// 区域, 坐标取值0~8191, 仅使用left和top值, 点(left,top)应和(right,bottom)设置成同样的点
	AV_BOOL				bPreviewBlend;					// 叠加到预览视频
};

// 编码物件-时间标题
struct AV_CFG_VideoWidgetTimeTitle
{
	AV_int32			nStructSize;
	AV_BOOL				bEncodeBlend;					// 叠加到主码流
	AV_BOOL				bEncodeBlendExtra1;				// 叠加到辅码流1
	AV_BOOL				bEncodeBlendExtra2;				// 叠加到辅码流2
	AV_BOOL				bEncodeBlendExtra3;				// 叠加到辅码流3
	AV_BOOL				bEncodeBlendSnapshot;			// 叠加到抓图
	AV_CFG_Color		stuFrontColor;					// 前景色
	AV_CFG_Color		stuBackColor;					// 背景色
	AV_CFG_Rect			stuRect;						// 区域, 坐标取值0~8191, 仅使用left和top值, 点(left,top)应和(right,bottom)设置成同样的点
	AV_BOOL				bShowWeek;						// 是否显示星期
	AV_BOOL				bPreviewBlend;					// 叠加到预览视频
};
	
// 编码物件-自定义标题
struct AV_CFG_VideoWidgetCustomTitle 
{
	AV_int32			nStructSize;
	AV_BOOL				bEncodeBlend;					// 叠加到主码流
	AV_BOOL				bEncodeBlendExtra1;				// 叠加到辅码流1
	AV_BOOL				bEncodeBlendExtra2;				// 叠加到辅码流2
	AV_BOOL				bEncodeBlendExtra3;				// 叠加到辅码流3
	AV_BOOL				bEncodeBlendSnapshot;			// 叠加到抓图
	AV_CFG_Color		stuFrontColor;					// 前景色
	AV_CFG_Color		stuBackColor;					// 背景色
	AV_CFG_Rect			stuRect;						// 区域, 坐标取值0~8191, 仅使用left和top值, 点(left,top)应和(right,bottom)设置成同样的点
	char				szText[AV_CFG_Custom_Title_Len];// 标题内容
	AV_BOOL				bPreviewBlend;					// 叠加到预览视频
    char                szType[AV_CFG_Custom_TitleType_Len];// 标题类型 "Rtinfo" 实时刻录信息 "Custom" 自定义叠加、温湿度叠加 "Title" :片头信息 "Check"  校验码
                                                            // 地理信息 "Geography"  ATM卡号信息 "ATMCardInfo" 摄像机编号 "CameraID" 
    EM_TITLE_TEXT_ALIGN emTextAlign;                    // 标题对齐方式
};

//  编码物件-叠加传感器信息-叠加内容描述
struct AV_CFG_VideoWidgetSensorInfo_Description 
{
	AV_int32			nStructSize;
	AV_int32			nSensorID;						// 需要描述的传感器的ID(即模拟量报警通道号)
};

// 编码物件-叠加传感器信息
struct AV_CFG_VideoWidgetSensorInfo
{
	AV_int32			nStructSize;
	AV_BOOL				bPreviewBlend;					// 叠加到预览视频
	AV_BOOL				bEncodeBlend;					// 叠加到主码流视频编码
	AV_CFG_Rect			stuRect;						// 区域, 坐标取值0~8191
	AV_int32			nDescriptionNum;				// 叠加区域描述数目
	AV_CFG_VideoWidgetSensorInfo_Description stuDescription[AV_CFG_Max_Description_Num];// 叠加区域描述信息
};

// 视频编码物件配置
struct AV_CFG_VideoWidget 
{
	AV_int32						nStructSize;
	AV_CFG_VideoWidgetChannelTitle	stuChannelTitle;	// 通道标题
	AV_CFG_VideoWidgetTimeTitle		stuTimeTitle;		// 时间标题
	AV_int32						nConverNum;			// 区域覆盖数量
	AV_CFG_VideoWidgetCover			stuCovers[AV_CFG_Max_Video_Widget_Cover];				// 覆盖区域
	AV_int32						nCustomTitleNum;	// 自定义标题数量
	AV_CFG_VideoWidgetCustomTitle	stuCustomTitle[AV_CFG_Max_Video_Widget_Custom_Title];	// 自定义标题
	AV_int32						nSensorInfo;		// 传感器信息叠加区域数目
	AV_CFG_VideoWidgetSensorInfo	stuSensorInfo[AV_CFG_Max_Video_Widget_Sensor_Info];		// 传感器信息叠加区域信息
};

// 存储组通道相关配置
struct AV_CFG_StorageGroupChannel 
{
	AV_int32			nStructSize;
	AV_int32			nMaxPictures;					// 每个通道文件夹图片存储上限, 超过就覆盖
	char				szPath[AV_CFG_Max_ChannelRule];	// 通道在命名规则里的字符串表示, %c对应的内容
};

// 存储组配置
struct AV_CFG_StorageGroup 
{
	AV_int32			nStructSize;	
	char				szName[AV_CFG_Group_Name_Len];	// 分组名称
	char				szMemo[AV_CFG_Group_Memo_Len];	// 分组说明
	AV_int32			nFileHoldTime;					// 文件保留时间
	AV_BOOL				bOverWrite;						// 存储空间满是否覆盖
	char				szRecordPathRule[AV_CFG_Max_Path];	// 录像文件路径命名规则
	char				szPicturePathRule[AV_CFG_Max_Path];	// 图片文件路径命名规则
															// %y年, %M月, %d日, %h时, %m分, %s秒, %c通道路径
															// 如果年月日时分秒出现两次, 第一次表示开始时间, 第二次表示结束时间
	AV_CFG_StorageGroupChannel	stuChannels[AV_CFG_Max_Channel_Num];// 通道相关配置 
	AV_int32				nChannelCount;				// 通道配置数
};

// DST时间
struct AV_CFG_DSTTime 
{
	AV_int32			nStructSize;
	AV_int32			nYear;							// 年, 2000~2038
	AV_int32			nMonth;							// 月, 1~12
	AV_int32			nWeek;							// 第几周, 1-第一周,2-第二周,...,-1-最后一周,0-按日期计算
	AV_int32			nDay;							// 星期几或日期
														// 按周计算时, 0-周日, 1-周一,..., 6-周六
														// 按日期算时, 表示几号, 1~31
	AV_int32			nHour;							// 小时
	AV_int32			nMinute;						// 分钟
};

// 区域配置
struct AV_CFG_Locales 
{
	AV_int32			nStructSize;
	char				szTimeFormat[AV_CFG_Time_Format_Len];	// 时间格式
	AV_BOOL				bDSTEnable;						// 夏令时时能
	AV_CFG_DSTTime		stuDstStart;					// 夏令时起始时间
	AV_CFG_DSTTime		stuDstEnd;						// 夏令时结束时间
};

// 语言类型
enum AV_CFG_LanguageType
{
	AV_CFG_Language_English,							// 英文
	AV_CFG_Language_SimpChinese,						// 简体中文
	AV_CFg_Language_TradChinese,						// 繁体中文
	AV_CFG_Language_Italian,							// 意大利文
	AV_CFG_Language_Spanish,							// 西班牙文
	AV_CFG_Language_Janpanese,							// 日文
	AV_CFG_Language_Russian,							// 俄文
	AV_CFG_Language_French,								// 法文
	AV_CFG_Language_German,								// 德文
};

// 语言配置
struct AV_CFG_Language 
{
	AV_int32			nStructSize;
	AV_CFG_LanguageType emLanguage;						// 当前语言
};

// 访问地址过滤
struct AV_CFG_AccessFilter
{
	AV_int32			nStructSize;
	AV_BOOL				bEnable;						// 使能
	AV_int32			nType;							// 类型, 0-黑名单, 1-白名单
	AV_int32			nWhiteListNum;					// 白名单IP数量
	char				szWhiteList[AV_CFG_Max_White_List][AV_CFG_Filter_IP_Len];	// 白名单
	AV_int32			nBlackListNum;					// 黑名单IP或IP段数量
	char				szBlackList[AV_CFG_Max_Black_List][AV_CFG_Filter_IP_Len];	// 黑名单
};

// 自动维护
struct AV_CFG_AutoMaintain 
{
	AV_int32			nStructSize;
	AV_int32			nAutoRebootDay;					// 自动重启日期, -1永不, 0~6周日~周六, 7每天
	AV_int32			nAutoRebootHour;				// 自动重启小时, 0~23
	AV_int32			nAutoRebootMinute;				// 自动重启分钟, 0~59
	AV_int32			nAutoShutdownDay;				// 自动关机日期
	AV_int32			nAutoShutdownHour;				// 自动关机小时
	AV_int32			nAutoShutdownMinute;			// 自动关机分钟
	AV_int32			nAutoStartupDay;				// 自动启动日期
	AV_int32			nAutoStartupHour;				// 自动启动小时
	AV_int32			nAutoStartupMinute;				// 自动启动分钟
	AV_BOOL				bAutoRebootEnable;				// true表示开启自动重启，false表示关闭自动重启
};

#define AV_CFG_Monitor_Name_Len		64			// 电视墙名称长度
#define AV_CFG_Max_TV_In_Block		128			// 区块中TV的最大数量
#define AV_CFG_Max_Block_In_Wall	128			// 电视墙中区块的最大数量

// 电视墙输出通道信息
struct AV_CFG_MonitorWallTVOut
{
	AV_int32		nStructSize;
	char			szDeviceID[AV_CFG_Device_ID_Len];	// 设备ID, 为空或"Local"表示本地设备
	AV_int32		nChannelID;							// 通道ID
	char			szName[AV_CFG_Channel_Name_Len];	// 屏幕名称
};

// 电视墙区块
struct AV_CFG_MonitorWallBlock 
{
	AV_int32				nStructSize;
	AV_int32				nLine;				// 单个TV占的网格行数
	AV_int32				nColumn;			// 单个TV占的网格列数
	AV_CFG_Rect				stuRect;			// 区块的区域坐标
	AV_int32				nTVCount;			// TV数量
	AV_CFG_MonitorWallTVOut	stuTVs[AV_CFG_Max_TV_In_Block];					// TV数组
	CFG_TIME_SECTION		stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT];	// 开关机时间
	char					szName[AV_CFG_Channel_Name_Len];				// 区块名称
	char					szCompositeID[AV_CFG_Device_ID_Len];			// 融合屏ID
};

// 电视墙
struct AV_CFG_MonitorWall
{
	AV_int32			nStructSize;
	char				szName[AV_CFG_Monitor_Name_Len];	// 名称
	AV_int32			nLine;								// 网络行数
	AV_int32			nColumn;							// 网格列数
	AV_int32			nBlockCount;						// 区块数量
	AV_CFG_MonitorWallBlock stuBlocks[AV_CFG_Max_Block_In_Wall];// 区块数组
    BOOL                bDisable;                           // 是否禁用, 0-该电视墙有效, 1-该电视墙无效
    char                szDesc[CFG_COMMON_STRING_256];      // 电视墙描述信息
};

// 拼接屏
struct AV_CFG_SpliceScreen
{
	AV_int32			nStructSize;
	char				szName[AV_CFG_Channel_Name_Len];	// 拼接屏名称	
	char				szWallName[AV_CFG_Monitor_Name_Len];// 所属电视墙名称
	AV_int32			nBlockID;							// 所属区块序号
	AV_CFG_Rect			stuRect;							// 区域坐标(0~8191)
};

// 云台联动类型
typedef enum tagAV_CFG_PtzLinkType
{
	AV_CFG_PtzLink_None,				// 无联动
	AV_CFG_PtzLink_Preset,				// 联动预置点
	AV_CFG_PtzLink_Tour,				// 联动巡航
	AV_CFG_PtzLink_Pattern,				// 联动轨迹
} AV_CFG_PtzLinkType;

// 联动云台信息
typedef struct tagAV_CFG_PtzLink
{
	AV_int32            nStructSize;
	AV_CFG_PtzLinkType	emType;				// 联动类型 
	AV_int32			nParam1;			// 联动参数1
	AV_int32			nParam2;            // 联动参数2
	AV_int32			nParam3;            // 联动参数3
	AV_int32			nChannelID;         // 所联动云台通道
} AV_CFG_PtzLink;

// 坐标点
typedef struct tagAV_CFG_Point
{
	AV_int32			nStructSize;
	AV_int32			nX;
	AV_int32			nY;
} AV_CFG_Point;

// 宽高
typedef struct tagAV_CFG_Size
{
	AV_int32			nStructSize;
	AV_uint32			nWidth;
	AV_uint32			nHeight;
} AV_CFG_Size;	

// 事件标题内容
typedef struct tagAV_CFG_EventTitle
{
	AV_int32			nStructSize;
	char				szText[AV_CFG_Channel_Name_Len];	// 标题文本
	AV_CFG_Point		stuPoint;			// 标题左上角坐标, 采用0-8191相对坐标系
	AV_CFG_Size			stuSize;			// 标题的宽度和高度,采用0-8191相对坐标系，某项或者两项为0表示按照字体自适应宽高
    AV_CFG_Color		stuFrontColor;		// 前景颜色
    AV_CFG_Color		stuBackColor;		// 背景颜色
} AV_CFG_EventTitle;


// 轮巡联动配置
typedef struct tagAV_CFG_TourLink
{
	AV_int32			nStructSize;
	AV_BOOL				bEnable;			// 轮巡使能
	CFG_SPLITMODE		emSplitMode;		// 轮巡时的分割模式
	AV_int32			nChannels[AV_CFG_Max_Channel_Num];  // 轮巡通道号列表
	AV_int32			nChannelCount;		// 轮巡通道数量
} AV_CFG_TourLink;

// 报警联动
typedef struct tagAV_CFG_EventHandler
{
	AV_int32			nStructSize;
	AV_CFG_TimeSection  stuTimeSect[AV_CFG_Weekday_Num][AV_CFG_Max_TimeSection]; // 事件响应时间表
	AV_BOOL             bRecordEnable;		// 录像使能
	AV_uint32           nRecordMask[AV_CFG_Max_Channel_Num];	// 录像通道号列表
	AV_BOOL             abRecordLatch;		// 能力集, 标识nRecordLatch是否有效
	AV_int32            nRecordLatch;		// 录像延时时间（10~300秒）
	AV_BOOL				bAlarmOutEn;		// 报警输出使能
	AV_uint32			nAlarmOutMask[AV_CFG_Max_Channel_Num];	// 报警输出通道号列表
	AV_BOOL             abAlarmOutLatch;	// 能力集, 标识nAlarmOutLatch是否有效
	AV_int32			nAlarmOutLatch;		// 报警输出延时时间（10~300秒）
	AV_BOOL				bExAlarmOutEn;		// 扩展报警输出使能
	AV_uint32			nExAlarmOutMask[AV_CFG_Max_Channel_Num]; // 扩展报警输出通道列表
	AV_BOOL				bPtzLinkEn;			// 云台联动使能
	AV_int32            nPtzLinkNum;		// 有效联动项数目
	AV_CFG_PtzLink		stuPtzLink[AV_CFG_Max_Channel_Num];		// 云台联动项
	AV_BOOL				bSnapshotEn;		// 快照使能
	AV_uint32			nSnapshotMask[AV_CFG_Max_Channel_Num];  // 快照通道号列表	
	AV_BOOL             abSnapshotPeriod;	// 能力集, 标识nSnapshotPeriod是否有效
	AV_int32			nSnapshotPeriod;	// 帧间隔，每隔多少帧抓一张图片，一定时间内抓拍的张数还与抓图帧率有关。0表示不隔帧，连续抓拍。
	AV_BOOL             abSnapshotTimes;	// 能力集, nSnapshotTimes有效性
	AV_int32			nSnapshotTimes;		// 连拍次数, 在SnapshotEnable为true的情况下，SnapshotTimes为0则表示持续抓拍，直到事件结束。
	AV_BOOL             bSnapshotTitleEn;	// 是否叠加图片标题
	AV_int32            nSnapTitleNum;      // 有效图片标题数目
	AV_CFG_EventTitle   stuSnapTitles[AV_CFG_Max_Event_Title_Num]; // 图片标题内容
	AV_BOOL				bTipEnable;			// 本地消息框提示
	AV_BOOL				bMailEnable;		// 发送邮件，如果有图片，作为附件
	AV_BOOL				bMessageEnable;		// 上传到报警服务器
	AV_BOOL				bBeepEnable;		// 蜂鸣
	AV_BOOL				bVoiceEnable;		// 语音提示
	AV_BOOL             abDejitter;			// 能力集, nDejitter有效性
	AV_int32            nDejitter;			// 信号去抖动时间，单位为秒,0~100
	AV_BOOL             bLogEnable;			// 是否记录日志
	AV_BOOL             abDelay;			// nDelay有效性
	AV_int32            nDelay;				// 设置时先延时再生效, 单位为秒
	AV_BOOL             bVideoTitleEn;		// 是否叠加视频标题，主要指主码流
	AV_int32            nVideoTitleNum;		// 有效视频标题数目
	AV_CFG_EventTitle	stuVideoTitles[AV_CFG_Max_Event_Title_Num]; // 视频标题内容
	AV_BOOL				bMMSEnable;			// 发送彩信使能
	AV_int32            nTourNum;			// 轮巡联动数目，和视频输出一致
	AV_CFG_TourLink	    stuTour[AV_CFG_Max_Tour_Link_Num];		// 轮巡联动配置, 每个视频输出对应一个配置
	AV_int32            nDBKeysNum;			// 关键字数量
	char	            szDBKeys[AV_CFG_Max_DBKey_Num][AV_CFG_DBKey_Len]; // 关键字
	AV_BOOL             abJpegSummary;		// 能力集, 标识byJpegSummary是否有效
	AV_BYTE             byJpegSummary[AV_CFG_Max_Summary_Len]; // 叠加到JPEG图片的摘要信息
} AV_CFG_EventHandler;

#define AV_CFG_Event_Code_Len	64		// 事件码长度

// 远程设备事件处理
struct AV_CFG_RemoteEvent 
{
	AV_int32            nStructSize;
	AV_BOOL             bEnable;						 // 使能
	char                szDeviceID[AV_CFG_Device_ID_Len];// 设备ID
	char                szCode[AV_CFG_Event_Code_Len];	 // 事件码
	AV_int32            nIndex;							 // 序号
	AV_BOOL             abSensorType;                    // nSensorType是否有效
	AV_uint32           nSensorType;                     // 传感器类型 常开:1 or 常闭:0
	AV_CFG_EventHandler stuEventHandler;				 // 报警联动
};

// 温度报警配置
typedef struct tagAV_CFG_TemperatureAlarm
{
	AV_int32			nStructSize;
	AV_BOOL				bEnable;							// 报警使能
	char				szName[AV_CFG_Device_Name_Len];		// 传感器名称
	AV_float			fNormalTempMin;						// 正常温度最小值
	AV_float			fNormalTempMax;						// 正常温度最大值
	AV_CFG_EventHandler stuEventHandler;					// 报警联动
} AV_CFG_TemperatureAlarm;

// 风扇转速报警配置
typedef struct tagAV_CFG_FanSpeedAlarm
{
	AV_int32			nStructSize;
	AV_BOOL				bEnable;							// 报警使能
	char				szName[AV_CFG_Device_Name_Len];		// 传感器名称
	AV_uint32			nNormalSpeedMin;					// 正常转速最小值
	AV_uint32			nNormalSpeedMax;					// 正常转速最大值
	AV_CFG_EventHandler stuEventHandler;					// 报警联动
} AV_CFG_FanSpeedAlarm;

// 硬盘流量报警配置
typedef struct tagCFG_DISK_FLUX_INFO 
{
	BOOL				bEnable;							// 报警使能
	unsigned int		nNormalFluxMin;						// 正常流量最小值, 单位KB
	unsigned int		nNormalFluxMax;						// 正常流量最大值, 单位KB
	CFG_ALARM_MSG_HANDLE stuEventHandler;					// 报警联动
	CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT_EX];	// 事件响应时间段
} CFG_DISK_FLUX_INFO;

// 网络流量报警配置
typedef struct tagCFG_NET_FLUX_INFO
{
	BOOL				bEnable;							// 报警使能
	unsigned int		nNormalFluxMin;						// 正常流量最小值, 单位KB
	unsigned int		nNormalFluxMax;						// 正常流量最大值, 单位KB
	CFG_ALARM_MSG_HANDLE stuEventHandler;					// 报警联动
	CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT_EX];	// 事件响应时间段
} CFG_NET_FLUX_INFO;

// 服务器
typedef struct tagCFG_SERVER_INFO
{
	int                 nPort;                             // 服务器端口号
	char                szAddress[MAX_ADDRESS_LEN];        // IP地址或网络名
}CFG_SERVER_INFO;

// 主动注册配置
typedef struct tagCFG_REGISTER_SERVER_INFO
{
	BOOL                bEnable;                            // 主动注册使能
	char                szDeviceID[MAX_ADDRESS_LEN];        // 设备ID
	int                 nServersNum;                        // 服务器个数
	CFG_SERVER_INFO     stuServers[MAX_SERVER_NUM];         // 服务器数组
}CFG_REGISTER_SERVER_INFO;

// 带宽不足时码流策略
typedef enum tagSTREAM_POLICY
{
    STREAM_POLICY_UNKNOWN,
    STREAM_POLICY_NONE = 1,								// 无策略,不开启使能"None"
    STREAM_POLICY_QUALITY,                              // 画质优先"Quality"  
    STREAM_POLICY_FLUENCY,                              // 流畅度优先"Fluency"
    STREAM_POLICY_AUTOADAPT,                            // 自动"AutoAdapt"
}EM_STREAM_POLICY;

// 网络协议配置
typedef struct tagCFG_DVRIP_INFO
{
	int                 nTcpPort;                           // TCP服务端口,1025~65535
	int                 nSSLPort;                           // SSL服务端口,1025~65535
	int                 nUDPPort;                           // UDP服务端口,1025~65535
	int                 nMaxConnections;                    // 最大连接数 
	BOOL                bMCASTEnable;                       // 组播使能
	int                 nMCASTPort;                         // 组播端口号
	char                szMCASTAddress[MAX_ADDRESS_LEN];    // 组播地址
	int                 nRegistersNum;                      // 主动注册配置个数
	CFG_REGISTER_SERVER_INFO stuRegisters[MAX_REGISTER_NUM];// 主动注册配置 
    EM_STREAM_POLICY    emStreamPolicy;                     // 带宽不足时码流策略
}CFG_DVRIP_INFO;

// 假期录像计划
typedef struct tagCFG_HOLIDAY_SCHEDULE
{
	BOOL				bEnable;
	int					nChannel;
	DWORD				dwMonthSchedule[MONTH_OF_YEAR];		// 每个月的假期安排, 每个元素表示一个月, 
															// 掩码从低到高依次表示每月1-28/29/30/31号是否为假期
															// 0:不是假期, 1:是假期
	CFG_TIME_SECTION	stuTimeSection[MAX_REC_TSECT];		// 录像时间表
} CFG_HOLIDAY_SCHEDULE;

// 录像回传配置
typedef struct tagAV_CFG_RecordBackup
{
	AV_int32			nStructSize;
	AV_uint32			nBitrateLimit;						// 最大流量配置, 单位Kbps
	AV_CFG_RemoteDevice	*pstuDevices;						// 备份设备数组, 用户分配内存
	int					nMaxDeviceCount;					// 备份设置数组大小, 用户填写
	int					nRetDeviceCount;					// 返回的设备数量
} AV_CFG_RecordBackup;

typedef struct tagALARM_EVENT_INFO
{
	DWORD	        	dwEventType;					    // 事件类型，详见dhnetsdk.h中"智能分析事件类型"
	int		         	nEventSize;							// 该事件类型规则配置结构体大小
} ALARM_EVENT__INFO;

// 每个视频输入通道对应的所有事件：缓冲区pEventBuf填充多个事件信息，每个事件规则信息内容为ALARM_EVENT_INFO+"事件类型对应的规则配置结构体"。
typedef struct tagALARM_ANALYSEEVENTS_INFO
{
	int	         		nEventCount;						// 事件个数
	char*				pEventBuf;							// 每个视频输入通道对应的视频分析事件缓冲
	int		        	nEventBufLen;						// 缓冲大小
	
} ALARM_ANALYSEEVENTS_INFO;

// 串口信息
typedef struct tagCFG_COMM_INFO
{
	char				szProtocolName[MAX_PROTOCOL_NAME_LEN];	// 串口协议
	CFG_COMM_PROP		stuAttribute;							// 串口属性
	int					nAddress;								// 设备地址
} CFG_COMM_INFO;

// 串口配置
typedef struct tagCFG_COMMGROUP_INFO
{
	int					nCommNum;						// 串口数量
	CFG_COMM_INFO		stuComms[MAX_COMM_NUM];			// 串口数组
} CFG_COMMGROUP_INFO;

// 网络接口
typedef struct tagCFG_NETWORK_INTERFACE 
{
	char				szName[MAX_NAME_LEN];			// 网络接口名称
	char				szIP[MAX_ADDRESS_LEN];			// ip地址
	char				szSubnetMask[MAX_ADDRESS_LEN];	// 子网掩码
	char				szDefGateway[MAX_ADDRESS_LEN];	// 默认网关
	BOOL				bDhcpEnable;					// 是否开启DHCP
	BOOL				bDnsAutoGet;					// DNS获取方式，dhcp使能时可以设置为true，支持通过dhcp获取
	char				szDnsServers[MAX_DNS_SERVER_NUM][MAX_ADDRESS_LEN];	// DNS服务器地址
	int					nMTU;							// 网络最大传输单元
} CFG_NETWORK_INTERFACE;

// 网络接口配置
typedef struct tagCFG_NETWORK_INFO 
{
	char				szHostName[MAX_NAME_LEN];		// 主机名称
	char				szDomain[MAX_NAME_LEN];			// 所属域
	char				szDefInterface[MAX_NAME_LEN];	// 默认使用的网卡
	int					nInterfaceNum;					// 网卡数量
	CFG_NETWORK_INTERFACE	stuInterfaces[MAX_NETWORK_INTERFACE_NUM];	// 网卡列表
} CFG_NETWORK_INFO;

// 云存储协议类型
typedef enum tagEM_CFG_NAS_CLOUDPROTOCOL_TYPE
{
    EM_CFG_NAS_CLOUDPROTOCOL_TYPE_UNKNOWN,              // 未知
    EM_CFG_NAS_CLOUDPROTOCOL_TYPE_BAIDU_CLOUD,          // "BaiduCloud"
    EM_CFG_NAS_CLOUDPROTOCOL_TYPE_GOOGLE_DRIVE,         // "GoogleDrive"
    EM_CFG_NAS_CLOUDPROTOCOL_TYPE_DROPBOX,              // "Dropbox"
}EM_CFG_NAS_CLOUDPROTOCOL_TYPE;

// 网络存储配置
typedef struct tagCFG_NAS_INFO_NEW
{
	BOOL				            bEnable;						// 使能
	char				            szName[MAX_NAME_LEN];			// 名称
	int					            nPortocol;						// 协议类型, 0-FTP, 1-SMB, 2-ISCSI, 3-NFS, 4-Cloud ,协议类型是 4-Cloud时，具体云协议定义见 emCloudProtocol
	char				            szAddress[MAX_ADDRESS_LEN];		// IP地址或网址
    int					            nPort;							// 端口
    char				            szUser[MAX_USERNAME_LEN];		// 用户名
    char				            szPassword[MAX_PASSWORD_LEN];	// 密码
    char				            szDirectory[MAX_NAME_LEN];		// 共享的目录名
    int					            nCharEncoding;					// 字符编码格式, 0-UTF8, 1-GB2312
    int					            nTimeOut;						// 超时时间, 单位毫秒
    unsigned int		            nStreamID;						// 数据流ID
    CFG_NET_TIME_EX		            stuUpdateTime;					// 更新时间, 该字段值变化后，需要重新初始化iSCSI功能
    EM_CFG_NAS_CLOUDPROTOCOL_TYPE   emCloudProtocol;                // 云存储协议类型
    char                            szSubDirectory[CFG_COMMON_STRING_256];               // 客户端设备在服务器上的存储子目录，可以是IP地址，设备序列号，设备机器号，为空使用设备机器号
} CFG_NAS_INFO_NEW;

// 网络存储服务器配置, 包含多个服务器
typedef struct tagCFG_NAS_GROUP_INFO
{
	int					nNasNum;						// 存储服务器数量
	CFG_NAS_INFO_NEW	stuNasInfo[MAX_NAS_NUM];		// 存储服务器数组	
} CFG_NAS_GROUP_INFO;

// 网络存储服务器配置
typedef struct tagCFG_NAS_INFO_EX 
{
	int					nVersion;						// 0, 1, 由能力集确定, 只读
	CFG_NAS_INFO		stuNasOld;						// nVersion == 0时有效, 仅支持单服务器
	CFG_NAS_GROUP_INFO	stuNasGroup;					// nVersion == 1时有效, 支持多个服务器
} CFG_NAS_INFO_EX;

// 输入信号类型
typedef enum _EM_CFG_VIDEO_SIGNAL_TYPE
{
    EM_CFG_VIDEO_SIGNAL_UNKNOWN, 
    EM_CFG_VIDEO_SIGNAL_CVBS, 
    EM_CFG_VIDEO_SIGNAL_SDI, 
    EM_CFG_VIDEO_SIGNAL_VGA, 
    EM_CFG_VIDEO_SIGNAL_DVI, 
    EM_CFG_VIDEO_SIGNAL_HDMI, 
    EM_CFG_VIDEO_SIGNAL_YPBPR, 
    EM_CFG_VIDEO_SIGNAL_SFP, 
    EM_CFG_VIDEO_SIGNAL_HDCVI, 
} EM_CFG_VIDEO_SIGNAL_TYPE;

// 输入通道基本配置
typedef struct tagCFG_VIDEO_IN_INFO 
{
	char				szDevType[MAX_NAME_LEN];		// 通道类型（指通道连接的设备类型）
	char				szDevID[MAX_NAME_LEN];			// 摄像头唯一编号
	char				szChnName[MAX_NAME_LEN];		// 通道名称
	char				szManufacturer[MAX_NAME_LEN];	// 厂商
	char				szModel[MAX_NAME_LEN];			// 设备型号
	char				szAddress[MAX_ADDRESS_LEN];		// 安装地址
	char				szCivilCode[MAX_NAME_LEN];		// 行政区域
	char				szOwner[MAX_NAME_LEN];			// 设备归属
	BOOL				bParental;						// 是否有子设备
	BOOL				bEnable;						// 通道使能
	int					nRegisterWay;					// 注册方式
														// 0-符合sip3261标准的认证注册模式
														// 1-基于口令的双向认证注册模式
														// 2-基于数字证书的双向认证注册模式
	BOOL				bSecrecy;						// 保密属性, FALSE不涉密, TRUE涉密
	char				szUpperDevID[MAX_NAME_LEN];		// 上级连接设备设备ID
	int					nUpperDevOutChn;				// 上级连接设备输出通道号
    char				szRemoteName[MAX_NAME_LEN];		// 远程通道名称
    EM_CFG_VIDEO_SIGNAL_TYPE emSignalType;              // 输入信号类型
} CFG_VIDEO_IN_INFO;

// 刻录光盘编码计划(对应命令 CFG_CMD_ENCODEPLAN)，每个通道(包括画中画通道)一个配置结构体
typedef struct tagCFG_ENCODE_PLAN_INFO
{
	BOOL                bEnable;                        // 通道是否需要配置,FALSE:没有此通道,TRUE:此通道可用
	unsigned int        nExpectTime;                    // 业务预期时长	 整型,单位：分钟
	CFG_CAPTURE_SIZE    emResolution;                   // 视频分辨率
	unsigned int        nBitRate;                       // 视频固定码流值(kbps)
}CFG_ENCODE_PLAN_INFO;

//////////////////////////////////////////////////////////////////////////
// 司法审讯画中画需求
// 小画面窗口信息
typedef struct tagCFG_SMALLPIC_INFO
{
	char                szDeviceID[AV_CFG_Device_ID_Len];// 设备ID
	int                 nChannelID;						 // 通道号(0开始)
	BOOL                bAudio;                          // 大画面是否混合小画面音频
    CFG_RECT            stuPosition;                     // 使用相对坐标体系，取值均为0-8192,在整个屏幕上的位置
}CFG_SMALLPIC_INFO;

// 分割通道
typedef struct tagCFG_SPLIT_CHANNEL_INFO
{
	BOOL                bEnable;                         // 使能
	char                szDeviceID[AV_CFG_Device_ID_Len];// 设备ID
	int                 nChannelID;						 // 通道号(0开始)
	unsigned int        nMaxSmallChannels;               // 小画面通道个数，每个通道一个CFG_SMALLPIC_INFO,这里最大应该是设备通道数减一
	unsigned int        nReturnSmallChannels;            // 解析返回的或封装发送的小画面通道个数
	CFG_SMALLPIC_INFO  *pPicInfo;                        // 小画面信息
}CFG_SPLIT_CHANNEL_INFO;

// 分割方案
typedef struct tagCFG_SPLIT_INFO
{
	CFG_SPLITMODE       emSplitMode;        // 分割模式，通过CLIENT_GetSplitCaps接口获取，见emSplitMode
	unsigned int        nMaxChannels;       // 申请内存CFG_SPLIT_CHANNEL_INFO个数,比如有16个通道，nMaxChannels就是16，SPLITMODE_4模式，则按顺序依次分为4组
	unsigned int        nReturnChannels;    // 解析返回通道个数,要封装发送的通道个数
	CFG_SPLIT_CHANNEL_INFO* pSplitChannels; // 分割通道信息
}CFG_SPLIT_INFO;

// 画中画方案
typedef struct tagCFG_PICINPIC_INFO
{
	unsigned int        nMaxSplit;          // 内存申请的CFG_SPLIT_INFO个数,最大值通过CLIENT_GetSplitCaps接口获取，见nModeCount
	unsigned int        nReturnSplit;       // 解析得到实际使用的或封装发送的CFG_SPLIT_INFO个数
	CFG_SPLIT_INFO     *pSplits;            // 分割方案
}CFG_PICINPIC_INFO;

// 模拟矩阵外部输入源
typedef struct tagCFG_ANALOG_MATRIX_INPUT_CHN_SRC 
{
	char				szName[MAX_NAME_LEN];			// 输入通道名称
	char				szControlID[MAX_NAME_LEN];		// 控制编号
	BOOL				bActive;						// 是否激活启动
	int					nFormat;						// 类型, 0-VGA
} CFG_ANALOG_MATRIX_INPUT_CHN_SRC;

// 串口
typedef struct tagCFG_COM_PORT 
{
	int					nPortIndex;						// 串口索引号
	int					nAddress;						// 设备地址
	CFG_COMM_PROP		stComProp;						// 串口属性
} CFG_COM_PORT;

// 模拟矩阵
typedef struct tagCFG_ANALOG_MATRIX_INFO
{
	char				szDevID[MAX_NAME_LEN];			// 设备ID
	char				szName[MAX_NAME_LEN];			// 设备名称
	char				szModel[MAX_MODEL_LEN];			// 型号
	char				szUserName[MAX_USERNAME_LEN];	// 用户名
	char				szPassword[MAX_PASSWORD_LEN];	// 密码
	int					nChnInCount;					// 输入通道数量
	int					nChnOutCount;					// 输出通道数量
	CFG_ANALOG_MATRIX_INPUT_CHN_SRC* pstuChnInSrc;		// 外部输入源数组, 用户分配内存
	int					nChnInSrcCount;					// 外部输入源数组大小
	int					nRetChnInSrcCount;				// 实际返回的外部输入源数量, 一般同nChnInCount
	CFG_COM_PORT		stComPort;						// 关联串口
	char				szProtocol[MAX_NAME_LEN];		// 协议名称
} CFG_ANALOG_MATRIX_INFO;

// 模拟矩阵协议配置
typedef struct tagCFG_ANALOG_MATRIX_PROTOCOL 
{
	char				szName[MAX_NAME_LEN];			// 协议名称
	char				szProtocolRule[MAX_NAME_LEN];	// 协议内容, 规则：%A-地址码，%I-输入端口号，%O-输出端口号
} CFG_ANALOG_MATRIX_PROTOCOL;

// 视频输出标题
typedef struct tagCFG_VIDEO_OUT_TITLE 
{
	char				szName[MAX_NAME_LEN];			// 通道名称
} CFG_VIDEO_OUT_TITLE;

// 显示源
typedef struct tagCFG_DISPLAY_SOURCE
{
	BOOL				bEnable;						// 是否使能
	char				szDeviceID[MAX_NAME_LEN];		// 设备ID
	char				szControlID[MAX_NAME_LEN];		// 控制ID
	int					nVideoChannel;					// 视频通道号
	int					nVideoStream;					// 视频码流, -1-自动, 0-主码流, 1-辅码流1, 2-辅码流2, 3-辅码流3, 5-预览码流
	int					nAudioChannel;					// 音频通道号
	int					nAudioStream;					// 音频码流, -1-自动, 0-主码流, 1-辅码流1, 2-辅码流2, 3-辅码流3, 5-预览码流
	BOOL				abDeviceInfo;					// 设备信息是否有效
	AV_CFG_RemoteDevice stuDeviceInfo;					// 设备信息
} CFG_DISPLAY_SOURCE;

// 窗口位置
typedef struct tagCFG_SPLIT_WINDOW_POSITION 
{
	CFG_RECT			stuRect;						// 窗口区域
	BOOL				bDirectable;					// 是否满足直通条件, 直通是指拼接屏方式下，此窗口区域正好为物理屏区域
	int					nZorder;						// Z次序
} CFG_SPLIT_WINDOW_POSITION;

// 拼接屏窗口信息
typedef struct tagCFG_SPLIT_WINDOW 
{
	BOOL				bEnable;						// 窗口是否有视频源, 为FALSE时表示没有视频，也不用处理Source内容
	int					nWindowID;						// 窗口ID
	char				szControlID[MAX_NAME_LEN];		// 控制ID
	CFG_SPLIT_WINDOW_POSITION stuPosition;				// 窗口位置
	CFG_DISPLAY_SOURCE	stuSource;						// 视频源
} CFG_SPLIT_WINDOW;

// 拼接屏场景
typedef struct tagCFG_BLOCK_COLLECTION 
{
	char				szBlockID[MAX_NAME_LEN];		// 拼接屏ID
	char				szControlID[MAX_NAME_LEN];		// 控制ID
	CFG_SPLITMODE		emSplitMode;					// 分割模式
	CFG_SPLIT_WINDOW*	pstuWnds;						// 窗口信息数组, 用户分配内存
	int					nMaxWndCount;					// 窗口信息数组大小, 用户填写
	int					nRetWndCount;					// 返回的窗口数量
} CFG_BLOCK_COLLECTION;

// 电视墙中的某个预案配置
typedef struct tagCFG_MONITORWALL_COLLECTION_SINGLE
{
	char				szName[MAX_NAME_LEN];			// 名称
	char				szControlID[MAX_NAME_LEN];		// 控制ID
	AV_CFG_MonitorWall	stuMonitorWall;					// 电视墙配置
	CFG_BLOCK_COLLECTION* pstuBlockCollections;			// 拼接屏场景信息数组, 用户分配内存
	int					nMaxBlockCollectionCount;		// 拼接屏场景数组大小, 用户填写
	int					nRetBlockCollectionCount;		// 返回的拼接屏场景数量
} CFG_MONITORWALL_COLLECTION_SINGLE;

// 电视墙预案列表, 表示某个电视墙对应的多个预案
typedef struct tagCFG_MONITORWALL_COLLECTION_LIST
{
	CFG_MONITORWALL_COLLECTION_SINGLE* pstuCollections;	// 预案数组, 用户分配内存
	int					nMaxCollectionCount;			// 预案数组大小, 用户填写
	int					nRetCollectionCount;			// 返回的预案数量
} CFG_MONITORWALL_COLLECTION;

// 视频输入边界配置
typedef struct tagCFG_VIDEO_IN_BOUNDARY 
{
	CFG_RECT			stuBoundary;					// 边界
} CFG_VIDEO_IN_BOUNDARY;

// 和相机对接的区域屏配置,是数组，元素最大值是DH_PRODUCTION_DEFNITION.nMaxParkingSpaceScreen)
typedef struct tagCFG_PARKINGSPACE_SCREEN_INFO
{
	char                szAddress[MAX_PATH];            // 区域屏地址或域名
	int                 nPort;                          // 区域屏端口
	char                szAuthorization[MAX_PATH];      // 权限字
    char                szDeviceNo[MAX_PATH];           // 设备序号
	BOOL                bEnable;                        // 屏配置是否启用
} CFG_PARKINGSPACE_SCREEN_INFO;

// 车位设置(专有车位和普通车位设置)，是数组，元素最大值是DH_PRODUCTION_DEFNITION.nMaxRoadWays)
typedef struct tagCFG_PARKINGSPACE_STATUS_INFO
{
	int                  nLaneID;                        // 车位号
	int                  nLaneType;                      // 0：普通车位 1：专有车位
} CFG_PARKINGSPACE_STATUS_INFO;

#define CFG_MAX_BINARY_NUM      128						// 自定义数据最大个数

// 平台自定义信息
typedef struct tagCFG_CLIENT_CUSTOM_INFO
{
	char                szDescription[MAX_PATH];        // 描述信息,不同平台自定义描述信息,目前支持"LiFang"
	char*               pData;                          // 自定义数据缓冲, 数据中间不能存在二进制的0, 也就是字符'\0'
	int                 nDataLen;                       // 用户申请的长度, 不同平台自己确定
    bool                abBinary;                       // false表示pData和nDataLen有效, 而nBinaryNum和dwBinary无效
                                                        // true表示pData和nDataLen无效, 而nBinaryNum和dwBinary有效
    BYTE                byReserved[3];
    int                 nBinaryNum;                     // dwBinary数组有效成员个数
    DWORD               dwBinary[CFG_MAX_BINARY_NUM];   // 自定义数据
} CFG_CLIENT_CUSTOM_INFO;

// 刻录格式配置,兼容性考虑：无此配置时默认DHAV格式
typedef struct tagCFG_BURN_RECORD_FORMAT
{
	char                 szRecordPack[MAX_PATH];         // 码流打包模式:目前支持"DHAV","PS"
}CFG_BURN_RECORD_FORMAT;

// 多光盘同步刻录(对应 CFG_MULTIBURN_INFO) 是一个数组，每一个元素表示一组多光盘同步刻录及校验
typedef struct tagCFG_MULTIBURN_INFO
{
	BOOL                 bEnable;                        // 此配置使能开关
    BOOL                 bDataCheck;                     // 多光盘一致性校验使能
    char                 szDataCheckSpeed[MAX_PATH];     // 校验速度 "High":高速（头尾数据校验）,"Normal":正常（随机数据校验）,"Low":低速 （全盘数据校验）
}CFG_MULTIBURN_INFO;

// 单个网络存储服务器限制配置
typedef struct tagCFG_REMOTE_STORAGE_LIMIT
{
    char				        szName[MAX_NAME_LEN];                       // 名称
    int							nFileLen;									// 文件长度 单位,MB
	int							nInterval;									// 相邻文件时间间隔 单位,秒
	CFG_CHANNEL_TIME_SECTION	*pstuChnTime;        	                    // 存储时间段数组，用户分配内存
	int                         nMaxChnCount;                               // 最大通道数，用户填写
    int                         nRetChnCount;                               // 返回的通道数,保存设置时的有效通道数
}CFG_REMOTE_STORAGE_LIMIT;

// 网络存储服务器限制配置
typedef struct tagCFG_REMOTE_STORAGELIMIT_GROUP
{
	CFG_REMOTE_STORAGE_LIMIT    stuRemoteStorageLimit[MAX_NAS_NUM];         // 网络存储服务器配置数组
    int                         nLimitCount;                                // 有效的网络服务器数
}CFG_REMOTE_STORAGELIMIT_GROUP;

// 获取刻录管理能力集
typedef struct tagCFG_CAP_BURN_MANAGER	
{
    BOOL                 bSupportMultiBurn;              // 是否支持多光盘同步刻录
    int                  nMultiBurnGroups;               // 支持几组同步刻录
}CFG_CAP_BURN_MANAGER;

// 录像能力信息
typedef struct tagCFG_CAP_RECORD_INFO	
{
	BOOL  bSupportHoliday;				                 //录像计划是否支持假日功能
	BOOL  bSupportExtraRecordMode;						 //是否支持设置辅码流录像模式	
	DWORD dwMaxPreRecordTime;							 //最大预录时间
	DWORD dwMaxRemoteBitrate;							 //最大接入总码流,单位kbps
	DWORD dwMaxRemoteRawBitrate;						 //最大接入祼码流（包括路数、分辨率、帧率，色深按16bpp计算）
    DWORD dwMaxStreams;                                  //最大录像码流个数
} CFG_CAP_RECORD_INFO;

//-------------------------------编码加密---------------------------------
typedef  enum tagCFG_ENCRYPT_ALGO_TYPE
{
	ALGO_TYPE_AES	 , 
	ALGO_TYPE_UNKNOW ,
}CFG_ENCRYPT_ALGO_TYPE;

// 码流加密算法工作模式
typedef enum  tagCFG_ENCRYPT_ALGO_WORKMODE
{
	ENCRYPT_ALGO_WORKMODE_ECB,     // ECB模式
	ENCRYPT_ALGO_WORKMODE_CBC,     // CBC模式
	ENCRYPT_ALGO_WORKMODE_CFB,     // CFB模式
	ENCRYPT_ALGO_WORKMODE_OFB,     // OFB模式
	ENCRYPT_ALGO_WORKMODE_UNKNOW ,
}CFG_ENCRYPT_ALGO_WORKMODE;

typedef union tagCFG_ENCRYPT_KEY_INFO
{
	BYTE byAesKey[AES_KEY_LEN];							// aes密钥
}CFG_ENCRYPT_KEY_INFO;

//码流加密配置信息
typedef struct tagCFG_STREAM_ENCRYPT_INFO
{
	BOOL						bEncryptEnable;		// 是否加密
	CFG_ENCRYPT_ALGO_TYPE		emEncrptAlgoType;	// 加密算法类型: 参见枚举类型CFG_ENCRYPT_ALGO_TYPE
	CFG_ENCRYPT_ALGO_WORKMODE	emAlgoWorkMode;		// 工作模式,参考枚举类型 CFG_ENCRYPT_ALGO_WORKMODE
	WORD						wEncryptLenth;		// 密钥长度，当前为AES算法类型时，表示密钥位数(目前支持128，192，256位三种, 如: wEncryptLenth为128，则密钥信息ENCRYPT_KEY_INFO里的byAesKey[0]~[15])
	CFG_ENCRYPT_KEY_INFO		stuEncryptKeys;		// 通道的密钥信息 
	CFG_NET_TIME				stuPreTime;			// 加密计划的开始时间
}CFG_STREAM_ENCRYPT_INFO;

//码流加密配置通道信息
typedef struct tagCFG_ENCODE_ENCRYPT_CHN_INFO
{
	int						 nChannelID;					// 通道号(0开始)
	CFG_STREAM_ENCRYPT_INFO *pstEncodeEncryptInfo;			// 每个通道的配置列表,用户需配置
												            // nMaxEncryptInputs个CFG_STREAM_ENCRYPT
	BYTE					 nMaxEncryptInputs; 
	BYTE					 nRetEncryptOutputs;			// 解析出CFG_STREAM_ENCRYPT的个数
}CFG_ENCODE_ENCRYPT_CHN_INFO;


//编码自适应策略类型
typedef  enum tagCFG_ENCRYPT_POLICY_TYPE
{
	ENCRYPT_POLICY_UNKNOWN ,		//未知
	ENCRYPT_POLICY_NONE ,		//无策略，不开启自适应功能
	ENCRYPT_POLICY_QUALITY ,    //画质优先，优先保证分辨率，降低帧率
	ENCRYPT_POLICY_FLUENCY ,	//流畅优先，优先保证流畅性，降低分辨率
}CFG_ENCRYPT_POLICY_TYPE;

//编码流畅优先策略
typedef enum tagCFG_ENCRYPT_FLUENCY_MODE
{
	ENCRYPT_FLUENCY_UNKNOWN ,		//未知
	ENCRYPT_FLUENCY_FAST ,			//快恢复(网速变好时，立即恢复)
	ENCRYPT_FLUENCY_SLOW ,			//慢恢复(同一时间只能有一个通道恢复)
	ENCRYPT_FLUENCY_SYNC ,			//同步恢复(如果有通道下降，则其它通道不恢复)
	ENCRYPT_FLUENCY_SLOWSYNC ,		//慢同步恢复(结合慢恢复和同步恢复)
}CFG_ENCRYPT_FLUENCY_MODE;

//编码自适应配置
typedef struct tagCFG_ENCODE_ADAPT_INFO
{
	CFG_ENCRYPT_POLICY_TYPE		emPolicyType;		//自适应策略类型
	CFG_ENCRYPT_FLUENCY_MODE	emFluencyMode;		//流畅优先策略
}CFG_ENCODE_ADAPT_INFO;

// 变倍设置基本信息单元
typedef struct tagCFG_VIDEO_IN_ZOOM_UNIT
{
	int         nSpeed;									 //变倍速率(0~7)
	BOOL		bDigitalZoom;							 //是否数字变倍
	int			nZoomLimit;								 //当前速率下最大变倍上限(0~13)。
} CFG_VIDEO_IN_ZOOM_UNIT;

// 单通道变倍设置基本信息
typedef struct tagCFG_VIDEO_IN_ZOOM	
{
	int						nChannelIndex;				 //通道号
	int						nVideoInZoomRealNum;		 //配置使用个数
	CFG_VIDEO_IN_ZOOM_UNIT  stVideoInZoomUnit[MAX_VIDEO_IN_ZOOM];		 //通道变速配置单元信息
	
} CFG_VIDEO_IN_ZOOM;

// 抓图配置
typedef struct tagCFG_SNAP_INFO 
{
	CFG_TIME_SCHEDULE		stuTimeSchedule;			// 时间表, 每个时间段掩码按位定义如下: 
														// Bit0-定时抓图
														// Bit1-动态检测抓图
														// Bit2-报警抓图
														// Bit3-卡号抓图
														// Bit4~Bit31-保留
} CFG_SNAP_INFO;

//云台转动角度范围，单位：度
typedef struct tagCFG_PTZ_MOTION_RANGE
{
	int                 nHorizontalAngleMin;       // 水平角度范围最小值,单位:度
	int                 nHorizontalAngleMax;       // 水平角度范围最大值,单位:度
	int                 nVerticalAngleMin;          // 垂直角度范围最小值,单位:度
	int                 nVerticalAngleMax;          // 垂直角度范围最大值,单位:度
}CFG_PTZ_MOTION_RANGE;

//支持的焦距模式对应枚举
typedef enum tagSUPPORT_FOCUS_MODE
{
    ENUM_SUPPORT_FOCUS_CAR        = 1,                // 看清车模式         
	ENUM_SUPPORT_FOCUS_PLATE      = 2,                // 看清车牌模式 
	ENUM_SUPPORT_FOCUS_PEOPLE     = 3,                // 看清人模式     
	ENUM_SUPPORT_FOCUS_FACE       = 4,                // 看清人脸模式     
}EM_SUPPORT_FOCUS_MODE;

//云台转动角度范围，单位：度
typedef struct tagCFG_PTZ_LIGHTING_CONTROL
{
	char                szMode[CFG_COMMON_STRING_32];  // 手动灯光控制模式
	                                                   // on-off"：直接开关模式,
	                                                   // "adjustLight"：手动调节亮度模式

	DWORD               dwNearLightNumber;             // 近光灯组数量
	DWORD               dwFarLightNumber;              // 远光灯组数量
}CFG_PTZ_LIGHTING_CONTROL;

//获取云台能力集信息
typedef struct tagCFG_PTZ_PROTOCOL_CAPS_INFO
{
	int                 nStructSize;
    BOOL                bPan;                       // 是否支持云台水平摆动
	BOOL                bTile;                      // 是否支持云台垂直摆动
	BOOL                bZoom;                      // 是否支持云台变倍
	BOOL                bIris;                      // 是否支持云台光圈调节
	BOOL                bPreset;                    // 是否支持预置点
	BOOL                bRemovePreset;              // 是否支持清除预置点
	BOOL                bTour;                      // 是否支持自动巡航线路
	BOOL                bRemoveTour;                // 是否支持清除巡航
	BOOL                bPattern;                   // 是否支持轨迹线路
	BOOL                bAutoPan;                   // 是否支持自动水平摆动
	BOOL                bAutoScan;                  // 是否支持自动扫描
	BOOL                bAux;                       // 是否支持辅助功能
	BOOL                bAlarm;                     // 是否支持报警功能
	BOOL                bLight;                     // 是否支持灯光, 内容见下面"stuPtzLightingControl"
	BOOL                bWiper;                     // 是否支持雨刷
	BOOL                bFlip;                      // 是否支持镜头翻转
	BOOL                bMenu;                      // 是否支持云台内置菜单
	BOOL                bMoveRelatively;            // 是否支持云台按相对坐标定位
	BOOL                bMoveAbsolutely;            // 是否支持云台按绝对坐标定位
	BOOL                bReset;                     // 是否支持云台复位
	BOOL                bGetStatus;                 // 是否支持获取云台运动状态及方位坐标
	BOOL                bSupportLimit;              // 是否支持限位
	BOOL                bPtzDevice;                 // 是否支持云台设备
	BOOL                bIsSupportViewRange;        // 是否支持云台可视域

	WORD				wCamAddrMin;		    	// 通道地址的最小值
	WORD				wCamAddrMax;			    // 通道地址的最大值
	WORD				wMonAddrMin;    			// 监视地址的最小值
	WORD				wMonAddrMax;	    		// 监视地址的最大值
	WORD				wPresetMin;			    	// 预置点的最小值
	WORD				wPresetMax;				    // 预置点的最大值
	WORD				wTourMin;    				// 自动巡航线路的最小值
	WORD				wTourMax;	    			// 自动巡航线路的最大值
	WORD				wPatternMin;	    		// 轨迹线路的最小值
	WORD				wPatternMax;		    	// 轨迹线路的最大值
	WORD				wTileSpeedMin;			    // 垂直速度的最小值
	WORD				wTileSpeedMax;    			// 垂直速度的最大值
	WORD				wPanSpeedMin;	    		// 水平速度的最小值
	WORD				wPanSpeedMax;		    	// 水平速度的最大值
	WORD				wAutoScanMin;			    // 自动扫描的最小值
	WORD				wAutoScanMax;    			// 自动扫描的最大值
	WORD				wAuxMin;		    		// 辅助功能的最小值
	WORD				wAuxMax;			    	// 辅助功能的最大值

	DWORD				dwInterval;				    // 发送命令的时间间隔
	DWORD				dwType;				        // 协议的类型，0-本地云台，1-远程云台
	DWORD				dwAlarmLen;				    // 协议的报警长度
	DWORD				dwNearLightNumber;		    // 近光灯组数量,0~4,为0时表示不支持
	DWORD				dwFarLightNumber;		    // 远光灯组数量,0~4,为0时表示不支持

	DWORD               dwSupportViewRangeType;     // 支持的可视域数据获取方式掩码,从低位到高位依次数,目前支持
	                                                // 第1位:为1表示支持"ElectronicCompass" 电子罗盘方式

	DWORD               dwSupportFocusMode;         // 支持的支持的焦距模式掩码,从低位到高位依次数,见#EM_SUPPORT_FOCUS_MODE
	                  
	char				szName[MAX_PROTOCOL_NAME_LEN];                       // 操作的协议名
	char                szAuxs[CFG_COMMON_STRING_32][CFG_COMMON_STRING_32];  //云台辅助功能名称列表

	CFG_PTZ_MOTION_RANGE stuPtzMotionRange;         // 云台转动角度范围，单位：度
	CFG_PTZ_LIGHTING_CONTROL stuPtzLightingControl; // 灯光控制内容
	BOOL				bSupportPresetTimeSection;	// 是否支持预置点时间段配置的功能
}CFG_PTZ_PROTOCOL_CAPS_INFO;
// 特殊用途目录定义
typedef struct tagCFG_SPECIAL_DIR_INFO 
{
	char				szBackgroudImageDir[MAX_PATH];	// 屏幕底图目录
	char				szWindowIconDir[MAX_PATH];		// 窗口图标目录
	char				szEventVoiceDir[MAX_PATH];		// 报警语音提示音频文件存放目录
} CFG_SPECIAL_DIR_INFO;


// 关机后延时自动开机配置
typedef struct tagCFG_AUTO_STARTUP_DELAY_INFO
{
	BOOL	bEnable;		//功能是否打开           
	int		nDelay;			//关机后延时开机时间,单位：分钟(取值范围[30, 255])       
}CFG_AUTO_STARTUP_DELAY_INFO;

// 视频输入能力集(CFG_CAP_CMD_VIDEOINPUT_EX)扩展配置
typedef struct tagCFG_CAP_VIDEOINPUT_INFO_EX
{
	BOOL            bSupportDefog;                          // 是否支持透雾功能
	BOOL			bSupportABFFunction;					// 是否支持自动调后焦功能
	BOOL			bSupportImageStabilization;				// 是否支持电子防抖功能

	BOOL			bSupportKillShutLine;					// 是否支持消除快门线功能
	int             nMinKillShutLine;						// 可配的最小值
	int			    nMaxKillShutLine;						// 可配的最大值

    BOOL            bSupportVideoInColor;	                //是否支持图像设置能力		 
    BOOL            bSupportBrightness;                 	//是否支持亮度	
    BOOL            bSupportContrast;                       //是否支持对比度       	
    BOOL            bSupportSaturation;                     //是否支持饱和度	
    BOOL            bSupportHue;                            //是否支持色度	
    BYTE            bReserved[3];                           //字节对齐

}CFG_CAP_VIDEOINPUT_INFO_EX;

// CAN过滤配置
#define MAX_CAN_COUNT	16			// 最大CAN个数

// CAN 过滤策略
typedef enum tagCFG_CAN_POLICY_METHOD
{
	CFG_CAN_POLICY_METHOD_UNKONW,		// 未知策略
	CFG_CAN_POLICY_METHOD_NONE,			// 无过滤
	CFG_CAN_POLICY_METHOD_WHITE,		// 白名单
	CFG_CAN_POLICY_METHOD_BLACK,		// 黑名单
}CFG_CAN_POLICY_METHOD;

typedef struct tagCFG_CANFILTER_INFO
{
	int						nResponseTimeout;			// 等待应答超时(单位:毫秒)， 发送数据后，等待3000毫秒后，结束该路透传
	int						nRequestTimeout;			// 接收请求应答超时(单位:毫秒)， 超过指定时间未收到数据，认为请求结束
	int						nFilterPIDCount;			// 数据号个数
	int						nRetFiterPIDCount;			// 返回数据号个数
	int*					pnFilterPID;				// 过滤数据号
	CFG_CAN_POLICY_METHOD	emPolicy;					// 过滤策略
														// 如果是白名单，上报包含PID的数据
														// 如果是黑名单，上报不含PID的数据
														// 无过滤则所有数据都上报																
}CFG_CANFILTER_INFO;

typedef struct tagCFG_CANFILTER_LIST
{
	int						nCANCount;			// CAN个数
	int						nRetCANCount;		// 设备返回CAN个数
	CFG_CANFILTER_INFO		stuCANFilter[MAX_CAN_COUNT];			
}CFG_CANFILTER_LIST;

// 聚焦极限对应枚举
typedef enum tagEM_FOCUS_LIMIT_SELECT_MODE
{
    EM_FOCUS_LIMIT_MODE_MANUAL,                // "Manual" 自动
    EM_FOCUS_LIMIT_MODE_AUTO,                  // "Auto"手动
    EM_FOCUS_LIMIT_MODE_INVALID
}EM_FOCUS_LIMIT_SELECT_MODE;

// 聚焦设置基本信息单元
typedef struct tagCFG_VIDEO_IN_FOCUS_UNIT
{
	int                        nMode;                   // 聚焦模式, 0-关闭, 1-辅助聚焦, 2-自动聚焦, 3-半自动聚焦, 4-手动聚焦
	int                        nSensitivity;            // 聚焦灵敏度, 0-高, 1-默认, 2-低
	int                        nIRCorrection;           // 红外光聚焦修正, 0-不修正, 1-修正, 2-自动修正
	EM_FOCUS_LIMIT_SELECT_MODE emFocusMode;             // 聚焦极限
	int	                       nFocusLimit;				// 聚焦极限值, 单位毫米
} CFG_VIDEO_IN_FOCUS_UNIT;

// 单通道聚焦设置基本信息
typedef struct tagCFG_VIDEO_IN_FOCUS	
{
	int						 nChannelIndex;				             // 通道号
	int						 nVideoInFocusRealNum;		             // 配置使用个数
	CFG_VIDEO_IN_FOCUS_UNIT  stVideoInFocusUnit[MAX_VIDEO_IN_FOCUS]; //通道聚焦配置单元信息
	
} CFG_VIDEO_IN_FOCUS;

typedef enum tagEM_ANALYSE_MODE
{
	EM_ANALYSE_MODE_REAL_STREAM,                            // 实时流模式     
	EM_ANALYSE_MODE_RECORDFILE_STREAM,                      // 录像文件流模式
	EM_ANALYSE_MODE_PICFILE_STREAM,                         // 图片文件流模式
}EM_ANALYSE_MODE;

// 智能分析模式
typedef struct tagCFG_ANALYSE_MODE
{
	EM_ANALYSE_MODE emMode;                                 // 分析模式，详见EM_ANALYSE_MODE 
}CFG_ANALYSE_MODE;

// 云台控制预置点结构
typedef struct tagPTZ_PRESET
{
	BOOL                 bEnable;                             // 该预置点是否生效
	char                 szName[MAX_PTZ_PRESET_NAME_LEN];     // 预置点名称
	CFG_PTZ_SPACE_UNIT   stPosition;                          // 预置点的坐标和放大倍数
}PTZ_PRESET;

// 云台预置点配置对应结构
typedef struct tagPTZ_PRESET_INFO
{
	DWORD              dwMaxPtzPresetNum;                     // 最大预置点个数
	DWORD              dwRetPtzPresetNum;                     // 实际使用预置点个数
	PTZ_PRESET         *pstPtzPreset;                         // 预置点信息(根据最大个数申请内存)
}PTZ_PRESET_INFO;

// 语音激励音频通道配置
typedef struct tagCFG_AUDIO_SPIRIT_CHANNE
{
	int				nChannel;				// 语音激励联动视频通道号
	int				nPriority;				// 语音激励优先级, 1~10
	int				nPreset;				// 对应的视频摄像机的预置点, 与云台一致0~255
} CFG_AUDIO_SPIRIT_CHANNEL;

// 语音激励联动项
typedef struct tagCFG_AUDIO_SPIRIT_LINKAGE 
{
	int				nOutputNum;				// 矩阵输出口数量
	int				nOutputChanel[CFG_MAX_LOWER_MATRIX_OUTPUT];	// 同步大画面输出到(多个)矩阵输出口
} CFG_AUDIO_SPIRIT_LINKAGE;

// 语音激励
typedef struct tagCFG_AUDIO_SPIRIT 
{
	BOOL				bEnable;			// 使能
	int					nAudioLimit;		// 激励音量阈值, 0~100
	int					nDelayTime;			// 激励延时时间, 单位: 秒
	CFG_AUDIO_SPIRIT_CHANNEL* pstuChannels;	// 语音激励音频通道属性
	int					nChannelCount;		// 音频通道数
	CFG_AUDIO_SPIRIT_LINKAGE stuLinkage;	// 激励联动项
} CFG_AUDIO_SPIRIT;

// 合成通道配置
typedef struct tagCFG_COMPOSE_CHANNEL 
{
	CFG_SPLITMODE	emSplitMode;			// 分割模式
	int				nChannelCombination[MAX_VIDEO_CHANNEL_NUM]; // 割模式下的各子窗口显示内容
	int				nChannelCount;			// 分割窗口数量
} CFG_COMPOSE_CHANNEL;

// 下位矩阵输出配置
typedef struct tagCFG_LOWER_MATRIX_OUTPUT
{
	char					szName[CFG_COMMON_STRING_128]; // 输出通道名称
	CFG_SPLITMODE			emSplitMode;		// 分割模式
	int						nInputs[CFG_MAX_LOWER_MATRIX_INPUT]; // 输入通道组
	int						nInputCount;		// 输入通道数
} CFG_LOWER_MATRIX_OUTPUT;

// 下位矩阵信息
typedef struct tagCFG_LOWER_MATRIX_INFO 
{
	int						nOutputCount;			// 输出通道数
	CFG_LOWER_MATRIX_OUTPUT	stuOutputs[CFG_MAX_LOWER_MATRIX_OUTPUT]; // 输出通道配置
} CFG_LOWER_MATRIX_INFO;

// 下位矩阵配置
typedef struct tagCFG_LOWER_MATRIX_LIST
{
	int						nMatrixCount;		// 下位矩阵数量
	CFG_LOWER_MATRIX_INFO	stuMatrix[CFG_MAX_LOWER_MATRIX_NUM]; // 下位矩阵数组
} CFG_LOWER_MATRIX_LIST;

// 开始与结束日期
typedef struct tagCFG_DAYTIME_INFO
{
	int					nBeginMonth;		// 开始时间 月份
	int					nBeginDay;			// 开始时间 日期
	int					nEndMonth;			// 结束时间 月份
	int					nEndDay;			// 结束时间	日期
}CFG_DAYTIME_INFO;

// 时间段限速值配置
typedef struct tagCFG_TIMESPEEDLIMIT_INFO
{
	BOOL				bEnable;			// 速度限制开启
	CFG_DAYTIME_INFO	stuDayTime;			// 时间段开始与结束日期
	int					nDaySpeedLimit;		// 白天限速值，单位km/h
	int					nNightSpeedLimit;	// 晚上限速值，单位km/h
	CFG_TIME_SECTION	stuTimeSection;		// 白天时间段范围，掩码无效
}CFG_TIMESPEEDLIMIT_INFO;

typedef struct tagCFG_TIMESPEEDLIMIT_LIST
{
	int						nTimeSpeedLimitCount;		// 限速时间段个数
	CFG_TIMESPEEDLIMIT_INFO stuTimeSpeedLimit[MAX_TIMESPEEDLIMIT_NUM];
}CFG_TIMESPEEDLIMIT_LIST;

// 语音提示时间
typedef struct tagCFG_ALERTTIME_INFO
{
	int				nHour;				// 小时
	int				nMinute;			// 分钟
}CFG_ALERTTIME_INFO;

// 语音提示配置
typedef struct tagCFG_VOICEALERT_INFO
{
	CFG_ALERTTIME_INFO	stuAlertTime;							// 语音提醒时间点，定时提醒
	int					nIntervalTime;							// 提醒间隔时，单位秒
	char				szWarnText[CFG_COMMON_STRING_256];		// 语音提醒内容，用户自定义
}CFG_VOICEALERT_INFO;

typedef struct tagCFG_VOICEALERT_LIST
{
	int					nVoiceAlertCount;					// 语音提示个数
	CFG_VOICEALERT_INFO stuVoiceAlert[MAX_VOICEALERT_NUM];
}CFG_VOICEALERT_LIST;

// 红外面板按键
typedef struct tagCFG_INFRARED_KEY 
{
	char			szName[CFG_COMMON_STRING_32];	// 面板按键名称
	char			szText[CFG_COMMON_STRING_64];	// 面板按键显示文字，按钮label
} CFG_INFRARED_KEY;

// 红外面板模板
typedef struct tagCFG_INFRARED_BOARD_TEMPLATE 
{
	unsigned int	nID;							// 面板模板编号
	char			szName[CFG_COMMON_STRING_64];	// 面板品牌型号定义
	unsigned int	nCategory;						// 面板类型, 大类, 0-DVD, 1-TV
	int				nKeyNum;						// 面板按键数量
	CFG_INFRARED_KEY stuKeys[CFG_MAX_INFRARED_KEY_NUM];	// 面板按键
} CFG_INFRARED_BOARD_TEMPLATE;

// 红外面板模板组
typedef struct tagCFG_INFRARED_BOARD_TEMPLATE_GROUP 
{
	int			nTemplateNum;		// 模板数量
	CFG_INFRARED_BOARD_TEMPLATE stuTemplates[CFG_MAX_INFRARED_BOARD_TEMPLATE_NUM];	// 红外面板模板
} CFG_INFRARED_BOARD_TEMPLATE_GROUP;

// 红外面板
typedef struct tagCFG_INFRARED_BOARD 
{
	unsigned int	nID;							// 面板编号, 唯一标示
	char			szName[CFG_COMMON_STRING_64];	// 面板控制外设名称, 用户自定义
	unsigned int	nCategory;						// 面板类型, 0-DVD, 1-TV
	int				nCommPort;						// 红外通讯端口
	unsigned int	nTemplateID;					// 关联的模板ID
} CFG_INFRARED_BOARD;

// 红外面板组
typedef struct tagCFG_INFRARED_BOARD_GROUP
{
	int				nBoardNum;						// 红外面板数量
	CFG_INFRARED_BOARD stuBoards[CFG_MAX_INFRARED_BOARD_NUM];	// 红外面板信息		
} CFG_INFRARED_BOARD_GROUP;

// 设备保活配置
typedef struct tagCFG_DEVICEKEEPALIVE_INFO
{
	BOOL	bEnable;		// 开启保活使能
	int		nInterval;		// 保活时间间隔，必须是>=10的值，单位：秒
	int		nFailTimes;		// 保活失败次数，保活失败次数到达该值认为设备断线
	int		nWaitBootTime;	// 等待外设加电后启动后检测保活心跳，单位：秒
}CFG_DEVICEKEEPALIVE_INFO;

// 设备曝光配置基本信息
typedef struct tagCFG_VIDEOIN_EXPOSURE_BASE
{
    BOOL        bSlowShutter;           // 慢快门使能

    BYTE        byExposureMode;         // 曝光模式调节
    BYTE        byAntiFlicker;			// 防闪烁模式 0-Outdoor 1-50Hz防闪烁 2-60Hz防闪烁
    BYTE        byCompensation;         // 曝光补偿, [0~14]
    BYTE        byAutoGainMax;          // 自动增益上限, [0, 2]
    BYTE        byGain;                 // 增益档位, [0, 15]
    BYTE        bySlowAutoExposure;     // 慢曝光, [0, 15]
    BYTE        bybyReserv[2];          // 字节对齐
    int         byExposureSpeed;        // 曝光速度等级：0-自动曝光，1-曝光等级1，2-曝光等级2…n-1最大曝光等级数 n带时间上下限的自动曝光 n+1自定义时间手动曝光 (n为支持的曝光等级)
    BYTE        bySlowSpeed;            // 慢曝光等级
    BYTE        byIris;                 // 光圈设置, [0~17]
    BYTE        byBacklight;            // 背光补偿: 取值范围取决于设备能力集: 0-关闭 1-启用 2-指定区域背光补偿
    BYTE        byWideDynamicRange;     // 宽动态值 0-关闭，1~100-为真实范围值
    BYTE        byWideDynamicRangeMode; // 宽动态模式, 0:关闭; 1:手动调节; 2:自动调节
    BYTE        byGlareInhibition;      // 强光抑制, 0:关闭; 1:弱; 2:中; 3:强
    BYTE        byDoubleExposure;       // 双快门支持, 0:不支持; 1:支持双快门全帧率; 2:支持双快门半帧率; 3:支持双快门全帧率和半帧率
    BYTE        byReserved;             // 字节对齐
    int         nRecoveryTime;          // 自动曝光恢复, 0-表示不恢复, 其他表示恢复的时间, 单位为秒

    float       fValue1;                // 自动曝光时间下限或者手动曝光自定义时间, [0.1~80ms]
    float       fValue2;                // 自动曝光时间上限, 需不小于下限, [0.1~80ms]

    CFG_RECT    stuBacklightRegion;     // 背光补偿区域
}CFG_VIDEOIN_EXPOSURE_BASE;

// 设备曝光配置
typedef struct tagCFG_VIDEOIN_EXPOSURE_INFO
{
    DWORD                       dwMaxExposureNum;       // 配置的最大个数
    DWORD                       dwRetExposureNum;       // 实际使用的最大个数(查询时返回实际解析个数, 封装时按照此值个数封装)
    CFG_VIDEOIN_EXPOSURE_BASE   *pstuVideoInExposure;   // 曝光配置信息
}CFG_VIDEOIN_EXPOSURE_INFO;

//////////////////////////////////////////////////////////////////////////
// 门禁基本配置

// 自定义开门方式
typedef enum tagCFG_DOOR_OPEN_METHOD
{
	CFG_DOOR_OPEN_METHOD_UNKNOWN = 0,
	CFG_DOOR_OPEN_METHOD_PWD_ONLY,                  // 只允许密码开锁
	CFG_DOOR_OPEN_METHOD_CARD,                      // 只允许刷卡开锁
	CFG_DOOR_OPEN_METHOD_PWD_OR_CARD,               // 密码或刷卡开锁
	CFG_DOOR_OPEN_METHOD_CARD_FIRST,                // 先刷卡后密码开锁
	CFG_DOOR_OPEN_METHOD_PWD_FIRST,                 // 先密码后刷卡开锁
	CFG_DOOR_OPEN_METHOD_SECTION,                   // 分时段开门
    CFG_DOOR_OPEN_METHOD_FINGERPRINTONLY = 7,       // 仅指纹开锁
    CFG_DOOR_OPEN_METHOD_PWD_OR_CARD_OR_FINGERPRINT = 8,// 密码或刷卡或指纹开锁
    CFG_DOOR_OPEN_METHOD_CARD_AND_FINGERPRINT = 11, // 刷卡+指纹开锁
    CFG_DOOR_OPEN_METHOD_MULTI_PERSON = 12,         // 多人开锁
}CFG_DOOR_OPEN_METHOD;


// 门禁单双向配置类型
typedef enum tagCFG_ACCESS_PROPERTY_TYPE
{
    CFG_ACCESS_PROPERTY_UNKNOWN = 0,
    CFG_ACCESS_PROPERTY_BIDIRECT,       // 双向门禁
    CFG_ACCESS_PROPERTY_UNIDIRECT,      // 单向门禁
}CFG_ACCESS_PROPERTY_TYPE;

#define CFG_MAX_ABLOCK_DOORS_NUM        4                       // 最大的门禁的互锁门通道数

// 门禁的AB互锁的组
typedef struct tagCFG_ABLOCK_DOOR_INFO 
{
    int                 nDoor;                                  // 有效互锁门的个数
    int                 anDoor[CFG_MAX_ABLOCK_DOORS_NUM];       // 互锁的门的通道号
}CFG_ABLOCK_DOOR_INFO;

#define CFG_MAX_ABLOCK_GROUP_NUM        8                       // 最大的互锁组数

// 门禁的AB互锁功能, 多个门通道，只有其他B通道都关闭，唯一的A通道才打开
typedef struct tagCFG_ABLOCK_INFO 
{
    BOOL                bEnable;                                // 使能
    int                 nDoors;                                 // 有效互锁组数
    CFG_ABLOCK_DOOR_INFO stuDoors[CFG_MAX_ABLOCK_GROUP_NUM];    // 互锁组信息
}CFG_ABLOCK_INFO;

// 门禁基本配置
typedef struct tagCFG_ACCESS_GENERAL_INFO
{
	char                szOpenDoorAudioPath[MAX_ADDRESS_LEN];   // 开门音频文件路径
	char                szCloseDoorAudioPath[MAX_ADDRESS_LEN];  // 关门音频文件路径
	char                szInUsedAuidoPath[MAX_ADDRESS_LEN];     // 有人音频文件路径
	char                szPauseUsedAudioPath[MAX_ADDRESS_LEN];  // 暂停使用音频文件路径 
	char                szNotClosedAudioPath[MAX_ADDRESS_LEN];  // 门未关音频文件路径
	char                szWaitingAudioPath[MAX_ADDRESS_LEN];    // 等待提示音频文件路径
	int                 nUnlockReloadTime;                      // 开锁命令响应间隔时间,单位秒，取值10、15(默认值)、20
	int                 nUnlockHoldTime;                        // 开锁输出保持时间,单位秒，取值1、2(默认)、3、4、5、6、9、15。 

	// 能力
	bool                abProjectPassword;
    bool                abAccessProperty;
    bool                abABLockInfo;
	BYTE				byReserved;

	char				szProjectPassword[MAX_PASSWORD_LEN];	// 工程密码
    CFG_ACCESS_PROPERTY_TYPE emAccessProperty;                  // 门禁通道单双向配置
    CFG_ABLOCK_INFO     stuABLockInfo;                          // AB互锁信息
}CFG_ACCESS_GENERAL_INFO;

// 门禁状态
typedef enum CFG_ACCESS_STATE
{
	ACCESS_STATE_NORMAL,                                        // 普通
	ACCESS_STATE_CLOSEALWAYS,                                   // 常关
	ACCESS_STATE_OPENALWAYS,                                    // 常开 
}CFG_ACCESS_STATE; 

// 门禁模式
typedef enum CFG_ACCESS_MODE
{
	ACCESS_MODE_HANDPROTECTED,                                  // 防夹模式
	ACCESS_MODE_SAFEROOM,                                       // 防护房间模式    
	ACCESS_MODE_OTHER,                                          // 其它
}CFG_ACCESS_MODE;


// 分时段开门
typedef struct tagCFG_DOOROPEN_TIMESECTION_INFO
{
	CFG_TIME_PERIOD			stuTime;				// 时间段
	CFG_DOOR_OPEN_METHOD	emDoorOpenMethod;		// 开门模式
}CFG_DOOROPEN_TIMESECTION_INFO;

#define MAX_DOOR_TIME_SECTION		4				// 门禁每天分时时间段最大个数

// 首卡权限验证通过后的门禁状态
typedef enum CFG_ACCESS_FIRSTENTER_STATUS
{
	ACCESS_FIRSTENTER_STATUS_UNKNOWN,	// 未知状态
	ACCESS_FIRSTENTER_STATUS_KEEPOPEN,	// KeepOpen-首卡权限验证通过后，门保持常开
	ACCESS_FIRSTENTER_STATUS_NORMAL		// Normal-首卡权限验证通过后，其他用户才能刷卡(指纹等)验证通过
}CFG_ACCESS_FIRSTENTER_STATUS;

// 首卡开门信息
typedef struct tagCFG_ACCESS_FIRSTENTER_INFO
{
	BOOL							bEnable;	// 在指定的时间,只有拥有首卡权限的用户验证通过后，其他的用户才能刷卡(指纹等)进入，TRUE 使能 FALSE 关闭
	CFG_ACCESS_FIRSTENTER_STATUS	emStatus;	// 首卡权限验证通过后的门禁状态
	int								nTimeIndex;	// 需要首卡验证的时间段, 值为通道号
}CFG_ACCESS_FIRSTENTER_INFO;

// 远程开门验证
typedef struct tagCFG_REMOTE_DETAIL_INFO 
{
    int                 nTimeOut;                       // 超时时间, 0表示永久等待, 其他值表示超时时间(单位为秒)
    BOOL                bTimeOutDoorStatus;             // 超时后的门状态, TRUE:打开, FALSE:关闭
}CFG_REMOTE_DETAIL_INFO;

// TimeOut info for handicap
typedef struct tagCFG_HANDICAP_TIMEOUT_INFO
{
    int                 nUnlockHoldInterval;            // 门锁保持时间(自动关门时间),单位毫秒,[250, 60000]  
    int                 nCloseTimeout;                  // 关门超时时间, 超过阈值未关会触发报警，单位秒,[0,9999];0表示不检测超时
}CFG_HANDICAP_TIMEOUT_INFO;

// 门禁事件配置
typedef struct tagCFG_ACCESS_EVENT_INFO
{
	char                szChannelName[MAX_NAME_LEN];	// 门禁通道名称
	CFG_ACCESS_STATE    emState;						// 门禁状态
	CFG_ACCESS_MODE     emMode;							// 门禁模式
	int					nEnableMode;					// 门禁使能电平值, 0:低电平有效(断电启动); 1:高电平有效(通电启动);
	BOOL                bSnapshotEnable;				// 事件联动抓图使能
	
    // 能力
	bool                abDoorOpenMethod;
    bool                abUnlockHoldInterval;
	bool                abCloseTimeout;
	bool                abOpenAlwaysTimeIndex;
	bool                abHolidayTimeIndex;
	bool                abBreakInAlarmEnable;
	bool				abRepeatEnterAlarmEnable;
	bool                abDoorNotClosedAlarmEnable;
	bool				abDuressAlarmEnable;
	bool                abDoorTimeSection;
	bool				abSensorEnable;
	bool				abFirstEnterEnable;
    bool                abRemoteCheck;
    bool                abRemoteDetail;
    bool                abHandicapTimeOut;
    bool                abCheckCloseSensor;

	CFG_DOOR_OPEN_METHOD	emDoorOpenMethod;			// 开门方式
	int					nUnlockHoldInterval;			// 门锁保持时间(自动关门时间),单位毫秒,[250, 20000]
	int					nCloseTimeout;					// 关门超时时间, 超过阈值未关会触发报警，单位秒,[0,9999];0表示不检测超时
	int					nOpenAlwaysTimeIndex;			// 常开时间段, 值为CFG_ACCESS_TIMESCHEDULE_INFO配置的数组下标
	int					nHolidayTimeRecoNo;				// 假期内时间段, 值为假日记录集的记录编号，对应NET_RECORDSET_HOLIDAY的nRecNo
	BOOL				bBreakInAlarmEnable;			// 闯入报警使能
	BOOL				bRepeatEnterAlarm;				// 反潜报警使能
	BOOL				bDoorNotClosedAlarmEnable;		// 门未关报警使能
	BOOL				bDuressAlarmEnable;				// 胁迫报警使能
	CFG_DOOROPEN_TIMESECTION_INFO	stuDoorTimeSection[WEEK_DAY_NUM][MAX_DOOR_TIME_SECTION];// 分时段开门信息
	BOOL				bSensorEnable;					// 门磁使能
	CFG_ACCESS_FIRSTENTER_INFO stuFirstEnterInfo;		// 首卡开门信息
    BOOL                bRemoteCheck;                   // 是否需要平台验证, TRUE表示权限通过后必须要平台验证后才能开门, FALSE表示权限验证通过后可立即开门
    CFG_REMOTE_DETAIL_INFO  stuRemoteDetail;            // 与bRemoteCheck配合使用, 如果远端验证未应答, 设定的设备超时时间到后, 是正常开门还是不开门
    CFG_HANDICAP_TIMEOUT_INFO   stuHandicapTimeOut;     // 针对残疾人的开门参数
    BOOL                bCloseCheckSensor;              // 闭锁前是否检测门磁
                                                        // true:则当开锁保持时间计时结束后，只有监测到有效门磁信号时，才可以恢复关闭锁的动作。
                                                        // 反之，如果开锁保持时间已到，但未检测到有效门磁信号，则一直保持开锁状态；
                                                        // false(默认):则直接按照设定的开锁保持时间进行开锁保持和恢复关闭的动作。
}CFG_ACCESS_EVENT_INFO;



// 门禁刷卡时间段
typedef struct tagCFG_ACCESS_TIMESCHEDULE_INFO 
{
	CFG_TIME_SECTION		stuTime[WEEK_DAY_NUM][MAX_DOOR_TIME_SECTION];	// 刷卡时间段
	BOOL					bEnable;										// 时间段使能开关
}CFG_ACCESS_TIMESCHEDULE_INFO;

//////////////////////////////////////////////////////////////////////////
// 无线网络连接配置

// 每日流量控制策略
enum EM_CFG_DAY3GFLUXTACTIC
{
	EM_CFG_DAY3GFLUXTACTIC_BYFLUX = 0,	// 按流量
	EM_CFG_DAY3GFLUXTACTIC_BYTIME,		// 按时间
};

// 接入的网络名称
enum EM_CFG_APN
{
	EM_CFG_APN_CTNET = 0,				// CTNET
};

// 流量报警策略
enum EM_CFG_DAY3GFLUXACTION
{
	EM_CFG_DAY3GFLUXACTION_NOTHING = 0,	// 无动作
	EM_CFG_DAY3GFLUXACTION_3GNETDOWN,	// 3G下线
};

typedef struct tagCFG_WIRELESS_INFO
{
	BOOL			        bEnable;					                // 2G网络使能
	int				        nKeepAlive;						            // 保活时间, 单位为秒，0表示一直连接，不自动断开
	EM_CFG_APN		        emAPN;							            // 接入的2G网络名称
	char			        szUseName[MAX_USERNAME_LEN];	            // 用户名
	char			        szPassword[MAX_PASSWORD_LEN];	            // 密码
	EM_CFG_DAY3GFLUXTACTIC	emDay3GFluxTactic;		                    // 每日流量控制策略
	DWORD			        dwDay3GFluxUp;					            // 每日流量使用上限, MB或者分钟
	DWORD			        dwDay3GFluxUse;					            // 当日的已用流量, MB或者分钟
    EM_CFG_DAY3GFLUXACTION	emDay3GFluxAction;		                    // 流量报警策略
	CFG_TIME_SECTION        stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT];// 拨号时间段
}CFG_WIRELESS_INFO;

#define MAX_CONNECTION_TYPE_LEN		32	// 连接方式的名字长度

// 登报时间类型
enum emCFG_REPORTWEEKDAY
{
	emReportWeekDay_DoNotReport = -1,	// 不登报
	emReportWeekDay_Sunday,				// 每周日定时登报
	emReportWeekDay_Monday,				// 每周一定时登报
	emReportWeekDay_Tuesday,			// 每周二定时登报
	emReportWeekDay_Wednesday,			// 每周三定时登报
	emReportWeekDay_Thursday,			// 每周四定时登报
	emReportWeekDay_Friday,				// 每周五定时登报
	emReportWeekDay_Saturday,			// 每周六定时登报
	emReportWeekDay_Everyday,			// 每天定时登报
};

// 报警服务器的配置
typedef struct tagCFG_ALARMSERVER_INFO
{
	BOOL			bEnable;								// 使能
	char			szProtocol[MAX_PROTOCOL_NAME_LEN];		// 协议类型, 目前支持"DAHUA"
	char			szConnection[MAX_CONNECTION_TYPE_LEN];	// 连接方式
	char			szAddress[MAX_ADDRESS_LEN];				// IP地址或网络名
	int				nPort;									// 端口号
	char			szUserName[MAX_USERNAME_LEN];			// 用户名
	char			szPsw[MAX_PASSWORD_LEN];				// 密码
	emCFG_REPORTWEEKDAY	emReportWeekDay;					// 登报日
	int				nHour;									// 登报时间点的时
	int				nMinute;								// 登报时间点的分
	int				nSecond;								// 登报时间点的秒
}CFG_ALARMSERVER_INFO;

#define MAX_ALARMSERVER_NUM		8

// 报警主机使用的报警中心及备用中心的配置
typedef struct tagCFG_ALARMCENTER_INFO
{
	CFG_ALARMSERVER_INFO	stuMainServer;						// 报警主机使用的报警中心服务器
	int						nBackupAlarmServerNum;				// 备用报警中心服务器的数目
	CFG_ALARMSERVER_INFO	stuBackupAlarmServer[MAX_ALARMSERVER_NUM];	// 备用报警中心服务器的配置
}CFG_ALARMCENTER_INFO;

//////////////////////////////////////////////////////////////////////////
// 布防、撤防配置
#define	MAX_SCENE_COUNT	8		//	最大情景模式个数
// 情景模式
enum emCFG_SCENE_MODE
{	
	emCFG_SCENE_MODE_UNKNOWN,			// 未知模式
	emCFG_SCENE_MODE_OUTDOOR,			// 外出模式
	emCFG_SCENE_MODE_INDOOR,			// 在家模式
};
typedef struct tagCFG_SCENE_INFO
{
	emCFG_SCENE_MODE emName;							// 模式名
	int				 nAlarmInChannelsCount;				// 报警通道个数
	int				 nRetAlarmInChannelsCount;			// 实际返回的报警通道个数
	int*			 pnAlarmInChannels;					// 启用的报警输入通道号列表，需用户分配内存
}CFG_SCENE_INFO;
typedef struct tagCFG_COMMGLOBAL_INFO	// =>CFG_CMD_COMMGLOBAL
{
	BOOL				bEnable;								// TRUE: 布防; FALSE: 撤防; 作用于整台设备，不区分通道
	BOOL				bSceneEnable;							// 是否启用情景模式
	emCFG_SCENE_MODE	emCurrentScene;							// 当前选择的情景模式
	int					nSceneCount;							// 情景模式有效个数
	CFG_SCENE_INFO		stuScense[MAX_SCENE_COUNT];			// 情景模式定义，每个模式对应一个配置
}CFG_COMMGLOBAL_INFO;

#define MAX_ALARM_LIMITS_NUM    8                                   // 报警限值最大个数

// 模拟量报警输入通道配置
typedef struct tagCFG_ANALOGALARM_INFO	// =>CFG_CMD_ANALOGALARM
{
	BOOL				bEnable;									// 使能开关(整台设备处于布防且该通道非使能时为旁路)
	char				szChnName[MAX_CHANNELNAME_LEN];				// 报警通道名称
	float				fUpperLimit;								// 量程上限
	float				fLowerLimit;								// 量程下限
	int					nSensitivity;								// 灵敏度, 单位：百分比
	float				fCompensation;								// 补偿值, 根据传感器类型而定
	float				fLimit1;									// 报警限1, 不建议使用, 建议使用fAlarmLimits字段
	float				fLimit2;									// 报警限2, 不建议使用, 建议使用fAlarmLimits字段
	float				fLimit3;									// 报警限3, 不建议使用, 建议使用fAlarmLimits字段
	float				fLimit4;									// 报警限4, 不建议使用, 建议使用fAlarmLimits字段
	BYTE				byMode;										// 报警模式, 掩码表示, 可能如下值1111、1110、1100、1000、0000
																	// 1表示超过报警阈值，0表示低于报警阈值
																	// 模式从左到右分别对应4个报警阈值, 依次递增
																	// 例：1110表示超过第1、2、3个报警阈值, 并低于第4个报警阈值
	BYTE				byReserve[3];								// 保留字节
	CFG_ALARM_MSG_HANDLE	stuEventHandler;						// 报警联动
	CFG_TIME_SECTION	stuTimeSection[WEEK_DAY_NUM][MAX_REC_TSECT];// 事件响应时间段
	EM_SENSE_METHOD		emSense;									// 传感器方式
	char				szSensorType[CFG_COMMON_STRING_64];			// 传感器类型
    int                 nSlot;                                      // 根地址, 0表示本地通道, 1表示连接在第一个串口上的扩展通道, 2、3...以此类推, -1表示无效
	int                 nLevel1;                                    // 第一级级联地址, 表示连接在第nSlot串口上的第nLevel1个探测器或仪表, 从0开始, -1表示无效
    bool                abLevel2;                                   // 表示nLevel2字段是否存在
    int                 nLevel2;                                    // 第二级级联地址, 表示连接在第nLevel1个的仪表上的探测器序号, 从0开始
    int                 nAlamrLimits;                               // 有效的报警限值个数
    float               fAlarmLimits[MAX_ALARM_LIMITS_NUM];         // 报警限值
    int                 nNotifyInterval;                            // 模拟量上传周期, 单位: 秒
    int                 nAlarmInterval;                             // 触发上下限后的上传周期, 单位: 秒
}CFG_ANALOGALARM_INFO;

// 报警输出通道的状态的配置
typedef struct tagCFG_ALARMOUT_INFO		// =>CFG_CMD_ALARMOUT
{
	int					nChannelID;									// 报警通道号(0开始)
	char				szChnName[MAX_CHANNELNAME_LEN];				// 报警通道名称
	char				szOutputType[MAX_NAME_LEN];					// 输出类型, 用户自定义
	int					nOutputMode;								// 输出模式, 0-自动报警, 1-强制报警, 2-关闭报警
    int                 nPulseDelay;                                // 脉冲模式输出时间, 单位为秒(0-255秒)
    int                 nSlot;                                      // 根地址, 0表示本地通道, 1表示连接在第一个串口上的扩展通道, 2、3...以此类推, -1表示无效
    int                 nLevel1;                                    // 第一级级联地址, 表示连接在第nSlot串口上的第nLevel1个探测器或仪表, 从0开始, -1表示无效
    bool                abLevel2;                                   // 表示nLevel2字段是否存在
    int                 nLevel2;                                    // 第二级级联地址, 表示连接在第nLevel1个的仪表上的探测器序号, 从0开始
}CFG_ALARMOUT_INFO;


// 时区定义(NTP)
typedef enum __EM_CFG_TIME_ZONE_TYPE
{
	EM_CFG_TIME_ZONE_0,								// {0, 0*3600,"GMT+00:00"}
	EM_CFG_TIME_ZONE_1,								// {1, 1*3600,"GMT+01:00"}
	EM_CFG_TIME_ZONE_2,								// {2, 2*3600,"GMT+02:00"}
	EM_CFG_TIME_ZONE_3,								// {3, 3*3600,"GMT+03:00"}
	EM_CFG_TIME_ZONE_4,								// {4, 3*3600+1800,"GMT+03:30"}
	EM_CFG_TIME_ZONE_5,								// {5, 4*3600,"GMT+04:00"}
	EM_CFG_TIME_ZONE_6,								// {6, 4*3600+1800,"GMT+04:30"}
	EM_CFG_TIME_ZONE_7,								// {7, 5*3600,"GMT+05:00"}
	EM_CFG_TIME_ZONE_8,								// {8, 5*3600+1800,"GMT+05:30"}
	EM_CFG_TIME_ZONE_9,								// {9, 5*3600+1800+900,"GMT+05:45"}
	EM_CFG_TIME_ZONE_10,							// {10, 6*3600,"GMT+06:00"}
	EM_CFG_TIME_ZONE_11,							// {11, 6*3600+1800,"GMT+06:30"}
	EM_CFG_TIME_ZONE_12,							// {12, 7*3600,"GMT+07:00"}
	EM_CFG_TIME_ZONE_13,							// {13, 8*3600,"GMT+08:00"}
	EM_CFG_TIME_ZONE_14,							// {14, 9*3600,"GMT+09:00"}
	EM_CFG_TIME_ZONE_15,							// {15, 9*3600+1800,"GMT+09:30"}
	EM_CFG_TIME_ZONE_16,							// {16, 10*3600,"GMT+10:00"}
	EM_CFG_TIME_ZONE_17,							// {17, 11*3600,"GMT+11:00"}
	EM_CFG_TIME_ZONE_18,							// {18, 12*3600,"GMT+12:00"}
	EM_CFG_TIME_ZONE_19,							// {19, 13*3600,"GMT+13:00"}
	EM_CFG_TIME_ZONE_20,							// {20, -1*3600,"GMT-01:00"}
	EM_CFG_TIME_ZONE_21,							// {21, -2*3600,"GMT-02:00"}
	EM_CFG_TIME_ZONE_22,							// {22, -3*3600,"GMT-03:00"}
	EM_CFG_TIME_ZONE_23,							// {23, -3*3600-1800,"GMT-03:30"}
	EM_CFG_TIME_ZONE_24,							// {24, -4*3600,"GMT-04:00"}
	EM_CFG_TIME_ZONE_25,							// {25, -5*3600,"GMT-05:00"}
	EM_CFG_TIME_ZONE_26,							// {26, -6*3600,"GMT-06:00"}
	EM_CFG_TIME_ZONE_27,							// {27, -7*3600,"GMT-07:00"}
	EM_CFG_TIME_ZONE_28,							// {28, -8*3600,"GMT-08:00"}
	EM_CFG_TIME_ZONE_29,							// {29, -9*3600,"GMT-09:00"}
	EM_CFG_TIME_ZONE_30,							// {30, -10*3600,"GMT-10:00"}
	EM_CFG_TIME_ZONE_31,							// {31, -11*3600,"GMT-11:00"}
	EM_CFG_TIME_ZONE_32,							// {32, -12*3600,"GMT-12:00"}
}EM_CFG_TIME_ZONE_TYPE;

// 时间同步服务器配置
typedef struct tagCFG_NTP_INFO
{
	BOOL				bEnable;									// 使能开关
	char				szAddress[MAX_ADDRESS_LEN];					// IP地址或网络名
	int					nPort;										// 端口号
	int					nUpdatePeriod;								// 更新周期，单位为分钟
	EM_CFG_TIME_ZONE_TYPE emTimeZoneType;							// 时区
	char				szTimeZoneDesc[MAX_NAME_LEN];				// 时区描述
}CFG_NTP_INFO;

// 警号配置
typedef struct tagCFG_ALARMBELL_INFO
{
    int                 nPersistentTime;                            // 警号输出持续时间, 单位: 分钟(0-99), 0 表示响一下就停止
}CFG_ALARMBELL_INFO;

#define MAX_MSG_NUMBER_LEN	32				// 短信号码的最大长度
#define MAX_RECEIVER_NUM	100				// 接收短信用户的最大数目

// 短信类型
typedef enum tagEM_MSG_TYPE
{
	EM_MSG_UNKNOWN = 0,												// 未知类型
	EM_MSG_SMS,														// SMS短信
	EM_MSG_MMS,														// MMS彩信
}EM_MSG_TYPE;

// 系统事件触发彩信/短信发送的配置
typedef struct tagCFG_EVENT_MSG_SENDING_INFO
{
	BOOL				bEnable;									// 使能开关
	EM_MSG_TYPE			emMsgType;									// 发送的信息的类型
	char				szTitle[MAX_NAME_LEN];						// 标题, 也就是短信/彩信的第一行文字
	DWORD				dwReceiverCount;							// 收信人号码的个数
	char				szReceiverNumbersList[MAX_RECEIVER_NUM][MAX_MSG_NUMBER_LEN];// 收信人号码
}CFG_EVENT_MSG_SENDING_INFO;

// 移动相关业务配置
typedef struct tagCFG_MOBILE_INFO
{
	CFG_EVENT_MSG_SENDING_INFO	stuEventMsgSending;					// 系统时间触发的发送短信/彩信的配置
}CFG_MOBILE_INFO;

#define MAX_CONTACT_NUM		100				// 联系人最大数目

// 电话语音提醒配置
typedef struct tagCFG_PHONEEVENTNOTIFY_INFO
{
	BOOL				bEnable;									// 使能开关
	DWORD				dwContactCount;								// 呼叫号码的个数
	char				szContactNumbersList[MAX_CONTACT_NUM][MAX_MSG_NUMBER_LEN];// 呼叫号码列表
}CFG_PHONEEVENTNOTIFY_INFO;

// 电话报警中心配置
enum CFG_EM_SIGNALTRANSMIT_MODE
{
	CFG_EM_SIGNALTRANSMIT_ERROR = 0,								// 未知模式
	CFG_EM_SIGNALTRANSMIT_DTMF_5S,									// "DTMF 5/S" - DTMF模式慢拨
	CFG_EM_SIGNALTRANSMIT_DTMF_10S,									// "DTMF 10/S" - DTMF模式快拨
};
enum CFG_EM_PSTN_PROTOCOL_TYPE
{
	CFG_EM_PSTN_PROTOCOL_ERROR = 0,									// 未知类型
	CFG_EM_PSTN_PROTOCOL_CID,										// "CID" - Contact ID Protocol
};
typedef struct tagCFG_PSTN_ALARM_SERVER_INFO
{
	char							szName[MAX_NAME_LEN];						// 电话报警中心名称
	char							szNumber[MAX_PHONE_NUMBER_LEN];				// 电话报警中心接收机号码
																				// "057188888888PPP888",格式为[号码][停顿时间][分机号码]，其中P表示停顿2秒。
	CFG_EM_PSTN_PROTOCOL_TYPE		emProtocol;									// 协议类型，
	CFG_EM_SIGNALTRANSMIT_MODE		emMode;										// 信号传输模式																															
	int								nTryCount;									// 拨号尝试次数
	int								nDelay;										// 拨号延时，单位：秒
	char							szAccount[MAX_PHONE_NUMBER_LEN];			// 用户号码
}CFG_PSTN_ALARM_SERVER_INFO;

typedef struct tagCFG_PSTN_ALARM_CENTER_INFO
{
	BOOL						bEnable;								// 使能开关
	int							nServerCount;							// 电话报警服务器个数
	CFG_PSTN_ALARM_SERVER_INFO	stuPSTNAlarmServer[MAX_PSTN_SERVER_NUM];		// 电话报警服务器
}CFG_PSTN_ALARM_CENTER_INFO;

// 音量输出配置
typedef struct tagCFG_AUDIO_OUTPUT_VOLUME
{
	int				nAudioOutputCount;									// 实际音频输出通道个数
	char			szAudioOutputVolume[MAX_AUDIO_OUTPUT_NUM];			// 每个元素对应一个音频输出通道的音量值,范围[0, 100]
}CFG_AUDIO_OUTPUT_VOLUME;


// 报警键盘配置
typedef struct tagCFG_ALARMKEYBOARD_INFO
{
	BOOL			bEnable;								// 使能开关
	char			szProtocolName[MAX_PROTOCOL_NAME_LEN];	// 协议名称
	int				nPort;									// 使用的串口端口号
	int				nAddress;								// 设备地址，如果串口上挂了多个串口设备，通过这个地址区分
	CFG_COMM_PROP	stuCommAttr;							// 串口属性
}CFG_ALARMKEYBOARD_INFO;

// 获取文件管理能力
typedef struct tagCFG_CAP_FILEMANAGER
{
	int			nMaxUploadFileSize;		// 最大的上传文件的大小, 单位: 字节
}CFG_CAP_FILEMANAGER;

// 获取设备报警联动能力
typedef struct tagCFG_CAP_EVENTMANAGER_INFO
{
	BOOL				bTimeSectionEnable;                               // 是否支持时间事件响应
	BOOL				bRecordEnable;                                    // 是否支持录像
	BOOL				bAlarmOutEnable;                                  // 是否支持报警输出
	BOOL				bPtzLinkEnable;                                   // 是否支持云台联动
	BOOL				bSnapshotEnable;                                  // 是否支持快照
	BOOL				bMailEnable;                                      // 是否支持发送邮件
	BOOL				bBeepEnable;                                      // 是否支持蜂鸣
	BOOL				bDejitterEnable;                                  // 是否支持去抖动
	BOOL				bTipEnable;										  // 是否支持本地消息框提示
	BOOL				bMonitorTourEnable;								  // 是否支持轮询联动配置
	BOOL				bMMSEnable;										  // 是否支持短消息
	BOOL				bSupportAlarmBell;								  // 是否支持警号输出
	BOOL				bSupportAccessControl;							  // 是否支持门禁控制
	BOOL				bSupportAlarmServer;							  // 是否支持上传至报警服务器
	BOOL				bSupportPtzLinkDelay;							  // 是否支持云台联动延迟
	BOOL				bSupportPSTNAlarmServer;						  // 是否支持上传至电话报警中心
}CFG_CAP_EVENTMANAGER_INFO;

// 电源故障配置
typedef struct tagCFG_POWERFAULT_ONE
{
	BOOL			bEnable;									// 使能开关
	CFG_ALARM_MSG_HANDLE stuEventHandler;						// 报警联动
}CFG_POWERFAULT_ONE;

typedef struct tagCFG_POWERFAULT_INFO
{
	int				nPowerCount;								// 电源个数
	CFG_POWERFAULT_ONE stuPowerFault[MAX_POWER_NUM];			// 报警联动
}CFG_POWERFAULT_INFO;

// 机箱入侵报警(防拆报警)配置
typedef struct tagCFG_CHASSISINTRUSION_INFO
{
	BOOL			bEnable;									// 使能开关
	CFG_ALARM_MSG_HANDLE stuEventHandler;						// 报警联动
}CFG_CHASSISINTRUSION_INFO;

// 紧急事件配置
typedef struct tagCFG_URGENCY_INFO 
{
	BOOL			bEnable;									// 使能开关
	CFG_ALARM_MSG_HANDLE stuEventHandler;						// 报警联动
}CFG_URGENCY_INFO;

/************************************************************************
** 扩展报警模块
***********************************************************************/
// 扩展模块报警输入配置
typedef struct tagCFG_EXALARMINPUT_INFO
{
	CFG_ALARMIN_INFO		stuAlarmIn;						// 报警输入参数，详见 CFG_ALARMIN_INFO
	
}CFG_EXALARMINPUT_INFO;

// 扩展模块报警输出配置
typedef struct tagCFG_EXALARMOUTPUT_INFO
{
	char		szChnName[MAX_CHANNELNAME_LEN];				// 报警通道名称
	int			nOutputMode;								// 输出模式, 0-自动报警, 1-强制报警, 2-关闭报警
}CFG_EXALARMOUTPUT_INFO;

// 扩展模块报警盒配置
typedef struct tagCFG_EXALARMBOX_INFO
{
	BOOL			bEnable;								// 使能开关
	char			szProtocolName[MAX_PROTOCOL_NAME_LEN];	// 协议名称
	int				nPort;									// 使用的串口端口号
	int				nAddress;								// 设备地址
	CFG_COMM_PROP	stuCommAttr;							// 串口属性
}CFG_EXALARMBOX_INFO;

// 扩展报警盒协议类型
enum CFG_EM_EXALARM_PROTOCOL_TYPE
{
	CFG_EM_EXALARM_PROTOCOL_ERROR,								// 未知类型
	CFG_EM_EXALARM_PROTOCOL_DH_ALARMBOX,						// DH_AlarmBox 大华报警盒协议
};


// 扩展模块报警能力集
typedef struct tagCFG_CAP_EXALARM_INFO
{	
	int					 nAlarmInCount;											// 扩展报警模块输入个数
	int					 nAlarmOutCount;										// 扩展报警模块速出个数
	int				 	 nMaxDelay;												// 延时防区的最大延时时间,单位为秒，只有支持延时防区时此字段才有效。
	int					 nDefenceAreaTypeNum;									// 防区类型种类数,为0表示无此字段时报警输入不作为防区使用。
	EM_CFG_DEFENCEAREATYPE	emDefenceAreaType[MAX_ALARM_DEFENCE_TYPE_NUM];		// 支持防区类型 
	int					 nExAlarmChannelNum;									// 扩展模块报警通道数,为了保持兼容性,此为0时表示每个通道支持所有类型的传感器
	CFG_EXALARM_SENSE_METHOD stuExAlarmChannel[MAX_EXALARM_CHANNEL_NUM];		// 报警通道集合
	int					 nProtocolNum;											// 支持的协议种类
	CFG_EM_EXALARM_PROTOCOL_TYPE emProtocolType[MAX_EXALARMBOX_PROTOCOL_NUM];	// 扩展报警模块报警盒支持的协议类型	
}CAP_EXALARM_INFO;

// 扩展模块报警盒能力集
typedef struct tagCFG_CAP_EXALARMBOX_INFO 
{
	int nAlarmInCount; // 扩展报警模块输入个数
	int nAlarmOutCount; // 扩展报警模块输出个数 
}CFG_CAP_EXALARMBOX_INFO; 

// 查询记录能力集能力集
typedef struct tagCFG_CAP_RECORDFINDER_INFO 
{
	int nMaxPageSize; // 最大分页条数 
}CFG_CAP_RECORDFINDER_INFO;


// 传感器采样 ==>CFG_CMD_SENSORSAMPLING
typedef struct  tagCFG_SENSORSAMPLING_INFO 
{
	int			nDetectionPeriod;			// 检查周期, 单位：秒，按检测周期实时上传温度状态
	int			nStorageItem;				// 存储信息量, 单位：条数，设备本地以写文件方式，可导出（0~5000）
}CFG_SENSORSAMPLING_INFO;

// 环网 ==>CFG_CMD_STP
typedef struct tagCFG_STP_INFO 
{
	BOOL			bEnable;				// 使能
}CFG_STP_INFO;

#define DH_MAX_ZONE_NUM					(256)	// 最大防区数目
#define DH_MAX_PUBLIC_SUBSYSTEM_NUM		(8)		// 最大公共子系统数目

// 报警子系统配置 ==>CFG_CMD_ALARM_SUBSYSTEM
typedef struct tagCFG_ALARM_SUBSYSTEM_INFO 
{
	char		szName[CFG_COMMON_STRING_128];	// 名称
	int			nZoneNum;						// 本地防区数目
	int			anZone[DH_MAX_ZONE_NUM];		// 本地防区号
	int			nExZoneNum;						// 扩展防区数目
	int			anExZone[DH_MAX_ZONE_NUM];		// 扩展防区号
	int			nDisableDelay;					// 延时撤防时间（进入延时）, 单位为秒
	int			nEnableDelay;					// 延时布防时间（退出延时）, 单位为秒
	BOOL		bIsPublic;						// 是否为公共子系统
	int			nPublicSubSystem;				// 公共所属的子系统数目
	int			anPublicSubSystem[DH_MAX_PUBLIC_SUBSYSTEM_NUM];// 公共所属的关联子系统
}CFG_ALARM_SUBSYSTEM_INFO;

// 电池电压低配置 ==>CFG_CMD_BATTERY_LOW_POWER
typedef struct tagCFG_BATTERY_LOW_POWER_INFO 
{
	BOOL		bEnable;						// 使能
	CFG_ALARM_MSG_HANDLE stuEventHandler;		// 报警联动
}CFG_BATTERY_LOW_POWER_INFO;


// 抓图通道联动外设配置 ==>CFG_CMD_SNAPLINKAGE
typedef struct tagCFG_SNAPLINKAGE_INFO 
{
    int         nChannelNum;                    // 视频通道关联的模拟量通道数目
    int         anAnalogAlarm[DH_MAX_ZONE_NUM]; // 视频通道关联的模量通道号
}CFG_SNAPLINKAGE_INFO;

// 视频输入配置
typedef struct tagCFG_AUDIO_INPUT 
{
    char        szAudioSource[CFG_COMMON_STRING_256];   // 输入音频源. 如果音频通道的输入是由多路合成，用|分割.
                                                        // 例："Mic|LineIn|Remote" 表示此音频通道由Mic、LineIn和远程通道的音频输入构成.
                                                        // "Coaxial" 同轴口音频
                                                        // "BNC" 本地BNC口音频
                                                        // "HDCVI_BNC" 远程HDCVI设备音频
                                                        // "LineIn" 线性输入
                                                        // "Mic" 麦克风输入
                                                        // "MicOut" 麦克输出
                                                        // "Remote" 远程通道(仅对画中画通道有意义，表示画中画主画面为远程通道时，将当前远程通道的音频作为音频输入)
}CFG_AUDIO_INPUT;

// 邮件上报设备状况
typedef struct tagCFG_HEALTHREPORT_INFO 
{
    BOOL			bEnable;				// 使能
    int             nInterval;              // 邮件发送间隔,单位为秒,范围：0~3600
}CFG_HEALTHREPORT_INFO;

// 邮件发送配置 ==>CFG_CMD_EMAIL
typedef struct tagCFG_EMAIL_INFO 
{
    BOOL			bEnable;				                            // 使能
    BOOL            bSslEnable;                                         // 是否需要SSL加密
    BOOL            bTlsEnable;                                         // 是否需要TLS加密
    char            szAddress[MAX_ADDRESS_LEN];                         // SMTP服务器IP地址或网络名
    int             nPort;                                              // 端口号
    char            szUserName[MAX_USERNAME_LEN];                       // 帐户名
    char            szPassword[MAX_PASSWORD_LEN];                       // 密码
    BOOL            bAnonymous;                                         // 匿名邮件，true匿名，false非匿名
    char            szSendAddress[MAX_ADDRESS_LEN];                     // 发件人地址
    int             nRetReciversNum;                                    // 有效收件人数
    char            szReceivers[MAX_RECEIVER_NUM][MAX_ADDRESS_LEN];     // 收件人列表
    char            szTitle[MAX_MAILTITLE_LEN];                         // 邮件标题关键字
    BOOL            bOnlyAttachment;                                    // 事件联动邮件，只发送带附件的邮件
    BOOL            bAttachEnable;                                      // 邮件附件使能
    int             nSendInterv;                                        // 同一事件的最小邮件发送间隔，单位为秒
    
    bool            abHealthReport;                                     // 能力,为true时,stuHealthReport有效
    BYTE            byReserved[3];
    CFG_HEALTHREPORT_INFO   stuHealthReport;                            // 邮件上报设备状况
}CFG_EMAIL_INFO;

#define MAX_TRANSFER_SERVER_NUM          10                             // 最大传输服务器个数
// 传输离线文件配置
typedef struct tagTRAFFIC_TRANSFER_OFFLINE_INFO
{
    BOOL            bEnable;                                                // 使能
    int             nType;                                                  // 0: 使用IP地址; 1:使用MAC地址
    int             nIpAddrNum;                                             // 返回的IP地址个数
    char            szIpAddr[MAX_TRANSFER_SERVER_NUM][MAX_ADDRESS_LEN];     // IP地址或网络名
    int             nMacAddrNum;                                            // 返回的mac地址个数
    char            szClientID[MAX_TRANSFER_SERVER_NUM][MAX_ADDRESS_LEN];   // mac地址

}TRAFFIC_TRANSFER_OFFLINE_INFO;

#define MAX_DEVCOMM_NUM          16                                     // 最大串口个数
// 订阅串口数据配置-单个串口配置
typedef struct tagCFG_DEVCOMM_SUBSCRIBE_INFO
{
    int             nReadCycle;                                         // 串口读取间隔,单位: 秒    
}CFG_DEVCOMM_SUBSCRIBE_INFO;

// 订阅串口数据配置
typedef struct tagCFG_DEVCOMM_SUBSCRIBE
{
    int                             nSubscribeInfoNum;                  // 串口数据配置个数
    CFG_DEVCOMM_SUBSCRIBE_INFO      stuSubscribeInfo[MAX_DEVCOMM_NUM];  // 订阅串口数据配置，是一个数组，每个元素对应一个串口    
}CFG_DEVCOMM_SUBSCRIBE;

// 车位状态对应的车位指示灯
typedef enum tagEM_CFG_PARKINGSPACE_LIGHT_COLOR
{
    EM_CFG_PARKINGSPACE_LIGHT_RED,                                      // 红色
    EM_CFG_PARKINGSPACE_LIGHT_YELLOW,                                   // 黄色
    EM_CFG_PARKINGSPACE_LIGHT_BLUE,                                     // 蓝色 
    EM_CFG_PARKINGSPACE_LIGHT_GREEN,                                    // 绿色
    EM_CFG_PARKINGSPACE_LIGHT_PURPLE,                                   // 紫色
    EM_CFG_PARKINGSPACE_LIGHT_WHITE,                                    // 白色
    EM_CFG_PARKINGSPACE_LIGHT_PINK,                                     // 粉色
}EM_CFG_PARKINGSPACE_LIGHT_COLOR;

// 指示灯状态
typedef enum tagEM_CFG_PARKINGSPACE_LIGHT_STATE
{
    EM_CFG_PARKINGSPACE_LIGHT_OFF,                                      // 灭
    EM_CFG_PARKINGSPACE_LIGHT_ON,                                       // 亮
    EM_CFG_PARKINGSPACE_LIGHT_GLINT,                                    // 闪烁
}EM_CFG_PARKINGSPACE_LIGHT_STATE;

#define CFG_MAX_PARKINGSPACE_LIGHT_NUM       8

typedef struct tagCFG_PARKINGSPACE_LIGHT_STATE
{
    BYTE                            bySpaceFreeLinght[CFG_MAX_PARKINGSPACE_LIGHT_NUM]; // 车位空闲状态灯色,颜色枚举值作为数组下标，数组元素值表示指示灯状态，如bySpaceFreeLinght[0]=1,表示红色指示灯亮
    BYTE                            bySpaceFullLinght[CFG_MAX_PARKINGSPACE_LIGHT_NUM]; // 车位满状态灯色，颜色枚举值作为数组下标，数组元素值表示指示灯状态，如bySpaceFullLinght[1]=1,表示黄色指示灯亮
}CFG_PARKINGSPACE_LIGHT_STATE;

// 空调工作模式
typedef enum tagEM_CFG_AIRCONDITION_MODE
{
    EM_CFG_AIRCONDITION_MODE_UNKNOWN = 0,
    EM_CFG_AIRCONDITION_MODE_AUTO,             // 自动
    EM_CFG_AIRCONDITION_MODE_HOT,              // 制热
    EM_CFG_AIRCONDITION_MODE_COLD,             // 制冷
    EM_CFG_AIRCONDITION_MODE_WET,              // 除湿
    EM_CFG_AIRCONDITION_MODE_WIND,             // 通风
} EM_CFG_AIRCONDITION_MODE;

// 空调送风模式
typedef enum tagEM_CFG_AIRCONDITION_WINDMODE
{
    EM_CFG_AIRCONDITION_WINDMODE_UNKNOWN = 0,
    EM_CFG_AIRCONDITION_WINDMODE_STOP,            // 停止
    EM_CFG_AIRCONDITION_WINDMODE_AUTO,            // 自动
    EM_CFG_AIRCONDITION_WINDMODE_HIGH,            // 高速
    EM_CFG_AIRCONDITION_WINDMODE_MIDDLE,          // 中速
    EM_CFG_AIRCONDITION_WINDMODE_LOW,             // 低速
} EM_CFG_AIRCONDITION_WINDMODE;

// 串口地址
typedef struct tagCFG_COMMADDR_INFO
{
    int                 nAddressNum;                            // 串口地址个数
    int 				nAddress[MAX_ADDRESS_NUM];			// 地址描述,不同厂商地址位不同，用数组表示
}CFG_COMMADDR_INFO;

// 空调设备配置详情
typedef struct tagCFG_AIRCONDITION_DETAIL
{
    char				szDeviceID[MAX_DEVICE_ID_LEN];			// 设备编码,惟一标识符
    char                szName[MAX_DEVICE_MARK_LEN];            // 设备描述
    char                szBrand[MAX_BRAND_NAME_LEN];            // 设备品牌
    CFG_COMMADDR_INFO   stuCommAddr;                            // 串口地址
    int                 nState;                                 // 设备状态: 1-打开,0-关闭
    int                 nRange;                                 // 幅度值(温度)单位：摄氏度
    EM_CFG_AIRCONDITION_MODE        emAirconditionMode;         // 空调工作模式
    EM_CFG_AIRCONDITION_WINDMODE    emAirconditionWindMode;     // 空调送风模式
}CFG_AIRCONDITION_DETAIL;

// 空调设备配置(对应CFG_CMD_AIRCONDITION命令)
typedef struct tagCFG_AIRCONDITION_INFO
{
    int                         nAirConditionNum;                        // 空调设备个数
    CFG_AIRCONDITION_DETAIL 	stuAirConditions[MAX_AIRCONDITION_NUM];	 // 空调设备配置详情, 数组表示
}CFG_AIRCONDITION_INFO;

//压缩回放配置信息
typedef struct tagCFG_COMPRESS_PLAY_INFO
{
    BOOL                bEnable;                // 使能
	CFG_CAPTURE_SIZE    emResolution;           // 视频分辨率
	unsigned int        nBitRate;               // 视频固定码流值(kbps), 范围：192~1024
}CFG_COMPRESS_PLAY_INFO;

// 系统类型
typedef enum tagEM_CFG_BUILDING_SYSTEM_TYPE
{
    EM_CFG_BUILDING_SYSTEM_TYPE_UNKNOWN = 0,        // 未知
    EM_CFG_BUILDING_SYSTEM_TYPE_DIGITAL,            // 数字系统
    EM_CFG_BUILDING_SYSTEM_TYPE_ANALOG,             // 模拟系统
}EM_CFG_BUILDING_SYSTEM_TYPE;

// VTO 楼层配置(对应 CFG_CMD_BUILDING 命令)
typedef struct tagCFG_BUILDING_INFO
{
    char                            szIssueNumber[CFG_COMMON_STRING_16];                // 期号，范围：0 ~ 99
    char                            szSectionNumber[CFG_COMMON_STRING_16];              // 区号，范围：0 ~ 99
    char                            szBuildingNumber[CFG_COMMON_STRING_16];             // 楼号，范围：0 ~ 999
    char                            szBuildingUnitNumber[CFG_COMMON_STRING_16];         // 楼内单元号，范围：0 ~ 9
    char                            szSectionUnitNumber[CFG_COMMON_STRING_16];          // 小区单元编号，范围：0 ~ 999
    int                             nUnitFloorNumber;                                   // 单元楼层数，范围：0 ~ 99
    int                             nFloorPerRoomNumber;                                // 一层房间数，范围：0 ~ 99
    BOOL                            bCreateRoomEnable;                                  // 创建房间号使能
    EM_CFG_BUILDING_SYSTEM_TYPE     emSystemType;                                       // 系统类型
}CFG_BUILDING_INFO;

//VTO 楼层扩展配置(对应 CFG_CMD_BUILDING_EXTERNAL 命令)
typedef struct tagCFG_BUILDING_EXTERNAL_INFO
{
    int                                     nFloorCount;                                            // 单元总层数
    int                                     nRoomCount;                                             // 每层房间数
    int                                     nBeginNumberCount;                                      // 获取/设置时，对应的开始房间号的有效个数
    // 获取时，当获取的开始房间号个数超过MAX_FLOOR_NUM，前MAX_FLOOR_NUM个有效
    // 设置时，当设置的开始房间号个数超过MAX_FLOOR_NUM，前MAX_FLOOR_NUM个有效
    char                                    szBeginNumber[MAX_FLOOR_NUM][CFG_COMMON_STRING_16];     // 开始的房间号，nBeginNumber[0] 为第一层开始房间号，nBeginNumber[1] 为第二层开始房间号，
    int                                     nTotalBuildingNumber;                                   // 小区总幢数，范围：0 ~ 99
    int                                     nBuildingPerUintNumber;                                 // 每幢单元数，范围：0 ~ 9
}CFG_BUILDING_EXTERNAL_INFO;

//拨号规则(对应 CFG_CMD_DIALRULE 命令)
typedef struct tagCFG_DIALRULE_INFO
{
    BOOL                            bBuildingModeEnable;            //幢模式使能
    BOOL                            bUnitModeEnable;                //单元模式使能
    BOOL                            bExtentionModeEnable;           //分机模式使能
    char                            cSeperator;                     //拨号分隔符, 如 "#", "-"
    BYTE				            byReserved[3];				    //字节对齐
}CFG_DIALRULE_INFO;

// 车辆油箱配置
typedef struct tagCFG_OIL_MASS_INFO
{
    int                 nTankVolume;            // 油箱容积，单位：升
    int                 nNotifyIntervalTime;    // 上报油箱信息间隔时间,单位：秒
    int                 nLowOil;                // 油量液位低报警百分比(例：低于20%则报警),单位：百分比，0－100
    int                 nAlarmIntervalTime;     // 上报油量液位低的报警时间间隔(即报警后，每隔一段时间就重复报警),单位：秒
}CFG_OIL_MASS_INFO; 

// MAC冲突事件报警配置
typedef struct tagCFG_MACCONFLICT_INFO 
{
    BOOL                bEnable;                // 使能开关
    CFG_ALARM_MSG_HANDLE stuEventHandler;       // 报警联动
}CFG_MACCONFLICT_INFO;

// 空闲动作功能枚举
typedef enum tagEM_CFG_IDLEMOTION_FUNCTION
{
    EM_CFG_IDLEMOTION_FUNCTION_NONE = 0,         // 无
    EM_CFG_IDLEMOTION_FUNCTION_PRESET,           // 预置点
    EM_CFG_IDLEMOTION_FUNCTION_SCAN,             // 自动线扫
    EM_CFG_IDLEMOTION_FUNCTION_TOUR,             // 巡航
    EM_CFG_IDLEMOTION_FUNCTION_PATTERN,          // 自动巡迹
} EM_CFG_IDLEMOTION_FUNCTION;

// 空闲动作配置信息
typedef struct tagCFG_IDLE_MOTION_INFO
{
    BOOL                        bEnable;         // 使能
    int                         nTime;           // 启动空闲动作的时间1~60分钟
    EM_CFG_IDLEMOTION_FUNCTION  emFunction;      // 空闲动作功能,见枚举 EM_CFG_IDLEMOTION_FUNCTION
    int                         nPresetId;       // 预置点编号,   范围参照CFG_PTZ_PROTOCOL_CAPS_INFO的wPresetMin和wPresetMax
    int                         nScanId;         // 自动线扫编号, 范围参照CFG_PTZ_PROTOCOL_CAPS_INFO的wAutoScanMin和wAutoScanMax
    int                         nTourId;         // 巡航编号,     范围参照CFG_PTZ_PROTOCOL_CAPS_INFO的wTourMin和wTourMax
    int                         nPatternId;      // 自动巡迹编号, 范围参照CFG_PTZ_PROTOCOL_CAPS_INFO的wPatternMin和wPatternMax
}CFG_IDLE_MOTION_INFO;

// 电视墙预案轮巡配置
typedef struct tagCFG_MONITORWALL_COLLECTION_TOUR_INFO
{
    int                 nInterval;               // 轮巡间隔时间, 单位秒
    int                 nCollectionNum;          // 预案轮巡组中包含的预案数量
    char                szCollectionGroup[CFG_MAX_COLLECTION_NUM][CFG_COMMON_STRING_128]; // 预案轮巡组内容, 每一项是预案的名称
}CFG_MONITORWALL_COLLECTION_TOUR_INFO;

// PSTN掉线事件配置
typedef struct tagCFG_PSTN_BREAK_LINE_INFO
{
    BOOL                bEnable;                // 使能开关
    CFG_ALARM_MSG_HANDLE stuEventHandler;       // 报警联动
}CFG_PSTN_BREAK_LINE_INFO;

// 网络采集设备配置, 对应CFG_CMD_NET_COLLECTION命令
typedef struct tagCFG_NET_COLLECTION_INFO
{
    char                szIp[MAX_ADDRESS_LEN];  // IP
	int                 nPort;                  // 端口
}CFG_NET_COLLECTION_INFO;

// 物理接口类型
typedef enum tagEM_CFG_INTERFACE_TYPE
{
    EM_CFG_INTERFACE_TYPE_UNKNOWN = 0,
	EM_CFG_INTERFACE_TYPE_COMM,                 // Comm类型, 即串口, 对应CFG_COMMGROUP_INFO配置
	EM_CFG_INTERFACE_TYPE_NETCOLLECTION,        // NetCollection类型, 即网络采集点, 对应CFG_NET_COLLECTION_INFO配置
}EM_CFG_INTERFACE_TYPE;

// 虚拟Slot节点与具体物理设备的对应关系, 对应CFG_CMD_ALARM_SLOT_BOND命令
// 由于第一个通道(即通道0)已经于本地通道绑定，故无法设置;
// 其他通道对应Slot节点序号, 元素内容为相应物理接口
typedef struct tagCFG_ALARM_SLOT_BOND_INFO
{
    EM_CFG_INTERFACE_TYPE   emType;             // 物理接口类型
	int                     nIndex;	            // 通道号, 从0开始
	                                            // 类型为EM_CFG_INTERFACE_TYPE_COMM时, 表示CFG_COMMGROUP_INFO配置的数组下标;
	                                            // 类型为EM_CFG_INTERFACE_TYPE_NETCOLLECTION时, 表示CFG_NET_COLLECTION_INFO配置的数组下标;
}CFG_ALARM_SLOT_BOND_INFO;

#define CFG_MAX_CTRLTYPE_NUM       16            // 最大道闸控制方式
// 道闸控制方式枚举
typedef enum tagEM_CFG_TRAFFICSTROBE_CTRTYPE
{
    EM_CFG_CTRTYPE_UNKNOWN = 0,                 // 未定义
    EM_CFG_CTRTYPE_TRAFFICTRUSTLIST,            // 通过白名单控制是否开闸；只有白名单内车辆才开闸
    EM_CFG_CTRTYPE_ALLSNAPCAR,                  // 针对所有抓拍车辆都开闸
    EM_CFG_CTRTYPE_ORDER,                       // 通过上层下发的命令开闸
} EM_CFG_TRAFFICSTROBE_CTRTYPE;

// 道闸配置信息(对应 CFG_CMD_TRAFFICSTROBE 命令)
typedef struct tagCFG_TRAFFICSTROBE_INFO
{
    BOOL                            bEnable;                            // 使能
    int                             nCtrlTypeCount;                     // 道闸控制方式个数
    EM_CFG_TRAFFICSTROBE_CTRTYPE    emCtrType[CFG_MAX_CTRLTYPE_NUM];    // 道闸控制方式,见枚举 EM_CFG_TRAFFICSTROBE_CTRTYPE
    CFG_ALARM_MSG_HANDLE            stuEventHandler;					// 开启道闸联动参数
    CFG_ALARM_MSG_HANDLE            stuEventHandlerClose;               // 关闭道闸联动参数
}CFG_TRAFFICSTROBE_INFO;

#define CFG_MAX_PLATEENABLE_NUM       16        // 最大使能过车车牌播报个数
#define CFG_MAX_TRAFFICVOICE_NUM      8         // 最大语音播报配置个数
// 使能过车车牌播报功能枚举
typedef enum tagEM_CFG_PLATEENABLE_TYPE
{
    EM_CFG_PLATEENABLE_UNKNOWN = 0,             // 未定义
    EM_CFG_PLATEENABLE_TIPS,                    // 播放欢迎词
    EM_CFG_PLATEENABLE_PLATE,                   // 播放车牌
} EM_CFG_PLATEENABLE_TYPE;

// 智能交通语音播报信息
typedef struct tagCFG_TRAFFICVOICE_BROADCAST_INFO
{
    int                             nEnableCount;                       // 使能播报个数
    EM_CFG_PLATEENABLE_TYPE         emEnable[CFG_MAX_PLATEENABLE_NUM];  // 使能过车车牌播报,见枚举 EM_CFG_PLATEENABLE_TYPE
    char                            szNormalCar[MAX_PATH];              // 普通车辆过车播报内容,例如:播报语音文件"欢迎光临.wav"
    char                            szTrustCar[MAX_PATH];               // 信任车辆过车播报内容,例如:播报语音文件"欢迎光临.wav"
    char                            szSuspiciousCar[MAX_PATH];          // 嫌疑车辆过车播报内容,例如:播报语音文件"非注册车辆.wav"
}CFG_TRAFFICVOICE_BROADCAST_INFO;

// 智能交通语音播报配置(对应 CFG_CMD_TRAFFICVOICE 命令)
typedef struct tagCFG_TRAFFICVOICE_BROADCAST
{
    int                             nTrafficVoiceNum;                           // 语音播报配置个数
    CFG_TRAFFICVOICE_BROADCAST_INFO stuTrafficVoices[CFG_MAX_TRAFFICVOICE_NUM];	// 语音播报配置详情, 数组表示
}CFG_TRAFFICVOICE_BROADCAST;

// 停车时间配置
typedef struct tagCFG_STANDING_TIME_INFO
{
    BOOL                        bEnable;         // 是否启用停车超时报警功能
    int                         nUpperlimit;     // 停留时间上限, 单位：分钟
    int                         nInterval;       // DH_ALARM_VEHICLE_STANDING_OVER_TIME事件上报间隔, 单位：秒
} CFG_STANDING_TIME_INFO;

// 电子围栏报警时间段信息
typedef struct tagENCLOSURE_TIME_SCHEDULE_INFO
{
    int                         nEnclosureID;                                          // 围栏的ID号
    CFG_TIME_SECTION            stuTimeSection[MAX_TIME_SCHEDULE_NUM][MAX_REC_TSECT];  // 事件响应时间段
} ENCLOSURE_TIME_SCHEDULE_INFO;

// 电子围栏最大数量
#define MAX_ENCLOSURE_NUM 128

// 电子围栏报警时间段配置
typedef struct tagCFG_ENCLOSURE_TIME_SCHEDULE_INFO
{
    int                                nEnclosureInfoCount;                     // 围栏数量
    ENCLOSURE_TIME_SCHEDULE_INFO       stuEnclosureInfo[MAX_ENCLOSURE_NUM];     // 围栏信息
    char                               szVersion[CFG_COMMON_STRING_64];         // 围栏时间段配置版本号
} CFG_ENCLOSURE_TIME_SCHEDULE_INFO;

// 停车场出入口控制器工作模式
typedef enum tagEM_ECK_WORK_MODE_TYPE
{
    EM_ECK_WORK_MODE_UNKNOWN = 0,
    EM_ECK_WORK_MODE_IMPORT,                                    // 入口控制机
    EM_ECK_WORK_MODE_EXPORT,                                    // 出口控制机
}EM_ECK_WORK_MODE_TYPE;

// 停车场出入口控制器开闸模式
typedef enum tagEM_ECK_STROBE_MODE_TYPE
{
    EM_ECK_STROBE_MODE_UNKNOWN = 0,
    EM_ECK_STROBE_MODE_ON,                                      // 始终开闸
    EM_ECK_STROBE_MODE_OFF,                                     // 始终关闸
    EM_ECK_STROBE_MODE_AUTO,                                    // 自动开关闸
}EM_ECK_STROBE_MODE_TYPE;

// 停车场出入口控制器滚动屏初始滚动速度
typedef enum tagEM_ECK_LED_SPEED_TYPE
{
    EM_ECK_LED_SPEED_UNKNOWN = 0,
    EM_ECK_LED_SPEED_LOW,                                       // 慢
    EM_ECK_LED_SPEED_NORMAL,                                    // 正常
    EM_ECK_LED_SPEED_HIGH,                                      // 快
}EM_ECK_LED_SPEED_TYPE;

// 停车场出入口控制器LED滚动屏配置
typedef struct tagCFG_ECK_LED_INFO 
{
    EM_ECK_LED_SPEED_TYPE   emLEDSpeed;                         // LED滚动屏初始滚动速度
    char                    szCustomData[CFG_COMMON_STRING_512];// LED滚动屏初始自定义字符, 有效长度0-256字节
}CFG_ECK_LED_INFO;

// 停车场出入口控制器配置
typedef struct tagCFG_ECKCONFIG_INFO 
{
    EM_ECK_WORK_MODE_TYPE   emWorkMode;                         // 工作模式
    EM_ECK_STROBE_MODE_TYPE emStrobeMode;                       // 开闸模式
    BOOL                    bForceOffline;                      // 强制脱机开关, TRUE:强制脱机工作, FALSE:接受平台控制工作
    BOOL                    bLoopSence;                         // 地感功能开关, TRUE:开启地感功能, FALSE:关闭地感功能
    CFG_ECK_LED_INFO        stuLED;                             // 滚动屏幕配置
}CFG_ECKCONFIG_INFO;

// 箭头指向
typedef enum tagEM_DIRECTION
{
    EM_DIRECTION_UNKNOWN,
    EM_DIRECTION_LEFT,                                          // 左
    EM_DIRECTION_UPLEFT,                                        // 左上
    EM_DIRECTION_UP,                                            // 上
    EM_DIRECTION_UPRIGHT,                                       // 右上
    EM_DIRECTION_RIGHT,                                         // 右
    EM_DIRECTION_DOWNRIGHT,                                     // 右下
    EM_DIRECTION_DOWN,                                          // 下
    EM_DIRECTION_DOWNLEFT,                                      // 左下
}EM_DIRECTION;

// 箭头相对于数字的位置
typedef enum tagEM_GUIDESCREEN_POS
{
    EM_GUIDESCREEN_POS_UNKNOWN,
    EM_GUIDESCREEN_POS_LEFT,                                    // 左侧
    EM_GUIDESCREEN_POS_RIGHT,                                   // 右侧
}EM_GUIDESCREEN_POS;

// 诱导屏内容是否滚动
typedef enum tagEM_GUIDESCREEN_ROLL
{
    EM_GUIDESCREEN_ROLL_UNKNOWN,
    EM_GUIDESCREEN_ROLL_DISABLE,                                // 不滚动
    EM_GUIDESCREEN_ROLL_ENABLE,                                 // 滚动
}EM_GUIDESCREEN_ROLL;

// 诱导屏箭头设置
typedef struct tagCFG_GUISCREEN_ARROW
{
    EM_DIRECTION            emDirect;                           // 箭头指向
    EM_GUIDESCREEN_POS      emPos;                              // 箭头相对于数字的位置
    EM_GUIDESCREEN_ROLL     emRoll;                             // 是否滚动
}CFG_GUISCREEN_ARROW;

#define CFG_GUIDE_SCREEN_NUM_MAX (8)                            // 诱导屏最大数量

// 诱导屏系统配置(对应 CFG_CMD_GUIDESCREEN 命令)
typedef struct tagCFG_GUIDESCREEN_INFO
{
    char                    szText[CFG_COMMON_STRING_128];      // 上下屏时,上屏显示内容
                                                                // 英文或常用中文汉字，中文需要GB2312编码，长度不超过64字节
    int                     nArrowNum;                          // 箭头标志数量
    CFG_GUISCREEN_ARROW     stuArrow[CFG_GUIDE_SCREEN_NUM_MAX]; // 箭头标志设置, 对应的屏从左至右依次排列
}CFG_GUIDESCREEN_INFO;

// 停车场出入口刷卡报警事件配置(对应CFG_CMD_PARKING_CARD命令)
typedef struct tagCFG_PARKING_CARD_INFO
{
    BOOL                            bEnable;                // 是否启用
    CFG_ALARM_MSG_HANDLE            stuEventHandler;        // 报警联动
} CFG_PARKING_CARD_INFO;

// 报警方式, 即通过什么方式发出的报警
typedef enum tagEM_CFG_RCEMERGENCY_MODE_TYPE
{
    EM_CFG_RCEMERGENCY_MODE_UNKNOWN = 0,
    EM_CFG_RCEMERGENCY_MODE_KEYBOARD,                       // 键盘
    EM_CFG_RCEMERGENCY_MODE_WIRELESS_CONTROL,               // 遥控器
}EM_CFG_RCEMERGENCY_MODE_TYPE;

// 紧急救助报警类型
typedef enum tagEM_CFG_RCEMERGENCY_CALL_TYPE
{
    EM_CFG_RCEMERGENCY_CALL_UNKNOWN = 0,
    EM_CFG_RCEMERGENCY_CALL_FIRE,                           // 火警
    EM_CFG_RCEMERGENCY_CALL_DURESS,                         // 胁迫
    EM_CFG_RCEMERGENCY_CALL_ROBBER,                         // 匪警
    EM_CFG_RCEMERGENCY_CALL_MEDICAL,                        // 医疗
}EM_CFG_RCEMERGENCY_CALL_TYPE;

// 紧急呼叫报警事件配置(对应 CFG_CMD_RCEMERGENCYCALL 命令)
typedef struct tagCFG_RCEMERGENCY_CALL_INFO 
{
    BOOL                            bEnable;                // 是否启用
    EM_CFG_RCEMERGENCY_MODE_TYPE    emMode;                 // 报警方式
    EM_CFG_RCEMERGENCY_CALL_TYPE    emAlarmType;            // 报警类型
    CFG_ALARM_MSG_HANDLE            stuEventHandler;        // 报警联动
}CFG_RCEMERGENCY_CALL_INFO;

// 车道信息上报配置(对应 CFG_CMD_LANES_STATE_REPORT 命令)
typedef struct tagCFG_LANES_STATE_REPORT
{
    BOOL                bEnable;        //上报使能	true:上报使能 ,false:上报不使能
    int                 nPeriod;        //上报周期	单位：秒
}CFG_LANES_STATE_REPORT;

#define CFG_MAX_USER_ID_LEN                     32              // 门禁卡用户ID最大长度

// 多人组合开门的开门方式
typedef enum tagEM_CFG_OPEN_DOOR_GROUP_METHOD
{
    EM_CFG_OPEN_DOOR_GROUP_METHOD_UNKNOWN = 0,
    EM_CFG_OPEN_DOOR_GROUP_METHOD_CARD,                         // 刷卡
    EM_CFG_OPEN_DOOR_GROUP_METHOD_PWD,                          // 密码
    EM_CFG_OPEN_DOOR_GROUP_METHOD_FINGERPRINT,                  // 指纹
}EM_CFG_OPEN_DOOR_GROUP_METHOD;

// 多人组合开门组详细信息
typedef struct tagCFG_OPEN_DOOR_GROUP_DETAIL 
{
    char                            szUserID[CFG_MAX_USER_ID_LEN];  // 用户ID
    EM_CFG_OPEN_DOOR_GROUP_METHOD   emMethod;                       // 开门方式
}CFG_OPEN_DOOR_GROUP_DETAIL;

#define CFG_MAX_OPEN_DOOR_GROUP_DETAIL_NUM      64               // 每一组多人开门组合的最大人数

// 多人组合开门组信息
typedef struct tagCFG_OPEN_DOOR_GROUP 
{
    int                         nUserCount;                     // 用户数目，表示需要组合才能开门的人数
    int                         nGroupNum;                      // 有效组数目
    CFG_OPEN_DOOR_GROUP_DETAIL  stuGroupDetail[CFG_MAX_OPEN_DOOR_GROUP_DETAIL_NUM];// 多人组合开门组的详细信息
}CFG_OPEN_DOOR_GROUP;

#define CFG_MAX_OPEN_DOOR_GROUP_NUM             4               // 多人开门组合的最大组合数

// 多人多开门方式组合(对应 CFG_CMD_OPEN_DOOR_GROUP 命令),表示每个通道的组合信息，
// 第一个通道的组合的开门优先级最高，后面依次递减
typedef struct tagCFG_OPEN_DOOR_GROUP_INFO 
{
    int                         nGroup;                         // 有效组合数
    CFG_OPEN_DOOR_GROUP         stuGroupInfo[CFG_MAX_OPEN_DOOR_GROUP_NUM];// 多人开门组合信息
}CFG_OPEN_DOOR_GROUP_INFO;

#define MAX_READER_ID_LEN                       32              // 读卡器ID最大长度

// 开门路线的每个节点的信息
typedef struct tagCFG_DOOR_ROUTE_NODE_INFO
{
    char                        szReaderID[MAX_READER_ID_LEN];  // 读卡器ID，即门禁控制器相连的读卡器的ID
}CFG_DOOR_ROUTE_NODE_INFO;

// 每条开门路线最大节点(读卡器数目)
#define MAX_DOOR_ROUTE_NODE_NUM     4

// 门数组集合信息，按照数组下标从小到大顺序，表示开门路线
typedef struct tagCFG_DOOR_ROUTE_INFO
{
    int                         nDoors;                             // 开门路线有效节点数
    CFG_DOOR_ROUTE_NODE_INFO    stuDoors[MAX_DOOR_ROUTE_NODE_NUM];  // 开门路线节点信息
}CFG_DOOR_ROUTE_INFO;

#define MAX_OPEN_DOOR_ROUTE_NUM                 16                  // 最大开门路线数目

// 开门路线集合，或称防反潜路线配置(对应 CFG_CMD_OPEN_DOOR_ROUTE 命令)
typedef struct tagCFG_OPEN_DOOR_ROUTE_INFO
{
    int                         nDoorList;
    CFG_DOOR_ROUTE_INFO         stuDoorList[MAX_OPEN_DOOR_ROUTE_NUM];
}CFG_OPEN_DOOR_ROUTE_INFO;

#define MAX_BURNPLAN_DEVICES_NUM                     32
#define MAX_BURNPLAN_CHANNELS_NUM                     32

// 刻录流格式
typedef enum tagEM_CFG_BURNPLAN_RECORDPACK_TYPE
{
    EM_CFG_BURNPLAN_RECORDPACK_TYPE_UNKNOWN,        // 未知
    EM_CFG_BURNPLAN_RECORDPACK_TYPE_DHAV,           // "DHAV"
    EM_CFG_BURNPLAN_RECORDPACK_TYPE_PS,             // "PS"
    EM_CFG_BURNPLAN_RECORDPACK_TYPE_ASF,            // "ASF"
    EM_CFG_BURNPLAN_RECORDPACK_TYPE_MP4,            // "MP4"
    EM_CFG_BURNPLAN_RECORDPACK_TYPE_TS,             // "TS"
}EM_CFG_BURNPLAN_RECORDPACK_TYPE;

// 刻录模式
typedef enum tagEM_CFG_BURNPLAN_MODE
{
    EM_CFG_BURNPLAN_MODE_UNKNOWN,           // 未知
    EM_CFG_BURNPLAN_MODE_SYNC,              // 同步： "Sync"
    EM_CFG_BURNPLAN_MODE_TURN,              // 轮流:  "Turn"
    EM_CFG_BURNPLAN_MODE_CYCLE,             // 循环:  "Cycle"
}EM_CFG_BURNPLAN_MODE;

// 刻录计划信息
typedef struct tagCFG_BURNPLAN_DETAIL
{
    int                                 nSessionId;                             // 审讯室
    int                                 nDevicesNum;                            // 参与该会话的设备列表有效个数
    int                                 nDevices[MAX_BURNPLAN_DEVICES_NUM];     // 参与该会话的设备列表
    int                                 nChannelsNum;                           // 刻录的视频通道有效个数
    int                                 nChannels[MAX_BURNPLAN_CHANNELS_NUM];   // 刻录的视频通道
    EM_CFG_BURNPLAN_RECORDPACK_TYPE     emRecordpack;                           // 刻录流格式
    EM_CFG_BURNPLAN_MODE                emMode;                                 // 刻录模式
    CFG_NET_TIME                        stuStarttime;                           // 刻录开始时间
}CFG_BURNPLAN_DETAIL;

#define MAX_BURNPLAN_DETAIL_NUM          32

// 刻录计划配置(对应CFG_BURNPLAN_INFO)
typedef struct tagCFG_BURNPLAN_INFO
{
    int                         nBurnPlanDetailNum;                                 // 刻录计划信息列表有效个数
    CFG_BURNPLAN_DETAIL         stuBurnPlanDetail[MAX_BURNPLAN_DETAIL_NUM];         // 刻录计划信息列表
}CFG_BURNPLAN_INFO;

typedef struct tagCFG_SCADA_DEV_INFO 
{
    BOOL                            bEnable;                // 是否启用
    char                            szDevType[CFG_COMMON_STRING_64];// 设备类型
    char                            szDevName[CFG_COMMON_STRING_64];// 设备名称, 唯一标示设备用
    int                             nSlot;                  // 虚拟槽位号, 详见AlarmSlotBond配置
    int                             nLevel;                 // 如果Slot绑定的是NetCollection类型的话，该字段为-1
    CFG_ALARM_MSG_HANDLE            stuEventHandler;        // 报警联动
}CFG_SCADA_DEV_INFO;

// 通道相关信息
typedef struct tagCFG_VSP_GAYS_CHANNEL_INFO
{
    char                            szId[CFG_COMMON_STRING_64];             // 通道编号	字符串（24位）
    int                             nAlarmLevel;                            // 报警级别[1,6]	整型
}CFG_VSP_GAYS_CHANNEL_INFO;

// 报警相关信息
typedef struct tagCFG_VSP_GAYS_ALARM_INFO
{
    char                            szId[CFG_COMMON_STRING_64];             // 通道编号	字符串（24位）
    int                             nAlarmLevel;                            // 报警级别[1,6]	整型
}CFG_VSP_GAYS_ALARM_INFO;

// 公安一所平台接入配置(CFG_CMD_VSP_GAYS)
typedef struct tagCFG_VSP_GAYS_INFO
{
    BOOL                            bEnable;                                // 是否使能，TRUE使能，FALSE不使能
    char                            szSipSvrId[CFG_COMMON_STRING_64];       // SIP服务器编号	字符串（24位）
    char                            szDomain[CFG_COMMON_STRING_256];        // SIP域	字符串（128位）
    char                            szSipSvrIp[CFG_COMMON_STRING_32];       // SIP服务器IP	字符串（16位）
    char                            szDeviceId[CFG_COMMON_STRING_64];       // 设备编号，也是注册用户名	字符串（24位）
    char                            szPassword[CFG_COMMON_STRING_64];       // 注册密码,密文	字符串（24位）
    unsigned short                  nLocalSipPort;                          // 本地SIP服务端口	无符号短整型
    unsigned short                  nSipSvrPort;                            // SIP服务器端口	无符号短整型
    int                             nSipRegExpires;                         // 注册有效期	整型
    int                             nKeepAliveCircle;                       // 心跳周期	整型
    int                             nMaxTimeoutTimes;                       // 最大心跳超时次数	整型
    char                            szCivilCode[CFG_COMMON_STRING_64];      // 行政区划代码	字符串（24位）
    char                            szIntervideoID[CFG_COMMON_STRING_64];   // 接入模块识别码	字符串（24位）
    unsigned short                  nChannelSum;                            // 通道数	无符号短整型
    unsigned short                  nAlarmInSum;                            // 外部报警输入数	无符号短整型
    CFG_VSP_GAYS_CHANNEL_INFO       stuChannelInfo[MAX_VIDEO_CHANNEL_NUM];  // 通道相关信息	数组，有效个数同channelSum
    CFG_VSP_GAYS_ALARM_INFO         stuAlarmInfo[MAX_ALARM_CHANNEL_NUM];    // 报警相关信息	数组，有效个数同alarmInSum
}CFG_VSP_GAYS_INFO;

// 音频检测报警配置(CFG_CMD_AUDIODETECT)
typedef struct tagCFG_AUDIO_DETECT_INFO
{
    BOOL                            bEnable;                                // 是否使能，TRUE使能，FALSE不使能
    int                             nMinVolume;                             // 音量下限
    int                             nMaxVolume;                             // 音量上限
    BOOL                            bAnomalyDetect;                         // 声音异常检测使能
    int                             nAnomalySensitive;                      // 声音异常检测灵敏度值	取值范围1~100
    BOOL                            bMutationDetect;                        // 声强突变检测使能
    int                             nMutationThreold;                       // 声强突变检测阈值	取值范围1~100
    CFG_ALARM_MSG_HANDLE            stuEventHandler;						// 联动配置
}CFG_AUDIO_DETECT_INFO;

// VTS呼叫配置(对应命令 CFG_CMD_VTS_CALL_INFO)
typedef struct tagCFG_VTS_CALL_INFO 
{
    CFG_TIME_SECTION                stuCallEnableTime;                      // 允许呼叫VTS的时间段
}CFG_VTS_CALL_INFO;

// 设备列表配置中每个设备的信息
typedef struct tagCFG_DEV_LIST
{
    char                            szDevType[CFG_COMMON_STRING_128];       // 设备类型, 支持: "VTT", "VTS"
    char                            szDevName[CFG_COMMON_STRING_128];       // 设备名称
    char                            szIP[MAX_ADDRESS_LEN];                  // ip地址
    int                             nPort;                                  // 端口号
    char                            szUser[CFG_COMMON_STRING_64];           // 用户名
    char                            szPassword[CFG_COMMON_STRING_64];       // 密码
    char                            szDevID[CFG_COMMON_STRING_128];         // 设备ID号, 必须唯一
    char                            szParentID[CFG_COMMON_STRING_128];      // 父节点ID, 必须唯一
}CFG_DEV_LIST;

// 设备列表配置(对应命令 CFG_CMD_DEV_LIST_INFO)
typedef struct tagCFG_DEV_LIST_INFO 
{
    CFG_DEV_LIST*                   pstuDevList;                            // 配置信息, 用户分配内存
    DWORD                           dwDevListMaxCount;                      // pstuDevList分配内存的有效结构体个数
    DWORD                           dwDevListRetCount;                      // 实际返回的结构体个数, 解析成结构体时有效
}CFG_DEV_LIST_INFO;

#define MAX_CALIBRATE_MATRIX_LEN    8       // 标定矩阵最大长度

// 主从式跟踪器标定矩阵配置(对应 CFG_CMD_CALIBRATE_MATRIX 命令)
typedef struct tagCFG_CALIBRATE_MATRIX_INFO 
{
    char                szSlaveSN[CFG_COMMON_STRING_128];                   // 从设备序列号
    DWORD               dwMatrixLen;                                        // 标定矩阵中有效dword个数
    DWORD               dwMatrix[MAX_CALIBRATE_MATRIX_LEN];                 // 标定矩阵, 是一个128字节的二进制串, 为提高解析效率, 保存为32个uint32_t值
}CFG_CALIBRATE_MATRIX_INFO;

// 防区延时配置(对应 CFG_CMD_DEFENCE_AREA_DELAY 命令)
typedef struct tagCFG_DEFENCE_AREA_DELAY_INFO 
{
    int                 nEnterDelay1;           // 有进入延时的防区类型，除防区类型EM_CFG_DefenceAreaType_Entrance2外, 都使用此进入延时
    int                 nEnterDelay2;           // 只有防区类型为EM_CFG_DefenceAreaType_Entrance2, 才会使用此进入延时
    int                 nExitDelay;             // 所有有退出延时的防区, 都使用此退出延时
}CFG_DEFENCE_AREA_DELAY_INFO;

// 近光灯信息
typedef struct tagCFG_NEARLIGHT_INFO
{
    BOOL                bEnable;                // 是否使能，TRUE使能，FALSE不使能
    DWORD               dwLightPercent;         // 灯光亮度百分比值(0~100)
    DWORD               dwAnglePercent;         // 灯光角度百分比值(0~100)
}CFG_NEARLIGHT_INFO;

// 远光灯信息
typedef struct tagCFG_FARLIGHT_INFO 
{
    BOOL                bEnable;                // 是否使能，TRUE使能，FALSE不使能
    DWORD               dwLightPercent;         // 灯光亮度百分比值(0~100)
    DWORD               dwAnglePercent;         // 灯光角度百分比值(0~100)
}CFG_FARLIGHT_INFO;

// 灯光模式
typedef enum tagEM_CFG_LIGHTING_MODE
{
    EM_CFG_LIGHTING_MODE_UNKNOWN,               // 未知
    EM_CFG_LIGHTING_MODE_MANUAL,                // 手动: "Manual"
    EM_CFG_LIGHTING_MODE_ZOOMPRIO,              // 倍率优先: "ZoomPrio"
}EM_CFG_LIGHTING_MODE;

#define MAX_LIGHTING_NUM         16

// 灯光设置详情
typedef struct tagCFG_LIGHTING_DETAIL
{
    int                                 nCorrection;                     // 灯光补偿 (0~4) 倍率优先时有效
    int                                 nSensitive;                      // 灯光灵敏度(0~5)倍率优先时有效，默认为3
    EM_CFG_LIGHTING_MODE                emMode;                          // 灯光模式
    int                                 nNearLight;                      // 近光灯有效个数
    CFG_NEARLIGHT_INFO                  stuNearLights[MAX_LIGHTING_NUM]; // 近光灯列表
    int                                 nFarLight;                       // 远光灯有效个数
    CFG_FARLIGHT_INFO                   stuFarLights[MAX_LIGHTING_NUM];  // 远光灯列表
}CFG_LIGHTING_DETAIL;

#define MAX_LIGHTING_DETAIL_NUM  16

// 灯光设置(对应 CFG_CMD_LIGHTING 命令)
typedef struct tagCFG_LIGHTING_INFO
{
    int                         nLightingDetailNum;                         // 灯光设置有效个数
    CFG_LIGHTING_DETAIL         stuLightingDetail[MAX_LIGHTING_DETAIL_NUM]; // 灯光设置信息列表
}CFG_LIGHTING_INFO;

// 雨刷工作模式
typedef enum tagEM_CFG_RAINBRUSHMODE_MODE
{
    EM_CFG_RAINBRUSHMODE_MODE_UNKNOWN,           // 未知
    EM_CFG_RAINBRUSHMODE_MODE_MANUAL,            // 手动模式
    EM_CFG_RAINBRUSHMODE_MODE_TIMING,            // 定时模式
}EM_CFG_RAINBRUSHMODE_MODE;

// 雨刷使能电平模式
typedef enum tagEM_CFG_RAINBRUSHMODE_ENABLEMODE
{
    EM_CFG_RAINBRUSHMODE_ENABLEMODE_UNKNOWN,     // 未知
    EM_CFG_RAINBRUSHMODE_ENABLEMODE_LOW,         // 低电平有效（常闭）
    EM_CFG_RAINBRUSHMODE_ENABLEMODE_HIGH,        // 高电平有效（常开）
}EM_CFG_RAINBRUSHMODE_ENABLEMODE;

// 雨刷模式相关配置(对应 CFG_RAINBRUSHMODE_INFO 命令)
typedef struct tagCFG_RAINBRUSHMODE_INFO
{
    EM_CFG_RAINBRUSHMODE_MODE        emMode;         // 雨刷工作模式
    EM_CFG_RAINBRUSHMODE_ENABLEMODE  emEnableMode;   // 雨刷使能电平模式
    int                              nPort;          // 雨刷使用的IO端口,-1表示未接入设备,-2表示该字段无效（设备未传送该字段）
}CFG_RAINBRUSHMODE_INFO;

#define MAX_EMERGENCY_REOCRD_CLIENT_NUM         8       // 可以紧急录像存储的最大客户端数

// 客户端的紧急录像配置信息
typedef struct tagCFG_EMERGENCY_RECORD_CLIENT 
{
    char        szDevID[CFG_COMMON_STRING_128];         // 客户端字符串标识作为对象名称，可以是客户端mac地址，若客户端是设备，则使用设备序列号
    BOOL        bEnable;                                // 使能
    int         nMaxTime;                               // 拉流异常断开之后进行紧急存储的最大时间, 
}CFG_EMERGENCY_RECORD_CLIENT;

// 紧急录像存储配置(对应 CFG_CMD_EMERGENCY_RECORD_FOR_PULL)
typedef struct tagCFG_EMERGENCY_RECORD_FOR_PULL_INFO 
{
    int         nClientNum;                             // 有效客户端紧急录像配置个数
    CFG_EMERGENCY_RECORD_CLIENT stuEmRecordInfo[MAX_EMERGENCY_REOCRD_CLIENT_NUM];// 客户端紧急录像配置信息 
}CFG_EMERGENCY_RECORD_FOR_PULL_INFO;

// 高频次报警
typedef struct tagCFG_HIGH_FREQUENCY 
{
    int         nPeriod;                            // 统计周期, 以秒为单位, 默认30分钟(1800s)
    int         nMaxCount;                          // 在对应统计周期内最大允许上报报警数
}CFG_HIGH_FREQUENCY;

// 告警屏蔽规则配置(对应 CFG_CMD_ALARM_SHIELD_RULE)
typedef struct tagCFG_ALARM_SHIELD_RULE_INFO 
{
    CFG_HIGH_FREQUENCY  stuHighFreq;                // 高频次报警, 在一定周期内允许上报的报警次数，以此过滤对于报警的频繁上报导致信息干扰
}CFG_ALARM_SHIELD_RULE_INFO;

#define CFG_MAX_VIDEOIN_ANALYSER_NUM        3       // 每个视频通道内的最大视频分析器数量
#define CFG_MAX_ANALYSE_RULE_GROUP_NUM      8       // 视频分析规则组最大数量

// 智能分析规则组, 一个组中包含同类型的多条规则
typedef struct tagCFG_ANALYSERULE_GROUP
{
    DWORD				dwRuleType;					// 规则类型，详见dhnetsdk.h中"智能分析事件类型"
    int                 nRuleStructSize;            // 规则类型对应的规则结构的大小, parse时的输出参数, packet时是输入参数
    BOOL                bEnable;                    // 使能
    BOOL                bEventHandlerEnable;        // 报警联动使能, TRUE规则组报警联动使能, 组内所有规则使用共同的联动项; FALSE使用规则中各自的联动项
    CFG_ALARM_MSG_HANDLE stuEventHandler;			// 规则组报警联动
    CFG_TIME_SCHEDULE   stuEventTimeSection;        // 规则组报警联动时间表
    int                 nRuleNum;                   // 规则数量, parse时的输出参数, packet时是输入参数
    char*               pRuleBuf;                   // 规则缓冲, 需要用户分配内存, 用于存放规则信息
                                                    // 如规则类型为警戒线, pRuleBuf的内容就是多个CFG_CROSSLINE_INFO
    int                 nRuleBufSize;               // 规则缓冲大小, 用户填写
}CFG_ANALYSERULE_GROUP;

// 视频分析器信息
typedef struct tagCFG_VIDEO_IN_ANALYSER_INFO
{
    CFG_ANALYSEGLOBAL_INFO  stuGlobal;              // 全局配置
    CFG_ANALYSEMODULES_INFO stuModules;             // 模块配置
    CFG_ANALYSERULE_GROUP	stuRuleGroup[CFG_MAX_ANALYSE_RULE_GROUP_NUM]; // 规则配置, 数组内元素的规则缓冲需要用户分配内存
    int                     nRuleGroupNum;          // 规则组数量
}CFG_VIDEOIN_ANALYSER_INFO;

// 视频通道内的智能规则, 该结构体很大, 使用时在堆中分配内存
typedef struct tagCFG_VIDEO_IN_ANALYSE_RULE_INFO
{
    int                     nAnalyserNum;                               // 分析器数量
    CFG_VIDEOIN_ANALYSER_INFO stuAnalysers[CFG_MAX_VIDEOIN_ANALYSER_NUM]; // 分析器信息
}CFG_VIDEOIN_ANALYSE_RULE_INFO;

typedef enum tagEM_CFG_ACCESS_WORD_MODE
{
    EM_CFG_ACCESS_WORD_MODE_UNKNOWN,                // 未知
        EM_CFG_ACCESS_WORD_MODE_NORMAL,                 // "Normal" 正常模式
        EM_CFG_ACCESS_WORD_MODE_CLEAN,                  // "Clean"  打扫模式
        EM_CFG_ACCESS_WORD_MODE_DECORATION,             // "Decoration"  装修模式
}EM_CFG_ACCESS_WORD_MODE;

// 门锁工作模式(对应 CFG_CMD_ACCESS_WORK_MODE)
typedef struct tagCFG_ACCESS_WORK_MODE_INFO 
{
    EM_CFG_ACCESS_WORD_MODE  emMode;                // 工作模式
}CFG_ACCESS_WORK_MODE_INFO;

/************************************************************************
** 接口定义
***********************************************************************/
// 报警事件类型根据dhnetsdk.h解析出来的报警类型
typedef int  (CALLBACK *fALARMEvent)(DWORD dwAlarmType, void* pAlarmInfo, DWORD dwStructSize, BYTE *pBuffer, DWORD dwBufSize, LDWORD dwUser);

// 回调方式进行数据解析，dwDataType表示数据解析得到类型
typedef int  (CALLBACK *fAnalyzerData)(DWORD dwDataType, void* pDataInfo, DWORD dwStructSize, BYTE *pBuffer, DWORD dwBufSize, LDWORD dwUser);

// 解析查询到的配置信息
CLIENT_API BOOL  CALL_METHOD CLIENT_ParseData(char* szCommand, char* szInBuffer, LPVOID lpOutBuffer, DWORD dwOutBufferSize, void* pReserved);

// 组成要设置的配置信息
CLIENT_API BOOL  CALL_METHOD CLIENT_PacketData(char* szCommand, LPVOID lpInBuffer, DWORD dwInBufferSize, char* szOutBuffer, DWORD dwOutBufferSize);

// 录像报警事件解析
CLIENT_API BOOL  CALL_METHOD CLIENT_ParseAnalyzerEventData(LPVOID lpInBuffer, DWORD dwInBufferSize, fALARMEvent cbEvent, LDWORD dwUser);

// 回调方式数据解析
CLIENT_API BOOL CALL_METHOD CLIENT_ParseDataByCallback(LPVOID lpInBuffer, DWORD dwInBufferSize, fAnalyzerData cbAnalyzer, LDWORD dwUser);
#ifdef __cplusplus
}
#endif

#endif // DHCONFIGSDK_H

