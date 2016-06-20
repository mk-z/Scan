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
        /// confirm if the button is pressed
        /// </summary>
        public bool blnOKEnter = false;

        public frm_AddDevice()
        {
            InitializeComponent();
        }

        /// <summary>
        /// click confirm button
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btnOK_Click(object sender, EventArgs e)
        {
            blnOKEnter = true;
            this.Close();
        }

        /// <summary>
        /// click cancel button
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
            string oldAppName = Utility.StringUtil.AppName;

            Utility.StringUtil.AppName = "Common";
            Utility.StringUtil.InitControlText(this);

            Utility.StringUtil.AppName = oldAppName;
        }

        private void cmbDevIP_SelectedIndexChanged(object sender, EventArgs e)
        {

        }
    }
}