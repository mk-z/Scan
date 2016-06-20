using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.Drawing.Drawing2D;
using Utility;

namespace SDKPlayDemo
{
    public partial class frmDrawFunSet : Form
    {
        /// <summary>
        /// Typeface
        /// </summary>
        public Font FontSet;
        /// <summary>
        /// Format painter
        /// </summary>
        public Brush BrushSet;
        /// <summary>
        /// Display text location
        /// </summary>
        public PointF TextPointSet;
        /// <summary>
        /// Dispaly time
        /// </summary>
        public PointF TimePointSet;
        /// <summary>
        /// Display text content
        /// </summary>
        public string DisplayText;
        /// <summary>
        /// Whether to show time
        /// </summary>
        public bool ShowTime;
        /// <summary>
        /// Whether to press the button
        /// </summary>
        public bool BlnOK=true;
        /// <summary>
        /// Whether to display custom drawing
        /// </summary>
        public bool BlnDraw = false;
        /// <summary>
        /// Drawing format[0:curve; 1:round: 2:sector]
        /// </summary>
        public int DrawStyle = 0;
        /// <summary>
        /// Color
        /// </summary>
        private Color pColor;
        public frmDrawFunSet()
        {
            InitializeComponent();
        }
        /// <summary>
        /// Image loading process
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void frmDrawFunSet_Load(object sender, EventArgs e)
        {
            pColor = Color.Red;

            StringUtil.InitControlText(this);
        }
        /// <summary>
        /// Comfirm button press to process
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btnOK_Click(object sender, EventArgs e)
        {
            FontSet = txtDisplayText.Font;
            BrushSet=new SolidBrush(pColor);
            TextPointSet = new PointF((float)numDisplayTextX.Value, (float)numDisplayTextY.Value);
            TimePointSet = new PointF((float)numDisplayTimeX.Value, (float)numDisplayTimeY.Value);
            DisplayText = txtDisplayText.Text.ToString().Trim();
            ShowTime = chkDisplayTime.Checked;
            BlnDraw = chkDraw.Checked;
            DrawStyle = cmbDrawStyle.SelectedIndex;
            this.Close();
        }
        /// <summary>
        /// press the button to set the font
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btnFontSet_Click(object sender, EventArgs e)
        {
            fdlMain.ShowColor = true;
            if (fdlMain.ShowDialog() == DialogResult.OK)
            {
                txtDisplayText.Font = fdlMain.Font;
                txtDisplayText.ForeColor = fdlMain.Color;
            }
        }
        /// <summary>
        /// press the button to set color
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btnColorSet_Click(object sender, EventArgs e)
        {
            cdlMain.FullOpen = true;
            if (cdlMain.ShowDialog() == DialogResult.OK)
            {
                pColor = cdlMain.Color;
                txtDisplayText.ForeColor = pColor;
            }
        }
        /// <summary>
        /// Process of the pressed cancel button 
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btnCancel_Click(object sender, EventArgs e)
        {
            BlnOK = false;
        }

    }
}