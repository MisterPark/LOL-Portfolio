using System;
using System.Collections.Generic;
using System.Text;
using System.Runtime.InteropServices;

namespace LOLClient
{
    [Serializable]
    [StructLayout(LayoutKind.Sequential, Pack =1)]
    public struct NetHeader
    {
        public byte code; // 매직넘버
        public ushort length; // 페이로드 길이
        public byte randKey; // 랜덤키
        public byte checkSum; // 체크섬
    }

    [Serializable]
    [StructLayout(LayoutKind.Sequential, Pack = 1)]
    public struct LanHeader
    {
        public ushort length;
    }

    public enum MsgType : ushort
    {
        GAME_SERVER = 1000,
        GAME_REQ_NICK,
        GAME_RES_NICK,
        GAME_REQ_LOGIN,
        GAME_RES_LOGIN,
        GAME_REQ_JOIN_GAME,
        GAME_RES_JOIN_GAME,
        GAME_REQ_SELECT_CHAMP,
        GAME_RES_SELECT_CHAMP,
        GAME_REQ_READY,
        GAME_RES_READY,
        GAME_RES_START,
    }

    public enum LoginResult
    {
        SUCCEED,
        ID_DOES_NOT_EXIST,
        PASSWORD_DOES_NOT_MATCH,
        ID_ALREADY_LOGGED_IN,
        SPECIAL_CHARACTER,
    }

    class Protocol
    {
        public static readonly byte PACKET_CODE = 0x77;
        public static readonly byte ENDCODE = 0x79;
        public static readonly int SizeOfNetHeader = 5;
        public static readonly int SizeOfLanHeader = 2;
    }

    public enum SpellType
    {
        Barrier,
        Boost,
        Exhaust,
        Flash,
        Haste,
        Heal,
        Ignite,
        Mana,
        Smite,
        Teleport,
    }

}
