// EncodeDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Client_Demo.h"
#include "EncodeDlg.h"
#include "Pub_Data.h"

// CEncodeDlg 对话框


IMPLEMENT_DYNAMIC(CEncodeDlg, CDialog)

CEncodeDlg::CEncodeDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CEncodeDlg::IDD, pParent)
{
	ZeroMemory(&m_encodeParamer1, sizeof(m_encodeParamer1));
	ZeroMemory(&m_encodeParamer2, sizeof(m_encodeParamer2));
	ZeroMemory(&m_encodeParamer3, sizeof(m_encodeParamer3));
	m_StreamId = -1;
}

CEncodeDlg::~CEncodeDlg()
{
	DestroyWindow();
}

void CEncodeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_CHOOSE_CHANNEL, m_comChooseChannel);
	DDX_Control(pDX, IDC_CHECK_STARTVOICE, m_bStartVoice);
	DDX_Control(pDX, IDC_COMBO_INVOICE, m_eInVoice);
	DDX_Control(pDX, IDC_TABSTREAM, m_TabStream);
}


BEGIN_MESSAGE_MAP(CEncodeDlg, CDialog)
	ON_NOTIFY(TCN_SELCHANGING, IDC_TABSTREAM, &CEncodeDlg::OnTcnSelchangingTabstream)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TABSTREAM, &CEncodeDlg::OnTcnSelchangeTabstream)
	ON_BN_CLICKED(IDC_BUTTON_FLASH, &CEncodeDlg::OnBnClickedButtonFlash)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &CEncodeDlg::OnBnClickedButtonSave)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CEncodeDlg 消息处理程序

BOOL CEncodeDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_comChooseChannel.AddString(_T("0"));
	m_comChooseChannel.SetCurSel(0);

	m_eInVoice.AddString(_T("MIC"));
	if(g_PubData.g_iLanguageFlag == 0)
	{
		m_eInVoice.AddString(_T("线输入"));
	}
	else
	{
		m_eInVoice.AddString(_T("Line input"));
	}
	

	CRect rect; 
	m_TabStream.GetClientRect(&rect); 
	rect.top+=20; 
	rect.bottom-=4; 
	rect.left+=4; 
	rect.right-=4; 

	//按设备能力集 取码流个数
	if(g_PubData.g_iLanguageFlag == 0)
		m_TabStream.InsertItem(0, _T("主码流"));
	else
		m_TabStream.InsertItem(0, _T("Main Stream"));
	m_MainStream.Create(IDD_DIALOG_MAIN_STREAM, &m_TabStream);
	m_MainStream.MoveWindow(&rect); 

	if(g_PubData.g_jDevCap[g_PubData.g_iAttributeIng].chn_cap.stream_count  >= 2)
	{
		if(g_PubData.g_iLanguageFlag == 0)
			m_TabStream.InsertItem(1, _T("次码流"));
		else
			m_TabStream.InsertItem(1, _T("Second Stream"));
		m_SecondStream.Create(IDD_DIALOG_SECOND_STREAM, &m_TabStream);
		m_SecondStream.MoveWindow(&rect);
	}
	if(g_PubData.g_jDevCap[g_PubData.g_iAttributeIng].chn_cap.stream_count  >= 3)
	{
		if(g_PubData.g_iLanguageFlag == 0)
			m_TabStream.InsertItem(2, _T("三码流"));
		else
			m_TabStream.InsertItem(2, _T("Third Stream"));
		m_ThirdStream.Create(IDD_DIALOG_THIRD_STREAM, &m_TabStream);
		m_ThirdStream.MoveWindow(&rect); 
	}
	m_TabStream.SetCurSel(0); 
	m_MainStream.ShowWindow(TRUE);


	InitResalutionWnd();

	return TRUE;
}
void CEncodeDlg::InitResalutionWnd()
{
	for(int i = 0; i< m_MainStream.m_strArray.GetCount(); i++)
	{
		m_MainStream.m_comResolution.AddString(m_MainStream.m_strArray.GetAt(i));
	}

	for(int i = 0; i< m_SecondStream.m_strArray.GetCount(); i++)
	{
		m_SecondStream.m_comResolution.AddString(m_SecondStream.m_strArray.GetAt(i));
	}

	for(int i = 0; i< m_ThirdStream.m_strArray.GetCount(); i++)
	{
		m_ThirdStream.m_comResolution.AddString(m_ThirdStream.m_strArray.GetAt(i));
	}
}

CString CEncodeDlg::GetComReasolution(int iText)
{
	CString strText = _T("");
	if(iText == J_SDK_VIDEO_QCIF)
	{
		strText =  _T("QCIF");
	}
	else if(iText == J_SDK_VIDEO_CIF)
	{
		strText = _T("CIF");
	}
	else if(iText == J_SDK_VIDEO_D1)
	{
		strText = _T("D1");
	}
	else if(iText == J_SDK_VIDEO_QQVGA)
	{
		strText = _T("QQVGA");
	}
	else if(iText == J_SDK_VIDEO_QVGA)
	{
		strText = _T("QVGA");
	}
	else if(iText == J_SDK_VIDEO_VGA)
	{
		strText = _T("VGA");
	}
	else if(iText == J_SDK_VIDEO_SVGA)
	{
		strText = _T("SVGA");
	}
	else if(iText == J_SDK_VIDEO_UXGA)
	{
		strText = _T("UXGA");
	}
	else if(iText == J_SDK_VIDEO_720P)
	{
		strText = _T("720P");
	}
	else if(iText == J_SDK_VIDEO_960P)
	{
		strText = _T("960P");
	}
	else if(iText == J_SDK_VIDEO_1080P)
	{
		strText = _T("1080P");
	}
	else if(iText == J_SDK_VIDEO_XGA)
	{
		strText = _T("XGA");
	}
	else if(iText == J_SDK_VIDEO_WXGA)
	{
		strText = _T("WXGA");
	}
	else if(iText == J_SDK_VIDEO_SXGA)
	{
		strText = _T("SXGA");
	}
	else if(iText == J_SDK_VIDEO_3Mega)
	{
		strText = _T("3Mega");
	}
	else if(iText == J_SDK_VIDEO_5Mega)
	{
		strText = _T("5Mega");
	}
	else if(iText == J_SDK_VIDEO_UltraHD)
	{
		strText = _T("UltraHD");
	}

	return strText;
}

int CEncodeDlg::GetIndexOfString(CString strText)
{
	int iText = -1;
	if(strText ==  _T("QCIF"))
	{
		iText = J_SDK_VIDEO_QCIF;
	}
	else if(strText == _T("CIF"))
	{
		iText = J_SDK_VIDEO_CIF;
	}
	else if(strText == _T("D1"))
	{
		iText = J_SDK_VIDEO_D1;
	}
	else if(strText == _T("QQVGA"))
	{
		iText = J_SDK_VIDEO_QQVGA;
	}
	else if(strText == _T("QVGA"))
	{
		iText = J_SDK_VIDEO_QVGA;
	}
	else if(strText == _T("VGA"))
	{
		iText = J_SDK_VIDEO_VGA;
	}
	else if(strText == _T("SVGA"))
	{
		iText = J_SDK_VIDEO_SVGA;
	}
	else if(strText == _T("UXGA"))
	{
		iText = J_SDK_VIDEO_UXGA;
	}
	else if(strText == _T("720P"))
	{
		iText = J_SDK_VIDEO_720P;
	}
	else if(strText == _T("960P"))
	{
		iText = J_SDK_VIDEO_960P;
	}
	else if(strText == _T("1080P"))
	{
		iText = J_SDK_VIDEO_1080P;
	}
	else if(strText == _T("XGA"))
	{
		iText = J_SDK_VIDEO_XGA;
	}
	else if(strText == _T("WXGA"))
	{
		iText = J_SDK_VIDEO_WXGA;
	}
	else if(strText == _T("SXGA"))
	{
		iText = J_SDK_VIDEO_SXGA;
	}
	else if(strText == _T("3Mega"))
	{
		iText = J_SDK_VIDEO_3Mega;
	}
	else if(strText == _T("5Mega"))
	{
		iText = J_SDK_VIDEO_5Mega;
	}
	else if(strText == _T("UltraHD"))
	{
		iText = J_SDK_VIDEO_UltraHD;
	}

	return iText;
}
void CEncodeDlg::OnTcnSelchangingTabstream(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}

void CEncodeDlg::OnTcnSelchangeTabstream(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码

	int iCursel;
	iCursel=m_TabStream.GetCurSel(); 
	if(g_PubData.g_jDevCap[g_PubData.g_iAttributeIng].chn_cap.stream_count == 1)
	{
		return;
	}
	else if(g_PubData.g_jDevCap[g_PubData.g_iAttributeIng].chn_cap.stream_count == 2)
	{
		switch(iCursel) 
		{ 
		case 0: 
			m_MainStream.ShowWindow(TRUE); 
			m_SecondStream.ShowWindow(FALSE); 
		
			break; 
		case 1: 
			m_MainStream.ShowWindow(FALSE); 
			m_SecondStream.ShowWindow(TRUE); 
			break; 
		default: ; 
		}
	}
	else if(g_PubData.g_jDevCap[g_PubData.g_iAttributeIng].chn_cap.stream_count == 3)
	{
		switch(iCursel) 
		{ 
		case 0: 
			m_MainStream.ShowWindow(TRUE); 
			m_SecondStream.ShowWindow(FALSE); 
			m_ThirdStream.ShowWindow(FALSE); 
			break; 
		case 1: 
			m_MainStream.ShowWindow(FALSE); 
			m_SecondStream.ShowWindow(TRUE); 
			m_ThirdStream.ShowWindow(FALSE); 
			break; 
		case 2: 
			m_MainStream.ShowWindow(FALSE); 
			m_SecondStream.ShowWindow(FALSE); 
			m_ThirdStream.ShowWindow(TRUE); 
			break; 
		default: ; 
		}
	}
	
	*pResult = 0;
}

void CEncodeDlg::OnBnClickedButtonFlash()
{
	// TODO: 在此添加控件通知处理程序代码
	//g_PubData.g_iStreamType[g_PubData.g_iAttributeIng]
	/////////////////////////////////////////////////////////////////////////////////////////
	
	////////////////////////////////////////////////////////////////////////////////////////
	//根据设备能力集判断支持的码流数
	int iRet = -1;
	

	int iCursel = m_TabStream.GetCurSel(); 
	if(iCursel < 0)
		return;

	
	if(iCursel == 0)
	{
		m_encodeParamer1.level = 0;
		iRet = JNetGetParam(g_PubData.g_vLoginHandle[g_PubData.g_iAttributeIng],0,PARAM_ENCODE_INFO, (char *)&m_encodeParamer1, sizeof(m_encodeParamer1),NULL, NULL );
		if( iRet != 0)
		{
			AfxMessageBox(g_PubData.g_strGetMessage);
		}
		ReFreshMainStream();
	}
	if(iCursel == 1)
	{
		m_encodeParamer2.level = 1;
		iRet = JNetGetParam(g_PubData.g_vLoginHandle[g_PubData.g_iAttributeIng],0,PARAM_ENCODE_INFO, (char *)&m_encodeParamer2, sizeof(m_encodeParamer2),NULL, NULL );
		if( iRet != 0)
		{
			AfxMessageBox(g_PubData.g_strGetMessage);
		}
		ReFreshSecondStream();
	}
	if(iCursel == 2)
	{
		m_encodeParamer3.level = 2;
		iRet = JNetGetParam(g_PubData.g_vLoginHandle[g_PubData.g_iAttributeIng],0,PARAM_ENCODE_INFO, (char *)&m_encodeParamer3, sizeof(m_encodeParamer3),NULL, NULL );
		if( iRet != 0)
		{
			AfxMessageBox(g_PubData.g_strGetMessage);
		}

		ReFreshThirdStream();
	}	
}

//保存主码流
void CEncodeDlg::SaveMainStream()
{
	int iTest = -1;
	int iIndex = -1;
	CString str = _T("");

	m_encodeParamer1.level = 0;

	m_MainStream.m_eZl.GetWindowText(str);
	m_encodeParamer1.frame_rate = _ttoi(str);


	m_MainStream.m_eSpaceZ.GetWindowText(str);
	m_encodeParamer1.i_frame_interval = _ttoi(str);

	m_encodeParamer1.au_in_mode = m_eInVoice.GetCurSel();

	m_encodeParamer1.audio_enble = m_bStartVoice.GetCheck();


	iTest = m_MainStream.m_comResolution.GetCurSel();

	iIndex = GetIndexOfString(m_MainStream.m_strArray.GetAt(iTest));

	m_encodeParamer1.resolution = iIndex;

	m_encodeParamer1.qp_value = m_MainStream.m_comQuality.GetCurSel();

	m_MainStream.m_eMlv.GetWindowText(str);
	m_encodeParamer1.code_rate = _ttoi(str);

	m_encodeParamer1.frame_priority = m_MainStream.m_IfFirst.GetCheck();

	m_encodeParamer1.format = m_MainStream.m_eZs.GetCurSel();

	m_encodeParamer1.bit_rate = m_MainStream.m_comWlv.GetCurSel() + 1;

	m_encodeParamer1.encode_level = m_MainStream.m_comEncodeOrder.GetCurSel();

	int iRet = -1;
	iRet = JNetSetParam(g_PubData.g_vLoginHandle[g_PubData.g_iAttributeIng],0,PARAM_ENCODE_INFO, (char *)&m_encodeParamer1, sizeof(m_encodeParamer1), TRUE);
	if( iRet != 0)
	{
		AfxMessageBox(g_PubData.g_strSetMessage);
		return ;
	}

}
//保存次码流
void CEncodeDlg::SaveSecondStream()
{
	int iTest = -1;
	int iIndex = -1;
	CString str = _T("");
	m_encodeParamer2.level = 1;

	m_SecondStream.m_eZl.GetWindowText(str);
	m_encodeParamer2.frame_rate = _ttoi(str);


	m_SecondStream.m_eSpaceZ.GetWindowText(str);
	m_encodeParamer2.i_frame_interval = _ttoi(str);

	m_encodeParamer2.au_in_mode = m_eInVoice.GetCurSel();

	m_encodeParamer2.audio_enble = m_bStartVoice.GetCheck();

	iTest = m_SecondStream.m_comResolution.GetCurSel();
	iIndex = GetIndexOfString(m_SecondStream.m_strArray.GetAt(iTest));

	m_encodeParamer2.resolution = iIndex;

	m_encodeParamer2.qp_value = m_SecondStream.m_comQuality.GetCurSel();

	m_SecondStream.m_eMlv.GetWindowText(str);
	m_encodeParamer2.code_rate = _ttoi(str);

	m_encodeParamer2.frame_priority = m_SecondStream.m_IfFirst.GetCheck();

	m_encodeParamer2.format = m_SecondStream.m_eZs.GetCurSel();

	m_encodeParamer2.bit_rate = m_SecondStream.m_comWlv.GetCurSel() + 1;

	m_encodeParamer2.encode_level = m_SecondStream.m_comEncodeOrder.GetCurSel();

	int iRet = -1;

	iRet = JNetSetParam(g_PubData.g_vLoginHandle[g_PubData.g_iAttributeIng],0,PARAM_ENCODE_INFO, (char *)&m_encodeParamer2, sizeof(m_encodeParamer2), TRUE);
	if( iRet != 0)
	{
		AfxMessageBox( g_PubData.g_strSetMessage);
		return ;
	}
}
//保存三码流
void CEncodeDlg::SaveThirdStream()
{
	int iTest = -1;
	int iIndex = -1;
	CString str = _T("");
	m_encodeParamer3.level = 2 ;

	m_ThirdStream.m_eZl.GetWindowText(str);
	m_encodeParamer3.frame_rate = _ttoi(str);


	m_ThirdStream.m_eSpaceZ.GetWindowText(str);
	m_encodeParamer3.i_frame_interval = _ttoi(str);

	m_encodeParamer3.au_in_mode = m_eInVoice.GetCurSel();

	m_encodeParamer3.audio_enble = m_bStartVoice.GetCheck();

	iTest = m_ThirdStream.m_comResolution.GetCurSel();
	iIndex = GetIndexOfString(m_ThirdStream.m_strArray.GetAt(iTest));

	m_encodeParamer3.resolution = iIndex;

	m_encodeParamer3.qp_value = m_ThirdStream.m_comQuality.GetCurSel();

	m_ThirdStream.m_eMlv.GetWindowText(str);
	m_encodeParamer3.code_rate = _ttoi(str);

	m_encodeParamer3.frame_priority = m_ThirdStream.m_IfFirst.GetCheck();

	m_encodeParamer3.format = m_ThirdStream.m_eZs.GetCurSel();

	m_encodeParamer3.bit_rate = m_ThirdStream.m_comWlv.GetCurSel() + 1;

	m_encodeParamer3.encode_level = m_ThirdStream.m_comEncodeOrder.GetCurSel();

	int iRet = -1;
	iRet = JNetSetParam(g_PubData.g_vLoginHandle[g_PubData.g_iAttributeIng],0,PARAM_ENCODE_INFO, (char *)&m_encodeParamer3, sizeof(m_encodeParamer3), TRUE);
	if( iRet != 0)
	{
		AfxMessageBox(g_PubData.g_strSetMessage);
		return ;
	}
}

void CEncodeDlg::OnBnClickedButtonSave()
{
	// TODO: 在此添加控件通知处理程序代码

	int iCursel;
	iCursel=m_TabStream.GetCurSel(); 
	if(iCursel == 0)
	{
		SaveMainStream();
	}
	else if(iCursel == 1)
	{
		SaveSecondStream();
	}
	else if(iCursel == 2)
	{
		SaveThirdStream();
	}

}


int CEncodeDlg::ReFreshMainStream()
{
	
	int iText =	0;;
	CString str = _T("");

	iText = m_encodeParamer1.frame_rate;
	str.Format(_T("%d"), iText);
	m_MainStream.m_eZl.SetWindowText(str);

	iText = m_encodeParamer1.i_frame_interval;
	str.Format(_T("%d"), iText);
	m_MainStream.m_eSpaceZ.SetWindowText(str);

	m_eInVoice.SetCurSel(m_encodeParamer1.au_in_mode);

	m_bStartVoice.SetCheck(m_encodeParamer1.audio_enble);

	iText = m_encodeParamer1.resolution;
	CString strReasolution = GetComReasolution(iText);
	for(int i = 0; i< m_MainStream.m_strArray.GetCount(); i++)
	{
		if(strReasolution == m_MainStream.m_strArray.GetAt(i))
		{
			m_MainStream.m_comResolution.SetCurSel(i);
		}
	}
	
	m_MainStream.m_comQuality.SetCurSel(m_encodeParamer1.qp_value);

	iText = m_encodeParamer1.code_rate;
	str.Format(_T("%d"), iText);
	m_MainStream.m_eMlv.SetWindowText(str);

	m_MainStream.m_IfFirst.SetCheck(m_encodeParamer1.frame_priority);

	m_MainStream.m_eZs.SetCurSel(m_encodeParamer1.format);

	m_MainStream.m_comWlv.SetCurSel(m_encodeParamer1.bit_rate - 1);

	m_MainStream.m_comEncodeOrder.SetCurSel(m_encodeParamer1.encode_level);
	
	return 0;
}

int CEncodeDlg::ReFreshSecondStream()
{
	
	int iText =	0;;
	CString str = _T("");

	iText = m_encodeParamer2.frame_rate;
	str.Format(_T("%d"), iText);
	m_SecondStream.m_eZl.SetWindowText(str);

	iText = m_encodeParamer2.i_frame_interval;
	str.Format(_T("%d"), iText);
	m_SecondStream.m_eSpaceZ.SetWindowText(str);

	m_eInVoice.SetCurSel(m_encodeParamer2.au_in_mode);

	m_bStartVoice.SetCheck(m_encodeParamer2.audio_enble);

	iText = m_encodeParamer2.resolution;
	CString strReasolution = GetComReasolution(iText);
	for(int i = 0; i< m_SecondStream.m_strArray.GetCount(); i++)
	{
		if(strReasolution ==m_SecondStream.m_strArray.GetAt(i))
		{
			m_SecondStream.m_comResolution.SetCurSel(i);
		}
	}

	m_SecondStream.m_comQuality.SetCurSel(m_encodeParamer2.qp_value);

	iText = m_encodeParamer2.code_rate;
	str.Format(_T("%d"), iText);
	m_SecondStream.m_eMlv.SetWindowText(str);

	m_SecondStream.m_IfFirst.SetCheck(m_encodeParamer2.frame_priority);

	m_SecondStream.m_eZs.SetCurSel(m_encodeParamer2.format);

	m_SecondStream.m_comWlv.SetCurSel(m_encodeParamer2.bit_rate -1);

	m_SecondStream.m_comEncodeOrder.SetCurSel(m_encodeParamer2.encode_level);

	return 0;
}

int CEncodeDlg::ReFreshThirdStream()
{
	int iText =	0;;
	CString str = _T("");

	iText = m_encodeParamer3.frame_rate;
	str.Format(_T("%d"), iText);
	m_ThirdStream.m_eZl.SetWindowText(str);

	iText = m_encodeParamer3.i_frame_interval;
	str.Format(_T("%d"), iText);
	m_ThirdStream.m_eSpaceZ.SetWindowText(str);

	m_eInVoice.SetCurSel(m_encodeParamer3.au_in_mode);

	m_bStartVoice.SetCheck(m_encodeParamer3.audio_enble);

	iText = m_encodeParamer3.resolution;
	CString strReasolution = GetComReasolution(iText);
	for(int i = 0; i< m_ThirdStream.m_strArray.GetCount(); i++)
	{
		if(strReasolution == m_ThirdStream.m_strArray.GetAt(i))
		{
			m_ThirdStream.m_comResolution.SetCurSel(i);
		}
	}

	m_ThirdStream.m_comQuality.SetCurSel(m_encodeParamer3.qp_value);

	iText = m_encodeParamer3.code_rate;
	str.Format(_T("%d"), iText);
	m_ThirdStream.m_eMlv.SetWindowText(str);

	m_ThirdStream.m_IfFirst.SetCheck(m_encodeParamer3.frame_priority);

	m_ThirdStream.m_eZs.SetCurSel(m_encodeParamer3.format);

	m_ThirdStream.m_comWlv.SetCurSel(m_encodeParamer3.bit_rate - 1);

	m_ThirdStream.m_comEncodeOrder.SetCurSel(m_encodeParamer3.encode_level);

	return 0;
}
void CEncodeDlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CDialog::OnClose();
}
