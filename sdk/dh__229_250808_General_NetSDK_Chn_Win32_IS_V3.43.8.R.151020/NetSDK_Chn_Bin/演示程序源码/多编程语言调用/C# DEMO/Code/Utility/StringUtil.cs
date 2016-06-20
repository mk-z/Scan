using System;
using System.Collections.Generic;
using System.Text;
using System.Runtime.InteropServices;
using System.Windows.Forms;

namespace Utility
{
    public sealed class StringUtil
    {
        /// <summary>
        /// Init File Name
        /// </summary>
        private static string strIniFileName = @".\language.ini";
        public static string IniFileName
        {
            set
            {
                if (!value.Equals(string.Empty))
                {
                    strIniFileName = value;
                }
            }

            get
            {
                return strIniFileName;
            }
        }

        /// <summary>
        /// Set/Get Application Name 
        /// </summary>
        private static string strAppName = "String";
        public static string AppName
        {
            set
            {
                if (!value.Equals(string.Empty))
                {
                    strAppName = value;
                }
            }

            get
            {
                return strAppName;
            }
        }
        
        /// <summary>
        /// Init control or sub control title
        /// </summary>
        /// <param name="control"></param>
        public static void InitControlText(Control control)
        {
            try
            {
                control.Text = ConvertString(control.Text);

                Control.ControlCollection children = control.Controls;
                for (int i = 0; i < children.Count; i++)
                {
                    InitControlText(children[i]);
                }

                Type type = control.GetType();
               
                if (type.Equals(typeof(StatusStrip)))
                {
                    StatusStrip stsStrip = (StatusStrip)control;
                    int nCount = stsStrip.Items.Count;
                    for (int i = 0; i < nCount; i++ )
                        InitToolStripItemText(stsStrip.Items[i], false);
                }
                else if (type.Equals(typeof(MenuStrip)))
                {
                    MenuStrip menuStrip = (MenuStrip)control;
                    int nCount = menuStrip.Items.Count;
                    for (int i = 0; i < nCount; i++ )
                        InitToolStripItemText(menuStrip.Items[i], true);
                }
                else if (type.Equals(typeof(ListView)))
                {
                    ListView listView = (ListView)control;
                    int nCount = listView.Columns.Count;
                    for (int i = 0; i < nCount; i++)
                        listView.Columns[i].Text = ConvertString(listView.Columns[i].Text);
                }
                else if (type.Equals(typeof(ComboBox)))
                {
                    ComboBox comboBox = (ComboBox)control;
                    int nCount = comboBox.Items.Count;
                    for (int i = 0; i < nCount; i++)
                        comboBox.Items[i] = ConvertString(comboBox.Items[i].ToString());
                }
            }
            catch (System.Exception)
            {
            }
        }

        /// <summary>
        ///  Init Tool bar title 
        /// </summary>
        /// <param name="ToolStripItem"></param>
        /// <param name="isMenuItem"></param>
        public static void InitToolStripItemText(ToolStripItem item, bool isMenuItem)
        {
            try
            {
                item.Text = ConvertString(item.Text);

                if (isMenuItem)
                {
                    ToolStripMenuItem menuItem = (ToolStripMenuItem)item;
                    int nCount = menuItem.DropDownItems.Count;
                    for (int i = 0; i < nCount; i++ )
                    {
                        InitToolStripItemText(menuItem.DropDownItems[i], true);
                    }
                }
            }
            catch(System.Exception)
            {
            }      
        }


        /// <summary>
        /// 
        /// </summary>
        /// <param name="strKey"></param>
        /// <returns></returns>
        public static string ConvertString(string strKey)
        {
            try
            {
                string strEnd = string.Empty;
                string strNewKey = strKey;
                if (strNewKey.EndsWith(":") ||
                    strNewKey.EndsWith("：") ||
                    strNewKey.EndsWith("!") ||
                    strNewKey.EndsWith("!") ||
                    strNewKey.EndsWith("?") ||
                    strNewKey.EndsWith("?"))
                {
                    strEnd = strNewKey.Substring(strNewKey.Length - 1);
                    strNewKey = strNewKey.Substring(0, strNewKey.Length - 1);
                }

                StringBuilder strBuilder = new StringBuilder(256);
                GetPrivateProfileString(strAppName, strNewKey, "", strBuilder, 256, strIniFileName);

                string strRet = strBuilder.ToString();

                return (strRet.Length > 0) ?
                        strRet + strEnd : 
                        strKey;
            }
            catch (System.Exception ex)
            {
                Console.WriteLine(ex.Message);
                return strKey;
            }
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="strKey"></param>
        /// <param name="strApp"></param>
        /// <returns></returns>
        public static string ConvertString(string strKey, string strTempApp)
        {
            try
            {
                string strOldApp = strAppName;
                strAppName = strTempApp;

                string strRet = ConvertString(strKey);
                strAppName = strOldApp;

                return strRet;
            }
            catch (System.Exception)
            {
                return strKey;
            }

        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="strKey"></param>
        /// <param name="strApp"></param>
        /// <returns></returns>
        public static string ConvertString(string strKey, string strTempApp, string strTempFile)
        {
            try
            {
                string strOldApp = strAppName;
                string strOldFile = strIniFileName;
                strAppName = strTempApp;
                strIniFileName = strTempFile;

                string strRet = ConvertString(strKey);
                strAppName = strOldApp;
                strIniFileName = strOldFile;

                return strRet;
            }
            catch (System.Exception ex)
            {
                return strKey;
            }
        }

        public enum CodePage
        {
            CP_ACP = 0,          // default to ANSI code page
            CP_OEMCP = 1,           // default to OEM  code page
            CP_MACCP = 2,           // default to MAC  code page
            CP_THREAD_ACP = 3,           // current thread's ANSI code page
            CP_SYMBOL = 42,          // SYMBOL translations

            CP_UTF7 = 65000,       // UTF-7 translation
            CP_UTF8 = 65001,       // UTF-8 translation
        }

        public static void Change_Utf8_Ascii(char[] pUTF8, ref char[] destbuf)
        {
            int nSrcStrLen = pUTF8.Length;
            int nDestStrLen = nSrcStrLen * 2;
            char[] tmpBuf = new char[nDestStrLen];
            for (int i = 0; i < nDestStrLen; i++)
                tmpBuf[i] = '\0';

            int nNum = MultiByteToWideChar(CodePage.CP_UTF8, 0, pUTF8, nSrcStrLen, ref tmpBuf, nDestStrLen);

            nNum = WideCharToMultiByte(CodePage.CP_ACP, 0, tmpBuf, nNum, ref destbuf, nSrcStrLen, null, IntPtr.Zero);
        }

        /// <summary>
        ///  Read Private Profile
        /// </summary>
        /// <param name="strAppName"></param>
        /// <returns></returns>
        [DllImport("kernel32.dll")]
        public static extern int GetPrivateProfileString(string strAppName,
                                                         string strKeyName, 
                                                         string strDefualt, 
                                                         StringBuilder strReturned,
                                                         int nSize,
                                                         string strFileName);


        /// <summary>
        ///  Write Private Profile
        /// </summary>
        /// <param name="strAppName"></param>
        /// <returns></returns>
        [DllImport("kernel32.dll")]
        public static extern int WritePrivateProfileString(string strAppName,
                                                           string strKeyName,
                                                           string strValue,
                                                           string strFileName);

        /// <summary>
        /// Write Private Profile
        /// </summary>
        /// <param name="strAppName"></param>
        /// <returns></returns>
        [DllImport("kernel32.dll")]
        public static extern int MultiByteToWideChar(CodePage CodePage, 
                                                     ulong dwFlags,
                                                     char[] lpMultiByteStr,
                                                     int cchMultiByte,
                                                     ref char[] lpWideCharStr,
                                                     int cchWideChar);

        /// <summary>
        /// Write Private Profile
        /// </summary>
        /// <param name="strAppName"></param>
        /// <returns></returns>
        [DllImport("kernel32.dll")]
        public static extern int WideCharToMultiByte(CodePage CodePage,
                                                     ulong dwFlags,
                                                     char[] lpWideCharStr,
                                                     int cchWideChar,
                                                     ref char[] lpMultiByteStr,
                                                     int cchMultiByte,
                                                     char[] lpDefaultChar,
                                                     IntPtr lpUsedDefaultChar);
    }
}
