namespace HID_PnP_Demo
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            this.PushbuttonState_lbl = new System.Windows.Forms.Label();
            this.ToggleLEDs_btn = new System.Windows.Forms.Button();
            this.ANxVoltage_lbl = new System.Windows.Forms.Label();
            this.StatusBox_lbl = new System.Windows.Forms.Label();
            this.StatusBox_txtbx = new System.Windows.Forms.TextBox();
            this.progressBar1 = new System.Windows.Forms.ProgressBar();
            this.ReadWriteThread = new System.ComponentModel.BackgroundWorker();
            this.FormUpdateTimer = new System.Windows.Forms.Timer(this.components);
            this.ANxVoltageToolTip = new System.Windows.Forms.ToolTip(this.components);
            this.ToggleLEDToolTip = new System.Windows.Forms.ToolTip(this.components);
            this.PushbuttonStateTooltip = new System.Windows.Forms.ToolTip(this.components);
            this.toolTip1 = new System.Windows.Forms.ToolTip(this.components);
            this.toolTip2 = new System.Windows.Forms.ToolTip(this.components);
            this.DACVoltage_udn = new System.Windows.Forms.NumericUpDown();
            this.DACVoltage_lbl = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            ((System.ComponentModel.ISupportInitialize)(this.DACVoltage_udn)).BeginInit();
            this.SuspendLayout();
            // 
            // PushbuttonState_lbl
            // 
            this.PushbuttonState_lbl.AutoSize = true;
            this.PushbuttonState_lbl.Enabled = false;
            this.PushbuttonState_lbl.Location = new System.Drawing.Point(131, 65);
            this.PushbuttonState_lbl.Name = "PushbuttonState_lbl";
            this.PushbuttonState_lbl.Size = new System.Drawing.Size(141, 13);
            this.PushbuttonState_lbl.TabIndex = 25;
            this.PushbuttonState_lbl.Text = "Pushbutton State: Unknown";
            // 
            // ToggleLEDs_btn
            // 
            this.ToggleLEDs_btn.Enabled = false;
            this.ToggleLEDs_btn.Location = new System.Drawing.Point(12, 60);
            this.ToggleLEDs_btn.Name = "ToggleLEDs_btn";
            this.ToggleLEDs_btn.Size = new System.Drawing.Size(96, 23);
            this.ToggleLEDs_btn.TabIndex = 24;
            this.ToggleLEDs_btn.Text = "ToggleLED(s)";
            this.ToggleLEDs_btn.UseVisualStyleBackColor = true;
            this.ToggleLEDs_btn.Click += new System.EventHandler(this.ToggleLEDs_btn_Click);
            // 
            // ANxVoltage_lbl
            // 
            this.ANxVoltage_lbl.AutoSize = true;
            this.ANxVoltage_lbl.Enabled = false;
            this.ANxVoltage_lbl.Location = new System.Drawing.Point(122, 105);
            this.ANxVoltage_lbl.Name = "ANxVoltage_lbl";
            this.ANxVoltage_lbl.Size = new System.Drawing.Size(93, 13);
            this.ANxVoltage_lbl.TabIndex = 23;
            this.ANxVoltage_lbl.Text = "ANx/POT Voltage";
            // 
            // StatusBox_lbl
            // 
            this.StatusBox_lbl.AutoSize = true;
            this.StatusBox_lbl.Location = new System.Drawing.Point(316, 15);
            this.StatusBox_lbl.Name = "StatusBox_lbl";
            this.StatusBox_lbl.Size = new System.Drawing.Size(37, 13);
            this.StatusBox_lbl.TabIndex = 22;
            this.StatusBox_lbl.Text = "Status";
            // 
            // StatusBox_txtbx
            // 
            this.StatusBox_txtbx.BackColor = System.Drawing.SystemColors.Window;
            this.StatusBox_txtbx.Location = new System.Drawing.Point(12, 12);
            this.StatusBox_txtbx.Name = "StatusBox_txtbx";
            this.StatusBox_txtbx.ReadOnly = true;
            this.StatusBox_txtbx.Size = new System.Drawing.Size(298, 20);
            this.StatusBox_txtbx.TabIndex = 21;
            // 
            // progressBar1
            // 
            this.progressBar1.BackColor = System.Drawing.Color.White;
            this.progressBar1.ForeColor = System.Drawing.Color.Red;
            this.progressBar1.Location = new System.Drawing.Point(12, 121);
            this.progressBar1.Maximum = 1024;
            this.progressBar1.Name = "progressBar1";
            this.progressBar1.Size = new System.Drawing.Size(298, 23);
            this.progressBar1.Step = 1;
            this.progressBar1.Style = System.Windows.Forms.ProgressBarStyle.Continuous;
            this.progressBar1.TabIndex = 20;
            // 
            // ReadWriteThread
            // 
            this.ReadWriteThread.WorkerReportsProgress = true;
            this.ReadWriteThread.DoWork += new System.ComponentModel.DoWorkEventHandler(this.ReadWriteThread_DoWork);
            // 
            // FormUpdateTimer
            // 
            this.FormUpdateTimer.Enabled = true;
            this.FormUpdateTimer.Interval = 6;
            this.FormUpdateTimer.Tick += new System.EventHandler(this.FormUpdateTimer_Tick);
            // 
            // ANxVoltageToolTip
            // 
            this.ANxVoltageToolTip.AutomaticDelay = 20;
            this.ANxVoltageToolTip.AutoPopDelay = 20000;
            this.ANxVoltageToolTip.InitialDelay = 15;
            this.ANxVoltageToolTip.ReshowDelay = 15;
            // 
            // ToggleLEDToolTip
            // 
            this.ToggleLEDToolTip.AutomaticDelay = 2000;
            this.ToggleLEDToolTip.AutoPopDelay = 20000;
            this.ToggleLEDToolTip.InitialDelay = 15;
            this.ToggleLEDToolTip.ReshowDelay = 15;
            // 
            // PushbuttonStateTooltip
            // 
            this.PushbuttonStateTooltip.AutomaticDelay = 20;
            this.PushbuttonStateTooltip.AutoPopDelay = 20000;
            this.PushbuttonStateTooltip.InitialDelay = 15;
            this.PushbuttonStateTooltip.ReshowDelay = 15;
            // 
            // toolTip1
            // 
            this.toolTip1.AutomaticDelay = 2000;
            this.toolTip1.AutoPopDelay = 20000;
            this.toolTip1.InitialDelay = 15;
            this.toolTip1.ReshowDelay = 15;
            // 
            // toolTip2
            // 
            this.toolTip2.AutomaticDelay = 20;
            this.toolTip2.AutoPopDelay = 20000;
            this.toolTip2.InitialDelay = 15;
            this.toolTip2.ReshowDelay = 15;
            // 
            // DACVoltage_udn
            // 
            this.DACVoltage_udn.Location = new System.Drawing.Point(12, 83);
            this.DACVoltage_udn.Maximum = new decimal(new int[] {
            4095,
            0,
            0,
            0});
            this.DACVoltage_udn.Name = "DACVoltage_udn";
            this.DACVoltage_udn.Size = new System.Drawing.Size(94, 20);
            this.DACVoltage_udn.TabIndex = 26;
            // 
            // DACVoltage_lbl
            // 
            this.DACVoltage_lbl.AutoSize = true;
            this.DACVoltage_lbl.Location = new System.Drawing.Point(131, 85);
            this.DACVoltage_lbl.Name = "DACVoltage_lbl";
            this.DACVoltage_lbl.Size = new System.Drawing.Size(143, 13);
            this.DACVoltage_lbl.TabIndex = 27;
            this.DACVoltage_lbl.Text = "DAC Voltage Level (0~4095)";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(46, 44);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(143, 13);
            this.label1.TabIndex = 28;
            this.label1.Text = "DAC Voltage Level (0~4095)";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(210, 44);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(143, 13);
            this.label2.TabIndex = 29;
            this.label2.Text = "DAC Voltage Level (0~4095)";
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(359, 166);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.DACVoltage_lbl);
            this.Controls.Add(this.DACVoltage_udn);
            this.Controls.Add(this.PushbuttonState_lbl);
            this.Controls.Add(this.ToggleLEDs_btn);
            this.Controls.Add(this.ANxVoltage_lbl);
            this.Controls.Add(this.StatusBox_lbl);
            this.Controls.Add(this.StatusBox_txtbx);
            this.Controls.Add(this.progressBar1);
            this.Name = "Form1";
            this.Text = "HID PnP Demo";
            ((System.ComponentModel.ISupportInitialize)(this.DACVoltage_udn)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label PushbuttonState_lbl;
        private System.Windows.Forms.Button ToggleLEDs_btn;
        private System.Windows.Forms.Label ANxVoltage_lbl;
        private System.Windows.Forms.Label StatusBox_lbl;
        private System.Windows.Forms.TextBox StatusBox_txtbx;
        private System.Windows.Forms.ProgressBar progressBar1;
        private System.ComponentModel.BackgroundWorker ReadWriteThread;
        private System.Windows.Forms.Timer FormUpdateTimer;
        private System.Windows.Forms.ToolTip ANxVoltageToolTip;
        private System.Windows.Forms.ToolTip ToggleLEDToolTip;
        private System.Windows.Forms.ToolTip PushbuttonStateTooltip;
        private System.Windows.Forms.ToolTip toolTip1;
        private System.Windows.Forms.ToolTip toolTip2;
        private System.Windows.Forms.NumericUpDown DACVoltage_udn;
        private System.Windows.Forms.Label DACVoltage_lbl;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
    }
}

