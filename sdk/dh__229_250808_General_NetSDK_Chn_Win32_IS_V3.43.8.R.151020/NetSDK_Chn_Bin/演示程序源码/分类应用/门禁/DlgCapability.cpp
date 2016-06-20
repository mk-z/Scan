// DlgCapability.cpp : implementation file
//

#include "stdafx.h"
#include "AccessControl.h"
#include "DlgCapability.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgCapability dialog

CDlgCapability::CDlgCapability(CWnd* pParent /* = NULL */, LLONG hLoginID /* = NULL */, AV_uint32 uiAlarmIn /* = 0 */, AV_uint32 uiAlarmOut /* = 0 */)
	: CDialog(CDlgCapability::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgCapability)
	m_hLogin = hLoginID;
	m_uiAlarmIn = uiAlarmIn;
	m_uiAlarmOut = uiAlarmOut;
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgCapability::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgCapability)
	DDX_Control(pDX, IDC_DLG_CAP_LIST_ERR, m_lsErrorInfo);
	DDX_Control(pDX, IDC_DLG_CAP_EDT_SHOW, m_edtShow);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgCapability, CDialog)
	//{{AFX_MSG_MAP(CDlgCapability)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgCapability message handlers

BOOL CDlgCapability::OnInitDialog() 
{
	CDialog::OnInitDialog();
	g_SetWndStaticText(this, DLG_CAPABILITY);
	// TODO: Add extra initialization here
	if (!m_hLogin)
	{
		OutputInfo(ConvertString(CString("we haven't login a device yet!"), DLG_CAPABILITY));
		return TRUE;
	}

	GetCapability();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgCapability::GetCapability()
{
	// string for storing all caps
	CString csCap;
	
	// cap of log service
	CString csLogService;
	if (GetLogServiceCap(csLogService))
	{
		csCap += csLogService;
	}

    // cap of RecordSetFinder
    CString csRecordSetFinder;
    if (GetRecordSetFinderCap(csRecordSetFinder))
    {
        csCap += csRecordSetFinder;
    }

	// cap of access manager
	CString csAccessControlCap;
	if (GetAccessControlCap(csAccessControlCap))
	{
		csCap += csAccessControlCap;
	}

	// show all these caps
	{		
		m_edtShow.SetWindowText(csCap);
	}
}

void CDlgCapability::OutputInfo(const CString& csInfo)
{
	SYSTEMTIME st;
	GetLocalTime(&st);
	
	CString csOut;
	csOut.Format("%04d-%02d-%02d %02d:%02d:%02d: %s",
		st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond,
		csInfo);
	
	m_lsErrorInfo.InsertString(0, csOut);
}

BOOL CDlgCapability::GetLogServiceCap(CString& csCap)
{
	char szBuff[1024] = {0};
	int nError = 0;
	BOOL bRet = CLIENT_QueryNewSystemInfo(m_hLogin, CFG_CAP_CMD_LOG, 0, szBuff, sizeof(szBuff), &nError, SDK_API_WAITTIME);
	if (bRet)
	{
		CFG_CAP_LOG stuInfo = {0};
		DWORD dwRet = 0;
		bRet = CLIENT_ParseData(CFG_CAP_CMD_LOG, szBuff, &stuInfo, sizeof(CFG_CAP_LOG), &dwRet);
		if (bRet && dwRet == sizeof(CFG_CAP_LOG))
		{
			CString csLogServiceCap;
			csLogServiceCap.Format("%s = %d\r\n\
%s = %d\r\n\
%s = %s\r\n\
%s = %s\r\n\
%s = %s\r\n",
				ConvertString("LogMaxItem", DLG_CAPABILITY),
				stuInfo.dwMaxLogItems,
				ConvertString("MaxPageLogItem", DLG_CAPABILITY),
				stuInfo.dwMaxPageItems,
				ConvertString("IsSupportStartNo", DLG_CAPABILITY),
				stuInfo.bSupportStartNo ? ConvertString("Yes", DLG_CAPABILITY) : ConvertString("No", DLG_CAPABILITY),
				ConvertString("IsSupportTypeFilter", DLG_CAPABILITY),
				stuInfo.bSupportTypeFilter ? ConvertString("Yes", DLG_CAPABILITY) : ConvertString("No", DLG_CAPABILITY),
				ConvertString("IsSupportTimeFilter", DLG_CAPABILITY),
				stuInfo.bSupportTimeFilter ? ConvertString("Yes", DLG_CAPABILITY) : ConvertString("No", DLG_CAPABILITY));
			csCap += csLogServiceCap;
			csCap += "\r\n";
		}
		else
		{
			return FALSE;
		}
	}
	else
	{
		return FALSE;
	}
	return TRUE;

}

BOOL CDlgCapability::GetRecordSetFinderCap(CString& csCap)
{
    char szBuff[1024] = {0};
    int nError = 0;
	BOOL bRet = CLIENT_QueryNewSystemInfo(m_hLogin, CFG_CAP_CMD_RECORDFINDER, 0, szBuff, sizeof(szBuff), &nError, SDK_API_WAITTIME);
    if (bRet)
    {
        CFG_CAP_RECORDFINDER_INFO stuCap = {0};
        DWORD dwRet = 0;
        bRet = CLIENT_ParseData(CFG_CAP_CMD_RECORDFINDER, szBuff, &stuCap, sizeof(stuCap), &dwRet);
        if (bRet && dwRet == sizeof(CFG_CAP_RECORDFINDER_INFO))
        {
            csCap += ConvertString("RecordSetFinder Cap:", DLG_CAPABILITY);
            csCap += "\r\n";

            CString csMaxPageSize;
            csMaxPageSize.Format("%s = %d\r\n",
                ConvertString("MaxPageSize", DLG_CAPABILITY),
                stuCap.nMaxPageSize);
            csCap += csMaxPageSize;
            csCap += "\r\n";
        }
        else
        {
            return FALSE;
        }
    }
    else
    {
        return FALSE;
    }
    return TRUE;
}

BOOL CDlgCapability::GetAccessControlCap(CString& csCap)
{
	char szBuf[1024] = {0};
	int nError = 0;
	BOOL bRet = CLIENT_QueryNewSystemInfo(m_hLogin, CFG_CAP_CMD_ACCESSCONTROLMANAGER, -1, szBuf, sizeof(szBuf), &nError, SDK_API_WAITTIME);
	if (bRet)
	{
		CFG_CAP_ACCESSCONTROL stuCap = {0};
		DWORD dwRet = 0;
		bRet = CLIENT_ParseData(CFG_CAP_CMD_ACCESSCONTROLMANAGER, szBuf, &stuCap, sizeof(stuCap), &dwRet);
		if (bRet && dwRet == sizeof(CFG_CAP_ACCESSCONTROL))
		{			
			csCap += ConvertString("AccessControlManager Cap:", DLG_CAPABILITY);

			csCap += "\r\n";
			CString csAccessControl;
			csAccessControl.Format("%s = %d \r\n", 
				ConvertString("support access count ", DLG_CAPABILITY),
				stuCap.nAccessControlGroups);
			csCap += csAccessControl;
			csCap += "\r\n";
		}
		else
		{
			return FALSE;
		}
	}
	else
	{
		return FALSE;
	}
	return TRUE;
}
