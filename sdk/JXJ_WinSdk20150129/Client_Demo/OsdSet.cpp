// OsdSet.cpp : 实现文件
//

#include "stdafx.h"
#include "Client_Demo.h"
#include "OsdSet.h"
#include "Pub_Data.h"

// COsdSet 对话框



IMPLEMENT_DYNAMIC(COsdSet, CDialog)

COsdSet::COsdSet(CWnd* pParent /*=NULL*/)
	: CDialog(COsdSet::IDD, pParent)
{

	m_strGB2312toUTF8 = NULL;
	m_strUTF8toGB2312 = NULL;
}

COsdSet::~COsdSet()
{
	delete m_strGB2312toUTF8;
	m_strGB2312toUTF8 = NULL;
	delete m_strUTF8toGB2312;
	m_strUTF8toGB2312 = NULL;

	DestroyWindow();
}

void COsdSet::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_TEXT, m_eText);
	DDX_Control(pDX, IDC_COMBO_CHANNEL, m_comChannel);
	DDX_Control(pDX, IDC_CHECK_SHOWTIME, m_bShowTime);
	DDX_Control(pDX, IDC_CHECK_SHOWTEXT, m_bShowText);
	DDX_Control(pDX, IDC_CHECKSHOWSTREAM, m_bShowStream);
	DDX_Control(pDX, IDC_EDIT_TIMEX, m_eTimeX);
	DDX_Control(pDX, IDC_EDIT_TIMEY, m_eTimeY);
	DDX_Control(pDX, IDC_EDIT_TEXTX, m_eTextX);
	DDX_Control(pDX, IDC_EDIT_TEXTY, m_eTextY);
	DDX_Control(pDX, IDC_CHECK_OSDOPPOSITE, m_OSDOpposite);
	DDX_Control(pDX, IDC_BUTTONTIMECOLOR, m_TimeColor);
	DDX_Control(pDX, IDC_BUTTON_TEXTCOLOR, m_TextColor);
	DDX_Control(pDX, IDC_CHECK_SHOWTEXT2, m_bShowText2);
	DDX_Control(pDX, IDC_CHECK_SHOWTEXT3, m_bShowText3);
	DDX_Control(pDX, IDC_EDIT_TEXT2, m_eText2);
	DDX_Control(pDX, IDC_EDIT_TEXT3, m_eText3);
	DDX_Control(pDX, IDC_EDIT_TEXTX2, m_eTextX2);
	DDX_Control(pDX, IDC_EDIT_TEXTX3, m_eTextX3);
	DDX_Control(pDX, IDC_EDIT_TEXTY2, m_eTextY2);
	DDX_Control(pDX, IDC_EDIT_TEXTY3, m_eTextY3);
}


BEGIN_MESSAGE_MAP(COsdSet, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &COsdSet::OnBnClickedButtonSave)
	ON_BN_CLICKED(IDC_BUTTON_FLASH, &COsdSet::OnBnClickedButtonFlash)
	ON_BN_CLICKED(IDC_BUTTONTIMECOLOR, &COsdSet::OnBnClickedButtontimecolor)
	ON_BN_CLICKED(IDC_BUTTON_TEXTCOLOR, &COsdSet::OnBnClickedButtonTextcolor)
	ON_WM_CLOSE()
	ON_WM_DESTROY()
	ON_EN_CHANGE(IDC_EDIT_TEXTX, &COsdSet::OnEnChangeEditTextx)
END_MESSAGE_MAP()


// COsdSet 消息处理程序
BOOL COsdSet::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	GetDlgItem(IDC_STATIC_SHOWSCREEN)->GetWindowRect(m_cRect);

	m_comChannel.AddString(_T("0"));
	m_comChannel.SetCurSel(0);

	m_TimeColor.EnableAutomaticButton(_T("默认值"), RGB(0, 0, 0)); 
	m_TimeColor.EnableOtherButton(_T("其余颜色")); 
	m_TimeColor.SetColor((COLORREF)-1); 
	m_TimeColor.SetColumnsNumber(10);     

	m_TextColor.EnableAutomaticButton(_T("默认值"), RGB(0, 0, 0)); 
	m_TextColor.EnableOtherButton(_T("其余颜色")); 
	m_TextColor.SetColor((COLORREF)-1); 
	m_TextColor.SetColumnsNumber(10);     

	return TRUE;
}

void COsdSet::OnBnClickedButtonSave()
{
	// TODO: 在此添加控件通知处理程序代码

	m_osdParameter.time_enable = m_bShowTime.GetCheck();
	m_osdParameter.text_enable = m_bShowText.GetCheck();
	m_osdParameter.stream_enable = m_bShowStream.GetCheck();
	m_osdParameter.ext_osd.ext_text1_enable = m_bShowText2.GetCheck();
	m_osdParameter.ext_osd.ext_text2_enable = m_bShowText3.GetCheck();
	CString strText(_T(""));
	CString strText2(_T(""));
	CString strText3(_T(""));
	m_eText.GetWindowText(strText);
	if(strText.GetLength() >= J_SDK_MAX_TEXT_DATA_LEN)
	{
		//AfxMessageBox(_T("输入文本1超出范围"));
		return;
	}
	memset(m_osdParameter.text_data, '\0', sizeof(m_osdParameter.text_data));
	GB2312toUTF8(strText.GetBuffer(0));
	memcpy(m_osdParameter.text_data, m_strGB2312toUTF8, strlen(m_strGB2312toUTF8));
	strText.ReleaseBuffer();


	m_eText2.GetWindowText(strText2);
	if(strText2.GetLength() >= J_SDK_MAX_TEXT_DATA_LEN)
	{
		//AfxMessageBox(_T("输入文本2超出范围"));
		return;
	}
	memset(m_osdParameter.ext_osd.ext_text1_data, '\0', sizeof(m_osdParameter.ext_osd.ext_text1_data));
	GB2312toUTF8(strText2.GetBuffer(0));
	memcpy(m_osdParameter.ext_osd.ext_text1_data, m_strGB2312toUTF8, strlen(m_strGB2312toUTF8));
	strText2.ReleaseBuffer();


	m_eText3.GetWindowText(strText3);
	if(strText3.GetLength() >= J_SDK_MAX_TEXT_DATA_LEN)
	{
		//AfxMessageBox(_T("输入文本3超出范围"));
		return;
	}
	memset(m_osdParameter.ext_osd.ext_text2_data, '\0', sizeof(m_osdParameter.ext_osd.ext_text2_data));
	GB2312toUTF8(strText3.GetBuffer(0));
	memcpy(m_osdParameter.ext_osd.ext_text2_data, m_strGB2312toUTF8, strlen(m_strGB2312toUTF8));
	strText3.ReleaseBuffer();


	

	CRect cRect;
	GetDlgItem(IDC_STATIC_SHOWSCREEN)->GetWindowRect(cRect);
	int iDeviceWidth;
	int iDeviceHeight;
	iDeviceWidth = m_osdParameter.max_width;
	iDeviceHeight = m_osdParameter.max_height;

	m_eTimeX.GetWindowText(strText);
	m_osdParameter.time_display_x = (_ttoi(strText) * iDeviceWidth) / cRect.Width() + 1;

	m_eTimeY.GetWindowText(strText);
	m_osdParameter.time_display_y = (_ttoi(strText) * iDeviceHeight) / cRect.Height() + 1;

	m_eTextX.GetWindowText(strText);
	m_osdParameter.text_display_x = (_ttoi(strText) * iDeviceWidth) / cRect.Width() + 1;

	m_eTextY.GetWindowText(strText);
	m_osdParameter.text_display_y = (_ttoi(strText) * iDeviceHeight) / cRect.Height() + 1;

	m_eTextX2.GetWindowText(strText);
	m_osdParameter.ext_osd.ext_text1_display_x = (_ttoi(strText) * iDeviceWidth) / cRect.Width() + 1;

	m_eTextY2.GetWindowText(strText);
	m_osdParameter.ext_osd.ext_text1_display_y = (_ttoi(strText) * iDeviceHeight) / cRect.Height() + 1;


	m_eTextX3.GetWindowText(strText);
	m_osdParameter.ext_osd.ext_text2_display_x = (_ttoi(strText) * iDeviceWidth) / cRect.Width() + 1;

	m_eTextY3.GetWindowText(strText);
	m_osdParameter.ext_osd.ext_text2_display_y = (_ttoi(strText) * iDeviceHeight) / cRect.Height() + 1;


	m_osdParameter.osd_invert_color = m_OSDOpposite.GetCheck();

	//m_osdParameter.text_display_color = 200;
	m_osdParameter.time_display_color = m_TimeColor.GetColor();

	m_osdParameter.text_display_color = m_TextColor.GetColor();

	//m_osdParameter.time_display_color = 400;

	int iRet = -1;
	iRet = JNetSetParam(g_PubData.g_vLoginHandle[g_PubData.g_iAttributeIng],0,PARAM_OSD_INFO, (char *)&m_osdParameter, sizeof(m_osdParameter), TRUE);
	if( iRet != 0)
	{
		AfxMessageBox(g_PubData.g_strSetMessage);
		return ;
	}

}

void COsdSet::OnBnClickedButtonFlash()
{
	// TODO: 在此添加控件通知处理程序代码
	if(g_PubData.g_iPlayWndFlag != 0 )
	{
		AVP_AddPlayWnd(g_PubData.g_iChancel[g_PubData.g_iAttributeIng],NULL, GetDlgItem(IDC_STATIC_SHOWSCREEN)->GetSafeHwnd(),NULL,NULL);
	}
	int iRet = -1;

	iRet = JNetGetParam(g_PubData.g_vLoginHandle[g_PubData.g_iAttributeIng],0,PARAM_OSD_INFO, (char *)&m_osdParameter, sizeof(m_osdParameter),NULL, NULL );
	if( iRet != 0)
	{
		AfxMessageBox(g_PubData.g_strGetMessage);
		return ;
	}

	ReFreshWindow();
}



int COsdSet::ReFreshWindow()
{

	int iDeviceWidth;
	int iDeviceHeight;
	iDeviceWidth = m_osdParameter.max_width;
	iDeviceHeight = m_osdParameter.max_height;

	int time_x =  0;
	int time_y =  0;
	int text_x =  0;
	int text_y =  0;
	if(iDeviceWidth != 0 && iDeviceHeight != 0)
	{
		time_x =  (m_osdParameter.time_display_x * m_cRect.Width()) / iDeviceWidth ;
		time_y =  (m_osdParameter.time_display_y * m_cRect.Height()) / iDeviceHeight;
		text_x =  (m_osdParameter.text_display_x * m_cRect.Width()) / iDeviceWidth ;
		text_y =  (m_osdParameter.text_display_y * m_cRect.Height()) / iDeviceHeight;
	}
////////////////////////////////////////////////////////////
	int text_x2 =  0;
	int text_y2 =  0;
	if(iDeviceWidth != 0 && iDeviceHeight != 0)
	{
		text_x2 =  (m_osdParameter.ext_osd.ext_text1_display_x * m_cRect.Width()) / iDeviceWidth ;
		text_y2 =  (m_osdParameter.ext_osd.ext_text1_display_y * m_cRect.Height()) / iDeviceHeight;
	}

	int text_x3 =  0;
	int text_y3 =  0;
	if(iDeviceWidth != 0 && iDeviceHeight != 0)
	{
		text_x3 =  (m_osdParameter.ext_osd.ext_text2_display_x * m_cRect.Width()) / iDeviceWidth ;
		text_y3 =  (m_osdParameter.ext_osd.ext_text2_display_y * m_cRect.Height()) / iDeviceHeight;
	}

	////////////////////////////////////////////////////
	

	m_bShowTime.SetCheck(m_osdParameter.time_enable);
	m_bShowText.SetCheck(m_osdParameter.text_enable);
	m_bShowStream.SetCheck(m_osdParameter.stream_enable);
// 	char TextData[J_SDK_MAX_TEXT_DATA_LEN];
// 	memset(TextData, '\0', sizeof(TextData));
	UTF8toGB2312((char *)m_osdParameter.text_data);
	CString str(m_strUTF8toGB2312);
	m_eText.SetWindowText(str);

	UTF8toGB2312((char *)m_osdParameter.ext_osd.ext_text1_data);
	CString str2(m_strUTF8toGB2312);
	m_eText2.SetWindowText(str2);

	UTF8toGB2312((char *)m_osdParameter.ext_osd.ext_text2_data);
	CString str3(m_strUTF8toGB2312);
	m_eText3.SetWindowText(str3);

	CString strText(_T(""));
	strText.Format(_T("%d"), time_x);
	m_eTimeX.SetWindowText(strText);

	strText.Format(_T("%d"), time_y);
	m_eTimeY.SetWindowText(strText);

	strText.Format(_T("%d"), text_x);
	m_eTextX.SetWindowText(strText);

	strText.Format(_T("%d"), text_y);
	m_eTextY.SetWindowText(strText);

	strText.Format(_T("%d"), text_x2);
	m_eTextX2.SetWindowText(strText);

	strText.Format(_T("%d"), text_y2);
	m_eTextY2.SetWindowText(strText);


	strText.Format(_T("%d"), text_x3);
	m_eTextX3.SetWindowText(strText);

	strText.Format(_T("%d"), text_y3);
	m_eTextY3.SetWindowText(strText);

	m_bShowText2.SetCheck(m_osdParameter.ext_osd.ext_text1_enable);
	m_bShowText3.SetCheck(m_osdParameter.ext_osd.ext_text2_enable);



	m_OSDOpposite.SetCheck(m_osdParameter.osd_invert_color);

	m_TimeColor.SetColor(m_osdParameter.time_display_color);

	m_TextColor.SetColor(m_osdParameter.text_display_color);
	return 0;
}
void COsdSet::OnBnClickedButtontimecolor()
{
	// TODO: 在此添加控件通知处理程序代码
	m_colorTime = m_TimeColor.GetColor(); 
	if (m_colorTime == -1) 
	{ 
		m_colorTime = m_TimeColor.GetAutomaticColor(); 
	} 

}

void COsdSet::OnBnClickedButtonTextcolor()
{
	// TODO: 在此添加控件通知处理程序代码
	m_colorText = m_TextColor.GetColor(); 
	if (m_colorText == -1) 
	{ 
		m_colorText = m_TextColor.GetAutomaticColor(); 
	} 
}
//UTF-8转换为GB2312
void COsdSet::UTF8toGB2312(const char *utf8)
{
	if(m_strUTF8toGB2312 != NULL)
	{	
		delete m_strUTF8toGB2312;
		m_strUTF8toGB2312 = NULL;
	}
	int len = MultiByteToWideChar(CP_UTF8, 0, utf8, -1, NULL, 0);
	wchar_t* wstr = new wchar_t[len+1];
	memset(wstr, 0, len+1);
	MultiByteToWideChar(CP_UTF8, 0, utf8, -1, wstr, len);
	len = WideCharToMultiByte(CP_ACP, 0, wstr, -1, NULL, 0, NULL, NULL);
	m_strUTF8toGB2312 = new char[len+1];
	memset(m_strUTF8toGB2312, 0, len+1);
	WideCharToMultiByte(CP_ACP, 0, wstr, -1, m_strUTF8toGB2312, len, NULL, NULL);
	if(wstr) delete[] wstr;
}
//GB2312转换为UTF-8
void COsdSet::GB2312toUTF8(const char *gb2312)
{
	if(m_strGB2312toUTF8 != NULL)
	{
		delete m_strGB2312toUTF8;
		m_strGB2312toUTF8 = NULL;
	}
	int len = MultiByteToWideChar(CP_ACP, 0, gb2312, -1, NULL, 0);
	wchar_t* wstr = new wchar_t[len+1];
	memset(wstr, 0, len+1);
	MultiByteToWideChar(CP_ACP, 0, gb2312, -1, wstr, len);
	len = WideCharToMultiByte(CP_UTF8, 0, wstr, -1, NULL, 0, NULL, NULL);
	m_strGB2312toUTF8 = new char[len+1];
	memset(m_strGB2312toUTF8, 0, len+1);
	WideCharToMultiByte(CP_UTF8, 0, wstr, -1, m_strGB2312toUTF8, len, NULL, NULL);
	if(wstr) delete[] wstr;
}

/*//GB2312 to UTF-8
char *src = m_ShowText.GetBuffer(0); // 需转换的字串 
char dst[256] = {0}; // 转换后的内容 
//char buf[1024] = {0}; //格式化转换后的字串
size_t src_len = strlen(src);
size_t dst_len = sizeof(dst);
const char *in = src;
char *out = dst;
iconv_t cd;
//int i;
cd = iconv_open("UTF-8", "GB2312"); // 将GB2312字符集转换为UTF-8字符集 
if ((iconv_t)-1 == cd)
{
	return;
}

iconv(cd, &in, &src_len, &out, &dst_len); // 执行转换

iconv_close(cd); //执行清理

//UTF-8 to GB2312
char szsrc[256] = {0};
memcpy(szsrc, dst, dst_len);
const char *psrc = szsrc;
char szDst[256] = {0};
char *pDst = szDst;
int iDst_len = sizeof(szDst);
iconv_t ct = iconv_open("GB2312", "UTF-8");
if (ct == (iconv_t)-1)
{
	return;
}

size_t len = dst_len;
iconv(ct, &psrc, &len, &pDst, (size_t *)&iDst_len);
iconv_close(ct);
int size = sizeof(dst) - dst_len;
TRACE(_T("%d %d 长度： %d\n数据：\n%s"), len, size, iDst_len, szDst);*/
void COsdSet::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	
	CDialog::OnClose();
}

void COsdSet::OnDestroy()
{
	CDialog::OnDestroy();

	// TODO: 在此处添加消息处理程序代码
}

void COsdSet::OnEnChangeEditTextx()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}
