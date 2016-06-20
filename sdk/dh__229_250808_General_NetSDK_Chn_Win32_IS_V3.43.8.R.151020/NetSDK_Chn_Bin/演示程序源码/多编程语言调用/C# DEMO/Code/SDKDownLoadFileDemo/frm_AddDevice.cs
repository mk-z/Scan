

using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.IO;


namespace SDKDownLoadFileDemo
{
    public partial class frm_AddDevice : Form
    {
        [Serializable]
        private class DEVINFO
        {
            public string strDevName;
            public string strDevIP;
            public string strDevPort;
            public string strDevUser;
            public string strDevPwd;
        }

        /// <summary>
        /// Confirm Button Is Pressed
        /// </summary>
        public bool blnOKEnter = false;

        /// <summary>
        /// Number Of Device Recorded
        /// </summary>
        private int devNum;

        /// <summary>
        /// Information Of Divice Recorded
        /// </summary>
        private DEVINFO[] devInfos;

        private const string fileName = @"DownLoadFile_devInfo.dat";

        public frm_AddDevice()
        {
            InitializeComponent();
        }

        /// <summary>
        /// Initialize When Window Is Loaded
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void frm_AddDevice_Load(object sender, EventArgs e)
        {
            ReadDevInfo();

            foreach (DEVINFO info in devInfos)
                cmbDevIP.Items.Add(info.strDevIP);

            cmbDevIP.SelectedIndex = 0;

            //Set Language 
            string oldAppName = Utility.StringUtil.AppName;

            Utility.StringUtil.AppName = "Common";
            Utility.StringUtil.InitControlText(this);

            Utility.StringUtil.AppName = oldAppName;
        }

        /// <summary>
        /// Choose Different Devices Through Drop-down box
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void cmbDevIP_SelectedIndexChanged(object sender, EventArgs e)
        {
            try
            {
                int index = ((ComboBox)sender).SelectedIndex;
                DEVINFO info = devInfos[index];

                txtDevName.Text = info.strDevName;
                txtDevProt.Text = info.strDevPort;
                txtName.Text = info.strDevUser;
                txtPassword.Text = info.strDevPwd;
            }
            catch (System.Exception ex)
            {
                Console.WriteLine(ex.Message);
            }

        }

        /// <summary>
        /// Confirm Button Is Clicked
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btnOK_Click(object sender, EventArgs e)
        {
            blnOKEnter = true;

            SaveDevInfo();

            this.Close();
        }

        /// <summary>
        /// Cancel Button Click
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btnCancel_Click(object sender, EventArgs e)
        {
            blnOKEnter = false;

            this.Close();
        }

        /// <summary>
        /// initialize the device information with no equipment information file
        /// </summary>
        private void InitDevInfo()
        {
            devNum = 1;
            devInfos = new DEVINFO[1];

            devInfos[0] = new DEVINFO();
            devInfos[0].strDevName = "test";
            devInfos[0].strDevIP = "10.24.5.23";
            devInfos[0].strDevPort = "37777";
            devInfos[0].strDevUser = "admin";
            devInfos[0].strDevPwd = "admin";
        }

        /// <summary>
        /// save the input device information 
        /// </summary>
        private void SaveDevInfo()
        {
            //  at most iMaxNum device information recorded
            const int iMaxNum = 10;

            try
            {
                using (StreamWriter sw = File.CreateText(fileName))
                {
                    string strIP = cmbDevIP.Text;
                    bool bNewIP = true;

                    foreach (DEVINFO info in devInfos)
                    {
                        if (strIP.Equals(info.strDevIP))
                        {
                            bNewIP = false;
                            break;
                        }
                    }

                    int oldNum = devNum;
                    devNum += (bNewIP && devNum < iMaxNum) ? 1 : 0;
                    sw.WriteLine(devNum);

                    sw.WriteLine(txtDevName.Text);
                    sw.WriteLine(strIP);
                    sw.WriteLine(txtDevProt.Text);
                    sw.WriteLine(txtName.Text);
                    sw.WriteLine(txtPassword.Text);

                    for (int i = 0; i < oldNum && i < iMaxNum; i++)
                    {
                        DEVINFO info = devInfos[i];

                        if (!strIP.Equals(info.strDevIP))
                        {
                            sw.WriteLine(info.strDevName);
                            sw.WriteLine(info.strDevIP);
                            sw.WriteLine(info.strDevPort);
                            sw.WriteLine(info.strDevUser);
                            sw.WriteLine(info.strDevPwd);
                        }
                    }

                    sw.Close();
                }

            }
            catch (System.Exception ex)
            {

            }
        }

        /// <summary>
        /// read the device information
        /// </summary>
        private void ReadDevInfo()
        {
            try
            {
                if (File.Exists(fileName))
                {
                    string strLine;
                    StreamReader sr = File.OpenText(fileName);

                    strLine = sr.ReadLine();
                    devNum = int.Parse(strLine);
                    devInfos = new DEVINFO[devNum];

                    for (int i = 0; i < devNum; i++)
                    {
                        devInfos[i] = new DEVINFO();
                        devInfos[i].strDevName = sr.ReadLine();
                        devInfos[i].strDevIP = sr.ReadLine();
                        devInfos[i].strDevPort = sr.ReadLine();
                        devInfos[i].strDevUser = sr.ReadLine();
                        devInfos[i].strDevPwd = sr.ReadLine();
                    }

                    sr.Close();
                }
                else
                {
                    InitDevInfo();
                }
            }
            catch (System.Exception ex)
            {
                Console.WriteLine(ex.Message);

                InitDevInfo();
            }
        }
    }
}
