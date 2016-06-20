

using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace NetSDKSample
{
    public partial class frm_AddDevice : Form
    {
        /// <summary>
        /// Confirm button on
        /// </summary>
        public bool blnOKEnter = false;

        public frm_AddDevice()
        {
            InitializeComponent();
        }

        /// <summary>
        /// Comfirm button clicked 
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btnOK_Click(object sender, EventArgs e)
        {
            blnOKEnter = true;
            this.Close();
        }

        /// <summary>
        /// Cancel clicking button
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btnCancel_Click(object sender, EventArgs e)
        {
            blnOKEnter = false;
            this.Close();
        }

        private void frm_AddDevice_Load(object sender, EventArgs e)
        {
            //Language Setup
            string oldAppName = Utility.StringUtil.AppName;

            Utility.StringUtil.AppName = "Common";
            Utility.StringUtil.InitControlText(this);

            Utility.StringUtil.AppName = oldAppName;
        }

    }
}