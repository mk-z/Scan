using System;
using System.Collections.Generic;
using System.Text;
using System.Runtime.InteropServices;

namespace VDCSDK
{
    public class VDC
    {
        #region << Public Method >>

        /// <summary>
        /// Initialization Device 
        /// </summary>
        /// <param name="pDeviceTotal">Initialization Successful Channl Number</param>
        /// <returns>Error Code</returns>
        public static int VDCInitDecDevice(ref int pDeviceTotal)
        {
            int returnValue = 0;
            returnValue = DH_InitDecDevice(ref pDeviceTotal);
            return returnValue;
        }

        /// <summary>
        /// Call when closing device, the program exits

        /// </summary>
        /// <returns>Error Code</returns>
        public static int VDCReleaseDecDevice()
        {
            int returnValue = 0;
            returnValue = DH_ReleaseDecDevice();
            return returnValue;
        }

        /// <summary>
        /// Initialise DirectDraw[The part About DirectDraw is created internally by the SDK, users do not need to call the interface function]
        /// </summary>
        /// <param name="hParent">Window Handle</param>
        /// <param name="colorKey">User Set Transparent Color</param>
        /// <returns>Error Code</returns>
        public static int VDCInitDirectDraw(IntPtr hParent, UInt32 colorKey)
        {
            int returnValue = 0;
            returnValue = DH_InitDirectDraw(hParent,colorKey);
            return returnValue;
        }
        /// <summary>
        /// Release DirectDraw
        /// </summary>
        /// <returns>Error Code</returns>
        public static int VDCReleaseDirectDraw()
        {
            int returnValue = 0;
            returnValue = DH_ReleaseDirectDraw();
            return returnValue;
        }

        /// <summary>
        /// Find the open channel, operating handle, and channel related operations must use the handle
        /// </summary>
        /// <param name="nChannelNum">Channel No.（from 0）</param>
        /// <param name="phChannel">Operation Handle</param>
        /// <returns>Error Code</returns>
        public static int VDCChannelOpen(int nChannelNum, ref UInt32 phChannel)
        {
            int returnValue = 0;
            returnValue = DH_ChannelOpen(nChannelNum, ref phChannel);
            return returnValue;
        }

        /// <summary>
        /// Close the channel, release the related resources
        /// </summary>
        /// <param name="hChannel">Channel Handle</param>
        /// <returns>Error Code</returns>
        public static int VDCChannelClose(UInt32 hChannel)
        {
            int returnValue = 0;
            returnValue = DH_ChannelClose(hChannel);
            return returnValue;
        }

        /// <summary>
        /// Open the stream interface (similar to open the file)
        /// </summary>
        /// <param name="hChannel">Channel Handle</param>
        /// <param name="pFileHeadBuf">File Head Data</param>
        /// <param name="dwSize">File Head Length</param>
        /// <returns>Error Code</returns>
        public static int VDCOpenStream(UInt32 hChannel, IntPtr pFileHeadBuf, UInt32 dwSize)
        {
            int returnValue = 0;            
            System.Console.WriteLine("dwSize:"+dwSize.ToString());
            System.IO.FileStream fs= System.IO.File.Open(@"c:\Test.txt",System.IO.FileMode.OpenOrCreate);
            char[] buffer = new char[256];
            buffer = dwSize.ToString().ToCharArray();
            byte[] buffer1 = new byte[256];
            for (int i = 0; i < 6; i++)
            {
                buffer1[i] = (byte)buffer[i];
            }
                fs.Write(buffer1, 0, 256);        
            fs.Close();
            returnValue = DH_OpenStream(hChannel, pFileHeadBuf, dwSize);
            return returnValue;
        }

        /// <summary>
        /// Open the stream interface (enhanced version)
        /// </summary>
        /// <param name="hChannel">Channel Handle</param>
        /// <param name="pFileHeadBuf">File Head Data</param>
        /// <param name="dwSize">File Head Length</param>
        /// <returns>Error Code</returns>
        public static int VDCOpenStreamEx(UInt32 hChannel, IntPtr pFileHeadBuf, UInt32 dwSize)
        {
            int returnValue = 0;
            returnValue = DH_OpenStreamEx(hChannel, pFileHeadBuf, dwSize);
            return returnValue;
        }

        /// <summary>
        /// fflush
        /// </summary>
        /// <param name="hChannel">Channel Handle</param>
        /// <returns>Error Code</returns>
        public static int VDCResetStream(UInt32 hChannel)
        {
            int returnValue = 0;
            returnValue = DH_ResetStream(hChannel);
            return returnValue;
        }
        /// <summary>
        /// Close the data flow
        /// </summary>
        /// <param name="hChannel">Channel Handle</param>
        /// <returns>Error Code</returns>
        public static int VDCCloseStream(UInt32 hChannel)
        {
            int returnValue = 0;
            returnValue = DH_CloseStream(hChannel);
            return returnValue;
        }

         /// <summary>
        /// Close the data flow
        /// </summary>
        /// <param name="hChannel">Channel Handle</param>
        /// <returns>Error Code</returns>
        public static int VDCCloseStreamEx(UInt32 hChannel)
        {
            int returnValue = 0;
            returnValue = DH_CloseStreamEx(hChannel);
            return returnValue;
        }

        /// <summary>
        /// Input data after opening the stream 
        /// </summary>
        /// <param name="hChannel">Channel Handle</param>
        /// <param name="pBuf">Buffer Address</param>
        /// <param name="dwSize">Buffer Area Size</param>
        /// <returns>Error Code</returns>
        public static int VDCInputData(UInt32 hChannel, IntPtr pBuf, UInt32 dwSize)
        {
            int returnValue = 0;
            returnValue = DH_InputData(hChannel, pBuf, dwSize);
            return returnValue;
        }

        /// <summary>
        /// Open the file
        /// </summary>
        /// <param name="hChannel">Channel Handle</param>
        /// <param name="szFileName">File Name</param>
        /// <returns>Error Code</returns>
        public static int VDCOpenFile(UInt32 hChannel,string szFileName)
        {
            int returnValue = 0;
            returnValue = DH_OpenFile(hChannel,szFileName);
            return returnValue;
        }
        /// <summary>
        /// Close the file
        /// </summary>
        /// <param name="hChannel">Channel Handle</param>
        /// <returns>Error Code</returns>
        public static int VDCCloseFile(UInt32 hChannel)
        {
            int returnValue = 0;
            returnValue = DH_CloseFile(hChannel);
            return returnValue;
        }
        /// <summary>
        /// Start to Paly
        /// </summary>
        /// <param name="hChannel">Channel Handle</param>
        /// <param name="hwnd">Window Handle</param>
        /// <returns>Error Code</returns>
        public static int VDCPlay(UInt32 hChannel, IntPtr hwnd)
        {
            int returnValue = 0;
            returnValue = DH_Play(hChannel, hwnd);
            return returnValue;
        }
        /// <summary>
        /// Pause
        /// </summary>
        /// <param name="hChannel">Channel Handle</param>
        /// <param name="bPause">true: pause;false: continue</param>
        /// <returns>Error Code</returns>
        public static int VDCPause(UInt32 hChannel, bool bPause)
        {
            int returnValue = 0;            
            returnValue = DH_Pause(hChannel,(uint) (bPause==true?1:0));
            return returnValue;
        }
        /// <summary>
        /// Stop
        /// </summary>
        /// <param name="hChannel">Channel Handle</param>
        /// <returns>Error Code</returns>
        public static int VDCStop(UInt32 hChannel)
        {
            int returnValue = 0;
            returnValue = DH_Stop(hChannel);
            return returnValue;
        }

        #endregion

        #region << Entrust >>
        public delegate void fnDecProgressCB(int nCurrent, int nTotal, IntPtr dwUser);
        public delegate void FILE_REF_DONE_CALLBACK(uint nChannel, uint nSize);
        public delegate void IMAGE_STREAM_CALLBACK(uint nDisplayChannel, IntPtr context);
        #endregion

        #region << Enumeration Definition >>

        /// <summary>
        /// Video Standards 
        /// </summary>
        public enum VIDEO_STANDARD
        {
            PAL,
            NTSC,
            UNKNOW,
        }

        #endregion

        #region << Structure Definition >>
        // Structural Definition 
        public struct tagDSPDetail
        {
            public uint encodeChannelCount;				//the number of coded channel on the board
            public uint firstEncodeChannelIndex;		//the first channel coding index on board
            public uint decodeChannelCount;				//the number of decoded channel for the board
            public uint firstDecodeChannelIndex;		//the first channel decoding index on board
            public uint displayChannelCount;			//the video output channel number in  board 
            public uint firstDisplayChannelIndex;		///the first channel coding index for the video output channel
            public uint reserved1;						/*reserve*/
            public uint reserved2;						/*reserve*/
            public uint reserved3;						/*reserve*/
            public uint reserved4;						/*reserve*/
        };

        public struct DS_BOARD_DETAIL
        {
            public int /*BOARD_TYPE_DS*/ type; // Board Type
            [MarshalAs(UnmanagedType.ByValArray, SizeConst = 16)]
            public byte[] sn; //Serial Number
            public uint dspCount; //The number of DSP in board
            public uint firstDspIndex; //The first DSP index in all the index of the DSP of board
            public uint encodeChannelCount; //the number of coded channel on the board
            public uint firstEncodeChannelIndex; //the first channel coding index on board
            public uint decodeChannelCount; //the first channel decoding index on board
            public uint firstDecodeChannelIndex; //The first channel decoding in all the decoding
            public uint displayChannelCount; //the video output channel number in  board 
            public uint firstDisplayChannelIndex; //the first channel coding index for the video output channel
            public uint reserved1;
            public uint reserved2;
            public uint reserved3;
            public uint reserved4;
        };

        public struct REGION_PARAM
        {
            public uint left;// Area of the left border
            public uint top; //Area of the up border
            public uint width; //Width Of Region
            public uint height; //Height Of Region
            public UInt32 color; //Regional background color
            public uint param; //Regional extension parameter
        };
        public struct SYSTEMTIME
        {
            public UInt16 wYear;
            public UInt16 wMonth;
            public UInt16 wDayOfWeek;
            public UInt16 wDay;
            public UInt16 wHour;
            public UInt16 wMinute;
            public UInt16 wSecond;
            public UInt16 wMilliseconds;
        };
        public struct tagVersion
        {
            public UInt32 nSDKVer;
            public UInt32 nSDKBuildTime;

            public UInt32 nDriverVer;
            public UInt32 nDriBuildTime;

            public UInt32 nDSPVer;
            public UInt32 nDSPBuildTime;
        };

        #endregion
        #region << Original SDK Call >>
        /// <summary>
        /// Initialization Device
        /// </summary>
        /// <param name="pDeviceTotal">Initialization Successful Channel Number</param>
        /// <returns>Error Code</returns>
        [DllImport("VDCDecode.dll")]
        private static extern int DH_InitDecDevice(ref int pDeviceTotal);

        [DllImport("VDCDecode.dll")]
        private static extern int DH_SetDECProgressCB(fnDecProgressCB fnCallback, UInt32 dwUser);

        [DllImport("VDCDecode.dll")]
        private static extern int DH_ReleaseDecDevice();

        [DllImport("VDCDecode.dll")]
        private static extern int DH_InitDirectDraw(IntPtr hParent, UInt32 colorKey);
        [DllImport("VDCDecode.dll")]
        private static extern int DH_ReleaseDirectDraw();
        [DllImport("VDCDecode.dll")]
        private static extern int DH_ChannelOpen(Int32 nChannelNum, ref UInt32 phChannel);

        [DllImport("VDCDecode.dll")]
        private static extern int DH_ChannelClose(UInt32 hChannel);

        //Open Part
        [DllImport("VDCDecode.dll")]
        private static extern int DH_OpenStream(UInt32 hChannel, IntPtr pFileHeadBuf, UInt32 dwSize);

        [DllImport("VDCDecode.dll")]
        private static extern int DH_ResetStream(UInt32 hChannel);
        [DllImport("VDCDecode.dll")]
        private static extern int DH_CloseStream(UInt32 hChannel);

        [DllImport("VDCDecode.dll")]
        private static extern int DH_InputData(UInt32 hChannel, IntPtr pBuf, UInt32 dwSize);
        [DllImport("VDCDecode.dll")]
        private static extern int DH_OpenFile(UInt32 hChannel, string szFileName);

        [DllImport("VDCDecode.dll")]
        private static extern int DH_CloseFile(UInt32 hChannel);
        [DllImport("VDCDecode.dll")]
        private static extern int DH_SetDisplayPara(UInt32 hChannel, IntPtr pPara);

        [DllImport("VDCDecode.dll")]
        private static extern int DH_Play(UInt32 hChannel, IntPtr hwnd);

        [DllImport("VDCDecode.dll")]
        private static extern int DH_Stop(UInt32 hChannel);

        [DllImport("VDCDecode.dll")]
        private static extern int DH_Pause(UInt32 hChannel, UInt32 bPause);

        [DllImport("VDCDecode.dll")]
        private static extern int DH_PlaySound(UInt32 hChannel);

        [DllImport("VDCDecode.dll")]
        private static extern int DH_StopSound(UInt32 hChannel);

        [DllImport("VDCDecode.dll")]
        private static extern int DH_SetVolume(UInt32 hChannel, UInt32 nVolume);

        //overlay part(not been used)
        [DllImport("VDCDecode.dll")]
        private static extern int DH_RefreshSurface();
        [DllImport("VDCDecode.dll")]
        private static extern int DH_ReStoreSurface();
        [DllImport("VDCDecode.dll")]
        private static extern int DH_ClearSurface();


        [DllImport("VDCDecode.dll")]
        private static extern int DH_ZoomOverlay(IntPtr pSrcClientRect, IntPtr pDecScreenRect);

        [DllImport("VDCDecode.dll")]
        private static extern int DH_StartCapFile(UInt32 hChannel, string sFileName);
        [DllImport("VDCDecode.dll")]
        private static extern int DH_StopCapFile(UInt32 hChannel);

        [DllImport("VDCDecode.dll")]
        private static extern int DH_GetYV12Image(UInt32 hChannel, ref string pBuffer, UInt32 nSize);

        [DllImport("VDCDecode.dll")]
        private static extern int DH_GetPictureSize(UInt32 hChannel, ref UInt32 pWidth, ref UInt32 pHeight);

        [DllImport("VDCDecode.dll")]
        private static extern int DH_ConvertToBmpFile(ref byte[] pBuf, UInt32 nSize, UInt32 nWidth, UInt32 nHeight,
                                                      ref  string sFileName, UInt32 nReserved);

        [DllImport("VDCDecode.dll")]
        private static extern int DH_Jump(UInt32 hChannel, UInt32 nDirection);
        [DllImport("VDCDecode.dll")]
        private static extern int DH_SetJumpInterval(UInt32 hChannel, UInt32 nSecond);

        [DllImport("VDCDecode.dll")]
        private static extern int DH_GetSpeed(UInt32 hChannel, ref Int32 pSpeed);

        [DllImport("VDCDecode.dll")]
        private static extern int DH_SetSpeed(UInt32 hChannel, Int32 nSpeed);

        [DllImport("VDCDecode.dll")]
        private static extern int DH_SetPlayPos(UInt32 hChannel, UInt32 nPos);

        [DllImport("VDCDecode.dll")]
        private static extern int DH_GetPlayPos(UInt32 hChannel, ref UInt32 pPos);

        [DllImport("VDCDecode.dll")]
        private static extern int DH_GetVersion(ref tagVersion pVersion);
        [DllImport("VDCDecode.dll")]
        private static extern int DH_GetCurrentFrameRate(UInt32 hChannel, ref UInt32 pFrameRate);

        [DllImport("VDCDecode.dll")]
        private static extern int DH_GetCurrentFrameNum(UInt32 hChannel, ref UInt32 pFrameNum);

        [DllImport("VDCDecode.dll")]
        private static extern int DH_GetFileTotalFrames(UInt32 hChannel, ref UInt32 pTotalFrames);
        [DllImport("VDCDecode.dll")]
        private static extern int DH_GetFileTime(UInt32 hChannel, ref UInt32 pFileTime);

        [DllImport("VDCDecode.dll")]
        private static extern int DH_GetCurrentFrameTime(UInt32 hChannel, ref UInt32 pFrameTime);

        [DllImport("VDCDecode.dll")]
        private static extern int DH_GetPlayedFrames(UInt32 hChannel, ref UInt32 pDecVFrames);

        [DllImport("VDCDecode.dll")]
        private static extern int DH_GetDeviceSerialNo(UInt32 hChannel, ref UInt32 pDeviceSerialNo);

        [DllImport("VDCDecode.dll")]
        private static extern int DH_SetFileEndMsg(UInt32 hChannel, IntPtr hWnd, uint nMsg);

        [DllImport("VDCDecode.dll")]
        private static extern int DH_SetStreamOpenMode(UInt32 hChannel, UInt32 nMode);

        [DllImport("VDCDecode.dll")]
        private static extern int DH_GetStreamOpenMode(UInt32 hChannel, ref UInt32 pMode);

        [DllImport("VDCDecode.dll")]
        private static extern int DH_SetVideoOutStandard(UInt32 hChannel, UInt32 nStandard);

        [DllImport("VDCDecode.dll")]
        private static extern int DH_SetDspDeadlockMsg(IntPtr hWnd, uint nMsg);

        [DllImport("VDCDecode.dll")]
        private static extern int DH_GetChannelNum(Int32 nDspNum, ref Int32 pChannelNum, UInt32 nNumsToGet, ref UInt32 pNumsGotten);

        [DllImport("VDCDecode.dll")]
        private static extern int DH_ResetDsp(Int32 nDspNum);

        [DllImport("VDCDecode.dll")]
        private static extern int DH_SetAudioPreview(UInt32 hChannel, bool bEnable);

        [DllImport("VDCDecode.dll")]
        private static extern uint DH_GetDspCount();

        [DllImport("VDCDecode.dll")]
        private static extern int DH_GetDspDetail(uint dspNum, ref tagDSPDetail pDspDetail);

        [DllImport("VDCDecode.dll")]
        private static extern int DH_GetBoardDetail(uint boardNum, ref DS_BOARD_DETAIL pBoardDetail);

        [DllImport("VDCDecode.dll")]
        private static extern int DH_OpenStreamEx(UInt32 hChannel, IntPtr pFileHeadBuf, UInt32 nSize);

        [DllImport("VDCDecode.dll")]
        private static extern int DH_CloseStreamEx(UInt32 hChannel);

        [DllImport("VDCDecode.dll")]
        private static extern int DH_InputVideoData(UInt32 hChannel, ref string pBuf, UInt32 dwSize);

        [DllImport("VDCDecode.dll")]
        private static extern int DH_InputAudioData(UInt32 hChannel, ref string pBuf, UInt32 nSize);
        [DllImport("VDCDecode.dll")]
        private static extern int DH_GetBoardCount();



        [DllImport("VDCDecode.dll")]
        private static extern int DH_SetDefaultVideoStandard(VIDEO_STANDARD VideoStandard);

        [DllImport("VDCDecode.dll")]
        private static extern int DH_GetDisplayChannelCount();

        [DllImport("VDCDecode.dll")]
        private static extern int DH_SetDisplayStandard(uint nDisplayChannel, VIDEO_STANDARD VideoStandard);

        [DllImport("VDCDecode.dll")]
        private static extern int DH_SetDisplayRegion(uint nDisplayChannel, uint nRegionCount,
                                                        ref REGION_PARAM pParam, uint nReserved);

        [DllImport("VDCDecode.dll")]
        private static extern int DH_ClearDisplayRegion(uint nDisplayChannel, uint nRegionFlag);

        [DllImport("VDCDecode.dll")]
        private static extern int DH_SetDisplayRegionPosition(uint nDisplayChannel,
                                                               uint nRegion, uint nLeft, uint nTop);
        [DllImport("VDCDecode.dll")]
        private static extern int DH_FillDisplayRegion(uint nDisplayChannel, uint nRegion, ref byte[] pImage);
        [DllImport("VDCDecode.dll")]
        private static extern int DH_SetDecoderAudioOutput(uint nDecodeChannel, bool bOpen, uint nOutputChannel);

        [DllImport("VDCDecode.dll")]
        private static extern int DH_SetDecoderVideoOutput(uint nDecodeChannel, uint nPort, bool bOpen,
                                                            uint nDisplayChannel, uint nDisplayRegion, uint nReserved);
        [DllImport("VDCDecode.dll")]
        private static extern int DH_SetDecoderVideoExtOutput(uint nDecodeChannel, uint nPort, bool bOpen,
                                                               uint nDisplayChannel, uint nDisplayRegion, uint nReserved);

        [DllImport("VDCDecode.dll")]
        private static extern int DH_SetFileRef(UInt32 hChannel, bool bEnable, FILE_REF_DONE_CALLBACK FileRefDoneCallback);

        [DllImport("VDCDecode.dll")]
        private static extern int DH_GetFileAbsoluteTime(UInt32 hChannel,ref  SYSTEMTIME pStartTime,ref  SYSTEMTIME pEndTime);

        [DllImport("VDCDecode.dll")]
        private static extern int DH_GetCurrentAbsoluteTime(UInt32 hChannel, ref SYSTEMTIME pTime);

        [DllImport("VDCDecode.dll")]
        private static extern int DH_LocateByAbsoluteTime(UInt32 hChannel, SYSTEMTIME time);

        [DllImport("VDCDecode.dll")]
        private static extern int DH_LocateByFrameNumber(UInt32 hChannel, uint frmNum);

        [DllImport("VDCDecode.dll")]
        private static extern int DH_ImportFileRef(UInt32 hChannel, byte[] pBuffer, uint nSize);

        [DllImport("VDCDecode.dll")]
        private static extern int DH_ExportFileRef(UInt32 hChannel, byte[] pBuffer, uint nSize);

        [DllImport("VDCDecode.dll")]
        private static extern int DH_SetDisplayVideoCapture(uint nDisplayChannel, bool bStart, uint fps,
                                                             uint width, uint height, ref byte[] imageBuffer);


        [DllImport("VDCDecode.dll")]
        private static extern int RegisterDisplayVideoCaptureCallback(IMAGE_STREAM_CALLBACK DisplayVideoCaptureCallback, IntPtr context);

        [DllImport("VDCDecode.dll")]
        private static extern int SetDisplayVideoBrightness(uint chan, int Brightness);

        [DllImport("VDCDecode.dll")]
        private static extern int DH_SetDecoderPostProcess(UInt32 hChannel, uint param);

        [DllImport("VDCDecode.dll")]
        private static extern int DH_SetTVMargin(UInt32 hChannel, int left, int top, int right, int bottom);


        //Raw data play part

        [DllImport("VDCDecode.dll")]
        private static extern int DH_SetRawPlayMode(UInt32 hChannel, bool bRaw);

        [DllImport("VDCDecode.dll")]
        private static extern int DH_UpdateVideoFormat(UInt32 hChannel, int nWidth, int nHeight, int nFrameRate, int videoFormat);

        [DllImport("VDCDecode.dll")]
        private static extern int DH_InputRawData(UInt32 hChannel, ref byte[] pBuf, int nSize);

        #endregion
    }
}
