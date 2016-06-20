namespace ColligateDemo
{
    partial class frm_Main
    {
        /// <summary>
        /// Required design variable. 
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clear all resources in use.
        /// </summary>
        /// <param name="disposing">If release controller resource, as true；otherwise, as false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Window design generated code

        /// <summary>
        /// Design supported method - not
        /// Use code editor to modify this method.
        /// </summary>
        private void InitializeComponent()
        {
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(frm_Main));
            this.picPlayMain = new System.Windows.Forms.PictureBox();
            this.btnVDC = new System.Windows.Forms.Button();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.btnLogout = new System.Windows.Forms.Button();
            this.btnStartRealPlay = new System.Windows.Forms.Button();
            this.btnStopRealPlay = new System.Windows.Forms.Button();
            this.btnLogin = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.picPlayMain)).BeginInit();
            this.groupBox1.SuspendLayout();
            this.groupBox2.SuspendLayout();
            this.SuspendLayout();
            // 
            // picPlayMain
            // 
            this.picPlayMain.Location = new System.Drawing.Point(12, 12);
            this.picPlayMain.Name = "picPlayMain";
            this.picPlayMain.Size = new System.Drawing.Size(449, 380);
            this.picPlayMain.TabIndex = 0;
            this.picPlayMain.TabStop = false;
            // 
            // btnVDC
            // 
            this.btnVDC.Location = new System.Drawing.Point(6, 20);
            this.btnVDC.Name = "btnVDC";
            this.btnVDC.Size = new System.Drawing.Size(106, 32);
            this.btnVDC.TabIndex = 4;
            this.btnVDC.Text = "Demonstration";
            this.btnVDC.UseVisualStyleBackColor = true;
            this.btnVDC.Click += new System.EventHandler(this.btnVDC_Click);
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.btnVDC);
            this.groupBox1.Location = new System.Drawing.Point(467, 200);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(122, 61);
            this.groupBox1.TabIndex = 6;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Switch video wall";
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.btnLogout);
            this.groupBox2.Controls.Add(this.btnStartRealPlay);
            this.groupBox2.Controls.Add(this.btnStopRealPlay);
            this.groupBox2.Controls.Add(this.btnLogin);
            this.groupBox2.Location = new System.Drawing.Point(467, 12);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(122, 182);
            this.groupBox2.TabIndex = 7;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "Stream play";
            // 
            // btnLogout
            // 
            this.btnLogout.Enabled = false;
            this.btnLogout.Location = new System.Drawing.Point(8, 137);
            this.btnLogout.Name = "btnLogout";
            this.btnLogout.Size = new System.Drawing.Size(106, 32);
            this.btnLogout.TabIndex = 9;
            this.btnLogout.Text = "Login Out";
            this.btnLogout.UseVisualStyleBackColor = true;
            this.btnLogout.Click += new System.EventHandler(this.btnLogout_Click);
            // 
            // btnStartRealPlay
            // 
            this.btnStartRealPlay.Enabled = false;
            this.btnStartRealPlay.Location = new System.Drawing.Point(8, 61);
            this.btnStartRealPlay.Name = "btnStartRealPlay";
            this.btnStartRealPlay.Size = new System.Drawing.Size(106, 32);
            this.btnStartRealPlay.TabIndex = 8;
            this.btnStartRealPlay.Text = "Start Play";
            this.btnStartRealPlay.UseVisualStyleBackColor = true;
            this.btnStartRealPlay.Click += new System.EventHandler(this.btnStartRealPlay_Click);
            // 
            // btnStopRealPlay
            // 
            this.btnStopRealPlay.Enabled = false;
            this.btnStopRealPlay.Location = new System.Drawing.Point(8, 99);
            this.btnStopRealPlay.Name = "btnStopRealPlay";
            this.btnStopRealPlay.Size = new System.Drawing.Size(106, 32);
            this.btnStopRealPlay.TabIndex = 7;
            this.btnStopRealPlay.Text = "Stop Play";
            this.btnStopRealPlay.UseVisualStyleBackColor = true;
            this.btnStopRealPlay.Click += new System.EventHandler(this.btnStopRealPlay_Click);
            // 
            // btnLogin
            // 
            this.btnLogin.Location = new System.Drawing.Point(8, 23);
            this.btnLogin.Name = "btnLogin";
            this.btnLogin.Size = new System.Drawing.Size(106, 32);
            this.btnLogin.TabIndex = 6;
            this.btnLogin.Text = "Login In";
            this.btnLogin.UseVisualStyleBackColor = true;
            this.btnLogin.Click += new System.EventHandler(this.btnLogin_Click);
            // 
            // frm_Main
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(601, 405);
            this.Controls.Add(this.groupBox2);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.picPlayMain);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "frm_Main";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Some Special Functions";
            this.Load += new System.EventHandler(this.frm_Main_Load);
            ((System.ComponentModel.ISupportInitialize)(this.picPlayMain)).EndInit();
            this.groupBox1.ResumeLayout(false);
            this.groupBox2.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.PictureBox picPlayMain;
        private System.Windows.Forms.Button btnVDC;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.Button btnLogout;
        private System.Windows.Forms.Button btnStartRealPlay;
        private System.Windows.Forms.Button btnStopRealPlay;
        private System.Windows.Forms.Button btnLogin;
    }
}

