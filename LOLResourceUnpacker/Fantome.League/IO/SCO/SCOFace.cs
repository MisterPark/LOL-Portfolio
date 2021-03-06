﻿using Fantome.Libraries.League.Helpers.Structures;
using System;
using System.Diagnostics;
using System.Globalization;
using System.IO;

namespace Fantome.Libraries.League.IO.SCO
{
    [DebuggerDisplay("[ {Material} ]")]
    public class SCOFace
    {
        public UInt16[] Indices { get; private set; } = new UInt16[3];
        public string Material { get; private set; }
        public Vector2[] UV { get; private set; } = new Vector2[3];

        public SCOFace(UInt16[] Indices, string Material, Vector2[] UV)
        {
            this.Indices = Indices;
            this.Material = Material;
            this.UV = UV;
        }
        public SCOFace(StreamReader sr)
        {
            string[] input = sr.ReadLine().Split(new char[] { ' ', '\t' }, StringSplitOptions.RemoveEmptyEntries);

            for (int i = 0; i < 3; i++)
            {
                this.Indices[i] = UInt16.Parse(input[i + 1]);
            }

            this.Material = input[4];

            for (int i = 0; i < 3; i++)
            {
                this.UV[i] = new Vector2(0,0);
                
            }
            this.UV[0].X = float.Parse(input[5], CultureInfo.InvariantCulture);
            this.UV[0].Y = float.Parse(input[6], CultureInfo.InvariantCulture);
            this.UV[1].X = float.Parse(input[7], CultureInfo.InvariantCulture);
            this.UV[1].Y = float.Parse(input[8], CultureInfo.InvariantCulture);
            this.UV[2].X = float.Parse(input[9], CultureInfo.InvariantCulture);
            this.UV[2].Y = float.Parse(input[10], CultureInfo.InvariantCulture);
        }
    }
}
