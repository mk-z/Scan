// AddDevice.cpp : implementation file
//

#include "stdafx.h"
#include "IVS_VDemo.h"
#include "AddDevice.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAddDevice dialog


CAddDevice::CAddDevice(CWnd* pParent /*=NULL*/)
	: CDialog(CAddDevice::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAddDevice)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CAddDevice::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAddDevice)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAddDevice, CDialog)
	//{{AFX_MSG_MAP(CAddDevice)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAddDevice message handlers

void CAddDevice::OnOK() 
{
	// TODO: Add extra validation here
	
	CDialog::OnOK();
}

void CAddDevice::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}
