using System;
using System.Collections.Generic;
using System.Text;
using System.Runtime.InteropServices;
using System.ComponentModel;


namespace PlaySDK
{
    #region << DHPlay class definition >>
    public sealed class NETPlay
    {
        /// <summary>
        /// whether it has initialized
        /// </summary>
        private static bool initialized = false;

        /// <summary>
        /// whether shoot off mistake[default no pop,only return mistake to attribute LastOperationInfo]
        /// </summary>
        private static bool pShowException = false;

        #region << attribute >>
        //Temporarily no
        #endregion

        #region << Class method >>

        #region << private method >>

        /// <summary>
        /// When call SDK fail ,it shoot off abnormity and  when succeed,it return no abnormity and copy operational information to LastOperationInfo
        /// </summary>
        /// <param name="nPort">play channel</param>
        /// <exception cref="Win32Exception">primary anomalies,when call SDK failed,it strike.</exception>
        private static OPERATION_INFO NETThrowLastError(int nPort)
        {
            OPERATION_INFO returnValue;
            Int32 errorCode = (int)PLAY_GetLastError(nPort);
            returnValue.errCode = errorCode.ToString();
            returnValue.errMessage = NETGetLastErrorName((uint)errorCode);
            if (pShowException == true)
            {
                throw new Win32Exception(errorCode, returnValue.errMessage);
            }
            return returnValue;
        }

        /// <summary>
        /// The error code switch to normal discription of the error message
        /// </summary>
        /// <param name="errorCode">Error code</param>
        /// <returns>Normal discription of the error message</returns>
        private static string NETGetLastErrorName(uint errorCode)
        {
            switch (errorCode)
            {
                case 0x80000000 | 0:
                    return "No error";
                case 0x80000000 | 1:
                    return "Illegal parameters input";
                case 0x80000000 | 2:
                    return "Wrong calling order";
                case 0x80000000 | 3:
                    return "Multimedia clock setup failed";
                case 0x80000000 | 4:
                    return "Video decoding failed";
                case 0x80000000 | 5:
                    return "Audio decoding failed";
                case 0x80000000 | 6:
                    return "Allocate memory failed";
                case 0x80000000 | 7:
                    return "fail operate failed";
                case 0x80000000 | 8:
                    return "The events like creating thread failed";
                case 0x80000000 | 9:
                    return "Creat directDraw failed";
                case 0x80000000 | 10:
                    return "Create back-end cache failed";
                case 0x80000000 | 11:
                    return "The cache is full ,the input stream failed";
                case 0x80000000 | 12:
                    return "Create audio equipment failed";
                case 0x80000000 | 13:
                    return "Setup sound volume failed";
                case 0x80000000 | 14:
                    return "Only used when play files";
                case 0x80000000 | 15:
                    return "Only used when play stream";
                case 0x80000000 | 16:
                    return "System nonsupport,decoder only work upon Pentium 3";
                case 0x80000000 | 17:
                    return "No file header";
                case 0x80000000 | 18:
                    return "No corresponding of version of decoder and encoder ";
                case 0x80000000 | 19:
                    return "Initialize file failed";
                case 0x80000000 | 20:
                    return "File is too short or stream cannot be realized";
                case 0x80000000 | 21:
                    return "weiInitialize multimedia clock failed";
                case 0x80000000 | 22:
                    return "Bit copy failed";
                case 0x80000000 | 23:
                    return "Display 'overlay' failed";
                default:
                    return "Unknown error";
            }
        }

        #region << Shield code >>

        //private static void NETThrowLastError(int returnValue)
        //{
        //    if (returnValue == 0)
        //    {
        //        NETThrowLastError();
        //    }
        //    else
        //    {
        //        pErrInfo.errCode = "0";
        //        pErrInfo.errMessage = "There is no abnormity in recent operation";
        //    }
        //}

        //private static void NETThrowLastError(bool returnValue)
        //{
        //    if (returnValue == false)
        //    {
        //        NETThrowLastError();
        //    }
        //    else
        //    {
        //        pErrInfo.errCode = "0";
        //        pErrInfo.errMessage = "There is no abnormity in recent operation";
        //    }
        //}

        ///// <summary>
        ///// Shoot off abnormity when call SDK failed
        ///// </summary>
        ///// <param name="e"></param>
        //private static void NETThrowLastError(Exception e)
        //{

        //    pErrInfo.errCode = e.ToString();
        //    pErrInfo.errMessage = e.Message;
        //    if (pShowException == true)
        //    {
        //        throw e;
        //    }
        //}

        #endregion

        #endregion

        #region << Public method >>

        #region << Setup method of shoot off error >>

        /// <summary>
        /// Setup about whether shoot off error information in usage of this kind of program[Default no pop,only return error information to attribute'LastOperationInfo']
        /// </summary>
        /// <param name="blnShowException">
        /// true:Shoot off error information,and return error information to attribute 'LastOperationInfo',let clients dispose voluntarily;
        /// false:Not shoot off error information,and return error information to attribute 'LastOperationInfo',no any dispose,clients can judge whether there is errors by method`s return value or 
        ///       'LastOperationInfo',then make corresponding processing
        /// </param>
        public static void NETSetShowException(bool blnShowException)
        {
            pShowException = blnShowException;
        }

        #endregion

        #region << Play file >>

        /// <summary>
        /// Play control
        /// </summary>
        /// <param name="pPlayCom">
        /// Play order:
        /// 1.PLAY_COMMAND.StopSound:Stop voice
        /// </param>
        /// <returns>true:Succeed;false:failed</returns>
        public static bool NETPlayControl(PLAY_COMMAND pPlayCom)
        {
            bool returnValue = false;
            if (pPlayCom == PLAY_COMMAND.StopSound)
            {
                returnValue = PLAY_StopSound();
                NETThrowLastError(0);
            }
            return returnValue;    
        }

        /// <summary>
        /// Play control
        /// </summary>
        /// <param name="pPlayCom">
        /// Play order:
        /// 1.PLAY_COMMAND.SetVolume:Setup volume
        /// 2.PLAY_COMMAND.SetCurrentFrameNum:set play frame nu.
        /// </param>
        /// <param name="nPort">Play channel</param>
        /// <param name="nValue">Order parameter value</param>
        /// <returns>true:Succeed;false:Failed</returns>
        public static bool NETPlayControl(PLAY_COMMAND pPlayCom, int nPort, UInt32 nValue)
        {
            bool returnValue = false;
            switch (pPlayCom)
            {
                case PLAY_COMMAND.SetVolume:
                    returnValue = PLAY_SetVolume(nPort, nValue);
                    break;
                case PLAY_COMMAND.SetCurrentFrameNum:
                    returnValue = PLAY_SetCurrentFrameNum(nPort, nValue);
                    break;
                case PLAY_COMMAND.SetPlayedTimeEx:
                    returnValue = PLAY_SetPlayedTimeEx(nPort, nValue);
                    break;
            }
            NETThrowLastError(nPort);
            return returnValue;   
        }

        /// <summary>
        /// Play control
        /// </summary>
        /// <param name="pPlayCom">
        /// Play order:
        /// 1.PLAY_COMMAND.SetPlayPos:Setup the relative position of file playing(precentage)
        /// </param>
        /// <param name="nPort">Play channel</param>
        /// <param name="nValue">parameter value</param>
        /// <returns>true:Succeed;false:failed</returns>
        public static bool NETPlayControl(PLAY_COMMAND pPlayCom, int nPort, ref float nValue)
        {
            bool returnValue = false;
            switch (pPlayCom)
            {
                case PLAY_COMMAND.SetPlayPos:
                    returnValue = PLAY_SetPlayPos(nPort, nValue);
                    break;
                case PLAY_COMMAND.GetPlayPos:                    
                    nValue = PLAY_GetPlayPos(nPort);
                    returnValue = true;
                    break;
            }
            NETThrowLastError(nPort);
            return returnValue;
        }
        

        /// <summary>
        /// Play control
        /// </summary>
        /// <param name="pPlayCom">
        /// Play order:
        /// 1.PLAY_COMMAND.Start:Start play
        /// </param>
        /// <param name="nPort">Play channel number</param>
        /// <param name="hWnd">Play case`s sentence handel</param>
        /// <returns>true:succeed;false:failed</returns>
        public static bool NETPlayControl(PLAY_COMMAND pPlayCom, int nPort, IntPtr hWnd)
        {
            bool returnValue = false;
            if (pPlayCom == PLAY_COMMAND.Start)
            {
                returnValue = PLAY_Play(nPort, hWnd);
                NETThrowLastError(nPort);
            }
            return returnValue;            
        }

        /// <summary>
        /// play control
        /// </summary>
        /// <param name="pPlayCom">
        /// play order:
        /// 1.PLAY_COMMAND.OpenFile:open file;
        /// 2.PLAY_COMMAND.CatchPic:catch picture;</param>
        /// <param name="nPort">Play channel number</param>
        /// <param name="sFileName">open/save file name</param>
        /// <returns>true:succeed;false:failed</returns>
        public static bool NETPlayControl(PLAY_COMMAND pPlayCom, int nPort, string sFileName)
        {
            bool returnValue = false;
            switch (pPlayCom)
            {
                case PLAY_COMMAND.OpenFile:
                    returnValue = PLAY_OpenFile(nPort, sFileName);
                    break;
                case PLAY_COMMAND.CatchPic:
                    returnValue = PLAY_CatchPic(nPort, sFileName);
                    break;
            }
            NETThrowLastError(nPort);
            return returnValue;
        }

        /// <summary>
        /// play control
        /// </summary>
        /// <param name="pPlayCom">
        /// play order:
        /// 1.PLAY_COMMAND.Stop:stop;
        /// 2.PLAY_COMMAND.CloseFile:close file;
        /// 3.PLAY_COMMAND.Pause:pause play;
        /// 4.PLAY_COMMAND.ReSume:keep on play;
        /// 5.PLAY_COMMAND.Fast:rapid play;
        /// 6.PLAY_COMMAND.Slow:slow play;
        /// 7.PLAY_COMMAND.OneByOne:single frame play;
        /// 8.PLAY_COMMAND.PlaySound:play sound;
        /// 9.PLAY_COMMAND.PlaySoundShare:share play sound;
        /// 10.PLAY_COMMAND.StopSoundShare:stop share play sound;
        /// 11.PLAY_COMMAND.OneByOneBack:single frame play back
        /// 12.PLAY_COMMAND.CloseStream:close data stream
        /// 13.PLAY_COMMAND.CloseStreamEx:close data stream(open stream in the way that video and audio detach)
        /// </param>
        /// <param name="nPort">play channel number</param>
        /// <returns>true:succeed;false:failed</returns>
        public static bool NETPlayControl(PLAY_COMMAND pPlayCom, int nPort)
        {
            bool returnValue = false;

            switch (pPlayCom)
            {
                case PLAY_COMMAND.Stop://stop
                    returnValue = PLAY_Stop(nPort);
                    break;
                case PLAY_COMMAND.CloseFile://close file
                    returnValue = PLAY_CloseFile(nPort);
                    break;
                case PLAY_COMMAND.Pause://pause play
                    returnValue = PLAY_Pause(nPort, 1);
                    break;
                case PLAY_COMMAND.ReSume://keep on play
                    returnValue = PLAY_Pause(nPort, 0);
                    break;
                case PLAY_COMMAND.Fast://rapid play
                    returnValue = PLAY_Fast(nPort);
                    break;
                case PLAY_COMMAND.Slow://slow play
                    returnValue = PLAY_Slow(nPort);
                    break; 
                case PLAY_COMMAND.OneByOne://single frame play
                    returnValue = PLAY_OneByOne(nPort);
                    break;
                case PLAY_COMMAND.OneByOneBack://single frame play back
                    returnValue = PLAY_OneByOneBack(nPort);
                    break;
                case PLAY_COMMAND.PlaySound://play sound
                    returnValue = PLAY_PlaySound(nPort);
                    break;
                case PLAY_COMMAND.PlaySoundShare://share play sound
                    returnValue = PLAY_PlaySoundShare(nPort);
                    break;
                case PLAY_COMMAND.StopSoundShare://stop share play sound
                    returnValue = PLAY_StopSoundShare(nPort);
                    break;                    
                case PLAY_COMMAND.ToBegin:
                    if (!NETPlayControl(PLAY_COMMAND.SetCurrentFrameNum, nPort, (uint)0))
                    {
                        if (!NETPlayControl(PLAY_COMMAND.SetPlayedTimeEx, nPort, (uint)0))
                        {
                            float playBegionPos = 0.00F;
                            if (!NETPlayControl(PLAY_COMMAND.SetPlayPos, nPort, ref playBegionPos))
                            {
                                returnValue = false;
                                break;
                            }
                        }
                    }
                    returnValue = true;
                    break;
                case PLAY_COMMAND.ToEnd:
                    if (!NETPlayControl(PLAY_COMMAND.SetCurrentFrameNum, nPort,NETPlayControl(PLAY_COMMAND.GetFileTotalFrames,nPort,true)-1))
                    {
                        if (!NETPlayControl(PLAY_COMMAND.SetPlayedTimeEx, nPort, NETPlayControl(PLAY_COMMAND.GetFileTotalTime, nPort, true)))
                        {
                            float playEndPos = 0.99F;
                            if (!NETPlayControl(PLAY_COMMAND.SetPlayPos, nPort, ref playEndPos))
                            {
                                returnValue = false;
                                break;
                            }                            
                        }
                    }
                    returnValue = true;
                    break;
                case PLAY_COMMAND.CloseStream:
                    returnValue = PLAY_CloseStream(nPort);
                    break;
                case PLAY_COMMAND.CloseStreamEx:
                    returnValue = PLAY_CloseStreamEx(nPort);
                    break;
                case PLAY_COMMAND.ReleasePort:
                    returnValue = PLAY_ReleasePort(nPort);
                    break;
                case PLAY_COMMAND.Forward://play forward
                    returnValue = PLAY_SetPlayDirection(nPort, 0);
                    break;
                case PLAY_COMMAND.Backward://play backward
                    returnValue = PLAY_SetPlayDirection(nPort, 1);
                    break;
                default:
                    return false;
            }

            NETThrowLastError(nPort);
            return returnValue;
        }

        /// <summary>
        /// play control
        /// </summary>
        /// <param name="pPlayCom">
        /// play order:
        /// 1.PLAY_COMMAND.GetCurrentFrameNum:get the list number of current frame;
        /// 2.PLAY_COMMAND.GetCurrentFrameRate:get current frame rate;
        /// 3.PLAY_COMMAND.GetFileTotalTime:get file`s total time length,unit is second;
        /// 4.PLAY_COMMAND.GetFileTotalFrames:get file`s total number of frame;
        /// 5.PLAY_COMMAND.GetPlayedTime:get the time of current play,unit is second;
        /// 6.PLAY_COMMAND.GetPlayedTimeEx:get the current play`s time ,unit is millisecond;
        /// 7.PLAY_COMMAND.GetVolume:get current setting`s voice;
        /// </param>
        /// <param name="nPort">play channel number</param>
        /// <param name="blnReturnValue">this parameter is invalid,just to different over loading,must input a bool value</param>
        /// <returns>corresponding order`s value</returns>
        public static UInt32 NETPlayControl(PLAY_COMMAND pPlayCom, int nPort,bool blnReturnValue)
        {
            UInt32 returnValue = 0;

            switch (pPlayCom)
            {
                case PLAY_COMMAND.GetCurrentFrameNum:
                    returnValue = PLAY_GetCurrentFrameNum(nPort);
                    break;
                case PLAY_COMMAND.GetCurrentFrameRate:
                    returnValue = PLAY_GetCurrentFrameRate(nPort);
                    break;
                case PLAY_COMMAND.GetFileTotalTime:
                    returnValue = PLAY_GetFileTime(nPort);
                    break;
                case PLAY_COMMAND.GetFileTotalFrames:
                    returnValue = PLAY_GetFileTotalFrames(nPort);
                    break;
                case PLAY_COMMAND.GetPlayedTime:
                    returnValue = PLAY_GetPlayedTime(nPort);
                    break;
                case PLAY_COMMAND.GetPlayedTimeEx:
                    returnValue = PLAY_GetPlayedTimeEx(nPort);
                    break;
                case PLAY_COMMAND.GetVolume:
                    returnValue = PLAY_GetVolume(nPort);
                    break;
            }
            NETThrowLastError(nPort);
            return returnValue;
        }

        /// <summary>
        /// play control
        /// </summary>
        /// <param name="pPlayCom">
        /// play order:
        /// 1.PLAY_COMMAND.GetColor:get color value
        /// </param>
        /// <param name="nPort">play channel number</param>
        /// <param name="nRegionNum">show area</param>
        /// <param name="returnColor">color`s reback value</param>
        /// <returns>true:succeed;false:failed</returns>
        public static bool NETPlayControl(PLAY_COMMAND pPlayCom, int nPort, UInt32 nRegionNum,ref COLOR_STRUCT returnColor)
        {
            bool returnValue = false;
            switch (pPlayCom)
            { 
                case PLAY_COMMAND.GetColor:
                    returnValue = PLAY_GetColor(nPort, nRegionNum, ref returnColor.pBrightness, ref returnColor.pContrast, ref returnColor.pSaturation, ref returnColor.pHue);
                    break;
                case PLAY_COMMAND.SetColor:
                    returnValue = PLAY_SetColor(nPort, nRegionNum, returnColor.pBrightness, returnColor.pContrast, returnColor.pSaturation, returnColor.pHue);
                    break;
            }
            NETThrowLastError(nPort);
            return returnValue;
        }

        /// <summary>
        /// play control
        /// </summary>
        /// <param name="pPlayCom">
        /// play order:
        /// 1.PLAY_COMMAND.GetPictureSize:get frame`s original picture size
        /// </param>
        /// <param name="nPort">play channel</param>
        /// <param name="frameInfo">frame information</param>
        /// <returns>true:succeed;false:failed</returns>
        public static bool NETPlayControl(PLAY_COMMAND pPlayCom, int nPort, ref FRAME_INFO frameInfo)
        {
            bool returnValue = false;
            switch (pPlayCom)
            { 
                case PLAY_COMMAND.GetPictureSize:
                    returnValue = PLAY_GetPictureSize(nPort, ref frameInfo.nWidth, ref frameInfo.nHeight);
                    break;
            }
            NETThrowLastError(nPort);
            return returnValue;
        }


        /// <summary>
        /// play control
        /// </summary>
        /// <param name="pPlayCom">
        /// play order:
        /// 1.PLAY_COMMAND.GetDateTimeInfo:get date time
        /// </param>
        /// <param name="nPort">play channel</param>
        /// <param name="pBuf">buf to store datetime</param>
        /// <param name="nBufLen">lenth of buf</param>
        /// <param name="pRetLen">return availible lenth</param>
        /// <returns>true:succeed;false:failed</returns>
        public static bool NETPlayControl(PLAY_COMMAND pPlayCom, int nPort, IntPtr pBuf, int nBufLen, ref int pRetLen)
        {
            bool returnValue = false;
            switch (pPlayCom)
            {
                case PLAY_COMMAND.GetDateTimeInfo:
                    returnValue = PLAY_QueryInfo(nPort, 1, pBuf, nBufLen, ref pRetLen);
                    break;
            }
            NETThrowLastError(nPort);
            return returnValue;
        }

        /// <summary>
        /// Play control
        /// </summary>
        /// <param name="pPlayCom">
        /// Play order:
        /// 1.PLAY_COMMAND.ResetBuffer:Reset play buffer
        /// </param>
        /// <param name="nPort">Play channel</param>
        /// <param name="nBufType">buffer type, enum BUF_TYPE</param>
        /// <returns>true:Succeed;false:Failed</returns>
        public static bool NETPlayControl(PLAY_COMMAND pPlayCom, int nPort, BUF_TYPE nBufType)
        {
            bool returnValue = false;
            switch (pPlayCom)
            {
                case PLAY_COMMAND.ResetBuffer:
                    returnValue = PLAY_ResetBuffer(nPort, (UInt32)nBufType);
                    break;
            }
            NETThrowLastError(nPort);
            return returnValue;
        }
        #endregion

        #region << play data stream >>

        /// <summary>
        /// play control
        /// </summary>
        /// <param name="pPlayCom">
        /// play order:
        /// 1.PLAY_COMMAND.OpenStream:open frame interface
        /// 2.PLAY_COMMAND.OpenStreamEx:open frame in the way that video and audio is apart 
        /// </param>
        /// <param name="nPort">channel number</param>
        /// <param name="pFileHeadBuff">nonuse now,fill NULL</param>
        /// <param name="nSize">nonuse,fill 0</param>
        /// <param name="nBufPoolSize">
        /// setup the size of buffer to storage data in player
        /// range is SOURCE_BUF_MIN~ SOURCE_BUF_MAX。
        /// set 900*1024 generally,if the send data is equal relatively,can make this value small,if the data`s transport is not equal,can make the value big</param>
        /// <returns>true:succeed;false:failed</returns>
        public static bool NETPlayControl(PLAY_COMMAND pPlayCom, int nPort, IntPtr pFileHeadBuff, UInt32 nSize, UInt32 nBufPoolSize)
        {

            bool returnValue = false;
            switch (pPlayCom)
            {
                case PLAY_COMMAND.OpenStream:
                    returnValue = PLAY_OpenStream(nPort, pFileHeadBuff, nSize, nBufPoolSize);
                    break;
                case PLAY_COMMAND.OpenStreamEx:
                    returnValue = PLAY_OpenStreamEx(nPort, pFileHeadBuff, nSize, nBufPoolSize);
                    break;
            }
            NETThrowLastError(nPort);
            return returnValue;
        }

        /// <summary>
        /// play control
        /// </summary>
        /// <param name="pPlayCom">
        /// play order:
        /// 1.PLAY_COMMAND.OpenStream:input the frame data get from card ；open frame and transfer PLAY_Play,only then can you input data
        /// 2.PLAY_COMMAND.InputVideoData:input the video frame get from the card (can be complex stream,but audio data will be ignored);data can be input only after open frame 
        /// 3.PLAY_COMMAND.InputAudioData:input the audio frame get from the card；data can be input only after audio open
        /// </param>
        /// <param name="nPort">channel number</param>
        /// <param name="pBuf">buffer address</param>
        /// <param name="nSize">buffer size</param>
        /// <returns>true:succeed;false:failed</returns>
        public static bool NETPlayControl(PLAY_COMMAND pPlayCom, int nPort, IntPtr pBuf, UInt32 nSize)
        {
            bool returnValue = false;
            switch (pPlayCom)
            {
                case PLAY_COMMAND.InputData:
                    returnValue = PLAY_InputData(nPort, pBuf, nSize);
                    break;
                case PLAY_COMMAND.InputVideoData:
                    returnValue = PLAY_InputVideoData(nPort, pBuf, nSize);
                    break;
                case PLAY_COMMAND.InputAudioData:
                    returnValue = PLAY_InputAudioData(nPort, pBuf, nSize);
                    break;
            }
            NETThrowLastError(nPort);
            return returnValue;

        }

        public static bool NETPlaySetSecurityKey(int nPort, IntPtr szKey, UInt32 nKeylen)
        {
            return PLAY_SetSecurityKey(nPort, szKey, nKeylen);
        }

        public static bool NETPlayGetFreePort(IntPtr pnPort)
        {
            return PLAY_GetFreePort(pnPort);
        }

        #region << screen code >>

        ///// <summary>
        ///// play control
        ///// </summary>
        ///// <param name="pPlayCom">
        ///// play order:
        ///// 1.PLAY_COMMAND.CloseStream:close data stream
        ///// 2.PLAY_COMMAND.CloseStreamEx:close data stream(open stream in the way that video and audio is apart)
        ///// </param>
        ///// <param name="nPort">channel number</param>
        ///// <returns>true:succeed;false:failed</returns>
        //public static bool DHPlayControl(PLAY_COMMAND pPlayCom, int nPort)
        //{ 
        //    bool returnValue = false;
        //    switch (pPlayCom)
        //    {
        //        case PLAY_COMMAND.CloseStream:
        //            returnValue = PLAY_CloseStream(nPort);
        //            break;
        //        case PLAY_COMMAND.CloseStreamEx:
        //            returnValue = PLAY_CloseStreamEx(nPort);
        //            break;
        //    }
        //    NETThrowLastError(nPort);
        //    return returnValue;            
        //}

        #endregion

        #endregion

        #region << character fold >>

        /// <summary>
        /// register a call-back function,get current external device context, you can draw(or write) on this DC,just like drawing on the cilent block of the window,
        /// but this DC is not the DC of cilent block`s window ,it is the DC on the external of off-Screen in DirectDraw。notice,if use overlay external ,this port is invailed,
        /// you can draw pictures on windows directly ,it will not be covered only it is not transparent
        /// </summary>
        /// <param name="nPort">player`s channel number</param>
        /// <param name="privateDrawFun">call-back function`s sentence handle</param>
        /// <param name="nUser">user`s data</param>
        /// <returns>true:succeed;false:failed</returns>
        public static bool NETRigisterDrawFun(int nPort, DrawFun privateDrawFun, int nUser)
        {
            bool returnValue = false;
            returnValue = PLAY_RigisterDrawFun(nPort, privateDrawFun, nUser);
            NETThrowLastError(nPort);
            return returnValue;
        }

        #endregion

        #region << show in many areas >>

        /// <summary>
        /// setup and add show areas。can do local enlarged display
        /// </summary>
        /// <param name="nPort">player channel number</param>
        /// <param name="nRegionNum">show area`s serial number,0~(MAX_DISPLAY_WND-1)。if nRegionNum is 0,mean to primary display in windows</param>
        /// <param name="pSrcRect">local display area</param>
        /// <param name="hDestWnd">display window sentence handle</param>
        /// <param name="bEnable">open (setup) or close display area</param>
        /// <returns>true:succeed;false:failed</returns>
        public static bool NETSetDisplayRegion(int nPort, UInt32 nRegionNum, IntPtr pSrcRect, IntPtr hDestWnd, bool bEnable)
        {
            bool returnValue = false;
            returnValue = PLAY_SetDisplayRegion(nPort, nRegionNum, pSrcRect, hDestWnd, bEnable);
            NETThrowLastError(nPort);
            return returnValue;
        }

        /// <summary>
        /// refresh display,refresh window of multi areas display
        /// </summary>
        /// <param name="nPort">player channel number</param>
        /// <param name="nRegionNum">display area`s serial number</param>
        /// <returns>true:succeed;false:failed</returns>
        public static bool NETRefreshPlayEx(int nPort, UInt32 nRegionNum)
        {
            bool returnValue = false;
            returnValue = PLAY_RefreshPlayEx(nPort, nRegionNum);
            NETThrowLastError(nPort);
            return returnValue;

        }

        #endregion

        #region << data stream recording >>

        /// <summary>
        /// start stream data recording。only be useful to stream pattern,transfer after PLAY_Play
        /// </summary>
        /// <param name="nPort">player channel number</param>
        /// <param name="sFileName">video file name,if there is nonexistent folder in file name ,then creat this folder. </param>
        /// <param name="idataType">0:original data stream;1:AVI</param>
        /// <returns>true:succeed;false:failed</returns>
        public static bool NETStartDataRecord(int nPort, string sFileName, int idataType)
        {
            bool returnValue = false;
            returnValue = PLAY_StartDataRecord(nPort, sFileName,idataType);
            NETThrowLastError(nPort);
            return returnValue;
        }

        /// <summary>
        /// stop stream data record
        /// </summary>
        /// <param name="nPort">player channel number</param>
        /// <returns>true:succeed;false:failed</returns>
        public static bool NETStopDataRecord(int nPort)
        {
            bool returnValue = false;
            returnValue = PLAY_StopDataRecord(nPort);
            NETThrowLastError(nPort);
            return returnValue;
        }

        #endregion

        #region << call-back data >>

        /// <summary>
        /// setup call-back function
        /// </summary>
        /// <param name="nPort">port</param>
        /// <param name="cbFun">call-back function</param>
        /// <returns>true:succeed;false:failed</returns>
        public static bool NETSetDecCallBack(int nPort, DecCBFun cbFun)
        {
            bool returnValue=false;
            returnValue = PLAY_SetDecCallBack(nPort,ref cbFun);
            NETThrowLastError(nPort);
            return returnValue;
        }

        /// <summary>
        /// setup the kind of decoding call-back stream
        /// </summary>
        /// <param name="nPort">play channel number</param>
        /// <param name="streamType">decode call-back stream type</param>
        /// <returns>true:succeed;false:failed</returns>
        public static bool NETSetDecCBStream(int nPort, STREAM_TYPE streamType)
        {
            bool returnValue = false;
            
            if (streamType != STREAM_TYPE.STREAM_WITHOUT)
            {
                returnValue= PLAY_SetDecCBStream(nPort, (uint)streamType);
            }            
            NETThrowLastError(nPort);
            return returnValue;
        }

        /// <summary>
        /// setup video picture data call-back,can use to catch picture.if want to stop call-back,can set the call-back function index DisplayCBFun to NULL。
        /// once setup call-back function,it will always efficient,until process exit.this function can call-back at any time
        /// </summary>
        /// <param name="nPort">play channel number</param>
        /// <param name="dCBFun">DisplayCBFun`s call-back function</param>
        /// <param name="nUser">user-defined data,default 0</param>
        /// <returns>true:succeed;false:filed</returns>
        public static bool NETSetDisplayCallBack(int nPort, DisplayCBFun dCBFun, int nUser)
        {
            bool returnValue = false;
            returnValue = PLAY_SetDisplayCallBack(nPort, dCBFun,nUser);
            NETThrowLastError(nPort);
            return returnValue;
        }

        /// <summary>
        /// setup video picture data call-back,can use to catch picture.if want to stop call-back,can set the call-back function index DisplayCBFun to NULL。
        /// once setup call-back function,it will always efficient,until process exit.this function can call-back at any time
        /// </summary>
        /// <param name="nPort">play channel number</param>
        /// <param name="dCBFun">DisplayCBFun`s call-back function</param>
        /// <returns>true:succeed;false:failed</returns>
        public static bool NETSetDisplayCallBack(int nPort, DisplayCBFun dCBFun)
        {
            return NETSetDisplayCallBack(nPort, dCBFun, 0);
        }

        /// <summary>
        /// wave data call-back after audio frame was decoded
        /// <param name="nPort">player channel number</param>
        /// <param name="funAudio">audio call-back function</param>
        /// <param name="nUser">user-defined data</param>
        /// <returns>true:succeed;false:failed</returns>
        public static bool NETSetAudioCallBack(int nPort, FunAudio funAudio, int nUser)
        {
            bool returnValue = false;
            returnValue = PLAY_SetAudioCallBack(nPort, funAudio, nUser);
            NETThrowLastError(nPort);
            return returnValue;
        }

        #endregion

        #region << get version number >>

        /// <summary>
        /// get current player sdk`s main version number、sub version number and mend number
        /// </summary>
        /// <returns>
        /// high 16 bit mean current main version number.
        /// 9~16 bit mean sub version number,1~8 bit mean mend number.
        /// for example：return value 0x00030107 mean：main version number is 3,sub version number is 1,mend number is 7
        /// </returns>
        public static UInt32 NETGetSdkVersion()
        {
            return PLAY_GetSdkVersion();
        }

        /// <summary>
        /// return current player sdk`s version number as appointed format
        /// </summary>
        /// <param name="verFormatStyle">version format character string:A:main version number;B:sub version number;C:mend number;</param>
        /// <returns>version number of player`s SDK</returns>
        public static string NETGetSdkVersion(string verFormatStyle)
        {
            UInt32 sdkVer = NETGetSdkVersion();
            string strTemp = verFormatStyle.ToUpper();
            //count version number
            int AA = (int)sdkVer >> 16;//main version number:high 16 bit
            int BB = (int)(sdkVer >> 8)&0x0000FF;//sub version number:9~16 bit
            int CC = (int)sdkVer & 0x000000FF;//mend number:1~8 bit 
            strTemp = strTemp.Replace("A", AA.ToString()).Replace("B", BB.ToString()).Replace("C",CC.ToString());
            return strTemp;
        }

        #endregion

        #region << setup attribute >>

        /// <summary>
        /// setup the mode of frame play.Must setup before play
        /// </summary>
        /// <param name="nPort">player channel number</param>
        /// <param name="nMode">play mode</param>
        /// <returns>true:succeed;false:failed</returns>
        public static bool NETSetStreamOpenMode(int nPort, PLAY_MODE nMode)
        {
            bool returnValue = false;
            returnValue = PLAY_SetStreamOpenMode(nPort, (uint)nMode);
            NETThrowLastError(nPort);
            return returnValue;
        }

        #endregion

        #endregion

        #endregion

        #region << public function >>

        /// <summary>
        /// make a integer to appointed time format
        /// </summary>
        /// <param name="uintValue">time value/param>
        /// <param name="rate">through rate between second,for example:when time format is second,through rate is 1;if time value is millisecond ,through rate is0.001;when time value`s unit is cent,
        /// through rate is60,if there is no time format character ,this value is invalid</param>
        /// <param name="timeStyle">time format character string,for example:HH:mm:ss,refer to DateTime.Format character string defining</param>
        /// <returns>The time expression of character string with defined form </returns>
        public static string NETConvertToTime(uint  uintValue,decimal rate,string timeStyle)
        {
            uint uintSec=Convert.ToUInt32( uintValue*rate);
            int d=(int)(uintSec/87840);
            int h = (int)((uintSec - d * 87840) / 3600);
            int m = (int)((uintSec - d * 87840 - h * 3600) / 60);
            int s = (int)(uintSec - d * 87840 - h * 3600 - m * 60);
            string DD=(d>=10?d.ToString():"0"+d.ToString());
            string HH = (h>=10?h.ToString():"0"+h.ToString());
            string mm = (m >= 10 ? m.ToString() : "0" + m.ToString());
            string ss = (s >= 10 ? s.ToString() : "0" + s.ToString());
            string strTemp = timeStyle.ToUpper();
            strTemp = strTemp.Replace("DD", DD).Replace("HH", HH).Replace("MM",mm).Replace("SS",ss).Replace("D",d.ToString()).Replace("H",h.ToString()).Replace("M",m.ToString()).Replace("S",s.ToString());
            if (timeStyle.Length == 0)//the condition without input time form
            {
                strTemp = uintValue.ToString();
            }
            return strTemp;
        }
        #region << shield code >>

        ///// <summary>
        ///// change a integer value change to definded time form
        ///// </summary>
        ///// <param name="uintValue">time value</param>
        ///// <param name="rate">the advanced rate with second ,for example:time value's unit is millisecond,then the advanced rate is 0.001;time value's unit is minute,then the advanced rate is 60</param>
        ///// <returns>DateTime form time</returns>
        //public static DateTime DHConvertToTime(uint uintValue, decimal rate)
        //{
        //    return new DateTime((long)(uintValue * 10 * rate), DateTimeKind.Local);
        //}

        #endregion 

        #endregion

        #region << original SDK port invoke >>

        #region << play the  file >>

        /// <summary>
        /// open the file
        /// </summary>
        /// <param name="nPort">play the channel number</param>
        /// <param name="sFileName">file name</param>
        /// <returns>true:succeed ;false:failed</returns>
        [DllImport("dhplay.dll")]
        private static extern bool PLAY_OpenFile(int nPort, string sFileName);

        /// <summary>
        /// Start play.If it has played ,change the current play condition to normal speed to play
        /// </summary>
        /// <param name="nPort">play channel number</param>
        /// <param name="hWnd">play window's sentence handel</param>
        /// <returns>true:succeed;false:failed</returns>
        [DllImport("dhplay.dll")]
        private static extern bool PLAY_Play(int nPort, IntPtr hWnd);

        /// <summary>
        /// stop play
        /// </summary>
        /// <param name="nPort">play channel number</param>
        /// <returns>true:succeed;false:failed</returns>
        [DllImport("dhplay.dll")]
        private static extern bool PLAY_Stop(int nPort);

        /// <summary>
        /// close the played file
        /// </summary>
        /// <param name="nPort">play channel number</param>
        /// <returns>true:succeed;false:failed</returns>
        [DllImport("dhplay.dll")]
        private static extern bool PLAY_CloseFile(int nPort);

        #endregion

        #region << fix the position of file >>

        /// <summary>
        /// set the current playing position to defined frame number；fix the playing position based on the frame number.This function must be invoke after the file index generate.
        /// </summary>
        /// <param name="nPort">play channel number</param>
        /// <param name="nFrameNum">frame number</param>
        /// <returns>true:succeed;false:failed</returns>
        [DllImport("dhplay.dll")]
        private static extern bool PLAY_SetCurrentFrameNum(int nPort, UInt32 nFrameNum);

        /// <summary>
        /// set the file playing position based on the time ,this port use more time than PLAY_SetPlayPos,but if control the schedule bar rely on time（use with PLAY_GetPlayedTime(Ex)）,the schedule bar can move smoothly
        /// </summary>
        /// <param name="nPort">player's channel number</param>
        /// <param name="nTime">set file's playing position to defined time.Unit is millisecond</param>
        /// <returns>true:succeed;false:failed</returns>
        [DllImport("dhplay.dll")]
        private static extern bool PLAY_SetPlayedTimeEx(int nPort, UInt32 nTime);

        /// <summary>
        /// set the relative position of file's playing indicator（percentage）
        /// </summary>
        /// <param name="nPort">play channel number</param>
        /// <param name="fRelativePos">range 0-100%</param>
        /// <returns>true:succeed;false:failed</returns>
        [DllImport("dhplay.dll")]
        private static extern bool PLAY_SetPlayPos(int nPort, float fRelativePos);

        /// <summary>
        /// get the relative position of file's playing index
        /// </summary>
        /// <param name="nPort">player's channel number</param>
        /// <returns>range 0-100%</returns>
        [DllImport("dhplay.dll")]
        private static extern float PLAY_GetPlayPos(int nPort);

        #endregion

        #region << set attribute >>

        /// <summary>
        /// set picture's video parameter ,play a part immediately
        /// </summary>
        /// <param name="nPort">player's channel number</param>
        /// <param name="nRegionNum">display area,refer to PLAY_SetDisplayRegion；if there is only one display area(under normal condition),set 0</param>
        /// <param name="nBrightness">brigthness,default 64； range 0-128</param>
        /// <param name="nContrast">contrast,default64； range 0-128</param>
        /// <param name="nSaturation">saturation,default64；range 0-128</param>
        /// <param name="nHue">tone,default 64； range 0-128</param>
        /// <returns>true:succeed;false:failed</returns>
        [DllImport("dhplay.dll")]
        private static extern bool PLAY_SetColor(int nPort, UInt32 nRegionNum, int nBrightness, int nContrast, int nSaturation, int nHue);

        /// <summary>
        /// set the model of frame's playing.Must be set before playing .
        /// </summary>
        /// <param name="nPort">player's channel number</param>
        /// <param name="nMode">
        /// STREAME_REALTIME:real time model（default）
        /// STREAME_FILE:file model
        /// </param>
        /// <returns>true:succeed;false:failed</returns>
        [DllImport("dhplay.dll")]
        private static extern bool PLAY_SetStreamOpenMode(int nPort, UInt32 nMode);
        #endregion

        #region << voice band control >>

        /// <summary>
        /// open voice
        /// [only one channel voice at the same time.if there has voice opened,close the original opened voice.]
        /// **Notice：default voice is closed**
        /// </summary>
        /// <param name="nPort">player's channel number</param>
        /// <returns>true:succeed;false:failed</returns>
        [DllImport("dhplay.dll")]
        private static extern bool PLAY_PlaySound(int nPort);

        /// <summary>
        /// close voice
        /// </summary>
        /// <returns>true:succeed;false:failed</returns>
        [DllImport("dhplay.dll")]
        private static extern bool PLAY_StopSound();

        /// <summary>
        /// play the voice in the sharing way,play this channel's voice but not shut up other channel's voice
        /// </summary>
        /// <param name="nPort">player's channel number</param>
        /// <returns>true:succeed;false:failed</returns>
        [DllImport("dhplay.dll")]
        private static extern bool PLAY_PlaySoundShare(int nPort);

        /// <summary>
        /// Close the voice in the sharing way.PLAY_PlaySound和PLAY_StopSound is play the voice in monopolize way.
        /// **Notice：in the same process,every channel must play or close the voice in the same way**
        /// </summary>
        /// <param name="nPort">play the channel number</param>
        /// <returns>true:succeed;false:failed</returns>
        [DllImport("dhplay.dll")]
        private static extern bool PLAY_StopSoundShare(int nPort);

        /// <summary>
        /// set volume
        /// </summary>
        /// <param name="nPort">player's channel number</param>
        /// <param name="nVolume">volume,range 0-0XFFFF</param>
        /// <returns>true:succeed;false:failed</returns>
        [DllImport("dhplay.dll")]
        private static extern bool PLAY_SetVolume(int nPort, UInt32 nVolume);

        /// <summary>
        /// get the voice of present set
        /// </summary>
        /// <param name="nPort">player's channel number</param>
        /// <returns>true:succeed;false:failed</returns>
        [DllImport("dhplay.dll")]
        private static extern UInt32 PLAY_GetVolume(int nPort);

        /// <summary>
        /// change WAVE wave form,and can change the volume.the difference between it and PLAY_SetVolume is that it just change the voice data
        /// just affect this channel,but PLAY_SetVolume change the volume of sound card,affect the total system.this function has not come true.
        /// </summary>
        /// <param name="nPort">player's channel number</param>
        /// <param name="nCoefficient">adjusted parameter,range is from MIN_WAVE_COEF to MAX_WAVE_COEF,0 is not adjust</param>
        /// <returns>true:succeed;false:failed</returns>
        [DllImport("dhplay.dll")]
        private static extern bool PLAY_AdjustWaveAudio(int nPort, int nCoefficient);

        #endregion

        #region << play stream data >>

        /// <summary>
        /// open stream port（like open file）
        /// </summary>
        /// <param name="nPort">player's channel number</param>
        /// <param name="pFileHeadBuf">not use present,fill IntPtr.Zero</param>
        /// <param name="nSize">not use present,fill 0</param>
        /// <param name="nBufPoolSize">
        /// set the buffer's size of storage data frame in player 
        /// range is DATABUF_SIZE.SOURCE_BUF_MIN~ DATABUF_SIZE.SOURCE_BUF_MAX
        /// set 900*1024 ordinary,if the data is realatively unique when sending,this value can be changed smaller,if not unique,can change big
        /// </param>
        /// <returns>true:succeed;false:failed</returns>
        [DllImport("dhplay.dll")]
        private static extern bool PLAY_OpenStream(int nPort, IntPtr pFileHeadBuf, UInt32 nSize, UInt32 nBufPoolSize);

        /// <summary>
        /// input the data frame read from the card；only after open stream and invoke PLAY_Play,data can be input
        /// </summary>
        /// <param name="nPort"> channel number</param>
        /// <param name="pBuf">buffer's address</param>
        /// <param name="nSize">buffer's size</param>
        /// <returns>true:succeed;false:failed</returns>
        [DllImport("dhplay.dll")]
        private static extern bool PLAY_InputData(int nPort, IntPtr pBuf, UInt32 nSize);

        /// <summary>
        /// close data stream（like close file）
        /// </summary>
        /// <param name="nPort">channel number</param>
        /// <returns>true:succeed;false:failed</returns>
        [DllImport("dhplay.dll")]
        private static extern bool PLAY_CloseStream(int nPort);

        /// <summary>
        /// open the stream in the way that audio and video is apart 
        /// </summary>
        /// <param name="nPort">channel number</param>
        /// <param name="pFileHeadBuf">the data of file head that user get from the card</param>
        /// <param name="nSize">file head 's length</param>
        /// <param name="nBufPoolSize">set the buffer's size of storage data frame in player .range is SOURCE_BUF_MIN~ SOURCE_BUF_MAX</param>
        /// <returns>true:succeed;false:failed</returns>
        [DllImport("dhplay.dll")]
        private static extern bool PLAY_OpenStreamEx(int nPort, IntPtr pFileHeadBuf, UInt32 nSize, UInt32 nBufPoolSize);

        /// <summary>
        /// input the video stream get from the card (it can be complex stream ,but audio data will be ignored)；
        /// data can be input after open stream
        /// </summary>
        /// <param name="nPort">channel number</param>
        /// <param name="pBuf">buffer's address</param>
        /// <param name="nSize">buffer's size</param>
        /// <returns>true:succeed;false:failed</returns>
        [DllImport("dhplay.dll")]
        private static extern bool PLAY_InputVideoData(int nPort, IntPtr pBuf, UInt32 nSize);

        /// <summary>
        /// input the video stream get from the card；data can be input after voice is opened
        /// </summary>
        /// <param name="nPort">channel number</param>
        /// <param name="pBuf">buffer's address</param>
        /// <param name="nSize">buffer's size</param>
        /// <returns>true:succeed;false:failed</returns>
        [DllImport("dhplay.dll")]
        private static extern bool PLAY_InputAudioData(int nPort, IntPtr pBuf, UInt32 nSize);

        /// <summary>
        /// close data stream
        /// </summary>
        /// <param name="nPort">channel number</param>
        /// <returns>true:succeed;false:failed</returns>
        [DllImport("dhplay.dll")]
        private static extern bool PLAY_CloseStreamEx(int nPort);

        /// <summary>
        /// open secret port
        /// </summary>
        /// <param name="nPort"></param>
        /// <param name="?"></param>
        /// <returns></returns>
        [DllImport("dhplay.dll")]
        private static extern bool PLAY_SetSecurityKey(int nPort, IntPtr szKey, UInt32 nKeylen);

        /// <summary>
        /// clearn play buffer
        /// </summary>
        /// <param name="nPort">player's channel number</param>
        /// <param name="nBufType">choose which type of buffer to clearn</param>
        /// <returns>true:succeed;false:failed</returns>
        [DllImport("dhplay.dll")]
        private static extern bool PLAY_ResetBuffer(int nPort, UInt32 nBufType);

        #endregion

        #region << playback control >>

        /// <summary>
        /// channel's number
        /// </summary>
        /// <param name="nPort">player's channel number</param>
        /// <param name="nPause">1:suspend;0:recover</param>
        /// <returns>true:succeed;false:failed</returns>
        [DllImport("dhplay.dll")]
        private static extern bool PLAY_Pause(int nPort, UInt32 nPause);

        /// <summary>
        /// rapid play.playing speed is divide into 9 grade,playing speed is 
        /// 1,3,6,12,25,50,75,100,125 frames pictures every second respectively.every time call playing speed promote one grade 
        /// can be call 4 time most,if want to recovery normal playing,call PLAY_Play,start normal playing from current position
        /// </summary>
        /// <param name="nPort">player's channel number</param>
        /// <returns>true:succeed;false:failed</returns>
        [DllImport("dhplay.dll")]
        private static extern bool PLAY_Fast(int nPort);

        /// <summary>
        /// low speeding play,idem.every time call playing speed fall one grade ;call 4 times most,if want recover normal play ,callPLAY_Play
        /// </summary>
        /// <param name="nPort">player's channel number</param>
        /// <returns>true:succeed;false:failed</returns>
        [DllImport("dhplay.dll")]
        private static extern bool PLAY_Slow(int nPort);

        /// <summary>
        /// one frame play.if want to recover normal play ,transfer PLAY_ Play
        /// </summary>
        /// <param name="nPort">player's channel number</param>
        /// <returns>true:succeed;false:failed</returns>
        [DllImport("dhplay.dll")]
        private static extern bool PLAY_OneByOne(int nPort);

        /// <summary>
        /// one frame playback.reverse one frame in every call.this function only can be revoked after file index generated
        /// </summary>
        /// <param name="nPort">player's channel number</param>
        /// <returns>true:succeed;false:failed</returns>
        [DllImport("dhplay.dll")]
        private static extern bool PLAY_OneByOneBack(int nPort);

        #endregion

        #region << get error number >>

        /// <summary>
        /// get present error's error code.User should revoke this function to get the detail of error after revoke one function is failed.
        /// </summary>
        /// <param name="nPort">player's channel number</param>
        /// <returns>true:succeed;false:failed</returns>
        [DllImport("dhplay.dll")]
        private static extern UInt32 PLAY_GetLastError(int nPort);

        #endregion

        #region << data return >>

        /// <summary>
        /// set revoke function,replace player's display part,user control display himsself,this function is revoked before PLAY_Play,
        /// lose effectiveness automatic when PLAY_Stop,it need to be set again before next time revoke PLAY_Play.
        /// decoded part not control the speed,only return from the revoke function by user,decoder will decode next part's data.
        /// 【Notice】This function's usage need users should have enough understanding of video's display and audio's play.
        /// </summary>
        /// <param name="nPort">player's channel number</param>
        /// <param name="cbFun">revoke function index</param>
        /// <returns>true:succeed;false:failed</returns>
        [DllImport("dhplay.dll")]
        private static extern bool PLAY_SetDecCallBack(int nPort,ref DecCBFun cbFun);

        /// <summary>
        /// set decode revoke frame's form
        /// </summary>
        /// <param name="nPort">player's channel number</param>
        /// <param name="nStream">
        /// 1:video stream;
        /// 2:audio stream;
        /// 3:complex stream;
        /// </param>
        /// <returns>true:succeed;false:failed</returns>
        [DllImport("dhplay.dll")]
        private static extern bool PLAY_SetDecCBStream(int nPort, UInt32 nStream);

        /// <summary>
        /// set video picture data's revoke,can be used to catch picture.if want to stop revoke ,can set revoke index DisplayCBFun to NULL.Once set revoke function,it will effective always until the process is exit.this function can be revoke at anytime.
        /// </summary>
        /// <param name="nPort">player's channel number</param>
        /// <param name="dCBFun">revoke function</param>
        /// <param name="nUser">user's self-defineded data</param>
        /// <returns>true:succeed;false:failed</returns>
        [DllImport("dhplay.dll")]
        private static extern bool PLAY_SetDisplayCallBack(int nPort, DisplayCBFun dCBFun, int nUser);

        /// <summary>
        /// wave data revoke of audio's frame after decode
        /// </summary>
        /// <param name="nPort">player's channel number</param>
        /// <param name="funAudio">audio revoke function</param>
        /// <param name="nUser">user's self-defineded data</param>
        /// <returns>true:succeed;false:failed</returns>
        [DllImport("dhplay.dll")]
        private static extern bool PLAY_SetAudioCallBack(int nPort, FunAudio funAudio, int nUser);
                
        #endregion

        #region << many areas display >>
        /// <summary>
        /// set or add displaying area.can amplifly display of some apart.
        /// </summary>
        /// <param name="nPort">player's channel number</param>
        /// <param name="nRegionNum">show area's serial number,0~(MAX_DISPLAY_WND-1).if nRegionNum is 0,it means in main display window</param>
        /// <param name="pSrcRect">part display area</param>
        /// <param name="hDestWnd">show window sentence handel</param>
        /// <param name="bEnable">open(set)or close display </param>
        /// <returns>true:succeed;false:failed</returns>
        [DllImport("dhplay.dll")]
        private static extern bool PLAY_SetDisplayRegion(int nPort, UInt32 nRegionNum,IntPtr pSrcRect, IntPtr hDestWnd, bool bEnable);
        //original C++ style API definition：BOOL PLAY_SetDisplayRegion(LONG nPort,DWORD nRegionNum, RECT *pSrcRect, HWND hDestWnd, BOOL bEnable)

        /// <summary>
        /// refresh display,refresh many areas display's windows
        /// </summary>
        /// <param name="nPort">player's channel number</param>
        /// <param name="nRegionNum">show areas's serial number</param>
        /// <returns>true:succeed;false:failed</returns>
        [DllImport("dhplay.dll")]
        private static extern bool PLAY_RefreshPlayEx(int nPort, UInt32 nRegionNum);
        //original C++ style API definition：BOOL PLAY_RefreshPlayEx(LONG nPort,DWORD nRegionNum)
        #endregion

        #region << get attribute >>

        /// <summary>
        /// get present playing frame serial number.but PLAY_GetPlayedFrames is total decode's frame.
        /// if the file playing position is not changed,then this two function's return value should be very adjacent,unless code stream is lost.
        /// </summary>
        /// <param name="nPort">player's channel number</param>
        /// <returns>play current frame serial number</returns>
        [DllImport("dhplay.dll")]
        private static extern UInt32 PLAY_GetCurrentFrameNum(int nPort);

        /// <summary>
        /// get the file's total time length,unit is second
        /// </summary>
        /// <param name="nPort">player's channel number</param>
        /// <returns>ile's total time length</returns>
        [DllImport("dhplay.dll")]
        private static extern UInt32 PLAY_GetFileTime(int nPort);

        /// <summary>
        /// test some system function which player need.
        /// </summary>
        /// <returns>attribute value,get 1~9 bit by bit ,which expess the meaning below（bit and TRUE mean support）：
        /// SUPPORT_DDRAW		   	support DIRECTDRAW；if not support ,player can not work.
        /// SUPPORT_BLT			  VGA Card support BLT operation；if not support ,player can not work. 
        /// SUPPORT_BLTFOURCC		VGA Card BLT support color conversion；if not support ,player will use software way to make RGB conversion.
        /// SUPPORT_BLTSHRINKX      VGA Card BLT support X axle shrink；if not support ,player will use software way to make RGB conversion. 
        /// SUPPORT_BLTSHRINKY      VGA Card BLT support Y axle shrink；if not support ,player will use software way to make RGB conversion. 
        /// SUPPORT_BLTSTRETCHX	    VGA Card BLT support X axle magnify；if not support ,player will use software way to make RGB conversion. 
        /// SUPPORT_BLTSTRETCHY	    VGA Card BLT support Y axle magnify；if not support ,player will use software way to make RGB conversion.
        /// SUPPORT_SSE CPU		    support SSE order,above Intel Pentium3 support SSE order. 
        /// SUPPORT_MMX CPU		    support MMX order set.
        /// </returns>
        [DllImport("dhplay.dll")]
        private static extern Int16 PLAY_GetCaps();

        /// <summary>
        /// get relevant color value
        /// </summary>
        /// <param name="nPort">player's channel number</param>
        /// <param name="nRegionNum">display area,refer to PLAY_SetDisplayRegion；if there is only one display area(generally)set 0</param>
        /// <param name="pBrightness">brightness</param>
        /// <param name="pContrast">contrast</param>
        /// <param name="pSaturation">saturation</param>
        /// <param name="pHue">tone</param>
        /// <returns>true:succeed;false:failed</returns>
        [DllImport("dhplay.dll")]
        private static extern bool PLAY_GetColor(int nPort, UInt32 nRegionNum, ref int pBrightness, ref int pContrast, ref int pSaturation, ref int pHue);

        /// <summary>
        /// get the frame rate when coding in current frame stream 
        /// </summary>
        /// <param name="nPort">player's channel number</param>
        /// <returns>frame rate value of current when decoding in curent frame stream</returns>
        [DllImport("dhplay.dll")]
        private static extern UInt32 PLAY_GetCurrentFrameRate(int nPort);

        /// <summary>
        /// get the total frame number in the file 
        /// </summary>
        /// <param name="nPort">player's channel number</param>
        /// <returns>the total frame number </returns>
        [DllImport("dhplay.dll")]
        private static extern UInt32 PLAY_GetFileTotalFrames(int nPort);

        /// <summary>
        /// get the file's current playing time ,unit is second
        /// </summary>
        /// <param name="nPort">player's channel number</param>
        /// <returns>file's current playing time</returns>
        [DllImport("dhplay.dll")]
        private static extern UInt32 PLAY_GetPlayedTime(int nPort);

        /// <summary>
        /// get the file's current playing time ,unit is millisecond
        /// </summary>
        /// <param name="nPort">player's channel number</param>
        /// <returns>file's current playing time</returns>
        [DllImport("dhplay.dll")]
        private static extern UInt32 PLAY_GetPlayedTimeEx(int nPort);

        /// <summary>
        /// get the original picture's size in the code stream,set the window's area by this size,can not use VGA Card to do scaling,
        /// it is very useful to those VGA Card that not support hardware zoom
        /// </summary>
        /// <param name="nPort">player's channel number</param>
        /// <param name="pWidth">original image's wide.in PAL and CIF format is 352</param>
        /// <param name="pHeight">original image's tall.in PAL and CIFformat is 288</param>
        /// <returns>true:succeed;false:failed</returns>
        [DllImport("dhplay.dll")]
        private static extern bool PLAY_GetPictureSize(int nPort, ref int pWidth, ref int pHeight);

        /// <summary>
        /// query play info
        /// </summary>
        /// <param name="nPort">player's channel number</param>
        /// <param name="nType">query type</param>
        /// <param name="pBuf">query buffer</param>
        /// <param name="nBufLen">the lenth of query buffer</param>
        /// <param name="pRetLen">availible buffer</param>
        /// <returns>true:succeed;false:failed</returns>
        [DllImport("dhplay.dll")]
        private static extern bool PLAY_QueryInfo(int nPort, int nType, IntPtr pBuf, int nBufLen, ref int pRetLen);

        #endregion

        #region << get vision number >>
        /// <summary>
        /// get current player sdk's main version number、sub version number and patch number
        /// </summary>
        /// <returns>
        /// high is 16 bit means current main version number.
        /// 9~16bit mean sub version number,1~8 bit means patch number.
        /// for example：returned value 0x00030107 means：main version number is 3,sub version number is 1,patch number is 7</returns>
        [DllImport("dhplay.dll")]
        private static extern UInt32 PLAY_GetSdkVersion();

        #endregion

        #region << catch picture >>

        /// <summary>
        /// save the picture data getting from catching picture to BMP file.changeing function occupy cpu resource,if not need to save picture,it needn't invoke.
        /// </summary>
        /// <param name="pBuf">like the parameter in catching invoke function</param>
        /// <param name="nSize">like the parameter in catching invoke function</param>
        /// <param name="nWidth">like the parameter in catching invoke function</param>
        /// <param name="nHeight">like the parameter in catching invoke function</param>
        /// <param name="nType">like the parameter in catching invoke function</param>
        /// <param name="sFileName">the file name which need to save.sever BMP as filename extension is better</param>
        /// <returns>true:succeed;false:failed</returns>
        [DllImport("dhplay.dll")]
        private static extern bool PLAY_ConvertToBmpFile(ref string pBuf, int nSize, int nWidth, int nHeight, int nType,ref string  sFileName);

        /// <summary>
        /// screenshot
        /// </summary>
        /// <param name="nPort">player's channel number</param>
        /// <param name="sFileName">file name</param>
        /// <returns>true:succeed;false:failed</returns>
        [DllImport("dhplay.dll")]
        private static extern bool PLAY_CatchPic(int nPort, string sFileName);

        #endregion

        #region << data stream video >>
        
        /// <summary>
        /// begining stream's data video.just useful to stream pattern,invoke after PLAY_Play.
        /// </summary>
        /// <param name="nPort">player's channel number</param>
        /// <param name="sFileName">video file name,if there is not existing file in file name,creat this file</param>
        /// <param name="idataType">0:original code stream;1:AVI</param>
        /// <returns>true:succeed;false:failed</returns>
        [DllImport("dhplay.dll")]
        private static extern bool PLAY_StartDataRecord(int nPort,string sFileName,int idataType);

        /// <summary>
        /// stop stream data's video
        /// </summary>
        /// <param name="nPort">player's channel number</param>
        /// <returns>true:succeed;false:failed</returns>
        [DllImport("dhplay.dll")]
        private static extern bool PLAY_StopDataRecord(int nPort);

        /// <summary>
        /// Get Free channel
        /// </summary>
        /// <param name="nPort">player's channel number ptr</param>
        /// <returns>true:succeed;false:failed</returns>
        [DllImport ("dhplay.dll")]
        private static extern  bool PLAY_GetFreePort(IntPtr pnPort);

        /// <summary>
        /// Release channel
        /// </summary>
        /// <param name="nPort">player's channel number</param>
        /// <returns>true:succeed;false:failed</returns>
        [DllImport ("dhplay.dll")]
        private static extern  bool PLAY_ReleasePort(int nPort);

        /// <summary>
        /// set play direction
        /// </summary>
        /// <param name="nPort">player's channel number</param>
        /// <param name="emDirection">0:forward;1:backward</param>
        /// <returns>true:succeed;false:failed</returns>
        [DllImport("dhplay.dll")]
        private static extern bool PLAY_SetPlayDirection(int nPort, UInt32 emDirection);
        #endregion

        #region << character superimposition >>

        /// <summary>
        /// character superimposition
        /// </summary>
        /// <param name="nPort">player's channel number</param>
        /// <param name="privateDrawFun">callback function handle</param>
        /// <param name="nUser">user data</param>
        /// <returns>true:succeed;false:failed</returns>
        [DllImport("dhplay.dll")]
        private static extern bool PLAY_RigisterDrawFun(int nPort, DrawFun privateDrawFun, int nUser);

        #endregion

        #endregion
    }

    #region << entrust >>

    /// <summary>
    /// character superimposition callback function
    /// </summary>
    /// <param name="nPort">channel number</param>
    /// <param name="hDc">OffScreen surface set context,you can do like operate displaying windows cilent area DC</param>
    /// <param name="nUser">cilent's data</param>
    public delegate void DrawFun(int nPort,IntPtr hDc,int nUser);

    /// <summary>
    /// player's data invoke
    /// </summary>
    /// <param name="nPort">player's channel number</param>
    /// <param name="pBuf">audio and video data after decode</param>
    /// <param name="nSize">the length of audio and video data pBuf after decode</param>
    /// <param name="pFrameInfo">picture and voice's frame information</param>
    /// <param name="nReserved1">retention parameter</param>
    /// <param name="nReserved2">retention parameter</param>
    public delegate void DecCBFun(int nPort, ref String pBuf, int nSize,ref  FRAME_INFO pFrameInfo, int nReserved1, int nReserved2);

    /// <summary>
    /// 
    /// </summary>
    /// <param name="nPort">player's channel number</param>
    /// <param name="nUser">cilent's data</param>
    public delegate void pFileRefDone (UInt32 nPort,IntPtr nUser);

    /// <summary>
    /// 
    /// </summary>
    /// <param name="nPort">player's channel number</param>
    /// <param name="nUser">cilent's data</param>
    public delegate void funEncChange (int nPort, int nUser);

    /// <summary>
    /// set invoking function entrust of video picture data
    /// </summary>
    /// <param name="nPort">player's channel number</param>
    /// <param name="pBuf">return picture data</param>
    /// <param name="nSize">return picture data's size</param>
    /// <param name="nWidth">picture wide,unit pixel</param>
    /// <param name="nHeight">picture tall</param>
    /// <param name="nStamp">time sign information,unit millisecond</param>
    /// <param name="nType">data type, T_RGB32,T_UYVY,detail is in decoding invoke video frame type instruction.</param>
    /// <param name="nReceaved">reserve</param>
    public delegate void DisplayCBFun ( int  nPort,String pBuf,int nSize,int nWidth,int nHeight,int nStamp,int nType,int nReceaved);

    /// <summary>
    /// wave data's invoking entrust of audio frame after decode
    /// </summary>
    /// <param name="nPort">player's channel number</param>
    /// <param name="pAudioBuf">form audio data</param>
    /// <param name="nSize">audio data length</param>
    /// <param name="nStamp">time mark(ms)</param>
    /// <param name="nType">audio typeT_AUDIO16, sampling rate8000,one track,every sampling point 16 bits mean</param>
    /// <param name="nUser">user self defined data</param>
    public delegate void FunAudio(int nPort,String pAudioBuf, int nSize, int nStamp, int nType, int nUser);

    #endregion

    #region << structure definition >>

    /// <summary>
    /// frame position
    /// </summary>
    public struct FRAME_POS
    {
        /// <summary>
        /// pointed frame's skewing position in file
        /// </summary>
        public int nFilePos;
        /// <summary>
        /// frame serial number
        /// </summary> 
        public int nFrameNum;
        /// <summary>
        /// frame time
        /// </summary>
        public int nFrameTime;
        /// <summary>
        /// wrong frame number
        /// </summary>
        public SYSTEM_TIME nErrorFrameNum;
        /// <summary>
        /// wrong frame time
        /// </summary>
        public int pErrorTime;
        /// <summary>
        /// wrong frame number
        /// </summary>
        public int nErrorLostFrameNum;
        /// <summary>
        /// wrong frame size
        /// </summary>
        public int nErrorFrameSize;
    }

    /// <summary>
    /// system's time form(C++)
    /// </summary>
    public struct SYSTEM_TIME
    {
        /// <summary>
        /// year
        /// </summary>
        public UInt16 wYear;
        /// <summary>
        /// mouth
        /// </summary>
        public UInt16 wMonth;
        /// <summary>
        /// week
        /// </summary>
        public UInt16 wDayOfWeek;
        /// <summary>
        /// day
        /// </summary>
        public UInt16 wDay;
        /// <summary>
        /// hour
        /// </summary>
        public UInt16 wHour;
        /// <summary>
        /// minute
        /// </summary>
        public UInt16 wMinute;
        /// <summary>
        /// second
        /// </summary>
        public UInt16 wSecond;
        /// <summary>
        /// millisecond
        /// </summary>
        public UInt16 wMilliseconds;
    }

    /// <summary>
    /// custom color's construction
    /// </summary>
    public struct COLOR_STRUCT
    {
        /// <summary>
        /// brightness[range:0-128]
        /// </summary>
        public int pBrightness;
        /// <summary>
        /// contrast[range:0-128]
        /// </summary>
        public int pContrast;
        /// <summary>
        /// saturation[range:0-128]
        /// </summary>
        public int pSaturation;
        /// <summary>
        /// tone[range:0-128]
        /// </summary>
        public int pHue;
 
    }

    /// <summary>
    /// frame information
    /// </summary>
    public struct FRAME_INFO
    {
        /// <summary>
        /// frame width,unit is pixel.if it is audio data ,the result is 0
        /// </summary>
        public int nWidth;
        /// <summary>
        /// frame height.if it is audio data ,the result is 0
        /// </summary>
        public int nHeight;
        /// <summary>
        /// time mark information,unit is millisecond
        /// </summary>
        public int nStamp;
        /// <summary>
        /// data type,T_AUDIO16,T_RGB32, T_YV12,detail is in macro fefinition instruction.
        /// </summary>
        public int nType;
        /// <summary>
        /// picture's frame rate generated in decoding
        /// </summary>
        public int nFrameRate;
    }

    /// <summary>
    /// frame type
    /// </summary>
    public struct FRAME_TYPE
    {
        /// <summary>
        /// frame data
        /// </summary>
        public string pDataBuf;
        /// <summary>
        /// frame size
        /// </summary>
        public int nSize;
        /// <summary>
        /// frame serial number
        /// </summary>
        public int nFrameNum;
        /// <summary>
        /// audio frame or not(TRUE:1;FALSE:0)
        /// </summary>
        public Int16 bIsAudio;
        /// <summary>
        /// reserved word
        /// </summary>
        public int nReserved;
    }

    /// <summary>
    /// datetime type
    /// </summary>
    public struct DATETIME_INFO
    {
        /// <summary>
        /// nYear
        /// </summary>
        public uint nYear;
        /// <summary>
        /// nMonth
        /// </summary>
        public uint nMonth;
        /// <summary>
        /// <summary>
        /// nDay
        /// </summary>
        public uint nDay;
        /// <summary>
        /// nHour
        /// </summary>
        public uint nHour;
        /// <summary>
        /// nDay
        /// </summary>
        public uint nMinute;
        /// <summary>
        /// nHour
        /// </summary>
        public uint nSecond;
    }

    /// <summary>
    /// wrong content
    /// </summary>
    public struct OPERATION_INFO
    {
        /// <summary>
        /// wrong code
        /// </summary>
        public string errCode;
        /// <summary>
        /// wrong description
        /// </summary>
        public string errMessage;
        /// <summary>
        /// return wrong content character string base self-defined form
        /// </summary>
        /// <param name="FormatStyle">wrong content character string form：errcode replace wrong code;errmsg replace wrong description</param>
        /// <returns>self-defined form's wrong content character string</returns>
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

    ///// <summary>
    ///// frame's original picture size
    ///// </summary>
    //public struct FRAME_SIZE
    //{
    //    /// <summary>
    //    /// frame's original picture size:width
    //    /// </summary>
    //    public int Width;
    //    /// <summary>
    //    /// frame's original picture size:height
    //    /// </summary>
    //    public int Height;
        
    //}


    #endregion

    #region << enum definition >>

    /// <summary>
    /// decoding invoking stream type
    /// </summary>
    public enum STREAM_TYPE
    { 
        /// <summary>
        /// decoding invoking stream :no
        /// </summary>
        STREAM_WITHOUT,
        /// <summary>
        /// decoding invoking stream:audio
        /// </summary>
        STREAM_AUDIO,
        /// <summary>
        /// decoding invoking stream:video
        /// </summary>
        STREAM_VIDEO,
        /// <summary>
        /// decoding invoking stream:mix
        /// </summary>
        STREAM_MIX
    }

    /// <summary>
    /// play control order
    /// </summary>
    public enum PLAY_COMMAND
    {
        /// <summary>
        /// start playing
        /// </summary>
        Start,
        /// <summary>
        /// pause playing
        /// </summary>
        Pause,
        /// <summary>
        /// continue playing 
        /// </summary>
        ReSume,
        /// <summary>
        /// stop playing
        /// </summary>
        Stop,
        /// <summary>
        ///  play forward
        /// </summary>
        Forward,
        /// <summary>
        /// play backward
        /// </summary>
        Backward,
        /// <summary>
        /// open file
        /// </summary>
        OpenFile,
        /// <summary>
        /// close file
        /// </summary>
        CloseFile,
        /// <summary>

        /// rapid play.playing speed is divide into 9 grade,playing speed is 1,3,6,12,25,50,75,100,125 frames pictures every second respectively. 
        /// every time call playing speed promote one grade can be call 4 time most,if want to recovery normal playing,call PLAY_Play,start normal playing from current position
        /// </summary>
        Fast,
        /// <summary>
        /// low speeding play,idem.every time call playing speed fall one grade ;call 4 times most,if want recover normal play ,callPLAY_Play
        /// </summary>
        Slow,
        /// <summary>
        /// one frame play.if want to recover normal play ,transfer PLAY_ Play
        /// </summary>
        OneByOne,
        /// <summary>
        /// one frame playback.(reverse one frame in every call.if want to recover normal playing invokePLAY_ Play)
        /// </summary>
        OneByOneBack,
        /// <summary>
        /// screenshot
        /// </summary>
        CatchPic,
        /// <summary>
        /// get current frame serial number
        /// </summary>
        GetCurrentFrameNum,
        /// <summary>
        /// set current playing position to pointed frame number
        /// </summary>
        SetCurrentFrameNum,
        /// <summary>
        /// gain current frame rate
        /// </summary>
        GetCurrentFrameRate,
        /// <summary>
        /// gain file's total frame number 
        /// </summary>
        GetFileTotalFrames,
        /// <summary>
        /// gain file's total time length,unit is second
        /// </summary>
        GetFileTotalTime,
        /// <summary>
        /// gain file's current playing time,unit is second
        /// </summary>
        GetPlayedTime,
        /// <summary>
        /// gain file's current playing time,unit is millisecond
        /// </summary>
        GetPlayedTimeEx,
        /// <summary>
        /// set file's playing position based on the time
        /// </summary>
        SetPlayedTimeEx,
        /// <summary>
        /// get color value
        /// </summary>
        GetColor,
        /// <summary>
        /// set color property
        /// </summary>
        SetColor,
        /// <summary>
        /// play audio[only one channel voice in the same time]
        /// </summary>
        PlaySound,
        /// <summary>
        /// stop audio
        /// </summary>
        StopSound,
        /// <summary>
        /// play audio in sharing mode[play this channel's audio and not other's]
        /// </summary>
        PlaySoundShare,
        /// <summary>
        /// close audio in the sharing way
        /// </summary>
        StopSoundShare,
        /// <summary>
        /// set volume[range:0-0XFFFF(0-65535)]
        /// </summary>
        SetVolume,
        /// <summary>
        /// get current the volume's setting
        /// </summary>
        GetVolume,
        /// <summary>
        /// set WAVE form,can change audio's size[the difference between it and SetVolume is ,it change the audio's data,only work to this channel,
        /// but SetVolume is change the sound card's volume,it work to the whole system]
        /// </summary>
        AdjustWaveAudio,
        /// <summary>
        /// gain file's playing position
        /// </summary>
        GetPlayPos,
        /// <summary>
        /// set file's playing position
        /// </summary>
        SetPlayPos,
        /// <summary>
        /// gain frame original picture's size
        /// </summary>
        GetPictureSize,
        /// <summary>
        /// get datetime
        /// </summary>
        GetDateTimeInfo,
        /// <summary>
        /// set the position to the video's head
        /// </summary>
        ToBegin,
        /// <summary>
        /// set the poisition to the end of video
        /// </summary>
        ToEnd,
        /// <summary>
        /// open stream port
        /// </summary>
        OpenStream,
        /// <summary>
        /// get the stream data from the card；data can be input only after open stream and invoke PLAY_Play
        /// </summary>
        InputData,
        /// <summary>
        /// close data stream
        /// </summary>
        CloseStream,
        /// <summary>
        /// open stream in the way that audio and video is apart
        /// </summary>
        OpenStreamEx,
        /// <summary>
        /// get the stream data from the card (it can be complete stream,but audio data will be ignored)
        /// data can be input only after stream is opened
        /// </summary>
        InputVideoData,
        /// <summary>
        /// input the audio stream getting from the card;data can be input only after audio is opened
        /// </summary>
        InputAudioData,
        /// <summary>
        /// close data stream
        /// </summary>
        CloseStreamEx,
        /// <sumary>
        /// release channel
        /// </summary>
        ReleasePort ,
        /// <summary>
        /// clearn play buffer
        /// </summary>
        ResetBuffer,
    }

    /// <summary>
    /// system function
    /// </summary>
    public enum SYSFUN_TYPE
    {
        /// <summary>
        /// support DIRECTDRAW(if not support ,player can not work)
        /// </summary>
        SUPPORT_DDRAW = 1,
        /// <summary>
        /// VGA card support BLT operation(if not support ,player can not work)
        /// </summary>
        SUPPORT_BLT = 2,
        /// <summary>
        /// VGA card BLT support color conversion
        /// </summary>
        SUPPORT_BLTFOURCC = 4,
        /// <summary>
        /// VGA card BLT support X axle shrink
        /// </summary>
        SUPPORT_BLTSHRINKX = 8,
        /// <summary>
        /// VGA card BLT support Y axle shrink
        /// </summary>
        SUPPORT_BLTSHRINKY = 16,
        /// <summary>
        /// VGA card BLT support X axle magnify
        /// </summary>
        SUPPORT_BLTSTRETCHX = 32,
        /// <summary>
        /// VGA card BLT support Y axle magnify
        /// </summary>
        SUPPORT_BLTSTRETCHY = 64,
        /// <summary>
        /// CPU support SSE order,above Intel Pentium3 support SSE order
        /// </summary>
        SUPPORT_SSE = 128,
        /// <summary>
        /// CPU support MMX order set
        /// </summary>
        SUPPORT_MMX = 256
    }

    /// <summary>
    /// decode invoking video frame type
    /// </summary>
    public enum VIDEO_TYPE
    {
        T_UYVY = 1,
        T_YV12 = 3,
        T_RGB32 = 7
    }

    /// <summary>
    /// decode invoking audio frame type
    /// </summary>
    public enum AUDIO_TYPE
    {
        T_AUDIO16 = 101,
        T_AUDIO8 = 100
    }

    /// <summary>
    /// data stream playing pattern
    /// </summary>
    public enum PLAY_MODE
    {
        /// <summary>
        /// most real time way
        /// </summary>
        STREAME_REALTIME = 0,
        /// <summary>
        /// most fluent way
        /// </summary>
        STREAME_FILE = 1
    }

    /// <summary>
    /// data stream original buffer size
    /// </summary>
    public enum DATABUF_SIZE
    {
        /// <summary>
        /// max original buffer(1024*100000)
        /// </summary>
        SOURCE_BUF_MAX = 102400000,
        /// <summary>
        /// minimum original buffer(1024*50)
        /// </summary>
        SOURCE_BUF_MIN = 51200
    }

    /// <summary>
    /// location type
    /// </summary>
    public enum GOTO_TYPE
    {
        /// <summary>
        /// by frame number
        /// </summary>
        BY_FRAMENUM = 1,
        /// <summary>
        /// by time
        /// </summary>
        BY_FRAMETIME = 2
    }

    /// <summary>
    /// decode buffer frame number
    /// </summary>
    public enum BUF_FRAME_NUM
    {
        /// <summary>
        /// maximum decode buffer frame number
        /// </summary>
        MAX_DIS_FRAMES = 50,
        /// <summary>
        /// minimum decode buffer frame number
        /// </summary>
        MIN_DIS_FRAMES = 6
    }

    /// <summary>
    /// display type and maximum area display number 
    /// </summary>
    public enum DISPLAY_MODE
    {
        /// <summary>
        /// show in normal resolution ratio
        /// </summary>
        DISPLAY_NORMAL = 1,
        /// <summary>
        /// show in quarter resolution ratio以
        /// </summary>
        DISPLAY_QUARTER = 2,
        /// <summary>
        /// maximum area display number(open 4 areas display windows most in the same time)
        /// </summary>
        MAX_DISPLAY_WND = 4
    }

    /// <summary>
    /// buffer type
    /// </summary>
    public enum BUF_TYPE
    {
        /// <summary>
        /// video origin buffer
        /// </summary>
        BUF_VIDEO_SRC = 1,
        /// <summary>
        /// audio origin buffer
        /// </summary>
        BUF_AUDIO_SRC = 2,
        /// <summary>
        /// video data buffer after decode
        /// </summary>
        BUF_VIDEO_RENDER = 3,
        /// <summary>
        /// audio data buffer after decode
        /// </summary>
        BUF_AUDIO_RENDER = 4
    }

    //unfinished list：decided time type、error type、audio wave range、maximum channel number
    #endregion

    #endregion
}

