using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using PlaySDK;
using Utility;

namespace SDKPlayDemo
{
    public partial class frmDataRecord : Form
    {
        public frmDataRecord()
        {
            InitializeComponent();
        }

        private void frmDataRecord_Load(object sender, EventArgs e)
        {
            StringUtil.InitControlText(this);
        }
        /// <summary>
        /// Find the video save path dialog and press the handle 
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btnShowOpenFileDlg_Click(object sender, EventArgs e)
        {
            if (fbdMain.ShowDialog() == DialogResult.OK)
            {
                txtDirPath.Text = fbdMain.SelectedPath;
            }
        }
        /// <summary>
        /// Press start video button 
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btnStartRecord_Click(object sender, EventArgs e)
        {
            string strtemp = txtDirPath.Text.ToString() + @"\" + txtFileName.Text.ToString();
            strtemp=strtemp.Replace(@"\\", @"\");
            if (strtemp.Length > 0)
            {
                //To start recording
                if (NETPlay.NETStartDataRecord((int)nudPlayChannelNO.Value, strtemp, cmbDataType.SelectedIndex))
                {
                    //MessageBox.Show("Start data flow save success!", "Prompt:");
                    MessageBox.Show(strtemp, "Prompt:");
                }
                else
                {
                    MessageBox.Show("Start data flow save failure!", "Prompt:");
                };
            }
            else
            {
                MessageBox.Show("Please choose the save path and equipment save file name !", "Prompt:");
            }
        }
        /// <summary>
        /// Press stop video button
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btnStopRecord_Click(object sender, EventArgs e)
        {

            if (NETPlay.NETStopDataRecord((int)nudPlayChannelNO.Value)==false)
            {
                MessageBox.Show("Stop data flow save failure!", "Prompt:");
            }
        }
    }
}