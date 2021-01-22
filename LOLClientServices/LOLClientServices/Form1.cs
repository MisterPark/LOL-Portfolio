using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.Diagnostics;

namespace LOLClientServices
{
    public partial class Form1 : Form
    {
        //=======================================
        // 네트워크 관련
        //=======================================
        NetworkProcessor net;
        Queue<Packet> packQ;
        Client user;
        Timer timer;

        public Form1()
        {
            InitializeComponent();

            user = new Client();
            packQ = new Queue<Packet>();

            timer = new Timer();
            timer.Interval = 20;
            timer.Enabled = true;
            timer.Tick += Tick;

            timer.Start();

            TextParser parser = new TextParser("setting.ini");
            //net = new NetworkProcessor("1.236.172.67", 1222);
            net = new NetworkProcessor(parser.ip, 1222);
            net.OnConnectCallback += OnConnected;
            net.OnReceiveCallback += OnReceiveMsg;
            net.OnDisconnectCallback += OnDisconnected;

            net.Connect();
        }

        ~Form1()
        {
            timer.Stop();
            net.Disconnect();
        }

        void Tick(object sender, EventArgs e)
        {
            if(packQ.Count > 0)
            {
                Packet packet = packQ.Dequeue();
                ushort type;

                packet.Pop(out type);

                ProcessPacket((MsgType)type, packet);
            }
            
        }

        void ProcessPacket(MsgType type, Packet pack)
        {
            switch (type)
            {
                case MsgType.GAME_RES_NICK:
                    ResponseNick(pack);
                    break;
                default:
                    break;
            }
        }

        //==================================================
        // 응답
        //==================================================
        void ResponseNick(Packet packet)
        {
            byte status;
            string nick;

            packet.PopWithoutNull(out nick, 40);
            packet.Pop(out status);
            LoginResult result = (LoginResult)status;
            switch (result)
            {
                case LoginResult.SUCCEED:
                    label1.ForeColor = Color.Green;
                    label1.Text = "로그인 완료";
                    Process.Start(Application.StartupPath + "\\LOLClient.exe",nick);
                    Application.Exit();
                    break;
                case LoginResult.ID_DOES_NOT_EXIST:
                    label1.ForeColor = Color.Red;
                    label1.Text = "존재하지 않는 아이디";
                    break;
                case LoginResult.PASSWORD_DOES_NOT_MATCH:
                    label1.ForeColor = Color.Red;
                    label1.Text = "일치하지 않는 비밀번호";
                    break;
                case LoginResult.ID_ALREADY_LOGGED_IN:
                    label1.ForeColor = Color.Red;
                    label1.Text = "이미 접속중인 닉네임";
                    break;
                case LoginResult.SPECIAL_CHARACTER:
                    label1.ForeColor = Color.Red;
                    label1.Text = "특수문자 사용금지";
                    break;
                default:
                    label1.ForeColor = Color.Red;
                    label1.Text = "로그인 실패";
                    break;
            }
            
        }


        //==================================================
        // 요청
        //==================================================

        void RequestNick(string nick)
        {
            Packet packet = new Packet();
            packet.Push((ushort)MsgType.GAME_REQ_NICK);
            packet.Push(nick, 40);

            net.SendPacket(packet);
        }

        //=======================================
        // 콜백
        //=======================================

        void OnConnected()
        {
            if(net.isConnected == false)
            {
                net.Connect();
            }
        }

        void OnReceiveMsg(Packet packet)
        {
            packQ.Enqueue(packet);
        }

        void OnDisconnected()
        {
            Debug.Log("서버에 의해 연결이 종료되었습니다.");
            
            Application.Exit();
        }

        private void pictureBox2_MouseHover(object sender, EventArgs e)
        {
            pictureBox2.Image = Properties.Resources.exitButton;
            
        }

        private void pictureBox2_MouseClick(object sender, MouseEventArgs e)
        {
            Application.Exit();
        }

        private void pictureBox2_MouseLeave(object sender, EventArgs e)
        {
            pictureBox2.Image = Properties.Resources.exitButton1;
        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {
            if(textBox1.Text == string.Empty)
            {
                pictureBox3.Image = Properties.Resources.loginButton1;
            }
            else
            {
                pictureBox3.Image = Properties.Resources.loginButton;
            }
        }

        private void pictureBox3_MouseHover(object sender, EventArgs e)
        {
            if (textBox1.Text == string.Empty)
            {
                pictureBox3.Image = Properties.Resources.loginButton1;
            }
            else
            {
                pictureBox3.Image = Properties.Resources.loginButton2;
            }
        }

        private void pictureBox3_MouseLeave(object sender, EventArgs e)
        {
            if (textBox1.Text == string.Empty)
            {
                pictureBox3.Image = Properties.Resources.loginButton1;
            }
            else
            {
                pictureBox3.Image = Properties.Resources.loginButton;
            }
        }

        private void pictureBox3_MouseClick(object sender, MouseEventArgs e)
        {
            RequestNick(textBox1.Text);
        }

        private void pictureBox3_Click(object sender, EventArgs e)
        {
            RequestNick(textBox1.Text);
        }
    }
}
