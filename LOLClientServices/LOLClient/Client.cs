using System;
using System.Collections.Generic;
using System.Text;

namespace LOLClient
{
    class Client
    {
        public string Nick { get; set; }
        public long ID { get; set; }
        public int roomNum = 0;
        public int numInRoom = 0;
        public byte champ = 0;
        public bool isReady = false;
        public byte spell1 = 6;
        public byte spell2 = 3;
    }
}
