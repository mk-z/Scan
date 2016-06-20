using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using NetSDK;
using PlaySDK;

namespace NetSDKSample
{

    public partial class frmMultiDVRSample : Form
    {
        /// <summary>
        /// Login handle 1
        /// </summary>
        private int pLoginID1;
        /// <summary>
        /// Login handle 2
        /// </summary>
        private int pLoginID2;
        /// <summary>
        /// Device info
        /// </summary>
        private NET_DEVICEINFO deviceInfo;
        /// <summary>
        /// Callback Disconnect 
        /// </summary>
        private fDisConnect disConnect;
        /// <summary>
        /// Real-time play handle 1
        /// </summary>
        private int realPlayHandle1 = 0;
        /// <summary>
        /// Real-time play handle 2
        /// </summary>
        private int realPlayHandle2 = 0;


        public frmMultiDVRSample()
        {            
            InitializeComponent();
        }

        /// <summary>
        /// Device disconnect handling
        /// </summary>
        /// <param name="lLoginID">Login ID</param>
        /// <param name="pchDVRIP">DVR device IP</param>
        /// <param name="nDVRPort">Port</param>
        /// <param name="dwUser">User data</param>
        private void DisConnectEvent(int lLoginID, StringBuilder pchDVRIP, int nDVRPort, IntPtr dwUser)
        {
            //Device disconnect handling          
            MessageBox.Show("Device user is disconnected", "Warning");
        }
        /// <summary>
        /// Add device 1 handling
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btnAddDevice1_Click(object sender, EventArgs e)
        {
            frm_AddDevice fAddDev = new frm_AddDevice();
            fAddDev.ShowDialog();
            try
            {
                if (fAddDev.blnOKEnter == true)
                {
                    //Get device user info.
                    deviceInfo = new NET_DEVICEINFO();
                    int error = 0;
                    //Device 1 login:Pay attention to the login ID.
                    pLoginID1 = NETClient.NETLogin(fAddDev.cmbDevIP.Text.ToString(), ushort.Parse(fAddDev.txtDevProt.Text.ToString()), fAddDev.txtName.Text.ToString(), fAddDev.txtPassword.Text.ToString(), out deviceInfo, out error);
                    //Judge if it login success.
                    if (pLoginID1 != 0)
                    {
                        MessageBox.Show("Device1 login successed!", "Warning");
                    }
                    else
                    {
                        MessageBox.Show("Device1 login failed!", "Warning");
                    }
                }
            }
            catch
            {

            }
        }

        /// <summary>
        /// Add device1 handling
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btnAddDevice2_Click(object sender, EventArgs e)
        {

            frm_AddDevice fAddDev = new frm_AddDevice();
            fAddDev.ShowDialog();
            try
            {
                if (fAddDev.blnOKEnter == true)
                {
                    //Get device user info.
                    deviceInfo = new NET_DEVICEINFO();
                    int error = 0;
                    //Device2 login:Pay attention to the login ID.
                    pLoginID2 = NETClient.NETLogin(fAddDev.cmbDevIP.Text.ToString(), ushort.Parse(fAddDev.txtDevProt.Text.ToString()), fAddDev.txtName.Text.ToString(), fAddDev.txtPassword.Text.ToString(), out deviceInfo, out error);
                   //Judge if it login success.
                    if (pLoginID2 != 0)
                    {
                        MessageBox.Show("Device2 login successed!", "Warning");
                    }
                    else
                    {
                        MessageBox.Show("Device2 login failed!", "Warning");
                    }
                }
            }
            catch
            {

            }
        }
        /// <summary>
        /// Device1 real-time play handling
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btnRealPlay1_Click(object sender, EventArgs e)
        {
            //Start real-time monitoring:Pay attention to realPlayHandle1 & pLoginID1
            realPlayHandle1 = NETClient.NETRealPlay(pLoginID1, 0, picRealPlay1.Handle);
        }
        /// <summary>
        ///  Multi-device demo procedure loading
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void frmMultiDVRSample_Load(object sender, EventArgs e)
        {
            disConnect = new fDisConnect(DisConnectEvent);
            NETClient.NETInit(disConnect, IntPtr.Zero);
            NETClient.NETSetEncoding(LANGUAGE_ENCODING.gb2312);// Character encoding format setting, default is gb2312 encoding,please set if it is other encoding.

            Utility.StringUtil.InitControlText(this);
        }
        /// <summary>
        /// Device2 real-time monitoring handling
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btnRealPlay2_Click(object sender, EventArgs e)
        {
            //Start real-time monitoring: Pay attention to realPlayHandle2 & pLoginID1
            realPlayHandle2 = NETClient.NETRealPlay(pLoginID2, 1, picRealPlay2.Handle);
        }
        /// <summary>
        /// Stop Device1 real-time monitoring handling.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btnStopReal1_Click(object sender, EventArgs e)
        {
            //Stop monitoring：Pay attention to realPlayHandle1
            NETClient.NETStopRealPlay(realPlayHandle1);
            picRealPlay1.Refresh();
        }
        /// <summary>
        /// Stop Device2 real-time monitoring handling.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btnStopReal2_Click(object sender, EventArgs e)
        {
            //Stop monitoring：Pay attention to realPlayHandle2
            NETClient.NETStopRealPlay(realPlayHandle2);            
            picRealPlay2.Refresh();

        }

        private void picRealPlay1_Click(object sender, EventArgs e)
        {

        }

    }
}