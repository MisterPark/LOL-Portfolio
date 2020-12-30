using System;
using System.Collections.Generic;
using System.Text;

namespace LOLClient
{
    public class PacketPool
    {
        // Stack 안쓰고 Queue쓴 이유 : lock걸기 싫음
        Queue<Packet> packets;
        const int chunkSize = 50;
        public int Count
        {
            get { return packets.Count; }
        }

        public PacketPool(int packetCount = chunkSize)
        {
            packets = new Queue<Packet>(packetCount);
        }

        public void Free(Packet pack)
        {
            if (pack == null) return;
            pack.Clear();
            packets.Enqueue(pack);
        }

        public Packet Alloc()
        {
            if (packets.Count == 0)
            {
                Packet pack;
                for (int i = 0; i < chunkSize; i++)
                {
                    pack = new Packet();
                    packets.Enqueue(pack);
                }
            }
            return packets.Dequeue();
        }


    }

}
