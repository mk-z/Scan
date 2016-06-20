
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using NetSDK;                     
using System.Runtime.InteropServices;

namespace NetSDKSample
{
    public partial class frm_PlayBackByFileSet : Form
    {

        /// <summary>
        /// User login ID
        /// </summary>
        public int gLoginID;

        /// <summary>
        /// Selected file info
        /// </summary>
        public NET_RECORDFILE_INFO gFileInfo;

        /// <summary>
        /// Search result of file info
        /// </summary>
        private NET_RECORDFILE_INFO[] nriFileInfo;

        /// <summary>
        /// The max search file number
        /// </summary>
        private const int intFilesMaxCount = 50;

        /// <summary>
        /// If the Confirm Button is pressed.
        /// </summary>
        public bool blnOKEnter = false;

        /// <summary>
        /// Remind Message Title
        /// </summary>
        private const string strMsgTitle = "Network SDK Demo Procedure";

        public frm_PlayBackByFileSet()
        {
            InitializeComponent();
        
        }

        private void frm_PlayBackByFileSet_Load(object sender, EventArgs e)
        {
            //Channel seletion list
            //for (int i = 1; i <= 8; i++)
            //{
            //    cmbChannelSelect.Items.Add(i.ToString());
            //}
            //Default option
            cmbChannelSelect.SelectedIndex = 0;
            //Recorder file type default option 
            cmbRecordFileTypeSelect.SelectedIndex = 0;
            //OK button is not pressed.
            blnOKEnter = false;
            btnOK.Enabled = false;
            //Start period is one week before now.
            dtpStart.Value = DateTime.Now.AddDays(-7);
            ////Start period is one month before now.
            //dtpStart.Value = DateTime.Now.AddMonths(-1);

            Utility.StringUtil.InitControlText(this);
        }

        /// <summary>
        /// Channel Select
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void cmbChannelSelect_SelectedIndexChanged(object sender, EventArgs e)
        {
            txtChannelID.Text = cmbChannelSelect.SelectedIndex.ToString();
        }

        /// <summary>
        /// Click Search Button
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btnQuery_Click(object sender, EventArgs e)
        {
            #region << Screen Operation>>
            int channelID = 0;
            RECORD_FILE_TYPE rfType = RECORD_FILE_TYPE.ALLRECORDFILE;
            if (txtChannelID.Text.Trim().Length == 0)
            {
                MessageBox.Show("Please type in the channel#!", strMsgTitle);
                return;
            }
            else
            {
                channelID = int.Parse(txtChannelID.Text);
            }
            if (txtDevName.Text.Trim().Length == 0)
            {
                MessageBox.Show("Please type in the device name!", strMsgTitle);
                return;
            }
            if (cmbChannelSelect.SelectedIndex == -1)
            {
                MessageBox.Show("Please select the file type!", strMsgTitle);
                return;
            }
            else
            {
                switch (cmbRecordFileTypeSelect.SelectedIndex)
                {
                    case 0:
                        rfType = RECORD_FILE_TYPE.ALLRECORDFILE;
                        break;
                    case 1:
                        rfType = RECORD_FILE_TYPE.OUTALARM;
                        break;
                    case 2:
                        rfType = RECORD_FILE_TYPE.DYNAMICSCANALARM;
                        break;
                    case 3:
                        rfType = RECORD_FILE_TYPE.ALLALARM;
                        break;
                    case 4:
                        rfType = RECORD_FILE_TYPE.CARDNOSEACH;
                        break;
                    case 5:
                        rfType = RECORD_FILE_TYPE.COMBINEDSEACH;
                        break;

                }
            }
            DateTime tmStart = dtpStart.Value;
            DateTime tmEnd = dtpEnd.Value;
            string[] strTemp = txtTimeStart.Text.ToString().Split(':');
            if (3 == strTemp.Length)
            {
                tmStart = tmStart.AddHours(double.Parse(strTemp[0]));
                tmStart = tmStart.AddMinutes(double.Parse(strTemp[1]));
                tmStart = tmStart.AddSeconds(double.Parse(strTemp[2]));
            }
            string[] strTempEnd = txtTimeEnd.Text.ToString().Split(':');
            if (3 == strTempEnd.Length)
            {
                tmEnd = tmEnd.AddHours(double.Parse(strTempEnd[0]));
                tmEnd = tmEnd.AddMinutes(double.Parse(strTempEnd[1]));
                tmEnd = tmEnd.AddSeconds(double.Parse(strTempEnd[2]));
            }

            if (tmStart >= tmEnd)
            {
                MessageBox.Show("Start period is not before the end period!", strMsgTitle);
                return;
            }

            #endregion

            #region << Search Operation >>

            nriFileInfo = new NET_RECORDFILE_INFO[intFilesMaxCount];
            string strTimeFormatStyle = "yyyy year mm month dd day hh:MM:ss";//Date time format character, detailed definition please refer to ToSting instruction of NET_TIME struct.
            int intFileCount = 0;
            bool blnQueryRecordFile = false;
            //Search Recoder
            blnQueryRecordFile = NETClient.NETQueryRecordFile(gLoginID, channelID, rfType, tmStart, tmEnd, null, ref nriFileInfo, intFilesMaxCount * Marshal.SizeOf(typeof(NET_RECORDFILE_INFO)), out intFileCount, 5000, false);            
            if (blnQueryRecordFile == true)
            {
                lsvFiles.Items.Clear();
                ListViewItem lvi;
                for (int i = 0; i < intFileCount; i++)
                {
                    lvi = new ListViewItem();
                    lvi.SubItems[0].Text = txtDevName.Text + nriFileInfo[i].ch.ToString();
                    lvi.SubItems.Add(nriFileInfo[i].starttime.ToString(strTimeFormatStyle));
                    lvi.SubItems.Add(nriFileInfo[i].endtime.ToString(strTimeFormatStyle));
                    lvi.SubItems.Add(nriFileInfo[i].size.ToString());
                    lsvFiles.Items.Add(lvi);
                }
                return;
            }
            else
            {
                btnOK.Enabled = false;
            }
            return;
            #endregion

        }

        /// <summary>
        /// File info list selection
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void lsvFiles_ItemSelectionChanged(object sender, ListViewItemSelectionChangedEventArgs e)
        {
            if (e.ItemIndex != -1)
            {
                btnOK.Enabled = true;
                gFileInfo = nriFileInfo[e.ItemIndex];
            }
            else
            {
                btnOK.Enabled = false;
            }
        }
        
        /// <summary>
        /// Click Confirm Button
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btnOK_Click(object sender, EventArgs e)
        {
            blnOKEnter = true;
            gFileInfo = nriFileInfo[lsvFiles.SelectedItems[0].Index];
            this.Close();
        }

        /// <summary>
        /// Click Cancel Button
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btnCancel_Click(object sender, EventArgs e)
        {
            blnOKEnter = false;
            this.Close();
        }
    }
}