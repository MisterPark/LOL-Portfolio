using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace LOLResourceUnpacker
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void button_openfile_Click(object sender, EventArgs e)
        {
            string currentDirectory = System.IO.Directory.GetCurrentDirectory();
            string directory = currentDirectory + "\\resources";
            string outputDirectory = currentDirectory + "\\output";
            System.IO.Directory.CreateDirectory(directory);
            System.IO.Directory.CreateDirectory(outputDirectory);
            openFileDialog1.InitialDirectory = directory;
            DialogResult result = openFileDialog1.ShowDialog();
            if(result == DialogResult.OK)
            {
                string[] fileNames = openFileDialog1.FileNames;
                int count = fileNames.Length;
                for(int i=0;i<count;i++)
                {
                    string fileName = fileNames[i];
                    string ext = System.IO.Path.GetExtension(fileName);
                    string name = System.IO.Path.GetFileNameWithoutExtension(fileName);

                    if (ext == ".sco")
                    {
                        Fantome.Libraries.League.IO.SCO.SCOFile sco = new Fantome.Libraries.League.IO.SCO.SCOFile(fileName);
                        var objFile = Fantome.Libraries.League.Converters.OBJConverter.ConvertSCO(sco);
                        objFile.Write(outputDirectory + "\\" + name + ".obj");
                    }
                    else if(ext == ".scb")
                    {
                        Fantome.Libraries.League.IO.SCB.SCBFile scb = new Fantome.Libraries.League.IO.SCB.SCBFile(fileName);
                        var objFile = Fantome.Libraries.League.Converters.OBJConverter.ConvertSCB(scb);
                        objFile.Write(outputDirectory + "\\" + name + ".obj");
                    }
                }
            }

        }
    }
}
