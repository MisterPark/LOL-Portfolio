using System;
using System.Collections.Generic;
using System.Text;

namespace LOLClient
{
    class RingBuffer
    {
        const int DefaltSize = 20240;

        public byte[] buffer { get; private set; }
        public int size { get; private set; }
        public int front { get; private set; }
        public int rear { get; private set; }

        public RingBuffer(int bufferSize = DefaltSize)
        {
            Init(bufferSize);
        }

        void Init(int bufferSize = DefaltSize)
        {
            buffer = new byte[bufferSize];
            size = bufferSize;
            front = 0;
            rear = 0;
        }

        public bool isEmpty()
        {
            return (front == rear);
        }

        public int BufferSize()
        {
            return size;
        }

        public int UseSize()
        {
            if (front > rear)
            {
                return (size - (front - rear));
            }
            return (rear - front);
        }

        public int FreeSize()
        {
            int ret = (size - 1) - UseSize();
            return ret;
        }

        public int DequeSize()
        {
            int deq = size - front;
            int use = UseSize();

            if (use > deq)
            {
                return deq;
            }

            return use;
        }

        public int EnqueSize()
        {
            int enq = size - rear;
            int free = FreeSize();

            if (free > enq)
            {
                return enq;
            }

            return free;
        }

        public int Enqueue(byte[] data, int length)
        {
            if (length <= 0) return 0;

            int enqSize = length;
            int free = FreeSize();
            int part = EnqueSize();


            if (free < enqSize)
            {
                enqSize = free;
            }

            if (enqSize > part)
            {
                Buffer.BlockCopy(data, 0, buffer, rear, part);
                Buffer.BlockCopy(data, part, buffer, 0, enqSize - part);
            }
            else
            {
                Buffer.BlockCopy(data, 0, buffer, rear, enqSize);
            }

            MoveRear(enqSize);

            return enqSize;
        }

        public int Dequeue(ref byte[] dest, int length)
        {
            if (length <= 0) return 0;

            int deqSize = length;
            int use = UseSize();
            int part = DequeSize();

            if (use < length)
            {
                deqSize = use;
            }

            if (deqSize > part)
            {
                Buffer.BlockCopy(buffer, front, dest, 0, part);
                Buffer.BlockCopy(buffer, 0, dest, part, deqSize - part);
            }
            else
            {
                Buffer.BlockCopy(buffer, front, dest, 0, deqSize);
            }

            MoveFront(deqSize);

            return deqSize;
        }

        public int Peek(ref byte[] dest, int length)
        {
            if (length <= 0) return 0;

            int deqSize = length;
            int use = UseSize();
            int part = DequeSize();

            if (use < length)
            {
                deqSize = use;
            }

            if (deqSize > part)
            {
                Buffer.BlockCopy(buffer, front, dest, 0, part);
                Buffer.BlockCopy(buffer, 0, dest, part, deqSize - part);
            }
            else
            {
                Buffer.BlockCopy(buffer, front, dest, 0, deqSize);
            }

            return deqSize;
        }

        public void MoveRear(int length)
        {
            int ret = rear += length;
            rear = ret % size;
        }

        public void MoveFront(int length)
        {
            int ret = front += length;
            front = ret % size;
        }
    }
}
