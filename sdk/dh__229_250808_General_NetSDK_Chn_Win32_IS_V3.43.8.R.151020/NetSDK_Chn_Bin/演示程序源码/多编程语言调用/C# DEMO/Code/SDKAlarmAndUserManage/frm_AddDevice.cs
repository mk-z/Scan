

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
        /// confirm the button is pressed or not
        /// </summary>
        public bool blnOKEnter = false;

        public frm_AddDevice()
        {
            InitializeComponent();
        }

        /// <summary>
        /// Click if OK
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btnOK_Click(object sender, EventArgs e)
        {
            blnOKEnter = true;
            this.Close();
        }

        /// <summary>
        /// cancel the button click
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
            //language setting
            string oldAppName = Utility.StringUtil.AppName;

            Utility.StringUtil.AppName = "Common";
            Utility.StringUtil.InitControlText(this);

            Utility.StringUtil.AppName = oldAppName;
        }
    }
}