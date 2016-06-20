using System;
using System.Collections.Generic;
using System.Windows.Forms;

namespace NetSDKSample
{
    static class Program
    {
        /// <summary>
        /// Application main point
        /// </summary>
        [STAThread]
        static void Main()
        {
            Utility.StringUtil.AppName = @"NetSDKSample";

            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            Application.Run(new frm_MainC());
        }
    }
}