using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using NetSDK;

namespace NetSDKSample
{
    public partial class frm_PTZControl : Form
    {
        /// <summary>
        /// User login ID
        /// </summary>
        public int LoginID=0;

        private bool blnLam = true;
        public frm_PTZControl()
        {
            InitializeComponent();
        }
        /// <summary>
        ///  Set perset position handling
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btnSetPoint_Click(object sender, EventArgs e)
        {
            if (NETClient.NETPTZControl(LoginID, (int)nudChannel.Value, PTZ_CONTROL.PTZ_POINT_SET_CONTROL, (ushort)nudPointNO.Value/*perset value*/, false))
            { 

            }
            else
            {
                MessageBox.Show("PTZ Control: Setting perset position failed!", "Warning");
            }
        }
        /// <summary>
        /// Screen loading handling
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void frm_PTZControl_Load(object sender, EventArgs e)
        {
            Utility.StringUtil.InitControlText(this);

            if (LoginID == 0)
            {
                MessageBox.Show("Please login the device.","Warning");
                this.Close();
            }
        }
        /// <summary>
        /// Diversion perset position handling
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btnGotoPoint_Click(object sender, EventArgs e)
        {
            if (NETClient.NETPTZControl(LoginID, (int)nudChannel.Value, PTZ_CONTROL.PTZ_POINT_MOVE_CONTROL, (ushort)nudPointNO.Value/*perset value*/, false))
            {

            }
            else
            {
                MessageBox.Show("PTZ Control: Diversion perset position failed!", "Warning");
            }
        }
        /// <summary>
        /// Delete perset position handling
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btnDelPoint_Click(object sender, EventArgs e)
        {
            if (NETClient.NETPTZControl(LoginID, (int)nudChannel.Value, PTZ_CONTROL.PTZ_POINT_DEL_CONTROL, (ushort)nudPointNO.Value/*perset value*/, false))
            {

            }
            else
            {
                MessageBox.Show("PTZ Control: Deleting perset position failed!", "Warning");
            }
        }
        /// <summary>
        /// windshield wiper on/off handling
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btnLamControl_Click(object sender, EventArgs e)
        {
            if (NETClient.NETPTZControl(LoginID, (int)nudChannel.Value, PTZ_CONTROL.PTZ_LAMP_CONTROL, (ushort)(blnLam == true ? 1 : 0), false))
            {
                blnLam = !blnLam;
            }
            else
            {
                MessageBox.Show("PTZ Control: Windshield wiper function failed!", "Warning");
            }
        }
    }
}