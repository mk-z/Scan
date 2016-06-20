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
    public partial class frm_PlayBackByFileSet : Form
    {
        /// <summary>
        /// user login ID
        /// </summary>
        public int gLoginID;

        /// <summary>
        /// file information chose
        /// </summary>
        public NET_RECORDFILE_INFO gFileInfo;

        /// <summary>
        /// the results of the file information query
        /// </summary>
        private NET_RECORDFILE_INFO[] nriFileInfo;

        /// <summary>
        /// Most query file number
        /// </summary>
        private const int intFilesMaxCount = 1024;

        /// <summary>
        /// make sure whether to press the confirming button
        /// </summary>
        public bool blnOKEnter = false;

        /// <summary>
        /// the notice header
        /// </summary>
        private const string strMsgTitle = "Network SDK Demo program";

        public frm_PlayBackByFileSet()
        {
            InitializeComponent();
        
        }

        private void frm_PlayBackByFileSet_Load(object sender, EventArgs e)
        {
            //channel selecting list
            //for (int i = 1; i <= 8; i++)
            //{
            //    cmbChannelSelect.Items.Add(i.ToString());
            //}
            //the default option
            cmbChannelSelect.SelectedIndex = 0;
            //record the default option of the type of the file
            cmbRecordFileTypeSelect.SelectedIndex = 0;
            //OK the button has not been pressed
            blnOKEnter = false;
            btnOK.Enabled = false;
            //the beginning date is a week before the current date
            dtpStart.Value = DateTime.Now.AddDays(-7);
            ////the beginning date is a month before the current date
            //dtpStart.Value = DateTime.Now.AddMonths(-1);

            StringUtil.InitControlText(this);
        }

        /// <summary>
        /// channel option
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void cmbChannelSelect_SelectedIndexChanged(object sender, EventArgs e)
        {
            txtChannelID.Text = cmbChannelSelect.SelectedIndex.ToString();
        }

        /// <summary>
        /// click the query button
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btnQuery_Click(object sender, EventArgs e)
        {
            #region << image operation >>
            int channelID = 0;
            RECORD_FILE_TYPE rfType = RECORD_FILE_TYPE.ALLRECORDFILE;
            if (txtChannelID.Text.Trim().Length == 0)
            {
                MessageUtil.ShowMsgBox(StringUtil.ConvertString("please input the channel number!"),
                                       StringUtil.ConvertString(strMsgTitle));
                return;
            }
            else
            {
                channelID = int.Parse(txtChannelID.Text);
            }
            if (txtDevName.Text.Trim().Length == 0)
            {
                MessageUtil.ShowMsgBox(StringUtil.ConvertString("please input the name of the equipment!"),
                                       StringUtil.ConvertString(strMsgTitle));
                return;
            }
            if (cmbChannelSelect.SelectedIndex == -1)
            {
                MessageUtil.ShowMsgBox(StringUtil.ConvertString("please choose the type of the file!"),
                                       StringUtil.ConvertString(strMsgTitle));
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

            string strTmStart = dtpStart.Text + " " + txtTimeStart.Text;
            string strTmEnd = dtpEnd.Text + " " + txtTimeEnd.Text;

            DateTime tmStart;
            DateTime tmEnd;

            try
            {
                tmStart = DateTime.Parse(strTmStart);
                tmEnd = DateTime.Parse(strTmEnd);
            }
            catch (System.Exception ex)
            {
                MessageUtil.ShowMsgBox(StringUtil.ConvertString("please input the correct format of time!"),
                                       StringUtil.ConvertString(strMsgTitle));
                return;
            }

            if (tmStart >= tmEnd)
            {
                MessageUtil.ShowMsgBox(StringUtil.ConvertString("the starting date is not before the ending date!"), 
                                       StringUtil.ConvertString(strMsgTitle));
                return;
            }

            #endregion

            #region << query operation >>

            nriFileInfo = new NET_RECORDFILE_INFO[intFilesMaxCount];
            string strTimeFormatStyle = "on mm dd,yyyy hh:MM:ss";// the ToSting of the structure NET_TIME gives the detailed definition of the formating characters of the date and time 
            int intFileCount = 0;
            bool blnQueryRecordFile = false;
            blnQueryRecordFile = NETClient.NETQueryRecordFile(gLoginID, channelID, rfType, tmStart, tmEnd, null, ref nriFileInfo, intFilesMaxCount * Marshal.SizeOf(typeof(NET_RECORDFILE_INFO)), out intFileCount, 5000, false);            
            if (blnQueryRecordFile == true)
            {
                lsvFiles.Items.Clear();
                if(0==intFileCount)
                {
                    MessageUtil.ShowMsgBox(StringUtil.ConvertString("no video file is available!"),
                                           StringUtil.ConvertString(strMsgTitle));
                    return;
                }

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
        /// choose the file information list 
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
        /// click the confirming button
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
        /// cancel the click of the button
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btnCancel_Click(object sender, EventArgs e)
        {
            blnOKEnter = false;
            this.Close();
        }

        private void cmbRecordFileTypeSelect_SelectedIndexChanged(object sender, EventArgs e)
        {

        }
    }
}