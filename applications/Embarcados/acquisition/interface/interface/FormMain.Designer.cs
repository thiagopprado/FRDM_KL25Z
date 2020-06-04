namespace @interface {
    partial class Form1 {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing) {
            if (disposing && (components != null)) {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent() {
            System.Windows.Forms.DataVisualization.Charting.ChartArea chartArea3 = new System.Windows.Forms.DataVisualization.Charting.ChartArea();
            System.Windows.Forms.DataVisualization.Charting.Legend legend3 = new System.Windows.Forms.DataVisualization.Charting.Legend();
            System.Windows.Forms.DataVisualization.Charting.Series series3 = new System.Windows.Forms.DataVisualization.Charting.Series();
            this.button_update = new System.Windows.Forms.Button();
            this.comboBox_port = new System.Windows.Forms.ComboBox();
            this.button_connect = new System.Windows.Forms.Button();
            this.chart_wave = new System.Windows.Forms.DataVisualization.Charting.Chart();
            this.button_init = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.chart_wave)).BeginInit();
            this.SuspendLayout();
            // 
            // button_update
            // 
            this.button_update.Location = new System.Drawing.Point(117, 5);
            this.button_update.Name = "button_update";
            this.button_update.Size = new System.Drawing.Size(75, 23);
            this.button_update.TabIndex = 0;
            this.button_update.Text = "Atualizar";
            this.button_update.UseVisualStyleBackColor = true;
            this.button_update.Click += new System.EventHandler(this.button_update_Click);
            // 
            // comboBox_port
            // 
            this.comboBox_port.AllowDrop = true;
            this.comboBox_port.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBox_port.FormattingEnabled = true;
            this.comboBox_port.Location = new System.Drawing.Point(12, 6);
            this.comboBox_port.Name = "comboBox_port";
            this.comboBox_port.Size = new System.Drawing.Size(99, 21);
            this.comboBox_port.TabIndex = 1;
            // 
            // button_connect
            // 
            this.button_connect.Location = new System.Drawing.Point(197, 5);
            this.button_connect.Name = "button_connect";
            this.button_connect.Size = new System.Drawing.Size(75, 23);
            this.button_connect.TabIndex = 2;
            this.button_connect.Text = "Conectar";
            this.button_connect.UseVisualStyleBackColor = true;
            this.button_connect.Click += new System.EventHandler(this.button_connect_Click);
            // 
            // chart_wave
            // 
            chartArea3.Name = "ChartArea1";
            this.chart_wave.ChartAreas.Add(chartArea3);
            this.chart_wave.Dock = System.Windows.Forms.DockStyle.Bottom;
            legend3.Name = "Legend1";
            this.chart_wave.Legends.Add(legend3);
            this.chart_wave.Location = new System.Drawing.Point(0, 33);
            this.chart_wave.Name = "chart_wave";
            series3.ChartArea = "ChartArea1";
            series3.Legend = "Legend1";
            series3.Name = "Series1";
            this.chart_wave.Series.Add(series3);
            this.chart_wave.Size = new System.Drawing.Size(692, 547);
            this.chart_wave.TabIndex = 3;
            this.chart_wave.Text = "Wave Form";
            // 
            // button_init
            // 
            this.button_init.Location = new System.Drawing.Point(605, 6);
            this.button_init.Name = "button_init";
            this.button_init.Size = new System.Drawing.Size(75, 23);
            this.button_init.TabIndex = 4;
            this.button_init.Text = "Iniciar";
            this.button_init.UseVisualStyleBackColor = true;
            this.button_init.Click += new System.EventHandler(this.button_init_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(692, 580);
            this.Controls.Add(this.button_init);
            this.Controls.Add(this.chart_wave);
            this.Controls.Add(this.button_connect);
            this.Controls.Add(this.comboBox_port);
            this.Controls.Add(this.button_update);
            this.Name = "Form1";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Interface";
            this.Load += new System.EventHandler(this.Form1_Load);
            ((System.ComponentModel.ISupportInitialize)(this.chart_wave)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Button button_update;
        private System.Windows.Forms.ComboBox comboBox_port;
        private System.Windows.Forms.Button button_connect;
        private System.Windows.Forms.DataVisualization.Charting.Chart chart_wave;
        private System.Windows.Forms.Button button_init;
    }
}

