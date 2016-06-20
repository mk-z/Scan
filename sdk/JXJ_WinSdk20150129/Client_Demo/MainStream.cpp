// MainStream.cpp : 实现文件
//

#include "stdafx.h"
#include "Client_Demo.h"
#include "MainStream.h"
#include "Pub_Data.h"

// CMainStream 对话框

IMPLEMENT_DYNAMIC(CMainStream, CDialog)

CMainStream::CMainStream(CWnd* pParent /*=NULL*/)
	: CDialog(CMainStream::IDD, pParent)
{

}

CMainStream::~CMainStream()
{
	DestroyWindow();
}

void CMainStream::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_ZL, m_eZl);
	DDX_Control(pDX, IDC_EDIT_SPACEZ, m_eSpaceZ);
	DDX_Control(pDX, IDC_COMBO_RESOLUTION, m_comResolution);
	DDX_Control(pDX, IDC_COMBO_QUALITY, m_comQuality);
	DDX_Control(pDX, IDC_COMBO_ZS, m_eZs);
	DDX_Control(pDX, IDC_EDIT_MLV, m_eMlv);
	DDX_Control(pDX, IDC_COMBO_WLV, m_comWlv);
	DDX_Control(pDX, IDC_COMBO_ENCODEORDER, m_comEncodeOrder);
	DDX_Control(pDX, IDC_COMBO_ENCODEMODEL, m_comEncodeModel);
	DDX_Control(pDX, IDC_CHECK_IFFIRST, m_IfFirst);
}


BEGIN_MESSAGE_MAP(CMainStream, CDialog)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CMainStream 消息处理程序
BOOL CMainStream::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	if(g_PubData.g_jDevCap[g_PubData.g_iAttributeIng].chn_cap.stream_supp_resolution[0] & CAP_VIDEO_QCIF)
	{
		m_strArray.Add(_T("QCIF"));
	}
	if(g_PubData.g_jDevCap[g_PubData.g_iAttributeIng].chn_cap.stream_supp_resolution[0] & CAP_VIDEO_CIF)
	{
		m_strArray.Add(_T("CIF"));
	}
	if(g_PubData.g_jDevCap[g_PubData.g_iAttributeIng].chn_cap.stream_supp_resolution[0] & CAP_VIDEO_D1)
	{
		m_strArray.Add(_T("D1"));
	}
	if(g_PubData.g_jDevCap[g_PubData.g_iAttributeIng].chn_cap.stream_supp_resolution[0] & CAP_VIDEO_QQVGA)
	{
		m_strArray.Add(_T("QQVGA"));
	}
	if(g_PubData.g_jDevCap[g_PubData.g_iAttributeIng].chn_cap.stream_supp_resolution[0] & CAP_VIDEO_QVGA)
	{
		m_strArray.Add(_T("QVGA"));
	}
	if(g_PubData.g_jDevCap[g_PubData.g_iAttributeIng].chn_cap.stream_supp_resolution[0] & CAP_VIDEO_VGA)
	{
		m_strArray.Add(_T("VGA"));
	}
	if(g_PubData.g_jDevCap[g_PubData.g_iAttributeIng].chn_cap.stream_supp_resolution[0] & CAP_VIDEO_SVGA)
	{
		m_strArray.Add(_T("SVGA"));
	}
	if(g_PubData.g_jDevCap[g_PubData.g_iAttributeIng].chn_cap.stream_supp_resolution[0] & CAP_VIDEO_UXGA)
	{
		m_strArray.Add(_T("UXGA"));
	}
	if(g_PubData.g_jDevCap[g_PubData.g_iAttributeIng].chn_cap.stream_supp_resolution[0] & CAP_VIDEO_720P)
	{
		m_strArray.Add(_T("720P"));
	}
	if(g_PubData.g_jDevCap[g_PubData.g_iAttributeIng].chn_cap.stream_supp_resolution[0] & CAP_VIDEO_960)
	{
		m_strArray.Add(_T("960P"));
	}
	if(g_PubData.g_jDevCap[g_PubData.g_iAttributeIng].chn_cap.stream_supp_resolution[0] & CAP_VIDEO_1080P)
	{
		m_strArray.Add(_T("1080P"));
	}
	if(g_PubData.g_jDevCap[g_PubData.g_iAttributeIng].chn_cap.stream_supp_resolution[0] & CAP_VIDEO_XGA)
	{
		m_strArray.Add(_T("XGA"));
	}
	if(g_PubData.g_jDevCap[g_PubData.g_iAttributeIng].chn_cap.stream_supp_resolution[0] & CAP_VIDEO_WXGA)
	{
		m_strArray.Add(_T("WXGA"));
	}
	if(g_PubData.g_jDevCap[g_PubData.g_iAttributeIng].chn_cap.stream_supp_resolution[0] & CAP_VIDEO_SXGA)
	{
		m_strArray.Add(_T("SXGA"));
	}
	if(g_PubData.g_jDevCap[g_PubData.g_iAttributeIng].chn_cap.stream_supp_resolution[0] & CAP_VIDEO_3Mega)
	{
		m_strArray.Add(_T("3Mega"));
	}
	if(g_PubData.g_jDevCap[g_PubData.g_iAttributeIng].chn_cap.stream_supp_resolution[0] & CAP_VIDEO_5Mega)
	{
		m_strArray.Add(_T("5Mega"));
	}
	if(g_PubData.g_jDevCap[g_PubData.g_iAttributeIng].chn_cap.stream_supp_resolution[0] & CAP_VIDEO_UltraHD)
	{
		m_strArray.Add(_T("UltraHD"));
	}
	if(g_PubData.g_iLanguageFlag == 0)
	{
		m_comQuality.AddString(_T("最好"));
		m_comQuality.AddString(_T("次好"));
		m_comQuality.AddString(_T("较好"));
		m_comQuality.AddString(_T("一般"));
		m_comQuality.AddString(_T("较查"));
		m_comQuality.AddString(_T("差"));

		m_comWlv.AddString(_T("定码流"));
		m_comWlv.AddString(_T("变码流"));
		m_comWlv.AddString(_T("按质量编码"));
	}
	else
	{
		m_comQuality.AddString(_T("Best"));
		m_comQuality.AddString(_T("Better"));
		m_comQuality.AddString(_T("Good"));
		m_comQuality.AddString(_T("Normal"));
		m_comQuality.AddString(_T("Worse"));
		m_comQuality.AddString(_T("Worst"));

		m_comWlv.AddString(_T("Constant Rate"));
		m_comWlv.AddString(_T("Variable Rate"));
		m_comWlv.AddString(_T("Encode According to img quality"));
	}
	


	m_eZs.AddString(_T("PAL"));
	m_eZs.AddString(_T("NTSC"));


	m_comEncodeOrder.AddString(_T("BASELINE"));
	m_comEncodeOrder.AddString(_T("MAIN"));
	m_comEncodeOrder.AddString(_T("HIGH"));

	m_comEncodeModel.AddString(_T("H264"));
	m_comEncodeModel.SetCurSel(0);
	return TRUE;
}
void CMainStream::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CDialog::OnClose();
}
