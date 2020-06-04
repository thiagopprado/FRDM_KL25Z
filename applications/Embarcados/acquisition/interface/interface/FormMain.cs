using System;
using System.Drawing;

using System.IO.Ports;
using System.Windows.Forms;
using System.Windows.Forms.DataVisualization.Charting;

namespace @interface {
    public partial class Form1 : Form {
        const int MAX_POINTS = 200;
        private SerialPort port = new SerialPort();
        private int[] buffer = new int[MAX_POINTS];
        private int current = 0;
        private bool init = false;
        private bool is_negative = false;

        delegate void chart_Delegate();

        public Form1() {
            InitializeComponent();
        }       

        private void Form1_Load(object sender, EventArgs e) {
            button_update_Click(sender, e);

            chart_wave.Series.Clear();
            chart_wave.ChartAreas[0].AxisX.Minimum = 0;
            chart_wave.ChartAreas[0].AxisX.Maximum = MAX_POINTS;
            chart_wave.ChartAreas[0].AxisX.Interval = 20;
            chart_wave.ChartAreas[0].AxisY.Minimum = -4800;
            chart_wave.ChartAreas[0].AxisY.Maximum = 4801;
            chart_wave.ChartAreas[0].AxisY.Interval = 400;

            chart_wave.ChartAreas[0].AxisX.MajorGrid.LineColor = Color.LightGray;
            chart_wave.ChartAreas[0].AxisY.MajorGrid.LineColor = Color.LightGray;

            chart_wave.Legends[0].Enabled = false;

            Series medidas = new Series();
            for (int i = 0; i < MAX_POINTS; i++) {
                medidas.Points.AddXY(i, 0);
            }
            medidas.ChartType = SeriesChartType.Line;
            medidas.Color = Color.DarkRed;
            medidas.BorderWidth = 2;

            chart_wave.Series.Clear();
            chart_wave.Series.Add(medidas);
        }

        private void button_update_Click(object sender, EventArgs e) {
            // Clear port combobox
            comboBox_port.Items.Clear();
            foreach (string port_name in SerialPort.GetPortNames()) {
                // Add available ports to combobox
                comboBox_port.Items.Add(port_name);
                comboBox_port.SelectedIndex++;
            }
        }

        private void button_connect_Click(object sender, EventArgs e) {
            string port_name = comboBox_port.SelectedItem.ToString();
            if (port.IsOpen || string.IsNullOrEmpty(port_name)) {
                // Already connected
                return;
            }
            port.PortName = port_name;
            port.BaudRate = 115000;
            port.Open();
            port.DiscardInBuffer();
            port.DataReceived += Port_DataReceived;
        }

        private void button_init_Click(object sender, EventArgs e) {
            if (port.IsOpen) {
                port.Write(" ");
            }
        }

        private void Port_DataReceived(object sender, SerialDataReceivedEventArgs e) {
            SerialPort spL = (SerialPort)sender;
            char[] buf = new char[spL.BytesToRead];
            spL.Read(buf, 0, buf.Length);

            for (int i = 0; i < buf.Length; i++) {
                if (buf[i] == '\r') {
                    // First char
                    init = true;
                    buffer[current] = 0;
                    is_negative = false;
                }
                else if (buf[i] >= '0' && buf[i] <= '9' && init) {
                    // Values
                    buffer[current] = buffer[current] * 10;
                    buffer[current] += (int)buf[i] - '0';
                }
                else if (buf[i] == '\n' && init) {
                    // Last char
                    init = false;
                    if (is_negative) {
                        buffer[current] *= -1;
                    }
                    // Calls insert values to update chart
                    chart_wave.Invoke(new chart_Delegate(insert_values));
                    current++;
                    current %= MAX_POINTS;
                }
                else if ((buf[i] == '+' || buf[i] == '-') && init) {
                    if (buf[i] == '-') {
                        is_negative = true;
                    }
                }
                else {                
                    init = false;
                }
            }
        }

        private void insert_values () {
            Series medidas = new Series();
            for (int i = 0; i < MAX_POINTS; i++) {
                medidas.Points.AddXY(i, buffer[(current + i + 1) % MAX_POINTS]);
            }
            medidas.ChartType = SeriesChartType.Line;
            medidas.Color = Color.DarkRed;
            medidas.BorderWidth = 2;

            chart_wave.Series.Clear();
            chart_wave.Series.Add(medidas);

            // using (System.IO.StreamWriter file = new System.IO.StreamWriter("data.m", true)) {
                // file.WriteLine(buffer[current].ToString());
            // }
        }
    }
}
