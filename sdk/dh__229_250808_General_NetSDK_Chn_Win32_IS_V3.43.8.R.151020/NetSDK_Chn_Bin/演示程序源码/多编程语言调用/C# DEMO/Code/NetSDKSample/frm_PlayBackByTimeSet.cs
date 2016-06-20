using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace NetSDKSample
{
    public partial class frm_PlayBackByTimeSet : Form
    {
        public int nStreamType  = 0;
        public bool blnOKEnter = false;
        public frm_PlayBackByTimeSet()
        {
            InitializeComponent();
            
        }

        private void btnOK_Click(object sender, EventArgs e)
        {
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
            cmbChannelSelect.SelectedIndex = 0;
            cmbStreamType.SelectedIndex = 0;
            dtpStart.Value = DateTime.Now.AddDays(-7);

            Utility.StringUtil.InitControlText(this);
        }

        private void cmbChannelSelect_SelectedIndexChanged(object sender, EventArgs e)
        {
            txtChannelID.Text = cmbChannelSelect.SelectedIndex.ToString();
        }

        private void cmbStreamType_SelectedIndexChanged(object sender, EventArgs e)
        {
            nStreamType = cmbStreamType.SelectedIndex;
        }
    }
}