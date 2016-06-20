// ConfigFile.cpp : implementation file
//

#include "stdafx.h"
#include "ClientDemo5.h"
#include "ConfigFile.h"
#include "ClientDemo5Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CConfigFile dialog
void CALLBACK  ImportCallBack(LONG lPlayHandle, DWORD dwTotalSize, DWORD dwDownLoadSize, DWORD dwUser)
{
	CConfigFile* dlg = (CConfigFile*)dwUser;
	if(NULL == dlg)
	{
		return;
	}
	
	if (dwTotalSize != 0 && dwDownLoadSize > 0)	//Sending out data
	{
		dlg->m_progressImport.SetPos(dwTotalSize*100/dwDownLoadSize);
	}
	else if (dwTotalSize != 0 && -1 == dwDownLoadSize)	//Send out process completed
	{
		dlg->m_progressImport.SetPos(0);
	}
	else if (dwTotalSize == 0 && -1 == dwDownLoadSize)	//Import configuration file successfully
	{
		dlg->SetDlgItemText(IDC_STATIC_STATUS, ConvertString("Import config file successfully!"));
		((CButton*)dlg->GetDlgItem(IDC_BUTTON_IMPORT))->EnableWindow(TRUE);
		((CButton*)dlg->GetDlgItem(IDC_BUTTON_STOP_IMPORT))->EnableWindow(FALSE);
		
		((CButton*)dlg->GetDlgItem(IDC_BUTTON_EXPORT))->EnableWindow(TRUE);
		((CButton*)dlg->GetDlgItem(IDC_BUTTON_STOP_EXPORT))->EnableWindow(FALSE);

		CLIENT_StopImportCfgFile(dlg->m_lImport);
	}
	else if (dwTotalSize == 0 && -2 == dwDownLoadSize)	//Import configuration file failed
	{
		dlg->SetDlgItemText(IDC_STATIC_STATUS, ConvertString("Failed to import config file!"));
		((CButton*)dlg->GetDlgItem(IDC_BUTTON_IMPORT))->EnableWindow(TRUE);
		((CButton*)dlg->GetDlgItem(IDC_BUTTON_STOP_IMPORT))->EnableWindow(FALSE);
		
		((CButton*)dlg->GetDlgItem(IDC_BUTTON_EXPORT))->EnableWindow(TRUE);
		((CButton*)dlg->GetDlgItem(IDC_BUTTON_STOP_EXPORT))->EnableWindow(FALSE);

		CLIENT_StopImportCfgFile(dlg->m_lImport);
	}
	else if (dwTotalSize == 0 && -3 == dwDownLoadSize)	//Error occurred when importing configuration file
	{
		dlg->SetDlgItemText(IDC_STATIC_STATUS, ConvertString("Import config file error!"));
		((CButton*)dlg->GetDlgItem(IDC_BUTTON_IMPORT))->EnableWindow(TRUE);
		((CButton*)dlg->GetDlgItem(IDC_BUTTON_STOP_IMPORT))->EnableWindow(FALSE);
		
		((CButton*)dlg->GetDlgItem(IDC_BUTTON_EXPORT))->EnableWindow(TRUE);
		((CButton*)dlg->GetDlgItem(IDC_BUTTON_STOP_EXPORT))->EnableWindow(FALSE);

		CLIENT_StopImportCfgFile(dlg->m_lImport);
	}

//	dlg->m_dwImportTotalSize = dwTotalSize;
//	dlg->m_dwImportDownloadSize = dwDownLoadSize;
}

void CALLBACK  ExportCallBack(LONG lPlayHandle, DWORD dwTotalSize, DWORD dwDownLoadSize, DWORD dwUser)
{
	CConfigFile* dlg = (CConfigFile*)dwUser;
	if(NULL == dlg)
	{
		return;
	}

	if (-1 != dwDownLoadSize)	//Exporting data
	{
		if (dwDownLoadSize > 0)
		{
			dlg->m_progressExport.SetPos(dwTotalSize*100/dwDownLoadSize);
		}
	}
	else	//Export process completed
	{
		CLIENT_StopExportCfgFile(dlg->m_lExport);

		dlg->m_progressExport.SetPos(0);

		((CButton*)dlg->GetDlgItem(IDC_BUTTON_IMPORT))->EnableWindow(TRUE);
		((CButton*)dlg->GetDlgItem(IDC_BUTTON_STOP_IMPORT))->EnableWindow(FALSE);

		((CButton*)dlg->GetDlgItem(IDC_BUTTON_EXPORT))->EnableWindow(TRUE);
		((CButton*)dlg->GetDlgItem(IDC_BUTTON_STOP_EXPORT))->EnableWindow(FALSE);
	}

//	dlg->m_dwExportTotalSize = dwTotalSize;
//	dlg->m_dwExportDownloadSize = dwDownLoadSize;
}

CConfigFile::CConfigFile(CWnd* pParent /*=NULL*/)
	: CDialog(CConfigFile::IDD, pParent)
{
	//{{AFX_DATA_INIT(CConfigFile)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CConfigFile::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CConfigFile)
	DDX_Control(pDX, IDC_PROGRESS_IMPORT, m_progressImport);
	DDX_Control(pDX, IDC_PROGRESS_EXPORT, m_progressExport);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CConfigFile, CDialog)
	//{{AFX_MSG_MAP(CConfigFile)
	ON_BN_CLICKED(IDC_BUTTON_IMPORT, OnButtonImport)
	ON_BN_CLICKED(IDC_BUTTON_STOP_IMPORT, OnButtonStopImport)
	ON_BN_CLICKED(IDC_BUTTON_EXPORT, OnButtonExport)
	ON_BN_CLICKED(IDC_BUTTON_STOP_EXPORT, OnButtonStopExport)
	ON_WM_CANCELMODE()
	ON_WM_TIMER()
	ON_WM_CAPTURECHANGED()
	ON_BN_CLICKED(IDC_BTN_FILE, OnBtnFile)
	ON_BN_CLICKED(IDC_BTN_FOLDER, OnBtnFolder)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CConfigFile message handlers
void CConfigFile::OnButtonImport() 
{
	// TODO: Add your control notification handler code here
	if (m_CSFolder.IsEmpty())
	{
		return;
	}

	SetDlgItemText(IDC_STATIC_STATUS, "");
	m_lImport = ((CClientDemo5Dlg*)AfxGetMainWnd())->ImportConfigFile(m_CSFolder.GetBuffer(0), ImportCallBack, (DWORD)this);
	if(m_lImport <= 0)
	{
		SetDlgItemText(IDC_STATIC_STATUS, ConvertString("Failed to import config file!"));
		return;
	}
	
	((CButton*)GetDlgItem(IDC_BUTTON_IMPORT))->EnableWindow(FALSE);
	((CButton*)GetDlgItem(IDC_BUTTON_STOP_IMPORT))->EnableWindow(TRUE);
	
	((CButton*)GetDlgItem(IDC_BUTTON_EXPORT))->EnableWindow(FALSE);
	((CButton*)GetDlgItem(IDC_BUTTON_STOP_EXPORT))->EnableWindow(FALSE);

//	m_Timer1 = SetTimer(1, 500, NULL);
}

void CConfigFile::OnButtonStopImport() 
{
	// TODO: Add your control notification handler code here
	if(!CLIENT_StopImportCfgFile(m_lImport))
	{
		MessageBox("stop failed", NULL, MB_OK);
		return ;
	}

	((CButton*)GetDlgItem(IDC_BUTTON_IMPORT))->EnableWindow(TRUE);
	((CButton*)GetDlgItem(IDC_BUTTON_STOP_IMPORT))->EnableWindow(FALSE);
	
	((CButton*)GetDlgItem(IDC_BUTTON_EXPORT))->EnableWindow(TRUE);
	((CButton*)GetDlgItem(IDC_BUTTON_STOP_EXPORT))->EnableWindow(FALSE);

	m_progressImport.SetPos(0);
	
//	KillTimer(m_Timer1);
}

void CConfigFile::OnButtonExport() 
{
	// TODO: Add your control notification handler code here
	if (m_CSFile.IsEmpty())
	{
		return;
	}

	DH_CONFIG_FILE_TYPE emFileType = DH_CONFIGFILE_ALL;
	m_lExport = ((CClientDemo5Dlg*)AfxGetMainWnd())->ExportConfigFile(m_CSFile.GetBuffer(0), emFileType, ExportCallBack, (DWORD)this);
	if(m_lExport <= 0)
	{
		return;
	}
	
	((CButton*)GetDlgItem(IDC_BUTTON_IMPORT))->EnableWindow(FALSE);
	((CButton*)GetDlgItem(IDC_BUTTON_STOP_IMPORT))->EnableWindow(FALSE);
	
	((CButton*)GetDlgItem(IDC_BUTTON_EXPORT))->EnableWindow(FALSE);
	((CButton*)GetDlgItem(IDC_BUTTON_STOP_EXPORT))->EnableWindow(TRUE);

//	m_Timer2 = SetTimer(2, 500, NULL);
}

void CConfigFile::OnButtonStopExport() 
{
	// TODO: Add your control notification handler code here
	if(!CLIENT_StopExportCfgFile(m_lExport))
	{
		MessageBox("stop export failed", NULL, MB_OK);
		return;
	}

	((CButton*)GetDlgItem(IDC_BUTTON_IMPORT))->EnableWindow(TRUE);
	((CButton*)GetDlgItem(IDC_BUTTON_STOP_IMPORT))->EnableWindow(FALSE);
	
	((CButton*)GetDlgItem(IDC_BUTTON_EXPORT))->EnableWindow(TRUE);
	((CButton*)GetDlgItem(IDC_BUTTON_STOP_EXPORT))->EnableWindow(FALSE);

	m_progressExport.SetPos(0);
	
//	KillTimer(m_Timer2);
}

BOOL CConfigFile::OnInitDialog() 
{
	CDialog::OnInitDialog();
	g_SetWndStaticText(this);
	// TODO: Add extra initialization here
	((CButton*)GetDlgItem(IDC_BUTTON_FOLDER))->EnableWindow(TRUE);
	((CButton*)GetDlgItem(IDC_BUTTON_IMPORT))->EnableWindow(TRUE);
	((CButton*)GetDlgItem(IDC_BUTTON_STOP_IMPORT))->EnableWindow(FALSE);
	
	((CButton*)GetDlgItem(IDC_BUTTON_FILE))->EnableWindow(TRUE);
	((CButton*)GetDlgItem(IDC_BUTTON_EXPORT))->EnableWindow(TRUE);
	((CButton*)GetDlgItem(IDC_BUTTON_STOP_EXPORT))->EnableWindow(FALSE);

	m_dwImportDownloadSize = 0;
	m_lImport = 0;
	m_lExport = 0;

	m_dwImportTotalSize = 0;
	m_dwImportDownloadSize = 0;
	m_dwExportTotalSize = 0;
	m_dwExportDownloadSize = 0;

	m_Timer1 = 0;
	m_Timer2 = 0;

	m_progressImport.SetRange(0, 100);
	m_progressExport.SetRange(0, 100);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CConfigFile::OnCancelMode() 
{
	CDialog::OnCancelMode();
	
	// TODO: Add your message handler code here


}

void CConfigFile::OnTimer(UINT_PTR nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	switch(nIDEvent)
	{
	case 1:
		{
			if (m_dwImportDownloadSize != 0)
			{
				m_progressImport.SetPos(m_dwImportTotalSize*100/m_dwImportDownloadSize);
			}
			
			if (m_dwImportDownloadSize == -1)
			{
				CLIENT_StopImportCfgFile(m_lImport);
				KillTimer(m_Timer1);
				((CButton*)GetDlgItem(IDC_BUTTON_IMPORT))->EnableWindow(TRUE);
				((CButton*)GetDlgItem(IDC_BUTTON_STOP_IMPORT))->EnableWindow(FALSE);

				((CButton*)GetDlgItem(IDC_BUTTON_EXPORT))->EnableWindow(TRUE);
				((CButton*)GetDlgItem(IDC_BUTTON_STOP_EXPORT))->EnableWindow(FALSE);
			}
		}
		break;
	case 2:
		{
			if (m_dwExportDownloadSize != 0)
			{
				m_progressExport.SetPos(m_dwExportDownloadSize*100/m_dwExportDownloadSize);
			}
			
			if (m_dwExportDownloadSize == -1)
			{
				CLIENT_StopExportCfgFile(m_lExport);
				KillTimer(m_Timer2);
				((CButton*)GetDlgItem(IDC_BUTTON_IMPORT))->EnableWindow(TRUE);
				((CButton*)GetDlgItem(IDC_BUTTON_STOP_IMPORT))->EnableWindow(FALSE);

				((CButton*)GetDlgItem(IDC_BUTTON_EXPORT))->EnableWindow(TRUE);
				((CButton*)GetDlgItem(IDC_BUTTON_STOP_EXPORT))->EnableWindow(FALSE);
			}
		}
		break;
	default:
		return;
	}
	CDialog::OnTimer(nIDEvent);
}

void CConfigFile::OnCaptureChanged(CWnd *pWnd) 
{
	// TODO: Add your message handler code here
	
	CDialog::OnCaptureChanged(pWnd);
}

void CConfigFile::OnBtnFile() 
{
	// TODO: Add your control notification handler code here
	CFileDialog dlg(TRUE, "*.*", "", OFN_OVERWRITEPROMPT|OFN_HIDEREADONLY,
		"All File(*.*)|*.*||",this);
	if(dlg.DoModal() == IDOK)
	{
		m_CSFolder = dlg.GetPathName();
		SetDlgItemText(IDC_EDIT_IMPORT, m_CSFolder);
	}
}

void CConfigFile::OnBtnFolder() 
{
	// TODO: Add your control notification handler code here
	//Open file folder dialogue box
	LPMALLOC   pMalloc;  
	if   (::SHGetMalloc(&pMalloc)   ==   NOERROR)   
	{   
		BROWSEINFO   bi;   
		TCHAR   pszBuffer[MAX_PATH];   
		LPITEMIDLIST   pidl;   
		bi.hwndOwner   =   this->m_hWnd;   
		bi.pidlRoot   =   NULL;   
		bi.pszDisplayName   =   pszBuffer;   
		bi.lpszTitle   =   _T(ConvertString("select folder"));   
		bi.ulFlags   =   BIF_RETURNFSANCESTORS   |   BIF_RETURNONLYFSDIRS;   
		bi.lpfn   =   NULL;   
		bi.lParam   =   0;   
		bi.iImage   =   0;   
		if   ((pidl   =   ::SHBrowseForFolder(&bi))   !=   NULL)   
		{   
			if   (::SHGetPathFromIDList(pidl,   pszBuffer))   
			{
				m_CSFile.Empty();
				m_CSFile  =  pszBuffer;  
				SetDlgItemText(IDC_EDIT_EXPORT, pszBuffer);
			}
			else
			{
				return;   
			}
			pMalloc->Free(pidl);   
		}   
		pMalloc->Release();   
	} 
}








































































































































































































































































































































































































































































































































