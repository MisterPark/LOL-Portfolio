using System;
using System.Collections.Generic;
using System.Text;
using System.Net;
using System.Net.Sockets;

namespace LOLClientServices
{
    public class NetworkProcessor
    {
        // 네트워크
        Socket socket;
        IPAddress serverIP;
        IPEndPoint endPoint;
        int port;

        public bool isSetServer { get; private set; }
        public bool isConnected { get; private set; }

        RingBuffer recvQ;
        PacketPool packetPool;

        // 콜백
        public delegate void OnConnect();
        public OnConnect OnConnectCallback;
        public delegate void OnReceive(Packet packet);
        public OnReceive OnReceiveCallback;
        public delegate void OnSend();
        public OnSend OnSendCallback;
        public delegate void OnDisconnect();
        public OnDisconnect OnDisconnectCallback;

        public NetworkProcessor()
        {
            recvQ = new RingBuffer();
            packetPool = new PacketPool();
        }
        public NetworkProcessor(string ipAddress, int appPort)
        {
            Init(ipAddress, appPort);
        }
        ~NetworkProcessor()
        {
            socket.Close();
        }

        public void SetServer(string ipAddr, int appPort)
        {
            serverIP = IPAddress.Parse(ipAddr);
            port = appPort;
            isConnected = false;
            isSetServer = true;
        }
        private void Init(string ipAddress, int appPort)
        {
            recvQ = new RingBuffer();
            packetPool = new PacketPool();
            SetServer(ipAddress, appPort);
        }

        public void Connect()
        {
            if (!isSetServer) return;
            // 비동기이기 때문에 커넥트 시도 후
            // 완료 통지가 오기 전에 다시 커넥트하는 경우가 발생
            // 때문에 일단 isConnected를 true로 바꿔주고
            // 성공하면 true, 실패하면 false로 바꿔줘서 재연결을 유도한다.
            isConnected = true;

            endPoint = new IPEndPoint(serverIP, port);
            socket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
            //Debug.Log("소켓생성");
            SocketAsyncEventArgs connEvnetArg = new SocketAsyncEventArgs();
            connEvnetArg.RemoteEndPoint = endPoint;
            connEvnetArg.Completed += new System.EventHandler<SocketAsyncEventArgs>(Connect_Completed);
            //Debug.Log("커넥 직전");
            socket.ConnectAsync(connEvnetArg);
        }

        void ProcessReceive(SocketAsyncEventArgs e)
        {
            if (e.SocketError == SocketError.Success)
            {
                recvQ.Enqueue(e.Buffer, e.BytesTransferred);

                Packet pack = packetPool.Alloc();
                NetHeader header;
                int qSize;

                while (true)
                {
                    pack.Clear();
                    qSize = recvQ.UseSize();
                    if (qSize < Protocol.SizeOfNetHeader)
                    {
                        //Debug.Log("NetworkProcessor : ProcessRecv() : 헤더 크기 보다 적은 패킷");
                        break;
                    }
                    //Debug.Log("뭔가받음");
                    recvQ.Peek(ref pack.buffer, Protocol.SizeOfNetHeader);
                    pack.GetHeader(out header);
                    if (qSize < Protocol.SizeOfNetHeader + header.length)
                    {
                        //Debug.Log("NetworkProcessor : ProcessRecv() : 패킷 전체 보다 적은 패킷");
                        break;
                    }

                    recvQ.Dequeue(ref pack.buffer, Protocol.SizeOfNetHeader + header.length);
                    pack.MoveWritePos(header.length);

                    if (!pack.Decryption(header))
                    {
                        Debug.Log("복호화 실패");
                        //Disconnect();
                        break;
                    }

                    Packet packet = new Packet(pack);
                    // 리시브 콜백
                    if (OnReceiveCallback != null)
                    {
                        OnReceiveCallback.Invoke(packet);
                    }
                }
                packetPool.Free(pack);

                SocketAsyncEventArgs args = new SocketAsyncEventArgs();
                args.SetBuffer(new byte[1024], 0, 1024);
                args.Completed += IO_Completed;
                bool pending = socket.ReceiveAsync(args);
                //Debug.Log("리시브 걸음");
                if (!pending)
                {
                    ProcessReceive(args);
                }
            }
            else
            {
                Disconnect();
            }

        }

        void ProcessSend(SocketAsyncEventArgs e)
        {
            if (OnSendCallback != null)
                OnSendCallback.Invoke();
        }

        public void SendPacket(Packet packet)
        {
            SocketAsyncEventArgs sendEventArg = new SocketAsyncEventArgs();

            packet.Encryption();
            sendEventArg.SetBuffer(packet.buffer, 0, packet.GetDataSize());
            sendEventArg.Completed += IO_Completed;
            socket.SendAsync(sendEventArg);
        }

        public void Disconnect()
        {
            //Debug.Log("서버와의 연결을 끊습니다.");

            if (OnDisconnectCallback != null)
            {
                OnDisconnectCallback.Invoke();
            }
            if (socket != null)
                socket.Close();
            isConnected = false;

        }

        void Connect_Completed(object sender, SocketAsyncEventArgs e)
        {
            if (e.SocketError == SocketError.Success)
            {
                //Debug.Log("Connect 성공");
                isConnected = true;
                SocketAsyncEventArgs recvEvnetArg = new SocketAsyncEventArgs();
                recvEvnetArg.SetBuffer(new byte[1024], 0, 1024);
                recvEvnetArg.Completed += IO_Completed;
                socket.ReceiveAsync(recvEvnetArg);

                // 커넥트 콜백
                if (OnConnectCallback != null)
                    OnConnectCallback.Invoke();

            }
            else
            {
                Debug.Log("Connect 실패");
                Debug.Log(e.SocketError.ToString());
                isConnected = false;
            }
        }

        void IO_Completed(object sender, SocketAsyncEventArgs e)
        {
            switch (e.LastOperation)
            {
                case SocketAsyncOperation.Receive:
                    ProcessReceive(e);
                    break;
                case SocketAsyncOperation.Send:
                    ProcessSend(e);
                    break;
                default:
                    throw new ArgumentException("The last operation completed on the socket was not a receive or send");
            }
        }
    }

}
