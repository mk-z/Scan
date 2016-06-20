using System;
using System.Collections.Generic;
using System.Windows.Forms;

namespace SDKCapturePicture
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
            Application.Run(new Form1());
        }
    }
}