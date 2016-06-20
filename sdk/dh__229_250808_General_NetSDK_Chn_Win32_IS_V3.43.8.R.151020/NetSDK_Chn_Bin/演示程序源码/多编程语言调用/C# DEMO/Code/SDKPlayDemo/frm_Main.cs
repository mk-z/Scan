using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using PlaySDK;
using Utility;


namespace SDKPlayDemo
{
    public partial class frm_Main : Form
    {
        /// <summary>
        /// Program message prompts Title 
        /// </summary>
        private const string pMsgTitle = "PlaySDK Demo program";
        /// <summary>
        /// Decoding the callback type
        /// </summary>
        private STREAM_TYPE stmType = STREAM_TYPE.STREAM_WITHOUT;//None
        /// <summary>
        /// Broadcast data correction
        /// </summary>
        private DecCBFun playCBFun;
        /// <summary>
        /// Save the image path
        /// </summary>
        private string strSavePicPath="";
        /// <summary>
        /// Video size model
        /// </summary>
        private int pPlayVideoSizeMode = 0;
        /// <summary>
        /// If the loop
        /// </summary>
        private bool blnLoop = false;

        #region << Character superposition processing related variables >>
        /// <summary>
        /// Display the character of the text
        /// </summary>
        private string pDisplayText;
        /// <summary>
        /// Font format, no separate time font and display character font, use the same font both
        /// </summary>
        private Font pFontSet;
        /// <summary>
        /// The format paintbrush for font rendering
        /// </summary>
        private Brush pBrushSet;
        /// <summary>
        /// Display the location point of the character 
        /// </summary>
        private PointF pTextPointSet;
        /// <summary>
        /// Display the location of time
        /// </summary>
        private PointF pTimePointSet;
        /// <summary>
        /// Whether to display the time
        /// </summary>
        private bool pShowTime;
        /// <summary>
        /// Whether to display the self drawing
        /// </summary>
        private bool pShowDraw=false;
        /// <summary>
        /// Drawing format
        /// </summary>
        private int pDrawStyle;
        #endregion
        /// <summary>
        /// Video color information preservation
        /// </summary>
        private COLOR_STRUCT pColor = new COLOR_STRUCT();
        /// <summary>
        /// Custom drawing callback(for character overlay)
        /// </summary>
        private DrawFun dFun;

        public frm_Main()
        {
            InitializeComponent();
        }
        private void frm_Main_Load(object sender, EventArgs e)
        {
            chkEnableSound.Checked = true;//Judge whether it is the allowed sound
            //The initial value of the character superposition
            pShowTime =true;
            pTextPointSet = new PointF(100,10);
            pTimePointSet = new PointF(200,30);
            pFontSet = this.Font;
            pBrushSet = new SolidBrush(Color.Red);
            pDisplayText = "";
            //Setting screen controls available properties
            SetOpenCloseFileControl(0);
            //Play data callback settings
            playCBFun = new DecCBFun(pDecCBFun);
            SetCallBackTypeCheck(stmType);
            mnuSizeTrue_Click(null, null);
            //Character superposition settings
            dFun = new DrawFun(DrawFun);
            NETPlay.NETRigisterDrawFun(0, dFun, 0);//Character overlay function demonstration

            StringUtil.InitControlText(this);
        }

        /// <summary>
        /// Audio allowed settings
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void chkEnableSound_CheckedChanged(object sender, EventArgs e)
        {
            if (chkEnableSound.Checked)
            {
                chkEnableSound.Image=imlMain.Images["AUDIO_ENABLE"];                
                NETPlay.NETPlayControl(PLAY_COMMAND.PlaySound, 0);                
            }
            else
            {
                chkEnableSound.Image = imlMain.Images["AUDIO_DISABLE"];
                NETPlay.NETPlayControl(PLAY_COMMAND.StopSound);
            }
            trbSound.Enabled = chkEnableSound.Checked;
            mnuSoundUp.Enabled = trbSound.Enabled;
            mnuSoundDown.Enabled = trbSound.Enabled;
            mnuSoundSwitch.Checked = chkEnableSound.Checked;
            mnuSoundSwitch.Image = chkEnableSound.Image;
        }

        
        /// <summary>
        /// Open video file menu processing
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void mnuOpenFile_Click(object sender, EventArgs e)
        {
            if (ofdMain.ShowDialog() == DialogResult.OK)
            {
                if (NETPlay.NETPlayControl(PLAY_COMMAND.OpenFile, 0, ofdMain.FileName))
                {
                        SetOpenCloseFileControl(1);                                                
                        stlTotalTime.Text = NETPlay.NETConvertToTime(NETPlay.NETPlayControl(PLAY_COMMAND.GetFileTotalTime, 0, true),1,"HH:mm:ss");
                        bool blnReturn=NETPlay.NETPlayControl(PLAY_COMMAND.GetColor,0,(uint)picPlayMain.Handle,ref pColor);
                        if (blnReturn)
                        {
                            hsbBrightness.Value = pColor.pBrightness;
                            hsbContrast.Value = pColor.pContrast;
                            hsbHue.Value = pColor.pHue;
                            hsbSaturation.Value = pColor.pSaturation;
                        }
                        trbSound.Value =(int) NETPlay.NETPlayControl(PLAY_COMMAND.GetVolume, 0,true);
                }
                else
                {
                    MessageBox.Show("Failed to open the file!", pMsgTitle);
                }
            }
        }

        /// <summary>
        /// Playing the video menu processing
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void mnuStart_Click(object sender, EventArgs e)
        {
            if (!NETPlay.NETPlayControl(PLAY_COMMAND.Start, 0, this.picPlayMain.Handle))            
            {
                MessageBox.Show("Failed to play file!", pMsgTitle);
            }
            else
            {
                SetPlayStopControl(1);
                chkEnableSound_CheckedChanged(sender, e);//Voice switch6
            }
         
        }
        /// <summary>
        /// Close the file menu processing
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void mnuCloseFile_Click(object sender, EventArgs e)
        {
            if (!NETPlay.NETPlayControl(PLAY_COMMAND.CloseFile, 0))
            {
                MessageBox.Show("Failed to close file!", pMsgTitle);
            }
            else
            {
                this.picPlayMain.Refresh();//Refresh the screen 
                if (mnuStop.Enabled)
                {
                    mnuStop_Click(sender, e);
                }
                SetOpenCloseFileControl(0);
            }            
        }
        /// <summary>
        /// Exit the menu processing
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void mnuExit_Click(object sender, EventArgs e)
        {
            this.Close();
        }
        /// <summary>
        /// The processing of closing the window
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void frm_Main_FormClosing(object sender, FormClosingEventArgs e)
        {
            //The cleaning work of closing the added window
            if (mnuStop.Enabled)
            {
                mnuStop_Click(sender, e);
            }
        }
        /// <summary>
        /// The processing of playing the pause menu 
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void mnuPause_Click(object sender, EventArgs e)
        {
            if (NETPlay.NETPlayControl(PLAY_COMMAND.Pause, 0))
            {
                SetPauseResumControl(1);
            }
            else
            {
                MessageBox.Show("Failed to pause playback!", pMsgTitle);
            }            
        }
        /// <summary>
        /// The processing of stopping playing the menu 
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void mnuStop_Click(object sender, EventArgs e)
        {
            if (!NETPlay.NETPlayControl(PLAY_COMMAND.Stop, 0))
            {
                MessageBox.Show("Failed to stop play!", pMsgTitle);
            }
            else
            {
                SetPlayStopControl(0);
                trbPlayFrames.Value = 0;
                stlCurrentFrame.Text = "0";
                stlCurrentTime.Text = "00:00:00";
                this.picPlayMain.Refresh();//Refresh the screen 
            }            
        }
        

        /// <summary>
        /// Play/Stop button processing
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btnStartPlay_Click(object sender, EventArgs e)
        {
            if (btnStartPlay.Tag.ToString() == "Start")
            {
                mnuStart_Click(null, null);
            }
            else
            {
                mnuStop_Click(null, null);
            }
        }

        /// <summary>
        /// Play callbace function
        /// </summary>
        /// <param name="nPort"></param>
        /// <param name="pBuf"></param>
        /// <param name="nSize"></param>
        /// <param name="pFrameInfo"></param>
        /// <param name="nReserved1"></param>
        /// <param name="nReserved2"></param>
        private void pDecCBFun(int nPort, ref String pBuf,int nSize, ref  FRAME_INFO pFrameInfo, int nReserved1, int nReserved2)
        {
            this.picPlayMain.Height = pFrameInfo.nHeight;
            this.picPlayMain.Width = pFrameInfo.nWidth;
            this.stlCurrentTime.Text = pFrameInfo.nStamp.ToString();

        }

        /// <summary>
        /// The menu processing of continue to play
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void mnuResum_Click(object sender, EventArgs e)
        {
            if (NETPlay.NETPlayControl(PLAY_COMMAND.ReSume, 0))
            {                
                SetPauseResumControl(0);
            }
            else
            {
                MessageBox.Show("Failed to continue playing!", pMsgTitle);
            }            
        }

        /// <summary>
        /// The menu processing of pause play
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btnPauseResume_Click(object sender, EventArgs e)
        {
            if (btnPauseResume.Tag.ToString() == "Pause")
            {
                mnuPause_Click(null, null);
            }
            else
            {
                mnuResum_Click(null, null);
            }
        }

        /// <summary>
        /// Related control of setting pause/continue
        /// </summary>
        /// <param name="intPause">0:Suspend;1:Continue;2:All invalid</param>
        private void SetPauseResumControl(int intPause)
        {
            switch (intPause)
            { 
                case 0:
                    mnuPause.Enabled = true;
                    btnPauseResume.Enabled = true;
                    mnuResum.Enabled = false;
                    btnPauseResume.Image = imlMain.Images["PAUSE_ENABLE"];
                    btnPauseResume.Tag = "Pause";
                    timerGetPlayInfo.Enabled = true;
                    break;
                case 1:
                    mnuPause.Enabled = false;
                    mnuResum.Enabled = true;
                    btnPauseResume.Image = imlMain.Images["RESUM_ENABLE"];
                    btnPauseResume.Tag = "Resum";
                    timerGetPlayInfo.Enabled = false;
                    break;
                case 2:
                    mnuPause.Enabled = false;
                    mnuResum.Enabled = false;
                    btnPauseResume.Image = imlMain.Images["PAUSE_ENABLE"];
                    btnPauseResume.Tag = "Pause";
                    btnPauseResume.Enabled = false;
                    timerGetPlayInfo.Enabled = false;
                    break;
            }
        }
        /// <summary>
        /// Set the related control of play/stop
        /// </summary>
        /// <param name="intPlay">0:Play;1:Stop;2:All invalid;3:Play valid(single-frame playback without control)</param>
        private void SetPlayStopControl(int intPlay)
        {
            switch (intPlay)
            { 
                case 0:
                    mnuStart.Enabled = true;
                    mnuStop.Enabled = false;
                    btnStartPlay.Enabled = true;
                    btnStartPlay.Tag = "Start";
                    btnStartPlay.Image = imlMain.Images["PLAY_ENABLE"];
                    SetPauseResumControl(2);
                    SetOtherControl(1);
                    SetStepControl(1);
                    mnuSetDisplayRegion.Enabled = false;
                    timerGetPlayInfo.Enabled = false;
                    trbPlayFrames.Enabled = false;                    
                    break;
                case 1:
                    mnuStart.Enabled = false;
                    mnuStop.Enabled = true;
                    btnStartPlay.Tag = "Stop";
                    btnStartPlay.Image = imlMain.Images["STOP_ENABLE"];
                    mnuSetDisplayRegion.Enabled = true;
                    trbPlayFrames.Enabled = true;
                    SetPauseResumControl(0);
                    SetOtherControl(0);
                    SetStepControl(0);
                    timerGetPlayInfo.Enabled = true;                    
                    break;
                case 2:
                    mnuStart.Enabled = false;
                    mnuStop.Enabled = false;
                    btnStartPlay.Tag = "Start";
                    btnStartPlay.Image = imlMain.Images["PLAY_ENABLE"];
                    btnStartPlay.Enabled = false;
                    SetPauseResumControl(2);
                    SetOtherControl(1);
                    SetStepControl(1);
                    trbPlayFrames.Enabled = false;
                    timerGetPlayInfo.Enabled = false;
                    break;
                case 3:
                    mnuStart.Enabled = true;
                    mnuStop.Enabled = false;
                    btnStartPlay.Enabled = true;
                    btnStartPlay.Tag = "Start";
                    btnStartPlay.Image = imlMain.Images["PLAY_ENABLE"];
                    SetPauseResumControl(2);
                    SetOtherControl(1);
                    timerGetPlayInfo.Enabled = true;                    
                    break;
            }
        }
        
        /// <summary>
        /// Set the related control of Open/Close filev
        /// </summary>
        /// <param name="intOpen">0:Open;1:Close;2:Cut;3:All invalid</param>
        private void SetOpenCloseFileControl(int intOpen)
        {
            switch (intOpen)
            { 
                case 0:
                    mnuOpenFile.Enabled = true;
                    mnuCloseFile.Enabled = false;
                    mnuCutFile.Enabled = false;
                    SetPlayStopControl(2);
                    break;
                case 1:
                    mnuCloseFile.Enabled = true;
                    mnuCutFile.Enabled = true;
                    mnuOpenFile.Enabled = false;
                    SetPlayStopControl(0);
                    break;
                case 2:
                    mnuCutFile.Enabled = true;                    
                    break;
                case 3:
                    mnuOpenFile.Enabled = false;
                    mnuCloseFile.Enabled = false;
                    mnuCutFile.Enabled = false;
                    break;
            }
        }
        /// <summary>
        /// Set the related control
        /// </summary>
        /// <param name="intStepNext">0:Effective control;1:Ineffective control</param>
        private void SetOtherControl(int intStepNext)
        {
            bool blnEnable = false;
            switch (intStepNext)
            { 
                case 0:
                    blnEnable = true;
                    break;
                case 1:
                    blnEnable = false;
                    break;
            }
            btnPlayFast.Enabled = blnEnable;
            btnPlaySlow.Enabled = blnEnable;
            btnFullScreen.Enabled = blnEnable;
            mnuLoop.Enabled = blnEnable;
            mnuSlow.Enabled = blnEnable;
            mnuFast.Enabled = blnEnable;            
            btnPlayFast.Image = imlMain.Images["FAST_ENABLE"];
            btnPlaySlow.Image = imlMain.Images["SLOW_ENABLE"];
        }
        /// <summary>
        /// Single frame play related widget 
        /// </summary>
        /// <param name="intStep">0:Effective control;1:Ineffective control</param>
        private void SetStepControl(int intStep)
        {
            bool blnEnable = false;
            switch (intStep)
            {
                case 0:
                    blnEnable = true;
                    break;
                case 1:
                    blnEnable = false;
                    break;
            }
            btnStepBack.Enabled = blnEnable;
            btnStepOnByOne.Enabled = blnEnable;
            btnToBegin.Enabled = blnEnable;
            btnToEnd.Enabled = blnEnable;
            mnuStepBack.Enabled = blnEnable;
            mnuStepOneByOne.Enabled = blnEnable;
            mnuToBegin.Enabled = blnEnable;
            mnuToEnd.Enabled = blnEnable;
            mnuFullScreen.Enabled = blnEnable;
            mnuCatchPic.Enabled = blnEnable;
            btnCatchPic.Enabled = blnEnable;
            //Sound related widget
            chkEnableSound.Enabled = blnEnable;
            trbSound.Enabled = blnEnable;
            mnuSoundControl.Enabled = blnEnable;
            //Color related widget
            hsbBrightness.Enabled = blnEnable;
            hsbContrast.Enabled = blnEnable;
            hsbHue.Enabled = blnEnable;
            hsbSaturation.Enabled = blnEnable;
            mnuColorControl.Enabled = blnEnable;
            btnStepBack.Image = imlMain.Images["STEPBACK_ENABLE"];
            btnStepOnByOne.Image = imlMain.Images["STEP_ENABLE"];
            btnToBegin.Image = imlMain.Images["TOBEGIN_ENABLE"];
            btnToEnd.Image = imlMain.Images["TOEND_ENABLE"];
            btnCatchPic.Image = imlMain.Images["CATCHPIC_ENABLE"];
            btnFullScreen.Image = imlMain.Images["FULLSCREEN_ENABLE"];

        }

        /// <summary>
        /// Quik play menu dispose
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void mnuFast_Click(object sender, EventArgs e)
        {
            if (!NETPlay.NETPlayControl(PLAY_COMMAND.Fast,0))
            {
                MessageBox.Show("Quik play failure!", pMsgTitle);
            }
        }

        /// <summary>
        /// Slow play menu dispose
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void mnuSlow_Click(object sender, EventArgs e)
        {
            if (!NETPlay.NETPlayControl(PLAY_COMMAND.Slow,0))
            {
                MessageBox.Show("Single frame play failure!", pMsgTitle);
            }
        }

        /// <summary>
        /// Single frame play menu dispose
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void mnuStepOneByOne_Click(object sender, EventArgs e)
        {
            if (!NETPlay.NETPlayControl(PLAY_COMMAND.OneByOne, 0))
            {
                MessageBox.Show("Single frame play failure!", pMsgTitle);
            }
            else
            { 
                //Play/stop button as playing state
                SetPlayStopControl(3);
                
            }
        }
        /// <summary>
        /// Single frame play
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btnStepOnByOne_Click(object sender, EventArgs e)
        {
            mnuStepOneByOne_Click(sender, e);
        }
        /// <summary>
        /// Callback play type: none
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void mnuCallBack_WithOut_Click(object sender, EventArgs e)
        {
            stmType = STREAM_TYPE.STREAM_WITHOUT;
            SetCallBackTypeCheck(stmType);
        }

        /// <summary>
        /// Set Callback play type select menu
        /// </summary>
        /// <param name="stmTp"></param>
        private void SetCallBackTypeCheck(STREAM_TYPE stmTp)
        {
            bool blnChecked = false;
            mnuCallBack_Audio.Checked = blnChecked;
            mnuCallBack_Audio.Image = imlMain.Images["AUDIO_ENABLE"];
            mnuCallBack_Mix.Checked = blnChecked;
            mnuCallBack_Mix.Image = imlMain.Images["MIX_ENABLE"];
            mnuCallBack_Video.Checked = blnChecked;
            mnuCallBack_Video.Image = imlMain.Images["VIDEO_ENABLE"];
            mnuCallBack_WithOut.Checked = blnChecked;
            mnuCallBack_WithOut.Image = imlMain.Images["WITHOUT_ENABLE"];            
            blnChecked=true;
            switch (stmTp)
            { 
                case STREAM_TYPE.STREAM_WITHOUT:
                    mnuCallBack_WithOut.Checked = blnChecked;
                    mnuCallBack_WithOut.Image = imlMain.Images["CHECKED_ENABLE"];
                    break;
                case STREAM_TYPE.STREAM_AUDIO:
                    mnuCallBack_Audio.Checked = blnChecked;
                    mnuCallBack_Audio.Image = imlMain.Images["CHECKED_ENABLE"];
                    break;
                case STREAM_TYPE.STREAM_VIDEO:
                    mnuCallBack_Video.Checked = blnChecked;
                    mnuCallBack_Video.Image = imlMain.Images["CHECKED_ENABLE"];
                    break;
                case STREAM_TYPE.STREAM_MIX:
                    mnuCallBack_Mix.Checked = blnChecked;
                    mnuCallBack_Mix.Image = imlMain.Images["CHECKED_ENABLE"];
                    break;
            }
        }
        /// <summary>
        /// Decode callback flow-audio menu dispose
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void mnuCallBack_Audio_Click(object sender, EventArgs e)
        {
            stmType = STREAM_TYPE.STREAM_AUDIO;
            SetCallBackTypeCheck(stmType);
        }
        /// <summary>
        /// Decode callback flow-video menu dispose
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void mnuCallBack_Video_Click(object sender, EventArgs e)
        {
            stmType = STREAM_TYPE.STREAM_VIDEO;
            SetCallBackTypeCheck(stmType);
        }
        /// <summary>
        /// Decode callback flow-hybrid menu dispose
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void mnuCallBack_Mix_Click(object sender, EventArgs e)
        {
            stmType = STREAM_TYPE.STREAM_MIX;
            SetCallBackTypeCheck(stmType);
        }

        /// <summary>
        /// Looping menu dispose
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void mnuLoop_Click(object sender, EventArgs e)
        {
            if (mnuLoop.Checked)
            {
                mnuLoop.Image = imlMain.Images["CHECKED_ENABLE"];                
            }
            else
            {
                mnuLoop.Image = imlMain.Images["LOOP_ENABLE"];
            }
            blnLoop = mnuLoop.Checked;
        }
        /// <summary>
        /// Full screen menu dispose
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void mnuFullScreen_Click(object sender, EventArgs e)
        {
            stsMain.Visible = !mnuFullScreen.Checked;
            palMain.Visible = !mnuFullScreen.Checked;
            trbPlayFrames.Visible = !mnuFullScreen.Checked;
            groupBox1.Visible = !mnuFullScreen.Checked;
            
            musMain.Visible = !mnuFullScreen.Checked;
            if (mnuFullScreen.Checked)
            {
                this.FormBorderStyle = FormBorderStyle.None;
                this.WindowState = FormWindowState.Maximized;
                mnuFullScreen.Image = imlMain.Images["CHECKED_ENABLE"];
                picPlayMain.Parent = this;
                
                
            }
            else
            {
                this.FormBorderStyle = FormBorderStyle.Sizable;
                this.WindowState = FormWindowState.Normal;
                mnuFullScreen.Image = imlMain.Images["FULLSCREEN_ENABLE"];
                picPlayMain.Parent = palMain;
                
            }
            
        }
        /// <summary>
        /// Press screenshot button
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btnCatchPic_Click(object sender, EventArgs e)
        {
            mnuCatchPic_Click(sender, e);
        }
        /// <summary>
        /// Press full screen button
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btnFullScreen_Click(object sender, EventArgs e)
        {
            mnuFullScreen.Checked = !mnuFullScreen.Checked;
            mnuFullScreen_Click(sender,e);
        }

        /// <summary>
        /// Screenshots menu dispose
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void mnuCatchPic_Click(object sender, EventArgs e)
        {
            //None select image save path, then it should choose save path
            if (strSavePicPath.Length == 0)
            {
                if (fbdMain.ShowDialog() == DialogResult.OK)
                {
                    strSavePicPath = fbdMain.SelectedPath;
                }
                else
                {
                    return;
                }
            }
            //Screenshot dispose code
            bool blnSavePic = false;
            string saveFilePath=strSavePicPath+@"\"+(DateTime.Now.ToString("yyyyMMdd_HHmmss"))+".bmp";            
            blnSavePic = NETPlay.NETPlayControl(PLAY_COMMAND.CatchPic, 0,saveFilePath);
            if (!blnSavePic)            
            {
                MessageBox.Show("Single frame play failure!\n" + saveFilePath, pMsgTitle);
            }

        }
        /// <summary>
        /// Double-click playing picture dispose
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void picPlayMain_DoubleClick(object sender, EventArgs e)
        {
            if (btnFullScreen.Enabled)
            {
                btnFullScreen_Click(sender, e);
            }
        }

        /// <summary>
        /// Sound control slider dispose
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void trbSound_ValueChanged(object sender, EventArgs e)
        {
            mnuSoundUp.Enabled = (trbSound.Value == trbSound.Maximum ? false : true);
            mnuSoundDown.Enabled = (trbSound.Value == 0 ? false : true);
            NETPlay.NETPlayControl(PLAY_COMMAND.SetVolume, 0,(uint) trbSound.Value);
        }
        /// <summary>
        /// Video brightness
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void hsbBrightness_ValueChanged(object sender, EventArgs e)
        {
            mnuBrightnessUp.Enabled = (hsbBrightness.Value == hsbBrightness.Maximum ? false : true);            
            mnuBrightnessDown.Enabled = (hsbBrightness.Value == 0 ? false : true);
            pColor.pBrightness = hsbBrightness.Value;            
            NETPlay.NETPlayControl(PLAY_COMMAND.SetColor,0,0, ref pColor);
        }
        /// <summary>
        /// Video contrast
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void hsbContrast_ValueChanged(object sender, EventArgs e)
        {
            mnuContrastUp.Enabled = (hsbContrast.Value == hsbContrast.Maximum ? false : true);
            mnuContrastDown.Enabled = (hsbContrast.Value == 0 ? false : true);
            pColor.pContrast = hsbContrast.Value;
            NETPlay.NETPlayControl(PLAY_COMMAND.SetColor, 0, 0, ref pColor);
        }
        /// <summary>
        /// Video saturation
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void hsbSaturation_ValueChanged(object sender, EventArgs e)
        {
            mnuSaturationDown.Enabled = (hsbSaturation.Value == 0 ? false : true);
            mnuSaturationUp.Enabled = (hsbSaturation.Value == hsbSaturation.Maximum ? false : true);
            pColor.pSaturation = hsbSaturation.Value;
            NETPlay.NETPlayControl(PLAY_COMMAND.SetColor, 0, 0, ref pColor);
        }
        /// <summary>
        /// Video tonal
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void hsbHue_ValueChanged(object sender, EventArgs e)
        {
            mnuHueUp.Enabled = (hsbHue.Value == hsbHue.Maximum ? false : true);
            mnuHueDown.Enabled = (hsbHue.Value == 0 ? false : true);
            pColor.pHue = hsbHue.Value;
            NETPlay.NETPlayControl(PLAY_COMMAND.SetColor, 0, 0, ref pColor);
        }
        /// <summary>
        /// Set the current broadcast properties
        /// </summary>
        /// <param name="playedFrameNum"></param>
        /// <param name="playedTime"></param>
        private void SetPlayCurrentInfo(UInt32 playedFrameNum, UInt32 playedTime)
        {            
            stlCurrentFrame.Text = Convert.ToString(playedFrameNum+1);
            stlCurrentTime.Text  =NETPlay.NETConvertToTime(playedTime,1,"HH:MM:SS");
            trbPlayFrames.Value = (int)(playedFrameNum < trbPlayFrames.Maximum ? playedFrameNum : 0);
            if (trbPlayFrames.Maximum <= playedFrameNum+1)
            {
                mnuStop_Click(null, null);
                if (blnLoop)
                {
                    mnuStart_Click(null, null);
                }
            }
        }
        /// <summary>
        /// Picture clock dispose
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void timerGetPlayInfo_Tick(object sender, EventArgs e)
        {
            
            if (pPlayVideoSizeMode != 9)
            {
                FRAME_INFO pFrameInfo = new FRAME_INFO();
                uint totalFrames = NETPlay.NETPlayControl(PLAY_COMMAND.GetFileTotalFrames, 0, true);
                NETPlay.NETPlayControl(PLAY_COMMAND.GetPictureSize, 0, ref pFrameInfo);
                stlTotalFrames.Text = Convert.ToString(totalFrames);
                trbPlayFrames.Maximum =(int) (totalFrames>0?totalFrames:0);
                int pParentHeight;
                int pParentWidth;
                if (palMain.Visible)
                {
                    pParentWidth = palMain.Width;
                    pParentHeight = palMain.Height;
                }
                else
                {
                    pParentWidth = this.Width;
                    pParentHeight = this.Height;
                }
                switch (pPlayVideoSizeMode )
                { 
                    case 0://Original size
                        picPlayMain.Width = pFrameInfo.nWidth;
                        picPlayMain.Height = pFrameInfo.nHeight;
                        picPlayMain.Top = (pParentHeight - picPlayMain.Height) / 2;
                        picPlayMain.Left = (pParentWidth - picPlayMain.Width) / 2;
                        break;
                    case 1://Zoom
                        picPlayMain.Top = 0;
                        picPlayMain.Height = pParentHeight;
                        picPlayMain.Width = Convert.ToInt32( pFrameInfo.nWidth * ((float)pParentHeight / (float)pFrameInfo.nHeight));
                        picPlayMain.Left = (pParentWidth - picPlayMain.Width) / 2;
                        break;
                }
            }
            SetPlayCurrentInfo(NETPlay.NETPlayControl(PLAY_COMMAND.GetCurrentFrameNum, 0, true), NETPlay.NETPlayControl(PLAY_COMMAND.GetPlayedTime, 0, true));
        }
        /// <summary>
        /// Playback progress bar
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void trbPlayFrames_MouseUp(object sender, MouseEventArgs e)
        {
            mnuResum_Click(sender, e);
            //float playPos = ((float)trbPlayFrames.Value / (float)trbPlayFrames.Maximum);
            NETPlay.NETPlayControl(PLAY_COMMAND.SetCurrentFrameNum, 0,(uint)trbPlayFrames.Value);
            
        }
        /// <summary>
        /// Playback progress bar
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void trbPlayFrames_MouseDown(object sender, MouseEventArgs e)
        {
            mnuPause_Click(sender, e);
        }

        /// <summary>
        /// Original size menu dispose
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void mnuSizeTrue_Click(object sender, EventArgs e)
        {
            pPlayVideoSizeMode = 0;
            picPlayMain.Dock = DockStyle.None;
            picPlayMain.Anchor = AnchorStyles.None;
        }

        /// <summary>
        /// Auto-adapt menu dispose
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void mnuSizeRoom_Click(object sender, EventArgs e)
        {
            pPlayVideoSizeMode = 1;
            picPlayMain.Dock = DockStyle.None;
            picPlayMain.Anchor = AnchorStyles.None;
        }
        /// <summary>
        /// Follow size menu dispose
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void mnuVideoResizeByForm_Click(object sender, EventArgs e)
        {
            pPlayVideoSizeMode = 9;
            picPlayMain.Dock = DockStyle.Fill;
        }

        /// <summary>
        /// Single frame play menu dispose
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void mnuStepBack_Click(object sender, EventArgs e)
        {

            if (!NETPlay.NETPlayControl(PLAY_COMMAND.OneByOneBack, 0))
            {
                MessageBox.Show("Single frame play failure!", pMsgTitle);
            }
            else
            {
                //Play/Stop button as paly state
                SetPlayStopControl(3);
            }
        }
        /// <summary>
        /// Single frame play button dispose
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btnStepBack_Click(object sender, EventArgs e)
        {
            mnuStepBack_Click(sender, e);
        }
        /// <summary>
        /// To front frame play menu dispose
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void mnuToBegin_Click(object sender, EventArgs e)
        {
            if (!NETPlay.NETPlayControl(PLAY_COMMAND.ToBegin, 0))
            {
                MessageBox.Show("Location to front frame failure!", pMsgTitle);
            }
            else
            {
                if (mnuPause.Enabled)
                {
                    mnuPause_Click(null, null);
                }
                trbPlayFrames.Value = 0;
                stlCurrentFrame.Text = "1";
            }

        }
        /// <summary>
        /// To last frame play menu dispose
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void mnuToEnd_Click(object sender, EventArgs e)
        {
            if (!NETPlay.NETPlayControl(PLAY_COMMAND.ToEnd,0))
            {
                MessageBox.Show("Location to last frame failure!", pMsgTitle);
            }
            else
            {
                if (mnuPause.Enabled)
                {
                    mnuPause_Click(null, null);
                }
                trbPlayFrames.Value = (trbPlayFrames.Maximum - 1>0?trbPlayFrames.Maximum - 1:0);
                stlCurrentFrame.Text = Convert.ToString((uint.Parse(stlTotalFrames.Text) - 1));
            }
        }
        /// <summary>
        /// To the front frame
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btnToBegin_Click(object sender, EventArgs e)
        {
            mnuToBegin_Click(sender, e);
        }
        /// <summary>
        /// To the last frame
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btnToEnd_Click(object sender, EventArgs e)
        {
            mnuToEnd_Click(sender, e);
        }
        /// <summary>
        /// Sound control dispose
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void mnuSoundSwitch_Click(object sender, EventArgs e)
        {
            chkEnableSound.Checked = !chkEnableSound.Checked;
            chkEnableSound_CheckedChanged(null, null);
        }
        /// <summary>
        /// Volume up processing
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void mnuSoundUp_Click(object sender, EventArgs e)
        {
            if (trbSound.Value + 500 > trbSound.Maximum)
            {
                trbSound.Value = trbSound.Maximum;
            }
            else
            {
                trbSound.Value += 500;
            }
            trbSound_ValueChanged(null,null);
        }
        /// <summary>
        /// Volume down processing
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void mnuSoundDown_Click(object sender, EventArgs e)
        {
            if (trbSound.Value - 500 <0)
            {
                trbSound.Value = 0;
            }
            else
            {
                trbSound.Value -= 500;
            }
            trbSound_ValueChanged(null, null);
        }

        #region << video play color configuration >>
        private void mnuBrightnessUp_Click(object sender, EventArgs e)
        {
            if (hsbBrightness.Value + 1 > hsbBrightness.Maximum)
            {
                hsbBrightness.Value = hsbBrightness.Maximum;
            }
            else
            {
                hsbBrightness.Value += 1;
            }
            hsbBrightness_ValueChanged(null, null);
        }

        private void mnuBrightnessDown_Click(object sender, EventArgs e)
        {
            if (hsbBrightness.Value -1 > hsbBrightness.Maximum)
            {
                hsbBrightness.Value =0;
            }
            else
            {
                hsbBrightness.Value -= 1;
            }
            hsbBrightness_ValueChanged(null, null);
        }

        private void mnuContrastUp_Click(object sender, EventArgs e)
        {
            if (hsbContrast.Value + 1 > hsbContrast.Maximum)
            {
                hsbContrast.Value = hsbContrast.Maximum;
            }
            else
            {
                hsbContrast.Value += 1;
            }
            hsbContrast_ValueChanged(null, null);
        }

        private void mnuContrastDown_Click(object sender, EventArgs e)
        {
            if (hsbContrast.Value -1 > hsbContrast.Maximum)
            {
                hsbContrast.Value = hsbContrast.Maximum;
            }
            else
            {
                hsbContrast.Value -= 1;
            }
            hsbContrast_ValueChanged(null, null);
        }

        private void mnuSaturationUp_Click(object sender, EventArgs e)
        {
            if (hsbSaturation.Value + 1 > hsbSaturation.Maximum)
            {
                hsbSaturation.Value = hsbSaturation.Maximum;
            }
            else
            {
                hsbSaturation.Value += 1;
            }
            hsbSaturation_ValueChanged(null, null);
        }

        private void mnuSaturationDown_Click(object sender, EventArgs e)
        {
            if (hsbSaturation.Value - 1 > hsbSaturation.Maximum)
            {
                hsbSaturation.Value = hsbSaturation.Maximum;
            }
            else
            {
                hsbSaturation.Value -= 1;
            }
            hsbSaturation_ValueChanged(null, null);
        }

        private void mnuHueUp_Click(object sender, EventArgs e)
        {
            if (hsbHue.Value + 1 > hsbHue.Maximum)
            {
                hsbHue.Value = hsbHue.Maximum;
            }
            else
            {
                hsbHue.Value += 1;
            }
            hsbHue_ValueChanged(null, null);
        }

        private void mnuHueDown_Click(object sender, EventArgs e)
        {
            if (hsbHue.Value + 1 > hsbHue.Maximum)
            {
                hsbHue.Value = hsbHue.Maximum;
            }
            else
            {
                hsbHue.Value -= 1;
            }
            hsbHue_ValueChanged(null, null);
        }

        #endregion

        private void mnuAbout_Click(object sender, EventArgs e)
        {
            frmAbout fa = new frmAbout();
            fa.ShowDialog();
        }
        /// <summary>
        /// Local amplification demo
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void mnuSetDisplayRegion_Click(object sender, EventArgs e)
        {
            frmDisplayRegion fdr = new frmDisplayRegion();//Local amplification demo window          
            fdr.DisplayRegionPort = 0;
            fdr.ShowDialog();
        }
        /// <summary>
        /// video conversion demo
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void mnuDataRecord_Click(object sender, EventArgs e)
        {
            frmDataRecord fdr = new frmDataRecord();    //Data flow video demo window            
            fdr.ShowDialog();
        }

        #region << Character superposition dispose >>

        /// <summary>
        /// Character superposition function
        /// </summary>
        /// <param name="PlayPort"></param>
        /// <param name="Hdc"></param>
        /// <param name="UserData"></param>
        private void DrawFun(int PlayPort, IntPtr Hdc, int UserData)
        {
            Graphics gps = Graphics.FromHdc(Hdc);
            if (pDisplayText.Length > 0)
            {
                gps.DrawString(pDisplayText, pFontSet/*The text font*/, pBrushSet/*The format paintbrush*/, pTextPointSet);
            }
            if (pShowTime == true)
            {
                gps.DrawString(DateTime.Now.ToString("yyyy-MM-dd hh:mm:ss"), pFontSet/*The text font*/, pBrushSet/*The format paintbrush*/, pTimePointSet);
            }
            if (pShowDraw == true)
            {
                switch (pDrawStyle)
                {
                    case 0://Curve
                        gps.DrawBezier(Pens.Yellow, pTextPointSet, new PointF(pTextPointSet.X + 100, pTextPointSet.Y + 10), pTimePointSet, new PointF(pTimePointSet.X + 200, pTimePointSet.Y));
                        break;
                    case 1://Circle
                        gps.DrawEllipse(Pens.Yellow, pTextPointSet.X, pTextPointSet.Y, pTimePointSet.X, pTimePointSet.Y);
                        break;
                    case 2://Fan
                        //gps.DrawPie(Pens.BlueViolet , pTextPointSet.X, pTextPointSet.Y, pTimePointSet.X, pTimePointSet.Y, 30, -150);
                        gps.DrawPie(new Pen(pBrushSet, 4), 100, 150, 200, 250, 0, -90);
                        break;
                }

            }
            //Others to draw need to be added in the soft 

        }

        #endregion

        /// <summary>
        /// Character superposition menu dispose
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void mnuDrawFunSet_Click(object sender, EventArgs e)
        {
            frmDrawFunSet fDFS=new frmDrawFunSet();
            fDFS.ShowDialog();
            if (fDFS.BlnOK)
            {
                pShowTime = fDFS.ShowTime;
                pTextPointSet = fDFS.TextPointSet;
                pTimePointSet = fDFS.TimePointSet;
                pFontSet = fDFS.FontSet;
                pBrushSet = fDFS.BrushSet;
                pDisplayText = fDFS.DisplayText;
                pShowDraw = fDFS.BlnDraw;
                pDrawStyle = fDFS.DrawStyle;
            }
        }

    }
}