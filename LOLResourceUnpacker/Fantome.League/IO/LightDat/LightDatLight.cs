﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;
using Fantome.Libraries.League.Helpers.Structures;
using System.Globalization;

namespace Fantome.Libraries.League.IO.LightDat
{
    public class LightDatLight
    {
        public Vector3 Position;
        public ColorRGBVector3Byte Color;
        public float Radius;
        public LightDatLight(StreamReader sr)
        {
            string[] Line = sr.ReadLine().Split(' ');
            this.Position = new Vector3(
                float.Parse(Line[0], CultureInfo.InvariantCulture),
                float.Parse(Line[1], CultureInfo.InvariantCulture), 
                float.Parse(Line[2], CultureInfo.InvariantCulture)
                );
            this.Color = new ColorRGBVector3Byte(byte.Parse(Line[3]), byte.Parse(Line[4]), byte.Parse(Line[5]));
            this.Radius = float.Parse(Line[6], CultureInfo.InvariantCulture);
        }
        public void Write(StreamWriter sw)
        {
            this.Position.Write(sw, "{0} {1} {2} ");
            this.Color.Write(sw, "{0} {1} {2} ");
            sw.Write(this.Radius + Environment.NewLine);
        }
    }
}
