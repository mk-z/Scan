using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace ColligateDemo
{
    public partial class frm_AddDevice : Form
    {
        /// <summary>
        /// Confirm
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
        /// Cancel
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