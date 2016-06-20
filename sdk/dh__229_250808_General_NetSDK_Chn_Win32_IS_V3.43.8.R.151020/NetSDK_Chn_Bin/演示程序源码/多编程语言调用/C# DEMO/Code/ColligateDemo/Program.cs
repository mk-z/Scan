using System;
using System.Collections.Generic;
using System.Windows.Forms;

namespace ColligateDemo
{
    static class Program
    {
        /// <summary>
        /// Application main entrance
        /// </summary>
        [STAThread]
        static void Main()
        {
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            Application.Run(new frm_Main());
        }
    }
}