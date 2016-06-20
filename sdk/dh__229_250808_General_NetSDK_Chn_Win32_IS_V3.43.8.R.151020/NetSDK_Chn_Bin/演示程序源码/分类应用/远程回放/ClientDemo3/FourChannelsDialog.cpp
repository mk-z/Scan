// FourChannelsDialog.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo3.h"
#include "FourChannelsDialog.h"
#include "PlaybackMulty.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFourChannelsDialog dialog


CFourChannelsDialog::CFourChannelsDialog(CWnd* pParent /*=NULL*/, int nChannel)
	: CDialog(CFourChannelsDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFourChannelsDialog)
	m_nChannelFourValible = m_nChannelFour = 4;
	m_nChannelOneValible = m_nChannelOne = 1;
	m_nChannelThreeValible = m_nChannelThree = 3;
	m_nChannelTwoValible = m_nChannelTwo = 2;
    m_nChannelNum = nChannel;
	//}}AFX_DATA_INIT
}


void CFourChannelsDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFourChannelsDialog)
	DDX_Text(pDX, IDC_EDIT_CHANNEL_FOUR, m_nChannelFour);
	DDV_MinMaxInt(pDX, m_nChannelFour, 1, 999);
	DDX_Text(pDX, IDC_EDIT_CHANNEL_ONE, m_nChannelOne);
	DDV_MinMaxInt(pDX, m_nChannelOne, 1, 999);
	DDX_Text(pDX, IDC_EDIT_CHANNEL_THREE, m_nChannelThree);
	DDV_MinMaxInt(pDX, m_nChannelThree, 1, 999);
	DDX_Text(pDX, IDC_EDIT_CHANNEL_TWO, m_nChannelTwo);
	DDV_MinMaxInt(pDX, m_nChannelTwo, 1, 999);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFourChannelsDialog, CDialog)
	//{{AFX_MSG_MAP(CFourChannelsDialog)
	ON_BN_CLICKED(IDC_BUTTON_OK, OnButtonOk)
	ON_BN_CLICKED(IDC_BUTTON_CANCEL, OnButtonCancel)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFourChannelsDialog message handlers

void CFourChannelsDialog::OnButtonOk() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
    if (m_nChannelOne > m_nChannelNum || m_nChannelTwo > m_nChannelNum || m_nChannelThree > m_nChannelNum || m_nChannelFour > m_nChannelNum)
    {
        MessageBox(ConvertString("Wrong channel number!"), ConvertString("Prompt"));
        return;
    }

    if (m_nChannelOne == m_nChannelTwo || m_nChannelOne == m_nChannelThree || m_nChannelOne == m_nChannelFour || m_nChannelTwo == m_nChannelThree || m_nChannelTwo == m_nChannelFour || m_nChannelThree == m_nChannelFour)
    {
        MessageBox(ConvertString("Same channel number!"), ConvertString("Prompt"));
        return;
    }

    m_nChannelOneValible = m_nChannelOne;
    m_nChannelTwoValible = m_nChannelTwo;
    m_nChannelThreeValible = m_nChannelThree;
    m_nChannelFourValible = m_nChannelFour;

    CDialog::OnOK();
}

void CFourChannelsDialog::OnButtonCancel() 
{
	// TODO: Add your control notification handler code here
    m_nChannelOne = m_nChannelOneValible;
    m_nChannelTwo = m_nChannelTwoValible;
    m_nChannelThree = m_nChannelThreeValible;
    m_nChannelFour = m_nChannelFourValible;
    UpdateData(FALSE);
    CDialog::OnCancel();
}


void CFourChannelsDialog::GetFourChannelsNumber(int &nChannelOne, int &nChannelTwo, int &nChannelThree, int &nChannelFour)
{
    nChannelOne = m_nChannelOneValible - 1;
    nChannelTwo = m_nChannelTwoValible - 1;
    nChannelThree = m_nChannelThreeValible - 1;
    nChannelFour = m_nChannelFourValible - 1;
}

BOOL CFourChannelsDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	g_SetWndStaticText(this);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
