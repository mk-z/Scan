// DlgDVR.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo5.h"
#include "DlgDVR.h"
#include "ClientDemo5Dlg.h"
#include "dhconfigsdk.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define WAITTIME 2000

/////////////////////////////////////////////////////////////////////////////
// CDlgDVR dialog


CDlgDVR::CDlgDVR(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgDVR::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgDVR)
	m_bIPColl = FALSE;
	m_bNewProtocol = FALSE;
	//}}AFX_DATA_INIT

	m_stuIPConflitInfo = new CFG_IPCONFLICT_INFO;
	if (m_stuIPConflitInfo)
	{
		memset(m_stuIPConflitInfo, 0, sizeof(CFG_IPCONFLICT_INFO));
	}
}

CDlgDVR::~CDlgDVR()
{
	if (m_stuIPConflitInfo)
	{
		delete m_stuIPConflitInfo;
	}
};


void CDlgDVR::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgDVR)
	DDX_Check(pDX, IDC_CHECK_IPCOLL, m_bIPColl);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgDVR, CDialog)
	//{{AFX_MSG_MAP(CDlgDVR)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, OnButtonSave)
	ON_BN_CLICKED(IDC_BUTTON_READ, OnButtonRead)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgDVR message handlers

void CDlgDVR::OnButtonSave() 
{
	// TODO: Add your control notification handler code here
	SetIPCollisionCfg();
}

void CDlgDVR::OnButtonRead() 
{
	// TODO: Add your control notification handler code here
 	GetIPCollisionCfg();
}

BOOL CDlgDVR::OnInitDialog() 
{
	CDialog::OnInitDialog(); 
	
	g_SetWndStaticText(this);
	// TODO: Add extra initialization here
	m_dlgMsgHandle.Create(IDD_DIALOG_MSGHANDLE, this);
	m_dlgMsgHandle.Attach(IDC_STATIC_MSGHANDLE, this);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgDVR::GetIPCollisionCfg()
{
	DWORD dwRetLen = 0;
	
	DHDEV_SYSTEM_ATTR_CFG sysConfigInfo = {0};
	
	   BOOL bSuccess = CLIENT_GetDevConfig(m_lLogin, DH_DEV_DEVICECFG, 0,
		   &sysConfigInfo, sizeof(DHDEV_SYSTEM_ATTR_CFG), &dwRetLen, 3000);
	   if (bSuccess && dwRetLen == sizeof(DHDEV_SYSTEM_ATTR_CFG))
	   {
		   //Alarm input channel amount 
		   BYTE nAlarmInCount = sysConfigInfo.byAlarmInNum>32?32:sysConfigInfo.byAlarmInNum;
		   //Alarm output channel amount 
		   BYTE nAlarmOutCount = sysConfigInfo.byAlarmOutNum>32?32:sysConfigInfo.byAlarmOutNum;
		   //Channel amount 
		   BYTE nChannelCount = sysConfigInfo.byVideoCaptureNum>32?32:sysConfigInfo.byVideoCaptureNum;
		   	   
// 		   if (m_bNewProtocol == FALSE)
// 		   {
// 			   BOOL bRet = CLIENT_GetDevConfig(m_lLogin,
// 				   DH_DEV_IP_COLLISION_CFG,
// 				   0,
// 				   (LPVOID)&m_stuIPCollCfg,
// 				   sizeof(m_stuIPCollCfg),
// 				   &dwRetLen,
// 				   WAITTIME);
// 			   if(dwRetLen != sizeof(m_stuIPCollCfg) || (bRet == FALSE))
// 			   {
// #ifdef _DEBUG
// 				   DWORD dwError = CLIENT_GetLastError();
// #endif
// 				   MessageBox(ConvertString("Get ip collision configure failed."));	
// 			   }	
// 			   //TODO
// 			   m_dlgMsgHandle.SetMsgHandle(m_stuIPCollCfg.struHandle, nAlarmInCount, nAlarmOutCount, nChannelCount);
// 			   m_bIPColl = m_stuIPCollCfg.bEnable;
// 		   }
// 		   else//超过16路的设备
		   {
			   char *szOutBuffer = new char[32*1024];
			   if (szOutBuffer == NULL)
			   {	
				   return;	
			   }
			   int nerror = 0;
			   {
				   DH_MSG_HANDLE_EX struHandle = {0};
				   BOOL bSuccess = CLIENT_GetNewDevConfig(m_lLogin, CFG_CMD_IPCONFLICT, 0, szOutBuffer, 32*1024, &nerror, 3000);		
				   if (bSuccess)
				   {
					   //解析 
					   int nRetLen = 0;
					   BOOL bRet = CLIENT_ParseData(CFG_CMD_IPCONFLICT, szOutBuffer, (char *)m_stuIPConflitInfo, sizeof(CFG_IPCONFLICT_INFO), &nRetLen);
					   if (bRet == FALSE)
					   {
						   MessageBox(ConvertString("Parser data error"), ConvertString("Prompt"));
					   }
					   else
					   {
						   m_bIPColl = m_stuIPConflitInfo->bEnable;
						   
						   ((CClientDemo5Dlg*)AfxGetMainWnd())->ParseEventHandle(m_stuIPConflitInfo->stuEventHandler, &struHandle);
						   
						   //TODO
						   m_dlgMsgHandle.SetMsgHandleEx(struHandle, nAlarmInCount, nAlarmOutCount, nChannelCount);			   
					   }
				   }
				   else
				   {
					   MessageBox(ConvertString("Get ip collision configure failed."), ConvertString("Prompt"));
				   }
			   }
			   
			   if (szOutBuffer)
			   {
				   delete []szOutBuffer;
				   szOutBuffer = NULL;
			   }		
		   }
	   }

	UpdateData(FALSE);
}

void CDlgDVR::SetIPCollisionCfg()
{
	if(UpdateData(TRUE) == FALSE)
	{
		return;
	}
	
// 	if (m_bNewProtocol == FALSE)
// 	{
// 		if(m_dlgMsgHandle.GetMsgHandle(m_stuIPCollCfg.struHandle) == FALSE)
// 		{
// 			return;
// 		}
// 		m_stuIPCollCfg.bEnable = m_bIPColl;
// 		
// 		BOOL bRet = CLIENT_SetDevConfig(m_lLogin,
// 			DH_DEV_IP_COLLISION_CFG,
// 			0,
// 			(LPVOID)&m_stuIPCollCfg,
// 			sizeof(m_stuIPCollCfg),
// 			WAITTIME);
// 		if(bRet == FALSE)
// 		{
// #ifdef _DEBUG
// 			DWORD dwError = CLIENT_GetLastError();
// #endif
// 			MessageBox(ConvertString("Set ip collision configure failed."));
// 			return;
// 		}
// 	}
// 	else
	{
		DH_MSG_HANDLE_EX struHandle;
		memset(&struHandle, 0, sizeof(DH_MSG_HANDLE_EX));
		if(m_dlgMsgHandle.GetMsgHandleEx(struHandle) == FALSE)
		{
			return;
		}
		m_stuIPCollCfg.bEnable = m_bIPColl;
		
		char *szOutBuffer = new char[32*1024];
		if (szOutBuffer == NULL)
		{
			return;	
		}
		
		int nalarmerror = 0;	
		int nrestart = 0;

		if(0 != m_lLogin)
		{
			memset(szOutBuffer, 0, 32*1024);
			//组包
			m_stuIPConflitInfo->bEnable = m_bIPColl;
			
			((CClientDemo5Dlg*)AfxGetMainWnd())->BuildEventHandle(struHandle, &m_stuIPConflitInfo->stuEventHandler);

			BOOL bRet = CLIENT_PacketData(CFG_CMD_IPCONFLICT, m_stuIPConflitInfo, sizeof(CFG_IPCONFLICT_INFO), szOutBuffer, 32*1024);
			if (bRet == FALSE)
			{
				MessageBox(ConvertString("Pack data error"), ConvertString("Prompt"));
			}
			else
			{
				BOOL bSuccess = CLIENT_SetNewDevConfig(m_lLogin, CFG_CMD_IPCONFLICT, 0, (char *)szOutBuffer, 32*1024, &nalarmerror, &nrestart, 3000);		
				if (bSuccess)
				{
					if (nrestart == 1)
					{
						MessageBox(ConvertString("Save config info successfully!devide need restart!"), ConvertString("Prompt"));
					}
					
				}
				else
				{
					MessageBox(ConvertString("Set ip collision configure failed."), ConvertString("Prompt"));	
				}
				
			}		
		}
		else
		{
			MessageBox(ConvertString("Login first!"), ConvertString("Prompt"));
		}
		
		if (szOutBuffer)
		{
			delete []szOutBuffer;
			szOutBuffer = NULL;
		}	
	}	
}
