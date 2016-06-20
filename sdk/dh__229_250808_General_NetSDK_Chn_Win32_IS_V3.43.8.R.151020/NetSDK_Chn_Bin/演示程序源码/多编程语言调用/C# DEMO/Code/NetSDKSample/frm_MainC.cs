using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using NetSDK;                         //Network SDK(C#)
using System.Runtime.InteropServices;
using PlaySDK;
using Utility;

namespace NetSDKSample
{
    public partial class frm_MainC : Form
    {
        #region << variable definition >>

        /// <summary>
        /// user login ID
        /// </summary>
        private int pLoginID;

        /// <summary>
        /// Message Title
        /// </summary>
        private const string pMsgTitle = "Network SDK Demo Apps";

        /// <summary>
        ///  Information Display Format of the Last Operation 
        /// </summary>
        private const string pErrInfoFormatStyle = "Code:errcode;\nDescription:errmSG.";

        /// <summary>
        /// The Current Playback File Information
        /// </summary>
        NET_RECORDFILE_INFO fileInfo;

        /// <summary>
        /// Play Mode
        /// </summary>
        private int playBy = 0;

        /// <summary>
        /// Save the Handle of Real-time Playback.
        /// </summary>
        private int[] pRealPlayHandle;

        /// <summary>
        /// Save the Handle of Playback.
        /// </summary>
        private int[] pPlayBackHandle;

        /// <summary>
        /// Channel Number of Playback 
        /// </summary>
        private int pPlayBackChannelID;

        /// <summary>
        /// PictureBox button of Last Click
        /// </summary>
        private PictureBox oldPicRealPlay;

        /// <summary>
        /// PictureBox button of Click Currently 
        /// </summary>
        private PictureBox picRealPlay;

        private List<PictureBox> lstAllRealPlay;

        private fDisConnect disConnect;

        private NET_DEVICEINFO deviceInfo;

        private int pMultiPlayHandle;
        private string strMultiPlayStart = "Start MultiPlay";
        private string strMultiPlayStop = "Stop MultiPlay";
		
        private bool        bFullModel = false;
        private Rectangle   stuOriRect;
		
        private DateTime PlaybackBeginTime;
		private DateTime PlaybackEndTime;
        private int m_LastScrollValue;
        #endregion

        #region << Window Class Constructor >>

        public frm_MainC()
        {
            InitializeComponent();

        }

        #endregion 

        #region << Code for Application Functionality  >>

        /// <summary>
        /// Image Initial Porcessing
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void frm_MainC_Load(object sender, EventArgs e)
        {
            disConnect = new fDisConnect(DisConnectEvent);
            NETClient.NETInit(disConnect, IntPtr.Zero);
            NETClient.NETSetEncoding(LANGUAGE_ENCODING.gb2312);//Character Encoding Format Setting.Default Value is gb2312 Character Encoding,Otherwise Please Set it.       
            pRealPlayHandle             = null;
            btnRealPlay.Text            = StringUtil.ConvertString("Start Real-time Monitoring");
            btnRealPlay.Enabled         = false;
            btnPlayBackByTime.Enabled   = false;
            gpbPlayBackControl.Enabled  = false;
            btnUserLogout.Enabled       = false;
            gpbPTZControl.Enabled       = false;
            btnPlayByRecordFile.Enabled = false;
            btnMultiPlay.Enabled        = false;
            pMultiPlayHandle            = 0;
            stuOriRect = new Rectangle();
            InitPlayBoxManger();
            StringUtil.InitControlText(this);
        }
        /// <summary>
        /// [user login]Press the button.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btnUserLogin_Click(object sender, EventArgs e)
        {
            frm_AddDevice fAddDev = new frm_AddDevice();
            fAddDev.ShowDialog();
            try
            {
                if (fAddDev.blnOKEnter == true)
                {
                    //Device User Info Acquisition
                    deviceInfo = new NET_DEVICEINFO();
                    int error = 0;
                    pLoginID = NETClient.NETLogin(fAddDev.cmbDevIP.Text.ToString(), ushort.Parse(fAddDev.txtDevProt.Text.ToString()),fAddDev.txtName.Text.ToString(), fAddDev.txtPassword.Text.ToString(), out deviceInfo, out error);
                    if (pLoginID != 0)
                    {
                        pPlayBackHandle             = new int[deviceInfo.byChanNum];
                        pRealPlayHandle             = null;
                        btnRealPlay.Text            = StringUtil.ConvertString("Start Real-time Monitoring");
                        btnMultiPlay.Text           = strMultiPlayStart;
                        btnUserLogin.Enabled        = false;
                        btnRealPlay.Enabled         = true;
                        btnPlayBackByTime.Enabled   = true;
                        gpbPlayBackControl.Enabled  = false;
                        btnUserLogout.Enabled       = true;
                        gpbPTZControl.Enabled       = false;
                        btnPlayByRecordFile.Enabled = true;
                        btnMultiPlay.Enabled        = true;
                        cmbChannelSelect.Items.Clear();
                        picRealPlay = picRealPlay0;
                        for (int i = 0; i < deviceInfo.byChanNum; i++)
                        {
                            cmbChannelSelect.Items.Add(i.ToString());
                        }
                    }
                    else
                    { 
                        MessageBox.Show(NETClient.LastOperationInfo.ToString(pErrInfoFormatStyle),pMsgTitle);
                        btnUserLogin_Click(null, null);                        
                    }
                }
            }
            catch
            {
                MessageBox.Show(NETClient.LastOperationInfo.ToString(pErrInfoFormatStyle), pMsgTitle);
                btnUserLogin_Click(null, null);
            }
        }

        /// <summary>
        /// [Logout User]Press The Button.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btnUserLogout_Click(object sender, EventArgs e)
        {
            try
            {
                bool result = NETClient.NETLogout(pLoginID);
                if (result == false)
                {
                    //Report the Error Information of the Last Operation.
                    MessageBox.Show(NETClient.LastOperationInfo.ToString(pErrInfoFormatStyle), pMsgTitle);
                }
                StopMultiPlay();
                RefreshAllPlayBox();
                //Image Initialized
                this.Controls.Clear();
                InitializeComponent();
                InitPlayBoxManger();
                Utility.StringUtil.InitControlText(this);
                pLoginID = 0;
                fileInfo = new NET_RECORDFILE_INFO();
                playBy = 0;
                pRealPlayHandle = new int[16];
                pPlayBackHandle = new int[16];
                pPlayBackChannelID = 0;
                deviceInfo = new NET_DEVICEINFO();
                this.WindowState = FormWindowState.Normal;
                btnRealPlay.Enabled = false;
                btnPlayBackByTime.Enabled = false;
                gpbPlayBackControl.Enabled = false;
                btnUserLogout.Enabled = false;
                btnMultiPlay.Enabled = false;
                btnRealPlay.Text = StringUtil.ConvertString("Start Real-time Monitoring");
                btnPlayByRecordFile.Enabled = false;
                gpbPlayBackControl.Enabled = false;
                gpbPTZControl.Enabled = false;
                pLoginID = 0;
                m_LastScrollValue = 0;
            }
            catch
            {
                MessageBox.Show("Device User Logout Failed!", pMsgTitle);                
            }
        }

        /// <summary>
        /// Close Window 
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void frm_MainC_FormClosing(object sender, FormClosingEventArgs e)
        {
            NETClient.NETCleanup();
        }

        /// <summary>
        /// Press the Real-time Play Button.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btnRealPlay_Click(object sender, EventArgs e)
        {
            string strStart = StringUtil.ConvertString("Start Real-time Monitoring");
            string strStop = StringUtil.ConvertString("End Real-time Monitoring");

            if (btnRealPlay.Text.Equals(strStart))
            {
                btnRealPlay.Text = strStop;
                pRealPlayHandle = new int[deviceInfo.byChanNum];
                cmbChannelSelect.Items.Clear();
                for (int i = 0; i < deviceInfo.byChanNum; i++)
                {
                    cmbChannelSelect.Items.Add(i.ToString());
                }
                cmbChannelSelect.SelectedIndex = 0;

                for (int i = 0; i < deviceInfo.byChanNum; i++)
                {
                    pRealPlayHandle[i] = RealPlayInBox(i);
                    NETClient.NetSetSecurityKey(pRealPlayHandle[i], "SPL17THALES00000");// Set Aes Security Key
                    if (pRealPlayHandle[i] == 0)
                    {
                        break;
                    }
                }
                gpbPTZControl.Enabled = true;
            }
            else
            {
                btnRealPlay.Text = strStart;
                cmbChannelSelect.Items.Clear();
                for (int i = 0; i < deviceInfo.byChanNum; i++)
                {
                    NETClient.NETStopRealPlay(pRealPlayHandle[i]);

                }
                RefreshAllPlayBox();
                gpbPTZControl.Enabled = false;
            }
        }


        /// <summary>
        /// Press the button of playback according to the time.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btnPlayBackByTime_Click(object sender, EventArgs e)
        {
            playBy = 1;
            frm_PlayBackByTimeSet fPBSet = new frm_PlayBackByTimeSet();
            fPBSet.cmbChannelSelect.Items.Clear();
            for (int i = 0; i < deviceInfo.byChanNum; i++)
            {
                fPBSet.cmbChannelSelect.Items.Add(i.ToString());
            }
            fileInfo = new NET_RECORDFILE_INFO();
            int fileCount = 0;
            bool blnQueryRecordFile = false;

            fPBSet.ShowDialog();
            if (fPBSet.blnOKEnter == true)
            {
                DateTime startTime = fPBSet.dtpStart.Value;
                string[] strTemp = fPBSet.txtTimeStart.Text.ToString().Split(':');
                if (3 == strTemp.Length)
                {
                    startTime = startTime.AddHours(double.Parse(strTemp[0]));
                    startTime = startTime.AddMinutes(double.Parse(strTemp[1]));
                    startTime = startTime.AddSeconds(double.Parse(strTemp[2]));
                }
                DateTime endTime = fPBSet.dtpEnd.Value;
                string[] strTempEnd = fPBSet.txtTimeEnd.Text.ToString().Split(':');
                if (3 == strTempEnd.Length)
                {
                    endTime = endTime.AddHours(double.Parse(strTempEnd[0]));
                    endTime = endTime.AddMinutes(double.Parse(strTempEnd[1]));
                    endTime = endTime.AddSeconds(double.Parse(strTempEnd[2]));
                }
                if (startTime >= endTime)
                {
                    MessageBox.Show("Start date is not before the end date,please reset!", pMsgTitle);
                }
                else
                {
                    IntPtr pValue = new IntPtr();
                    pValue = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(int)));
                    Marshal.StructureToPtr(fPBSet.nStreamType, pValue, true);
                    if (NETClient.NETSetDeviceMode(pLoginID, NETClient.EM_USEDEV_MODE.DH_RECORD_STREAM_TYPE, pValue))
                    {
                        MessageBox.Show("Set Device Mode Success!");
                    }
                    else
                    {
                        MessageBox.Show("Set Devcie Mode Failed!", pMsgTitle);
                    }

                    blnQueryRecordFile = NETClient.NETQueryRecordFile(pLoginID, int.Parse(fPBSet.txtChannelID.Text.ToString()), RECORD_FILE_TYPE.ALLRECORDFILE, 
                                                                    startTime, endTime, null, ref fileInfo, Marshal.SizeOf(typeof(NET_RECORDFILE_INFO)), out  fileCount, 5000, false);//按时间回放
                    if (blnQueryRecordFile == true)
                    {
                        pPlayBackChannelID = int.Parse(fPBSet.txtChannelID.Text.ToString());
                        pPlayBackHandle[pPlayBackChannelID] = NETClient.NETPlayBackByTime(pLoginID, pPlayBackChannelID, startTime, endTime, picRealPlay.Handle, null, IntPtr.Zero);
                        if (pPlayBackHandle[pPlayBackChannelID] == 0)
                        {
                            MessageBox.Show("Playback According to The Time Failed!", pMsgTitle);
                        }
                        else
                        {
                            NETClient.NetSetSecurityKey(pPlayBackHandle[pPlayBackChannelID], "SPL17THALES00000");// Set Aes Security Key
                            btnPlay.Text = "||";
                            //Image Button Availability Control
                            btnPlayBackByTime.Enabled = false;
                            gpbPlayBackControl.Enabled = true;
                            btnPlay.Enabled = true;
                            btnSlow.Enabled = true;
                            btnStop.Enabled = true;
                            btnFast.Enabled = true;
                            btnSetpPlayS.Enabled = true;
                            hsbPlayBack.Enabled = true;
                            btnBackward.Enabled = true;
                            btnPlayByRecordFile.Enabled = false;
                            PlaybackBeginTime = startTime;
                            PlaybackEndTime = endTime;
                        }
                    }
                    else
                    {
                        MessageBox.Show("Cannot Find File!", pMsgTitle);
                    }
                }
            }
        }

        /// <summary>
        /// Press Pause Button
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btnPlay_Click(object sender, EventArgs e)
        {
            if (btnStepPlayE.Enabled == true)
            {
                btnStepPlayE_Click(null, null);
            }
            switch (btnPlay.Text.ToString())
            {
                case ">"://Play Control
                    if (NETClient.NETPlayBackControl(pPlayBackHandle[pPlayBackChannelID], PLAY_CONTROL.Play) == true)//play
                    {
                        btnPlay.Text = "||";
                    }
                    break;
                case "||"://Pause Control
                    if (NETClient.NETPlayBackControl(pPlayBackHandle[pPlayBackChannelID], PLAY_CONTROL.Pause) == true)//pause
                    {
                        btnPlay.Text = ">";
                    }
                    break;
            }
        }

        /// <summary>
        /// Press Stop Button
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btnStop_Click(object sender, EventArgs e)
        {
            if (NETClient.NETPlayBackControl(pPlayBackHandle[pPlayBackChannelID], PLAY_CONTROL.Stop) == false)//stop playback
            {
                MessageBox.Show("Stop Playback Failed!", pMsgTitle);
            }
            //Image Button Availability Control
            gpbPlayBackControl.Enabled = false;
            btnPlay.Enabled = false;
            btnSlow.Enabled = false;
            btnStop.Enabled = false;
            btnFast.Enabled = false;
            btnSetpPlayS.Enabled = false;
            hsbPlayBack.Enabled = false;
            btnPlayBackByTime.Enabled = true;
            btnPlayByRecordFile.Enabled = true;
            btnBackward.Text = "Backward";      
            picRealPlay.Refresh();
            picRealPlay.BackColor = SystemColors.Control;
            m_LastScrollValue = 0;
        }

        /// <summary>
        /// Press Step Forward Button
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btnNext_Click(object sender, EventArgs e)
        {
            try
            {
                if (NETClient.NETPlayBackControl(pPlayBackHandle[pPlayBackChannelID], PLAY_CONTROL.StepPlay) == true)//Start Step Forward
                {
                    btnStepPlayE.Enabled = true;
                }
                else
                {
                    MessageBox.Show("Step Forward Play Failed!", pMsgTitle);
                }
            }
            catch
            {
                MessageBox.Show(NETClient.LastOperationInfo.ToString(pErrInfoFormatStyle), pMsgTitle);
            }

        }

        /// <summary>
        /// Stop Step Forward
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btnStepPlayE_Click(object sender, EventArgs e)
        {
            try
            {
                if (NETClient.NETPlayBackControl(pPlayBackHandle[pPlayBackChannelID], PLAY_CONTROL.StepStop) == false)//Stop Step Forward
                {
                    MessageBox.Show("Step Forward Stop Failed!", pMsgTitle);
                }
                
            }
            catch
            {
                MessageBox.Show(NETClient.LastOperationInfo.ToString(pErrInfoFormatStyle), pMsgTitle);
            }
            btnStepPlayE.Enabled = false;
        }

        /// <summary>
        /// Press Slow Play Button
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btnSlow_Click(object sender, EventArgs e)
        {
            //Stop Step Play
            if (btnStepPlayE.Enabled == true)
            {
                btnStepPlayE_Click(null, null);
            }

            NETClient.NETPlayBackControl(pPlayBackHandle[pPlayBackChannelID], PLAY_CONTROL.Slow);//Slow Play Control
        }

        /// <summary>
        /// Play Quick Button
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btnFast_Click(object sender, EventArgs e)
        {
            //Stop Step Play
            if (btnStepPlayE.Enabled==true)
            {
                btnStepPlayE_Click(null, null);
            }
            NETClient.NETPlayBackControl(pPlayBackHandle[pPlayBackChannelID], PLAY_CONTROL.Fast);//Fast Play Control
        }

        /// <summary>
        /// Drag and Drop
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void hsbPlayBack_MouseCaptureChanged(object sender, EventArgs e)
        {
            if (hsbPlayBack.Value == m_LastScrollValue)
            {
                return;
            }
            //stop step play
            if (btnStepPlayE.Enabled == true)
            {
                btnStepPlayE_Click(null, null);
            }
            
            #region << Drag Function >>
            
            NETClient.NETPlayBackControl(pPlayBackHandle[pPlayBackChannelID], PLAY_CONTROL.Stop);
            long nTime = (long)(PlaybackBeginTime.Ticks + ((PlaybackEndTime.Ticks - PlaybackBeginTime.Ticks) * hsbPlayBack.Value / 100));
            DateTime SeekTime = new DateTime(nTime);
            switch (btnBackward.Text.ToString())
            {
                case "Backward":
                    pPlayBackHandle[pPlayBackChannelID] = NETClient.NETPlayBackByTimeEx2(pLoginID, pPlayBackChannelID, SeekTime, PlaybackEndTime, picRealPlay.Handle, null, IntPtr.Zero, null, IntPtr.Zero, 0, 10000);
                    if (0 == pPlayBackHandle[pPlayBackChannelID])//Backward
                    {
                        MessageBox.Show("Playback According to The Time Failed!", pMsgTitle);
                    }
                    else
                    {
                        NETClient.NetSetSecurityKey(pPlayBackHandle[pPlayBackChannelID], "SPL17THALES00000");// Set Aes Security Key
                    }
                    break;
                case "Forward":
                    pPlayBackHandle[pPlayBackChannelID] = NETClient.NETPlayBackByTimeEx2(pLoginID, pPlayBackChannelID, PlaybackBeginTime, SeekTime, picRealPlay.Handle, null, IntPtr.Zero, null, IntPtr.Zero, 1, 10000);
                    if (0 == pPlayBackHandle[pPlayBackChannelID])//Backward
                    {
                        MessageBox.Show("Playback According to The Time Failed!", pMsgTitle);
                    }
                    else
                    {
                        NETClient.NetSetSecurityKey(pPlayBackHandle[pPlayBackChannelID], "SPL17THALES00000");// Set Aes Security Key
                    }
                    break;                
            }

            #endregion
            m_LastScrollValue = hsbPlayBack.Value;// save last scroll value
        }
        /// <summary>
        /// PTZ Control[Click mouse button]Handling
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btnPTZControl_MouseDown(object sender, MouseEventArgs e)
        {
            int channelId = 0;
            if (cmbChannelSelect.SelectedIndex == -1)
            {
                MessageBox.Show("Please select the channel!", pMsgTitle);
                return;
            }
            else
            {
                channelId = cmbChannelSelect.SelectedIndex;
            }
            ushort stepValue = 1;
            if (txtStep.Text.Length > 0)
            {
                stepValue = ushort.Parse(txtStep.Text.ToString());
            }
            else
            {
                MessageBox.Show("Please type into the step(speed)value!", pMsgTitle);
                return;
            }

            # region <<**********PTZ Control Code**********>>
            switch (((Button)sender).Name)
            {
                case "btnLEFTTOP"://Upper Left
                    NETClient.NETPTZControl(pLoginID, channelId, PTZ_CONTROL.EXTPTZ_LEFTTOP, stepValue, stepValue, false);
                    break;
                case "btnTOP"://Up
                    NETClient.NETPTZControl(pLoginID, channelId, PTZ_CONTROL.PTZ_UP_CONTROL, 0, stepValue, false);
                    break;
                case "btnRIGHTDOWN"://Lower Right
                    NETClient.NETPTZControl(pLoginID, channelId, PTZ_CONTROL.EXTPTZ_RIGHTDOWN, stepValue, stepValue, false);
                    break;
                case "btnLEFT"://Left
                    NETClient.NETPTZControl(pLoginID, channelId, PTZ_CONTROL.PTZ_LEFT_CONTROL, 0, stepValue, false);
                    break;
                case "btnDOWN"://Down
                    NETClient.NETPTZControl(pLoginID, channelId, PTZ_CONTROL.PTZ_DOWN_CONTROL, 0, stepValue, false);
                    break;
                case "btnRIGHT"://Right
                    NETClient.NETPTZControl(pLoginID, channelId, PTZ_CONTROL.PTZ_RIGHT_CONTROL, 0, stepValue, false);
                    break;
                case "btnRIGHTTOP"://Upper Right
                    NETClient.NETPTZControl(pLoginID, channelId, PTZ_CONTROL.EXTPTZ_RIGHTTOP, stepValue, stepValue, false);
                    break;
                case "btnLEFTDOWN"://Lower Left
                    NETClient.NETPTZControl(pLoginID, channelId, PTZ_CONTROL.EXTPTZ_LEFTDOWN, stepValue, stepValue, false);
                    break;
                //case "btnZoomP"://Zoom in
                //    DHClient.DHPTZControl(pLoginID, channelId, PTZ_CONTROL.PTZ_ZOOM_ADD_CONTROL, stepValue, false);
                //    break;
                //case "btnZoomD"://Zoom out
                //    DHClient.DHPTZControl(pLoginID, channelId, PTZ_CONTROL.PTZ_ZOOM_DEC_CONTROL, stepValue, false);
                //    break;
                //case "btnFocusP"://Near Focus
                //    DHClient.DHPTZControl(pLoginID, channelId, PTZ_CONTROL.PTZ_FOCUS_ADD_CONTROL, stepValue, false);
                //    break;
                //case "btnFocusD"://Far Focus
                //    DHClient.DHPTZControl(pLoginID, channelId, PTZ_CONTROL.PTZ_FOCUS_DEC_CONTROL, stepValue, false);
                //    break;
                //case "btnIrisOpen"://IRIS Open
                //    DHClient.DHPTZControl(pLoginID, channelId, PTZ_CONTROL.PTZ_APERTURE_ADD_CONTROL, stepValue, false);
                //    break;
                //case "btnIrisClose"://IRIS Close
                //    DHClient.DHPTZControl(pLoginID, channelId, PTZ_CONTROL.PTZ_APERTURE_DEC_CONTROL, stepValue, false);
                //    break;
            }
            #endregion 
        }
        /// <summary>
        /// PTZ Control[Click mouse button] Handling
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btnPTZControl_MouseUp(object sender, MouseEventArgs e)
        {
            int channelId = 0;
            if (cmbChannelSelect.SelectedIndex == -1)
            {
                MessageBox.Show("Please select the channel!", pMsgTitle);
                return;
            }
            else
            {
                channelId = cmbChannelSelect.SelectedIndex;
            }
            ushort stepValue = 1;
            if (txtStep.Text.Length > 0)
            {
                stepValue = ushort.Parse(txtStep.Text.ToString());
            }
            else
            {
                MessageBox.Show("Please type into the step(speed)value!", pMsgTitle);
                return;
            }

            # region <<**********PTZ Control Code**********>>
            switch (((Button)sender).Name)
            {
                case "btnLEFTTOP"://Upper Left
                    NETClient.NETPTZControl(pLoginID, channelId, PTZ_CONTROL.EXTPTZ_LEFTTOP, stepValue, stepValue, true);
                    break;
                case "btnTOP"://Up
                    NETClient.NETPTZControl(pLoginID, channelId, PTZ_CONTROL.PTZ_UP_CONTROL, 0, stepValue, true);
                    break;
                case "btnRIGHTDOWN"://Lower Right
                    NETClient.NETPTZControl(pLoginID, channelId, PTZ_CONTROL.EXTPTZ_RIGHTDOWN, stepValue, stepValue, true);
                    break;
                case "btnLEFT"://Left
                    NETClient.NETPTZControl(pLoginID, channelId, PTZ_CONTROL.PTZ_LEFT_CONTROL, 0, stepValue, true);
                    break;
                case "btnDOWN"://Down
                    NETClient.NETPTZControl(pLoginID, channelId, PTZ_CONTROL.PTZ_DOWN_CONTROL, 0, stepValue, true);
                    break;
                case "btnRIGHT"://Right
                    NETClient.NETPTZControl(pLoginID, channelId, PTZ_CONTROL.PTZ_RIGHT_CONTROL, 0, stepValue, true);
                    break;
                case "btnRIGHTTOP"://Upper Right
                    NETClient.NETPTZControl(pLoginID, channelId, PTZ_CONTROL.EXTPTZ_RIGHTTOP, stepValue, stepValue, true);
                    break;
                case "btnLEFTDOWN"://Lower Left
                    NETClient.NETPTZControl(pLoginID, channelId, PTZ_CONTROL.EXTPTZ_LEFTDOWN, stepValue, stepValue, true);
                    break;
                //case "btnZoomP"://Zoom in
                //    NETClient.NETPTZControl(pLoginID, channelId, PTZ_CONTROL.PTZ_ZOOM_ADD_CONTROL, stepValue, true);
                //    break;
                //case "btnZoomD"://Zoom out
                //    NETClient.NETPTZControl(pLoginID, channelId, PTZ_CONTROL.PTZ_ZOOM_DEC_CONTROL, stepValue, true);
                //    break;
                //case "btnFocusP"://Near Focus
                //    NETClient.NETPTZControl(pLoginID, channelId, PTZ_CONTROL.PTZ_FOCUS_ADD_CONTROL, stepValue, true);
                //    break;
                //case "btnFocusD"://Far Focus
                //    NETClient.NETPTZControl(pLoginID, channelId, PTZ_CONTROL.PTZ_FOCUS_DEC_CONTROL, stepValue, true);
                //    break;
                //case "btnIrisOpen"://IRIS Open
                //    NETClient.NETPTZControl(pLoginID, channelId, PTZ_CONTROL.PTZ_APERTURE_ADD_CONTROL, stepValue, true);
                //    break;
                //case "btnIrisClose"://IRIS Close
                //    NETClient.NETPTZControl(pLoginID, channelId, PTZ_CONTROL.PTZ_APERTURE_DEC_CONTROL, stepValue, true);
                //    break;
            }
            #endregion 

        }
        /// <summary>
        /// Click PTZ Control Button
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btnPTZControl_Click(object sender, EventArgs e)
        {
            int channelId = 0;
            if (cmbChannelSelect.SelectedIndex == -1)
            {
                MessageBox.Show("Please select the channel!", pMsgTitle);
                return;
            }
            else
            {
                channelId = cmbChannelSelect.SelectedIndex;
            }
            ushort stepValue = 1;
            if (txtStep.Text.Length > 0)
            {
                stepValue = ushort.Parse(txtStep.Text.ToString());
            }
            else
            {
                MessageBox.Show("Please type into the step(speed)value!", pMsgTitle);
                return;
            }

            # region <<**********PTZ Control Code**********>>
            switch (((Button)sender).Name)
            {
                case "btnZoomP"://Zoom in
                    NETClient.NETPTZControl(pLoginID, channelId, PTZ_CONTROL.PTZ_ZOOM_ADD_CONTROL, 0, stepValue, false);
                    NETClient.NETPTZControl(pLoginID, channelId, PTZ_CONTROL.PTZ_ZOOM_ADD_CONTROL, 0, stepValue, true);
                    break;
                case "btnZoomD"://Zoom out
                    NETClient.NETPTZControl(pLoginID, channelId, PTZ_CONTROL.PTZ_ZOOM_DEC_CONTROL, 0, stepValue, false);
                    NETClient.NETPTZControl(pLoginID, channelId, PTZ_CONTROL.PTZ_ZOOM_DEC_CONTROL, 0, stepValue, true);
                    break;
                case "btnFocusP"://Near Focus
                    NETClient.NETPTZControl(pLoginID, channelId, PTZ_CONTROL.PTZ_FOCUS_ADD_CONTROL, 0, stepValue, false);
                    NETClient.NETPTZControl(pLoginID, channelId, PTZ_CONTROL.PTZ_FOCUS_ADD_CONTROL, 0, stepValue, true);
                    break;
                case "btnFocusD"://Far Focus
                    NETClient.NETPTZControl(pLoginID, channelId, PTZ_CONTROL.PTZ_FOCUS_DEC_CONTROL, 0, stepValue, false);
                    NETClient.NETPTZControl(pLoginID, channelId, PTZ_CONTROL.PTZ_FOCUS_DEC_CONTROL, 0, stepValue, true);
                    break;
                case "btnIrisOpen"://IRIS Open
                    NETClient.NETPTZControl(pLoginID, channelId, PTZ_CONTROL.PTZ_APERTURE_ADD_CONTROL, 0, stepValue, false);
                    NETClient.NETPTZControl(pLoginID, channelId, PTZ_CONTROL.PTZ_APERTURE_ADD_CONTROL, 0, stepValue, true);
                    break;
                case "btnIrisClose"://IRIS Close
                    NETClient.NETPTZControl(pLoginID, channelId, PTZ_CONTROL.PTZ_APERTURE_DEC_CONTROL, 0, stepValue, false);
                    NETClient.NETPTZControl(pLoginID, channelId, PTZ_CONTROL.PTZ_APERTURE_DEC_CONTROL, 0, stepValue, true);
                    break;
            }
            #endregion 
        }

        /// <summary>
        /// Click File Playback Button
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btnPlayByRecordFile_Click(object sender, EventArgs e)
        {
            playBy = 0;
            frm_PlayBackByFileSet fpf = new frm_PlayBackByFileSet();
            fpf.gLoginID = pLoginID;
            fpf.cmbChannelSelect.Items.Clear();
            for (int i = 0; i < deviceInfo.byChanNum; i++)
            {
                fpf.cmbChannelSelect.Items.Add(i.ToString());
            }
             fpf.ShowDialog(this);
            if (fpf.blnOKEnter == true)
            {
                pPlayBackChannelID = int.Parse(fpf.txtChannelID.Text.ToString());
                fileInfo = fpf.gFileInfo;
                //**********Playback according to the file**********
                pPlayBackHandle[pPlayBackChannelID] = NETClient.NETPlayBackByRecordFile(pLoginID, ref fileInfo, picRealPlay.Handle, null, IntPtr.Zero);
                //******************************
                if (pPlayBackHandle[pPlayBackChannelID] == 0)
                {
                    MessageBox.Show("Playback according to the time failed!", pMsgTitle);
                }
                else
                {
                    NETClient.NetSetSecurityKey(pPlayBackHandle[pPlayBackChannelID], "SPL17THALES00000");// Set Aes Security Key
                    //**********Screen Control Button**********
                    btnPlay.Text = "||";
                    //Screen Button Availability Control
                    btnPlayBackByTime.Enabled = false;
                    gpbPlayBackControl.Enabled = true;
                    btnPlay.Enabled = true;
                    btnSlow.Enabled = true;
                    btnStop.Enabled = true;
                    btnFast.Enabled = true;
                    btnSetpPlayS.Enabled = true;
                    btnBackward.Enabled = false;
                    hsbPlayBack.Enabled = true;
                    btnPlayByRecordFile.Enabled = false;
                    PlaybackBeginTime = fileInfo.starttime.ToDateTime();
                    PlaybackEndTime = fileInfo.endtime.ToDateTime();
                    //*********************************
                }
            }
        }

        /// <summary>
        ///  Device Disconnection Handling
        /// </summary>
        /// <param name="lLoginID"></param>
        /// <param name="pchDVRIP"></param>
        /// <param name="nDVRPort"></param>
        /// <param name="dwUser"></param>
        private void DisConnectEvent(int lLoginID, StringBuilder pchDVRIP, int nDVRPort, IntPtr dwUser)
        {
            //Device Disconnection Handling          
            MessageBox.Show("Device User Disconnect", pMsgTitle);
        }
        /// <summary>
        /// Capture Handling Code
        /// </summary>
        /// <param name="hPlayHandle">Play Handle</param>
        /// <param name="bmpPath">Path to Save Image</param>
        private void CapturePicture(int hPlayHandle,string bmpPath)
        {
            if (NETClient.NETCapturePicture(hPlayHandle, bmpPath))
            {
                //Capture Success Handling
                MessageBox.Show("Capture Successed!", pMsgTitle);
            }
            else
            {
                //Capture Failed Handling
                MessageBox.Show("Capture Failed!", pMsgTitle);
            }
        }
        /// <summary>
        /// Click Capture Button
        /// </summary>
        /// <param name="hPlayHandle"></param>
        private void CapturePicture(int hPlayHandle)
        {
            string bmpPath = Application.StartupPath +  @"\DH_" + DateTime.Now.ToString("yyyyMMddHHmmss") + ".bmp";
            //Capture Handling
            CapturePicture(hPlayHandle, bmpPath);
        }
        #endregion

        #region << Frame Control　Nothing with function >>

        private void txtStep_KeyPress(object sender, KeyPressEventArgs e)
        {

            //Step/Speed,Range 1~8, 8 Control effect is most obvious.  btnPTZControl_Click event use this value.
            if ((e.KeyChar >= '1' && e.KeyChar <= '8'))
            {
                txtStep.Text = e.KeyChar.ToString();
                e.Handled = true;
            }
            else
            {
                e.Handled = true;
            }
        }

        private void txtStep_KeyDown(object sender, KeyEventArgs e)
        {
            //Step(Speed)Value Type in Control,nothing with traffic.
            ushort i = 0;
            if (txtStep.Text.Length > 0)
            {

                i = ushort.Parse(txtStep.Text.ToString());
                if (e.KeyCode == Keys.Up)
                {
                    if (i < 8)
                    {
                        i += 1;
                        txtStep.Text = i.ToString();
                    }
                    e.Handled = true;

                }
                if (e.KeyCode == Keys.Down)
                {

                    if (i > 1)
                    {
                        i -= 1;
                        txtStep.Text = i.ToString();
                    }
                    e.Handled = true;
                }
                if (e.KeyCode == Keys.Back)
                {
                    txtStep.Text = "1";
                    e.Handled = true;
                }
            }
            else
            {
                txtStep.Text = "1";
            }
        }

        private bool checkSelectAbleChang()
        {
            if (
                pLoginID != 0 &&                                //login success
                btnPlayByRecordFile.Enabled == true &&          //not in playback by file
                btnPlayBackByTime.Enabled == true &&            //not in playback by time
                btnMultiPlay.Text.Equals(strMultiPlayStart)     //not in multiplay 
                )
            {
                return true;
            }
            else
            {
                return false;
            }
        }

        /// <summary>
        /// Click Image Contol Button
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void picRealPlay_Click(object sender, EventArgs e)
        {
            if (checkSelectAbleChang())
            {
                if (oldPicRealPlay != null)
                {
                    oldPicRealPlay.BackColor = SystemColors.Control;
                }

                picRealPlay = (PictureBox)sender;
                picRealPlay.BackColor = SystemColors.MenuHighlight;
                oldPicRealPlay = picRealPlay;
            }
        }

        #endregion
        /// <summary>
        /// Click Capture Button Handling
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btnCapturePicture2_Click(object sender, EventArgs e)
        {
            CapturePicture(pPlayBackHandle[pPlayBackChannelID]);
        }
        /// <summary>
        /// Click Capture Button Handling
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btnCapturePicture_Click(object sender, EventArgs e)
        {
            int channelId = 0;
            if (cmbChannelSelect.SelectedIndex == -1)
            {
                MessageBox.Show("Please select the channel!", pMsgTitle);
                return;
            }
            else
            {
                channelId = cmbChannelSelect.SelectedIndex;
            }
            CapturePicture(pRealPlayHandle[channelId]);
        }

        /// <summary>
        /// PTZ Extension Control
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btnPTZControl_Click_1(object sender, EventArgs e)
        {
            frm_PTZControl fPTZ = new frm_PTZControl();
            fPTZ.LoginID = pLoginID;
            fPTZ.ShowDialog();
        }

        /// <summary>
        /// Multi-device Demo
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btnMultiDrv_Click(object sender, EventArgs e)
        {
            frmMultiDVRSample fmds = new frmMultiDVRSample();
            fmds.ShowDialog();
        }
   
        private void startMultiPlay()
        {
            frm_MultiPlay fMutltiPlay = new frm_MultiPlay();
            fMutltiPlay.cmbChannel.Items.Clear();
            for (int i = 0; i < deviceInfo.byChanNum ; i++)
            {
                fMutltiPlay.cmbChannel.Items.Add(i.ToString());
            }
            fMutltiPlay.cmbChannel.SelectedIndex = 0;
            fMutltiPlay.cmbSplitType.SelectedIndex = 0;
            fMutltiPlay.ShowDialog(this);
            if (fMutltiPlay.bOKEnter == true)
            {
                int nStartChannel = fMutltiPlay.cmbChannel.SelectedIndex;
                REALPLAY_TYPE emSplitType = fMutltiPlay.emSplitType;
                if (emSplitType != REALPLAY_TYPE.NET_RType_Multiplay)
                {
                    pMultiPlayHandle = NETClient.NETRealPlayEx(pLoginID, nStartChannel, emSplitType, picRealPlay .Handle);
                }
                else
                {
                    //Show ALL Channel
                    pMultiPlayHandle = NETClient.NETRealPlayEx(pLoginID, 0, emSplitType, picRealPlay .Handle);
                }

                if (0 == pMultiPlayHandle)
                {
                    MessageBox.Show("MultiPlay Failed", pMsgTitle);
                    return;
                }
                btnMultiPlay.Text = strMultiPlayStop;
            }
        }

        private void StopMultiPlay()
        {
            btnMultiPlay.Text = strMultiPlayStart;
            if (pMultiPlayHandle != 0)
            {
                NETClient.NETStopRealPlay(pMultiPlayHandle);
                picRealPlay .Refresh();
            }
        }

        private void btnMultiPlay_Click(object sender, EventArgs e)
        {
            if (btnMultiPlay.Text.Equals(strMultiPlayStart))
            {
                startMultiPlay();
            }
            else
            {
                StopMultiPlay();
            }
        }

        private void btnBackward_Click(object sender, EventArgs e)
        {
            try
            {
                //Get last play time of picture
                DateTime tmOsdTime = new DateTime();
                DateTime tmStartTime = new DateTime();
                DateTime tmEndTime = new DateTime();
                bool bResult = NETClient.NETGetPlayBackOsdTime(pPlayBackHandle[pPlayBackChannelID], ref tmOsdTime, ref tmStartTime, ref tmEndTime);
                if (!bResult)
                {
                    MessageBox.Show(NETClient.LastOperationInfo.ToString(pErrInfoFormatStyle), pMsgTitle);
                    return;
                }
                NETClient.NETPlayBackControl(pPlayBackHandle[pPlayBackChannelID], PLAY_CONTROL.Stop);
                switch (btnBackward.Text.ToString())
                {
                    case "Backward":
                        pPlayBackHandle[pPlayBackChannelID] = NETClient.NETPlayBackByTimeEx2(pLoginID, pPlayBackChannelID, PlaybackBeginTime, tmOsdTime, picRealPlay.Handle, null, IntPtr.Zero, null, IntPtr.Zero, 1, 10000);
                        if (0 == pPlayBackHandle[pPlayBackChannelID])//Backward
                        {
                            MessageBox.Show("Playback According to The Time Failed!", pMsgTitle);
                        }
                        else
                        {
                            NETClient.NetSetSecurityKey(pPlayBackHandle[pPlayBackChannelID], "SPL17THALES00000");// Set Aes Security Key
                            btnBackward.Text = "Forward";
                        }
                        break;
                    case "Forward":
                        pPlayBackHandle[pPlayBackChannelID] = NETClient.NETPlayBackByTimeEx2(pLoginID, pPlayBackChannelID, tmOsdTime, PlaybackEndTime, picRealPlay.Handle, null, IntPtr.Zero, null, IntPtr.Zero, 0, 10000);
                        if (0 == pPlayBackHandle[pPlayBackChannelID])//Backward
                        {
                            MessageBox.Show("Playback According to The Time Failed!", pMsgTitle);
                        }
                        else
                        {
                            NETClient.NetSetSecurityKey(pPlayBackHandle[pPlayBackChannelID], "SPL17THALES00000");// Set Aes Security Key
                            btnBackward.Text = "Backward";
                        }
                        break;
                }
            }
            catch
            {
                MessageBox.Show(NETClient.LastOperationInfo.ToString(pErrInfoFormatStyle), pMsgTitle);
            }
        }

        private void InitPlayBoxManger()
        {
            lstAllRealPlay = new List<PictureBox>();
            lstAllRealPlay.Add(picRealPlay0);
            lstAllRealPlay.Add(picRealPlay1);
            lstAllRealPlay.Add(picRealPlay2);
            lstAllRealPlay.Add(picRealPlay3);
            lstAllRealPlay.Add(picRealPlay4);
            lstAllRealPlay.Add(picRealPlay5);
            lstAllRealPlay.Add(picRealPlay6);
            lstAllRealPlay.Add(picRealPlay7);
            lstAllRealPlay.Add(picRealPlay8);
            lstAllRealPlay.Add(picRealPlay9);
            lstAllRealPlay.Add(picRealPlay10);
            lstAllRealPlay.Add(picRealPlay11);
            lstAllRealPlay.Add(picRealPlay12);
            lstAllRealPlay.Add(picRealPlay13);
            lstAllRealPlay.Add(picRealPlay14);
            lstAllRealPlay.Add(picRealPlay15);

        }

        private void RefreshAllPlayBox()
        {
            foreach (PictureBox picBox in lstAllRealPlay)
            {
                picBox.Refresh();
            }
        }

        private int RealPlayInBox(int index)
        {
            if (index >= 0 && index < lstAllRealPlay.Count)
            {
                return NETClient.NETRealPlay(pLoginID, index, lstAllRealPlay[index].Handle);
            }
            else
            {
                return 0;
            }

        }

        private void picRealPlay_DoubleClick(object sender, EventArgs e)
        {
            PictureBox picCur = (PictureBox)sender;
            if (bFullModel == false)
            {
                bFullModel = true;
                foreach (PictureBox picBox in lstAllRealPlay)
                {
                    if (picCur != picBox)
                    {
                        picBox.Visible = false;
                    }
                    else
                    {
                        stuOriRect.Location = picBox.Location;
                        stuOriRect.Width = picBox.Width;
                        stuOriRect.Height = picBox.Height;
                        picBox.SetBounds(groupBox1.Location.X, groupBox1.Location.Y, groupBox1.Width - 20, groupBox1.Height - 20);
                    }
                }
            }
            else
            {
                bFullModel = false;
                foreach (PictureBox picBox in lstAllRealPlay)
                {
                    if (picCur != picBox)
                    {
                        picBox.Visible = true;
                    }
                    else
                    {
                        picBox.SetBounds(stuOriRect.Location.X, stuOriRect.Location.Y, stuOriRect.Width, stuOriRect.Height);
                    }
                }
            }

        }
    }
}