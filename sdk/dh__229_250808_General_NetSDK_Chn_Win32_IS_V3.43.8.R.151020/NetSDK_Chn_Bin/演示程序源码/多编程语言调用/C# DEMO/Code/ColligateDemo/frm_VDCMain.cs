using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using NetSDK;
using VDCSDK;

namespace ColligateDemo
{
    public partial class frm_VDCDemo : Form
    {

        private NET_DEVICEINFO deviceInfo;
        /// <summary>
        /// Channel no.
        /// </summary>
        private int ChannelCount=0;

        /// <summary>
        /// Device user login id
        /// </summary>
        private int pLoginID;

        /// <summary>
        /// Program Title
        /// </summary>
        private const string pMsgTitle = "Decode card SDK Demo";

        /// <summary>
        /// Last operation info format
        /// </summary>
        private const string pErrInfoFormatStyle = "Code :errcode;\nDescription  :errmSG.";

        /// <summary>
        /// Real-time monitor handle
        /// </summary>
        private int uRealHandle;
        /// <summary>
        /// Initialize device status value
        /// </summary>
        private bool blnInitDevDevice = false;
        /// <summary>
        /// Initialization DirectDraw
        /// </summary>
        private bool blnInitDraw = false;
        /// <summary>
        /// Play channel handle
        /// </summary>
        private UInt32 hChannel = 0;

        private fDisConnect disConnect;

        private fRealDataCallBack cbRealData;

        public frm_VDCDemo()
        {
            InitializeComponent();
        }

        private void frm_VDCMain_Load(object sender, EventArgs e)
        {

            //Initialization network SDK
            //disConnect = new fDisConnect(DisConnectEvent);
            //if (VDCClient.VDCInit(disConnect, IntPtr.Zero)==true)
            //{

            //}
            //else
            //{
            //    MessageBox.Show("Network SDK initialization failed!", pMsgTitle);
            //    return;
            //}


            #region << Image process >>
            //Start button
            btnStartPlay.Enabled = false;
            //Pause button
            btnPause.Enabled = false;
            btnPause.Tag = "1";
            btnPause.Text = "Pause play";
            //Stop button
            btnStop.Enabled = false;
            #endregion

            #region << Initialize decode card device >>
            if (VDC.VDCInitDecDevice(ref ChannelCount) == 0)
            {
                //MessageBox.Show("Initialize decoder card successfully!", "Prompt");
                blnInitDevDevice = true;
            }
            else
            {
                //MessageBox.Show("Failed to initialize decoder card!", "Prompt");
                blnInitDevDevice = false;
                return;
            }
            #endregion

            #region << Initialization DirectDraw >>
            if(VDC.VDCInitDirectDraw(picMain.Handle,(uint)Color.Blue.ToArgb())==0)
            {
                //MessageBox.Show("Initialization DirectDraw successfully!", "Prompt");
                blnInitDraw = true;
            }
            else
            {
                //MessageBox.Show("Initialization DirectDraw failed!", "Prompt");
                blnInitDraw = false;
                return;
            }
            #endregion
        }

        private void frm_VDCMain_FormClosing(object sender, FormClosingEventArgs e)
        {
            # region << Release DirectDraw >>
            if (blnInitDraw == true)
            {
                if (VDC.VDCReleaseDirectDraw() == 0)
                {
                    //MessageBox.Show("Release DirectDraw successfully!", pMsgTitle);
                }
                else
                {
                    //MessageBox.Show("Failed to release DirectDraw!", pMsgTitle);
                    return;
                }
            }
            #endregion
            #region << Device off >>
            if (blnInitDevDevice == true)
            {
                if (VDC.VDCReleaseDecDevice() == 0)
                {
                    //MessageBox.Show("Successfully turn off decoder card!", pMsgTitle);
                }
                else
                {
                    //MessageBox.Show("Turn off decoder card failed!", pMsgTitle);
                    return;
                }
            }
            #endregion
        }

        private void btnStartPlay_Click(object sender, EventArgs e)
        {
            //Open channel
            if (VDC.VDCChannelOpen(0, ref hChannel) == 0)
            {
                MessageBox.Show("Open channel successfully!", pMsgTitle);
            }
            else
            {
                MessageBox.Show("Failed to open channel!", pMsgTitle);
                return;
            }
            //Open stream method
            if(VDC.VDCOpenStream(hChannel,IntPtr.Zero,(uint)921600/*900*1024*/)==0)
            {
                MessageBox.Show("Open stream play successfully!", pMsgTitle);
            }
            else
            {
                MessageBox.Show("Failed to open stream play!", pMsgTitle);
                return;
            }
            //Get data via network SDK
            cbRealData = new fRealDataCallBack(cbRealDataFun);
            uRealHandle = NETClient.NETRealPlay(pLoginID, 0, IntPtr.Zero);//Get date no play
            VDC.VDCPlay(hChannel, picMain.Handle);
            if (NETClient.NETSetRealDataCallBack(uRealHandle, cbRealData, IntPtr.Zero)==true)//Set data call process function
            {
                // MessageBox.Show("Set data call function successfully!", pMsgTitle);
            }
            else
            {
                MessageBox.Show("Failed to set data call process function!", pMsgTitle);
                return;
            }
            btnPause.Enabled = true;
            btnStop.Enabled = true;
        }

        private void btnPause_Click(object sender, EventArgs e)
        {
            switch (int.Parse(btnPause.Tag.ToString()))
            { 
                case 0://Continue to play
                    btnPause.Tag = "1";
                    btnPause.Text = "Pause";
                    if (VDC.VDCPause(hChannel, false)==0)
                    {
                        MessageBox.Show("Continue to play successfully!", pMsgTitle);
                    }
                    break;
                case 1://Pause
                    btnPause.Tag = "0";
                    btnPause.Text = "Continue to play";
                    if (VDC.VDCPause(hChannel,true)==0)
                    {
                        MessageBox.Show("Pause successfully!", pMsgTitle);
                    }
                    break;
            }
        }

        private void btnAddDev_Click(object sender, EventArgs e)
        {
            frm_AddDevice fAddDev = new frm_AddDevice();
            fAddDev.ShowDialog();
            //NETClient.NETSetShowException(true);
            try
            {
                if (fAddDev.blnOKEnter == true)
                {
                    //Device user info get
                    deviceInfo = new NET_DEVICEINFO();
                    int error = 0;
                    //Device user login
                    pLoginID = NETClient.NETLogin(fAddDev.cmbDevIP.Text.ToString(), ushort.Parse(fAddDev.txtDevProt.Text.ToString()), fAddDev.txtName.Text.ToString(), fAddDev.txtPassword.Text.ToString(), out deviceInfo, out error);
                    if (pLoginID != 0)
                    {                        
                        //btnStartRealPlay.Enabled = true;
                        btnStartPlay.Enabled = true;
                    }
                    else
                    {
                        //btnStartRealPlay.Enabled = false;
                        btnStartPlay.Enabled = false;
                        MessageBox.Show(NETClient.LastOperationInfo.ToString(pErrInfoFormatStyle), pMsgTitle);
                    }
                }
            }
            catch
            {
                //Report last operation error
                MessageBox.Show(NETClient.LastOperationInfo.ToString(pErrInfoFormatStyle), pMsgTitle);
            }
        }

        /// <summary>
        /// Real-time monitoring data call process
        /// </summary>
        /// <param name="lRealHandle"></param>
        /// <param name="dwDataType"></param>
        /// <param name="pBuffer"></param>
        /// <param name="dwBufSize"></param>
        /// <param name="dwUser"></param>
        private void cbRealDataFun(int lRealHandle, UInt32 dwDataType, IntPtr pBuffer, UInt32 dwBufSize, IntPtr dwUser)
        {
            VDC.VDCInputData(hChannel, pBuffer, dwBufSize);
        }

        private void DisConnectEvent(int lLoginID, StringBuilder pchDVRIP, int nDVRPort, IntPtr dwUser)
        {
            MessageBox.Show("Device offline!", pMsgTitle);
        }

        private void btnStop_Click(object sender, EventArgs e)
        {

        }
    }
}