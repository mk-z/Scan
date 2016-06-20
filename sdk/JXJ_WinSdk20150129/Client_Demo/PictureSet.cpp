// PictureSet.cpp : 实现文件
//

#include "stdafx.h"
#include "Client_Demo.h"
#include "PictureSet.h"
#include "Pub_Data.h"



// CPictureSet 对话框

IMPLEMENT_DYNAMIC(CPictureSet, CDialog)

CPictureSet::CPictureSet(CWnd* pParent /*=NULL*/)
	: CDialog(CPictureSet::IDD, pParent)
{

}

CPictureSet::~CPictureSet()
{
	DestroyWindow();
}

void CPictureSet::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_CHANNEL, m_comChannel);
	DDX_Control(pDX, IDC_SLIDER_COMPARE, m_Compare);
	DDX_Control(pDX, IDC_SLIDER_LIGHT, m_Light);
	DDX_Control(pDX, IDC_SLIDER_GRAY, m_Gray);
	DDX_Control(pDX, IDC_SLIDER_SATURATION, m_Saturation);
	DDX_Control(pDX, IDC_SLIDER_SHAR, m_Shar);
	DDX_Control(pDX, IDC_CHECK_IMAGE, m_Image);
	DDX_Control(pDX, IDC_CHECK_ROLLTURN, m_RollTurn);
	DDX_Control(pDX, IDC_COMBO_FLICKER, m_Flicker);
	DDX_Control(pDX, IDC_COMBO_WHITETYPE, m_WhiteType);
	DDX_Control(pDX, IDC_SLIDER_WHITE_RED, m_White_Red);
	DDX_Control(pDX, IDC_SLIDER_WHITE_BLUE, m_White_Blue);
	DDX_Control(pDX, IDC_COMBO_ROTE, m_Rote);
	DDX_Control(pDX, IDC_CHECK_IMAGE, m_Image);
	DDX_Control(pDX, IDC_CHECK_ROLLTURN, m_RollTurn);
	DDX_Control(pDX, IDC_COMBO_FLICKER, m_Flicker);
	DDX_Control(pDX, IDC_COMBO_WHITETYPE, m_WhiteType);
	//DDX_Control(pDX, IDC_SLIDER_WHITE_RED, m_White_Red);
	//DDX_Control(pDX, IDC_SLIDER_WHITE_BLUE, m_White_Blue);
	DDX_Control(pDX, IDC_COMBOLIGHTTYE, m_LightType);
	DDX_Control(pDX, IDC_SLIDER_LIGHTMAKEUP, m_LightWakeUp);
	DDX_Control(pDX, IDC_COMBOAUTOLIGHT, m_AutoLight);
	DDX_Control(pDX, IDC_COMBO_OUTSPRAY, m_OutSprat);
	DDX_Control(pDX, IDC_SLIDER_JIBIANCHECK, m_JiBianCheck);
	DDX_Control(pDX, IDC_SLIDER_WIDTHSTATE, m_WidthState);
	DDX_Control(pDX, IDC_COMBO_SHUTTER, m_bShutter);
}


BEGIN_MESSAGE_MAP(CPictureSet, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_FLASH, &CPictureSet::OnBnClickedButtonFlash)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &CPictureSet::OnBnClickedButtonSave)
	ON_WM_HSCROLL()
	ON_WM_LBUTTONUP()
	ON_BN_CLICKED(IDC_BUTTON_RESET, &CPictureSet::OnBnClickedButtonReset)
	ON_WM_CLOSE()
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CPictureSet 消息处理程序
BOOL CPictureSet::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	
	m_comChannel.AddString(_T("0"));
	m_comChannel.SetCurSel(0);

	m_Compare.SetRange(0,255);
	m_Light.SetRange(0,255);
	m_Gray.SetRange(0,255);
	m_Saturation.SetRange(0,255);
	m_Shar.SetRange(0,255);
	m_WidthState.SetRange(0, 255);
	/*
	Image//镜像(图像左右调换) 1 镜像 0 不镜像
	uint32_t flip;							RollTurn//翻转(图像上下调换) 1 翻转 0 不翻转
	uint32_t hz;							Flicker//抗闪烁 0-关闭 1-50Hz 2-60 Hz 
	uint32_t awb_mode;						WhiteType//白平衡模式 0 自动白平衡 1手动白平衡
	uint32_t awb_red;						White_Red//白平衡红色强度 0-255
	uint32_t awb_blue;						White_Blue//白平衡蓝色强度 0-255
	uint32_t wdr;										//宽动态0 关闭 1-255为宽动态强度
	uint32_t iris_type;						LightType//光圈类型 0 手动光圈 1 自动光圈
	uint32_t exp_compensation;				LightWakeUp//曝光补偿 0-255
	uint32_t ae_mode;	 					AutoLight//自动曝光模式（0-2）：0 噪声优先	  1 帧率优先	2 增益优先
	uint32_t ldc_value;									//畸变校正强度(0-255)：0 不启用    1-255 畸变校正强度值
	uint32_t anti_fog;	 					OutSprat//去雾：0 不启用    1 开启
	uint32_t rotate;	 					Rote//旋转：0 无    1 旋转90度    2 旋转270度 
	*/
	m_Flicker.AddString(_T("Close"));
	m_Flicker.AddString(_T("50Hz"));
	m_Flicker.AddString(_T("60Hz"));

	m_White_Red.SetRange(0,255);

	m_White_Blue.SetRange(0,255);

	m_JiBianCheck.SetRange(0,255);



	m_LightWakeUp.SetRange(0,255);

	if(g_PubData.g_iLanguageFlag == 0)
	{
		m_WhiteType.AddString(_T("自动白平衡"));
		m_WhiteType.AddString(_T("手动白平衡"));

		m_LightType.AddString(_T("手动光圈"));
		m_LightType.AddString(_T("自动光圈"));

		m_AutoLight.AddString(_T("噪声优先"));
		m_AutoLight.AddString(_T("帧率优先"));
		m_AutoLight.AddString(_T("增益优先"));

		m_OutSprat.AddString(_T("不启用"));
		m_OutSprat.AddString(_T("启用"));

		m_Rote.AddString(_T("无"));
		m_Rote.AddString(_T("旋转90度"));
		m_Rote.AddString(_T("旋转270度"));


		m_bShutter.AddString(_T("自动快门"));
	}
	else
	{
		m_WhiteType.AddString(_T("Automatic white balance"));
		m_WhiteType.AddString(_T("Manual white balance"));

		m_LightType.AddString(_T("Manual Iris"));
		m_LightType.AddString(_T("Automatic aperture"));

		m_AutoLight.AddString(_T("The noise"));
		m_AutoLight.AddString(_T("Frame rate"));
		m_AutoLight.AddString(_T("Gain priority"));

		m_OutSprat.AddString(_T("Do not enable"));
		m_OutSprat.AddString(_T("Start using"));

		m_Rote.AddString(_T("No"));
		m_Rote.AddString(_T("90 degree rotation"));
		m_Rote.AddString(_T("270 degree rotation"));


		m_bShutter.AddString(_T("Automatic shutter"));
	}
	
	m_bShutter.AddString(_T("1/25S"));
	m_bShutter.AddString(_T("1/50S"));
	m_bShutter.AddString(_T("1/100S"));
	m_bShutter.AddString(_T("1/200S"));
	m_bShutter.AddString(_T("1/500S"));
	m_bShutter.AddString(_T("1/1000S"));
	m_bShutter.AddString(_T("1/2000S"));
	m_bShutter.AddString(_T("1/5000S"));
	m_bShutter.AddString(_T("1/10000S"));
	//OnBnClickedButtonFlash();
	
	return TRUE;
}
void CPictureSet::OnBnClickedButtonFlash()
{
	// TODO: 在此添加控件通知处理程序代码
	if(g_PubData.g_iPlayWndFlag != 2 )
	{
		AVP_AddPlayWnd(g_PubData.g_iChancel[g_PubData.g_iAttributeIng],NULL,GetDlgItem(IDC_STATIC_SHOWVIDEO)->GetSafeHwnd(),NULL,NULL);
	}
	
	int iRet = -1;
	iRet = JNetGetParam(g_PubData.g_vLoginHandle[g_PubData.g_iAttributeIng],0,PARAM_DISPLAY_INFO, (char *)&m_display, sizeof(m_display),NULL, NULL );
	if( iRet != 0)
	{
		AfxMessageBox( g_PubData.g_strGetMessage);
		return ;
	}

	iRet = JNetGetParam(g_PubData.g_vLoginHandle[g_PubData.g_iAttributeIng],0,PARAM_PIC_INFO, (char *)&m_picture, sizeof(m_picture),NULL, NULL );
	if( iRet != 0)
	{
		AfxMessageBox( g_PubData.g_strGetMessage);
		return ;
	}
	ReFreshDisPlayWindow();
	ReFreshPictureWindow();
	//SliderCtrlSetPos();
}
void CPictureSet::SliderCtrlSetPos()
{
	CString strShow = _T("");
	strShow.Format(_T("%d"),  m_Compare.GetPos());
	GetDlgItem(IDC_STATIC_COMPARE1)->SetWindowText(strShow);

	strShow.Format(_T("%d"),  m_Light.GetPos());
	GetDlgItem(IDC_STATIC_COMPARE2)->SetWindowText(strShow);

	strShow.Format(_T("%d"), m_Gray.GetPos());
	GetDlgItem(IDC_STATIC_COMPARE3)->SetWindowText(strShow);

	strShow.Format(_T("%d"), m_Saturation.GetPos());
	GetDlgItem(IDC_STATIC_COMPARE4)->SetWindowText(strShow);

	strShow.Format(_T("%d"), m_Shar.GetPos());
	GetDlgItem(IDC_STATIC_COMPARE5)->SetWindowText(strShow);

	strShow.Format(_T("%d"),  m_LightWakeUp.GetPos());
	GetDlgItem(IDC_STATIC_COMPARE6)->SetWindowText(strShow);

	strShow.Format(_T("%d"), m_White_Red.GetPos());
	GetDlgItem(IDC_STATIC_COMPARE7)->SetWindowText(strShow);

	strShow.Format(_T("%d"), m_White_Blue.GetPos());
	GetDlgItem(IDC_STATIC_COMPARE8)->SetWindowText(strShow);

	strShow.Format(_T("%d"), m_JiBianCheck.GetPos());
	GetDlgItem(IDC_STATIC_JIBIAN)->SetWindowText(strShow);

	strShow.Format(_T("%d"), m_WidthState.GetPos());
	GetDlgItem(IDC_STATIC_WIDTHSTATE)->SetWindowText(strShow);
}
void CPictureSet::OnBnClickedButtonSave()
{
	// TODO: 在此添加控件通知处理程序代码
	m_display.contrast = m_Compare.GetPos();
	m_display.bright = m_Light.GetPos();
	m_display.hue = m_Gray.GetPos();
	m_display.saturation = m_Saturation.GetPos();
	m_display.sharpness = m_Shar.GetPos();

	int iRet = -1;
	iRet = JNetSetParam(g_PubData.g_vLoginHandle[g_PubData.g_iAttributeIng],0,PARAM_DISPLAY_INFO, (char *)&m_display, sizeof(m_display), TRUE);
	if( iRet != 0)
	{
		AfxMessageBox(g_PubData.g_strSetMessage);
		return ;
	}

	
	m_picture.mirror = m_Image.GetCheck();
	m_picture.flip = m_RollTurn.GetCheck();
	m_picture.hz = m_Flicker.GetCurSel();
	m_picture.awb_mode = m_WhiteType.GetCurSel();
	m_picture.awb_red = m_White_Red.GetPos();
	m_picture.awb_blue = m_White_Blue.GetPos();
	m_picture.iris_type = m_LightType.GetCurSel();
	m_picture.exp_compensation = m_LightWakeUp.GetPos();
	m_picture.ae_mode = m_AutoLight.GetCurSel();
	m_picture.anti_fog = m_OutSprat.GetCurSel();
	m_picture.rotate = m_Rote.GetCurSel();
	m_picture.ldc_value = m_JiBianCheck.GetPos();
	m_picture.wdr = m_WidthState.GetPos();
	//m_picture.shutter = ;

	if(m_bShutter.GetCurSel() == 4)
		m_picture.shutter = 9;
	else if(m_bShutter.GetCurSel() > 4)
		m_picture.shutter = m_bShutter.GetCurSel() - 1;
	else
		m_picture.shutter = m_bShutter.GetCurSel();



	iRet = JNetSetParam(g_PubData.g_vLoginHandle[g_PubData.g_iAttributeIng],0,PARAM_PIC_INFO, (char *)&m_picture, sizeof(m_picture), TRUE);
	if( iRet != 0)
	{
		//AfxMessageBox(g_PubData.g_strSetMessage);
		return ;
	}

}


int CPictureSet::ReFreshDisPlayWindow()
{
	
	m_Compare.SetPos(m_display.contrast);
	m_Light.SetPos(m_display.bright);
	m_Gray.SetPos(m_display.hue);
	m_Saturation.SetPos(m_display.saturation);
	m_Shar.SetPos(m_display.sharpness);
	return 0;
}

int CPictureSet::ReFreshPictureWindow()
{
	m_Image.SetCheck(m_picture.mirror);
	m_RollTurn.SetCheck(m_picture.flip);
	m_Flicker.SetCurSel(m_picture.hz);
	m_WhiteType.SetCurSel(m_picture.awb_mode);
	m_White_Red.SetPos(m_picture.awb_red);
	m_White_Blue.SetPos(m_picture.awb_blue);
	m_LightType.SetCurSel(m_picture.iris_type);
	m_LightWakeUp.SetPos(m_picture.exp_compensation);
	m_AutoLight.SetCurSel(m_picture.ae_mode);
	m_OutSprat.SetCurSel(m_picture.anti_fog);
	m_Rote.SetCurSel(m_picture.rotate);
	m_JiBianCheck.SetPos(m_picture.ldc_value);
	m_WidthState.SetPos(m_picture.wdr);
	if(m_picture.shutter == 9)
		m_bShutter.SetCurSel(4);
	else if(m_picture.shutter > 3)
		m_bShutter.SetCurSel(m_picture.shutter + 1);
	else
		m_bShutter.SetCurSel(m_picture.shutter);
	SliderCtrlSetPos();
	return 0;
}

void CPictureSet::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CPictureSet::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CDialog::OnLButtonUp(nFlags, point);
}

BOOL CPictureSet::PreTranslateMessage(MSG* pMsg) 
{

	int buID;
	buID= GetWindowLong(pMsg->hwnd,GWL_ID);//由窗口句柄获得ID号，GetWindowLong为获得窗口的ID号。
	if(pMsg->message==WM_LBUTTONDOWN)   //按下 
	{	

	}
	if(pMsg->message==WM_LBUTTONUP)  //松开
	{  
		if(buID == IDC_SLIDER_COMPARE ||
		   buID == IDC_SLIDER_LIGHT ||
		   buID == IDC_SLIDER_GRAY ||
		   buID == IDC_SLIDER_SATURATION ||
		   buID == IDC_SLIDER_SHAR ||
		   buID == IDC_SLIDER_WHITE_RED ||
		   buID == IDC_SLIDER_WHITE_BLUE ||
		   buID == IDC_SLIDER_LIGHTMAKEUP ||
		   buID == IDC_SLIDER_JIBIANCHECK ||
		   buID == IDC_SLIDER_WIDTHSTATE  )
		{
			OnBnClickedButtonSave();
			SliderCtrlSetPos();
		}
	}

	if(pMsg->message == WM_KEYUP && (pMsg->wParam == VK_RIGHT  || pMsg->wParam == VK_LEFT) )
	{
	
		if(buID == IDC_SLIDER_COMPARE ||
			buID == IDC_SLIDER_LIGHT ||
			buID == IDC_SLIDER_GRAY ||
			buID == IDC_SLIDER_SATURATION ||
			buID == IDC_SLIDER_SHAR ||
			buID == IDC_SLIDER_WHITE_RED ||
			buID == IDC_SLIDER_WHITE_BLUE ||
			buID == IDC_SLIDER_LIGHTMAKEUP ||
			buID == IDC_SLIDER_JIBIANCHECK )
		{
			OnBnClickedButtonSave();
			SliderCtrlSetPos();
			
		}
		return FALSE;
	}

	return CDialog::PreTranslateMessage(pMsg);
}

void CPictureSet::OnBnClickedButtonReset()
{
	// TODO: 在此添加控件通知处理程序代码
	int iRet = -1;
	iRet = JNetGetParam(g_PubData.g_vLoginHandle[g_PubData.g_iAttributeIng],0,PARAM_DEF_DISPLAY_INFO, (char *)&m_display, sizeof(m_display),NULL, NULL );
	if( iRet != 0)
	{
		AfxMessageBox( g_PubData.g_strGetMessage);
		return ;
	}

	iRet = JNetGetParam(g_PubData.g_vLoginHandle[g_PubData.g_iAttributeIng],0,PARAM_DEF_PICTURE_INFO, (char *)&m_picture, sizeof(m_picture),NULL, NULL );
	{
		AfxMessageBox( g_PubData.g_strGetMessage);
		return ;
	}

	ReFreshDisPlayWindow();
	ReFreshPictureWindow();
}


void CPictureSet::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CDialog::OnClose();
}

void CPictureSet::OnDestroy()
{
	CDialog::OnDestroy();

	// TODO: 在此处添加消息处理程序代码
}
