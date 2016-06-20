using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace Utility
{
    public partial class MsgForm : Form
    {
        /// <summary>
        /// Button Type
        /// </summary>
        private MessageUtil.MBButtonType btnType;

        public MsgForm()
        {
            InitializeComponent();
        }

        /// <summary>
        /// According to the callback,set window size based on the amount of info 
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void MsgForm_Shown(object sender, EventArgs e)
        {
            int iTextMargin = 50; // Text and the window frame spacing

            int iBottomMargin = 10; // The interval between button and bottom of window
            Point point = picShow.Location;
            if (picShow.Image == null)
                txtLable.Location = picShow.Location;

            Size txtSize = txtLable.Size;
            Size formSize = this.Size;

            // According to the text box size, scale size of the window
            int nWidth = txtLable.Size.Width + iTextMargin * 2; //point.X * 2
            int nHeight = point.Y * 2 + txtLable.Height + btnOne.Size.Height + iBottomMargin;
            this.Size = new Size(nWidth, nHeight);

            //Center Text Box
            txtLable.Location = new Point((nWidth - txtSize.Width) / 2, txtLable.Location.Y);

            // Set up button position
            int iBtnY = point.Y * 2 + txtLable.Height + btnOne.Size.Height;
            btnOne.Location = new Point(btnOne.Location.X, iBtnY);
            btnTwo.Location = new Point(btnTwo.Location.X, iBtnY);
            btnThree.Location = new Point(btnThree.Location.X, iBtnY);

            this.CenterButtons();
        }

        /// <summary>
        /// Content of the message box
        /// </summary>
        public string Content
        {
            set
            {
                txtLable.Text = value;
            }
            get
            {
                return txtLable.Text;
            }
        }

        /// <summary>
        /// Icon Type 
        /// </summary>
        public MessageUtil.MBIconType IconType
        {
            set
            {
                switch (value)
                {
                    case MessageUtil.MBIconType.MBIcon_None:
                        picShow.Image = null;
                        picShow.Visible = false;
                        break;

                    case MessageUtil.MBIconType.MBIcon_OK:
                        break;

                    case MessageUtil.MBIconType.MBIcon_Warning:
                        picShow.Image = imgList.Images["Warning"];
                        break;

                    case MessageUtil.MBIconType.MBIcon_Error:
                        picShow.Image = imgList.Images["Error"];
                        break;

                    default:
                        picShow.Image = null;
                        picShow.Visible = false;
                        break;
                }
            }
        }

        /// <summary>
        /// Button Type
        /// </summary>
        public MessageUtil.MBButtonType ButtonType
        {
            set
            {
                btnType = value;
            }
        }

        private void CenterButtons()
        {
            int nMarginButtons = 15;

            switch (btnType)
            {
                case MessageUtil.MBButtonType.MBBtn_OK:
                    {
                        btnTwo.Visible = false;
                        btnThree.Visible = false;
                        Point point = btnOne.Location;
                        int x = (this.Size.Width - btnOne.Size.Width) / 2;
                        point.X = x;
                        btnOne.Location = point;
                        btnOne.Text = StringUtil.ConvertString("OK", "Common");
                        btnOne.DialogResult = DialogResult.OK;
                    }
                    break;

                case MessageUtil.MBButtonType.MBBtn_OKCancel:
                    {
                        btnThree.Visible = false;
                        Point point = btnOne.Location;

                        int x = (this.Size.Width - btnOne.Size.Width * 2) / 2;

                        point.X = x - nMarginButtons;
                        btnOne.Location = point;
                        point.X = x + btnOne.Size.Width + nMarginButtons;
                        btnTwo.Location = point;

                        btnOne.Text = StringUtil.ConvertString("OK", "Common");
                        btnTwo.Text = StringUtil.ConvertString("Cancel", "Common");
                        btnOne.DialogResult = DialogResult.OK;
                        btnTwo.DialogResult = DialogResult.Cancel;
                    }
                    break;

                default:
                    break;
            }
        }
    }
}