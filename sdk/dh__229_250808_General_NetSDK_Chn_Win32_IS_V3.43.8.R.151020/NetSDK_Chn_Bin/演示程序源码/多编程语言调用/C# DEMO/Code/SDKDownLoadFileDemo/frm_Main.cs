using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using NetSDK;
using System.Runtime.InteropServices;
using Utility;      

namespace SDKDownLoadFileDemo
{
    public partial class frm_Main : Form
    { 
        /// <summary>
        /// the login handle of the device users
        /// </summary>
        private int pLoginID;
        /// <summary>
        /// the program message notice Title
        /// </summary>
        private const string pMsgTitle = "Network program SDK Demo";
        /// <summary>
        /// the displaying format of the last operation information
        /// </summary>
        private const string pErrInfoFormatStyle = "Code:errcode;\ndescription:errmSG.";
        /// <summary>
        /// the information of the users
        /// </summary>
        private USER_MANAGE_INFO userManageInfo;
        /// <summary>
        /// regular alarming messages
        /// </summary>
        private NET_CLIENT_STATE clientState;
        /// <summary>
        /// download the handles according the file
        /// </summary>
        private int pDownloadHandleByFile;
        /// <summary>
        /// download the handles according the file
        /// </summary>
        private int pDownloadHandleByTime;
        /// <summary>
        /// download the handles
        /// </summary>
        private int pDownloadHandle;
        /// <summary>
        /// interrupt the callback
        /// </summary>
        private fDisConnect disConnect;
        /// <summary>
        /// download the callback
        /// </summary>
        private fDownLoadPosCallBack downLoadFun;

        //private delegate void fTimeDownLoadPosCallBack(int lPlayHandle, UInt32 dwTotalSize, UInt32 dwDownLoadSize, int index, NET_RECORDFILE_INFO recordfileinfo, IntPtr dwUser);

        private fTimeDownLoadPosCallBack timeDownLoadFun;
        /// <summary>
        /// the download percentage
        /// </summary>
        private double dblDownLoadPos;

        private delegate void fSetProgressPos(int lPlayHandle, UInt32 dwTotalSize, UInt32 dwDownLoadSize);

        private fSetProgressPos setProgressPos;

        private string strUserName = "test";

        private NET_DEVICEINFO deviceInfo;

        public frm_Main()
        {
            InitializeComponent();
        }
        /// <summary>
        /// initialize the images' loading
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void frmMain_Load(object sender, EventArgs e)
        {
            disConnect = new fDisConnect(DisConnectEvent);
            NETClient.NETInit(disConnect, IntPtr.Zero);
            downLoadFun = new fDownLoadPosCallBack(DownLoadPosFun);
            timeDownLoadFun = new fTimeDownLoadPosCallBack(TimeDownLoadPosFun);
            //timeDownLoadFun = new fDownLoadPosCallBack(TimeDownLoadPosFun);
            setProgressPos  = new fSetProgressPos(DownloadProgress);
            grbMain.Enabled = false;
            btnDownLoad1.Tag = "";
            btnDownLoad2.Tag = "";

            StringUtil.InitControlText(this);
        }
        /// <summary>
        /// deal with the disconnected equipment
        /// </summary>
        /// <param name="lLoginID"> login ID</param>
        /// <param name="pchDVRIP">DVR equipment IP</param>
        /// <param name="nDVRPort">DVR equipment port </param>
        /// <param name="dwUser"> the users data </param>
        private void DisConnectEvent(int lLoginID, StringBuilder pchDVRIP, int nDVRPort, IntPtr dwUser)
        {
            //deal with the disconnect          
            MessageUtil.ShowMsgBox(StringUtil.ConvertString("Device users interrupt the connection"),
                                   StringUtil.ConvertString(pMsgTitle));
        }
        /// <summary>
        /// press the user login button to deal with
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btnUserLogin_Click(object sender, EventArgs e)
        {
            string strBtn = btnUserLogin.Text;
            if (strBtn == Utility.StringUtil.ConvertString("Equipment users login"))
            {
                frm_AddDevice fLogin = new frm_AddDevice();
                fLogin.ShowDialog();
                if (fLogin.blnOKEnter == true)
                {
                    //achieve the information of the equipment users
                    deviceInfo = new NET_DEVICEINFO();
                    int error = 0;
                    //equipment users login
                    pLoginID = NETClient.NETLogin(fLogin.cmbDevIP.Text.ToString(), ushort.Parse(fLogin.txtDevProt.Text.ToString()), fLogin.txtName.Text.ToString(), fLogin.txtPassword.Text.ToString(), out deviceInfo, out error);
                    if (pLoginID != 0)
                    {
                        strUserName = fLogin.txtDevName.Text;
                        btnUserLogin.BackColor = Color.Yellow;
                        btnUserLogin.Text = StringUtil.ConvertString("Equipment users logout");
                        grbMain.Enabled = true;
                    }
                    else
                    {
                        //report the error information of the last operation
                        MessageUtil.ShowMsgBox(StringUtil.ConvertString(NETClient.LastOperationInfo.errMessage, "ErrorMessage"),
                                               StringUtil.ConvertString(pMsgTitle));
                    }
                }
            }
            else if (strBtn == Utility.StringUtil.ConvertString("Equipment users logout"))
            {
                bool result = NETClient.NETLogout(pLoginID);
                if (result == false)
                {
                    //report the error information of the last operation
                    MessageUtil.ShowMsgBox(StringUtil.ConvertString(NETClient.LastOperationInfo.errMessage, "ErrorMessage"),
                                           StringUtil.ConvertString(pMsgTitle));
                }
                btnUserLogin.BackColor = Color.Transparent;
                btnUserLogin.Text = StringUtil.ConvertString("Equipment users login");
                grbMain.Enabled = false;

                Utility.StringUtil.InitControlText(this);
            }
        }

        /// <summary>
        /// press the button downloading according the file
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btnDownLoad1_Click(object sender, EventArgs e)
        {
            frm_PlayBackByFileSet fpf = new frm_PlayBackByFileSet();
            int pPlayBackChannelID = 0;
            NET_RECORDFILE_INFO fileInfo;
            fpf.gLoginID = pLoginID;
            fpf.txtDevName.Text = strUserName;
            fpf.cmbChannelSelect.Items.Clear();
            for (int i = 1; i <= deviceInfo.byChanNum; i++)
                fpf.cmbChannelSelect.Items.Add(i);
            fpf.ShowDialog(this);
            if (fpf.blnOKEnter == true)
            {
                pPlayBackChannelID = int.Parse(fpf.txtChannelID.Text.ToString());
                fileInfo = fpf.gFileInfo;
                //**********download according the file**********
                if (txtDirPath1.Text.Trim().Length>0 && txtFileName1.Text.Trim().Length > 0)
                {
                    string strFileName = txtFileName1.Text;
                    strFileName = strFileName.ToLower();
                    if (!strFileName.EndsWith(".dav"))
                        strFileName += ".dav";

                    pDownloadHandleByFile = NETClient.NETDownloadByRecordFile(pLoginID, fileInfo, txtDirPath1.Text + @"\" + strFileName, downLoadFun, IntPtr.Zero);
                    if (pDownloadHandleByFile != 0)
                    {
                        btnDownLoad1.Tag = "in the download";
                        pDownloadHandle = pDownloadHandleByFile;
                        btnDownLoad2.Enabled = false;
                        btnDownLoad1.Enabled = false;
                        btnStopDownLoad1.Enabled = true;
                        MessageUtil.ShowMsgBox(StringUtil.ConvertString("begin to download!"),
                                               StringUtil.ConvertString(pMsgTitle));
                    }
                    else
                    {
                        MessageUtil.ShowMsgBox(StringUtil.ConvertString(NETClient.LastOperationInfo.errMessage, "ErrorMessage"),
                                               StringUtil.ConvertString(pMsgTitle));
                    }
                }
                else
                {
                    MessageUtil.ShowMsgBox(StringUtil.ConvertString("please input the valid video-saving directory and file name!"),
                                           StringUtil.ConvertString(pMsgTitle));
                }
                
                //******************************                
            }
        }

        private void DownloadProgress(int lPlayHandle, UInt32 dwTotalSize, UInt32 dwDownLoadSize)
        {

            if (dwDownLoadSize != 0xFFFFFFFF &&
                dwDownLoadSize != 0xFFFFFFFE &&
                dwDownLoadSize <= dwTotalSize)
            {
                int iPos = (int)((dwDownLoadSize * 100) / dwTotalSize);
                Console.WriteLine(iPos.ToString() + " " + dwDownLoadSize.ToString() + "/" + dwTotalSize.ToString());
                psbMain.Value = iPos;
            }
            else
            {
                if (0xFFFFFFFF == dwDownLoadSize)
                {
                    btnDownLoad2.Tag = "";
                    psbMain.Value = 0;
                    MessageUtil.ShowMsgBox(StringUtil.ConvertString("download end!"));
                    btnDownLoad1.Enabled = true;
                    btnDownLoad2.Enabled = true;

                    psbMain.Value = 0;

                    //NETClient.NETStopDownload(lPlayHandle);
                }
                else if (0xFFFFFFFE == dwDownLoadSize)
                {
                    btnDownLoad2.Tag = "";
                    psbMain.Value = 0;
                    MessageUtil.ShowMsgBox(StringUtil.ConvertString("insufficient disk space!"));
                    btnDownLoad1.Enabled = true;
                    btnDownLoad2.Enabled = true;

                    psbMain.Value = 0;

                    //NETClient.NETStopDownload(lPlayHandle);
                }
            }
        }

        /// <summary>
        /// download the callback
        /// </summary>
        /// <param name="lPlayHandle"> paly the handles </param>
        /// <param name="dwTotalSize"> the cumulative size </param>
        /// <param name="dwDownLoadSize"> the download size </param>
        /// <param name="dwUser"> the user data </param>
        private void DownLoadPosFun(int lPlayHandle, UInt32 dwTotalSize, UInt32 dwDownLoadSize, IntPtr dwUser)
        {
            this.Invoke(setProgressPos, new object[]{lPlayHandle, dwTotalSize, dwDownLoadSize});

            if (0xFFFFFFFF == dwDownLoadSize || 0xFFFFFFFE == dwDownLoadSize)
            {
                NETClient.NETStopDownload(lPlayHandle);
            }
        }

        //private void TimeDownLoadPosFun(int lPlayHandle, UInt32 dwTotalSize, UInt32 dwDownLoadSize, int index, NET_RECORDFILE_INFO recordfileinfo, IntPtr dwUser)
        //private void TimeDownLoadPosFun(int lPlayHandle, UInt32 dwTotalSize, UInt32 dwDownLoadSize, IntPtr dwUser)
        public void TimeDownLoadPosFun(int lPlayHandle, int dwTotalSize, int dwDownLoadSize, int index
            , NET_RECORDFILE_INFO recordfileinfo, IntPtr dwUser)
        {
            this.Invoke(setProgressPos, new object[] { lPlayHandle, (UInt32)dwTotalSize, (UInt32)dwDownLoadSize });

            if (0xFFFFFFFF == dwDownLoadSize || 0xFFFFFFFE == dwDownLoadSize)
            {
                NETClient.NETStopDownload(lPlayHandle);
            }
        }

        /// <summary>
        /// choose according to the file-downloading directory
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btnDirSelect1_Click(object sender, EventArgs e)
        {
            if(fbdMain.ShowDialog()==DialogResult.OK)
            {
                txtDirPath1.Text = fbdMain.SelectedPath;
            }
        }
        /// <summary>
        /// press the button of downloading according to the file
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btnStopDownLoad1_Click(object sender, EventArgs e)
        {
            if (btnDownLoad1.Tag.ToString().Equals("in the download"))
            {
                bool blnStopSucced = NETClient.NETStopDownload(pDownloadHandleByFile);
                if (blnStopSucced)
                {
                    btnDownLoad1.Enabled = true;
                    btnDownLoad2.Enabled = true;
                    btnStopDownLoad1.Enabled = false;

                    MessageUtil.ShowMsgBox(StringUtil.ConvertString("succeed to stop the download!"),
                                           StringUtil.ConvertString(pMsgTitle));
                }
                else
                {
                    MessageUtil.ShowMsgBox(StringUtil.ConvertString(NETClient.LastOperationInfo.errMessage, "ErrorMessage"),
                                           StringUtil.ConvertString(pMsgTitle));
                }
                btnDownLoad1.Tag = "";
                psbMain.Maximum = 100;
                psbMain.Value = 0;
            }
            else
            {
                MessageUtil.ShowMsgBox(StringUtil.ConvertString("no download task at the time!"),
                                       StringUtil.ConvertString(pMsgTitle));
            }
            
        }
        /// <summary>
        /// get the download percentage according to the file
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btnGetDownLoadPos1_Click(object sender, EventArgs e)
        {
            if (btnDownLoad1.Tag.ToString().Equals("in the download"))
            {
                int dwTotal=0;
                int dwSize=0;
                bool blnGetPosSucced = NETClient.NETGetDownloadPos(pDownloadHandleByFile, out dwTotal, out dwSize);
                if (blnGetPosSucced)
                {
                    MessageUtil.ShowMsgBox(StringUtil.ConvertString("download statistics:") + "\n\t" +
                                           StringUtil.ConvertString("total length:") +
                                           dwTotal.ToString() + "\n\t" + StringUtil.ConvertString("downloaded:") + dwSize.ToString(),
                                           StringUtil.ConvertString(pMsgTitle));
                }
                else
                {
                    MessageUtil.ShowMsgBox(StringUtil.ConvertString(NETClient.LastOperationInfo.errMessage, "ErrorMessage"),
                                           StringUtil.ConvertString(pMsgTitle));
                }
            }
            else
            {
                MessageUtil.ShowMsgBox(StringUtil.ConvertString("no download task at the time!"),
                                       StringUtil.ConvertString(pMsgTitle));
            }
        }
        /// <summary>
        /// press the button of downloading according the time
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btnDownLoad2_Click(object sender, EventArgs e)
        {
            frm_PlayBackByTimeSet fPBSet = new frm_PlayBackByTimeSet();
            NET_RECORDFILE_INFO            fileInfo = new NET_RECORDFILE_INFO();
            int fileCount = 0;
            bool blnQueryRecordFile = false;
            int pPlayBackChannelID=0;
            fPBSet.txtDevName.Text = strUserName;
            fPBSet.cmbChannelSelect.Items.Clear();
            for (int i = 1; i <= deviceInfo.byChanNum; i++ )
            {
                fPBSet.cmbChannelSelect.Items.Add(i);
            }
            fPBSet.ShowDialog();
            if (fPBSet.blnOKEnter == true)
            {
                DateTime startTime = fPBSet.StartTime;
                DateTime endTime = fPBSet.EndTime;

                blnQueryRecordFile = NETClient.NETQueryRecordFile(pLoginID, int.Parse(fPBSet.txtChannelID.Text.ToString()), RECORD_FILE_TYPE.ALLRECORDFILE,
                                                                startTime, endTime, null, ref fileInfo, Marshal.SizeOf(typeof(NET_RECORDFILE_INFO)), out  fileCount, 5000, false);//按时间回放
                if (blnQueryRecordFile == true)
                {
                    //**********download according the file**********
                    pPlayBackChannelID = int.Parse(fPBSet.txtChannelID.Text.ToString());
                    if (txtDirPath2.Text.Trim().Length > 0 && txtFileName2.Text.Trim().Length > 0)
                    {
                        string strFileName = txtFileName2.Text;
                        strFileName = strFileName.ToLower();
                        if (!strFileName.EndsWith(".dav"))
                            strFileName += ".dav";

                        // close the related resource downloaded last time
                        if (pDownloadHandleByTime != 0)
                        {
                            NETClient.NETStopDownload(pDownloadHandleByTime);
                            pDownloadHandle = 0;
                        }

                        pDownloadHandleByTime = NETClient.NETDownloadByTime(pLoginID, pPlayBackChannelID, 0, startTime
                            , endTime, txtDirPath2.Text + @"\" + strFileName, timeDownLoadFun, IntPtr.Zero);
                        if (pDownloadHandleByTime != 0)
                        {
                            btnDownLoad2.Tag = "in the download";
                            pDownloadHandle = pDownloadHandleByTime;
                            btnDownLoad2.Enabled = false;
                            btnDownLoad1.Enabled = false;
                            btnStopDownLoad2.Enabled = true;
                            MessageUtil.ShowMsgBox(StringUtil.ConvertString("begin to download!"),
                                                   StringUtil.ConvertString(pMsgTitle));
                        }
                        else
                        {
                            MessageUtil.ShowMsgBox(StringUtil.ConvertString(NETClient.LastOperationInfo.errMessage, "ErrorMessage"),
                                                   StringUtil.ConvertString(pMsgTitle));
                        }
                    }
                    else
                    {
                        MessageUtil.ShowMsgBox(StringUtil.ConvertString("please input the valid video-saving dierectory and file name!"),
                                               StringUtil.ConvertString(pMsgTitle));
                    }
                    //*******************************
                }
                else
                {
                    MessageUtil.ShowMsgBox(StringUtil.ConvertString("no video file is available during the time!"),
                                           StringUtil.ConvertString(pMsgTitle));
                }
            }
        }
        /// <summary>
        /// stop and press the button of downloading according to the time
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btnStopDownLoad2_Click(object sender, EventArgs e)
        {
            if (btnDownLoad2.Tag.ToString().Equals("in the download"))
            {
                bool blnStopSucced = NETClient.NETStopDownload(pDownloadHandleByTime);
                if (blnStopSucced)
                {
                    btnDownLoad1.Enabled = true;
                    btnDownLoad2.Enabled = true;
                    btnStopDownLoad2.Enabled = false;

                    MessageUtil.ShowMsgBox(StringUtil.ConvertString("succeed to stop the download!"),
                       StringUtil.ConvertString(pMsgTitle));
                }
                else
                {
                    MessageUtil.ShowMsgBox(StringUtil.ConvertString(NETClient.LastOperationInfo.errMessage, "ErrorMessage"),
                                           StringUtil.ConvertString(pMsgTitle));
                }
                btnDownLoad2.Tag = "";
                psbMain.Maximum = 100;
                psbMain.Value = 0;
            }
            else
            {
                MessageUtil.ShowMsgBox(StringUtil.ConvertString("no download task at the time!"),
                                       StringUtil.ConvertString(pMsgTitle));
            }
        }
        /// <summary>
        /// get the download percentage according the time and press the button to deal with
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btnGetDownLoadPos2_Click(object sender, EventArgs e)
        {
            if (btnDownLoad2.Tag.ToString().Equals("in the download"))
            {
                int dwTotal = 0;
                int dwSize = 0;
                bool blnGetPosSucced = NETClient.NETGetDownloadPos(pDownloadHandleByTime, out dwTotal, out dwSize);
                if (blnGetPosSucced)
                {
                    MessageUtil.ShowMsgBox(StringUtil.ConvertString("download statistics:") + "\n\t" +
                                           StringUtil.ConvertString("total length:") +
                                           dwTotal.ToString() + "\n\t" + StringUtil.ConvertString("downed:") + dwSize.ToString(),
                                           StringUtil.ConvertString(pMsgTitle));
                }
                else
                {
                    MessageUtil.ShowMsgBox(StringUtil.ConvertString(NETClient.LastOperationInfo.errMessage, "ErrorMessage"),
                                           StringUtil.ConvertString(pMsgTitle));
                }
            }
            else
            {
                MessageUtil.ShowMsgBox(StringUtil.ConvertString("no download task at the time!"), 
                                       StringUtil.ConvertString(pMsgTitle));
            }
        }
        /// <summary>
        /// press the directory-saving button
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btnDirSelect_Click(object sender, EventArgs e)
        {
            if (fbdMain.ShowDialog() == DialogResult.OK)
            {
                txtDirPath2.Text = fbdMain.SelectedPath;
            }

        }
    }
}