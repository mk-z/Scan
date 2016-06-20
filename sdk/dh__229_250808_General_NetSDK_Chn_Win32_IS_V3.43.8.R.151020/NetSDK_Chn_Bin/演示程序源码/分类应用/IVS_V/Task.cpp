// Task.cpp : implementation file
//

#include "stdafx.h"
#include "IVS_VDemo.h"
#include "Task.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTaskCfg dialog


CTaskCfg::CTaskCfg(CWnd* pParent /*=NULL*/)
	: CDialog(CTaskCfg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTaskCfg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CTaskCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTaskCfg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTaskCfg, CDialog)
	//{{AFX_MSG_MAP(CTaskCfg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTaskCfg message handlers

void CTaskCfg::OnOK() 
{
	// TODO: Add extra validation here
	
	CDialog::OnOK();
}

void CTaskCfg::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}
