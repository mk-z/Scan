// ChannelOneDialog.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo3.h"
#include "ChannelOneDialog.h"
#include "PlaybackMulty.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChannelOneDialog dialog


CChannelOneDialog::CChannelOneDialog(CWnd* pParent /*=NULL*/, int nChannelNum)
	: CDialog(CChannelOneDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CChannelOneDialog)
	m_nChannelOneValible = m_nChannelOne = 1;
    m_nChannelNum = nChannelNum;
	//}}AFX_DATA_INIT
}


void CChannelOneDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CChannelOneDialog)
	DDX_Text(pDX, IDC_EDIT_CHANNEL_ONE, m_nChannelOne);
	DDV_MinMaxInt(pDX, m_nChannelOne, 1, 999);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CChannelOneDialog, CDialog)
	//{{AFX_MSG_MAP(CChannelOneDialog)
	ON_BN_CLICKED(IDC_BUTTON_OK, OnButtonOk)
	ON_BN_CLICKED(IDC_BUTTON_CANCEL, OnButtonCancel)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChannelOneDialog message handlers

void CChannelOneDialog::OnButtonOk() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);
	if (m_nChannelOne > m_nChannelNum)
    {
        MessageBox(ConvertString("Wrong channel number!"), ConvertString("Prompt"));
        return;
    }

    m_nChannelOneValible = m_nChannelOne;
    CDialog::OnOK();
}

void CChannelOneDialog::OnButtonCancel() 
{
	// TODO: Add your control notification handler code here
    m_nChannelOne = m_nChannelOneValible;
    UpdateData(FALSE);
	CDialog::OnCancel();
}

void CChannelOneDialog::GetOneChannelModeNumber(int &nChannelOne)
{
    nChannelOne = m_nChannelOne - 1;
}

BOOL CChannelOneDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	g_SetWndStaticText(this);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
