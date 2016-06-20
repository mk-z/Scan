using System;
using System.Collections.Generic;
using System.Windows.Forms;

namespace SDKPlayDemo
{
    static class Program
    {
        /// <summary>
        /// The main entry point for the application program.
        /// </summary>
        [STAThread]
        static void Main()
        {
            Utility.StringUtil.AppName = @"SDKPlay";

            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            Application.Run(new frm_Main());
        }
    }
}