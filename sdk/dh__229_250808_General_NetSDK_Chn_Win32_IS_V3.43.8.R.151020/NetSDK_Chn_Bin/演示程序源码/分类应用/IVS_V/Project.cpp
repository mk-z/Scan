// Project.cpp : implementation file
//

#include "stdafx.h"
#include "IVS_VDemo.h"
#include "Project.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CProjectCfg dialog


CProjectCfg::CProjectCfg(CWnd* pParent /*=NULL*/)
	: CDialog(CProjectCfg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CProjectCfg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CProjectCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CProjectCfg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CProjectCfg, CDialog)
	//{{AFX_MSG_MAP(CProjectCfg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProjectCfg message handlers

void CProjectCfg::OnOK() 
{
	// TODO: Add extra validation here
	
	CDialog::OnOK();
}

void CProjectCfg::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}
