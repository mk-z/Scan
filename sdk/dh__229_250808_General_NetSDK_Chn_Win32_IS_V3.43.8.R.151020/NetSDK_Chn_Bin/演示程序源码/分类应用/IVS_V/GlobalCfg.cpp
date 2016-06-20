// GlobalCfg.cpp : implementation file
//

#include "stdafx.h"
#include "IVS_VDemo.h"
#include "GlobalCfg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGlobalCfg dialog


CGlobalCfg::CGlobalCfg(CWnd* pParent /*=NULL*/)
	: CDialog(CGlobalCfg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGlobalCfg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CGlobalCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGlobalCfg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CGlobalCfg, CDialog)
	//{{AFX_MSG_MAP(CGlobalCfg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGlobalCfg message handlers

void CGlobalCfg::OnOK() 
{
	// TODO: Add extra validation here
	
	//CDialog::OnOK();
}

void CGlobalCfg::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	//CDialog::OnCancel();
}
