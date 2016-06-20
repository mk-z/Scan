using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using PlaySDK;
using System.Runtime.InteropServices;
using Utility;

namespace SDKPlayDemo
{
    public partial class frmDisplayRegion : Form
    {
        /// <summary>
        /// Player channel number
        /// </summary>
        public int DisplayRegionPort = 0;
        /// <summary>
        /// Display area number
        /// </summary>
        public UInt32 RegionSN = 1;

        
        public frmDisplayRegion()
        {
            InitializeComponent();
        }

        private void frmDisplayRegion_Load(object sender, EventArgs e)
        {
            StringUtil.InitControlText(this);
        }
        /// <summary>
        /// Display the button press processing
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btnDisplay_Click(object sender, EventArgs e)
        {
            //Here need to figure out whether the text box input of pure integer numbers

            Rectangle pRectangle = new Rectangle((int)nudLeft.Value, (int)nudTop.Value, (int)(nudRight.Value - nudLeft.Value), (int)(nudBottom.Value - nudTop.Value));
            IntPtr pBoxInfo = IntPtr.Zero;
            pBoxInfo = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(Rectangle)));//Allocate the fixed specified size of memory space
            if (pBoxInfo != IntPtr.Zero)
            {
                Marshal.StructureToPtr(pRectangle, pBoxInfo, true); 
            }
            NETPlay.NETSetDisplayRegion(DisplayRegionPort, RegionSN, pBoxInfo, this.picDisplayMain.Handle, true);
        }
        /// <summary>
        /// Refresh
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btnRefresh_Click(object sender, EventArgs e)
        {
            NETPlay.NETRefreshPlayEx(DisplayRegionPort, RegionSN);            
            
        }
        /// <summary>
        /// Progress to close the window
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void frmDisplayRegion_FormClosing(object sender, FormClosingEventArgs e)
        {
            //The picture can not display correctly without this operetion next time
            NETPlay.NETSetDisplayRegion(DisplayRegionPort, RegionSN, IntPtr.Zero, this.picDisplayMain.Handle, false);
        }
    }
}