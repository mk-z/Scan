
using System;
using System.Collections.Generic;
using System.Text;
using System.Runtime.InteropServices;
using System.ComponentModel;
using System.Net;
using NetSDK;

namespace NetSDK
{
    #region << DHClientdefinition >>

    /// <summary>
	/// In the SDK development kit is in (c + + version) on the basis of the package is on the original SDK c + + interface to c # style interface development kit,
	/// In order to facilitate application development,When using this development kit release application needs to be original SDK dynamic link library files and
	/// the SDK files placed in the same directory
	/// </summary>
	
    public sealed class NETClient
    {
        private static bool initialized = false;

        /// <summary>
        /// Whether the error thrown [default not selling, only the error information returned to the attributesLastOperationInfo]
        /// </summary>
        private static bool pShowException = false;

        #region << property >>

        /// <summary>
        /// The last operation information
        /// </summary>
        private static OPERATION_INFO pErrInfo;

        /// <summary>
        /// The last operation information [the last error and successful, this property is read-only]
        /// </summary>
        public static OPERATION_INFO LastOperationInfo
        {
            get
            {
                return pErrInfo;
            }
        }

        /// <summary>
        /// Character Encoding Forms[default:gb2312 → 936]
        /// </summary>
        private static Encoding pEncoding=Encoding.GetEncoding(936);

        /// <summary>
        ///  Character Encoding Forms
        /// </summary>
        public static Encoding EncodingInfo
        {
            get
            {
                return pEncoding;
            }
            set
            {
                pEncoding = value;
            }
        }
        #endregion

        #region << class methods >>

        #region <<  private method >>

        /// <summary>
        /// SDK call fails when an exception is thrown, successful return without exception information, and the operation information is assigned toLastOperationInfo
        /// </summary>
        /// <exception cref="Win32Exception">Digital video recorders primary anomalies, trigger when SDK call fails</exception>
        private static void NETThrowLastError()
        {
            Int32 errorCode = CLIENT_GetLastError();
            if (errorCode != 0)
            {
                pErrInfo.errCode = errorCode.ToString();
                pErrInfo.errMessage = NETGetLastErrorName((uint)errorCode);
                if (pShowException == true)
                {
                    throw new Win32Exception(errorCode, pErrInfo.errMessage);
                }
            }
            else
            {
                pErrInfo.errCode = "0";
                pErrInfo.errMessage = "no exception at last";
            }
        }

        /// <summary>
        /// Error code conversion error message described as standard equipment
        /// </summary>
        /// <param name="errorCode">Error code</param>
        /// <returns>Standard equipment error message description</returns>
        private static string NETGetLastErrorName(uint errorCode)
        {
            switch (errorCode)
            {
                case 0x80000000 | 1:
                    return "Windows   SYSTEM ERROR";
                case 0x80000000 | 2:
                    return "Network error, probably because the network timeout";
                case 0x80000000 | 3:
                    return "Equipment agreement does not match";
                case 0x80000000 | 4:
                    return " Invalid handle";
                case 0x80000000 | 5:
                    return "Open the channel failure";
                case 0x80000000 | 6:
                    return "Close the channel failure";
                case 0x80000000 | 7:
                    return "The user parameter is illegal";
                case 0x80000000 | 8:
                    return "The SDK initialization error";
                case 0x80000000 | 9:
                    return "SDK clear error";
                case 0x80000000 | 10:
                    return "apply for render resource error";
                case 0x80000000 | 11:
                    return "Open the decoding error";
                case 0x800000 | 12:
                    return "close the decoding error";
                case 0x80000000 | 13:
                    return "Detected more picture preview channel number is 0";
                case 0x80000000 | 14:
                    return "The tape library initialization failed";
                case 0x80000000 | 15:
                    return "The tape library uninitialized";
                case 0x80000000 | 16:
                    return "Send audio data error";
                case 0x80000000 | 17:
                    return "Real-time data is in a state of preservation";
                case 0x80000000 | 18:
                    return "Unsaved data in real time";
                case 0x80000000 | 19:
                    return "Error Reading Form";
                case 0x80000000 | 20:
                    return "Start the yuntai timer control failure";
                case 0x80000000 | 21:
                    return "To return the data validation errors";
                case 0x80000000 | 22:
                    return "There is not enough cache";
                case 0x80000000 | 23:
                    return "The current SDK does not support this feature";
                case 0x80000000 | 24:
                    return "The query is less than the video";
                case 0x80000000 | 25:
                    return "No operation permissions";
                case 0x80000000 | 26:
                    return "Temporarily unable to perform";
                case 0x80000000 | 27:
                    return "Not found the intercom";
                case 0x80000000 | 28:
                    return "Not found the audio";
                case 0x80000000 | 29:
                    return "CLientSDK is not uninitialized.";
                case 0x80000000 | 30:
                    return "The download has finished";
                case 0x80000000 | 31:
                    return "The query result is empty";
                case 0x80000000 | 32:
                    return "Failed to get the configuration location: system properties";
                case 0x80000000 | 33:
                    return "Failed to get the configuration location: serial number";
                case 0x80000000 | 34:
                    return "Failed to get the configuration location: conventional properties";
                case 0x80000000 | 35:
                    return "Failed to get the configuration location: DSP ability to describe";
                case 0x80000000 | 36:
                    return "Failed to get the configuration location: network properties";
                case 0x80000000 | 37:
                    return "Failed to get the configuration location: channel name";
                case 0x80000000 | 38:
                    return "Failed to get the configuration location: video attributes";
                case 0x80000000 | 39:
                    return "Failed to get the configuration location: video timer configuration";
                case 0x80000000 | 40:
                    return "Failed to get the configuration location: decoder protocol name";
                case 0x80000000 | 41:
                    return "Failed to get the configuration location: 232 serial port function name";
                case 0x80000000 | 42:
                    return "Failed to get the configuration location: decoder properties";
                case 0x80000000 | 43:
                    return "Failed to get the configuration location: 232 serial port properties";
                case 0x80000000 | 44:
                    return "ake the configuration failure location: external alarm input attribute";
                case 0x80000000 | 45:
                    return "Failed to get the configuration location: image detection alarm properties";
                case 0x80000000 | 46:
                    return "Failed to get the configuration location: image detection alarm properties";
                case 0x80000000 | 47:
                    return "Failed to get the configuration location: preview parameters";
                case 0x80000000 | 48:
                    return "Failed to get the configuration location: automatic maintenance configuration";
                case 0x80000000 | 49:
                    return "Failed to get the configuration location: video matrix configuration";
                case 0x80000000 | 55:
                    return "Set configuration failure location: conventional properties";
                case 0x80000000 | 56:
                    return "Set configuration failure location: network properties";
                case 0x80000000 | 57:
                    return "Set the configuration failure location: channel name";
                case 0x80000000 | 58:
                    return "Set configuration failure location: video attributes";
                case 0x80000000 | 59:
                    return "Set configuration failure location: video timer configuration";
                case 0x80000000 | 60:
                    return "Set configuration failure location: decoder properties";
                case 0x80000000 | 61:
                    return "Set configuration failure location: 232 serial port properties";
                case 0x80000000 | 62:
                    return "Set configuration failure location: external alarm input attribute";
                case 0x80000000 | 63:
                    return "Set configuration failure location: image detection alarm properties";
                case 0x80000000 | 64:
                    return "Time set configuration failure location: equipment";
                case 0x80000000 | 65:
                    return "Set the configuration failure location: preview parameters";
                case 0x80000000 | 66:
                    return "Set the configuration failure location: automatic maintenance configuration";
                case 0x80000000 | 67:
                    return "Set the configuration failure location: video matrix configuration";
                case 0x80000000 | 70:
                    return "Audio coding interface failed initialization";
                case 0x80000000 | 71:
                    return " Data  too large";
                case 0x80000000 | 72:
                    return "The device does not support this operation";
                case 0x80000000 | 73:
                    return "Lack of equipment resources";
                case 0x80000000 | 74:
                    return "The server has been started";
                case 0x80000000 | 75:
                    return "The server has been started";
                case 0x80000000 | 80:
                    return "Enter the serial number is wrong";
                case 0x80000000 | 100:
                    return " incorreCt password";
                case 0x80000000 | 101:
                    return "There is no account";
                case 0x80000000 | 102:
                    return "Return to timeout waiting for login";
                case 0x80000000 | 103:
                    return "The account is logged in";
                case 0x80000000 | 104:
                    return "The account has been locked";
                case 0x80000000 | 105:
                    return "Account has been listed as blacklist";
                case 0x80000000 | 106:
                    return "Insufficient resources, the system is busy";
                case 0x80000000 | 107:
                    return "Connection host failed";
                case 0x80000000 | 108:
                    return "network connection is failed";
                case 0x80000000 | 120:
                    return "RenderLibrary open audio error";
                case 0x80000000 | 121:
                    return "RenderLibrary close audio error";
                case 0x80000000 | 122:
                    return "RenderLibrary control volume error";
                case 0x80000000 | 123:
                    return "RenderLibrary setting parameter error";
                case 0x80000000 | 124:
                    return "RenderLibrary pause playback error";
                case 0x80000000 | 125:
                    return "RenderThe library at wrong";
                case 0x80000000 | 126:
                    return "RenderLibraries stepping error";
                case 0x80000000 | 127:
                    return "RenderLibrary setup error frame rate";
                case 0x80000000 | 129:
                    return "RenderLibrary get current osdtime error";
                case 0x80000000 | 999:
                    return "emporarily unable to set the";
                case 0x80000000 | 1000:
                    return "The configuration data is illegal";
                default:
                    return " Unknown Error";
            }
        }

        private static void NETThrowLastError(int returnValue)
        {
            if (returnValue == 0)
            {
                NETThrowLastError();
            }
            else
            {
                pErrInfo.errCode = "0";
                pErrInfo.errMessage = "The recent operation without exception occurs";
            }
        }

        private static void NETThrowLastError(bool returnValue)
        {
            if (returnValue == false)
            {
                NETThrowLastError();
            }
            else
            {
                pErrInfo.errCode = "0";
                pErrInfo.errMessage = "The recent operation without exception occurs";
            }
        }

        /// <summary>
        /// The SDK call fails to throw an exception
        /// </summary>
        /// <param name="e"></param>
        private static void NETThrowLastError(Exception e)
        {

            pErrInfo.errCode = e.ToString();
            pErrInfo.errMessage = e.Message;
            if (pShowException == true)
            {
                throw e;
            }
        }

        #endregion

        #region <<  common access method >>

        #region << Set up the wrong way >>

        /// <summary>
        /// Set of programs that use this class will error messages thrown [default not selling, only the error information returned to the attribute LastOperationInfo]
        /// </summary>
        /// <param name="blnShowException">true:Throw an error message, and the error information returned to the attribute LastOperationInfo, processing by the customers themselves; Don't throw an error message, error messages will be returned to the propertyLastOperationInfo,Do not make any processing, users according to the method's return value or LastOperationInfo determine whether there is an error occurs, and then make corresponding processing</param>
        public static void NETSetShowException(bool blnShowException)
        {
            pShowException = blnShowException;
        }

        #endregion

        #region << character encoding >>

        /// <summary>
        ///Sets the character encoding format [defaults to: gb2312, other character encoding through this function, please set]
        /// </summary>
        /// <param name="encodingNum">A character encoding integer</param>
        public static void NETSetEncoding(int encodingNum)
        {
            pEncoding = Encoding.GetEncoding(encodingNum);
        }

        /// <summary>
        /// Equipment character encoding format (the default is: gb2312, other character encoding through this function, please set]
        /// </summary>
        /// <param name="encodingString">A character Encoding string, see MSDN  Encoding</param>
        public static void NETSetEncoding(string encodingString)
        {
            pEncoding = Encoding.GetEncoding(encodingString);
        }

        /// <summary>
        /// Equipment character encoding format (the default is: gb2312, other character encoding through this function, please set]
        /// </summary>
        /// <param name="encoding">A character ENCODING enumeration, see LANGUAGE ENCODING enumeration type</param>
        public static void NETSetEncoding(LANGUAGE_ENCODING encoding)
        {
            pEncoding =  Encoding.GetEncoding((int)encoding);
        }

        /// <summary>
        /// Equipment character encoding format (the default is: gb2312, other character encoding through this function, please set]
        /// </summary>
        /// <param name="encoding">character encoding</param>
        public static void NETSetEncoding(Encoding encoding)
        {
            pEncoding = encoding;
        }

        #endregion

        #region << The SDK and access to information >>

        /// <summary>
        /// initialization SDK
        /// </summary>
        /// <param name="cbDisConnect">
        /// Disconnect the callback function, see the entrusted:<seealso cref="fDisConnect"/>
        /// </param>
        /// <param name="dwUser">User data, there is no data, please use IntPtr. Zero</param>
        /// <returns>true:succeed;false:fail</returns>
        public static bool NETInit(fDisConnect cbDisConnect, IntPtr dwUser)
        {
            bool returnValue = false;
            if (initialized == false)
            {
                returnValue = CLIENT_Init(cbDisConnect, dwUser);
                NETThrowLastError(returnValue);
                initialized = true;
            }
            return returnValue;
        }

        /// <summary>
        /// Empty SDK, release the amount of resources, after all the SDK function calls
        /// </summary>
        public static void NETCleanup()
        {
            CLIENT_Cleanup();
            //NETThrowLastError();
        }

        /// <summary>
        /// Settings and equipment connection wait time
        /// </summary>
        /// <param name="nWaitTime">Connection wait time (unit: ms]</param>
        /// <param name="nTryTimes">connection times</param>
        public static void NETSetConnectTime(int nWaitTime, int nTryTimes)
        {
            CLIENT_SetConnectTime(nWaitTime, nTryTimes);
            //NETThrowLastError();
        }

        /// <summary>
        /// Get the SDK version number
        /// </summary>
        /// <param name="formatStyle">Format[S:00.00.00.00;D:0.0.0.0;S3:00.00.00;D3:0.0.0;X:Hexadecimal representation version number information]</param>
        /// <returns>format</returns>
        public static string NETGetSDKVersion(string formatStyle)
        {
            UInt32 returnValue = CLIENT_GetSDKVersion();
            //Convert hexadecimal values       
            string returnString = returnValue.ToString("X");
            //格式化版本号
            string strTemp = "00000000";
            strTemp = strTemp.Remove(0, returnString.Length) + returnString;
            string strVerPart1 = strTemp.Substring(0, 2);
            string strVerPart2 = strTemp.Substring(2, 2);
            string strVerPart3 = strTemp.Substring(4, 2);
            string strVerPart4 = strTemp.Substring(6, 2);
            switch (formatStyle.ToUpper())
            {
                case "S":
                    returnString = strVerPart1 + "." + strVerPart2 + "." + strVerPart3 + "." + strVerPart4;
                    break;
                case "D":
                    returnString = int.Parse(strVerPart1).ToString() + "." + int.Parse(strVerPart2).ToString() + "." + int.Parse(strVerPart3).ToString() + "." + int.Parse(strVerPart4).ToString();
                    break;
                case "S3":
                    returnString = strVerPart1 + "." + int.Parse(strVerPart2).ToString() +int.Parse(strVerPart3).ToString() + "." + strVerPart4;
                    break;
                case "D3":
                    returnString = int.Parse(strVerPart1).ToString() + "." + int.Parse(strVerPart2).ToString() + int.Parse(strVerPart3).ToString() + "." + int.Parse(strVerPart4).ToString();
                    break;
                case "X":
                    returnString = returnValue.ToString("X");
                    break;
                default:
                    returnString = strVerPart1 + "." + strVerPart2 + "." + strVerPart3;
                    break;
            }
            NETThrowLastError(int.Parse(returnValue.ToString()));
            return returnString;
        }

        /// <summary>
        /// The version of the SDK (format for S3)
        /// </summary>
        /// <returns>format</returns>
        public static string NETGetSDKVersion()
        {
            return NETGetSDKVersion("S3");
        }

        #endregion

        #region << character superimposition >>

        /// <summary>
        /// User-defined drawing, call this function before open the images, otherwise is invalid, must call before all window does not display, can be used to do character on the image stack
        /// </summary>
        /// <param name="cbDraw">Drawing the callback, said ban callback when set to 0</param>
        /// <param name="dwUser">User data, there is no data, please use IntPtr. Zero</param>
        public static void NETRigisterDrawFun(fDrawCallBack cbDraw, IntPtr dwUser)
        {   
            CLIENT_RigisterDrawFun(cbDraw,dwUser);
            //NETThrowLastError();
        }

        #endregion

        #region << parameter configuration >>

        #region << optimget >>

        /// <summary>
        ///  Access to equipment
        /// </summary>
        /// <param name="lLoginID">Equipment user Login ID: CLIENT Login return values</param>
        /// <param name="dwCommand">configuration type</param>
        /// <param name="lChannel">Channel number, if not channel parameter, lChannel need not, can be set to 1</param>
        /// <param name="lpOutBuffer">To store the output parameters of the buffer, according to the different types, the output of different configuration, see the specific data structure definition</param>
        /// <param name="dwOutBufferSize">The input buffer size (in bytes).</param>
        /// <param name="lpBytesReturned">The actual return buffer size, the size of the corresponding configuration, (in bytes)</param>
        /// <param name="waittime">waittime</param>
        /// <returns>true:succeed;false:fail</returns>
        public static bool NETGetDevConfig(int lLoginID, CONFIG_COMMAND dwCommand, int lChannel, IntPtr lpOutBuffer, UInt32 dwOutBufferSize, ref UInt32 lpBytesReturned, int waittime)
        {
            bool returnValue = false;
            returnValue = CLIENT_GetDevConfig(lLoginID, (UInt32)dwCommand, lChannel, lpOutBuffer, dwOutBufferSize, ref lpBytesReturned, waittime);
            NETThrowLastError(returnValue);
            return returnValue;
        }

        /// <summary>
        ///  Access to equipment
        /// </summary>
        /// <param name="lLoginID">Equipment user Login ID: CLIENT Login return values</param>
        /// <param name="dwCommand">configuration type</param>
        /// <param name="lChannel">Channel number, if not channel parameter, lChannel need not, can be set to 1</param>
        /// <param name="lpOutBuffer">To store the output parameters of the buffer, according to the different types, the output of different configuration, see the specific data structure definition</param>
        /// <param name="dwOutBufferSize">The input buffer size (in bytes).</param>
        /// <param name="lpBytesReturned">The actual return buffer size, the size of the corresponding configuration, (in bytes)</param>
        /// <returns>true:sucdeed;false:fail</returns>
        public static bool NETGetDevConfig(int lLoginID, CONFIG_COMMAND dwCommand, int lChannel, IntPtr lpOutBuffer, UInt32 dwOutBufferSize, ref UInt32 lpBytesReturned)
        {
            return NETGetDevConfig(lLoginID, dwCommand, lChannel, lpOutBuffer, dwOutBufferSize, ref lpBytesReturned, 3000);            
        }

        /// <summary>
        /// Internal use of equipment information command function
        /// </summary>
        /// <param name="lLoginID">Equipment user Login ID: CLIENT Login return values</param>
        /// <param name="lChannel">channel</param>
        /// <param name="dwCommand">Configuration commands</param>
        /// <param name="obj">object Object</param>
        /// <param name="typeName">type name</param>
        /// <param name="waittime">waittime</param>
        /// <returns>true:succeed;false:fail</returns>
        private static bool PGetDevConfig(int lLoginID, int lChannel, CONFIG_COMMAND dwCommand, ref object obj, Type typeName, int waittime)
        {
            bool returnValue = false;
            IntPtr pBoxInfo = IntPtr.Zero;
            try
            {                
                UInt32 returnBuffSize = 0;
                pBoxInfo = Marshal.AllocHGlobal(Marshal.SizeOf(typeName));//Allocation of fixed specified the size of the memory space
                if (pBoxInfo != IntPtr.Zero)
                {
                    returnValue = NETGetDevConfig(lLoginID, dwCommand, lChannel, pBoxInfo, (UInt32)Marshal.SizeOf(typeName), ref returnBuffSize, waittime);
                    if (returnValue == true)
                    {
                        obj = Marshal.PtrToStructure((IntPtr)((UInt32)pBoxInfo), typeName);
                    }
                }
                NETThrowLastError(returnValue);
            }
            catch (Exception e)
            {
                NETThrowLastError(e);
                returnValue= false;
            }
            finally
            {
                Marshal.FreeHGlobal(pBoxInfo);//Release the fixed memory allocation
                pBoxInfo = IntPtr.Zero;                
            }
            return returnValue;
        }

        /// <summary>
        /// Internal use of all equipment information command function
        /// </summary>
        /// <param name="lLoginID">Equipment user Login ID: CLIENT Login return values</param>
        /// <param name="lChannel">channel</param>
        /// <param name="dwCommand">ConfigurationCommand</param>
        /// <param name="obj">object object</param>
        /// <param name="typeName">typename</param>
        /// <param name="waittime">waittime</param>
        /// <returns>true:succeed;false:fail</returns>
        private static bool PGetDevConfig(int lLoginID, CONFIG_COMMAND dwCommand, ref object[] obj, Type typeName, int waittime)
        {
            bool returnValue = false;
            IntPtr pBoxInfo = IntPtr.Zero;
            try
            {
                UInt32 returnBuffSize = 0;
                pBoxInfo = Marshal.AllocHGlobal(obj.Length * Marshal.SizeOf(typeName));//Allocate fixed and specified memory space   
                if (pBoxInfo != IntPtr.Zero)
                {
                    returnValue = NETGetDevConfig(lLoginID, dwCommand, -1, pBoxInfo, (uint)obj.Length * (UInt32)Marshal.SizeOf(typeName), ref returnBuffSize, waittime);
                    if (returnValue == true)
                    {
                        for (int loop = 0; loop < obj.Length; loop++)
                        {
                            obj[loop] = Marshal.PtrToStructure((IntPtr)((UInt32)pBoxInfo + (UInt32)Marshal.SizeOf(typeName) * loop), typeName);
                        }
                    }
                }
                NETThrowLastError(returnValue);
            }
            catch (Exception e)
            {
                NETThrowLastError(e);
                returnValue= false;
            }
            finally
            {
                Marshal.FreeHGlobal(pBoxInfo);//Release the fixed memory allocation
                pBoxInfo = IntPtr.Zero;
            }
            return returnValue;            
        }

        /// <summary>
        /// Access to equipment configuration [equipment configuration information]
        /// </summary>
        /// <param name="lLoginID">Equipment user Login ID: CLIENT Login return values</param>
        /// <param name="systemAttrConfig">equipment information</param>
        /// <param name="waittime">waittime</param>
        /// <returns>true:succeed;false:fail</returns>
        public static bool NETGetDevConfig(int lLoginID, ref NETDEV_SYSTEM_ATTR_CFG systemAttrConfig, int waittime)
        {
            object result = new object();
            bool returnValue = false;
            returnValue = PGetDevConfig(lLoginID, 0, CONFIG_COMMAND.NET_DEV_DEVICECFG, ref result, typeof(NETDEV_SYSTEM_ATTR_CFG),waittime);
            systemAttrConfig = (NETDEV_SYSTEM_ATTR_CFG)result;
            return returnValue;
        }
        
        /// <summary>
        ///  Access to equipment configuration [device information configuration default waiting time 3000]
        /// </summary>
        /// <param name="lLoginID">Equipment user Login ID: CLIENT Login return values</param>
        /// <param name="systemAttrConfig">equipment information</param>
        /// <returns>true:succeed;false:fail</returns>
        public static bool NETGetDevConfig(int lLoginID, ref NETDEV_SYSTEM_ATTR_CFG systemAttrConfig)
        {
            return NETGetDevConfig(lLoginID, ref systemAttrConfig, 3000);
        }

        /// <summary>
        ///  Access to network parameters
        /// </summary>
        /// <param name="lLoginID">Equipment user Login ID: CLIENT Login return values	</param>
        /// <param name="netConfig">etwork parameter</param>
        /// <param name="waittime">waittime</param>
        /// <returns>true:succeed;false:fail</returns>
        public static bool NETGetDevConfig(int lLoginID, ref NETDEV_NET_CFG netConfig, int waittime)
        {
            object result = new object();
            bool returnValue = false;
            returnValue = PGetDevConfig(lLoginID, 0, CONFIG_COMMAND.NET_DEV_NETCFG, ref result, typeof(NETDEV_NET_CFG), waittime);
            netConfig = (NETDEV_NET_CFG)result;
            return returnValue;

        }

        /// <summary>
        ///  Access to the network parameters [the default wait time 3000]
        /// </summary>
        /// <param name="lLoginID">Equipment user Login ID: CLIENT Login return values</param>
        /// <param name="netConfig"> network parameter</param>
        /// <returns>true:succeed;false:fail</returns>
        public static bool NETGetDevConfig(int lLoginID, ref NETDEV_NET_CFG netConfig)
        {
            return NETGetDevConfig(lLoginID, ref netConfig, 3000);
        }

        /// <summary>
        ///  Access to specified channel configuration
        /// </summary>
        /// <param name="lLoginID">Equipment user Login ID: CLIENT Login return values</param>
        /// <param name="lChannel">Channel number [this value to 1]</param>
        /// <param name="netConfig">Channel Configuration</param>
        /// <param name="waittime">waittime</param>
        /// <returns>true:succeed;false:fail</returns>
        public static bool NETGetDevConfig(int lLoginID, int lChannel, ref NETDEV_CHANNEL_CFG channelConfig, int waittime)
        {
            object result = new object();
            bool returnValue = false;
            returnValue = PGetDevConfig(lLoginID, lChannel, CONFIG_COMMAND.NET_DEV_CHANNELCFG, ref result, typeof(NETDEV_CHANNEL_CFG), waittime);
            channelConfig = (NETDEV_CHANNEL_CFG)result;
            return returnValue;
        }

        /// <summary>
        ///  For specified channel configuration [the default wait time 3000]
        /// </summary>
        /// <param name="lLoginID">Equipment user Login ID: CLIENT Login return values</param>
        /// <param name="lChannel">Channel number [this value to 1]</param>
        /// <param name="netConfig">Channel Configuration</param>
        /// <returns>true:succeed;false:fail</returns>
        public static bool NETGetDevConfig(int lLoginID, int lChannel, ref NETDEV_CHANNEL_CFG channelConfig)
        {
            return NETGetDevConfig(lLoginID, lChannel, ref channelConfig);
        }

        /// <summary>
        ///  Get all the channel configuration
        /// </summary>
        /// <param name="lLoginID">Get all the channel configuration</param>
        /// <param name="lChannel">channel</param>
        /// <param name="netConfig">Channel Configuration</param>
        /// <param name="waittime">waittime</param>
        /// <returns>true:succeed;false:fail</returns>
        public static bool NETGetDevConfig(int lLoginID, ref NETDEV_CHANNEL_CFG[] channelConfig, int waittime)
        {
            object[] result = new object[channelConfig.Length];
            bool returnValue = false;
            returnValue = PGetDevConfig(lLoginID, CONFIG_COMMAND.NET_DEV_CHANNELCFG, ref result, typeof(NETDEV_CHANNEL_CFG), waittime);
            for(int i=0;i<channelConfig.Length;i++)
            {
                channelConfig[i] = (NETDEV_CHANNEL_CFG)result[i];
            }            
            return returnValue;
        }

        /// <summary>
        ///  Get all the channel configuration [the default wait time 3000]
        /// </summary>
        /// <param name="lLoginID">Equipment user Login ID: CLIENT Login return values</param>
        /// <param name="lChannel">channel</param>
        /// <param name="netConfig">Channel Configuration</param>
        /// <returns>true:succeed;false:fail</returns>
        public static bool NETGetDevConfig(int lLoginID, ref NETDEV_CHANNEL_CFG[] channelConfig)
        {
            return NETGetDevConfig(lLoginID, ref channelConfig, 3000);
        }

        /// <summary>
        ///  Obtain the specified channel video configuration
        /// </summary>
        /// <param name="lLoginID">Equipment user Login ID: CLIENT Login return values</param>
        /// <param name="lChannel">channel</param>
        /// <param name="netConfig">Video configuration</param>
        /// <param name="waittime">waittime</param>
        /// <returns>true:succeed;false:fail</returns>
        public static bool NETGetDevConfig(int lLoginID, int lChannel, ref NETDEV_RECORD_CFG recordConfig, int waittime)
        {
            object result = new object();
            bool returnValue = false;
            returnValue = PGetDevConfig(lLoginID, lChannel, CONFIG_COMMAND.NET_DEV_RECORDCFG, ref result, typeof(NETDEV_RECORD_CFG), waittime);
            recordConfig = (NETDEV_RECORD_CFG)result;
            return returnValue;
        }

        /// <summary>
        /// Obtain the specified channel video configuration [the default wait time 3000]
        /// </summary>
        /// <param name="lLoginID">Equipment user Login ID: CLIENT Login return values</param>
        /// <param name="lChannel">channel</param>
        /// <param name="netConfig">Video configuration</param>
        /// <returns>true:succeed;false:fail</returns>
        public static bool NETGetDevConfig(int lLoginID, int lChannel, ref NETDEV_RECORD_CFG recordConfig)
        {
            return NETGetDevConfig(lLoginID, lChannel, ref recordConfig, 3000);
        }

        /// <summary>
        ///  Get all the video channel configuration
        /// </summary>
        /// <param name="lLoginID">Equipment user Login ID: CLIENT Login return values</param>
        /// <param name="netConfig">Video configuration</param>
        /// <param name="waittime">waittime</param>
        /// <returns>true:succeed;false:fail</returns>
        public static bool NETGetDevConfig(int lLoginID, ref NETDEV_RECORD_CFG[] recordConfig, int waittime)
        {
            object[] result = new object[recordConfig.Length];
            bool returnValue = false;
            returnValue = PGetDevConfig(lLoginID, CONFIG_COMMAND.NET_DEV_RECORDCFG, ref result, typeof(NETDEV_RECORD_CFG), waittime);
            if (returnValue == true)
            {
                for (int i = 0; i < recordConfig.Length; i++)
                {
                    recordConfig[i] = (NETDEV_RECORD_CFG)result[i];
                }
            }
            return returnValue;
        }

        /// <summary>
        ///  Get all the video channel configuration [the default wait time 3000]
        /// </summary>
        /// <param name="lLoginID">Equipment user Login ID: CLIENT Login return values</param>
        /// <param name="netConfig">Video configuration</param>
        /// <returns>true:succeed;false:fail</returns>
        public static bool NETGetDevConfig(int lLoginID, ref NETDEV_RECORD_CFG[] recordConfig)
        {
            return NETGetDevConfig(lLoginID, ref recordConfig, 3000);
        }

        /// <summary>
        ///  Equipment user Login ID: CLIENT Login return values
        /// </summary>
        /// <param name="lLoginID">Equipment user Login ID: CLIENT Login return values</param>
        /// <param name="netConfig">Preview the parameters</param>
        /// <param name="waittime">waittime</param>
        /// <returns>true:succeed;false:fail</returns>
        public static bool NETGetDevConfig(int lLoginID, ref NETDEV_PREVIEW_CFG previewConfig, int waittime)
        {
            object result = new object();
            bool returnValue = false;
            returnValue = PGetDevConfig(lLoginID, -1, CONFIG_COMMAND.NET_DEV_PREVIEWCFG, ref result, typeof(NETDEV_PREVIEW_CFG), waittime);
            previewConfig = (NETDEV_PREVIEW_CFG)result;
            return returnValue;
        }

        /// <summary>
        /// Access to preview parameters [the default wait time 3000]
        /// </summary>
        /// <param name="lLoginID">quipment user Login ID: CLIENT Login return values</param>
        /// <param name="netConfig">Preview the parameters</param>
        /// <returns>true:succeed;false:fail</returns>
        public static bool NETGetDevConfig(int lLoginID, ref NETDEV_PREVIEW_CFG previewConfig)
        {
            return NETGetDevConfig(lLoginID, ref previewConfig, 3000);
        }

        /// <summary>
        ///  Access to a serial port parameters
        /// </summary>
        /// <param name="lLoginID">Equipment user Login ID: CLIENT Login return values</param>
        /// <param name="netConfig">Preview the parameters</param>
        /// <param name="waittime">waittime</param>
        /// <returns>true:succeed;false:fail</returns>
        public static bool NETGetDevConfig(int lLoginID, ref NETDEV_COMM_CFG commConfig, int waittime)
        {
            object result = new object();
            bool returnValue = false;
            returnValue = PGetDevConfig(lLoginID, -1, CONFIG_COMMAND.NET_DEV_COMMCFG, ref result, typeof(NETDEV_COMM_CFG), waittime);
            commConfig = (NETDEV_COMM_CFG)result;
            return returnValue;
        }

        /// <summary>
        /// Access to a serial port parameters [the default wait time 3000]
        /// </summary>
        /// <param name="lLoginID">Equipment user Login ID: CLIENT Login return values</param>
        /// <param name="netConfig">Preview the parameters</param>
        /// <returns>true:succeed;false:fail</returns>
        public static bool NETGetDevConfig(int lLoginID, ref NETDEV_COMM_CFG commConfig)
        {
            return NETGetDevConfig(lLoginID, ref commConfig, 3000);
        }

        /// <summary>
        ///  Get alarm parameters
        /// </summary>
        /// <param name="lLoginID">Equipment user Login ID: CLIENT Login return values</param>
        /// <param name="alarmConfig">alarm parameters</param>
        /// <param name="waittime">waittime</param>
        /// <returns>true:succeed;false:fail</returns>
        public static bool NETGetDevConfig(int lLoginID, ref NETDEV_ALARM_SCHEDULE alarmConfig, int waittime)
        {
            object result = new object();
            bool returnValue = false;
            returnValue = PGetDevConfig(lLoginID, 0, CONFIG_COMMAND.NET_DEV_ALARMCFG, ref result, typeof(NETDEV_ALARM_SCHEDULE), waittime);
            if (returnValue == true)
            {
                alarmConfig = (NETDEV_ALARM_SCHEDULE)result;
            }
  
            return returnValue;
        }

        /// <summary>
        /// Get alarm parameters [the default wait time 3000]
        /// </summary>
        /// <param name="lLoginID">Equipment user Login ID: CLIENT Login return values</param>
        /// <param name="alarmConfig">alarm parameters</param>
        /// <returns>true:succeed;false:fail</returns>
        public static bool NETGetDevConfig(int lLoginID, ref NETDEV_ALARM_SCHEDULE alarmConfig)
        {
            return NETGetDevConfig(lLoginID, ref alarmConfig, 3000);

        }

        /// <summary>
        ///  get DVD time
        /// </summary>
        /// <param name="lLoginID">Equipment user Login ID: CLIENT Login return values</param>
        /// <param name="dvrTime">time parameters</param>
        /// <param name="waittime">waitime</param>
        /// <returns>true:succeed;false:fail</returns>
        public static bool NETGetDevConfig(int lLoginID, ref NET_TIME dvrTime, int waittime)
        {
            object result = new object();
            bool returnValue = false;
            returnValue = PGetDevConfig(lLoginID, -1, CONFIG_COMMAND.NET_DEV_TIMECFG, ref result, typeof(NET_TIME), waittime);
            dvrTime = (NET_TIME)result;
            return returnValue;
        }

        public static bool NETQueryRecordState(int lLoginID ,  byte[] pRSBuffer , int maxlen , ref int nRSBufferLen , int waittime)
        {
            bool returnValue = false;
            returnValue = CLIENT_QueryRecordState(lLoginID,  pRSBuffer, maxlen, ref nRSBufferLen, waittime);
            return returnValue;
        }

        public static bool NETSetupRecordState(int lLoginID, byte[] pRSBuffer, int nRSBufferlen)
        {
            bool returnValue = false;
            returnValue = CLIENT_SetupRecordState(lLoginID, pRSBuffer, nRSBufferlen);
            return returnValue;
        }
       
        /// <summary>
        /// Get DVR time [the default wait time 3000]
        /// </summary>
        /// <param name="lLoginID">Equipment user Login ID: CLIENT Login return values</param>
        /// <param name="dvrTime">time parameters</param>
        /// <returns>true:succeed;false:fail</returns>
        public static bool NETGetDevConfig(int lLoginID, ref NET_TIME dvrTime)
        {
            return NETGetDevConfig(lLoginID, ref dvrTime, 3000);
        }

        #region << Intercom parameter information later because related to model the first edition SDK temporarily not realize [temporary shielding] >>

        ///// <summary>
        /////  To obtain the intercom parameters
        ///// </summary>
        ///// <param name="lLoginID">Equipment user Login ID: CLIENT Login return values</param>
        ///// <param name="dvrTime">Intercom parameters</param>
        ///// <returns>true:succeed;false:fail</returns>
        //public static bool NETGetDevConfig(int lLoginID, ref NETDEV_TALK_CFG talkConfig)
        //{
        //    object result = new object();
        //    bool returnValue = false;
        //    returnValue = PGetDevConfig(lLoginID, -1, CONFIG_COMMAND.NET_DEV_TALKCFG, ref result, typeof(NETDEV_TALK_CFG));
        //    talkConfig = (NETDEV_TALK_CFG)result;
        //    return returnValue;
        //}

        ///// <summary>
        /////  For automatic maintenance parameters
        ///// </summary>
        ///// <param name="lLoginID">Equipment user Login ID: CLIENT Login return values</param>
        ///// <param name="dvrTime">Automatic maintenance parameters</param>
        ///// <returns>true:succeed;false:fail</returns>
        //public static bool NETGetDevConfig(int lLoginID, ref NETDEV_TALK_CFG autoConfig)
        //{
        //    object result = new object();
        //    bool returnValue = false;
        //    returnValue = PGetDevConfig(lLoginID, -1, CONFIG_COMMAND.NET_DEV_AUTOMTCFG, ref result, typeof(NETDEV_TALK_CFG));
        //    autoConfig = (NETDEV_TALK_CFG)result;
        //    return returnValue;
        //}

        #endregion

        #endregion

        #region << set up parameters >>

        /// <summary>
        /// Set the device configuration
        /// </summary>
        /// <param name="lLoginID">Equipment user Login ID: CLIENT Login return values</param>
        /// <param name="dwCommand"> configuration type</param>
        /// <param name="lChannel">Channel number, if the channel data set to 0 XFFFFFFFF (1), if you don't need to channel number command, this parameter is invalid</param>
        /// <param name="lpInBuffer">To store the output parameters of the buffer, according to the different types, different input configuration, see the specific data structure definition</param>
        /// <param name="dwInBufferSize">The input buffer size (in bytes).</param>
        /// <param name="waittime">waittime</param>
        /// <returns>true:succeed;false:fail</returns>
        public static bool NETSetDevConfig(int lLoginID, CONFIG_COMMAND dwCommand, int lChannel, IntPtr lpInBuffer, UInt32 dwInBufferSize, int waittime)
        {
            bool returnValue = false;
            returnValue = CLIENT_SetDevConfig(lLoginID, (UInt32)dwCommand, lChannel, lpInBuffer, dwInBufferSize, waittime);
            NETThrowLastError(returnValue);
            return returnValue;
        }

        /// <summary>
        /// Set the device configuration
        /// </summary>
        /// <param name="lLoginID">Equipment user Login ID: CLIENT Login return values</param>
        /// <param name="dwCommand"> configuration type</param>
        /// <param name="lChannel">Channel number, if the channel data set to 0 XFFFFFFFF (1), if you don't need to channel number command, this parameter is invalid</param>
        /// <param name="lpOutBuffer">To store the output parameters of the buffer, according to the different types, different input configuration, see the specific data structure definition</param>
        /// <param name="dwOutBufferSize">The input buffer size (in bytes).</param>
        /// <returns>true:succeed;false:fail</returns>
        public static bool NETSetDevConfig(int lLoginID, CONFIG_COMMAND dwCommand, int lChannel, IntPtr lpInBuffer, UInt32 dwInBufferSize)
        {
            return NETSetDevConfig(lLoginID, dwCommand, lChannel, lpInBuffer, dwInBufferSize, 3000);
        }

        /// <summary>
        /// nternal use setting device information command function
        /// </summary>
        /// <param name="lLoginID">Equipment user Login ID: CLIENT Login return values</param>
        /// <param name="lChannel">Channel number, if the channel data set to 0 XFFFFFFFF (1), if you don't need to channel number command, this parameter is invalid</param>
        /// <param name="dwCommand">Configuration commands</param>
        /// <param name="obj">objectobject</param>
        /// <param name="typeName">structure type</param>
        /// <param name="waittime">waittime</param>
        /// <returns>true:succeed;false:fail</returns>
        private static bool PSetDevConfig(int lLoginID, int lChannel, CONFIG_COMMAND dwCommand, object obj, Type typeName, int waittime)
        {
            bool returnValue = false;
            IntPtr pBoxInfo = IntPtr.Zero;
            try
            {
                pBoxInfo = Marshal.AllocHGlobal(Marshal.SizeOf(typeName));//Allocation of fixed specified the size of the memory space
                if (pBoxInfo != IntPtr.Zero)
                {
                    Marshal.StructureToPtr(obj, pBoxInfo, true);
                    returnValue = NETSetDevConfig(lLoginID, dwCommand, lChannel, pBoxInfo, (UInt32)Marshal.SizeOf(typeName), waittime);
                }
            }
            catch (Exception e)
            {
                NETThrowLastError(e);
                returnValue= false;
            }
            finally
            {
                Marshal.FreeHGlobal(pBoxInfo);//Release the fixed memory allocation
                pBoxInfo = IntPtr.Zero;
            }
            return returnValue;
            
        }

        /// <summary>
        /// Internal use of all information set equipment command function
        /// </summary>
        /// <param name="lLoginID">Equipment user Login ID: CLIENT Login return values</param>
        /// <param name="dwCommand">Configuration commands</param>
        /// <param name="obj">objectobject</param>
        /// <param name="typeName">struct types</param>
        /// <param name="waittime">waittime</param>
        /// <returns>true:succeed;false:fail</returns>
        private static bool PSetDevConfig(int lLoginID, CONFIG_COMMAND dwCommand,object[] obj, Type typeName, int waittime)
        {
            bool returnValue = false;
            IntPtr pBoxInfo = IntPtr.Zero;
            try
            {
                pBoxInfo = Marshal.AllocHGlobal(obj.Length * Marshal.SizeOf(typeName));//Allocation of fixed specified the size of the memory space
                if (pBoxInfo != IntPtr.Zero)
                {
                    for (int loop = 0; loop < obj.Length; loop++)
                    {
                        Marshal.StructureToPtr(obj[loop], (IntPtr)((UInt32)pBoxInfo + (UInt32)Marshal.SizeOf(typeName) * loop), true);
                    }
                    returnValue = NETSetDevConfig(lLoginID, dwCommand, -1, pBoxInfo, (uint)obj.Length * (UInt32)Marshal.SizeOf(typeName), waittime);
                }
            }
            catch (Exception e)
            {
                NETThrowLastError(e);
                returnValue= false;
            }
            finally
            {
                Marshal.FreeHGlobal(pBoxInfo);//Release the fixed memory allocation
                pBoxInfo = IntPtr.Zero;
                
            }
            return returnValue;
        }

        /// <summary>
        /// Device attributes set
        /// </summary>
        /// <param name="lLoginID">Equipment user Login ID: CLIENT Login return values</param>
        /// <param name="systemAttrConfig">equipment attributes</param>
        /// <param name="waittime">waitime</param>
        /// <returns>true:succeed;false:fail</returns>
        public static bool NETSetDevConfig(int lLoginID,NETDEV_SYSTEM_ATTR_CFG systemAttrConfig, int waittime)
        {
            bool returnValue = false;
            returnValue = PSetDevConfig(lLoginID, 0, CONFIG_COMMAND.NET_DEV_DEVICECFG, (object)systemAttrConfig, typeof(NETDEV_SYSTEM_ATTR_CFG), waittime);
            return returnValue;
        }

        /// <summary>
        /// Device attributes set [the default wait time 3000]
        /// </summary>
        /// <param name="lLoginID">Equipment user Login ID: CLIENT Login return values</param>
        /// <param name="systemAttrConfig">Equipment Properties</param>
        /// <returns>true:succeed;false:fail</returns>
        public static bool NETSetDevConfig(int lLoginID, NETDEV_SYSTEM_ATTR_CFG systemAttrConfig)
        {
            return NETSetDevConfig(lLoginID, systemAttrConfig, 3000);
        }

        /// <summary>
        /// Set the network parameters
        /// </summary>
        /// <param name="lLoginID">Equipment user loginID:CLIENT_Loginreturn value</param>
        /// <param name="netConfig">network parameter</param>
        /// <param name="waittime">waittime</param>
        /// <returns>true:succeed;false:fail</returns>
        public static bool NETSetDevConfig(int lLoginID, NETDEV_NET_CFG netConfig, int waittime)
        {            
            bool returnValue = false;
            returnValue = PSetDevConfig(lLoginID, 0, CONFIG_COMMAND.NET_DEV_NETCFG, (object)netConfig, typeof(NETDEV_NET_CFG), waittime);           
            return returnValue;
        }

        /// <summary>
        /// Set the network parameters [the default wait time 3000]
        /// </summary>
        /// <param name="lLoginID">Equipment user Login ID: CLIENT Login return values</param>
        /// <param name="netConfig">network parameter</param>
        /// <returns>true:succeed;false:fail</returns>
        public static bool NETSetDevConfig(int lLoginID, NETDEV_NET_CFG netConfig)
        {
            return NETSetDevConfig(lLoginID, netConfig, 3000);
        }

        /// <summary>
        /// Set the specified channel configuration
        /// </summary>
        /// <param name="lLoginID">Equipment user Login ID: CLIENT Login return values</param>
        /// <param name="lChannel">Channel number [this value to 1]</param>
        /// <param name="netConfig"> Channel Configuration</param>
        /// <param name="waittime">waittime</param>
        /// <returns>true:succeed;false:fai;</returns>
        public static bool NETSetDevConfig(int lLoginID, int lChannel, NETDEV_CHANNEL_CFG channelConfig, int waittime)
        {            
            bool returnValue = false;
            returnValue = PSetDevConfig(lLoginID, lChannel, CONFIG_COMMAND.NET_DEV_CHANNELCFG,(object)channelConfig, typeof(NETDEV_CHANNEL_CFG), waittime);           
            return returnValue;
        }

        /// <summary>
        /// Set the specified channel configuration [the default time 3000] 
        /// </summary>
        /// <param name="lLoginID">Equipment user Login ID: CLIENT Login return values</param>
        /// <param name="lChannel">Channel number [this value to 1]</param>
        /// <param name="netConfig">channel configuration</param>
        /// <param name="waittime"></param>
        /// <returns>true:succeed;false:fail</returns>
        public static bool NETSetDevConfig(int lLoginID, int lChannel, NETDEV_CHANNEL_CFG channelConfig)
        {
            return NETSetDevConfig(lLoginID, lChannel, channelConfig, 3000);
        }

        /// <summary>
        ///  Set all channel configuration
        /// </summary>
        /// <param name="lLoginID">Equipment user Login ID: CLIENT Login return values</param>
        /// <param name="lChannel">channel NUMBER</param>
        /// <param name="netConfig">channel configuration</param>
        /// <param name="waittime">waittime</param>
        /// <returns>true:succeed;false:fail</returns>
        public static bool NETSetDevConfig(int lLoginID, NETDEV_CHANNEL_CFG[] channelConfig, int waittime)
        {
            object[] result = new object[channelConfig.Length];
            for (int i = 0; i < channelConfig.Length; i++)
            {
                result[i] = (object)channelConfig[i];
            }
            bool returnValue = false;
            returnValue = PSetDevConfig(lLoginID, CONFIG_COMMAND.NET_DEV_CHANNELCFG, result, typeof(NETDEV_CHANNEL_CFG), waittime);
            
            return returnValue;
        }

        /// <summary>
        ///  Set all channel configuration
        /// </summary>
        /// <param name="lLoginID">Equipment user Login ID: CLIENT Login return values</param>
        /// <param name="lChannel">Channel number</param>
        /// <param name="netConfig">channel configuration</param>
        /// <param name="waittime">waittime</param>
        /// <returns>true:succeed;false:fail</returns>
        public static bool NETSetDevConfig(int lLoginID, NETDEV_CHANNEL_CFG[] channelConfig)
        {
            return NETSetDevConfig(lLoginID, channelConfig, 3000);
        }

        /// <summary>
        /// Set the specified channel video configuration
        /// </summary>
        /// <param name="lLoginID">Equipment user Login ID: CLIENT Login return values</param>
        /// <param name="lChannel">Channel number</param>
        /// <param name="netConfig">Video configuration</param>
        /// <param name="waittime">waittime</param>
        /// <returns>true:succeed;false:fail</returns>
        public static bool NETSetDevConfig(int lLoginID, int lChannel,NETDEV_RECORD_CFG recordConfig, int waittime)
        {
            bool returnValue = false;
            returnValue = PSetDevConfig(lLoginID, lChannel, CONFIG_COMMAND.NET_DEV_RECORDCFG, (object)recordConfig, typeof(NETDEV_RECORD_CFG), waittime);
            return returnValue;
        }

        /// <summary>
        /// Set the specified channel configuration [the default time 3000] 
        /// </summary>
        /// <param name="lLoginID">Equipment user Login ID: CLIENT Login return values</param>
        /// <param name="lChannel">Channel number</param>
        /// <param name="netConfig">Video configuration</param>
        /// <param name="waittime">waittime</param>
        /// <returns>true:succeed;false:fail</returns>
        public static bool NETSetDevConfig(int lLoginID, int lChannel, NETDEV_RECORD_CFG recordConfig)
        {
            return NETSetDevConfig(lLoginID, lChannel, recordConfig, 600);
        }

        /// <summary>
        /// Set all channel video configuration
        /// </summary>
        /// <param name="lLoginID">Equipment user Login ID: CLIENT Login return values</param>
        /// <param name="netConfig">Video configuration</param>
        /// <param name="waittime">waittime</param>
        /// <returns>true:succeed;false:fail</returns>
        public static bool NETSetDevConfig(int lLoginID, NETDEV_RECORD_CFG[] recordConfig, int waittime)
        {
            object[] result = new object[recordConfig.Length];
            for (int i = 0; i < recordConfig.Length; i++)
            {
                result[i]=(object)recordConfig[i];
            }
            bool returnValue = false;
            returnValue = PSetDevConfig(lLoginID, CONFIG_COMMAND.NET_DEV_RECORDCFG, result, typeof(NETDEV_RECORD_CFG), waittime);
            
            return returnValue;
        }

        /// <summary>
        /// Set all channels video configuration [the default wait time 3000]
        /// </summary>
        /// <param name="lLoginID">Equipment user Login ID: CLIENT Login return values</param>
        /// <param name="netConfig">Video configuration</param>
        /// <returns>true:succeed;false:fail</returns>
        public static bool NETSetDevConfig(int lLoginID, NETDEV_RECORD_CFG[] recordConfig)
        {
            return NETSetDevConfig(lLoginID, recordConfig, 3000);
        }


        /// <summary>
        /// Set up the parameter preview
        /// </summary>
        /// <param name="lLoginID">Equipment user Login ID: CLIENT Login return values</param>
        /// <param name="netConfig">preview parameter</param>
        /// <param name="waittime">waittime</param>
        /// <returns>true:succeed;false:fail</returns>
        public static bool NETSetDevConfig(int lLoginID,NETDEV_PREVIEW_CFG previewConfig, int waittime)
        {
            bool returnValue = false;
            returnValue = PSetDevConfig(lLoginID, -1, CONFIG_COMMAND.NET_DEV_PREVIEWCFG, (object)previewConfig, typeof(NETDEV_PREVIEW_CFG), waittime);
            return returnValue;
        }

        /// <summary>
        /// Set the preview parameters [the default wait time 3000]
        /// </summary>
        /// <param name="lLoginID">Equipment user Login ID: CLIENT Login return values</param>
        /// <param name="netConfig">preview parameter</param>
        /// <returns>true:succeed;false:fail</returns>
        public static bool NETSetDevConfig(int lLoginID,NETDEV_PREVIEW_CFG previewConfig)
        {
            return NETSetDevConfig(lLoginID,previewConfig, 3000);
        }

        /// <summary>
        /// Set the serial port parameters
        /// </summary>
        /// <param name="lLoginID">Equipment user Login ID: CLIENT Login return values</param>
        /// <param name="netConfig">preview parameter</param>
        /// <param name="waittime">waittime</param>
        /// <returns>true:succeed;false:fail</returns>
        public static bool NETSetDevConfig(int lLoginID, NETDEV_COMM_CFG commConfig, int waittime)
        {
            bool returnValue = false;
            returnValue = PSetDevConfig(lLoginID, -1, CONFIG_COMMAND.NET_DEV_COMMCFG, (object)commConfig, typeof(NETDEV_COMM_CFG), waittime);
            return returnValue;
        }

        /// <summary>
        /// Set the serial port parameters [the default wait time 3000]
        /// </summary>
        /// <param name="lLoginID">Equipment user Login ID: CLIENT Login return values</param>
        /// <param name="netConfig">preview parameter</param>
        /// <returns>true:succeed;false:fail</returns>
        public static bool NETSetDevConfig(int lLoginID, NETDEV_COMM_CFG commConfig)
        {
            return NETSetDevConfig(lLoginID, commConfig, 3000);
        }

        /// <summary>
        /// Set the alarm parameters
        /// </summary>
        /// <param name="lLoginID">Equipment user Login ID: CLIENT Login return values</param>
        /// <param name="alarmConfig">alarm parameters</param>
        /// <param name="waittime">waittime</param>
        /// <returns>true:succeed;false:fail</returns>
        public static bool NETSetDevConfig(int lLoginID,NETDEV_ALARM_SCHEDULE alarmConfig, int waittime)
        {
            bool returnValue = false;
            returnValue = PSetDevConfig(lLoginID, 0, CONFIG_COMMAND.NET_DEV_ALARMCFG, (object)alarmConfig, typeof(NETDEV_ALARM_SCHEDULE), waittime);
            return returnValue;
        }

        /// <summary>
        /// Set the alarm parameters [the default wait time 3000]
        /// </summary>
        /// <param name="lLoginID">Equipment user Login ID: CLIENT Login return values</param>
        /// <param name="alarmConfig">alarm parameters</param>
        /// <returns>true:succeed;false:fail</returns>
        public static bool NETSetDevConfig(int lLoginID,NETDEV_ALARM_SCHEDULE alarmConfig)
        {
            return NETSetDevConfig(lLoginID,alarmConfig, 3000);
        }

        /// <summary>
        /// set DVR time
        /// </summary>
        /// <param name="lLoginID">Equipment user Login ID: CLIENT Login return values</param>
        /// <param name="dvrTime">time parameters</param>
        /// <param name="waittime">waittime</param>
        /// <returns>true:succeed;false:fail</returns>
        public static bool NETSetDevConfig(int lLoginID,NET_TIME dvrTime, int waittime)
        {
            
            bool returnValue = false;
            returnValue = PSetDevConfig(lLoginID, -1, CONFIG_COMMAND.NET_DEV_TIMECFG, (object)dvrTime, typeof(NET_TIME), waittime);
            return returnValue;
        }

        /// <summary>
        /// Set the DVR time [the default wait time 3000]
        /// </summary>
        /// <param name="lLoginID">quipment user Login ID: CLIENT Login return values</param>
        /// <param name="dvrTime">time parameters</param>
        /// <returns>true:succeed;false:fail</returns>
        public static bool NETSetDevConfig(int lLoginID, NET_TIME dvrTime)
        {
            return NETSetDevConfig(lLoginID, dvrTime, 3000);
        }

        #endregion

        #endregion

        #region << user management >>

        /// <summary>
        /// view user information
        /// </summary>
        /// <param name="iLogin">DHLogin return value</param>
        /// <param name="userInfo">USER_MANAGE_INFOStructure</param>
        /// <param name="waitTime">waittime</param>
        /// <returns>true:succeed;false:fail</returns>
        public static bool NETQueryUserInfo(int iLogin,ref USER_MANAGE_INFO userInfo,int waitTime)
        {
            bool retValue = false;
            IntPtr pBoxInfo = IntPtr.Zero;
            try
            {
                pBoxInfo = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(USER_MANAGE_INFO)));//Allocation of fixed specified the size of the memory space
                if (pBoxInfo != IntPtr.Zero)
                {
                    retValue = CLIENT_QueryUserInfo(iLogin, pBoxInfo, waitTime);
                    if (retValue == true)
                    {
                        userInfo = (USER_MANAGE_INFO)Marshal.PtrToStructure((IntPtr)((UInt32)pBoxInfo), typeof(USER_MANAGE_INFO));
                    }
                }
                NETThrowLastError(retValue);                
            }
            catch (Exception e)
            {
                NETThrowLastError(e);
                retValue = false;
            }
            finally
            {
                Marshal.FreeHGlobal(pBoxInfo);//Release the fixed memory allocation
                pBoxInfo = IntPtr.Zero;
            } 
            return retValue;
                           
        }

        /// <summary>
        /// Add User Group/ Delete User Group
        /// </summary>
        /// <param name="iLogin">DHLogin return value</param>
        /// <param name="grpInfo">Add User Information</param>
        /// <param name="waitTime">Waiting Time</param>
        /// <returns></returns>
        public static bool NETOperateUserInfo(int iLogin, USER_OPERATE operate,USER_GROUP_INFO grpInfo,int waitTime)
        {
            bool retValue = false;
            IntPtr pBoxInfo = IntPtr.Zero;
            try
            {
                pBoxInfo = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(USER_GROUP_INFO)));//Allocate fixed and specified memory space
                if (pBoxInfo != IntPtr.Zero)
                {
                    Marshal.StructureToPtr(grpInfo, pBoxInfo, true);
                    retValue = CLIENT_OperateUserInfo(iLogin, (int)operate, pBoxInfo, IntPtr.Zero, waitTime);
                }
                NETThrowLastError(retValue);
            }
            catch (Exception e)
            {
                NETThrowLastError(e);
                retValue = false;
            }
            finally
            {
                Marshal.FreeHGlobal(pBoxInfo);//Release the fixed memory allocation
                pBoxInfo = IntPtr.Zero;                
            }
            return retValue;
        }

        /// <summary>
        /// correct user group
        /// </summary>
        /// <param name="iLogin"></param>
        /// <param name="grpInfo"></param>
        /// <param name="waitTime"></param>
        /// <returns></returns>
        public static bool NETOperateUserInfo(int iLogin, USER_OPERATE operate, USER_GROUP_INFO grpNewInfo, USER_GROUP_INFO grpOldInfo, int waitTime)
        {
            bool retValue = false;
            IntPtr pBoxInfo = IntPtr.Zero;
            IntPtr pBoxInfo1 = IntPtr.Zero;
            try
            {
                pBoxInfo = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(USER_GROUP_INFO)));//Allocate fixed and specified memory space           
                pBoxInfo1 = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(USER_GROUP_INFO)));//Allocate fixed and specified memory space 
                if (pBoxInfo != IntPtr.Zero && pBoxInfo1!=IntPtr.Zero)
                {
                    Marshal.StructureToPtr(grpNewInfo, pBoxInfo, true);
                    Marshal.StructureToPtr(grpOldInfo, pBoxInfo1, true);
                    retValue = CLIENT_OperateUserInfo(iLogin, (int)operate, pBoxInfo, pBoxInfo1, waitTime);
                }
                NETThrowLastError(retValue);                
            }
            catch (Exception e)
            {
                NETThrowLastError(e);
                retValue= false;
            }
            finally
            {
                Marshal.FreeHGlobal(pBoxInfo);//Release the fixed memory allocation
                pBoxInfo = IntPtr.Zero;
                Marshal.FreeHGlobal(pBoxInfo1);//Release the fixed memory allocation
                pBoxInfo = IntPtr.Zero;                
            }
            return retValue;
            
        }

        /// <summary>
        /// Add User Group/ Delete User Group
        /// </summary>
        /// <param name="iLogin">DHLogin return value</param>
        /// <param name="usrInfo">Add User Information</param>
        /// <param name="waitTime">Waiting Time</param>
        /// <returns></returns>
        public static bool NETOperateUserInfo(int iLogin, USER_OPERATE operate, USER_INFO usrInfo, int waitTime)
        {
            bool retValue = false;
            IntPtr pBoxInfo = IntPtr.Zero;
            try
            {
                pBoxInfo = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(USER_INFO)));//Allocate fixed and specified memory space
                if (pBoxInfo != IntPtr.Zero)
                {
                    Marshal.StructureToPtr(usrInfo, pBoxInfo, true);
                    retValue = CLIENT_OperateUserInfo(iLogin, (int)operate, pBoxInfo, IntPtr.Zero, waitTime);
                }
                NETThrowLastError(retValue);
            }
            catch (Exception e)
            {
                NETThrowLastError(e);
                retValue = false;
            }
            finally
            {
                Marshal.FreeHGlobal(pBoxInfo);//Release the fixed memory allocation
                pBoxInfo = IntPtr.Zero;
            }
            return retValue;
        }

        /// <summary>
        /// Correct user basic information/correct user password
        /// </summary>
        /// <param name="iLogin">DHLogin return value</param>
        /// <param name="userNewInfo">information after user changes</param>
        /// <param name="userOldInfo">information before user changes</param>
        /// <param name="waitTime">waiting time</param>
        /// <returns></returns>
        public static bool NETOperateUserInfo(int iLogin, USER_OPERATE operate, USER_INFO userNewInfo, USER_INFO userOldInfo, int waitTime)
        {
            bool retValue = false;
            IntPtr pBoxInfo = IntPtr.Zero;
            IntPtr pBoxInfo1 = IntPtr.Zero;
            try
            {                
                pBoxInfo = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(USER_INFO)));//Allocate fixed and specified memory space               
                pBoxInfo1 = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(USER_INFO)));//Allocate fixed and specified memory space
                if (pBoxInfo != IntPtr.Zero & pBoxInfo1!=IntPtr.Zero)
                {
                    Marshal.StructureToPtr(userNewInfo, pBoxInfo, true);
                    Marshal.StructureToPtr(userOldInfo, pBoxInfo1, true);
                    retValue = CLIENT_OperateUserInfo(iLogin, (int)operate, pBoxInfo, pBoxInfo1, waitTime);
                }
                NETThrowLastError(retValue);                
            }
            catch (Exception e)
            {
                NETThrowLastError(e);
                retValue = false;
            }
            finally
            {
                Marshal.FreeHGlobal(pBoxInfo);//Release the fixed memory allocation
                pBoxInfo = IntPtr.Zero;
                Marshal.FreeHGlobal(pBoxInfo1);//Release the fixed memory allocation
                pBoxInfo1 = IntPtr.Zero;                
            }
            return retValue;
        }
        
        #endregion

        #region << 状态侦听 >>

        /// <summary>
        /// Set up callback function of equipment information, in order to get the current information of the equipment
        /// </summary>
        /// <param name="cbMessage">callback parameter of message</param>
        /// <param name="dwUser">user data,if there is no data,please use IntPtr.Zero</param>
        public static void NETSetDVRMessCallBack(fMessCallBack cbMessage, IntPtr dwUser)
        {
            CLIENT_SetDVRMessCallBack(cbMessage, dwUser);
            //NETThrowLastError();
        }

        /// <summary>
        /// Start to subscribe message of equipment,used to set whether you need to callback equipment information,get news from<seealso cref="DHSetDVRMessCallBack"/>call back from set values。
        /// </summary>
        /// <param name="lLoginID">Equipment user loginID:<seealso cref="DHLogin"/> return value</param>
        /// <returns>true:success;false:failure</returns>
        public static bool NETStartListen(int lLoginID)
        {
            bool returnValue = false;
            returnValue = CLIENT_StartListen(lLoginID);
            NETThrowLastError(returnValue);
            return returnValue;
        }

        /// <summary>
        /// Stop listenting some equipments
        /// </summary>
        /// <param name="lLoginID">equioment user loginID:<seealso cref="CLIENT_Login"/>的returen value</param>
        /// <returns>true:success;false:fail</returns>
        public static bool NETStopListen(int lLoginID)
        {
            bool returnValue = false;
            returnValue = CLIENT_StopListen(lLoginID);
            NETThrowLastError(returnValue);
            return returnValue;
        }

        /// <summary>
        /// Start to subscribe message of equipment,used to set whether you need to callback equipment information,get news from<seealso cref="DHSetDVRMessCallBack"/>call back from set values。
        /// </summary>
        /// <param name="lLoginID">Equipment user loginID:<seealso cref="DHLogin"/>return value</param>
        /// <returns>true:success;false:failure</returns>
        public static bool NETStartListenEx(int lLoginID)
        {
            bool returnValue = false;
            returnValue = CLIENT_StartListenEx(lLoginID);
            NETThrowLastError(returnValue);
            return returnValue;
        }

        /// <summary>
        /// Start listening service, currently only alarm monitoring function is realized
        /// </summary>
        /// <param name="wPort">Start listening ports</param>
        /// <param name="pIp">binding IP,when is , binding all legitimate IP in this machine</param>
        /// <param name="pfscb">callback interface of the server</param>
        /// <param name="dwTimeOut">Server maintenance connection timeout</param>
        /// <param name="dwUserData">Custom data that the user callback</param>
        /// <returns>Successfully return a handle to the server,fail to return  0</returns>
        public static int NETStartService(ushort wPort, string pIp, fServiceCallBack pfscb, int dwTimeOut, IntPtr dwUserData)
        {
            int returnValue;
            returnValue = CLIENT_StartService(wPort, pIp, pfscb, dwTimeOut, dwUserData);
            NETThrowLastError(returnValue);
            return returnValue;
        }

        /// <summary>
        /// Stop port monitoring service
        /// </summary>
        /// <param name="lHandle">
        /// shut down the server handle:<seealso cref="CLIENT_StartService"/>returm value</param>
        /// <returns>true:success;false:failure</returns>
        public static bool NETStopService(int lHandle)
        {
            bool returnValue = false;
            returnValue = CLIENT_StopService(lHandle);
            NETThrowLastError(returnValue);
            return returnValue;
        }

        #endregion

        #region << login >>

        /// <summary>
        /// Registered users to the device,When the equipment end set user to reuse（equipmentdefault user 如admin,cannot set to reuse）,so use this account to the device can register many times
        /// </summary>
        /// <param name="pchDVRIP">equipmentIP</param>
        /// <param name="wDVRPort">equipmentport</param>
        /// <param name="pchUserName">user name</param>
        /// <param name="pchPassword">user password</param>
        /// <param name="lpDeviceInfo">equipment information,belongs to the output parameters</param>
        /// <param name="error">Return to the login error code</param>
        /// <returns>Failure to return0,return successfully equipmentID</returns>
        public static int NETLogin(string pchDVRIP, ushort wDVRPort, string pchUserName, string pchPassword, out NET_DEVICEINFO lpDeviceInfo, out int error)
        {
            int result = CLIENT_Login(pchDVRIP, wDVRPort, pchUserName, pchPassword, out lpDeviceInfo, out error);
            NETThrowLastError(result);
            return result;
        }

        /// <summary>
        /// Query Device`s current Time
        /// </summary>
        /// <param name="lLoginID">Device handles user login</param>
        /// <param name="tmDevTime">Device time</param>
        /// <param name="waittime">Waiting Time</param>
        /// <returns>true:success;false:failure</returns>
        public static bool NETQueryDeviceTime(Int32 lLoginID, ref DateTime tmDevTime, int waittime)
        {
            bool returnValue = false;
            NET_TIME netQueryTime = new NET_TIME();
            returnValue = CLIENT_QueryDeviceTime(lLoginID, out netQueryTime, waittime);
            if (returnValue)
            {
                tmDevTime = ToDateTime(netQueryTime);
            }
            NETThrowLastError();
            return returnValue;
        }

        /// <summary>
        /// Set Device Time
        /// </summary>
        /// <param name="lLoginID">Device handles user login</param>
        /// <param name="tmSetup">Device time</param>
        /// <returns>true:success;false:failure</returns>
        public static bool NETSetupDeviceTime(Int32 lLoginID , DateTime tmSetup)
        {
            bool returnValue = false;
            NET_TIME netSetupTime = ToNetTime(tmSetup);
            returnValue = CLIENT_SetupDeviceTime(lLoginID, ref netSetupTime);
            NETThrowLastError();
            return returnValue;
        }

        /// <summary>
        /// Set SecurityKey
        /// </summary>
        /// <param name="lPlayHandle">Play handles</param>
        /// <param name="szKey">SecurityKey</param>
        /// <returns>true:success;false:failure</returns>
        public static bool NetSetSecurityKey(Int32 lPlayHandle, string szKey)
        {
            bool result = CLIENT_SetSecurityKey(lPlayHandle, szKey, (UInt32)szKey.Length);
            NETThrowLastError(result);
            return result;
        }

        /// <summary>
        ///  registere users to the expansion interface device interface,Support a user to specify equipment support ability
        /// </summary>
        /// <param name="pchDVRIP">equipmentIP</param>
        /// <param name="wDVRPort">equipmentequipment port</param>
        /// <param name="pchUserName">user name</param>
        /// <param name="pchPassword">user password</param>
        /// <param name="nSpecCap">Equipment support ability,Value of 2 indicates active listening mode user login。[Vehicledvrlogin]</param>
        /// <param name="pCapParam">nSpecCap supplement parameter, when nSpecCap = 2,pCapParam Filling equipment serial number string。[vehicle dvr login]</param>
        /// <param name="lpDeviceInfo">equipment information,belongs to the output parameters</param>
        /// <param name="error">Return to the login error code</param>
        /// <returns>Failure to return0,return successfully equipmentID</returns>
        public static int NETLogin(string pchDVRIP, ushort wDVRPort, string pchUserName, string pchPassword, int nSpecCap, string pCapParam, out NET_DEVICEINFO lpDeviceInfo, out int error)
        {
            int result = CLIENT_LoginEx(pchDVRIP, wDVRPort, pchUserName, pchPassword, nSpecCap, pCapParam, out lpDeviceInfo, out error);
            NETThrowLastError(result);
            return result;
        }

        /// <summary>
        /// cancellation of device users
        /// </summary>
        /// <param name="lLoginID">Equipment user loginID:<seealso cref="CLIENT_Login"/>returen value</param>
        /// <returns>true:success;false:failure</returns>
        public static bool NETLogout(int lLoginID)
        {
            bool returnValue = false;
            returnValue = CLIENT_Logout(lLoginID);
            NETThrowLastError(returnValue);
            return returnValue;
        }

        #endregion

        #region << equipment control >>
        //no for the moment
        #endregion

        #region << real-time monitoring >>

        /// <summary>
        /// Start the real-time monitoring
        /// </summary>
        /// <param name="lLoginID">Equipment user loginID:<seealso cref="CLIENT_Login"/>return value</param>
        /// <param name="nChannelID">channelID</param>
        /// <param name="hWnd">Show the container window handle</param>
        /// <returns>Failure to return0,Successful return to the real-time monitoringID( real-time monitoring handle)</returns>
        public static int NETRealPlay(int lLoginID, int nChannelID, IntPtr hWnd)
        {
            int returnValue = CLIENT_RealPlay(lLoginID, nChannelID, hWnd);
            NETThrowLastError(returnValue);
            return returnValue;
        }

        /// <summary>
        /// Start the real-time monitoring(enhanced edition)
        /// </summary>
        /// <param name="lLoginID">Equipment user loginID:<seealso cref="CLIENT_Login"/>return value</param>
        /// <param name="nChannelID">channelID</param>
        /// <param name="realPlayType">Real-time broadcast type</param>
        /// <param name="hWnd">Show the container window handle</param>
        /// <returns>Failure to return0,Successful return to the real-time monitoringID(real-time monitoring handle)</returns>
        public static int NETRealPlayEx(int lLoginID, int nChannelID, REALPLAY_TYPE realPlayType,IntPtr hWnd)
        {
            int returnValue = CLIENT_RealPlayEx(lLoginID, nChannelID, hWnd,realPlayType);
            NETThrowLastError(returnValue);
            return returnValue;
        }

        /// <summary>
        /// Stop the real-time monitoring
        /// </summary>
        /// <param name="lRealHandle">real-time monitoring handle:<seealso cref="CLIENT_RealPlay"/>reture value</param>
        /// <returns>true:success;false:failure</returns>
        public static bool NETStopRealPlay(int lRealHandle)
        {
            bool returnValue = CLIENT_StopRealPlay(lRealHandle);
            NETThrowLastError(returnValue);
            return returnValue;
        }

        /// <summary>
        /// Stop the real-time monitoring(enhanced edition)
        /// </summary>
        /// <param name="lRealHandle">real-time monitoring handle:<seealso cref="CLIENT_RealPlay"/>return value</param>
        /// <returns>true:success;false:failure</returns>
        public static bool NETStopRealPlayEx(int lRealHandle)
        {
            bool returnValue = CLIENT_StopRealPlayEx(lRealHandle);
            NETThrowLastError(returnValue);
            return returnValue;
        }

        /// <summary>
        /// Begin to save the real-time monitoring data,save the screen image of front-end equipment monitoring data
        /// </summary>
        /// <param name="lRealHandle">CLIENT_RealPlayr return value</param>
        /// <param name="pchFileName">Real-time monitoring to save the file name</param>
        /// <returns>true:success;false:failure</returns>
        public static bool NETStartSaveRealData(int lRealHandle, string pchFileName)
        {
            bool returnValue = CLIENT_SaveRealData(lRealHandle, pchFileName);
            NETThrowLastError(returnValue);
            return returnValue;
        }

        /// <summary>
        /// Stop saving real-time monitoring data,Close to save the file
        /// </summary>
        /// <param name="lRealHandle">CLIENT_RealPlay return value</param>
        /// <returns>true:success;false:failure</returns>
        public static bool NETStopSaveRealData(int lRealHandle)
        {
            bool returnValue = CLIENT_StopSaveRealData(lRealHandle);
            NETThrowLastError(returnValue);
            return returnValue;
        }

        /// <summary>
        /// Set real-time monitoring data callback,Provide users with equipment out of data,when cbRealData is NULL finish the callback data
        /// </summary>
        /// <param name="lRealHandle">CLIENT_RealPlay return value</param>
        /// <param name="cbRealData">The callback function,Real-time data out of the device for outgoing</param>
        /// <param name="dwUser">user data</param>
        /// <returns>true:success;false:failure</returns>
        public static bool NETSetRealDataCallBack(int lRealHandle, fRealDataCallBack cbRealData, IntPtr dwUser)
        {
            bool returnValue = CLIENT_SetRealDataCallBack(lRealHandle, cbRealData, dwUser);
            NETThrowLastError(returnValue);
            return returnValue;
        }

        /// <summary>
        /// Set real-time monitoring data callback expansion interface ,is complementary to the previous interface, add a callback parameter data type flag dwFlag, can be selectively to bring up the needed data,for the type of data did not set a callback callback out, when set to 0x1f with the same effect as an interface, but also done on the callback function expansion
        /// </summary>
        /// <param name="lRealHandle">CLIENT_RealPlay return value</param>
        /// <param name="cbRealData">The callback function,for outgoing various types of real-time data</param>
        /// <param name="dwFlag">
        /// Come bitwise, Can be combined, When is the 0x1f,callback of five data types 
        /// 0x00000001  Equivalent to the original raw data
        /// 0x00000002  Is the standard data MPEG4/H264
        /// 0x00000004  YUVdata
        /// 0x00000008  PCMdata
        /// 0x00000010  Original audio data</param>
        /// <param name="dwUser">user data</param>
        /// <returns>true:success;false:failure</returns>
        public static bool NETSetRealDataCallBack(int lRealHandle, fRealDataCallBackEx cbRealData,UInt32 dwFlag, IntPtr dwUser)
        {
            bool returnValue = CLIENT_SetRealDataCallBackEx(lRealHandle, cbRealData, dwUser,dwFlag);
            NETThrowLastError(returnValue);
            return returnValue;
        }

        #endregion

        #region << PTZ control >>

        /// <summary>
        /// PTZ control
        /// </summary>
        /// <param name="lLoginID">Equipment User LoginID:<seealso cref="CLIENT_Login"/>return value</param>
        /// <param name="nChannelID">Channel number</param>
        /// <param name="dwPTZCommand">PTZ control commands<seealso cref="PTZControlType"/>[PTZ_****commod]</param>
        /// <param name="dwStep">Stepping/Speed</param>
        /// <param name="dwStop">Whether to stop</param>
        /// <returns>true:success;false:failure</returns>
        public static bool NETPTZControl(int lLoginID, int nChannelID, PTZ_CONTROL dwPTZCommand, ushort dwStep, bool dwStop)
        {
            bool returnValue = false;
            switch (dwPTZCommand)
            {
                case PTZ_CONTROL.PTZ_APERTURE_ADD_CONTROL:
                case PTZ_CONTROL.PTZ_APERTURE_DEC_CONTROL:
                case PTZ_CONTROL.PTZ_DOWN_CONTROL:
                case PTZ_CONTROL.PTZ_FOCUS_ADD_CONTROL:
                case PTZ_CONTROL.PTZ_FOCUS_DEC_CONTROL:
                //case PTZ_CONTROL.PTZ_LAMP_CONTROL:
                case PTZ_CONTROL.PTZ_LEFT_CONTROL:
                //case PTZ_CONTROL.PTZ_POINT_DEL_CONTROL:
                case PTZ_CONTROL.PTZ_POINT_LOOP_CONTROL:
                //case PTZ_CONTROL.PTZ_POINT_MOVE_CONTROL:
                //case PTZ_CONTROL.PTZ_POINT_SET_CONTROL:
                case PTZ_CONTROL.PTZ_RIGHT_CONTROL:
                case PTZ_CONTROL.PTZ_UP_CONTROL:
                case PTZ_CONTROL.PTZ_ZOOM_ADD_CONTROL:
                case PTZ_CONTROL.PTZ_ZOOM_DEC_CONTROL:
                    returnValue = CLIENT_PTZControl(lLoginID, nChannelID, (ushort)dwPTZCommand, dwStep, dwStop);
                    break;
                case PTZ_CONTROL.PTZ_LAMP_CONTROL:
                    returnValue = CLIENT_DHPTZControlEx(lLoginID, nChannelID, (ushort)dwPTZCommand, dwStep, 0, 0, dwStop);
                    break;
                case PTZ_CONTROL.PTZ_POINT_DEL_CONTROL:                
                case PTZ_CONTROL.PTZ_POINT_MOVE_CONTROL:
                case PTZ_CONTROL.PTZ_POINT_SET_CONTROL:
                    returnValue = CLIENT_DHPTZControlEx(lLoginID, nChannelID, (ushort)dwPTZCommand, 0, dwStep, 0, dwStop);
                    break;

                //case PTZControlType.PTZ_POINT_LOOP_CONTROL:
                //    returnValue = CLIENT_DHPTZControl(lLoginID, nChannelID, (ushort)dwPTZCommand, "", "", dwStep, dwStop);
                //    break;
                case PTZ_CONTROL.EXTPTZ_SETMODESTART:
                case PTZ_CONTROL.EXTPTZ_SETMODESTOP:
                case PTZ_CONTROL.EXTPTZ_RUNMODE:
                case PTZ_CONTROL.EXTPTZ_STOPMODE:
                case PTZ_CONTROL.EXTPTZ_DELETEMODE:
                    returnValue = CLIENT_DHPTZControlEx(lLoginID, nChannelID, (ushort)dwPTZCommand, dwStep, 0, 0, dwStop);
                    break;
                case PTZ_CONTROL.EXTPTZ_STARTPANCRUISE:
                case PTZ_CONTROL.EXTPTZ_STOPPANCRUISE:
                case PTZ_CONTROL.EXTPTZ_SETLEFTBORDER:
                case PTZ_CONTROL.EXTPTZ_RIGHTBORDER:
                case PTZ_CONTROL.EXTPTZ_STARTLINESCAN:
                case PTZ_CONTROL.EXTPTZ_CLOSELINESCAN:
                case PTZ_CONTROL.EXTPTZ_REVERSECOMM:
                case PTZ_CONTROL.EXTPTZ_OPENMENU:
                case PTZ_CONTROL.EXTPTZ_CLOSEMENU:
                case PTZ_CONTROL.EXTPTZ_MENUOK:
                case PTZ_CONTROL.EXTPTZ_MENUCANCEL:
                case PTZ_CONTROL.EXTPTZ_MENUUP:
                case PTZ_CONTROL.EXTPTZ_MENUDOWN:
                case PTZ_CONTROL.EXTPTZ_MENULEFT:
                case PTZ_CONTROL.EXTPTZ_MENURIGHT:
                case PTZ_CONTROL.EXTPTZ_TOTAL:
                    returnValue = CLIENT_DHPTZControlEx(lLoginID, nChannelID, (ushort)dwPTZCommand, 0, 0, 0, dwStop);
                    break;
            }
            
            return returnValue;
        }

        /// <summary>
        /// Extended PTZ control, Enhanced control of the PTZ control function functions
        /// </summary>
        /// <param name="lLoginID">Equipment User LoginID:<seealso cref="CLIENT_Login"/>return value</param>
        /// <param name="nChannelID">channel number</param>
        /// <param name="dwPTZCommand">PTZ control commands<seealso cref="PTZControlType"/>See the documentation accept parameters format</param>
        /// <param name="param1">Parameter1</param>
        /// <param name="param2">Parameter2</param>
        /// <param name="param3">Parameter3</param>
        /// <param name="dwStop">Whether to stop</param>
        /// <returns>true:suceess;false:failure</returns>
        public static bool NETPTZControl(int lLoginID, int nChannelID, PTZ_CONTROL dwPTZCommand, ushort param1, ushort param2, ushort param3, bool dwStop)
        {
            bool returnValue = false;
            switch (dwPTZCommand)
            {
                case PTZ_CONTROL.PTZ_APERTURE_ADD_CONTROL:
                case PTZ_CONTROL.PTZ_APERTURE_DEC_CONTROL:
                case PTZ_CONTROL.PTZ_DOWN_CONTROL:
                case PTZ_CONTROL.PTZ_FOCUS_ADD_CONTROL:
                case PTZ_CONTROL.PTZ_FOCUS_DEC_CONTROL:
                case PTZ_CONTROL.PTZ_LAMP_CONTROL:
                case PTZ_CONTROL.PTZ_LEFT_CONTROL:
                case PTZ_CONTROL.PTZ_POINT_DEL_CONTROL:
                case PTZ_CONTROL.PTZ_POINT_MOVE_CONTROL:
                case PTZ_CONTROL.PTZ_POINT_SET_CONTROL:
                case PTZ_CONTROL.PTZ_RIGHT_CONTROL:
                case PTZ_CONTROL.PTZ_UP_CONTROL:
                case PTZ_CONTROL.PTZ_ZOOM_ADD_CONTROL:
                case PTZ_CONTROL.PTZ_ZOOM_DEC_CONTROL:
                    returnValue = CLIENT_DHPTZControlEx(lLoginID, nChannelID, (ushort)dwPTZCommand, 0, param2, 0, dwStop);
                    break;
                case PTZ_CONTROL.PTZ_POINT_LOOP_CONTROL:
                    returnValue = CLIENT_DHPTZControlEx(lLoginID, nChannelID, (ushort)dwPTZCommand, 0, 0, param3, dwStop);
                    break;
                case PTZ_CONTROL.EXTPTZ_LEFTTOP:
                case PTZ_CONTROL.EXTPTZ_RIGHTTOP:
                case PTZ_CONTROL.EXTPTZ_LEFTDOWN:
                case PTZ_CONTROL.EXTPTZ_RIGHTDOWN:
                case PTZ_CONTROL.EXTPTZ_ADDTOLOOP:
                case PTZ_CONTROL.EXTPTZ_DELFROMLOOP:
                case PTZ_CONTROL.EXTPTZ_AUXIOPEN:
                case PTZ_CONTROL.EXTPTZ_AUXICLOSE:
                    returnValue = CLIENT_DHPTZControlEx(lLoginID, nChannelID, (ushort)dwPTZCommand, param1, param2, 0, dwStop);
                    break;
                case PTZ_CONTROL.EXTPTZ_SETMODESTART:
                case PTZ_CONTROL.EXTPTZ_SETMODESTOP:
                case PTZ_CONTROL.EXTPTZ_RUNMODE:
                case PTZ_CONTROL.EXTPTZ_STOPMODE:
                case PTZ_CONTROL.EXTPTZ_DELETEMODE:
                    returnValue = CLIENT_DHPTZControlEx(lLoginID, nChannelID, (ushort)dwPTZCommand, param1, 0, 0, dwStop);
                    break;
                //case PTZ_CONTROL.EXTPTZ_FASTGOTO:
                //    returnValue = CLIENT_DHPTZControl(lLoginID, nChannelID, (ushort)dwPTZCommand, param1, param2, param3, dwStop);
                //    break;
            }
            return returnValue;
        }

        /// <summary>
        /// Extended PTZ control, Enhanced control of the PTZ control  functions
        /// </summary>
        /// <param name="lLoginID">Equipment User LoginID:<seealso cref="CLIENT_Login"/>return value</param>
        /// <param name="nChannelID">Channel number</param>
        /// <param name="dwPTZCommand">PTZ control commands<seealso cref="PTZControlType"/>Command only accepts two parameters</param>
        /// <param name="param1">Parameter1</param>
        /// <param name="param2">Parameter2</param>
        /// <param name="param3">Parameter3</param>
        /// <param name="dwStop">Whether to stop</param>
        /// <returns>true:success;false:failure</returns>
        public static bool NETPTZControl(int lLoginID, int nChannelID, PTZ_CONTROL dwPTZCommand, ushort param1, ushort param2, bool dwStop)
        {
            bool returnValue = false;
            switch (dwPTZCommand)
            {
                case PTZ_CONTROL.PTZ_UP_CONTROL:
                case PTZ_CONTROL.PTZ_LEFT_CONTROL:
                case PTZ_CONTROL.PTZ_DOWN_CONTROL:
                case PTZ_CONTROL.PTZ_RIGHT_CONTROL:
                case PTZ_CONTROL.PTZ_ZOOM_ADD_CONTROL:
                case PTZ_CONTROL.PTZ_ZOOM_DEC_CONTROL:
                case PTZ_CONTROL.PTZ_FOCUS_ADD_CONTROL:
                case PTZ_CONTROL.PTZ_FOCUS_DEC_CONTROL:
                case PTZ_CONTROL.PTZ_APERTURE_ADD_CONTROL:
                case PTZ_CONTROL.PTZ_APERTURE_DEC_CONTROL:
                case PTZ_CONTROL.EXTPTZ_LEFTTOP:
                case PTZ_CONTROL.EXTPTZ_RIGHTTOP:
                case PTZ_CONTROL.EXTPTZ_LEFTDOWN:
                case PTZ_CONTROL.EXTPTZ_RIGHTDOWN:
                case PTZ_CONTROL.EXTPTZ_ADDTOLOOP:
                case PTZ_CONTROL.EXTPTZ_DELFROMLOOP:
                case PTZ_CONTROL.EXTPTZ_AUXIOPEN:
                case PTZ_CONTROL.EXTPTZ_AUXICLOSE:
                    returnValue = CLIENT_DHPTZControl(lLoginID, nChannelID, (ushort)dwPTZCommand, param1, param2, 0, dwStop, IntPtr.Zero);
                    break;
            }
            return returnValue;
        }

        /// <summary>
        /// Extended PTZ control, Supports three-dimensional fast positioning
        /// </summary>
        /// <param name="lLoginID">Equipment User LoginID:<seealso cref="CLIENT_Login"/>return value</param>
        /// <param name="nChannelID">Channel number</param>
        /// <param name="dwPTZCommand">PTZ control commands<seealso cref="PTZControlType"/>Command only accepts two parameters</param>
        /// <param name="param1">Parameter1</param>
        /// <param name="param2">Parameter2</param>
        /// <param name="param3">Parameter3</param>
        /// <param name="dwStop">Whether to stop</param>
        /// <returns>true:success;false:failure</returns>
        public static bool NETPTZControl(int lLoginID, int nChannelID, bool blnFastGoto, int  param1, int param2,int param3, bool dwStop)
        {
            bool returnValue = false;
            if (blnFastGoto)
            {
                returnValue = CLIENT_DHPTZControlEx(lLoginID, nChannelID, (ushort)PTZ_CONTROL.EXTPTZ_FASTGOTO, param1, param2, param3, dwStop);
            }
            return returnValue;
        }

        #endregion

        #region << Playback downloads >>

        /// <summary>
        /// Query video files
        /// </summary>
        /// <param name="lLoginID">Device handles user login</param>
        /// <param name="nChannelId">channelID</param>
        /// <param name="nRecordFileType">Video file types </param>
        /// <param name="tmStart">Recording start time</param>
        /// <param name="tmEnd">Recording end time</param>
        /// <param name="pchCardid">card number,Only for card number query effectively,In other cases you can fill NULL</param>
        /// <param name="nriFileinfo">Return to video file information,Is an array of structures NET_RECORDFILE_INFO[Video file information for the specified bar]</param>
        /// <param name="maxlen">nriFileinfoThe maximum length of the buffer;[Unit of byte,Dimensional structure of an array of size number*sizeof(NET_RECORDFILE_INFO),Victoria is the size of the array is equal to 1,Recommend less than 200]</param>
        /// <param name="filecount">The number of documents returned,Maximum output parameters are only found in video recording until the buffer is full</param>
        /// <param name="waittime">Waiting Time</param>
        /// <param name="bTime">Whether by time(Currently inactive)</param>
        /// <returns>true:success;false:failure</returns>
        public static bool NETQueryRecordFile(int lLoginID, int nChannelId, RECORD_FILE_TYPE nRecordFileType, DateTime tmStart, DateTime tmEnd, string pchCardid, ref NET_RECORDFILE_INFO[] nriFileinfo, int maxlen, out  int filecount, int waittime, bool bTime)
        {
            bool returnValue = false;
            filecount = 0;
            IntPtr pBoxInfo = IntPtr.Zero;
            try
            {                
                NET_TIME timeStart = ToNetTime(tmStart);
                NET_TIME timeEnd = ToNetTime(tmEnd);
                pBoxInfo = Marshal.AllocHGlobal(maxlen);//Allocation of fixed specified the size of the memory space
                int fileCountMin = 0;
                if (pBoxInfo != IntPtr.Zero)
                {
                    returnValue = CLIENT_QueryRecordFile(lLoginID, nChannelId, (int)nRecordFileType, ref timeStart, ref timeEnd, pchCardid, pBoxInfo, maxlen, out filecount, waittime, bTime);
                    fileCountMin = (filecount <= nriFileinfo.Length ? filecount : nriFileinfo.Length);
                    for (int dwLoop = 0; dwLoop < fileCountMin; dwLoop++)
                    {
                        // specify the memory space of the data is copied to the purpose in the array in the specified format
                        nriFileinfo[dwLoop] = (NET_RECORDFILE_INFO)Marshal.PtrToStructure((IntPtr)((UInt32)pBoxInfo + Marshal.SizeOf(typeof(NET_RECORDFILE_INFO)) * dwLoop), typeof(NET_RECORDFILE_INFO));
                    }
                }
                NETThrowLastError(returnValue);
               
            }
            catch (Exception e)
            {
                NETThrowLastError(e);
                returnValue= false;
            }
            finally
            {
                Marshal.FreeHGlobal(pBoxInfo);//Release the fixed memory allocation
                pBoxInfo = IntPtr.Zero;                
            }
            return returnValue;           
        }

        /// <summary>
        /// Query the video file
        /// </summary>
        /// <param name="lLoginID">Device handles user login</param>
        /// <param name="nChannelId">channelID</param>
        /// <param name="nRecordFileType">Video file type </param>
        /// <param name="tmStart">Recording start time</param>
        /// <param name="tmEnd">Recording end time</param>
        /// <param name="pchCardid">card number,Only for card number query effectively,In other cases you can fill NULL</param>
        /// <param name="nriFileinfo">Return to video file information,Structure is a NET_RECORDFILE_INFO[Only one video file information]</param>
        /// <param name="maxlen">nriFileinfoThe maximum length of the buffer;[Sizeof size in bytes(NET_RECORDFILE_INFO)]</param>
        /// <param name="filecount">The number of documents returned,Maximum output parameters are only found in video recording until the buffer is full</param>
        /// <param name="waittime">waiting time</param>
        /// <param name="bTime">Whether by time(Currently inactive)</param>
        /// <returns>true:success;false:failure</returns>
        public static bool NETQueryRecordFile(int lLoginID, int nChannelId, RECORD_FILE_TYPE nRecordFileType, DateTime tmStart, DateTime tmEnd, string pchCardid, ref NET_RECORDFILE_INFO nriFileinfo, int maxlen, out  int filecount, int waittime, bool bTime)
        {
            bool returnValue = false;
            filecount = 0;
            NET_RECORDFILE_INFO[] ntFileInfo = new NET_RECORDFILE_INFO[1];
            returnValue = NETQueryRecordFile(lLoginID, nChannelId, nRecordFileType, tmStart, tmEnd, pchCardid, ref ntFileInfo, maxlen, out filecount, waittime, bTime);
            nriFileinfo = ntFileInfo[0];
            NETThrowLastError(returnValue);
            return returnValue;
        }

        /// <summary>
        /// Network Playback[Note:After the user logs in one device,Each channel can only play a video at the same time,Can't play the same channel multiple records at the same time]
        /// </summary>
        /// <param name="lLoginID">Device handle user login</param>
        /// <param name="lpRecordFile">Video file information, When the player is simply filled by the time the start time and end time, Other items to fill0</param>
        /// <param name="hWnd">Playback container handler</param>
        /// <param name="cbDownLoadPos">Progress callback function</param>
        /// <param name="dwUserData">User-defined data</param>
        /// <returns>Successful return network playback ID,Failure to return0</returns>
        public static int NETPlayBackByRecordFile(int lLoginID, ref NET_RECORDFILE_INFO lpRecordFile, IntPtr hWnd, fDownLoadPosCallBack cbDownLoadPos, IntPtr dwUserData)
        {
            int returnValue;
            returnValue = CLIENT_PlayBackByTime(lLoginID, (int)lpRecordFile.ch, ref lpRecordFile.starttime, ref lpRecordFile.endtime, hWnd, cbDownLoadPos, dwUserData);
            NETThrowLastError(returnValue);
            return returnValue;
        }

        /// <summary>
        ///Callback with data playback video files by extension interface,Each channel at the same time can only play a video,Can't play the same channel multiple records at the same time。Window parameter（hWnd）Effective correction data return values will be ignored,when window parameter(hWnd)is 0,need to pay attention to the callback function return values,See detail the callback function。
        /// </summary>
        /// <param name="lLoginID">CLIENT_Login return value</param>
        /// <param name="lpRecordFile">Video file information</param>
        /// <param name="hWnd">Playback handle container</param>
        /// <param name="cbDownLoadPos">Progress of the callback function</param>
        /// <param name="dwPosUser">Progress callback function user data</param>
        /// <param name="fDownLoadDataCallBack">Data callback function</param>
        /// <param name="dwDataUser">The callback function data user data</param>
        /// <returns>Successful return to network playback ID,Failure to return0</returns>
        public static int NETPlayBackByRecordFile(int lLoginID, ref NET_RECORDFILE_INFO lpRecordFile, IntPtr hWnd, fDownLoadPosCallBack cbDownLoadPos, IntPtr dwPosUser, fDataCallBack fDownLoadDataCallBack, IntPtr dwDataUser)
        {
            int returnValue;
            //returnValue = CLIENT_PlayBackByRecordFileEx(lLoginID, ref lpRecordFile, hWnd, cbDownLoadPos, dwPosUser,fDownLoadDataCallBack,dwDataUser);
            returnValue = CLIENT_PlayBackByTimeEx(lLoginID, (int)lpRecordFile.ch, ref lpRecordFile.starttime, ref  lpRecordFile.endtime, hWnd, cbDownLoadPos, dwPosUser, fDownLoadDataCallBack, dwDataUser);
            NETThrowLastError(returnValue);
            return returnValue;
        }

        /// <summary>
        /// Network playback by time
        /// </summary>
        /// <param name="lLoginID">Device handles user login</param>
        /// <param name="nChannelID">channelID</param>
        /// <param name="lpStartTime">Recording start time</param>
        /// <param name="lpStopTime">Recording end time</param>
        /// <param name="hWnd">Playback container handler</param>
        /// <param name="cbDownLoadPos">Progress callback function</param>
        /// <param name="dwUserData">User-defined data</param>
        /// <returns>Successful return network playback ID,Failure to return0</returns>
        public static int NETPlayBackByTime(int lLoginID, int nChannelID, DateTime tmStart, DateTime tmEnd, IntPtr hWnd, fDownLoadPosCallBack cbDownLoadPos, IntPtr dwUserData)
        {
            
            try
            {
                int returnValue = 0;
                NET_TIME timeStart = ToNetTime(tmStart);
                NET_TIME timeEnd = ToNetTime(tmEnd);
                returnValue = CLIENT_PlayBackByTime(lLoginID, nChannelID, ref timeStart, ref  timeEnd, hWnd, cbDownLoadPos, dwUserData);
                NETThrowLastError(returnValue);
                return returnValue;
            }
            catch (Exception e)
            {
                NETThrowLastError(e);
                return 0;
            }
            
        }

        public static int NETPlayBackByTimeEx2(int lLoginID, int nChannelID, DateTime tmStart, DateTime tmEnd, IntPtr hWnd, fDownLoadPosCallBack cbDownLoadPos, IntPtr dwPosUser, fDataCallBack fDownLoadDataCallBack, IntPtr dwDataUser, int nDirection, int nWaittime)
        {

            try
            {
                int returnValue = 0;
                NET_IN_PLAY_BACK_BY_TIME_INFO pbTimeInParam = new NET_IN_PLAY_BACK_BY_TIME_INFO();
                pbTimeInParam.stStartTime = ToNetTime(tmStart);
                pbTimeInParam.stStopTime = ToNetTime(tmEnd);
                pbTimeInParam.hWnd = hWnd;
                pbTimeInParam.cbDownLoadPos = cbDownLoadPos;
                pbTimeInParam.dwPosUser = dwPosUser;
                pbTimeInParam.fDownLoadDataCallBack = fDownLoadDataCallBack;
                pbTimeInParam.dwDataUser = dwDataUser;
                pbTimeInParam.nPlayDirection = nDirection;
                pbTimeInParam.nWaittime = nWaittime;
                NET_OUT_PLAY_BACK_BY_TIME_INFO pbTimeOutParam = new NET_OUT_PLAY_BACK_BY_TIME_INFO();
                returnValue = CLIENT_PlayBackByTimeEx2(lLoginID, nChannelID, ref pbTimeInParam, ref  pbTimeOutParam);
                NETThrowLastError(returnValue);
                return returnValue;
            }
            catch (Exception e)
            {
                NETThrowLastError(e);
                return 0;
            }

        }
        /// <summary>
        /// network by time playback
        /// </summary>
        /// <param name="lLoginID">Device handle user login</param>
        /// <param name="nChannelID">channelID</param>
        /// <param name="tmStart">The video start time</param>
        /// <param name="tmEnd">Recording end time</param>
        /// <param name="hWnd">Playback container handler</param>
        /// <param name="cbDownLoadPos">Progress callback function</param>
        /// <param name="dwPosUser">User-defined data[progress]</param>
        /// <param name="cbData">Data callback function</param>
        /// <param name="dwDataUser">User-defined data[progress]</param>
        /// <returns>Successful return network playback ID,Failure return 0</returns>
        public static int NETPlayBackByTime(int lLoginID, int nChannelID, DateTime tmStart, DateTime tmEnd, IntPtr hWnd, fDownLoadPosCallBack cbDownLoadPos, IntPtr dwPosUser,fDataCallBack cbData,IntPtr dwDataUser)
        {
            try
            {
                int returnValue = 0;
                NET_TIME timeStart = ToNetTime(tmStart);
                NET_TIME timeEnd = ToNetTime(tmEnd);
                returnValue = CLIENT_PlayBackByTimeEx(lLoginID, nChannelID, ref timeStart, ref  timeEnd, hWnd, cbDownLoadPos, dwPosUser,cbData,dwDataUser);
                NETThrowLastError(returnValue);
                return returnValue;
            }
            catch (Exception e)
            {
                NETThrowLastError(e);
                return 0;
            }

        }

        /// <summary>
        /// Playback playback controls:lay, pause, stop, single step, step to stop, slow, fast
        /// </summary>
        /// <param name="lPlayHandle">Play a handle</param>
        /// <param name="pPlayCommand">Control command:see<seealso cref="PlayControlType"/></param>
        /// <returns>true:success;false:failure</returns>
        public static bool NETPlayBackControl(int lPlayHandle, PLAY_CONTROL pPlayCommand)
        {
            bool returnValue = false;
            switch (pPlayCommand)
            {
                case PLAY_CONTROL.Play:
                    returnValue = CLIENT_PausePlayBack(lPlayHandle, 0);
                    break;
                case PLAY_CONTROL.Pause:
                    returnValue = CLIENT_PausePlayBack(lPlayHandle, 1);
                    break;
                case PLAY_CONTROL.Stop:
                    returnValue = CLIENT_StopPlayBack(lPlayHandle);
                    break;
                case PLAY_CONTROL.StepPlay:
                    returnValue = CLIENT_StepPlayBack(lPlayHandle, false);
                    break;
                case PLAY_CONTROL.StepStop:
                    returnValue = CLIENT_StepPlayBack(lPlayHandle, true);
                    break;
                case PLAY_CONTROL.Fast:
                    returnValue = CLIENT_FastPlayBack(lPlayHandle);
                    break;
                case PLAY_CONTROL.Slow:
                    returnValue = CLIENT_SlowPlayBack(lPlayHandle);
                    break;
            }
            NETThrowLastError(returnValue);
            return returnValue;
        }

        /// <summary>
        /// Playback playback controls:Change position [i.e. drag,Only parameter function effectively hWnd parameter of the function of the image acquired before the effective opening,Otherwise meaningless]
        /// </summary>
        /// <param name="lPlayHandle">Play handle</param>
        /// <param name="pPlayCommand">Play command:SeekByBit,SeekByTime</param>
        /// <param name="offset">SeekByTime:Offset relative to the beginning of time to file,Seconds;SeekByBit:Byte offset relative to the beginning of the file;</param>
        /// <returns>true:success;false:failure</returns>
        public static bool NETPlayBackControl(int lPlayHandle, PLAY_CONTROL pPlayCommand, uint offset)
        {
            bool returnValue = false;
            uint FalseValue = 0xFFFFFFFF;
            switch (pPlayCommand)
            {
                case PLAY_CONTROL.SeekByBit:
                    returnValue = CLIENT_SeekPlayBack(lPlayHandle, FalseValue, offset);
                    break;
                case PLAY_CONTROL.SeekByTime:
                    returnValue = CLIENT_SeekPlayBack(lPlayHandle, offset, FalseValue);
                    break;
            }
            NETThrowLastError(returnValue);
            return returnValue;
        }

        /// <summary>
        /// Playback playback controls:Change position [i.e. drag,Only parameter function effectively hWnd parameter of the function of the image acquired before the effective opening,Otherwise meaningless]
        /// </summary>
        /// <param name="lPlayHandle">Play handle</param>
        /// <param name="pPlayCommand">Play command:SeekByBit,SeekByTime</param>
        /// <param name="offset">SeekByTime:Offset relative to the beginning of time to file,Seconds;SeekByBit:Byte offset relative to the beginning of the file;</param>
        /// <returns>true:success;false:failure</returns>
        public static bool NETGetPlayBackOsdTime(int lPlayHandle, ref DateTime tmOsdTime, ref DateTime tmStartTime, ref DateTime tmEndTime)
        {
            bool returnValue = false;
            NET_TIME lpOsdTime = new NET_TIME();
            NET_TIME lpStartTime = new NET_TIME();
            NET_TIME lpEndTime = new NET_TIME();
            returnValue = CLIENT_GetPlayBackOsdTime(lPlayHandle, out lpOsdTime, out lpStartTime, out lpEndTime);
            if (true == returnValue)
            {
                tmOsdTime = ToDateTime(lpOsdTime);
                tmStartTime = ToDateTime(lpStartTime);
                tmEndTime = ToDateTime(lpEndTime);
            }
            NETThrowLastError(returnValue);
            return returnValue;
        }

        public static bool NETPlaybackControlDirection(int lPlayHandle, bool bBackward)
        {

            bool returnValue = false;

            returnValue = CLIENT_PlayBackControlDirection(lPlayHandle, bBackward);
            if (false == returnValue)
            {
                NETThrowLastError(returnValue);
                return returnValue;
            }

             return returnValue;
        }
        /// <summary>
        /// Download video files by file, Information by querying the file to download
        /// </summary>
        /// <param name="lLoginID">CLIENT_Loginreture value</param>
        /// <param name="lpRecordFile">Video file information</param>
        /// <param name="sSavedFileName">To save the video file name,Full path</param>
        /// <param name="cbDownLoadPos">Download progress callback function</param>
        /// <param name="dwUserData">Download progress callback user-defined data</param>
        /// <returns>Successful return Download ID,Failure to return0</returns>
        public static int NETDownloadByRecordFile(int lLoginID, NET_RECORDFILE_INFO lpRecordFile,string sSavedFileName,  fDownLoadPosCallBack cbDownLoadPos, IntPtr dwUserData)
        {
            int intReturnValue = 0;
            intReturnValue=CLIENT_DownloadByRecordFile(lLoginID, ref  lpRecordFile,sSavedFileName, cbDownLoadPos, dwUserData);            
            NETThrowLastError();            
            return intReturnValue;
        }

        /// <summary>
        /// Chronological Download,Specified channel direct input start time and end time to put video download
        /// </summary>
        /// <param name="lLoginID">CLIENT_Loginreturn value</param>
        /// <param name="nChannelId">Image channel number,Starting from 0</param>
        /// <param name="nRecordFileType">Retention</param>
        /// <param name="tmStart">Start time</param>
        /// <param name="tmEnd">End Time</param>
        /// <param name="sSavedFileName">To save the video file name,Full path</param>
        /// <param name="cbTimeDownLoadPos">Download progress callback function</param>
        /// <param name="dwUserData">Download progress callback user-defined data</param>
        /// <returns>Successful return downloadsID,Failure to return0</returns>
        public static int NETDownloadByTime(int lLoginID, int nChannelId, int nRecordFileType, DateTime tmStart, DateTime tmEnd, string sSavedFileName, fTimeDownLoadPosCallBack cbTimeDownLoadPos, IntPtr dwUserData)
        {
            int intReturnValue = 0;
            NET_TIME ntStart = ToNetTime(tmStart);
            NET_TIME ntEnd = ToNetTime(tmEnd);
            intReturnValue = CLIENT_DownloadByTime(lLoginID, nChannelId, nRecordFileType, ref ntStart, ref ntEnd, sSavedFileName, cbTimeDownLoadPos, dwUserData);
            NETThrowLastError();
            return intReturnValue;
        }

        /// <summary>
        /// Stop downloading video files
        /// </summary>
        /// <param name="lFileHandle">CLIENT_DownloadByRecordFile return value</param>
        /// <returns>true:success;false:failure</returns>
        public static bool NETStopDownload(int lFileHandle)
        {
            bool blnReturnValue = false;
            blnReturnValue = CLIENT_StopDownload(lFileHandle);
            NETThrowLastError();
            return blnReturnValue;
        }

        /// <summary>
        /// Download the video to get the current position,Can be used to display the download progress does not require real-time interface,Similar to the callback function to download
        /// </summary>
        /// <param name="lFileHandle">CLIENT_DownloadByRecordFilereturn value</param>
        /// <param name="nTotalSize">The total length of the downloaded,UnitKB</param>
        /// <param name="nDownLoadSize">Downloaded length,UnitKB</param>
        /// <returns>true:success;false:failure</returns>
        public static bool NETGetDownloadPos(int lFileHandle, out int nTotalSize, out int nDownLoadSize)
        {
            bool blnReturnValue = false;
            blnReturnValue = CLIENT_GetDownloadPos(lFileHandle, out nTotalSize, out  nDownLoadSize);
            NETThrowLastError();
            return blnReturnValue;
        }

        #endregion

        #region << Video capture >>

        /// <summary>
        /// Save the picture,Capture images instantly on the display,Only parameter function effectively hWnd parameter of the function of the image acquired before the effective opening,Otherwise meaningless
        /// </summary>
        /// <param name="hPlayHandle">CLIENT_RealPlay return value</param>
        /// <param name="pchPicFileName">Bitmap file name,Currently only supports BMP bitmap </param>
        /// <returns>true:succcess;false:failure</returns>
        public static bool NETCapturePicture(int lPlayHandle, string phPicFileName)
        { 
            return CLIENT_CapturePicture(lPlayHandle,phPicFileName);
        }

        #endregion

        #region <<Intelligent traffic increased interface>>

        /// <summary>
        /// The new version--Equipment used inside information to take command function
        /// </summary>
        /// <param name="lLoginID">Equipment User LoginID:CLIENT_Loginreturn value</param>
        /// <param name="lChannel">Channel number</param>
        /// <param name="dwCommand">Preparation of command</param>
        /// <param name="obj">objectObject</param>
        /// <param name="typeName">Type Name</param>
        /// <param name="nRuleSize">
        ///     CFG_CMD_ANALYSERULEtis type will use,Other default is set to 0,ShowCFG_ANALYSERULES_INFO
        ///     This data structure is a pointer to the allocated memory size,
        /// </param>
        /// <param name="waittime">Wait Time</param>
        /// <returns>true:success;false:failure</returns>
        public static bool NETGetNewDevConfig(int lLoginID, int lChannel, string strCommand, ref object obj, Type typeName, int nRuleSize, int waittime)
        {
            bool returnValue = false;
            IntPtr pInBuf = IntPtr.Zero;
            IntPtr pOutBuf = IntPtr.Zero;
            IntPtr pRetLen = IntPtr.Zero;

            UInt32 nRetLen = 0;
            UInt32 nBufSize = 32 * 1024;
            UInt32 nError = 0;

            try
            {
                // Allocation of fixed specified the size of the memory space
                pInBuf = Marshal.AllocHGlobal((int)nBufSize);
                pOutBuf = Marshal.AllocHGlobal(Marshal.SizeOf(typeName));
                pRetLen = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(UInt32)));
                
                // CFG_ANALYSERULES_INFOThere are pointers to the data structure,To assign a separate space
                if (strCommand.CompareTo(NETClient.CFG_CMD_ANALYSERULE) == 0)
                {
                    CFG_ANALYSERULES_INFO resultInfo = new CFG_ANALYSERULES_INFO();
                    resultInfo.pRuleBuf = Marshal.AllocHGlobal((int)nRuleSize); 
                    resultInfo.nRuleLen = nRuleSize;
                    Marshal.StructureToPtr(resultInfo, pOutBuf, true);
                }
                else if (strCommand.CompareTo(NETClient.CFG_CMD_RECORDMODE) == 0)
                {
                    AV_CFG_RecordMode resultInfo = new AV_CFG_RecordMode();
                    resultInfo.nStructSize = Marshal.SizeOf(typeof(AV_CFG_RecordMode));
                    Marshal.StructureToPtr(resultInfo, pOutBuf, true);
                }
                else if( strCommand.CompareTo(NETClient.CFG_CMD_MONITORWALL) == 0)
                {
                    Marshal.StructureToPtr(obj , pOutBuf , true);
                }

                if (pInBuf != IntPtr.Zero && pOutBuf != IntPtr.Zero)
                {
                    returnValue = CLIENT_GetNewDevConfig(lLoginID, strCommand, lChannel, pInBuf,
                                                         nBufSize, ref nError, waittime);
                    VIDEOThrowLastError(returnValue);
                    if (returnValue == true)
                    {
                        if (CLIENT_ParseData(strCommand, pInBuf, pOutBuf, (UInt32)Marshal.SizeOf(typeName), pRetLen))
                        {
                            nRetLen = (UInt32)Marshal.PtrToStructure((IntPtr)((UInt32)pRetLen), typeof(UInt32));
                            obj = Marshal.PtrToStructure((IntPtr)((UInt32)pOutBuf), typeName);
                        }
                    }
                }
                VIDEOThrowLastError(returnValue);
            }
            catch (Exception e)
            {
                VIDEOThrowLastError(e);
                returnValue = false;
            }
            finally
            {
                Marshal.FreeHGlobal(pInBuf);//Release the fixed memory allocation
                Marshal.FreeHGlobal(pOutBuf);//Release the fixed memory allocation
                Marshal.FreeHGlobal(pRetLen);//Release the fixed memory allocation
                
                pInBuf = IntPtr.Zero;
                pOutBuf = IntPtr.Zero;
                pRetLen = IntPtr.Zero;
            }
            return returnValue;
        }

        /// <summary>
        /// new version--Set the device information for internal use command function
        /// </summary>
        /// <param name="lLoginID">Equipment User LoginID:CLIENT_Login return value</param>
        /// <param name="dwCommand">Preparation of command</param>
        /// <param name="objArray">objectObject array</param>
        /// <param name="typeName">Type Name</param>
        /// <param name="waittime">Wait Time</param>
        /// <returns>true:success;false:failure</returns>
        public static bool NETSetNewDevConfig(int lLoginID,  string strCommand, object[] objArray, Type typeName, int waittime)
        {
            bool returnValue = false;
            IntPtr pInBuf = IntPtr.Zero;
            IntPtr pOutBuf = IntPtr.Zero;

            UInt32 nBufSize = 32 * 1024;
            UInt32 nRestart = 0;
            UInt32 nError = 0;

            try
            {
                pInBuf = Marshal.AllocHGlobal(objArray.Length * Marshal.SizeOf(typeName));
                pOutBuf = Marshal.AllocHGlobal((int)nBufSize);

                for (UInt32 i = 0; i < (UInt32)objArray.Length; i++)
                {
                    Marshal.StructureToPtr(objArray[i], (IntPtr)((UInt32)pInBuf + i * (UInt32)Marshal.SizeOf(typeName)), true);
                }
                returnValue = CLIENT_PacketData(strCommand, pInBuf, (UInt32)objArray.Length * (UInt32)Marshal.SizeOf(typeName), pOutBuf, nBufSize);
                VIDEOThrowLastError(returnValue);

                if (returnValue)
                {
                    returnValue = CLIENT_SetNewDevConfig(lLoginID, strCommand, -1, pOutBuf,
                                     nBufSize, ref nError, ref nRestart, waittime);
                    VIDEOThrowLastError(returnValue);
                }
            }
            catch (Exception e)
            {
                VIDEOThrowLastError(e);
                returnValue = false;
            }
            finally
            {
                Marshal.FreeHGlobal(pInBuf);//Release fixed memory allocation
                Marshal.FreeHGlobal(pOutBuf);//Release fixed memory allocation
                pInBuf = IntPtr.Zero;
                pOutBuf = IntPtr.Zero;
            }
            return returnValue;
        }



        /// <summary>
        /// new version--Set the device information for internal use command function
        /// </summary>
        /// <param name="lLoginID">Equipment User LoginID:CLIENT_Login return value</param>
        /// <param name="lChannel">Channel number</param>
        /// <param name="dwCommand">Preparation of command</param>
        /// <param name="obj">objectObject</param>
        /// <param name="typeName">Type Name</param>
        /// <param name="waittime">Wait Time</param>
        /// <returns>true:success;false:failure</returns>
        public static bool NETSetNewDevConfig(int lLoginID, int lChannel, string strCommand, object obj, Type typeName, int waittime)
        {
            bool returnValue = false;
            IntPtr pInBuf = IntPtr.Zero;
            IntPtr pOutBuf = IntPtr.Zero;

            UInt32 nBufSize = 32 * 1024;
            UInt32 nRestart = 0;
            UInt32 nError = 0;

            try
            {
                pInBuf = Marshal.AllocHGlobal(Marshal.SizeOf(typeName));
                pOutBuf = Marshal.AllocHGlobal((int)nBufSize);

                Marshal.StructureToPtr(obj, pInBuf, true);
                returnValue = CLIENT_PacketData(strCommand, pInBuf, (UInt32)Marshal.SizeOf(typeName), pOutBuf, nBufSize);
                VIDEOThrowLastError(returnValue);

                if (returnValue)
                {
                    returnValue = CLIENT_SetNewDevConfig(lLoginID, strCommand, lChannel, pOutBuf,
                                     nBufSize, ref nError, ref nRestart, waittime);
                    VIDEOThrowLastError(returnValue);
                }
            }
            catch (Exception e)
            {
                VIDEOThrowLastError(e);
                returnValue = false;
            }
            finally
            {
                Marshal.FreeHGlobal(pInBuf);//Release fixed memory allocation
                Marshal.FreeHGlobal(pOutBuf);//Release fixed memory allocation
                pInBuf = IntPtr.Zero;
                pOutBuf = IntPtr.Zero;
            }
            return returnValue;
        }

        /// <summary>
        /// The new system is the ability to query interface,Ability information inquiry system(In Json format, see the specific configuration SDK)
        /// </summary>
        /// <param name="lLoginID">CLIENT_Login return value</param>
        /// <param name="szCommand"></param>
        /// <param name="nChannelID">Channel number</param>
        /// <param name="szOutBuffer">Output Buffer</param>
        /// <param name="dwOutBufferSize">Output buffer size</param>
        /// <param name="error">Error code</param>
        /// <param name="waittime">Wait timeout,The default setting is 1000</param>
        /// <returns></returns>
        public static bool NETQueryNewSystemInfo(Int32 lLoginID, Int32 lChannel, string strCommand, ref object obj, Type typeName, int waittime)
        {
            bool returnValue = false;
            IntPtr pInBuf = IntPtr.Zero;
            IntPtr pOutBuf = IntPtr.Zero;
            IntPtr pRetLen = IntPtr.Zero;

            UInt32 nRetLen = 0;
            UInt32 nBufSize = 1024 * 1024;
            UInt32 nError = 0;

            try
            {
                pInBuf = Marshal.AllocHGlobal((int)nBufSize);//Allocation of fixed specified the size of the memory space
                pOutBuf = Marshal.AllocHGlobal(Marshal.SizeOf(typeName));

                pRetLen = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(UInt32)));

                if (pInBuf != IntPtr.Zero && pOutBuf != IntPtr.Zero)
                {
                    returnValue = CLIENT_QueryNewSystemInfo(lLoginID, strCommand, lChannel, pInBuf,
                                                         nBufSize, ref nError, waittime);
                    VIDEOThrowLastError(returnValue);
                    if (returnValue == true)
                    {
                        returnValue = CLIENT_ParseData(strCommand, pInBuf, pOutBuf, (UInt32)Marshal.SizeOf(typeName), pRetLen);
                        nRetLen = (UInt32)Marshal.PtrToStructure((IntPtr)((UInt32)pRetLen), typeof(UInt32));
                        obj = Marshal.PtrToStructure((IntPtr)((UInt32)pOutBuf), typeName);
                    }
                }
                VIDEOThrowLastError(returnValue);
            }
            catch (Exception e)
            {
                VIDEOThrowLastError(e);
                returnValue = false;
            }
            finally
            {
                Marshal.FreeHGlobal(pInBuf);//Release fixed memory allocation
                Marshal.FreeHGlobal(pOutBuf);//Release fixed memory allocation
                Marshal.FreeHGlobal(pRetLen);//Release fixed memory allocation
                pInBuf = IntPtr.Zero;
                pOutBuf = IntPtr.Zero;
                pRetLen = IntPtr.Zero;
            }
            return returnValue;
        }

        /// <summary>
        /// Real-time intelligent analysis of data uploaded - Pictures
        /// </summary>
        /// <param name="lLoginID">CLIENT_Loginreturn value</param>
        /// <param name="nChannelID">Channel number</param>
        /// <param name="dwAlarmType">Type</param>
        /// <param name="cbAnalyzerData">Analysis of the data callback</param>
        /// <param name="dwUser">User data</param>
        /// <returns></returns>
        public static Int32 NETRealLoadPicture(Int32 lLoginID, Int32 nChannelID, UInt32 dwAlarmType, fAnalyzerDataCallBack cbAnalyzerData, UInt32 dwUser)
        {
            Int32 nReturn = 0;
            try
            {
                nReturn = CLIENT_RealLoadPicture(lLoginID, nChannelID, dwAlarmType, cbAnalyzerData, dwUser);
                VIDEOThrowLastError(nReturn);
            }
            catch (System.Exception ex)
            {
                VIDEOThrowLastError(ex);
                nReturn = 0;
            }

            return nReturn;
        }

        /// <summary>
        /// Real-time intelligent analysis of data uploaded - Pictures(Extended Interface,bNeedPicFileIndicates whether or not to subscribe to image files,ReservedTypeRESERVED_PARA) 
        /// </summary>
        /// <param name="lLoginID">CLIENT_Loginreturn value</param>
        /// <param name="nChannelID">Channel number</param>
        /// <param name="dwAlarmType">Type</param>
        /// <param name="cbAnalyzerData">Analysis of the data callback</param>
        /// <param name="dwUser">User data</param>
        /// <returns></returns>
        public static Int32 NETRealLoadPictureEx(Int32 lLoginID, Int32 nChannelID, UInt32 dwAlarmType, bool bNeedPicFile, fAnalyzerDataCallBack cbAnalyzerData, UInt32 dwUser, IntPtr Reserved)
        {
            Int32 nReturn = 0;
            try
            {
                nReturn = CLIENT_RealLoadPictureEx(lLoginID, nChannelID, dwAlarmType, bNeedPicFile, cbAnalyzerData, dwUser, Reserved);
                VIDEOThrowLastError(nReturn);
            }
            catch (System.Exception ex)
            {
            	VIDEOThrowLastError(ex);
                nReturn = 0;
            }
            return nReturn;
        }

        /// <summary>
        /// Stop uploading intelligent analysis of data - pictures
        /// </summary>
        /// <param name="lAnalyzerHandle">CLIENT_RealLoadPictureExreturn value</param>
        /// <returns></returns>
        public static bool NETStopLoadPic(Int32 lAnalyzerHandle)
        {
            bool bReturn = false;
            try
            {
                bReturn = CLIENT_StopLoadPic(lAnalyzerHandle);
                VIDEOThrowLastError(bReturn);
            }
            catch (System.Exception ex)
            {
            	VIDEOThrowLastError(ex);
                bReturn = false;
            }
            return bReturn;
        }

        /// <summary>
        /// Download designated intelligent analysis of data - pictures
        /// </summary>
        /// <param name="lLoginID">CLIENT_Login的return value</param>
        /// <param name="emType">EM_FILE_QUERY_TYPEEnum values</param>
        /// <param name="lpMediaFileInfo"></param>
        /// <param name="sSavedFileName"></param>
        /// <param name="cbDownLoadPos"></param>
        /// <param name="dwUserData"></param>
        /// <param name="reserved"></param>
        /// <returns></returns>
        public static Int32 NETDownloadMediaFile(Int32 lLoginID, EM_FILE_QUERY_TYPE emType, IntPtr lpMediaFileInfo, string sSavedFileName, fDownLoadPosCallBack cbDownLoadPos, UInt32 dwUserData, IntPtr reserved)
        {
            Int32 nReturn = 0;
            try
            {
                nReturn = CLIENT_DownloadMediaFile(lLoginID, emType, lpMediaFileInfo, sSavedFileName, cbDownLoadPos, dwUserData, reserved);
                VIDEOThrowLastError(nReturn);
            }
            catch (System.Exception ex)
            {
            	VIDEOThrowLastError(ex);
                nReturn = 0;
            }
            return nReturn;
        }

        /// <summary>
        /// Stop downloading data
        /// </summary>
        /// <param name="lFileHandle"></param>
        /// <returns></returns>
        public static bool NETStopDownloadMediaFile(Int32 lFileHandle)
        {
            bool bReturn = false;
            try
            {
                bReturn = CLIENT_StopDownloadMediaFile(lFileHandle);
                VIDEOThrowLastError(bReturn);
            }
            catch (System.Exception ex)
            {
            	VIDEOThrowLastError(ex);
                bReturn = false;
            }
            return bReturn;
        }

        /// <summary>
        /// Set Devcie Mode
        /// </summary>
        /// <param name="lHandle">CLIENT_Login return value</param>
        /// <param name="emType">User Dev Mode</param>
        /// <returns>true:success;false:failure</returns>
        public static bool NETSetDeviceMode(Int32 lLoginID, EM_USEDEV_MODE emMode, IntPtr pValue)
        {
            bool bReturn = false;
            try
            {
                bReturn = CLIENT_SetDeviceMode(lLoginID, emMode, pValue);
                VIDEOThrowLastError(bReturn);
            }
            catch (System.Exception ex)
            {
                VIDEOThrowLastError(ex);
                bReturn = false;
            }

            return bReturn;
        }

        /// <summary>
        /// Start Talk
        /// </summary>
        /// <param name="lHandle">CLIENT_Login return value</param>
        /// <param name="emType">Audio Data Call Back</param>
        /// <param name="dwUser">User data</param>
        /// <returns>Failure to return 0,Successful return talkID</returns>
        public static int NETStartTalkEx(int lLoginID, fAudioDataCallBack pfcb, IntPtr dwUser)
        {
            int nReturn = 0;
            try
            {
                nReturn = CLIENT_StartTalkEx(lLoginID, pfcb, dwUser);
            }
            catch (System.Exception ex)
            {
                VIDEOThrowLastError(ex);
                nReturn = 0;
            }
            return nReturn;
        }
        /// <summary>
        /// Stop Talk
        /// </summary>
        /// <param name="lTalkHandle">CLIENT_StartTalkEx return value</param>
        /// <returns>Failure to return false,Successful return true</returns>
        public static bool NETStopTalkEx(int lTalkHandle)
        {
            bool bReturn = false;
            try
            {
                bReturn = CLIENT_StopTalkEx(lTalkHandle);
            }
            catch (System.Exception ex)
            {
                VIDEOThrowLastError(ex);
                bReturn = false;
            }
            return bReturn;
        }
        /// <summary>
        /// Send Audio Data To Devcie 
        /// </summary>
        /// <param name="lTalkHandle">CLIENT_StartTalkEx return value</param>
        /// <param name="pSendBuf">Audio Data Buffer</param>
        /// <param name="dwBufSize">Buffsiez</param>
        /// <returns>Send Data Length</returns>
        public static int NETTalkSendData(int lTalkHandle, byte[] pSendBuf, int dwBufSize)
        {
            int nReturn = 0;
            try
            {
                nReturn = CLIENT_TalkSendData(lTalkHandle, pSendBuf, dwBufSize);
            }
            catch (System.Exception ex)
            {
                VIDEOThrowLastError(ex);
                nReturn = 0;
            }
            return nReturn;
        }
            
        /// <summary>
        /// Device Control
        /// </summary>
        /// <param name="lLoginID">CLIENT_Loginreturn value</param>
        /// <param name="type">CtrlTypeEnumerate</param>
        /// <param name="param"></param>
        /// <param name="waittime">Timeout waiting,The default setting1000</param>
        /// <returns></returns>
        public static bool NETControlDevice(Int32 lLoginID, CtrlType type, IntPtr param, Int32 waittime)
        {
            bool bReturn = false;
            try
            {
                bReturn = CLIENT_ControlDevice(lLoginID, type, param, waittime);
                VIDEOThrowLastError(bReturn);
            }
            catch (System.Exception ex)
            {
            	VIDEOThrowLastError(ex);
                bReturn = false;
            }

            return bReturn;
        }

        /// <summary>
        /// Configuration information to resolve queries
        /// </summary>
        /// <param name="szCommand">Command parameters,See the developer documentation</param>
        /// <param name="szInBuffer">Input Buffer,Character buffer configuration</param>
        /// <param name="lpOutBuffer">Output Buffer,Structure types can refer to the table</param>
        /// <param name="dwOutBufferSize">Size of the output buffer</param>
        /// <param name="pReserved">Retention parameters</param>
        /// <returns></returns>
        public static bool NETParseData(string szCommand, IntPtr szInBuffer, IntPtr lpOutBuffer, UInt32 dwOutBufferSize, IntPtr pReserved)
        {
            bool bReturn = false;
            try
            {
                bReturn = CLIENT_ParseData(szCommand, szInBuffer, lpOutBuffer, dwOutBufferSize, pReserved);
                VIDEOThrowLastError(bReturn);
            }
            catch (System.Exception ex)
            {
            	VIDEOThrowLastError(ex);
                bReturn = false;
            }
            return bReturn;
        }


        /// <summary>
        /// Will need to set the configuration information,Packaged into a string format
        /// </summary>
        /// <param name="szCommand">Command parameters,see CLIENT_ParseData table</param>
        /// <param name="lpInBuffer">Input Buffer,See structure typeCLIENT_ParseData table</param>
        /// <param name="dwInBufferSize">Input Buffer Size</param>
        /// <param name="szOutBuffer">Output Buffer</param>
        /// <param name="dwOutBufferSize">Output buffer size</param>
        /// <returns></returns>
        public static bool NETPacketData(string szCommand, IntPtr lpInBuffer, UInt32 dwInBufferSize, IntPtr szOutBuffer, UInt32 dwOutBufferSize)
        {
            bool bReturn = false;
            try
            {
                bReturn = CLIENT_PacketData(szCommand, lpInBuffer, dwInBufferSize, szOutBuffer, dwOutBufferSize);
                VIDEOThrowLastError(bReturn);
            }
            catch (System.Exception ex)
            {
            	VIDEOThrowLastError(ex);
                bReturn = false;
            }
            return bReturn;
        }

        /// <summary>
        /// According to the query conditions query file
        /// </summary>
        /// <param name="lLoginID">CLIENT_Loginreturn value</param>
        /// <param name="emType">mediaFile query </param>
        /// <param name="pQueryCondition">query condition </param>
        /// <param name="reserved">Reserved bytes</param>
        /// <param name="waittime">Wait Time</param>
        /// <returns></returns>
        public static Int32 NETFindFileEx(Int32 lLoginID, EM_FILE_QUERY_TYPE emType, IntPtr pQueryCondition, IntPtr reserved, Int32 waittime)
        {
            Int32 nReturn = 0;
            try
            {
                nReturn = CLIENT_FindFileEx(lLoginID, emType, pQueryCondition, reserved, waittime);
                VIDEOThrowLastError(nReturn);
            }
            catch (System.Exception ex)
            {
            	VIDEOThrowLastError(ex);
                nReturn = 0;
            }
            return nReturn;
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="lFindHandle">CLIENT_FindFileEx return value</param>
        /// <param name="nFilecount">The number of queries needed</param>
        /// <param name="pMediaFileInfo">Documentation buffer,Query for output media files to record</param>
        /// <param name="maxlen">The maximum buffer length</param>
        /// <param name="reserved">Reserved bytes</param>
        /// <param name="waittime">Wait Time</param>
        /// <returns></returns>
        public static Int32 NETFindNextFileEx(Int32 lFindHandle, Int32 nFilecount, IntPtr pMediaFileInfo, Int32 maxlen, IntPtr reserved, Int32 waittime)
        {
            Int32 nReturn = 0;
            try
            {
                nReturn = CLIENT_FindNextFileEx(lFindHandle, nFilecount, pMediaFileInfo, maxlen, reserved, waittime);
                VIDEOThrowLastError(nReturn);
            }
            catch (System.Exception ex)
            {
                VIDEOThrowLastError(ex);
                nReturn = 0;
            }
            return nReturn;
        }

        /// <summary>
        /// Close the query handle
        /// </summary>
        /// <param name="lFindHandle">CLIENT_FindFileEx return value</param>
        /// <returns></returns>
        public static bool NETFindCloseEx(Int32 lFindHandle)
        {
            bool bReturn = false;
            try
            {
                bReturn = CLIENT_FindCloseEx(lFindHandle);
                VIDEOThrowLastError(bReturn);
            }
            catch (System.Exception ex)
            {
            	VIDEOThrowLastError(ex);
                bReturn = false;
            }
            return bReturn;
        }

        /// <summary>
        /// Query System Information,Different messages have different data structures
        /// </summary>
        /// <param name="lLoginID">Equipment User LoginID:CLIENT_Login return value</param>
        /// <param name="nSystemType">The type of query to the system
        ///  0		General Information
        ///  1		Query device attribute information
        ///  2		Check the hard disk information
        ///  3		Query File System Information
        ///  4		Video attribute information
        ///  5		Charset attribute information inquiry system
        ///  6		Optical storage device information query
        ///  7		Get the serial number of the device
        /// </param>
        /// <param name="pSysInfoBuffer">Protocol buffers received</param>
        /// <param name="maxlen">Agreement received buffer length,(In bytes)</param>
        /// <param name="nSysInfolen">The total number of bytes received,(In bytes).</param>
        /// <param name="waittime">Wait Time</param>
        /// <returns>true:success;false:failure</returns>
        public static bool NETQuerySystemInfo(Int32 lLoginID, NET_SYS_ABILITY nSystemType, IntPtr pSysInfoBuffer, Int32 maxlen, ref  Int32 nSysInfolen, Int32 waittime)
        {
            bool bReturn = false;
            try
            {
                bReturn = CLIENT_QuerySystemInfo(lLoginID, (int)nSystemType, pSysInfoBuffer, maxlen, ref nSysInfolen, waittime);
                VIDEOThrowLastError(bReturn);
            }
            catch (System.Exception )
            {
                VIDEOThrowLastError(bReturn);
                bReturn = false;
            }
            return bReturn;
        }


        public static bool NETQueryDevState(int lLoginID, int nType, IntPtr pBuf, int nBufLen, ref int pRetLen, int waittime)
        {
             bool bReturn = false;
            try
            {
                bReturn = CLIENT_QueryDevState(lLoginID, nType, pBuf, nBufLen, ref pRetLen, waittime);
                VIDEOThrowLastError(bReturn);
            }
            catch (System.Exception)
            {
                VIDEOThrowLastError(bReturn);
                bReturn = false;
            }
            return bReturn;
        }


        public static bool NETSnapPicture(Int32 lLoginID, SNAP_PARAMS par)
        {
            
            bool bReturn = false;
            try
            {
                bReturn = CLIENT_SnapPicture(lLoginID, par);
                VIDEOThrowLastError(bReturn);
            }
            catch (System.Exception)
            {
                VIDEOThrowLastError(bReturn);
                bReturn = false;
            }
            return bReturn;
        }

        public static void NETSetSnapRevCallBack(fSnapRev OnSnapRevMessage, Int32 dwUser)
        {
            CLIENT_SetSnapRevCallBack(OnSnapRevMessage, dwUser);
        }
        //CLIENT_API void CALL_METHOD CLIENT_SetSnapRevCallBack(fSnapRev OnSnapRevMessage, DWORD dwUser);


        public static Int32 NETStartSearchDevices(fSearchDevicesCB cbSearchDevices, IntPtr pUserData, IntPtr szLocalIp)
        {
            return CLIENT_StartSearchDevices(cbSearchDevices, pUserData, szLocalIp);
        }

        public static bool NETStopSearchDevices(Int32 lSearchHandle)
        {
            return CLIENT_StopSearchDevices(lSearchHandle);
        }


        #endregion

        #region <<Monitor Wall>>

        /// <summary>
        /// Load Monitor Wall Plan
        /// </summary>
        /// <param name="lLoginID">CLIENT_Login return value</param>
        /// <param name="pInParam">In Param , type = NET_IN_WM_LOAD_COLLECTION </param>
        /// <param name="pOutParam">Out Param , type = NET_OUT_WM_LOAD_COLLECTION</param>
        /// <param name="waittime">Wait Time</param>
        /// <returns></returns>
        public static bool NETLoadMonitorWallCollection(Int32 lLoginID, IntPtr pInParam, IntPtr pOutParam, Int32 waittime)
        {
            bool returnValue = CLIENT_LoadMonitorWallCollection(lLoginID, pInParam, pOutParam , waittime);
            NETThrowLastError(returnValue);
            return returnValue;
        }

        /// <summary>
        /// Save Monitor Wall Plan
        /// </summary>
        /// <param name="lLoginID">CLIENT_Login return value</param>
        /// <param name="pInParam">In Param , type = NET_IN_WM_SAVE_COLLECTION </param>
        /// <param name="pOutParam">Out Param , type = NET_OUT_WM_LOAD_COLLECTION</param>
        /// <param name="waittime">Wait Time</param>
        /// <returns></returns>
        public static  bool NETSaveMonitorWallCollection(Int32 lLoginID, IntPtr pInParam, IntPtr pOutParam, Int32 waittime)
        {
            bool returnValue = CLIENT_SaveMonitorWallCollection(lLoginID, pInParam, pOutParam, waittime);
            NETThrowLastError(returnValue);
            return returnValue;
        }

        #endregion

        #region << Equipment upgrades >>

        /// <summary>
        /// Start the upgrade
        /// </summary>
        public static Int32 NETCLIENT_StartUpgradeEx(Int32 lLoginID, EM_UPGRADE_TYPE emType, string pchFileName, fUpgradeCallBack cbUpgrade, UInt32 dwUser)
        {
            Int32 nErr = CLIENT_StartUpgradeEx(lLoginID, emType, pchFileName, cbUpgrade, dwUser);
            Int32 errorCode = CLIENT_GetLastError();
            return nErr;
        }

        // <summary>
        /// Sending data
        /// </summary>
        public static bool NETCLIENT_SendUpgrade(Int32 lUpgradeID)
        {
            return CLIENT_SendUpgrade(lUpgradeID);
        }


        // <summary>
        /// End upgrade equipment program
        /// </summary>
        public static bool NETCLIENT_StopUpgrade(Int32 lUpgradeID)
        {
            return CLIENT_StopUpgrade(lUpgradeID);
        }

        // <summary>
        /// Query TransCom Info
        /// <param name="TransComType">2 hight bites means coms number , 2 low  bites means coms type(0：232，1:485) </param>
        /// </summary>
        public static bool  NETQueryTransComParams(int lLoginID, int TransComType, out NET_COMM_STATE pCommState, int nWaitTime)
        {
            if (nWaitTime <= 0)
            {
                nWaitTime = 1000;
            }
            return  CLIENT_QueryTransComParams(lLoginID, TransComType, out pCommState, nWaitTime);
        }

        // <summary>
        /// Query TransCom Info
        /// <param name="TransComType">2 hight bites means coms number , 2 low  bites means coms type(0：232，1:485) </param>
        /// </summary>
        public static int NETCreateTransComChannel(int lLoginID, int TransComType, uint baudrate, uint databits, uint stopbits, 
                                                        uint parity, fTransComCallBack cbTransCom, IntPtr dwUser)
        {
            return  CLIENT_CreateTransComChannel(lLoginID, TransComType, baudrate, databits, stopbits, parity, cbTransCom,  dwUser);
        }

        // <summary>
        /// Send Data To Transcom Channel
        /// </summary>
        public static bool NetSendTransComData(int lTransComChannel, string pBuffer, int dwBufSize)
        {
            return  CLIENT_SendTransComData(lTransComChannel, pBuffer, dwBufSize);
        }

        // <summary>
        /// Destroy Transcom Channel
        /// </summary>
        public static bool NetDestroyTransComChannel(int lTransComChannel)
        {
            return CLIENT_DestroyTransComChannel(lTransComChannel);
        }

#endregion

        #endregion

        #endregion

        #region << Public function >>

        /// <summary>
        /// WindowsSystem standard time format to a custom format
        /// </summary>
        /// <param name="dateTime">System Time Object</param>
        /// <returns>From time to time format of data definition</returns>
        private static NET_TIME ToNetTime(DateTime dateTime)
        {
            NET_TIME result = new NET_TIME();
            result.dwYear = dateTime.Year;
            result.dwMonth = dateTime.Month;
            result.dwDay = dateTime.Day;
            result.dwHour = dateTime.Hour;
            result.dwMinute = dateTime.Minute;
            result.dwSecond = dateTime.Second;
            return result;
        }
		
        /// <summary>
        /// a custom format to WindowsSystem standard time format
        /// </summary>
        /// <param name="netTime">custom format time</param>
        /// <returns>System Time Object</returns>
        private static DateTime ToDateTime(NET_TIME netTime)
        {
            try
            {
                return new DateTime(netTime.dwYear, netTime.dwMonth, netTime.dwDay,
                     netTime.dwHour, netTime.dwMinute, netTime.dwSecond);
            }
            catch
            {
                return DateTime.Now;
            }
        }

        /// <summary>
        ///Special column type UInt32 value converted to the specified format
        /// </summary>
        /// <param name="formatStyle">
        /// Format parameters:
        /// yyyy Represents the date year(4);yy Represents the date year(2);
        /// mRepresents the date month(Automatic);mm Represents the date month(2);
        /// dRepresents the date day(Automatic);ddRepresents the date day(2);
        /// p1 represents first portion of the IP address;p2represents second portion of the IP address;p3 represents third portion of the IP address;represents fourth portion of the IP address;
        /// v1represents the first part of the version number;v2 represents the second part of the version number;[The version number format:The major version number.Minor version number]
        /// vs1represents the first part of the version number;vs2represents the second part of the version number;vs3represents the third part of the version number;vs4represents the fourth part of the version number;[The version number format:x.x.x.x]
        /// </param>
        /// <returns></returns>
        public static string NETUInt32ToString(UInt32 intValue,string formatStyle)
        {
            //Convert hexadecimal values       
            string valueString = intValue.ToString("X");
            string strReturn = formatStyle.ToUpper();
            //Format
            string strTemp = "00000000";
            strTemp = strTemp.Remove(0, valueString.Length) + valueString;
            string strPart1 = strTemp.Substring(0, 2);
            string strPart2 = strTemp.Substring(2, 2);
            string strPart3 = strTemp.Substring(4, 2);
            string strPart4 = strTemp.Substring(6, 2);
            //Years of the date of treatment
            if (strReturn.IndexOf("YYYY") != -1)
            {
                strReturn = strReturn.Replace("YYYY", int.Parse(strPart1 + strPart2, System.Globalization.NumberStyles.AllowHexSpecifier).ToString());
            }
            if (strReturn.IndexOf("YY") != -1)
            {
                strReturn = strReturn.Replace("YY", (int.Parse(strPart1 + strPart2, System.Globalization.NumberStyles.AllowHexSpecifier) % 100).ToString());
            }
            //Months of the date of treatment
            if (strReturn.IndexOf("MM") != -1)
            {
                int mm = int.Parse(strPart3, System.Globalization.NumberStyles.AllowHexSpecifier);
                strReturn = strReturn.Replace("MM", ((mm>10?mm.ToString():"0"+mm.ToString())));
            }
            if (strReturn.IndexOf("M") != -1)
            {
                strReturn = strReturn.Replace("M", int.Parse(strPart3, System.Globalization.NumberStyles.AllowHexSpecifier).ToString());
            }
            //Days of the date of treatment
            if (strReturn.IndexOf("DD") != -1)
            {
                int dd = int.Parse(strPart4, System.Globalization.NumberStyles.AllowHexSpecifier);
                strReturn = strReturn.Replace("DD", ((dd > 10 ? dd.ToString() : "0" + dd.ToString())));
            }
            if (strReturn.IndexOf("D") != -1)
            {
                strReturn = strReturn.Replace("D", int.Parse(strPart4, System.Globalization.NumberStyles.AllowHexSpecifier).ToString());
            }
            //Processing IP addresses
            if (strReturn.IndexOf("P1") != -1)
            {
                strReturn = strReturn.Replace("P1", int.Parse(strPart1, System.Globalization.NumberStyles.AllowHexSpecifier).ToString());
            }
            if (strReturn.IndexOf("P2") != -1)
            {
                strReturn = strReturn.Replace("P2", int.Parse(strPart2, System.Globalization.NumberStyles.AllowHexSpecifier).ToString());
            }
            if (strReturn.IndexOf("P3") != -1)
            {
                strReturn = strReturn.Replace("P3", int.Parse(strPart1, System.Globalization.NumberStyles.AllowHexSpecifier).ToString());
            }
            if (strReturn.IndexOf("P4") != -1)
            {
                strReturn = strReturn.Replace("P4", int.Parse(strPart1, System.Globalization.NumberStyles.AllowHexSpecifier).ToString());
            }
            //Processing version number[The major version number.Minor version number]
            if (strReturn.IndexOf("V1") != -1)
            {
                strReturn = strReturn.Replace("V1", int.Parse(strPart1 + strPart2, System.Globalization.NumberStyles.AllowHexSpecifier).ToString());
            }
            if (strReturn.IndexOf("V2") != -1)
            {
                strReturn = strReturn.Replace("V2", int.Parse(strPart3 + strPart4, System.Globalization.NumberStyles.AllowHexSpecifier).ToString());
            }
            //Processing version number[X.X.X.X]
            if (strReturn.IndexOf("VS1") != -1)
            {
                strReturn = strReturn.Replace("VS1", int.Parse(strPart1, System.Globalization.NumberStyles.AllowHexSpecifier).ToString());
            }
            if (strReturn.IndexOf("VS2") != -1)
            {
                strReturn = strReturn.Replace("VS2", int.Parse(strPart2, System.Globalization.NumberStyles.AllowHexSpecifier).ToString());
            }
            if (strReturn.IndexOf("VS3") != -1)
            {
                strReturn = strReturn.Replace("VS3", int.Parse(strPart1, System.Globalization.NumberStyles.AllowHexSpecifier).ToString());
            }
            if (strReturn.IndexOf("VS4") != -1)
            {
                strReturn = strReturn.Replace("VS4", int.Parse(strPart1, System.Globalization.NumberStyles.AllowHexSpecifier).ToString());
            }
            return strReturn;
        }

        /// <summary>
        /// Character array is converted to a string
        /// </summary>
        /// <param name="charValue">Character array</param>
        /// <returns>String</returns>
        public static string NETByteArrayToString(byte[] byteArray)
        {
            //string result = Encoding.GetEncoding("gb2312").GetString(byteArray);
            //string result = Encoding.GetEncoding(936).GetString(byteArray);
            string result = pEncoding.GetString(byteArray);
            return result;
        }

        /// <summary>
        /// Character array is converted to a string[Applies only to character data of length 16 character array objects]
        /// </summary>
        /// <param name="charValue">Character array</param>
        /// <param name="formatStyle">String format[Not case-sensitive] IP1:The first part of the IP address;IP2:The second part of the IP address;IP3:The third part of the IP address;IP4:The fourth part of the IP address</param>
        /// <returns>String</returns>
        public static string NETByteArrayToString(byte[] byteArray,string formatStyle)
        {
            //string result = Encoding.GetEncoding("gb2312").GetString(byteArray);
            //string result = Encoding.GetEncoding(936).GetString(byteArray);
            string result = pEncoding.GetString(byteArray);
            if (result.Length == 16)
            {
                string sPart1 = result.Substring(0, 4);
                string sPart2 = result.Substring(4, 4);
                string sPart3 = result.Substring(8, 4);
                string sPart4 = result.Substring(12, 4);
                string strTemp = formatStyle.ToUpper();
                //IP address format processing
                if (strTemp.IndexOf("IP1")!=-1)
                {
                    strTemp = strTemp.Replace("IP1", int.Parse(sPart1).ToString());
                }
                if (strTemp.IndexOf("IP2") != -1)
                {
                    strTemp = strTemp.Replace("IP2", int.Parse(sPart2).ToString());
                }
                if (strTemp.IndexOf("IP3") != -1)
                {
                    strTemp = strTemp.Replace("IP3", int.Parse(sPart3).ToString());
                }
                if (strTemp.IndexOf("IP4") != -1)
                {
                    strTemp = strTemp.Replace("IP4", int.Parse(sPart4).ToString());
                }
                result = strTemp;
            }
            return result;
        }


        /// <summary>
        /// Convert a string to a character array
        /// </summary>
        /// <param name="strValue"></param>
        /// <returns></returns>
        public static bool NETStringToByteArry(string strValue,ref byte[] byteArry)
        {
            try
            {
                //byte[] byteTemp = Encoding.GetEncoding("gb2312").GetBytes(strValue);
                byte[] byteTemp = pEncoding.GetBytes(strValue);
                int maxLen=(byteTemp.Length>byteArry.Length?byteArry.Length:byteTemp.Length);
                for (int i = 0; i < byteArry.Length; i++)
                {
                    if (i < maxLen)
                    {
                        byteArry[i] = byteTemp[i];
                    }
                    else
                    {
                        byteArry[i] = new byte();
                    }
                }
                    return true;
            }
            catch
            {
                return false;
            }
        }

        /// <summary>
        /// SDK throws an exception if the call fails,No exception information return on success,And to assign operational informationLastOperationInfo
        /// </summary>
        /// <exception cref="Win32Exception">Digital video recorders native exception,When the SDK call fails to trigger</exception>
        private static void VIDEOThrowLastError()
        {
            Int32 errorCode = CLIENT_GetLastError();
            if (errorCode != 0)
            {
                pErrInfo.errCode = errorCode.ToString();
                pErrInfo.errMessage = VIDEOGetLastErrorName((uint)errorCode);
                if (pShowException == true)
                {
                    throw new Win32Exception(errorCode, pErrInfo.errMessage);
                }
            }
            else
            {
                pErrInfo.errCode = "0";
                pErrInfo.errMessage = "Recent operations without exception occurs";
            }
        }

        /// <summary>
        /// Error code conversion error message described as standard equipment
        /// </summary>
        /// <param name="errorCode">Error code</param>
        /// <returns>Standard equipment error message description</returns>
        private static string VIDEOGetLastErrorName(uint errorCode)
        {
            switch (errorCode)
            {
                case 0x80000000 | 1:
                    return "WindowsSystem error";
                case 0x80000000 | 2:
                    return "Network Error,Probably because the network timeout";
                case 0x80000000 | 3:
                    return "Device protocol mismatch";
                case 0x80000000 | 4:
                    return "The handle is invalid";
                case 0x80000000 | 5:
                    return "fail to open channel ";
                case 0x80000000 | 6:
                    return "fail to close channel";
                case 0x80000000 | 7:
                    return "User parameters are not legitimate";
                case 0x80000000 | 8:
                    return "SDK initialization error";
                case 0x80000000 | 9:
                    return "SDK to clean up mistakes";
                case 0x80000000 | 10:
                    return "Application render resource error";
                case 0x80000000 | 11:
                    return "Open the decoding error";
                case 0x800000 | 12:
                    return "Close decoding library error";
                case 0x80000000 | 13:
                    return "Detected in multi-screen preview channel number is 0";
                case 0x80000000 | 14:
                    return "Recording library initialization failed";
                case 0x80000000 | 15:
                    return "Recording Library uninitialized";
                case 0x80000000 | 16:
                    return "error refers to send audio data";
                case 0x80000000 | 17:
                    return "Real-time data is already in a saved state";
                case 0x80000000 | 18:
                    return "Unsaved data in real time";
                case 0x80000000 | 19:
                    return "error refers to open documents";
                case 0x80000000 | 20:
                    return "fail to start PTZ control timer";
                case 0x80000000 | 21:
                    return "error to  return data for validation";
                case 0x80000000 | 22:
                    return "There is not enough cache";
                case 0x80000000 | 23:
                    return "The current SDK does not support this feature";
                case 0x80000000 | 24:
                    return "Can not find the video";
                case 0x80000000 | 25:
                    return "No operating authority";
                case 0x80000000 | 26:
                    return "Temporarily unable to perform";
                case 0x80000000 | 27:
                    return "Intercom channel was not found";
                case 0x80000000 | 28:
                    return "Audio not found";
                case 0x80000000 | 29:
                    return "CLientSDK uninitialized";
                case 0x80000000 | 30:
                    return "Download has ended";
                case 0x80000000 | 31:
                    return "Query result is empty";
                case 0x80000000 | 32:
                    return "Failed to get the configuration location：System Properties";
                case 0x80000000 | 33:
                    return "Failed to get the configuration location：Serial Number";
                case 0x80000000 | 34:
                    return "Failed to get the configuration location：General Properties";
                case 0x80000000 | 35:
                    return "Failed to get the configuration location：DSP capability description";
                case 0x80000000 | 36:
                    return "Failed to get the configuration location：Network Properties";
                case 0x80000000 | 37:
                    return "Failed to get the configuration location：Channel Name";
                case 0x80000000 | 38:
                    return "Failed to get the configuration location：Video Properties";
                case 0x80000000 | 39:
                    return "Failed to get the configuration location：Video Timing Configuration";
                case 0x80000000 | 40:
                    return "Failed to get the configuration location：Decoder protocol name";
                case 0x80000000 | 41:
                    return "Failed to get the configuration location：232 Function Name";
                case 0x80000000 | 42:
                    return "Failed to get the configuration location：Decoder Properties";
                case 0x80000000 | 43:
                    return "Failed to get the configuration location：232 Properties";
                case 0x80000000 | 44:
                    return "Configuration failed to take the position：External alarm input attributes";
                case 0x80000000 | 45:
                    return "Failed to get the configuration location：Image detection alarm attributes";
                case 0x80000000 | 46:
                    return "Failed to get the configuration location：Equipment time";
                case 0x80000000 | 47:
                    return "Failed to get the configuration location：Preview parameters";
                case 0x80000000 | 48:
                    return "Failed to get the configuration location：Configure Automatic Maintenance";
                case 0x80000000 | 49:
                    return "Failed to get the configuration location：Video matrix configurations";
                case 0x80000000 | 55:
                    return "Configuration failed to take the position：General Properties";
                case 0x80000000 | 56:
                    return "Configuration failed to take the position：Network Properties";
                case 0x80000000 | 57:
                    return "Configuration failed to take the position：Channel Name";
                case 0x80000000 | 58:
                    return "Configuration failed to take the position：：Video Properties";
                case 0x80000000 | 59:
                    return "Set Configuration failed position：Video Timing Configuration";
                case 0x80000000 | 60:
                    return "Set Configuration failed position：Decoder properties";
                case 0x80000000 | 61:
                    return "Set Configuration failed position：232 serial interface properties";
                case 0x80000000 | 62:
                    return "Set Configuration failed position：External alarm input attribute";
                case 0x80000000 | 63:
                    return "Set Configuration failed position：Image detection alarm properties";
                case 0x80000000 | 64:
                    return "Set Configuration failed position：Equipment time";
                case 0x80000000 | 65:
                    return "Set Configuration failed position：Preview parameters";
                case 0x80000000 | 66:
                    return "Set Configuration failed position：Configure Automatic Maintenance";
                case 0x80000000 | 67:
                    return "Set Configuration failed position：Video matrix configurations";
                case 0x80000000 | 70:
                    return "Audio encoding interface is not initialized successfully";
                case 0x80000000 | 71:
                    return "Data is too long";
                case 0x80000000 | 72:
                    return "Device does not support this operation";
                case 0x80000000 | 73:
                    return "Inadequate equipment resources";
                case 0x80000000 | 74:
                    return "Server has started";
                case 0x80000000 | 75:
                    return "Server has not been started successfully";
                case 0x80000000 | 80:
                    return "Enter the serial number is incorrect";
                case 0x80000000 | 100:
                    return "The password is incorrect";
                case 0x80000000 | 101:
                    return "Account does not exist";
                case 0x80000000 | 102:
                    return "Login Timeout waiting for return";
                case 0x80000000 | 103:
                    return "Account logged";
                case 0x80000000 | 104:
                    return "Account has been locked";
                case 0x80000000 | 105:
                    return "Account has been blacklisted";
                case 0x80000000 | 106:
                    return "Lack of resources,The system is busy";
                case 0x80000000 | 107:
                    return "fail to connect the host";
                case 0x80000000 | 108:
                    return "Network connection failure";
                case 0x80000000 | 120:
                    return "Render library open audio error";
                case 0x80000000 | 121:
                    return "Render library close audio error";
                case 0x80000000 | 122:
                    return "Render library control volume error";
                case 0x80000000 | 123:
                    return "Render library settings screen parameter error";
                case 0x80000000 | 124:
                    return "Render Gallery pause playback error";
                case 0x80000000 | 125:
                    return "Render library capture error";
                case 0x80000000 | 126:
                    return "Render Library stepping error";
                case 0x80000000 | 127:
                    return "Render library set the frame rate error";
                case 0x80000000 | 999:
                    return "Temporarily unable to set";
                case 0x80000000 | 1000:
                    return "Configuration data is not legitimate";
                default:
                    return "Unknown error";
            }
        }

        private static void VIDEOThrowLastError(int returnValue)
        {
            if (returnValue == 0)
            {
                VIDEOThrowLastError();
            }
            else
            {
                pErrInfo.errCode = "0";
                pErrInfo.errMessage = "Recent operations without exception occurs";
            }
        }

        private static void VIDEOThrowLastError(bool returnValue)
        {
            if (returnValue == false)
            {
                VIDEOThrowLastError();
            }
            else
            {
                pErrInfo.errCode = "0";
                pErrInfo.errMessage = "Recent operations without exception occurs";
            }
        }

        /// <summary>
        /// SDK throws an exception if the call fails
        /// </summary>
        /// <param name="e"></param>
        private static void VIDEOThrowLastError(Exception e)
        {

            pErrInfo.errCode = e.ToString();
            pErrInfo.errMessage = e.Message;
            if (pShowException == true)
            {
                throw e;
            }
        }
        
        #region **IP address is converted to a character array function code[Temporary don't have to use]**

        ///// <summary>
        ///// The IP address into a character array
        ///// </summary>
        ///// <param name="P1">The first part of the IP address</param>
        ///// <param name="P2">The second part of the IP address</param>
        ///// <param name="P3">The third part of the IP address</param>
        ///// <param name="P4">The fourth part of the IP address</param>
        ///// <returns></returns>
        //public static char[] NETIPAddToCharArry(string P1, string P2, string P3, string P4)
        //{
        //    char[] result = new char[16];
        //    string strResult = "";
        //    string strTemp = "0000";
        //    strTemp = strTemp.Remove(0, P1.ToString().Length) + P1.ToString();
        //    strResult+=strTemp;
        //    strTemp = "0000";
        //    strTemp = strTemp.Remove(0, P2.ToString().Length) + P2.ToString();
        //    strResult += strTemp;
        //    strTemp = "0000";
        //    strTemp = strTemp.Remove(0, P3.ToString().Length) + P3.ToString();
        //    strResult += strTemp;
        //    strTemp = "0000";
        //    strTemp = strTemp.Remove(0, P4.ToString().Length) + P4.ToString();
        //    strResult += strTemp;
        //    strResult.CopyTo(0, result, 0, 16);
        //    return result;
        //}

        ///// <summary>
        ///// The IP address of the string into an array of characters
        ///// </summary>
        ///// <param name="IPAdd">IP address string</param>
        ///// <param name="strSprtr">Delimiter</param>
        ///// <returns></returns>
        //public static char[] NETIPAddToCharArry(string IPAdd,char chrSprtr)
        //{
        //    string[] strPart = new string[4];
        //    strPart = IPAdd.Split(chrSprtr);
        //    if (strPart.Length ==4)
        //    {
        //        return NETIPAddToCharArry(strPart[0], strPart[1], strPart[2], strPart[3]);
        //    }
        //    else
        //    {
        //        return new char[16];
        //    }
        //}
        #endregion

        #endregion

        #region << Original SDK calls >>

        /// <summary>
        /// Return the function fails code
        /// </summary>
        /// <returns>Failure code execution</returns>
        [DllImport("dhnetsdk.dll")]
        private static extern Int32 CLIENT_GetLastError();

        /// <summary>
        ///Initialization SDK
        /// </summary>
        /// <param name="cbDisConnect">
        /// Disconnection callback function,See also commissioned<seealso cref="fDisConnect"/>
        /// </param>
        /// <param name="dwUser">User Information</param>
        /// <returns>true:success;false:failure</returns>
        [DllImport("dhnetsdk.dll")]
        private static extern bool CLIENT_Init(fDisConnect cbDisConnect, IntPtr dwUser);

        /// <summary>
        /// Empty SDK, Releases the resources,After calling all SDK functions
        /// </summary>
        [DllImport("dhnetsdk.dll")]
        private static extern void CLIENT_Cleanup();

        /// <summary>
        /// And the device connected to the waiting time set
        /// </summary>
        /// <param name="nWaitTime">Connection waiting time[Unit:Millisecond]</param>
        /// <param name="nTryTimes">connection times</param>
        [DllImport("dhnetsdk.dll")]
        private static extern void CLIENT_SetConnectTime(int nWaitTime, int nTryTimes);

        /// <summary>
        /// Set the device message callback function, Used to obtain information on the current status of the device
        /// </summary>
        /// <param name="cbMessage">Message callback parameter,See  commissioned<seealso cref="fMessCallBack"/></param>
        /// <param name="dwUser">User data</param>
        [DllImport("dhnetsdk.dll")]
        private static extern void CLIENT_SetDVRMessCallBack(fMessCallBack cbMessage, IntPtr dwUser);        

        /// <summary>
        /// Start to subscribe message a equipment,Used to set whether you need to equipment news callback,Get the message callback settings from <seealso cref="CLIENT_SetDVRMessCallBack"/>。
        /// </summary>
        /// <param name="lLoginID">Equipment User LoginID:<seealso cref="CLIENT_Login"/>return value</param>
        /// <returns>true:success;false:failue</returns>
        [DllImport("dhnetsdk.dll")]
        private static extern bool CLIENT_StartListenEx(int lLoginID);

        /// <summary>
        ///  Start to subscribe message a equipment,Whether the equipment is used to set a callback message,Get the message callback settings from<seealso cref="CLIENT_SetDVRMessCallBack"/>。
        /// </summary>
        /// <param name="lLoginID">Equipment User LoginID:<seealso cref="CLIENT_Login"/>return value</param>
        /// <returns>true:success;false:failure</returns>
        [DllImport("dhnetsdk.dll")]
        private static extern bool CLIENT_StartListen(int lLoginID);

        /// <summary>
        /// Stop listening for messages on a device
        /// </summary>
        /// <param name="lLoginID">Equipment User LoginID:<seealso cref="CLIENT_Login"/>return value</param>
        /// <returns>true:success;false:failure</returns>
        [DllImport("dhnetsdk.dll")]
        private static extern bool CLIENT_StopListen(int lLoginID);

        /// <summary>
        /// Start listening service, Currently only realized the alarm monitoring function
        /// </summary>
        /// <param name="wPort">Start listening port</param>
        /// <param name="pIp">BindingIP,The machine is NULL bind all legitimate IP</param>
        /// <param name="pfscb">Message server callback interface</param>
        /// <param name="dwTimeOut">Server maintains the connection timeout</param>
        /// <param name="dwUserData">Custom data user callback</param>
        /// <returns>The successful return of server handles,Failure to return0</returns>
        [DllImport("dhnetsdk.dll")]
        private static extern int CLIENT_StartService(ushort wPort, string pIp, fServiceCallBack pfscb, int dwTimeOut, IntPtr dwUserData);

        /// <summary>
        /// Stop listening service port
        /// </summary>
        /// <param name="lHandle">
        /// To shut down the server handles:<seealso cref="CLIENT_StartService"/>return value</param>
        /// <returns>true:success;false:failure</returns>
        [DllImport("dhnetsdk.dll")]
        private static extern bool CLIENT_StopService(int lHandle);

        public enum EM_USEDEV_MODE
        {
            /// <summary>
            /// Set client style with talk
            /// </summary>
            DH_TALK_CLIENT_MODE = 0,
            /// <summary>
            /// Set server style with talk
            /// </summary>
            DH_TALK_SERVER_MODE,
            /// <summary>
            /// Set code type with talk , pValue is type DHDEV_TALKDECODE_INFO
            /// </summary>
            DH_TALK_ENCODE_TYPE,
            /// <summary>
            /// Set alarm listen mode
            /// </summary> 
            DH_ALARM_LISTEN_MODE, 
            /// <summary>
            /// 
            /// </summary>
            DH_CONFIG_AUTHORITY_MODE,                  
            /// <summary>
            /// Set channel num of talk ,(0~MaxChannel-1)
            /// </summary> 
            DH_TALK_TALK_CHANNEL,                      
            /// <summary>
            /// Set play back stream type(0-Main&Extra stream , 1-Main stream , 2-Extra stream
            /// </summary>
            DH_RECORD_STREAM_TYPE,    
            /// <summary>
            /// Set speak param , pValue is NET_SPEAK_PARAM
            /// </summary>
            DH_TALK_SPEAK_PARAM,          
            /// <summary>
            /// Set file type with playback and download
            /// </summary>
            DH_RECORD_TYPE,                            
            /// <summary>
            /// Set Gen3 talk param
            /// </summary>
            DH_TALK_MODE3,                              
        }
        /// <summary>

        /// <summary>
        /// Set Devcie Mode
        /// </summary>
        /// <param name="lHandle">CLIENT_Login return value</param>
        /// <param name="emType">User Dev Mode</param>
        /// <returns>true:success;false:failure</returns>
        [DllImport("dhnetsdk.dll")]
        private static extern bool CLIENT_SetDeviceMode(int lLoginID, EM_USEDEV_MODE emType, IntPtr pValue);

        /// <summary>
        /// Start Talk
        /// </summary>
        /// <param name="lHandle">CLIENT_Login return value</param>
        /// <param name="emType">Audio Data Call Back</param>
        /// <param name="dwUser">User data</param>
        /// <returns>Failure to return 0,Successful return talkID</returns>
        [DllImport("dhnetsdk.dll")]
        private static extern int CLIENT_StartTalkEx(int lLoginID, fAudioDataCallBack pfcb, IntPtr dwUser);
        /// <summary>
        /// Stop Talk
        /// </summary>
        /// <param name="lTalkHandle">CLIENT_StartTalkEx return value</param>
        /// <returns>Failure to return false,Successful return true</returns>
        [DllImport("dhnetsdk.dll")]
        private static extern bool CLIENT_StopTalkEx(int lTalkHandle);
        /// <summary>
        /// Send Audio Data To Devcie 
        /// </summary>
        /// <param name="lTalkHandle">CLIENT_StartTalkEx return value</param>
        /// <param name="pSendBuf">Audio Data Buffer</param>
        /// <param name="dwBufSize">Buffsiez</param>
        /// <returns>Send Data Length</returns>
        [DllImport("dhnetsdk.dll")]
        private static extern int CLIENT_TalkSendData(int lTalkHandle, byte[] pSendBuf, int dwBufSize);
        /// <summary>
        /// Registered user to the device,When the equipment end user Settings for reuse（The default user equipment such asadmin,Can not be set to reuse）,This account can be used multiple times to register the device
        /// </summary>
        /// <param name="pchDVRIP">EquipmentIP</param>
        /// <param name="wDVRPort">Device Port</param>
        /// <param name="pchUserName">User name</param>
        /// <param name="pchPassword">User password</param>
        /// <param name="lpDeviceInfo">Equipment inflormation,Belongs to the output parameters</param>
        /// <param name="error">Return to login error code</param>
        /// <returns>Failure to return0,Successful return equipmentID</returns>
        [DllImport("dhnetsdk.dll")]
        private static extern int CLIENT_Login(string pchDVRIP, ushort wDVRPort, string pchUserName, string pchPassword, out NET_DEVICEINFO lpDeviceInfo, out int error);

        /// <summary>
        /// Registered user interface device to expand,Supports a user-specified device's ability to support
        /// </summary>
        /// <param name="pchDVRIP">EquipmentIP</param>
        /// <param name="wDVRPort">Device Port</param>
        /// <param name="pchUserName">User name</param>
        /// <param name="pchPassword">User password</param>
        /// <param name="nSpecCap">Ability to support device,User login value of 2 indicates actively listening mode。[Car dvr Login]</param>
        /// <param name="pCapParam">Supplementary parameter for nSpecCap, nSpecCap = 2时,pCapParamFill the device serial number string。Car dvr Login]</param>
        /// <param name="lpDeviceInfo">Device information, are output parameters</param>
        /// <param name="error">Return to login error code</param>
        /// <returns>Failure to return0,Successful return equipmentID</returns>
        [DllImport("dhnetsdk.dll")]
        private static extern int CLIENT_LoginEx(string pchDVRIP, ushort wDVRPort, string pchUserName, string pchPassword, int nSpecCap, string pCapParam, out NET_DEVICEINFO lpDeviceInfo, out int error);

        /// <summary>
        /// Cancellation device users
        /// </summary>
        /// <param name="lLoginID">Equipment User LoginID:<seealso cref="CLIENT_Login"/>return value</param>
        /// <returns>true:success;false:failure</returns>
        [DllImport("dhnetsdk.dll")]
        private static extern bool CLIENT_Logout(int lLoginID);

        /// <summary>
        /// Start real-time monitoring
        /// </summary>
        /// <param name="lLoginID">Equipment User LoginID:<seealso cref="CLIENT_Login"/>return value</param>
        /// <param name="nChannelID">channelID</param>
        /// <param name="hWnd">Show container window handle</param>
        /// <returns>Failure to return0,The successful return of real-time monitoring ID(Handle real-time monitoring)</returns>
        [DllImport("dhnetsdk.dll")]
        private static extern int CLIENT_RealPlay(int lLoginID, int nChannelID, IntPtr hWnd);

        /// <summary>
        /// Stop real-time monitoring
        /// </summary>
        /// <param name="lRealHandle">Stop real-time monitoring:<seealso cref="CLIENT_RealPlay"/>return value</param>
        /// <returns>true:success;false:failure</returns>
        [DllImport("dhnetsdk.dll")]
        private static extern bool CLIENT_StopRealPlay(int lRealHandle);

        /// <summary>
        /// Stop real-time monitoring
        /// </summary>
        /// <param name="lRealHandle">Handle real-time monitoring:<seealso cref="CLIENT_RealPlay"/>return value</param>
        /// <returns>true:success;false:failure</returns>
        [DllImport("dhnetsdk.dll")]
        private static extern bool CLIENT_StopRealPlayEx(int lRealHandle);

        /// <summary>
        /// Set real-time monitoring data callback,Provide users with equipment out of data,When the end of the callback is NULL data cbRealData
        /// </summary>
        /// <param name="lRealHandle">CLIENT_RealPlayreturn value</param>
        /// <param name="cbRealData">The callback function,Outflow from equipment used in real-time data</param>
        /// <param name="dwUser">user data</param>
        /// <returns>true:success;false:failure</returns>
        [DllImport("dhnetsdk.dll")]
        private static extern bool CLIENT_SetRealDataCallBack(int lRealHandle, fRealDataCallBack cbRealData, IntPtr dwUser);

        /// <summary>
        /// Set up a real-time monitoring data callback extension interface,Is complementary to the previous interface, Add a callback parameter data type flag dwFlag, 
        /// Can be selectively to bring up the needed data, For the type of data did not set a callback callback out, When the time is set to 0x1f
        /// With the same effect as an interface, But also done on the callback function expansion。
        /// </summary>
        /// <param name="lRealHandle">CLIENT_RealPlay return value</param>
        /// <param name="cbRealData">The callback function,Outflow from equipment used in real-time data</param>
        /// <param name="dwUser">user data</param>
        /// <param name="dwFlag">Data type flag</param>
        /// <returns>true:success;false:failure</returns>
        [DllImport("dhnetsdk.dll")]
        private static extern bool CLIENT_SetRealDataCallBackEx(int lRealHandle, fRealDataCallBackEx cbRealData, IntPtr dwUser, UInt32 dwFlag);

        /// <summary>
        /// PTZ control
        /// </summary>
        /// <param name="lLoginID">Equipment User LoginID:<seealso cref="CLIENT_Login"/>return value</param>
        /// <param name="nChannelID">Channel number</param>
        /// <param name="dwPTZCommand">PTZ control commands<seealso cref="PTZControlType"/></param>
        /// <param name="dwStep">Stepping/speed</param>
        /// <param name="dwStop">Whether to stop</param>
        /// <returns>true:success;false:failure</returns>
        [DllImport("dhnetsdk.dll")]
        private static extern bool CLIENT_PTZControl(int lLoginID, int nChannelID, ushort dwPTZCommand, ushort dwStep, bool dwStop);

        /// <summary>
        /// Extended PTZ control, Enhanced control of the PTZ control function functions
        /// </summary>
        /// <param name="lLoginID">Equipment User LoginID:<seealso cref="CLIENT_Login"/>return value</param>
        /// <param name="nChannelID">Channel number</param>
        /// <param name="dwPTZCommand">PTZ control commands</param>
        /// <param name="param1">Parameter1</param>
        /// <param name="param2">Parameter2</param>
        /// <param name="param3">Parameter3</param>
        /// <param name="dwStop">Whether to stop</param>
        /// <returns>true:success;false:failure</returns>
        [DllImport("dhnetsdk.dll")]
        private static extern bool CLIENT_DHPTZControl(int lLoginID, int nChannelID, ushort dwPTZCommand, ushort param1, ushort param2, ushort param3, bool dwStop, IntPtr intPtr);

        /// <summary>
        /// Extended PTZ control, Supports three-dimensional fast positioning
        /// </summary>
        /// <param name="lLoginID">Equipment User LoginID:<seealso cref="CLIENT_Login"/>return value</param>
        /// <param name="nChannelID">Channel number</param>
        /// <param name="dwPTZCommand">PTZ control commands</param>
        /// <param name="param1">Parameter1</param>
        /// <param name="param2">Parameter2</param>
        /// <param name="param3">Parameter3</param>
        /// <param name="dwStop">Whether to stop</param>
        /// <returns>true:success;false:failure</returns>
        [DllImport("dhnetsdk.dll")]
        private static extern bool CLIENT_DHPTZControlEx(int lLoginID, int nChannelID, ushort dwPTZCommand, int lParam1, int lParam2, int lParam3, bool dwStop);

        /// <summary>
        /// Query video files
        /// </summary>
        /// <param name="lLoginID">Device handles user login</param>
        /// <param name="nChannelId">Channel ID</param>
        /// <param name="nRecordFileType">Video file types </param>
        /// <param name="tmStart">Recording start time</param>
        /// <param name="tmEnd">Recording end time</param>
        /// <param name="pchCardid">Card valid only for queries,In other cases you can fill NULL</param>
        /// <param name="nriFileinfo">Return to video file information,Is an array of structures NET_RECORDFILE_INFO</param>
        /// <param name="maxlen">nriFileinfoThe maximum length of the buffer;（In bytes,Recommended 100-200 * sizeof(NET_RECORDFILE_INFO)之间）</param>
        /// <param name="filecount">The number of documents returned,Maximum output parameters are only found in video recording until the buffer is full</param>
        /// <param name="waittime">Wait Time</param>
        /// <param name="bTime">Whether by time(Currently inactive)</param>
        /// <returns>true:success;false:failure</returns>
        [DllImport("dhnetsdk.dll")]
        private static extern bool CLIENT_QueryRecordFile(int lLoginID, int nChannelId, int nRecordFileType, ref NET_TIME tmStart, ref NET_TIME tmEnd, string pchCardid, IntPtr nriFileinfo, int maxlen, out  int filecount, int waittime, bool bTime);

        /// <summary>
        /// Network playback[Pay attention to:After a user logs in a device,Each channel can only play a video at the same time,Can't play the multiple of the same channel at the same time]
        /// </summary>
        /// <param name="lLoginID">Device handle user login</param>
        /// <param name="lpRecordFile">Video file information, When the press time play is only need to fill the start time and end time, Other items to fill0</param>
        /// <param name="hWnd">Playback handle container</param>
        /// <param name="cbDownLoadPos">Progress of the callback function</param>
        /// <param name="dwUserData">User-defined data</param>
        /// <returns>Successful return to network playbackID,Failure to return0</returns>
        [DllImport("dhnetsdk.dll")]
        private static extern int CLIENT_PlayBackByRecordFile(int lLoginID, ref NET_RECORDFILE_INFO lpRecordFile, IntPtr hWnd, fDownLoadPosCallBack cbDownLoadPos, IntPtr dwUserData);

        /// <summary>
        /// With data playback according to time extension of callback interface。Window parameter（hWnd）Effective correction data return values will be ignored,when window parameter (hWnd)is 0,needs take care the callback return value.
        /// </summary>
        /// <param name="lLoginID">CLIENT_Login return value</param>
        /// <param name="nChannelID">Image channel number,must specify</param>
        /// <param name="lpStartTime">Start time</param>
        /// <param name="lpStopTime">End Time</param>
        /// <param name="hWnd">Playback container handler</param>
        /// <param name="cbDownLoadPos">Progress callback function</param>
        /// <param name="dwPosUser">Progress callback user data</param>
        /// <param name="fDownLoadDataCallBack">Data callback function</param>
        /// <param name="dwDataUser">Data callback user data</param>
        /// <returns>Successful return network playback ID,Failure to return0</returns>
        [DllImport("dhnetsdk.dll")]
        private static extern int CLIENT_PlayBackByTimeEx(int lLoginID,int nChannelID, ref NET_TIME lpStartTime,
                                                          ref NET_TIME lpStopTime, IntPtr hWnd,
                                                          fDownLoadPosCallBack cbDownLoadPos, IntPtr dwPosUser,
                                                          fDataCallBack fDownLoadDataCallBack, IntPtr dwDataUser);

        /// <summary>
        /// Callback with data playback video files by extension interface,Each channel can only play a video at the same time,Can't play the same channel multiple records at the same time。Window parameter（hWnd）Effective correction data return values will be ignored,when Window parameter (hWnd)is 0,Need to pay attention to the callback function return values,See the callback function
        /// </summary>
        /// <param name="lLoginID">Device handle user login</param>
        /// <param name="lpRecordFile">record file info</param>
        /// <param name="hWnd">Video file information</param>
        /// <param name="cbDownLoadPos">Progress of the callback function</param>
        /// <param name="dwPosUser">Progress callback function user data</param>
        /// <param name="fDownLoadDataCallBack">Data callback function</param>
        /// <param name="dwDataUser">The callback function data user data</param>
        /// <returns>Successful return to network playback ID,Failure to return0</returns>
        [DllImport("dhnetsdk.dll")]
        private static extern int CLIENT_PlayBackByRecordFileEx(int lLoginID, ref NET_RECORDFILE_INFO lpRecordFile, IntPtr hWnd, fDownLoadPosCallBack cbDownLoadPos, IntPtr dwPosUser,fDataCallBack fDownLoadDataCallBack, IntPtr dwDataUser);

        /// <summary>
        /// Network by time playback
        /// </summary>
        /// <param name="lLoginID">Device handles user login</param>
        /// <param name="nChannelID">Channel ID</param>
        /// <param name="lpStartTime">Recording start time</param>
        /// <param name="lpStopTime">Recording end time</param>
        /// <param name="hWnd">Playback container handler</param>
        /// <param name="cbDownLoadPos">Progress of the callback function</param>
        /// <param name="dwUserData">User-defined data</param>
        /// <returns>Successful return to network playback ID,Failure to return0</returns>
        [DllImport("dhnetsdk.dll")]
        private static extern int CLIENT_PlayBackByTime(int lLoginID, int nChannelID, ref NET_TIME lpStartTime,
                                                        ref NET_TIME lpStopTime, IntPtr hWnd,
                                                        fDownLoadPosCallBack cbDownLoadPos,
                                                        IntPtr dwUserData);

        [DllImport("dhnetsdk.dll")]
        private static extern int CLIENT_PlayBackByTimeEx2(int lLoginID, int nChannelID, ref NET_IN_PLAY_BACK_BY_TIME_INFO pstNetIn, ref NET_OUT_PLAY_BACK_BY_TIME_INFO pstNetOut);
        
        /// <summary>
        /// Network playback stop
        /// </summary>
        /// <param name="lPlayHandle">Handle to the playback</param>
        /// <returns>true:success;false:failure</returns>
        [DllImport("dhnetsdk.dll")]
        private static extern bool CLIENT_StopPlayBack(int lPlayHandle);

        /// <summary>
        /// Network playback pause and resume playing
        /// </summary>
        /// <param name="lPlayHandle">Play a handle</param>
        /// <param name="bPause">1:suspended;0:restore</param>
        /// <returns>true:success;false:failure</returns>
        [DllImport("dhnetsdk.dll")]
        private static extern bool CLIENT_PausePlayBack(int lPlayHandle, int bPause);

        /// <summary>
        /// Change position [i.e. drag,Only parameter function effectively hWnd parameter of the function of the image acquired before the effective opening,Otherwise meaningless]
        /// </summary>
        /// <param name="lPlayHandle">Play a handle</param>
        /// <param name="offsettime">Relative file start migration time,The unit is in seconds .When its value is 0 XFFFFFFFF,This parameter is null and void.</param>
        /// <param name="offsetbyte">Relative file start offset bytes, When its value is 0 XFFFFFFFF, This parameter is null and void；When offsettime is effectively,This parameter is meaningless</param>
        /// <returns>true:success;false:failure</returns>
        [DllImport("dhnetsdk.dll")]
        private static extern bool CLIENT_SeekPlayBack(int lPlayHandle, uint offsettime, uint offsetbyte);

        /// <summary>
        /// Single step play[Called once played a picture,Only parameter function effectively hWnd parameter of the function of the image acquired before the effective opening,Otherwise meaningless]
        /// </summary>
        /// <param name="lPlayHandle">Playback handle</param>
        /// <param name="bStop">Whether to stop playing a single step, When called at the end of the single-step</param>
        /// <returns>true:success;false:failure</returns>
        [DllImport("dhnetsdk.dll")]
        private static extern bool CLIENT_StepPlayBack(int lPlayHandle, bool bStop);

        /// <summary>
        /// Quick put[To double the current frame rate,Fast but not unlimited,The biggest 200,Return FALSE greater than, cannot be faster if the audio release,Slow no problem,Only parameter function effectively hWnd parameter of the function of the image acquired before the effective opening,Otherwise meaningless]
        /// </summary>
        /// <param name="lPlayHandle">Playback handle</param>
        /// <returns>true:success;false:failure</returns>
        [DllImport("dhnetsdk.dll")]
        private static extern bool CLIENT_FastPlayBack(int lPlayHandle);

        /// <summary>
        /// In slow[The current frame rate is twice as slow, the slowest one frame per second,Less than 1 returns FALSE ,Only opened the image hWnd effectively the function parameters of the function to obtain the parameters of the,Otherwise meaningless]
        /// </summary>
        /// <param name="lPlayHandle">Playback handle</param>
        /// <returns>true:success;false:failure</returns>
        [DllImport("dhnetsdk.dll")]
        private static extern bool CLIENT_SlowPlayBack(int lPlayHandle);

        [DllImport("dhnetsdk.dll")]
        //Control forward or backard play   
        private static extern bool  CLIENT_PlayBackControlDirection(int lPlayHandle, bool bBackward);

        [DllImport("dhnetsdk.dll")]
        //get play current time   
        private static extern bool CLIENT_GetPlayBackOsdTime(int lPlayHandle, out NET_TIME lpOsdTime, out NET_TIME lpStartTime, out NET_TIME lpEndTime);

        /// <summary>
        /// Get the SDK version number
        /// </summary>
        /// <returns>version number</returns>
        [DllImport("dhnetsdk.dll")]
        private static extern UInt32 CLIENT_GetSDKVersion();

        /// <summary>
        /// User-defined drawing, Before calling this function to open image,Otherwise it is invalid,Must be called before any window is not displayed, Can be used to screen for character overlay
        /// </summary>
        /// <param name="cbDraw">Drawing callback,When set to 0 said callback is prohibited</param>
        /// <param name="dwUser">user data</param>
        [DllImport("dhnetsdk.dll")]
        private static extern void CLIENT_RigisterDrawFun(fDrawCallBack cbDraw, IntPtr dwUser);

        /// <summary>
        /// Get Device Configuration
        /// </summary>
        /// <param name="lLoginID">Equipment User LoginID:CLIENT_Login return value</param>
        /// <param name="dwCommand">Configuration Type</param>
        /// <param name="lChannel">Channel number,If they are not channel parameters,lChannelDon't have to use,Can be set to -1</param>
        /// <param name="lpOutBuffer">Storing the output parameter buffer, According to the different types, The output of different configuration structure,See data structure definition</param>
        /// <param name="dwOutBufferSize">The size of the input buffer, (Unit of byte).</param>
        /// <param name="lpBytesReturned">The actual size of the buffer returned,Size corresponds to the configuration structure, (Unit of byte)</param>
        /// <param name="waittime">wait time</param>
        /// <returns>true:success;false:failure</returns>
        [DllImport("dhnetsdk.dll")]
        private static extern bool CLIENT_GetDevConfig(int lLoginID, UInt32 dwCommand, int lChannel, IntPtr lpOutBuffer, UInt32 dwOutBufferSize, ref UInt32 lpBytesReturned, int waittime);

        /// <summary>
        /// Device configuration settings
        /// </summary>
        /// <param name="lLoginID">Equipment User LoginID:CLIENT_Loginreturn value</param>
        /// <param name="dwCommand">Configuration Type</param>
        /// <param name="lChannel">Channel number,If you set all channel data to 0xFFFFFFFF,If the command does not require channel number,This parameter is invalid</param>
        /// <param name="lpInBuffer">A buffer for storing the input parameters, According to the different types, Enter a different configuration structure, See specific data structure definitions</param>
        /// <param name="dwInBufferSize">Enter the size of the buffer, (Unit of byte)</param>
        /// <returns>true:success;false:failure</returns>
        [DllImport("dhnetsdk.dll")]
        private static extern bool CLIENT_SetDevConfig(int lLoginID, UInt32 dwCommand, int lChannel, IntPtr lpInBuffer, UInt32 dwInBufferSize, int waittime);

        /// <summary>
        ///Check equipment channel names
        /// </summary>
        /// <param name="lLoginID">Equipment user loginID:CLIENT_Login return value</param>
        /// <param name="pChannelName">Channel name buffer,Generally speaking, each channel name is 32 bytes long,Here need to allocate 16 * 32 bytes in length buffer）</param>
        /// <param name="maxlen">Buffer length, (Unit of byte)</param>
        /// <param name="nChannelCount">A total number of channels</param>
        /// <param name="waittime">waiting time</param>
        /// <returns>true:success;false:failure</returns>
        [DllImport("dhnetsdk.dll")]
        private static extern bool CLIENT_QueryChannelName(int lLoginID, ref char pChannelName, int maxlen, ref int nChannelCount, int waittime);

        /// <summary>
        ///Query Record State
        /// </summary>
        [DllImport("dhnetsdk.dll")]
        private static extern bool CLIENT_QueryRecordState(int lLoginID, byte[] pRSBuffer, int maxlen, ref int nRSBufferlen, int waittime);

        /// <summary>
        ///Setup Record State
        /// </summary>
        [DllImport("dhnetsdk.dll")]
        private static extern bool CLIENT_SetupRecordState(int lLoginID, byte[] pRSBuffer, int nRSBufferlen);



        /// <summary>
        /// Query a serial port protocol and decoder, Are part of the configuration information,Queries the device supports optional front-end control protocol
        /// </summary>
        /// <param name="lLoginID">Equipment user loginID:CLIENT_Login return value</param>
        /// <param name="nProtocolType">0 is the serial protocol1 is a protocol decoder(PTZ control protocol)</param>
        /// <param name="pProtocolBuffer">Protocol buffers received</param>
        /// <param name="maxlen">Agreement received buffer length</param>
        /// <param name="nProtocollen">The total number of bytes received,(Unit of byte).</param>
        /// <param name="waittime">waiting time </param>
        /// <returns>true:success;false:failure</returns>
        [DllImport("dhnetsdk.dll")]
        private static extern bool CLIENT_QueryComProtocol(int lLoginID, int nProtocolType, ref char pProtocolBuffer, int maxlen, ref int nProtocollen, int waittime);

        /// <summary>
        /// Information query system,Different information has different data structure
        /// </summary>
        /// <param name="lLoginID" equipment user loginID:CLIENT_Login return value</param>
        /// <param name="nSystemType">The types of systems to query
        ///  0		General Information
        ///  1		Query device attribute information
        ///  2		Check the hard disk information
        ///  3		Query File System Information
        ///  4		Video attribute information
        ///  5		Charset attribute information inquiry system
        ///  6		Optical storage device information query
        ///  7		Get the serial number of the device
        /// </param>
        /// <param name="pSysInfoBuffer">Protocol buffers received</param>
        /// <param name="maxlen">Agreement received buffer length,(Unit of byte)</param>
        /// <param name="nSysInfolen">Receive the total number of bytes,(Unit of byte).</param>
        /// <param name="waittime">waiting time</param>
        /// <returns>true:success;false:failure</returns>
        [DllImport("dhnetsdk.dll")]
        private static extern bool CLIENT_QuerySystemInfo(int lLoginID, int nSystemType, IntPtr pSysInfoBuffer, int maxlen, ref  int nSysInfolen, int waittime);

        [DllImport("dhnetsdk.dll")]
        private static extern bool CLIENT_QueryDevState(int lLoginID, int nType, IntPtr pBuf, int nBufLen,ref int pRetLen, int waittime);

        /// <summary>
        ///The configuration information acquisition device
        /// </summary>
        /// <param name="lLoginID">Equipment User LoginID:CLIENT_Loginreturn value</param>
        /// <param name="nConfigType">Configuration type</param>
        /// <param name="pConfigbuf">Configure the receive buffer, According to the different configuration information,Structure and data length is not consistent</param>
        /// <param name="maxlen">The maximum length of the receive buffer configuration,(Unit of byte)</param>
        /// <param name="nConfigbuflen">Configure received packet length,(Unit of byte)</param>
        /// <param name="waittime">waiting time</param>
        /// <returns>true:success;false:failure</returns>
        [DllImport("dhnetsdk.dll")]
        private static extern bool CLIENT_QueryConfig(int lLoginID, int nConfigType, ref  char pConfigbuf, int maxlen, ref int nConfigbuflen, int waittime);

        /// <summary>
        /// Set up information
        /// </summary>
        /// <param name="lLoginID">Equipment User LoginID:CLIENT_Login return value</param>
        /// <param name="nConfigType">Configuration Type</param>
        /// <param name="pConfigbuf">Set Configuration Buffer</param>
        /// <param name="nConfigbuflen">Set Configuration packet length,(Unit of byte)</param>
        /// <param name="waittime">waiting time</param>
        /// <returns>true:success;false:failure</returns>
        [DllImport("dhnetsdk.dll")]
        private static extern bool CLIENT_SetupConfig(int lLoginID, int nConfigType, ref char pConfigbuf, int nConfigbuflen, int waittime);

        /// <summary>
        /// Query user information
        /// </summary>
        /// <param name="lLoginID">CLIENT_Login return value</param>
        /// <param name="info">Cache user information,Should pass into an allocated memory USER_MANAGE_INFO good structure pointer; Returns all user information USER_INFO the password field is applied too close。</param>
        /// <param name="waittime">waiting time</param>
        /// <returns>true:success;false:failure</returns>
        [DllImport("dhnetsdk.dll")]
        private static extern bool CLIENT_QueryUserInfo(int lLoginID, IntPtr info, int waittime);

        /// <summary>
        /// Setting up user information
        /// </summary>
        /// <param name="lLoginID">CLIENT_Loginreturn value</param>
        /// <param name="nOperateType">
        /// Set the type
        /// 0		add user group-opParam want to USER_GROUP_INF structure pointer set
        /// 1		delete user group－To set up the structure for the USER_GROUP_INF opParam pointer whose name is actually functioning member variables
        /// 2		Modify User Group-opParam new USER_GROUP_INF structure pointer, subParam to the original USER_GROUP_INF structure pointer
        /// 3		To add the user-opParam to increase its password USER_INF structure pointer members can pass an ordinary string, without encryption
        /// 4		To delete a user-opParam want to delete USER_INF structure pointer member whose name is the actual role of the variables
        /// 5		Modifying User-opParam new USER_INF structure pointer subParam USER_INF structure pointer to the original, its password is the password field members must return a query (encrypted)
        /// 6		Modify the user password-opParam new USER_INF structure pointer subParam USER_INF structure pointer to the original, its members must be an ordinary string password, do not encrypt
        /// </param>
        /// <param name="opParam">Set the input buffer of user information,See specific instructions nOperateType。</param>
        /// <param name="subParam">Set the input buffer of user information,See specific instructions nOperateType。</param>
        /// <param name="waittime">waiting time</param>
        /// <returns>true:success;false:failure</returns>
        [DllImport("dhnetsdk.dll")]
        private static extern bool CLIENT_OperateUserInfo(int lLoginID, int nOperateType, IntPtr opParam, IntPtr subParam, int waittime);

        /// <summary>
        /// Save the picture,Instantly the display image,Only parameter function effectively hWnd parameter of the function of the image acquired before the effective opening,Otherwise meaningless
        /// </summary>
        /// <param name="hPlayHandle">CLIENT_RealPlay return value</param>
        /// <param name="pchPicFileName">Bitmap file name,Currently only supports bitmap BMP</param>
        /// <returns>true:success;false:failure</returns>
        [DllImport("dhnetsdk.dll")]
        private static extern bool CLIENT_CapturePicture(int hPlayHandle, string pchPicFileName);

        
        /// <summary>
        /// Download the video file by file, By querying the file information to download
        /// </summary>
        /// <param name="lLoginID">CLIENT_Login return value</param>
        /// <param name="lpRecordFile">Video file information</param>
        /// <param name="sSavedFileName">To save the video file name,Full path</param>
        /// <param name="cbDownLoadPos">Download progress callback function</param>
        /// <param name="dwUserData">Download progress callback user-defined data</param>
        /// <returns>Successful return Download ID,Failure to return0</returns>
        [DllImport("dhnetsdk.dll")]
        private static extern int CLIENT_DownloadByRecordFile(int lLoginID,ref NET_RECORDFILE_INFO lpRecordFile,string  sSavedFileName, fDownLoadPosCallBack cbDownLoadPos, IntPtr dwUserData);

        /// <summary>
        /// Chronological Download,Direct input channel start time and end time download the lounge
        /// </summary>
        /// <param name="lLoginID">CLIENT_Loginreturn value</param>
        /// <param name="nChannelId">Image channel number,Starting from 0</param>
        /// <param name="nRecordFileType">Retention</param>
        /// <param name="tmStart">Start time</param>
        /// <param name="tmEnd">End Time</param>
        /// <param name="sSavedFileName">To save the video file name,full channel</param>
        /// <param name="cbTimeDownLoadPos">Download progress callback function</param>
        /// <param name="dwUserData">Download progress callback user-defined data</param>
        /// <returns>Successful return to downloadID,Failure to return0</returns>
        [DllImport("dhnetsdk.dll")]
        private static extern int CLIENT_DownloadByTime(int lLoginID, int nChannelId, int nRecordFileType, ref  NET_TIME tmStart, ref  NET_TIME tmEnd, string sSavedFileName, fTimeDownLoadPosCallBack cbTimeDownLoadPos, IntPtr dwUserData);

        /// <summary>
        /// Stop downloading video files
        /// </summary>
        /// <param name="lFileHandle">CLIENT_DownloadByRecordFilereturn value</param>
        /// <returns>true:success;false:failure</returns>
        [DllImport("dhnetsdk.dll")]
        private static extern bool CLIENT_StopDownload(int lFileHandle);

        /// <summary>
        /// Download the video to get the current position,Can be used to display the download progress does not require real-time interface,Similar to the callback function to download
        /// </summary>
        /// <param name="lFileHandle">CLIENT_DownloadByRecordFile return value</param>
        /// <param name="nTotalSize">The total length of the downloaded,UnitKB</param>
        /// <param name="nDownLoadSize">Downloaded length,UnitKB</param>
        /// <returns>true:success;false:failure</returns>
        [DllImport("dhnetsdk.dll")]
        private static extern bool CLIENT_GetDownloadPos(int lFileHandle, out int nTotalSize, out int nDownLoadSize);

        /// <summary>
        /// Start real-time monitoring or screen preview
        /// </summary>
        /// <param name="lLoginID">CLIENT_Login return value</param>
        /// <param name="nChannelID">Real-time monitoring channel number,If this parameter is reserved rType is RType_Multiplay。当rType为RType_Multiplay_1~RType_Multiplay_16时,nChannelIDDetermines the preview screen,For example, when RType_Multiplay_4 time,Channel 4 or 5 or 6 or 7, said four screen preview preview fifth to seventh channel。
 
        /// <param name="hWnd">Window handle,A value of 0 does not decode the data、Do not show images。</param>
        /// <param name="rType">Data Types(seeREALPLAY_TYPE)</param>
        /// <returns>Failure to return0,The successful return of real-time monitoring ID(Handle real-time monitoring),The correlation function as a parameter</returns>
        [DllImport("dhnetsdk.dll")]
        private static extern int CLIENT_RealPlayEx(int lLoginID, int nChannelID, IntPtr hWnd, REALPLAY_TYPE rType);

        /// <summary>
        /// Start saving real-time monitoring data,Front-end equipment to monitor the image data to be saved,Form video files,This data is transmitted from the device side original video data
        /// </summary>
        /// <param name="lRealHandle">CLIENT_RealPlay return value</param>
        /// <param name="pchFileName">Real-time monitoring to save the file name</param>
        /// <returns>true:success;false:failure</returns>
        [DllImport("dhnetsdk.dll")]
        private static extern bool CLIENT_SaveRealData(int lRealHandle, string pchFileName);

        /// <summary>
        /// Stop saving real-time monitoring data, close the saved file
        /// </summary>
        /// <param name="lRealHandle">CLIENT_RealPlay return value</param>
        /// <returns>true:success;false:failure</returns>
        [DllImport("dhnetsdk.dll")]
        private static extern bool CLIENT_StopSaveRealData(int lRealHandle);
        
        /// <summary>
        /// Set video parameters decoding library,Only parameter function effectively hWnd parameter image to open the function gets to be valid, otherwise meaningless
        /// </summary>
        /// <param name="lPlayHandle">CLIENT_RealPlay return value</param>
        /// <param name="nBrightness">Brightness(0-255)</param>
        /// <param name="nContrast">contrast(0-255)</param>
        /// <param name="nHue">chroma(0-255)</param>
        /// <param name="nSaturation">saturation(0-255)</param>
        /// <returns>true:success;false:failure</returns>
        [DllImport("dhnetsdk.dll")]
        private static extern bool CLIENT_ClientSetVideoEffect(int lPlayHandle, byte nBrightness, byte nContrast, byte nHue, byte nSaturation);

        /// <summary>
        /// Access to video decoding library parameters,Only the open image hWnd effectively the function parameters of the function to obtain the parameters of the is valid, otherwise meaningless。
        /// </summary>
        /// <param name="lPlayHandle">CLIENT_RealPlay return value</param>
        /// <param name="nBrightness">Return a pointer to the brightness(0-255)</param>
        /// <param name="nContrast">Return a pointer to the contrast(0-255)</param>
        /// <param name="nHue">Return a pointer to chroma(0-255)</param>
        /// <param name="nSaturation">Return a pointer to the saturation(0-255)</param>
        /// <returns>true:success;false:failure</returns>
        [DllImport("dhnetsdk.dll")]
        private static extern bool CLIENT_ClientGetVideoEffect(int lPlayHandle, ref byte nBrightness, ref byte nContrast, ref byte nHue, ref byte nSaturation);

        /// <summary>
        /// Access to the configuration,According to the format string
        /// </summary>
        /// <param name="lLoginID">CLIENT_Loginreturn value</param>
        /// <param name="szCommand">The command parameter,seeCLIENT_ParseData</param>
        /// <param name="nChannelID">Channel number</param>
        /// <param name="szOutBuffer">Output Buffer </param>
        /// <param name="dwOutBufferSize">Output buffer size</param>
        /// <param name="error">Error code</param>
        /// <param name="waittime">Wait timeout,The default setting is500</param>
        /// <returns>true:success;false:failure</returns>
        [DllImport("dhnetsdk.dll")]
        private static extern bool CLIENT_GetNewDevConfig(Int32 lLoginID, string szCommand, Int32 nChannelID, IntPtr szOutBuffer, UInt32 dwOutBufferSize, ref UInt32 error, Int32 waittime);

        /// <summary>
        /// Set the configuration,According to the format string
        /// </summary>
        /// <param name="lLoginID">CLIENT_Loginreturn value</param>
        /// <param name="szCommand">please seeCLIENT_GetNewDevConfig instructions</param>
        /// <param name="nChannelID">Channel number</param>
        /// <param name="szInBuffer">The input buffer </param>
        /// <param name="dwInBufferSize">Input Buffer Size</param>
        /// <param name="error">Error code</param>
        /// <param name="restart">Will you need to restart your device after configuration Settings,1 means need to restart,0 means no need to restart</param>
        /// <param name="waittime">Wait timeout,The default setting is 500</param>
        /// <returns>true:success;false:failure</returns>
        [DllImport("dhnetsdk.dll")]
        private static extern bool CLIENT_SetNewDevConfig(Int32 lLoginID, string strCommand, Int32 lChannel, IntPtr lpInBuffer, UInt32 dwInBufferSize, ref UInt32 error, ref UInt32 restart, Int32 waittime);

        /// <summary>
        /// The new system is the ability to query interface,Ability information inquiry system(In Json format, see the specific configuration SDK)
        /// </summary>
        /// <param name="lLoginID">CLIENT_Loginreturn value</param>
        /// <param name="szCommand"></param>
        /// <param name="nChannelID">Channel number</param>
        /// <param name="szOutBuffer">Output Buffer</param>
        /// <param name="dwOutBufferSize">Output buffer size</param>
        /// <param name="error">Error code</param>
        /// <param name="waittime">Wait timeout,The default setting for1000</param>
        /// <returns></returns>
        [DllImport("dhnetsdk.dll")]
        private static extern bool CLIENT_QueryNewSystemInfo(Int32 lLoginID, string szCommand, Int32 nChannelID, IntPtr szOutBuffer, UInt32 dwOutBufferSize, ref UInt32 error, Int32 waittime);

        /// <summary>
        /// Real-time intelligent analysis of data uploaded - Pictures
        /// </summary>
        /// <param name="lLoginID">CLIENT_Loginreturn value</param>
        /// <param name="nChannelID">Channel number</param>
        /// <param name="dwAlarmType">type</param>
        /// <param name="cbAnalyzerData">Analyze data correction</param>
        /// <param name="dwUser">user data</param>
        /// <returns></returns>
        [DllImport("dhnetsdk.dll")]
        private static extern Int32 CLIENT_RealLoadPicture(Int32 lLoginID, Int32 nChannelID, UInt32 dwAlarmType, fAnalyzerDataCallBack cbAnalyzerData, UInt32 dwUser);

        /// <summary>
        /// Real-time intelligent analysis of data uploaded - Pictures(Extended Interface,bNeedPicFileIndicates whether or not to subscribe to image files,Reservedtype is RESERVED_PARA) 
        /// </summary>
        /// <param name="lLoginID">CLIENT_Login的return value</param>
        /// <param name="nChannelID">channel number</param>
        /// <param name="dwAlarmType">type</param>
        /// <param name="cbAnalyzerData">Analysis of the data callback</param>
        /// <param name="dwUser">user data</param>
        /// <returns></returns>
        [DllImport("dhnetsdk.dll")]
        private static extern Int32 CLIENT_RealLoadPictureEx(Int32 lLoginID, Int32 nChannelID, UInt32 dwAlarmType, bool bNeedPicFile, fAnalyzerDataCallBack cbAnalyzerData, UInt32 dwUser, IntPtr Reserved);

        /// <summary>
        /// Stop uploading intelligent analysis of data - pictures
        /// </summary>
        /// <param name="lAnalyzerHandle">CLIENT_RealLoadPictureEx return value</param>
        /// <returns></returns>
        [DllImport("dhnetsdk.dll")]
        private static extern bool CLIENT_StopLoadPic(Int32 lAnalyzerHandle);

        /// <summary>
        /// Device Control
        /// </summary>
        /// <param name="lLoginID">CLIENT_Login return value</param>
        /// <param name="type">CtrlTypeEnumerate</param>
        /// <param name="param"></param>
        /// <param name="waittime">Timeout waiting,The default setting1000</param>
        /// <returns></returns>
        [DllImport("dhnetsdk.dll")]
        private static extern bool CLIENT_ControlDevice(Int32 lLoginID, CtrlType type, IntPtr param, Int32 waittime);

        /// <summary>
        ///Configuration information to resolve queries
        /// </summary>
        /// <param name="szCommand">Command parameters,See the developer documentation</param>
        /// <param name="szInBuffer">Input Buffer,Character buffer configuration</param>
        /// <param name="lpOutBuffer">Output Buffer,Type of structure can be found in the table</param>
        /// <param name="dwOutBufferSize">Size of the output buffer</param>
        /// <param name="pReserved">Retention parameters</param>
        /// <returns></returns>
        [DllImport("dhconfigsdk.dll")]
        private static extern bool CLIENT_ParseData(string szCommand, IntPtr szInBuffer, IntPtr lpOutBuffer, UInt32 dwOutBufferSize, IntPtr pReserved);


        /// <summary>
        /// Will need to set the configuration information,Packaged into a string format
        /// </summary>
        /// <param name="szCommand">Command parameters,seeCLIENT_ParseData table</param>
        /// <param name="lpInBuffer">Input Buffer,See structure typeCLIENT_ParseDatatable</param>
        /// <param name="dwInBufferSize">Input Buffer Size</param>
        /// <param name="szOutBuffer">Output Buffer</param>
        /// <param name="dwOutBufferSize">Output buffer size</param>
        /// <returns></returns>
        [DllImport("dhconfigsdk.dll")]
        private static extern bool CLIENT_PacketData(string strCommand, IntPtr lpInBuffer, UInt32 dwInBufferSize, IntPtr szOutBuffer, UInt32 dwOutBufferSize);

        /// <summary>
        /// Download designated intelligent analysis of data - pictures
        /// </summary>
        /// <param name="lLoginID">CLIENT_Login return value</param>
        /// <param name="emType">EM_FILE_QUERY_TYPEEnumerate</param>
        /// <param name="lpMediaFileInfo">Picture file data</param>
        /// <param name="sSavedFileName">Save the file name</param>
        /// <param name="cbDownLoadPos">Download callback</param>
        /// <param name="dwUserData">user data</param>
        /// <param name="reserved">Retain data</param>
        /// <returns></returns>
        [DllImport("dhnetsdk.dll")]
        private static extern Int32 CLIENT_DownloadMediaFile(Int32 lLoginID,EM_FILE_QUERY_TYPE emType, IntPtr lpMediaFileInfo, string sSavedFileName, fDownLoadPosCallBack cbDownLoadPos, UInt32 dwUserData,  IntPtr reserved);

        /// <summary>
        /// Stop downloading data
        /// </summary>
        /// <param name="lFileHandle">CLIENT_DownloadMediaFile return value</param>
        /// <returns></returns>
        [DllImport("dhnetsdk.dll")]
        private static extern bool CLIENT_StopDownloadMediaFile(Int32 lFileHandle);

        /// <summary>
        ///By query query file
        /// </summary>
        /// <param name="lLoginID">CLIENT_Login return value</param>
        /// <param name="emType">mediaFile query </param>
        /// <param name="pQueryCondition">Query </param>
        /// <param name="reserved">Reserved bytes</param>
        /// <param name="waittime">Wait Time</param>
        /// <returns></returns>
        [DllImport("dhnetsdk.dll")]
        private static extern Int32	CLIENT_FindFileEx(Int32 lLoginID, EM_FILE_QUERY_TYPE emType, IntPtr pQueryCondition, IntPtr reserved, Int32 waittime);	

        /// <summary>
        /// 
        /// </summary>
        /// <param name="lFindHandle">CLIENT_FindFileEx return value</param>
        /// <param name="nFilecount">The number of queries needed</param>
        /// <param name="pMediaFileInfo">Documentation buffer,Query for output media files to record</param>
        /// <param name="maxlen">The maximum buffer length</param>
        /// <param name="reserved">Reserved bytes</param>
        /// <param name="waittime">Wait Time</param>
        /// <returns></returns>
        [DllImport("dhnetsdk.dll")]
        private static extern Int32 CLIENT_FindNextFileEx(Int32 lFindHandle, Int32 nFilecount, IntPtr pMediaFileInfo, Int32 maxlen, IntPtr reserved, Int32 waittime);

        /// <summary>
        /// Close the query handle
        /// </summary>
        /// <param name="lFindHandle">CLIENT_FindFileEx return value</param>
        /// <returns></returns>
        [DllImport("dhnetsdk.dll")]
        private static extern bool CLIENT_FindCloseEx(Int32 lFindHandle);

        [DllImport("dhnetsdk.dll")]
        private static extern bool CLIENT_SnapPicture(Int32 lLoginID, SNAP_PARAMS par);

        [DllImport("dhnetsdk.dll")]
        private static extern void CLIENT_SetSnapRevCallBack(fSnapRev OnSnapRevMessage, Int32 dwUser);


        [DllImport("dhnetsdk.dll")]
        private static extern Int32 CLIENT_StartSearchDevices(fSearchDevicesCB cbSearchDevices, IntPtr pUserData, IntPtr szLocalIp);


        /// <summary>
        ///Stop the asynchronous search LAN IPC, NVS and other equipment
        /// </summary>
        [DllImport("dhnetsdk.dll")]
        private static extern bool CLIENT_StopSearchDevices(Int32 lSearchHandle);

        /// <summary>
        /// Stop the asynchronous search LAN IPC, NVS and other equipment
        /// </summary>
        [DllImport("dhnetsdk.dll")]
        private static extern Int32 CLIENT_StartUpgradeEx(Int32 lLoginID, EM_UPGRADE_TYPE emType, string pchFileName, fUpgradeCallBack cbUpgrade, UInt32 dwUser);

        // <summary>
        /// Sending data
        /// </summary>
        [DllImport("dhnetsdk.dll")]
        private static extern bool CLIENT_SendUpgrade(Int32 lUpgradeID);


        // <summary>
        /// End upgrade equipment program
        /// </summary>
        [DllImport("dhnetsdk.dll")]
        private static extern bool CLIENT_StopUpgrade(Int32 lUpgradeID);

        // <summary>
        /// Set Device Time
        /// </summary>
        [DllImport("dhnetsdk.dll")]
        private static extern bool CLIENT_SetupDeviceTime(Int32 lLoginID, ref NET_TIME pDeviceTime);

        // <summary>
        /// Query Device Time
        /// </summary>
        [DllImport("dhnetsdk.dll")]
        private static extern bool CLIENT_QueryDeviceTime(int lLoginID, out NET_TIME pDeviceTime, int waittime = 1000);

        // <summary>
        /// Set SecurityKey
        /// </summary>
        [DllImport("dhnetsdk.dll")]
        private static extern bool CLIENT_SetSecurityKey(Int32 lPlayHandle, string szKey, UInt32 nKeyLen);

        // <summary>
        /// Query TransCom Info
        /// <param name="TransComType">2 hight bites means coms number , 2 low  bites means coms type(0：232，1:485) </param>
        /// </summary>
        [DllImport("dhnetsdk.dll")]
        private static extern bool CLIENT_QueryTransComParams(int lLoginID, int TransComType, out NET_COMM_STATE pCommState, int nWaitTime);

        // <summary>
        /// Query TransCom Info
        /// <param name="TransComType">2 hight bites means coms number , 2 low  bites means coms type(0：232，1:485) </param>
        /// </summary>
        [DllImport("dhnetsdk.dll")]
        private static extern int CLIENT_CreateTransComChannel(int lLoginID, int TransComType, uint baudrate, uint databits, uint stopbits, uint parity, fTransComCallBack cbTransCom, IntPtr dwUser);

        // <summary>
        /// Send Data To Transcom Channel
        /// </summary>
        [DllImport("dhnetsdk.dll")]
        private static extern bool CLIENT_SendTransComData(int lTransComChannel, string pBuffer, int dwBufSize);

        // <summary>
        /// Destroy Transcom Channel
        /// </summary>
        [DllImport("dhnetsdk.dll")]
        private static extern bool CLIENT_DestroyTransComChannel(int lTransComChannel);

        #endregion

        #region <<Constant string--Configuration commands Corresponding CLIENT_GetNewDevConfig and CLIENT_SetNewDevConfig Interface>>
        /// <summary>
        /// Image channel attribute configuration(Corresponding CFG_ENCODE_INFO or AV_CFG_Encode)
        /// </summary>
        public static string CFG_CMD_ENCODE = "Encode";
        /// <summary>
        /// Timer recording configuration(Corresponding CFG_RECORD_INFO or AV_CFG_Record)
        /// </summary>
        public static string CFG_CMD_RECORD = "Record";
        /// <summary>
        ///External input alarm configuration(Corresponding CFG_ALARMIN_INFO)
        /// </summary>
        public static string CFG_CMD_ALARMINPUT = "Alarm";
        /// <summary>
        ///Network alarm configuration(Corresponding CFG_NETALARMIN_INFO)
        /// </summary>
        public static string CFG_CMD_NETALARMINPUT = "NetAlarm";
        /// <summary>
        /// Dynamic detection alarm configuration(Corresponding CFG_MOTION_INFO)
        /// </summary>
        public static string CFG_CMD_MOTIONDETECT = "MotionDetect";
        /// <summary>
        /// Video loss alarm configuration(Corresponding CFG_VIDEOLOST_INFO)
        /// </summary>
        public static string CFG_CMD_VIDEOLOST = "LossDetect";
        /// <summary>
        /// Video Tampering configuration(Corresponding CFG_SHELTER_INFO)
        /// </summary>
        public static string CFG_CMD_VIDEOBLIND = "BlindDetect";
        /// <summary>
        ///No storage devices configured alarm(Corresponding CFG_STORAGENOEXIST_INFO)
        /// </summary>
        public static string CFG_CMD_STORAGENOEXIST = "StorageNotExist";
        /// <summary>
        /// Storage device access configuration error alarm(Corresponding CFG_STORAGEFAILURE_INFO)
        /// </summary>
        public static string CFG_CMD_STORAGEFAILURE = "StorageFailure";
        /// <summary>
        /// Storage space is insufficient alarm configuration(Corresponding CFG_STORAGELOWSAPCE_INFO)
        /// </summary>
        public static string CFG_CMD_STORAGELOWSAPCE = "StorageLowSpace";
        /// <summary>
        ///Network disconnect alarm configuration(Corresponding CFG_NETABORT_INFO)	
        /// </summary>
        public static string CFG_CMD_NETABORT = "NetAbort";
        /// <summary>
        /// IP conflict alarm configuration(Corresponding CFG_IPCONFLICT_INFO)
        /// </summary>
        public static string CFG_CMD_IPCONFLICT = "IPConflict";
        /// <summary>
        /// Grab the ability to query(Corresponding CFG_SNAPCAPINFO_INFO)
        /// </summary>
        public static string CFG_CMD_SNAPCAPINFO = "SnapInfo";
        /// <summary>
        /// Network Storage Server Configuration(Corresponding CFG_NAS_INFO)
        /// </summary>
        public static string CFG_CMD_NAS = "NAS";
        /// <summary>
        /// PTZ configuration(Corresponding CFG_PTZ_INFO)
        /// </summary>
        public static string CFG_CMD_PTZ = "Ptz";
        /// <summary>
        /// Video Watermark configuration(Corresponding CFG_WATERMARK_INFO)
        /// </summary>
        public static string CFG_CMD_WATERMARK = "WaterMark";
        /// <summary>
        /// Video Analytics Global Configuration(Corresponding CFG_ANALYSEGLOBAL_INFO)
        /// </summary>
        public static string CFG_CMD_ANALYSEGLOBAL = "VideoAnalyseGlobal";
        /// <summary>
        ///Object detection module configuration(Corresponding CFG_ANALYSEMODULES_INFO)
        /// </summary>
        public static string CFG_CMD_ANALYSEMODULE = "VideoAnalyseModule";
        /// <summary>
        ///Video analysis rule configuration(Corresponding CFG_ANALYSERULES_INFO)
        /// </summary>
        public static string CFG_CMD_ANALYSERULE = "VideoAnalyseRule";
        /// <summary>
        ///Configure video analysis resources(Corresponding CFG_ANALYSESOURCE_INFO)
        /// </summary>
        public static string CFG_CMD_ANALYSESOURCE = "VideoAnalyseSource";
        /// <summary>
        /// Wiper configuration(Corresponding CFG_RAINBRUSH_INFO)
        /// </summary>
        public static string CFG_CMD_RAINBRUSH = "RainBrush";
        /// <summary>
        /// Intelligent traffic capture(CFG_TRAFFICSNAPSHOT_INFO)
        /// </summary>
        public static string CFG_CMD_INTELLECTIVETRAFFIC = "TrafficSnapshot";
        /// <summary>
        /// Intelligent Transportation Global Configuration(CFG_TRAFFICGLOBAL_INFO)
        /// </summary>
        public static string CFG_CMD_TRAFFICGLOBAL = "TrafficGlobal";
        /// <summary>
        /// Common Configuration (CFG_DEV_DISPOSITION_INFO)
        /// </summary>
        public static string CFG_CMD_DEV_GENERRAL = "General";
        /// <summary>
        /// ATM before moving alarm(Corresponding CFG_ATMMOTION_INFO)
        /// </summary>
        public static string CFG_CMD_ATMMOTION = "FetchMoneyOverTime";
        /// <summary>
        ///Device status information(Corresponding CFG_DEVICESTATUS_INFO)
        /// </summary>
        public static string CFG_CMD_DEVICESTATUS = "DeviceStatus";
        /// <summary>
        /// Expansion Cabinet Information(Corresponding CFG_HARDISKTANKGROUP_INFO)
        /// </summary>
        public static string CFG_CMD_HARDDISKTANK = "HardDiskTank";
        /// <summary>
        ///Raid group information(Corresponding CFG_RAIDGROUP_INFO)
        /// </summary>
        public static string CFG_CMD_RAIDGROUP = "RaidGroup";
        /// <summary>
        /// Storage pool group information(Corresponding CFG_STORAGEPOOLGROUP_INFO)
        /// </summary>
        public static string CFG_CMD_STORAGEPOOLGROUP = "StoragePoolGroup";
        /// <summary>
        ///File System group information(Corresponding CFG_STORAGEPOSITIONGROUP_INFO)
        /// </summary>
        public static string CFG_CMD_STORAGEPOSITIONGROUP = "StoragePositionGroup";
        /// <summary>
        /// Front-end device group information(Corresponding CFG_VIDEOINDEVGROUP_INFO)
        /// </summary>
        public static string CFG_CMD_VIDEOINDEVGROUP = "VideoInDevGroup";
        /// <summary>
        /// Channel recording group status(Corresponding CFG_DEVRECORDGROUP_INFO)
        /// </summary>
        public static string CFG_CMD_DEVRECORDGROUP = "DevRecordGroup";
        /// <summary>
        ///Service Status(Corresponding CFG_IPSERVER_STATUS)
        /// </summary>
        public static string CFG_CMD_IPSSERVER = "IpsServer";
        /// <summary>
        /// Grab source configuration(Corresponding CFG_SNAPSOURCE_INFO)
        /// </summary>
        public static string CFG_CMD_SNAPSOURCE = "SnapSource";
        /// <summary>
        /// radar configuration
        /// </summary>
        public static string CFG_CMD_DHRADER = "DahuaRadar";
        /// <summary>
        /// Chuansuleida configuration
        /// </summary>
        public static string CFG_CMD_TRANSRADER = "TransRadar";
        /// <summary>
        /// Blue Shield radar configuration
        /// </summary>
        public static string CFG_CMD_LANDUNRADER = "LanDunRadar";
        /// <summary>
        /// Blue Shield coil configuration
        /// </summary>
        public static string CFG_CMD_LANDUNCOILS = "LanDunCoils";
        /// <summary>
        /// Spot Matrix Screen(Corresponding CFG_VIDEO_MATRIX)
        /// </summary>
        public static string CFG_CMD_MATRIX_SPOT = "SpotMatrix";
        /// <summary>
        ///Dsp information HDVR pass each digital channel Digital channels can be connected to the IPC or DVR That is, the ability of IPC or DVR(CFG_DSPENCODECAP_INFO)
        /// </summary>
        public static string CFG_CMD_HDVR_DSP = "DspEncodeCap";
        /// <summary>
        /// Information HDVR pass each digital channel connected devices
        /// </summary>
        public static string CFG_CMD_HDVR_ATTR_CFG = "SystemAttr";
        public static string CFG_CMD_CHANNEL_HOLIDAY = "HolidaySchedule";
        /// <summary>
        /// Health email
        /// </summary>
        public static string CFG_CMD_HEALTH_MAIL = "HealthMail";
        /// <summary>
        /// Video division round robin configuration(The corresponding CFG_VIDEO_MATRIX)
        /// </summary>
        public static string CFG_CMD_SPLITTOUR = "SplitTour";
        /// <summary>
        /// Video codingROI(Region of Intrest)Configuration
        /// </summary>
        public static string CFG_CMD_VIDEOENCODEROI = "VideoEncodeROI";
        /// <summary>
        /// Metering Configuration(Corresponding CFG_VIDEO_INMETERING_INFO)
        /// </summary>
        public static string CFG_CMD_VIDEO_INMETERING = "VideoInMetering";
        /// <summary>
        /// Configure traffic statistics(Corresponding CFG_TRAFFIC_FLOWSTAT_INFO)
        /// </summary>
        public static string CFG_CMD_TRAFFIC_FLOWSTAT = "TrafficFlowStat";
        /// <summary>
        ///HDMI video matrix configurations
        /// </summary>
        public static string CFG_CMD_HDMIMATRIX = "HDMIMatrix";
        /// <summary>
        /// Video input front-end options(Corresponding CFG_VIDEO_IN_OPTIONS)
        /// </summary>
        public static string CFG_CMD_VIDEOINOPTIONS = "VideoInOptions";
        /// <summary>
        /// RTSP configuration( Corresponding CFG_RTSP_INFO_IN and CFG_RTSP_INFO_OUT )
        /// </summary>
        public static string CFG_CMD_RTSP = "RTSP";
        /// <summary>
        /// Intelligent traffic capture(CFG_TRAFFICSNAPSHOT_INFO)
        /// </summary>
        public static string CFG_CMD_TRAFFICSNAPSHOT = "TrafficSnapshotNew";
        /// <summary>
        /// Intelligent traffic capture(CFG_TRAFFICSNAPSHOT_NEW_INFO)
        /// </summary>
        public static string CFG_CMD_TRAFFICSNAPSHOT_MULTI = "TrafficSnapshotNew";
        /// <summary>
        ///Related multicast configuration(Corresponding CFG_MULTICASTS_INFO_IN and CFG_MULTICASTS_INFO_OUT)
        /// </summary>
        public static string CFG_CMD_MULTICAST = "Multicast";
        /// <summary>
        /// Video diagnostic parameter table(CFG_VIDEODIAGNOSIS_PROFILE)
        /// </summary>
        public static string CFG_CMD_VIDEODIAGNOSIS_PROFILE = "VideoDiagnosisProfile";
        /// <summary>
        /// Video diagnostic tasks table(CFG_VIDEODIAGNOSIS_TASK)
        /// </summary>
        public static string CFG_CMD_VIDEODIAGNOSIS_TASK = "VideoDiagnosisTask";
        /// <summary>
        /// Video diagnostic schedule(CFG_VIDEODIAGNOSIS_PROJECT)
        /// </summary>
        public static string CFG_CMD_VIDEODIAGNOSIS_PROJECT = "VideoDiagnosisProject";
        /// <summary>
        /// Video Diagnostics global table(CFG_VIDEODIAGNOSIS_GLOBAL)
        /// </summary>
        public static string CFG_CMD_VIDEODIAGNOSIS_GLOBAL = "VideoDiagnosisGlobal";
        /// <summary>
        /// Video diagnostic tasks table(CFG_VIDEODIAGNOSIS_TASK)
        /// </summary>
        public static string CFG_CMD_VIDEODIAGNOSIS_TASK_ONE = "VideoDiagnosisTask.x";
        /// <summary>
        /// Device configuration work status(CFG_TRAFFIC_WORKSTATE_INFO)
        /// </summary>
        public static string CFG_CMD_TRAFFIC_WORKSTATE = "WorkState";
        /// <summary>
        ///Disk storage group configuration(Corresponding CFG_STORAGEGROUP_INFO)
        /// </summary>
        public static string CFG_CMD_STORAGEDEVGROUP = "StorageDevGroup";
        /// <summary>
        /// Video storage configuration storage group(Corresponding CFG_RECORDTOGROUP_INFO)
        /// </summary>
        public static string CFG_CMD_RECORDTOGROUP = "RecordToGroup";
        /// <summary>
        /// Scene Intelligent Tracking Configuration(CFG_INTELLITRACKSCENE_INFO) 
        /// </summary>
        public static string CFG_CMD_INTELLITRACKSCENE = "IntelliTrackScene";
        /// <summary>
        /// Intelligent Frame rule configuration(CFG_ANALYSERULES_INFO)
        /// </summary>
        public static string CFG_CMD_IVSFRAM_RULE = "IVSFramRule";

        // The following configuration if not explicitly stated nothing to do with the channel, so each has a single-channel mode and all-channel mode
        // When the channel is independent, can only correspond to a single structure and the structure of the array is one of the channel number must be -1
        // When channel-related, single-channel mode (0 ~ n) corresponds to a single configuration structure, all channel mode (-1) corresponds to the configuration structure array
        /// <summary>
        /// Channel Name(AV_CFG_ChannelName)
        /// </summary>
        public static string CFG_CMD_CHANNELTITLE = "ChannelTitle";
        /// <summary>
        /// Video mode(AV_CFG_RecordMode)
        /// </summary>
        public static string CFG_CMD_RECORDMODE = "RecordMode";
        /// <summary>
        ///Video Output Properties(AV_CFG_VideoOutAttr)
        /// </summary>
        public static string CFG_CMD_VIDEOOUT = "VideoOut";
        /// <summary>
        /// Remote Device Information(Nothing to correspond AV_CFG_RemoteDevice array channel)
        /// </summary>
        public static string CFG_CMD_REMOTEDEVICE = "RemoteDevice";
        /// <summary>
        /// Remote access(AV_CFG_RemoteChannel)
        /// </summary>
        public static string CFG_CMD_REMOTECHANNEL = "RemoteChannel";
        /// <summary>
        /// Configuration screen rotation(Corresponding AV_CFG_MonitorTour), Not supported
        /// </summary>
        public static string CFG_CMD_MONITORTOUR = "MonitorTour";
        /// <summary>
        ///Screen Collection Configuration, Not supported
        /// </summary>
        public static string CFG_CMD_MONITORCOLLECTION = "MonitorCollection";
        /// <summary>
        /// Split screen display source configuration(Corresponding AV_CFG_ChannelDisplaySource)
        /// </summary>
        public static string CFG_CMD_DISPLAYSOURCE = "DisplaySource";
        /// <summary>
        /// Storage volume group configuration(Nothing to correspond AV_CFG_Raid array channel)
        /// </summary>
        public static string CFG_CMD_RAID = "Raid";
        /// <summary>
        /// Video source configuration(Corresponding AV_CFG_RecordSource)
        /// </summary>
        public static string CFG_CMD_RECORDSOURCE = "RecordSource";
        /// <summary>
        /// Video input color scheme(Corresponding AV_CFG_ChannelVideoColor)
        /// </summary>
        public static string CFG_CMD_VIDEOCOLOR = "VideoColor";
        /// <summary>
        /// Video encoding object allocation(Corresponding AV_CFG_VideoWidget)
        /// </summary>
        public static string CFG_CMD_VIDEOWIDGET = "VideoWidget";
        /// <summary>
        /// Storage group information(Nothing to correspond AV_CFG_StorageGroup array channel), Not supported
        /// </summary>
        public static string CFG_CMD_STORAGEGROUP = "StorageGroup";
        /// <summary>
        ///Zone configuration(Corresponding AV_CFG_Locales)
        /// </summary>
        public static string CFG_CMD_LOCALS = "Locales";
        /// <summary>
        ///Language Selection(Corresponding AV_CFG_Language)
        /// </summary>
        public static string CFG_CMD_LANGUAGE = "Language";
        /// <summary>
        /// Visit address filtering(Corresponding AV_CFG_AccessFilter)
        /// </summary>
        public static string CFG_CMD_ACCESSFILTER = "AccessFilter";
        /// <summary>
        /// Auto Maintenance(Corresponding AV_CFG_AutoMaintain)
        /// </summary>
        public static string CFG_CMD_AUTOMAINTAIN = "AutoMaintain";
        /// <summary>
        /// Remote device event processing(Array corresponds AV_CFG_RemoteEvent), Not supported
        /// </summary>
        public static string CFG_CMD_REMOTEEVENT = "RemoteEvent";
        /// <summary>
        /// TV wall configuration(Nothing to correspond AV_CFG_Monitor,Wall array channel)
        /// </summary>
        public static string CFG_CMD_MONITORWALL = "MonitorWall";
        /// <summary>
        /// Fusion-screen configuration(Array corresponds AV_CFG_SpliceScreen, Independent of the channel)
        /// </summary>
        public static string CFG_CMD_SPLICESCREEN = "VideoOutputComposite";
        /// <summary>
        /// Temperature alarm configuration(Corresponding AV_CFG_TemperatureAlarm, Independent of the channel)
        /// </summary>
        public static string CFG_CMD_TEMPERATUREALARM = "TemperatureAlarm";
        /// <summary>
        /// Fan speed alarm configuration(Corresponding AV_CFG_FanSpeedAlarm, Independent of the channel)
        /// </summary>
        public static string CFG_CMD_FANSPEEDALARM = "FanSpeedAlarm";
        /// <summary>
        /// Video backhaul configuration(Corresponding AV_CFG_RecordBackup, Independent of the channel)
        /// </summary>
        public static string CFG_CMD_RECORDBACKUP = "RecordBackupRestore.BitrateLimit";
        /// <summary>
        /// Recording device configuration backup return(AV_CFG_RemoteDevice[], Independent of the channel)
        /// </summary>
        public static string CFG_CMD_RECORDBACKUPDEVICE = "RecordBackupRestore.BackupDevices";
        /// <summary>
        /// ParkingSpace Light State (CFG_PARKINGSPACE_LIGHT_STATE, Independent of the channel)
        /// </summary>
        public static string CFG_CMD_PARKINGSPACE_LIGHT_STATE = "ParkingSpaceLightState";

          #endregion

        #region <<constant string--capability sets command  correspondence CLIENT_QueryNewSystemInfo>>
        /// <summary>
        /// video analysis ability(correspondence CFG_CAP_ANALYSE_INFO)
        /// </summary>
        public static string CFG_CAP_CMD_VIDEOANALYSE = "devVideoAnalyse.getCaps";
        /// <summary>
        /// get the on-line state of backing devices (correspondence CFG_REMOTE_DEVICE_STATUS)
        /// </summary>
        public static string CFG_NETAPP_REMOTEDEVICE = "netApp.getRemoteDeviceStatus";
        /// <summary>
        /// access Device information
        /// </summary>
        public static string CFG_CAP_CMD_PRODUCTDEFINITION = "magicBox.getProductDefinition";
        /// <summary>
        /// intelligent analysis of devices(correspondence CFG_DEVICE_ANALYSE_INFO) compatible with the old equipment
        /// </summary>
        public static string CFG_DEVICE_CAP_CMD_VIDEOANALYSE = "intelli.getVideoAnalyseDeviceChannels";
        /// <summary>
        /// Intelligent analysis ability of devices (correspondence CFG_CAP_DEVICE_ANALYSE_INFO)
        /// </summary>
        public static string CFG_DEVICE_CAP_NEW_CMD_VIDEOANALYSE = "devVideoAnalyse.factory.getCollect";
        /// <summary>
        /// get the CPU number
        /// </summary>
        public static string CFG_CAP_CMD_CPU_COUNT = "magicBox.getCPUCount";
        /// <summary>
        /// get the CPU usage
        /// </summary>
        public static string CFG_CAP_CMD_CPU_USAGE = "magicBox.getCPUUsage";
        /// <summary>
        /// get the memory capacity set
        /// </summary>
        public static string CFG_CAP_CMD_MEMORY_INFO = "magicBox.getMemoryInfo";
        /// <summary>
        /// get the information of device status 
        /// </summary>
        public static string CFG_CAP_CMD_DEVICE_STATE = "trafficSnap.getDeviceStatus";
        /// <summary>
        /// video input ability ((correspondence CFG_CAP_VIDEOINPUT_INFO)
        /// </summary>
        public static string CFG_CAP_CMD_VIDEOINPUT = "devVideoInput.getCaps";
        /// <summary>
        /// Get the information of all the active users(correspondence CFG_ACTIVEUSER_INFO)
        /// </summary>
        public static string CFG_USERMANAGER_ACTIVEUSER = "userManager.getActiveUserInfoAll";
        /// <summary>
        /// get the information of vidio statistical summaries (correspondence CFG_VIDEOSATA_SUMMARY_INFO)
        /// </summary>
        public static string CFG_CAP_VIDEOSTAT_SUMMARY = "videoStatServer.getSummary";
        /// <summary>
        /// (CFG_VIDEODIAGNOSIS_CAPS_INFO)
        /// </summary>
        public static string CFG_CAP_CMD_VIDEODIAGNOSIS_SERVER = "videoDiagnosisServer.getCaps";
        /// <summary>
        /// (CFG_VIDEODIAGNOSIS_GETCOLLECT_INFO)
        /// </summary>
        public static string CFG_CMD_VIDEODIAGNOSIS_GETCOLLECT = "videoDiagnosisServer.factory.getCollect";
        /// <summary>
        /// (CFG_VIDEODIAGNOSIS_GETSTATE_INFO)
        /// </summary>
        public static string CFG_CMD_VIDEODIAGNOSIS_GETSTATE = "videoDiagnosisServer.getState";

        #endregion

        #region <<  correspondence CLIENT_ParseData>>
        /// <summary>
        /// ATM video analysis capability (correspondence CFG_CAP_ATM_SCENE)
        /// </summary>
        public static string CFG_CAP_CMD_ATM_SCENE = "devVideoAnalyse.getCaps.ATM";
        /// <summary>
        /// common scene  video analysis capability (correspondence CFG_CAP_NORMAL_SCENE)
        /// </summary>
        public static string CFG_CAP_CMD_NORMAL_SCENE = "devVideoAnalyse.getCaps.Normal";
        #endregion

        #region <<Original Monitor Wall>>
        /// <summary>
        /// Load Monitor Wall Plan
        /// </summary>
        /// <param name="lLoginID">CLIENT_Login return value</param>
        /// <param name="pInParam">In Param , type = NET_IN_WM_LOAD_COLLECTION </param>
        /// <param name="pOutParam">Out Param , type = NET_OUT_WM_LOAD_COLLECTION</param>
        /// <param name="waittime">Wait Time</param>
        /// <returns></returns>
        [DllImport("dhnetsdk.dll")]
        private static extern bool CLIENT_LoadMonitorWallCollection(Int32 lLoginID, IntPtr pInParam ,  IntPtr pOutParam ,  Int32 waittime);


        /// <summary>
        /// Save Monitor Wall Plan
        /// </summary>
        /// <param name="lLoginID">CLIENT_Login return value</param>
        /// <param name="pInParam">In Param , type = NET_IN_WM_SAVE_COLLECTION </param>
        /// <param name="pOutParam">Out Param , type = NET_OUT_WM_LOAD_COLLECTION</param>
        /// <param name="waittime">Wait Time</param>
        /// <returns></returns>
        [DllImport("dhnetsdk.dll")]
        private static extern bool CLIENT_SaveMonitorWallCollection(Int32 lLoginID, IntPtr pInParam , IntPtr pOutParam ,  Int32 waittime);

        #endregion

        #region <<constant UInt32>>
        public static UInt32 RESERVED_TYPE_FOR_COMMON = 0x00000010;

        // query type,correspondence CLIENT_QueryDevState接口
        public static UInt32 NET_DEVSTATE_COMM_ALARM	=	0x0001;		// Query the status of general alarm (including external alarm, video missing, motion detect)
        public static UInt32 NET_DEVSTATE_SHELTER_ALARM=	0x0002;		// Query block alarm status
        public static UInt32 NET_DEVSTATE_RECORDING	=	0x0003;		// Query the status of the video
        public static UInt32 NET_DEVSTATE_DISK		=	0x0004;		// Query the hard disk information
        public static UInt32 NET_DEVSTATE_RESOURCE	=	0x0005;		//Query the system resource state 
        public static UInt32 NET_DEVSTATE_BITRATE	=		0x0006;		// Query channel stream
        public static UInt32 NET_DEVSTATE_CONN		=	0x0007	;	//Query the equipment connection status
        public static UInt32 NET_DEVSTATE_PROTOCAL_VER=	0x0008	;	// Query network protocol version number,pBuf = int*
        public static UInt32 NET_DEVSTATE_TALK_ECTYPE=		0x0009;		// Query equipment support voice intercom list format,as the structure DHDEV_TALKFORMAT_LIST
        public static UInt32 NET_DEVSTATE_SD_CARD	=		0x000A;		// Query SD card information (IPC products)
        public static UInt32 NET_DEVSTATE_BURNING_DEV=		0x000B;		// Query Recorders information
        public static UInt32 NET_DEVSTATE_BURNING_PROGRESS= 0x000C;		// Query Burn the progress
        public static UInt32 NET_DEVSTATE_PLATFORM	=	0x000D	;	// Query the device supports access platform
        public static UInt32 NET_DEVSTATE_CAMERA		=	0x000E	;	// Query camera attribute information (IPC products),pBuf = DHDEV_CAMERA_INFO *,There can be multiple structure
        public static UInt32 NET_DEVSTATE_SOFTWARE	=	0x000F	;	// Query Device software version information
        public static UInt32 NET_DEVSTATE_LANGUAGE    =    0x0010;		// Query The kinds of voice equipment support
        public static UInt32 NET_DEVSTATE_DSP		=		0x0011;		// Query DSP capability description(correspondence Structures DHDEV_DSP_ENCODECAP)
        public static UInt32	NET_DEVSTATE_OEM		=		0x0012;		// Query OEM information
        public static UInt32	NET_DEVSTATE_NET		=		0x0013;		// Query the running state of the network information
        public static UInt32 NET_DEVSTATE_TYPE		=	0x0014	;	// Query device type
        public static UInt32 NET_DEVSTATE_SNAP		=	0x0015	;	// Query Functional properties (IPC products)
        public static UInt32 NET_DEVSTATE_RECORD_TIME=		0x0016;		// Query the first video and recent video time
        public static UInt32 NET_DEVSTATE_NET_RSSI    =    0x0017   ;   // Query Wireless network signal strength, refer to structure DHDEV_WIRELESS_RSS_INFO
        public static UInt32 NET_DEVSTATE_BURNING_ATTACH	=0x0018	;	// Query Attachment burn options
       public static UInt32 NET_DEVSTATE_BACKUP_DEV = 0x0019; // Query a list of backup devices
        public static UInt32 NET_DEVSTATE_BACKUP_DEV_INFO = 0x001a; // Query Backup Device Details
        public static UInt32 NET_DEVSTATE_BACKUP_FEEDBACK = 0x001b; // backup progress feedback
        public static UInt32 NET_DEVSTATE_ATM_QUERY_TRADE = 0x001c; // QueryATM transaction types
        public static UInt32 NET_DEVSTATE_SIP = 0x001d; // Querysip status
        public static UInt32 NET_DEVSTATE_VICHILE_STATE = 0x001e; // Query vehicle wifi state
        public static UInt32 NET_DEVSTATE_TEST_EMAIL = 0x001f; // Query mail configuration is successful
        public static UInt32 NET_DEVSTATE_SMART_HARD_DISK = 0x0020; // Query HDD smart information
        public static UInt32 NET_DEVSTATE_TEST_SNAPPICTURE = 0x0021; // Query whether successful capture settings
        public static UInt32 NET_DEVSTATE_STATIC_ALARM = 0x0022; // Query static alarm status
        public static UInt32 NET_DEVSTATE_SUBMODULE_INFO = 0x0023; // Query equipment sub- module information
        public static UInt32 NET_DEVSTATE_DISKDAMAGE = 0x0024; // Query capacity hard disk damage
        public static UInt32 NET_DEVSTATE_IPC = 0x0025; /// Query device supports IPC capabilities, see the structure DH_DEV_IPC_INFO
        public static UInt32 NET_DEVSTATE_ALARM_ARM_DISARM = 0x0026; // Query arm and disarm the alarm state
        public static UInt32 NET_DEVSTATE_ACC_POWEROFF_ALARM = 0x0027; // QueryACC off alarm status ( returns a DWORD, 1 represents power , 0 energized )
        public static UInt32 NET_DEVSTATE_TEST_FTP_SERVER = 0x0028; // test the FTP server connection
        public static UInt32 NET_DEVSTATE_3GFLOW_EXCEED = 0x0029; // Query3G flow exceeds a threshold state ( see structure DHDEV_3GFLOW_EXCEED_STATE_INFO)
        public static UInt32 NET_DEVSTATE_3GFLOW_INFO = 0x002a; // Query3G network traffic information , see the structure DH_DEV_3GFLOW_INFO
        public static UInt32 NET_DEVSTATE_VIHICLE_INFO_UPLOAD = 0x002b; // Custom Car upload information ( see structure ALARM_VEHICLE_INFO_UPLOAD)
        public static UInt32 NET_DEVSTATE_SPEED_LIMIT = 0x002c; // Query speed alarm status ( see structure ALARM_SPEED_LIMIT)
        public static UInt32 NET_DEVSTATE_DSP_EX = 0x002d; // QueryDSP expansion capability description (correspondence structure DHDEV_DSP_ENCODECAP_EX)
        public static UInt32 NET_DEVSTATE_3GMODULE_INFO = 0x002e; // Query3G module information (correspondence structure DH_DEV_3GMODULE_INFO)
        public static UInt32 NET_DEVSTATE_MULTI_DDNS = 0x002f; // Query multiple DDNS status information (correspondence structure DH_DEV_MULTI_DDNS_INFO)
        public static UInt32 NET_DEVSTATE_CONFIG_URL = 0x0030; // Query device configuration URL information (correspondence structure DH_DEV_URL_INFO)
        public static UInt32 NET_DEVSTATE_HARDKEY = 0x0031 ;// QueryHardKey state (correspondence structure DHDEV_HARDKEY_STATE)
        public static UInt32 NET_DEVSTATE_VIRTUALCAMERA = 0x003a; //Query Virtual Camera (correspondence structure NET_VIRTUALCAMERA_STATE_INFO)
        public static UInt32 NET_DEVSTATE_WHOLE_RECORDING = 0x0048; // Query whole recording status(struct BOOL),as long as ther is a channel running,it indicates that the overall state
        public static UInt32 NET_DEVSTATE_DISK_RECORDE_TIME = 0x004a; // Query disk record time(pBuf = NET_DEV_DISK_RECORD_TIME*)
        public static UInt32 NET_DEVSTATE_DEV_CHN_COUNT = 0x0052; //Query Device channel info(correspondence structure NET_DEV_CHN_COUNT_INFO)
        #endregion

    }
    # region <<intelligent analysis of the type of event>>
    
    public sealed class EventIvs
    {
        //
        /// <summary>
        /// Subscribe to all events
        /// </summary>
        public  const UInt32 EVENT_IVS_ALL = 0x00000001;
        /// <summary>
        /// Cordon event
        /// </summary>
        public const UInt32 EVENT_IVS_CROSSLINEDETECTION = 0x00000002;
        /// <summary>
        /// Warning area events
        /// </summary>
        public const UInt32 EVENT_IVS_CROSSREGIONDETECTION = 0x00000003;
        /// <summary>
        /// Stickers Event
        /// </summary>
        public const UInt32 EVENT_IVS_PASTEDETECTION = 0x00000004;
        /// <summary>
        /// Articles legacy event
        /// </summary>
        public const UInt32 EVENT_IVS_LEFTDETECTION = 0x00000005;
        /// <summary>
        /// Stop events
        /// </summary>
        public const UInt32 EVENT_IVS_STAYDETECTION = 0x00000006;
        /// <summary>
        /// Hover events
        /// </summary>
        public const UInt32 EVENT_IVS_WANDERDETECTION = 0x00000007;
        /// <summary>
        /// Item Security Event
        /// </summary>
        public const UInt32 EVENT_IVS_PRESERVATION = 0x00000008;
        /// <summary>
        /// Move event
        /// </summary>
        public const UInt32 EVENT_IVS_MOVEDETECTION = 0x00000009;
        /// <summary>
        /// Trailing event
        /// </summary>
        public const UInt32 EVENT_IVS_TAILDETECTION = 0x0000000A;
        /// <summary>
        /// Mob event
        /// </summary>
        public const UInt32 EVENT_IVS_RIOTERDETECTION = 0x0000000B;
        /// <summary>
        /// Fire event
        /// </summary>
        public const UInt32 EVENT_IVS_FIREDETECTION = 0x0000000C;
        /// <summary>
        /// Smoke alarm events
        /// </summary>
        public const UInt32 EVENT_IVS_SMOKEDETECTION = 0x0000000D;
        /// <summary>
        /// Brawl
        /// </summary>
        public const UInt32 EVENT_IVS_FIGHTDETECTION = 0x0000000E;
        /// <summary>
        /// Traffic Statistics Events
        /// </summary>
        public const UInt32 EVENT_IVS_FLOWSTAT = 0x0000000F;
        /// <summary>
        /// Number of statistical events
        /// </summary>
        public const UInt32 EVENT_IVS_NUMBERSTAT = 0x00000010;
        /// <summary>
        /// Camera covering the event
        /// </summary>
        public const UInt32 EVENT_IVS_CAMERACOVERDDETECTION = 0x00000011;
        /// <summary>
        /// Camera movement events
        /// </summary>
        public const UInt32 EVENT_IVS_CAMERAMOVEDDETECTION = 0x00000012;
        /// <summary>
        /// Video abnormal events
        /// </summary>
        public const UInt32 EVENT_IVS_VIDEOABNORMALDETECTION = 0x00000013;
        /// <summary>
        /// Video damage event
        /// </summary>
        public const UInt32 EVENT_IVS_VIDEOBADDETECTION = 0x00000014;
        /// <summary>
        /// Traffic Control Incident
        /// </summary>
        public const UInt32 EVENT_IVS_TRAFFICCONTROL = 0x00000015;
        /// <summary>
        /// Accident events
        /// </summary>
        public const UInt32 EVENT_IVS_TRAFFICACCIDENT = 0x00000016;
        /// <summary>
        /// Traffic junctions event
        /// </summary>
        public const UInt32 EVENT_IVS_TRAFFICJUNCTION = 0x00000017;
        /// <summary>
        /// Traffic bayonet event
        /// </summary>
        public const UInt32 EVENT_IVS_TRAFFICGATE = 0x00000018;
        /// <summary>
        /// Capture traffic incident
        /// </summary>
        public const UInt32 EVENT_TRAFFICSNAPSHOT = 0x00000019;
        /// <summary>
        /// Face Detection Event
        /// </summary>
        public const UInt32 EVENT_IVS_FACEDETECT = 0x0000001A;
        /// <summary>
        /// Traffic congestion event
        /// </summary>
        public const UInt32 EVENT_IVS_TRAFFICJAM = 0x0000001B;
        /// <summary>
        /// Traffic violation - red light incident
        /// </summary>
        public const UInt32 EVENT_IVS_TRAFFIC_RUNREDLIGHT = 0x00000100;
        /// <summary>
        /// Traffic violation - Pressure lane incident
        /// </summary>
        public const UInt32 EVENT_IVS_TRAFFIC_OVERLINE = 0x00000101;
        /// <summary>
        /// Traffic violation - retrograde event
        /// </summary>
        public const UInt32 EVENT_IVS_TRAFFIC_RETROGRADE = 0x00000102;
        /// <summary>
        /// Traffic violation - illegal left turn
        /// </summary>
        public const UInt32 EVENT_IVS_TRAFFIC_TURNLEFT = 0x00000103;
        /// <summary>
        /// Traffic violation - illegal right turn
        /// </summary>
        public const UInt32 EVENT_IVS_TRAFFIC_TURNRIGHT = 0x00000104;
        /// <summary>
        /// Traffic violation - illegal U-turn
        /// </summary>
        public const UInt32 EVENT_IVS_TRAFFIC_UTURN = 0x00000105;
        /// <summary>
        /// Traffic violations - speeding
        /// </summary>
        public const UInt32 EVENT_IVS_TRAFFIC_OVERSPEED = 0x00000106;
        /// <summary>
        /// Traffic violation - low
        /// </summary>
        public const UInt32 EVENT_IVS_TRAFFIC_UNDERSPEED = 0x00000107;
        /// <summary>
        /// Traffic violation - illegal parking
        /// </summary>
        public const UInt32 EVENT_IVS_TRAFFIC_PARKING = 0x00000108;
        /// <summary>
        /// Traffic violation - not traveling by lane
        /// </summary>
        public const UInt32 EVENT_IVS_TRAFFIC_WRONGROUTE = 0x00000109;
        /// <summary>
        /// Traffic violation - illegal lane change
        /// </summary>
        public const UInt32 EVENT_IVS_TRAFFIC_CROSSLANE = 0x0000010A;
        ///<summary>
        /// Traffic violation - press the yellow line
        /// </summary>
        public const UInt32 EVENT_IVS_TRAFFIC_OVERYELLOWLINE = 0x0000010B;
        /// <summary>
        /// Traffic violation - driving incident shoulder
        /// </summary>
        public const UInt32 EVENT_IVS_TRAFFIC_DRIVINGONSHOULDER = 0x0000010C;
        /// <summary>
        /// Traffic violation - Yellow car lane and events
        /// </summary>
        public const UInt32 EVENT_IVS_TRAFFIC_YELLOWPLATEINLANE = 0x0000010E;
        /// <summary>
        /// Traffic violation - zebra pedestrian priority event
        /// </summary>
        public const UInt32 EVENT_IVS_TRAFFIC_PEDESTRAINPRIORITY = 0X0000010F;
        /// <summary>
        /// Event over the fence
        /// </summary>
        public const UInt32 EVENT_IVS_CROSSFENCEDETECTION = 0x0000011F;
        /// <summary>
        /// EDM Event
        /// </summary>
        public const UInt32 EVENT_IVS_ELECTROSPARKDETECTION = 0X00000110;
        /// <summary>
        /// Traffic violation - closed to traffic incidents
        /// </summary>
        public const UInt32 EVENT_IVS_TRAFFIC_NOPASSING = 0x00000111;
        /// <summary>
        /// Exception run incident
        /// </summary>
        public  const UInt32 EVENT_IVS_ABNORMALRUNDETECTION = 0x00000112;
        /// <summary>
        /// Staff retrograde event
        /// </summary>
        public  const UInt32 EVENT_IVS_RETROGRADEDETECTION = 0x00000113;
        /// <summary>
        /// Detect events in the region
        /// </summary>
        public  const UInt32 EVENT_IVS_INREGIONDETECTION = 0x00000114;
        /// <summary>
        /// Objects move event
        /// </summary>
        public  const UInt32 EVENT_IVS_TAKENAWAYDETECTION = 0x00000115;
        /// <summary>
        /// Illegal parking incident
        /// </summary>
        public  const UInt32 EVENT_IVS_PARKINGDETECTION = 0x00000116;
        /// <summary>
        /// Recognition Event
        /// </summary>
        public  const UInt32 EVENT_IVS_FACERECOGNITION = 0x00000117;
        /// <summary>
        /// Traffic Manual capture event
        /// </summary>
        public  const UInt32 EVENT_IVS_TRAFFIC_MANUALSNAP = 0x00000118;
        /// <summary>
        /// Traffic statistics event
        /// </summary>
        public  const UInt32 EVENT_IVS_TRAFFIC_FLOWSTATE = 0x00000119;
        /// <summary>
        /// Transport stranded event
        /// </summary>
        public  const UInt32 EVENT_IVS_TRAFFIC_STAY = 0x0000011A;
        /// <summary>
        /// Have a car lane and events
        /// </summary>
        public  const UInt32 EVENT_IVS_TRAFFIC_VEHICLEINROUTE = 0x0000011B;
        /// <summary>
        /// Video motion detection event
        /// </summary>
        public  const UInt32 EVENT_ALARM_MOTIONDETECT = 0x0000011C;
        /// <summary>
        /// External alarm events
        /// </summary>
        public  const UInt32 EVENT_ALARM_LOCALALARM = 0x0000011D;
        /// <summary>
        /// Detention of prisoners up event
        /// </summary>
        public const UInt32 EVENT_IVS_PRISONERRISEDETECTION = 0X0000011E;
        /// <summary>
        /// Traffic bayonet event
        /// </summary>
        public const UInt32 EVENT_IVS_TRAFFIC_TOLLGATE = 0X00000120;
        /// <summary>
        /// Personnel -intensive detection
        /// </summary>
        public const UInt32 EVENT_IVS_DENSITYDETECTION = 0x00000121;
        /// <summary>
        /// Video diagnosis event
        /// </summary>
        public const UInt32 EVENT_IVS_VIDEODIAGNOSIS = 0X00000122;
        /// <summary>
        /// Parking space paring
        /// </summary>
        public const UInt32 EVENT_IVS_TRAFFIC_PARKINGSPACEPARKING  = 0x0000012B;   
        /// <summary>
        /// Parking space no paring
        /// </summary>
        public const UInt32 EVENT_IVS_TRAFFIC_PARKINGSPACENOPARKING = 0x0000012C;
        /// <summary>
        /// Parking space OverLine
        /// </summary>
        public const UInt32 EVENT_IVS_TRAFFIC_PARKINGSPACEOVERLINE = 0x00000134;       
        /// <summary>
        /// To all the events at the beginning of the traffic, currently refers
        /// EVENT_IVS_TRAFFICCONTROL -> EVENT_TRAFFICSNAPSHOT
        /// EVENT_IVS_TRAFFIC_RUNREDLIGHT -> EVENT_IVS_TRAFFIC_UNDERSPEED
        /// </summary>
        public const UInt32 EVENT_IVS_TRAFFIC_ALL = 0x000001FF;
    }
    #endregion

    #endregion

    # region <<delegate>>

    /// <summary>
    /// Disconnection callback function , the callback of the current network equipment has been disconnected , a call to the SDK ClIENT_LogOut () function of the device is not active disconnect callback
    /// </summary>
    /// <param Name="lLoginID"> device user logon handle </param>
    /// <param Name="pchDVRIP"> DVR device IP </param>
    /// <param Name="nDVRPort"> DVR device connection port </param>
    /// <param Name="dwUser"> user data </param>
    public delegate void fDisConnect (
        int lLoginID, StringBuilder pchDVRIP, int nDVRPort, IntPtr dwUser);

    /// <summary>
    /// Device message callback
    /// </summary>
    /// <param Name="lCommand"> callback type </param>
    /// <param Name="lLoginID"> device user login ID: <seealso cref="CLIENT_Login"/> return value </param>
    /// <param Name="pBuf"> receive buffer alarm data , according to the listener interface and lCommand call different values , different filling data </param>
    /// <param Name="dwBufLen"> pBuf length [ in bytes ] </param>
    /// <param Name="pchDVRIP"> device IP </param>
    /// <param Name="nDVRPort"> device port </param>
    /// <param Name="dwUser"> callback user data </param>
    /// <returns> True: success ; false: failed </returns>
     public delegate bool fMessCallBack (int lCommand, int lLoginID, IntPtr pBuf, UInt32 dwBufLen, IntPtr pchDVRIP, int nDVRPort, UInt32 dwUser);

    /// <summary>
    /// Listener callback function
    /// </summary>
    /// <param Name="lHandle"> callback message server handles </param>
    /// <param Name="pIp"> uploaded equipment Ip message </param>
    /// <param Name="wPort"> upload device Port message </param>
    /// <param Name="lCommand"> callback type </param>
    /// <param Name="pParam"> receive buffer alarm data , according to the listener interface and lCommand call different values , different filling data </param>
    /// <param Name="dwParamLen"> pParam length [ in bytes ] </param>
    /// <param Name="dwUserData"> user -defined data callback </param>
    /// <returns> </returns>
    public delegate int fServiceCallBack (
        int lHandle, string pIp, ushort wPort, int lCommand, IntPtr pParam, ushort dwParamLen, IntPtr dwUserData);

    /// <summary>
    /// Progress callback function
    /// </summary>
    /// <param Name="lPlayHandle"> player handles : <seealso cref="CLIENT_PlayBackByRecordFile"/> return value </param>
    /// <param Name="dwTotalSize"> refers to the total size of this play , the unit is KB </param>
    /// <param Name="dwDownLoadSize"> means already playing size in KB, indicating the end of this back on defense </param> When the value -1
    /// <param Name="dwUser"> user data </param>
    public delegate void fDownLoadPosCallBack (int lPlayHandle, UInt32 dwTotalSize, UInt32 dwDownLoadSize, IntPtr dwUser);


    public delegate void fTimeDownLoadPosCallBack (
            int lPlayHandle, int dwTotalSize, int dwDownLoadSize, int index, NET_RECORDFILE_INFO recordfileinfo, IntPtr dwUser);

    /// <summary>
    /// Drawing callback
    /// </summary>
    /// <param Name="lLoginID"> device user logon handle : <seealso cref="CLIENT_Login"/> return value identifies the device </param>
    /// <param Name="lPlayHandle"> player handles real-time monitoring : <seealso cref="CLIENT_RealPlay"/> return value identifies the channel. </param>
    /// <param Name="hDC"> is a pointer to the entire screen area to display the drawing board , according to the needs of users can be anywhere on the overlay display </param>
    /// <param Name="dwUser"> user data , user data is entered above </param>
    public delegate void fDrawCallBack (int lLoginID, int lPlayHandle, IntPtr hDC, IntPtr dwUser);

    /// <summary>
    /// Real-time monitoring data callback
    /// </summary>
    /// <param Name="lRealHandle"> CLIENT_RealPlay return value </param>
    /// <param Name="dwDataType">
    /// Callback from the data type identifier , if the callback is set , the following four kinds of data are out of the callback , the user can select the required data processing section ;
    /// 0: raw data ( the data are consistent with the preservation SaveRealData ) ;
    /// 1: The standard video data ;
    /// 2: yuv data ;
    /// 3: pcm audio data ;
    /// </param>
    /// <param Name="pBuffer"> callback data , depending on the data type of each callback different lengths of data , in addition to Type 0 , other data types are in frames , each frame of data callback </param>
    /// Length <param name="dwBufSize"> callback data ( in bytes ) </param>
    /// <param Name="dwUser"> user data </param>
    public delegate void fRealDataCallBack (int lRealHandle, UInt32 dwDataType, IntPtr pBuffer, UInt32 dwBufSize, IntPtr dwUser);

    /// <summary>
    /// Real-time monitoring data callback ( real-time monitoring data callback )
    /// </summary>
    /// <param Name="lRealHandle"> real-time monitoring ID </param>
    /// <param Name="dwDataType">
    /// Callback from the data type identified , only the identified data set will callback dwFlag out :
    /// 0: raw data ( the data are consistent with the preservation SaveRealData ) ;
    /// 1: The standard video data ;
    /// 2: yuv data
    /// 3: pcm audio data
    /// </param>
    /// <param Name="pBuffer"> callback data , depending on the data type of each callback different lengths of data , in addition to Type 0 , other data types are in frames , each frame of data callback </param>
    /// <param Name="dwBufSize"> callback data length , depending on the type, length or different ( in bytes ) </param>
    /// <param Name="param"> callback parameter data structure , depending on the type of the parameter structure is inconsistent, when the type is 0 ( raw data ) and 2 (YUV data ) when 0 </param>
    /// <param Name="dwUser"> user data , user data is entered above </param>
    public delegate void fRealDataCallBackEx (int lRealHandle, UInt32 dwDataType, IntPtr pBuffer, UInt32 dwBufSize, int param, IntPtr dwUser);

    /// <summary> Real-time monitoring data callback ( real-time monitoring data callback ) </summary>
    /// <param Name="lRealHandle"> real-time monitoring ID </param>
    /// <param Name="dwDataType">
    /// Callback from the data type identified , only the identified data set will callback dwFlag out :
    /// 0: raw data ( the data are consistent with the preservation SaveRealData ) ;
    /// 1: The standard video data ;
    /// 2: yuv data
    /// 3: pcm audio data
    /// </param>
    /// <param Name="pBuffer"> callback data , depending on the data type of each callback different lengths of data , in addition to Type 0 , other data types are in frames , each frame of data callback </param>
    /// <param Name="dwBufSize"> callback data length , depending on the type, length or different ( in bytes ) </param>
    /// <param Name="param"> callback parameter data structure , depending on the type of the parameter structure is inconsistent, when the type is 0 ( raw data ) and 2 (YUV data ) when 0 </param>
    /// <param Name="dwUser"> user data , user data is entered above </param>
    /// <returns>
    /// Return value will affect the internal operation of the SDK callback function :
    /// 1 : Represents the callback is successful, nothing special circumstances should return this value
    /// 0 : represents the application buffer is full , the network SDK will pause a little while (ms level ) , then the callback of the same data , generally used for data speed control.
    /// -1: Representatives of system error , the direct end playback threads, caution
    /// </returns>
    public delegate int fDataCallBack (int lRealHandle, UInt32 dwDataType, IntPtr pBuffer, UInt32 dwBufSize, UInt32 dwUser);

    /// <summary>
    /// Real-time intelligent analysis of data uploaded - Pictures callback
    /// </summary>
    /// <param Name="lAnalyzerHandle"> </param>
    /// <param Name="dwAlarmType"> </param>
    /// <param Name="pAlarmInfo"> </param>
    /// <param Name="pBuffer"> </param>
    /// <param Name="dwBufSize"> </param>
    /// <param Name="dwUser"> </param>
    /// <param Name="nSequence"> said upload the same picture , the 0 is the first time said ,
    /// 2 means the last or only appear once , there is a representation of this after </param>
    /// <param Name="reserved"> int nState = (int *) reserved indicates the current state of the data callback , 0 means the current data for the real-time data ,
    /// 1 indicates that the current correction data are offline data for 2:00 indicates the end of the offline data transfer </param>
    /// <returns> </returns>
    public delegate int fAnalyzerDataCallBack (Int32 lAnalyzerHandle, UInt32 dwAlarmType, IntPtr pAlarmInfo, IntPtr pBuffer, UInt32 dwBufSize, UInt32 dwUser, Int32 nSequence, IntPtr reserved);

    /// <summary>
    ///// Grab the callback function prototype
    /// </summary>
    /// <param Name="lLoginID"> </param>
    /// <param Name="pBuf"> </param>
    /// <param Name="RevLen"> </param>
    /// <param Name="EncodeType"> </param>
    /// <param Name="CmdSerial"> </param>
    /// <param Name="dwUser"> </param>
    public delegate void fSnapRev (Int32 lLoginID, IntPtr pBuf, UInt32 RevLen, UInt32 EncodeType, UInt32 CmdSerial, UInt32 dwUser);


    /// <summary>
    /// Asynchronous callback search equipment
    /// </summary>
    /// <param Name="pDevNetInfo"> </param>
    /// <param Name="pUserData"> </param>
    public delegate void fSearchDevicesCB (IntPtr pDevNetInfo, IntPtr pUserData);

    /// <summary>
    /// Asynchronous callback Transcom Data CallBack
    /// </summary>
    public delegate void fTransComCallBack(int lLoginID, int lTransComChannel,string pBuffer, int dwBufSize, IntPtr dwUser);

    /// <summary>
    /// Callback function prototype program to upgrade equipment
    /// </summary>
    /// <param Name="lLoginID"> </param>
    /// <param Name="pBuf"> </param>
    /// <param Name="RevLen"> </param>
    /// <param Name="EncodeType"> </param>
    /// <param Name="CmdSerial"> </param>
    /// <param Name="dwUser"> </param>
    public delegate void fUpgradeCallBack (Int32 lLoginID, UInt32 lUpgradechannel, Int32 nTotalSize, Int32 nSendSize, UInt32 dwUser);

    /// <summary>
    /// Callback function prototype program to Audio Data
    /// </summary>
    /// <param Name="lTalkHandle"> </param>
    /// <param Name="pDataBuf"> </param>
    /// <param Name="dwBufSize"> </param>
    /// <param Name="byAudioFlag"> </param>
    /// <param Name="dwUser"> </param>
    public delegate void fAudioDataCallBack(Int32 lTalkHandle, byte[] pDataBuf, Int32 dwBufSize, byte byAudioFlag, IntPtr dwUser);
    # endregion

    # region << enum definition >>

    /// <summary>
    /// Real Player Types
    /// </summary>
    public enum REALPLAY_TYPE
    {
        NET_RType_RealPlay = 0,
        NET_RType_Multiplay,
        NET_RType_RealPlay_0,
        NET_RType_RealPlay_1,
        NET_RType_RealPlay_2,
        NET_RType_RealPlay_3,
        NET_RType_Multiplay_1,
        NET_RType_Multiplay_4,
        NET_RType_Multiplay_8,
        NET_RType_Multiplay_9,
        NET_RType_Multiplay_16,
        NET_RType_Multiplay_6,                       
        NET_RType_Multiplay_12,                     
        NET_RType_Multiplay_25,                      
        NET_RType_Multiplay_36,                      
    }

    /// <summary>
    /// Playback control commands
    /// </summary>
    public enum PLAY_CONTROL
    {
        /// <summary>
        /// Play
        /// </summary>
        Play,
        /// <summary>
        /// Pause
        /// </summary>
        Pause,
        /// <summary>
        /// Stop
        /// </summary>
        Stop,
        /// <summary>
        /// Drag play [Time Offset ]
        /// </summary>
        SeekByTime,
        /// <summary>
        /// Drag play [ byte offset ]
        /// </summary>
        SeekByBit,
        /// <summary>
        /// Step Play starts [ called once played a ]
        /// </summary>
        StepPlay,
        /// <summary>
        /// Step Play Stop
        /// </summary>
        StepStop,
        /// <summary>
        /// Quick release
        /// </summary>
        Fast,
        /// <summary>
        /// Slow
        /// </summary>
        Slow
    }

    /// <summary>
    /// PTZ control commands
    /// </summary>
    public enum PTZ_CONTROL
    {
        /// <summary>
        /// On
        /// </summary>
        PTZ_UP_CONTROL = 0,
        /// <summary>
        /// Under
        /// </summary>
        PTZ_DOWN_CONTROL,
        /// <summary>
        /// Left
        /// </summary>
        PTZ_LEFT_CONTROL,
        /// <summary>
        /// R
        /// </summary>
        PTZ_RIGHT_CONTROL,
        /// <summary>
        /// Zoom +
        /// </summary>
        PTZ_ZOOM_ADD_CONTROL,
        /// <summary>
        /// Zoom -
        /// </summary>
        PTZ_ZOOM_DEC_CONTROL,
        /// <summary>
        /// Focus +
        /// </summary>
        PTZ_FOCUS_ADD_CONTROL,
        /// <summary>
        /// Focus -
        /// </summary>
        PTZ_FOCUS_DEC_CONTROL,
        /// <summary>
        /// Aperture +
        /// </summary>
        PTZ_APERTURE_ADD_CONTROL,
        /// <summary>
        /// Iris -
        /// </summary>
        PTZ_APERTURE_DEC_CONTROL,
        /// <summary>
        /// Go preset
        /// </summary>
        PTZ_POINT_MOVE_CONTROL,
        /// <summary>
        /// Set
        /// </summary>
        PTZ_POINT_SET_CONTROL,
        /// <summary>
        /// Delete
        /// </summary>
        PTZ_POINT_DEL_CONTROL,
        /// <summary>
        /// Point in round robin
        /// </summary>
        PTZ_POINT_LOOP_CONTROL,
        /// <summary>
        /// Lights wipers
        /// </summary>
        PTZ_LAMP_CONTROL,
        /// <summary>
        /// Top-left : p1 horizontal velocity , p2 vertical speed
        /// </summary>
        EXTPTZ_LEFTTOP = 0X20,
        /// <summary>
        /// Top right : p1 horizontal velocity , p2 vertical speed
        /// </summary>
        EXTPTZ_RIGHTTOP,
        /// <summary>
        /// Left : p1 horizontal velocity , p2 vertical speed
        /// </summary>
        EXTPTZ_LEFTDOWN,
        /// <summary>
        /// Right : p1 horizontal velocity , p2 vertical speed
        /// </summary>
        EXTPTZ_RIGHTDOWN,
        /// <summary>
        /// Add preset point to cruise : p1 p2 preset value cruise line
        /// </summary>
        EXTPTZ_ADDTOLOOP,
        /// <summary>
        /// Delete cruise preset : p1 p2 preset value cruise line
        /// </summary>
        EXTPTZ_DELFROMLOOP,
        /// <summary>
        /// Clear Cruise : p1 Cruise Line
        /// </summary>
        EXTPTZ_CLOSELOOP,
        /// <summary>
        /// Start horizontal rotation
        /// </summary>
        EXTPTZ_STARTPANCRUISE,
        /// <summary>
        /// Stop horizontal rotation
        /// </summary>
        EXTPTZ_STOPPANCRUISE,
        /// <summary>
        /// Set the left margin
        /// </summary>
        EXTPTZ_SETLEFTBORDER,
        /// <summary>
        /// Set the right margin
        /// </summary>
        EXTPTZ_RIGHTBORDER,
        /// <summary>
        /// Start line scan
        /// </summary>
        EXTPTZ_STARTLINESCAN,
        /// <summary>
        /// Stop line scan
        /// </summary>
        EXTPTZ_CLOSELINESCAN,
        /// <summary>
        /// Set the start mode : Mode Line
        /// </summary>
        EXTPTZ_SETMODESTART,
        /// <summary>
        /// Set the mode ends : Mode Line
        /// </summary>
        EXTPTZ_SETMODESTOP,
        /// <summary>
        /// Run mode : p1 mode line
        /// </summary>
        EXTPTZ_RUNMODE,
        /// <summary>
        /// Stop mode : p1 mode line
        /// </summary>
        EXTPTZ_STOPMODE,
        /// <summary>
        /// Clear mode : p1 mode line
        /// </summary>
        EXTPTZ_DELETEMODE,
        /// <summary>
        /// Flip command
        /// </summary>
        EXTPTZ_REVERSECOMM,
        /// <summary>
        /// Horizontal coordinate quickly locate p1 p2 p3 vertical coordinate Zoom
        /// </summary>
        EXTPTZ_FASTGOTO,
        /// <summary>
        /// X34: Auxiliary switch on the auxiliary point p1
        /// </summary>
        EXTPTZ_AUXIOPEN,
        /// <summary>
        /// 0x35: Auxiliary switch off the auxiliary point p1
        /// </summary>
        EXTPTZ_AUXICLOSE,
        /// <summary>
        /// Open menu ball machine
        /// </summary>
        EXTPTZ_OPENMENU = 0X36,
        /// <summary>
        /// Close the menu
        /// </summary>
        EXTPTZ_CLOSEMENU,
        /// <summary>
        /// Menu OK
        /// </summary>
        EXTPTZ_MENUOK,
        /// <summary>
        /// Menu Cancel
        /// </summary>
        EXTPTZ_MENUCANCEL,
        /// <summary>
        /// Menu
        /// </summary>
        EXTPTZ_MENUUP,
        /// <summary>
        /// Menu
        /// </summary>
        EXTPTZ_MENUDOWN,
        /// <summary>
        /// Menu Left
        /// </summary>
        EXTPTZ_MENULEFT,
        /// <summary>
        /// Menu Right
        /// </summary>
        EXTPTZ_MENURIGHT,
        /// <summary>
        /// Maximum command value
        /// </summary>
        EXTPTZ_TOTAL
    }

    /// <summary>
    /// Video file types
    /// </summary>
    public enum RECORD_FILE_TYPE
    {
        /// <summary>
        /// 0 : All video files
        /// </summary>
        ALLRECORDFILE,
        /// <summary>
        /// 1: external alarm
        /// </summary>
        OUTALARM,
        /// <summary>
        /// 2: motion detection alarm
        /// </summary>
        DYNAMICSCANALARM,
        /// <summary>
        /// 3: All alarms
        /// </summary>
        ALLALARM,
        /// <summary>
        /// 4: Card Number Query
        /// </summary>
        CARDNOSEACH,
        /// <summary>
        /// 5: Query combination of conditions
        /// </summary>
        COMBINEDSEACH
    }

    /// <summary>
    /// Formulation command
    /// </summary>
    public enum CONFIG_COMMAND
    {
        /// <summary>
        /// 1 : Get device parameters , see DHDEV_SYSTEM_ATTR_CFG
        /// </summary>
        NET_DEV_DEVICECFG = 1,
        /// <summary>
        /// 2 : Get the network parameters , see DHDEV_NET_CFG
        /// </summary>
        NET_DEV_NETCFG = 2,
        /// <summary>
        /// 3 : Get channel configuration - image and compression parameters , see DHDEV_CHANNEL_CFG
        /// </summary>
        NET_DEV_CHANNELCFG = 3,
        /// <summary>
        /// 4 : Get preview parameters , see DHDEV_PREVIEW_CFG
        /// </summary>
        NET_DEV_PREVIEWCFG = 4,
        /// <summary>
        /// 5 : Get recording time parameters , see DHDEV_RECORD_CFG
        /// </summary>
        NET_DEV_RECORDCFG = 5,
        /// <summary>
        /// 6 : Get the serial port parameters , see DHDEV_COMM_CFG
        /// </summary>
        NET_DEV_COMMCFG = 6,
        /// <summary>
        /// 7 : Get alarm parameters , see DHDEV_ALARM_SCHEDULE
        /// </summary>
        NET_DEV_ALARMCFG = 7,
        /// <summary>
        /// 8 : Get the DVR time , see NET_TIME structure
        /// </summary>
        NET_DEV_TIMECFG = 8,
        /// <summary>
        /// 9: Intercom parameters , see DHDEV_TALK_CFG
        /// </summary>
        DH_DEV_TALKCFG = 9,
        /// <summary>
        /// 10: Configure Automatic Maintenance
        /// </summary>
        NET_DEV_AUTOMTCFG = 10,
        /// <summary>
        /// 11 : Local matrix control policy configuration
        /// </summary>
        NET_DEV_video_MARTIX = 11,
        /// <summary>
        /// 12 : Multi ddns server configuration
        /// </summary>
        NET_DEV_MULTI_DDNS = 12,
        /// <summary>
        /// 13: Grab configuration
        /// </summary>
        NET_DEV_SNAP_CFG = 13,
        /// <summary>
        /// 14: HTTP path configuration
        /// </summary>
        NET_DEV_WEB_URL_CFG = 14,
        /// <summary>
        /// 15: FTP upload configuration
        /// </summary>
        DH_DEV_FTP_PROTO_CFG = 15,
        /// <summary>
        /// 16: platform access configuration , then channel parameter represents the type of platform , such as the 11 representatives of U Netcom
        /// </summary>
        DH_DEV_INTERVIDEO_CFG = 16,
        /// <summary>
        /// IP filtering configuration extension (correspondence structure DHDEV_IPIFILTER_CFG_EX)
        /// </summary>
        NET_DEV_IPFILTER_CFG_EX = 0x0056,
        /// <summary>
        /// MAC, IP filtering ( requires ip, mac is eleven correspondence of ) configuration (correspondence structure DHDEV_MACIPFILTER_CFG)
        /// </summary>
        NET_DEV_MACIPFILTER_CFG = 0x0074,
        /// <summary>
        /// Stream encryption configuration (correspondence structure DHEDV_STREAM_ENCRYPT)
        /// </summary>
        NET_DEV_STREAM_ENCRYPT_CFG = 0x0055,
        /// <summary>
        /// Local alarm configuration ( structure DH_ALARMIN_CFG_EX)
        /// </summary>
        NET_DEV_LOCALALARM_CFG = 0x0039,
    }

    /// <summary>
    /// Device Model (DVR type )
    /// </summary>
    public enum NET_DEVICE_TYPE
    {
        NET_PRODUCT_NONE = 0,
        /// <summary>
        /// Non-real time MACE
        /// </summary>
        NET_DVR_NONREALTIME_MACE,
        /// <summary>
        /// Non-real time
        /// </summary>
        NET_DVR_NONREALTIME,
        /// <summary>
        /// Network Video Server
        /// </summary>
        NET_NVS_MPEG1,
        /// <summary>
        /// MPEG1 Road Recorder
        /// </summary>
        NET_DVR_MPEG1_2,
        /// <summary>
        /// MPEG1 eight Recorder
        /// </summary>
        NET_DVR_MPEG1_8,
        /// <summary>
        /// MPEG4 video recorder eight
        /// </summary>
        NET_DVR_MPEG4_8,
        /// <summary>
        /// MPEG4 video recorder Sixteenth Street
        /// </summary>
        NET_DVR_MPEG4_16,
        /// <summary>
        /// MPEG4 video recorder , as new Sixteenth Street
        /// </summary>
        NET_DVR_MPEG4_SX2,
        /// <summary>
        /// MPEG4 Vision Recorder
        /// </summary>
        NET_DVR_MEPG4_ST2,
        /// <summary>
        /// MPEG4 video recorder , as ho
        /// </summary>
        NET_DVR_MEPG4_SH2,
        /// <summary>
        /// MPEG4 video recorder Enhanced Vision II
        /// </summary>
        NET_DVR_MPEG4_GBE,
        /// <summary>
        /// MPEG4 Network Video Server II generation
        /// </summary>
        NET_DVR_MPEG4_NVSII,
        /// <summary>
        /// New standard configuration protocol
        /// </summary>
        NET_DVR_STD_NEW,
        /// <summary>
        /// DDNS server
        /// </summary>
        NET_DVR_DDNS
    } ;

    /// <summary>
    /// Query log expansion interface parameters: log type
    /// </summary>
    public enum NET_LOG_QUERY_TYPE
    {
        /// <summary>
        /// All of the log
        /// </summary>
        NETLOG_ALL = 0,
        /// <summary>
        /// System log
        /// </summary>
        DHLOG_SYSTEM,
        /// <summary>
        /// Configuration log
        /// </summary>
        NETLOG_CONFIG,
        /// <summary>
        /// Storage-related
        /// </summary>
        NETLOG_STORAGE,
        /// <summary>
        /// Alarm log
        /// </summary>
        NETLOG_ALARM,
        /// <summary>
        /// Video related
        /// </summary>
        NETLOG_RECORD,
        /// <summary>
        /// Account Related
        /// </summary>
        NETLOG_ACCOUNT,
        /// <summary>
        /// Clear Log
        /// </summary>
        NETLOG_CLEAR,
        /// <summary>
        /// Playback -related
        /// </summary>
        NETLOG_PLAYBACK
    }

    /// <summary>
    /// Type logs
    /// </summary>
    public enum NET_LOG_TYPE
    {
        /// <summary>
        /// Re-starting the application
        /// </summary>
        NET_LOG_REBOOT = 0x0000,
        /// <summary>
        /// Close the application
        /// </summary>
        NET_LOG_SHUT,
        /// <summary>
        /// Save the preparation
        /// </summary>
        NET_LOG_CONFSAVE = 0x0100,
        /// <summary>
        /// Read configuration
        /// </summary>
        NET_LOG_CONFLOAD,
        /// <summary>
        /// File system errors
        /// </summary>
        NET_LOG_FSERROR = 0x0200,
        /// <summary>
        /// HDD write error
        /// </summary>
        NET_LOG_HDD_WERR,
        /// <summary>
        /// Hard disk read error
        /// </summary>
        NET_LOG_HDD_RERR,
        /// <summary>
        /// Set the hard disk type
        /// </summary>
        NET_LOG_HDD_TYPE,
        /// <summary>
        /// Format the hard disk
        /// </summary>
        NET_LOG_HDD_FORMAT,
        /// <summary>
        /// External alarm input
        /// </summary>
        NET_LOG_ALM_IN = 0x0300,
        /// <summary>
        /// External alarm input stops
        /// </summary>
        NET_LOG_ALM_END = 0x0302,
        /// <summary>
        /// Manual recording open
        /// </summary>
        NET_LOG_MANUAL_RECORD = 0x0401,
        /// <summary>
        /// Video Stop
        /// </summary>
        NET_LOG_CLOSED_RECORD,
        /// <summary>
        /// User Management : Log
        /// </summary>
        NET_LOG_LOGIN = 0x0500,
        /// <summary>
        /// User Management : Cancelled
        /// </summary>
        NET_LOG_LOGOUT,
        /// <summary>
        /// User Management: Add User
        /// </summary>
        NET_LOG_ADD_USER,
        /// <summary>
        /// User management: delete users
        /// </summary>
        NET_LOG_DELETE_USER,
        /// <summary>
        /// User Management: Modify User
        /// </summary>
        NET_LOG_MODIFY_USER,
        /// <summary>
        /// User Management: Add Group
        /// </summary>
        NET_LOG_ADD_GROUP,
        /// <summary>
        /// User management: delete a group
        /// </summary>
        NET_LOG_DELETE_GROUP,
        /// <summary>
        /// User Management: Modify Group
        /// </summary>
        NET_LOG_MODIFY_GROUP,
        /// <summary>
        /// Log Clear
        /// </summary>
        NET_LOG_CLEAR = 0x0600,			//clear 
        /// <summary>
        ///
        /// </summary>
        NET_LOG_TYPE_NR = 7,
    }

    /// <summary>
    /// The type of formulation
    /// </summary>
    /// C + + in the name of CFG_INDEX
    public enum CFG_TYPE
    {
        /// <summary>
        /// General
        /// </summary>
        CFG_GENERAL = 0,
        /// <summary>
        /// Serial
        /// </summary>
        CFG_COMM,
        /// <summary>
        /// Network
        /// </summary>
        CFG_NET,
        /// <summary>
        /// Video
        /// </summary>
        CFG_RECORD,
        /// <summary>
        /// Video Channel
        /// </summary>
        CFG_CAPTURE,
        /// <summary>
        /// PTZ
        /// </summary>
        CFG_PTZ,
        /// <summary>
        /// Motion Detection
        /// </summary>
        CFG_DETECT,
        /// <summary>
        /// Alert
        /// </summary>
        CFG_ALARM,
        /// <summary>
        /// Display
        /// </summary>
        CFG_DISPLAY,
        /// <summary>
        /// Channel title
        /// </summary>
        CFG_TITLE = 10,
        /// <summary>
        /// E-mail
        /// </summary>
        CFG_MAIL,
        /// <summary>
        /// Preview image configuration
        /// </summary>
        CFG_EXCAPTURE,
        /// <summary>
        /// Pppoe dial-up configuration
        /// </summary>
        CFG_PPPOE,
        /// <summary>
        /// Ddns configuration
        /// </summary>
        CFG_DDNS,
        /// <summary>
        /// Capture configuration
        /// </summary>
        CFG_SNIFFER,
        /// <summary>
        /// DSP capability information encoded
        /// </summary>
        CFG_DSPINFO,
        /// <summary>
        /// Color scheme
        /// </summary>
        CFG_COLOR = 126,
        /// <summary>
        /// All configuration
        /// </summary>
        CFG_ALL,
    }

    /// <summary>
    /// Timer recording type - regular , motion detection , alarm
    /// </summary>
    public enum REC_TYPE
    {
        NET_REC_TYPE_TIM = 0,
        NET_REC_TYPE_MTD,
        NET_REC_TYPE_ALM,
        NET_REC_TYPE_NUM,
    }

    /// <summary>
    /// User Management Operation Command
    /// </summary>
    public enum USER_OPERATE
    {
        /// <summary>
        /// Add User Group
        /// </summary>
        NET_GROUP_ADD = 0,
        /// <summary>
        /// Delete User Group
        /// </summary>
        NET_GROUP_DELETE,
        /// <summary>
        /// Modify User Group
        /// </summary>
        NET_GROUP_EDIT,
        /// <summary>
        /// New users
        /// </summary>
        NET_USER_ADD,
        /// <summary>
        /// Remove users
        /// </summary>
        NET_USER_DELETE,
        /// <summary>
        /// Modify User
        /// </summary>
        NET_USER_EDIT,
        /// <summary>
        /// Modify user passwords
        /// </summary>
        NET_USER_CHANGEPASSWORD
        
    }

    /// <summary>
    /// for CLIENT_StartService API,NEW_ALARM_UPLOAD.dwAlarmType Field
    /// </summary>
    public enum UPDATE_ALARM_TYPE
    {
        /// <summary>
        /// External alarm
        /// </summary>
        NET_UPLOAD_ALARM                    = 0x4000 , 
         /// <summary>
        /// Motion detection alarm
        /// </summary>
         NET_UPLOAD_MOTION_ALARM            = 0x4001 ,     
        /// <summary>
        //// Video loss alarm
        /// </summary>
        NET_UPLOAD_VIDEOLOST_ALARM          = 0x4002 ,     
        /// <summary>
        /// Occlusion alarm
        /// </summary>
        NET_UPLOAD_SHELTER_ALARM             = 0x4003 ,
        /// <summary>
        /// Audio detection alarm
        /// </summary>
        NET_UPLOAD_SOUND_DETECT_ALARM        = 0x4004 ,
        /// <summary>
        /// HDD full alarm
        /// </summary>
        NET_UPLOAD_DISKFULL_ALARM            = 0x4005 ,        
        /// <summary>
        /// Bad hard disk alarm
        /// </summary>
        NET_UPLOAD_DISKERROR_ALARM           = 0x4006 ,      
        /// <summary>
        /// Encoder alarm
        /// </summary>
        NET_UPLOAD_ENCODER_ALARM             = 0x4007 ,   
        /// <summary>
        /// Decoder alarm
        /// </summary>
        NET_UPLOAD_DECODER_ALARM             = 0x400B ,
        /// <summary>
        /// intelligent alarm,corresponding to ALARM_UPLOAD_IVS_INFO
        /// </summary>
        NET_UPLOAD_IVS                       = 0x400D, 
}

    /// <summary>
    /// Callback message type
    /// </summary>
    public enum CALLBACK_TYPE
    {
        /// <summary>
        /// General alarm information
        /// </summary>
        NET_COMM_ALARM = 0x1100,
        /// <summary>
        /// Video Tampering
        /// </summary>
        NET_SHELTER_ALARM = 0x1101,
        /// <summary>
        /// HDD full alarm
        /// </summary>
        NET_DISK_FULL_ALARM = 0X1102,
        /// <summary>
        /// HDD failure alarm
        /// </summary>
        NET_DISK_ERROR_ALARM = 0x1103,
        /// <summary>
        /// Audio detection alarm
        /// </summary>
        NET_SOUND_DETECT_ALARM = 0x1104,
        /// <summary>
        /// Decoder warning alarm
        /// </summary>
        NET_ALARM_DECODER_ALARM = 0x1105,

        /* The following types of information for the expansion of the callback alarm , correspondence CLIENT_StartListenEx */

        /// <summary>
        /// External alarm
        /// </summary>
        NET_ALARM_ALARM_EX = 0x2101,
        /// <summary>
        /// Motion detection alarm
        /// </summary>
        NET_MOTION_ALARM_EX = 0x2102,
        /// <summary>
        //// Video loss alarm
        /// </summary>
        NET_VIDEOLOST_ALARM_EX = 0X2103,
        /// <summary>
        /// Occlusion alarm
        /// </summary>
        NET_SHELTER_ALARM_EX = 0x2104,
        /// <summary>
        /// Audio detection alarm
        /// </summary>
        NET_SOUND_DETECT_ALARM_EX = 0x2105,
        /// <summary>
        /// HDD full alarm
        /// </summary>
        NET_DISKFULL_ALARM_EX = 0x2106,
        /// <summary>
        /// Bad hard disk alarm
        /// </summary>
        NET_DISKERROR_ALARM_EX = 0x2107,
        /// <summary>
        /// Record state Changed
        /// </summary>
        NET_RECORD_CHANGED_EX  = 0x2116 ,
        /// <summary>
        /// Record Failed Alarm -- with ALARM_RECORD_FAILED_INFO Struct 
        /// </summary>
        NET_RECORD_FAILED_ALARM  = 0x2164 ,           
        /// <summary>
        /// Alarm Net-- with ALARM_NET_INFO Struct 
        /// </summary>
        NET_ALARM_NET = 0x31b2,
    }

    /// <summary>
    /// Indicates the character encoding
    /// </summary>
    public enum LANGUAGE_ENCODING
    {
        /// <summary>
        /// IBM EBCDIC ( U.S. - Canada )
        /// </summary>
        IBM037 = 37,
        /// <summary>
        /// OEM USA
        /// </summary>
        IBM437 = 437,
        /// <summary>
        /// IBM EBCDIC ( International )
        /// </summary>
        IBM500 = 500,
        /// <summary>
        /// Arabic characters (ASMO 708)
        /// </summary>
        ASMO_708 = 708,
        /// <summary>
        /// Arabic characters (DOS)
        /// </summary>
        DOS_720 = 720,
        /// <summary>
        /// Greek characters (DOS)
        /// </summary>
        ibm737 = 737,
        /// <summary>
        /// Baltic characters (DOS)
        /// </summary>
        ibm775 = 775,
        /// <summary>
        /// Western European (DOS)
        /// </summary>
        ibm850 = 850,

        /// <summary>
        /// Central European characters (DOS)
        /// </summary>
        ibm852 = 852,
        /// <summary>
        /// OEM Cyrillic
        /// </summary>
        IBM855 = 855,
        /// <summary>
        /// Turkish characters (DOS)
        /// </summary>
        ibm857 = 857,
        /// <summary>
        /// OEM multi-language Latin I
        /// </summary>
        IBM00858 = 858,
        /// <summary>
        /// Portuguese (DOS)
        /// </summary>
        IBM860 = 860,
        /// <summary>
        /// Icelandic (DOS)
        /// </summary>
        ibm861 = 861,
        /// <summary>
        /// Hebrew characters (DOS)
        /// </summary>
        DOS_862 = 862,

        /// <summary>
        /// Canadian French (DOS)
        /// </summary>
        IBM863 = 863,
        /// <summary>
        /// Arabic characters ( 864 )
        /// </summary>
        IBM864 = 864,
        /// <summary>
        /// Nordic characters (DOS)
        /// </summary>
        IBM865 = 865,
        /// <summary>
        /// Cyrillic (DOS)
        /// </summary>
        cp866 = 866,
        /// <summary>
        /// Modern Greek characters (DOS)
        /// </summary>
        ibm869 = 869,
        /// <summary>
        /// IBM EBCDIC ( multi-language Latin 2 )
        /// </summary>
        IBM870 = 870,
        /// <summary>
        /// Thai (Windows)
        /// </summary>
        windows_874 = 874,
        /// <summary>
        /// IBM EBCDIC ( Modern Greek )
        /// </summary>
        cp875 = 875,
        /// <summary>
        /// Japanese (Shift-JIS)
        /// </summary>
        shift_jis = 932,
        /// <summary>
        /// Simplified Chinese (GB2312)
        /// </summary>
        gb2312 = 936,
        /// <summary>
        /// Korean
        /// </summary>
        ks_c_5601_1987 = 949,
        /// <summary>
        /// Traditional Chinese (Big5)
        /// </summary>
        big5 = 950,
        /// <summary>
        /// IBM EBCDIC ( Turkey Latin 5 )
        /// </summary>
        IBM1026 = 1026,
        /// <summary>
        /// IBM Latin 1
        /// </summary>
        IBM01047 = 1047,
        /// <summary>
        /// IBM EBCDIC ( USA - Canada - Europe )
        /// </summary>
        IBM01140 = 1140,
        /// <summary>
        /// IBM EBCDIC ( Germany - Europe )
        /// </summary>
        IBM01141 = 1141,
        /// <summary>
        /// IBM EBCDIC ( Denmark - Norway - Europe )
        /// </summary>
        IBM01142 = 1142,
        /// <summary>
        /// IBM EBCDIC ( Finland - Sweden - Europe )
        /// </summary>
        IBM01143 = 1143,
        /// <summary>
        /// IBM EBCDIC ( Italy - Europe )
        /// </summary>
        IBM01144 = 1144,
        /// <summary>
        /// IBM EBCDIC ( Spain - Europe )
        /// </summary>
        IBM01145 = 1145,
        /// <summary>
        /// IBM EBCDIC ( United Kingdom - Europe )
        /// </summary>
        IBM01146 = 1146,
        /// <summary>
        /// IBM EBCDIC ( France - Europe )
        /// </summary>
        IBM01147 = 1147,
        /// <summary>
        /// IBM EBCDIC ( International - Europe )
        /// </summary>
        IBM01148 = 1148,
        /// <summary>
        /// IBM EBCDIC ( Icelandic - Europe )
        /// </summary>
        IBM01149 = 1149,
        /// <summary>
        /// Unicode
        /// </summary>
        utf_16 = 1200,
        /// <summary>
        /// Unicode (Big-Endian)
        /// </summary>
        UnicodeFFFE = 1201,
        /// <summary>
        /// Central European (Windows)
        /// </summary>
        windows_1250 = 1250,
        /// <summary>
        /// Cyrillic (Windows)
        /// </summary>
        windows_1251 = 1251,
        /// <summary>
        /// Western European (Windows)
        /// </summary>
        Windows_1252 = 1252,
        /// <summary>
        /// Greek characters (Windows)
        /// </summary>
        windows_1253 = 1253,
        /// <summary>
        /// Turkish character (Windows)
        /// </summary>
        windows_1254 = 1254,
        /// <summary>
        /// Hebrew (Windows)
        /// </summary>
        windows_1255 = 1255,
        /// <summary>
        /// Arabic characters (Windows)
        /// </summary>
        windows_1256 = 1256,
        /// <summary>
        /// Baltic character (Windows)
        /// </summary>
        windows_1257 = 1257,
        /// <summary>
        /// Vietnamese characters (Windows)
        /// </summary>
        windows_1258 = 1258,
        /// <summary>
        /// Korean (Johab)
        /// </summary>
        Johab = 1361,
        /// <summary>
        /// Western European (Mac)
        /// </summary>
        macintosh = 10000,
        /// <summary>
        /// Japanese (Mac)
        /// </summary>
        x_mac_japanese = 10001,
        /// <summary>
        /// Traditional Chinese (Mac)
        /// </summary>
        x_mac_chinesetrad = 10002,
        /// <summary>
        /// Korean (Mac)
        /// </summary>
        x_mac_korean = 10003,
        /// <summary>
        /// Arabic characters (Mac)
        /// </summary>
        x_mac_arabic = 10004,
        /// <summary>
        /// Hebrew characters (Mac)
        /// </summary>
        x_mac_hebrew = 10005,
        /// <summary>
        /// Greek characters (Mac)
        /// </summary>
        x_mac_greek = 10006,
        /// <summary>
        /// Cyrillic (Mac)
        /// </summary>
        x_mac_cyrillic = 10007,
        /// <summary>
        /// Simplified Chinese (Mac)
        /// </summary>
        x_mac_chinesesimp = 10008,
        /// <summary>
        /// Romanian (Mac)
        /// </summary>
        x_mac_romanian = 10010,
        /// <summary>
        /// Ukrainian (Mac)
        /// </summary>
        x_mac_ukrainian = 10017,
        /// <summary>
        /// Thai (Mac)
        /// </summary>
        x_mac_thai = 10021,
        /// <summary>
        /// Central European characters (Mac)
        /// </summary>
        x_mac_ce = 10029,
        /// <summary>
        /// Icelandic (Mac)
        /// </summary>
        x_mac_icelandic = 10079,
        /// <summary>
        /// Turkish character (Mac)
        /// </summary>
        x_mac_turkish = 10081,
        /// <summary>
        /// Croatian (Mac)
        /// </summary>
        x_mac_croatian = 10082,
        /// <summary>
        /// Traditional Chinese (CNS)
        /// </summary>
        x_Chinese_CNS = 20000,
        /// <summary>
        /// TCA Taiwan
        /// </summary>
        x_cp20001 = 20001,
        /// <summary>
        /// Traditional Chinese (Eten)
        /// </summary>
        x_Chinese_Eten = 20002,
        /// <summary>
        /// IBM5550 Taiwan
        /// </summary>
        x_cp20003 = 20003,
        /// <summary>
        /// TeleText Taiwan
        /// </summary>
        x_cp20004 = 20004,
        /// <summary>
        /// Wang Taiwan
        /// </summary>
        x_cp20005 = 20005,
        /// <summary>
        /// Western European character (IA5)
        /// </summary>
        x_IA5 = 20105,
        /// <summary>
        /// German (IA5)
        /// </summary>
        x_IA5_German = 20106,
        /// <summary>
        /// Swedish (IA5)
        /// </summary>
        x_IA5_Swedish = 20107,
        /// <summary>
        /// Norwegian (IA5)
        /// </summary>
        x_IA5_Norwegian = 20108,
        /// <summary>
        /// US-ASCII
        /// </summary>
        us_ascii = 20127,
        /// <summary>
        /// T.61
        /// </summary>
        x_cp20261 = 20261,
        /// <summary>
        /// ISO-6937
        /// </summary>
        x_cp20269 = 20269,
        /// <summary>
        /// IBM EBCDIC ( Germany )
        /// </summary>
        IBM273 = 20273,
        /// <summary>
        /// IBM EBCDIC ( Denmark - Norway )
        /// </summary>
        IBM277 = 20277,
        /// <summary>
        /// IBM EBCDIC ( Finland - Sweden )
        /// </summary>
        IBM278 = 20278,
        /// <summary>
        /// IBM EBCDIC ( Italy )
        /// </summary>
        IBM280 = 20280,
        /// <summary>
        /// IBM EBCDIC ( Spain )
        /// </summary>
        IBM284 = 20284,
        /// <summary>
        /// IBM EBCDIC ( UK )
        /// </summary>
        IBM285 = 20285,
        /// <summary>
        /// IBM EBCDIC ( Japanese Katakana )
        /// </summary>
        IBM290 = 20290,
        /// <summary>
        /// IBM EBCDIC ( France )
        /// </summary>
        IBM297 = 20297,
        /// <summary>
        /// IBM EBCDIC ( Arabic )
        /// </summary>
        IBM420 = 20420,
        /// <summary>
        /// IBM EBCDIC ( Greek )
        /// </summary>
        IBM423 = 20423,
        /// <summary>
        /// IBM EBCDIC ( Hebrew )
        /// </summary>
        IBM424 = 20424,
        /// <summary>
        /// IBM EBCDIC ( Extended Korean )
        /// </summary>
        x_EBCDIC_KoreanExtended = 20833,
        /// <summary>
        /// IBM EBCDIC ( Thai )
        /// </summary>
        IBM_Thai = 20838,
        /// <summary>
        /// Cyrillic (KOI8-R)
        /// </summary>
        koi8_r = 20866,
        /// <summary>
        /// IBM EBCDIC ( Icelandic )
        /// </summary>
        IBM871 = 20871,
        /// <summary>
        /// IBM EBCDIC ( Cyrillic Russian )
        /// </summary>
        IBM880 = 20880,
        /// <summary>
        /// IBM EBCDIC ( Turkish )
        /// </summary>
        IBM905 = 20905,
        /// <summary>
        /// IBM Latin 1
        /// </summary>
        IBM00924 = 20924,
        /// <summary>
        /// Japanese (JIS 0208-1990 and 0212-1990 )
        /// </summary>
        EUC_JP = 20932,
        /// <summary>
        /// Simplified Chinese (GB2312-80)
        /// </summary>
        x_cp20936 = 20936,
        /// <summary>
        /// Korean Wansung
        /// </summary>
        x_cp20949 = 20949,
        /// <summary>
        /// IBM EBCDIC ( Cyrillic Serbian - Bulgarian )
        /// </summary>
        cp1025 = 21025,
        /// <summary>
        /// Cyrillic (KOI8-U)
        /// </summary>
        koi8_u = 21866,
        /// <summary>
        /// Western European (ISO)
        /// </summary>
        iso_8859_1 = 28591,
        /// <summary>
        /// Central European (ISO)
        /// </summary>
        iso_8859_2 = 28592,
        /// <summary>
        /// Latin 3 (ISO)
        /// </summary>
        iso_8859_3 = 28593,
        /// <summary>
        /// Baltic character (ISO)
        /// </summary>
        iso_8859_4 = 28594,
        /// <summary>
        /// Cyrillic (ISO)
        /// </summary>
        iso_8859_5 = 28595,
        /// <summary>
        /// Arabic characters (ISO)
        /// </summary>
        iso_8859_6 = 28596,
        /// <summary>
        /// Greek characters (ISO)
        /// </summary>
        iso_8859_7 = 28597,
        /// <summary>
        /// Hebrew (ISO-Visual)
        /// </summary>
        iso_8859_8 = 28598,
        /// <summary>
        /// Turkish character (ISO)
        /// </summary>
        iso_8859_9 = 28599,
        /// <summary>
        /// Estonian (ISO)
        /// </summary>
        iso_8859_13 = 28603,
        /// <summary>
        /// Latin 9 (ISO)
        /// </summary>
        iso_8859_15 = 28605,
        /// <summary>
        /// Europa
        /// </summary>
        x_Europa = 29001,
        /// <summary>
        /// Hebrew (ISO-Logical)
        /// </summary>
        iso_8859_8_i = 38598,
        /// <summary>
        /// J (JIS)
        /// </summary>
        iso_jp_JIS = 50220,
        /// <summary>
        /// Japanese (JIS- Allow 1 byte Kana )
        /// </summary>
        csISO2022JP = 50221,
        /// <summary>
        /// Japanese (JIS- Allow 1 byte Kana - SO / SI)
        /// </summary>
        iso_2022_jp = 50222,
        /// <summary>
        /// Korean (ISO)
        /// </summary>
        iso_2022_kr = 50225,
        /// <summary>
        /// Simplified Chinese (ISO-2022)
        /// </summary>
        x_cp50227 = 50227,
        /// <summary>
        /// Japanese (EUC)
        /// </summary>
        euc_jp = 51932,
        /// <summary>
        /// Simplified Chinese (EUC)
        /// </summary>
        EUC_CN = 51936,
        /// <summary>
        /// Korean (EUC)
        /// </summary>
        euc_kr = 51949,
        /// <summary>
        /// Simplified Chinese (HZ)
        /// </summary>
        hz_gb_2312 = 52936,
        /// <summary>
        /// Simplified Chinese (GB18030)
        /// </summary>
        GB18030 = 54936,
        /// <summary>
        /// ISCII Sanskrit
        /// </summary>
        x_iscii_de = 57002,
        /// <summary>
        /// ISCII Bengali
        /// </summary>
        x_iscii_be = 57003,
        /// <summary>
        /// ISCII Tamil
        /// </summary>
        x_iscii_ta = 57004,
        /// <summary>
        /// ISCII Telugu
        /// </summary>
        x_iscii_te = 57005,
        /// <summary>
        /// ISCII Assamese
        /// </summary>
        x_iscii_as = 57006,
        /// <summary>
        /// ISCII Oriya
        /// </summary>
        x_iscii_or = 57007,
        /// <summary>
        /// ISCII Kannada
        /// </summary>
        x_iscii_ka = 57008,
        /// <summary>
        /// ISCII Malayalam
        /// </summary>
        x_iscii_ma = 57009,
        /// <summary>
        /// ISCII Gujarati
        /// </summary>
        x_iscii_gu = 57010,
        /// <summary>
        /// ISCII Punjabi
        /// </summary>
        x_iscii_pa = 57011,
        /// <summary>
        /// Unicode (UTF-7)
        /// </summary>
        utf_7 = 65000,
        /// <summary>
        /// Unicode (UTF-8)
        /// </summary>
        utf_8 = 65001,
        /// <summary>
        /// Unicode (UTF-32)
        /// </summary>
        utf_32 = 65005,
        /// <summary>
        /// Unicode (UTF-32 Big-Endian)
        /// </summary>
        utf_32BE = 65006
    }

    /// <summary>
    /// Media file Query Conditions
    /// </summary>
    public enum EM_FILE_QUERY_TYPE
    {
        /// <summary>
        /// Transportation Vehicle Information
        /// </summary>
        NET_FILE_QUERY_TRAFFICCAR,
        /// <summary>
        /// ATM Information
        /// </summary>
        NET_FILE_QUERY_ATM,
        /// <summary>
        /// ATM transaction information
		/// </summary>       
        NET_FILE_QUERY_ATMTXN,
    }

    /// <summary>
    /// Control type , correspondence CLIENT_ControlDevice Interface
    /// </summary>
    public enum CtrlType
    {
        /// <summary>
        /// Reboot the device
        /// </summary>
        NET_CTRL_REBOOT = 0,
        /// <summary>
        /// Off the device
        /// </summary>
        NET_CTRL_SHUTDOWN,
        /// <summary>
        /// Hard disk management
        /// </summary>
        NET_CTRL_DISK,
        /// <summary>
        /// Network Keyboard
        /// </summary>
        NET_KEYBOARD_POWER = 3,
        NET_KEYBOARD_ENTER,
        NET_KEYBOARD_ESC,
        NET_KEYBOARD_UP,
        NET_KEYBOARD_DOWN,
        NET_KEYBOARD_LEFT,
        NET_KEYBOARD_RIGHT,
        NET_KEYBOARD_BTN0,
        NET_KEYBOARD_BTN1,
        NET_KEYBOARD_BTN2,
        NET_KEYBOARD_BTN3,
        NET_KEYBOARD_BTN4,
        NET_KEYBOARD_BTN5,
        NET_KEYBOARD_BTN6,
        NET_KEYBOARD_BTN7,
        NET_KEYBOARD_BTN8,
        NET_KEYBOARD_BTN9,
        NET_KEYBOARD_BTN10,
        NET_KEYBOARD_BTN11,
        NET_KEYBOARD_BTN12,
        NET_KEYBOARD_BTN13,
        NET_KEYBOARD_BTN14,
        NET_KEYBOARD_BTN15,
        NET_KEYBOARD_BTN16,
        NET_KEYBOARD_SPLIT,
        NET_KEYBOARD_ONE,
        NET_KEYBOARD_NINE,
        NET_KEYBOARD_ADDR,
        NET_KEYBOARD_INFO,
        NET_KEYBOARD_REC,
        NET_KEYBOARD_FN1,
        NET_KEYBOARD_FN2,
        NET_KEYBOARD_PLAY,
        NET_KEYBOARD_STOP,
        NET_KEYBOARD_SLOW,
        NET_KEYBOARD_FAST,
        NET_KEYBOARD_PREW,
        NET_KEYBOARD_NEXT,
        NET_KEYBOARD_JMPDOWN,
        NET_KEYBOARD_JMPUP,
        /// <summary>
        /// Trigger alarm input
        /// </summary>
        NET_TRIGGER_ALARM_IN = 100,
        /// <summary>
        /// Trigger the alarm output
        /// </summary>
        NET_TRIGGER_ALARM_OUT,
        /// <summary>
        /// Matrix Control
        /// </summary>
        NET_CTRL_MATRIX,
        /// <summary>
        /// SD Card Control (IPC products ) parameters are the same hard disk controller
        /// </summary>
        NET_CTRL_SDCARD,
        /// <summary>
        /// Burner control , began to burn
        /// </summary>
        NET_BURNING_START,
        /// <summary>
        /// Burner control , the end of the burn
        /// </summary>
        NET_BURNING_STOP,
        /// <summary>
        /// Burner control , overlay password ( '\ 0 ' is the end of the string , the maximum length of 8 )
        /// </summary>
        NET_BURNING_ADDPWD,
        /// <summary>
        /// Burner control , overlay titles ( '\ 0 ' is a string , the maximum length of 1024 bytes at the end to support branch line separator '\ n')
        /// </summary>
        NET_BURNING_ADNETEAD,
        /// <summary>
        /// Burner control , superimposed RBI to burn information ( parameter -free )
        /// </summary>
        NET_BURNING_ADDSIGN,
        /// <summary>
        /// Burner control , custom overlay ( '\ 0 ' is the end of the string , the maximum length of 1024 bytes, to support branch line separator '\ n')
        /// </summary>
        NET_BURNING_ADDCURSTOMINFO,
        /// <summary>
        /// Restore the device's default settings
        /// </summary>
        NET_CTRL_RESTOREDEFAULT,
        /// <summary>
        /// Capture trigger device
        /// </summary>
        NET_CTRL_CAPTURE_START,
        /// <summary>
        /// Clear Log
        /// </summary>
        NET_CTRL_CLEARLOG,
        /// <summary>
        /// Trigger wireless alarm (IPC products )
        /// </summary>
        NET_TRIGGER_ALARM_WIRELESS = 200,
        /// <summary>
        /// Video files to identify important
        /// </summary>
        NET_MARK_IMPORTANT_RECORD,
        /// <summary>
        /// Network hard disk partition
        /// </summary>
        NET_CTRL_DISK_SUBAREA,
        /// <summary>
        /// Burner controls , accessories burning.
        /// </summary>
        NET_BURNING_ATTACH,
        /// <summary>
        /// Burn pause
        /// </summary>
        NET_BURNING_PAUSE,
        /// <summary>
        /// Burning continue
        /// </summary>
        NET_BURNING_CONTINUE,
        /// <summary>
        /// Burn postponed
        /// </summary>
        NET_BURNING_POSTPONE,
        /// <summary>
        /// Stop control report
        /// </summary>
        NET_CTRL_OEMCTRL,
        /// <summary>
        /// Device backup starts
        /// </summary>
        NET_BACKUP_START,
        ///<summary>
        /// Device backup stops
        /// </summary>
        NET_BACKUP_STOP,
        /// <summary>
        /// Vehicle configuration manually add WIFI
        /// </summary>
        NET_VIHICLE_WIFI_ADD,
        /// <summary>
        /// Vehicle configuration manually deleted WIFI
        /// </summary>
        NET_VIHICLE_WIFI_DEC,
        /// <summary>
        /// Buzzer control start
        /// </summary>
        NET_BUZZER_START,
        /// <summary>
        /// Buzzer control end
        /// </summary>
        NET_BUZZER_STOP,
        /// <summary>
        /// Remove users
        /// </summary>
        NET_REJECT_USER,
        /// <summary>
        /// Shield users
        /// </summary>
        NET_SHIELD_USER,
        /// <summary>
        /// Intelligent Transportation , wiper control
        /// </summary>
        NET_RAINBRUSH,
        /// <summary>
        /// Intelligent Transportation , manual capture (correspondence structure MANUAL_SNAP_PARAMETER)
        /// </summary>
        NET_MANUAL_SNAP,
        /// <summary>
        /// Manual NTP school when
        /// </summary>
        NET_MANUAL_NTP_TIMEADJUST,
        /// <summary>
        /// Navigation information and the short message
        /// </summary>
        NET_NAVIGATION_SMS,
        /// <summary>
        /// Route point information
        /// </summary>
        NET_CTRL_ROUTE_CROSSING,
        /// <summary>
        /// Format backup device
        /// </summary>
        NET_BACKUP_FORMAT,
        /// <summary>
        /// End local control devices division preview (correspondence structure DEVICE_LOCALPREVIEW_SLIPT_PARAMETER)
        /// </summary>
        NET_DEVICE_LOCALPREVIEW_SLIPT,
        /// <summary>
        /// RAID initialization
        /// </summary>
        NET_CTRL_INIT_RAID,
        /// <summary>
        /// RAID operation
        /// </summary>
        NET_CTRL_RAID,
        /// <summary>
        /// Hot spare operation
        /// </summary>
        NET_CTRL_SAPREDISK,
        /// <summary>
        /// Manual launched WIFI connection (correspondence structure WIFI_CONNECT)
        /// </summary>
        NET_WIFI_CONNECT,
        /// <summary>
        /// Manually disconnect WIFI connection (correspondence structure WIFI_CONNECT)
        /// </summary>
        NET_WIFI_DISCONNECT,
        /// <summary>
        /// Arm/disarm operation
        /// </summary>
        NET_CTRL_ARMED,
        /// <summary>
        /// IP modify(struct DHCTRL_IPMODIFY_PARAM)
        /// </summary>
        NET_CTRL_IP_MODIFY,
        /// <summary>
        /// wps connect wifi(struct DHCTRL_CONNECT_WIFI_BYWPS)
        /// </summary>
        NET_CTRL_WIFI_BY_WPS,
        /// <summary>
        /// format pattion (struct DH_FORMAT_PATITION)
        /// </summary>
        NET_CTRL_FORMAT_PATITION,
        /// <summary>
        /// eject storage device(struct DH_EJECT_STORAGE_DEVICE)
        /// </summary>
        NET_CTRL_EJECT_STORAGE,
        /// <summary>
        /// load storage device(struct DH_LOAD_STORAGE_DEVICE)
        /// </summary>
        NET_CTRL_LOAD_STORAGE,
        /// <summary>
        /// close burner(struct NET_CTRL_BURNERDOOR) need wait 6s
        /// </summary>
        NET_CTRL_CLOSE_BURNER,
        /// <summary>
        /// eject burner(struct NET_CTRL_BURNERDOOR) need wait 4s
        /// </summary>
        NET_CTRL_EJECT_BURNER,
        /// <summary>
        /// alarm elimination corresponding structure NET (CTRL CLEAR ALARM)
        /// </summary>
        NET_CTRL_CLEAR_ALARM,
        /// <summary>
        /// TV wall information display corresponding structure NET (CTRL MONITORWALL TVINFO)
        /// </summary>
        NET_CTRL_MONITORWALL_TVINFO,
        /// <summary>
        /// start Intelligent VIDEO analysis (corresponding structure NET CTRL START VIDEO ANALYSE)
        /// </summary>
        NET_CTRL_START_VIDEO_ANALYSE,
        /// <summary>
        /// STOP intelligent VIDEO analysis corresponding structure NET (CTRL STOP VIDEO ANALYSE)
        /// </summary>
        NET_CTRL_STOP_VIDEO_ANALYSE,
        /// <summary>
        /// independently complete the upgrade process by the equipment do not need to upgrade file
        /// </summary>
        NET_CTRL_UPGRADE_DEVICE,
        /// <summary>
        /// Multi-channel preview playback channel switching corresponding structure NET (CTRL MULTIPLAYBACK CHANNALES)
        /// </summary>
        NET_CTRL_MULTIPLAYBACK_CHANNALES,
        /// <summary>
        /// Turn on the switch power supply timing device output corresponding.net (CTRL SEQPOWER PARAM)
        /// </summary>
        NET_CTRL_SEQPOWER_OPEN,
        /// <summary>
        /// Close the switch power supply timing device output corresponding.net (CTRL SEQPOWER PARAM)
        /// </summary>
        NET_CTRL_SEQPOWER_CLOSE,
        /// <summary>
        /// Power timing group open the switch quantity output corresponding.net (CTRL SEQPOWER PARAM)
        /// </summary>
        NET_CTRL_SEQPOWER_OPEN_ALL,
        /// <summary>
        /// Power sequence set close the switch quantity output corresponding.net (CTRL SEQPOWER PARAM)
        /// </summary>
        NET_CTRL_SEQPOWER_CLOSE_ALL,
        /// <summary>
        /// PROJECTOR up corresponding.net (CTRL PROJECTOR PARAM)
        /// </summary>
        NET_CTRL_PROJECTOR_RISE,
        /// <summary>
        /// PROJECTOR drop (corresponding to the.net CTRL PROJECTOR PARAM)
        /// </summary>
        NET_CTRL_PROJECTOR_FALL,
        /// <summary>
        /// PROJECTOR stop (corresponding to the.net CTRL PROJECTOR PARAM)
        /// </summary>
        NET_CTRL_PROJECTOR_STOP,
        /// <summary>
        /// INFRARED buttons (corresponding to the.net CTRL INFRARED KEY PARAM)
        /// </summary>
        NET_CTRL_INFRARED_KEY,
        /// <summary>
        /// Device START playback of audio file corresponding structure NET (CTRL START PLAYAUDIO)
        /// </summary>
        NET_CTRL_START_PLAYAUDIO,
        /// <summary>
        /// Equipment stop playback of audio file
        /// </summary>
        NET_CTRL_STOP_PLAYAUDIO,
        /// <summary>
        /// Corresponding structure NET open alarm (CTRL ALARMBELL)
        /// </summary>
        NET_CTRL_START_ALARMBELL,
        /// <summary>
        /// Close the warning signal corresponding structure NET (CTRL ALARMBELL)
        /// </summary>
        NET_CTRL_STOP_ALARMBELL,
        /// <summary>
        /// OPEN ACCESS control - corresponding structure NET (CTRL ACCESS OPEN)
        /// </summary>
        NET_CTRL_ACCESS_OPEN,
        /// <summary>
        /// Corresponding structure NET BYPASS function (CTRL SET BYPASS)
        /// </summary>
        NET_CTRL_SET_BYPASS,
        /// <summary>
        /// Add records to record set number (corresponding to the.net CTRL you INSERT PARAM)
        /// </summary>
        NET_CTRL_RECORDSET_INSERT,
        /// <summary>
        /// Update a record of the number (corresponding to the.net CTRL you PARAM)
        /// </summary>
        NET_CTRL_RECORDSET_UPDATE,
        /// <summary>
        /// According to the record set number to delete a record (corresponding to the.net CTRL you PARAM)
        /// </summary>
        NET_CTRL_RECORDSET_REMOVE,
        /// <summary>
        /// Remove all RECORDSET information corresponding.net (CTRL you PARAM)
        /// </summary>
        NET_CTRL_RECORDSET_CLEAR,
        /// <summary>
        /// Entrance guard control - CLOSE corresponding structure NET (CTRL ACCESS CLOSE)
        /// </summary>
        NET_CTRL_ACCESS_CLOSE,
        /// <summary>
        /// Alarm sub system activation setup(corresponding structure NET_CTRL_ALARM_SUBSYSTEM_SETACTIVE)
        /// </summary>
        NET_CTRL_ALARM_SUBSYSTEM_ACTIVE_SET,
        /// <summary>
        /// Disable device open gateway(corresponding to structure  NET_CTRL_FORBID_OPEN_STROBE)
        /// </summary>
        NET_CTRL_FORBID_OPEN_STROBE,
        /// <summary>
        /// Enable gateway(corresponding to structure  NET_CTRL_OPEN_STROBE)
        /// </summary>
        NET_CTRL_OPEN_STROBE,
        /// <summary>
        /// Talk no response(corresponding to structure  NET_CTRL_TALKING_REFUSE)
        /// </summary>
        NET_CTRL_TALKING_REFUSE,
        /// <summary>
        /// CTRL_ARM_DISARM_PARAM upgrade，recommended
        /// </summary>
        NET_CTRL_ARMED_EX,
        /// <summary>
        /// Net keyboard control(corresponding to structure  DHCTRL_NET_KEYBOARD)
        /// </summary>
        NET_CTRL_NET_KEYBOARD = 400,
        /// <summary>
        /// Open air conditioner(corresponding to structure  NET_CTRL_OPEN_AIRCONDITION)
        /// </summary>
        NET_CTRL_AIRCONDITION_OPEN,
        /// <summary>
        /// Close air-conditioner(corresponding to structure  NET_CTRL_CLOSE_AIRCONDITION)
        /// </summary>
        NET_CTRL_AIRCONDITION_CLOSE,
        /// <summary>
        /// Set temperature (corresponding to structure  NET_CTRL_SET_TEMPERATURE)
        /// </summary>
        NET_CTRL_AIRCONDITION_SET_TEMPERATURE,
        /// <summary>
        /// Adjust temperature(corresponding to structure  NET_CTRL_ADJUST_TEMPERATURE)
        /// </summary>
        NET_CTRL_AIRCONDITION_ADJUST_TEMPERATURE,
        /// <summary>
        /// Set air work mode(corresponding to structure  NET_CTRL_ADJUST_TEMPERATURE)
        /// </summary>
        NET_CTRL_AIRCONDITION_SETMODE,
        /// <summary>
        /// Set fan mode(corresponding to structure  NET_CTRL_AIRCONDITION_SETMODE)
        /// </summary>
        NET_CTRL_AIRCONDITION_SETWINDMODE,
        /// <summary>
        /// Recover device default and set new protocol(corresponding to structure NET_CTRL_RESTORE_DEFAULT) Recover config and use this enumeration first, if port failed, and CLIENT_GetLastError return NET_UNSUPPORTED, try again DH_CTRL_RESTOREDEFAULT restore config
        /// </summary>
        NET_CTRL_RESTOREDEFAULT_EX,
        /// <summary>
        /// send event to device (corresponding to  structure  NET_NOTIFY_EVENT_DATA)
        /// </summary>
        NET_CTRL_NOTIFY_EVENT,
        /// <summary>
        /// mute alarm setup
        /// </summary>
        NET_CTRL_SILENT_ALARM_SET,
        /// <summary>
        /// device start sound report(corresponding to  structure  NET_CTRL_START_PLAYAUDIOEX)
        /// </summary>
        NET_CTRL_START_PLAYAUDIOEX,
        /// <summary>
        /// device stop sound report
        /// </summary>
        NET_CTRL_STOP_PLAYAUDIOEX,
        /// <summary>
        /// close gateway(corresponding to  structure  NET_CTRL_CLOSE_STROBE)
        /// </summary>
        NET_CTRL_CLOSE_STROBE,
        /// <summary>
        /// set parking reservation status (corresponding to  structure  NET_CTRL_SET_ORDER_STATE)
        /// </summary>
        NET_CTRL_SET_ORDER_STATE,
        /// <summary>
        /// add record，get record collection no.(corresponding to NET_CTRL_RECORDSET_INSERT_PARAM)
        /// </summary>
        NET_CTRL_RECORDSET_INSERTEX,
        /// <summary>
        /// update record set no.’s record(corresponding to NET_CTRL_RECORDSET_PARAM)
        /// </summary>
        NET_CTRL_RECORDSET_UPDATEEX,
        /// <summary>
        /// fingerprint collection (corresponding to structure NET_CTRL_CAPTURE_FINGER_PRINT)
        /// </summary>
        NET_CTRL_CAPTURE_FINGER_PRINT,
        /// <summary>
        /// Parking lot entrance/exit controller LED setup(corresponding structure  NET_CTRL_ECK_LED_SET_PARAM)
        /// </summary>
        NET_CTRL_ECK_LED_SET,
        /// <summary>
        /// Intelligent parking system in/out device IC card info import (corresponding structure  NET_CTRL_ECK_IC_CARD_IMPORT_PARAM)
        /// </summary>
        NET_CTRL_ECK_IC_CARD_IMPORT,
        /// <summary>
        /// device will delete original IC card info(corresponding structure  NET_CTRL_ECK_SYNC_IC_CARD_PARAM)
        /// </summary>
        NET_CTRL_ECK_SYNC_IC_CARD,
        /// <summary>
        /// Delete specific wireless device(corresponding structure  NET_CTRL_LOWRATEWPAN_REMOVE)
        /// </summary>
        NET_CTRL_LOWRATEWPAN_REMOVE,
        /// <summary>
        /// Modify wireless device info(corresponding structure  NET_CTRL_LOWRATEWPAN_MODIFY)
        /// </summary>
        NET_CTRL_LOWRATEWPAN_MODIFY,
        /// <summary>
        /// Set up the vehicle spot information of the machine at the passageway of the intelligent parking system (corresponding to  NET_CTRL_ECK_SET_PARK_INFO_PARAM)
        /// </summary>
        NET_CTRL_ECK_SET_PARK_INFO,
        /// <summary>
        /// hang up the video phone (corresponding to NET_CTRL_VTP_DISCONNECT)
        /// </summary>
        NET_CTRL_VTP_DISCONNECT,
        /// <summary>
        /// the update of the remote multimedia files (corresponding to NET_CTRL_UPDATE_FILES)
        /// </summary>
        NET_CTRL_UPDATE_FILES,
        /// <summary>
        /// Save up the relationship between the hyponymy matrixes (corresponding to NET_CTRL_MATRIX_SAVE_SWITCH)
        /// </summary>
        NET_CTRL_MATRIX_SAVE_SWITCH,
        /// <summary>
        /// recover the relationship between the hyponymy matrixes (corresponding to NET_CTRL_MATRIX_RESTORE_SWITCH)
        /// </summary>
        NET_CTRL_MATRIX_RESTORE_SWITCH,
        /// <summary>
        /// video talk phone divert ack(corresponding to NET_CTRL_VTP_DIVERTACK)
        /// </summary>
        NET_CTRL_VTP_DIVERTACK,
        /// <summary>
        /// efficient when set as manual mode(corresponding to NET_CTRL_RAINBRUSH_MOVEONCE)
        /// </summary>
        NET_CTRL_RAINBRUSH_MOVEONCE,
        /// <summary>
        /// efficient when set as manal mode(corresponding to NET_CTRL_RAINBRUSH_MOVECONTINUOUSLY)
        /// </summary>
        NET_CTRL_RAINBRUSH_MOVECONTINUOUSLY,
        /// <summary>
        /// efficient when set as manal mode(corresponding to NET_CTRL_RAINBRUSH_STOPMOVE)
        /// </summary>
        NET_CTRL_RAINBRUSH_STOPMOVE,
        /// <summary>
        /// affirm the alarm event(corresponding to NET_CTRL_ALARM_ACK) DH_CTRL_ALARM_ACK DO NOT call this method in callback interface
        /// </summary>
        NET_CTRL_ALARM_ACK,
    }


    public enum EM_STAFF_TYPE
    {
        EM_STAFF_TYPE_ERR,
        /// <summary>
        /// "Horizontal" horizontal line
        /// </summary>
        EM_STAFF_TYPE_HORIZONTAL,
        /// <summary>
        /// "Vertical" vertical segment
        /// </summary>
        EM_STAFF_TYPE_VERTICAL,
        /// <summary>
        /// "Any" arbitrary line
        /// </summary>
        EM_STAFF_TYPE_ANY,
        /// <summary>
        /// "Cross" personally vertical line
        /// </summary>
        EM_STAFF_TYPE_CROSS,
    }

    public enum EM_CALIBRATEAREA_TYPE
    {
	    EM_CALIBRATEAREA_TYPE_ERR,
        /// <summary>
        /// "Groud": ground requires N + M of the vertical line of horizontal line ((N = 3, M = 1); (N = 2, M = 2); future expansion ) .
        /// </summary>
		EM_CALIBRATEAREA_TYPE_GROUD, 
        /// <summary>
        /// "Horizontal": horizontal , the need for horizontal ground surface to the point that the vertical projection line .
        /// </summary>
		EM_CALIBRATEAREA_TYPE_HORIZONTAL,
        /// <summary>
        /// "Vertical": vertical , require vertical lines of intersection with the ground .
        /// </summary>
		EM_CALIBRATEAREA_TYPE_VERTICAL,
        /// <summary>
        /// "Any" any plane , N of vertical segments , and each length (N = 3, and future expansion ) .
        /// </summary>
		EM_CALIBRATEAREA_TYPE_ANY,
    };

    /// <summary>
    /// Video compression formats
    /// </summary>
    public enum CFG_VIDEO_COMPRESSION
    {
        /// <summary>
        /// MPEG4
        /// </summary>
	    VIDEO_FORMAT_MPEG4,
        /// <summary>
        /// MS-MPEG4
        /// </summary>
	    VIDEO_FORMAT_MS_MPEG4,
        /// <summary>
        /// MPEG2
        /// </summary>
	    VIDEO_FORMAT_MPEG2,
        /// <summary>
        /// MPEG1
        /// </summary>
	    VIDEO_FORMAT_MPEG1,
        /// <summary>
        /// H.263
        /// </summary>
	    VIDEO_FORMAT_H263,
        /// <summary>
        /// MJPG
        /// </summary>
	    VIDEO_FORMAT_MJPG,
        /// <summary>
        /// FCC-MPEG4
        /// </summary>
	    VIDEO_FORMAT_FCC_MPEG4,
        /// <summary>
        /// H.264
        /// </summary>
	    VIDEO_FORMAT_H264,
    } ;

    /// <summary>
    /// Stream control mode
    /// </summary>
    public enum CFG_BITRATE_CONTROL
    {
        /// <summary>
        /// Fixed stream
        /// </summary>
	    BITRATE_CBR, 
        /// <summary>
        /// Variable stream
        /// </summary>
	    BITRATE_VBR, 
    }

    /// <summary>
    /// HD
    /// </summary>
    public enum CFG_IMAGE_QUALITY
    {
        /// <summary>
        /// Image Quality 10%
        /// </summary>
        IMAGE_QUALITY_Q10 = 1,
        /// <summary>
        /// Image Quality 30%
        /// </summary>
        IMAGE_QUALITY_Q30,
        /// <summary>
        /// Image Quality 50%
        /// </summary>
        IMAGE_QUALITY_Q50,
        /// <summary>
        /// Image Quality 60%
        /// </summary>
        IMAGE_QUALITY_Q60,
        /// <summary>
        /// Image Quality 80%
        /// </summary>
        IMAGE_QUALITY_Q80,
        /// <summary>
        /// Image Quality 100%
        /// </summary>
        IMAGE_QUALITY_Q100,
    }

    /// <summary>
    /// H264 Coder ProFile
    /// </summary>
    public  enum CFG_H264_PROFILE_RANK
    {
        /// <summary>
        /// Support I/P Frame , progressive. CAVLC
        /// </summary>
	    PROFILE_BASELINE = 1,                       
        /// <summary>
        /// Support I/P/B Frame , progressive and interlaced ,  CAVLC or CABAC
        /// </summary>
	    PROFILE_MAIN,                              
        /// <summary>
        /// Support I/P/B/SP/SI Frame , progressive,  CAVLC
        /// </summary>
	    PROFILE_EXTENDED,                           
        /// <summary>
        /// Just FRExt , like PROFILE_MAIN but add 8x8 intra prediction , custom quant , lossless video coding , and more yuv type
        /// </summary>
	    PROFILE_HIGH,                               
    }

    /// <summary>
    /// Audio coding mode
    /// </summary>
    public enum CFG_AUDIO_FORMAT
    {
        /// <summary>
        /// G711a
        /// </summary>
        AUDIO_FORMAT_G711A,
        /// <summary>
        /// PCM
        /// </summary>
        AUDIO_FORMAT_PCM,
        /// <summary>
        /// G711u
        /// </summary>
        AUDIO_FORMAT_G711U,
        /// <summary>
        /// AMR
        /// </summary>
        AUDIO_FORMAT_AMR,
        /// <summary>
        /// AAC
        /// </summary>
        AUDIO_FORMAT_AAC,
    }

    /// <summary>
    /// PTZ linkage type
    /// </summary>
    public enum CFG_LINK_TYPE
    {
        /// <summary>
        /// No linkage
        /// </summary>
        LINK_TYPE_NONE,
        /// <summary>
        /// Preset point linkage
        /// </summary>
        LINK_TYPE_PRESET,
        /// <summary>
        /// Linkage cruise
        /// </summary>
        LINK_TYPE_TOUR,
        /// <summary>
        /// Linkage locus
        /// </summary>
        LINK_TYPE_PATTERN,
    } 


    // Resolution enumeration
    public enum CFG_CAPTURE_SIZE
    {
        /// <summary>
        /// 704 * 576 (PAL) 704 * 480 (NTSC)
        /// </summary>
IMAGE_SIZE_D1,
        /// <summary>
        /// 352 * 576 (PAL) 352 * 480 (NTSC)
        /// </summary>
IMAGE_SIZE_HD1,
        /// <summary>
        /// 704 * 288 (PAL) 704 * 240 (NTSC)
        /// </summary>
IMAGE_SIZE_BCIF,
        /// <summary>
        /// 352 * 288 (PAL) 352 * 240 (NTSC)
        /// </summary>
IMAGE_SIZE_CIF,
        /// <summary>
        /// 176 * 144 (PAL) 176 * 120 (NTSC)
        /// </summary>
IMAGE_SIZE_QCIF,
        /// <summary>
        /// 640 * 480
        /// </summary>
IMAGE_SIZE_VGA,
        /// <summary>
        /// 320 * 240
        /// </summary>
IMAGE_SIZE_QVGA,
        /// <summary>
        /// 480 * 480
        /// </summary>
IMAGE_SIZE_SVCD,
        /// <summary>
        /// 160 * 128
        /// </summary>
IMAGE_SIZE_QQVGA,
        /// <summary>
        /// 800 * 592
        /// </summary>
IMAGE_SIZE_SVGA,
        /// <summary>
        /// 1024 * 768
        /// </summary>
IMAGE_SIZE_XVGA,
        /// <summary>
        /// 1280 * 800
        /// </summary>
IMAGE_SIZE_WXGA,
        /// <summary>
        /// 1280 * 1024
        /// </summary>
IMAGE_SIZE_SXGA,
        /// <summary>
        /// 1600 * 1024
        /// </summary>
IMAGE_SIZE_WSXGA,
        /// <summary>
        /// 1600 * 1200
        /// </summary>
IMAGE_SIZE_UXGA,
        /// <summary>
        /// 1920 * 1200
        /// </summary>
IMAGE_SIZE_WUXGA,
        /// <summary>
        /// 240 * 192
        /// </summary>
IMAGE_SIZE_LTF,
        /// <summary>
        /// 1280 * 720
        /// </summary>
IMAGE_SIZE_720,
        /// <summary>
        /// 1920 * 1080
        /// </summary>
IMAGE_SIZE_1080,
        /// <summary>
        /// 1280 * 960
        /// </summary>
IMAGE_SIZE_1_3M,
        /// <summary>
        /// 1872*1408
        /// </summary>
IMAGE_SIZE_2M,                               
        /// <summary>
        /// 3744*1408
        /// </summary>
IMAGE_SIZE_5M,                  
        /// <summary>
        /// 2048*1536
        /// </summary>
IMAGE_SIZE_3M,               
        /// <summary>
        /// 2432*2050
        /// </summary>
IMAGE_SIZE_5_0M,            
        /// <summary>
        /// 1216*1024
        /// </summary>
IMAGE_SIZE_1_2M,          
        /// <summary>
        /// 1408*1024
        /// </summary>
IMAGE_SIZE_1408_1024,            
        /// <summary>
        /// 3296*2472
        /// </summary>
IMAGE_SIZE_8M,                
        /// <summary>
        /// 2560*1920(5M)
        /// </summary>
IMAGE_SIZE_2560_1920,                
        /// <summary>
        /// 960*576(PAL) 960*480(NTSC)
        /// </summary>
IMAGE_SIZE_960H,                
        /// <summary>
        /// 960*720
        /// </summary>
IMAGE_SIZE_960_720,            
        /// <summary>
        /// 640*360
        /// </summary>
IMAGE_SIZE_NHD,                
        /// <summary>
        /// 320*180
        /// </summary>
IMAGE_SIZE_QNHD,               
        /// <summary>
        /// 160*90
        /// </summary>
IMAGE_SIZE_QQNHD,                   
        /// <summary>
        /// 960*540
        /// </summary>
IMAGE_SIZE_960_540,               
        /// <summary>
        /// 640*352
        /// </summary>
IMAGE_SIZE_640_352,              
        /// <summary>
        /// 640*400
        /// </summary>
IMAGE_SIZE_640_400,                   
        /// <summary>
        /// 320*192  
        /// </summary>
IMAGE_SIZE_320_192,                      
        /// <summary>
        /// 320*176
        /// </summary>
IMAGE_SIZE_320_176,                         
IMAGE_SIZE_NR
    }

    // Capture mode
    public enum CFG_TRAFFIC_SNAP_MODE
    {
        /// <summary>
        /// Automatically capture
        /// </summary>
        TRAFFIC_SNAP_MODE_AUTO = 0,
        /// <summary>
        /// Capture coil
        /// </summary>
        TRAFFIC_SNAP_MODE_COIL,
        /// <summary>
        /// Coil capture, image analysis
        /// </summary>
        TRAFFIC_SNAP_MODE_COIL_PICANALYSIS,
        /// <summary>
        /// Video capture
        /// </summary>
        TRAFFIC_SNAP_MODE_STREAM,
        /// <summary>
        /// Video capture, and identify
        /// </summary>
        TRAFFIC_SNAP_MODE_STREAM_IDENTIFY,
    }

    // Language type
    public enum AV_CFG_LanguageType
    {
        /// <summary>
        /// English
        /// </summary>
        AV_CFG_Language_English,
        /// <summary>
        /// Simplified Chinese
        /// </summary>
        AV_CFG_Language_SimpChinese,
        /// <summary>
        /// Traditional Chinese
        /// </summary>
        AV_CFg_Language_TradChinese,
        /// <summary>
        /// Italian
        /// </summary>
        AV_CFG_Language_Italian,
        /// <summary>
        /// Spanish
        /// </summary>
        AV_CFG_Language_Spanish,
        /// <summary>
        /// Japanese
        /// </summary>
        AV_CFG_Language_Janpanese,
        /// <summary>
        /// Russian
        /// </summary>
        AV_CFG_Language_Russian,
        /// <summary>
        /// French
        /// </summary>
        AV_CFG_Language_French,
        /// <summary>
        /// German
        /// </summary>
        AV_CFG_Language_German,
    } ;

    // PTZ linkage type
    public enum AV_CFG_PtzLinkType
    {
        /// <summary>
        /// No linkage
        /// </summary>
        AV_CFG_PtzLink_None,
        /// <summary>
        /// Preset point linkage
        /// </summary>
        AV_CFG_PtzLink_Preset,
        /// <summary>
        /// Linkage cruise
        /// </summary>
        AV_CFG_PtzLink_Tour,
        /// <summary>
        /// Linkage locus
        /// </summary>
        AV_CFG_PtzLink_Pattern,
    }

    // Split Mode
    public enum AV_CFG_SplitMode
    {
        /// <summary>
        /// 1 screen
        /// </summary>
        AV_CFG_Split1 = 1,
        /// <summary>
        /// 2 screen
        /// </summary>
        AV_CFG_Split2 = 2,
        /// <summary>
        /// 4 screen
        /// </summary>
        AV_CFG_Split4 = 4,
        /// <summary>
        /// 6 picture
        /// </summary>
        AV_CFG_Split6 = 6,
        /// <summary>
        /// 8 screen
        /// </summary>
        AV_CFG_Split8 = 8,
        /// <summary>
        /// 9 screen
        /// </summary>
        AV_CFG_Split9 = 9,
        /// <summary>
        /// 12 picture
        /// </summary>
        AV_CFG_Split12 = 12,
        /// <summary>
        /// 16 picture
        /// </summary>
        AV_CFG_Split16 = 16,
        /// <summary>
        /// 20 Screen
        /// </summary>
        AV_CFG_Split20 = 20,
        /// <summary>
        /// 25 Screen
        /// </summary>
        AV_CFG_Split25 = 25,
        /// <summary>
        /// 36 Screen
        /// </summary>
        AV_CFG_Split36 = 36,
        /// <summary>
        /// PIP Mode , a small picture in full-screen window big picture +1
        /// </summary>
        AV_CFG_PIP1 = 100 + 1,
        /// <summary>
        /// PIP Mode , a small picture in full-screen +3 big picture window
        /// </summary>
        AV_CFG_PIP3 = 100 + 3,
    }

    //// / Video diagnostic tasks
    public enum CFG_EM_STREAM_TYPE
    {
        /// <summary>
        /// Other
        /// </summary>
        CFG_EM_STREAM_ERR,
        /// <summary>
        /// "Main" - Main Stream
        /// </summary>
        CFG_EM_STREAM_MAIN,
        /// <summary>
        /// "Extra1" - an extra stream
        /// </summary>
        CFG_EM_STREAM_EXTRA_1,
        /// <summary>
        /// "Extra2" - sub-stream 2
        /// </summary>
        CFG_EM_STREAM_EXTRA_2,
        /// <summary>
        /// "Extra3" - sub-stream 3
        /// </summary>
        CFG_EM_STREAM_EXTRA_3,
        /// <summary>
        /// "Snapshot" - capture stream
        /// </summary>
        CFG_EM_STREAM_SNAPSHOT,
        /// <summary>
        /// "Object" - the object flow
        /// </summary>
        CFG_EM_STREAM_OBJECT,
    } ;

    public enum NET_SYS_ABILITY
    {
		ABILITY_WATERMARK_CFG = 17, // Watermark configuration capacity
		ABILITY_WIRELESS_CFG = 18, // wireless confuguration capacity
		ABILITY_DEVALL_INFO = 26, // Device capacity list
		ABILITY_CARD_QUERY = 0x0100, // Card number search capacity
		ABILITY_MULTIPLAY = 0x0101, // Multiple-window preview capacity
		ABILITY_QUICK_QUERY_CFG = 0x0102, // Fast query configuration Capabilities
		ABILITY_INFRARED = 0x0121, // Wireless alarm capacity
		ABILITY_TRIGGER_MODE = 0x0131, // Alarm activation mode function
		ABILITY_DISK_SUBAREA = 0x0141, // Network hard disk partition
		ABILITY_DSP_CFG = 0x0151, // Query DSP Capabilities
		ABILITY_STREAM_MEDIA = 0x0161, // Query SIP, RTSP Capabilities
    } 

    public enum NET_FUN_SUPPORT
    {
		EN_FTP = 0, // FTP bitwise, 1: send out record file; 2: Send out snapshot file
		EN_SMTP, // SMTP bitwise, 1: alarm send out text mail 2: Alarm send out image
		EN_NTP, // NTP Bitwise: 1: Adjust system time
		EN_AUTO_MAINTAIN, // Auto maintenance Bitwise: 1: reboot 2: close 3: delete file
		EN_VIDEO_COVER, // Privacy mask Bitwise: 1: multiple-window privacy mask
		EN_AUTO_REGISTER, // Auto registration Bitwise: 1: SDK auto log in after registration
		EN_DHCP, // DHCP Bitwise: 1: DHCP
		EN_UPNP, // UPNP Bitwise: 1: UPNP
		EN_COMM_SNIFFER, // COM sniffer Bitwise: 1: CommATM
		EN_NET_SNIFFER, // Network sniffer Bitwise: 1: NetSniffer
		EN_BURN, // Burn function Bitwise 1: Search burn status
		EN_VIDEO_MATRIX, // Video matrix Bitwise 1: Support video matrix or not
		EN_AUDIO_DETECT, // Video detection Bitwise: 1: Support video detection or not
		EN_STORAGE_STATION, // Storage position Bitwise: 1: Ftp server (Ips) 2: SBM 3: NFS 16: DISK 17: Flash disk
		EN_IPSSEARCH, // IPS storage search Bitwise 1: IPS storage search
		EN_SNAP, // Snapshot Bitwise 1: Resoluiton 2: Frame rate 3: Snapshoot 4: Snapshoot file image; 5: Image quality
		EN_DEFAULTNIC, // Search default network card search Bitwise 1: Support
		EN_SHOWQUALITY, // Image quality configuration time in CBR mode 1: support
		EN_CONFIG_IMEXPORT, // Configuration import & emport function capacity Bitwise 1:. Support
		EN_LOG, // Support search log page by page or not Bitwise 1:. Support
		EN_SCHEDULE, // Record setup capacity Bitwise 1:. Redandunce 2: Pre-record 3: Record period
		EN_NETWORK_TYPE, // Network type Bitwise 1:. Wire Network 2: Wireless Network 3: CDMA / GPRS
		EN_MARK_IMPORTANTRECORD, // Important record Bitwise 1:. Important record mark
		EN_ACFCONTROL, // Frame rate control activities Bitwise 1:. Support frame rate control activities
		EN_MULTIASSIOPTION, // Multiple-channel extra stream Bitwise:. 1: support three channel extra stream
		EN_DAVINCIMODULE, // Component modules bitwise: 1.Separate processing the schedule 2.Standard I franme Interval setting
		EN_GPS, // GPS function bitwise: 1: Gps locate function
		EN_MULTIETHERNET, // Support multi net card query bitwise: 1: support
		EN_LOGIN_ATTRIBUTE, // Login properties bitwise: 1: support query login properties
		EN_RECORD_GENERAL, // Recording associated bitwise: 1: Normal recording; 2: Alarm recording;
							// 3: Motion detection recording; 4: Local storage; 5: Network storage;
							// 6: Redundancy storage; 7: Local emergency storage
		EN_JSON_CONFIG, // Whether support Json configuration, bitwise: 1: support Json
		EN_HIDE_FUNCTION, // Hide function: bitwise :: 1, hide PTZ function
    }

    // Upgrade Type
    public enum EM_UPGRADE_TYPE
    {
		NET_UPGRADE_BIOS_TYPE = 1, // BIOS upgrade
		NET_UPGRADE_WEB_TYPE, // WEB Upgrade
		NET_UPGRADE_BOOT_YPE, // BOOT Upgrade
		NET_UPGRADE_CHARACTER_TYPE, // Store
		NET_UPGRADE_LOGO_TYPE, // LOGO
		NET_UPGRADE_EXE_TYPE, // EXE, for example, players
    }

    #endregion
}