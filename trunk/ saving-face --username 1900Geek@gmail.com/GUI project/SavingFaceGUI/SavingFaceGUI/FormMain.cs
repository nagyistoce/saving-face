using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace SavingFaceGUI
{
    public partial class FormMain : Form
    {
        public FormMain()
        {
            InitializeComponent();
            this.DesktopLocation = new Point(0,0);
        }

        private void buttonExit_Click(object sender, EventArgs e)
        {
            Application.Exit();
        }

        private void buttonIdentify_Click(object sender, EventArgs e)
        {
            Form identify = new FormIdentify();
            identify.Owner = this;
            identify.DesktopLocation = this.DesktopLocation;
            identify.Show();
            this.Hide();
            //TODO: add code for identify
        }

        private void buttonSave_Click(object sender, EventArgs e)
        {
            Form save = new FormSave();
            save.Owner = this;
            save.DesktopLocation = this.DesktopLocation;
            save.Show();
            this.Hide();
        }
    }
}
