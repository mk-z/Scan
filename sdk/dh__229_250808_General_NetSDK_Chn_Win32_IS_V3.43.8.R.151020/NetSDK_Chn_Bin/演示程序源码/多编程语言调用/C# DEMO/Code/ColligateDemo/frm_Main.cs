using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using PlaySDK;
using NetSDK;

namespace ColligateDemo
{
    public partial class frm_Main : Form
    {
        private NET_DEVICEINFO deviceInfo;

        /// <summary>
        /// Device user login ID
        /// </summary>
        private int pLoginID;

        /// <summary>
        /// Program Info prompt Title
        /// </summary>
        private const string pMsgTitle = "Network SDK Demo";

        /// <summary>
        /// Late operation info display format
        /// </summary>
        private const string pErrInfoFormatStyle = "Code :errcode;\nDescription :errmSG.";

        /// <summary>
        /// Real-monitor handle
        /// </summary>
        private int uRealHandle;

        /// <summary>
        /// Real-time data call
        /// </summary>
        private fRealDataCallBack cbRealData;

        /// <summary>
        /// Disconnect call
        /// </summary>
        private fDisConnect disConnect;

        /// <summary>
        /// Set real-time data call or not
        /// </summary>
        private bool blnSetRealDataCallBack = false;

        //private int aa = 0;
        public frm_Main()
        {
            InitializeComponent();
        }

        private void btnLogin_Click(object sender, EventArgs e)
        {
            frm_AddDevice fAddDev = new frm_AddDevice();
            fAddDev.ShowDialog();
            //NETClient.NETSetShowException(true);
            try
            {
                if (fAddDev.blnOKEnter == true)
                {
                    //Device username info get
                    deviceInfo = new NET_DEVICEINFO();
                    int error = 0;
                    //Device user login
                    pLoginID = NETClient.NETLogin(fAddDev.cmbDevIP.Text.ToString(), ushort.Parse(fAddDev.txtDevProt.Text.ToString()), fAddDev.txtName.Text.ToString(), fAddDev.txtPassword.Text.ToString(), out deviceInfo, out error);
                    if (pLoginID != 0)
                    {

                        btnStartRealPlay.Enabled = true;
                        btnLogin.Enabled = false;
                        btnLogout.Enabled = true;
                    }
                    else
                    {
                        btnStartRealPlay.Enabled = false;
                        btnLogin.Enabled = true;
                        btnLogout.Enabled = false;
                        MessageBox.Show(NETClient.LastOperationInfo.ToString(pErrInfoFormatStyle), pMsgTitle);
                    }
                }
            }
            catch
            {
                //Error in last operation
                MessageBox.Show(NETClient.LastOperationInfo.ToString(pErrInfoFormatStyle), pMsgTitle);
            }
        }

        /// <summary>
        /// Real-time monitor data call process
        /// </summary>
        /// <param name="lRealHandle"></param>
        /// <param name="dwDataType"></param>
        /// <param name="pBuffer"></param>
        /// <param name="dwBufSize"></param>
        /// <param name="dwUser"></param>
        private void cbRealDataFun(int lRealHandle, UInt32 dwDataType, IntPtr pBuffer, UInt32 dwBufSize, IntPtr dwUser)
        {
            NETPlay.NETPlayControl(PLAY_COMMAND.InputData, 0,pBuffer,dwBufSize);//Here second parameter nPort parameter corresponds to network monitor data RealHandle
        }

        private void frm_Main_Load(object sender, EventArgs e)
        {
            disConnect = new fDisConnect(DisConnectEvent);
            bool blnInit=  NETClient.NETInit(disConnect, IntPtr.Zero);
            //MessageBox.Show((blnInit == true ? "successfully" : "failed"), pMsgTitle);
        }
        private void DisConnectEvent(int lLoginID, StringBuilder pchDVRIP, int nDVRPort, IntPtr dwUser)
        {
            MessageBox.Show("Device offline!", pMsgTitle);
        }

        private void btnStopRealPlay_Click(object sender, EventArgs e)
        {
            NETPlay.NETPlayControl(PLAY_COMMAND.Stop, 0);
            NETPlay.NETPlayControl(PLAY_COMMAND.CloseStream, 0);
            btnStartRealPlay.Enabled = true;
            btnStopRealPlay.Enabled = false;
            picPlayMain.Refresh();
        }

        private void btnStartRealPlay_Click(object sender, EventArgs e)
        {
            if (pLoginID != 0)
            {

                uRealHandle = NETClient.NETRealPlay(pLoginID, 0, IntPtr.Zero);//Only data, no play
                cbRealData = new fRealDataCallBack(cbRealDataFun);
                if (NETPlay.NETPlayControl(PLAY_COMMAND.OpenStream, 0, IntPtr.Zero, 0, (UInt32)(900 * 1024)))
                {
                    // MessageBox.Show("Open stream play successfully!", pMsgTitle);
                }
                else
                {
                    MessageBox.Show("Failed to open stream play!", pMsgTitle);
                    btnStopRealPlay.Enabled = false;
                    return;
                }

                if (NETPlay.NETSetStreamOpenMode(0, PLAY_MODE.STREAME_REALTIME))//Set stream play mode
                {
                    //MessageBox.Show("Set stream play mode successfullly!", pMsgTitle);
                }
                else
                {
                    MessageBox.Show("Failed to set stream mode!", pMsgTitle); 
                    btnStopRealPlay.Enabled = false;
                    return;
                }
                if (NETPlay.NETPlayControl(PLAY_COMMAND.Start, 0, picPlayMain.Handle))
                {
                    // MessageBox.Show("Stream play start successfully!", pMsgTitle);
                }
                else
                {
                    MessageBox.Show("Failed to stream play!", pMsgTitle);
                    btnStopRealPlay.Enabled = false;
                    return;
                }
                if (blnSetRealDataCallBack == true)
                {
                    btnStopRealPlay.Enabled = true;
                    btnStartRealPlay.Enabled = false;
                    return;
                }
                if (NETClient.NETSetRealDataCallBack(uRealHandle, cbRealData, IntPtr.Zero))//Set data call process function
                {
                    // MessageBox.Show("Set data call process function successfully!", pMsgTitle);
                    blnSetRealDataCallBack = true;
                }
                else
                {
                    MessageBox.Show("Failed to set data call process function!", pMsgTitle);
                    btnStopRealPlay.Enabled = false;
                    blnSetRealDataCallBack = false;
                    return;
                }
                btnStopRealPlay.Enabled = true;
                btnStartRealPlay.Enabled = false;
                //picPlayMain.Refresh();
            }            
        }

        private void btnVDC_Click(object sender, EventArgs e)
        {
            frm_VDCDemo fVDC = new frm_VDCDemo();
            fVDC.ShowDialog();
        }

        private void btnLogout_Click(object sender, EventArgs e)
        {
            blnSetRealDataCallBack = false;
            btnStartRealPlay.Enabled = false;
            btnStopRealPlay.Enabled = false;
            btnLogout.Enabled = false;
            btnLogin.Enabled = true;
            NETClient.NETLogout(pLoginID);
        }
    }
}
