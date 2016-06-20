// Logo.cpp : implementation file
//

#include "stdafx.h"
#include "demoIVSPC.h"
#include "Logo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


CLogo::CLogo(CWnd* pParent /*=NULL*/)
	: CDialog(CLogo::IDD, pParent)
{

}


void CLogo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLogo)
	DDX_Control(pDX, IDC_PROGRESS, m_ctrlProgress);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLogo, CDialog)
	//{{AFX_MSG_MAP(CLogo)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLogo message handlers

BOOL CLogo::OnInitDialog() 
{
	CDialog::OnInitDialog();
		g_SetWndStaticText(this);
	// TODO: Add extra initialization here
	m_ctrlProgress.SetRange(1, 8);
	m_ctrlProgress.SetStep(1);

	return TRUE;
}

void CLogo::stepIt()
{
	m_ctrlProgress.StepIt();
}