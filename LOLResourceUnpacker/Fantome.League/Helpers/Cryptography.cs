﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Fantome.Libraries.League.Helpers.Cryptography
{
    public static class Cryptography
    {
        public static UInt32 FNV32Hash(string toHash)
        {
            toHash = toHash.ToLower();
            UInt32 hash = 2166136261;
            for (int i = 0; i < toHash.Length; i++)
            {
                hash = hash ^ toHash[i];
                hash = hash * 16777619;
            }

            return hash;
        }

        public static UInt32 SectionHash(string section, string property)
        {
            UInt32 hash = 0;
            section = section.ToLower();
            property = property.ToLower();
            for(int i = 0; i < section.Length; i++)
            {
                hash = section[i] + 65599 * hash;
            }
            hash = (65599 * hash + 42);
            for (int i = 0; i < property.Length; i++)
            {
                hash = property[i] + 65599 * hash;
            }
            return hash;
        }

        public static UInt32 LeagueHash(string toHash)
        {
            uint hash = 0;
            uint temp = 0;
            toHash = toHash.ToLower();
            for (int i = 0; i < toHash.Length; i++)
            {
                hash = (hash << 4) + toHash[i];
                temp = hash & 0xF0000000;
                if (temp != 0)
                {
                    hash = hash ^ (temp >> 24);
                    hash = hash ^ temp;
                }
            }
            return hash;
        }
    }
}