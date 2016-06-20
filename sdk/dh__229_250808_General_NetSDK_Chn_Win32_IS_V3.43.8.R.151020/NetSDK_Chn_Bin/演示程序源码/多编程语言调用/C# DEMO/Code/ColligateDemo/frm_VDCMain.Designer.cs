namespace ColligateDemo
{
    partial class frm_VDCDemo
    {
        /// <summary>
        /// Required design varibale
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clear all resources in use
        /// </summary>
        /// <param name="disposing">If release controller resource, as true；otherwise as false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows window design generated code

        /// <summary>
        /// Design supported method - not
        /// Use code editor modify this method.
        /// </summary>
        private void InitializeComponent()
        {
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(frm_VDCDemo));
            this.picMain = new System.Windows.Forms.PictureBox();
            this.btnAddDev = new System.Windows.Forms.Button();
            this.btnStartPlay = new System.Windows.Forms.Button();
            this.btnPause = new System.Windows.Forms.Button();
            this.btnStop = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.picMain)).BeginInit();
            this.SuspendLayout();
            // 
            // picMain
            // 
            this.picMain.Location = new System.Drawing.Point(12, 12);
            this.picMain.Name = "picMain";
            this.picMain.Size = new System.Drawing.Size(603, 509);
            this.picMain.TabIndex = 0;
            this.picMain.TabStop = false;
            // 
            // btnAddDev
            // 
            this.btnAddDev.Location = new System.Drawing.Point(621, 12);
            this.btnAddDev.Name = "btnAddDev";
            this.btnAddDev.Size = new System.Drawing.Size(109, 38);
            this.btnAddDev.TabIndex = 1;
            this.btnAddDev.Text = "Add Device";
            this.btnAddDev.UseVisualStyleBackColor = true;
            this.btnAddDev.Click += new System.EventHandler(this.btnAddDev_Click);
            // 
            // btnStartPlay
            // 
            this.btnStartPlay.Location = new System.Drawing.Point(621, 56);
            this.btnStartPlay.Name = "btnStartPlay";
            this.btnStartPlay.Size = new System.Drawing.Size(109, 38);
            this.btnStartPlay.TabIndex = 2;
            this.btnStartPlay.Text = "Play 0 Channel";
            this.btnStartPlay.UseVisualStyleBackColor = true;
            this.btnStartPlay.Click += new System.EventHandler(this.btnStartPlay_Click);
            // 
            // btnPause
            // 
            this.btnPause.Location = new System.Drawing.Point(621, 100);
            this.btnPause.Name = "btnPause";
            this.btnPause.Size = new System.Drawing.Size(109, 38);
            this.btnPause.TabIndex = 3;
            this.btnPause.Tag = "0";
            this.btnPause.Text = "Pause";
            this.btnPause.UseVisualStyleBackColor = true;
            this.btnPause.Click += new System.EventHandler(this.btnPause_Click);
            // 
            // btnStop
            // 
            this.btnStop.Location = new System.Drawing.Point(621, 144);
            this.btnStop.Name = "btnStop";
            this.btnStop.Size = new System.Drawing.Size(109, 38);
            this.btnStop.TabIndex = 4;
            this.btnStop.Text = "End";
            this.btnStop.UseVisualStyleBackColor = true;
            this.btnStop.Click += new System.EventHandler(this.btnStop_Click);
            // 
            // frm_VDCDemo
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(739, 532);
            this.Controls.Add(this.btnStop);
            this.Controls.Add(this.btnPause);
            this.Controls.Add(this.btnStartPlay);
            this.Controls.Add(this.btnAddDev);
            this.Controls.Add(this.picMain);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "frm_VDCDemo";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Decoding card related demonstration";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.frm_VDCMain_FormClosing);
            this.Load += new System.EventHandler(this.frm_VDCMain_Load);
            ((System.ComponentModel.ISupportInitialize)(this.picMain)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.PictureBox picMain;
        private System.Windows.Forms.Button btnAddDev;
        private System.Windows.Forms.Button btnStartPlay;
        private System.Windows.Forms.Button btnPause;
        private System.Windows.Forms.Button btnStop;
    }
}