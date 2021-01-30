using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.Diagnostics;

namespace LOLClient
{
    public partial class Form1 : Form
    {
        NetworkProcessor net;
        Queue<Packet> packQ;
        Timer timer;
        bool wait = false;
        DateTime oldTime;
        DateTime curTime;
        Client client;

        Color brightGold = Color.FromArgb(240, 230, 210);
        Color gold = Color.FromArgb(205, 190, 145);
        Color gray = Color.FromArgb(30, 35, 40);

        Label[] names = new Label[10];
        PictureBox[] champButton = new PictureBox[10];
        PictureBox[] userChamp = new PictureBox[10];
        Image[] champCircleImage = new Image[10];
        Image[] spellImage = new Image[10];
        public Form1(string nick)
        {
            InitializeComponent();
            names[0] = label_Name1;
            names[1] = label_Name2;
            names[2] = label_Name3;
            names[3] = label_Name4;
            names[4] = label_Name5;
            names[5] = label_Name6;
            names[6] = label_Name7;
            names[7] = label_Name8;
            names[8] = label_Name9;
            names[9] = label_Name10;
            
            champButton[0] = button_garen;
            champButton[1] = button_darius;
            champButton[2] = button_diana;
            champButton[3] = button_leona;
            champButton[4] = button_leesin;
            champButton[5] = button_missfortune;
            champButton[6] = button_blitzcrank;
            champButton[7] = button_ahri;
            champButton[8] = button_jax;
            champButton[9] = button_jinx;

            userChamp[0] = face1;
            userChamp[1] = face2;
            userChamp[2] = face3;
            userChamp[3] = face4;
            userChamp[4] = face5;
            userChamp[5] = face6;
            userChamp[6] = face7;
            userChamp[7] = face8;
            userChamp[8] = face9;
            userChamp[9] = face10;

            champCircleImage[0] = Properties.Resources.garen_circle;
            champCircleImage[1] = Properties.Resources.darius_circle_0;
            champCircleImage[2] = Properties.Resources.diana_circle_0;
            champCircleImage[3] = Properties.Resources.leona_circle;
            champCircleImage[4] = Properties.Resources.leesin_circle;
            champCircleImage[5] = Properties.Resources.missfortune_circle_0;
            champCircleImage[6] = Properties.Resources.steamgolem_circle;
            champCircleImage[7] = Properties.Resources.ahri_circle;
            champCircleImage[8] = Properties.Resources.jax_circle;
            champCircleImage[9] = Properties.Resources.jinx_circle;

            spellImage[0] = Properties.Resources.summoner_barrier;
            spellImage[1] = Properties.Resources.summoner_boost;
            spellImage[2] = Properties.Resources.summoner_exhaust;
            spellImage[3] = Properties.Resources.summoner_flash;
            spellImage[4] = Properties.Resources.summoner_haste;
            spellImage[5] = Properties.Resources.summoner_heal;
            spellImage[6] = Properties.Resources.summoner_ignite;
            spellImage[7] = Properties.Resources.summoner_mana;
            spellImage[8] = Properties.Resources.summoner_smite;
            spellImage[9] = Properties.Resources.summoner_teleport;

            oldTime = DateTime.Now;

            client = new Client();

            //label4.Text = nick;

            client.Nick = nick;

            panel1.Visible = true;
            panel2.Visible = false;

            button_Ready.Enabled = false;
            button_spell1.Image = spellImage[6];
            button_spell2.Image = spellImage[3];
            // 패킷 큐
            packQ = new Queue<Packet>();
            // 타이머
            timer = new Timer();
            timer.Interval = 20;
            timer.Enabled = true;
            timer.Tick += Tick;

            timer.Start();
            // 네트워크
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
            if(wait == true)
            {
                curTime = DateTime.Now;
                TimeSpan elapsed = curTime - oldTime;

                label_waitTime.Text = elapsed.Minutes.ToString() + ":" + elapsed.Seconds.ToString();
            }

            if (packQ.Count > 0)
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
                case MsgType.GAME_RES_LOGIN:
                    ResponseLogin(pack);
                    break;
                case MsgType.GAME_RES_JOIN_GAME:
                    ResponseJoinGame(pack);
                    break;
                case MsgType.GAME_RES_SELECT_CHAMP:
                    ResponseSelectChamp(pack);
                    break;
                case MsgType.GAME_RES_READY:
                    ResponseReady(pack);
                    break;
                case MsgType.GAME_RES_START:
                    ResponseStart(pack);
                    break;
                default:
                    break;
            }
        }


        //=======================================
        // 콜백
        //=======================================
        void OnConnected()
        {
            if (net.isConnected == false)
            {
                net.Connect();
            }
            else
            {
                // 연결되면
                // 연결되자마자 로그인 패킷 보내야함
                RequestLogin(client.Nick);
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

        // 요청
        void RequestLogin(string nick)
        {
            Packet packet = new Packet();
            packet.Push((ushort)MsgType.GAME_REQ_LOGIN);
            packet.Push(nick, 40);

            net.SendPacket(packet);
        }

        void RequestJoinGame()
        {
            Packet pack = new Packet();
            pack.Push((ushort)MsgType.GAME_REQ_JOIN_GAME);

            net.SendPacket(pack);
        }

        void RequestSelectChamp(byte numChamp)
        {
            Packet pack = new Packet();
            pack.Push((ushort)MsgType.GAME_REQ_SELECT_CHAMP);
            pack.Push(numChamp);

            net.SendPacket(pack);
        }

        void RequestReady()
        {
            Packet pack = new Packet();
            pack.Push((ushort)MsgType.GAME_REQ_READY);
            pack.Push((int)client.spell1);
            pack.Push((int)client.spell2);

            net.SendPacket(pack);
        }

        // 응답

        void ResponseLogin(Packet packet)
        {
            string nick;
            long id;
            byte status;

            packet.PopWithoutNull(out nick, 40);
            packet.Pop(out id);
            packet.Pop(out status);
            LoginResult result = (LoginResult)status;
            if(result != LoginResult.SUCCEED)
            {
                Application.Exit();
                return;
            }

            client.Nick = nick;
            client.ID = id;

            label4.Text = client.Nick;
        }

        void ResponseJoinGame(Packet pack)
        {
            panel1.Visible = false;
            panel2.Visible = true;

            string nick;
            int number;
            uint count;

            pack.Pop(out count);

            for (int i = 0; i < count; i++)
            {
                pack.PopWithoutNull(out nick, 40);
                pack.Pop(out number);

                names[number].Text = nick;
                if(nick == client.Nick)
                {
                    client.numInRoom = number;
                }
            }

        }

        void ResponseSelectChamp(Packet pack)
        {
            uint userNum;
            byte champ;

            pack.Pop(out userNum);
            pack.Pop(out champ);

            userChamp[userNum].Image = champCircleImage[champ];
            client.champ = champ;

            if(userNum == client.numInRoom)
            {
                button_Ready.Enabled = true;
            }
        }

        void ResponseReady(Packet pack)
        {
            client.isReady = true;
        }

        void ResponseStart(Packet pack)
        {

            Process.Start(Application.StartupPath + "\\LeagueOfLegends.exe", client.Nick);
            Application.Exit();
        }

        private void pictureBox2_MouseClick(object sender, MouseEventArgs e)
        {
            // 닫기버튼
            Application.Exit();
        }


        private void button_CreateRoom_Click_1(object sender, EventArgs e)
        {
            // 게임 시작 버튼 ( 대기열에 넣어야함)
            // 대기 시간 세팅
            wait = true;
            oldTime = DateTime.Now;
            button_CreateRoom.Enabled = false;

            RequestJoinGame();

            //panel1.Visible = false;
            //panel2.Visible = true;
        }

        private void button_Ready_EnabledChanged(object sender, EventArgs e)
        {
            if(button_Ready.Enabled)
            {
                button_Ready.Image = Properties.Resources.readyButton2_03;
            }
            else
            {
                button_Ready.Image = Properties.Resources.readyButton_03;
            }
        }

        private void button_Ready_Click(object sender, EventArgs e)
        {
            // 준비 완료 버튼
            // 준비 완료 패킷 보내고
            // Enabled = false

            button_Ready.Enabled = false;
            RequestReady();
        }

        private void button_spell1_Click(object sender, EventArgs e)
        {
            // 스펠1

            int spellIndex = 0;
            int spell2Index = 0;

            for(int i=0;i<10;i++)
            {
                if (button_spell1.Image == spellImage[i])
                {
                    spellIndex = i;
                    break;
                }
            }

            for (int i = 0; i < 10; i++)
            {
                if (button_spell2.Image == spellImage[i])
                {
                    spell2Index = i;
                    break;
                }
            }

            // 스펠 카운트 올리고
            spellIndex++;
            spellIndex %= 10;

            if(spellIndex == spell2Index)
            {
                spellIndex++;
                spellIndex %= 10;
            }

            button_spell1.Image = spellImage[spellIndex];
            client.spell1 = (byte)spellIndex;
        }

        private void button_spell2_Click(object sender, EventArgs e)
        {
            // 스펠2
            int spellIndex = 0;
            int spell2Index = 0;

            for (int i = 0; i < 10; i++)
            {
                if (button_spell2.Image == spellImage[i])
                {
                    spellIndex = i;
                    break;
                }
            }

            for (int i = 0; i < 10; i++)
            {
                if (button_spell1.Image == spellImage[i])
                {
                    spell2Index = i;
                    break;
                }
            }

            // 스펠 카운트 올리고
            spellIndex++;
            spellIndex %= 10;

            if (spellIndex == spell2Index)
            {
                spellIndex++;
                spellIndex %= 10;
            }

            button_spell2.Image = spellImage[spellIndex];
            client.spell2 = (byte)spellIndex;
        }

        private void button_garen_Click(object sender, EventArgs e)
        {
            // 캐릭터 선택 버튼
            // 무슨 챔프 선택했는지 확인하고
            // 선택한 챔피언 서버로 전송
            if (client.isReady) return;
            for (int i = 0; i < 10; i++) 
            {
                if(sender == champButton[i])
                {
                    // 패킷보내고
                    RequestSelectChamp((byte)i);
                    return;
                }
            }
        }

        private void button_CreateRoom_EnabledChanged(object sender, EventArgs e)
        {
            if(button_CreateRoom.Enabled)
            {
                button_CreateRoom.Image = Properties.Resources.btn1;
            }
            else
            {
                button_CreateRoom.Image = Properties.Resources.btn0;
            }
        }
    }
}
