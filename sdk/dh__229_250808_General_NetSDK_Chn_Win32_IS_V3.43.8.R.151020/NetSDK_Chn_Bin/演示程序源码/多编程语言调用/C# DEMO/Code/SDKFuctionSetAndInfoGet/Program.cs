using System;
using System.Collections.Generic;
using System.Windows.Forms;

namespace SDKFuctionSetAndInfoGet
{
    static class Program
    {
        /// <summary>
        /// Application main entrance
        /// </summary>
        [STAThread]
        static void Main()
        {
            Utility.StringUtil.AppName = @"FunctionSetAndInfoGet";

            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            Application.Run(new frm_Main());
        }
    }
}