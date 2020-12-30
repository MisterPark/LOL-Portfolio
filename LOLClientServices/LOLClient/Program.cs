using System;
using System.Collections.Generic;
using System.Windows.Forms;

namespace LOLClient
{
    static class Program
    {
        /// <summary>
        /// 해당 애플리케이션의 주 진입점입니다.
        /// </summary>
        [STAThread]
        static void Main(string[] args)
        {
            if (args.Length < 1) return;
            string nick = args[0];
            
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            Application.Run(new Form1(nick));

            
        }
    }
}
