
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using Utility;

namespace SDKDownLoadFileDemo
{
    public partial class frm_PlayBackByTimeSet : Form
    {
        public bool blnOKEnter = false;

        private DateTime tmStart;
        public DateTime StartTime
        {
            get
            {
                return tmStart;
            }
        }

        private DateTime tmEnd;
        public DateTime EndTime
        {
            get
            {
                return tmEnd;
            }
        }

        public frm_PlayBackByTimeSet()
        {
            InitializeComponent();
            
        }

        private void btnOK_Click(object sender, EventArgs e)
        {
            string strTmStart = dtpStart.Text + " " + txtTimeStart.Text;
            string strTmEnd = dtpEnd.Text + " " + txtTimeEnd.Text;

            try
            {
                tmStart = DateTime.Parse(strTmStart);
                tmEnd = DateTime.Parse(strTmEnd);
            }
            catch (System.Exception ex)
            {
                MessageUtil.ShowMsgBox(StringUtil.ConvertString("please input the correct format of the time!"));
                return;
            }

            if (tmStart >= tmEnd)
            {
                MessageUtil.ShowMsgBox(StringUtil.ConvertString("the beginning date is not before the ending time!"));
                return;
            }

            blnOKEnter = true;
            this.Close();
        }

        private void btnCancel_Click(object sender, EventArgs e)
        {
            blnOKEnter = false;
            this.Close();
        }

        private void frm_PlayBackByTimeSet_Load(object sender, EventArgs e)
        {
            //for(int i =1;i<=8;i++)
            //{
            //    cmbChannelSelect.Items.Add(i.ToString());
            //}
            cmbChannelSelect.SelectedIndex = 0;
            dtpStart.Value = DateTime.Now.AddDays(-7);

            Utility.StringUtil.InitControlText(this);
        }

        private void cmbChannelSelect_SelectedIndexChanged(object sender, EventArgs e)
        {
            txtChannelID.Text = cmbChannelSelect.SelectedIndex.ToString();
        }
    }
}