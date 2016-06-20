namespace Utility
{
    partial class MsgForm
    {
        /// <summary>
        /// 必需的设计器变量。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 清理所有正在使用的资源。
        /// </summary>
        /// <param name="disposing">如果应释放托管资源,为 true；否则为 false。</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows 窗体设计器生成的代码

        /// <summary>
        /// 设计器支持所需的方法 - 不要
        /// 使用代码编辑器修改此方法的内容。
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(MsgForm));
            this.btnTwo = new System.Windows.Forms.Button();
            this.picShow = new System.Windows.Forms.PictureBox();
            this.txtLable = new System.Windows.Forms.Label();
            this.btnOne = new System.Windows.Forms.Button();
            this.imgList = new System.Windows.Forms.ImageList(this.components);
            this.btnThree = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.picShow)).BeginInit();
            this.SuspendLayout();
            // 
            // btnTwo
            // 
            this.btnTwo.DialogResult = System.Windows.Forms.DialogResult.Cancel;
            this.btnTwo.Location = new System.Drawing.Point(104, 88);
            this.btnTwo.Name = "btnTwo";
            this.btnTwo.Size = new System.Drawing.Size(75, 23);
            this.btnTwo.TabIndex = 8;
            this.btnTwo.Text = "Two";
            this.btnTwo.UseVisualStyleBackColor = true;
            // 
            // picShow
            // 
            this.picShow.Location = new System.Drawing.Point(12, 22);
            this.picShow.Name = "picShow";
            this.picShow.Size = new System.Drawing.Size(31, 32);
            this.picShow.TabIndex = 7;
            this.picShow.TabStop = false;
            // 
            // txtLable
            // 
            this.txtLable.AutoSize = true;
            this.txtLable.Location = new System.Drawing.Point(49, 33);
            this.txtLable.Name = "txtLable";
            this.txtLable.Size = new System.Drawing.Size(41, 12);
            this.txtLable.TabIndex = 6;
            this.txtLable.Text = "label1";
            this.txtLable.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // btnOne
            // 
            this.btnOne.DialogResult = System.Windows.Forms.DialogResult.OK;
            this.btnOne.Location = new System.Drawing.Point(12, 88);
            this.btnOne.Name = "btnOne";
            this.btnOne.Size = new System.Drawing.Size(75, 23);
            this.btnOne.TabIndex = 5;
            this.btnOne.Text = "One";
            this.btnOne.UseVisualStyleBackColor = true;
            // 
            // imgList
            // 
            this.imgList.ImageStream = ((System.Windows.Forms.ImageListStreamer)(resources.GetObject("imgList.ImageStream")));
            this.imgList.TransparentColor = System.Drawing.Color.Transparent;
            this.imgList.Images.SetKeyName(0, "Warning");
            this.imgList.Images.SetKeyName(1, "Error");
            // 
            // btnThree
            // 
            this.btnThree.DialogResult = System.Windows.Forms.DialogResult.Cancel;
            this.btnThree.Location = new System.Drawing.Point(196, 88);
            this.btnThree.Name = "btnThree";
            this.btnThree.Size = new System.Drawing.Size(75, 23);
            this.btnThree.TabIndex = 9;
            this.btnThree.Text = "Three";
            this.btnThree.UseVisualStyleBackColor = true;
            // 
            // MsgForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(290, 128);
            this.Controls.Add(this.btnThree);
            this.Controls.Add(this.btnTwo);
            this.Controls.Add(this.picShow);
            this.Controls.Add(this.txtLable);
            this.Controls.Add(this.btnOne);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "MsgForm";
            this.ShowIcon = false;
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent;
            this.Shown += new System.EventHandler(this.MsgForm_Shown);
            ((System.ComponentModel.ISupportInitialize)(this.picShow)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button btnTwo;
        private System.Windows.Forms.PictureBox picShow;
        private System.Windows.Forms.Label txtLable;
        private System.Windows.Forms.Button btnOne;
        private System.Windows.Forms.ImageList imgList;
        private System.Windows.Forms.Button btnThree;
    }
}