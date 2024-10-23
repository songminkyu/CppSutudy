using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using Wrapper;

namespace WindowsFormsApp1
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        MyArithmetic arithmetic = new MyArithmetic(); //객체 생성

        private void Add_Click(object sender, EventArgs e)
        {
            
            int value = arithmetic.Add(Convert.ToInt32(textBox1.Text), Convert.ToInt32(textBox2.Text));
            textBox3.Text = value.ToString();
        }

        private void Subtract_Click(object sender, EventArgs e)
        {
          
            int value = arithmetic.Subtract(Convert.ToInt32(textBox1.Text), Convert.ToInt32(textBox2.Text));
            textBox3.Text = value.ToString();
        }

        private void Multiply_Click(object sender, EventArgs e)
        {
            int value = arithmetic.Multiply(Convert.ToInt32(textBox1.Text), Convert.ToInt32(textBox2.Text));
            textBox3.Text = value.ToString();
        }

        private void Divide_Click(object sender, EventArgs e)
        {
            int value = arithmetic.Divide(Convert.ToInt32(textBox1.Text), Convert.ToInt32(textBox2.Text));
            textBox3.Text = value.ToString();
        }
    }
}
