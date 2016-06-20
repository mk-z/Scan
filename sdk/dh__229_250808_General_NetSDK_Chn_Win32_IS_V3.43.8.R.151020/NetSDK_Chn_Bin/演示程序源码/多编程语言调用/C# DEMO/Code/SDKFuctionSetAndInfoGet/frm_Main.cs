using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using NetSDK;                 // Network SDK
using NetSDKSample;        // universal screen routines
using Utility;
using System.Runtime.InteropServices;
using System.Diagnostics;

namespace SDKFuctionSetAndInfoGet
{
    public partial class frm_Main : Form
    {
        /// <summary>
        /// Device user login handle
        /// </summary>
        private int pLoginID;

        /// <summary>
        /// Program news tips Title
        /// </summary>
        private const string pMsgTitle = "Network SDK Demo Program";

        /// <summary>
        /// Final operation information display format
        /// </summary>
        private const string pErrInfoFormatStyle = "Code:errcode;\n Description:errmSG.";

        /// <summary>
        /// Device configuration
        /// </summary>
        private NETDEV_SYSTEM_ATTR_CFG sysAttrConfig;

        /// <summary>
        /// All image channels properties
        /// </summary>
        private NETDEV_CHANNEL_CFG[] channelConfig;

        /// <summary>
        /// Network configuration properties
        /// </summary>
        NETDEV_NET_CFG netConfig;

        /// <summary>
        /// Timer recording configuration information
        /// </summary>
        NETDEV_RECORD_CFG[] recConfig;

        /// <summary>
        /// Serial port configuration
        /// </summary>
        NETDEV_COMM_CFG commConfig;

        /// <summary>
        /// Alarm set up
        /// </summary>
        NETDEV_ALARM_SCHEDULE alarmAllConfig;

        /// <summary>
        /// Interrupt callback
        /// </summary>
        private fDisConnect disConnect;

        /// <summary>
        /// Update handle
        /// </summary>
        private Int32 hUpgradeId;

        /// <summary>
        /// Update callback
        /// </summary>
        private fUpgradeCallBack upgradeCallBack;


        /// <summary>
        /// Update progress
        /// </summary>
        public delegate void UpdatePosDelegate(int pos);
        private UpdatePosDelegate updatePosDelegate;
        private void UpdatePos(int npos)
        {
            if (-1 == npos)
            {
                hUpgradeId = 0;
                progressBarUpdate.Value = 0;
                labelUpgradeMsg.Text = "Progress Updating";
                MessageBox.Show("Update Complete");
            }
            else if (-2 == npos)
            {
                MessageBox.Show("Update Data Sent Fail!");
                if (hUpgradeId != 0)
                {
                    if (!NETClient.NETCLIENT_StopUpgrade(hUpgradeId))
                    {
                        MessageBox.Show("End Upgrading Fail");
                    }
                    hUpgradeId = 0;
                    progressBarUpdate.Value = 0;
                    labelUpgradeMsg.Text = "Update Progress";
                }
            }
            else
            {
                progressBarUpdate.Value = npos;
                if (npos >= 100)
                {
                    labelUpgradeMsg.Text = "Files have been transferred, please wait..";
                }
            }
        }


        public frm_Main()
        {
            InitializeComponent();
        }
        /// <summary>
        /// Getting version number of button and pressing to process
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btnSDKVersion_Click(object sender, EventArgs e)
        {
            ////Standard SDK version format:00.00.00.00
            //labSDKVersion.Text = DHClient.DHGetSDKVersion();
            //Numeric SDK version number format:0.0.0.0
            labSDKVersion.Text = NETClient.NETGetSDKVersion("D3");
            //labSDKVersion.Text = NETClient.NETGetSDKVersion();//Equivalent to:DHClient.DHGetSDKVersion("S3");
        }
        /// <summary>
        /// Screen load handling
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void frm_Main_Load(object sender, EventArgs e)
        {
            disConnect = new fDisConnect(DisConnectEvent);
            NETClient.NETInit(disConnect, IntPtr.Zero);//SDK Initialization
            NETClient.NETSetEncoding(LANGUAGE_ENCODING.gb2312);//Character encoding format set,the default is gb2312 character encoding, please set to other character encoding if needed
            grbMain.Enabled = false;

            hUpgradeId = 0;
            upgradeCallBack = new fUpgradeCallBack(UpgradeCallBack);

            this.updatePosDelegate = this.UpdatePos;

            StringUtil.InitControlText(this);
        }
        /// <summary>
        /// User login button pressed
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btnUserLogin_Click(object sender, EventArgs e)
        {
            string strLogin = StringUtil.ConvertString("Device User Login");
            string strLogout = StringUtil.ConvertString("Device User Logout");

            if (btnUserLogin.Text.Equals(strLogin))
            {
                frm_AddDevice fadFrom = new frm_AddDevice();
                fadFrom.ShowDialog();
                if (fadFrom.blnOKEnter == true)
                {
                    //Device user information acquired
                    NET_DEVICEINFO deviceInfo = new NET_DEVICEINFO();
                    int error = 0;
                    pLoginID = NETClient.NETLogin(fadFrom.cmbDevIP.Text.ToString(), ushort.Parse(fadFrom.txtDevProt.Text.ToString()), fadFrom.txtName.Text.ToString(), fadFrom.txtPassword.Text.ToString(), out deviceInfo, out error);
                    if (pLoginID != 0)
                    {
                        btnUserLogin.BackColor = Color.Yellow;
                        btnUserLogin.Text = strLogout;
                        grbMain.Enabled = true;
                        tbcMain.SelectedIndex = 0;
                        GetDevAttrConfig();
                    }
                    else
                    {
                        //Report erro message for the last operation
                        MessageBox.Show(NETClient.LastOperationInfo.ToString(pErrInfoFormatStyle), pMsgTitle);
                        btnUserLogin_Click(null, null);
                    }
                }
            }
            else
            {
                bool result = NETClient.NETLogout(pLoginID);
                if (result == false)
                {
                    //Report erro message for the last operation
                    MessageBox.Show(NETClient.LastOperationInfo.ToString(pErrInfoFormatStyle), pMsgTitle);
                }

                //Screen initialization
                this.Controls.Clear();
                InitializeComponent();
                pLoginID = 0;
                sysAttrConfig = new NETDEV_SYSTEM_ATTR_CFG();
                channelConfig = new NETDEV_CHANNEL_CFG[16];
                netConfig = new NETDEV_NET_CFG();
                recConfig = new NETDEV_RECORD_CFG[16];
                commConfig = new NETDEV_COMM_CFG();
                alarmAllConfig = new NETDEV_ALARM_SCHEDULE();
                btnUserLogin.BackColor = Color.Transparent;
                btnUserLogin.Text = strLogin;
                grbMain.Enabled = false;
                tbcMain.SelectedIndex = 0;
            }
        }

        private bool GetDevAttrConfig()
        {
            bool returnValue = NETClient.NETGetDevConfig(pLoginID, ref sysAttrConfig);
            if (returnValue == true)
            {
                setDataToControl(sysAttrConfig);
            }
            else
            {
                //Report error message for the last operation
                MessageBox.Show(NETClient.LastOperationInfo.ToString(pErrInfoFormatStyle), pMsgTitle);
            }

            return returnValue;
        }
        /// <summary>
        /// Press read button to process
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btnReadConfig_Click(object sender, EventArgs e)
        {
            bool returnValue = false;
            switch (tbcMain.SelectedIndex)
            {
                case 0://Device property                    
                    returnValue = GetDevAttrConfig();

                    break;
                case 1://Channel property

                    # region << Obtain the channel property for the specified channel >>
                    //DHDEV_CHANNEL_CFG channelConfig = new DHDEV_CHANNEL_CFG();
                    //returnValue = DHClient.DHGetDevConfig(pLoginID, 0, ref channelConfig);
                    //if (returnValue == true)
                    //{
                    //    setDataToControl(channelConfig);
                    //}
                    //else
                    //{
                    //    //Report erro message for the last operation
                    //    MessageBox.Show(DHClient.LastOperationInfo.ToString(pErrInfoFormatStyle), pMsgTitle);
                    //}
                    #endregion

                    #region << Obtain the channel property for all channels  >>
                    if (sysAttrConfig.Equals(new NETDEV_SYSTEM_ATTR_CFG()) == false)
                    {
                        channelConfig = new NETDEV_CHANNEL_CFG[sysAttrConfig.byVideoCaptureNum];
                        #region << Processing channel number list>>
                        cmbChannelNum.Items.Clear();
                        for (int i = 0; i < sysAttrConfig.byVideoCaptureNum; i++)
                        {
                            cmbChannelNum.Items.Add(i.ToString());
                        }
                        #endregion
                        returnValue = NETClient.NETGetDevConfig(pLoginID, ref channelConfig);
                        if (returnValue == true)
                        {
                            //setDataToControl(channelConfig[0]);//Display channel 0 information
                            cmbChannelNum.SelectedIndex = 0;//Display channel 0 information
                        }
                        else
                        {
                            //Report error message for the last operation
                            MessageBox.Show(NETClient.LastOperationInfo.ToString(pErrInfoFormatStyle), pMsgTitle);
                        }
                    }
                    #endregion

                    #region << Multi preview >>
                    //DHDEV_PREVIEW_CFG previewConfig = new DHDEV_PREVIEW_CFG();
                    //returnValue = DHClient.DHGetDevConfig(pLoginID, ref previewConfig);
                    //if(returnValue==true)
                    //{

                    //}
                    //else
                    //{
                    //    //Report erro message for the last operation
                    //    MessageBox.Show(DHClient.LastOperationInfo.ToString(pErrInfoFormatStyle), pMsgTitle);
                    //}
                    #endregion

                    break;
                case 2://Serial port property
                    //Obtaining serial port property
                    commConfig = new NETDEV_COMM_CFG();
                    returnValue = NETClient.NETGetDevConfig(pLoginID, ref commConfig);
                    if (returnValue == true)
                    {
                        cmbCOMFunction.Items.Clear();
                        foreach(NET_PROANDFUN_NAME pName in commConfig.s232FuncName)
                        {
                            cmbCOMFunction.Items.Add(NETClient.NETByteArrayToString(pName.ProName));
                        }
                        cmb458DecProName.Items.Clear();
                        foreach (NET_PROANDFUN_NAME pName in commConfig.DecProName)
                        {
                            cmb458DecProName.Items.Add(NETClient.NETByteArrayToString(pName.ProName));
                        }
                        cmbRS232.SelectedIndex = 0;
                        cmb485.SelectedIndex = 0;
                        //setDataToControl(commConfig.st232[0]);//Present 232 serial port property
                        //setDataToControl(commConfig.stDecoder[0]);//Present 485 serial port property
                    }
                    else
                    {
                        //Report error message for the last operation
                        MessageBox.Show(NETClient.LastOperationInfo.ToString(pErrInfoFormatStyle), pMsgTitle);
                    }

                    break;
                case 3://Recording configuration

                    #region << Obtaining special channel recording configuration >>
                    /*
                    NETDEV_RECORD_CFG recConfig = new NETDEV_RECORD_CFG();
                    returnValue = NETClient.NETGetDevConfig(pLoginID, 0, ref recConfig);
                    if (returnValue == true)
                    {
                        setDataToControl(recConfig);//Present recording configuration
                    }
                    else
                    {
                        //Report erro message for the last operation
                        MessageBox.Show(NETClient.LastOperationInfo.ToString(pErrInfoFormatStyle), pMsgTitle);
                    }
                    */
                    #endregion
                    
                    #region << Obtain recording configuration for all channels >>
                    if (sysAttrConfig.Equals(new NETDEV_SYSTEM_ATTR_CFG()) == false)
                    {
                        cmbRecChannel.Items.Clear();
                        for (int i = 0; i < sysAttrConfig.byVideoCaptureNum; i++)
                        {
                            cmbRecChannel.Items.Add(i.ToString());
                        }

                        recConfig = new NETDEV_RECORD_CFG[sysAttrConfig.byVideoCaptureNum];
                        returnValue = NETClient.NETGetDevConfig(pLoginID, ref recConfig);

                        if (returnValue == true)
                        {
                            cmbRecChannel.SelectedIndex = 0;
                        }
                        else
                        {
                            //Report erro message for the last operation
                            MessageBox.Show(NETClient.LastOperationInfo.ToString(pErrInfoFormatStyle), pMsgTitle);
                        }
                    }
                    #endregion

                    break;
                case 4://Network configuration

                    returnValue = NETClient.NETGetDevConfig(pLoginID, ref  netConfig);
                    if (returnValue == true)
                    {
                        setDataToControl(netConfig);
                    }
                    else
                    {
                        //Reporting error message for the last operation
                        MessageBox.Show(NETClient.LastOperationInfo.ToString(pErrInfoFormatStyle), pMsgTitle);
                    }
                    break;
                case 5://Alarm property
                    alarmAllConfig = new NETDEV_ALARM_SCHEDULE();
                    returnValue = NETClient.NETGetDevConfig(pLoginID, ref  alarmAllConfig);
                    if (returnValue == true)
                    {
                        cmbAlarm.SelectedIndex = -1;// make sure trigger the control event
                        cmbAlarm.SelectedIndex = 0;                        
                        //setDataToControl(alarmConfig);//Display alarm property
                    }
                    else
                    {
                        //Report error message for the last operation
                        MessageBox.Show(NETClient.LastOperationInfo.ToString(pErrInfoFormatStyle), pMsgTitle);
                    }
                    ////DVR time information obtaining
                    //NET_TIME dvrTime = new NET_TIME();
                    //returnValue = NETClient.NETGetDevConfig(pLoginID, ref  dvrTime);
                    //if (returnValue == true)
                    //{
                    //    //setDataToControl(alarmConfig);//Display alarm property
                    //}
                    //else
                    //{
                    //    //Report erro message for the last operation
                    //    MessageBox.Show(NETClient.LastOperationInfo.ToString(pErrInfoFormatStyle), pMsgTitle);
                    //}
                    //break;                    
                    break;
            }
        }

        #region << Acquire data to present in screen controls >>
        /// <summary>
        /// Display 232 serial port configuration
        /// </summary>
        /// <param name="c232Config">232 Serial port configuration</param>
        private void setDataToControl(NET_RS232_CFG c232Config)
        {
            try
            {
                cmbCOMFunction.SelectedIndex = (int)((uint)c232Config.byFunction);
                cmbCOMDataBit.SelectedIndex = (int)((uint)c232Config.struComm.byDataBit);
                cmbCOMStopBit.SelectedIndex = (int)((uint)c232Config.struComm.byStopBit);
                cmbCOMBaudRate.SelectedIndex = (int)((uint)c232Config.struComm.byBaudRate);
                cmbCOMParity.SelectedIndex = (int)((uint)c232Config.struComm.byParity);
            }
            catch
            {
                MessageBox.Show("Assignment error!", pMsgTitle);
            }
        }
        /// <summary>
        /// Display 458 serial port configuration 
        /// </summary>
        /// <param name="c232Config">458 Serial port configuration</param>
        private void setDataToControl(NET_485_CFG c458Config)
        {
            try
            {
                cmb458DecProName.SelectedIndex = (int)c458Config.wProtocol;
                cmb458DataBit.SelectedIndex = (int)((uint)c458Config.struComm.byDataBit);
                cmb458StopBit.SelectedIndex = (int)((uint)c458Config.struComm.byStopBit);
                cmb458BaudRate.SelectedIndex = (int)((uint)c458Config.struComm.byBaudRate);
                cmb458Parity.SelectedIndex = (int)((uint)c458Config.struComm.byParity);
                txt458Add.Text = c458Config.wDecoderAddress.ToString();
            }
            catch
            {
                MessageBox.Show("Assignment error!", pMsgTitle);
            }

        }
        /// <summary>
        /// Display device information 
        /// </summary>
        /// <param name="sysAttrConfig">Device property</param>
        private void setDataToControl(NETDEV_SYSTEM_ATTR_CFG sysAttrConfig)
        {
            try
            {
                txtDevType.Text = sysAttrConfig.DevType();//Device type                
                txtDevType2.Text="";
                for(int i =0 ; i<sysAttrConfig.szDevType.Length;i++)
                {
                    txtDevType2.Text += (char)sysAttrConfig.szDevType[i];
                }
                txtSN.Text = sysAttrConfig.DevSerialNo();//Device serial number
                txtVideoIn.Text = sysAttrConfig.byVideoCaptureNum.ToString("D");//Video capture number
                txtAudioIn.Text = sysAttrConfig.byAudioCaptureNum.ToString("D");//audio capture number
                txtAlarmIn.Text = sysAttrConfig.byAlarmInNum.ToString("D");//Alarm input number
                txtAlarmOut.Text = sysAttrConfig.byAlarmOutNum.ToString("D");//Alarm output number
                txtNetIO.Text = sysAttrConfig.byNetIONum.ToString("D");//Network port number
                txtUSBIO.Text = sysAttrConfig.byUsbIONum.ToString("D");//USB port count
                txtIDEIO.Text = sysAttrConfig.byIdeIONum.ToString("D");//IDE port count
                txt232IO.Text = sysAttrConfig.byComIONum.ToString("D");//232 port count
                txtLPTIO.Text = sysAttrConfig.byLPTIONum.ToString("D");//Parallel number
                txtTalkIn.Text = sysAttrConfig.byTalkInChanNum.ToString("D");//Talk intercom input channel number
                txtTalkOut.Text = sysAttrConfig.byTalkOutChanNum.ToString("D");//Talk intercom output channel number
                txtDecodeChanNum.Text = sysAttrConfig.byDecodeChanNum.ToString();//Decoding channel number
                txtIdeControlNum.Text = sysAttrConfig.byIdeControlNum.ToString();//IDE controller number
                txtIdeControlType.Text = sysAttrConfig.byIdeControlType.ToString();//IDE controller type
                txtVgaIONum.Text = sysAttrConfig.byVgaIONum.ToString();//VGA port number
                txtDevNo.Text = sysAttrConfig.wDevNo.ToString();//Device number
                cmbOverWrite.SelectedIndex = sysAttrConfig.byOverWrite;//Hard disk is full
                txtRecordLen.Text = sysAttrConfig.byRecordLen.ToString();//Record package length
                cmbVideoStandard.SelectedIndex = sysAttrConfig.byVideoStandard;//Video standard
                cmbTimeFmt.SelectedIndex = sysAttrConfig.byTimeFmt;//Time format
                cmbDateFormat.SelectedIndex = sysAttrConfig.byDateFormat;//Date format
                cmbDateSprtr.SelectedIndex = sysAttrConfig.byDateSprtr;//Date delimiter
                txtStartChanNo.Text = sysAttrConfig.byStartChanNo.ToString();//Start channel number
                txtSoftWareVersion.Text = "Software version number:" + NETClient.NETUInt32ToString(sysAttrConfig.stVersion.dwSoftwareVersion, "V1.V2") + ";SoftwareBuildData:" + NETClient.NETUInt32ToString(sysAttrConfig.stVersion.dwSoftwareBuildDate, "yyyy/m/d");//software version
            }
            catch
            {
                MessageBox.Show("Assignment error!", pMsgTitle);
            }
        }
        /// <summary>
        /// Display network configuration information
        /// </summary>
        /// <param name="netConfig">Network configuration</param>
        private void setDataToControl(NETDEV_NET_CFG netConfig)
        {
            try
            {
                txtDevName.Text = NETClient.NETByteArrayToString(netConfig.sDevName);
                txtTcpLinkNum.Text = netConfig.wTcpMaxConnectNum.ToString();
                txtTcpPort.Text = netConfig.wTcpPort.ToString();
                txtUDPPort.Text = netConfig.wUdpPort.ToString();
                txtHTTPPort.Text = netConfig.wHttpPort.ToString();
                txtHTTPSPort.Text = netConfig.wHttpsPort.ToString();
                txtSSLPort.Text = netConfig.wSslPort.ToString();                
                //Read Email information
                txtMailCCAdd.Text = netConfig.struMail.CcAddr();
                txtMailUserName.Text = NETClient.NETByteArrayToString(netConfig.struMail.sUserName);
                txtMailPassword.Text = NETClient.NETByteArrayToString(netConfig.struMail.sUserPsw);
                txtMailPort.Text = netConfig.struMail.wMailPort.ToString();
                txtMailIPAdd.Text = NETClient.NETByteArrayToString(netConfig.struMail.sMailIPAddr);
                txtMailSendAdd.Text = NETClient.NETByteArrayToString(netConfig.struMail.sSenderAddr);
                txtMailReceiveAdd.Text = NETClient.NETByteArrayToString(netConfig.struMail.sDestAddr);
                txtMailBCCAdd.Text = NETClient.NETByteArrayToString(netConfig.struMail.sBccAddr);
                txtMailSubject.Text = NETClient.NETByteArrayToString(netConfig.struMail.sSubject);
                //Ethnet information
                cmbNetIONum.SelectedIndex = 0;
                //Remote host information
                //cmbRemohost.SelectedIndex = 0;
            }
            catch
            {
                MessageBox.Show("Assignment error!", pMsgTitle);
            }
        }

        /// <summary>
        /// Displat channel information
        /// </summary>
        /// <param name="netConfig">Channel information</param>
        private void setDataToControl(NETDEV_CHANNEL_CFG channelConfig)
        {
            try
            {
                txtChannelName.Text = NETClient.NETByteArrayToString(channelConfig.szChannelName);
                txtBrightness0.Text = channelConfig.stColorCfg[0].byBrightness.ToString("D");//Brightness
                txtContrast0.Text = channelConfig.stColorCfg[0].byContrast.ToString("D");//Contrast
                txtSaturation0.Text = channelConfig.stColorCfg[0].bySaturation.ToString("D");//Saturation
                txtHue0.Text = channelConfig.stColorCfg[0].byHue.ToString("D");//Hue
                chkGainEn0.Checked = (channelConfig.stColorCfg[0].byGainEn == 1 ? true : false);//Gain enable
                txtGain0.Text = channelConfig.stColorCfg[0].byGain.ToString("D");//Gain
                txtBrightness1.Text = channelConfig.stColorCfg[1].byBrightness.ToString("D");//Brightness
                txtContrast1.Text = channelConfig.stColorCfg[1].byContrast.ToString("D");//Contrast
                txtSaturation1.Text = channelConfig.stColorCfg[1].bySaturation.ToString("D");//Saturation
                txtHue1.Text = channelConfig.stColorCfg[1].byHue.ToString("D");//Hue
                chkGainEn1.Checked = (channelConfig.stColorCfg[1].byGainEn == 1 ? true : false);//Gain enable
                txtGain1.Text = channelConfig.stColorCfg[1].byGain.ToString("D");//Gain
                cmbVideoEncOpt.SelectedIndex = 0;//Selected index
                cmbOSD.SelectedIndex = 0;//OSD type selected

            }
            catch
            {
                MessageBox.Show("Assignment error!", pMsgTitle);
            }
        }

        /// <summary>
        /// Display recording configuration information
        /// </summary>
        /// <param name="netConfig">recording configuration</param>
        private void setDataToControl(NETDEV_RECORD_CFG recConfig)
        {
            try
            {
                chkRedundancyEn.Checked = (recConfig.byRedundancyEn == 1 ? true : false);
                txtPreRecordLen.Text = recConfig.byPreRecordLen.ToString();
                cmbWeeks.SelectedIndex = -1;
                cmbWeeks.SelectedIndex = 0;

            }
            catch
            {
                MessageBox.Show("Assignment error!", pMsgTitle);
            }
        }

        /// <summary>
        /// Display time information of the recording configuration
        /// </summary>
        /// <param name="netConfig">Time information</param>
        private void setDataToControl(NET_REC_TSECT tsectConfig)
        {
            try
            {
                //Time one
                chkT1Enable.Checked = tsectConfig.sTSECT[0].bEnable;
                txtT1StartH.Text = tsectConfig.sTSECT[0].iBeginHour.ToString();
                txtT1StartM.Text = tsectConfig.sTSECT[0].iBeginMin.ToString();
                txtT1StartS.Text = tsectConfig.sTSECT[0].iBeginSec.ToString();
                txtT1EndH.Text = tsectConfig.sTSECT[0].iEndHour.ToString();
                txtT1EndM.Text = tsectConfig.sTSECT[0].iEndMin.ToString();
                txtT1EndS.Text = tsectConfig.sTSECT[0].iEndSec.ToString();
                //Time two
                chkT2Enable.Checked = tsectConfig.sTSECT[1].bEnable;
                txtT2StartH.Text = tsectConfig.sTSECT[1].iBeginHour.ToString();
                txtT2StartM.Text = tsectConfig.sTSECT[1].iBeginMin.ToString();
                txtT2StartS.Text = tsectConfig.sTSECT[1].iBeginSec.ToString();
                txtT2EndH.Text = tsectConfig.sTSECT[1].iEndHour.ToString();
                txtT2EndM.Text = tsectConfig.sTSECT[1].iEndMin.ToString();
                txtT2EndS.Text = tsectConfig.sTSECT[1].iEndSec.ToString();
                //Time three
                chkT3Enable.Checked = tsectConfig.sTSECT[2].bEnable;
                txtT3StartH.Text = tsectConfig.sTSECT[2].iBeginHour.ToString();
                txtT3StartM.Text = tsectConfig.sTSECT[2].iBeginMin.ToString();
                txtT3StartS.Text = tsectConfig.sTSECT[2].iBeginSec.ToString();
                txtT3EndH.Text = tsectConfig.sTSECT[2].iEndHour.ToString();
                txtT3EndM.Text = tsectConfig.sTSECT[2].iEndMin.ToString();
                txtT3EndS.Text = tsectConfig.sTSECT[2].iEndSec.ToString();
                //Time four
                chkT4Enable.Checked = tsectConfig.sTSECT[3].bEnable;
                txtT4StartH.Text = tsectConfig.sTSECT[3].iBeginHour.ToString();
                txtT4StartM.Text = tsectConfig.sTSECT[3].iBeginMin.ToString();
                txtT4StartS.Text = tsectConfig.sTSECT[3].iBeginSec.ToString();
                txtT4EndH.Text = tsectConfig.sTSECT[3].iEndHour.ToString();
                txtT4EndM.Text = tsectConfig.sTSECT[3].iEndMin.ToString();
                txtT4EndS.Text = tsectConfig.sTSECT[3].iEndSec.ToString();
                //Time five
                chkT5Enable.Checked = tsectConfig.sTSECT[4].bEnable;
                txtT5StartH.Text = tsectConfig.sTSECT[4].iBeginHour.ToString();
                txtT5StartM.Text = tsectConfig.sTSECT[4].iBeginMin.ToString();
                txtT5StartS.Text = tsectConfig.sTSECT[4].iBeginSec.ToString();
                txtT5EndH.Text = tsectConfig.sTSECT[4].iEndHour.ToString();
                txtT5EndM.Text = tsectConfig.sTSECT[4].iEndMin.ToString();
                txtT5EndS.Text = tsectConfig.sTSECT[4].iEndSec.ToString();
                //Time six
                chkT6Enable.Checked = tsectConfig.sTSECT[5].bEnable;
                txtT6StartH.Text = tsectConfig.sTSECT[5].iBeginHour.ToString();
                txtT6StartM.Text = tsectConfig.sTSECT[5].iBeginMin.ToString();
                txtT6StartS.Text = tsectConfig.sTSECT[5].iBeginSec.ToString();
                txtT6EndH.Text = tsectConfig.sTSECT[5].iEndHour.ToString();
                txtT6EndM.Text = tsectConfig.sTSECT[5].iEndMin.ToString();
                txtT6EndS.Text = tsectConfig.sTSECT[5].iEndSec.ToString();
            }
            catch
            {
                MessageBox.Show("Assignment error!", pMsgTitle);
            }
        }
         /// <summary>
        /// Display time information of the recording configuration
        /// </summary>
        /// <param name="netConfig">time information</param>
        private void setDataToControl(NET_REC_TSECT tsectConfig,string strType)
        {
            try
            {
                if (strType == "Alarm")
                {
                    //Time one
                    chkAT1Enable.Checked = tsectConfig.sTSECT[0].bEnable;
                    txtAT1StartH.Text = tsectConfig.sTSECT[0].iBeginHour.ToString();
                    txtAT1StartM.Text = tsectConfig.sTSECT[0].iBeginMin.ToString();
                    txtAT1StartS.Text = tsectConfig.sTSECT[0].iBeginSec.ToString();
                    txtAT1EndH.Text = tsectConfig.sTSECT[0].iEndHour.ToString();
                    txtAT1EndM.Text = tsectConfig.sTSECT[0].iEndMin.ToString();
                    txtAT1EndS.Text = tsectConfig.sTSECT[0].iEndSec.ToString();
                    //Time two
                    chkAT2Enable.Checked = tsectConfig.sTSECT[1].bEnable;
                    txtAT2StartH.Text = tsectConfig.sTSECT[1].iBeginHour.ToString();
                    txtAT2StartM.Text = tsectConfig.sTSECT[1].iBeginMin.ToString();
                    txtAT2StartS.Text = tsectConfig.sTSECT[1].iBeginSec.ToString();
                    txtAT2EndH.Text = tsectConfig.sTSECT[1].iEndHour.ToString();
                    txtAT2EndM.Text = tsectConfig.sTSECT[1].iEndMin.ToString();
                    txtAT2EndS.Text = tsectConfig.sTSECT[1].iEndSec.ToString();
                    //Time three
                    chkAT3Enable.Checked = tsectConfig.sTSECT[2].bEnable;
                    txtAT3StartH.Text = tsectConfig.sTSECT[2].iBeginHour.ToString();
                    txtAT3StartM.Text = tsectConfig.sTSECT[2].iBeginMin.ToString();
                    txtAT3StartS.Text = tsectConfig.sTSECT[2].iBeginSec.ToString();
                    txtAT3EndH.Text = tsectConfig.sTSECT[2].iEndHour.ToString();
                    txtAT3EndM.Text = tsectConfig.sTSECT[2].iEndMin.ToString();
                    txtAT3EndS.Text = tsectConfig.sTSECT[2].iEndSec.ToString();
                    //Time four
                    chkAT4Enable.Checked = tsectConfig.sTSECT[3].bEnable;
                    txtAT4StartH.Text = tsectConfig.sTSECT[3].iBeginHour.ToString();
                    txtAT4StartM.Text = tsectConfig.sTSECT[3].iBeginMin.ToString();
                    txtAT4StartS.Text = tsectConfig.sTSECT[3].iBeginSec.ToString();
                    txtAT4EndH.Text = tsectConfig.sTSECT[3].iEndHour.ToString();
                    txtAT4EndM.Text = tsectConfig.sTSECT[3].iEndMin.ToString();
                    txtAT4EndS.Text = tsectConfig.sTSECT[3].iEndSec.ToString();
                    //Time five 
                    chkAT5Enable.Checked = tsectConfig.sTSECT[4].bEnable;
                    txtAT5StartH.Text = tsectConfig.sTSECT[4].iBeginHour.ToString();
                    txtAT5StartM.Text = tsectConfig.sTSECT[4].iBeginMin.ToString();
                    txtAT5StartS.Text = tsectConfig.sTSECT[4].iBeginSec.ToString();
                    txtAT5EndH.Text = tsectConfig.sTSECT[4].iEndHour.ToString();
                    txtAT5EndM.Text = tsectConfig.sTSECT[4].iEndMin.ToString();
                    txtAT5EndS.Text = tsectConfig.sTSECT[4].iEndSec.ToString();
                    //Time six
                    chkAT6Enable.Checked = tsectConfig.sTSECT[5].bEnable;
                    txtAT6StartH.Text = tsectConfig.sTSECT[5].iBeginHour.ToString();
                    txtAT6StartM.Text = tsectConfig.sTSECT[5].iBeginMin.ToString();
                    txtAT6StartS.Text = tsectConfig.sTSECT[5].iBeginSec.ToString();
                    txtAT6EndH.Text = tsectConfig.sTSECT[5].iEndHour.ToString();
                    txtAT6EndM.Text = tsectConfig.sTSECT[5].iEndMin.ToString();
                    txtAT6EndS.Text = tsectConfig.sTSECT[5].iEndSec.ToString();
                }
            }
            catch
            {
                MessageBox.Show("Assignment error!", pMsgTitle);
            }
        }

        /// <summary>
        /// Message triggers profiling
        /// </summary>
        private void setActionMask(NET_MSG_HANDLE msgHandle)
        {
            //Valid or not
            chkActionMask01.Enabled = ((int)(msgHandle.dwActionMask & 0x00000001) == 0x00000001 ? true : false);//Upload server　0x00000001
            chkActionMask02.Enabled = ((int)(msgHandle.dwActionMask & 0x00000002) == 0x00000002 ? true : false);//Linkage video　0x00000002
            chkActionMask08.Enabled = ((int)(msgHandle.dwActionMask & 0x00000008) == 0x00000008 ? true : false);//Send Email　0x00000008
            chkActionMask10.Enabled = ((int)(msgHandle.dwActionMask & 0x00000010) == 0x00000010 ? true : false);//Local alarm device polling　0x00000010
            chkActionMask20.Enabled = ((int)(msgHandle.dwActionMask & 0x00000020) == 0x00000020 ? true : false);//Tips enabled device　0x00000020
            chkActionMask40.Enabled = ((int)(msgHandle.dwActionMask & 0x00000040) == 0x00000040 ? true : false);//Device alarm output enable　0x00000040
            //Selected or not
            chkActionMask01.Checked = ((int)(msgHandle.dwActionFlag & 0x00000001) == 0x00000001 ? true : false);//Upload server　0x00000001
            chkActionMask02.Checked = ((int)(msgHandle.dwActionFlag & 0x00000002) == 0x00000002 ? true : false);//Linkage video　0x00000002
            chkActionMask08.Checked = ((int)(msgHandle.dwActionFlag & 0x00000008) == 0x00000008 ? true : false);//Send Email　0x00000008
            chkActionMask10.Checked = ((int)(msgHandle.dwActionFlag & 0x00000010) == 0x00000010 ? true : false);//Local alarm device polling　0x00000010
            chkActionMask20.Checked = ((int)(msgHandle.dwActionFlag & 0x00000020) == 0x00000020 ? true : false);//Tips enabled device　0x00000020
            chkActionMask40.Checked = ((int)(msgHandle.dwActionFlag & 0x00000040) == 0x00000040 ? true : false);//Device alarm output enable　0x00000040

            chkRelAlarmOut01.Checked = ((int)msgHandle.byRelAlarmOut[0] == 1 ? true : false);
            chkRelAlarmOut02.Checked = ((int)msgHandle.byRelAlarmOut[1] == 1 ? true : false);
            chkRelAlarmOut03.Checked = ((int)msgHandle.byRelAlarmOut[2] == 1 ? true : false);
            chkRelAlarmOut04.Checked = ((int)msgHandle.byRelAlarmOut[3] == 1 ? true : false);
            chkRelAlarmOut05.Checked = ((int)msgHandle.byRelAlarmOut[4] == 1 ? true : false);
            chkRelAlarmOut06.Checked = ((int)msgHandle.byRelAlarmOut[5] == 1 ? true : false);
            chkRelAlarmOut07.Checked = ((int)msgHandle.byRelAlarmOut[6] == 1 ? true : false);
            chkRelAlarmOut08.Checked = ((int)msgHandle.byRelAlarmOut[7] == 1 ? true : false);
            chkRelAlarmOut09.Checked = ((int)msgHandle.byRelAlarmOut[8] == 1 ? true : false);
            chkRelAlarmOut10.Checked = ((int)msgHandle.byRelAlarmOut[9] == 1 ? true : false);
            chkRelAlarmOut11.Checked = ((int)msgHandle.byRelAlarmOut[10] == 1 ? true : false);
            chkRelAlarmOut12.Checked = ((int)msgHandle.byRelAlarmOut[11] == 1 ? true : false);
            chkRelAlarmOut13.Checked = ((int)msgHandle.byRelAlarmOut[12] == 1 ? true : false);
            chkRelAlarmOut14.Checked = ((int)msgHandle.byRelAlarmOut[13] == 1 ? true : false);
            chkRelAlarmOut15.Checked = ((int)msgHandle.byRelAlarmOut[14] == 1 ? true : false);
            chkRelAlarmOut16.Checked = ((int)msgHandle.byRelAlarmOut[15] == 1 ? true : false);
            chkRecordChannel01.Checked = ((int)msgHandle.byRecordChannel[0] == 1 ? true : false);
            chkRecordChannel02.Checked = ((int)msgHandle.byRecordChannel[1] == 1 ? true : false);
            chkRecordChannel03.Checked = ((int)msgHandle.byRecordChannel[2] == 1 ? true : false);
            chkRecordChannel04.Checked = ((int)msgHandle.byRecordChannel[3] == 1 ? true : false);
            chkRecordChannel05.Checked = ((int)msgHandle.byRecordChannel[4] == 1 ? true : false);
            chkRecordChannel06.Checked = ((int)msgHandle.byRecordChannel[5] == 1 ? true : false);
            chkRecordChannel07.Checked = ((int)msgHandle.byRecordChannel[6] == 1 ? true : false);
            chkRecordChannel08.Checked = ((int)msgHandle.byRecordChannel[7] == 1 ? true : false);
            chkRecordChannel09.Checked = ((int)msgHandle.byRecordChannel[8] == 1 ? true : false);
            chkRecordChannel10.Checked = ((int)msgHandle.byRecordChannel[9] == 1 ? true : false);
            chkRecordChannel11.Checked = ((int)msgHandle.byRecordChannel[10] == 1 ? true : false);
            chkRecordChannel12.Checked = ((int)msgHandle.byRecordChannel[11] == 1 ? true : false);
            chkRecordChannel13.Checked = ((int)msgHandle.byRecordChannel[12] == 1 ? true : false);
            chkRecordChannel14.Checked = ((int)msgHandle.byRecordChannel[13] == 1 ? true : false);
            chkRecordChannel15.Checked = ((int)msgHandle.byRecordChannel[14] == 1 ? true : false);
            chkRecordChannel16.Checked = ((int)msgHandle.byRecordChannel[15] == 1 ? true : false);
        }

        /// <summary>
        /// Display alarm configuration information
        /// </summary>
        /// <param name="alarmConfig"></param>
        private void setDataToControl(NET_ALARMIN_CFG alarmConfig)
        { 
            try
            {
                chkAlarmEn.Checked = (alarmConfig.byAlarmEn == 1 ? true : false);
                cmbAlarmType.SelectedIndex = alarmConfig.byAlarmType;
                setActionMask(alarmConfig.struHandle);
                cmbAWeeks.SelectedIndex = -1;
                cmbAWeeks.SelectedIndex = 0;
            }
            catch
            {
                MessageBox.Show("Assignment error!", pMsgTitle);
            }
        }

        /// <summary>
        /// Display image occlusion alarm configuration information
        /// </summary>
        /// <param name="alarmConfig"></param>
        private void setDataToControl(NET_BLIND_CFG alarmConfig)
        {
            try
            {
                chkAlarmEn.Checked = (alarmConfig.byBlindEnable == 1 ? true : false);
                txtSenseLevel.Text = alarmConfig.byBlindLevel.ToString();
                setActionMask(alarmConfig.struHandle);
                cmbAWeeks.SelectedIndex = -1;
                cmbAWeeks.SelectedIndex = 0;
            }
            catch
            {
                MessageBox.Show("Assignment error!", pMsgTitle);
            }
        }


        /// <summary>
        /// Display video loss alarm configuration information
        /// </summary>
        /// <param name="alarmConfig"></param>
        private void setDataToControl(NET_VIDEO_LOST_CFG alarmConfig)
        {
            try
            {
                chkAlarmEn.Checked = (alarmConfig.byAlarmEn == 1 ? true : false);
                setActionMask(alarmConfig.struHandle);
                cmbAWeeks.SelectedIndex = -1;
                cmbAWeeks.SelectedIndex = 0;
            }
            catch
            {
                MessageBox.Show("Assignment error!", pMsgTitle);
            }
        }


        /// <summary>
        /// Display dynamic detection alarm configuration information
        /// </summary>
        /// <param name="alarmConfig"></param>
        private void setDataToControl(NET_MOTION_DETECT_CFG alarmConfig)
        {
            try
            {
                /*******************************************
                 * Here you need the dynamic structure of the detection area: Dynamic Inspection
                 * The number of rows and columns measuring area handled accordingly
                 * -------This routine does not reflect accordingly-------
                 *******************************************/
                string strTemp ;
                string strValue;
                chkAlarmEn.Checked = (alarmConfig.byMotionEn == 1 ? true : false);
                txtSenseLevel.Text = alarmConfig.wSenseLevel.ToString();
                foreach (Control bt in grpDetected.Controls)
                {
                    if (bt.GetType() == typeof(Button))
                    {
                        strTemp = ((Button)bt).Tag.ToString().Substring(0, 2);
                        strValue = alarmConfig.byDetected[int.Parse(((Button)bt).Tag.ToString().Substring(0, 1), System.Globalization.NumberStyles.AllowHexSpecifier)].Detected[int.Parse(((Button)bt).Tag.ToString().Substring(1, 1), System.Globalization.NumberStyles.AllowHexSpecifier)].ToString();
                        switch (strValue)
                        {
                            case "1"://Valid
                                ((Button)bt).BackColor = Color.White;
                                break;
                            case "0"://Invalid
                                ((Button)bt).BackColor = Color.Gray;
                                break;
                        }
                        ((Button)bt).Tag = strTemp + strValue;
                    }
                }
                setActionMask(alarmConfig.struHandle);
                cmbAWeeks.SelectedIndex = -1;
                cmbAWeeks.SelectedIndex = 0;
            }
            catch
            {
                MessageBox.Show("Assignment error!", pMsgTitle);
            }
        }


        #endregion

        /// <summary>
        /// Channel number selecting process
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void cmbChannelNum_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (cmbChannelNum.Items.Count > 0 && channelConfig.Equals(new NETDEV_CHANNEL_CFG()) == false && cmbChannelNum.SelectedIndex != -1)
            {
                setDataToControl(channelConfig[cmbChannelNum.SelectedIndex]);
            }

        }

        /// <summary>
        /// Gain enable time 0
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void chkGainEn_CheckedChanged(object sender, EventArgs e)
        {
            txtGain0.Enabled = chkGainEn0.Checked;
        }

        /// <summary>
        /// Gain enable time 1
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void chkGainEn1_CheckedChanged(object sender, EventArgs e)
        {
            txtGain1.Enabled = chkGainEn1.Checked;
        }
        /// <summary>
        /// Stream selecting
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void cmbVideoEncOpt_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (cmbChannelNum.Items.Count > 0 && cmbChannelNum.SelectedIndex != -1 && channelConfig.Equals(new NETDEV_CHANNEL_CFG()) == false && cmbVideoEncOpt.SelectedIndex != -1)
            {
                if (cmbVideoEncOpt.SelectedIndex < 3)
                {
                    VideoEncOptSelectChange(channelConfig[cmbChannelNum.SelectedIndex].stMainVideoEncOpt[cmbVideoEncOpt.SelectedIndex]);
                }
                else
                {
                    VideoEncOptSelectChange(channelConfig[cmbChannelNum.SelectedIndex].stAssiVideoEncOpt[cmbVideoEncOpt.SelectedIndex - 3]);
                }
            }


        }

        /// <summary>
        /// Steam selecting process
        /// </summary>
        /// <param name="videoOpt"></param>
        private void VideoEncOptSelectChange(NET_VIDEOENC_OPT videoOpt)
        {
            try
            {
                chkVideoEnable.Checked = (videoOpt.byVideoEnable == 1 ? true : false);//Video enable
                chkAudioEnable.Checked = (videoOpt.byAudioEnable == 1 ? true : false);//Audio enable
                cmbBitRateControl.SelectedIndex = videoOpt.byBitRateControl;//Stream control
                cmbFramesPerSec.SelectedIndex = videoOpt.byFramesPerSec;//Frame rate
                cmbEncodeMode.SelectedIndex = videoOpt.byEncodeMode;//Encode mode
                cmbImageSize.SelectedIndex = videoOpt.byImageSize;//Resolution
                cmbImageQlty.SelectedIndex = videoOpt.byImageQlty - 1;//Image qulity [Need to minus 1 when 1-6 transfer to SelectIndex]
                cmbFormatTag.SelectedIndex = videoOpt.wFormatTag;//Audio encode
                txtChannels.Text = videoOpt.nChannels.ToString("D");//Channel number
                txtSamplesPerSec.Text = videoOpt.nSamplesPerSec.ToString("D");//Sampling rate
                txtBitsPerSampl.Text = videoOpt.wBitsPerSample.ToString("D");//Sampling depth
            }
            catch
            {
                MessageBox.Show("Assignment error!", pMsgTitle);
            }

        }

        /// <summary>
        /// OSD type selection
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void cmbOSD_SelectedIndexChanged(object sender, EventArgs e)
        {
            labBlindEnable.Visible = false;
            cmbBlindEnable.Visible = false;
            if (cmbChannelNum.Items.Count > 0 && cmbChannelNum.SelectedIndex != -1 && channelConfig.Equals(new NETDEV_CHANNEL_CFG()) == false && cmbOSD.SelectedIndex != -1)
            {
                NET_ENCODE_WIDGET encodeWidGet;
                switch (cmbOSD.SelectedIndex)
                {
                    case 1://TimeOSD
                        encodeWidGet = channelConfig[cmbChannelNum.SelectedIndex].stTimeOSD;
                        break;
                    case 0://ChannelNameOSD
                        encodeWidGet = channelConfig[cmbChannelNum.SelectedIndex].stChannelOSD;
                        break;
                    case 2://BlindCover
                        labBlindEnable.Visible = true;
                        cmbBlindEnable.Visible = true;
                        encodeWidGet = channelConfig[cmbChannelNum.SelectedIndex].stBlindCover[0];
                        cmbBlindEnable.SelectedIndex = (int)channelConfig[cmbChannelNum.SelectedIndex].byBlindEnable;
                        break;
                    default:
                        encodeWidGet = channelConfig[cmbChannelNum.SelectedIndex].stChannelOSD;
                        break;
                }
                OSDSelectChange(encodeWidGet);
            }
        }
        /// <summary>
        /// OSD Type selecting process
        /// </summary>
        /// <param name="encodeWidGet"></param>
        private void OSDSelectChange(NET_ENCODE_WIDGET encodeWidGet)
        {
            try
            {
                chkShow.Checked = (encodeWidGet.bShow == 1 ? true : false);
                string rgbaValue = "";
                //Foreground color
                rgbaValue = encodeWidGet.rgbaFrontground.ToString("X");
                rgbaValue = "00000000".Remove(0, rgbaValue.Length) + rgbaValue;
                txtFrontgroundR.Text = int.Parse(rgbaValue.Substring(0, 2), System.Globalization.NumberStyles.AllowHexSpecifier).ToString();
                txtFrontgroundG.Text = int.Parse(rgbaValue.Substring(2, 2), System.Globalization.NumberStyles.AllowHexSpecifier).ToString();
                txtFrontgroundB.Text = int.Parse(rgbaValue.Substring(4, 2), System.Globalization.NumberStyles.AllowHexSpecifier).ToString();
                txtFrontgroundA.Text = int.Parse(rgbaValue.Substring(6, 2), System.Globalization.NumberStyles.AllowHexSpecifier).ToString();
                //Background color
                rgbaValue = encodeWidGet.rgbaBackground.ToString("X");
                rgbaValue = "00000000".Remove(0, rgbaValue.Length) + rgbaValue;
                txtBackgroundR.Text = int.Parse(rgbaValue.Substring(0, 2), System.Globalization.NumberStyles.AllowHexSpecifier).ToString();
                txtBackgroundG.Text = int.Parse(rgbaValue.Substring(2, 2), System.Globalization.NumberStyles.AllowHexSpecifier).ToString();
                txtBackgroundB.Text = int.Parse(rgbaValue.Substring(4, 2), System.Globalization.NumberStyles.AllowHexSpecifier).ToString();
                txtBackgroundA.Text = int.Parse(rgbaValue.Substring(6, 2), System.Globalization.NumberStyles.AllowHexSpecifier).ToString();
                //distance
                txtLeft.Text = encodeWidGet.rcRect.left.ToString();
                txtRight.Text = encodeWidGet.rcRect.right.ToString();
                txtTop.Text = encodeWidGet.rcRect.top.ToString();
                txtBottom.Text = encodeWidGet.rcRect.bottom.ToString();
            }
            catch
            {
                MessageBox.Show("Assignment error!", pMsgTitle);
            }

        }
        /// <summary>
        /// Press the button to save the configuration information
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btnSaveConfig_Click(object sender, EventArgs e)
        {
            bool returnValue = false;
            switch (tbcMain.SelectedIndex)
            {
                case 0://Device property
                    #region << Save writable attribute settings >>
                    sysAttrConfig.wDevNo = ushort.Parse(txtDevNo.Text);//Device number
                    sysAttrConfig.byOverWrite = (byte)cmbOverWrite.SelectedIndex;//Process method for hard dics full
                    sysAttrConfig.byRecordLen = (byte)int.Parse(txtRecordLen.Text);//video package length
                    sysAttrConfig.byDateFormat = (byte)cmbDateFormat.SelectedIndex;//Date format
                    sysAttrConfig.byDateSprtr = (byte)cmbDateSprtr.SelectedIndex;//Date delimiter
                    sysAttrConfig.byTimeFmt = (byte)cmbTimeFmt.SelectedIndex;//Time format
                    #endregion
                    returnValue = NETClient.NETSetDevConfig(pLoginID, sysAttrConfig);
                    break;
                case 1://Image channel property
                    cmbChannelNum_DropDown(null, null);//Save channel setup information
                    returnValue = NETClient.NETSetDevConfig(pLoginID, channelConfig);
                    break;
                case 2://Serial port property                   
                    cmbRS232_DropDown(null, null);//Save 232 serial port information
                    cmb485_DropDown(null, null);//Save 485 serial port information
                    returnValue = NETClient.NETSetDevConfig(pLoginID,commConfig);
                    break;
                case 3://Recording property
                    cmbRecChannel_DropDown(null, null);
                    cmbWeeks_DropDown(null, null);
                    returnValue = NETClient.NETSetDevConfig(pLoginID, recConfig);
                    break;
                case 4://Network configuration
                    #region << Save writable property configuration >>
                    NETClient.NETStringToByteArry(txtDevName.Text, ref  netConfig.sDevName);
                    netConfig.wTcpMaxConnectNum = (ushort)int.Parse(txtTcpLinkNum.Text);//Maxium TCP connection number
                    netConfig.wTcpPort = (ushort)int.Parse(txtTcpPort.Text);//TCP port
                    netConfig.wUdpPort = (ushort)int.Parse(txtUDPPort.Text);//UDP port
                    netConfig.wHttpPort = (ushort)int.Parse(txtHTTPPort.Text);//HTTP port
                    netConfig.wHttpsPort = (ushort)int.Parse(txtHTTPSPort.Text);//HTTPS port
                    netConfig.wSslPort = (ushort)int.Parse(txtSSLPort.Text);//SSL port
                    //Save email information
                    NETClient.NETStringToByteArry(txtMailBCCAdd.Text, ref netConfig.struMail.sBccAddr);
                    NETClient.NETStringToByteArry(txtMailCCAdd.Text, ref netConfig.struMail.sCcAddr);
                    NETClient.NETStringToByteArry(txtMailPassword.Text, ref netConfig.struMail.sUserPsw);
                    netConfig.struMail.wMailPort = ushort.Parse(txtMailPort.Text);
                    NETClient.NETStringToByteArry(txtMailReceiveAdd.Text, ref  netConfig.struMail.sDestAddr);
                    NETClient.NETStringToByteArry(txtMailSendAdd.Text, ref  netConfig.struMail.sSenderAddr);
                    NETClient.NETStringToByteArry(txtMailSubject.Text, ref  netConfig.struMail.sSubject);                    
                    NETClient.NETStringToByteArry(txtMailUserName.Text, ref netConfig.struMail.sUserName);
                    NETClient.NETStringToByteArry(txtMailIPAdd.Text, ref netConfig.struMail.sMailIPAddr);
                    //Save Ethernet port information data
                    cmbNetIONum_DropDown(null, null);
                    //Save remote host data information
                    cmbRemohost_DropDown(null, null);
                    #endregion
                    returnValue = NETClient.NETSetDevConfig(pLoginID, netConfig);
                    break;
                case 5://Alarm property
                    cmbAlarm_DropDown(null, null);
                    cmbAlarmInOrChannel_DropDown(null, null);
                    returnValue = NETClient.NETSetDevConfig(pLoginID, alarmAllConfig);
                    break;
            }
            if (returnValue == true)
            {
                //Report setting successfully
                MessageBox.Show("set success!", pMsgTitle);
            }
            else
            {
                if (NETClient.LastOperationInfo.errCode != "0")
                {
                    //Report error message for the last operation
                    MessageBox.Show(NETClient.LastOperationInfo.ToString(pErrInfoFormatStyle), pMsgTitle);
                }
            }
        }

        /// <summary>
        /// Only number input controller pressed is admitted to process
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void Num_KeyPress(object sender, KeyPressEventArgs e)
        {
            char[] chrAccept = new char[1];
            chrAccept[0] = (char)Keys.Back;
            DHKeyPressSet('0', '9', chrAccept, e);

        }

        #region << Screen control buttons are unrelated to business >>
        /// <summary>
        /// Screen control only can press number key
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        public static void DHKeyPressSet(char chrFrom, char chrTo, KeyPressEventArgs e)
        {
            if ((e.KeyChar >= chrFrom && e.KeyChar <= chrTo) == false)
            {
                e.Handled = true;
            }
        }

        /// <summary>
        /// Screen control only can press number key
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        public static void DHKeyPressSet(char[] chrAccept, KeyPressEventArgs e)
        {
            foreach (char chr in chrAccept)
            {
                if (e.KeyChar == chr)
                {
                    return;
                }
            }
            e.Handled = true;
        }

        /// <summary>
        /// Screen control only can press number key
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        public static void DHKeyPressSet(char chrFrom, char chrTo, char[] chrAccept, KeyPressEventArgs e)
        {
            if ((e.KeyChar >= chrFrom && e.KeyChar <= chrTo) == true)
            {
                return;
            }
            foreach (char chr in chrAccept)
            {
                if (e.KeyChar == chr)
                {
                    return;
                }
            }
            e.Handled = true;
        }

        /// <summary>
        /// Screen control only can press number key
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        public static void DHKeyPressSet(Keys[] keysAccept, KeyPressEventArgs e)
        {
            char[] chrAccept = new char[keysAccept.Length];
            for (int i = 0; i < keysAccept.Length; i++)
            {
                chrAccept[i] = (char)keysAccept[i];
            }
            DHKeyPressSet(chrAccept, e);
        }

        /// <summary>
        /// Screen control only can press number key
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        public static void DHKeyPressSet(char chrFrom, char chrTo, Keys[] keysAccept, KeyPressEventArgs e)
        {
            char[] chrAccept = new char[keysAccept.Length];
            for (int i = 0; i < keysAccept.Length; i++)
            {
                chrAccept[i] = (char)keysAccept[i];
            }
            DHKeyPressSet(chrFrom, chrTo, chrAccept, e);
        }

        #endregion

        /// <summary>
        /// Ethernet port selection process
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void cmbNetIONum_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (netConfig.Equals(new NETDEV_NET_CFG()) == false && cmbNetIONum.SelectedIndex != -1)
            {
                NetIONumSelect(netConfig.stEtherNet[cmbNetIONum.SelectedIndex]);
            }
        }
        /// <summary>
        /// Ethernet port selection process
        /// </summary>
        /// <param name="ethernetConfig"></param>
        private void NetIONumSelect(NET_ETHERNET ethernetConfig)
        {
            txtIPAdd.Text = NETClient.NETByteArrayToString(ethernetConfig.sDevIPAddr);
            txtMaskAdd.Text = NETClient.NETByteArrayToString(ethernetConfig.sDevIPMask);
            txtGatewayIP.Text = NETClient.NETByteArrayToString(ethernetConfig.sGatewayIP);
            cmbNetInterface.SelectedIndex = (int)ethernetConfig.dwNetInterface;
            txtMacIP.Text = NETClient.NETByteArrayToString(ethernetConfig.byMACAddr);
        }
        /// <summary>
        /// Select remote host
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void cmbRemohost_SelectedIndexChanged(object sender, EventArgs e)
        {
            labIPorHostNameTitle.Visible = false;
            txtIPorHostName.Visible = false;
            labIPorHostNameTitle.Text = ":";
            txtIPorHostName.Text = "";
            if (netConfig.Equals(new NETDEV_NET_CFG()) == false && cmbRemohost.SelectedIndex != -1)
            {
                NET_REMOTE_HOST remoteHost = new NET_REMOTE_HOST();
                int selectIndex=cmbRemohost.SelectedIndex;
                #region << Control valid/invalid process >>
                switch (selectIndex)
                {
                    case 0://Alarm sever
                    case 1://Log sever
                    case 2://SMTP sever
                    case 3://Multicast group
                        chkHostEnable.Enabled = false;
                        txtHostIPAddr.Enabled = true;
                        txtHostPort.Enabled = true;
                        txtHostUserName.Enabled = false;
                        txtHostPassword.Enabled = false;
                        break;
                    case 4:////NFS sever
                        chkHostEnable.Enabled = true;
                        txtHostIPAddr.Enabled = true;
                        txtHostPort.Enabled = true;
                        txtHostUserName.Enabled = true;
                        txtHostPassword.Enabled = true;
                        break;
                    case 5://PPPoE sever
                        chkHostEnable.Enabled = true;
                        txtHostIPAddr.Enabled = false;
                        txtHostPort.Enabled = false;
                        txtHostUserName.Enabled = true;
                        txtHostPassword.Enabled = true;
                        break;
                    case 6://DDNS sever
                        chkHostEnable.Enabled = true;
                        txtHostIPAddr.Enabled = true;
                        txtHostPort.Enabled = true;
                        txtHostUserName.Enabled = false;
                        txtHostPassword.Enabled = false;
                        break;
                    case 7://DNS sever
                        chkHostEnable.Enabled = false;
                        txtHostIPAddr.Enabled = true;
                        txtHostPort.Enabled = false;
                        txtHostUserName.Enabled = false;
                        txtHostPassword.Enabled = false;
                        break;
                }
                #endregion
                
                switch (selectIndex)
                {
                    case 0://Alarm sever
                        remoteHost = netConfig.struAlarmHost;
                        break;
                    case 1://Log sever
                        remoteHost = netConfig.struLogHost;
                        break;
                    case 2://SMTP sever
                        remoteHost = netConfig.struSmtpHost;
                        break;
                    case 3://Multicast group
                        remoteHost = netConfig.struMultiCast;
                        break;
                    case 4://NFS sever
                        remoteHost = netConfig.struNfs;
                        break;
                    case 5://PPPoE sever
                        remoteHost = netConfig.struPppoe;
                        labIPorHostNameTitle.Visible = true;
                        txtIPorHostName.Visible = true;
                        labIPorHostNameTitle.Text = "Register IP:";
                        txtIPorHostName.Text = NETClient.NETByteArrayToString(netConfig.sPppoeIP);
                        break;
                    case 6://DDNS sever
                        remoteHost = netConfig.struDdns;
                        labIPorHostNameTitle.Visible = true;
                        txtIPorHostName.Visible = true;
                        labIPorHostNameTitle.Text = "DDNS host name:";
                        txtIPorHostName.Text = NETClient.NETByteArrayToString(netConfig.sDdnsHostName);
                        break;
                    case 7://DNS sever
                        remoteHost = netConfig.struDns;
                        break;
                }
                if (remoteHost.Equals(new NET_REMOTE_HOST()) == false)
                {
                    RemohostSelect(remoteHost);
                }

            }
        }
        /// <summary>
        /// Remote host process selection 
        /// </summary>
        /// <param name="remoteHost"></param>
        private void RemohostSelect(NET_REMOTE_HOST remoteHost)
        {
            txtHostIPAddr.Text = NETClient.NETByteArrayToString(remoteHost.sHostIPAddr);
            txtHostPassword.Text = NETClient.NETByteArrayToString(remoteHost.sHostPassword);
            txtHostPort.Text = remoteHost.wHostPort.ToString();
            txtHostUserName.Text = NETClient.NETByteArrayToString(remoteHost.sHostUser);
            chkHostEnable.Checked = (remoteHost.byEnable == 1 ? true : false);
        }

        /// <summary>
        /// Save data before selecting OSD type
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void cmbOSD_DropDown(object sender, EventArgs e)
        {
            if (cmbOSD.SelectedIndex != -1)
            {
                switch (cmbOSD.SelectedIndex)
                {
                    case 1://TimeOSD
                        OSDSaveData(ref channelConfig[cmbChannelNum.SelectedIndex].stTimeOSD);
                        break;
                    case 0://ChannelNameOSD
                        OSDSaveData(ref channelConfig[cmbChannelNum.SelectedIndex].stChannelOSD);
                        break;
                    case 2://BlindCover
                        OSDSaveData(ref channelConfig[cmbChannelNum.SelectedIndex].stBlindCover[0]);
                        channelConfig[cmbChannelNum.SelectedIndex].byBlindEnable = (byte)cmbBlindEnable.SelectedIndex;
                        break;
                }
            }
        }

        /// <summary>
        /// Save data before selecting OSD type
        /// </summary>
        /// <param name="encodeWidGet"></param>
        private void OSDSaveData(ref NET_ENCODE_WIDGET encodeWidGet)
        {
            encodeWidGet.bShow = (byte)(chkShow.Checked == true ? 1 : 0);
            encodeWidGet.rcRect.left = int.Parse(txtLeft.Text);
            encodeWidGet.rcRect.top = int.Parse(txtTop.Text);
            encodeWidGet.rcRect.right = int.Parse(txtRight.Text);
            encodeWidGet.rcRect.bottom = int.Parse(txtBottom.Text);
            encodeWidGet.rgbaBackground = uint.Parse(StringToHexString(txtBackgroundR.Text) + 
                                                     StringToHexString(txtBackgroundG.Text) + 
                                                     StringToHexString(txtBackgroundB.Text) + 
                                                     StringToHexString(txtBackgroundA.Text), 
                                                     System.Globalization.NumberStyles.AllowHexSpecifier);
            encodeWidGet.rgbaFrontground = uint.Parse(StringToHexString(txtFrontgroundR.Text) +
                                                      StringToHexString(txtFrontgroundG.Text) +
                                                      StringToHexString(txtFrontgroundB.Text) +
                                                      StringToHexString(txtFrontgroundA.Text),
                                                      System.Globalization.NumberStyles.AllowHexSpecifier);

        }

        /// <summary>
        /// Convert integer into standard hexadecimal to present [Format:00]
        /// </summary>
        /// <param name="strValue">0-255 integer</param>
        /// <returns></returns>
        private string StringToHexString(string strValue)
        {
            try
            {
                string result = "";
                int value = int.Parse(strValue);
                if (value < 0 || value > 255)
                {
                    MessageBox.Show("Illegal string!", pMsgTitle);
                    return ""; 
                }
                result = value.ToString("X");
                result = "00".Remove(0, result.Length) + result;
                return result;

            }
            catch
            {
                MessageBox.Show("Illegal string!", pMsgTitle);
                return "";
            }
        }

        /// <summary>
        /// Save data before selecting the method of stream encoding
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void cmbVideoEncOpt_DropDown(object sender, EventArgs e)
        {
            if (cmbVideoEncOpt.SelectedIndex != -1)
            {
                if (cmbVideoEncOpt.SelectedIndex < 3)
                {
                    VideEncOptSaveData(ref channelConfig[cmbChannelNum.SelectedIndex].stMainVideoEncOpt[cmbVideoEncOpt.SelectedIndex]);
                }
                else
                {
                    VideEncOptSaveData(ref channelConfig[cmbChannelNum.SelectedIndex].stAssiVideoEncOpt[cmbVideoEncOpt.SelectedIndex - 3]);
                }
            }

        }
        
        /// <summary>
        /// Save data before selecting the method of stream encoding
        /// </summary>
        private void VideEncOptSaveData(ref NET_VIDEOENC_OPT videoOpt)
        {
            try
            {
                videoOpt.byVideoEnable=(byte)(chkVideoEnable.Checked ==true? 1 : 0);//Enable Video
                videoOpt.byAudioEnable = (byte)(chkAudioEnable.Checked == true ? 1 : 0);//Audio enabled
                videoOpt.byBitRateControl=(byte)cmbBitRateControl.SelectedIndex ;//Stream Encoding Control
                videoOpt.byFramesPerSec=(byte)cmbFramesPerSec.SelectedIndex ;//Frame Rate
                videoOpt.byEncodeMode = (byte)cmbEncodeMode.SelectedIndex;//Decoding mode
                videoOpt.byImageSize=(byte)cmbImageSize.SelectedIndex;//Resolution
                videoOpt.byImageQlty=(byte)(cmbImageQlty.SelectedIndex +1);//Definition[Minus one when transfer 1-6 into SelectIndex]
                videoOpt.wFormatTag=(byte)cmbFormatTag.SelectedIndex;//Audio Coding
                videoOpt.nChannels=ushort.Parse(txtChannels.Text);//Number of Channels
                videoOpt.nSamplesPerSec=ushort.Parse(txtSamplesPerSec.Text);//Sampling Rate
                videoOpt.wBitsPerSample=ushort.Parse(txtBitsPerSampl.Text);//Sampling depth
            }
            catch
            {
                MessageBox.Show("Save error!", pMsgTitle);
            }
        }

        /// <summary>
        /// Save before selecting the channel  
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void cmbChannelNum_DropDown(object sender, EventArgs e)
        {
            if (cmbChannelNum.SelectedIndex != -1)
            {
                ChannelNumSaveData(ref channelConfig[cmbChannelNum.SelectedIndex]);
                cmbVideoEncOpt_DropDown(null, null);
                cmbOSD_DropDown(null, null);
            }
        }

        /// <summary>
        /// Save before selecting the channel
        /// </summary>
        /// <param name="channelConfig"></param>
        private void ChannelNumSaveData(ref NETDEV_CHANNEL_CFG channelConfig)
        {
            try
            {
                NETClient.NETStringToByteArry(txtChannelName.Text ,ref channelConfig.szChannelName);
                channelConfig.stColorCfg[0].byBrightness=(byte)int.Parse(txtBrightness0.Text);//Brightness
                channelConfig.stColorCfg[0].byContrast=(byte)int.Parse(txtContrast0.Text );//Contrast
                channelConfig.stColorCfg[0].bySaturation=(byte)int.Parse(txtSaturation0.Text);//Saturation
                channelConfig.stColorCfg[0].byHue=(byte)int.Parse(txtHue0.Text);//Chroma
                channelConfig.stColorCfg[0].byGainEn = (byte)(chkGainEn0.Checked ==true ?1 : 0);//Gain Enable
                channelConfig.stColorCfg[0].byGain=(byte)int.Parse(txtGain0.Text);//Gain
                channelConfig.stColorCfg[1].byBrightness = (byte)int.Parse(txtBrightness1.Text);//Brightness
                channelConfig.stColorCfg[1].byContrast = (byte)int.Parse(txtContrast1.Text);//Contrast
                channelConfig.stColorCfg[1].bySaturation = (byte)int.Parse(txtSaturation1.Text);//Saturation
                channelConfig.stColorCfg[1].byHue = (byte)int.Parse(txtHue1.Text);//Chroma
                channelConfig.stColorCfg[1].byGainEn = (byte)(chkGainEn1.Checked == true ? 1 : 0);//Gain Enable
                channelConfig.stColorCfg[1].byGain = (byte)int.Parse(txtGain1.Text);//Gain
            }
            catch
            {
                MessageBox.Show("Save error!", pMsgTitle);
            }
        }
        /// <summary>
        /// Save before selecting earth net port
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void cmbNetIONum_DropDown(object sender, EventArgs e)
        {
            if (cmbNetInterface.SelectedIndex != -1)
            {
                NetIONumSaveData(ref netConfig.stEtherNet[cmbNetIONum.SelectedIndex]);
            }
        }
        /// <summary>
        /// Save before selecting earth net port
        /// </summary>
        /// <param name="ethernetConfig"></param>
        private void NetIONumSaveData(ref NET_ETHERNET ethernetConfig)
        {
           NETClient.NETStringToByteArry(txtIPAdd.Text,ref ethernetConfig.sDevIPAddr);
           NETClient.NETStringToByteArry(txtMaskAdd.Text,ref  ethernetConfig.sDevIPMask);
           NETClient.NETStringToByteArry(txtGatewayIP.Text,ref  ethernetConfig.sGatewayIP);
            ethernetConfig.dwNetInterface=(uint)cmbNetInterface.SelectedIndex;
            NETClient.NETStringToByteArry(txtMacIP.Text,ref ethernetConfig.byMACAddr);
        }

        /// <summary>
        /// Selecting Remote host 
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void cmbRemohost_DropDown(object sender, EventArgs e)
        {
            if (cmbRemohost.SelectedIndex != -1)
            {
                switch (cmbRemohost.SelectedIndex)
                {
                    case 0://Alarm Server
                        RemohostSaveData(ref netConfig.struAlarmHost);
                        break;
                    case 1://Log Server
                        RemohostSaveData(ref netConfig.struLogHost);
                        break;
                    case 2://SMTP Server
                        RemohostSaveData(ref netConfig.struSmtpHost);
                        break;
                    case 3://Multicast group
                        RemohostSaveData(ref netConfig.struMultiCast);
                        break;
                    case 4://NFS Server
                        RemohostSaveData(ref netConfig.struNfs);
                        break;
                    case 5://PPPoE Server
                        RemohostSaveData(ref netConfig.struPppoe);
                        NETClient.NETStringToByteArry(txtIPorHostName.Text,ref netConfig.sPppoeIP);
                        break;
                    case 6://DDNS Server
                        RemohostSaveData(ref netConfig.struDdns);
                        NETClient.NETStringToByteArry(txtIPorHostName.Text,ref netConfig.sDdnsHostName);
                        break;
                    case 7://DNS Server
                        RemohostSaveData(ref netConfig.struDns);
                        break;
                }
            }

        }
        /// <summary>
        /// Selecting Remote host
        /// </summary>
        /// <param name="remoteHost"></param>
        private void RemohostSaveData(ref NET_REMOTE_HOST remoteHost)
        {
            NETClient.NETStringToByteArry(txtHostIPAddr.Text, ref remoteHost.sHostIPAddr);
            NETClient.NETStringToByteArry(txtHostPassword.Text, ref remoteHost.sHostPassword);
            remoteHost.wHostPort = ushort.Parse(txtHostPort.Text);
            NETClient.NETStringToByteArry(txtHostUserName.Text,ref  remoteHost.sHostUser);
            remoteHost.byEnable = (byte)(chkHostEnable.Checked == true ? 1 : 0);
        }

        /// <summary>
        /// IP Address key in control
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void IPAdd_KeyPress(object sender, KeyPressEventArgs e)
        {
            char[] chrAccept = new char[2];
            chrAccept[0] = (char)Keys.Back;
            chrAccept[1] = '.';//IP address separator
            DHKeyPressSet('0', '9', chrAccept, e);
        }
        /// <summary>
        /// Selecting 232 port
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void cmbRS232_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (cmbRS232.SelectedIndex != -1 && commConfig.Equals(new NETDEV_COMM_CFG())==false)
            {
                setDataToControl(commConfig.st232[cmbRS232.SelectedIndex]);
            }
        }

        /// <summary>
        /// Decoder selection
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void cmb485_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (cmb485.SelectedIndex != -1 && commConfig.Equals(new NETDEV_COMM_CFG()) == false)
            {
                setDataToControl(commConfig.stDecoder[cmb485.SelectedIndex]);
            }
        }

        /// <summary>
        /// Save before selecting 232 port
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void cmbRS232_DropDown(object sender, EventArgs e)
        {
            if (cmbRS232.SelectedIndex != -1)
            {
                COMSaveData(ref commConfig.st232[cmbRS232.SelectedIndex]);
            }
        }

        /// <summary>
        /// Save before selecting 485 port
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void cmb485_DropDown(object sender, EventArgs e)
        {
            if (cmb485.SelectedIndex != -1)
            {
                COMSaveData(ref commConfig.stDecoder[cmb485.SelectedIndex]);
            }
        }

        /// <summary>
        /// Save 232 port information
        /// </summary>
        /// <param name="rs232Config"></param>
        private void COMSaveData(ref NET_RS232_CFG rs232Config)
        {
            try
            {
                rs232Config.struComm.byBaudRate = (byte)cmbCOMBaudRate.SelectedIndex;
                rs232Config.struComm.byDataBit = (byte)cmbCOMDataBit.SelectedIndex;
                rs232Config.struComm.byParity = (byte)cmbCOMParity.SelectedIndex;
                rs232Config.struComm.byStopBit = (byte)cmbCOMStopBit.SelectedIndex;
                rs232Config.byFunction = (byte)cmbCOMFunction.SelectedIndex;
            }
            catch
            {
                MessageBox.Show("Save error!", pMsgTitle);
            }
        }
        /// <summary>
        /// Save 485 port information
        /// </summary>
        /// <param name="rs232Config"></param>
        private void COMSaveData(ref NET_485_CFG rs485Config)
        {
            try
            {
                rs485Config.wDecoderAddress = (ushort)int.Parse(txt458Add.Text);
                rs485Config.struComm.byBaudRate = (byte)cmb458BaudRate.SelectedIndex;
                rs485Config.struComm.byDataBit = (byte)cmb458DataBit.SelectedIndex;
                rs485Config.struComm.byParity = (byte)cmb458Parity.SelectedIndex;
                rs485Config.struComm.byStopBit = (byte)cmb458StopBit.SelectedIndex;
                rs485Config.wProtocol = (ushort)cmb458DecProName.SelectedIndex;
            }
            catch
            {
                MessageBox.Show("Save error!", pMsgTitle);
            }
        }
        /// <summary>
        /// Is the password shown by '*' ?
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void chkEmailPassword_CheckedChanged(object sender, EventArgs e)
        {
            if (chkEmailPassword.Checked == true)
            {
                txtMailPassword.PasswordChar = '*';
            }
            else
            {
                txtMailPassword.PasswordChar =new char();
            }
        }

        private void cmbRecChannel_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (sysAttrConfig.Equals(new NETDEV_SYSTEM_ATTR_CFG()) == false && cmbRecChannel.SelectedIndex != -1)
            {
                setDataToControl(recConfig[cmbRecChannel.SelectedIndex]);
            }
        }

        private void cmbWeeks_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (sysAttrConfig.Equals(new NETDEV_SYSTEM_ATTR_CFG()) == false && cmbRecChannel.SelectedIndex != -1　&& cmbWeeks.SelectedIndex!=-1)
            {
                setDataToControl(recConfig[cmbRecChannel.SelectedIndex].stSect[cmbWeeks.SelectedIndex]);
            }
        }

        /// <summary>
        /// Save data before selecting the video information for a week 
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void cmbWeeks_DropDown(object sender, EventArgs e)
        {
            if ( cmbRecChannel.SelectedIndex!=-1 &&  cmbWeeks.SelectedIndex != -1)
            {
                TSECTSaveDate(ref recConfig[cmbRecChannel.SelectedIndex].stSect[cmbWeeks.SelectedIndex]);
            }
        }
        /// <summary>
        ///  Save data before selecting the video information for a week
        /// </summary>
        /// <param name="recTsect"></param>
        private void TSECTSaveDate(ref NET_REC_TSECT recTsect)
        {
            
            //Time 1
            int intTimeIndex = 0;
            recTsect.sTSECT[intTimeIndex].bEnable = chkT1Enable.Checked;
            recTsect.sTSECT[intTimeIndex].iBeginHour = int.Parse(txtT1StartH.Text);
            recTsect.sTSECT[intTimeIndex].iBeginMin = int.Parse(txtT1StartM.Text);
            recTsect.sTSECT[intTimeIndex].iBeginSec = int.Parse(txtT1StartS.Text);
            recTsect.sTSECT[intTimeIndex].iEndHour = int.Parse(txtT1EndH.Text);
            recTsect.sTSECT[intTimeIndex].iEndMin = int.Parse(txtT1EndM.Text);
            recTsect.sTSECT[intTimeIndex].iEndSec = int.Parse(txtT1EndS.Text);
            //Time 2
            intTimeIndex = 1;
            recTsect.sTSECT[intTimeIndex].bEnable = chkT2Enable.Checked;
            recTsect.sTSECT[intTimeIndex].iBeginHour = int.Parse(txtT2StartH.Text);
            recTsect.sTSECT[intTimeIndex].iBeginMin = int.Parse(txtT2StartM.Text);
            recTsect.sTSECT[intTimeIndex].iBeginSec = int.Parse(txtT2StartS.Text);
            recTsect.sTSECT[intTimeIndex].iEndHour = int.Parse(txtT2EndH.Text);
            recTsect.sTSECT[intTimeIndex].iEndMin = int.Parse(txtT2EndM.Text);
            recTsect.sTSECT[intTimeIndex].iEndSec = int.Parse(txtT2EndS.Text);
            //Time 3
            intTimeIndex = 2;
            recTsect.sTSECT[intTimeIndex].bEnable = chkT3Enable.Checked;
            recTsect.sTSECT[intTimeIndex].iBeginHour = int.Parse(txtT3StartH.Text);
            recTsect.sTSECT[intTimeIndex].iBeginMin = int.Parse(txtT3StartM.Text);
            recTsect.sTSECT[intTimeIndex].iBeginSec = int.Parse(txtT3StartS.Text);
            recTsect.sTSECT[intTimeIndex].iEndHour = int.Parse(txtT3EndH.Text);
            recTsect.sTSECT[intTimeIndex].iEndMin = int.Parse(txtT3EndM.Text);
            recTsect.sTSECT[intTimeIndex].iEndSec = int.Parse(txtT3EndS.Text);
            //Time 4
            intTimeIndex = 3;
            recTsect.sTSECT[intTimeIndex].bEnable = chkT4Enable.Checked;
            recTsect.sTSECT[intTimeIndex].iBeginHour = int.Parse(txtT4StartH.Text);
            recTsect.sTSECT[intTimeIndex].iBeginMin = int.Parse(txtT4StartM.Text);
            recTsect.sTSECT[intTimeIndex].iBeginSec = int.Parse(txtT4StartS.Text);
            recTsect.sTSECT[intTimeIndex].iEndHour = int.Parse(txtT4EndH.Text);
            recTsect.sTSECT[intTimeIndex].iEndMin = int.Parse(txtT4EndM.Text);
            recTsect.sTSECT[intTimeIndex].iEndSec = int.Parse(txtT4EndS.Text);
            //Time 5
            intTimeIndex = 4;
            recTsect.sTSECT[intTimeIndex].bEnable = chkT5Enable.Checked;
            recTsect.sTSECT[intTimeIndex].iBeginHour = int.Parse(txtT5StartH.Text);
            recTsect.sTSECT[intTimeIndex].iBeginMin = int.Parse(txtT5StartM.Text);
            recTsect.sTSECT[intTimeIndex].iBeginSec = int.Parse(txtT5StartS.Text);
            recTsect.sTSECT[intTimeIndex].iEndHour = int.Parse(txtT5EndH.Text);
            recTsect.sTSECT[intTimeIndex].iEndMin = int.Parse(txtT5EndM.Text);
            recTsect.sTSECT[intTimeIndex].iEndSec = int.Parse(txtT5EndS.Text);
            //Time 6
            intTimeIndex = 5;
            recTsect.sTSECT[intTimeIndex].bEnable = chkT6Enable.Checked;
            recTsect.sTSECT[intTimeIndex].iBeginHour = int.Parse(txtT6StartH.Text);
            recTsect.sTSECT[intTimeIndex].iBeginMin = int.Parse(txtT6StartM.Text);
            recTsect.sTSECT[intTimeIndex].iBeginSec = int.Parse(txtT6StartS.Text);
            recTsect.sTSECT[intTimeIndex].iEndHour = int.Parse(txtT6EndH.Text);
            recTsect.sTSECT[intTimeIndex].iEndMin = int.Parse(txtT6EndM.Text);
            recTsect.sTSECT[intTimeIndex].iEndSec = int.Parse(txtT6EndS.Text);
        }

        /// <summary>
        /// Save data before selecting video information port
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void cmbRecChannel_DropDown(object sender, EventArgs e)
        {
            if (cmbRecChannel.SelectedIndex != -1)
            {
                RecConfigSaveData(ref recConfig[cmbRecChannel.SelectedIndex]);
            }
        }
        /// <summary>
        /// Save data before selecting video information port
        /// </summary>
        /// <param name="recCfg">video configuration information</param>
        private void RecConfigSaveData(ref NETDEV_RECORD_CFG recCfg)
        {
            recCfg.byRedundancyEn = (byte)(chkRedundancyEn.Checked == true ? 1 : 0);
            recCfg.byPreRecordLen = (byte)int.Parse(txtPreRecordLen.Text);
            cmbWeeks_DropDown(null, null);
        }

        private void chkActionMask40_CheckedChanged(object sender, EventArgs e)
        {

        }

        private void cmbAlarm_SelectedIndexChanged(object sender, EventArgs e)
        { 
            int sltIndex=cmbAlarm.SelectedIndex;

            if (sltIndex != -1 & sysAttrConfig.Equals(new NETDEV_SYSTEM_ATTR_CFG()) == false)
            {
                int channelCount;
                cmbAlarmInOrChannel.Items.Clear();
                if (sltIndex == 0)
                {

                    labChannelOrAlarmIn.Text = "Alarm enter:";
                    labAlarmTypeOrSenseLevel.Text = "Alarm type:";
                    labAlarmTypeOrSenseLevel.Visible = true;
                    cmbAlarmType.Visible = true;
                    txtSenseLevel.Visible = false;

                    channelCount = sysAttrConfig.byAlarmInNum;//Alarm enter number
                    for (int i = 1; i <= channelCount; i++)
                    {
                        cmbAlarmInOrChannel.Items.Add("Alarm enter" + i.ToString());
                    }
                }
                else
                {

                    labChannelOrAlarmIn.Text = "Channel:";
                    labAlarmTypeOrSenseLevel.Text = "Sensitivity:";
                    cmbAlarmType.Visible = false;
                    if (sltIndex != 3)
                    {
                        labAlarmTypeOrSenseLevel.Visible = true;
                        txtSenseLevel.Visible = true;
                    }
                    else
                    {
                        labAlarmTypeOrSenseLevel.Visible = false;
                        txtSenseLevel.Visible = false;
                    }

                    channelCount = sysAttrConfig.byVideoCaptureNum;//The number of video ports
                    for (int i = 1; i <= channelCount; i++)
                    {
                        cmbAlarmInOrChannel.Items.Add("Channel" + i.ToString());
                    }
                }
                chkActionMask01.Enabled = (sltIndex == 2 || cmbAlarm.SelectedIndex == 3 ? false : true);
                chkActionMask20.Enabled = (sltIndex == 1 ? false : true);
                chkActionMask10.Enabled = (sltIndex == 0 ? true : false);
                btnDetected.Visible = (sltIndex == 1 ? true : false);
                //When the selection is not as dynamic detection motion detection area setting screen is not displayed
                if (sltIndex != 1)
                {
                    grpDetected.Visible = false;
                }
                //Display data to the screen
                switch (sltIndex)
                {
                    case 0://Alarm enter
                        setDataToControl(alarmAllConfig.struLocalAlmIn[0]);
                        cmbAlarmInOrChannel.SelectedIndex = 0;
                        break;
                    case 1://Dynamic detection
                        setDataToControl(alarmAllConfig.struMotion[0]);
                        cmbAlarmInOrChannel.SelectedIndex = 0;
                        break;
                    case 2://Video loss
                        setDataToControl(alarmAllConfig.struVideoLost[0]);
                        cmbAlarmInOrChannel.SelectedIndex = 0;
                        break;
                    case 3://Video block
                        setDataToControl(alarmAllConfig.struBlind[0]);
                        cmbAlarmInOrChannel.SelectedIndex = 0;
                        break;

                }
            }
        }

        private void cmbAWeeks_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (cmbAlarm.SelectedIndex != -1 & cmbAlarmInOrChannel.SelectedIndex != -1 & cmbAWeeks.SelectedIndex != -1)
            {
                switch (cmbAlarm.SelectedIndex)
                { 
                    case 0://Alarm enter
                        setDataToControl(alarmAllConfig.struLocalAlmIn[cmbAlarmInOrChannel.SelectedIndex].stSect[cmbAWeeks.SelectedIndex], "Alarm");
                        break;
                    case 1://Dynamic detection
                        setDataToControl(alarmAllConfig.struMotion[cmbAlarmInOrChannel.SelectedIndex].stSect[cmbAWeeks.SelectedIndex], "Alarm");
                        break;
                    case 2://Video loss
                        setDataToControl(alarmAllConfig.struVideoLost[cmbAlarmInOrChannel.SelectedIndex].stSect[cmbAWeeks.SelectedIndex], "Alarm");
                        break;
                    case 3://Video block
                        setDataToControl(alarmAllConfig.struBlind[cmbAlarmInOrChannel.SelectedIndex].stSect[cmbAWeeks.SelectedIndex], "Alarm");
                        break;
                }
            }
        }

        private void cmbAlarmInOrChannel_SelectedIndexChanged(object sender, EventArgs e)
        {
            switch (cmbAlarm.SelectedIndex)
            {
                case 0://Alarm enter
                    setDataToControl(alarmAllConfig.struLocalAlmIn[cmbAlarmInOrChannel.SelectedIndex]);
                    break;
                case 1://Dynamic detection
                    setDataToControl(alarmAllConfig.struMotion[cmbAlarmInOrChannel.SelectedIndex]);
                    break;
                case 2://Video loss
                    setDataToControl(alarmAllConfig.struVideoLost[cmbAlarmInOrChannel.SelectedIndex]);
                    break;
                case 3://Video block
                    setDataToControl(alarmAllConfig.struBlind[cmbAlarmInOrChannel.SelectedIndex]);
                    break;
            }
        }

        private void cmbAlarm_DropDown(object sender, EventArgs e)
        {
            if (cmbAlarm.SelectedIndex != -1)
            {
                switch (cmbAlarm.SelectedIndex)
                {
                    case 0://Alarm enter
                        AlarmSaveData(ref alarmAllConfig.struLocalAlmIn[cmbAlarmInOrChannel.SelectedIndex]);
                        break;
                    case 1://Dynamic detection
                        AlarmSaveData(ref alarmAllConfig.struMotion[cmbAlarmInOrChannel.SelectedIndex]);
                        break;
                    case 2://Video loss
                        AlarmSaveData(ref alarmAllConfig.struVideoLost[cmbAlarmInOrChannel.SelectedIndex]);
                        break;
                    case 3://Video block
                        AlarmSaveData(ref alarmAllConfig.struBlind[cmbAlarmInOrChannel.SelectedIndex]);
                        break;
                }
            }
        }
        /// <summary>
        /// Save alarm enter information
        /// </summary>
        /// <param name="AlarmConfig"></param>
        private void AlarmSaveData(ref NET_ALARMIN_CFG AlarmConfig)
        {
            cmbAWeeks_DropDown(null, null);
            AlarmConfig.byAlarmEn = (byte)(chkAlarmEn.Checked==true?1:0);
            AlarmConfig.byAlarmType =(byte) cmbAlarmType.SelectedIndex;
            AlarmSaveData(ref AlarmConfig.struHandle);
            
        }
        /// <summary>
        /// Save video loss information
        /// </summary>
        /// <param name="AlarmConfig"></param>
        private void AlarmSaveData(ref NET_VIDEO_LOST_CFG AlarmConfig)
        {
            cmbAWeeks_DropDown(null, null);
            AlarmConfig.byAlarmEn =(byte) (chkAlarmEn.Checked == true ? 1 : 0);
            AlarmSaveData(ref AlarmConfig.struHandle);
            
        }
        /// <summary>
        /// Save video block information
        /// </summary>
        /// <param name="AlarmConfig"></param>
        private void AlarmSaveData(ref NET_BLIND_CFG AlarmConfig)
        {
            cmbAWeeks_DropDown(null, null);
            AlarmConfig.byBlindEnable =(byte) (chkAlarmEn.Checked == true ? 1 : 0);
            AlarmConfig.byBlindLevel = (byte)(int.Parse(txtSenseLevel.Text));            
            AlarmSaveData(ref AlarmConfig.struHandle);
            
        }
        /// <summary>
        /// Save dynamic detection information
        /// </summary>
        /// <param name="AlarmConfig"></param>
        private void AlarmSaveData(ref NET_MOTION_DETECT_CFG AlarmConfig)
        {
            cmbAWeeks_DropDown(null, null);
            AlarmConfig.byMotionEn = (byte)(chkAlarmEn.Checked == true ? 1 : 0);
            AlarmConfig.wSenseLevel = (ushort)(int.Parse(txtSenseLevel.Text));            
            AlarmSaveData(ref AlarmConfig.struHandle);
            
        }

        private void AlarmSaveData(ref NET_MSG_HANDLE msgHandle)
        {
            msgHandle.dwActionMask =(uint) ((uint)(msgHandle.dwActionMask) | (uint)(chkActionMask01.Checked == true ? 0x00000001 : 0x00000000));
            msgHandle.dwActionMask = (uint)((uint)(msgHandle.dwActionMask)| (uint)(chkActionMask02.Checked == true ? 0x00000002 : 0x00000000));
            msgHandle.dwActionMask = (uint)((uint)msgHandle.dwActionMask | (uint)(chkActionMask08.Checked == true ? 0x00000008 : 0x00000000));
            msgHandle.dwActionMask = (uint)((uint)msgHandle.dwActionMask | (uint)(chkActionMask10.Checked == true ? 0x00000010 : 0x00000000));
            msgHandle.dwActionMask = (uint)((uint)msgHandle.dwActionMask | (uint)(chkActionMask20.Checked == true ? 0x00000020 : 0x00000000));
            msgHandle.dwActionMask = (uint)((uint)msgHandle.dwActionMask | (uint)(chkActionMask40.Checked == true ? 0x00000040 : 0x00000000));
            msgHandle.byRecordChannel[0] = (byte)(chkRecordChannel01.Checked == true ? 1 : 0);
            msgHandle.byRecordChannel[1] = (byte)(chkRecordChannel02.Checked == true ? 1 : 0);
            msgHandle.byRecordChannel[2] = (byte)(chkRecordChannel03.Checked == true ? 1 : 0);
            msgHandle.byRecordChannel[3] = (byte)(chkRecordChannel04.Checked == true ? 1 : 0);
            msgHandle.byRecordChannel[4] = (byte)(chkRecordChannel05.Checked == true ? 1 : 0);
            msgHandle.byRecordChannel[5] = (byte)(chkRecordChannel06.Checked == true ? 1 : 0);
            msgHandle.byRecordChannel[6] = (byte)(chkRecordChannel07.Checked == true ? 1 : 0);
            msgHandle.byRecordChannel[7] = (byte)(chkRecordChannel08.Checked == true ? 1 : 0);
            msgHandle.byRecordChannel[8] = (byte)(chkRecordChannel09.Checked == true ? 1 : 0);
            msgHandle.byRecordChannel[9] = (byte)(chkRecordChannel10.Checked == true ? 1 : 0);
            msgHandle.byRecordChannel[10] = (byte)(chkRecordChannel11.Checked == true ? 1 : 0);
            msgHandle.byRecordChannel[11] = (byte)(chkRecordChannel12.Checked == true ? 1 : 0);
            msgHandle.byRecordChannel[12] = (byte)(chkRecordChannel13.Checked == true ? 1 : 0);
            msgHandle.byRecordChannel[13] = (byte)(chkRecordChannel14.Checked == true ? 1 : 0);
            msgHandle.byRecordChannel[14] = (byte)(chkRecordChannel15.Checked == true ? 1 : 0);
            msgHandle.byRecordChannel[15] = (byte)(chkRecordChannel16.Checked == true ? 1 : 0);
            msgHandle.byRelAlarmOut[0] = (byte)(chkRelAlarmOut01.Checked == true ? 1 : 0);
            msgHandle.byRelAlarmOut[1] = (byte)(chkRelAlarmOut02.Checked == true ? 1 : 0);
            msgHandle.byRelAlarmOut[2] = (byte)(chkRelAlarmOut03.Checked == true ? 1 : 0);
            msgHandle.byRelAlarmOut[3] = (byte)(chkRelAlarmOut04.Checked == true ? 1 : 0);
            msgHandle.byRelAlarmOut[4] = (byte)(chkRelAlarmOut05.Checked == true ? 1 : 0);
            msgHandle.byRelAlarmOut[5] = (byte)(chkRelAlarmOut06.Checked == true ? 1 : 0);
            msgHandle.byRelAlarmOut[6] = (byte)(chkRelAlarmOut07.Checked == true ? 1 : 0);
            msgHandle.byRelAlarmOut[7] = (byte)(chkRelAlarmOut08.Checked == true ? 1 : 0);
            msgHandle.byRelAlarmOut[8] = (byte)(chkRelAlarmOut09.Checked == true ? 1 : 0);
            msgHandle.byRelAlarmOut[9] = (byte)(chkRelAlarmOut10.Checked == true ? 1 : 0);
            msgHandle.byRelAlarmOut[10] = (byte)(chkRelAlarmOut11.Checked == true ? 1 : 0);
            msgHandle.byRelAlarmOut[11] = (byte)(chkRelAlarmOut12.Checked == true ? 1 : 0);
            msgHandle.byRelAlarmOut[12] = (byte)(chkRelAlarmOut13.Checked == true ? 1 : 0);
            msgHandle.byRelAlarmOut[13] = (byte)(chkRelAlarmOut14.Checked == true ? 1 : 0);
            msgHandle.byRelAlarmOut[14] = (byte)(chkRelAlarmOut15.Checked == true ? 1 : 0);
            msgHandle.byRelAlarmOut[15] = (byte)(chkRelAlarmOut16.Checked == true ? 1 : 0);
        }

        private void cmbAWeeks_DropDown(object sender, EventArgs e)
        {
            if (cmbAlarm.SelectedIndex != -1 & cmbAlarmInOrChannel.SelectedIndex != -1 & cmbAWeeks.SelectedIndex != -1)
            {
                switch (cmbAlarm.SelectedIndex)
                {
                    case 0://Alarm enter
                        AlarmSaveData(ref alarmAllConfig.struLocalAlmIn[cmbAlarmInOrChannel.SelectedIndex].stSect[cmbAWeeks.SelectedIndex]);
                        break;
                    case 1://Dynamic detection
                        AlarmSaveData(ref alarmAllConfig.struMotion[cmbAlarmInOrChannel.SelectedIndex].stSect[cmbAWeeks.SelectedIndex]);
                        break;
                    case 2://video loss
                        AlarmSaveData(ref alarmAllConfig.struVideoLost[cmbAlarmInOrChannel.SelectedIndex].stSect[cmbAWeeks.SelectedIndex]);
                        break;
                    case 3://video block
                        AlarmSaveData(ref alarmAllConfig.struBlind[cmbAlarmInOrChannel.SelectedIndex].stSect[cmbAWeeks.SelectedIndex]);
                        break;
                }
            }
        }

        private void AlarmSaveData(ref NET_REC_TSECT recTsect)
        {
            //Time 1
            recTsect.sTSECT[0].bEnable = chkAT1Enable.Checked;
            recTsect.sTSECT[0].iBeginHour = int.Parse(txtAT1StartH.Text);
            recTsect.sTSECT[0].iBeginMin = int.Parse(txtAT1StartM.Text);
            recTsect.sTSECT[0].iBeginSec = int.Parse(txtAT1StartS.Text);
            recTsect.sTSECT[0].iEndHour = int.Parse(txtAT1EndH.Text);
            recTsect.sTSECT[0].iEndMin = int.Parse(txtAT1EndM.Text);
            recTsect.sTSECT[0].iEndSec = int.Parse(txtAT1EndS.Text);
            //Time 2
            recTsect.sTSECT[1].bEnable = chkAT2Enable.Checked;
            recTsect.sTSECT[1].iBeginHour = int.Parse(txtAT2StartH.Text);
            recTsect.sTSECT[1].iBeginMin = int.Parse(txtAT2StartM.Text);
            recTsect.sTSECT[1].iBeginSec = int.Parse(txtAT2StartS.Text);
            recTsect.sTSECT[1].iEndHour = int.Parse(txtAT2EndH.Text);
            recTsect.sTSECT[1].iEndMin = int.Parse(txtAT2EndM.Text);
            recTsect.sTSECT[1].iEndSec = int.Parse(txtAT2EndS.Text);
            //Time 3
            recTsect.sTSECT[2].bEnable = chkAT3Enable.Checked;
            recTsect.sTSECT[2].iBeginHour = int.Parse(txtAT3StartH.Text);
            recTsect.sTSECT[2].iBeginMin = int.Parse(txtAT3StartM.Text);
            recTsect.sTSECT[2].iBeginSec = int.Parse(txtAT3StartS.Text);
            recTsect.sTSECT[2].iEndHour = int.Parse(txtAT3EndH.Text);
            recTsect.sTSECT[2].iEndMin = int.Parse(txtAT3EndM.Text);
            recTsect.sTSECT[2].iEndSec = int.Parse(txtAT3EndS.Text);
            //Time 4
            recTsect.sTSECT[3].bEnable = chkAT4Enable.Checked;
            recTsect.sTSECT[3].iBeginHour = int.Parse(txtAT4StartH.Text);
            recTsect.sTSECT[3].iBeginMin = int.Parse(txtAT4StartM.Text);
            recTsect.sTSECT[3].iBeginSec = int.Parse(txtAT4StartS.Text);
            recTsect.sTSECT[3].iEndHour = int.Parse(txtAT4EndH.Text);
            recTsect.sTSECT[3].iEndMin = int.Parse(txtAT4EndM.Text);
            recTsect.sTSECT[3].iEndSec = int.Parse(txtAT4EndS.Text);
            //Time 5
            recTsect.sTSECT[4].bEnable = chkAT5Enable.Checked;
            recTsect.sTSECT[4].iBeginHour = int.Parse(txtAT5StartH.Text);
            recTsect.sTSECT[4].iBeginMin = int.Parse(txtAT5StartM.Text);
            recTsect.sTSECT[4].iBeginSec = int.Parse(txtAT5StartS.Text);
            recTsect.sTSECT[4].iEndHour = int.Parse(txtAT5EndH.Text);
            recTsect.sTSECT[4].iEndMin = int.Parse(txtAT5EndM.Text);
            recTsect.sTSECT[4].iEndSec = int.Parse(txtAT5EndS.Text);
            //Time 6
            recTsect.sTSECT[5].bEnable = chkAT6Enable.Checked;
            recTsect.sTSECT[5].iBeginHour = int.Parse(txtAT6StartH.Text);
            recTsect.sTSECT[5].iBeginMin = int.Parse(txtAT6StartM.Text);
            recTsect.sTSECT[5].iBeginSec = int.Parse(txtAT6StartS.Text);
            recTsect.sTSECT[5].iEndHour = int.Parse(txtAT6EndH.Text);
            recTsect.sTSECT[5].iEndMin = int.Parse(txtAT6EndM.Text);
            recTsect.sTSECT[5].iEndSec = int.Parse(txtAT6EndS.Text);
        }

        private void cmbAlarmInOrChannel_DropDown(object sender, EventArgs e)
        {
            if (cmbAlarmInOrChannel.SelectedIndex != -1)
            {
                switch (cmbAlarm.SelectedIndex)
                {
                    case 0://Alarm enter
                        AlarmSaveData(ref alarmAllConfig.struLocalAlmIn[cmbAlarmInOrChannel.SelectedIndex]);
                        break;
                    case 1://Dynamic detection
                        AlarmSaveData(ref alarmAllConfig.struMotion[cmbAlarmInOrChannel.SelectedIndex]);
                        break;
                    case 2://video loss
                        AlarmSaveData(ref alarmAllConfig.struVideoLost[cmbAlarmInOrChannel.SelectedIndex]);
                        break;
                    case 3://video block
                        AlarmSaveData(ref alarmAllConfig.struBlind[cmbAlarmInOrChannel.SelectedIndex]);
                        break;
                }
            }
        }

        private void btnDetected_Click(object sender, EventArgs e)
        {
            grpDetected.Visible = !grpDetected.Visible;
        }

        private void btnDetectedSelect_Click(object sender, EventArgs e)
        {
            string strTemp = ((Button)sender).Tag.ToString().Substring(0,2);
            string strValue="";
            if (((Button)sender).Tag.ToString().Length >= 3)
            {
                strValue = ((Button)sender).Tag.ToString().Substring(2, 1);
            }
            else
            {
                strValue = "0";
            }
            switch (strValue)
            { 
                case "0"://Invalid
                    strValue = "1";//Effective
                    ((Button)sender).BackColor = Color.White;
                    break;
                case "1"://Effective
                    strValue = "0";
                    ((Button)sender).BackColor = Color.Gray ;
                    break;
            }
            alarmAllConfig.struMotion[cmbAlarmInOrChannel.SelectedIndex].byDetected[int.Parse(strTemp.Substring(0, 1), System.Globalization.NumberStyles.AllowHexSpecifier)].Detected[int.Parse(strTemp.Substring(1, 1), System.Globalization.NumberStyles.AllowHexSpecifier)] = (byte)int.Parse(strValue);
            ((Button)sender).Tag = strTemp + strValue;
        }

        /// <summary>
        /// Disconnect handling equipment
        /// </summary>
        /// <param name="lLoginID"></param>
        /// <param name="pchDVRIP"></param>
        /// <param name="nDVRPort"></param>
        /// <param name="dwUser"></param>
        private void DisConnectEvent(int lLoginID, StringBuilder pchDVRIP, int nDVRPort, IntPtr dwUser)
        {
            //Disconnect handling equipment            
            MessageBox.Show("Disconnect handling equipment", pMsgTitle);            
        }

        private void buttonOpenFile_Click(object sender, EventArgs e)
        {
            OpenFileDialog fbdMain = new OpenFileDialog();
            
            if (fbdMain.ShowDialog() == DialogResult.OK)
            {
                textBoxFilePath.Text = fbdMain.FileName;
            }
        }

        private void buttonStartUpgrate_Click(object sender, EventArgs e)
        {
            if (0 != pLoginID)
            {
                if (textBoxFilePath.Text.Length == 0)
                {
                    MessageBox.Show("Select the upgrade file");
                    return;
                }
                if (hUpgradeId != 0)
                {
                    NETClient.NETCLIENT_StopUpgrade(hUpgradeId);
                    hUpgradeId = 0;
                }

                hUpgradeId = NETClient.NETCLIENT_StartUpgradeEx(pLoginID, EM_UPGRADE_TYPE.NET_UPGRADE_BIOS_TYPE, textBoxFilePath.Text, upgradeCallBack, 0);
                if (hUpgradeId != 0)
                {
                    if (NETClient.NETCLIENT_SendUpgrade(hUpgradeId))
                    {
                        MessageBox.Show("Start the upgrade");
                    }
                }
            }
            else
            {
                MessageBox.Show("Login!");
            }
             
        }

        private void buttonStopUpgrate_Click(object sender, EventArgs e)
        {
            if (hUpgradeId != 0)
            {
                if (NETClient.NETCLIENT_StopUpgrade(hUpgradeId))
                {
                    MessageBox.Show("Stop success!");
                }
                hUpgradeId = 0;
            }
        }

        private void UpgradeCallBack(Int32 lLoginID, UInt32 lUpgradechannel, Int32 nTotalSize, Int32 nSendSize, UInt32 dwUser)
        {
            if (-1 == nSendSize)
            {
                this.progressBarUpdate.Invoke(this.updatePosDelegate, -1);
            }
            else if (-2 == nSendSize)
            {
                this.progressBarUpdate.Invoke(this.updatePosDelegate, -2);
            }
            else if (-1 == nTotalSize)
            {
                if(0 <= nSendSize && nSendSize <= 100)
                {
                    this.progressBarUpdate.Invoke(this.updatePosDelegate, nSendSize);
                }
            }
            else
            {
                int nPos = (int)((nSendSize * 100.0) / (nTotalSize * 1.0) );
                this.progressBarUpdate.Invoke(this.updatePosDelegate, nPos);
            }
        }


    }
}