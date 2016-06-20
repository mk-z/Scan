// Profile.cpp : implementation file
//

#include "stdafx.h"
#include "IVS_VDemo.h"
#include "Profile.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CProfileCfg dialog


CProfileCfg::CProfileCfg(CWnd* pParent /*=NULL*/)
	: CDialog(CProfileCfg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CProfileCfg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CProfileCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CProfileCfg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CProfileCfg, CDialog)
	//{{AFX_MSG_MAP(CProfileCfg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProfileCfg message handlers

void CProfileCfg::OnOK() 
{
	// TODO: Add extra validation here
	
	CDialog::OnOK();
}

void CProfileCfg::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}
