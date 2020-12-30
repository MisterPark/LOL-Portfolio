using System;
using System.Collections.Generic;
using System.Text;
using System.Runtime.InteropServices;
using System.Windows.Forms;

namespace LOLClientServices
{
    public class Packet
    {
        public const int defaultSize = 1024;
        public static readonly int headerSize = Marshal.SizeOf(typeof(NetHeader));
        public static readonly byte FIXED_KEY = 0x32;

        public byte[] buffer;
        public int read { get; private set; } // 읽기 위치
        public int write { get; private set; } // 쓰기 위치
        public int size { get; private set; } // 총 사이즈
        public int UseSize
        {
            get { return (write - read); }
        }

        public Packet(int bufferSize = defaultSize)
        {
            Init(bufferSize);
        }

        public Packet(Packet packet)
        {
            Init(packet.size);
            Buffer.BlockCopy(packet.buffer, 0, buffer, 0, packet.size);
            write = packet.write;
            read = packet.read;
        }

        void Init(int bufferSize = defaultSize)
        {
            if (bufferSize < headerSize) bufferSize = headerSize;
            buffer = new byte[bufferSize];
            size = bufferSize;
            Clear();
        }

        public int GetFreeSize()
        {
            return (size - 1 - write);
        }

        public int GetPayloadSize()
        {
            return (write - headerSize);
        }

        public int GetDataSize()
        {
            return write;
        }

        public bool Resize(int newSize)
        {
            if (newSize <= size) return false;

            byte[] newBuffer = new byte[newSize];
            int useSize = UseSize;

            Buffer.BlockCopy(buffer, read, newBuffer, 0, useSize);

            buffer = newBuffer;

            return true;
        }

        public void Clear()
        {
            read = write = headerSize;
        }

        // 쓰기 위치 이동
        // param (bytesLength : 이동할 거리)
        // return : write
        public int MoveWritePos(int length)
        {
            if (length <= 0) return write;

            int newWrite = write + length;

            if (newWrite > size)
            {
                // 50 bytes 씩 리사이징
                newWrite = newWrite / 50;
                newWrite = (newWrite + 1) * 50;
                Resize(newWrite);
            }

            write = newWrite;

            return write;
        }

        // 읽기 위치 이동
        // param (bytesLength : 이동할 거리)
        // return : read
        public int MoveReadPos(int length)
        {
            if (length <= 0) return read;

            int newRead = read + length;

            if (newRead > size)
            {
                newRead = newRead / 50;
                newRead = (newRead + 1) * 50;
                Resize(newRead);
            }

            read = newRead;

            return read;
        }

        //====================================
        // 헤더 관련
        // ===================================
        public void SetHeader(out byte randKey)
        {
            System.Random random = new System.Random();
            int packetSize = UseSize;
            // 랜덤키 생성
            randKey = (byte)random.Next(0, 255);
            // 체크섬 구하기
            byte checksum = 0;
            for (int i = 0; i < packetSize; i++)
            {
                checksum += buffer[i + Protocol.SizeOfNetHeader];
            }

            NetHeader header;
            header.code = Protocol.PACKET_CODE;
            header.length = (ushort)packetSize;
            header.randKey = randKey;
            header.checkSum = checksum;

            buffer[0] = header.code;
            buffer[1] = (byte)(header.length & 0x00FF);
            buffer[2] = (byte)((header.length & 0xFF00) >> 8);
            buffer[3] = header.randKey;
            buffer[4] = header.checkSum;
        }

        public void GetHeader(out NetHeader header)
        {
            header.code = buffer[0];
            header.length = (ushort)(buffer[1] + (buffer[2] << 8));
            header.randKey = buffer[3];
            header.checkSum = buffer[4];
        }

        public void Encryption()
        {
            byte randKey;
            SetHeader(out randKey);

            byte temp1;
            byte temp2;

            temp1 = (byte)(buffer[4] ^ (randKey + 1));
            buffer[4] = (byte)(temp1 ^ (FIXED_KEY + 1));
            temp2 = buffer[4];

            int loopCnt = UseSize + 1;
            for (int i = 1; i < loopCnt; i++)
            {
                temp1 = (byte)(buffer[i + 4] ^ (temp1 + randKey + (i + 1)));
                buffer[i + 4] = (byte)(temp1 ^ (temp2 + FIXED_KEY + (i + 1)));
                temp2 = buffer[i + 4];
            }

        }

        public bool Decryption(NetHeader header)
        {
            if (header.code != Protocol.PACKET_CODE)
            {
                MessageBox.Show("복호화 에러: 패킷 코드 에러");
                return false;
            }

            int offset = Protocol.SizeOfNetHeader;
            int packetSize = UseSize;
            byte randKey = header.randKey;

            byte temp1;
            byte temp2;

            temp1 = (byte)(header.checkSum ^ (FIXED_KEY + 1));
            temp2 = temp1;

            byte decodeCheckSum = (byte)(temp1 ^ (byte)(randKey + 1));
            byte checkSum = 0;
            byte predata;

            temp1 = (byte)(buffer[offset] ^ (byte)(FIXED_KEY + 2 + header.checkSum));
            predata = buffer[offset];
            buffer[offset] = (byte)(temp1 ^ (byte)(temp2 + randKey + 2));
            temp2 = temp1;
            checkSum += buffer[offset];

            for (int i = 1; i < packetSize; i++)
            {
                temp1 = (byte)(buffer[offset + i] ^ (byte)(FIXED_KEY + (i + 2) + predata));
                predata = buffer[offset + i];

                buffer[offset + i] = (byte)(temp1 ^ (byte)(temp2 + randKey + (i + 2)));
                temp2 = temp1;
                checkSum += buffer[offset + i];
            }

            if (checkSum != decodeCheckSum)
            {
                MessageBox.Show("복호화 에러: 체크섬 에러 / checkSum :" + checkSum + "/ decode : " + decodeCheckSum);
                return false;
            }


            return true;
        }


        public void Push(byte data)
        {
            if (GetFreeSize() < sizeof(byte))
                Resize(size + 50);
            buffer[write] = data;
            MoveWritePos(sizeof(byte));
        }

        public void Push(short data)
        {
            if (GetFreeSize() < sizeof(short))
                Resize(size + 50);
            byte[] temp_buffer = BitConverter.GetBytes(data);
            Buffer.BlockCopy(temp_buffer, 0, buffer, write, temp_buffer.Length);
            MoveWritePos(temp_buffer.Length);
        }

        public void Push(ushort data)
        {
            if (GetFreeSize() < sizeof(ushort))
                Resize(size + 50);
            byte[] temp_buffer = BitConverter.GetBytes(data);
            Buffer.BlockCopy(temp_buffer, 0, buffer, write, temp_buffer.Length);
            MoveWritePos(temp_buffer.Length);
        }

        public void Push(int data)
        {
            if (GetFreeSize() < sizeof(int))
                Resize(size + 50);
            byte[] temp_buffer = BitConverter.GetBytes(data);
            Buffer.BlockCopy(temp_buffer, 0, buffer, write, temp_buffer.Length);
            MoveWritePos(temp_buffer.Length);
        }

        public void Push(uint data)
        {
            if (GetFreeSize() < sizeof(uint))
                Resize(size + 50);
            byte[] temp_buffer = BitConverter.GetBytes(data);
            Buffer.BlockCopy(temp_buffer, 0, buffer, write, temp_buffer.Length);
            MoveWritePos(temp_buffer.Length);
        }

        public void Push(long data)
        {
            if (GetFreeSize() < sizeof(long))
                Resize(size + 50);
            byte[] temp_buffer = BitConverter.GetBytes(data);
            Buffer.BlockCopy(temp_buffer, 0, buffer, write, temp_buffer.Length);
            MoveWritePos(temp_buffer.Length);
        }

        public void Push(ulong data)
        {
            if (GetFreeSize() < sizeof(ulong))
                Resize(size + 50);
            byte[] temp_buffer = BitConverter.GetBytes(data);
            Buffer.BlockCopy(temp_buffer, 0, buffer, write, temp_buffer.Length);
            MoveWritePos(temp_buffer.Length);
        }
        public void Push(float data)
        {
            if (GetFreeSize() < sizeof(float))
                Resize(size + 50);
            byte[] temp_buffer = BitConverter.GetBytes(data);
            Buffer.BlockCopy(temp_buffer, 0, buffer, write, temp_buffer.Length);
            MoveWritePos(temp_buffer.Length);
        }
        public void Push(double data)
        {
            if (GetFreeSize() < sizeof(double))
                Resize(size + 50);
            byte[] temp_buffer = BitConverter.GetBytes(data);
            Buffer.BlockCopy(temp_buffer, 0, buffer, write, temp_buffer.Length);
            MoveWritePos(temp_buffer.Length);
        }

        public void Push(string data)
        {
            byte[] temp_buffer = Encoding.Unicode.GetBytes(data);
            if (GetFreeSize() < temp_buffer.Length)
                Resize(size + temp_buffer.Length);
            Buffer.BlockCopy(temp_buffer, 0, buffer, write, temp_buffer.Length);
            MoveWritePos(temp_buffer.Length);
        }

        public void Push(string data, int bytesLength)
        {
            if (GetFreeSize() < data.Length)
                Resize(size + data.Length);
            byte[] temp_buffer = Encoding.Unicode.GetBytes(data);
            Buffer.BlockCopy(temp_buffer, 0, buffer, write, temp_buffer.Length);
            MoveWritePos(bytesLength);
        }

        public void Push(byte[] data, int bytesLength)
        {
            if (GetFreeSize() < bytesLength)
                Resize(size + bytesLength);
            Buffer.BlockCopy(data, 0, buffer, write, bytesLength);
            MoveWritePos(bytesLength);
        }

        public void Pop(out byte data)
        {
            data = buffer[read];
            MoveReadPos(sizeof(byte));
        }

        public void Pop(out short data)
        {
            data = BitConverter.ToInt16(buffer, read);
            MoveReadPos(sizeof(short));
        }

        public void Pop(out ushort data)
        {
            data = BitConverter.ToUInt16(buffer, read);
            MoveReadPos(sizeof(ushort));
        }
        public void Pop(out int data)
        {
            data = BitConverter.ToInt32(buffer, read);
            MoveReadPos(sizeof(int));
        }

        public void Pop(out uint data)
        {
            data = BitConverter.ToUInt32(buffer, read);
            MoveReadPos(sizeof(uint));
        }

        public void Pop(out long data)
        {
            data = BitConverter.ToInt64(buffer, read);
            MoveReadPos(sizeof(long));
        }

        public void Pop(out ulong data)
        {
            data = BitConverter.ToUInt64(buffer, read);
            MoveReadPos(sizeof(ulong));
        }
        public void Pop(out float data)
        {
            data = BitConverter.ToSingle(buffer, read);
            MoveReadPos(sizeof(float));
        }
        public void Pop(out double data)
        {
            data = BitConverter.ToDouble(buffer, read);
            MoveReadPos(sizeof(double));
        }

        public void Pop(out string data)
        {
            int length = UseSize;
            string str = Encoding.Unicode.GetString(buffer, read, length);
            data = str;
            MoveReadPos(length);

        }

        public void Pop(out byte[] data, int bytesLength)
        {
            data = new byte[bytesLength + 1];
            Buffer.BlockCopy(buffer, read, data, 0, bytesLength);
            MoveReadPos(bytesLength);
        }

        public void PopWithoutNull(out string data, int bytesLength)
        {
            // 바이트 배열로 뽑아서
            byte[] temp1 = new byte[bytesLength];
            Buffer.BlockCopy(buffer, read, temp1, 0, bytesLength);
            // 널문자 검사
            int readLen = 0;
            for (int i = 0; i < bytesLength; i += 2) // 유니코드라서 2bytes 씩 읽음 
            {
                if (temp1[i] == 0 && temp1[i + 1] == 0) // null문자면 break
                {
                    break;
                }
                readLen += 2; // 아니면 2bytes 씩 읽을 bytes 추가
            }
            string str = Encoding.Unicode.GetString(buffer, read, readLen);
            data = str;
            MoveReadPos(bytesLength);
        }
    }
}
