using System;
using System.Collections.Generic;
using System.Text;
using System.IO;

namespace LOLClient
{
    class TextParser
    {
        string path;
        public string ip;

        public TextParser(string path)
        {
            StreamReader sr = new StreamReader(path);
            ip = sr.ReadLine();
            sr.Close();
        }

    }
}
