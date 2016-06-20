using System;
using System.Collections.Generic;
using System.Text;
using System.Runtime.InteropServices;
using System.ComponentModel;
using System.Net;


namespace NetSDK
{

    #region << Structural Definition  >>

    /// <summary>
    /// Network Devices Information
    /// </summary>
    [StructLayout(LayoutKind.Sequential)]
    public struct NET_DEVICEINFO
    {
        /// <summary>
        /// Serial Number[Length48]
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 48)]
        public byte[] sSerialNumber;

        /// <summary>
        /// DVR Alarm Input Number
        /// </summary>
        public byte byAlarmInPortNum;

        /// <summary>
        /// DVR Alarm Output Number
        /// </summary>
        public byte byAlarmOutPortNum;

        /// <summary>
        /// DVR HDD Number
        /// </summary>
        public byte byDiskNum;

        /// <summary>
        /// DVR Type
        /// </summary>
        public byte byDVRType;

        /// <summary>
        /// DVR Channel Number
        /// </summary>
        public byte byChanNum;

    }

    /// <summary>
    /// Internet Time
    /// </summary>
    [StructLayout(LayoutKind.Sequential)]
    public struct NET_TIME
    {
        /// <summary>
        /// Year
        /// </summary>
        public int dwYear;
        /// <summary>
        /// Month
        /// </summary>
        public int dwMonth;
        /// <summary>
        /// Day
        /// </summary>
        public int dwDay;
        /// <summary>
        /// Hour
        /// </summary>
        public int dwHour;
        /// <summary>
        /// Minute
        /// </summary>
        public int dwMinute;
        /// <summary>
        /// Second
        /// </summary>
        public int dwSecond;

        /// <summary>
        /// Change Date According To The Format
        /// </summary>
        /// <param name="FormatStyle">Date Format Strings:yyyy is the value format of year[Fixed Four]；mm is the value format of month[Fixed Two]；dd is the value format of day[Fixed Two]；d is the value format of day[Not Limit Digits]；m is format of month[Not Limit Digits]；yy is format of year[Fixed Two]；y is format of year[Not Limit Digits]；hh is the value format of hour[Fixed Two]；h is the value format of hour[Not Limit Digits]；MM is the value format of minute[Fixed Two]；M is the value format of minute[Not Limit Digits]；ss is the value format of second[Fixed Two]；s is the value format of second[Not Limit Digits]；</param>
        /// <returns></returns>
        public string ToString(string FormatStyle)
        {
            string returnValue = FormatStyle;
            //The Format Process of Year
            string strY = "";
            if (returnValue.IndexOf("yyyy") != -1)
            {
                strY = "0000".Remove(4 - dwYear.ToString().Length) + dwYear.ToString();
                returnValue = returnValue.Replace("yyyy", strY);
            }
            else if (returnValue.IndexOf("yy") != -1)
            {
                if (dwYear.ToString().Length > 2)
                {
                    strY = dwYear.ToString().Substring(dwYear.ToString().Length - 2);
                    returnValue = returnValue.Replace("yy", strY);
                }
                else
                {
                    strY = "00".Remove(2 - dwYear.ToString().Length) + dwYear.ToString();
                    returnValue = returnValue.Replace("yy", strY);
                }
            }
            else if (returnValue.IndexOf("y") != -1)
            {
                strY = dwYear.ToString();
                returnValue = returnValue.Replace("y", strY);
            }
            //The Format Process of Month
            string strM = "";
            if (returnValue.IndexOf("mm") != -1)
            {
                strM = "00".Remove(2 - dwMonth.ToString().Length) + dwMonth.ToString();
                returnValue = returnValue.Replace("mm", strM);
            }
            else if (returnValue.IndexOf("m") != -1)
            {
                strM = dwMonth.ToString();
                returnValue = returnValue.Replace("m", strM);
            }
            //The Format Process of Day
            string strD = "";
            if (returnValue.IndexOf("dd") != -1)
            {
                strD = "00".Remove(2 - dwDay.ToString().Length) + dwDay.ToString();
                returnValue = returnValue.Replace("dd", strD);
            }
            else if (returnValue.IndexOf("d") != -1)
            {
                strD = dwDay.ToString();
                returnValue = returnValue.Replace("d", strD);
            }
            //The Format Process of Hour
            string strH = "";
            if (returnValue.IndexOf("hh") != -1)
            {
                strH = "00".Remove(2 - dwHour.ToString().Length) + dwHour.ToString();
                returnValue = returnValue.Replace("hh", strH);
            }
            else if (returnValue.IndexOf("h") != -1)
            {
                strH = dwHour.ToString();
                returnValue = returnValue.Replace("h", strH);
            }
            //The Format Process of Minute
            string strMM = "";
            if (returnValue.IndexOf("MM") != -1)
            {
                strMM = "00".Remove(2 - dwMinute.ToString().Length) + dwMinute.ToString();
                returnValue = returnValue.Replace("MM", strMM);
            }
            else if (returnValue.IndexOf("M") != -1)
            {
                strMM = dwMinute.ToString();
                returnValue = returnValue.Replace("M", strMM);
            }
            //The Format Process of Second
            string strS = "";
            if (returnValue.IndexOf("ss") != -1)
            {
                strS = "00".Remove(2 - dwSecond.ToString().Length) + dwSecond.ToString();
                returnValue = returnValue.Replace("ss", strS);
            }
            else if (returnValue.IndexOf("s") != -1)
            {
                strS = dwSecond.ToString();
                returnValue = returnValue.Replace("s", strS);
            }
            return returnValue;
        }

        public string ToString()
        {
            return string.Format("{0}-{1}-{2} {3}:{4}:{5}", dwYear, dwMonth, dwDay, dwHour, dwMinute, dwSecond);
        }

        /// <summary>
        /// Turn Into Standard System Time
        /// </summary>
        /// <returns></returns>
        public DateTime ToDateTime()
        {
            try
            {
                return new DateTime(dwYear, dwMonth, dwDay, dwHour, dwMinute, dwSecond);
            }
            catch
            {
                return DateTime.Now;
            }
        }

    }

    /// <summary>
    /// Record File Information
    /// </summary>
    public struct NET_RECORDFILE_INFO
    {
        /// <summary>
        /// Channel Number
        /// </summary>
        public uint ch;
        /// <summary>
        /// File Name
        /// </summary>
        //[MarshalAs(UnmanagedType.ByValArray, ArraySubType = UnmanagedType.ByValTStr, SizeConst = 128)]
        //public char[] filename;
        [MarshalAs(UnmanagedType.ByValArray,  SizeConst = 124)]
        public byte[] filename;
        /// <summary>
        /// The File's Frame Num
        /// </summary>
        public uint framenum;
        /// <summary>
        /// File Length
        /// </summary>
        public uint size;
        /// <summary>
        /// Start Time
        /// </summary>
        public NET_TIME starttime;
        /// <summary>
        /// End Time
        /// </summary>
        public NET_TIME endtime;
        /// <summary>
        /// Drive Number
        /// </summary>
        public uint driveno;
        /// <summary>
        /// Start Cluster Number
        /// </summary>
        public uint startcluster;
        /// <summary>
        /// Record File Type  0：Ordinary Record；1：Alarm Record;2. Motion
        /// </summary>
        public byte nRecordFileType;
        /// <summary>
        /// Record File Impportant?  0：Ordinary Record；1：Important Record
        /// </summary>
        public byte bImportantRecID;            
        /// <summary>
        /// File Index
        /// </summary>
        public byte bHint;                      
        /// <summary>
        /// Record Stream Type. 0-Main Stream 1-Extra1 Stream 2-Extra2 Stream 3-Extra3 Stream
        /// </summary>
        public byte bRecType;                   
    }

    public struct NET_IN_PLAY_BACK_BY_TIME_INFO
    {
        public NET_TIME stStartTime;
        public NET_TIME stStopTime;
        public IntPtr hWnd;
        public fDownLoadPosCallBack cbDownLoadPos;
        public IntPtr dwPosUser;
        public fDataCallBack fDownLoadDataCallBack;
        public IntPtr dwDataUser;
        public int nPlayDirection;
        public int nWaittime;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 1024)]
        public byte[] bReserved;
    }


    public struct NET_OUT_PLAY_BACK_BY_TIME_INFO
    {
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 1024)]
        public byte[] bReserved;
    }


    /// <summary>
    /// Com State
    /// </summary>
    public  struct NET_COMM_STATE
    {
        public uint        uBeOpened;
        public uint        uBaudRate;
        public uint        uDataBites;
        public uint        uStopBits;
        public uint        uParity;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 32)]
        public byte []     bReserved;
    }

    /// <summary>
    /// Error Content
    /// </summary>
    public struct OPERATION_INFO
    {
        /// <summary>
        /// Error Code
        /// </summary>
        public string errCode;
        /// <summary>
        /// Error Description
        /// </summary>
        public string errMessage;
        /// <summary>
        /// Return Error Content String According to custom format 
        /// </summary>
        /// <param name="FormatStyle">Error Content String Format：errcode Instead Error Code;errmsg Instead Error Description</param>
        /// <returns></returns>
        public string ToString(string FormatStyle)
        {
            string returnValue = FormatStyle;
            if (returnValue.Length == 0)
            {
                returnValue = "errcode:errmsg!";
            }
            returnValue = returnValue.ToUpper();
            returnValue = returnValue.Replace("ERRCODE", errCode).Replace("ERRMSG", errMessage);
            return returnValue;

        }
    }

    /// <summary>
    /// Device State Information
    /// </summary>
    public struct NET_CLIENT_STATE
    {
        /// <summary>
        /// Channel Number
        /// </summary>
        public int channelcount;

        /// <summary>
        /// Alarm Input Number
        /// </summary>
        public int alarminputcount;

        /// <summary>
        /// External Alarm
        /// </summary>
        //[MarshalAs(UnmanagedType.ByValArray, ArraySubType = UnmanagedType.ByValTStr, SizeConst = 16)]
        //public char[] alarm;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 16)]
        public byte[] alarm;

        /// <summary>
        /// Motion Detection
        /// </summary>
        //[MarshalAs(UnmanagedType.ByValArray, ArraySubType = UnmanagedType.ByValTStr, SizeConst = 16)]
        //public char[] motiondection;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 16)]
        public byte[] motiondection;

        /// <summary>
        /// Video Loss
        /// </summary>
        //[MarshalAs(UnmanagedType.ByValArray, ArraySubType = UnmanagedType.ByValTStr, SizeConst = 16)]
        //public char[] videolost;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 16)]
        public byte[] videolost;
    }

    /// <summary>
    /// Device Channel State Information
    /// </summary>
    public struct NET_DEV_CHANNELSTATE
    {
        /// <summary>
        /// Whether the channel is recording,0-Not Record,1-Record
        /// </summary>
        public byte byRecordStatic;
        /// <summary>
        /// Signal State Connected,0-Normal,1-Signal Loss
        /// </summary>
        public byte bySignalStatic;
        /// <summary>
        /// Channel Hardware State,0-Normal,1-Abnormal,e.g.,DSP Crash
        /// </summary>
        public byte byHardwareStatic;
        /// <summary>
        /// Invalid Temporarily
        /// </summary>
        public char reserve;
        /// <summary>
        /// Actual Bit Rate,Invalid Temporarily
        /// </summary>
        public UInt32 dwBitRate;
        /// <summary>
        /// Client Connection Number, Invalid Temporarily
        /// </summary>
        public UInt32 dwLinkNum;
        /// <summary>
        /// Client IP Address,Invalid Temporarily
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 6)]
        public UInt32[] dwClientIP;
    }
	
    /// <summary>
    /// Disk Type
    /// </summary>
    public enum EM_DISK_TYPE
    {
        /// <summary>
        /// read write disk
        /// </summary>
        DISK_TYPE_READ_WRITE,
        /// <summary>
        /// read only disk
        /// </summary> 
        DISK_TYPE_READ_ONLY,
        /// <summary>
        /// back up disk or media disk
        /// </summary> 
        DISK_TYPE_BACKUP,
        /// <summary>
        /// redundancy disk
        /// </summary> 
        DISK_TYPE_REDUNDANT,
        /// <summary>
        /// snapshot disk
        /// </summary> 
        DISK_TYPE_SNAPSHOT,
    };

    /// <summary>
    /// Device HDD State Information
    /// </summary>
    public struct NET_DEV_DISKSTATE
    {
        /// <summary>
        /// HDD Volume (MB)
        /// </summary>
        public UInt32 dwVolume;
        /// <summary>
        /// HDD Freespace (MB)
        /// </summary>
        public UInt32 dwFreeSpace;
        /// <summary>
        /// higher 4 byte instruct hdd type, see the enum struct EM_DISK_TYPE; lower four byte instruct HDD status,0-hiberation,1-active,2-malfucntion and etc.;Devide DWORD into four BYTE.
        /// </summary>
        public byte dwStatus;
        /// <summary>
        /// HDD number
        /// </summary>
        public byte bDiskNum;
        /// <summary>
        /// Subarea number
        /// </summary>
        public byte bSubareaNum;
        /// <summary>
        /// Symbol. 0:local. 1:remote
        /// </summary>
        public byte bSignal;
    }

    /// <summary>
    /// disk record time
    /// </summary>
    public struct NET_DEV_DISK_RECORD_TIME
    {
        /// <summary>
        /// Start Time1
        /// </summary>
        public NET_TIME stuStartTime1;
        /// <summary>
        /// End Time1
        /// </summary>
        public NET_TIME stuEndTime1;
        /// <summary>
        /// is there two part or not
        /// </summary>
        public UInt32 bTwoPart;
        /// <summary>
        /// Start Time2
        /// </summary>
        public NET_TIME stuStartTime2;
        /// <summary>
        /// End Time2
        /// </summary>
        public NET_TIME stuEndTime2;
        /// <summary>
        /// HDD number
        /// </summary>
        public byte bDiskNum;
        /// <summary>
        /// Subarea number
        /// </summary>
        public byte bSubareaNum;
        /// <summary>
        /// Reserve
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 62)]
        public byte[] byReserved;
    }

    /// <summary>
    /// Device Work State Information
    /// </summary>
    public struct NET_DEV_WORKSTATE
    {
        /// <summary>
        /// Device State 0x00 Normal,0x01 CPU High Usage, 0x02 Hardware Error
        /// </summary>
        public UInt32 dwDeviceStatic;
        /// <summary>
        /// Device Not Support Temporarily
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 32)]
        public NET_DEV_DISKSTATE[] stHardDiskStatic;
        /// <summary>
        /// Channel State
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 16)]
        public NET_DEV_CHANNELSTATE[] stChanStatic;
        /// <summary>
        /// Alarm Port State 0-Alarm Free,1-Alarm
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 128)]
        public byte[] byAlarmInStatic;
        /// <summary>
        /// Alarm Output Port State 0-No Output,1-Output
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 64)]
        public byte[] byAlarmOutStatic;
        /// <summary>
        /// Local Display State 0-Normal,1-Abnormal
        /// </summary>
        public UInt32 dwLocalDisplay;
    }

    /// <summary>
    /// Serial Port Protocol Information(232 and 485)
    /// </summary>
    public struct PROTOCOL_INFO
    {
        /// <summary>
        /// Protocol Name 
        /// </summary>
        //[MarshalAs(UnmanagedType.ByValArray, ArraySubType = UnmanagedType.ByValTStr, SizeConst = 12)]
        //public char[] protocolname;
        [MarshalAs(UnmanagedType.ByValArray,  SizeConst = 12)]
        public byte[] protocolname;
        /// <summary>
        /// Baud Rate
        /// </summary>
        public uint baudbase;
        /// <summary>
        /// Data Bits
        /// </summary>
        public char databits;
        /// <summary>
        /// Stop Bit
        /// </summary>
        public char stopbits;
        /// <summary>
        /// Parity Bit
        /// </summary>
        public char parity;
        /// <summary>
        /// Not Support Temporary
        /// </summary>
        public char reserve;
    }

    /// <summary>
    /// Alarm IO Control(Alarm Output And Alarm Input Function)
    /// </summary>
    public struct ALARM_CONTROL
    {
        /// <summary>
        /// Port Number
        /// </summary>
        public ushort index;
        /// <summary>
        /// Port State
        /// </summary>
        public ushort state;
    }

    
    public struct OPR_RIGHT
    {
        public UInt32 dwID;
        //[MarshalAs(UnmanagedType.ByValArray, ArraySubType = UnmanagedType.ByValTStr, SizeConst = 32)]
        //public char[] name;
        [MarshalAs(UnmanagedType.ByValArray,  SizeConst = 32)]
        public byte[] name;
        //[MarshalAs(UnmanagedType.ByValArray, ArraySubType = UnmanagedType.ByValTStr, SizeConst = 32)]
        //public char[] memo;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 32)]
        public byte[] memo;
    }

    /// <summary>
    /// User Information
    /// </summary>
    public struct USER_INFO
    {
        public UInt32 dwID;
        public UInt32 dwGroupID;
        //[MarshalAs(UnmanagedType.ByValArray, ArraySubType = UnmanagedType.ByValTStr, SizeConst = 8)]
        //public char[] name;
        [MarshalAs(UnmanagedType.ByValArray,  SizeConst = 8)]
        public byte[] name;
        //[MarshalAs(UnmanagedType.ByValArray, ArraySubType = UnmanagedType.ByValTStr, SizeConst = 8)]
        //public char[] passWord;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 8)]
        public byte[] passWord;
        public UInt32 dwRightNum;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 100)]
        public UInt32[] rights;
        //[MarshalAs(UnmanagedType.ByValArray, ArraySubType = UnmanagedType.ByValTStr, SizeConst = 32)]
        //public char[] memo;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 32)]
        public byte[] memo;
        /// <summary>
        /// The user whether to allow reuse:1.Reuse;0:Not Reuse;
        /// </summary>
        public UInt32 dwReusable;
        public USER_INFO(string st)
        {
            dwID = new UInt32();
            dwGroupID = new UInt32();
            dwRightNum = new UInt32();
            dwReusable = new UInt32();
            name = new byte[8];
            passWord = new byte[8];
            rights = new UInt32[100];
            memo = new byte[32];
        }
    }

    /// <summary>
    /// User Group Structure
    /// </summary>
    public struct USER_GROUP_INFO
    {
        public UInt32 dwID;
        //[MarshalAs(UnmanagedType.ByValArray, ArraySubType = UnmanagedType.ByValTStr, SizeConst = 8)]
        //public char[] name;
        [MarshalAs(UnmanagedType.ByValArray,SizeConst = 8)]
        public byte[] name;
        public UInt32 dwRightNum;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 100)]
        public UInt32[] rights;
        //[MarshalAs(UnmanagedType.ByValArray, ArraySubType = UnmanagedType.ByValTStr, SizeConst = 32)]
        //public char[] memo;
        [MarshalAs(UnmanagedType.ByValArray,  SizeConst = 32)]
        public byte[] memo;
        public USER_GROUP_INFO(string strP)
        {
            dwID = new UInt32();
            name = new byte[8];
            dwRightNum = new UInt32();
            rights = new UInt32[100];
            memo = new byte[32];
        }
    }


    /// <summary>
    /// User Information Configuration Structure
    /// </summary>
    public struct USER_MANAGE_INFO
    {
        public UInt32 dwRightNum;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 100)]
        public OPR_RIGHT[] rightList;
        public UInt32 dwGroupNum;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 20)]
        public USER_GROUP_INFO[] groupList;
        public UInt32 dwUserNum;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 200)]
        public USER_INFO[] userList;
        /// <summary>
        /// Special Message:1.Enable Users to Reuse;0.Not Enable Users to Reuse;
        /// </summary>
        public UInt32 dwSpecial;
    }

    /// <summary>
    /// Log-Structured
    /// </summary>
    public struct NET_LOG_ITEM
    {
        /// <summary>
        /// Date
        /// </summary>
        public NET_TIME time;
        /// <summary>
        /// Type
        /// </summary>
        public UInt16 type;
        /// <summary>
        /// Reserve
        /// </summary>
        public byte reserved;
        /// <summary>
        /// Data
        /// </summary>
        public byte data;
        /// <summary>
        /// Content
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 8)]
        public byte[] context;
    }


    /// <summary>
    /// Query the Return Data Structure of the HDD Information
    /// </summary>
    public struct NET_HARDDISK_STATE
    {
        /// <summary>
        /// HDD Number
        /// </summary>
        public UInt32 dwDiskNum;
        /// <summary>
        /// Each HDD Information
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 256)]
        public NET_DEV_DISKSTATE[] stDisks;
    }

    /// <summary>
    /// Audio Data Format
    /// </summary>
    public struct NET_AUDIO_FORMAT
    {
        /// <summary>
        /// Encoding Type,0-PCM
        /// </summary>
        public byte byFormatTag;
        /// <summary>
        /// Sound Channel Number
        /// </summary>
        public UInt16 nChannels;
        /// <summary>
        /// Sampling Depth
        /// </summary>
        public UInt16 wBitsPerSample;
        /// <summary>
        /// Sample Rate 
        /// </summary>
        public UInt32 nSamplesPerSec;
    }

    /// <summary>
    /// Version Information
    /// Data organization on time：yyyymmdd
    /// </summary>
    public struct NET_VERSION_INFO
    {
        /// <summary>
        /// Version Number:High 16-bit Denote the Main Version Number,Low 16-bit Denote the Second Version Number
        /// </summary>
        public UInt32 dwSoftwareVersion;
        /// <summary>
        /// Build Time
        /// </summary>
        public UInt32 dwSoftwareBuildDate;
        /// <summary>
        /// DSP Version Number
        /// </summary>
        public UInt32 dwDspSoftwareVersion;
        /// <summary>
        /// DSP Bersion Build Time
        /// </summary>
        public UInt32 dwDspSoftwareBuildDate;
        /// <summary>
        /// Panel Version
        /// </summary>
        public UInt32 dwPanelVersion;
        /// <summary>
        /// Panel Software Creation Date
        /// </summary>
        public UInt32 dwPanelSoftwareBuildDate;
        /// <summary>
        /// Hardware Version 
        /// </summary>
        public UInt32 dwHardwareVersion;
        /// <summary>
        /// Hardware Production Date
        /// </summary>
        public UInt32 dwHardwareDate;
        /// <summary>
        /// Web Version
        /// </summary>
        public UInt32 dwWebVersion;
        /// <summary>
        /// Web Build Date
        /// </summary>
        public UInt32 dwWebBuildDate;
    }



    /// <summary>
    /// DSP Capability Description
    /// </summary>
    public struct NET_DSP_ENCODECAP
    {
        /// <summary>
        /// Video Format Mask,Bitwise Said Device Can Support the Video Formats
        /// </summary>
        public UInt32 dwVideoStandardMask;
        /// <summary>
        /// Resolution Mask,Bitwise Said Device Can Support the Resolution Setting
        /// </summary>
        public UInt32 dwImageSizeMask;
        /// <summary>
        /// Encode Mode Mask,Bitwise Said Device Can Support the Coding mode setting
        /// </summary>
        public UInt32 dwEncodeModeMask;
        /// <summary>
        /// Bitwise Said Device Can Support the Multi-Media Function:The 1-bit support for the main stream,The 2-bit support for sub stream1,The 3-bit support for sub stream2,The 4-bit support for jpg capture
        /// </summary>
        public UInt32 dwStreamCap;
        /// <summary>
        /// When the main stream for the resolution, the sub stream resolution mask support
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 8)]
        public UInt32[] dwImageSizeMask_Assi;
        /// <summary>
        /// DSP Support the Highest Coding Ability
        /// </summary>
        public UInt32 dwMaxEncodePower;
        /// <summary>
        /// Each DSP Supports Up to the Input Video Channel Number 
        /// </summary>
        public UInt16 wMaxSupportChannel;
        /// <summary>
        /// DSP biggest coding Settings per channel are synchronous 0-non-synchronous, 1-synchronous
        /// </summary>
        public UInt16 wChannelMaxSetSync;
    }

    /// <summary>
    /// Device Channel Count Info
    /// </summary
    public  struct NET_CHN_COUNT_INFO
    {
        public UInt32   dwSize;
        public int      nMaxTotal;              // 设备总通道数(所有有效通道数之和)
        public int      nCurTotal;              // 已配置的通道数
        public int      nMaxLocal;              // 最大本地通道数, 含主板和可插拔子卡通道
        public int      nCurLocal;              // 已配置本地通道数
        public int      nMaxRemote;             // 最大远程通道数
        public int      nCurRemote;             // 已配置远程通道数
    } ;

    /// <summary>
    /// Device Channel Count
    /// </summary
    public struct NET_DEV_CHN_COUNT_INFO
    {
        public UInt32 dwSize;
        public NET_CHN_COUNT_INFO     stuVideoIn;             // Video in channel count
        public NET_CHN_COUNT_INFO      stuVideoOut;            // Video out channel count
    }

    /// <summary>
    /// Device Configuration Information
    /// </summary>
    public struct NETDEV_SYSTEM_ATTR_CFG
    {
        /// <summary>
        /// 
        /// </summary>
        public UInt32 dwSize;
        /*Below is a read only part of the device*/
        /// <summary>
        /// Version
        /// </summary>
        public NET_VERSION_INFO stVersion;
        /// <summary>
        /// DSP Capability Description
        /// </summary>
        public NET_DSP_ENCODECAP stDspEncodeCap;
        /// <summary>
        /// Serial Number
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 48)]
        public byte[] szDevSerialNo;
        /// <summary>
        /// Serial Number Turn Into a String
        /// </summary>
        /// <returns></returns>
        public string DevSerialNo()
        {
            string result = "";
            foreach (byte bt in szDevSerialNo)
            {
                result += bt.ToString("D");
            }
            return result;
        }
        /// <summary>
        /// Device Type,See the Enumeration NET_DEVICE_TYPE
        /// </summary>
        public byte byDevType;
        /// <summary>
        /// Display Standard Device Types Description
        /// </summary>
        /// <returns></returns>
        public string DevType()
        {
            string result = "";
            switch(int.Parse(byDevType.ToString()))
            {
                case (int)NET_DEVICE_TYPE.NET_DVR_DDNS:
                    result = "DDNS Server";
                    break;
                case (int)NET_DEVICE_TYPE.NET_DVR_MEPG4_SH2:
                    result = "MPEG4 Shihao Recoder";
                    break;
                case (int)NET_DEVICE_TYPE.NET_DVR_MEPG4_ST2:
                    result = "MPEG4 Shitong Recoder";
                    break;
                case (int)NET_DEVICE_TYPE.NET_DVR_MPEG1_2:
                    result = "MPEG1 Two Channel Recoder";
                    break;
                case (int)NET_DEVICE_TYPE.NET_DVR_MPEG1_8:
                    result = "MPEG1 Eight Channel Recoder ";
                    break;
                case (int)NET_DEVICE_TYPE.NET_DVR_MPEG4_16:
                    result = "MPEG4 Sixteen Channel Recoder";
                    break;
                case (int)NET_DEVICE_TYPE.NET_DVR_MPEG4_8:
                    result = "MPEG4 Eight Channel Recoder";
                    break;
                case (int)NET_DEVICE_TYPE.NET_DVR_MPEG4_GBE:
                    result = "MPEG4 Shitong 2th Generation Enhanced Recorder";
                    break;
                case (int)NET_DEVICE_TYPE.NET_DVR_MPEG4_NVSII:
                    result = "MPEG4 Network Video Server II Generation";
                    break;
                case (int)NET_DEVICE_TYPE.NET_DVR_MPEG4_SX2:
                    result = "MPEG4 Shixin 16 Channel Recorder";
                    break;
                case (int)NET_DEVICE_TYPE.NET_DVR_NONREALTIME:
                    result = "Not Real-Time";
                    break;
                case (int)NET_DEVICE_TYPE.NET_DVR_NONREALTIME_MACE:
                    result = "Not Real-Time MACE";
                    break;
                case (int)NET_DEVICE_TYPE.NET_DVR_STD_NEW:
                    result = "New Standard Configuration Protocal";
                    break;
                case (int)NET_DEVICE_TYPE.NET_NVS_MPEG1:
                    result = "Network Video Server";
                    break;
                case (int)NET_DEVICE_TYPE.NET_PRODUCT_NONE:
                    result = "None";
                    break;
            }
            return result;
        }
        /// <summary>
        /// Device Model In Detail, String Format, Which May Be Null
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 32)]
        public byte[] szDevType;
        /// <summary>
        /// Video Port Number
        /// </summary>
        public byte byVideoCaptureNum;
        /// <summary>
        /// Audio Port Number
        /// </summary>
        public byte byAudioCaptureNum;
        /// <summary>
        /// NSP
        /// </summary>
        public byte byTalkInChanNum;
        /// <summary>
        /// NSP
        /// </summary>
        public byte byTalkOutChanNum;
        /// <summary>
        /// NSP
        /// </summary>
        public byte byDecodeChanNum;
        /// <summary>
        /// Alarm Input Number
        /// </summary>
        public byte byAlarmInNum;
        /// <summary>
        /// Alarm Output Number
        /// </summary>
        public byte byAlarmOutNum;
        /// <summary>
        /// Network Port Number
        /// </summary>
        public byte byNetIONum;
        /// <summary>
        /// USB Port Number
        /// </summary>
        public byte byUsbIONum;
        /// <summary>
        /// IDE Number
        /// </summary>
        public byte byIdeIONum;
        /// <summary>
        /// Serial Number
        /// </summary>
        public byte byComIONum;
        /// <summary>
        /// Parallel Port Number
        /// </summary>
        public byte byLPTIONum;
        /// <summary>
        /// NSP
        /// </summary>
        public byte byVgaIONum;
        /// <summary>
        /// NSP
        /// </summary>
        public byte byIdeControlNum;
        /// <summary>
        /// NSP
        /// </summary>
        public byte byIdeControlType;
        /// <summary>
        /// NSP,Extension Description 
        /// </summary>
        public byte byCapability;
        /// <summary>
        /// Video Matrix Output Number
        /// </summary>
        public byte byMatrixOutNum;
        /*The following is the write part of the device*/
        /// <summary>
        /// Disk Full Treatment(Cover、Stop)
        /// </summary>
        public byte byOverWrite;
        /// <summary>
        /// Video Package Length
        /// </summary>
        public byte byRecordLen;
        /// <summary>
        /// NSP
        /// </summary>
        public byte byStartChanNo;
        /// <summary>
        /// Device Number,Used For Remote Control
        /// </summary>
        public UInt16 wDevNo;
        /// <summary>
        /// Video Format
        /// </summary>
        public byte byVideoStandard;
        /// <summary>
        /// Date Format
        /// </summary>
        public byte byDateFormat;
        /// <summary>
        /// Date Separator(0-".", 1-"-", 2-"/")
        /// </summary>
        public byte byDateSprtr;
        /// <summary>
        /// Time Format (0-24Hour,1－12Hour)
        /// </summary>
        public byte byTimeFmt;
        /// <summary>
        /// Reserved Word
        /// </summary>
        public byte byReserved;
    }

    /// <summary>
    /// Speak Param
    /// </summary>
    public struct NET_SPEAK_PARAM
    {
        public int dwSize;
        /// <summary>
        /// 0：对讲（默认模式），1：喊话；从喊话切换到对讲要重新设置
        /// </summary>
        public int nMode;
        /// <summary>
        /// 扬声器通道号，喊话时有效
        /// </summary>      
        public int nSpeakChannel;       
    }

    // 邮件附件类型
    public enum DH_TALK_CODING_TYPE
    {
        DH_TALK_DEFAULT = 0,                        // 无头PCM
        DH_TALK_PCM = 1,                            // 带头PCM
        DH_TALK_G711a,                              // G711a
        DH_TALK_AMR,                                // AMR
        DH_TALK_G711u,                              // G711u
        DH_TALK_G726,                               // G726
        DH_TALK_G723_53,                            // G723_53
        DH_TALK_G723_63,                            // G723_63
        DH_TALK_AAC,                                // AAC
        DH_TALK_OGG,                                // OGG
        DH_TALK_ADPCM = 21,                         // ADPCM
        DH_TALK_MP3 = 22,                           // MP3
    }

    /// <summary>
    /// Talk Decode Info
    /// </summary>
    public struct DHDEV_TALKDECODE_INFO// 语音编码信息
    {
        /// <summary>
        /// 编码类型
        /// </summary>
        public DH_TALK_CODING_TYPE encodeType;                       
        /// <summary>
        /// 位数，如8或16
        /// </summary>
        public int                 nAudioBit;    
        /// <summary>
        /// 采样率，如8000或16000
        /// </summary>              
        public int                 dwSampleRate;        
        /// <summary>
        /// 打包周期, 单位ms
        /// </summary>        
        public int                 nPacketPeriod;                      
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 60)]
        public byte[] reserved;
    }

    /// <summary>
    /// Time Structure  
    /// </summary>
    public struct NET_TSECT
    {
        public bool bEnable;
        public int iBeginHour;
        public int iBeginMin;
        public int iBeginSec;
        public int iEndHour;
        public int iEndMin;
        public int iEndSec;
    }

    /// <summary>
    /// Time Structure[Length6]
    /// </summary>
    public struct NET_REC_TSECT
    {
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 6)]
        public NET_TSECT[] sTSECT;
    }
    
    /// <summary>
    /// Area:The margin according to the proportion of the whole length 8192 
    /// </summary>
    public struct NET_RECT
    {
        public int left;
        public int top;
        public int right;
        public int bottom;
    }

    /// <summary>
    /// OSD Attribute Structure  
    /// </summary>
    public struct NET_ENCODE_WIDGET
    {
        /// <summary>
        /// The Prospect of the Object RGB,and Transparency  
        /// </summary>
        public UInt32 rgbaFrontground;
        /// <summary>
        /// The Background of the Object RGB,and Transparency 
        /// </summary>
        public UInt32 rgbaBackground;
        /// <summary>
        /// Position  
        /// </summary>
        public NET_RECT rcRect;
        /// <summary>
        /// Objects Displayed
        /// </summary>
        public byte bShow;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 3)]
        public byte[] byReserved;
    }

    /// <summary>
    /// Channel Audio and Video Properties 
    /// </summary>
    public struct NET_VIDEOENC_OPT
    {
        //Video Parameter
        /// <summary>
        /// Video Enable:1－Open,0－Close
        /// </summary>
        public byte byVideoEnable;
        /// <summary>
        /// Bit Rate Control, Reference to Constant Defines
        /// </summary>
        public byte byBitRateControl;
        /// <summary>
        /// Frame
        /// </summary>
        public byte byFramesPerSec;
        /// <summary>
        /// Encode Mode, Reference to Constant Defines 
        /// </summary>
        public byte byEncodeMode;
        /// <summary>
        /// Resolution, Reference to Constant Defines 
        /// </summary>
        public byte byImageSize;
        /// <summary>
        /// Grade1-6 
        /// </summary>
        public byte byImageQlty;
        /// <summary>
        /// Limit Stream Parameters, Range：50~4*1024 (k)
        /// </summary>
        public UInt16 wLimitStream;

        //Audio Parameters 
        /// <summary>
        /// Audio Enable:1－Open,0－Close
        /// </summary>
        public byte byAudioEnable;
        /// <summary>
        /// Encoding Type,Like PCM
        /// </summary>
        public byte wFormatTag;
        /// <summary>
        /// Video Channel Number
        /// </summary>
        public UInt16 nChannels;
        /// <summary>
        /// Sampling Depth	
        /// </summary>
        public UInt16 wBitsPerSample;
        /// <summary>
        /// Sample Rate 
        /// </summary>
        public UInt32 nSamplesPerSec;
        /// <summary>
        /// Reserved Word 
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 2)]
        public byte[] reserved;
    }

    /// <summary>
    /// Picture Color Attribute
    /// </summary>
    public struct NET_COLOR_CFG
    {
        public NET_TSECT stSect;
        /// <summary>
        /// Brightness	0-100
        /// </summary>
        public byte byBrightness;
        /// <summary>
        /// Contrast	0-100
        /// </summary>
        public byte byContrast;
        /// <summary>
        /// Saturation 	0-100
        /// </summary>
        public byte bySaturation;
        /// <summary>
        /// Chroma	0-100
        /// </summary>
        public byte byHue;
        /// <summary>
        /// Gain Enabled	  
        /// </summary>
        public byte byGainEn;
        /// <summary>
        /// Gain	0-100
        /// </summary>
        public byte byGain;

        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 2)]
        public byte[] byReserved;
    }



    /// <summary>
    /// Image Channel Attribute Structure
    /// </summary>
    public struct NETDEV_CHANNEL_CFG
    {
        public UInt32 dwSize;
        /// <summary>
        /// 
        /// </summary>
        //[MarshalAs(UnmanagedType.ByValArray, ArraySubType = UnmanagedType.ByValTStr, SizeConst = 32)]
        //public char[] szChannelName;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 32)]
        public byte[] szChannelName;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 3)]
        public NET_VIDEOENC_OPT[] stMainVideoEncOpt;
        /// <summary>
        ///  Usually Refers to Network Transmission Stream	
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 3)]
        public NET_VIDEOENC_OPT[] stAssiVideoEncOpt;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 2)]
        public NET_COLOR_CFG[] stColorCfg;
        public NET_ENCODE_WIDGET stTimeOSD;
        public NET_ENCODE_WIDGET stChannelOSD;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 1)]
        public NET_ENCODE_WIDGET[] stBlindCover;

        /// <summary>
        ///  Area Cover Switches,0x00 Not Enable Cover,0x01 Only Cover, Device Local Preview,0x10 Only cover the video(and Network preview),0x11 All Cover
        ///  </summary>
        public byte byBlindEnable;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 3)]
        public byte[] byReserved;
    }

    /// <summary>
    /// Preview Image Parameters
    /// </summary>
    public struct NETDEV_PREVIEW_CFG
    {
        public UInt32 dwSize;
        public NET_VIDEOENC_OPT stPreView;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 2)]
        public NET_COLOR_CFG[] stColorCfg;
    }

    /// <summary>
    /// Voice Intercom Audio Properties
    /// </summary>
    public struct NETDEV_TALK_CFG
    {
        #region << Audio Input Parameters >>
        /// <summary>
        /// Encoding Type ,Like PCM
        /// </summary>
        public byte byInFormatTag;
        /// <summary>
        /// Audio Channel Number
        /// </summary>
        public byte byInChannels;
        /// <summary>
        /// Sampling Depth	
        /// </summary>
        public UInt16 wInBitsPerSample;
        /// <summary>
        /// Sample Rate
        /// </summary>
        public UInt32 dwInSamplesPerSec;

        #endregion

        #region << Audio Output Parameters >>
        /// <summary>
        /// Encoding Type ,Like PCM
        /// </summary>
        public byte byOutFormatTag;
        /// <summary>
        /// Audio Channel Number
        /// </summary>
        public byte byOutChannels;
        /// <summary>
        /// Sampling Depth
        /// </summary>
        public UInt16 wOutBitsPerSample;
        /// <summary>
        /// Sample Rate
        /// </summary>
        public UInt32 dwOutSamplesPerSec;
        #endregion

    }

    /// <summary>
    /// Timing Video
    /// </summary>
    public struct NETDEV_RECORD_CFG
    {
        
        public UInt32 dwSize;
        /// <summary>
        /// Time Structure
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 7)]
        public NET_REC_TSECT[] stSect;
        /// <summary>
        /// Pre-record Time,The Unit Is s,0 Denote Not Pre-record 
        /// </summary>
        public byte byPreRecordLen;
        /// <summary>
        /// Video Redundancy Switch
        /// </summary>
        public byte byRedundancyEn;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 2)]
        public byte[] byReserved;
    }

    /// <summary>
    /// Alarm Config
    /// </summary>
    public struct NET_PTZ_LINK
    {
        public int iType;
        public int iValue;
    }

    /// <summary>
    /// Message Trigger Configuration
    /// Message Handling Method, A Variety of Treatment At the Same Time,Include
    /// 0x00000001 - Network:Upload the Management Server
    /// 0x00000002 - Record:Trigger
    /// 0x00000004 - PTZ Linkage
    /// 0x00000008 - Sendmail
    /// 0x00000010 - Device Local Alarm Round Tour
    /// 0x00000020 - Device Hint Enable
    /// 0x00000040 - Device Alarm Output Enable
    /// 0x00000080 - Ftp Upload Enable
    /// 0x00000100 - Buzzing
    /// 0x00000200 - Voice Prompt
    /// 0x00000400 - Snap Enable
    /// </summary>
    public struct NET_MSG_HANDLE
    {
        /// <summary>
        /// Handling Supported By the Current Alarm,Bitwise Mask Express
        /// </summary>
        public UInt32 dwActionMask;
        /// <summary>
        /// Trigger Action,Bitwise Mask Express,The parameters of the specific actions required are reflected in their respective configuration
        /// </summary>
        public UInt32 dwActionFlag;
        /// <summary>
        /// Alarm Trigger Output Channel, 1 Denote Trigger the Output
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 16)]
        public byte[] byRelAlarmOut;
        /// <summary>
        /// Alarm Duration
        /// </summary>
        public UInt32 dwDuration;
        /// <summary>
        /// Linkage Video, Alarm Trigger Video Channel,1 Denote Trigger The Channel	
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 16)]
        public byte[] byRecordChannel;
        /// <summary>
        /// Record Duration 
        /// </summary>
        public UInt32 dwRecLatch;
        /// <summary>
        /// Cauture Channel
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 16)]
        public byte[] bySnap;
        /// <summary>
        /// Round Round Channel
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 16)]
        public byte[] byTour;
        /// <summary>
        /// PTZ Linkage
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 16)]
        public NET_PTZ_LINK[] struPtzLink;
        /// <summary>
        ///  Event Delay Time. [0-15]s , defalut value is 0
        /// </summary>
        public UInt32  dwEventLatch;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 16)]
        public byte[]   byRelWIAlarmOut;
        public byte     bMessageToNet;
        public byte     bMMSEn;                                 
        public byte     bySnapshotTimes;                        
        public byte     bMatrixEn;                              
        public UInt32   dwMatrix;                                        
        public byte     bLog;                                 
        public byte     bSnapshotPeriod;                       
        public byte     byEmailType;                            
        public byte     byEmailMaxLength;                      
        public byte     byEmailMaxTime; 
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 99)]                
        public byte[]   byReserved;  
    }

    /// <summary>
    /// External Alarms
    /// </summary>
    public struct NET_ALARMIN_CFG
    {
        /// <summary>
        /// Alarm Type,0：Normal Close ,1：Normal Open   	
        /// </summary>
        public byte byAlarmType;
        /// <summary>
        /// Alarm Enable Alarm Enable
        /// </summary>
        public byte byAlarmEn;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 2)]
        public byte[] byReserved;
        /// <summary>
        /// NSP
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 7)]
        public NET_REC_TSECT[] stSect;
        /// <summary>
        /// Process Mode
        /// </summary>
        public NET_MSG_HANDLE struHandle;
    }

    /// <summary>
    /// Surveyed Area[Length16]
    /// </summary>
    public struct NET_DETECT
    {
        [MarshalAs(UnmanagedType.ByValArray, SizeConst =32)]
        public byte[] Detected;
    }

    /// <summary>
    /// Motion Detection
    /// </summary>
    public struct NET_MOTION_DETECT_CFG
    {
        /// <summary>
        /// Motion Detection Alarm Enable(Enable)
        /// </summary>
        public byte byMotionEn;

        public byte byReserved;
        /// <summary>
        /// Sensitivity 
        /// </summary>
        public UInt16 wSenseLevel;
        /// <summary>
        /// The Number of Rows Motion Detection Area
        /// </summary>
        public UInt16 wMotionRow;
        /// <summary>
        /// The Number of Column Motion Detection Area
        /// </summary>
        public UInt16 wMotionCol;
        /// <summary>
        /// Detection Area,A Total of 32 * 32 Area
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 32)]
        public NET_DETECT[] byDetected;
        /// <summary>
        /// NSP
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 7)]
        public NET_REC_TSECT[] stSect;
        /// <summary>
        /// Process Mode
        /// </summary>
        public NET_MSG_HANDLE struHandle;
    }

    /// <summary>
    /// Video Loss Alarm
    /// </summary>
    public struct NET_VIDEO_LOST_CFG
    {
        /// <summary>
        /// Video Loss Alarm Enable
        /// </summary>
        public byte byAlarmEn;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 3)]
        public byte[] byReserved;
        /// <summary>
        /// NSP
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 7)]
        public NET_REC_TSECT[] stSect;
        /// <summary>
        /// Process Mode
        /// </summary>
        public NET_MSG_HANDLE struHandle;
    }

    /// <summary>
    /// Image Block Alarm
    /// </summary>
    public struct NET_BLIND_CFG
    {
        /// <summary>
        /// Enable
        /// </summary>
        public byte byBlindEnable;
        /// <summary>
        /// Sensitivity 1-6 
        /// </summary>
        public byte byBlindLevel;

        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 2)]
        public byte[] byReserved;
        /// <summary>
        /// NSP
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 7)]
        public NET_REC_TSECT[] stSect;
        /// <summary>
        /// Process Mode
        /// </summary>
        public NET_MSG_HANDLE struHandle;
    }

    /// <summary>
    /// HDD Message(Internal Alarm)
    /// </summary>
    public struct NET_DISK_ALARM_CFG
    {
        /// <summary>
        /// No HDD Alarm
        /// </summary>
        public byte byNoDiskEn;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 3)]
        public byte[] byReserved_1;
        /// <summary>
        /// NSP
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 7)]
        public NET_REC_TSECT[] stNDSect;
        /// <summary>
        /// Process Mode 
        /// </summary>
        public NET_MSG_HANDLE struNDHandle;
        /// <summary>
        /// HDD Low Vilume Alarm
        /// </summary>
        public byte byLowCapEn;
        /// <summary>
        /// Volume Threshold 0-99
        /// </summary>
        public byte byLowerLimit;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 2)]
        public byte[] byReserved_2;
        /// <summary>
        /// NSP
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 7)]
        public NET_REC_TSECT[] stLCSect;
        /// <summary>
        /// Process Mode  
        /// </summary>
        public NET_MSG_HANDLE struLCHandle;
        /// <summary>
        /// HDD failure Alarm
        /// </summary>
        public byte byDiskErrEn;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 3)]
        public byte[] byReserved_3;
        /// <summary>
        /// NSP
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 7)]
        public NET_REC_TSECT[] stEDSect;
        /// <summary>
        /// Process Mode 
        /// </summary>
        public NET_MSG_HANDLE struEDHandle;
    }

    public struct NET_NETBROKEN_ALARM_CFG
    {
        public byte byEnable;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 3)]
        public byte[] byReserved;
        public NET_MSG_HANDLE struHandle;
    }

    /// <summary>
    /// Alarm Protection
    /// </summary>
    public struct NETDEV_ALARM_SCHEDULE
    {
        public UInt32 dwSize;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 16)]
        public NET_ALARMIN_CFG[] struLocalAlmIn;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 16)]
        public NET_ALARMIN_CFG[] struNetAlmIn;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 16)]
        public NET_MOTION_DETECT_CFG[] struMotion;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 16)]
        public NET_VIDEO_LOST_CFG[] struVideoLost;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 16)]
        public NET_BLIND_CFG[] struBlind;
        public NET_DISK_ALARM_CFG struDiskAlarm;
        public NET_NETBROKEN_ALARM_CFG struNetBrokenAlarm;
    }


    // Alarm Linkage Extension Structure
    public struct NET_MSG_HANDLE_EX
    {
	    /* Message Handling Method, A Variety of Treatment At the Same Time,Include
	     * 0x00000001 - Alarm Upload
	     * 0x00000002 - Linkage Video
	     * 0x00000004 - PTZ Linkage
	     * 0x00000008 - Sendmail
	     * 0x00000010 - Local Tour Round
	     * 0x00000020 - Local Tip
	     * 0x00000040 - Alarm Output
	     * 0x00000080 - Ftp Upload
	     * 0x00000100 - Buzzing
	     * 0x00000200 - Voice Prompt
	     * 0x00000400 - Capture
	    */

        /// <summary>
        /// Handling Supported By the Current Alarm,Bitwise Mask Express
        /// </summary>
	    public UInt32				dwActionMask;

        /// <summary>
        /// Handling Supported By the Current Alarm,Bitwise Mask Express
        /// </summary>
	    public UInt32				dwActionFlag;
    	
        /// <summary>
        /// Alarm Trigger Output Channel, 1 Denote Trigger the Output
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 32)]
	    public byte[]				byRelAlarmOut;
        /// <summary>
        /// Alarm Duration
        /// </summary>
	    public UInt32				dwDuration;

        /// <summary>
        /// Linkage Record
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 32)]
	    public byte[]				byRecordChannel; /* Alarm Trigger Record Channel, 1 Denote Trigger the Output*/
        /// <summary>
        /// Record Duration
        /// </summary>
	    public UInt32				dwRecLatch;

        /// <summary>
        /// Cauture Channel
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 32)]
	    public byte[]				bySnap;
        /// <summary>
        /// Round Round Channel
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 32)]
	    public byte[]				byTour;

        /// <summary>
        /// PTZ Linkage
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 32)]
	    public NET_PTZ_LINK[]			struPtzLink;
        /// <summary>
        /// Linkage Start Delay Time,s Is Unit,Range is 0~15,Default is 0
        /// </summary>
	    public UInt32				dwEventLatch;
        /// <summary>
        /// Alarm Trigger Wireless Output Channel, Alarm Trigger Output, 1 Denote Trigger the Output
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 32)]
	    public byte[]			byRelWIAlarmOut;
	    public byte				bMessageToNet;
        /// <summary>
        /// Message Alarm Enable
        /// </summary>
	    public byte                bMMSEn;
        /// <summary>
        /// Text messaging capture number
        /// </summary>
	    public byte                bySnapshotTimes;
        /// <summary>
        /// Matrix Enable
        /// </summary>
	    public byte				bMatrixEn;
        /// <summary>
        /// Matrix Mask
        /// </summary>
	    public UInt32				dwMatrix;
	    /// <summary>
	    /// Blog Enable,Only Used In WTN Motion Detection currently
	    /// </summary>
	    public byte				bLog;
        /// <summary>
        /// Capture Frame Interval,Every how many frames to grasp a picture,Captured within a certain time the number of picture is also related to the captured frame。0 Denote Not Every Frame,Continuous Capture。
        /// </summary>
	    public byte				bSnapshotPeriod;
        /// <summary>
        /// Round Round channel 32-63 Channel
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 32)]
	    public byte[]				byTour2;
        /// <summary>
        /// 0,Photo Attachments,1,Record Attachments
        /// </summary>
	    public byte                byEmailType;
        /// <summary>
        /// The Maximum Length of the Attachment Video,Unit is MB
        /// </summary>
	    public byte                byEmailMaxLength;
        /// <summary>
        /// The Maximum Time of the Attachment Video,Unit is Second
        /// </summary>
	    public byte                byEmailMaxTime;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 475)]
	    public byte[]				byReserved;   
    }



    /// <summary>
    /// External Alarm Extension
    /// </summary>
    public struct NET_ALARMIN_CFG_EX
    {
        /// <summary>
        /// Alarm Type,0：normal close,1：normal open
        /// </summary>
	    public byte				byAlarmType;
        /// <summary>
        /// Alarm Enable
        /// </summary>
	    public byte				byAlarmEn;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 2)]
	    public byte[]				byReserved;				
        /// <summary>
        /// NSP
        /// </summary>
		[MarshalAs(UnmanagedType.ByValArray, SizeConst = 7*6)]
	    public NET_TSECT[]			stSect;
        /// <summary>
        /// Process Mode
        /// </summary>
	    public NET_MSG_HANDLE_EX	struHandle;
    }

    /// <summary>
    /// Ethernet Configuration
    /// </summary>
    public struct NET_ETHERNET
    {
        /// <summary>
        /// DVR IP Address  
        /// </summary>
        //[MarshalAs(UnmanagedType.ByValArray, ArraySubType = UnmanagedType.ByValTStr, SizeConst = 16)]
        //public char[] sDevIPAddr;
        [MarshalAs(UnmanagedType.ByValArray,  SizeConst = 16)]
        public byte[] sDevIPAddr;
        /// <summary>
        /// DVR IP Address Mask
        /// </summary>
        //[MarshalAs(UnmanagedType.ByValArray, ArraySubType = UnmanagedType.ByValTStr, SizeConst = 16)]
        //public char[] sDevIPMask;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 16)]
        public byte[] sDevIPMask;
        /// <summary>
        ///  Default Gateway    
        /// </summary>
        //[MarshalAs(UnmanagedType.ByValArray, ArraySubType = UnmanagedType.ByValTStr, SizeConst = 16)]
        //public char[] sGatewayIP;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 16)]
        public byte[] sGatewayIP;
        /// <summary>
        /// NSP
        /// 10M/100M  Self-Adaption,Index
        /// 1-10MBase - T
        /// 2-10MBase-T Full Duplex  
        /// 3-100MBase - TX
        /// 4-100M Full Duplex
        /// 5-10M/100M  Self-Adaption 
        /// </summary>
        public UInt32 dwNetInterface;
        /// <summary>
        /// MAC Address,Read-Only   
        /// </summary>
        //[MarshalAs(UnmanagedType.ByValArray, ArraySubType = UnmanagedType.ByValTStr, SizeConst = 40)]
        //public char[] byMACAddr;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 40)]
        public byte[] byMACAddr;
    }

    /// <summary>
    /// Remote Host Configuration
    /// </summary>
    public struct NET_REMOTE_HOST
    {
        /// <summary>
        /// Connect Enable
        /// </summary>
        public byte byEnable;
        public byte byReserved;
        /// <summary>
        /// Remote Host Port
        /// </summary>
        public UInt16 wHostPort;
        /// <summary>
        /// Remote Host IP Address
        /// </summary>
        //[MarshalAs(UnmanagedType.ByValArray, ArraySubType = UnmanagedType.ByValTStr, SizeConst = 16)]
        //public char[] sHostIPAddr;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 16)]
        public byte[] sHostIPAddr;
        /// <summary>
        /// Remote Host User Name
        /// </summary>
        //[MarshalAs(UnmanagedType.ByValArray, ArraySubType = UnmanagedType.ByValTStr, SizeConst = 64)]
        //public char[] sHostUser;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 64)]
        public byte[] sHostUser;
        /// <summary>
        /// Remote Host Password
        /// </summary>
        //[MarshalAs(UnmanagedType.ByValArray, ArraySubType = UnmanagedType.ByValTStr, SizeConst = 32)]
        //public char[] sHostPassword;
        [MarshalAs(UnmanagedType.ByValArray,  SizeConst = 32)]
        public byte[] sHostPassword;
    }

    /// <summary>
    /// Email Configuration
    /// </summary>
    public struct NET_MAIL_CFG
    {
        /// <summary>
        /// Mail Servers IP Address
        /// </summary>
        //[MarshalAs(UnmanagedType.ByValArray, ArraySubType = UnmanagedType.ByValTStr, SizeConst = 16)]
        //public char[] sMailIPAddr;
        [MarshalAs(UnmanagedType.ByValArray, ArraySubType = UnmanagedType.ByValTStr, SizeConst = 16)]
        public byte[] sMailIPAddr;

        /// <summary>
        /// Mail Servers Port
        /// </summary>
        public UInt16 wMailPort;
        /// <summary>
        /// Reserve
        /// </summary>
        public UInt16 wReserved;
        /// <summary>
        /// Send Address
        /// </summary>
        //[MarshalAs(UnmanagedType.ByValArray, ArraySubType = UnmanagedType.ByValTStr, SizeConst = 128)]
        //public char[] sSenderAddr;
        [MarshalAs(UnmanagedType.ByValArray, ArraySubType = UnmanagedType.ByValTStr, SizeConst = 128)]
        public byte[] sSenderAddr;
        /// <summary>
        /// User Name
        /// </summary>
        //[MarshalAs(UnmanagedType.ByValArray, ArraySubType = UnmanagedType.ByValTStr, SizeConst = 16)]
        //public char[] sUserName;
        [MarshalAs(UnmanagedType.ByValArray,SizeConst = 16)]
        public byte[] sUserName;
        ///// <summary>
        ///// User Name String
        ///// </summary>
        ///// <returns></returns>
        //public string UserName()
        //{
        //    string result = "";
        //    foreach (char chr in sUserName)
        //    {
        //        if (chr != '\0')
        //        {
        //            result += chr.ToString();
        //        }
        //    }
        //    return result;
        //}
        /// <summary>
        /// user Password
        /// </summary>
        //[MarshalAs(UnmanagedType.ByValArray, ArraySubType = UnmanagedType.ByValTStr, SizeConst = 16)]
        //public char[] sUserPsw;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 16)]
        public byte[] sUserPsw;

        ///// <summary>
        ///// User Password String
        ///// </summary>
        ///// <returns></returns>
        //public string UserPsw()
        //{
        //    string result = "";
        //    foreach (char chr in sUserPsw)
        //    {
        //        if (chr != '\0')
        //        {
        //            result += chr.ToString();
        //        }
        //    }
        //    return result;
        //}

        /// <summary>
        /// Destination Address
        /// </summary>
        //[MarshalAs(UnmanagedType.ByValArray, ArraySubType = UnmanagedType.ByValTStr, SizeConst = 128)]
        //public char[] sDestAddr;
        [MarshalAs(UnmanagedType.ByValArray,  SizeConst = 128)]
        public byte[] sDestAddr;
        /// <summary>
        /// CC Address
        /// </summary>
        //[MarshalAs(UnmanagedType.ByValArray, ArraySubType = UnmanagedType.ByValTStr, SizeConst = 128)]
        //public char[] sCcAddr;
        [MarshalAs(UnmanagedType.ByValArray,  SizeConst = 128)]
        public byte[] sCcAddr;
        /// <summary>
        /// CC Address String
        /// </summary>
        /// <returns></returns>
        public string CcAddr()
        {
            string result = "";
            foreach (char chr in sCcAddr)
            {
                if (chr != '\0')
                {
                    result += chr.ToString();
                }
            }
            return result;
        }
        /// <summary>
        /// Dark Copy Address
        /// </summary>
        //[MarshalAs(UnmanagedType.ByValArray, ArraySubType = UnmanagedType.ByValTStr, SizeConst = 128)]
        //public char[] sBccAddr;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 128)]
        public byte[] sBccAddr;
        /// <summary>
        /// Dark Copy Address String
        /// </summary>
        /// <returns></returns>
        public string BccAddr()
        {
            string result = "";
            foreach (char chr in sBccAddr)
            {
                if (chr != '\0')
                {
                    result += chr.ToString();
                }
            }
            return result;
        }
        /// <summary>
        /// Title
        /// </summary>        
        //[MarshalAs(UnmanagedType.ByValArray, ArraySubType = UnmanagedType.ByValTStr, SizeConst = 64)]
        //public char[] sSubject;        
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 64)]
        public byte[] sSubject;       
        /// <summary>
        /// Title String
        /// </summary>
        /// <returns></returns>
        public string Subject()
        {
            string result = "";
            foreach (byte chr in sSubject)
            {
                if (chr != '\0')
                {
                    result += (char)chr;
                }
            }
            return result;
        }
    }

    /// <summary>
    /// Network Configuration Structure
    /// </summary>
    public struct NETDEV_NET_CFG
    {
        public UInt32 dwSize;
        /// <summary>
        /// Device Host Name
        /// </summary>
        //[MarshalAs(UnmanagedType.ByValArray, ArraySubType = UnmanagedType.ByValTStr, SizeConst = 16)]
        //public char[] sDevName;
        [MarshalAs(UnmanagedType.ByValArray,  SizeConst = 16)]
        public byte[] sDevName;
        /// <summary>
        /// Device Host Name String
        /// </summary>
        /// <returns>Device Host Name String</returns>
        public string DevName()
        {
            string result = "";
            foreach (char chr in sDevName)
            {
                if (chr != '\0')
                {
                    result += chr.ToString();
                }
            }
            return result;
        }
        /// <summary>
        /// TCP Max Connections (Generally refers to the video data requests) 
        /// </summary>
        public UInt16 wTcpMaxConnectNum;
        /// <summary>
        /// TCP Listens on Port
        /// </summary>
        public UInt16 wTcpPort;
        /// <summary>
        /// UDP Listens on Port
        /// </summary>
        public UInt16 wUdpPort;
        /// <summary>
        /// HTTP Port
        /// </summary>
        public UInt16 wHttpPort;
        /// <summary>
        /// HTTPS Port 
        /// </summary>
        public UInt16 wHttpsPort;
        /// <summary>
        /// SSL Port
        /// </summary>
        public UInt16 wSslPort;
        /// <summary>
        /// Ethernet Port
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 2)]
        public NET_ETHERNET[] stEtherNet;
        /// <summary>
        /// Alarm Server 
        /// </summary>
        public NET_REMOTE_HOST struAlarmHost;
        /// <summary>
        /// Log Server  
        /// </summary>
        public NET_REMOTE_HOST struLogHost;
        /// <summary>
        /// SMTP Sever
        /// </summary>
        public NET_REMOTE_HOST struSmtpHost;
        /// <summary>
        /// Multicast Group 
        /// </summary>
        public NET_REMOTE_HOST struMultiCast;
        /// <summary>
        /// NFS Sever
        /// </summary>
        public NET_REMOTE_HOST struNfs;
        /// <summary>
        /// PPPoE Sever
        /// </summary>
        public NET_REMOTE_HOST struPppoe;
        /// <summary>
        /// PPPoE Register Return IP
        /// </summary>
        //[MarshalAs(UnmanagedType.ByValArray, ArraySubType = UnmanagedType.ByValTStr, SizeConst = 16)]
        //public char[] sPppoeIP;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 16)]
        public byte[] sPppoeIP;
        /// <summary>
        /// DDNS Sever
        /// </summary>
        public NET_REMOTE_HOST struDdns;
        /// <summary>
        /// DDNS Host Name
        /// </summary>
        //[MarshalAs(UnmanagedType.ByValArray, ArraySubType = UnmanagedType.ByValTStr, SizeConst = 64)]
        //public char[] sDdnsHostName;
        [MarshalAs(UnmanagedType.ByValArray,SizeConst = 64)]
        public byte[] sDdnsHostName;
        /// <summary>
        /// DNS Sever
        /// </summary>
        public NET_REMOTE_HOST struDns;
        /// <summary>
        /// Email Configuration
        /// </summary>
        public NET_MAIL_CFG struMail;
    }

    /// <summary>
    /// Serial Port Basic Attributes
    /// </summary>
    public struct NET_COMM_PROP
    {
        /// <summary>
        /// Data Bit 0:5;1:6;2:7;3-8;
        /// </summary>
        public byte byDataBit;
        /// <summary>
        /// Stop Bit 0:1Bit;1:1.5Bit; 2:2Bit;
        /// </summary>
        public byte byStopBit;
        /// <summary>
        /// Check Bit 0:Not Check;1:Odd; 2:Even;
        /// </summary>
        public byte byParity;
        /// <summary>
        /// Baud rate 0:300;1:600;2:1200;3:2400;4:4800;5:9600;6:19200;7:38400;8:57600;9:115200;
        /// </summary>
        public byte byBaudRate;
    }

    /// <summary>
    /// 485 Decoder Configuration
    /// </summary>
    public struct NET_485_CFG
    {
        public NET_COMM_PROP struComm;
        /// <summary>
        /// Protocol Type Save the Agreement Subscript,Dynamic Change
        /// </summary>
        public UInt16 wProtocol;
        /// <summary>
        /// Address decoder:0 - 255
        /// </summary>
        public UInt16 wDecoderAddress;
    }

    /// <summary>
    /// 232 Serial Port Configuration
    /// </summary>
    public struct NET_RS232_CFG
    {
        public NET_COMM_PROP struComm;
        public byte byFunction;			// Serial Port Function, Corresponding to the Function List of the Serial Port Configuration  

        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 3)]
        public byte[] byReserved;
    }


    /// <summary>
    /// Protocol Name 
    /// </summary>
    public struct NET_PROANDFUN_NAME
    {
        /// <summary>
        /// Protocol Name[Length16]
        /// </summary>
        //[MarshalAs(UnmanagedType.ByValArray, ArraySubType = UnmanagedType.ByValTStr, SizeConst = 16)]
        //public char[] ProName;
        [MarshalAs(UnmanagedType.ByValArray,  SizeConst = 16)]
        public byte[] ProName;
    }


    /// <summary>
    /// Serial Port Configuration Structure
    /// </summary>
    public struct NETDEV_COMM_CFG
    {
        /// <summary>
        /// Decoder Protocol
        /// </summary>
        public UInt32 dwSize;
        /// <summary>
        /// Protocol Number
        /// </summary>
        public UInt32 dwDecProListNum;
        /// <summary>
        /// Protocol List 100
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 100)]
        public NET_PROANDFUN_NAME[] DecProName;
        /// <summary>
        /// The Decoder Current Attributes
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 16)]
        public NET_485_CFG[] stDecoder;
        /// <summary>
        /// 232 Function Number
        /// </summary>
        public UInt32 dw232FuncNameNum;
        /// <summary>
        /// Function List10*16
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, ArraySubType = UnmanagedType.ByValTStr, SizeConst = 10)]
        public NET_PROANDFUN_NAME[] s232FuncName;
        /// <summary>
        /// The 232 Serial Current Attributes
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 2)]
        public NET_RS232_CFG[] st232;
    }

    /// <summary>
    /// Automatic Maintenance Attributes
    /// </summary>
    public struct NETDEV_AUTOMT_CFG
    {
        /// <summary>
        /// Auto Reboot
        /// </summary>
        public UInt32 dwSize;
        /// <summary>
        ///  Auto Reboot Date Setting 0:Never;1:Everyday;2:Sundays;3:Every Mondy;......
        /// </summary>
        public byte byAutoRebootDay;
        /// <summary>
        /// Auto Reboot Time Setting 0:0:00;1:1:00;........23:23:00;
        /// </summary>
        public byte byAutoRebootTime;
        /// <summary>
        /// Auto Delete File 0:Never;1:24H;2:48H;3:72H;4:96H:5:One Week;6:One Month
        /// </summary>
        public byte byAutoDeleteFilesTime;
        /// <summary>
        /// Reserve
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 13)]
        public byte[] reserved;
    }

    /// <summary>
    /// Native Machine Control Strategy Configuration
    /// </summary>
    public struct NET_VIDEOGROUP_CFG
    {
        /// <summary>
        /// Video Output 0:Invalid;1:The Channel Number Representations of Device;Device Channel Number+1 Represent all;
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 6)]
        public byte[] byVideoOut;
        /// <summary>
        /// Tour Interval,Unit is Second, 5-300 
        /// </summary>
        public int iInterval;
        /// <summary>
        /// Whether Enable Tour 
        /// </summary>
        public byte byEnableTour;
        /// <summary>
        /// Linkage Alarm Channel 0:Invalid;1:Alarm Channel Number Represent Corresponding Channel;Alarm Channel Number+1 Represent1-4;Alarm Channel Number+2 Represent 5-8...;Refer to the Local Interface
        /// </summary>
        public byte byAlarmChannel;

        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 2)]
        public byte[] byReserved;
    }

    /// <summary>
    /// Native Matrix Control Strategy Configuration
    /// </summary>
    public struct NETDEV_VIDEO_MATRIX_CFG
    {
        public UInt32 dwSize;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 4)]
        public NET_VIDEOGROUP_CFG[] struVideoGroup;
    }

    /// <summary>
    /// ddns Configuration
    /// </summary>
    public struct NET_DDNS_SERVER_CFG
    {
        /// <summary>
        /// ddns Server id Number
        /// </summary>
        public UInt32 dwId;
        /// <summary>
        /// Enable,At the same time, there can only be a DDNS server in the enabled state
        /// </summary>
        public bool bEnable;
        /// <summary>
        /// Server Type,xiwang
        /// </summary>	
        //[MarshalAs(UnmanagedType.ByValArray, ArraySubType = UnmanagedType.ByValTStr, SizeConst = 32)]
        //public char[] szServerType;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 32)]
        public byte[] szServerType;
        /// <summary>
        /// Server ip
        /// </summary>
        //[MarshalAs(UnmanagedType.ByValArray, ArraySubType = UnmanagedType.ByValTStr, SizeConst = 16)]
        //public char[] szServerIp;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 16)]
        public byte[] szServerIp;
        /// <summary>
        /// Server Port 
        /// </summary>
        public UInt32 dwServerPort;
        /// <summary>
        /// dvr Domain Name Like jecke.3322.org
        /// </summary>
        //[MarshalAs(UnmanagedType.ByValArray, ArraySubType = UnmanagedType.ByValTStr, SizeConst = 256)]
        //public char[] szDomainName;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 256)]
        public byte[] szDomainName;
        /// <summary>
        /// User Name
        /// </summary>
        //[MarshalAs(UnmanagedType.ByValArray, ArraySubType = UnmanagedType.ByValTStr, SizeConst = 32)]
        //public char[] szUserName;
        [MarshalAs(UnmanagedType.ByValArray,  SizeConst = 32)]
        public byte[] szUserName;
        /// <summary>
        /// Password
        /// </summary>
        //[MarshalAs(UnmanagedType.ByValArray, ArraySubType = UnmanagedType.ByValTStr, SizeConst = 32)]
        //public char[] szUserPsw;
        [MarshalAs(UnmanagedType.ByValArray,  SizeConst = 32)]
        public byte[] szUserPsw;
        /// <summary>
        /// Server Alias,Like "ddns"
        /// </summary>
        //[MarshalAs(UnmanagedType.ByValArray, ArraySubType = UnmanagedType.ByValTStr, SizeConst = 32)]
        //public char[] szAlias;
        [MarshalAs(UnmanagedType.ByValArray,  SizeConst = 32)]
        public byte[] szAlias;
    }
    /// <summary>
    /// Multi ddns Configuration
    /// </summary>
    public struct NETDEV_MULTI_DDNS_CFG
    {
        public UInt32 dwSize;
        public UInt32 dwDdnsServerNum;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 10)]
        public NET_DDNS_SERVER_CFG[] struDdnsServer;
    }

    /// <summary>
    /// Snap Function Configuration
    /// </summary>
    public struct NETDEV_SNAP_CFG
    {
        public UInt32 dwSize;
        /// <summary>
        /// Timing Snap Switch（Alarm Snap Switch Reflected in the Configuration of Alarm Linkage）
        /// </summary>
        public byte bTimingEnable;
        public byte bReserved;
        /// <summary>
        /// Timing Snap Intervals,Unit is Second,The largest capture device support time interval for 30 minutes
        /// </summary>
        public ushort PicTimeInterval;
        /// <summary>
        /// Snap Encode Configuration,Now Support the Resolution, Image Quality and Frame Rate Setting,Here said frame is negative,represent Snap number in one second.
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 32)]
        public NET_VIDEOENC_OPT[] struSnapEnc;
    }

    /// <summary>
    /// web Path Configuration
    /// </summary>
    public struct NETDEV_URL_CFG
    {
        public UInt32 dwSize;
        /// <summary>
        /// Whether or Not Snap
        /// </summary>
        public bool bSnapEnable;
        /// <summary>
        /// Snap Interval
        /// </summary>
        public int iSnapInterval;
        /// <summary>
        /// HTTP Host IP
        /// </summary>
        //[MarshalAs(UnmanagedType.ByValArray, ArraySubType = UnmanagedType.ByValTStr, SizeConst = 16)]
        //public char[] szHostIp;
        [MarshalAs(UnmanagedType.ByValArray,SizeConst = 16)]
        public byte[] szHostIp;
        public UInt16 wHostPort;
        /// <summary>
        /// Status Message Sending Interval
        /// </summary>
        public int iMsgInterval;
        /// <summary>
        /// Status Message UploadingURL
        /// </summary>
        //[MarshalAs(UnmanagedType.ByValArray, ArraySubType = UnmanagedType.ByValTStr, SizeConst = 128)]
        //public char[] szUrlState;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 128)]
        public byte[] szUrlState;
        /// <summary>
        /// Image Upload URL
        /// </summary>
        //[MarshalAs(UnmanagedType.ByValArray, ArraySubType = UnmanagedType.ByValTStr, SizeConst = 128)]
        //public char[] szUrlImage;
        [MarshalAs(UnmanagedType.ByValArray,  SizeConst = 128)]
        public byte[] szUrlImage;
        /// <summary>
        /// Mechanized web Index
        /// </summary>
        //[MarshalAs(UnmanagedType.ByValArray, ArraySubType = UnmanagedType.ByValTStr, SizeConst = 48)]
        //public char[] szDevId;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 48)]
        public byte[] szDevId;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 2)]
        public byte[] byReserved;
    }


    /// <summary>
    /// 
    /// </summary>
    public struct struPeriod
    {
        /// <summary>
        /// The period of "enable" is invalid,Negligible
        /// </summary>
        public NET_TSECT struSect;
        /// <summary>
        /// Dynamic Testing Video Upload
        /// </summary>
        public bool bMdEn;
        /// <summary>
        /// Upload the External Alarm Video
        /// </summary>
        public bool bAlarmEn;
        /// <summary>
        /// Upload the Common Timing Video
        /// </summary>	
        public bool bTimerEn;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 4)]
        public UInt32[] dwRev;
    }
    /// <summary>
    /// FTP Uplode Configuration
    /// </summary>
    public struct NET_FTP_UPLOAD_CFG
    {

        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 2)]
        public struPeriod[] Period;
    }

    /// <summary>
    /// FTP Uplode Configuration
    /// </summary>
    public struct NETDEV_FTP_PROTO_CFG
    {
        public UInt32 dwSize;

        /// <summary>
        /// Enable
        /// </summary>
        public bool bEnable;
        /// <summary>
        /// Host IP
        /// </summary>
        //[MarshalAs(UnmanagedType.ByValArray, ArraySubType = UnmanagedType.ByValTStr, SizeConst = 16)]
        //public char[] szHostIp;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 16)]
        public byte[] szHostIp;
        /// <summary>
        /// Host Port
        /// </summary>
        public UInt32 wHostPort;
        /// <summary>
        /// FTP Directory Path
        /// </summary>
        //[MarshalAs(UnmanagedType.ByValArray, ArraySubType = UnmanagedType.ByValTStr, SizeConst = 240)]
        //public char[] szDirName;
        [MarshalAs(UnmanagedType.ByValArray,  SizeConst = 240)]
        public byte[] szDirName;
        /// <summary>
        /// User Name
        /// </summary>
        //[MarshalAs(UnmanagedType.ByValArray, ArraySubType = UnmanagedType.ByValTStr, SizeConst = 64)]
        //public char[] szUserName;
        [MarshalAs(UnmanagedType.ByValArray,SizeConst = 64)]
        public byte[] szUserName;
        /// <summary>
        /// Password
        /// </summary>
        //[MarshalAs(UnmanagedType.ByValArray, ArraySubType = UnmanagedType.ByValTStr, SizeConst = 64)]
        //public char[] szPassword;
        [MarshalAs(UnmanagedType.ByValArray,  SizeConst = 64)]
        public byte[] szPassword;
        /// <summary>
        /// File Length
        /// </summary>
        public int iFileLen;
        /// <summary>
        /// Adjacent File Time Interval
        /// </summary>
        public int iInterval;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 42)]
        public NET_FTP_UPLOAD_CFG[] struUploadCfg;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 130)]
        public byte[] reserved;
    }

    /// <summary>
    /// The Platform Access Configuration － U Net Platform
    /// </summary>
    public struct NET_INTERVIDEO_UCOM_CHN_CFG
    {
        public bool bChnEn;
        //[MarshalAs(UnmanagedType.ByValArray, ArraySubType = UnmanagedType.ByValTStr, SizeConst = 32)]
        //public char[] szChnId;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 32)]
        public byte[] szChnId;
    }

    /// <summary>
    /// The Platform Access Configuration － U Net Platform
    /// </summary>
    public struct NETDEV_INTERVIDEO_UCOM_CFG
    {
        public UInt32 dwSize;
        /// <summary>
        /// Access Function Enabled 0:Enable
        /// </summary>
        public bool bFuncEnable;
        /// <summary>
        /// Heartbeat Enable
        /// </summary>
        public bool bAliveEnable;
        /// <summary>
        /// Heartbeat Cycle,Unit is Second,0-3600
        /// </summary>
        public UInt32 dwAlivePeriod;
        /// <summary>
        /// CMS's IP
        /// </summary>
        //[MarshalAs(UnmanagedType.ByValArray, ArraySubType = UnmanagedType.ByValTStr, SizeConst = 16)]
        //public char[] szServerIp;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 16)]
        public byte[] szServerIp;
        /// <summary>
        /// CMS的Port
        /// </summary>
        public UInt16 wServerPort;
        /// <summary>
        /// Register Password 
        /// </summary>
        //[MarshalAs(UnmanagedType.ByValArray, ArraySubType = UnmanagedType.ByValTStr, SizeConst = 16)]
        //public char[] szRegPwd;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 16)]
        public byte[] szRegPwd;
        /// <summary>
        /// Device id
        /// </summary>
        //[MarshalAs(UnmanagedType.ByValArray, ArraySubType = UnmanagedType.ByValTStr, SizeConst = 32)]
        //public char[] szDeviceId;
        [MarshalAs(UnmanagedType.ByValArray,  SizeConst = 32)]
        public byte[] szDeviceId;
        //[MarshalAs(UnmanagedType.ByValArray, ArraySubType = UnmanagedType.ByValTStr, SizeConst = 32)]
        //public char[] szUserName;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 32)]
        public byte[] szUserName;
        //[MarshalAs(UnmanagedType.ByValArray, ArraySubType = UnmanagedType.ByValTStr, SizeConst = 32)]
        //public char[] szPassWord;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 32)]
        public byte[] szPassWord;
        /// <summary>
        /// Channel id,en
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 16)]
        public NET_INTERVIDEO_UCOM_CHN_CFG[] struChnInfo;
    }


    // IP Information Extension
    public struct NETDEV_IPIFILTER_INFO_EX
    {
        /// <summary>
        /// IP Number
        /// </summary>
	    public UInt32 dwIPNum;
        /// <summary>
        /// IP
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 512*16)]
	    public byte[] SZIP;
        /// <summary>
        /// Reserve
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 32)]
	    public byte[] byReserve; 
    } ;

    // IP Filter Configuration Structure Expansion
    public struct NETDEV_IPIFILTER_CFG_EX
    {
	    public UInt32 dwSize;
        /// <summary>
        /// Enable
        /// </summary>
	    public UInt32 dwEnable;
        /// <summary>
        /// The Current List of Type：0：WhitelList 1：Blacklist （Device Can Only Make a List, or a Whitelist or Blacklist）
        /// </summary>
	    public UInt32 dwType;
        /// <summary>
        /// Blacklist
        /// </summary>
	    public NETDEV_IPIFILTER_INFO_EX BannedIP;
        /// <summary>
        /// Whitelist
        /// </summary>
	    public NETDEV_IPIFILTER_INFO_EX TrustIP;
        /// <summary>
        /// Reserve
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 256)]
	    public byte[] byReserve;
    }


    // MAC,IP Filtering Information
    public struct MACIP_INFO
    {
        /// <summary>
        /// Initialize the Structure Size when Use
        /// </summary>
	    public UInt32	dwSize;
        /// <summary>
        /// MAC
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 40)]
	    public byte[]	szMac;
        /// <summary>
        /// IP
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 16)]
	    public byte[]	szIp;
    }

    // MAC,IP Filtering Configuration Information
    public struct NETDEV_MACIPFILTER_CFG
    {
        /// <summary>
        /// Initialize the Structure Size when Use
        /// </summary>
	    public UInt32   dwSize;
        /// <summary>
        /// Enable
        /// </summary>
	    public UInt32   dwEnable;
        /// <summary>
        /// The Current List of Type：0：WhitelList 1：Blacklist （Device Can Only Make a List, or a Whitelist or Blacklist）
        /// </summary>
	    public UInt32   dwType;
        /// <summary>
        /// Blacklist MAC,IP Number(MAC,IP one-to-one correspondence)
        /// </summary>
	    public UInt32   dwBannedMacIpNum;
        /// <summary>
        /// Blacklist Mac,IP
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 512)]
	    public MACIP_INFO[]  stuBannedMacIp;
        /// <summary>
        /// WhitelList MAC,IP Number(MAC,IP one-to-one correspondence)
        /// </summary>
	    public UInt32   dwTrustMacIpNum;
        /// <summary>
        /// WhitelList Mac,IP
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 512)]
	    public MACIP_INFO[]  stuTrustMacIp;
    } 

    /// <summary>
    /// The Key Information 36 Byte
    /// </summary>
    public struct ENCRYPT_KEY_INFO
    {
        /// <summary>
        /// Whether Encryption0:Not Encryption, 1:Encryption
        /// </summary>
	    public byte         byEncryptEnable;
        /// <summary>
        /// Reserve
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 3)]
	    public byte[]       byReserved;
        /// <summary>
        /// union
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 32)]
        public byte[]       byKey; 
        //public ENCRYPT_TYPE_UNION  stuEncryptTypeUinon;
    }


    /// <summary>
    /// Encryption Algorithm Parameters
    /// </summary>
    public struct ALGO_PARAM_INFO
    {
        /// <summary>
        /// Key Length,The current for AES algorithm type, said the key figures number(Currently support 128,192,256-bit 3 kinds)
        /// Like: wEncryptLenth is 128,Then Key Information ENCRYPT_KEY_INFO's byAesKey[0]~[15])
        /// DES Algorithm Type,Key Length Fixed 64 bit
        /// 3DESAlgorithm Type,Denote Key Number(2 or 3 Keys)
        /// </summary>
	    public UInt16   wEncryptLenth; 
        /// <summary>
        /// Working Mode,Reference Enumerated Type EM_ENCRYPT_ALOG_WORKMODE 
        /// </summary>
	    public byte     byAlgoWorkMode; 
        /// <summary>
        /// Reserve
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 13)]
	    public byte[]   reserved; 
    }

    /// <summary>
    /// Stream Encryption Configuration Information 
    /// </summary>
    public struct NETEDV_STREAM_ENCRYPT
    {
        /// <summary>
        /// Encryption Algorithm Type：00: AES、01:DES、02: 3DES
        /// </summary>
        public byte    byEncrptAlgoType;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 3)]
        public byte[]   byReserved1;
        /// <summary>
        /// Encryption Algorithm Parameters
        /// </summary>
        public ALGO_PARAM_INFO     stuEncrptAlgoparam;
        /// <summary>
        /// Key Information of Each Channel
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 32)]
        public ENCRYPT_KEY_INFO[]    stuEncryptKeys; 
        /// <summary>
        /// Reserve
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 1388)]
        public byte[]       reserved2;
    }

    public enum CONNECT_STATE
    {
        CONNECT_STATE_UNCONNECT = 0,
        CONNECT_STATE_CONNECTING,
        CONNECT_STATE_CONNECTED,
        CONNECT_STATE_ERROR = 255,
    }

    // Virtual Camer State Info
    public struct NET_VIRTUALCAMERA_STATE_INFO
    {
        public int nStructSize;                                 //struct size
        public int nChannelID;                                  //channel ID
        public CONNECT_STATE emConnectState;                    //connect state
        public uint uiPOEPort;                                  // POE Port Number，0 means not POE connect 
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 64)]
        public byte[] szDeviceName;                              // device name
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 128)]
        public byte[] szDeviceType;                              // device type
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 128)]
        public byte[] szSystemType;                              // system type
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 48)]
        public byte[] szSerialNo;                                // serial number
        public int nVideoInput;                                  // video input
        public int nAudioInput;                                  // audio input
        public int nAlarmOutput;                                 // alaram output
    }

    //Recoding State Change Info
    public struct ALARM_RECORDING_CHANGED
    {
        public int nChannel;       //record channel
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 12)]
        public byte[] reserved;   //reserved
    }
    #endregion

    // Alarm information of alarm upload function
    public struct NEW_ALARM_UPLOAD
    {
        public UInt32   dwAlarmType;        //Alarm type,when dwAlarmType = DH_UPLOAD_EVENT,dwAlarmMask and bAlarmDecoderIndex are invalid.
        public UInt32   dwAlarmMask;		// Alarm information subnet mask. Bit represents each alarm status
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 16)]
	    public byte[]	szGlobalIP;			// Client-end IP address 
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 256)]
	    public byte[]	szDomainName;		// Client-end domain name
	    int			    nPort;				// The port client-end connected when upload alarm 
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 40)]
	    public byte[]	szAlarmOccurTime;	// Alarm occurred time 
	    byte			bAlarmDecoderIndex;	// It means which alarm decoder. It is valid when dwAlarmType = DH_UPLOAD_DECODER_ALARM.
	    [MarshalAs(UnmanagedType.ByValArray, SizeConst = 15)]
        public byte[]	bReservedSpace;
    }

    // intelligent alarm center
    public struct ALARM_UPLOAD_IVS_INFO
    {
        public UInt32   dwSize;
        NET_TIME        stuTime;                                // occur time	 
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 256)]
       	public byte[]	szDomainName;                           // client domain name
	    int				nChannelID;                             // channel,from 0
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 260)]
	    public byte[]	szType;                                 // alarm type,check rule
	    int				nState;                                 // alarm state, 0-reset,1-setting,2-pulse
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 128)]
        public byte[]	szRuleName;                             // Rule Name  
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 40)]
        public byte[]	szIPAddress;                            // Device IP Address  
        int             nPort;                                  // Device Port No.
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 40)]
        public byte[]	szMacAddress;                           // Device-end mac address
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 260)]
        public byte[]	szPicFilePath;                          // Picture Storage Path
        int             nPicFileNum;                            // Current alarm folder number
        int             nUploadPicFileNum;                      // Uploaded FTP picture  number
        public UInt32   dwChannelMask;                          // Snapshot video channel mask，15 means this alarm has 1,2,3,4 channels 
    } 

    #region <<Object Detection Module Configuration--Related Structure>>

    /// <summary>
    /// Regional Vertex Information
    /// </summary>
    public struct CFG_POLYGON
    {
        public Int32 nX; //0~8191
        public Int32 nY;
    }

    /// <summary>
    /// Size
    /// </summary>
    [StructLayout(LayoutKind.Explicit, CharSet = CharSet.Auto)]
    public struct CFG_SIZE
    {
        /// <summary>
        /// Wide or Area(In C++ is Denoted By union)
        /// </summary>
        [FieldOffset(0)]
        public float nWidth;
        [FieldOffset(0)]
        public float nArea;
        /// <summary>
        /// Height
        /// </summary>
        [FieldOffset(4)]
        public float nHeight;

    }

    /// <summary>
    /// Regional Information
    /// </summary>
    public struct CFG_REGION
    {
        public Int32 nPointNum;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 20)]
        public CFG_POLYGON[] stuPolygon;
    }

    /// <summary>
    /// Calibration Frame Information
    /// </summary>
    public struct CFG_CALIBRATEBOX_INFO
    {
        /// <summary>
        /// Calibration Center Coordinates(Coordinates are normalized to the point [0,8191] Interval)
        /// </summary>
        public CFG_POLYGON stuCenterPoint;
        /// <summary>
        /// Relative Calibration Box Ratio(Like 1 Denote Calibration Size,0.5 Denote Half Calibration Size)
        /// </summary>
        public float fRatio;
    }

    /// <summary>
    /// Size Filter
    /// </summary>
    public struct CFG_SIZEFILTER_INFO
    {
        /// <summary>
        /// Calibrate Box Number
        /// </summary>
        public Int32 nCalibrateBoxNum;
        /// <summary>
        /// Calibrate Box(Distal and Proximal Calibration Mode is Effective)
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 10)]
        public CFG_CALIBRATEBOX_INFO[] stuCalibrateBoxs;
        /// <summary>
        /// Whether Metering Parameters Are Valid
        /// </summary>
        public byte bMeasureModeEnable;
        /// <summary>
        /// Measure Mode,0-pixel,No Need Distal And Proximal Calibration, 1-Actual Length,Unit：Meter, 2-The pixels after distal and proximal calibration
        /// </summary>
        public byte bMeasureMode;
        /// <summary>
        /// Whether Filter Type Parameters Are Valid
        /// </summary>
        public byte bFilterTypeEnable;
        // ByArea,ByRatio Only Be Compatible,Use Separate ByArea and ByRatio Represent 2012/03/06
        /// <summary>
        /// Filter Type :0:"ByLength",1:"ByArea", 2"ByWidthHeight"
        /// </summary>
        public byte bFilterType;
        /// <summary>
        /// Reserved 
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 2)]
        public byte[] bReserved;
        /// <summary>
        /// Whether Minimal Size Parameters of the Object is valid
        /// </summary>
        public byte bFilterMinSizeEnable;
        /// <summary>
        /// Whether Max Size Parameters of the Object is valid
        /// </summary>
        public byte bFilterMaxSizeEnable;
        /// <summary>
        /// Objects in the smallest size "ByLength" mode represent the size of wide and high,In "ByArea" mode wide represent area,high is invalid(Represent the size of wide and high of calibration box in distal and proximal mode)
        /// </summary>
        public CFG_SIZE stuFilterMinSize;
        /// <summary>
        /// Objects in the Maximum size  "ByLength" mode represent the size of wide and high,In "ByArea" mode wide represent area,high is invalid(Represent the size of wide and high of calibration box in distal and proximal mode)
        /// </summary>
        public CFG_SIZE stuFilterMaxSize;

        public byte abByArea;
        public byte abMinArea;
        public byte abMaxArea;
        public byte abMinAreaSize;
        public byte abMaxAreaSize;
        /// <summary>
        /// Whether or not filter according to the area, Determine whether the ComplexSizeFilter available through capacity
        /// </summary>
        public byte bByArea;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 2)]
        public byte[] bReserved1;
        /// <summary>
        /// Minimal Area
        /// </summary>
        public Int32 nMinArea;
        /// <summary>
        /// Max Area
        /// </summary>
        public Int32 nMaxArea;
        /// <summary>
        /// The minimum area of the rectangular frame size " When Measuring Type" is "pixel", denote the minimum area of the rectangular box wide and high dimensions；When Measuring Type" is "distal and proximal calibration mode",represent minimum width size of calibration box；
        /// </summary>
        public CFG_SIZE stuMinAreaSize;
        /// <summary>
        /// The Max Area of Rectangle Size, Ditto
        /// </summary>
        public CFG_SIZE stuMaxAreaSize;

        public byte abByRatio;
        public byte abMinRatio;
        public byte abMaxRatio;
        public byte abMinRatioSize;
        public byte abMaxRatioSize;
        /// <summary>
        /// Whether or not filter according to the aspect ratio, Determine whether the ComplexSizeFilter available through capacity
        /// </summary>
        public byte bByRatio;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 2)]
        public byte[] bReserved2;
        /// <summary>
        /// The Minimum Width to Height Ratio
        /// </summary>
        public double dMinRatio;
	/// <summary>
        /// The Max Width to Height Ratio
        /// </summary>
        public double dMaxRatio;
        /// <summary>
        /// The rectangular frame size of the minimum aspect ratio,the minimum aspect ratio of the rectangular frame area
        /// </summary>
        public CFG_SIZE stuMinRatioSize;
        /// <summary>
        /// The rectangular frame size of the max aspect ratio,Ditto
        /// </summary>
        public CFG_SIZE stuMaxRatioSize;
        /// <summary>
        /// Area Calibrate Box Number
        /// </summary>
        public Int32 nAreaCalibrateBoxNum;
        /// <summary>
        /// Area Calibrate Box
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 10)]
        public CFG_CALIBRATEBOX_INFO[] stuAreaCalibrateBoxs;
        /// <summary>
        /// Aspect Ratio Calibrate Box Number
        /// </summary>
        public Int32 nRatioCalibrateBoxs;
        /// <summary>
        /// Aspect Ratio Calibrate Box Number
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 10)]
        public CFG_CALIBRATEBOX_INFO[] stuRatioCalibrateBoxs;
        /// <summary>
        /// Whether Length and Width Filter Enable Parameter is Effiective
        /// </summary>
        public byte abBySize;
        /// <summary>
        /// Length and Width Filter Enable
        /// </summary>
        public byte bBySize;
    };

    // Various Objects Specific Filter
    public struct CFG_OBJECT_SIZEFILTER_INFO
    {
        /// <summary>
        /// Object Type
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 32)]
        public byte[] szObjectType;
        /// <summary>
        /// Corresponding Size Filter
        /// </summary>
        public CFG_SIZEFILTER_INFO stSizeFilter;
    };

    /// <summary>
    /// Detection Module Configuration of Different Region Various Types of Objects 
    /// </summary>
    public struct CFG_MODULE_INFO
    {
        // Information
        /// <summary>
        /// Default Object Types,See "Test Object Type List Supported"
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 32)]
        public byte[] szObjectType;
        /// <summary>
        /// Whether Snap for Object Recognition
        /// </summary>
        public byte bSnapShot;
        /// <summary>
        /// Sensitivity,Value 1-10,The smaller the value of the lower sensitivity
        /// </summary>
        public byte bSensitivity;
        /// <summary>
        /// Whether Metering Parameters Are Valid
        /// </summary>
        public byte bMeasureModeEnable;
        /// <summary>
        /// Whether Metering Parameters Are Valid
        /// </summary>
        public byte bMeasureMode;
        /// <summary>
        /// Detect Region Point
        /// </summary>
        public Int32 nDetectRegionPoint;
        /// <summary>
        /// Detect Region
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 20)]
        public CFG_POLYGON[] stuDetectRegion;
        /// <summary>
        /// Track Region Point
        /// </summary>
        public Int32 nTrackRegionPoint;
        /// <summary>
        /// Track Region
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 20)]
        public CFG_POLYGON[] stuTrackRegion;
        /// <summary>
        /// Whether or Not Filter Type Parameters Are Valid
        /// </summary>
        public byte bFilterTypeEnable;
        // ByArea,ByRatio Only Be Compatible,use Seperate ByArea And ByRatio Represent 2012/03/06
        /// <summary>
        /// Filter Type:0:"ByLength",1:"ByArea", 2:"ByWidthHeight", 3:"ByRatio": According to the aspect ratio,The result of the width divided by height will be filter if it is less than or more than a certain value
        /// </summary>
        public byte nFilterType;
        /// <summary>
        /// Whether or Not Background of the Region Type is valid
        /// </summary>
        public byte bBackgroudEnable;
        /// <summary>
        /// Background of the Region Type, 0-Common Type, 1-Specular Type
        /// </summary>
        public byte bBackgroud;
        /// <summary>
        /// Whether Length and Width Filter Enable Parameter is Effiective
        /// </summary>
        public byte abBySize;
        /// <summary>
        /// Length and Width Filter Enable
        /// </summary>
        public byte bBySize;
        /// <summary>
        /// Whether Object Min Size is Valid
        /// </summary>
        public byte bFilterMinSizeEnable;
        /// <summary>
        /// Whether Object Max Size is Valid
        /// </summary>
        public byte bFilterMaxSizeEnable;
        /// <summary>
        /// Object Min Size "ByLength"mode represent the size of wide and high,In "ByArea" mode wide represent area,high is invalid
        /// </summary>
        public CFG_SIZE stuFilterMinSize;
        /// <summary>
        /// Object Max Size "ByLength"Mode Denote the size of wide and high,In "ByArea" mode wide represent area,high is invalid
        /// </summary>
        public CFG_SIZE stuFilterMaxSize;
        /// <summary>
        /// Exclusion Region Number
        /// </summary>
        public Int32 nExcludeRegionNum;
        /// <summary>
        /// Exclusion Region
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 10)]
        public CFG_REGION[] stuExcludeRegion;
        /// <summary>
        /// Calibrate Box Number
        /// </summary>
        public Int32 nCalibrateBoxNum;
        /// <summary>
        /// Calibrate Box(Effective in Distal and Proximal Calibrate Mode )
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 10)]
        public CFG_CALIBRATEBOX_INFO[] stuCalibrateBoxs;
        /// <summary>
        /// Whether or Not Detection Accuracy Effective
        /// </summary>
        public byte bAccuracy;
        /// <summary>
        /// Detection Accuracy
        /// </summary>
        public byte byAccuracy;
        /// <summary>
        /// Whether or not Algorithm Moving Step Effective
        /// </summary>
        public byte bMovingStep;
        /// <summary>
        /// Algorithm Moving Step
        /// </summary>
        public byte byMovingStep;
        /// <summary>
        /// Whether or Not Algorithm Scaling Factor Effective
        /// </summary>
        public byte bScalingFactor;
        /// <summary>
        /// Algorithm Scaling Factor
        /// </summary>
        public byte byScalingFactor;
        /// <summary>
        /// Reserved
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 1)]
        public byte[] bReserved2;
        /// <summary>
        /// Whether or Not Leak Detection And False Detection Balance Parameter Effective
        /// </summary>
        public byte abDetectBalance;
        /// <summary>
        /// Leak Detection And False Detection Balance	0-Compromise Mode(Default)1-Less Leak Detection 2-Less False Detection
        /// </summary>
        public Int32 nDetectBalance;

        public byte abByRatio;
        public byte abMinRatio;
        public byte abMaxRatio;
        public byte abMinAreaSize;
        public byte abMaxAreaSize;
        /// <summary>
        /// Whether or not filter according to the aspect ratio, Determine whether the ComplexSizeFilter available through capacity, can reuse with nFilterType
        /// </summary>
        public byte bByRatio;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 2)]
        public byte[] bReserved1;
        /// <summary>
        /// The Minimum Width to Height Ratio
        /// </summary>
        public double dMinRatio;
        /// <summary>
        /// The Max Width to Height Ratio
        /// </summary>
        public double dMaxRatio;
        /// <summary>
        /// The rectangular frame size of the minimum area       public byte abMinArea;
        /// </summary>
        public CFG_SIZE stuMinAreaSize;
        /// <summary>
        /// The Max Area of Rectangle Size, Ditto
        /// </summary>
        public CFG_SIZE stuMaxAreaSize;

        public byte abByArea;
        public byte abMinArea;
        public byte abMaxArea;
        public byte abMinRatioSize;
        public byte abMaxRatioSize;
        /// <summary>
        /// Whether or not filter according to the area, Determine whether the ComplexSizeFilter available through capacity  can reuse with nFilterType
        /// </summary>
        public byte bByArea;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 2)]
        public byte[] bReserved3;
        /// <summary>
        /// Min Area
        /// </summary>
        public Int32 nMinArea;
        /// <summary>
        /// Max Area
        /// </summary>
        public Int32 nMaxArea;
        /// <summary>
        /// The rectangular frame size of the minimum aspect ratio,the minimum aspect ratio of the rectangular frame area
        /// </summary>
        public CFG_SIZE stuMinRatioSize;
        /// <summary>
        /// The rectangular frame size of the max aspect ratio,Ditto
        /// </summary>
        public CFG_SIZE stuMaxRatioSize;
        /// <summary>
        /// Area Calibrate Box Number
        /// </summary>
        public Int32 nAreaCalibrateBoxNum;
        /// <summary>
        /// AreaCalibrateBoxNum
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 10)]
        public CFG_CALIBRATEBOX_INFO[] stuAreaCalibrateBoxs;
        /// <summary>
        /// Ratio Calibrate Box Number
        /// </summary>
        public int nRatioCalibrateBoxs;
        /// <summary>
        /// Ratio Calibrate Box Number
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 10)]
        public CFG_CALIBRATEBOX_INFO[] stuRatioCalibrateBoxs;
        /// <summary>
        /// If Open the Disturbance module
        /// </summary>
        public byte bAntiDisturbance;
        /// <summary>
        /// If There is a Backlight
        /// </summary>
        public byte bBacklight;
        /// <summary>
        /// If There is a Shadow
        /// </summary>
        public byte bShadow;
        /// <summary>
        /// PTZ Preset Points ,0~255,0 Denote Fixed Scene,Ignore Preset Points。>0 denote Modules are effective in the preset point
        /// </summary>
        public int nPtzPresetId;
        /// <summary>
        /// The Number of Specific Filters of Objects
        /// </summary>
        public int nObjectFilterNum;
        /// <summary>
        /// A Specific Filter Information of Object
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 16)]
        public CFG_OBJECT_SIZEFILTER_INFO[] stObjectFilter;
    }

    public struct CFG_ANALYSEMODULES_INFO
    {
        /// <summary>
        /// Detection Mode Number
        /// </summary>
        public Int32 nMoudlesNum;
        /// <summary>
        /// Each video input channel corresponding to the various types of object detection module configuration
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 16)]
        public CFG_MODULE_INFO[] stuModuleInfo;

    }


    #endregion

    #region <<Global Configuration Video Analysis--Related structure>>

    /// <summary>
    /// Broken Line Endpoint Information
    /// </summary>
    public struct CFG_POLYLINE
    {
        /// <summary>
        /// 0~8191
        /// </summary>
        public Int32 nX;
        public Int32 nY;
    }

    /// <summary>
    /// Lane Information
    /// </summary>
    public struct CFG_LANE
    {
        /// <summary>
        /// Lane ID
        /// </summary>
        public Int32 nLaneId;
        /// <summary>
        /// Lane Direction(The direction of the car drive to),0-North 1-northeast 2-East 3-southeast 4-south 5-southwest 6-west 7-northwest
        /// </summary>
        public Int32 nDirection;
        /// <summary>
        /// Left Lane Line,Lane line represent lane direction, along the left of the lane are called left lane line
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 20)]
        public CFG_POLYLINE[] stuLeftLine;
        /// <summary>
        /// Left Lane Line Vertex Number
        /// </summary>
        public Int32 nLeftLineNum;
        /// <summary>
        /// Right Lane Line,Lane line represent lane direction, along the right of the lane are called right lane line
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 20)]
        public CFG_POLYLINE[] stuRightLine;
        /// <summary>
        /// Right Lane Line Vertex Number
        /// </summary>
        public Int32 nRightLineNum;
        /// <summary>
        /// Left Lane Line Type,1-Denote Write Full Line,2- Write Imaginary Line,3- Yellow Line
        /// </summary>
        public Int32 nLeftLineType;
        /// <summary>
        /// Right Lane Line Type,1-Denote Write Full Line,2- Write Imaginary Line,3- Yellow Line
        /// </summary>
        public Int32 nRightLineType;
        /// <summary>
        /// Lane Drive Direction Enable c++ Type BOOL
        /// </summary>
        public Int32 bDriveDirectionEnable;
        /// <summary>
        /// Drive Direction Number of The Lane 
        /// </summary>
        public Int32 nDriveDirectionNum;
        /// <summary>
        /// Drive Direction of The Lane,"Straight" Straight,"TurnLeft" TurnLeft,"TurnRight" TurnRight,"U-Turn":U-Turn
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 8 * 32)]
        public byte[] szDriveDirection;
        /// <summary>
        /// Stop Line Vertex Number Corresponding to the Lane
        /// </summary>
        public Int32 nStopLineNum;
        /// <summary>
        /// Stop Line Corresponding to the Lane
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 20)]
        public CFG_POLYLINE[] stuStopLine;
        /// <summary>
        /// Traffic Light Group Corresponding to the Lane
        /// </summary>
        public Int32 nTrafficLightNumber;
    };

    // Traffic Light Attribute
    public struct CFG_LIGHTATTRIBUTE
    {
        /// <summary>
        /// The validity of the current traffic lights, has nothing to do with the traffic transportation needs to set up invalid
        /// c++ Type BOOL
        /// </summary>
        public Int32 bEnable;
        public int nTypeNum;
        /// <summary>
        /// The Current Traffic Lights Show Content（Include:Red,Yellow,Green,Countdown）,such as a traffic light can display red, yellow, green three colors, the other traffic lights show only the countdown
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 8 * 32)]
        public byte[] szLightType;
        public int nDirectionNum;
        /// <summary>
        /// Traffic Lights Indicate the Direction,"Straight": Straight,"TurnLeft":TurnLeft,"TurnRight":TurnRight,"U-Turn": U-Turn
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 8 * 32)]
        public byte[] szDirection;
        /// <summary>
        /// Yellow Light On Time
        /// </summary>
        public int nYellowTime;
    }

    /// <summary>
    /// Region Information
    /// </summary>
    public struct CFG_RECT
    {
        public int nLeft;
        public int nTop;
        public int nRight;
        public int nBottom;
    }

    /// <summary>
    /// Traffic Light Group Configuration Information  
    /// </summary>
    public struct CFG_LIGHTGROUPS
    {
        /// <summary>
        /// Light Group ID
        /// </summary>
        public int nLightGroupId;
        /// <summary>
        /// Light Group Coordinates
        /// </summary>
        public CFG_RECT stuLightLocation;
        /// <summary>
        /// Light Group Direction,1- Light Group Horizontal Direction,2- Light Group Vertical Direction
        /// </summary>
        public int nDirection;
        /// <summary>
        /// Whether if external traffic light signals, when it is external traffic lights, signal judgment based on the outside world. The signal notice when every time they jump
        /// c++ Type is BOOL
        /// </summary>
        public Int32 bExternalDetection;
        /// <summary>
        /// Whether to support adaptive light group swing detection, under the scenarios of the wind or easy motion, location will be floating deviation. If test by the algorithm itself, this will increase more testing time
        /// c++ Type BOOL
        /// </summary>
        public Int32 bSwingDetection;
        /// <summary>
        /// Traffic Light Number in the Light Group
        /// </summary>
        public int nLightNum;
        /// <summary>
        /// Each Traffic Light Atrributes In the Light Group
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 8)]
        public CFG_LIGHTATTRIBUTE[] stuLightAtrributes;

    }

    public struct CFG_STAFF
    {
        /// <summary>
        /// Start Location
        /// </summary>
        public CFG_POLYLINE stuStartLocation;
        /// <summary>
        /// End Location
        /// </summary>
        public CFG_POLYLINE stuEndLocation;
        /// <summary>
        /// Actual Length,Unit Meter
        /// </summary>
        public float nLenth;
        /// <summary>
        /// Staff Type
        /// </summary>
        public EM_STAFF_TYPE emType;
    }

    /// <summary>
    /// Calibration Area,Common Scenario Uses
    /// </summary>
    public struct CFG_CALIBRATEAREA_INFO
    {
        /// <summary>
        /// Horizontal Ruler Line vertex Number
        /// </summary>
        public int nLinePoint;
        /// <summary>
        /// Horizontal Ruler Line
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 20)]
        public CFG_POLYGON[] stuLine;
        /// <summary>
        /// Actual Length
        /// </summary>
        public float fLenth;
        /// <summary>
        /// Region
        /// </summary>
        public CFG_REGION stuArea;
        /// <summary>
        /// Verticale Liniaal Number
        /// </summary>
        public int nStaffNum;
        /// <summary>
        /// Verticale Liniaal 
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 20)]
        public CFG_STAFF[] stuStaffs;
        /// <summary>
        /// Region Type
        /// </summary>
        public EM_CALIBRATEAREA_TYPE emType;
    }

    /// <summary>
    /// Face Detection Scenario
    /// </summary>
    public struct CFG_FACERECOGNITION_SCENCE_INFO
    {
        /// <summary>
        /// Camera Height Unit: Meter
        /// </summary>
        public double dbCameraHeight;
        /// <summary>
        /// Horizontal Distance From Camera to the Center of A Ground Test Area Unit: Meter
        /// </summary>
        public double dbCameraDistance;
        /// <summary>
        /// Main Direction of Flow Vertex Number
        /// </summary>
        public int nMainDirection;
        /// <summary>
        /// Main Direction of Flow,the first point is the starting point,the second point is the end point
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 20)]
        public CFG_POLYGON[] stuMainDirection;
        /// <summary>
        /// Unit is Degree,-45~45,negative denote face to the picture above,positive denote face to the picture below,0 denote face perpendicular to the direction opposite the camera
        /// </summary>
        public byte byFaceAngleDown;
        /// <summary>
        /// Unit is Degree,-45~45,negative denote face to the picture above,positive denote face to the picture below,0 denote face perpendicular to the direction opposite the camera
        /// </summary>
        public byte byFaceAngleUp;
        /// <summary>
        /// Unit is Degree,-45~45,negative denote face to the picture above,positive denote face to the picture below,0 denote face perpendicular to the direction opposite the camera
        /// </summary>
        public byte byFaceAngleLeft;
        /// <summary>
        /// Unit is Degree,-45~45,negative denote face to the picture above,positive denote face to the picture below,0 denote face perpendicular to the direction opposite the camera
        /// </summary>
        public byte byFaceAngleRight;
    }
    #endregion

    #region <<Three configuration in intelligent transportation：Scene、Module、traffic rules Configuration>>

    /// <summary>
    /// Video Analysis Global Configuration 
    /// </summary>
    //[StructLayout(LayoutKind.Sequential, public byte[]Set=public byte[]Set.Unicode)]
    //[StructLayout(LayoutKind.Sequential, public byte[]Set = public byte[]Set.Ansi)]
    public struct CFG_ANALYSEGLOBAL_INFO
    {
        /// <summary>
        /// Information
        /// Application Scenarios,See "Support the scene list" public byte[]
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 32)]
        public byte[] szSceneType;

        /// <summary>
        /// Traffic Scene Information
        /// Camera Height Unit：Meter
        /// </summary>
        public double CameraHeight;
        /// <summary>
        /// Horizontal Distance From Camera to the Center of A Ground Test Area Unit: Meter
        /// </summary>
        public double CameraDistance;
        /// <summary>
        /// Near Detection Point
        /// </summary>
        public CFG_POLYGON stuNearDetectPoint;
        /// <summary>
        /// Farther Detection Point
        /// </summary>
        public CFG_POLYGON stuFarDectectPoint;
        /// <summary>
        /// NearDetectPoint,conversion to the actual scene, the horizontal distance from camera vertical line
        /// </summary>
        int nNearDistance;
        /// <summary>
        /// FarDectectPoint,conversion to the actual scene, the horizontal distance from camera vertical line
        /// </summary>
        int nFarDistance;
        /// <summary>
        /// Traffic Scene Subtypes,"Gate",Bayonet Type,"Junction" Intersection Type public byte[]
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 32)]
        public byte[] szSubType;
        /// <summary>
        /// Lane Number
        /// </summary>
        public int nLaneNum;
        /// <summary>
        /// Lane Information
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 8)]
        public CFG_LANE[] stuLanes;
        /// <summary>
        /// Plate Characters Hint Number
        /// </summary>
        public int nPlateHintNum;
        /// <summary>
        /// Plate Characters Hint Array,In the picture you poor quality license plate recognition is uncertain, according to the characters in the array matching, array subscript is smaller, matching The higher the first gradepublic byte[]
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 8 * 32)]
        public byte[] szPlateHints;

        /// <summary>
        /// Light Group Number
        /// </summary>
        public int nLightGroupNum;
        /// <summary>
        /// Light Group Configuration Information
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 8)]
        public CFG_LIGHTGROUPS[] stLightGroups;

        // General Scene Information 
        /// <summary>
        /// Staff Number
        /// </summary>
        public int nStaffNum;
        /// <summary>
        /// Staff
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 20)]
        public CFG_STAFF[] stuStaffs;
        /// <summary>
        /// Calibrate Area Number
        /// </summary>
        public int nCalibrateAreaNum;
        /// <summary>
        /// Calibrate Area(If the field does not exist, the calibration area for the whole scene)
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 10)]
        public CFG_CALIBRATEAREA_INFO[] stuCalibrateArea;
        /// <summary>
        /// Whether Face Recognition Scene is Valid
        /// C++ Type is BOOL
        /// </summary>
        public Int32 bFaceRecognition;
        /// <summary>
        /// Face Recognition Scene
        /// </summary>
        public CFG_FACERECOGNITION_SCENCE_INFO stuFaceRecognitionScene;

        public byte abJitter;
        public byte abDejitter;
        /// <summary>
        /// Reserved 
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 2)]
        public byte[] bReserved;
        /// <summary>
        /// Camera Jitter Rate: Camera Jitter Rate,Value0-100,The reaction degree of static camera dithering,The more powerful jitter, the bigger the value.
        /// </summary>
        public Int32 nJitter;
        /// <summary>
        /// If Open Jitter Module Not Implemented At Moment,C++ Type is BOOL
        /// </summary>
        public Int32 bDejitter;
    }

    public struct CFG_RULE_INFO
    {
        /// <summary>
        /// Event Type,See dhnetsdk.h's"Intelligent Analysis Event Type"
        /// </summary>
	    public UInt32 dwRuleType;
        /// <summary>
        /// The Event Type Rule Configuration Structure Size
        /// </summary>
	    public Int32 nRuleSize;
    	
    } 

    /// <summary>
    /// Each video input channels corresponding rules of all events：Buffer pRuleBuf Fill more than one event information rules
    /// Information Content For Each Event Rules CFG_RULE_INFO+"Event Types Corresponding Rule Configuration Structure"。
    /// </summary>
    public struct CFG_ANALYSERULES_INFO
    {
        /// <summary>
        /// Number of Event Rules
        /// </summary>
        public Int32 nRuleCount;
        /// <summary>
        /// Each video input channels corresponding video analysis rule configuration event buffer
        /// C++ Format is char*
        /// </summary>
        public IntPtr pRuleBuf;
        /// <summary>
        /// Buffer Size 
        /// </summary>
        public Int32 nRuleLen;

    }

    /// <summary>
    /// Video Analysis Ability
    /// </summary>
    public struct CFG_CAP_ANALYSE_INFO
    {
        /// <summary>
        /// Scene List Supported
        /// </summary>
        public Int32 nSupportedSceneNum;
        /// <summary>
        /// Scene List Supported public byte[]
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 32 * 32)]
        public byte[] szSceneName;
        /// <summary>
        /// Max Analysis Moudle Number Each Channel Supported
        /// </summary>
        public Int32 nMaxMoudles;
        /// <summary>
        /// Test Object Type Number Supported
        /// </summary>
        public Int32 nSupportedObjectTypeNum;
        /// <summary>
        /// Test Object Type List Supported public byte[]
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 16 * 32)]
        public byte[] szObjectTypeName;
        /// <summary>
        /// Max Rules Each Channel Supported
        /// </summary>
        public Int32 nMaxRules;
        /// <summary>
        /// Number of Event Type Rules Supported
        /// </summary>
        public Int32 nSupportedRulesNum;
        /// <summary>
        /// List of Event Types Rules Supported,Event Type,See dhnetsdk.h's"Intelligent Analysis Event Type"
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 128)]
        public UInt32[] dwRulesType;
        /// <summary>
        /// Largest Scale Number Supported
        /// </summary>
        public Int32 nMaxStaffs;
        /// <summary>
        /// Max Vertex Point of Fold Line
        /// </summary>
        public Int32 nMaxPointOfLine;
        /// <summary>
        /// Max Vertex Point of Region 
        /// </summary>
        public Int32 nMaxPointOfRegion;
        /// <summary>
        /// The Largest Internal Number of Options
        /// </summary>
        public Int32 nMaxInternalOptions;
        /// <summary>
        /// Wheteher or Not Support Complex Size Filter	Complex size filter using separate area of width to height ratio and filter parameters.      
        /// </summary>
        public byte bComplexSizeFilter;
        /// <summary>
        /// Whether or Not Support Specified object Filter
        /// </summary>
        public byte bSpecifiedObjectFilter;
        /// <summary>
        /// The Maximum Exclusion Area Number In Support Module
        /// </summary>
        public Int32 nMaxExcludeRegionNum;
        /// <summary>
        /// Support the Biggest Calibration Module Box Number
        /// </summary>
        public Int32 nMaxCalibrateBoxNum;
        /// <summary>
        /// The Number of Calibration Frame in the Module At Least Need to Set Up
        /// </summary>
        public Int32 nMinCalibrateBoxNum;
    }
    #endregion

    #region <<Event Type EVENT_IVS_TRAFFICGATE(Traffic Monitoring Event)The Corresponding Data Block Description Information>>

    public struct NET_TIME_EX
    {
        /// <summary>
        /// Year
        /// </summary>
        public UInt32 dwYear;
        /// <summary>
        /// Month
        /// </summary>
        public UInt32 dwMonth;
        /// <summary>
        /// Day
        /// </summary>
        public UInt32 dwDay;
        /// <summary>
        /// Hour
        /// </summary>
        public UInt32 dwHour;
        /// <summary>
        /// Minute
        /// </summary>
        public UInt32 dwMinute;
        /// <summary>
        /// Second
        /// </summary>
        public UInt32 dwSecond;
        /// <summary>
        /// Reserved 
        /// </summary>
        public UInt32 dwMillisecond;
        /// <summary>
        /// Reserved 
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 2)]
        public UInt32[] dwReserved;
    }

    /// <summary>
    /// Two-Dimensional Spatial Point
    /// </summary>
    public struct NET_POINT
    {
        public short nx;
        public short ny;
    }


    /// <summary>
    /// Object File Information
    /// </summary>
    public struct NET_PIC_INFO
    {
        /// <summary>
        /// Offset in the File in Binary Data Block, Unit:Byte
        /// </summary>
        public UInt32 dwOffSet;
        /// <summary>
        /// File Size, Unit:Byte
        /// </summary>
        public UInt32 dwFileLenth;
        /// <summary>
        /// Picture Wide, Unit:Pixel
        /// </summary>
        public UInt16 wWidth;
        /// <summary>
        /// Picture Height, Unit:Pixel 
        /// </summary>
        public UInt16 wHeight;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 16)]
        public byte[] bReserved;
    };



    /// <summary>
    /// Video Analysis Object Information Structure
    /// </summary>
    public struct NET_MSG_OBJECT
    {
        /// <summary>
        /// Object ID,Each ID Denote Unique Object
        /// </summary>
        public Int32 nObjectID;
        /// <summary>
        /// Object Type
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 128)]
        public byte[] szObjectType;
        /// <summary>
        /// Confidence Coefficient(0~255),The higher the value is expressed confidence
        /// </summary>
        public Int32 nConfidence;
        /// <summary>
        /// Object Action:1:Appear 2:Move 3:Stay 4:Remove 5:Disappear 6:Split 7:Merge 8:Rename
        /// </summary>
        public Int32 nAction;
        /// <summary>
        /// Bounding Box
        /// </summary>
        public NET_RECT BoundingBox;
        /// <summary>
        /// Object Point Center
        /// </summary>
        public NET_POINT Center;
        /// <summary>
        /// Polygon Vertex Number
        /// </summary>
        public Int32 nPolygonNum;
        /// <summary>
        /// More Precise Outline Polygon
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 16)]
        public NET_POINT[] Contour;
        /// <summary>
        /// Object Main Color；Bitwise Representation,Red, Green, Blue and Transparency Respectively,Like:RGB Value is (0,255,0),Transparency is 0, the Value is 0x00ff0000.
        /// </summary>
        public UInt32 rgbaMainColor;
        /// <summary>
        /// Text Object Associated With Zero Terminator,Like Plate,container Number and so on public byte[]
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 128)]
        public byte[] szText;
        /// <summary>
        /// Object Subcategory,According to different types of object, can take the following types：
        /// Vehicle Category:"Unknown"  Unknown,"Motor" Motor,"Non-Motor":Non-Motor,"Bus": Bus,"Bicycle" Bicycle,"Motorcycle":Motorcycle
        /// Plate Category："Unknown" Unknown,"Normal" Blue and Black Plate,"Yellow" Yellow Plate,"DoubleYellow" DoubleYellow Plate,"Police" Police Plate "Armed" Armed Plate,
        /// "Military" Military Plate,"DoubleMilitary" DoubleMilitary,"SAR" SAR Plate,"Trainning" Trainning Plate
        /// "Personal" Personality Plate,"Agri" Agricultural brand,"Embassy" Embassy Plate,"Moto" Motorcycle Plate,"Tractor" Tractor Plate,"Other" Other Plate
        /// HumanFace Category:"Normal" Ordinary Face,"HideEye" Eye Mask,"HideNose" Nose Mask,"HideMouth" Mouth Mask
        /// public byte[]
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 64)]
        public byte[] szObjectSubType;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 3)]
        public byte[] byReserved1;
        /// <summary>
        /// Whether or Not Have Object Image File Infromation
        /// </summary>
        public byte bPicEnble;
        /// <summary>
        /// Object Image Information
        /// </summary>
        public NET_PIC_INFO stPicInfo;
        /// <summary>
        /// Whether or not Identify Results of Capture
        /// </summary>
        public byte bShotFrame;
        /// <summary>
        /// Object Color(rgbaMainColor)Whether or Not Available
        /// </summary>
        public byte bColor;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 222)]
        public byte[] byReserved;
    }

    /// <summary>
    /// Event Corresponding File Information
    /// </summary>
    public struct NET_EVENT_FILE_INFO
    {
        /// <summary>
        /// The Current File's Total Number of Files in The Group
        /// </summary>
        public byte bCount;
        /// <summary>
        /// Current File Index in a File Group
        /// </summary>
        public byte bIndex;
        /// <summary>
        /// File Tabs,Details See Enum Type EM_EVENT_FILETAG
        /// </summary>
        public byte bFileTag;
        /// <summary>
        /// File Type,0-Normal 1-Compound 2-Cutout
        /// </summary>
        public byte bFileType;
        /// <summary>
        /// File Time
        /// </summary>
        public NET_TIME_EX stuFileTime;
        /// <summary>
        /// Unique Identifier of the Same Group Capture File
        /// </summary>
        public int nGroupId;
    }

    /// <summary>
    /// Image Resolution
    /// </summary>
    public struct NET_RESOLUTION_INFO
    {
        /// <summary>
        /// Wide
        /// C++ Type is unsigned short
        /// </summary>
        public UInt16 snWidth;
        /// <summary>
        /// High
        /// C++ Type is unsigned short
        /// </summary>
        public UInt16 snHight;
    }

    /// <summary>
    /// Car Inspection Device Redundant Information
    /// </summary>
    public struct NET_SIG_CARWAY_INFO_EX
    {
        /// <summary>
        /// Produced By the Car Inspection Device Capture Redundant Information
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 8)]
        public byte[] byRedundance;
        /// <summary>
        /// Reserved 
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 120)]
        public byte[] bReserved;
    }


    public struct DEV_EVENT_TRAFFICGATE_INFO
    {
        /// <summary>
        /// Channel Number
        /// </summary>
        public Int32 nChannelID;
        /// <summary>
        /// Event Name public byte[]
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 128)]
        public byte[] szName;
        /// <summary>
        /// Timestamp(Unit is a millisecond)
        /// </summary>
        public double PTS;
        /// <summary>
        /// Time of Events
        /// </summary>
        public NET_TIME_EX UTC;
        /// <summary>
        /// Event ID
        /// </summary>
        public int nEventID;
        /// <summary>
        /// Detected Object
        /// </summary>
        public NET_MSG_OBJECT stuObject;
        /// <summary>
        /// Corresponding Lanes
        /// </summary>
        public Int32 nLane;
        /// <summary>
        /// Actual Vehicle Speed Km/h
        /// </summary>
        public Int32 nSpeed;
        /// <summary>
        /// Speed Upper Limit Unit：km/h
        /// </summary>
        public Int32 nSpeedUpperLimit;
        /// <summary>
        /// Speed Lower Limit Unit：km/h 
        /// </summary>
        public Int32 nSpeedLowerLimit;
        /// <summary>
        /// Violation Rule Mask,First:Retrograde; 
        /// Second:Line Pressing on; Third:Over speed; 
        /// Fourth：Under Speed; Fifth:Run the Red Light;Sixth:Through the Intersection(Mount Events)
        /// Seventh: Press the Yellow Line; Eighth: Car Presence; Ninth: Yellow Roadway taking-up;Otherwise the default value is:Transportation bayonet event
        /// </summary>
        public UInt32 dwBreakingRule;
        /// <summary>
        /// Event File Information  
        /// </summary>
        public NET_EVENT_FILE_INFO stuFileInfo;
        /// <summary>
        /// Car Body Message
        /// </summary>
        public NET_MSG_OBJECT stuVehicle;
        /// <summary>
        /// Manually Captured Serial Number
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 64)]
        public byte[] szManualSnapNo;
        /// <summary>
        /// Denote Capture Sequence,Like 3,2,1,1 Denote Capture Termination,0 Denote Abnormal Termination
        /// </summary>
        public int nSequence;
        /// <summary>
        /// Event Action,0 Denote Pulse Event,1 Denote Durable Events Start,2 Denote Durable Events Stop; 
        /// </summary>
        public byte bEventAction;
        /// <summary>
        /// Reserved Byte
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 3)]
        public byte[] byReserved;
        /// <summary>
        /// Capture Identify Produced By Device
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 16)]
        public byte[] szSnapFlag;
        /// <summary>
        /// Snap Mode,0-Unclassified 1-Panorama 2-Close Shot 4-Synthetic Capture 8-Reverse Capture 16-Plate Image
        /// </summary>
        public byte bySnapMode;
        /// <summary>
        /// Over Speed Percentage
        /// </summary>
        public byte byOverSpeedPercentage;
        /// <summary>
        /// Under Speed Percentage
        /// </summary>
        public byte byUnderSpeedingPercentage;
        /// <summary>
        /// Red Light Allowed Time Interval,Unit：Second
        /// </summary>
        public byte byRedLightMargin;
        /// <summary>
        /// Drive Direction,0-Up(The vehicle is getting closer and closer to equipment deployment point),1-Down(The vehicle is getting far away to equipment deployment point)
        /// </summary>
        public byte byDriveDirection;
        /// <summary>
        /// Road Number public byte[]
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 32)]
        public byte[] szRoadwayNo;
        /// <summary>
        /// Violation Code public byte[]
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 16)]
        public byte[] szViolationCode;
        /// <summary>
        /// Violation Description public byte[]
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 128)]
        public byte[] szViolationDesc;
        /// <summary>
        /// Corresponding to the Image Resolution
        /// </summary>
        public NET_RESOLUTION_INFO stuResolution;
        /// <summary>
        /// Vehicle Size Type,"Motor" Motorcycle "Light-duty" Light-Duty Car "Medium" Medium Car "Oversize" Oversize Car "Huge" Huge Car "Other" Other Type
        /// public byte[]
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 32)]
        public byte[] szVehicleType;
        /// <summary>
        /// Vehicle Length, Unit is Meter
        /// </summary>
        public byte byVehicleLenth;
        /// <summary>
        /// Retain Bytes For Extension
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 3)]
        public byte[] byReserved1;
        /// <summary>
        /// Over Speed Margin	Unit：km/h 
        /// </summary>
        public Int32 nOverSpeedMargin;
        /// <summary>
        /// Under Speed Margin	Unit：km/h 
        /// </summary>
        public Int32 nUnderSpeedMargin;
        /// <summary>
        /// "DrivingDirection" : ["Approach", "Shanghai", "Hangzhou"], Driving Direction
        /// "Approach"-Up,The vehicle is getting closer and closer to equipment deployment point；"Leave"-Down,
        /// The vehicle is getting far away to equipment deployment point,The second and the third parameter represent the two sites of up and down respectively 
        /// UTF-8 Encode
        /// public byte[]
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 3 * 256)]
        public byte[] szDrivingDirection;
        /// <summary>
        /// Local or Remote Device Name
        /// public byte[]
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 256)]
        public byte[] szMachineName;
        /// <summary>
        /// Machine Deployment Location、Road Coding
        /// public byte[]
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 256)]
        public byte[] szMachineAddress;
        /// <summary>
        /// Machine Group, Device Subordinate Units
        /// public byte[]
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 256)]
        public byte[] szMachineGroup;
        /// <summary>
        /// Capture Logo(Bitwise),See NET_RESERVED_COMMON	
        /// </summary>
        public UInt32 dwSnapFlagMask;
        /// <summary>
        /// Produced By the Car Inspection Device Capture Signal Redundant Information
        /// </summary>
        public NET_SIG_CARWAY_INFO_EX stuSigInfo;
        /// <summary>
        /// Retain Bytes For Extension
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 3964)]
        public byte[] bReserved;
    }

    // Corresponding to CLIENT_StartSearchDevices Interface
    public struct DEVICE_NET_INFO_EX
    {
        /// <summary>
        /// 4 for IPV4, 6 for IPV6
        /// </summary>
	    public Int32    iIPVersion;
        /// <summary>
        /// IP IPV4 Like "192.168.0.1" IPV6 Like "2008::1/64"
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 64)]
	    public byte[] szIP;
        /// <summary>
        /// tcp Port
        /// </summary>
	    public Int32    nPort;
        /// <summary>
        /// Subnet Mask IPV6 Have No Subnet Mask 
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 64)]
	    public byte[] szSubmask;
        /// <summary>
        /// Gateway 
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 64)]
	    public byte[] szGateway;
        /// <summary>
        /// MAC Address
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 40)]
	    public byte[] szMac;
        /// <summary>
        /// Device Type
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 32)]
	    public byte[] szDeviceType;
        /// <summary>
        /// Target Device Manufacturer ,Specific Reference EM_IPC_TYPE Class	
        /// </summary>
	    public byte byManuFactory;
        /// <summary>
        /// 1-Standard Definition  2-High Definition 
        /// </summary>
	    public byte byDefinition;
        /// <summary>
        /// Prototype is Bool,One Byte
        /// Dhcp Enable State, true-Open, false-Close
        /// </summary>
	    public byte bDhcpEn;
        /// <summary>
        /// Byte Alignment 
        /// </summary>
	    public byte byReserved1;
        /// <summary>
        /// Verify Data Search By Asynchronous Callback(Need to Use the Information to Verify in Modified Device IP)
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 88)]
	    public byte[] verifyData;
        /// <summary>
        /// Serial Number
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 48)]
	    public byte[] szSerialNo;
        /// <summary>
        /// Device Software Version Number
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 128)]
	    public byte[] szDevSoftVersion;
        /// <summary>
        /// Device Type
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 32)]
        public byte[] szDetailType;
        /// <summary>
        /// OEM Client Type
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 128)]
	    public byte[] szVendor;
        /// <summary>
        /// Device Name
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 64)]
	    public byte[] szDevName;
        /// <summary>
        /// Login Device User Name（Need to Fill in Modified Device IP）
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 16)]
	    public byte[] szUserName;
        /// <summary>
        /// Login Device Password（Need to Fill in Modified Device IP）
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 16)]
	    public byte[] szPassWord;
        /// <summary>
        /// HTTP Service Port Number
        /// </summary>
	    public short    nHttpPort;
        /// <summary>
        /// Reserve
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 254)]
	    public byte[] cReserved;
    }

    #endregion

    #region structures--Intelligent Analysis Event Type

    /// <summary>
    /// Event Type EVENT_IVS_CROSSLINEDETECTION(Warning Line Event)The Corresponding Data Block Description Information
    /// </summary>
    public struct DEV_EVENT_CROSSLINE_INFO 
    {
        /// <summary>
        /// Channel Number
        /// </summary>
	    public Int32 nChannelID;
        /// <summary>
        /// Event Name
        /// public byte[]
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 128)]
	    public byte[] szName;
        /// <summary>
        /// Timestamp(Unit is a millisecond)
        /// </summary>
	    public double PTS;
        /// <summary>
        /// Time of Events
        /// </summary>
	    public NET_TIME_EX UTC;
        /// <summary>
        /// Event ID
        /// </summary>
	    public int nEventID;
        /// <summary>
        /// Detected Object
        /// </summary>
	    public NET_MSG_OBJECT stuObject;
        /// <summary>
        /// Event File Information
        /// </summary>
	    public NET_EVENT_FILE_INFO  stuFileInfo;
        /// <summary>
        /// Regular Detection Line
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 20)]
	    public NET_POINT[] DetectLine;
        /// <summary>
        /// Regular Detection Line Vertex Number
        /// </summary>
	    public int nDetectLineNum;
        /// <summary>
        /// Object Motion Track
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 20)]
	    public NET_POINT[] TrackLine;
        /// <summary>
        /// Object Motion Track Vertex Number
        /// </summary>
	    public int nTrackLineNum;
        /// <summary>
        /// Event Action,0 Denote Pulse Event,1 Denote Durable Events Start,2 Denote Durable Events Stop;
        /// </summary>
	    public Byte bEventAction;
        /// <summary>
        /// Denote Invade Direction, 0-From Left to Right, 1-From Right to Left
        /// </summary>
	    public Byte bDirection;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 2)]
	    public Byte[] byReserved;
        /// <summary>
        /// Capture Logo(Bitwise),See NET_RESERVED_COMMON
        /// </summary>
	    public UInt32 dwSnapFlagMask;
        /// <summary>
        /// Retain Bytes For Extension
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 876)]
	    public Byte[] bReserved; 

    }

    /// <summary>
    /// Region or Curve Vertex Information
    /// </summary>
    public struct NET_POLY_POINTS
    {
        /// <summary>
        /// Vertex Number
        /// </summary>
	    public Int32 nPointNum;
        /// <summary>
        /// Vertex Information
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 20)]
	    public NET_POINT[] stuPoints; 
    }


    /// <summary>
    /// Event Type EVENT_IVS_CROSSREGIONDETECTION(Alert Events)The Corresponding Data Block Description Information
    /// </summary>
    public struct DEV_EVENT_CROSSREGION_INFO 
    {
        /// <summary>
        /// Channel Number
        /// </summary>
	    public int nChannelID;
        /// <summary>
        /// Event Name
        /// public byte[]
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 128)]
	    public byte[] szName;
        /// <summary>
        /// Timestamp(Unit is a millisecond)
        /// </summary>
	    public double PTS;
        /// <summary>
        /// Time of Events
        /// </summary>
	    public NET_TIME_EX UTC;
        /// <summary>
        /// Event ID
        /// </summary>
	    public int nEventID;
        /// <summary>
        /// Detected Object
        /// </summary>
	    public NET_MSG_OBJECT stuObject;
        /// <summary>
        /// Event File Information
        /// </summary>
	    public NET_EVENT_FILE_INFO stuFileInfo;
        /// <summary>
        /// Regulation Detect Region
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 20)]
	    public NET_POINT[] DetectRegion;
        /// <summary>
        /// Regulation Detect Region Vertex Number
        /// </summary>
	    public int nDetectRegionNum;
        /// <summary>
        /// Object Motion Track 
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 20)]
	    public NET_POINT[] TrackLine;
        /// <summary>
        /// Object Motion Track Vertex Number
        /// </summary>
	    public int nTrackLineNum;
        /// <summary>
        /// Event Action,0 Denote Pulse Event,1 Denote Durable Events Start,2 Denote Durable Events Stop;
        /// </summary>
	    public byte bEventAction;
        /// <summary>
        /// Denote Invade Direction, 0-Enter, 1-Leave,2-Appear,3-Leave
        /// </summary>
	    public byte bDirection;
        /// <summary>
        /// Denote Action Detection Type,0-Appear 1-Disappear 2-In the Area 3-Across the Region
        /// </summary>
	    public byte bActionType;
        /// <summary>
        /// Byte Alignment
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 1)]
	    public byte[] bReserved1; 
        /// <summary>
        /// Capture Logo(Bitwise),See NET_RESERVED_COMMON
        /// </summary>
        public UInt32 dwSnapFlagMask;
 	   /// <summary>
 	   /// Detected Objects Number
 	   /// </summary>
       [MarshalAs(UnmanagedType.ByValArray, SizeConst = 804)]
	    public byte[] bReserved; 
        /// <summary>
        /// Detected Objects Number
        /// </summary>
	    public int nObjectNum;
        /// <summary>
        /// Detected Objects
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 16)]
	    public NET_MSG_OBJECT[] stuObjectIDs;
        /// <summary>
        /// Track Number(Correspond to The Detected Objects Number)
        /// </summary>
	    public int nTrackNum;
        /// <summary>
        /// Track Information(Correspond to The Detected Objects)
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 16)]
	    public NET_POLY_POINTS[] stuTrackInfo;
    }

    /// <summary>
    /// Event Type EVENT_IVS_PASTEDETECTION(Paste Event)The Corresponding Data Block Description Information
    /// </summary>
    public struct DEV_EVENT_PASTE_INFO 
    {
        /// <summary>
        /// Channel Number
        /// </summary>
	    public int nChannelID;
        /// <summary>
        /// Event Name
        /// public byte[]
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 128)]
	    public byte[] szName; 
        /// <summary>
        /// Timestamp(Unit is a millisecond)
        /// </summary>
	    public double PTS;
        /// <summary>
        /// Time of Events
        /// </summary>
	    public NET_TIME_EX UTC;
        /// <summary>
        /// Event ID
        /// </summary>
	    public int nEventID;
        /// <summary>
        /// Detected Object
        /// </summary>
	    public NET_MSG_OBJECT stuObject;
        /// <summary>
        /// Event File Information
        /// </summary>
	    public NET_EVENT_FILE_INFO  stuFileInfo;
        /// <summary>
        /// Regulation Detect Region Vertex Number public 
        /// </summary>
	    public int nDetectRegionNum;
        /// <summary>
        /// Regulation Detect Region
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 20)]
	    public NET_POINT[] DetectRegion; 
        /// <summary>
        /// Event Action,0 Denote Pulse Event,1 Denote Durable Events Start,2 Denote Durable Events Stop;
        /// </summary>
	    public byte bEventAction;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 3)]
	    public byte[] byReserved;
        /// <summary>
        /// Capture Logo(Bitwise),See NET_RESERVED_COMMON
        /// </summary>
        public UInt32 dwSnapFlagMask;
 	   /// <summary>
 	   /// Retain Bytes For Extension
 	   /// </summary>
       [MarshalAs(UnmanagedType.ByValArray, SizeConst = 888)]
	    public byte[] bReserved; 

    }

    /// <summary>
    /// Event Type EVENT_IVS_LEFTDETECTION(Article Left Event)The Corresponding Data Block Description Information
    /// </summary>
    public struct DEV_EVENT_LEFT_INFO 
    {
        /// <summary>
        /// Channel Number
        /// </summary>
	    public int nChannelID;
        /// <summary>
        /// Event Name
        /// public byte[]
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 128)]
	    public byte[] szName;
        /// <summary>
        /// Timestamp(Unit is a millisecond)
        /// </summary>
	    public double PTS;
        /// <summary>
        /// Time of Events
        /// </summary>
	    public NET_TIME_EX UTC;
        /// <summary>
        /// Event ID
        /// </summary>
	    public int nEventID;
        /// <summary>
        /// Detected Object
        /// </summary>
	    public NET_MSG_OBJECT stuObject;
        /// <summary>
        /// Event File Information
        /// </summary>
	    public NET_EVENT_FILE_INFO  stuFileInfo;
        /// <summary>
        /// Event Action,0 Denote Pulse Event,1 Denote Durable Events Start,2 Denote Durable Events Stop;
        /// </summary>
	    public byte bEventAction;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 3)]
	    public byte[] byReserved;
        /// <summary>
        /// Regulation Detect Region Vertex Number
        /// </summary>
	    public int nDetectRegionNum;
        /// <summary>
        /// Regulation Detect Region
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 20)]  
	    public NET_POINT[] DetectRegion;
        /// <summary>
        /// Capture Logo(Bitwise),See NET_RESERVED_COMMON	
        /// </summary>
        public UInt32 dwSnapFlagMask;
        /// <summary>
        /// Retain Bytes For Extension
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 888)]
	    public byte[] bReserved;

    }

    /// <summary>
    /// Event Type EVENT_IVS_PRESERVATION(Article Preservation Event)The Corresponding Data Block Description Information
    /// </summary>
    public struct DEV_EVENT_PRESERVATION_INFO 
    {
        /// <summary>
        /// Channel Number
        /// </summary>
	    public int nChannelID;
        /// <summary>
        /// Event Name
        /// public byte[]
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 128)]
	    public byte[] szName;
        /// <summary>
        /// Timestamp(Unit is a millisecond)
        /// </summary>
	    public double PTS;
        /// <summary>
        /// Time of Events
        /// </summary>
	    public NET_TIME_EX UTC;
        /// <summary>
        /// Event ID
        /// </summary>
	    public int nEventID;
        /// <summary>
        /// Detected Object
        /// </summary>
	    public NET_MSG_OBJECT stuObject;
        /// <summary>
        /// Event File Information
        /// </summary>
	    public NET_EVENT_FILE_INFO stuFileInfo;
        /// <summary>
        /// Event Action,0 Denote Pulse Event,1 Denote Durable Events Start,2 Denote Durable Events Stop;
        /// </summary>
	    public byte bEventAction;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 3)]
	    public byte[] byReserved;
        /// <summary>
        /// Regulation Detect Region Vertex Number
        /// </summary>
	    public int nDetectRegionNum;
        /// <summary>
        /// Regulation Detect Region
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 20)]
	    public NET_POINT[] DetectRegion;
        /// <summary>
        /// Capture Logo(Bitwise),See NET_RESERVED_COMMON
        /// </summary>
        public UInt32 dwSnapFlagMask;
 	   /// <summary>
 	   /// Retain Bytes For Extension
 	   /// </summary>
       [MarshalAs(UnmanagedType.ByValArray, SizeConst = 888)]
	    public byte[] bReserved; 

    }

    /// <summary>
    /// Event Type EVENT_IVS_STAYDETECTION(Stay Information)The Corresponding Data Block Description Information
    /// </summary>
    public struct DEV_EVENT_STAY_INFO 
    {
        /// <summary>
        /// Channel Number
        /// </summary>
	    public int nChannelID;
        /// <summary>
        /// Event Name
        /// public byte[]
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 128)]
	    public byte[] szName;
        /// <summary>
        /// Timestamp(Unit is a millisecond)
        /// </summary>
	    public double PTS;
        /// <summary>
        /// Time of Events
        /// </summary>
	    public NET_TIME_EX UTC;
        /// <summary>
        /// Event ID
        /// </summary>
	    public int nEventID;
        /// <summary>
        /// Detected Object
        /// </summary>
	    public NET_MSG_OBJECT stuObject;
        /// <summary>
        /// Event File Information
        /// </summary>
	    public NET_EVENT_FILE_INFO stuFileInfo;
        /// <summary>
        /// Event Action,0 Denote Pulse Event,1 Denote Durable Events Start,2 Denote Durable Events Stop;
        /// </summary>
	    public byte bEventAction;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 3)]
	    public byte[] byReserved;
        /// <summary>
        /// Regulation Detect Region Vertex Number
        /// </summary>
	    public int nDetectRegionNum;
        /// <summary>
        /// Regulation Detect Region
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 20)]
	    public NET_POINT[] DetectRegion;
        /// <summary>
        /// Capture Logo(Bitwise),See NET_RESERVED_COMMON	
        /// </summary>
        public UInt32 dwSnapFlagMask;
        /// <summary>
        /// Retain Bytes For Extension
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 888)]
	    public byte[] bReserved; 

    }

    /// <summary>
    /// Event Type EVENT_IVS_WANDERDETECTION(Hover Event)The Corresponding Data Block Description Information
    /// </summary>
    public struct DEV_EVENT_WANDER_INFO 
    {
        /// <summary>
        /// Channel Number
        /// </summary>
	    public int nChannelID;
        /// <summary>
        /// Event Name
        /// public byte[]
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 128)]
	    public byte[] szName;
        /// <summary>
        /// Timestamp(Unit is a millisecond)
        /// </summary>
	    public double PTS;
        /// <summary>
        /// Time of Events
        /// </summary>
	    public NET_TIME_EX UTC;
        /// <summary>
        /// Event ID
        /// </summary>
	    public int nEventID;
        /// <summary>
        /// Event File Information
        /// </summary>
	    public NET_EVENT_FILE_INFO  stuFileInfo;
        /// <summary>
        /// Event Action,0 Denote Pulse Event,1 Denote Durable Events Start,2 Denote Durable Events Stop;
        /// </summary>
	    public byte bEventAction;
        /// <summary>
        /// Retain Bytes
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 3)]
	    public byte[] byReserved; 
        /// <summary>
        /// Detected Objects Number
        /// </summary>
	    public int nObjectNum;
        /// <summary>
        /// Detected Objects
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 16)]
	    public NET_MSG_OBJECT[] stuObjectIDs;
        /// <summary>
        /// Track Number(Correspond to The Detected Objects Number)
        /// </summary>
	    public Int32 nTrackNum;
        /// <summary>
        /// Track Information(Correspond to The Detected Objects)
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 16)]
	    public NET_POLY_POINTS[] stuTrackInfo;
        /// <summary>
        /// Regulation Detect Region Vertex Number
        /// </summary>
	    public Int32 nDetectRegionNum;
        /// <summary>
        /// Regulation Detect Region
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 20)]
	    public NET_POINT[] DetectRegion;
        /// <summary>
        /// Capture Logo(Bitwise),See NET_RESERVED_COMMON	
        /// </summary>
        public UInt32 dwSnapFlagMask;
        /// <summary>
        /// Retain Bytes For Extension
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 1020)]
	    public byte[] bReserved;
 
    }

    /// <summary>
    /// Event Type EVENT_IVS_MOVEDETECTION(Mobile Event)The Corresponding Data Block Description Information
    /// </summary>
    public struct DEV_EVENT_MOVE_INFO 
    {
        /// <summary>
        /// Channel Number
        /// </summary>
	    public Int32 nChannelID;
        /// <summary>
        /// Event Name
        /// public byte[]
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 128)]
	    public byte[] szName; 
        /// <summary>
        /// Timestamp(Unit is a millisecond)
        /// </summary>
	    public double PTS;
        /// <summary>
        /// Time of Events
        /// </summary>
	    public NET_TIME_EX UTC;
        /// <summary>
        /// Event ID
        /// </summary>
	    public Int32 nEventID;
        /// <summary>
        /// Detected Object
        /// </summary>
	    public NET_MSG_OBJECT stuObject;
        /// <summary>
        /// Event File Information
        /// </summary>
	    public NET_EVENT_FILE_INFO  stuFileInfo;
        /// <summary>
        /// Event Action,0 Denote Pulse Event,1 Denote Durable Events Start,2 Denote Durable Events Stop;
        /// </summary>
	    public byte bEventAction;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 3)]
	    public byte[] byReserved;
        /// <summary>
        /// Regulation Detect Region Vertex Number
        /// </summary>
	    public Int32 nDetectRegionNum;
        /// <summary>
        /// Regulation Detect Region
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 20)]
	    public NET_POINT[] DetectRegion;
        /// <summary>
        /// Capture Logo(Bitwise),See NET_RESERVED_COMMON
        /// </summary>
        public UInt32 dwSnapFlagMask;
 	   /// <summary>
 	   /// Retain Bytes For Extension
 	   /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 888)]
	    public byte[] bReserved; 

    }

    /// <summary>
    /// Event Type EVENT_IVS_TAILDETECTION(Following Event) Data Block Description
    /// </summary>
    public struct DEV_EVENT_TAIL_INFO 
    {
        /// <summary>
        /// Channel Number
        /// </summary>
	    public Int32 nChannelID;
        /// <summary>
        /// Event Name
        /// public byte[]
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 128)]
	    public byte[] szName;
        /// <summary>
        /// Timestamp(ms)
        /// </summary>
	    public double PTS;
        /// <summary>
        /// Event Time
        /// </summary>
	    public NET_TIME_EX UTC;
        /// <summary>
        /// Event ID
        /// </summary>
	    public Int32 nEventID;
        /// <summary>
        /// Number of Detected Objects
        /// </summary>
	    public NET_MSG_OBJECT stuObject;
        /// <summary>
        /// Event File Info
        /// </summary>
	    public NET_EVENT_FILE_INFO  stuFileInfo;
        /// <summary>
        /// Event Action,0:Pulse Event,1:Event Start,2:Event End;
        /// </summary>
	    public byte bEventAction;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 3)]
	    public byte[] byReserved;
        /// <summary>
        /// Detection Region Vertices
        /// </summary>
	    public Int32 nDetectRegionNum;
        /// <summary>
        /// Detection Region
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 20)]
	    public NET_POINT[] DetectRegion;
        /// <summary>
        /// Snap Flag(bitwise),Please See NET_RESERVED_COMMON	
        /// </summary>
        public UInt32 dwSnapFlagMask;
        /// <summary>
        /// Reserved Bytes,to be Developed.
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 888)]
	    public byte[] bReserved; 

    } 


    /// <summary>
    /// Event Type EVENT_IVS_RIOTERDETECTION (Riot Event) Data Block Description
    /// </summary>
    public struct DEV_EVENT_RIOTERL_INFO 
    {
        /// <summary>
        /// Channel Number
        /// </summary>
	    public Int32 nChannelID;
        /// <summary>
        /// Event Name
        /// public byte[]
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 128)]
	    public byte[] szName;
        /// <summary>
        /// TimeStamp(ms)
        /// </summary>
	    public double PTS;
        /// <summary>
        /// Event Time
        /// </summary>
	    public NET_TIME_EX UTC;
        /// <summary>
        /// Event ID
        /// </summary>
	    public Int32 nEventID;
        /// <summary>
        /// Number of Detected Objects 
        /// </summary>
	    public Int32 nObjectNum;
        /// <summary>
        /// Objects Detected List
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 16)]
	    public NET_MSG_OBJECT[] stuObjectIDs;
        /// <summary>
        /// Event File Info
        /// </summary>
	    public NET_EVENT_FILE_INFO  stuFileInfo;
        /// <summary>
        /// Event Action,0:Pulse Event,1:Event Start,2:Event End;
        /// </summary>
	    public byte bEventAction;
        /// <summary>
        /// Reserved Bytes
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 3)]
	    public byte[] byReserved; 
        /// <summary>
        /// Detection Region Vertices
        /// </summary>
	    public Int32 nDetectRegionNum;
        /// <summary>
        /// Detection Region
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 20)]
	    public NET_POINT[] DetectRegion;
        /// <summary>
        /// Snap Flag(bitwise),Please See NET_RESERVED_COMMON	
        /// </summary>
        public UInt32 dwSnapFlagMask;
        /// <summary>
        /// Reserved Bytes,to be Developed.
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 888)]
	    public byte[] bReserved; 

    }

    /// <summary>
    /// Event Type EVENT_IVS_FIREDETECTION(Fire Event) Data Block Description
    /// </summary>
    public struct DEV_EVENT_FIRE_INFO 
    {
        /// <summary>
        /// Channel Number
        /// </summary>
	    public Int32 nChannelID;
        /// <summary>
        /// Event Name
        /// public byte[]
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 128)]
	    public byte[] szName;
        /// <summary>
        ///TimeStamp(ms)
        /// </summary>
	    public double PTS;
        /// <summary>
        /// Event Time
        /// </summary>
	    public NET_TIME_EX UTC;
        /// <summary>
        /// Event ID
        /// </summary>
	    public Int32 nEventID;
        /// <summary>
        /// Detected Objects
        /// </summary>
	    public NET_MSG_OBJECT stuObject;
        /// <summary>
        /// Event File Info
        /// </summary>
	    public NET_EVENT_FILE_INFO stuFileInfo;
        /// <summary>
        /// Event Action,0:Pulse Event,1:Event Start,2:Event End;
        /// </summary>
	    public byte bEventAction;
        /// <summary>
        /// Reserved Bytes
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 3)]
	    public byte[] byReserved;
        /// <summary>
        /// Detection Region Vertices
        /// </summary>
	    public Int32 nDetectRegionNum;
        /// <summary>
        /// Detection Region
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 20)]
	    public NET_POINT[] DetectRegion;
    	/// <summary>
    	/// Snap Flag(bitwise),Please See NET_RESERVED_COMMON
    	/// </summary>
        public UInt32 dwSnapFlagMask;
 	   /// <summary>
 	   /// Reserved Bytes,to be Developed.
 	   /// </summary>
       [MarshalAs(UnmanagedType.ByValArray, SizeConst = 888)]
	    public byte[] bReserved;

    }

    /// <summary>
    /// Event Type EVENT_IVS_SMOKEDETECTION(Smoke Event) Data Block Description
    /// </summary>
    public struct DEV_EVENT_SMOKE_INFO 
    {
        /// <summary>
        /// Channel Number
        /// </summary>
	    public Int32 nChannelID;
        /// <summary>
        /// Event Name
        /// public byte[]
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 128)]
	    public byte[] szName; 
        /// <summary>
        /// TimeStamp(ms)
        /// </summary>
	    public double PTS;
        /// <summary>
        /// Event Time
        /// </summary>
	    public NET_TIME_EX UTC;
        /// <summary>
        /// Event ID 
        /// </summary>
	    public Int32 nEventID;
        /// <summary>
        /// Detected Objects
        /// </summary>
	    public NET_MSG_OBJECT stuObject;
        /// <summary>
        /// Event File Info
        /// </summary>
	    public NET_EVENT_FILE_INFO  stuFileInfo;
        /// <summary>
        /// Event Action,0:Pulse Event,1:Event Start,2:Event End;
        /// </summary>
	    public byte bEventAction;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 3)]
	    public byte[] byReserved;
        /// <summary>
        /// Snap Flag(bitwise),Please See NET_RESERVED_COMMON
        /// </summary>
        public UInt32 dwSnapFlagMask;
 	   /// <summary>
 	   /// Reserved Bytes,to be Developed.
 	   /// </summary>
       [MarshalAs(UnmanagedType.ByValArray, SizeConst = 972)]
	    public byte[] bReserved; 

    }

    /// <summary>
    /// Event Type EVENT_IVS_FLOWSTAT(Flow Statistics) Data Block Description
    /// </summary>
    public struct DEV_EVENT_FLOWSTAT_INFO 
    {
        /// <summary>
        /// Channel Number
        /// </summary>
	    public Int32 nChannelID;
        /// <summary>
        /// Event Name
        /// public byte[]
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 128)]
	    public byte[] szName;
        /// <summary>
        /// TimeStamp(ms)
        /// </summary>
	    public double PTS;
        /// <summary>
        /// Event Time
        /// </summary>
	    public NET_TIME_EX UTC;
        /// <summary>
        /// Event ID
        /// </summary>
	    public Int32 nEventID;
        /// <summary>
        /// Number of People from Left
        /// </summary>
	    public Int32 nNumberLeft;
        /// <summary>
        /// Number of People from Right 
        /// </summary>
	    public Int32 nNumberRight;
        /// <summary>
        /// Upper Limit
        /// </summary>
	    public Int32 nUpperLimit;
        /// <summary>
        /// Event File Info
        /// </summary>
	    public NET_EVENT_FILE_INFO stuFileInfo;
        /// <summary>
        /// Event Action,0:Pulse Event,1:Event Start,2:Event End;
        /// </summary>
	    public byte bEventAction;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 3)]
	    public byte[] byReserved;
        /// <summary>
        /// Snap Flag(bitwise),Please See NET_RESERVED_COMMON	
        /// </summary>
        public UInt32 dwSnapFlagMask;
        /// <summary>
        /// Reserved Bytes,to be Developed.
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 972)]
	    public byte[] bReserved; 

    }


    
    /// <summary>
    /// Event Type EVENT_IVS_NUMBERSTAT(Number Statistics) Data Block Description
    /// </summary>
    public struct DEV_EVENT_NUMBERSTAT_INFO 
    {
        /// <summary>
        /// Channel Number
        /// </summary>
	    public Int32 nChannelID;
        /// <summary>
        /// Event Name
        /// public byte[]
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 128)]
	    public byte[] szName; 
        /// <summary>
        /// TimeStamp(ms)
        /// </summary>
	    public double PTS;
        /// <summary>
        /// Event Time
        /// </summary>
	    public NET_TIME_EX UTC;
        /// <summary>
        /// Event ID
        /// </summary>
	    public Int32 nEventID;
        /// <summary>
        /// Number of Objects in Region
        /// </summary>
	    public Int32 nNumber;
        /// <summary>
        /// Upper Limit
        /// </summary>
	    public Int32 nUpperLimit;
        /// <summary>
        /// Event File Info
        /// </summary>
	    public NET_EVENT_FILE_INFO stuFileInfo;
        /// <summary>
        /// Event Action,0:Pulse Event,1:Event Start,2:Event End;
        /// </summary>
	    public byte bEventAction;
        /// <summary>
        /// Byte aligned 
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 3)]
	    public byte[] bReserved1;
        /// <summary>
        /// Number of Entered Objects
        /// </summary>
	    public Int32 nEnteredNumber;
        /// <summary>
        /// Number of Exit Objects
        /// </summary>
	    public Int32 nExitedNumber;
        /// <summary>
        /// Snap Flag(bitwise),Please See NET_RESERVED_COMMON	
        /// </summary>
        public UInt32 dwSnapFlagMask;
        /// <summary>
        /// Reserved Bytes,to be Developed.
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 964)]
	    public byte[] bReserved; 

    }

    /// <summary>
    /// Event Type EVENT_IVS_TRAFFICCONTROL( Traffic Control ) Data Block Description
    /// </summary>
    public struct DEV_EVENT_TRAFFICCONTROL_INFO 
    {
        /// <summary>
        /// Channel Number
        /// </summary>
	    public Int32 nChannelID;
        /// <summary>
        /// Event Name
        /// public byte[]
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 128)]
	    public byte[] szName;
        /// <summary>
        /// TimeStamp(ms)
        /// </summary>
	    public double PTS;
        /// <summary>
        /// Event Time
        /// </summary>
	    public NET_TIME_EX UTC;
        /// <summary>
        /// Event ID
        /// </summary>
	    public Int32 nEventID;
        /// <summary>
        /// Detected Objects
        /// </summary>
	    public NET_MSG_OBJECT stuObject;
        /// <summary>
        /// Event File Info
        /// </summary>
	    public NET_EVENT_FILE_INFO  stuFileInfo;
        /// <summary>
        /// Event Action,0:Pulse Event,1:Event Start,2:Event End;
        /// </summary>
	    public byte bEventAction;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 3)]
	    public byte[] byReserved;
        /// <summary>
        /// Snap Flag(bitwise),Please See NET_RESERVED_COMMON	
        /// </summary>
        public UInt32 dwSnapFlagMask;
        /// <summary>
        /// Reserved Bytes,to be Developed.
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 972)]
	    public byte[] bReserved; 
    }

    
    /// <summary>
    /// Event Type EVENT_IVS_TRAFFICACCIDENT( Traffic Accident) Data Block Description
    /// </summary>
    public struct DEV_EVENT_TRAFFICACCIDENT_INFO 
    {
        /// <summary>
        /// Channel Number
        /// </summary>
	    public Int32 nChannelID;
        /// <summary>
        /// Event Name
        /// public byte[]
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 128)]
	    public byte[] szName;
        /// <summary>
        /// TimeStamp(ms)
        /// </summary>
	    public double PTS;
        /// <summary>
        /// Event Time
        /// </summary>
	    public NET_TIME_EX UTC;
        /// <summary>
        /// Event ID
        /// </summary>
	    public Int32 nEventID;
        /// <summary>
        /// Number of Detected Objects
        /// </summary>
	    public Int32 nObjectNum;
        /// <summary>
        /// Detected Objects List
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 16)]
	    public NET_MSG_OBJECT[] stuObjectIDs;
        /// <summary>
        /// Event File Info
        /// </summary>
	    public NET_EVENT_FILE_INFO  stuFileInfo;
        /// <summary>
        /// Event Action,0:Pulse Event,1:Event Start,2:Event End;
        /// </summary>
	    public byte bEventAction;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 3)]
	    public byte[] byReserved;
        /// <summary>
        /// Snap Flag(bitwise),Please See NET_RESERVED_COMMON	
        /// </summary>
        public UInt32 dwSnapFlagMask;
        /// <summary>
        /// Reserved Bytes,to be Developed..
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 972)]
	    public byte[] bReserved; 

    }

    /// <summary>
    /// TrafficCar Traffic Car Info
    /// </summary>
    public struct DEV_EVENT_TRAFFIC_TRAFFICCAR_INFO
    {
        /// <summary>
        /// License Number
        /// public byte[]
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 32)]
	    public byte[] szPlateNumber;
        /// <summary>
        /// License Plate Type, Please See  VideoAnalyseRule 
        /// public byte[]
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 32)]
	    public byte[] szPlateType;
        /// <summary>
        /// License Plate Color  "Blue","Yellow", "White","Black"
        /// public byte[]
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 32)]
	    public byte[] szPlateColor;
        /// <summary>
        /// Car Color	"White", "Black", "Red", "Yellow", "Gray", "Blue","Green"
        /// public byte[]
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 32)]
	    public byte[] szVehicleColor;
        /// <summary>
        /// Speed    Km/H
        /// </summary>
	    public int nSpeed;
        /// <summary>
        /// Triggered Events	Please See Event List,For Traffic Events Only
        /// public byte[]
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 64)]
	    public byte[] szEvent;
        /// <summary>
        /// Violation Code	Please See  TrafficGlobal.ViolationCode
        /// public byte[]
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 32)]
	    public byte[] szViolationCode;
        /// <summary>
        /// Violation Descripiton
        /// public byte[]
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 64)]
	    public byte[] szViolationDesc; 
        /// <summary>
        /// Lower Speed Limit
        /// </summary>
	    public Int32 nLowerSpeedLimit;
        /// <summary>
        /// Upper Speed Limit
        /// </summary>
	    public Int32 nUpperSpeedLimit;
        /// <summary>
        /// Over Speed Margin    km/h 
        /// </summary>
	    public Int32 nOverSpeedMargin;
        /// <summary>
        /// Under Speed Margin   km/h 
        /// </summary>
	    public Int32 nUnderSpeedMargin;
        /// <summary>
        /// (Traffic) Lane	Please see crossing events in Event List
        /// </summary>
	    public Int32 nLane;
        /// <summary>
        /// Car Size	,Bitwise: 0:"Light-duty" , 1:"Medium", 2 :"Oversize" 
        /// </summary>
	    public Int32 nVehicleSize;
        /// <summary>
        /// Car Length (m)
        /// </summary>
	    public float fVehicleLength;
        /// <summary>
        /// Snap Mode  0-Unclassified,1-Panorama,2-Close Shot,4-Snap in Same Direction,8-Snap in Oppsite Direction,16-License Plate Picture
        /// </summary>
	    public Int32 nSnapshotMode;
        /// <summary>
        /// Local or Remote Channel Info,Could be place info from channel title setting 			   ChannelTitle.Name 
        /// public byte[]
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 32)]
	    public byte[] szChannelName;
        /// <summary>
        /// Local or Remote Machine Name	From general setting in General.MachineName
        /// public byte[]
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 256)]
	    public byte[] szMachineName;
        /// <summary>
        /// Machine Group ,default none, user can manage different machines to a group
        /// public byte[]
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 256)]
	    public byte[] szMachineGroup;
        /// <summary>
        /// Traffic Lane Number  	UTF-8 coding
        /// public byte[]
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 64)]
	    public byte[] szRoadwayNo;
        /// <summary>
        /// "DrivingDirection" : ["Approach", "Shanghai", "Hangzhou"], Driving direction
        /// "Approach"-  Car approach machine；"Leave"- Car leave machine
        ///  the second and third parameter refer to the approaching or leaving place, UTF-8 coding
        /// public byte[]
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 3 * 256)]
	    public byte[] szDrivingDirection;
        /// <summary>
        /// Reserved Bytes,to be Developed..
        /// </summary>
    	[MarshalAs(UnmanagedType.ByValArray, SizeConst = 1020)]
	    public byte[] bReserved; 
    }

    /// <summary>
    /// Event Type EVENT_IVS_TRAFFICJUNCTION(Traffic Conjunction) Data Block Description
    /// </summary>
    public struct DEV_EVENT_TRAFFICJUNCTION_INFO 
    {
        /// <summary>
        /// Channel Number
        /// </summary>
	    public Int32 nChannelID;
        /// <summary>
        /// Event Name
        /// public byte[]
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 128)]
	    public byte[] szName;
        /// <summary>
        /// TimeStamp(ms)
        /// </summary>
	    public double PTS;
        /// <summary>
        /// Event Time
        /// </summary>
	    public NET_TIME_EX UTC;
        /// <summary>
        /// Event ID
        /// </summary>
	    public Int32 nEventID;
        /// <summary>
        /// Detected Objects 
        /// </summary>
	    public NET_MSG_OBJECT stuObject;
        /// <summary>
        /// Traffic Lane Number
        /// </summary>
	    public Int32 nLane;
        /// <summary>
        /// Violation Mask: Bitwise,1: ignore red light
        /// 2: do not follow the lane;
        /// 3: go in the wrong direction;  4：illegal U-turn;
        /// 5: traffic congestion;        6: traffic free
        /// 7: car wheel on line ;        default: traffic junction event
        /// </summary>
	    public UInt32 dwBreakingRule;
        /// <summary>
        /// Red Light Start UTC time
        /// </summary>
	    public NET_TIME_EX RedLightUTC;
        /// <summary>
        /// Event File Info
        /// </summary>
	    public NET_EVENT_FILE_INFO  stuFileInfo;
        /// <summary>
        /// Snap Sequence, e.g. 3,2,1,1: snap complete, 0: snap wrong exit
        /// </summary>
	    public Int32 nSequence;
        /// <summary>
        /// Car Actual SpeedKm/h                 
        /// </summary>
	    public Int32 nSpeed;
        /// <summary>
        /// Event Action,0:Pulse Event,1:Event Start,2:Event End;
        /// </summary>
	    public byte bEventAction;
        /// <summary>
        /// Reserved Bytes
        /// </summary>
	    public byte[] byReserved;
        /// <summary>
        /// Car Body Info
        /// </summary>
	    public NET_MSG_OBJECT stuVehicle;
        /// <summary>
        /// Snap Flag(bitwise),Please See NET_RESERVED_COMMON	
        /// </summary>
        public UInt32 dwSnapFlagMask;
        /// <summary>
        /// Reserved Bytes,to be Developed..
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 476)]
        public byte[] bReserved;
        /// <summary>
        /// Traffic Car Info
        /// </summary>
	    public DEV_EVENT_TRAFFIC_TRAFFICCAR_INFO stTrafficCar; 

    }

    /// <summary>
    /// Snap Info
    /// </summary>
    public struct NET_SIG_CARWAY_INFO
    {
        /// <summary>
        /// Current Car Speed,km/h
        /// </summary>
	    public short snSpeed;
        /// <summary>
        /// Current Car Length, dm
        /// </summary>
	    public short snCarLength;
        /// <summary>
        /// Current lane red light dration , s.ms
        /// </summary>
	    public float fRedTime;
        /// <summary>
        /// Current Lane Snap Time m.ms 
        /// </summary>
	    public float fCapTime;
        /// <summary>
        /// Current Snap Sequence Number
        /// </summary>
	    public byte bSigSequence;
        /// <summary>
        /// Current lane Snap Mode
        /// 0: rader upper speed limit ;1: radar lower speed limti;
   	   /// 2: Sensor upper speed limit ;3:Sensor lower speed limit; 
        ///4:go in the wrong direction 
        /// 5:ignore the red light 6: red light on 7:red light off  8: all snap or traffic junction
         /// </summary>
	    public byte bType;
        /// <summary>
        ///  Ignore red light type :01:turn left red light; 02:go straight red light; 
        ///03:turn right red light
        /// </summary>
	    public byte bDirection;
        /// <summary>
        /// Current lane light state,0: green light, 1: red light 2: yellow light
        /// </summary>
	    public byte bLightColor;
        /// <summary>
        /// Snap Flag
        /// </summary>
	    public byte[] bSnapFlag;
    }

    /// <summary>
    /// Car lane info
    /// </summary>
    public struct NET_CARWAY_INFO
    {
        /// <summary>
        /// Current CarWay Info 
        /// </summary>
	    public byte bCarWayID;
        /// <summary>
        /// Reserved Field
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 2)]
	    public byte[] bReserve;
        /// <summary>
        /// Number of triggered snap
        /// </summary>
	    public byte bSigCount;
        /// <summary>
        /// triggered Snap Info on current lane
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 3)]
	    public NET_SIG_CARWAY_INFO[]  stuSigInfo;
        /// <summary>
        /// Reserved Field
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 12)]
	    public byte[] bReserved; 
    };

    /// <summary>
    /// Event Type EVENT_TRAFFICSNAPSHOT(Traffic Snap Shot ) Data Block Description
    /// </summary>
    public struct DEV_EVENT_TRAFFICSNAPSHOT_INFO 
    {
        /// <summary>
        /// Channel Number
        /// </summary>
	    public Int32 nChannelID;
        /// <summary>
        /// Event Name
        /// public byte[]
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 128)]
	    public byte[] szName;
        /// <summary>
        /// TimeStamp(ms)
        /// </summary>
	    public double PTS;
        /// <summary>
        /// Event Time
        /// </summary>
	    public NET_TIME_EX UTC;
        /// <summary>
        /// Event ID
        /// </summary>
	    public Int32 nEventID;
        /// <summary>
        /// Reserved Bytes 
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 3)]
	    public byte[] bReserv;
        /// <summary>
        /// Count of lanes that trigger snap
        /// </summary>
	    public byte bCarWayCount;
        /// <summary>
        /// Info of lanes that trigger snap
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 8)]
	    public NET_CARWAY_INFO[] stuCarWayInfo;
        /// <summary>
        /// Event File Info
        /// </summary>
	    public NET_EVENT_FILE_INFO  stuFileInfo;
        /// <summary>
        /// Event Action,0:Pulse Event,1:Event Start,2:Event End;
        /// </summary>
	    public byte bEventAction;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 3)]
	    public byte[] byReserved;
        /// <summary>
        /// Snap Flag(bitwise),Please See NET_RESERVED_COMMON	
        /// </summary>
        public UInt32 dwSnapFlagMask;
        /// <summary>
        /// Reserved Bytes,to be Developed.
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 340)]
	    public byte[] bReserved;
    }

    /// <summary>
    /// Event Type EVENT_IVS_FACEDETECT(Face Detect) Data Block Description
    /// </summary>
    public struct DEV_EVENT_FACEDETECT_INFO 
    {
        /// <summary>
        /// Channel Number
        /// </summary>
	    public Int32 nChannelID;
        /// <summary>
        /// Event Name
        /// public byte[]
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 128)]
	    public byte[] szName;
        /// <summary>
        /// TimeStamp(ms)
        /// </summary>
	    public double PTS;
        /// <summary>
        /// Event Time
        /// </summary>
	    public NET_TIME_EX UTC;
        /// <summary>
        /// Event ID
        /// </summary>
	    public Int32 nEventID;
        /// <summary>
        /// Detected Objects
        /// </summary>
	    public NET_MSG_OBJECT stuObject;
        /// <summary>
        /// Event File Info
        /// </summary>
	    public NET_EVENT_FILE_INFO  stuFileInfo;
        /// <summary>
        /// Event Action,0:Pulse Event,1:Event Start,2:Event End;
        /// </summary>
	    public byte bEventAction;
        /// <summary>
        /// Reserved Bytes
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 3)]
	    public byte[] reserved;
        /// <summary>
        /// Detection Region Vertices
        /// </summary>
	    public Int32 nDetectRegionNum;
        /// <summary>
        /// Detection Region
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 20)]
	    public NET_POINT[] DetectRegion;
        /// <summary>
        /// Snap Flag(bitwise),Please See NET_RESERVED_COMMON	
        /// </summary>
        public UInt32 dwSnapFlagMask;
        /// <summary>
        /// Reserved Bytes,to be Developed.
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 932)]
	    public byte[] bReserved;
    } 

    
    /// <summary>
    /// Event Type EVENT_IVS_TRAFFIC_RUNREDLIGHT(Traffic -run red light) Data Block Description
    /// </summary>
    public struct DEV_EVENT_TRAFFIC_RUNREDLIGHT_INFO
    {
        /// <summary>
        /// Channel Number
        /// </summary>
	    public Int32 nChannelID;
        /// <summary>
        /// Event Name
        /// public byte[]
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 128)]
	    public byte[] szName;
        /// <summary>
        /// TimeStamp(ms)
        /// </summary>
	    public double PTS;
        /// <summary>
        /// Event Time
        /// </summary>
	    public NET_TIME_EX UTC;
        /// <summary>
        /// Event ID
        /// </summary>
	    public Int32 nEventID;
        /// <summary>
        /// Traffic Lane Number
        /// </summary>
	    public Int32 nLane;
        /// <summary>
        /// License Plate Info
        /// </summary>
	    public NET_MSG_OBJECT stuObject;
        /// <summary>
        /// Car Body Info
        /// </summary>
	    public NET_MSG_OBJECT stuVehicle;
        /// <summary>
        /// Event File Info 
        /// </summary>
	    public NET_EVENT_FILE_INFO  stuFileInfo;
        /// <summary>
        /// Traffic light state 0:unknown 1：green light 2: red light 3: yellow light
        /// </summary>
	    public Int32 nLightState;
        /// <summary>
        /// Car Speed,km/h
        /// </summary>
	    public Int32 nSpeed;
        /// <summary>
        /// Snap Sequence, e.g. 3,2,1,1: snap complete, 0: snap wrong exit
        /// </summary>
	    public Int32 nSequence;
        /// <summary>
        /// Event Action,0:Pulse Event,1:Event Start,2:Event End;
        /// </summary>
	    public byte bEventAction;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 3)]
	    public byte[] byReserved;
        /// <summary>
        /// Snap Flag(bitwise),Please See NET_RESERVED_COMMON	
        /// </summary>
        public UInt32 dwSnapFlagMask;
        /// <summary>
        /// Reserved Bytes
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 1016)]
	    public byte[] bReserved;
        /// <summary>
        /// Traffic Car Info
        /// </summary>
	    public DEV_EVENT_TRAFFIC_TRAFFICCAR_INFO stTrafficCar;
    } 


    
    /// <summary>
    /// Event Type EVENT_IVS_TRAFFIC_OVERLINE(Traffic - Over Line) Data Block Description
    /// </summary>
    public struct DEV_EVENT_TRAFFIC_OVERLINE_INFO
    {
        /// <summary>
        /// Channel Number
        /// </summary>
	    public Int32 nChannelID;
        /// <summary>
        /// Event Name
        /// public byte[]
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 128)]
	    public byte[] szName;
        /// <summary>
        /// TimeStamp(ms)
        /// </summary>
	    public double PTS;
        /// <summary>
        /// Event Time
        /// </summary>
	    public NET_TIME_EX UTC;
        /// <summary>
        /// Event ID
        /// </summary>
	    public Int32 nEventID;
        /// <summary>
        /// Traffic Lane Number
        /// </summary>
	    public Int32 nLane;
        /// <summary>
        /// License Plate Info
        /// </summary>
	    public NET_MSG_OBJECT stuObject;
        /// <summary>
        /// Car Body Info
        /// </summary>
	    public NET_MSG_OBJECT stuVehicle;
        /// <summary>
        /// Event File Info
        /// </summary>
	    public NET_EVENT_FILE_INFO  stuFileInfo;
        /// <summary>
        /// Snap Sequence, e.g. 3,2,1,1: snap complete, 0: snap wrong exit
        /// </summary>
	    public Int32 nSequence;
        /// <summary>
        /// Car Actual Speed,Km/h
        /// </summary>
	    public Int32 nSpeed;
        /// <summary>
        /// Event Action,0:Pulse Event,1:Event Start,2:Event End;
        /// </summary>
	    public byte bEventAction;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 3)]
	    public byte[] byReserved;
        /// <summary>
        /// Snap Flag(bitwise),Please See NET_RESERVED_COMMON	
        /// </summary>
        public UInt32 dwSnapFlagMask;
        /// <summary>
        /// Reserved Bytes
        /// </summary>
    	[MarshalAs(UnmanagedType.ByValArray, SizeConst = 1008)]
	    public byte[] bReserved;
        /// <summary>
        /// Traffic Car Info
        /// </summary>
	    public DEV_EVENT_TRAFFIC_TRAFFICCAR_INFO stTrafficCar;
    }

     /// <summary>
    ///  Parking Info
    /// </summary>
    public  struct DEV_TRAFFIC_PARKING_INFO
    {
        /// <summary>
        /// Feature Picture Area Number
        /// </summary>
        public int              nFeaturePicAreaPointNum;  
        /// <summary>
        /// Feature Picture Area Infos
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 16)]
        public NET_POINT[]      stFeaturePicArea;   
        /// <summary>
        /// Reserved Bytes
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 572)]
        public byte[]            bReserved;          
    }

    //NTP校时状态
    public enum EM_NTP_STATUS
    {
        NET_NTP_STATUS_UNKNOWN = 0 ,
        NET_NTP_STATUS_DISABLE , 
        NET_NTP_STATUS_SUCCESSFUL , 
        NET_NTP_STATUS_FAILED , 
    }

    public struct EVENT_COMM_INFO
    {
        public EM_NTP_STATUS        emNTPStatus;     //NTP校时状态
        public int                  nDriversNum;     //驾驶员信息数
        public IntPtr               pstDriversInfo;  //驾驶员信息数据,//DH_MSG_OBJECT_EX *
        public IntPtr               pszFilePath;     //本地硬盘或者sd卡成功写入路径,为NULL时，路径不存在
        public IntPtr               pszFTPPath;      //设备成功写到ftp服务器的路径
        public IntPtr               pszVideoPath;    //当前接入需要获取当前违章的关联视频的FTP上传路径
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 2024)]
        public byte[]               bReserved; 
    }

    /// <summary>
    /// Event Type EVENT_IVS_TRAFFIC_PARKINGSPACEPARKING Data Block Description
    /// </summary>
    public  struct DEV_EVENT_TRAFFIC_PARKINGSPACEPARKING_INFO
    {
        /// <summary>
        /// Channel Number
        /// </summary>
	    public Int32 nChannelID;
        /// <summary>
        /// Event Name
        /// public byte[]
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 128)]
	    public byte[] szName;
        /// <summary>
        /// Reserved Bytes
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 8)]
        public byte[]  bReserved1;    
        /// <summary>
        /// TimeStamp(ms)
        /// </summary>
	    public double PTS;
        /// <summary>
        /// Event Time
        /// </summary>
	    public NET_TIME_EX UTC;
        /// <summary>
        /// Event ID
        /// </summary>
	    public Int32 nEventID;
        /// <summary>
        /// Traffic Lane Number
        /// </summary>
	    public Int32 nLane;
        /// <summary>
        /// License Plate Info
        /// </summary>
	    public NET_MSG_OBJECT stuObject;
        /// <summary>
        /// Car Body Info
        /// </summary>
	    public NET_MSG_OBJECT stuVehicle;
        /// <summary>
        /// Event File Info
        /// </summary>
	    public NET_EVENT_FILE_INFO  stuFileInfo;
        /// <summary>
        /// Snap Sequence, e.g. 3,2,1,1: snap complete, 0: snap wrong exit
        /// </summary>
	    public Int32 nSequence;
        /// <summary>
        /// Event Action,0:Pulse Event,1:Event Start,2:Event End;
        /// </summary>
	    public byte bEventAction;
        /// <summary>
        /// Reserved Bytes
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 2)]
	    public byte[] byReserved;
        /// <summary>
        ///  Image Index
        /// </summary>
        public byte  byImageIndex;
        /// <summary>
        /// Snap Flag(bitwise),Please See NET_RESERVED_COMMON	
        /// </summary>
        public UInt32 dwSnapFlagMask;
        /// <summary>
        /// Pictrue Resolution
        /// </summary>
        public NET_RESOLUTION_INFO  stuResolution;
        /// <summary>
        /// Traffic Car Info
        /// </summary>                    
        public DEV_EVENT_TRAFFIC_TRAFFICCAR_INFO stTrafficCar;    
        /// <summary>
        /// Parking Space Status
        /// </summary>
        public int     nParkingSpaceStatus;
        /// <summary>
        /// Paring Info
        /// </summary>
        public DEV_TRAFFIC_PARKING_INFO stTrafficParingInfo;     
        /// <summary>
        /// Reserved Bytes
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 380)]
	    public byte[] bReserved; 
        /// <summary>
        /// Common Info
        /// </summary>
        public EVENT_COMM_INFO     stCommInfo;                                 // 公共信息
    }

    /// <summary>
    /// Event Type EVENT_IVS_TRAFFIC_PARKINGSPACENOPARKING Data Block Description
    /// </summary>
    public struct DEV_EVENT_TRAFFIC_PARKINGSPACENOPARKING_INFO
    {
      /// <summary>
        /// Channel Number
        /// </summary>
	    public Int32 nChannelID;
        /// <summary>
        /// Event Name
        /// public byte[]
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 128)]
	    public byte[] szName;
        /// <summary>
        /// Reserved Bytes
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 8)]
        public byte[]  bReserved1;    
        /// <summary>
        /// TimeStamp(ms)
        /// </summary>
	    public double PTS;
        /// <summary>
        /// Event Time
        /// </summary>
	    public NET_TIME_EX UTC;
        /// <summary>
        /// Event ID
        /// </summary>
	    public Int32 nEventID;
        /// <summary>
        /// Traffic Lane Number
        /// </summary>
	    public Int32 nLane;
        /// <summary>
        /// License Plate Info
        /// </summary>
	    public NET_MSG_OBJECT stuObject;
        /// <summary>
        /// Car Body Info
        /// </summary>
	    public NET_MSG_OBJECT stuVehicle;
        /// <summary>
        /// Event File Info
        /// </summary>
	    public NET_EVENT_FILE_INFO  stuFileInfo;
        /// <summary>
        /// Snap Sequence, e.g. 3,2,1,1: snap complete, 0: snap wrong exit
        /// </summary>
	    public Int32 nSequence;
        /// <summary>
        /// Event Action,0:Pulse Event,1:Event Start,2:Event End;
        /// </summary>
	    public byte bEventAction;
        /// <summary>
        /// Reserved Bytes
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 2)]
	    public byte[] byReserved;
        /// <summary>
        ///  Image Index
        /// </summary>
        public byte  byImageIndex;
        /// <summary>
        /// Snap Flag(bitwise),Please See NET_RESERVED_COMMON	
        /// </summary>
        public UInt32 dwSnapFlagMask;
        /// <summary>
        /// Pictrue Resolution
        /// </summary>
        public NET_RESOLUTION_INFO  stuResolution;
        /// <summary>
        /// Traffic Car Info
        /// </summary>                    
        public DEV_EVENT_TRAFFIC_TRAFFICCAR_INFO stTrafficCar;    
        /// <summary>
        /// Paring Info
        /// </summary>
        public DEV_TRAFFIC_PARKING_INFO stTrafficParingInfo;     
        /// <summary>
        /// Reserved Bytes
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 384)]
	    public byte[] bReserved; 
        /// <summary>
        /// Common Info
        /// </summary>
        public EVENT_COMM_INFO     stCommInfo;                                 // 公共信息

    }

    /// <summary>
    /// Event Type EVENT_IVS_TRAFFIC_PARKINGSPACEOVERLINE Data Block Description
    /// </summary>
    public struct DEV_EVENT_TRAFFIC_PARKINGSPACEOVERLINE_INFO
    {/// <summary>
        /// Channel Number
        /// </summary>
        public Int32 nChannelID;
        /// <summary>
        /// Event Name
        /// public byte[]
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 128)]
        public byte[] szName;
        /// <summary>
        /// TimeStamp(ms)
        /// </summary>
        public double PTS;
        /// <summary>
        /// Event Time
        /// </summary>
        public NET_TIME_EX UTC;
        /// <summary>
        /// Event ID
        /// </summary>
        public Int32 nEventID;
        /// <summary>
        /// Traffic Lane Number
        /// </summary>
        public Int32 nLane;
        /// <summary>
        /// License Plate Info
        /// </summary>
        public NET_MSG_OBJECT stuObject;
        /// <summary>
        /// Car Body Info
        /// </summary>
        public NET_MSG_OBJECT stuVehicle;
        /// <summary>
        /// Event File Info
        /// </summary>
        public NET_EVENT_FILE_INFO stuFileInfo;
        /// <summary>
        /// Snap Sequence, e.g. 3,2,1,1: snap complete, 0: snap wrong exit
        /// </summary>
        public Int32 nSequence;
        /// <summary>
        /// Event Action,0:Pulse Event,1:Event Start,2:Event End;
        /// </summary>
        public byte bEventAction;
        /// <summary>
        ///  Image Index
        /// </summary>
        public byte byImageIndex;
        /// <summary>
        /// Reserved Bytes
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 2)]
        public byte[] byReserved;
        /// <summary>
        /// Snap Flag(bitwise),Please See NET_RESERVED_COMMON	
        /// </summary>
        public UInt32 dwSnapFlagMask;
        /// <summary>
        /// Pictrue Resolution
        /// </summary>
        public NET_RESOLUTION_INFO stuResolution;
        /// <summary>
        /// Traffic Car Info
        /// </summary>                    
        public DEV_EVENT_TRAFFIC_TRAFFICCAR_INFO stTrafficCar;
        /// <summary>
        /// Paring Info
        /// </summary>
        public DEV_TRAFFIC_PARKING_INFO stTrafficParingInfo;
        /// <summary>
        /// Reserved Bytes
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 384)]
        public byte[] bReserved;
        /// <summary>
        /// Common Info
        /// </summary>
        public EVENT_COMM_INFO stCommInfo;                                 // 公共信息
    }

    /// <summary>
    /// Event Type EVENT_IVS_TRAFFIC_RETROGRADE(Traffic - Retrograde) Data Block Description
    /// </summary>
    public struct DEV_EVENT_TRAFFIC_RETROGRADE_INFO
    {
        /// <summary>
        /// Channel Number
        /// </summary>
	    public Int32 nChannelID;
        /// <summary>
        /// Event Name
        /// public byte[]
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 128)]
	    public byte[] szName;
        /// <summary>
        /// TimeStamp(ms)
        /// </summary>
	    public double PTS;
        /// <summary>
        /// Event Time
        /// </summary>
	    public NET_TIME_EX UTC;
        /// <summary>
        /// Event ID
        /// </summary>
	    public Int32 nEventID;
        /// <summary>
        /// Traffic Lane Number
        /// </summary>
	    public Int32 nLane;
        /// <summary>
        /// License Plate Info
        /// </summary>
	    public NET_MSG_OBJECT stuObject;
        /// <summary>
        /// Car Body Info
        /// </summary>
	    public NET_MSG_OBJECT stuVehicle;
        /// <summary>
        /// Event File Info
        /// </summary>
	    public NET_EVENT_FILE_INFO stuFileInfo;
        /// <summary>
        /// Snap Sequence, e.g. 3,2,1,1: snap complete, 0: snap wrong exit
        /// </summary>
	    public Int32 nSequence;
        /// <summary>
        /// Car Actual Speed,Km/h
        /// </summary>
	    public Int32 nSpeed;
        /// <summary>
        /// Event Action,0:Pulse Event,1:Event Start,2:Event End;
        /// </summary>
	    public byte bEventAction;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 3)]
	    public byte[] byReserved;
        /// <summary>
        /// Snap Flag(bitwise),Please See NET_RESERVED_COMMON	
        /// </summary>
        public UInt32 dwSnapFlagMask;
        /// <summary>
        /// Reserved Bytes
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 1008)]
	    public byte[] bReserved;
        /// <summary>
        /// Traffic Car Info
        /// </summary>
	    public DEV_EVENT_TRAFFIC_TRAFFICCAR_INFO stTrafficCar;

    }

    /// <summary>
    /// Event Type EVENT_IVS_TRAFFIC_TURNLEFT(Traffic - Turn Left) Data Block Description
    /// </summary>
    public struct DEV_EVENT_TRAFFIC_TURNLEFT_INFO
    {
        /// <summary>
        /// Channel Number
        /// </summary>
	    public Int32 nChannelID;
        /// <summary>
        /// Event Name
        /// public byte[]
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 128)]
	    public byte[] szName;
        /// <summary>
        /// TimeStamp(ms)
        /// </summary>
	    public double PTS;
        /// <summary>
        /// Event Time
        /// </summary>
	    public NET_TIME_EX UTC;
        /// <summary>
        /// Event ID
        /// </summary>
	    public Int32 nEventID;
        /// <summary>
        /// Traffic Lane Number
        /// </summary>
	    public Int32 nLane;
        /// <summary>
        /// License Plate Info
        /// </summary>
	    public NET_MSG_OBJECT stuObject;
        /// <summary>
        /// Car Body Info
        /// </summary>
	    public NET_MSG_OBJECT stuVehicle;
        /// <summary>
        /// Event File Info
        /// </summary>
	    public NET_EVENT_FILE_INFO stuFileInfo;
        /// <summary>
        /// Snap Sequence, e.g. 3,2,1,1: snap complete, 0: snap wrong exit
        /// </summary>
	    public Int32 nSequence;
        /// <summary>
        /// Car Actual Speed,Km/h
        /// </summary>
	    public Int32 nSpeed;
        /// <summary>
        /// Event Action,0:Pulse Event,1:Event Start,2:Event End;
        /// </summary>
	    public byte bEventAction;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 3)]
	    public byte[] byReserved;
        /// <summary>
        /// Snap Flag(bitwise),Please See NET_RESERVED_COMMON	
        /// </summary>
        public UInt32 dwSnapFlagMask;
        /// <summary>
        /// Reserved Bytes
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 1008)]
	    public byte[] bReserved;
        /// <summary>
        /// Traffic Car Info
        /// </summary>
	    public DEV_EVENT_TRAFFIC_TRAFFICCAR_INFO stTrafficCar;

    }


    /// <summary>
    /// Event Type EVENT_IVS_TRAFFIC_TURNRIGHT(Traffic -Turn Right) Data Block Description
    /// </summary>
    public struct DEV_EVENT_TRAFFIC_TURNRIGHT_INFO
    {
        /// <summary>
        /// Channel Number
        /// </summary>
	    public Int32 nChannelID;
        /// <summary>
        /// Event Name
        /// public byte[]
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 128)]
	    public byte[] szName;
        /// <summary>
        /// TimeStamp(ms)
        /// </summary>
	    public double PTS;
        /// <summary>
        /// Event Time
        /// </summary>
	    public NET_TIME_EX UTC;
        /// <summary>
        /// Event ID
        /// </summary>
	    public Int32 nEventID;
        /// <summary>
        /// Traffic Lane Number
        /// </summary>
	    public Int32 nLane;
        /// <summary>
        /// License Plate Info
        /// </summary>
	    public NET_MSG_OBJECT stuObject;
        /// <summary>
        /// Car Body Info
        /// </summary>
	    public NET_MSG_OBJECT stuVehicle;
        /// <summary>
        /// Event File Info
        /// </summary>
	    public NET_EVENT_FILE_INFO  stuFileInfo;
        /// <summary>
        /// Snap Sequence, e.g. 3,2,1,1: snap complete, 0: snap wrong exit
        /// </summary>
	    public Int32 nSequence;
        /// <summary>
        /// Car Actual Speed,Km/h
        /// </summary>
	    public Int32 nSpeed;
        /// <summary>
        /// Event Action,0:Pulse Event,1:Event Start,2:Event End;
        /// </summary>
	    public byte bEventAction;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 3)]
	    public byte[] byReserved;
        /// <summary>
        /// Snap Flag(bitwise),Please See NET_RESERVED_COMMON	
        /// </summary>
        public UInt32 dwSnapFlagMask;
        /// <summary>
        /// Reserved Bytes
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 1008)]
	    public byte[] bReserved;
        /// <summary>
        /// Traffic Car Info
        /// </summary>
	    public DEV_EVENT_TRAFFIC_TRAFFICCAR_INFO stTrafficCar;
    } 

    /// <summary>
    /// Event Type EVENT_IVS_TRAFFIC_UTURN(Traffic Uturn) Data Block Description
    /// </summary>
    public struct DEV_EVENT_TRAFFIC_UTURN_INFO 
    {
        /// <summary>
        /// Channel Number
        /// </summary>
	    public Int32 nChannelID;
        /// <summary>
        /// Event Name
        /// public byte[]
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 128)]
	    public byte[] szName;
        /// <summary>
        /// TimeStamp(ms)
        /// </summary>
	    public double PTS;
        /// <summary>
        /// Event Time
        /// </summary>
	    public NET_TIME_EX UTC;
        /// <summary>
        /// Event ID
        /// </summary>
	    public Int32 nEventID;
        /// <summary>
        /// Traffic Lane Number
        /// </summary>
	    public Int32 nLane;
        /// <summary>
        /// Detected Objects
        /// </summary>
	    public NET_MSG_OBJECT stuObject;
        /// <summary>
        /// Car Body Info
        /// </summary>
	    public NET_MSG_OBJECT stuVehicle;
        /// <summary>
        /// Event File Info
        /// </summary>
	    public NET_EVENT_FILE_INFO  stuFileInfo;
        /// <summary>
        /// Snap Sequence, e.g. 3,2,1,1: snap complete, 0: snap wrong exit
        /// </summary>
	    public Int32 nSequence;
        /// <summary>
        /// Car Actual Speed,Km/h
        /// </summary>
	    public Int32 nSpeed;
        /// <summary>
        /// Event Action,0:Pulse Event,1:Event Start,2:Event End;
        /// </summary>
	    public byte bEventAction;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 3)]
	    public byte[] byReserved;
        /// <summary>
        /// Snap Flag(bitwise),Please See NET_RESERVED_COMMON	
        /// </summary>
        public UInt32 dwSnapFlagMask;
        /// <summary>
        /// Reserved Bytes
        /// </summary>
    	[MarshalAs(UnmanagedType.ByValArray, SizeConst = 1008)]
	    public byte[] bReserved;
        /// <summary>
        /// Traffic Car Info
        /// </summary>
	    public DEV_EVENT_TRAFFIC_TRAFFICCAR_INFO stTrafficCar;
    }

    /// <summary>
    /// Event Type EVENT_IVS_TRAFFIC_OVERSPEED(Traffic Overspeed) Data Block Description
    /// </summary>
    public struct DEV_EVENT_TRAFFIC_OVERSPEED_INFO 
    {
        /// <summary>
        /// Channel Number
        /// </summary>
	    public Int32 nChannelID;
        /// <summary>
        /// Event Name
        /// public byte[]
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 128)]
	    public byte[] szName;
        /// <summary>
        /// TimeStamp(ms)
        /// </summary>
	    public double PTS;
        /// <summary>
        /// Event Time
        /// </summary>
	    public NET_TIME_EX UTC;
        /// <summary>
        /// Event ID
        /// </summary>
	    public Int32 nEventID;
        /// <summary>
        /// Traffic Lane Number
        /// </summary>
	    public Int32 nLane;
        /// <summary>
        /// Detected Objects
        /// </summary>
	    public NET_MSG_OBJECT stuObject;
        /// <summary>
        /// Car Body Info
        /// </summary>
	    public NET_MSG_OBJECT stuVehicle;
        /// <summary>
        /// Event File Info
        /// </summary>
	    public NET_EVENT_FILE_INFO  stuFileInfo;
        /// <summary>
        /// Car Actual SpeedKm/h
        /// </summary>
        public Int32 nSpeed;
        /// <summary>
        /// Speed Upper Limit unit：km/h
        /// </summary>
	    public Int32 nSpeedUpperLimit;
        /// <summary>
        /// Speed Lower Limit unit：km/h 
        /// </summary>
	    public Int32 nSpeedLowerLimit;
        /// <summary>
        /// Snap Sequence, e.g. 3,2,1,1: snap complete, 0: snap wrong exit
        /// </summary>
	    public Int32 nSequence;
        /// <summary>
        /// Event Action,0:Pulse Event,1:Event Start,2:Event End;	
        /// </summary>
	    public byte bEventAction;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 3)]
	    public byte[] byReserved;
        /// <summary>
        /// Snap Flag(bitwise),Please See NET_RESERVED_COMMON	
        /// </summary>
        public UInt32 dwSnapFlagMask;
        /// <summary>
        /// Reserved Bytes
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 1012)]
	    public byte[] bReserved;
        /// <summary>
        /// Traffic Car Info
        /// </summary>
	    public DEV_EVENT_TRAFFIC_TRAFFICCAR_INFO stTrafficCar;
    }

    
    /// <summary>
    /// Event Type EVENT_IVS_TRAFFIC_UNDERSPEED(Traffic Under speed ) Data Block Description
    /// </summary>
    public struct DEV_EVENT_TRAFFIC_UNDERSPEED_INFO 
    {
        /// <summary>
        /// Channel Number
        /// </summary>
	    public Int32 nChannelID;
        /// <summary>
        /// Event Name
        /// public byte[]
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 128)]
	    public byte[] szName;
        /// <summary>
        /// TimeStamp(ms)
        /// </summary>
	    public double PTS;
        /// <summary>
        /// Event Time
        /// </summary>
	    public NET_TIME_EX UTC;
        /// <summary>
        /// Event ID
        /// </summary>
	    public Int32 nEventID;
        /// <summary>
        /// Traffic Lane Number
        /// </summary>
	    public Int32 nLane;
        /// <summary>
        /// Detected Objects
        /// </summary>
	    public NET_MSG_OBJECT stuObject;
        /// <summary>
        /// Car Body Info
        /// </summary>
	    public NET_MSG_OBJECT stuVehicle;
        /// <summary>
        /// Event File Info
        /// </summary>
	    public NET_EVENT_FILE_INFO  stuFileInfo;
        /// <summary>
        /// Car Actual SpeedKm/h
        /// </summary>
        public Int32 nSpeed;
        /// <summary>
        /// Speed Upper Limit    km/h
        /// </summary>
	    public Int32 nSpeedUpperLimit;
        /// <summary>
        /// Speed Lower Limit    km/h 
        /// </summary>
	    public Int32 nSpeedLowerLimit;
        /// <summary>
        /// Snap Sequence, e.g. 3,2,1,1: snap complete, 0: snap wrong exit
        /// </summary>
	    public Int32 nSequence;
        /// <summary>
        /// Event Action,0:Pulse Event,1:Event Start,2:Event End;
        /// </summary>
	    public byte bEventAction;
        /// <summary>
        /// Aligned
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 3)]
        public byte[] bReserved1;
        /// <summary>
        /// Under Speeding Percentage
        /// </summary>
	    public Int32 nUnderSpeedingPercentage;
        /// <summary>
        /// Snap Flag(bitwise),Please See NET_RESERVED_COMMON	
        /// </summary>
        public UInt32 dwSnapFlagMask;
        /// <summary>
        /// Reserved Bytes
        /// </summary>
    	[MarshalAs(UnmanagedType.ByValArray, SizeConst = 1008)]
	    public byte[] bReserved;
        /// <summary>
        /// Traffic Car Info
        /// </summary>
	    public DEV_EVENT_TRAFFIC_TRAFFICCAR_INFO stTrafficCar;

    }

    /// <summary>
    /// Event Type EVENT_IVS_TRAFFIC_PARKING(Traffic Parking) Data Block Description
    /// </summary>
    public struct DEV_EVENT_TRAFFIC_PARKING_INFO 
    {
        /// <summary>
        /// Channel Number
        /// </summary>
	    public Int32 nChannelID;
        /// <summary>
        /// Event Name
        /// public byte[]
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 128)]
	    public byte[] szName;
        /// <summary>
        /// TimeStamp(ms)
        /// </summary>
	    public double PTS;
        /// <summary>
        /// Event Time
        /// </summary>
	    public NET_TIME_EX UTC;
        /// <summary>
        /// Event ID
        /// </summary>
	    public Int32 nEventID;
        /// <summary>
        /// Detected Objects
        /// </summary>
	    public NET_MSG_OBJECT stuObject;
        /// <summary>
        /// Car Body Info
        /// </summary>
	    public NET_MSG_OBJECT stuVehicle;
        /// <summary>
        /// Traffic Lane Number
        /// </summary>
	    public Int32 nLane;
        /// <summary>
        /// Event File Info               
        /// </summary>
	    public NET_EVENT_FILE_INFO  stuFileInfo;
        /// <summary>
        /// Event Action,0:Pulse Event,1:Event Start,2:Event End;
        /// </summary>
	    public byte bEventAction;
        /// <summary>
        /// Reserved Bytes
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 3)]
	    public byte[] reserved;
        /// <summary>
        /// Start Parking Time
        /// </summary>
	    public NET_TIME_EX stuStartParkingTime;
        /// <summary>
        /// Snap Sequence, e.g. 3,2,1,1: snap complete, 0: snap wrong exit  ( parameters effective 			  when bEventAction=2)
        /// </summary>
	    public Int32 nSequence;
        /// <summary>
        /// Alarm interval, unit: m.( This is persistent event, after receiving the first, 
        /// if waiting time exceeds the interval, this event will be thought wrong abort)        
        /// </summary>
	    public Int32 nAlarmIntervalTime;
        /// <summary>
        /// Parking Permit Duration,unit:m
        /// </summary>
	    public Int32 nParkingAllowedTime;
        /// <summary>
        /// Detection Region Vertices
        /// </summary>
	    public Int32 nDetectRegionNum;
        /// <summary>
        /// Detection Region
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 20)]
	    public NET_POINT[] DetectRegion;
        /// <summary>
        /// Snap Flag(bitwise),Please See NET_RESERVED_COMMON	
        /// </summary>
        public UInt32 dwSnapFlagMask;
        /// <summary>
        /// Reserved Bytes,to be Developed..
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 924)]
	    public byte[] bReserved;
        /// <summary>
        /// Traffic Car Info
        /// </summary>
	    public DEV_EVENT_TRAFFIC_TRAFFICCAR_INFO stTrafficCar;
    	
    }

    /// <summary>
    /// Event Type EVENT_IVS_TRAFFICJAM(Traffic Jam) Data Block Description
    /// </summary>
    public struct DEV_EVENT_TRAFFICJAM_INFO 
    {
        /// <summary>
        /// Channel Number
        /// </summary>
	    public Int32 nChannelID;
        /// <summary>
        /// Event Name
        /// public byte[]
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 128)]
	    public byte[] szName;
        /// <summary>
        /// TimeStamp(ms)
        /// </summary>
	    public double PTS;
        /// <summary>
        /// Event Time
        /// </summary>
	    public NET_TIME_EX UTC;
        /// <summary>
        /// Event ID
        /// </summary>
	    public Int32 nEventID;
        /// <summary>
        /// Traffic Lane Number
        /// </summary>
	    public Int32 nLane;
        /// <summary>
        /// Event File Info               
        /// </summary>
	    public NET_EVENT_FILE_INFO  stuFileInfo;
        /// <summary>
        /// Event Action,0:Pulse Event,1:Event Start,2:Event End; 
        /// </summary>
	    public byte bEventAction;
        /// <summary>
        /// Reserved Bytes
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 3)]
	    public byte[] reserved;
        /// <summary>
        /// start time for stop
        /// </summary>
	    public NET_TIME_EX stuStartJamTime;
        /// <summary>
        /// Snap Sequence, e.g. 3,2,1,1: snap complete, 0: snap wrong exit (parameters effective 		    ///when bEventAction=2)
        /// </summary>
	    public Int32 nSequence;
        /// <summary>
        /// Alarm interval, unit: m.( This is persistent event, after receiving the first,
        /// if waiting time exceeds the interval, this event will be thought wrong abort)
        /// </summary>
	    public Int32 nAlarmIntervalTime;
        /// <summary>
        /// Snap Flag(bitwise),Please See NET_RESERVED_COMMON	
        /// </summary>
        public UInt32 dwSnapFlagMask;
        /// <summary>
        /// Reserved Bytes,to be Developed..
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 1012)]
	    public byte[] bReserved;
        /// <summary>
        /// Traffic Car Info	
        /// </summary>
	    public DEV_EVENT_TRAFFIC_TRAFFICCAR_INFO stTrafficCar;
    }

    /// <summary>
    /// Event Type EVENT_IVS_TRAFFIC_WRONGROUTE(Traffic - Wrong Route) Data Block Description
    /// </summary>
    public struct DEV_EVENT_TRAFFIC_WRONGROUTE_INFO 
    {
        /// <summary>
        /// Channel Number
        /// </summary>
	    public Int32 nChannelID;
        /// <summary>
        /// Event Name
        /// public byte[]
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 128)]
	    public byte[] szName;
        /// <summary>
        /// TimeStamp(ms)
        /// </summary>
	    public double PTS;
        /// <summary>
        /// Event Time
        /// </summary>
	    public NET_TIME_EX UTC;
        /// <summary>
        /// Event ID
        /// </summary>
	    public Int32 nEventID;
        /// <summary>
        /// Detected Objects
        /// </summary>
	    public NET_MSG_OBJECT stuObject;
        /// <summary>
        /// Car Body Info
        /// </summary>
	    public NET_MSG_OBJECT stuVehicle;
        /// <summary>
        /// Traffic Lane Number
        /// </summary>
	    public Int32 nLane;
        /// <summary>
        /// Event File Info               
        /// </summary>
	    public NET_EVENT_FILE_INFO  stuFileInfo;
        /// <summary>
        /// Event Action,0:Pulse Event,1:Event Start,2:Event End;
        /// </summary>
	    public byte bEventAction;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 3)]
	    public byte[] byReserved;
        /// <summary>
        /// Car Actual Speed,km/h
        /// </summary>
	    public Int32 nSpeed;
        /// <summary>
        /// Snap Flag(bitwise),Please See NET_RESERVED_COMMON	
        /// </summary>
        public UInt32 dwSnapFlagMask;
        /// <summary>
        /// Reserved Bytes,to be Developed..
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 1012)]
	    public byte[] bReserved;
        /// <summary>
        /// Traffic Car Info
        /// </summary>
	    public DEV_EVENT_TRAFFIC_TRAFFICCAR_INFO stTrafficCar;

    }

    /// <summary>
    /// Event Type EVENT_IVS_TRAFFIC_CROSSLANE(Traffic - Cross Lane) Data Block Description
    /// </summary>
    public struct DEV_EVENT_TRAFFIC_CROSSLANE_INFO 
    {
        /// <summary>
        /// Channel Number
        /// </summary>
	    public Int32 nChannelID;
        /// <summary>
        /// Event Name
        /// public byte[]
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 128)]
	    public byte[] szName;
        /// <summary>
        /// TimeStamp(ms)
        /// </summary>
	    public double PTS;
        /// <summary>
        /// Event Time
        /// </summary>
	    public NET_TIME_EX UTC;
        /// <summary>
        /// Event ID
        /// </summary>
	    public Int32 nEventID;
        /// <summary>
        /// Detected Objects
        /// </summary>
	    public NET_MSG_OBJECT stuObject;
        /// <summary>
        /// Car Body Info
        /// </summary>
	    public NET_MSG_OBJECT stuVehicle;
        /// <summary>
        /// Traffic Lane Number
        /// </summary>
	    public Int32 nLane;
        /// <summary>
        /// Event File Info               
        /// </summary>
	    public NET_EVENT_FILE_INFO stuFileInfo;
        /// <summary>
        /// Event Action,0:Pulse Event,1:Event Start,2:Event End;
        /// </summary>
	    public byte bEventAction;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 3)]
	    public byte[] byReserved;           
        /// <summary>
        /// Car Actual Speed,km/h
        /// </summary>
	    public Int32 nSpeed;
        /// <summary>
        /// Snap Flag(bitwise),Please See NET_RESERVED_COMMON	 
        /// </summary>
        public UInt32 dwSnapFlagMask;
        /// <summary>
        /// Reserved Bytes,to be Developed..to be Developed..
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 1012)]
	    public byte[] bReserved;
    	
    }


    /// <summary>
    /// Event Type EVENT_IVS_TRAFFIC_OVERYELLOWLINE(Traffic - over Yellow Lane) Data Block Description
    /// </summary>
    public struct DEV_EVENT_TRAFFIC_OVERYELLOWLINE_INFO 
    {
        /// <summary>
        /// Channel Number
        /// </summary>
	    public Int32 nChannelID;
        /// <summary>
        /// Event Name
        /// public byte[]
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 128)]
	    public byte[] szName;
        /// <summary>
        /// TimeStamp(ms)
        /// </summary>
	    public double PTS;
        /// <summary>
        /// Event Time
        /// </summary>
	    public NET_TIME_EX UTC;
        /// <summary>
        /// Event ID
        /// </summary>
	    public Int32 nEventID;
        /// <summary>
        /// Detected Objects
        /// </summary>
	    public NET_MSG_OBJECT stuObject;
        /// <summary>
        /// Car Body Info
        /// </summary>
	    public NET_MSG_OBJECT stuVehicle;
        /// <summary>
        /// Traffic Lane Number
        /// </summary>
	    public Int32 nLane;
        /// <summary>
        /// Event File Info               
        /// </summary>
	    public NET_EVENT_FILE_INFO  stuFileInfo;
        /// <summary>
        /// Event Action,0:Pulse Event,1:Event Start,2:Event End;
        /// </summary>
	    public byte bEventAction;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 3)]
	    public byte[] byReserved;
        /// <summary>
        /// Car Actual Speed,km/h
        /// </summary>
	    public Int32 nSpeed;
        /// <summary>
        /// Snap Flag(bitwise),Please See NET_RESERVED_COMMON	
        /// </summary>
        public UInt32 dwSnapFlagMask;
        /// <summary>
        /// Reserved Bytes,to be Developed..
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 1012)]
	    public byte[] bReserved;
        /// <summary>
        /// Traffic Car Info
        /// </summary>
	    public DEV_EVENT_TRAFFIC_TRAFFICCAR_INFO stTrafficCar;
    	
    }

    /// <summary>
    /// Event Type EVENT_IVS_TRAFFIC_DRIVINGONSHOULDER(Traffic - Driving on Road 	///Shoulder ) Data Block Description
    /// </summary>
    public struct DEV_EVENT_TRAFFIC_DRIVINGONSHOULDER_INFO
    {
        /// <summary>
        /// Channel Number
        /// </summary>
	    public Int32 nChannelID; 
        /// <summary>
        /// Event Name
        /// public byte[]
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 128)]
	    public byte[] szName;
        /// <summary>
        /// TimeStamp(ms)
        /// </summary>
	    public double PTS;
        /// <summary>
        /// Event Time
        /// </summary>
	    public NET_TIME_EX UTC;
        /// <summary>
        /// Event ID
        /// </summary>
	    public Int32 nEventID;
        /// <summary>
        /// Detected Objects
        /// </summary>
	    public NET_MSG_OBJECT stuObject;
        /// <summary>
        /// Car Body Info
        /// </summary>
	    public NET_MSG_OBJECT stuVehicle;
        /// <summary>
        /// Traffic Lane Number
        /// </summary>
	    public Int32 nLane;
        /// <summary>
        /// Event File Info               
        /// </summary>
	    public NET_EVENT_FILE_INFO  stuFileInfo;
        /// <summary>
        /// Event Action,0:Pulse Event,1:Event Start,2:Event End;
        /// </summary>
	    public byte bEventAction;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 3)]
	    public byte[] byReserved;
        /// <summary>
        /// Car Actual Speed,km/h
        /// </summary>
	    public Int32 nSpeed;
        /// <summary>
        /// Snap Flag(bitwise),Please See NET_RESERVED_COMMON	
        /// </summary>
        public UInt32 dwSnapFlagMask;
        /// <summary>
        /// Reserved Bytes,to be Developed..
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 1012)]
	    public byte[] bReserved;
    	
    }

    /// <summary>
    /// Event Type EVENT_IVS_TRAFFIC_YELLOWPLATEINLANE(Traffic - Yellow Plate in 	///Lane) Data Block Description
    /// </summary>
    public struct DEV_EVENT_TRAFFIC_YELLOWPLATEINLANE_INFO
    {
        /// <summary>
        /// Channel Number
        /// </summary>
	    public Int32 nChannelID;
        /// <summary>
        /// Event Name
        /// public byte[]
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 128)]
	    public byte[] szName;
        /// <summary>
        /// TimeStamp(ms)
        /// </summary>
	    public double PTS;
        /// <summary>
        /// Event Time
        /// </summary>
	    public NET_TIME_EX UTC;
        /// <summary>
        /// Event ID
        /// </summary>
	    public Int32 nEventID;
        /// <summary>
        /// Detected Objects
        /// </summary>
	    public NET_MSG_OBJECT stuObject;
        /// <summary>
        /// Car Body Info
        /// </summary>
	    public NET_MSG_OBJECT stuVehicle;
        /// <summary>
        /// Traffic Lane Number
        /// </summary>
	    public Int32 nLane;
        /// <summary>
        /// Event File Info               
        /// </summary>
	    public NET_EVENT_FILE_INFO  stuFileInfo;
        /// <summary>
        /// Event Action,0:Pulse Event,1:Event Start,2:Event End;
        /// </summary>
	    public byte bEventAction;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 3)]
	    public byte[] byReserved;
        /// <summary>
        /// Car Actual Speed,km/h
        /// </summary>
	    public Int32 nSpeed;
        /// <summary>
        /// Snap Flag(bitwise),Please See NET_RESERVED_COMMON	
        /// </summary>
        public UInt32 dwSnapFlagMask;
        /// <summary>
        /// Reserved Bytes,to be Developed..
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 1020)]
	    public byte[] bReserved;
        /// <summary>
        /// Traffic Car Info
        /// </summary>
	    public DEV_EVENT_TRAFFIC_TRAFFICCAR_INFO stTrafficCar;
    	
    }

    /// <summary>
    /// Event Type  EVENT_IVS_FIREDETECTION(Fire Detection) Data Block Description
    /// </summary>
    public struct DEV_EVENT_ELECTROSPARK_INFO 
    {
        /// <summary>
        /// ChannelId
        /// </summary>
	    public Int32 nChannelID;
        /// <summary>
        /// event name
        /// public byte[]
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 128)]
	    public byte[] szName;
        /// <summary>
        /// PTS(ms)
        /// </summary>
	    public double PTS;
        /// <summary>
        /// the event happen time
        /// </summary>
	    public NET_TIME_EX UTC;
        /// <summary>
        /// event ID
        /// </summary>
	    public Int32 nEventID;
        /// <summary>
        /// have being detected object
        /// </summary>
	    public NET_MSG_OBJECT stuObject;
        /// <summary>
        /// event file info
        /// </summary>
	    public NET_EVENT_FILE_INFO  stuFileInfo;
        /// <summary>
        /// Event action,0 means pulse event,1 means continuous event's begin,2means continuous event's end;
        /// </summary>
	    public byte bEventAction;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 3)]
	    public byte[] byReserved;
        /// <summary>
        /// Snap Flag(bitwise),Please See NET_RESERVED_COMMON	
        /// </summary>
        public UInt32 dwSnapFlagMask;
        //reserved
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 972)]
	    public byte[] bReserved;
    	
    }

    #endregion

    #region <<CtrlType Enumeration Structures>>

    /// <summary>
    /// Manual Snap Parameter
    /// </summary>
    public struct MANUAL_SNAP_PARAMETER
    {
        /// <summary>
        /// Snap Channel , start from 0
        /// </summary>
        public Int32 nChannel;
        /// <summary>
        /// Snap Sequence Character String
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 64)]
        public byte[] bySequence;
        /// <summary>
        /// Reserved Field
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 60)]
        public byte[] byReserved;
    }

    /// <summary>
    /// Slipt Parameter for Device Local Preview
    /// </summary>
    public struct DEVICE_LOCALPREVIEW_SLIPT_PARAMETER
    {
        /// <summary>
        /// Split Mode, Please see split modes supported by device local preview
        /// </summary>
        public Int32 nSliptMode;
        /// <summary>
        /// Sub Split preview ,start from 1
        /// </summary>
        public Int32 nSubSliptNum;
        /// <summary>
        /// Reserved Field
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 64)]
        public byte[] byReserved;
    }

    public struct WIFI_CONNECT
    {
        /// <summary>
        /// SSID
        /// public byte[]
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 128)]
        public byte[] szSSID;
        /// <summary>
        /// Reserved Bytes
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 256)]
        public byte[] bReserved;
    };

    /// <summary>
    /// Harddisk Operation
    /// </summary>
    public struct DISKCTRL_PARAM
    {
        /// <summary>
        /// Structure Size, for version control
        /// </summary>
	    public UInt32 dwSize; 
        /// <summary>
        /// Array stDisks in Hard disk info structure DH_HARDDISK_STATE,start from 0
        /// </summary>
	    public Int32 nIndex;
        /// <summary>
        /// Operation Mode,
        /// 0 - delete data, 1 - set to read-and-write disk, 2 - set to read-only disk
        /// 3 - set to redundant disk , 4 - recover error, 5 - set to snap disk,7 - eject SD card
        /// </summary>
	    public Int32 ctrlType;
        /// <summary>
        /// Disk Info, substitute for disk index because the disk sequence may change
        /// </summary>
	    NET_DEV_DISKSTATE	stuDisk;
    }

    public struct  DISKCTRL_SUBAREA
    {
        /// <summary>
        /// Number of pre-subarea
        /// </summary>
	    public byte bSubareaNum;
        /// <summary>
        /// Index of  Array “stDisks” in Harddisk info structure DH_HARDDISK_STATE
        /// </summary>
	    public byte bIndex;
        /// <summary>
        /// Partition Size（%）
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 32)]
	    public byte[] bSubareaSize;
        /// <summary>
        /// Reserved
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 30)]
	    public byte[] bReserved; 
    }

    /// <summary>
    /// Alarm State
    /// </summary>
    public struct ALARMCTRL_PARAM
    {
	    public UInt32 dwSize;
        /// <summary>
        /// Alarm Channel Number,start from 0
        /// </summary>
	    public Int32 nAlarmNo; 
        /// <summary>
        ///  1：trigger alarm,0：stop alarm
        /// </summary>
	    public Int32 nAction;
    }

    /// <summary>
    /// Matrix Control
    /// </summary>
    public struct MATRIXCTRL_PARAM
    {
	    public UInt32 dwSize;
        /// <summary>
        /// Video Channel Number,start from 0
        /// </summary>
	    public Int32 nChannelNo;
        /// <summary>
        /// Matrix out Number,start from 0
        /// </summary>
	    public Int32 nMatrixNo;
    }
 
    /// <summary>
    /// Disk Burning Control
    /// </summary>
    public struct BURNNG_PARM
    {
        /// <summary>
        /// Channel Mask, bitwise stand for burning channel
        /// </summary>
	    public Int32 channelMask;
        /// <summary>
        /// disk writer mask, bitwise stand for writers in writer list
        /// </summary>
	    public byte devMask;
        /// <summary>
        /// picture in picture channel (channel number +32)
        /// </summary>
	    public byte bySpicalChannel;
        /// <summary>
        /// Reserved Field
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 2)]
	    public byte[] byReserved; 
    }

    /// <summary>
    /// attach burning
    /// </summary>
    public struct BURNING_PARM_ATTACH
    {
        /// <summary>
        /// do attach burning or not,0:no; 1:yes
        /// </summary>
	    public Int32 bAttachBurn;
        /// <summary>
        /// Reserved Field
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 12)]
	    public byte[] bReserved; 
    } 

    /// <summary>
    /// trigger snap , and add card info
    /// </summary>
    public struct NET_SNAP_COMMANDINFO 
    {
        /// <summary>
        /// card number info
        /// public byte[]
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 16)]
	    public byte[] szCardInfo;
        /// <summary>
        /// reserved
        /// public byte[]
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 64)]
	    public byte[] reserved;
    }

    public struct  BACKUP_RECORD
    {
        /// <summary>
        /// backup device name
        /// public byte[]
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 32)]
	    public byte[] szDeviceName;
        /// <summary>
        /// number of backup record
        /// </summary>
	    public Int32 nRecordNum;
        /// <summary>
        /// backup record info
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 1024)]
	    public NET_RECORDFILE_INFO[]	stuRecordInfo;
    } 

    public struct NETDEV_VEHICLE_WIFI_CONFIG
    {
        /// <summary>
        /// SSID
        /// public byte[]
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 128)]
	    public byte[] szSSID;
        /// <summary>
        /// Priority Level,(1-32)
        /// </summary>
        public int nPriority;
        /// <summary>
        /// ctype
        /// 0:OPEN 
        /// 1:RESTRICTE
        /// 2:WEP
        /// 3:WPA
        /// 4:WPA2
        /// 5:WPA-PSK
        /// 6:WPA2-PSK
        /// </summary>
	    public int nSafeType;
        /// <summary>
        /// encryption mode
        /// 0:OPEN
        /// 1:TKIP
        /// 2:WEP
        /// 3:AES
        /// 4:NONE(do not check)
        /// </summary>
	    public int nEncryprion;
        /// <summary>
        /// connect secret key
        /// public byte[]
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 128)]
	    public byte[] szKey;
        /// <summary>
        /// host ip
        /// public byte[]
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 128)]
	    public byte[]	szHostIP;
        /// <summary>
        /// host mask
        /// public byte[]
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 128)]
	    public byte[]	szHostNetmask;
        /// <summary>
        /// host gateway
        /// public byte[]
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 128)]
	    public byte[]	szHostGateway;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 1024)]
	    public byte[]	bReserved;
    } 

    public struct NETDEV_USER_REJECT_INFO
    {
        /// <summary>
        /// ip
        /// public byte[]
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 16)]
        public byte[] szIpAddress;
        /// <summary>
        /// User Group
        /// public byte[]
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 32)]
	    public byte[] szUserGroup;
        /// <summary>
        /// User Name
        /// public byte[]
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 32)]
	    public byte[] szUserName;
        /// <summary>
        /// type in c++ is public byte[]
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 64)]
	    public byte[] reserved;
    }

    /// <summary>
    /// delete user
    /// </summary>
    public struct NETDEV_REJECT_USER
    { 
        /// <summary>
        /// User Count
        /// </summary>
	    public Int32 nUserCount; 
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 10)]
	    public NETDEV_USER_REJECT_INFO[] stuUserInfo;
        /// <summary>
        /// type in c++ is public byte[]
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 256)]
	    public byte[] reserved;
    }

    public struct NETDEV_USER_SHIELD_INFO
    {
        /// <summary>
        /// ip Address
        /// public byte[]
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 16)]
	    public byte[] szIpAddress;
        /// <summary>
        /// User Group
        /// public byte[]
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 32)]
	    public byte[] szUserGroup;
        /// <summary>
        /// User ID
        /// public byte[]
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 32)]
	    public byte[] szUserName;
        /// <summary>
        /// forbidden time
        /// public byte[]
        /// </summary>
	    public Int32 nForbiddenTime;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 64)]
	    public byte[] reserved;
    }

    /// <summary>
    /// shield user
    /// </summary>
    public struct NETDEV_SHIELD_USER
    { 
        /// <summary>
        /// User Count
        /// </summary>
	    public Int32 nUserCount; 
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 10)]
	    public NETDEV_USER_SHIELD_INFO[] stuUserInfo;     
        /// <summary>
        /// type in c++ is public byte[]
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 256)]
	    public byte[] reserved;
    }

    /// <summary>
    /// send event to device
    /// </summary>
    public struct NET_NOTIFY_EVENT_DATA
    {
        /// <summary>
        /// Struct Size
        /// </summary>
        public UInt32 dwSize;
        /// <summary>
        /// event type
        /// </summary>
        public UInt32 lCommand;
        /// <summary>
        /// event content,and lCommandcorresponding to structure indicator
        /// </summary>
        public IntPtr pEventData;
    }

            // 车位预定状态
    public enum EM_NET_ORDER_STATE
    {
        EM_NET_ORDER_STATE_UNKNOWN,
        EM_NET_ORDER_STATE_FREE,                            // 空闲Free
        EM_NET_ORDER_STATE_ORDERED,                         // 预定Ordered
    }

    // 车位预定状态信息
    public struct NET_ORDER_STATE_INFO
    {
        /// <summary>
        /// Struct Size
        /// </summary>
        public UInt32       dwSize;

        /// <summary>
        /// Lane Number
        /// </summary>
        public UInt32        nLane;               

        /// <summary>
        /// Order State
        /// </summary>
       public EM_NET_ORDER_STATE  emOrderState;                   // 预定情况
    }

    /// <summary>
    /// set order state
    /// </summary>
    public struct NET_CTRL_SET_ORDER_STATE
    {
        /// <summary>
        /// Struct Size
        /// </summary>
        public UInt32 dwSize;

        /// <summary>
        /// Order State(NET_ORDER_STATE_INFO)
        /// </summary>
        public IntPtr pOrderState; 

        /// <summary>
        /// Order State Number
        /// </summary>
        public UInt32  nStateCount;
    }

    #endregion

    #region <<structure--instructions in function set --- CLIENT_QueryNewSystemInfo>>


    // scene support rule
    public struct SCENE_SUPPORT_RULE
    {
        /// <summary>
        /// rule type
        /// </summary>
	    public UInt32 dwSupportedRule;
        /// <summary>
        /// number of detected objects type supported by current rule
        /// </summary>
	    public Int32 nSupportedObjectTypeNum;
        /// <summary>
        /// detected objects type list supported by current rule
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 16 * 32)]
	    public byte[] szObjectTypeName;
        /// <summary>
        /// number of detected objects action supported by current rule
        /// </summary>
	    public int nSupportedActionsNum;
        /// <summary>
        /// detected objects action list supported by current rule
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 16 * 32)]
	    public byte[] szSupportedActions;
        /// <summary>
        /// number of detection type supported by the current rule
        /// </summary>
	    public Int32 nSupportedDetectTypeNum;
        /// <summary>
        /// detectection type list supported by current rule
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 16 * 32)]
	    public byte[] szSupportedDetectTypes; 
    }

    /// <summary>
    /// funcitons of calibrated area
    /// </summary>
    public struct CFG_CAP_CELIBRATE_AREA
    {
        /// <summary>
        /// calibrated area type
        /// </summary>
	    public EM_CALIBRATEAREA_TYPE  emType;
        /// <summary>
        /// max number of horizontal staff supported
        /// </summary>
        public byte byMaxHorizontalStaffNum;
        /// <summary>
        /// minimum number of horizontal staff supported
        /// </summary>
        public byte byMinHorizontalStaffNum;
        /// <summary>
        /// max number of vertical staff supported
        /// </summary>
        public byte byMaxVerticalStaffNum;
        /// <summary>
        /// minimum number of vertical staff supported
        /// </summary>
        public byte byMinVerticalStaffNum;
    }

    /// <summary>
    /// scene ability
    /// </summary>
    public struct CFG_CAP_SCENE
    {
        /// <summary>
        /// scene name
        /// public byte[]
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 260)]
	    public byte[] szSceneName; 
        /// <summary>
        /// number of detected objects type supported by current rule
        /// </summary>
	    public Int32 nSupportedObjectTypeNum;
        /// <summary>
        /// detected objects type list supported by current rule
        /// public byte[]
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 16 * 32)]
	    public byte[] szObjectTypeName;
        /// <summary>
        /// number of rules supported
        /// </summary>
	    public Int32 nSupportRules;
        /// <summary>
        /// rule list supported
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 128)]
	    public SCENE_SUPPORT_RULE[] stSpportRules;

	    /// supported module parameter
        /// <summary>
        /// support disturbance setting or not
        /// </summary>
	    public byte bDisturbance;
        /// <summary>
        /// support anti-disturbance setting or not
        /// </summary>
	    public byte bAntiDisturbance;
        /// <summary>
        /// support backlight processing or not
        /// </summary>
	    public byte bBacklight;
        /// <summary>
        /// support shadow processing or not
        /// </summary>
	    public byte bShadow;
        /// <summary>
        /// support accuracy detection or not
        /// </summary>
	    public byte bAccuracy;
        /// <summary>
        /// support movingstep detection or not
        /// </summary>
	    public byte bMovingStep;
        /// <summary>
        /// support scaling detection or not
        /// </summary>
	    public byte bScalingFactor;
        /// <summary>
        /// support Y threshold or not
        /// </summary>
	    public byte bThresholdY;
        /// <summary>
        /// support UV threshold or not
        /// </summary>
	    public byte bThresholdUV;
        /// <summary>
        /// support threshold of edge detection or not
        /// </summary>
	    public byte bThresholdEdge;
        /// <summary>
        /// support balance detection or not
        /// </summary>
	    public byte bDetectBalance;
        /// <summary>
        /// support algorithm index or not
        /// </summary>
	    public byte bAlgorithmIndex;
        /// <summary>
        /// support highlight processing or not,i.e. Parameter Backgroud 
        /// </summary>
	    public byte bHighlight;
        /// <summary>
        /// support object snapshot or not
        /// </summary>
	    public byte bSnapshot;

	    /// supported scene parameter
        /// <summary>
        /// support camera aspect or not
        /// </summary>
	    public byte bCameraAspect;
        /// <summary>
        /// support jitter parameter or not
        /// </summary>
	    public byte bJitter;
        /// <summary>
        /// support Dejitter parameter or not
        /// </summary>
	    public byte bDejitter;

	    // supported calibrated funcitons set
        /// <summary>
        /// max number of calibrated area
        /// </summary>
	    public int nMaxCalibrateAreaNum;
        /// <summary>
        /// number of funcitons info in calibrated area
        /// </summary>
	    public int nCalibrateAreaNum;
        /// <summary>
        /// funcitons info of calibrated area
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 4)]
	    public CFG_CAP_CELIBRATE_AREA[] stCalibrateAreaCap;

    };


    /// <summary>
    /// scene list
    /// </summary>
    public struct CFG_VACAP_SUPPORTEDSCENES
    {
        /// <summary>
        /// number of supported scenes 
        /// </summary>
	    public Int32 nScenes;
        /// <summary>
        /// supported scene list
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 32)]
	    public CFG_CAP_SCENE[] stScenes;
    }


    public struct DEVICE_STATUS
    {
        /// <summary>
        /// remote device name
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 32)]
	    public byte[]szDeviceName;
        /// <summary>
        /// remote device state  0：offline 1：online
        /// </summary>
	    public byte	bDeviceStatus;
        /// <summary>
        /// Reserved Bytes
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 63)]
	    public byte[] bReserved;
    }


    public struct CFG_REMOTE_DEVICE_STATUS
    {
        /// <summary>
        /// device state
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 64)]
	    public DEVICE_STATUS[] devStatus;
        /// <summary>
        /// device count
        /// </summary>
	    public UInt32 dwDevCount;
        /// <summary>
        /// Reserved Bytes
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 1024)]
	    public byte[] bReserved;
    }

    /// <summary>
　　/// info of video analysis funcitons of the device
　　/// </summary>
    public struct CFG_CAP_DEVICE_ANALYSE_INFO
    {
        /// <summary>
        /// max number of channels which support intelligent video analysis
        /// </summary>
	    public Int32 nMaxChannels;
    }

    /// <summary>
    /// video input funcitons setting(CFG_CAP_CMD_VIDEOINPUT)
    /// </summary>
    public struct CFG_CAP_VIDEOINPUT_INFO
    {
        /// <summary>
        /// max number of metering regions
        /// </summary>
	    public Int32 nMeteringRegionCount;
    };


    /// <summary>
    /// time
    /// </summary>
    public struct CFG_NET_TIME
    {
	    Int32 nStructSize;
        /// <summary>
        /// year
        /// </summary>
	    UInt32 dwYear;
        /// <summary>
        /// month
        /// </summary>
        UInt32 dwMonth;
        /// <summary>
        /// day
        /// </summary>
        UInt32 dwDay;
        /// <summary>
        /// hour
        /// </summary>
        UInt32 dwHour;
        /// <summary>
        /// minute
        /// </summary>
        UInt32 dwMinute;
        /// <summary>
        /// second
        /// </summary>
        UInt32 dwSecond;
    }


    public struct CFG_ACTIVEUSER_INFO
    {
	    public Int32 nStructSize;
        /// <summary>
        /// active user ID,usually is session ID
        /// </summary>
	    public Int32 nUserID;
        /// <summary>
        /// User ID
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 64)]
	    public byte[] szUser;
        /// <summary>
        /// user’s group name 
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 64)]
	    public byte[] szGroupName;
        /// <summary>
        /// user’s group level
        /// </summary>
	    public int  nGroupLevel;
        /// <summary>
        /// client type
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 64)]
	    public byte[] szClientType;
        /// <summary>
        /// client IP address
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 256)]
	    public byte[] szClientAddr;
        /// <summary>
        /// user login time
        /// </summary>
	    public CFG_NET_TIME  stuLoginTime;
    };


    public struct CFG_NET_TIME_EX
    {
        /// <summary>
        /// year
        /// </summary>
	    public UInt32 dwYear;
        /// <summary>
        /// month
        /// </summary>
	    public UInt32 dwMonth;
        /// <summary>
        /// day
        /// </summary>
	    public UInt32 dwDay;
        /// <summary>
        /// hour
        /// </summary>
	    public UInt32 dwHour;
        /// <summary>
        /// minute
        /// </summary>
	    public UInt32 dwMinute;
        /// <summary>
        /// second
        /// </summary>
	    public UInt32 dwSecond;
        /// <summary>
        /// millisecond
        /// </summary>
	    public UInt32 dwMillisecond;
        /// <summary>
        /// Reserved Field
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 2)]
	    public UInt32[] dwReserved;
    }

    /// <summary>
    /// structure for getting video summary info 
    /// </summary>
    public struct CFG_VIDEOSATA_SUMMARY_INFO
    {
	    public Int32 nStructSize;
        /// <summary>
        /// channel count
        /// </summary>
        public Int32 nChannelID;
        /// <summary>
        /// rule name
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 32)]
        public byte[] szRuleName;
        /// <summary>
        /// time count,shift to UTC
        /// </summary>
        public CFG_NET_TIME_EX stuStatTime;
        /// <summary>
        /// enter total count
        /// </summary>
        public Int32 nEnteredTotal;
        /// <summary>
        /// enter total count today
        /// </summary>
        public Int32 nEnteredToday;
        /// <summary>
        /// enter total count this month
        /// </summary>
        public Int32 nEnteredMonth;
        /// <summary>
        /// enter total count this year
        /// </summary>
        public Int32 nEnteredYear;
        /// <summary>
        /// max enter daily
        /// </summary>
        public Int32 nEnteredDaily;
        /// <summary>
        /// exit total
        /// </summary>
        public Int32 nExitedTotal;
        /// <summary>
        /// exit total today
        /// </summary>
        public Int32 nExitedToday;
        /// <summary>
        /// exit total this month
        /// </summary>
        public Int32 nExitedMonth;
        /// <summary>
        /// exit total this year
        /// </summary>
        public Int32 nExitedYear;
        /// <summary>
        /// max exit total daily
        /// </summary>
        public Int32 nExitedDaily;
        /// <summary>
        /// average total(except 0)
        /// </summary>
        public Int32 nAvgTotal;
        /// <summary>
        /// average total today
        /// </summary>
        public Int32 nAvgToday;
        /// <summary>
        /// average total this month
        /// </summary>
        public Int32 nAvgMonth;
        /// <summary>
        /// average total this year         
        /// </summary>
        public Int32 nAvgYear;
        /// <summary>
        /// max total(except 0)
        /// </summary>
        public Int32 nMaxTotal;
        /// <summary>
        /// max total today
        /// </summary>
        public Int32 nMaxToday;
        /// <summary>
        /// max total this month
        /// </summary>
        public Int32 nMaxMonth;
        /// <summary>
        /// max total this year
        /// </summary>
        public Int32 nMaxYear;
    }

    // video diagnosis service set (CFG_CAP_CMD_VIDEODIAGNOSIS_SERVER)
    public struct CFG_VIDEODIAGNOSIS_CAPS_INFO
    {
        /// <summary>
        /// number of video diagnosis type supported
        /// </summary>
	    public Int32 nTypeCount;
        /// <summary>
        /// supported video diagnosis type
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 11 * 260)]
	    public byte[] szSupportedType;
        /// <summary>
        /// max number parameter list supported
        /// </summary>
	    public Int32 nMaxProfiles;
        /// <summary>
        /// max number of tasks
        /// </summary>
	    public Int32 nMaxTasks;
        /// <summary>
        /// max number of video sources for single task
        /// </summary>
	    public Int32 nMaxSourcesOfTask;
        /// <summary>
        /// max number for projects
        /// </summary>
	    public Int32 nMaxProjects;
    }

    #endregion

    #region <<structure--setting instructions CLIENT_GetNewDevConfig & CLIENT_SetNewDevConfig interface>>
    /// <summary>
    /// video format
    /// </summary>
    public struct CFG_VIDEO_FORMAT
    {
	    /// funcitons
	    public byte abCompression;
        public byte abWidth;
        public byte abHeight;
        public byte abBitRateControl;
        public byte abBitRate;
        public byte abFrameRate;
        public byte abIFrameInterval;
        public byte abImageQuality;
        public byte abFrameType;
        public byte abProfile;

	    // info
        /// <summary>
        /// video compression format
        /// </summary>
        public CFG_VIDEO_COMPRESSION emCompression;
        /// <summary>
        /// video width
        /// </summary>
        public Int32 nWidth;
        /// <summary>
        /// video height
        /// </summary>
        public Int32 nHeight;
        /// <summary>
        /// bitrate control mode
        /// </summary>
        public CFG_BITRATE_CONTROL emBitRateControl;
        /// <summary>
        /// video bitrate(kbps)
        /// </summary>
        public Int32 nBitRate;
        /// <summary>
        /// video frame rate
        /// </summary>
        public float fFrameRate;
        /// <summary>
        /// I frame interval(1-100),e.g. 50: set an I frame in every 49 B frame or P frame.
        /// </summary>
        public Int32 nIFrameInterval;
        /// <summary>
        /// image quality
        /// </summary>
        public CFG_IMAGE_QUALITY emImageQuality;
        /// <summary>
        /// packet mode,0－DHAV,1－"PS"
        /// </summary>
        public Int32 nFrameType;
        /// <summary>
        /// H264 Coder Profile
        /// </summary>
        CFG_H264_PROFILE_RANK emProfile;                
    }

    public struct CFG_AUDIO_ENCODE_FORMAT
    {
        //ability
	    public byte				abCompression;
	    public byte				abDepth;
	    public byte				abFrequency;
	    public byte				abMode;
	    public byte				abFrameType;
	    public byte				abPacketPeriod;

	    //information
	    CFG_AUDIO_FORMAT	emCompression;				
	    public int			nDepth;						
	    public int			nFrequency;					
	    public int			nMode;						
	    public int			nFrameType;					
	    public int			nPacketPeriod;				
    }

    /// <summary>
    /// video coding parameter
    /// </summary>
    public struct CFG_VIDEOENC_OPT
    {
	    // ability
	    public byte abVideoEnable;
        public byte abAudioEnable;
        public byte abSnapEnable;
        public byte abAudioAdd;
        public byte abAudioFormat;

	    // info
        /// <summary>
        /// video enable
        /// </summary>
        public int bVideoEnable;
        /// <summary>
        /// video format
        /// </summary>
        public CFG_VIDEO_FORMAT stuVideoFormat;
        /// <summary>
        /// audio enable
        /// </summary>
        public int bAudioEnable;
        /// <summary>
        /// snap enable at set time
        /// </summary>
        public int bSnapEnable;
        /// <summary>
        /// audio add enable
        /// </summary>
        public int bAudioAddEnable;
        /// <summary>
        /// audio Format
        /// </summary>
        public CFG_AUDIO_ENCODE_FORMAT stuAudioFormat;
    } 

    /// <summary>
    /// RGBA info
    /// </summary>
    public struct CFG_RGBA
    {
	    Int32 nRed;
	    Int32 nGreen;
	    Int32 nBlue;
	    Int32 nAlpha;
    }

    /// <summary>
    /// cover info
    /// </summary>
    public struct CFG_COVER_INFO
    {
	    // funcitons
	    public byte abBlockType;
        public byte abEncodeBlend;
        public byte abPreviewBlend;

	    /// info
        /// <summary>
        /// covered area coodinate
        /// </summary>
        public CFG_RECT stuRect;
        /// <summary>
        /// covered color
        /// </summary>
        public CFG_RGBA stuColor;
        /// <summary>
        /// cover mode；0－black block,1－mosaic
        /// </summary>
        public Int32 nBlockType;
        /// <summary>
        /// encode blend；1－effective,0－ineffective
        /// </summary>
        public Int32 nEncodeBlend;
        /// <summary>
        /// preview blend；1－effective,0－ ineffective
        /// </summary>
        public Int32 nPreviewBlend;
    } 

    /// <summary>
    /// multiple area cover setting
    /// </summary>
    public struct CFG_VIDEO_COVER
    {
        /// <summary>
        /// total blocks supported
        /// </summary>
	    public Int32 nTotalBlocks;
        /// <summary>
        /// number of blocks already set
        /// </summary>
	    public Int32 nCurBlocks;
        /// <summary>
        /// covered area
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 16)]
	    public CFG_COVER_INFO[] stuCoverBlock;
    } 

    /// <summary>
    /// OSD info
    /// </summary>
    public struct CFG_OSD_INFO
    {
	    // functions
	    public byte abShowEnable;

	    // info
        /// <summary>
        /// front color
        /// </summary>
        public CFG_RGBA stuFrontColor;
        /// <summary>
        /// back color
        /// </summary>
        public CFG_RGBA stuBackColor;
        /// <summary>
        /// rectangle area
        /// </summary>
        public CFG_RECT stuRect;
        /// <summary>
        /// show enable
        /// </summary>
        public int bShowEnable;
    }

    /// <summary>
    /// picture color attribute
    /// </summary>
    public struct CFG_COLOR_INFO
    {
        /// <summary>
        /// brightness(0-100)
        /// </summary>
	    public Int32 nBrightness;
        /// <summary>
        /// contrast(0-100) 
        /// </summary>
        public Int32 nContrast;
        /// <summary>
        /// saturation(0-100)
        /// </summary>
        public Int32 nSaturation;
        /// <summary>
        /// hue(0-100)
        /// </summary>
        public Int32 nHue;
        /// <summary>
        /// gain(0-100)
        /// </summary>
        public Int32 nGain;
        /// <summary>
        /// gain enable
        /// </summary>
        public Int32 bGainEn;
    } ;

    /// <summary>
    /// picture channel attribute info
    /// </summary>
    public struct CFG_ENCODE_INFO
    {
        /// <summary>
        /// Channel Number(start from 0)
        /// </summary>
	    public Int32 nChannelID;
        /// <summary>
        /// channel name
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 64)]
	    public byte[] szChnName;
        /// <summary>
        /// main bit stream,0－regular record,1- record when action detected,2－recored when 	   ///alarm triggered
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 3)]
	    public CFG_VIDEOENC_OPT[]	stuMainStream;
        /// <summary>
        /// auxiliary bit stream,0－auxiliary bit stream 1,1－auxiliary bit stream 2,2－auxiliary bit 	   ///stream 3
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 3)]
	    public CFG_VIDEOENC_OPT[]	stuExtraStream;
        /// <summary>
        /// snap,0－regular snap,1－snap when action detected,2－snap when alarm triggerd
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 3)]
	    public CFG_VIDEOENC_OPT[]	stuSnapFormat;
        /// <summary>
        /// cover ability mask,bitwise for local preview, record, and Internet monitoring
        /// </summary>
	    public UInt32 dwCoverAbilityMask;
        /// <summary>
        /// cover enable mask,bitwise for local preview, record, and Internet monitoring
        /// </summary>
	    public UInt32 dwCoverEnableMask;
        /// <summary>
        /// video cover
        /// </summary>
	    public CFG_VIDEO_COVER stuVideoCover;
        /// <summary>
        /// channel title
        /// </summary>
	    public CFG_OSD_INFO stuChnTitle;
        /// <summary>
        /// time title
        /// </summary>
	    public CFG_OSD_INFO stuTimeTitle;
        /// <summary>
        /// video color
        /// </summary>
	    public CFG_COLOR_INFO stuVideoColor;
        /// <summary>
        /// audio format: 0:G711A,1:PCM,2:G711U,3:AMR,4:AAC
        /// </summary>
	    public CFG_AUDIO_FORMAT emAudioFormat;
        /// <summary>
        /// Protocol version , readonly
        /// </summary>
        public Int32 nProtocolVer;						// 协议版本号, 只读
    } ;

    /// <summary>
    /// encode format, include audio and video
    /// </summary>
    public struct AV_CFG_EncodeFormat
    {
        public Int32 nStructSize;
        /// <summary>
        /// audio enable
        /// </summary>
        public bool bAudioEnable;
        /// <summary>
        /// audio bitrate
        /// </summary>
        public Int32 nAudioBitRate;
        /// <summary>
        /// audio compression 
        /// </summary>
        public CFG_AUDIO_FORMAT emAudioCompression;
        /// <summary>
        /// audio depth
        /// </summary>
        public Int32 nAudioDepth;
        /// <summary>
        /// audio frequency
        /// </summary>
        public Int32 nAudioFrequency;
        /// <summary>
        /// audio encode mode
        /// </summary>
        public Int32 nAudioMode;
        /// <summary>
        /// audio pack mode, 0-DHAV, 1-PS
        /// </summary>
        public Int32 nAudioPack;
        /// <summary>
        /// video enable
        /// </summary>
        public bool bVideoEnable;
        /// <summary>
        /// video bitrate
        /// </summary>
        public Int32 nVideoBitRate;
        /// <summary>
        /// video bitrate control mode
        /// </summary>
        public CFG_BITRATE_CONTROL emVideoBitRateControl;
        /// <summary>
        /// vdieo compression mode
        /// </summary>
        public CFG_VIDEO_COMPRESSION emVideoCompression;
        /// <summary>
        /// video frame rate
        /// </summary>
        public Int32 nVideoFPS;
        /// <summary>
        /// video I frame interval
        /// </summary>
        public Int32 nVideoGOP;
        /// <summary>
        /// video width
        /// </summary>
        public Int32 nVideoWidth;
        /// <summary>
        /// video height
        /// </summary>
        public Int32 nVideoHeight;
        /// <summary>
        /// video quality
        /// </summary>
        public CFG_IMAGE_QUALITY emVideoQuality;
        /// <summary>
        /// video pack mode, 0-DHAV, 1-PS	
        /// </summary>
        public Int32 nVideoPack;
    };

    /// <summary>
    /// encode setting
    /// </summary>
    public struct AV_CFG_Encode 
    {
	    public Int32 nStructSize;
        /// <summary>
        /// main bit stream, include regular encoding, encoding when action detected, and encoding 	   ///when alarm triggered
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 3)]
	    public AV_CFG_EncodeFormat[] stuMainFormat;
        /// <summary>
        /// auxiliary bit stream, include auxiliary bit stream1,auxiliary bit stream 2, and auxiliary bit 	   ///stream 3
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 3)]
	    public AV_CFG_EncodeFormat[]	stuExtraFormat;
        /// <summary>
        ///  snap,include regular snap,snap when action detected and snap when alarm triggered
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 3)]
	    public AV_CFG_EncodeFormat[]	stuSnapFormat;
    }

    /// <summary>
    /// time section info
    /// </summary>
    public struct CFG_TIME_SECTION 
    {
        /// <summary>
        /// Record Mask, bitwise for action detection record, alarm record, and record at set time, 		   ///Bit3~Bit15 are reserved,
        /// Bit16:snap when action detected、Bit17 :snap when alarm triggerd、Bit18:snap at set time
        /// </summary>
	    public UInt32 dwRecordMask;
        public Int32 nBeginHour;
        public Int32 nBeginMin;
        public Int32 nBeginSec;
        public Int32 nEndHour;
        public Int32 nEndMin;
        public Int32 nEndSec;	
    } 


    /// <summary>
    /// set-time record configuration info
    /// </summary>
    public struct CFG_RECORD_INFO
    {
        /// <summary>
        /// Channel Number(start from 0)
        /// </summary>
	    public Int32 nChannelID;
        /// <summary>
        /// timetable
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 7 * 6)]
        public CFG_TIME_SECTION[] stuTimeSection;
        /// <summary>
        /// pre-record time,0: turn off this function(0~300)
        /// </summary>
        public Int32 nPreRecTime;
        /// <summary>
        /// record redundancy enable
        /// </summary>
        public Int32 bRedundancyEn;
        /// <summary>
        /// 0 - main bitstream, 1 - auxiliary bitstream1, 2 - auxiliary bitstream2, 3 - auxiliary 	           	    ///bitstream 3        
　　　/// </summary>
        public Int32 nStreamType;

        public Int32 nProtocolVer;				// 协议版本号, 只读
        public Int32 abHolidaySchedule;          // 为true时有假日配置信息，bHolidayEn、stuHolTimeSection才有效;
        public Int32 bHolidayEn;                 // 假日录像使能TRUE:使能,FALSE:未使能
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 6)]
        public CFG_TIME_SECTION[]   stuHolTimeSection;          // 假日录像时间表
    }

    /// <summary>
    /// Time section
    /// </summary>
    public struct AV_CFG_TimeSection
    {
        public Int32 nStructSize;
        /// <summary>
        /// mask
        /// </summary>
        public Int32 nMask;
        /// <summary>
        /// begin time
        /// </summary>
        public Int32 nBeginHour;
        public Int32 nBeginMinute;
        public Int32 nBeginSecond;
        /// <summary>
        /// end time
        /// </summary>
        public Int32 nEndHour;
        public Int32 nEndMinute;
        public Int32 nEndSecond;
    };
    
    /// record setting
    public struct AV_CFG_Record 
    {
	    public Int32 nStructSize;
        /// <summary>
        /// pre-record time, unit : s
        /// </summary>
        public Int32 nPreRecord; 
        /// <summary>
        /// time section 
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 7 * 6)]
        public AV_CFG_TimeSection[] stuTimeSection;
    };

    /// <summary>
    /// PTZ link info
    /// </summary>
    public struct CFG_PTZ_LINK
    {
        /// <summary>
        /// link type
        /// </summary>
	    public CFG_LINK_TYPE emType;
        /// <summary>
        /// link values stand for pre-set point number and tour number,etc.
        /// </summary>
	    public Int32 nValue; 
    }

    // 联动云台信息扩展
    public  struct CFG_PTZ_LINK_EX
    {
	    CFG_LINK_TYPE	emType;				// 联动类型 
	    int			    nParam1;			// 联动参数1
	    int			    nParam2;            // 联动参数2
	    int			    nParam3;            // 联动参数3
	    int			    nChannelID;         // 所联动云台通道
    } ;

    // 事件标题内容结构体
    public struct CFG_EVENT_TITLE
    {
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 64)]
	    char[]				szText;
	    CFG_POLYGON			stuPoint;			// 标题左上角坐标, 采用0-8191相对坐标系
	    CFG_SIZE     		stuSize;			// 标题的宽度和高度,采用0-8191相对坐标系，某项或者两项为0表示按照字体自适应宽高
        CFG_RGBA			stuFrontColor;		// 前景颜色
        CFG_RGBA			stuBackColor;		// 背景颜色
    } ;

    // 邮件附件类型
    public enum CFG_ATTACHMENT_TYPE
    {
		    ATTACHMENT_TYPE_PIC,							// 图片附件
		    ATTACHMENT_TYPE_VIDEO,							// 视频附件
		    ATTACHMENT_TYPE_NUM,							// 附件类型总数
    } ;

    // 邮件详细内容
    public struct CFG_MAIL_DETAIL
    {
	       CFG_ATTACHMENT_TYPE emAttachType;                 // 附件类型
           int                 nMaxSize;                     // 文件大小上限，单位kB
           int                 nMaxTimeLength;               // 最大录像时间长度，单位秒，对video有效
    };

    // 分割模式
    public  enum CFG_SPLITMODE
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
    } ;

    // 轮巡联动配置
    public struct CFG_TOURLINK
    {
	    int				    bEnable;			             // 轮巡使能
	    CFG_SPLITMODE	    emSplitMode;		             // 轮巡时的分割模式
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 256)]
	    int[]			        nChannels;  // 轮巡通道号列表
	    int			        nChannelCount;		             // 轮巡通道数量
    } ;

    // 门禁操作类型
    public enum EM_CFG_ACCESSCONTROLTYPE
    {
	    EM_CFG_ACCESSCONTROLTYPE_NULL = 0,					// 不做操作
	    EM_CFG_ACCESSCONTROLTYPE_AUTO,						// 自动
	    EM_CFG_ACCESSCONTROLTYPE_OPEN,						// 开门
	    EM_CFG_ACCESSCONTROLTYPE_CLOSE,						// 关门
	    EM_CFG_ACCESSCONTROLTYPE_OPENALWAYS,				// 永远开启
	    EM_CFG_ACCESSCONTROLTYPE_CLOSEALWAYS,				// 永远关闭
    };

    /// <summary>
    /// alarm link info
    /// </summary>
    public struct CFG_ALARM_MSG_HANDLE
    {
	    //funcitions
	    public byte abRecordMask;
	    public byte abRecordEnable;
	    public byte abRecordLatch;
	    public byte abAlarmOutMask;
	    public byte abAlarmOutEn;
	    public byte abAlarmOutLatch;	
	    public byte abExAlarmOutMask;
	    public byte abExAlarmOutEn;
	    public byte abPtzLinkEn;
	    public byte abTourMask;
	    public byte abTourEnable;
	    public byte abSnapshot;
	    public byte abSnapshotEn;
	    public byte abSnapshotPeriod;
	    public byte abSnapshotTimes;
	    public byte abTipEnable;
	    public byte abMailEnable;
	    public byte abMessageEnable;
	    public byte abBeepEnable;
	    public byte abVoiceEnable;
	    public byte abMatrixMask;
	    public byte abMatrixEnable;
	    public byte abEventLatch;
	    public byte abLogEnable;
	    public byte abDelay;
	    public byte abVideoMessageEn;
	    public byte abMMSEnable;
	    public byte abMessageToNetEn;
	    public byte abTourSplit;
	    public byte abSnapshotTitleEn;

        public byte abChannelCount;
        public byte abAlarmOutCount;
        public byte abPtzLinkEx;
        public byte abSnapshotTitle;
        public byte abMailDetail;
        public byte abVideoTitleEn;
        public byte abVideoTitle;
        public byte abTour;
        public byte abDBKeys;
        public byte abJpegSummary;
        public byte abFlashEn;
        public byte abFlashLatch;

	    ///info
        /// <summary>
        /// device channel count
        /// </summary>
	    public Int32 	nChannelCount;
        /// <summary>
        /// device alarm out count
        /// </summary>
	    public Int32 	nAlarmOutCount;
        /// <summary>
        /// record channel mask(bitwise)
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 16)]
        public UInt32[] dwRecordMask;
        /// <summary>
        /// record enable
        /// </summary>
        public bool bRecordEnable;
        /// <summary>
        /// record delay (uint: s)
        /// </summary>
        public Int32 nRecordLatch;
        /// <summary>
        /// alarm out channel mask
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 16)]
        public UInt32[] dwAlarmOutMask;
        /// <summary>
        /// alarm out enable
        /// </summary>
        public bool bAlarmOutEn;
        /// <summary>
        /// alarm out delay(s)
        /// </summary>
        public Int32 nAlarmOutLatch;
        /// <summary>
        /// expanded alarm out channel mask
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 16)]
        public UInt32[] dwExAlarmOutMask;
        /// <summary>
        /// expanded alarm out enable
        /// </summary>
        public bool bExAlarmOutEn;
        /// <summary>
        /// PTZ link item
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 256)]
        public CFG_PTZ_LINK[] stuPtzLink;
        /// <summary>
        /// PTZ link enable
        /// </summary>
        public bool bPtzLinkEn;
        /// <summary>
        /// tour channel mask
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 16)]
        public UInt32[] dwTourMask;
        /// <summary>
        /// tour enable
        /// </summary>
        public bool bTourEnable;
        /// <summary>
        /// snap Channel Number mask
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 16)]
        public UInt32[] dwSnapshot;
        /// <summary>
        /// snap enable
        /// </summary>
        public bool bSnapshotEn;
        /// <summary>
        /// snapshot period ( unit:s )
        /// </summary>
        public Int32 nSnapshotPeriod;
        /// <summary>
        /// snapshot times
        /// </summary>
        public Int32 nSnapshotTimes;
        /// <summary>
        /// local message tip
        /// </summary>
        public bool bTipEnable;
        /// <summary>
        /// send e-mai(attach picture if available)
        /// </summary>
        public bool bMailEnable;
        /// <summary>
        /// upload to alarm server
        /// </summary>
        public bool bMessageEnable;
        /// <summary>
        /// beep
        /// </summary>
        public bool bBeepEnable;
        /// <summary>
        /// voice enable
        /// </summary>
        public bool bVoiceEnable;
        /// <summary>
        /// link video matrix channel mask
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 16)]
        public UInt32[] dwMatrixMask;
        /// <summary>
        /// link video matrix enable
        /// </summary>
        public bool bMatrixEnable;
        /// <summary>
        /// delay time( unit:s,0-15) when link begin
        /// </summary>
        public Int32 nEventLatch;
        /// <summary>
        /// log enable
        /// </summary>
        public bool bLogEnable;
        /// <summary>
        /// effective after delay in configuration(unit:second)
        /// </summary>
        public Int32 nDelay;
        /// <summary>
        /// add message to video, include Event Type , Channel Number, and timing (unit:s)
        /// </summary>
        public bool bVideoMessageEn;
        /// <summary>
        /// send multiple message enable
        /// </summary>
        public bool bMMSEnable;
        /// <summary>
        /// message to net enable
        /// </summary>
        public bool bMessageToNetEn;
        /// <summary>
        /// tour split mode,  0: 1 picture; 1: 8 picture
        /// </summary>
        public Int32 nTourSplit;
        /// <summary>
        /// snapshot title enable
        /// </summary>
        public bool bSnapshotTitleEn;

        public int nPtzLinkExNum;                                // 云台配置数
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 256)]
        public CFG_PTZ_LINK_EX[] stuPtzLinkEx;          // 扩展云台信息
        public int nSnapTitleNum;                                // 图片标题内容数
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 256)]
        public CFG_EVENT_TITLE[] stuSnapshotTitle;      // 图片标题内容
        public CFG_MAIL_DETAIL stuMailDetail;                                // 邮件详细内容
        public int bVideoTitleEn;                                // 是否叠加视频标题，主要指主码流
        public int nVideoTitleNum;                               // 视频标题内容数目
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 256)]
        public CFG_EVENT_TITLE[] stuVideoTitle;         // 视频标题内容
        public int nTourNum;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 256)]
        public CFG_TOURLINK[] stuTour;               // 轮询联动配置
        public int nDBKeysNum;			                          // 指定数据库关键字的有效数
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 64 * 64)]
        public char[] szDBKeys; // 指定事件详细信息里需要写到数据库的关键字
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 1024)]
        public char[] byJpegSummary;               // 叠加到JPEG图片的摘要信息
        public int                bFlashEnable;                                 // 是否使能补光灯
        public int                 nFlashLatch;                                  // 补光灯延时时间(秒),延时时间范围：[10,300]
	
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 424 )]
        public int[] nRevered;	                                   // 对齐
    }

    public enum EM_SENSE_METHOD
    {
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
	    EM_SENSE_CALLBUTTON,	 //呼叫按钮
	    EM_SENSE_GASPRESSURE,	 //气体压力
	    EM_SENSE_GASCONCENTRATION,//燃气浓度
	    EM_SENSE_GASFLOW,		 //气体流量
	    EM_SENSE_OTHER,			 //其他
	    EM_SENSE_NUM             //枚举类型总数
    };

    public enum EM_CTRL_ENABLE
    {
	    EM_CTRL_NORMAL=0,   //不控制使能
	    EM_CTRL_ALWAYS_EN,  //总是使能
	    EM_CTRL_ONCE_DIS,   //旁路
	    EM_CTRL_ALWAYS_DIS, //移除
	    EM_CTRL_NUM         //枚举类型总数
    };

    public enum EM_CFG_DEFENCEAREATYPE
    {
	    EM_CFG_DefenceAreaType_Unknown = 0,	// 未知类型
	    EM_CFG_DefenceAreaType_InTime,		// 即时防区 
	    EM_CFG_DefenceAreaType_Delay,		// 延时防区
	    EM_CFG_DefenceAreaType_FullDay,		// 24小时防区
    };

    // alarm in info configuration
    public struct CFG_ALARMIN_INFO
    {
        /// <summary>
        /// alarm Channel Number(begin from 0)
        /// </summary>
	    public Int32 nChannelID;
        /// <summary>
        /// enable
        /// </summary>
	    public bool bEnable;
        /// <summary>
        /// alarm channel name
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 64)]
	    public byte[] szChnName;
        /// <summary>
        /// alarm type,0：usual off,1：usual on
        /// </summary>
	    public Int32 nAlarmType;
        /// <summary>
        /// alarm link
        /// </summary>
	    public CFG_ALARM_MSG_HANDLE stuEventHandler;
        /// <summary>
        /// time section of event response
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 7 * 6)]
	    public CFG_TIME_SECTION[]	stuTimeSection;
        
        public int	    abDevID;	
		[MarshalAs(UnmanagedType.ByValArray, SizeConst = 128)]						
	    public char[]	szDevID;						
	    public int      nPole;

        public EM_SENSE_METHOD emSense;                                    
	    public EM_CTRL_ENABLE  emCtrl;                                     
	    public int             nDisDelay;                                 
	                                                              

	    public EM_CFG_DEFENCEAREATYPE emDefenceAreaType;						
	    public int					 nEnableDelay;
        public int nSlot;
        public int nLevel1;
        public int abLevel2;
        public int nLevel2;
    }


    // net alarm in info 
    public struct CFG_NETALARMIN_INFO 
    {
        /// <summary>
        /// alarm Channel Number(begin from 0)
        /// </summary>
	    public Int32 nChannelID;
        /// <summary>
        /// enable
        /// </summary>
	    public bool bEnable;
        /// <summary>
        /// alarm channal name
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 32)]
	    public byte[] szChnName;
        /// <summary>
        /// alarm type,0：usual off,1：usual on
        /// </summary>
	    public Int32 nAlarmType;
        /// <summary>
        /// alarm link
        /// </summary>
	    public CFG_ALARM_MSG_HANDLE stuEventHandler;
        /// <summary>
        /// time section of event response
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 7 * 6)]
	    public CFG_TIME_SECTION[]	stuTimeSection;
    }

    // motion detection info
    public struct CFG_MOTION_INFO 
    {
        /// <summary>
        /// alarm Channel Number(begin from 0)
        /// </summary>
	    public Int32 nChannelID;
        /// <summary>
        /// enable
        /// </summary>
	    public bool bEnable;
        /// <summary>
        /// sense level 1～6
        /// </summary>
	    public Int32 nSenseLevel;
        /// <summary>
        /// rows count in motion detection area
        /// </summary>
	    public Int32 nMotionRow;
        /// <summary>
        /// columns count in motion detection area
        /// </summary>
	    public Int32 nMotionCol;
        /// <summary>
        /// detection area,max 32*32
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 32 * 32)]
	    public byte[] byRegion;
        /// <summary>
        /// alarm link
        /// </summary>
	    public CFG_ALARM_MSG_HANDLE stuEventHandler;
        /// <summary>
        /// time section of event response
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 7 * 6)]
	    public CFG_TIME_SECTION[]	stuTimeSection;
    } 

    // alarm info for video lost
    public struct CFG_VIDEOLOST_INFO 
    {
        /// <summary>
        /// alarm Channel Number(begin from 0)
        /// </summary>
	    public Int32 nChannelID;
        /// <summary>
        /// enable
        /// </summary>
	    public bool bEnable;
        /// <summary>
        /// alarm link
        /// </summary>
	    public CFG_ALARM_MSG_HANDLE stuEventHandler;
        /// <summary>
        /// time section of event response
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 7 * 6)]
	    public CFG_TIME_SECTION[]	stuTimeSection;
    } 

    // alarm configuration for video shelter
    public struct CFG_SHELTER_INFO 
    {
        /// <summary>
        /// alarm Channel Number(begin from 0)
        /// </summary>
        public Int32 nChannelID;
        /// <summary>
        /// enable
        /// </summary>
        public bool bEnable;
        /// <summary>
        /// sense level
        /// </summary>
        public Int32 nSenseLevel;
        /// <summary>
        /// alarm link
        /// </summary>
        public CFG_ALARM_MSG_HANDLE stuEventHandler;
        /// <summary>
        /// time section of event response
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 7 * 6)]
        public CFG_TIME_SECTION[] stuTimeSection;
    }

    // alarm configuration for storage no-exist
    public struct CFG_STORAGENOEXIST_INFO 
    {
        /// <summary>
        /// enable
        /// </summary>
	    public bool bEnable;
        /// <summary>
        /// alarm link
        /// </summary>
	    public CFG_ALARM_MSG_HANDLE stuEventHandler;
    } ;

    // alarm configuration for storage failure
    public struct CFG_STORAGEFAILURE_INFO 
    {
        /// <summary>
        /// enable
        /// </summary>
	    public bool bEnable;
        /// <summary>
        /// alarm link
        /// </summary>
	    public CFG_ALARM_MSG_HANDLE stuEventHandler;
    } 

    /// alarm configuration for low space of storage
    public struct CFG_STORAGELOWSAPCE_INFO 
    {
        /// <summary>
        /// enable
        /// </summary>
	    public bool bEnable;
        /// <summary>
        /// lower limit of harddisk left Capacity, %(0~99)
        /// </summary>
	    public Int32 nLowerLimit;
        /// <summary>
        /// alarm link
        /// </summary>
	    public CFG_ALARM_MSG_HANDLE stuEventHandler;
    } 

    /// alarm configuration for net abort
    public struct CFG_NETABORT_INFO 
    {
        /// <summary>
        /// enable
        /// </summary>
	    public bool bEnable;
        /// <summary>
        /// alarm link
        /// </summary>
        public CFG_ALARM_MSG_HANDLE stuEventHandler;
    } 

    // alarm configuration for IP conflict
    public struct CFG_IPCONFLICT_INFO 
    {
        /// <summary>
        /// enable
        /// </summary>
	    public bool bEnable;
        /// <summary>
        /// alarm link
        /// </summary>
	    public CFG_ALARM_MSG_HANDLE stuEventHandler;
    } 

    /// snap capability configuration
    public struct CFG_SNAPCAPINFO_INFO  
    {
        /// <summary>
        /// snap Channel Number(begin from 0)
        /// </summary>
	    public Int32 nChannelID;
        /// <summary>
        /// supported resolution info
        /// </summary>
        public UInt32 dwIMageSizeNum;
        /// <summary>
        /// 
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 256)]
        public CFG_CAPTURE_SIZE[] emIMageSizeList;
        /// <summary>
        /// supported frame rate info
        /// </summary>
        public UInt32 dwFramesPerSecNum;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 1024)]
        public Int32[] nFramesPerSecList;
        /// <summary>
        /// supported video quality info
        /// </summary>
        public UInt32 dwQualityMun;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 32)]
        public CFG_IMAGE_QUALITY[] emQualityList;
        /// <summary>
        /// mode, bitwise: first bit: snap at set time；second bit：manual。
        /// </summary>
        public UInt32 dwMode;
        /// <summary>
        /// picture format mode, bitwise：first bit：bmp；second bit：jpg。
        /// </summary>
        public UInt32 dwFormat;
    } 

    // network storage server configuration
    public struct CFG_CHANNEL_TIME_SECTION 
    {
        /// <summary>
        /// storage time section
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 7 * 2)]
	    public CFG_TIME_SECTION[] stuTimeSection;
    } 

    public struct CFG_NAS_INFO
    {
        /// <summary>
        /// enable
        /// </summary>
	    public bool bEnable;
        /// <summary>
        /// netwok storage server version , 0= old FTP,1=NAS storage
        /// </summary>
	    public Int32 nVersion;
        /// <summary>
        /// protocol type ,0=FTP 1=SMB
        /// </summary>
	    public Int32 nProtocol;
        /// <summary>
        /// IP or network name
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 256)]
	    public byte[] szAddress;
        /// <summary>
        /// port number
        /// </summary>
	    public Int32 nPort;
        /// <summary>
        /// account ID
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 64)]
	    public byte[] szUserName;
        /// <summary>
        /// password
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 64)]
	    public byte[] szPassword;
        /// <summary>
        /// shared directory name
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 256)]
	    public byte[] szDirectory;
        /// <summary>
        /// file length
        /// </summary>
	    public Int32 nFileLen;
        /// <summary>
        /// time interval between files
        /// </summary>
	    public Int32 nInterval;
        /// <summary>
        /// storage time section
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 256)]
	    public CFG_CHANNEL_TIME_SECTION[] stuChnTime;
        /// <summary>
        /// valid storage time section count
        /// </summary>
	    public Int32 nChnTimeCount;
    } 

    /// protocol name
    public struct CFG_PRONAME
    {
        /// <summary>
        /// protocol name 
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 32)]
        public byte[] name;
    } 

    // serial port property
    public struct CFG_COMM_PROP
    {
        /// <summary>
        /// data bit；0：5,1：6,2：7,3：8
        /// </summary>
	    public byte byDataBit;
        /// <summary>
        /// stop bit；0：1位,1：1.5位,2：2位
        /// </summary>
        public byte byStopBit;
        /// <summary>
        /// parity bit；0：no parity check,1：odd check；2：even check
        /// </summary>
        public byte byParity;
        /// <summary>
        /// baud rate；0：300,1：600,2：1200,3：2400,4：4800,
        /// 5：9600,6：19200,7：38400,8：57600,9：115200
        /// </summary>
        public byte byBaudRate;
	        
    } 


    // PTZ configuration
    public struct CFG_PTZ_INFO
    {
	    // capability
	    public byte abMartixID;
        public byte abCamID;
        public byte abPTZType;

	    /// info
        /// <summary>
        /// Channel Number(begin from 0)	
        /// </summary>
        public Int32 nChannelID;
        /// <summary>
        /// protocol name list( Read Only)
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 100)]
        public CFG_PRONAME[] stuDecProName;
        /// <summary>
        /// protocol type, correspond to the index of "protocol name list"
        /// </summary>
        public Int32 nProName;
        /// <summary>
        /// decoder address；0 - 255
        /// </summary>
        public Int32 nDecoderAddress;
        public CFG_COMM_PROP struComm;
        /// <summary>
        /// matrix ID
        /// </summary>
        public Int32 nMartixID;
        /// <summary>
        /// PTZ type, 0-compatible ,local PTZ ,1-remote network PTZ
        /// </summary>
        public Int32 nPTZType;
        /// <summary>
        /// camera ID
        /// </summary>
        public Int32 nCamID;
    }   

    /// watermark configuration
    public struct CFG_WATERMARK_INFO 
    {
        /// <summary>
        /// Channel Number(begin from 0)
        /// </summary>
	    public Int32 nChannelID;
        /// <summary>
        /// enable
        /// </summary>
        public bool bEnable;
        /// <summary>
        /// bit stream type(1～n),0－all types
        /// </summary>
        public Int32 nStreamType;
        /// <summary>
        /// data type,1－text,2－pic
        /// </summary>
        public Int32 nDataType;
        /// <summary>
        /// watermark data of character string
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 4096)]
        public byte[] pData;
    } 

    /// video analysis configuration for each video-in channel
    public struct CFG_ANALYSESOURCE_INFO
    {
        /// <summary>
        /// video analysis enable
        /// </summary>
	    public byte bEnable;
        /// <summary>
        /// reserved alignment
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 3)]
	    public byte[] bReserved;
        /// <summary>
        /// video-in Channel Number of video analysis
        /// </summary>
	    public Int32 nChannelID;
        /// <summary>
        /// bit stream type of video analysis,0: snap mode; 1:main bitstream; 2:sub bitstream1; 3:sub bitstream2; 4:sub bitstream3; 5: object stream
        /// </summary>
	    public Int32 nStreamType;
        /// <summary>
        /// device name
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 32)]
	    public byte[] szRemoteDevice;
    	
    } 

    public struct CFG_RAINBRUSH_INFO
    {
        /// <summary>
        /// rain brush info
        /// </summary>
	    public byte bEnable;
        /// <summary>
        /// rain brush speed,1:fast;2:medium;3:slow
        /// </summary>
	    public byte bSpeedRate;
        /// <summary>
        /// reserved alignment
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 2)]
	    public byte[] bReserved;
        /// <summary>
        /// time section of event response
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 7 * 6)]
	    public CFG_TIME_SECTION[]	stuTimeSection;

    }

    // BreakingSnapTimes
    public struct BREAKINGSNAPTIMES_INFO
    {
        /// <summary>
        /// normal
        /// </summary>
	    Int32 nNormal;
        /// <summary>
        /// run red light
        /// </summary>
	    Int32 nRunRedLight;
        /// <summary>
        /// over line
        /// </summary>
	    Int32 nOverLine;
        /// <summary>
        /// over yellow line
        /// </summary>
	    Int32 nOverYellowLine;
        /// <summary>
        /// retrograde
        /// </summary>
	    Int32 nRetrograde;
        /// <summary>
        /// under speed
        /// </summary>
	    Int32 nUnderSpeed;
        /// <summary>
        /// over speed
        /// </summary>
        Int32 nOverSpeed;
        /// <summary>
        /// wrong running route
        /// </summary>
	    Int32 nWrongRunningRoute;
        /// <summary>
        /// yellow in route
        /// </summary>
	    Int32 nYellowInRoute;
        /// <summary>
        /// special retrograde
        /// </summary>
	    Int32 nSpecialRetrograde;
        /// <summary>
        /// illegal turn left 
        /// </summary>
	    Int32 nTurnLeft;
        /// <summary>
        /// illegal turn right
        /// </summary>
	    Int32 nTurnRight;
        /// <summary>
        /// illegal cross lane
        /// </summary>
	    Int32 nCrossLane;
        /// <summary>
        /// illegal U-turn
        /// </summary>
	    Int32 nU_Turn;
        /// <summary>
        /// illegal parking
        /// </summary>
	    Int32 nParking;
        /// <summary>
        /// illegal entering waiting area
        /// </summary>
	    Int32 nWaitingArea;
        /// <summary>
        /// illegal wrong route
        /// </summary>
	    Int32 nWrongRoute;
    }

    public struct COILCONFIG_INFO
    {
        /// <summary>
        /// delayed flash ID, each coil stand for a delayed flashID,range 0~5,0 stand for do not 		   ///delay any flash
        /// </summary>
	    public Int32 nDelayFlashID;
        /// <summary>
        /// flash ID, range 0~5,0 stand for flash off (only used in jinzhou project）
        /// </summary>
        public Int32 nFlashSerialNum;
        /// <summary>
        /// red light direction. Each coil stands for a red light direction: 0-none,1-turn-left red light,
	   ///2-go-straight red light,3- turn-right red light,4- turn-left waiting,5- go-straight 		                            	   ///waiting,6-turn-right waiting, only valid in electronic alarm
        /// </summary>
        public Int32 nRedDirection;
        /// <summary>
        /// coil trigger mode：0-enter coil trigger 1-exit coil trigger（only used in Jinzhou project）
        /// </summary>
        public Int32 nTriggerMode;
    }

    public struct DETECTOR_INFO
    {
        /// <summary>
        ///violation type mask：0-normal1-run red light2-over line3-go in the wrong way 4-under 		   ///speed5-over speed6-wrong running route7-yellow in route
        /// </summary>
	    public Int32 nDetectBreaking;
        /// <summary>
        /// array for coil configuration
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 3)]
	    public COILCONFIG_INFO[]    arstCoilCfg;
        /// <summary>
        /// roadway number 0-16 
        /// </summary>
	    public Int32 nRoadwayNumber;
        /// <summary>
        /// roadway direction(driving direction）	0- south to north 1-southwest to northeast 2-to 	
	   ///east 3-northwest to southeast  4-north to south 5-southwest to northeast 6-east to west 
        ///7-southeast ///to northwest 8-neglect
        /// </summary>
	    public Int32 nRoadwayDirection;
        /// <summary>
        /// bayonet picture number, for selecting one out of three as the bayonet picture
        /// 0: do not use,1~3: stand for the bayonet picture number
        /// </summary>
	    public Int32 nRedLightCardNum;
        /// <summary>
        /// coils number 1-3
        /// </summary>
	    public Int32 nCoilsNumber;
        /// <summary>
        /// operation type: 0-bayonet electronic alarm  1-electronic alarm  2-bayonet
        /// </summary>
	    public Int32 nOperationType;
        /// <summary>
        /// coil distance, range: 0-1000,unit: cm
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 3)]
	    public Int32[] arnCoilsDistance;
        /// <summary>
        /// coil width	0~200cm
        /// </summary>
	    public Int32 nCoilsWidth;
        /// <summary>
        /// small car Speed Lower Limit and upper limit	0~255km/h,if do not use speed limit for 
　　　   ///big and small car, speed limit for regular car will take effect
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 2)]
	    public Int32[] arnSmallCarSpeedLimit;
        /// <summary>
        /// big car Speed Lower Limit and upper limit	0~255km/h,valid when speed limit for big 
　　　   ///and small car function enables
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 2)]
	    public Int32[] arnBigCarSpeedLimit;
        /// <summary>
        /// over speed margin ,unit：km/h
        /// </summary>
	    public Int32 nOverSpeedMargin;
        /// <summary>
        /// big car over speed margin,	unit：km/h,valid when speed limit for big and small car  	   ///function enables
        /// </summary>
	    public Int32 nBigCarOverSpeedMargin;
        /// <summary>
        /// under speed margin,	unit：km/h
        /// </summary>
	    public Int32 nUnderSpeedMargin;
        /// <summary>
        /// big car under speed margin, unit：km/h,valid when speed limit for big and small car 
　　　   ///function enables
        /// </summary>
	    public Int32 nBigCarUnderSpeedMargin;
        /// <summary>
        /// use speed limit for big and small car function or not
        /// </summary>
	    public byte bSpeedLimitForSize;
        /// <summary>
        /// retrograde illegal or not
        /// </summary>
	    public byte bMaskRetrograde;
        /// <summary>
        /// reserved alignment
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 2)]
	    public byte[] byReserved;
        /// <summary>
        /// "DrivingDirection" : ["Approach", "Shanghai", "Hangzhou"],driving direction
        /// "Approach"-car approaches the device；"Leave"- car leaves the device,
        /// the second and third parameter stand for the two places the car approaches or leaves
        /// UTF-8 coding
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 3 * 256)]
        public byte[] szDrivingDirection;
        /// <summary>
        /// over speed percentage,snap if this car speed exceeds this percentage
        /// </summary>
	    public Int32 nOverPercentage; 
     
    }

    public struct CFG_TRAFFICSNAPSHOT_INFO
    {
        /// <summary>
        /// device address,	UTF-8 coding,256 bytes
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 256)]
	    public byte[] szDeviceAddress;
        /// <summary>
        /// OSD type mask：0-time 1-place 2-plate3-car length 4-Car Speed 5-speed limit
        /// 6-big car speed limit 7-small car speed limit 8-over speed 9-violation number
        ///10-lane number 
        /// 11-car color 12-plate type 13-plate color 14- time when red light on 15-violation type 
        /// 16-radar direction 17-device number 18- expire time 19-cat type 20-driving direction
        /// </summary>
	    public Int32 nVideoTitleMask;
        /// <summary>
        /// red light margin: time margin after red light on,cars will not be thought running red light 
　　　///during this period,unit：s
        /// </summary>
	    public Int32 nRedLightMargin;
        /// <summary>
        /// long vehicle length level unit: m,
        /// </summary>
	    public float fLongVehicleLengthLevel;
        /// <summary>
        /// large vehicle length level  unit：m,
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 2)]
	    public float[] arfLargeVehicleLengthLevel;
        /// <summary>
        /// medium vehicle length level	unit：m
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 2)]
	    public float[] arfMediumVehicleLengthLevel;
        /// <summary>
        /// small vehicle length level unit：m
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 2)]
	    public float[] arfSmallVehicleLengthLevel;
        /// <summary>
        /// motor vehicle length level unit:m 
        /// </summary>
	    public float fMotoVehicleLengthLevel;
        /// <summary>
        /// snap times when violation detected
        /// </summary>
	    public BREAKINGSNAPTIMES_INFO   stBreakingSnapTimes;
        /// <summary>
        /// detector info, the first three are used to put the 3 coils in the bayonet, the later three are 	 
　　　   ///used to put the 3 coils that has electronic alarm
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 6)]
	    public DETECTOR_INFO[] arstDetector;
        /// <summary>
        /// snap car type 0- snap big and small car ,1-snap small car ,2-snap big car 3- snap none
        /// </summary>
	    public Int32 nCarType;
        /// <summary>
        /// when detected speed exceeds max speed, use max speed   0~255km/h
        /// </summary>
	    public Int32 nMaxSpeed;
        /// <summary>
        /// frame interval mode  1- adaptive speed ( use 0 interval when exceed speed Upper 
 	   ///Limit, use 2 interval when under Speed Lower Limit, or use 1 interval）
 	   ///2- decided by link parameter
        /// </summary>
	    public Int32 nFrameMode;
        /// <summary>
        /// lower limit and upper limit of the adaptive speed 
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 2)]
	    public Int32[] arnAdaptiveSpeed;
        /// <summary>
        /// link parameter of traffic snap
        /// </summary>
	    public CFG_ALARM_MSG_HANDLE  stuEventHandler;
        /// <summary>
        /// Reserved Bytes
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 768)]
	    public byte[] bReserved;
    }


    public struct CFG_OVERSPEED_INFO
    {
        /// <summary>
        /// over speed percentage can not be overlaid, effective values are:0, positive number and -1,
　　　  /// -1 stands for infinity
        /// if under speed:under speed percentage can not be overlaid. effective values are:0,
        /// positive number and -1,  -1 stands for infinity
　　　  /// under speed percentage formula:lower speed limit - Car actual Speed/lower speed limit
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 2)]
	    public Int32[] nSpeedingPercentage;
        /// <summary>
        /// violation code
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 16)]
	    public byte[] szCode;
        /// <summary>
        /// violation description
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 64)]
	    public byte[] szDescription; 

    }

    public struct CFG_UNDERSPEED_INFO
    {
        /// <summary>
       /// over speed percentage can not be overlaid, effective values are : 0, positive number and -1, 
　　　    ///-1 stands for infinity
        /// if under speed：under speed percentage can not be overlaid. effective values are : 0, 	 
        ///positive number and -1,  -1 stands for infinity
　　　   ///under speed percentage formula：lower speed limit - Car actual Speed/lower speed limit

        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 2)]
	    public Int32[] nSpeedingPercentage;
        /// <summary>
        /// violation code
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 16)]
	    public byte[] szCode;
        /// <summary>
        /// violation description
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 64)]
	    public byte[] szDescription; 

    }

    public struct CFG_OVERSPEED_HIGHWAY_INFO
    {
        /// <summary>
       /// over speed percentage can not be overlaid, effective values are : 0, positive number and -1, 
　　　    ///-1 stands for infinity
        /// if under speed：under speed percentage can not be overlaid. effective values are : 0, 	 
        ///positive number and -1,  -1 stands for infinity
　　　   ///under speed percentage formula：lower speed limit - Car actual Speed/lower speed limit
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 2)]
        public Int32[] nSpeedingPercentage;
        /// <summary>
        /// violation code
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 16)]
        public byte[] szCode;
        /// <summary>
        /// violation description
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 64)]
        public byte[] szDescription;

    }

    /// <summary>
    /// ViolationCode violation code configuration
    /// </summary>
    public struct VIOLATIONCODE_INFO
    {
        /// <summary>
        /// retrograde
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 16)]
        public byte[] szRetrograde;
        /// <summary>
        /// violation description
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 64)]
	    public byte[] szRetrogradeDesc; 
        /// <summary>
        /// retrograde-highway
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 16)]
	    public byte[] szRetrogradeHighway;
        /// <summary>
        /// violation description
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 64)]
	    public byte[] szRetrogradeHighwayDesc;
        /// <summary>
        /// run red light
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 16)]
	    public byte[] szRunRedLight;
        /// <summary>
        /// violation description
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 64)]
	    public byte[] szRunRedLightDesc;
        /// <summary>
        /// illegal cross lane
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 16)]
	    public byte[] szCrossLane;
        /// <summary>
        /// violation description
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 64)]
	    public byte[] szCrossLaneDesc;
        /// <summary>
        /// illegal turn left
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 16)]
	    public byte[] szTurnLeft;
        /// <summary>
        /// violation description
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 64)]
	    public byte[] szTurnLeftDesc;
        /// <summary>
        /// illegal turn right
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 16)]
	    public byte[] szTurnRight;
        /// <summary>
        /// violation description
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 64)]
	    public byte[] szTurnRightDesc;
        /// <summary>
        /// illegal U-turn
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 16)]
	    public byte[] szU_Turn;
        /// <summary>
        /// violation description
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 64)]
	    public byte[] szU_TurnDesc;
        /// <summary>
        /// traffic jam
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 16)]
	    public byte[] szJam;
        /// <summary>
        /// violation description
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 64)]
	    public byte[] szJamDesc;
        /// <summary>
        /// illegal parking
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 16)]
	    public byte[] szParking;
        /// <summary>
        /// violation description
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 64)]
	    public byte[] szParkingDesc;

	    // over speed and over speed percentage, one and only one configuration is must
        /// <summary>
        /// over speed
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 16)]
	    public byte[] szOverSpeed;
        /// <summary>
        /// violation description
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 64)]
	    public byte[] szOverSpeedDesc;
        /// <summary>
        /// over speed percentage code
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 5)]
	    public CFG_OVERSPEED_INFO[]  stOverSpeedConfig;

　　　   /// over speed(highway) and over speed percentage (highway), 
　　　   ///one and only one configuration is must
        /// <summary>
        /// over speed-highway
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 16)]
	    public byte[] szOverSpeedHighway;
        /// <summary>
        /// over speed-violation description
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 64)]
	    public byte[] szOverSpeedHighwayDesc;
        /// <summary>
        /// over speed percentage code
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 5)]
	    public CFG_OVERSPEED_HIGHWAY_INFO[] stOverSpeedHighwayConfig;

	    // under speed and under speed percentage, one and only one configuration is must
        /// <summary>
        /// under speed
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 16)]
	    public byte[] szUnderSpeed;
        /// <summary>
        /// violation description
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 64)]
	    public byte[] szUnderSpeedDesc;
        /// <summary>
        /// under speed info is an array
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 5)]
	    public CFG_UNDERSPEED_INFO[] stUnderSpeedConfig;
        /// <summary>
        /// over line
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 16)]
	    public byte[] szOverLine;
        /// <summary>
        /// violation description
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 64)]
	    public byte[] szOverLineDesc;
        /// <summary>
        /// over yellow line
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 16)]
	    public byte[] szOverYellowLine;
        /// <summary>
        /// violation description
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 64)]
	    public byte[] szOverYellowLineDesc;
        /// <summary>
        /// yellow in route
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 16)]
	    public byte[] szYellowInRoute;
        /// <summary>
        /// violation description
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 64)]
	    public byte[] szYellowInRouteDesc;
        /// <summary>
        /// illegal wrong route
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 16)]
	    public byte[] szWrongRoute;
        /// <summary>
        /// violation description
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 64)]
	    public byte[] szWrongRouteDesc;
        /// <summary>
        /// driving on road shoulder
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 16)]
	    public byte[] szDrivingOnShoulder;
        /// <summary>
        /// violation description
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 64)]
	    public byte[] szDrivingOnShoulderDesc;
        /// <summary>
        /// normal passing
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 16)]
	    public byte[] szPassing;
        /// <summary>
        /// violation description
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 64)]
	    public byte[] szPassingDesc;
        /// <summary>
        /// no passing
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 16)]
	    public byte[] szNoPassing;
        /// <summary>
        /// violation description
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 64)]
	    public byte[] szNoPassingDesc;
        /// <summary>
        /// fake plate
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 16)]
	    public byte[] szFakePlate;
        /// <summary>
        /// violation description
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 64)]
	    public byte[] szFakePlateDesc;
    	[MarshalAs(UnmanagedType.ByValArray, SizeConst = 1024)]
	    public byte[] bReserved;
    }

    /// <summary>
    /// traffic global configuration list
    /// </summary>
    public struct CFG_TRAFFICGLOBAL_INFO
    {
        /// <summary>
        /// violation code configuration list
        /// </summary>
	    public VIOLATIONCODE_INFO   stViolationCode;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 1024)]
	    public byte[] bReserved;
    }


    // general configuration (CFG_CMD_DEV_GENERRAL) General 
    public struct CFG_DEV_DISPOSITION_INFO
    {
        /// <summary>
        /// local machine ID,used to distinguish machines	0~998
        /// </summary>
	    public Int32 nLocalNo;
        /// <summary>
        /// machine name or ID
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 256)]
	    public byte[] szMachineName;
        /// <summary>
        /// machine deploy place, i.e. Road number
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 256)]
	    public byte[] szMachineAddress; 
        /// <summary>
        /// machine group, default none, different machines can be set to a group
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 256)]
	    public byte[] szMachineGroup;
        /// <summary>
        /// Reserved Bytes
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 1024)]
	    public byte[] bReserved; 
    }

    public struct CFG_ATMMOTION_INFO
    {
	    public Int32 nTimeLimit;
    }

    // device state info
    public struct CFG_DEVICESTATUS_INFO
    {
        /// <summary>
        /// power number
        /// </summary>
	    public Int32 nPowerNum;
        /// <summary>
        /// power state,1:normal 2:abnormal 3:unknown
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 8)]
        public byte[] byPowerStatus;
        /// <summary>
        /// CPU number
        /// </summary>
        public Int32 nCPUNum;
        /// <summary>
        /// CPU temperature
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 8)]
        public Int32[] nCPUTemperature;
        /// <summary>
        /// fan nubmer
        /// </summary>
        public Int32 nFanNum;
        /// <summary>
        /// rotato speed
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 8)]
        public Int32[] nRotatoSpeed;
    }

    /// expanded harddisk info
    public struct CFG_HARDDISK_INFO 
    {
        /// <summary>
        /// Channel Number
        /// </summary>
	    public Int32 nChannel;
        /// <summary>
        /// harddisk Capacity
        /// </summary>
	    public Int32 nCapacity;
        /// <summary>
        /// harddisk state,0:unknown 1:running 2:fail
        /// </summary>
	    public byte byStatus;
        /// <summary>
        /// used status,1.free  2. Under operation 3. unknown
        /// </summary>
	    public byte byUsedStatus;
        /// <summary>
        /// hotback or nor,0:yes 1:no
        /// </summary>
        public byte byHotBack;
        /// <summary>
        ///  Bytes Aligned
        /// </summary>
	    public byte byReserved;
        /// <summary>
        /// "RaidName" : "Raid0",
        /// if do not belong to any Raid,the field will be null, hotback disk for example 
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 32)]
	    public byte[] szRaidName;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 32)]
	    public byte[] szType;                      // harddisk number 
	    public Int32 nTank;           // expanded tank,  0:host;  1:expanded tank1; 
　　　//2:expanded tank2	……
	    public Int32 nRemainSpace;					 // left Capacity,unit:M
    }

    public struct CFG_HARDDISKTANK_INFO
    {
        /// <summary>
        /// harddisk tank name
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 32)]
	    public byte[] szTankName;
        /// <summary>
        /// harddisk name
        /// </summary>
        public Int32 nHardDiskNum;
        /// <summary>
        /// Harddisk info
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 32)]
        public CFG_HARDDISK_INFO[] stuHarddiskInfo;
    }

    public struct CFG_HARDISKTANKGROUP_INFO
    {
        /// <summary>
        /// tank number
        /// </summary>
	    public Int32  nTankNum;
        /// <summary>
        /// tank group number
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 16)]
	    public CFG_HARDDISKTANK_INFO[]    stuHarddisktank;
    }

    // Raid group name
    public struct CFG_RAID_INFO
    {
        /// <summary>
        /// Raid name
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 32)]
	    public byte[] szRaidName;
        /// <summary>
        /// type 1:Jbob, 2:Raid0, 3:Raid1, 4:Raid5
        /// </summary>
	    public byte byType;
        /// <summary>
        /// status  0:unknown, 1:active, 2:degraded, 3:inactive, 4:recovering 同步中
        /// </summary>
	    public byte byStatus;
        /// <summary>
        ///  Bytes Aligned
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 2)]
	    public byte[] byReserved;
        /// <summary>
        /// harddisk channel
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 256)]
        public Int32[] nMember;
        /// <summary>
        /// Number of Disk
        /// </summary>
        public Int32 nDiskNUM;
        /// <summary>
        /// Capacity
        /// </summary>
        public Int32 nCapacity;
        /// <summary>
        /// expanded disk tank
        /// </summary>
        public Int32 nTank;
        /// <summary>
        /// Left Capacity,Unit: M
        /// </summary>
        public Int32 nRemainSpace;
    }

    public struct CFG_RAIDGROUP_INFO
    {
        /// <summary>
        /// Number of  Raid
        /// </summary>
	    public Int32 nRaidNum;
        /// <summary>
        /// Raid Group Info
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 16)]
	    public CFG_RAID_INFO[] stuRaidInfo;
    }

    // Storage pool group information
    public struct CFG_STORAGEPOOL_INFO
    {
        /// <summary>
        /// The name of storage pool
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 32)]
	    public byte[] szName;
        /// <summary>
        /// Device Volume 
        /// </summary>
        public Int32 nMemberNum;
        /// <summary>
        /// Device composition
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 16 * 32)]
        public byte[] szMember;
        /// <summary>
        /// Used capacity
        /// </summary>
        public Int32 nUsed;
        /// <summary>
        /// Total capacity 
        /// </summary>
        public Int32 nCapacity;
        /// <summary>
        /// Status	0:unknown 1:active 2:degraded 3:inactive
        /// </summary>
        public Int32 nStatus;
        /// <summary>
        /// JBOD	0:Host, 1:JBOD1, 2:JBOD2 ……
        /// </summary>
        public Int32 nTank;
    }

    public struct CFG_STORAGEPOOLGROUP_INFO
    {
        /// <summary>
        /// The number of storage pool
        /// </summary>
	    public Int32 nStroagePoolNum; 
        /// <summary>
        /// Storage pool information
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 16)]
	    public CFG_STORAGEPOOL_INFO[] stuStoragePoolInfo;
    }


    // The file system group information
    public struct CFG_STORAGEPOSITION_INFO
    {
        /// <summary>
        /// The name of the storage location	
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 32)]
	    public byte[] szName;
        /// <summary>
        /// The name of storage pool	
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 32)]
        public byte[] szStoragePoolName;
        /// <summary>
        /// Used capacity,Unit G	
        /// </summary>
        public Int32 nUsedCapacity;
        /// <summary>
        /// Capacity,Unit G
        /// </summary>
        public Int32 nTotalCapacity;
        /// <summary>
        /// Status 0.Unknown 1.Normal 2.Configuration abnormal 3.Mount abnormal
        /// </summary>
	    public byte byStatus;
        /// <summary>
        /// Byte alignment
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 3)]
        public byte[] byReserved;
    }

    public struct CFG_STORAGEPOSITIONGROUP_INFO
    {
        /// <summary>
        /// The number of stored information
        /// </summary>
	    public Int32 nStoragePositionNum;
        /// <summary>
        /// The file system group information
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 16)]
	    public CFG_STORAGEPOSITION_INFO[] stuStoragePositionInfo;      
    }

    // Front-end equipments group information
    public struct CFG_VIDEOINDEV_INFO
    {
        /// <summary>
        /// Name of front-end equipments
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 32)]
	    public byte[] szDevName; 
        /// <summary>
        /// Device ID	
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 32)]
        public byte[] szDevID;
        /// <summary>
        /// Device type
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 32)]
        public byte[] szDevType;
        /// <summary>
        /// Total number of channels 
        /// </summary>
        public Int32 nTotalChan;
        /// <summary>
        /// Total number of alarm channels
        /// </summary>
	    public Int32 nTotalAlarmChan;
        /// <summary>
        /// Device IP
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 256)]
        public byte[] szIP;
        /// <summary>
        /// Status 0:Unknown 1:Online 2:Offline
        /// </summary>
	    public byte byStatus;
        /// <summary>
        /// Byte alignment
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 3)]
        public byte[] byReserved;
    }

    public  struct CFG_VIDEOINDEVGROUP_INFO
    {
        /// <summary>
        /// Number of front-end equipments
        /// </summary>
	    public Int32 nVideoDevNum; 
        /// <summary>
        /// Front-end equipments group information     
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 256)]
	    public CFG_VIDEOINDEV_INFO[] stuVideoInDevInfo;
    }

    // Channel video group status
    public struct CFG_DEVRECORD_INFO
    {
        /// <summary>
        /// Device name
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 32)]
	    public byte[] szDevName;
        /// <summary>
        /// Device IP	
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 256)]
	    public byte[] szIP;
        /// <summary>
        /// Channel number 
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 32)]
	    public byte[] szChannel;
        /// <summary>
        /// Channel Name	
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 32)]
        public byte[] szChannelName;
        /// <summary>
        /// Storage position information
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 32)]
        public byte[] szStoragePosition;
        /// <summary>
        /// Status 0:Unknown 1: Recording 2:Halt
        /// </summary>
	    public byte byStatus;
        /// <summary>
        /// Byte alignment
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 3)]
	    public byte[] byReserved;
    }

    public  struct CFG_DEVRECORDGROUP_INFO
    {
        /// <summary>
        /// Channel Number
        /// </summary>
	    public Int32 nChannelNum;
        /// <summary>
        /// Channel record status information
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 256)]
        public CFG_DEVRECORD_INFO[] stuDevRecordInfo;
    }

    // Service status
    public struct CFG_IPSERVER_STATUS
    {
        /// <summary>
        /// Supported Server Number
        /// </summary>
	    public Int32  nSupportedServerNum;
        /// <summary>
        /// Supported Server Name Svr Svrd(SVR service daemon) DataBase DataBased(DataBase service daemon) 
        /// NtpServer NtpServerd(NtpServer service daemon) PrivateII PrivateIId(PrivateII service daemon) Samba Nfs Ftp iScsi 
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 16 * 32)] 
	    public byte[] szSupportServer; 
        /// <summary>
        /// Svr Supported subserver information number
        /// </summary>
	    public Int32  nSvrSuppSubServerNum;
        /// <summary>
        /// Svr Supported subserver information CMS DMS	MTS	SS RMS DBR
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 16 * 32)]
	    public byte[] szSvrSuppSubServer;
        /// <summary>
        /// 0:Unknown 1:In service 2:Out of service
        /// The following fields mean the same thing
        /// </summary>
        public byte byCMS;
	    public byte byDMS;
	    public byte byMTS;
	    public byte bySS;
	    public byte byRMS;
	    public byte byDBR;
	    public byte bySvrd;
	    public byte byDataBase;
	    public byte byDataBased;
	    public byte byNtpServer;
	    public byte byNtpServerd;
	    public byte byDahuaII;
	    public byte byDahuaIId;
	    public byte bySAMBA;  
	    public byte byNFS;    
	    public byte byFTP;    
	    public byte byISCSI;  
        /// <summary>
        /// Byte Alignment
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 3)]
	    public byte[] byReserved; 
    }


    public struct SNAPSOURCE_INFO_SINGLE_CHANNEL
    {
        /// <summary>
        /// Enable signal
        /// </summary>
	    public byte		bEnable;
        /// <summary>
        /// Reserved,alignment
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 3)]
	    public byte[] bReserved1;
        /// <summary>
        /// Device name
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 64)]
	    public byte[] bDevice;
        /// <summary>
        /// Video channel number
        /// </summary>
	    public UInt32		dwChannel;
        /// <summary>
        /// Screenshots channel corresponding video channel number
        /// </summary>
	    public UInt32		dwLinkVideoChannel;
        /// <summary>
        /// Reserved
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 512)]
	    public byte[]	bReserved;
    }

    public struct CFG_SNAPSOURCE_INFO
    {
        /// <summary>
        /// Number of channel to configure
        /// </summary>
	    public UInt32 dwCount;
        /// <summary>
        /// SNAPSOURCE_INFO_SINGLE_CHANNEL Array Address
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 256)]
	    public SNAPSOURCE_INFO_SINGLE_CHANNEL[] singleChnSanpInfo;
    }


    // Round tour mode
    public struct CFG_TOUR_MODE
    {
        /// <summary>
        /// Image segmentation model,Reference enumerated type MATRIX_VIEW_SPLITMODE
        /// </summary>
	    public Int32 nViewMode;
        /// <summary>
        /// Represent ViewMod such as:0x00000007:Represent Mode3(SPLIT8)separation 1,2,3 enable signal unlock,the other locked
        /// 0x0000000F Represent separating1,2,3,4 enable signal on e specified mode,some separation of enable signal,using mask presentation
        /// </summary>
	    public UInt32 dwViewSplitMask;
    }

    // SPOT Video matrix solution
   public  struct CFG_VIDEO_MATRIX_PLAN
    {
        /// <summary>
        /// Matrix configuration scheme of enable signal
        /// </summary>
	    public bool bEnable;
        /// <summary>
        /// Matrix wheel cruise intervals,Unit second,>=1
        /// </summary>
	    public Int32 nTourPeriod;
        /// <summary>
        /// Round tour queue number
        /// </summary>
	    public Int32 nTourModeNum;
        /// <summary>
        /// Round tour queue
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 16)]
	    public CFG_TOUR_MODE[]   stuTourMode;
    }

    // SPOT Matrix configuration
    public  struct CFG_VIDEO_MATRIX
    {
        /// <summary>
        /// number of the ability of image segmentation supported
        /// </summary>
	    public Int32 nSupportSplitModeNumber;
        /// <summary>
        /// ability of image segmentation supported
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 16)]
	    public byte[] bySupportSplitMode;
        /// <summary>
        /// Matrix solution number
        /// </summary>
	    public Int32 nMatrixPlanNumber;
        /// <summary>
        /// Matrix solution
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 4)]
	    public CFG_VIDEO_MATRIX_PLAN[] stuMatrixPlan;
    }


    // dsp configuration
    public struct CFG_DSPENCODECAP_INFO
    {
        /// <summary>
        /// Video format mask,Bitwise said equipment can support the video formats
        /// </summary>
	    public UInt32 dwVideoStandardMask;
        /// <summary>
        /// resolution mask,Bitwise said the resolution of the equipment can support
        /// </summary>
	    public UInt32 dwImageSizeMask;
        /// <summary>
        /// Encoding mode mask,Bitwise said the encoding scheme the equipment can support 
        /// </summary>
	    public UInt32 dwEncodeModeMask;
        /// <summary>
        /// Bitwise said multimedia capabilities the equipment can support,
        /// The first expressed support for the main stream
        /// The second expressed support for auxiliary stream 1
        /// The third expressed support for auxiliary stream 2
        /// The fifth expressed support for JPG screenshots
        /// </summary>
	    public UInt32 dwStreamCap;
        /// <summary>
        /// Mean when the main stream is the resolution,the resolution of auxiliary stream mask is supported.
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 32)]
	    public UInt32[] dwImageSizeMask_Assi;
        /// <summary>
        /// DSP the highest coding ability supported
        /// </summary>
	    public UInt32 dwMaxEncodePower;
        /// <summary>
        /// Number of each DSP supporting most input video channels 
        /// </summary>
	    public UInt16 wMaxSupportChannel;
        /// <summary>
        /// DSP If max coding settings in per channel are synchronous；0：non-synchronous ,1：synchronous
        /// </summary>
	    public UInt16 wChannelMaxSetSync;
        /// <summary>
        /// Max acquisition frame rate with different resolution,match with dwVideoStandardMask by bitwise
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 256)]
	    public byte[] bMaxFrameOfImageSize;
        /// <summary>
        /// Attribute,requirements conform to the following conditions when configuring,otherwise configuriton inoperative;
        /// 0:coding ability of main stream+coding ability of auxiliary stream <= coding ability of device,
        /// 1:coding ability of main stream+coding ability of auxiliary stream <= coding ability of device,
        /// coding ability of auxiliary stream <= coding ability of main stream,
        /// Resolution of auxiliary stream <= Resolution of main stream,
        /// Frame rate of main stream and auxiliary stream <= Frame rate of video Forward acquisition
        /// 2:N5 calculation method
        /// Resolution of auxiliary stream <= Resolution of main stream
        /// supported resolution and maximum frame rate query
        /// </summary>
	    public byte bEncodeCap;
        /// <summary>
        /// bResolution length
        /// </summary>
	    public byte byResolutionNum;
        /// <summary>
        /// bResolution_1 length
        /// </summary>
	    public byte byResolutionNum_1;
	    public byte byReserved;
        /// <summary>
        /// Main stream,indexing according to the resolution,If it supports the resolution,bResolution[n] equals max frame rate supported.Otherwise is 0.	
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 256)]
	    public byte[] byResolution;
        /// <summary>
        /// Auxiliary code flow1,following the main stream directions.
        /// </summary>
		[MarshalAs(UnmanagedType.ByValArray, SizeConst = 256)]			
	    public byte[] byResolution_1;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 28)]			
	    public byte[] reserved;
        /// <summary>
        /// Support Image Size,detail view to enumeration CFG_CAPTURE_SIZE
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 256)]
        public byte[] byImageSize;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 256 * 256)]
        public byte[] byImageSize_Assi;
    }

    public  struct VIDEO_INMETERING_INFO_CHANNEL
    {
	    // Capability
	    public  byte bRegion;
	    public  byte bMode;
        /// <summary>
        /// Reserved byte1
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 2)]
	    public  byte[] bReserved1;
    	/// <summary>
    	/// The metering region number
    	/// </summary>
	    public  Int32 nRegionNum; 
        /// <summary>
        /// Metering region, under local,multiple metering regions supported,using relative coordinate system,take mean value as 0~8191
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 8)]
	    public  CFG_RECT[] stuRegions;
        /// <summary>
        /// Metering mode,0:average metering,1:partial metering
        /// </summary>
	    public  byte byMode;
        /// <summary>
        /// Reserved byte2
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 3)]
	    public  byte[] bReserved2;
        /// <summary>
        /// Reserved byte3
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 32)]
	    public  byte[] bReserved3;
    }

    // Metering configuration(CFG_CMD_VIDEO_INMETERING) is a array,each video inputting channel for a configuration
    public struct CFG_VIDEO_INMETERING_INFO
    {
        /// <summary>
        /// ChannelNumber
        /// </summary>
	    public  Int32 nChannelNum;
        /// <summary>
        /// Each channel metering information,the subscript corresponding channel number
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 256)]
	    public  VIDEO_INMETERING_INFO_CHANNEL[]	stuMeteringMode;
    }


    // Data flow stat alarm information configuration 
    public struct CFG_TRAFFIC_FLOWSTAT_ALARM_INFO
    {
        /// <summary>
        /// Whether being enable signal
        /// </summary>
	    public bool bEnable;
        /// <summary>
        /// Statistical cycle,unit：minute
        /// </summary>
	    public int nPeriod;
        /// <summary>
        /// Vehicle number limitation in statistical cycle,unit：one
        /// </summary>
	    public int nLimit;
        /// <summary>
        /// Vehicle number alarm restore in statistical cycle,unit：one
        /// </summary>
	    public int nRestore;
        /// <summary>
        /// Time from alarm detected to being reported, unit:second,scope 1~65535
        /// </summary>
        public int nDelay;
        /// <summary>
        /// Alarm time interval, unit:second,scope 1~65535
        /// </summary>
	    public int nInterval;
        /// <summary>
        /// Report Times,1~255
        /// </summary>
	    public int nReportTimes;
        /// <summary>
        /// Current planned time section
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 7 * 6)]
	    public CFG_TIME_SECTION[] stCurrentTimeSection;
    }

    public struct CFG_TRAFFIC_FLOWSTAT_INFO_LANE
    {
	    // Capability
	    public byte abEnable;
        /// <summary>
        /// If enable
        /// </summary>
	    public byte bEnable;
        /// <summary>
        /// Alarm Upper Information
        /// </summary>
	    public CFG_TRAFFIC_FLOWSTAT_ALARM_INFO  stuAlarmUpperInfo;
        /// <summary>
        /// Alarm Low Information
        /// </summary>
	    public CFG_TRAFFIC_FLOWSTAT_ALARM_INFO  stuAlarmLowInfo; 
    }


    // Video input night special configuration options,when dark at night automatically switch to the night configuration parameters
    public struct CFG_VIDEO_IN_NIGHT_OPTIONS
    {
        /// <summary>
        /// 0-No switching；1-Switching by the brightness；2-Switching by the time
        /// </summary>
	    public byte bySwitchMode;
        /// <summary>
        /// Brightness threshold 0~100	
        /// </summary>
	    public byte byBrightnessThreshold ;
        /// <summary>
        /// Roughly the sunrise and sunset time,after the sunset or before the sunrise,use the night special configuration.
        /// </summary>
	    public byte bySunriseHour;
        /// <summary>
        /// 00:00:00 ~ 23:59:59
        /// </summary>
	    public byte bySunriseMinute;
	    public byte bySunriseSecond;
	    public byte bySunsetHour;
	    public byte bySunsetMinute;
	    public byte bySunsetSecond;  
        /// <summary>
        /// Red gain control,white balance is active under "Custom" mode 0~100
        /// </summary>
	    public byte byGainRed;
        /// <summary>
        /// Green gain control,white balance is active under "Custom" mode 0~100
        /// </summary>
	    public byte byGainBlue;
        /// <summary>
        /// Blue gain control,white balance is active under "Custom" mode 0~100
        /// </summary>
	    public byte byGainGreen;
        /// <summary>
        /// Exposure mode；Values range depends on the equipment capability：0-auto-exposure,1-exposure level 1,
        /// 2-exposure level 2…n-1 max exposure level number n Automatic exposure with a time limit n+1 Custom manual exposure time (n==byExposureEn）
        /// </summary>
	    public byte byExposure;
        /// <summary>
        /// Least automatic exposure time or Custom manual exposure time,unit is millisecond,values 0.1ms~80ms
        /// </summary>
	    public float fExposureValue1;
        /// <summary>
        /// Most automatic exposure time or Custom manual exposure time,unit is millisecond,values0.1ms~80ms	
        /// </summary>
	    public float fExposureValue2;
        /// <summary>
        /// White balance, 0-"Disable", 1-"Auto", 2-"Custom", 3-"Sunny", 4-"Cloudy", 5-"Home",
        /// 6-"Office", 7-"Night", 8-"HighColorTemperature", 9-"LowColorTemperature", 10-"AutoColorTemperature", 
        /// 11-"CustomColorTemperature"
        /// </summary>
	    public byte byWhiteBalance ;
        /// <summary>
        /// 0~100, GainAuto is true means the upper limit of automatic gain,otherwise fixed gain value
        /// </summary>
	    public byte byGain;
        /// <summary>
        /// Auto gain
        /// </summary>
	    public byte bGainAuto;
        /// <summary>
        /// Auto iris
        /// </summary>
	    public byte bIrisAuto;
        /// <summary>
        /// External synchronous phase settings 0~360
        /// </summary>
	    public float fExternalSyncPhase;
        /// <summary>
        /// Reserved
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 100)]
	    public byte[] reserved; 
    } 


    // Flash configuration
    public struct CFG_FLASH_CONTROL
    {
        /// <summary>
        /// Working pattern,0-No Flash,1-Keep Flash,2-Auto Flash
        /// </summary>
	    public byte byMode;
        /// <summary>
        /// Working value, 0-0us, 1-64us, 2-128us, 3-192...15-960us
        /// </summary>
	    public byte byValue;
        /// <summary>
        /// Burst mode, 0-low level 1-high level 2-rising edge 3-failling edge
        /// </summary>
	    public byte byPole;
        /// <summary>
        /// Brightness prevalue  interval 0~100
        /// </summary>
	    public byte byPreValue;
        /// <summary>
        /// Duty-cycle, 0~100
        /// </summary>
	    public byte byDutyCycle;
        /// <summary>
        /// Frequency multiple, 0~10
        /// </summary>
	    public byte byFreqMultiple;
        /// <summary>
        /// Reserved
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 122)]
	    public byte[] reserved;
    }

        // Snapshot configuration special options
    public struct CFG_VIDEO_IN_SNAPSHOT_OPTIONS
    {
        /// <summary>
        /// Red gain control,white balance is active under "Custom" mode 0~100
        /// </summary>
	    public byte byGainRed;
        /// <summary>
        /// Green gain control,white balance is active under "Custom" mode 0~100
        /// </summary>
	    public byte byGainBlue;
        /// <summary>
        /// Blue gain control,white balance is active under "Custom" mode 0~100
        /// </summary>
	    public byte byGainGreen;
        /// <summary>
        /// Exposure mode；Values range depends on the equipment capability：0-auto-exposure,1-exposure level 1,
        /// 2-exposure level 2…n-1 max exposure level number n Automatic exposure with a time limit n+1 Custom manual exposure time (n==byExposureEn）
        /// </summary>
	    public byte byExposure;
        /// <summary>
        /// Least automatic exposure time or Custom manual exposure time,unit is millisecond,values 0.1ms~80ms
        /// </summary>
	    public float fExposureValue1;
        /// <summary>
        /// Most automatic exposure time,unit is millisecond,values0.1ms~80ms	
        /// </summary>
	    public float fExposureValue2;
        /// <summary>
        /// White Balance, 0-"Disable", 1-"Auto", 2-"Custom", 3-"Sunny", 4-"Cloudy",
        /// 5-"Home", 6-"Office", 7-"Night", 8-"HighColorTemperature", 9-"LowColorTemperature", 
        /// 10-"AutoColorTemperature", 11-"CustomColorTemperature"
        /// </summary>
	    public byte byWhiteBalance;
        /// <summary>
        /// Color temperature level, White Balance is active under "CustomColorTemperature" mode
        /// </summary>
	    public byte byColorTemperature;
        /// <summary>
        /// Auto gain
        /// </summary>
	    public byte bGainAuto;
        /// <summary>
        /// Gain contro, GainAuto is true means the upper limit of auto gain,otherwise fixed gain value
        /// </summary>
	    public byte byGain;
        /// <summary>
        /// Reversed
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 112)]
	    public byte[] reversed;
    } 

    // Video fore-end input options
    public struct CFG_VIDEO_IN_OPTIONS
    {
        /// <summary>
        /// Backlight compensation：Backlight compensation level values range depends on the equipment capacity,0-close,1-Backlight compensation intensity1,
        /// 2-Backlight compensation intensity2…n-Max backlight compensation level
        /// </summary>
	    public byte byBacklight;
        /// <summary>
        /// Day/Night mode；0-Always colorful,1-Auto switching by brightness,2-Always black and white
        /// </summary>
	    public byte byDayNightColor;
        /// <summary>
        /// White Balance, 0-"Disable", 1-"Auto", 2-"Custom", 3-"Sunny", 4-"Cloudy", 5-"Home",
        /// 6-"Office", 7-"Night", 8-"HighColorTemperature", 9-"LowColorTemperature",
        /// 10-"AutoColorTemperature", 11-"CustomColorTemperature"
        /// </summary>
	    public byte byWhiteBalance;
        /// <summary>
        /// Color temperature level, White Balance is active under "CustomColorTemperature" mode
        /// </summary>
	    public byte byColorTemperature;
        /// <summary>
        /// Mirror
        /// </summary>
	    public byte bMirror;
        /// <summary>
        /// Reversal
        /// </summary>
	    public byte bFlip;
        /// <summary>
        /// Auto iris
        /// </summary>
	    public byte bIrisAuto;
        /// <summary>
        /// According to the ambient light open infrared compensation lamp automatically	
        /// </summary>
	    public byte bInfraRed;
        /// <summary>
        /// Red gain control,white balance is active under "Custom" mode 0~100
        /// </summary>
	    public byte byGainRed;
        /// <summary>
        /// Green gain control,white balance is active under "Custom" mode 0~100
        /// </summary>
	    public byte byGainBlue;
        /// <summary>
        /// Blue gain control,white balance is active under "Custom" mode 0~100
        /// </summary>
	    public byte byGainGreen;
        /// <summary>
        /// Exposure mode；Values range depends on the equipment capability：0-auto-exposure,1-exposure level 1,
        /// 2-exposure level 2…n-1 max exposure level number n Automatic exposure with a time limit n+1 Custom manual exposure time (n==byExposureEn）
        /// </summary>
	    public byte byExposure;
        /// <summary>
        /// Least automatic exposure time or Custom manual exposure time,unit is millisecond,values 0.1ms~80ms
        /// </summary>
	    public float fExposureValue1;
        /// <summary>
        /// Most automatic exposure time,unit is millisecond,values0.1ms~80ms	
        /// </summary>
	    public float fExposureValue2;
        /// <summary>
        /// Auto Gain
        /// </summary>
	    public byte bGainAuto;
        /// <summary>
        /// Gain contro, GainAuto is true means the upper limit of auto gain,otherwise fixed gain value
        /// </summary>
	    public byte byGain;
        /// <summary>
        /// Signal format, 0-Inside(internal input) 1-BT656 2-720p 3-1080p  4-1080i  5- 1080sF
        /// </summary>
	    public byte bySignalFormat;
        /// <summary>
        /// 0-nonspinning,1-clockwise 90°,2-anticlockwise 90°	
        /// </summary>
	    public byte byRotate90;
        /// <summary>
        /// External synchronous phase Settings 0~360	
        /// </summary>
	    public float fExternalSyncPhase;
        /// <summary>
        /// External synchronous signal input,0-Internal synchronization 1-external synchronization
        /// </summary>
	    public byte byExternalSync;
        /// <summary>
        /// reserved
        /// </summary>
	    public byte reserved0;
        /// <summary>
        /// Double shutter, 0-Disable,1-Double shutter full frame rate,only different between images and videos with shutter parameters,2-Double shutter half frame rate,means parameters of images,videos and white balance are totally different
        /// </summary>
	    public byte byDoubleExposure;
        /// <summary>
        /// Wide dynamic value
        /// </summary>
	    public byte byWideDynamicRange;
        /// <summary>
        /// Night Options
        /// </summary>
	    public CFG_VIDEO_IN_NIGHT_OPTIONS stuNightOptions;
        /// <summary>
        /// Flash configuration
        /// </summary>
	    public CFG_FLASH_CONTROL	stuFlash;
        /// <summary>
        /// Snapshot options, active with double shutter
        /// </summary>
	    public CFG_VIDEO_IN_SNAPSHOT_OPTIONS stuSnapshot;
        /// <summary>
        /// Reserved
        /// </summary>
       /// [MarshalAs(UnmanagedType.ByValArray, SizeConst = 96)]
	    public byte[] reserved;
    }

    public struct CFG_RTSP_INFO_IN
    {
	    Int32 nStructSize;
        /// <summary>
        /// If the whole function is enable
        /// </summary>
	    bool bEnable;
        /// <summary>
        /// RTSP service port
        /// </summary>
        Int32 nPort;
        /// <summary>
        /// RTP start port
        /// </summary>
        Int32 nRtpStartPort;
        /// <summary>
        /// RTP end port
        /// </summary>
        Int32 nRtpEndPort;
        /// <summary>
        /// RtspOverHttp enable
        /// </summary>
	    bool bHttpEnable;
        /// <summary>
        /// RtspOverHttp Port
        /// </summary>
        Int32 nHttpPort; 
    }

    public struct CFG_RTSP_INFO_OUT
    {
	    Int32 nStructSize;
        /// <summary>
        /// If the whole function is enable
        /// </summary>
	    bool bEnable; 
        /// <summary>
        /// RTSP service port
        /// </summary>
        Int32 nPort;
        /// <summary>
        /// RTP start port
        /// </summary>
        Int32 nRtpStartPort;
        /// <summary>
        /// RTP end port
        /// </summary>
        Int32 nRtpEndPort;
        /// <summary>
        /// RtspOverHttp Enable
        /// </summary>
        bool bHttpEnable;
        /// <summary>
        /// RtspOverHttp Port
        /// </summary>
        Int32 nHttpPort;
    }

    public struct CFG_TRAFFICSNAPSHOT_NEW_INFO
    {
        /// <summary>
        /// Effective members number
        /// </summary>
	    public Int32 nCount; 
        /// <summary>
        /// Traffic snapshot table array
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 8)]
	    public CFG_TRAFFICSNAPSHOT_INFO[]	stInfo;
    }

    public struct CFG_MULTICASTS_INFO_IN
    {
	    public Int32 nStructSize;
        /// <summary>
        /// TS multicast information
        /// CFG_MULTICAST_INFO*
        /// </summary>
        public IntPtr pTSMulticast;
        /// <summary>
        /// Effective TS array number
        /// </summary>
        public Int32 nTSCount;
        /// <summary>
        /// RTP multicast information
        /// CFG_MULTICAST_INFO*
        /// </summary>
        public IntPtr pRTPMulticast;
        /// <summary>
        ///  Effective RTP array number
        /// </summary>
        public Int32 nRTPCount;
    }

    // RTSP Input and output parameters configuration structure
    public struct CFG_MULTICAST_INFO
    {
	    public Int32  nStructSize;
	    public byte abStreamType;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 3)]
	    public byte[] byReserved;
        /// <summary>
        /// If enable
        /// </summary>
	    public bool bEnable;
        /// <summary>
        /// Multicast address
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 256)]
	    public byte[] szMulticastAddr;
        /// <summary>
        /// Multicast Port
        /// </summary>
	    public Int32  nPort;
        /// <summary>
        /// Unicast address,used for multicast specified network card in detail
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 256)]
	    public byte[] szLocalAddr; 
        /// <summary>
        /// Channel ID
        /// </summary>
	    public Int32  nChannelID;
        /// <summary>
        /// Stream Type 0-main stream, 1-Auxiliary stream1,2-Auxiliary stream2,3-Auxiliary stream3
        /// </summary>
	    public Int32  nStreamType; 
    }

    public struct CFG_MULTICASTS_INFO
    {
	    public Int32 nStructSize;
        /// <summary>
        /// Max multicast configuration
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 256)]
	    public CFG_MULTICAST_INFO[] stuMultiInfo;
        /// <summary>
        /// Effective array number
        /// </summary>
	    public Int32 nCount;
    }

    public struct CFG_MULTICASTS_INFO_OUT
    {
	    public Int32                  nStructSize;
        /// <summary>
        /// TS multicast information
        /// </summary>
	    public CFG_MULTICASTS_INFO  stuTSMulticast;
        /// <summary>
        /// RTP multicast information
        /// </summary>
	    public CFG_MULTICASTS_INFO  stuRTPMulticast;
    }

    ///////////////////////////////////Video diagnostic configuration///////////////////////////////////////
    // Video jitter detection
    public struct CFG_VIDEO_DITHER_DETECTION
    {
        /// <summary>
        /// Enable configuration
        /// </summary>
	    public bool bEnable;
        /// <summary>
        /// Minimum duration unit：second 0~65535
        /// </summary>
	    public Int32 nMinDuration;
        /// <summary>
        /// Warning threshold value 1-100
        /// </summary>
	    public byte byThrehold1;
        /// <summary>
        /// Alarm threshold value 1-100
        /// </summary>
	    public byte byThrehold2;
    }

    // Stripes detection
    public struct CFG_VIDEO_STRIATION_DETECTION 
    {
        /// <summary>
        /// Enable configuration
        /// </summary>
	    public bool bEnable;
        /// <summary>
        /// Minimum duration unit：second 0~65535
        /// </summary>
	    public Int32 nMinDuration;
        /// <summary>
        /// Warning threshold value 1-100
        /// </summary>
	    public byte byThrehold1;
        /// <summary>
        /// Alarm threshold value 1-100
        /// </summary>
	    public byte byThrehold2;
        /// <summary>
        /// Byte Alignment
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 2)]   
	    public byte[] byReserved1;
        /// <summary>
        /// UV Detection or not					
        /// </summary>
	    public bool bUVDetection;
    }

    // VIDEO LOSS DETECTION
    public struct CFG_VIDEO_LOSS_DETECTION
    {
        /// <summary>
        /// Enable configuration
        /// </summary>
	    public bool bEnable;
        /// <summary>
        /// Minimum duration unit：second 0~65535
        /// </summary>
	    public Int32 nMinDuration;
    }

    // VIDEO COVER DETECTION
    public struct CFG_VIDEO_COVER_DETECTION
    {
        /// <summary>
        /// Enable configuration
        /// </summary>
	    public bool bEnable;
        /// <summary>
        /// Minimum duration unit：second 0~65535
        /// </summary>
	    public Int32 nMinDuration;
        /// <summary>
        /// Warning threshold value 1-100
        /// </summary>
	    public byte byThrehold1;
        /// <summary>
        /// Alarm threshold value 1-100
        /// </summary>
	    public byte byThrehold2;
    }

    // VIDEO FROZEN DETECTION
    public struct CFG_VIDEO_FROZEN_DETECTION
    {
        /// <summary>
        /// Enable configuration
        /// </summary>
	    public bool bEnable;
        /// <summary>
        /// Minimum duration unit：second 0~65535
        /// </summary>
	    public Int32 nMinDuration;
    }

    // BRIGHTNESS DETECTION
    public struct CFG_VIDEO_BRIGHTNESS_DETECTION
    {	
        /// <summary>
        /// Enable configuration
        /// </summary>
	    public bool bEnable;
        /// <summary>
        /// Minimum duration unit：second 0~65535
        /// </summary>
	    public Int32 nMinDuration;
        /// <summary>
        /// Warning threshold value 1-100
        /// </summary>
	    public byte bylowerThrehold1;
        /// <summary>
        /// Alarm threshold value 1-100
        /// </summary>
	    public byte bylowerThrehold2;
        /// <summary>
        /// Warning threshold value 1-100
        /// </summary>
	    public byte byUpperThrehold1;
        /// <summary>
        /// Alarm threshold value 1-100
        /// </summary>
	    public byte byUpperThrehold2;
    }

    // CONTRAST DETECTION
    public struct CFG_VIDEO_CONTRAST_DETECTION
    {	
        /// <summary>
        /// Enable configuration
        /// </summary>
	    public bool bEnable;
        /// <summary>
        /// Minimum duration unit：second 0~65535
        /// </summary>
	    public Int32 nMinDuration;
        /// <summary>
        /// Warning threshold value 1-100
        /// </summary>
	    public byte bylowerThrehold1;
        /// <summary>
        /// Alarm threshold value 1-100
        /// </summary>
	    public byte bylowerThrehold2;
        /// <summary>
        /// Warning threshold value 1-100
        /// </summary>
	    public byte byUpperThrehold1;
        /// <summary>
        /// Alarm threshold value 1-100
        /// </summary>
	    public byte byUpperThrehold2;
    }

    // UNBALANCE DETECTION
    public struct CFG_VIDEO_UNBALANCE_DETECTION
    {	
        /// <summary>
        /// Enable configuration
        /// </summary>
	    public bool bEnable;
        /// <summary>
        /// Minimum duration unit：second 0~65535
        /// </summary>
	    public Int32 nMinDuration;
        /// <summary>
        /// Warning threshold value 1-100
        /// </summary>
	    public byte byThrehold1;
        /// <summary>
        /// Alarm threshold value 1-100
        /// </summary>
	    public byte byThrehold2;
    }

    // NOISE DETECTION
    public struct CFG_VIDEO_NOISE_DETECTION
    {	
        /// <summary>
        /// Enable configuration
        /// </summary>
	    public bool bEnable;
        /// <summary>
        /// Minimum duration unit：second 0~65535
        /// </summary>
	    public Int32 nMinDuration;
        /// <summary>
        /// Warning threshold value 1-100
        /// </summary>
	    public byte byThrehold1;
        /// <summary>
        /// Alarm threshold value 1-100
        /// </summary>
	    public byte byThrehold2;
    }

    // BLUR DETECTION
    public struct CFG_VIDEO_BLUR_DETECTION
    {
        /// <summary>
        /// Enable configuration
        /// </summary>
	    public bool bEnable;
        /// <summary>
        /// Minimum duration unit：second 0~65535
        /// </summary>
	    public Int32 nMinDuration;
        /// <summary>
        /// Warning threshold value 1-100
        /// </summary>
	    public byte byThrehold1;
        /// <summary>
        /// Alarm threshold value 1-100
        /// </summary>
	    public byte byThrehold2;
    }

    // SCENECHANGE DETECTION
    public struct CFG_VIDEO_SCENECHANGE_DETECTION
    {	
        /// <summary>
        /// Enable configuration
        /// </summary>
	    public bool bEnable;
        /// <summary>
        /// Minimum duration unit：second 0~65535
        /// </summary>
	    public Int32 nMinDuration;
        /// <summary>
        /// Warning threshold value 1-100
        /// </summary>
	    public byte byThrehold1;
        /// <summary>
        /// Alarm threshold value 1-100
        /// </summary>
	    public byte byThrehold2;
    }

    public struct CFG_VIDEO_DIAGNOSIS_PROFILE
    {
        /// <summary>
        /// Name
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 260)]     
	    public byte[] szName;

        /// <summary>
        /// VIDEO DITHER DETECTION
        /// CFG_VIDEO_DITHER_DETECTION*
        /// </summary>
	    public IntPtr pstDither;
        /// <summary>
        /// IDEO STRIATION DETECTION
        /// CFG_VIDEO_STRIATION_DETECTION*
        /// </summary>
	    public IntPtr	pstStriation;
        /// <summary>
        /// VIDEO LOSS DETECTION
        /// CFG_VIDEO_LOSS_DETECTION*
        /// </summary>
	    public IntPtr pstLoss;
        /// <summary>
        /// VIDEO COVER DETECTION
        /// CFG_VIDEO_COVER_DETECTION*
        /// </summary>
	    public IntPtr pstCover;
        /// <summary>
        /// VIDEO FROZEN DETECTION
        /// CFG_VIDEO_FROZEN_DETECTION*
        /// </summary>
	    public IntPtr pstFrozen;
        /// <summary>
        /// VIDEO BRIGHTNESS DETECTION
        /// CFG_VIDEO_BRIGHTNESS_DETECTION*
        /// </summary>
	    public IntPtr pstBrightness;
        /// <summary>
        /// CONTRAST DETECTION
        /// CFG_VIDEO_CONTRAST_DETECTION*
        /// </summary>
	    public IntPtr pstContrast;
        /// <summary>
        /// UNBALANCE DETECTION
        /// CFG_VIDEO_UNBALANCE_DETECTION*
        /// </summary>
	    public IntPtr pstUnbalance;
        /// <summary>
        /// NOISE DETECTION
        /// CFG_VIDEO_NOISE_DETECTION*
        /// </summary>
	    public IntPtr pstNoise;
        /// <summary>
        /// BLUR DETECTION
        /// CFG_VIDEO_BLUR_DETECTION*
        /// </summary>
	    public IntPtr pstBlur;
        /// <summary>
        /// SCENECHANGE DETECTION
        /// CFG_VIDEO_SCENECHANGE_DETECTION*
        /// </summary>
	    public IntPtr pstSceneChange;
    }

    // Video diagnostic parameter list(CFG_CMD_VIDEODIAGNOSIS_PROFILE),Support for multiple parameter table,With the table name to index   The caller applify for memory and initialize
    public struct CFG_VIDEODIAGNOSIS_PROFILE
    {
        /// <summary>
        /// The caller distributing parameter table number According to the ability to set
        /// </summary>
	    public Int32 nTotalProfileNum;
        /// <summary>
        /// Return Profile Number
        /// </summary>
	    public Int32 nReturnProfileNum;
        /// <summary>
        /// The caller distributing nProfileCount VIDEO_DIAGNOSIS_PROFILE
        /// CFG_VIDEO_DIAGNOSIS_PROFILE*
        /// </summary>
	    public IntPtr pstProfiles;
    }

    // Device detail information
    public struct CFG_TASK_REMOTEDEVICE
    {
        /// <summary>
        /// Device address or domain name
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 260)]  
	    public byte[] szAddress;
        /// <summary>
        /// Port ID
        /// </summary>
	    public UInt32 dwPort;
        /// <summary>
        /// User Name
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 260)]  
	    public byte[] szUserName;
        /// <summary>
        /// Password
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 260)]  
	    public byte[] szPassword;
        /// <summary>
        /// Protocol type of equipment connection
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 260)]  
	    public byte[] szProtocolType;
    }
    
    public struct CFG_TAST_SOURCES
    {
	    // Capability
	    public byte abDeviceID;
	    public byte abRemoteDevice;
        /// <summary>
        /// Device ID
        /// </summary>
	    public byte[] szDeviceID;
        /// <summary>
        /// Device detail information
        /// </summary>
	    public CFG_TASK_REMOTEDEVICE stRemoteDevice;
        /// <summary>
        /// Video Channel ID
        /// </summary>
	    public Int32 nVideoChannel;
        /// <summary>
        /// Video Stream Type
        /// </summary>
	    public CFG_EM_STREAM_TYPE emVideoStream;
        /// <summary>
        /// Diagnosis duration
        /// </summary>
	    public Int32 nDuration;
    }

    public struct CFG_DIAGNOSIS_TASK
    {
        /// <summary>
        /// Task Name
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 260)]         
	    public byte[] szTaskName;
        /// <summary>
        /// Profile Name used by this task
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 260)]         
	    public byte[] szProfileName;
        /// <summary>
        /// The number of data source caller assigned task according to the ability to set
        /// </summary>
	    public Int32 nTotalSourceNum;
        /// <summary>
        /// Return Source Number
        /// </summary>
	    public Int32 nReturnSourceNum;
        /// <summary>
        /// Task data source the caller to allocate memory nTotalSourceNum
        /// CFG_TAST_SOURCES*
        /// </summary>
	    public IntPtr pstSources;
    };

    // Video diagnostic tasks list(CFG_CMD_VIDEODIAGNOSIS_TASK),Different tasks  index by name The caller application memory and initialized 
    public struct CFG_VIDEODIAGNOSIS_TASK
    {
        /// <summary>
        /// The number of data source caller assigned task according to the ability to set
        /// </summary>
	    public Int32 nTotalTaskNum;
        /// <summary>
        /// Return Task Number
        /// </summary>
	    public Int32 nReturnTaskNum;
        /// <summary>
        /// Task Configuration the caller to allocate memory nTotalTaskNum
        /// CFG_DIAGNOSIS_TASK*
        /// </summary>
	    public IntPtr pstTasks;
    }

    // Video diagnostic program
    public struct CFG_PROJECT_TASK
    {
        /// <summary>
        /// Task enable or not
        /// </summary>
	    public bool bEnable;
        /// <summary>
        /// Task Name
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 260)]
	    public byte[] szTaskName;
        /// <summary>
        /// Task time section
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 7 * 6)]
	    public CFG_TIME_SECTION[] stTimeSection; 
    }

    public struct CFG_DIAGNOSIS_PROJECT
    {
        /// <summary>
        /// Project Name
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 260)]
	    public byte[] szProjectName;
        /// <summary>
        /// The caller number assigned task list according to the ability to set
        /// </summary>
	    public Int32 nTotalTaskNum;
        /// <summary>
        /// Return Task Number
        /// </summary>
	    public Int32 nReturnTaskNum;
        /// <summary>
        ///  Task list the caller allocate memory nTotalTaskNum
        /// CFG_PROJECT_TASK*
        /// </summary>
	    public IntPtr pstProjectTasks;
    }

    // Frequency in the diagnosis of the schedule(CFG_CMD_VIDEODIAGNOSIS_PROJECT),Different plans index by name The caller applify for memory and initialize
    public struct CFG_VIDEODIAGNOSIS_PROJECT
    {
        /// <summary>
        /// The caller assigned task number according to the ability to set
        /// </summary>
	    public Int32 nTotalProjectNum;
        /// <summary>
        /// Return Project Number
        /// </summary>
	    public Int32 nReturnProjectNum;
        /// <summary>
        /// Plan allocation the caller allocate memory nTotalProjectNum
        /// CFG_DIAGNOSIS_PROJECT*
        /// </summary>
	    public IntPtr pstProjects;
    }

    // Video in the diagnosis of the global table(CFG_CMD_VIDEODIAGNOSIS_GLOBAL),Each channel supportting a diagnosis of configuration 
    public struct CFG_VIDEODIAGNOSIS_GLOBAL_CHNNL
    {
        /// <summary>
        /// Project enable or not
        /// </summary>
	    public bool bEnable;
        /// <summary>
        /// Configuration applicated immediately	Apply now means parameter table,changes of tasks, plan take effect immediately,or perform after the current task completed.
        /// </summary>
	    public bool bApplyNow;
        /// <summary>
        /// Project Name
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 260)] 
	    public byte[] szProjectName;
    }

    public struct CFG_VIDEODIAGNOSIS_GLOBAL
    {
        /// <summary>
        /// Caller distributing global configuration number according to the ability to set
        /// </summary>
	    public Int32 nTotalGlobalNum;
        /// <summary>
        /// Return Global Configuration Number
        /// </summary>
	    public Int32 nReturnGlobalNum;
        /// <summary>
        /// Video diagnostic global configuration the caller allocate memory nGlobalCount CFG_VIDEODIAGNOSIS_GLOBAL_CHNNL
        /// CFG_VIDEODIAGNOSIS_GLOBAL_CHNNL	*
        /// </summary>
	    public IntPtr pstGlobals;
    }

    // STORAGEGROUP INFORMATION
    public struct CFG_STORAGEGROUP_INFO
    {
        /// <summary>
        /// STORAGEGROUP NAME
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 32)]
	    public byte[] szGroupName;
        /// <summary>
        /// Physical disk serial buffer
        /// BYTE*
        /// </summary>
	    public IntPtr byDisks;
        /// <summary>
        /// Buffer byDisks length
        /// </summary>
	    public Int32 nBufSize;
        /// <summary>
        /// STORAGEGROUP DISK NUMBER
        /// </summary>
	    public Int32 nDiskNum;
        /// <summary>
        /// STORAGEGROUP serial number(1~Maximum number of hard disk)
        /// </summary>
	    public Int32 nGroupIndex;
    }

    // Device workstate information
    public struct CFG_TRAFFIC_WORKSTATE_INFO
    {
        /// <summary>
        /// Channel ID
        /// </summary>
	    public Int32 nChannelID;
        /// <summary>
        /// Snap Mode
        /// </summary>
	    public CFG_TRAFFIC_SNAP_MODE   emSnapMode;
        /// <summary>
        /// Snap match mode: 0-Non real-time matching way,Alarm before snapping,Snap frame not alarm frame;  1-Real-time matching mode,Alarm frame and snap frame is the same frame
        /// </summary>
	    public Int32 nMatchMode;
    }

    // Recording-storagegroup corresponding information
    public struct CFG_RECORDTOGROUP_INFO
    {
        /// <summary>
        /// Channel ID
        /// </summary>
	    public Int32 nChannelID;
        /// <summary>
        /// Enable signal    
        /// </summary>
	    public bool bEnable; 
        /// <summary>
        /// STORAGEGROUP NAME, read only
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 32)]         
	    public byte[] szGroupName;
        /// <summary>
        /// STORAGEGROUP Number(1~grail group, 0 no corresponding disk group),by this parameter  associating with CFG_STORAGE_GROUP_INFO
        /// </summary>
	    public Int32 nGroupIndex;
    }

    // Channel Name
    public struct AV_CFG_ChannelName
    {
	    public Int32 nStructSize;
        /// <summary>
        /// Camera unique numbe
        /// </summary>
	    public Int32 nSerial;
        /// <summary>
        /// Channel Name
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 64)]
        public byte[] szName;
    };

    // Record Mode
    public struct AV_CFG_RecordMode
    {
        public Int32 nStructSize;
        /// <summary>
        /// Record Mode, 0-Auto record,1-manual record,2-record close
        /// </summary>
        public Int32 nMode;
        /// <summary>
        /// ExtraRecord Mode, 0-Auto record,1-manual record,2-record close
        /// </summary>
        public Int32 nModeExtra1;
    }

    // Video output properties
    public struct AV_CFG_VideoOutAttr
    {
        public Int32 nStructSize;
        /// <summary>
        /// Left margin, ratio, 0~100
        /// </summary>
        public Int32 nMarginLeft;
        /// <summary>
        /// top margin, ratio, 0~100
        /// </summary>
        public Int32 nMarginTop;
        /// <summary>
        /// Right margin, ratio, 0~100
        /// </summary>
        public Int32 nMarginRight;
        /// <summary>
        /// Bottom margin, ratio, 0~100
        /// </summary>
        public Int32 nMarginBottom;
        /// <summary>
        /// Brightness, 0~100
        /// </summary>
        public Int32 nBrightness;
        /// <summary>
        /// Contrast, 0~100
        /// </summary>
        public Int32 nContrast;
        /// <summary>
        /// Saturation, 0~100
        /// </summary>
        public Int32 nSaturation;
        /// <summary>
        /// Hue, 0~100
        /// </summary>
        public Int32 nHue;
        /// <summary>
        /// Horizontal resolution
        /// </summary>
        public Int32 nWidth;
        /// <summary>
        /// Vertical resolution
        /// </summary>
        public Int32 nHeight;
        /// <summary>
        /// Color depth
        /// </summary>
        public Int32 nBPP;
        /// <summary>
        /// 0-Auto, 1-TV, 2-VGA, 3-DVI
        /// </summary>
        public Int32 nFormat;
        /// <summary>
        /// Refresh rate
        /// </summary>
        public Int32 nRefreshRate;
        /// <summary>
        /// Output image enhancement
        /// </summary>
        public bool bIQIMode;
    };

    // Remote equipment
    public  struct AV_CFG_RemoteDevice 
    {
	    public Int32 nStructSize;
        /// <summary>
        /// Enable signal
        /// </summary>
	    public bool bEnable;
        /// <summary>
        /// Device ID
        /// </summary> 
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 64)]
	    public byte[] szID;
        /// <summary>
        /// Device IP
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 32)] 
	    public byte[] szIP;
        /// <summary>
        /// Port
        /// </summary>
	    public Int32 nPort;
        /// <summary>
        /// Protocol type
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 32)] 
	    public byte[] szProtocol;
        /// <summary>
        /// User Name
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 64)] 
	    public byte[] szUser;
	    /// <summary>
	    /// Password
	    /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 64)] 
	    public byte[] szPassword;
        /// <summary>
        /// Device serial number
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 32)] 
	    public byte[] szSerial;
        /// <summary>
        /// Device class
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 16)] 
	    public byte[] szDevClass;
        /// <summary>
        /// Device type
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 32)] 
	    public byte[] szDevType;
        /// <summary>
        /// Machine Name
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 64)] 
	    public byte[] szName;
        /// <summary>
        /// Machine deployment address
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 128)] 
	    public byte[] szAddress;
        /// <summary>
        /// Machine group
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 64)]
        public byte[] szGroup;
        /// <summary>
        /// Definition, 0-SD, 1-HD
        /// </summary>
	    public Int32 nDefinition;
        /// <summary>
        /// Video input channel number
        /// </summary>
	    public Int32 nVideoChannel;
        /// <summary>
        /// Audio input channel number
        /// </summary>
	    public Int32 nAudioChannel;
    };

    // Remote channel
    public struct AV_CFG_RemoteChannel 
    {
	    public Int32 nStructSize;
        /// <summary>
        /// Enable signal
        /// </summary>
	    public bool bEnable;
        /// <summary>
        /// Device ID
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 64)]
        public byte[] szDeviceID;
        /// <summary>
        /// Channel ID
        /// </summary>
	    public Int32 nChannel;
    };

    // Display Source
    public struct AV_CFG_DisplaySource 
    {
	    public Int32 nStructSize;
        /// <summary>
        /// Enable signal
        /// </summary>
        public bool bEnable;
        /// <summary>
        /// Device ID
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 64)]
        public byte[] szDeviceID;
        /// <summary>
        /// Video Channel number
        /// </summary>
        public Int32 nVideoChannel;
        /// <summary>
        /// Video Stream
        /// </summary>
        public Int32 nVideoStream;
        /// <summary>
        /// Audio Channle number
        /// </summary>
        public Int32 nAudioChannle;
        /// <summary>
        /// Audio Stream
        /// </summary>
        public Int32 nAudioStream;
    };

    // Channel Segmentation Display Source
    public struct AV_CFG_ChannelDisplaySource 
    {
	    public Int32 nStructSize;
        /// <summary>
        /// Split window number
        /// </summary>
	    public Int32 nWindowNum;
        /// <summary>
        /// Split window display source
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 128)]
	    public AV_CFG_DisplaySource[]	stuSource;
    };

    // Raid information
    public struct AV_CFG_Raid 
    {
	    public Int32 nStructSize;
        /// <summary>
        /// Name
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 64)]
	    public byte[] szName;
        /// <summary>
        /// Level
        /// </summary>
	    public Int32 nLevel;
        /// <summary>
        /// Disk members number
        /// </summary>
	    public Int32 nMemberNum;
        /// <summary>
        /// Disk members
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 32 * 260)]
        public byte[] szMembers;
    };

    // Record Source
    public struct AV_CFG_RecordSource
    {
	    public Int32 nStructSize;
        /// <summary>
        /// Enable signal
        /// </summary>
	    public bool bEnable;
        /// <summary>
        /// Device ID
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 64)]
	    public byte[] szDeviceID;
        /// <summary>
        /// Video Channel number
        /// </summary>
	    public Int32 nVideoChannel;
        /// <summary>
        /// Video Stream
        /// </summary>
	    public Int32 nVideoStream;
        /// <summary>
        /// Audio Channel number
        /// </summary>
	    public Int32 nAudioChannle;
        /// <summary>
        /// Audio Stream
        /// </summary>
	    public Int32 nAudioStream;
    };

    // Video input color configuration, each video input channels corresponding to multiple color configuration
    public struct AV_CFG_VideoColor
    {
        public Int32 nStructSize;
        /// <summary>
        /// Time Section
        /// </summary>
        public AV_CFG_TimeSection stuTimeSection;
        /// <summary>
        /// Brightness, 1~100
        /// </summary>
        public Int32 nBrightness;
        /// <summary>
        /// Contrast, 1~100
        /// </summary>
        public Int32 nContrast;
        /// <summary>
        /// Saturation, 1~100
        /// </summary>
        public Int32 nSaturation;
        /// <summary>
        /// Hue, 1~100
        /// </summary>
        public Int32 nHue;
    };

    // Channel video input color configuration
    public struct AV_CFG_ChannelVideoColor 
    {
	    public Int32 nStructSize;
        /// <summary>
        /// Channel number color configuration
        /// </summary>
	    public Int32 nColorNum;
        /// <summary>
        /// Channel color configuration, each channel multipling color configuration
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 24)]
	    public AV_CFG_VideoColor[]	stuColor;
    };

    // Color
    public struct AV_CFG_Color
    {
        public Int32 nStructSize;
        /// <summary>
        /// Red
        /// </summary>
        public Int32 nRed;
        /// <summary>
        /// Green
        /// </summary>
        public Int32 nGreen;
        /// <summary>
        /// Blue
        /// </summary>
        public Int32 nBlue;
        /// <summary>
        /// Alpha
        /// </summary>
        public Int32 nAlpha;
    };


    // Area
    public struct AV_CFG_Rect
    {
        public Int32 nStructSize;
        public Int32 nLeft;
        public Int32 nTop;
        public Int32 nRight;
        public Int32 nBottom;
    };

    // Code objects - channel title
    public struct AV_CFG_VideoWidgetChannelTitle
    {
        public Int32 nStructSize;
        /// <summary>
        /// Stack to main stream
        /// </summary>
        public bool bEncodeBlend;
        /// <summary>
        /// Stack to auxiliary stream1
        /// </summary>
        public bool bEncodeBlendExtra1;
        /// <summary>
        /// Stack to auxiliary stream2
        /// </summary>
        public bool bEncodeBlendExtra2;
        /// <summary>
        /// Stack to auxiliary stream3
        /// </summary>
        public bool bEncodeBlendExtra3;
        /// <summary>
        /// Stack to screenshots
        /// </summary>
        public bool bEncodeBlendSnapshot;
        /// <summary>
        /// Front Color
        /// </summary>
        public AV_CFG_Color stuFrontColor;
        /// <summary>
        /// Back Color
        /// </summary>
        public AV_CFG_Color stuBackColor;
        /// <summary>
        /// Area, Coordinate values0~8191, only use left and top value, point(left,top) should be setted as the same with point(right,bottom)
        /// </summary>
        public AV_CFG_Rect stuRect;
    };

    // Code objects-Time title
    public struct AV_CFG_VideoWidgetTimeTitle
    {
        public Int32 nStructSize;
        /// <summary>
        /// Stack to main stream
        /// </summary>
        public bool bEncodeBlend;
        /// <summary>
        /// Stack to auxiliary stream1
        /// </summary>
        public bool bEncodeBlendExtra1;
        /// <summary>
        /// Stack to auxiliary stream2
        /// </summary>
        public bool bEncodeBlendExtra2;
        /// <summary>
        /// Stack to auxiliary stream3
        /// </summary>
        public bool bEncodeBlendExtra3;
        /// <summary>
        /// Stack to screenshots
        /// </summary>
        public bool bEncodeBlendSnapshot;
        /// <summary>
        /// Front Color
        /// </summary>
        public AV_CFG_Color stuFrontColor;
        /// <summary>
        /// Back Color
        /// </summary>
        public AV_CFG_Color stuBackColor;
        /// <summary>
        /// Area, Coordinate values 0~8191, only use left and top value, point(left,top) should be setted as the same with point(right,bottom)
        /// </summary>
        public AV_CFG_Rect stuRect;
        /// <summary>
        /// whether show week
        /// </summary>
        public bool bShowWeek;
    };

    // Code objects-Regional coverage configuration
    public struct AV_CFG_VideoWidgetCover
    {
        public Int32 nStructSize;
        /// <summary>
        /// Stack to main stream
        /// </summary>
        public bool bEncodeBlend;
        /// <summary>
        /// Stack to auxiliary stream1
        /// </summary>
        public bool bEncodeBlendExtra1;
        /// <summary>
        /// Stack to auxiliary stream2
        /// </summary>
        public bool bEncodeBlendExtra2;
        /// <summary>
        /// Stack to auxiliary stream3
        /// </summary>
        public bool bEncodeBlendExtra3;
        /// <summary>
        /// Stack to screenshots
        /// </summary>
        public bool bEncodeBlendSnapshot;
        /// <summary>
        /// Front Color
        /// </summary>
        public AV_CFG_Color stuFrontColor;
        /// <summary>
        /// Back Color
        /// </summary>
        public AV_CFG_Color stuBackColor;
        /// <summary>
        /// Area, Coordinate values 0~8191
        /// </summary>
        public AV_CFG_Rect stuRect;
    };

    // Code objects-Custom Title
    public struct AV_CFG_VideoWidgetCustomTitle 
    {
	    public Int32 nStructSize;
        /// <summary>
        /// Stack to main stream
        /// </summary>
	    public bool bEncodeBlend;
        /// <summary>
        /// Stack to auxiliary stream1
        /// </summary>
	    public bool bEncodeBlendExtra1;
        /// <summary>
        /// Stack to auxiliary stream2
        /// </summary>
	    public bool bEncodeBlendExtra2;
        /// <summary>
        /// Stack to auxiliary stream3
        /// </summary>
	    public bool bEncodeBlendExtra3;
        /// <summary>
        /// Stack to screenshots
        /// </summary>
	    public bool bEncodeBlendSnapshot;
        /// <summary>
        /// Front Color
        /// </summary>
	    public AV_CFG_Color stuFrontColor;
        /// <summary>
        /// Back Color
        /// </summary>
	    public AV_CFG_Color stuBackColor;
        /// <summary>
        /// Area, Coordinate values 0~8191, only use left and top value, point(left,top) should be setted as the same with point(right,bottom)
        /// </summary>
	    public AV_CFG_Rect stuRect;
        /// <summary>
        /// Title text
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 256)]
	    public byte[] szText;
    };

    // Video coding object configuration
    public struct AV_CFG_VideoWidget 
    {
	    public Int32 nStructSize;
        /// <summary>
        /// Channel Title
        /// </summary>
	    public AV_CFG_VideoWidgetChannelTitle	stuChannelTitle;
        /// <summary>
        /// Time Title
        /// </summary>
	    public AV_CFG_VideoWidgetTimeTitle		stuTimeTitle;
        /// <summary>
        /// Regional coverage number
        /// </summary>
	    public Int32 nConverNum;
        /// <summary>
        /// Coverage area
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 16)]
	    public AV_CFG_VideoWidgetCover[] stuCovers;
        /// <summary>
        /// Custom Title Number
        /// </summary>
	    public Int32 nCustomTitleNum;
        /// <summary>
        /// Custom Title
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 4)]
	    public AV_CFG_VideoWidgetCustomTitle[]	stuCustomTitle;
    };

    // Storage group channel related configuration
    public struct AV_CFG_StorageGroupChannel 
    {
	    public Int32 nStructSize;
        /// <summary>
        /// Max storage pictures on each channel, exceed then cover
        /// </summary>
	    public Int32 nMaxPictures;
        /// <summary>
        /// A string representation of channel in the naming rules, %c the content of the corresponding
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 32)]
	    public byte[] szPath;
    };

    // Storage group configuration
    public struct AV_CFG_StorageGroup 
    {
	    public Int32 nStructSize;
        /// <summary>
        /// Group Name
        /// </summary>
	    [MarshalAs(UnmanagedType.ByValArray, SizeConst = 64)]
	    public byte[] szName;
        /// <summary>
        /// Group Memo
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 128)]
	    public byte[] szMemo;
        /// <summary>
        /// File Hold Time
        /// </summary>
	    public Int32 nFileHoldTime;
        /// <summary>
        /// Whether storage full
        /// </summary>
	    public bool bOverWrite;
        /// <summary>
        /// Video file path naming rule
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 260)]
	    public byte[] szRecordPathRule;
        /// <summary>
        /// Image file path naming rule
        /// %y year, %M month, %d day, %h hour, %m minute, %s second, %c channel path
        /// If year/month/day/hour/minute/second appear twice, first said start time,second said end time
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 260)]
	    public byte[] szPicturePathRule;
        /// <summary>
        /// Channel related configuration 
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 1024)]
	    public AV_CFG_StorageGroupChannel[]	stuChannels;
        /// <summary>
        /// Channel configuration number
        /// </summary>
	    public Int32 nChannelCount;
    };

    // DST time
    public struct AV_CFG_DSTTime
    {
        public Int32 nStructSize;
        /// <summary>
        /// Year, 2000~2038
        /// </summary>
        public Int32 nYear;
        /// <summary>
        /// Month, 1~12
        /// </summary>
        public Int32 nMonth;
        /// <summary>
        /// Week, 1-First week,2-Second week,...,-1-Last week,0-According to the date
        /// </summary>
        public Int32 nWeek;
        /// <summary>
        /// What day or date
        /// According to the week, 0-Sunday, 1-Monday,..., 6-Saturday
        /// According to the date, 1~31
        /// </summary>
        public Int32 nDay;
        /// <summary>
        /// Hour
        /// </summary>
        public Int32 nHour;
        /// <summary>
        /// Minute
        /// </summary>
        public Int32 nMinute;
    };

    // Regional collocation
    public struct AV_CFG_Locales 
    {
	    public Int32 nStructSize;
        /// <summary>
        /// Time Format
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 32)]
        public byte[] szTimeFormat;
        /// <summary>
        /// Summer time enable
        /// </summary>
	    public bool bDSTEnable;
        /// <summary>
        /// Summer time start
        /// </summary>
	    public AV_CFG_DSTTime stuDstStart;
        /// <summary>
        /// Summer time end
        /// </summary>
	    public AV_CFG_DSTTime stuDstEnd;
    };

    // Language collocation
    public struct AV_CFG_Language
    {
        public Int32 nStructSize;
        public AV_CFG_LanguageType emLanguage;						// Present language
    };

    // Access Filter Address
    public struct AV_CFG_AccessFilter
    {
	    public Int32 nStructSize;
        /// <summary>
        /// Enable signal
        /// </summary>
	    public bool bEnable;
        /// <summary>
        /// Type, 0-blacklist, 1-WhiteList
        /// </summary>
	    public Int32 nType;
        /// <summary>
        /// WhiteList IP number
        /// </summary>
	    public Int32 nWhiteListNum;
        /// <summary>
        /// WhiteList
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 1024 * 96)]
	    public byte[] szWhiteList;
        /// <summary>
        /// blacklist IP or IP number
        /// </summary>
	    public Int32 nBlackListNum;
        /// <summary>
        /// Blacklist 
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 1024 * 96)]
	    public byte[] szBlackList;
    };


    // Auto Maintain
    public struct AV_CFG_AutoMaintain
    {
        public Int32 nStructSize;
        /// <summary>
        /// Automatic restart date, -1Never, 0~6Sunday~Saturday, 7Everyday
        /// </summary>
        public Int32 nAutoRebootDay;
        /// <summary>
        /// Automatic restart hour, 0~23
        /// </summary>
        public Int32 nAutoRebootHour;
        /// <summary>
        /// Automatic restart minute, 0~59
        /// </summary>
        public Int32 nAutoRebootMinute;
        /// <summary>
        /// Auto Shutdown Day
        /// </summary>
        public Int32 nAutoShutdownDay;
        /// <summary>
        /// Auto Shutdown hour
        /// </summary>
        public Int32 nAutoShutdownHour;
        /// <summary>
        /// Auto Shutdown Minute
        /// </summary>
        public Int32 nAutoShutdownMinute;
        /// <summary>
        /// Auto Startup Day
        /// </summary>
        public Int32 nAutoStartupDay;
        /// <summary>
        /// Auto Startup Hour
        /// </summary>
        public Int32 nAutoStartupHour;
        /// <summary>
        /// Auto Startup Minute
        /// </summary>
        public Int32 nAutoStartupMinute;
    };

    // Remote device event process 
    public struct AV_CFG_RemoteEvent 
    {
	    public Int32 nStructSize;
        /// <summary>
        /// Enable signal
        /// </summary>
	    public bool bEnable;
        /// <summary>
        /// Device ID
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 64)]
	    public byte[] szDeviceID;
        /// <summary>
        /// Event Code
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 64)]
	    public byte[] szCode;
        /// <summary>
        /// Index number
        /// </summary>
	    public Int32 nIndex;
    };

    // Monitor WallTV output channel information
    public struct AV_CFG_MonitorWallTVOut
    {
	    public Int32		nStructSize;
        /// <summary>
        /// Device ID, empty or"Local" means local device
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 64)]
	    public byte[] szDeviceID;
        /// <summary>
        /// Channel ID
        /// </summary>
	    public Int32		nChannelID;				
        /// <summary>
        /// Screen Name
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 64)]
	    public byte[] szName;
    };

    // Monitor Wall Block
    public struct AV_CFG_MonitorWallBlock 
    {
	    public Int32 nStructSize;
        /// <summary>
        /// Grid lines of single TV
        /// </summary>
	    public Int32 nLine;
        /// <summary>
        /// Grid columns of single TV
        /// </summary>
	    public Int32 nColumn;
        /// <summary>
        /// Block area coordinates
        /// </summary>
	    public AV_CFG_Rect stuRect;
        /// <summary>
        /// TV count
        /// </summary>
	    public Int32 nTVCount;
        /// <summary>
        /// TV array
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 128)]
	    public AV_CFG_MonitorWallTVOut[]	stuTVs;
        /// <summary>
        /// Block Name
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 7 * 6)]
        public CFG_TIME_SECTION[] stuTimeSection;
        /// <summary>
        /// On/Off TV Time
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 64)]
        public byte[] szName;
        /// <summary>
        /// Composite ID
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 64)]
        public byte[] szCompositeID;
    };

    // Monitor Wall
    public struct AV_CFG_MonitorWall
    {
	    public Int32 nStructSize;
        /// <summary>
        /// Name
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 64)]
	    public byte[] szName;
        /// <summary>
        /// Grid lines
        /// </summary>
	    public Int32 nLine;
        /// <summary>
        /// Grid columns
        /// </summary>
	    public Int32 nColumn;
        /// <summary>
        /// Block Count
        /// </summary>
	    public Int32 nBlockCount;
        /// <summary>
        /// Block array
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 128)]
	    public AV_CFG_MonitorWallBlock[] stuBlocks;
        /// <summary>
        /// Is Disable?0:Monitor Wall enable 1:disable
        /// </summary>
        public int bDisable;
        /// <summary>
        /// Monitor Wall Describe Info
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 256)]
        public byte[] szDesc;
    };

    // Splice Screen
    public struct AV_CFG_SpliceScreen
    {
	    public Int32 nStructSize;
        /// <summary>
        /// Splice Screen Name	
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 64)]
	    public byte[] szName;
        /// <summary>
        /// Monitor Wall Name
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 64)]
	    public byte[] szWallName;
        /// <summary>
        /// Block ID
        /// </summary>
	    public Int32 nBlockID;
        /// <summary>
        /// Area coordinates(0~8191)
        /// </summary>
	    public AV_CFG_Rect stuRect;
    };

    // Linkage yuntai information
    public struct AV_CFG_PtzLink
    {
        public Int32 nStructSize;
        /// <summary>
        /// Linkage type
        /// </summary>
        public AV_CFG_PtzLinkType emType;
        /// <summary>
        /// Linkage param1
        /// </summary>
        public Int32 nParam1;
        /// <summary>
        /// Linkage param2
        /// </summary>
        public Int32 nParam2;
        /// <summary>
        /// Linkage param3
        /// </summary>
        public Int32 nParam3;
        /// <summary>
        /// Linkage yuntai channel
        /// </summary>
        public Int32 nChannelID;
    } 

    // coordinate point
    public struct AV_CFG_Point
    {
	    public Int32 nStructSize;
	    public Int32 nX;
	    public Int32 nY;
    } 

    // Width and height
    public struct AV_CFG_Size
    {
	    public Int32 nStructSize;
	    public UInt32 nWidth;
	    public UInt32 nHeight;
    } 	


    // Event title content
    public struct AV_CFG_EventTitle
    {
	    public Int32 nStructSize;
        /// <summary>
        /// Title text
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 64)]
	    public byte[] szText;
        /// <summary>
        /// Coordinate on the top left corner of title, using 0-8191 relative coordinate system
        /// </summary>
	    public AV_CFG_Point		stuPoint;
        /// <summary>
        /// Width and height of title, using 0-8191 relative coordinate system,One or two of 0 said according to the font adaptive to width and height
        /// </summary>
	    public AV_CFG_Size			stuSize;
        /// <summary>
        /// Front Color
        /// </summary>
        public AV_CFG_Color		stuFrontColor;
        /// <summary>
        /// Back Color
        /// </summary>
        public AV_CFG_Color		stuBackColor;
    } 

    // Round round linkage configuration
    public struct AV_CFG_TourLink
    {
	    public Int32 nStructSize;
        /// <summary>
        /// Round round enable signal
        /// </summary>
	    public bool bEnable;
        /// <summary>
        /// Round round split mode
        /// </summary>
	    public AV_CFG_SplitMode emSplitMode;
        /// <summary>
        /// Round round channel number list
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 1024)]
        public Int32[] nChannels;
        /// <summary>
        /// Round round channel count
        /// </summary>
        public Int32 nChannelCount;
    } 


    // Alarm linkage
    public  struct AV_CFG_EventHandler
    {
	    public Int32			nStructSize;
        /// <summary>
        /// Incident response schedule
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 7 * 6)]
	    public AV_CFG_TimeSection[]  stuTimeSect; 
        /// <summary>
        /// Record Enable
        /// </summary>
	    public bool bRecordEnable;
        /// <summary>
        /// Record channel number list
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 1024)]
	    public UInt32[] nRecordMask;
        /// <summary>
        /// Capability set, identification nRecordLatch effective or not
        /// </summary>
	    public bool abRecordLatch;
        /// <summary>
        /// Record delay time（10~300s）
        /// </summary>
	    public Int32 nRecordLatch;
        /// <summary>
        /// Alarm output enable
        /// </summary>
	    public bool bAlarmOutEn;
        /// <summary>
        /// Alarm output channel number list
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 1024)]
	    public UInt32[] nAlarmOutMask;
        /// <summary>
        /// Capability set, identification nAlarmOutLatch effective or not
        /// </summary>
	    public bool abAlarmOutLatch;
        /// <summary>
        /// Alarm output delay time（10~300s）
        /// </summary>
	    public Int32 nAlarmOutLatch;
        /// <summary>
        /// Extension Alarm Output Enable
        /// </summary>
	    public bool bExAlarmOutEn;
        /// <summary>
        /// Extension alarm output channel list
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 1024)]
	    public UInt32[] nExAlarmOutMask;
        /// <summary>
        /// Yuntai linkage enable
        /// </summary>
	    public bool bPtzLinkEn;
        /// <summary>
        /// Effective linkage item number
        /// </summary>
	    public Int32 nPtzLinkNum;
        /// <summary>
        /// Effective linkage item
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 1024)]
	    public AV_CFG_PtzLink[]		stuPtzLink;
        /// <summary>
        /// Snapshot enable
        /// </summary>
	    public bool bSnapshotEn;
        /// <summary>
        /// Snapshot mask list	
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 1024)]
	    public UInt32[] nSnapshotMask;
        /// <summary>
        ///// Capability set, identification nSnapshotPeriod effective or not
        /// </summary>
	    public bool abSnapshotPeriod;	
        /// <summary>
        /// Interframe gap,how many frames to grasp a picture,Captured number of sheets within a certain time is also related to the captured picture frame rate。0 No Short Interframe Space,Continuous capture。
        /// </summary>
	    public Int32 nSnapshotPeriod;	
        /// <summary>
        /// Capability set, nSnapshotTimes effectiveness
        /// </summary>
	    public bool abSnapshotTimes;	
        /// <summary>
        /// Snapshot Times, when SnapshotEnable is true,SnapshotTimes is 0,means continue to capture, until the end of the event
        /// </summary>
	    public Int32 nSnapshotTimes;		
        /// <summary>
        /// Superposition image title or not
        /// </summary>
	    public bool bSnapshotTitleEn;	
        /// <summary>
        /// Effective Snap Title Number
        /// </summary>
	    public Int32 nSnapTitleNum; 
        /// <summary>
        /// Content of Snap Title
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 32)]
	    public AV_CFG_EventTitle[]   stuSnapTitles;
        /// <summary>
        /// local tip message box
        /// </summary>
	    public bool bTipEnable;
        /// <summary>
        /// Send email,picture as accessory
        /// </summary>
	    public bool bMailEnable;
        /// <summary>
        /// Uploaded to the alarm server
        /// </summary>
	    public bool bMessageEnable;
        /// <summary>
        /// Buzzing
        /// </summary>
	    public bool bBeepEnable;
        /// <summary>
        /// Voice prompt 
        /// </summary>
	    public bool bVoiceEnable;
        /// <summary>
        /// Capability set, nDejitter effectiveness
        /// </summary>
	    public bool abDejitter;
        /// <summary>
        /// Signal Dejitter time,unit second,0~100
        /// </summary>
	    public Int32 nDejitter;
        /// <summary>
        /// Record blog or not
        /// </summary>
	    public bool bLogEnable;
        /// <summary>
        /// nDelay effectiveness
        /// </summary>
	    public bool abDelay;
        /// <summary>
        /// Set delay before effecting, unit second
        /// </summary>
	    public Int32 nDelay;
        /// <summary>
        /// Overlay video title or not,mainly refers to the main stream
        /// </summary>
	    public bool bVideoTitleEn;
        /// <summary>
        /// Effective video title number
        /// </summary>
	    public Int32 nVideoTitleNum;
        /// <summary>
        /// Video title content
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 32)]
	    public AV_CFG_EventTitle[]	stuVideoTitles;
        /// <summary>
        /// MMS enable
        /// </summary>
	    public bool bMMSEnable;
        /// <summary>
        /// Round tour linkage number,same with video outputting
        /// </summary>
	    public Int32 nTourNum;
        /// <summary>
        /// Round tour linkage configuration, each video outputs corresponding to a configuration
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 128)]
	    public AV_CFG_TourLink[]	    stuTour;
        /// <summary>
        /// Number of keywords
        /// </summary>
	    public Int32 nDBKeysNum;
        /// <summary>
        /// Keywords
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 64 * 32)]
	    public byte[] szDBKeys;
        /// <summary>
        /// Capability set, identification byJpegSummary effective or not
        /// </summary>
	    public bool abJpegSummary;
        /// <summary>
        /// The summary information of adding up to JPEG image
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 1024)]
	    public byte[] byJpegSummary;
    } 

    // Temperature alarm configuration
    public  struct AV_CFG_TemperatureAlarm
    {
	    public Int32 nStructSize;
        /// <summary>
        /// Alarm enable
        /// </summary>
	    public bool bEnable;
        /// <summary>
        /// Sensor Name
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 64)]
	    public byte[] szName;
        /// <summary>
        /// Minimum normal temperature
        /// </summary>
	    public float fNormalTempMin;
        /// <summary>
        /// Maximum normal temperature
        /// </summary>
	    public float fNormalTempMax;
        /// <summary>
        /// Alarm linkage 
        /// </summary>
	    public  AV_CFG_EventHandler stuEventHandler;
    } 

    // Fan speed alarm configuration
    public  struct AV_CFG_FanSpeedAlarm
    {
	    public Int32 nStructSize;
        /// <summary>
        /// Alarm enable
        /// </summary>
	    public bool bEnable;
        /// <summary>
        /// Sensor name
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 64)]
	    public byte[] szName;
        /// <summary>
        /// Minimum normal fan speed
        /// </summary>
	    public UInt32 nNormalSpeedMin;
        /// <summary>
        /// Maximum normal fan speed
        /// </summary>
	    public UInt32 nNormalSpeedMax;
        /// <summary>
        /// Alarm linkage 
        /// </summary>
	    public AV_CFG_EventHandler stuEventHandler;
    } 

    //  Record backup configuration
    public struct AV_CFG_RecordBackup
    {
	    public Int32 nStructSize;
        /// <summary>
        /// Bitrate Limit, unit Kbps
        /// </summary>
	    public UInt32 nBitrateLimit;
    }

    // 车位状态对应的车位指示灯
    public enum EM_CFG_PARKINGSPACE_LIGHT_COLOR
    {
        EM_CFG_PARKINGSPACE_LIGHT_RED,                                      // 红色
        EM_CFG_PARKINGSPACE_LIGHT_YELLOW,                                   // 黄色
        EM_CFG_PARKINGSPACE_LIGHT_BLUE,                                     // 蓝色
        EM_CFG_PARKINGSPACE_LIGHT_GREEN,                                    // 绿色
        EM_CFG_PARKINGSPACE_LIGHT_PURPLE,                                   // 紫色
        EM_CFG_PARKINGSPACE_LIGHT_WHITE,                                    // 白色
        EM_CFG_PARKINGSPACE_LIGHT_PINK,                                     // 粉色
    }

    // 指示灯状态
    public  enum EM_CFG_PARKINGSPACE_LIGHT_STATE
    {
        EM_CFG_PARKINGSPACE_LIGHT_OFF,                                      // 灭
        EM_CFG_PARKINGSPACE_LIGHT_ON,                                       // 亮
        EM_CFG_PARKINGSPACE_LIGHT_GLINT,                                    // 闪烁
    }

    public struct CFG_PARKINGSPACE_LIGHT_STATE
    {
        /// <summary>
        /// 车位空闲状态灯色,
        /// EM_CFG_PARKINGSPACE_LIGHT_COLOR作为数组下标,表示灯的颜色 
        /// EM_CFG_PARKINGSPACE_LIGHT_STATE作为数组元素值,表示指示灯状态
        /// 如bySpaceFreeLinght[EM_CFG_PARKINGSPACE_LIGHT_WHITE]=EM_CFG_PARKINGSPACE_LIGHT_ON,表示白色指示灯亮
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 8)]
        public byte[] bySpaceFreeLinght;
        /// <summary>
        /// 车位满状态灯色
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 8)]
        public byte[] bySpaceFullLinght;
        /// <summary>
        ///  车位压线状态灯色
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 8)]
        public byte[] bySpaceOverLineLight;
        /// <summary>
        /// 车位预定状态灯色
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 8)]
        public byte[] bySpaceOrderLight;
        /// <summary>
        /// 网口数
        /// </summary>
        public int nNetPortNum;
        /// <summary>
        /// 网口断开状态灯色
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 4 * 8)]
        public byte[] byNetPortAbortLight;
    }
   #endregion

    #region <<traffic inspection spot event – corresponding rule configuration >>


    // event type EVENT_IVS_TRAFFICGATE(traffic inspection spot event)corresponding rule configuration
    public struct CFG_TRAFFICGATE_INFO
    {
	    // information
        /// <summary>
        /// rule name, different rules cannot use same names
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 32)]
	    public byte[] szRuleName;
        /// <summary>
        /// rule enable
        /// </summary>
	    public byte bRuleEnable;
        /// <summary>
        /// reserved
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 3)]
	    public byte[] bReserved;
        /// <summary>
        /// corresponding object type number
        /// </summary>
	    public Int32 nObjectTypeNum;
        /// <summary>
        /// corresponding object type list
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 16 * 32)]
	    public byte[] szObjectTypes;
        /// <summary>
        /// lane number
        /// </summary>
	    public Int32 nLane;
        /// <summary>
        /// detection line (virtual coil) 1 vertex number
        /// </summary>
	    public Int32 nDetectLinePoint1;
        /// <summary>
        /// detection line 1
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 20)]
	    public CFG_POLYLINE[] stuDetectLine1;
        /// <summary>
        /// detection line (virtual coil) 2 vertex number
        /// </summary>
	    public Int32 nDetectLinePoint2;
        /// <summary>
        /// detection line 2
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 20)]
	    public CFG_POLYLINE[] stuDetectLine2;
        /// <summary>
        /// left lane line’s vertex number
        /// </summary>
	    public Int32 nLeftLinePoint;
        /// <summary>
        /// left lane line
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 20)]
	    public CFG_POLYLINE[] stuLeftLine;
        /// <summary>
        /// right lane line’s vertex number
        /// </summary>
	    public Int32 nRightLinePoint;
        /// <summary>
        /// right lane line 
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 20)]
	    public CFG_POLYLINE[] stuRightLine;
        /// <summary>
        /// speed weight coefficient (final car speed=measured car speed*weight coefficient)
        /// </summary>
	    public Int32 nSpeedWeight;
        /// <summary>
        /// actual distance between two detection line, unit: meter
        /// </summary>
	    public double MetricDistance;
        /// <summary>
        /// speed upper limit 0 means no upper limit, unit: km/h
        /// </summary>
	    public Int32 nSpeedUpperLimit;
        /// <summary>
        /// speed lower limit 0 means no lower limit, unit: km/h
        /// </summary>
	    public Int32 nSpeedLowerLimit;
        /// <summary>
        /// alarm linkage
        /// </summary>
	    public CFG_ALARM_MSG_HANDLE stuEventHandler;
        /// <summary>
        /// event responding periods of time
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 7 * 6)]
	    public CFG_TIME_SECTION[]	stuTimeSection;
        /// <summary>
        /// lane direction (car driving direction), 0-North, 1-Northeast, 2-East, 3-Southeast, 4-South, 5-Southwest, 6-West, 7-Northwest
        /// </summary>
	    public Int32 nDirection;
        /// <summary>
        /// triggered mode number
        /// </summary>
	    public Int32 nTriggerModeNum;
        /// <summary>
        /// trigger mode,"OverLine": overline,"Retrograde": retrograde,"OverSpeed": overspeed,"UnderSpeed": underspeed
        /// "Passing": pass through crossing, belongs to normal capture, "WrongRunningRoute":car parking(excusive use),"YellowVehicleInRoute": yellow card parking
        /// "OverYellowLine": on yellow line
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 32 * 32)]
	    public byte[] szTriggerMode;
        /// <summary>
        /// cloud deck preset position number 0-65535
        /// </summary>
	    public Int32 nPtzPresetId;
        /// <summary>
        /// whether shield retrograde, namely treat retrograde as normal
        /// </summary>
	    public bool bMaskRetrograde;
    } 

    // event type EVENT_IVS_TRAFFICJUNCTION(traffic crossing event)corresponding rules configuration
    public struct CFG_TRAJUNCTION_INFO
    {
	    // information
        /// <summary>
        /// rule name, different rules cannot use same names
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 32)]
	    public byte[] szRuleName;
        /// <summary>
        /// rule enable
        /// </summary>
	    public byte bRuleEnable;
        /// <summary>
        /// corresponding object type number
        /// </summary>
	    public Int32 nObjectTypeNum;
        /// <summary>
        /// corresponding object type list
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 16 * 32)]
	    public byte[] szObjectTypes;
        /// <summary>
        /// lane number
        /// </summary>
	    public Int32 nLane;
        /// <summary>
        /// lane direction(car driving direction), 0-North, 1-Northeast, 2-East, 3-Southeast, 4-South, 5-Southwest, 6-West, 7-Northwest 
        /// </summary>
	    public Int32 nDirection;
        /// <summary>
        /// front detection line vertex number
        /// </summary>
	    public Int32 nPreLinePoint;
        /// <summary>
        /// front detection line
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 20)]
	    public CFG_POLYLINE[] stuPreLine;
        /// <summary>
        /// middle detection line vertex number
        /// </summary>
	    public Int32 nMiddleLinePoint;
        /// <summary>
        /// middle detection line
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 20)]
	    public CFG_POLYLINE[] stuMiddleLine;
        /// <summary>
        /// back detection line vertex number
        /// </summary>
	    public Int32 nPostLinePoint;
        /// <summary>
        /// back detection line
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 20)]
	    public CFG_POLYLINE[] stuPostLine;
        /// <summary>
        /// flow upper limit, unit: one car per second
        /// </summary>
	    public Int32 nFlowLimit;
        /// <summary>
        /// flow lower limit, if 0, means no lower limit, km/h
        /// </summary>
	    public Int32 nSpeedDownLimit;
        /// <summary>
        /// speed upper limit, if 0, means no upper limit, km/h
        /// </summary>
	    public Int32 nSpeedUpLimit;
        /// <summary>
        /// triggered mode number
        /// </summary>
	    public Int32 nTriggerModeNum;
        /// <summary>
        /// triggered mode, "Passing" : cross crossing (regard middle detection line as norm, only use independently),"RunRedLight" : run the red light
        /// "Overline": step on white lane line,"OverYellowLine": step on yellow line, "Retrograde": retrograde
        /// "TurnLeft": turn left against rule, "TurnRight": turn right against rule, "CrossLane":switch lane against rule
        /// "U-Turn" turn around against rule, "Parking": parking against rule, "WaitingArea" enter vehicle-waiting area against rule
        /// "OverSpeed": exceed speed limit,"UnderSpeed": lack speed,"Overflow" : flow exceed limit
        /// "Human": pedestrian,"NoMotor": non-motor vehicle
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 32 * 32)]
	    public byte[] szTriggerMode;
        /// <summary>
        /// alarm linkage
        /// </summary>
	    public CFG_ALARM_MSG_HANDLE stuEventHandler;
        /// <summary>
        /// event response period of time
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 32)]
	    public CFG_TIME_SECTION[]	stuTimeSection;
        /// <summary>
        /// cloud deck preset number 0-65535
        /// </summary>
	    public Int32 nPtzPresetId;
        /// <summary>
        /// whether shield retrograde, namely treat retrograde as norm
        /// </summary>
	    public bool bMaskRetrograde;
    			
    } 

    // event type EVENT_IVS_TRAFFICACCIDENT(traffic accident event)corresponding rule configuration
    public struct CFG_TRAACCIDENT_INFO
    {
	    // information
        /// <summary>
        /// rule name, different rules cannot use same names
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 32)]
	    public byte[] szRuleName;
        /// <summary>
        /// rule enable
        /// </summary>
	    public byte bRuleEnable;
        /// <summary>
        /// reserved fields
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 3)]
	    public byte[] bReserved;
        /// <summary>
        /// corresponding object type number
        /// </summary>
	    public Int32 nObjectTypeNum;
        /// <summary>
        /// corresponding object type list
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 16 * 32)]
	    public byte[] szObjectTypes;
        /// <summary>
        /// detection zone vertex number
        /// </summary>
	    public Int32 nDetectRegionPoint;
        /// <summary>
        /// detection zone
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 20)]
	    public CFG_POLYGON[] stuDetectRegion;
        /// <summary>
        /// alarm linkage
        /// </summary>
	    public CFG_ALARM_MSG_HANDLE stuEventHandler;
        /// <summary>
        /// event response periods of time
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 7 * 6)]
	    public CFG_TIME_SECTION[]	stuTimeSection;
        /// <summary>
        /// cloud deck preset vertex number 0-65535
        /// </summary>
	    public Int32 nPtzPresetId;
    	
    } 

    // event type EVENT_IVS_TRAFFICCONTROL(traffic control event)corresponding rule configuration
    public struct CFG_TRAFFICCONTROL_INFO 
    {
	    // information
        /// <summary>
        /// rule names, different rules cannot use same names
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 32)]
	    public byte[] szRuleName;
        /// <summary>
        /// rule enable
        /// </summary>
	    public byte bRuleEnable;
        /// <summary>
        /// reserved fields
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 3)]
	    public byte[] bReserved;
        /// <summary>
        /// corresponding object type number
        /// </summary>
	    public Int32 nObjectTypeNum;
        /// <summary>
        /// corresponding object type list
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 16 * 32)]
	    public byte[] szObjectTypes;
        /// <summary>
        /// detection line vertex number
        /// </summary>
	    public Int32 nDetectLinePoint;
        /// <summary>
        /// detection line
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 20)]
	    public CFG_POLYLINE[] stuDetectLine;
        /// <summary>
        /// traffic control time table
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 7 * 6)]
	    public CFG_TIME_SECTION[]	stuTimeSchedule;
        /// <summary>
        /// car size type number
        /// </summary>
	    public Int32 nVehicleSizeNum;
        /// <summary>
        /// car size type list"Light-duty": small size car;	"Medium": middle size car; "Oversize": big size car
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 4 * 32)]
	    public byte[] szVehicleSizeList;
        /// <summary>
        /// car plate type number
        /// </summary>
	    public Int32 nPlateTypeNum;
        /// <summary>
        /// car plate list "Unknown" unknown; "Normal" blue and black plate; "Yellow" yellow plate; "DoubleYellow" double deck yellow plate
        /// "Police" police car plate; "Armed" armed police car plate; "Military" military car plate; "DoubleMilitary" Military double deck
        /// "SAR" Hong Kong and Macao SAR plate; "Trainning" coach vehicle plate; "Personal" personalized plate; "Agri" agricultural plate
        /// "Embassy" embassy plate; "Moto" motor-bicycle plate; "Tractor" tractor plate; "Other" other plates
        /// 
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 32 * 32)]
	    public byte[] szPlateTypesList;
        /// <summary>
        /// odd or even car plate 0:odd number; 1: even number; 2: odd or even number;	
        /// </summary>
	    public Int32 nPlateNumber;
        /// <summary>
        /// alarm linkage
        /// </summary>
	    public CFG_ALARM_MSG_HANDLE stuEventHandler;
        /// <summary>
        /// event response periods of time
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 7 * 6)]
	    public CFG_TIME_SECTION[]	stuTimeSection;
        /// <summary>
        /// cloud deck preset vertex number 0-65535
        /// </summary>
	    public Int32 nPtzPresetId;
    } 


    // event type EVENT_IVS_FACEDETECT(face recognition event)corresponding rule configuration
    public struct CFG_FACEDETECT_INFO
    {
        /// <summary>
        /// rule name, different rules cannot use same names
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 32)]
	    public byte[] szRuleName;
        /// <summary>
        /// rule enable
        /// </summary>
	    public bool bRuleEnable;
	    /// <summary>
	    /// reserved fields
	    /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 3)]
	    public byte[] bReserved;
        /// <summary>
        /// corresponding object type number
        /// </summary>
	    public int nObjectTypeNum;
        /// <summary>
        /// corresponding object type list
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 16 * 32)]
	    public byte[] szObjectTypes;
        /// <summary>
        /// detection zone vertex number
        /// </summary>
	    public int nDetectRegionPoint;
        /// <summary>
        /// detection zone
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 20)]
	    public CFG_POLYGON[] stuDetectRegion;
        /// <summary>
        /// number of face types triggering event
        /// </summary>
	    public Int32 nHumanFaceTypeCount;
        /// <summary>
        /// types of faces triggering event
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 4 * 32)]
	    public byte[] szHumanFaceType;
        /// <summary>
        /// alarm linkage
        /// </summary>
	    public CFG_ALARM_MSG_HANDLE stuEventHandler;
        /// <summary>
        /// event response periods of time
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 7 * 6)]
	    public CFG_TIME_SECTION[]	stuTimeSection;
        /// <summary>
        /// cloud deck preset vertex number 0-65535
        /// </summary>
	    public Int32 nPtzPresetId;
    }

    // event type EVENT_IVS_PASTEDETECTION(ATM)corresponding rule configuration
    public struct CFG_PASTE_INFO
    {
	    // information
        /// <summary>
        /// rule name, different rules cannot use same names
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 32)]
	    public byte[] szRuleName;
        /// <summary>
        /// rule enable
        /// </summary>
	    public byte bRuleEnable;
        /// <summary>
        /// preserved fields
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 3)]
	    public byte[] bReserved;
        /// <summary>
        /// corresponding object type number
        /// </summary>
	    public Int32 nObjectTypeNum;
        /// <summary>
        /// corresponding object type list
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 16 * 32)]
	    public byte[] szObjectTypes;
        /// <summary>
        /// shortest lasting time unit: second, 0-65535
        /// </summary>
	    public Int32 nMinDuration;
        /// <summary>
        /// detection zone vertex number
        /// </summary>
	    public Int32 nDetectRegionPoint;
        /// <summary>
        /// detection zone
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 20)]
	    public CFG_POLYGON[] stuDetectRegion;
        /// <summary>
        /// alarm linkage
        /// </summary>
	    public CFG_ALARM_MSG_HANDLE stuEventHandler;
        /// <summary>
        /// event response period of time
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 7 * 6)]
	    public CFG_TIME_SECTION[]	stuTimeSection;
        /// <summary>
        /// cloud deck preset vertex number 0-65535
        /// </summary>
	    public Int32 nPtzPresetId;
    		
    } 

    // video analytical event rule configuration
    // event type EVENT_IVS_CROSSLINEDETECTION(guard line event)corresponding rule configuration
    public struct CFG_CROSSLINE_INFO
    {
	    // information
        /// <summary>
        /// rule name, different rule cannot use same names
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 32)]
	    public byte[] szRuleName;
        /// <summary>
        /// rule enable
        /// </summary>
	    public byte bRuleEnable;
        /// <summary>
        /// preserved fields 
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 3)]
	    public byte[] bReserved;
        /// <summary>
        /// corresponding object type numbe
        /// </summary>
	    public Int32 nObjectTypeNum;
        /// <summary>
        /// corresponding object type list
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 16 * 32)]
	    public byte[] szObjectTypes;
        /// <summary>
        /// detection direction:0:from left to right;1:from right to left;2:either is ok
        /// </summary>
	    public Int32 nDirection;
        /// <summary>
        /// guard line vertex number
        /// </summary>
	    public Int32 nDetectLinePoint;
        /// <summary>
        /// guard line 
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 20)]
	    public CFG_POLYLINE[] stuDetectLine;
        /// <summary>
        /// alarm linkage
        /// </summary>
	    public CFG_ALARM_MSG_HANDLE stuEventHandler;
        /// <summary>
        /// event response periods of time
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 7 * 6)]
	    public CFG_TIME_SECTION[]	stuTimeSection;
        /// <summary>
        /// cloud deck preset vertex number 0~65535
        /// </summary>
	    public Int32 nPtzPresetId;
        /// <summary>
        /// whether the specific rule’s size filter is effective
        /// </summary>
	    public bool bSizeFileter;
        /// <summary>
        /// specific rule set size filter
        /// </summary>
	    public CFG_SIZEFILTER_INFO stuSizeFileter;
        /// <summary>
        /// the specific position parameter triggering alarm
        /// </summary>
	    public Int32 nTriggerPosition;      
        /// <summary>
        /// the specific position parameter triggering alarm,0-goal outside the target, 1-goal on the left of the target, 2-on the top of the target, 3-goal on the right of the target, 4-goal at the bottom of the target
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 8)]
	    public byte[] bTriggerPosition;

    } 

    // event type EVENT_IVS_CROSSREGIONDETECTION(guard zone event)corresponding rule configuration
    public struct CFG_CROSSREGION_INFO
    {
	    // information
        /// <summary>
        /// rule name, different rules cannot use same names
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 32)]
	    public byte[] szRuleName;
        /// <summary>
        /// rule enable
        /// </summary>
	    public byte bRuleEnable;
        /// <summary>
        /// preserved fields
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 3)]
	    public byte[] bReserved;
        /// <summary>
        /// corresponding object type number
        /// </summary>
	    public Int32 nObjectTypeNum;
        /// <summary>
        /// corresponding object type list
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 16* 32)]
	    public byte[] szObjectTypes;
        /// <summary>
        /// detection direction:0:Enter;1:Leave;2:Both
        /// </summary>
	    public Int32 nDirection;
        /// <summary>
        /// guard zone vertex number
        /// </summary>
	    public Int32 nDetectRegionPoint;
        /// <summary>
        /// guard zone
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 20)]
	    public CFG_POLYGON[] stuDetectRegion;
        /// <summary>
        /// alarm linkage
        /// </summary>
	    public CFG_ALARM_MSG_HANDLE stuEventHandler;
        /// <summary>
        /// event response periods of time
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 7 * 6)]
	    public CFG_TIME_SECTION[]	stuTimeSection;
        /// <summary>
        /// cloud deck preset vertex number 0~65535
        /// </summary>
	    public Int32 nPtzPresetId;
        /// <summary>
        /// whether the rule set size filter is effective
        /// </summary>
	    public bool bSizeFileter;
        /// <summary>
        /// rule set size filter
        /// </summary>
	    public CFG_SIZEFILTER_INFO stuSizeFileter;
        /// <summary>
        /// detect motion number
        /// </summary>
	    public Int32 nActionType;
        /// <summary>
        /// detect motion list,0-appear 1-disappear 2-in the zone 3-across the zone
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 4)]
	    public byte[] bActionType;
        /// <summary>
        /// the minimal target number(when bActionType include “2-in the zone” takes effect)
        /// </summary>
	    public Int32 nMinTargets;
        /// <summary>
        /// the maximum target number(when bActionType include “2-in the zone” takes effect)
        /// </summary>
	    public Int32 nMaxTargets;
        /// <summary>
        /// the shortest lasting time, unit second(when bActionType include “2-in the zone” takeseffect)
        /// </summary>
	    public Int32 nMinDuration;
        /// <summary>
        /// report time interval, unit second(when bActionType include “2-in the zone” takes effect)
        /// </summary>
	    public Int32 nReportInterval;
    		
    } 

    // event type EVENT_IVS_WANDERDETECTION(hover event)corresponding rule configuration
    public struct CFG_WANDER_INFO 
    {
	    // information
        /// <summary>
        /// rule name, different rule cannot use same names
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 32)]
	    public byte[] szRuleName;
        /// <summary>
        /// rule enable
        /// </summary>
	    public byte bRuleEnable;
        /// <summary>
        /// preserved fields
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 3)]
	    public byte[] bReserved;
        /// <summary>
        /// corresponding object type number
        /// </summary>
	    public Int32 nObjectTypeNum;
        /// <summary>
        /// corresponding object type list
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 16 * 32)]
	    public byte[] szObjectTypes;
        /// <summary>
        /// the shortest lasting time unit: second, 0~65535
        /// </summary>
	    public Int32 nMinDuration;
        /// <summary>
        /// detection zone vertex number
        /// </summary>
	    public Int32 nDetectRegionPoint;
        /// <summary>
        /// detection zone 
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 20)]
	    public CFG_POLYGON[] stuDetectRegion;
        /// <summary>
        /// alarm linkage
        /// </summary>
	    public CFG_ALARM_MSG_HANDLE stuEventHandler;
        /// <summary>
        /// event response periods of time
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 7 * 6)]
	    public CFG_TIME_SECTION[]	stuTimeSection;
        /// <summary>
        /// cloud deck preset vertex number 0~65535
        /// </summary>
	    public Int32 nPtzPresetId;
        /// <summary>
        /// position parameter triggering alaem
        /// </summary>
	    public Int32 nTriggerPosition;
        /// <summary>
        /// triggering alarm position,0-goal outside target, 1-goal on the left of the target, 2-goalon the top of the target, 3-goal on the right of the target, 4-goal at the bottom of the target 
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 8)]
	    public byte[] bTriggerPosition;
        /// <summary>
        /// the number of people hover or stay that triggering alarm
        /// </summary>
	    public Int32 nTriggerTargetsNumber;
        /// <summary>
        /// report interval, unit: second
        /// </summary>
	    public Int32 nReportInterval;
        /// <summary>
        /// whether the rule set specific size filter is effective
        /// </summary>
	    public bool bSizeFileter;
        /// <summary>
        /// rule set specific size filter
        /// </summary>
	    public CFG_SIZEFILTER_INFO stuSizeFileter;

    } 

    // event type EVENT_IVS_RIOTERDETECTION(gathering event)corresponding rule configuration
    public struct CFG_RIOTER_INFO 
    {
	    // information
        /// <summary>
        /// rule name, different rules cannot use same names
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 32)]
	    public byte[] szRuleName;
        /// <summary>
        /// rule enable
        /// </summary>
	    public byte bRuleEnable;
        /// <summary>
        /// percentage of area gathering takes
        /// </summary>
	    public byte bAreaPercent;
        /// <summary>
        /// sensitivity, range from 1-10, the smaller it is the less sensitive, the higher intensive of crowd(replace bAreaPercent)
        /// </summary>
	    public byte bSensitivity;
        /// <summary>
        /// preserved fields
        /// </summary>
	    public byte bReserved;
        /// <summary>
        /// corresponding object type number
        /// </summary>
	    public Int32 nObjectTypeNum;
        /// <summary>
        /// corresponding object type list
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 16 * 32)]
	    public byte[] szObjectTypes;
        /// <summary>
        /// the shortest lasting time unit: second, 0~65535
        /// </summary>
	    public Int32 nMinDuration;
        /// <summary>
        /// detection zone vertex number
        /// </summary>
	    public Int32 nDetectRegionPoint;
        /// <summary>
        /// detection zone
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 20)]
	    public CFG_POLYGON[] stuDetectRegion;
        /// <summary>
        /// alarm linkage
        /// </summary>
	    public CFG_ALARM_MSG_HANDLE stuEventHandler;
        /// <summary>
        /// event responsing time
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 7 * 6)]
	    public CFG_TIME_SECTION[]	stuTimeSection;
        /// <summary>
        /// Yuntai preset ID	0~65535
        /// </summary>
	    public Int32 nPtzPresetId;

    }

    public struct ReservedDataIntelBox
    {
        /// <summary>
        /// Event Count
        /// </summary>
        public UInt32 dwEventCount;
        /// <summary>
        /// type value of the pointing to the continuous event.Space applicated by the user.
        /// DWORD* dwPtrEventType;
        /// </summary>
        public IntPtr dwPtrEventType;
        /// <summary>
        /// Reserved
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 1024)]
        public byte[] bReserved;
    }

    public struct NET_RESERVED_COMMON
    {
        public UInt32 dwStructSize;
        /// <summary>
        /// Compatible RESERVED_TYPE_FOR_INTEL_BOX
        /// c++下定义：
        /// ReservedDataIntelBox* pIntelBox;
        /// </summary>
        public IntPtr pIntelBox;
        /// <summary>
        /// Screenshots logo(bitwise),0 bit:"*",1 bit:"Timing",2 bit:"Manual",3 bit:"Marked",4bit:"Event",5 bit:"Mosaic",6 bit:"Cutout"
        /// </summary>
        public UInt32 dwSnapFlagMask;
    }

    public struct ReservedPara
    {
        /// <summary>
        /// pData type
        /// </summary>
        public UInt32 dwType;
        /// <summary>
        /// When [dwType] is RESERVED_TYPE_FOR_INTEL_BOX,pData correspond the address of ReservedDataIntelBox structure				
        /// When [dwType] is...,[pData] correspond...
        /// Data
        /// c++ defined as：
        /// void*	pData;	//Data
        /// </summary>
        public IntPtr pData;

    }
    #endregion


   #region <<Alarm transportation - CLIENT_StartListen>>
   public struct ALARM_RECORD_FAILED_INFO
   {
        /// <summary>
        /// Struct Size
        /// </summary>
        public UInt32   dwSize;
        /// <summary>
        /// Action 0:Start 1:Stop
        /// </summary>
        public Int32    nAction;
        /// <summary>
        /// Channel No.
        /// </summary>
        public Int32    nIndex;
    }

    /// <summary>
    /// AlarmNet event info
    /// </summary>
    public struct ALARM_NET_INFO
    {
        /// <summary>
        /// Struct Size
        /// </summary>
        public UInt32 dwSize;
        /// <summary>
        /// action, 0:start, 1:stop
        /// </summary>
        public Int32 nAction;
        /// <summary>
        /// channel index, begin 0
        /// </summary>
        public Int32 nChannelID;
    }
   #endregion


   #region <<Intelligent transportation - download images related structure

    // DH_MEDIA_QUERY_TRAFFICCAR matching with the query conditions
    public struct  MEDIA_QUERY_TRAFFICCAR_PARAM
    {
        /// <summary>
        /// ChannelID start from 0,-1 means querying all the channel
        /// </summary>
	    public Int32 nChannelID;
        /// <summary>
        /// Start Time	
        /// </summary>
	    public NET_TIME StartTime;
        /// <summary>
        /// End Time
        /// </summary>
	    public NET_TIME EndTime;
        /// <summary>
        /// File type,0:Query any type,1:Query jpg picture
        /// </summary>
	    public Int32 nMediaType;
        /// <summary>
        /// Event Type,See "type of intelligent analysis event", 0:Query any type
        /// </summary>
	    public Int32 nEventType;
        /// <summary>
        /// Plate Number, "\0"Query any plate number
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 32)]
	    public byte[] szPlateNumber;
        /// <summary>
        /// Query speed range,Speed Upper Limit unit: km/h
        /// </summary>
	    public Int32 nSpeedUpperLimit;
        /// <summary>
        /// Query speed range,Speed Lower Limit unit: km/h 
        /// </summary>
	    public Int32 nSpeedLowerLimit;
        /// <summary>
        /// Whether query by speed; TRUE:Yes,nSpeedUpperLimit and nSpeedLowerLimit are effective.
        /// </summary>
	    public bool bSpeedLimit;
        /// <summary>
        /// Violation type：
        /// When the type is EVENT_IVS_TRAFFICGATE
        /// First:retrograde;  Second:rolling on the markings; Third:Overspeed; 
        /// Fourth：slack speed;Fifth:red light running ;
        /// When the type is EVENT_IVS_TRAFFICJUNCTION
        /// First:red light running;  Second:Lane not according to stipulations;  
        /// Third:retrograde; Fourth：illegal turn around;
        /// Fifth:rolling on the markings;
        /// </summary>
        public UInt32 dwBreakingRule;
        /// <summary>
        /// Plate Type,"Unknown" Unknown,"Normal" Blue card or black card,"Yellow" yellow card,"DoubleYellow" Double Yellow card,"Police" Police card "Armed" Armed card,
        /// "Military" Force plate,"DoubleMilitary" Forces double plate,"SAR" Hong Kong and Macao SAR plate,"Trainning" Drivers Ed plate
        /// "Personal" Personality plate,"Agri" Agricultural plate,"Embassy" embassy plate,"Moto" Motorcycle plate,"Tractor" tractor plate,"Other" other plate
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 32)]
	    public byte[] szPlateType;
        /// <summary>
        /// Plate Color, "Blue"Blue,"Yellow"Yellow, "White"White,"Black"Black
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 16)]
	    public byte[] szPlateColor;
        /// <summary>
        /// Vehicle Color:"White"White, "Black"Black, "Red"Red, "Yellow"Yellow, "Gray"Gray, "Blue"Blue,"Green"Green
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 16)]
	    public byte[] szVehicleColor;
        /// <summary>
        /// Vehicle Size:"Light-duty":small-size car;"Medium":mid-size car; "Oversize":full-size car
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 16)]
	    public byte[] szVehicleSize;
        /// <summary>
        /// Event group number(when it>=0,so effective)
        /// </summary>
	    public Int32 nGroupID;
        /// <summary>
        /// Lane No.(when it>=0,so effective)
        /// </summary>
	    public Int16 byLane;
        /// <summary>
        /// File mark, 0xFF-use nFileFlagEx, 0-all of the images, 1-Timing files, 2-manual files, 3-event files, 4-important files, 5-Composited files
        /// </summary>
	    public byte byFileFlag;
        /// <summary>
        /// File mark, by bitwise: bit0-Timing files, bit1-manual files, bit2-event files, bit3-important files, bit4-Composited files, 0xFFFFFFFF-all of the resordings
        /// </summary>
	    public Int32 nFileFlagEx;
	    public byte reserved;
        /// <summary>
        /// Reserved
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 41)]
	    public Int32[] bReserved;
    }

    // DH_MEDIA_QUERY_TRAFFICCAR file information
    public struct MEDIAFILE_TRAFFICCAR_INFO
    {
        /// <summary>
        /// Channel No.
        /// </summary>
        public UInt32 ch;
        /// <summary>
        /// File path
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 128)]
        public byte[] szFilePath;
        /// <summary>
        /// File length
        /// </summary>
        public UInt32 size;
        /// <summary>
        /// Starttime
        /// </summary>
        public NET_TIME starttime;
        /// <summary>
        /// Endtime
        /// </summary>
        public NET_TIME endtime;
        /// <summary>
        /// Working directory number									
        /// </summary>
        public UInt32 nWorkDirSN;
        /// <summary>
        /// File Type  1：jpg picture
        /// </summary>
        public byte nFileType;
        /// <summary>
        /// Index file location
        /// </summary>
        public byte bHint;
        /// <summary>
        /// Disk No.
        /// </summary>
        public byte bDriveNo;
        public byte bReserved2;
        /// <summary>
        /// Cluster Number
        /// </summary>
        public UInt32 nCluster;
        /// <summary>
        /// Picture Type, 0-Normal, 1-composition , 2-Cutout
        /// </summary>
        public byte byPictureType;
        /// <summary>
        /// Reserved
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 3)]
        public byte[] bReserved;

        //The following is a traffic information
        /// <summary>
        /// Plate Number
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 32)]
        public byte[] szPlateNumber;
        /// <summary>
        /// Plate Type"Unknown" Unknown; "Normal"  Blue card or black card; "Yellow" Yellow card; "DoubleYellow" Double Yellow card
        /// "Police" Police card; "Armed" Armed card; "Military" Military card; "DoubleMilitary" Double Military card
        /// "SAR" Hong Kong and Macao SAR plate; "Trainning" Drivers Ed plate; "Personal" Personality plate,"Agri" Agricultural plate
        /// "Embassy" embassy plate,"Moto" Motorcycle plate,"Tractor" tractor plate,"Other" other plate
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 32)]
        public byte[] szPlateType;
        /// <summary>
        /// Plate Color:"Blue","Yellow", "White","Black"
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 16)]
        public byte[] szPlateColor;
        /// <summary>
        /// Vehicle Color:"White", "Black", "Red", "Yellow", "Gray", "Blue","Green"
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 16)]
        public byte[] szVehicleColor;
        /// <summary>
        /// Speed,unit Km/H
        /// </summary>
        public Int32 nSpeed;
        /// <summary>
        /// Events number associated
        /// </summary>
        public Int32 nEventsNum;
        /// <summary>
        /// Events list associated,Array value indicates the corresponding event,See"the event type intelligent analysis"		
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 32)]
        public Int32[] nEvents;
        /// <summary>
        /// Violation type mask,First:red light running ; Second:Lane not according to stipulations;
        /// Third:retrograde; Fourth：Illegal turn around;the others:Traffic intersection event
        /// </summary>
        public UInt32 dwBreakingRule;
        /// <summary>
        /// Vehicle Size:"Light-duty":small-size car;"Medium":mid-size car; "Oversize":full-size car
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 16)]
        public byte[] szVehicleSize;
        /// <summary>
        /// Local or remote channel name
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 32)]
        public byte[] szChannelName;
        /// <summary>
        /// Local or remote device name
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 16)]
        public byte[] szMachineName;
        /// <summary>
        /// Speed Upper Limit Unit: km/h
        /// </summary>
        public Int32 nSpeedUpperLimit;
        /// <summary>
        /// Speed Lower Limit Unit: km/h	
        /// </summary>
        public Int32 nSpeedLowerLimit;
        /// <summary>
        /// Event group ID
        /// </summary>
        public Int32 nGroupID;
        /// <summary>
        /// Images count snapped within one events group
        /// </summary>
        public byte byCountInGroup;
        /// <summary>
        /// Snapping number within one events group
        /// </summary>
        public byte byIndexInGroup;
        /// <summary>
        /// Lane
        /// </summary>
        public byte byLane;
        /// <summary>
        /// Reserved
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 49)]
        public byte[] bReserved1;
    } 


    public struct NET_DEV_ENABLE_INFO
    {
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 512)]
	    public UInt32[] IsFucEnable;				// Function list capacity set. Corresponding to the above mentioned enumeration. Use bit to represent sub-function.
    }

    // Snap function attributes structure
    public struct NET_QUERY_SNAP_INFO
    {
        /// <summary>
        /// Channel Number
        /// </summary>
	    public Int32 nChannelNum; 
        /// <summary>
        /// Resolution(bitwise),detail view to enumeration CAPTURE_SIZE
        /// </summary>
	    public UInt32 dwVideoStandardMask;
		/// <summary>
		/// Frequence[128]effective length of the array
		/// </summary>
	    public Int32 nFramesCount;
        /// <summary>
        /// Frame rate(According to numeric value)
        /// -25：25 seconds per frame；-24：24 seconds per frame；-23：23 seconds per frame；-22：22 seconds per frame
        /// ……
        /// 0：ineffective；1：1 frame per second；2：2 frame per second；3：3 frame per second
        /// 4：4 frame per second；5：5 frame per second；17：17 frame per second；18：18 frame per second
        /// 19：19 frame per second；20：20 frame per second
        /// ……
        /// 25: 25 frame per second
        /// char
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 128)]
	    public sbyte[] Frames; 
        /// <summary>
        /// SnapMode[16]effective length of the array
        /// </summary>
	    public Int32 nSnapModeCount;
        /// <summary>
        /// (According to numeric value)0：Snapping timing,1：Snapping manually
        /// char
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 16)]
	    public byte[] SnapMode;
        /// <summary>
        /// Format[16]effective length of the array
        /// </summary>
	    public Int32 nPicFormatCount;
        /// <summary>
        /// (According to numeric value)0：BMP Format,1：JPG Format
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 16)]
	    public byte[] PictureFormat;
        /// <summary>
        /// Quality[32]effective length of the array
        /// </summary>
	    public Int32 nPicQualityCount;
        /// <summary>
        /// According to numeric value
        /// 100：Picture Quality100%；80:Picture Quality80%；60:Picture Quality60%
        /// 50:Picture Quality50%；30:Picture Quality30%；10:Picture Quality10%
        /// char
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 32)]
	    public byte[] PictureQuality;
        /// <summary>
        /// Reserved
        /// char
        /// </summary>
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 128)]
	    public byte[] nReserved; 
    } 

    public struct NET_SNAP_ATTR_EN
    {
        /// <summary>
        /// Channel Count
        /// </summary>
	    public Int32 nChannelCount; 

        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 16)]
	    public NET_QUERY_SNAP_INFO[]  stuSnap;
    } 

    
    // Screenshot params structure
    public struct SNAP_PARAMS
    {
        /// <summary>
        /// Screenshot Channel
        /// </summary>
	    public UInt32 Channel;
        /// <summary>
        /// Image Quality；1~6
        /// </summary>
	    public UInt32 Quality;
        /// <summary>
        /// Image Size；0：QCIF,1：CIF,2：D1
        /// </summary>
	    public UInt32 ImageSize;
        /// <summary>
        /// Capture mode；0：Request a frame,1：send the request regularly,2：consecutive request
        /// </summary>
	    public Int32 mode;
        /// <summary>
        /// Time unit second；If mode=1 said when sending the request regularly,the time is effective
        /// </summary>
	    public UInt32 InterSnap;
        /// <summary>
        /// Requested Sequence Number
        /// </summary>
	    public UInt32 CmdSerial;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 4)]
	    public UInt32[] Reserved;
    }

    #endregion

    #region <<Monitor Wall>>
    // CLIENT_LoadMonitorWallCollection in param struct
    struct NET_IN_WM_LOAD_COLLECTION 
    {
        public UInt32   dwSize;
        public Int32    nMonitorWallID;             //Monitor Wall ID
        public IntPtr   pszName;                    //Plan Name
    } 

    // CLIENT_LoadMonitorWallCollection out param struct 
    struct NET_OUT_WM_LOAD_COLLECTION 
    {
        public UInt32   dwSize;
    }

    // CLIENT_SaveMonitorWallCollection in param struct
    struct NET_IN_WM_SAVE_COLLECTION 
    {
        public UInt32       dwSize;
        public Int32        nMonitorWallID;            // Monitor Wall ID
        public IntPtr       pszName;                   // Plan Name
    } 

    // CLIENT_SaveMonitorWallCollection out param struct
    struct NET_OUT_WM_SAVE_COLLECTION 
    {
        public UInt32       dwSize;
    }

    #endregion

}