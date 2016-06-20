namespace SDKPlayDemo
{
    partial class frmDisplayRegion
    {
        /// <summary>
        /// The necessary designer variables.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up all the resources being used.
        /// </summary>
        /// <param name="disposing">It is true if the hosting resources should be released, or it will be false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Forms designer generated code

        /// <summary>
        /// Designer support methods - have no use for
        /// Using code editor modify the content of the method
        /// </summary>
        private void InitializeComponent()
        {
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(frmDisplayRegion));
            this.spcMain = new System.Windows.Forms.SplitContainer();
            this.picDisplayMain = new System.Windows.Forms.PictureBox();
            this.nudBottom = new System.Windows.Forms.NumericUpDown();
            this.nudTop = new System.Windows.Forms.NumericUpDown();
            this.nudLeft = new System.Windows.Forms.NumericUpDown();
            this.label4 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.btnRefresh = new System.Windows.Forms.Button();
            this.btnDisplay = new System.Windows.Forms.Button();
            this.nudRight = new System.Windows.Forms.NumericUpDown();
            this.spcMain.Panel1.SuspendLayout();
            this.spcMain.Panel2.SuspendLayout();
            this.spcMain.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.picDisplayMain)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.nudBottom)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.nudTop)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.nudLeft)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.nudRight)).BeginInit();
            this.SuspendLayout();
            // 
            // spcMain
            // 
            this.spcMain.Dock = System.Windows.Forms.DockStyle.Fill;
            this.spcMain.Location = new System.Drawing.Point(0, 0);
            this.spcMain.Name = "spcMain";
            this.spcMain.Orientation = System.Windows.Forms.Orientation.Horizontal;
            // 
            // spcMain.Panel1
            // 
            this.spcMain.Panel1.Controls.Add(this.picDisplayMain);
            // 
            // spcMain.Panel2
            // 
            this.spcMain.Panel2.Controls.Add(this.nudBottom);
            this.spcMain.Panel2.Controls.Add(this.nudTop);
            this.spcMain.Panel2.Controls.Add(this.nudLeft);
            this.spcMain.Panel2.Controls.Add(this.label4);
            this.spcMain.Panel2.Controls.Add(this.label3);
            this.spcMain.Panel2.Controls.Add(this.label2);
            this.spcMain.Panel2.Controls.Add(this.label1);
            this.spcMain.Panel2.Controls.Add(this.btnRefresh);
            this.spcMain.Panel2.Controls.Add(this.btnDisplay);
            this.spcMain.Panel2.Controls.Add(this.nudRight);
            this.spcMain.Size = new System.Drawing.Size(457, 443);
            this.spcMain.SplitterDistance = 381;
            this.spcMain.TabIndex = 0;
            // 
            // picDisplayMain
            // 
            this.picDisplayMain.Dock = System.Windows.Forms.DockStyle.Fill;
            this.picDisplayMain.Location = new System.Drawing.Point(0, 0);
            this.picDisplayMain.Name = "picDisplayMain";
            this.picDisplayMain.Size = new System.Drawing.Size(457, 381);
            this.picDisplayMain.TabIndex = 0;
            this.picDisplayMain.TabStop = false;
            // 
            // nudBottom
            // 
            this.nudBottom.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.nudBottom.Location = new System.Drawing.Point(223, 30);
            this.nudBottom.Maximum = new decimal(new int[] {
            600,
            0,
            0,
            0});
            this.nudBottom.Name = "nudBottom";
            this.nudBottom.Size = new System.Drawing.Size(91, 21);
            this.nudBottom.TabIndex = 23;
            this.nudBottom.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            this.nudBottom.Value = new decimal(new int[] {
            100,
            0,
            0,
            0});
            // 
            // nudTop
            // 
            this.nudTop.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.nudTop.Location = new System.Drawing.Point(87, 30);
            this.nudTop.Maximum = new decimal(new int[] {
            600,
            0,
            0,
            0});
            this.nudTop.Name = "nudTop";
            this.nudTop.Size = new System.Drawing.Size(91, 21);
            this.nudTop.TabIndex = 22;
            this.nudTop.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            // 
            // nudLeft
            // 
            this.nudLeft.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.nudLeft.Location = new System.Drawing.Point(87, 6);
            this.nudLeft.Maximum = new decimal(new int[] {
            600,
            0,
            0,
            0});
            this.nudLeft.Name = "nudLeft";
            this.nudLeft.Size = new System.Drawing.Size(91, 21);
            this.nudLeft.TabIndex = 21;
            this.nudLeft.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            // 
            // label4
            // 
            this.label4.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(188, 34);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(29, 12);
            this.label4.TabIndex = 19;
            this.label4.Text = "Down";
            // 
            // label3
            // 
            this.label3.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(59, 32);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(17, 12);
            this.label3.TabIndex = 18;
            this.label3.Text = "Up";
            // 
            // label2
            // 
            this.label2.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(184, 10);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(35, 12);
            this.label2.TabIndex = 17;
            this.label2.Text = "Right";
            // 
            // label1
            // 
            this.label1.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(53, 8);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(29, 12);
            this.label1.TabIndex = 16;
            this.label1.Text = "Left";
            // 
            // btnRefresh
            // 
            this.btnRefresh.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.btnRefresh.Location = new System.Drawing.Point(335, 32);
            this.btnRefresh.Name = "btnRefresh";
            this.btnRefresh.Size = new System.Drawing.Size(64, 23);
            this.btnRefresh.TabIndex = 15;
            this.btnRefresh.Text = "Refresh";
            this.btnRefresh.UseVisualStyleBackColor = true;
            this.btnRefresh.Click += new System.EventHandler(this.btnRefresh_Click);
            // 
            // btnDisplay
            // 
            this.btnDisplay.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.btnDisplay.Location = new System.Drawing.Point(335, 3);
            this.btnDisplay.Name = "btnDisplay";
            this.btnDisplay.Size = new System.Drawing.Size(64, 23);
            this.btnDisplay.TabIndex = 14;
            this.btnDisplay.Text = "Display";
            this.btnDisplay.UseVisualStyleBackColor = true;
            this.btnDisplay.Click += new System.EventHandler(this.btnDisplay_Click);
            // 
            // nudRight
            // 
            this.nudRight.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.nudRight.Location = new System.Drawing.Point(223, 5);
            this.nudRight.Maximum = new decimal(new int[] {
            600,
            0,
            0,
            0});
            this.nudRight.Name = "nudRight";
            this.nudRight.Size = new System.Drawing.Size(91, 21);
            this.nudRight.TabIndex = 20;
            this.nudRight.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            this.nudRight.Value = new decimal(new int[] {
            100,
            0,
            0,
            0});
            // 
            // frmDisplayRegion
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(457, 443);
            this.Controls.Add(this.spcMain);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MinimizeBox = false;
            this.Name = "frmDisplayRegion";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent;
            this.Text = "Local amplification demo";
            this.Load += new System.EventHandler(this.frmDisplayRegion_Load);
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.frmDisplayRegion_FormClosing);
            this.spcMain.Panel1.ResumeLayout(false);
            this.spcMain.Panel2.ResumeLayout(false);
            this.spcMain.Panel2.PerformLayout();
            this.spcMain.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.picDisplayMain)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.nudBottom)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.nudTop)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.nudLeft)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.nudRight)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.SplitContainer spcMain;
        private System.Windows.Forms.PictureBox picDisplayMain;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Button btnRefresh;
        private System.Windows.Forms.Button btnDisplay;
        private System.Windows.Forms.NumericUpDown nudRight;
        private System.Windows.Forms.NumericUpDown nudBottom;
        private System.Windows.Forms.NumericUpDown nudTop;
        private System.Windows.Forms.NumericUpDown nudLeft;


    }
}