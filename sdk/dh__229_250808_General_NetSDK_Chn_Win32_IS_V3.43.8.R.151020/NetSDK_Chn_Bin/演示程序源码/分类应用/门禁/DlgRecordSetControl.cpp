// DlgRecordSetControl.cpp : implementation file
//

#include "stdafx.h"
#include "accesscontrol.h"
#include "DlgRecordSetControl.h"
#include "SubDlgInfoCard.h"
#include "DlgSubDlgInfoPassword.h"
#include "DlgSubDlgInfoAccessRecord.h"
#include "DlgSubDlgInfoHoliday.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgRecordSetControl dialog


CDlgRecordSetControl::CDlgRecordSetControl(CWnd* pParent /* = NULL */, LLONG lLoginID /* = 0 */, int nAccess /* = 1 */)
	: CDialog(CDlgRecordSetControl::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgRecordSetControl)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_lLoginID      = lLoginID;
    m_nAccessGroup  = nAccess;
	m_emOpType = Em_Operate_Type_Show;
}


void CDlgRecordSetControl::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgRecordSetControl)
	DDX_Control(pDX, IDD_RECORDSET_CTL_CMB_SETTYPE, m_cmbSetType);
	DDX_Control(pDX, IDD_RECORDSET_CTL_CMB_CTLTYPE, m_cmbCtlType);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgRecordSetControl, CDialog)
	//{{AFX_MSG_MAP(CDlgRecordSetControl)
	ON_BN_CLICKED(IDD_RECORDSET_CTL_BTN_EXECUTE, OnRecordsetCtlBtnExecute)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgRecordSetControl private method

void CDlgRecordSetControl::InitDlg()
{
	int n = 0;

	m_cmbSetType.ResetContent();
    int nWidth = m_cmbSetType.GetDroppedWidth();
    m_cmbSetType.SetDroppedWidth(nWidth * 2);
	for (n = 0; n < sizeof(stuDemoRecordSetType)/sizeof(stuDemoRecordSetType[0]); n++)
	{
		m_cmbSetType.InsertString(-1, ConvertString(stuDemoRecordSetType[n].szName));
	}
	m_cmbSetType.SetCurSel(0);
	
	m_cmbCtlType.ResetContent();
	for (n = 0; n < sizeof(stuDemoRecordSetCtlType)/sizeof(stuDemoRecordSetCtlType[0]); n++)
	{
		m_cmbCtlType.InsertString(-1, ConvertString(stuDemoRecordSetCtlType[n].szName, DLG_RECORDSET_CONTROL));
	}
	m_cmbCtlType.SetCurSel(0);
}
//////////////////////////////////////////////////////////////////////////
// card
//////////////////////////////////////////////////////////////////////////
void CDlgRecordSetControl::CardInsert()
{
	CSubDlgInfoCard dlg(this, NULL, m_nAccessGroup);
	dlg.SetOperateType(m_emOpType);
	if (IDOK == dlg.DoModal())
	{
		if (!dlg.IsDirty())
		{
			const NET_RECORDSET_ACCESS_CTL_CARD& stuInfo = dlg.GetInfo();
			
			NET_CTRL_RECORDSET_INSERT_PARAM stuParam = {sizeof(stuParam)};
			stuParam.stuCtrlRecordSetInfo.dwSize = sizeof(NET_CTRL_RECORDSET_INSERT_IN);
			stuParam.stuCtrlRecordSetInfo.emType = NET_RECORD_ACCESSCTLCARD;
			stuParam.stuCtrlRecordSetInfo.pBuf = (void*)&stuInfo;
			stuParam.stuCtrlRecordSetInfo.nBufLen = sizeof(stuInfo);
			
			stuParam.stuCtrlRecordSetResult.dwSize = sizeof(NET_CTRL_RECORDSET_INSERT_OUT);
			
			BOOL bRet = FALSE;
			if (m_emOpType == Em_Operate_Type_Insert)
			{
				bRet = CLIENT_ControlDevice(m_lLoginID, DH_CTRL_RECORDSET_INSERT, &stuParam, SDK_API_WAITTIME);
			}
			else 
			{
				bRet = CLIENT_ControlDevice(m_lLoginID, DH_CTRL_RECORDSET_INSERTEX, &stuParam, SDK_API_WAITTIME);
			}
			
			if (bRet)
			{
				CString csInfo;
				csInfo.Format("%s:%d", ConvertString("Insert card ok with RecNo", DLG_RECORDSET_CONTROL), stuParam.stuCtrlRecordSetResult.nRecNo);
				MessageBox(csInfo, ConvertString("Prompt"));
			}
			else
			{
				CString csInfo;
				csInfo.Format("%s:0x%08x", ConvertString("Insert card failed", DLG_RECORDSET_CONTROL), CLIENT_GetLastError());
				MessageBox(csInfo, ConvertString("Prompt"));
			}
		}
	}
}

void CDlgRecordSetControl::CardGet()
{
	CSubDlgInfoCard dlg(this, NULL, m_nAccessGroup);
	dlg.SetOperateType(Em_Operate_Type_Get);
	if (IDOK == dlg.DoModal())
	{
		// get info by RecNo
		const NET_RECORDSET_ACCESS_CTL_CARD& stuInfo = dlg.GetInfo();

		NET_CTRL_RECORDSET_PARAM stuParam = {sizeof(stuParam)};
		stuParam.emType = NET_RECORD_ACCESSCTLCARD;

		NET_RECORDSET_ACCESS_CTL_CARD stuCard = {sizeof(stuCard)};
		stuCard.nRecNo = stuInfo.nRecNo;
		stuParam.pBuf = &stuCard;
		
		int nRet = 0;
		BOOL bRet = CLIENT_QueryDevState(m_lLoginID, DH_DEVSTATE_DEV_RECORDSET, (char*)&stuParam, 
			sizeof(stuParam), &nRet, SDK_API_WAITTIME);
		if (bRet)
		{
			dlg.SetInfo(&stuCard);
			dlg.SetOperateType(Em_Operate_Type_Show);
			dlg.DoModal();
		} 
		else
		{
			CString csInfo;
			csInfo.Format("%s:0x%08x", ConvertString("Get card failed", DLG_RECORDSET_CONTROL), CLIENT_GetLastError());
			MessageBox(csInfo, ConvertString("Prompt"));
		}
	}
}

void CDlgRecordSetControl::CardUpdate()
{
	CSubDlgInfoCard dlg(this, NULL, m_nAccessGroup);
	dlg.SetOperateType(Em_Operate_Type_Get);
	if (IDOK == dlg.DoModal())
	{
		if (!dlg.IsDirty())
		{
			// get full info by RecNo before update it
			NET_RECORDSET_ACCESS_CTL_CARD stuInfo = dlg.GetInfo();
			
			NET_CTRL_RECORDSET_PARAM stuParam = {sizeof(stuParam)};
			stuParam.emType = NET_RECORD_ACCESSCTLCARD;
			stuParam.pBuf = (void*)&stuInfo;
			stuParam.nBufLen = sizeof(stuInfo);
			
			int nRet = 0;
			BOOL bRet = CLIENT_QueryDevState(m_lLoginID, DH_DEVSTATE_DEV_RECORDSET, (char*)&stuParam,
				sizeof(stuParam), &nRet, SDK_API_WAITTIME);
			if (bRet)
			{
				dlg.SetInfo(&stuInfo);
				dlg.SetOperateType(m_emOpType);
				if (IDOK == dlg.DoModal())
				{
					stuInfo = dlg.GetInfo();
					
					stuParam.emType = NET_RECORD_ACCESSCTLCARD;
					stuParam.pBuf = (void*)&stuInfo;
					stuParam.nBufLen = sizeof(stuInfo);
					
					// update info
					BOOL bRet = FALSE;
					if (m_emOpType == Em_Operate_Type_Update)
					{
						bRet = CLIENT_ControlDevice(m_lLoginID, DH_CTRL_RECORDSET_UPDATE, &stuParam, SDK_API_WAITTIME);
					}
					else
					{
						bRet = CLIENT_ControlDevice(m_lLoginID, DH_CTRL_RECORDSET_UPDATEEX, &stuParam, SDK_API_WAITTIME);
					}
					
					if (bRet)
					{
						MessageBox(ConvertString("Update card ok", DLG_RECORDSET_CONTROL), ConvertString("Prompt"));
					} 
					else
					{
						CString csInfo;
						csInfo.Format("%s:0x%08x", ConvertString("Update card failed", DLG_RECORDSET_CONTROL), CLIENT_GetLastError());
						MessageBox(csInfo, ConvertString("Prompt"));
					}
				}
			} 
			else
			{
				CString csInfo;
				csInfo.Format("%s:0x%08x", ConvertString("Get card failed", DLG_RECORDSET_CONTROL), CLIENT_GetLastError());
				MessageBox(csInfo, ConvertString("Prompt"));
			}
		}
	}
}

void CDlgRecordSetControl::CardRemove()
{
	CSubDlgInfoCard dlg(this, NULL, m_nAccessGroup);
	dlg.SetOperateType(Em_Operate_Type_Remove);
	if (IDOK == dlg.DoModal())
	{
		const NET_RECORDSET_ACCESS_CTL_CARD& stuInfo = dlg.GetInfo();
		
		NET_CTRL_RECORDSET_PARAM stuParam = {sizeof(stuParam)};
		stuParam.emType = NET_RECORD_ACCESSCTLCARD;
		stuParam.pBuf = (void*)&stuInfo.nRecNo;
		stuParam.nBufLen = sizeof(stuInfo.nRecNo);

		BOOL bRet = CLIENT_ControlDevice(m_lLoginID, DH_CTRL_RECORDSET_REMOVE, &stuParam, SDK_API_WAITTIME);
		if (bRet)
		{
			MessageBox(ConvertString("Remove card ok", DLG_RECORDSET_CONTROL), ConvertString("Prompt"));
		} 
		else
		{
			CString csInfo;
			csInfo.Format("%s:0x%08x", ConvertString("Remove card failed", DLG_RECORDSET_CONTROL), CLIENT_GetLastError());
			MessageBox(csInfo, ConvertString("Prompt"));
		}
	}
}

void CDlgRecordSetControl::CardClear()
{	
	NET_CTRL_RECORDSET_PARAM stuParam = {sizeof(stuParam)};
	stuParam.emType = NET_RECORD_ACCESSCTLCARD;
    BOOL bRet = CLIENT_ControlDevice(m_lLoginID, DH_CTRL_RECORDSET_CLEAR, &stuParam, SDK_API_WAITTIME);
	if (bRet)
	{
		MessageBox(ConvertString("Clear card ok", DLG_RECORDSET_CONTROL), ConvertString("Prompt"));
	} 
	else
	{
		CString csInfo;
		csInfo.Format("%s:0x%08x", ConvertString("Clear card failed", DLG_RECORDSET_CONTROL), CLIENT_GetLastError());
		MessageBox(csInfo, ConvertString("Prompt"));
	}
}
//////////////////////////////////////////////////////////////////////////
// password
//////////////////////////////////////////////////////////////////////////
void CDlgRecordSetControl::PwdInsert()
{
	CDlgSubDlgInfoPassword dlg(this, NULL, m_nAccessGroup);
	dlg.SetOperateType(Em_Operate_Type_Insert);
	if (IDOK == dlg.DoModal())
	{
		const NET_RECORDSET_ACCESS_CTL_PWD& stuInfo = dlg.GetInfo();
		
		NET_CTRL_RECORDSET_INSERT_PARAM stuParam = {sizeof(stuParam)};
		stuParam.stuCtrlRecordSetInfo.dwSize = sizeof(NET_CTRL_RECORDSET_INSERT_IN);
		stuParam.stuCtrlRecordSetInfo.emType = NET_RECORD_ACCESSCTLPWD;
		stuParam.stuCtrlRecordSetInfo.pBuf = (void*)&stuInfo;
		stuParam.stuCtrlRecordSetInfo.nBufLen = sizeof(stuInfo);
		
		stuParam.stuCtrlRecordSetResult.dwSize = sizeof(NET_CTRL_RECORDSET_INSERT_OUT);
		
		BOOL bRet = CLIENT_ControlDevice(m_lLoginID, DH_CTRL_RECORDSET_INSERT, &stuParam, SDK_API_WAITTIME);
		if (bRet)
		{
			CString csInfo;
			csInfo.Format("%s:%d", ConvertString("Insert pwd ok with RecNo", DLG_RECORDSET_CONTROL), stuParam.stuCtrlRecordSetResult.nRecNo);
			MessageBox(csInfo, ConvertString("Prompt"));
		}
		else
		{
			CString csInfo;
			csInfo.Format("%s:0x%08x", ConvertString("Insert pwd failed", DLG_RECORDSET_CONTROL), CLIENT_GetLastError());
			MessageBox(csInfo, ConvertString("Prompt"));
		}
	}
}

void CDlgRecordSetControl::PwdGet()
{
	CDlgSubDlgInfoPassword dlg(this, NULL, m_nAccessGroup);
	dlg.SetOperateType(Em_Operate_Type_Get);
	if (IDOK == dlg.DoModal())
	{
		// get info by RecNo
		const NET_RECORDSET_ACCESS_CTL_PWD& stuInfo = dlg.GetInfo();
		
		NET_CTRL_RECORDSET_PARAM stuParam = {sizeof(stuParam)};
		stuParam.emType = NET_RECORD_ACCESSCTLPWD;
		
		NET_RECORDSET_ACCESS_CTL_PWD stuPwd = {sizeof(stuPwd)};
		stuPwd.nRecNo = stuInfo.nRecNo;
		stuParam.pBuf = &stuPwd;
		
		int nRet = 0;
		BOOL bRet = CLIENT_QueryDevState(m_lLoginID, DH_DEVSTATE_DEV_RECORDSET, (char*)&stuParam, 
			sizeof(stuParam), &nRet, SDK_API_WAITTIME);
		if (bRet)
		{
			dlg.SetInfo(&stuPwd);
			dlg.SetOperateType(Em_Operate_Type_Show);
			dlg.DoModal();
		} 
		else
		{
			CString csInfo;
			csInfo.Format("%s:0x%08x", ConvertString("Get pwd failed", DLG_RECORDSET_CONTROL), CLIENT_GetLastError());
			MessageBox(csInfo, ConvertString("Prompt"));
		}
	}
}

void CDlgRecordSetControl::PwdUpdate()
{
	CDlgSubDlgInfoPassword dlg(this, NULL, m_nAccessGroup);
	dlg.SetOperateType(Em_Operate_Type_Get);
	if (IDOK == dlg.DoModal())
	{
		// get full info by RecNo before update it
		NET_RECORDSET_ACCESS_CTL_PWD stuInfo = dlg.GetInfo();
		
		NET_CTRL_RECORDSET_PARAM stuParam = {sizeof(stuParam)};
		stuParam.emType = NET_RECORD_ACCESSCTLPWD;
		stuParam.pBuf = (void*)&stuInfo;
		stuParam.nBufLen = sizeof(stuInfo);
		
		int nRet = 0;
		BOOL bRet = CLIENT_QueryDevState(m_lLoginID, DH_DEVSTATE_DEV_RECORDSET, (char*)&stuParam,
			sizeof(stuParam), &nRet, SDK_API_WAITTIME);
		if (bRet)
		{
			dlg.SetInfo(&stuInfo);
			dlg.SetOperateType(Em_Operate_Type_Update);
			if (IDOK == dlg.DoModal())
			{
				stuInfo = dlg.GetInfo();
				
				stuParam.emType = NET_RECORD_ACCESSCTLPWD;
				stuParam.pBuf = (void*)&stuInfo;
				stuParam.nBufLen = sizeof(stuInfo);
				
				// update info
				BOOL bRet = CLIENT_ControlDevice(m_lLoginID, DH_CTRL_RECORDSET_UPDATE, &stuParam, SDK_API_WAITTIME);
				if (bRet)
				{
					MessageBox(ConvertString("Update pwd ok", DLG_RECORDSET_CONTROL), ConvertString("Prompt"));
				} 
				else
				{
					CString csInfo;
					csInfo.Format("%s:0x%08x", ConvertString("Update pwd failed", DLG_RECORDSET_CONTROL), CLIENT_GetLastError());
					MessageBox(csInfo, ConvertString("Prompt"));
				}
			}
		} 
		else
		{
			CString csInfo;
			csInfo.Format("%s:0x%08x", ConvertString("Get pwd failed", DLG_RECORDSET_CONTROL), CLIENT_GetLastError());
			MessageBox(csInfo, ConvertString("Prompt"));
		}
	}
}

void CDlgRecordSetControl::PwdRemove()
{
	CDlgSubDlgInfoPassword dlg(this, NULL, m_nAccessGroup);
	dlg.SetOperateType(Em_Operate_Type_Remove);
	if (IDOK == dlg.DoModal())
	{
		const NET_RECORDSET_ACCESS_CTL_PWD& stuInfo = dlg.GetInfo();
		
		NET_CTRL_RECORDSET_PARAM stuParam = {sizeof(stuParam)};
		stuParam.emType = NET_RECORD_ACCESSCTLPWD;
		stuParam.pBuf = (void*)&stuInfo.nRecNo;
		stuParam.nBufLen = sizeof(stuInfo.nRecNo);
		
		BOOL bRet = CLIENT_ControlDevice(m_lLoginID, DH_CTRL_RECORDSET_REMOVE, &stuParam, SDK_API_WAITTIME);
		if (bRet)
		{
			MessageBox(ConvertString("Remove pwd ok", DLG_RECORDSET_CONTROL), ConvertString("Prompt"));
		} 
		else
		{
			CString csInfo;
			csInfo.Format("%s:0x%08x", ConvertString("Remove pwd failed", DLG_RECORDSET_CONTROL), CLIENT_GetLastError());
			MessageBox(csInfo, ConvertString("Prompt"));
		}
	}
}

void CDlgRecordSetControl::PwdClear()
{
	NET_CTRL_RECORDSET_PARAM stuParam = {sizeof(stuParam)};
	stuParam.emType = NET_RECORD_ACCESSCTLPWD;
    BOOL bRet = CLIENT_ControlDevice(m_lLoginID, DH_CTRL_RECORDSET_CLEAR, &stuParam, SDK_API_WAITTIME);
	if (bRet)
	{
		MessageBox(ConvertString("Clear pwd ok", DLG_RECORDSET_CONTROL), ConvertString("Prompt"));
	} 
	else
	{
		CString csInfo;
		csInfo.Format("%s:0x%08x", ConvertString("Clear pwd failed", DLG_RECORDSET_CONTROL), CLIENT_GetLastError());
		MessageBox(csInfo, ConvertString("Prompt"));
	}
}
//////////////////////////////////////////////////////////////////////////
// access
//////////////////////////////////////////////////////////////////////////
void CDlgRecordSetControl::AccessInsert()
{
	MessageBox(ConvertString("Not supported by device", DLG_RECORDSET_CONTROL),	ConvertString("Prompt"));
}

void CDlgRecordSetControl::AccessGet()
{
	MessageBox(ConvertString("Not supported by device", DLG_RECORDSET_CONTROL),	ConvertString("Prompt"));
}

void CDlgRecordSetControl::AccessUpdate()
{	
	MessageBox(ConvertString("Not supported by device", DLG_RECORDSET_CONTROL),	ConvertString("Prompt"));
}

void CDlgRecordSetControl::AccessRemove()
{
	MessageBox(ConvertString("Not supported by device", DLG_RECORDSET_CONTROL),	ConvertString("Prompt"));
}

void CDlgRecordSetControl::AccessClear()
{
	MessageBox(ConvertString("Not supported by device", DLG_RECORDSET_CONTROL),	ConvertString("Prompt"));
}
//////////////////////////////////////////////////////////////////////////
// holiday
//////////////////////////////////////////////////////////////////////////
void CDlgRecordSetControl::HolidayInsert()
{
	CDlgSubDlgInfoHoliday dlg(this, NULL, m_nAccessGroup);
	dlg.SetOperateType(Em_Operate_Type_Insert);
	if (IDOK == dlg.DoModal())
	{
		const NET_RECORDSET_HOLIDAY& stuInfo = dlg.GetInfo();
		
		NET_CTRL_RECORDSET_INSERT_PARAM stuParam = {sizeof(stuParam)};
		stuParam.stuCtrlRecordSetInfo.dwSize = sizeof(NET_CTRL_RECORDSET_INSERT_IN);
		stuParam.stuCtrlRecordSetInfo.emType = NET_RECORD_ACCESSCTLHOLIDAY;
		stuParam.stuCtrlRecordSetInfo.pBuf = (void*)&stuInfo;
		stuParam.stuCtrlRecordSetInfo.nBufLen = sizeof(stuInfo);
		
		stuParam.stuCtrlRecordSetResult.dwSize = sizeof(NET_CTRL_RECORDSET_INSERT_OUT);
		
		BOOL bRet = CLIENT_ControlDevice(m_lLoginID, DH_CTRL_RECORDSET_INSERT, &stuParam, SDK_API_WAITTIME);
		if (bRet)
		{
			CString csInfo;
			csInfo.Format("%s:%d", ConvertString("Insert holiday ok with RecNo", DLG_RECORDSET_CONTROL), stuParam.stuCtrlRecordSetResult.nRecNo);
			MessageBox(csInfo, ConvertString("Prompt"));
		}
		else
		{
			CString csInfo;
			csInfo.Format("%s:0x%08x", ConvertString("Insert holiday failed", DLG_RECORDSET_CONTROL), CLIENT_GetLastError());
			MessageBox(csInfo, ConvertString("Prompt"));
		}
	}
}

void CDlgRecordSetControl::HolidayGet()
{
	CDlgSubDlgInfoHoliday dlg(this, NULL, m_nAccessGroup);
	dlg.SetOperateType(Em_Operate_Type_Get);
	if (IDOK == dlg.DoModal())
	{
		// get info by RecNo
		const NET_RECORDSET_HOLIDAY& stuInfo = dlg.GetInfo();
		
		NET_CTRL_RECORDSET_PARAM stuParam = {sizeof(stuParam)};
		stuParam.emType = NET_RECORD_ACCESSCTLHOLIDAY;
		
		NET_RECORDSET_HOLIDAY stuHoliday = {sizeof(stuHoliday)};
		stuHoliday.nRecNo = stuInfo.nRecNo;
		stuParam.pBuf = &stuHoliday;
		
		int nRet = 0;
		BOOL bRet = CLIENT_QueryDevState(m_lLoginID, DH_DEVSTATE_DEV_RECORDSET, (char*)&stuParam, 
			sizeof(stuParam), &nRet, SDK_API_WAITTIME);
		if (bRet)
		{
			dlg.SetInfo(&stuHoliday);
			dlg.SetOperateType(Em_Operate_Type_Show);
			dlg.DoModal();
		} 
		else
		{
			CString csInfo;
			csInfo.Format("%s:0x%08x", ConvertString("Get holiday failed", DLG_RECORDSET_CONTROL), CLIENT_GetLastError());
			MessageBox(csInfo, ConvertString("Prompt"));
		}
	}
}

void CDlgRecordSetControl::HolidayUpdate()
{
	CDlgSubDlgInfoHoliday dlg(this, NULL, m_nAccessGroup);
	dlg.SetOperateType(Em_Operate_Type_Get);
	if (IDOK == dlg.DoModal())
	{
		// get full info by RecNo before update it
		NET_RECORDSET_HOLIDAY stuInfo = dlg.GetInfo();
		
		NET_CTRL_RECORDSET_PARAM stuParam = {sizeof(stuParam)};
		stuParam.emType = NET_RECORD_ACCESSCTLHOLIDAY;
		stuParam.pBuf = (void*)&stuInfo;
		stuParam.nBufLen = sizeof(stuInfo);
		
		int nRet = 0;
		BOOL bRet = CLIENT_QueryDevState(m_lLoginID, DH_DEVSTATE_DEV_RECORDSET, (char*)&stuParam,
			sizeof(stuParam), &nRet, SDK_API_WAITTIME);
		if (bRet)
		{
			dlg.SetInfo(&stuInfo);
			dlg.SetOperateType(Em_Operate_Type_Update);
			if (IDOK == dlg.DoModal())
			{
				stuInfo = dlg.GetInfo();
				
				stuParam.emType = NET_RECORD_ACCESSCTLHOLIDAY;
				stuParam.pBuf = (void*)&stuInfo;
				stuParam.nBufLen = sizeof(stuInfo);
				
				// update info
				BOOL bRet = CLIENT_ControlDevice(m_lLoginID, DH_CTRL_RECORDSET_UPDATE, &stuParam, SDK_API_WAITTIME);
				if (bRet)
				{
					MessageBox(ConvertString("Update holiday ok", DLG_RECORDSET_CONTROL), ConvertString("Prompt"));
				} 
				else
				{
					CString csInfo;
					csInfo.Format("%s:0x%08x", ConvertString("Update holiday failed", DLG_RECORDSET_CONTROL), CLIENT_GetLastError());
					MessageBox(csInfo, ConvertString("Prompt"));
				}
			}
		} 
		else
		{
			CString csInfo;
			csInfo.Format("%s:0x%08x", ConvertString("Get holiday failed", DLG_RECORDSET_CONTROL), CLIENT_GetLastError());
			MessageBox(csInfo, ConvertString("Prompt"));
		}
	}
}

void CDlgRecordSetControl::HolidayRemove()
{
	CDlgSubDlgInfoHoliday dlg(this, NULL, m_nAccessGroup);
	dlg.SetOperateType(Em_Operate_Type_Remove);
	if (IDOK == dlg.DoModal())
	{
		const NET_RECORDSET_HOLIDAY& stuInfo = dlg.GetInfo();
		
		NET_CTRL_RECORDSET_PARAM stuParam = {sizeof(stuParam)};
		stuParam.emType = NET_RECORD_ACCESSCTLHOLIDAY;
		stuParam.pBuf = (void*)&stuInfo.nRecNo;
		stuParam.nBufLen = sizeof(stuInfo.nRecNo);
		
		BOOL bRet = CLIENT_ControlDevice(m_lLoginID, DH_CTRL_RECORDSET_REMOVE, &stuParam, SDK_API_WAITTIME);
		if (bRet)
		{
			MessageBox(ConvertString("Remove holiday rec ok", DLG_RECORDSET_CONTROL), ConvertString("Prompt"));
		} 
		else
		{
			CString csInfo;
			csInfo.Format("%s:0x%08x", ConvertString("Remove holiday rec failed", DLG_RECORDSET_CONTROL), CLIENT_GetLastError());
			MessageBox(csInfo, ConvertString("Prompt"));
		}
	}
}

void CDlgRecordSetControl::HolidayClear()
{
	NET_CTRL_RECORDSET_PARAM stuParam = {sizeof(stuParam)};
	stuParam.emType = NET_RECORD_ACCESSCTLHOLIDAY;
    BOOL bRet = CLIENT_ControlDevice(m_lLoginID, DH_CTRL_RECORDSET_CLEAR, &stuParam, SDK_API_WAITTIME);
	if (bRet)
	{
		MessageBox(ConvertString("Clear holiday ok", DLG_RECORDSET_CONTROL), ConvertString("Prompt"));
	} 
	else
	{
		CString csInfo;
		csInfo.Format("%s:0x%08x", ConvertString("Clear holiday failed", DLG_RECORDSET_CONTROL), CLIENT_GetLastError());
		MessageBox(csInfo, ConvertString("Prompt"));
	}
}
/////////////////////////////////////////////////////////////////////////////
// CDlgRecordSetControl message handlers

BOOL CDlgRecordSetControl::OnInitDialog() 
{
	CDialog::OnInitDialog();
	g_SetWndStaticText(this, DLG_RECORDSET_CONTROL);
	// TODO: Add extra initialization here
	InitDlg();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgRecordSetControl::OnRecordsetCtlBtnExecute() 
{
	// TODO: Add your control notification handler code here
	int nSetType = m_cmbSetType.GetCurSel();
	int nCtlType = m_cmbCtlType.GetCurSel();
	if (-1 == nSetType || -1 == nCtlType)
	{
		return;
	}

	if (Em_RecordSet_Type_Card == nSetType)
	{
		if (Em_Operate_Type_Insert == nCtlType + 1 || Em_Operate_Type_InsertEX == nCtlType + 1)
		{
			m_emOpType = static_cast<Em_RecordSet_Operate_Type>(nCtlType+1);
			CardInsert();
		}
		else if (Em_Operate_Type_Get == nCtlType + 1)
		{
			CardGet();
		}
		else if (Em_Operate_Type_Update == nCtlType + 1 || Em_Operate_Type_UpdateEX == nCtlType + 1)
		{
			m_emOpType = static_cast<Em_RecordSet_Operate_Type>(nCtlType+1);
			CardUpdate();
		}
		else if (Em_Operate_Type_Remove == nCtlType + 1)
		{
			CardRemove();
		}
		else if (Em_Operate_Type_Clear == nCtlType + 1)
		{
			CardClear();
		}
	}
	else if (Em_RecordSet_Type_Pwd == nSetType)
	{
		if (Em_Operate_Type_Insert == nCtlType + 1)
		{
			PwdInsert();
		}
		else if (Em_Operate_Type_Get == nCtlType + 1)
		{
			PwdGet();
		}
		else if (Em_Operate_Type_Update == nCtlType + 1)
		{
			PwdUpdate();
		}
		else if (Em_Operate_Type_Remove == nCtlType + 1)
		{
			PwdRemove();
		}
		else if (Em_Operate_Type_Clear == nCtlType + 1)
		{
			PwdClear();
		}
	}
	else if (Em_RecordSet_Type_Access == nSetType)
	{
		if (Em_Operate_Type_Insert == nCtlType + 1)
		{
			AccessInsert();
		}
		else if (Em_Operate_Type_Get == nCtlType + 1)
		{
			AccessGet();
		}
		else if (Em_Operate_Type_Update == nCtlType + 1)
		{
			AccessUpdate();
		}
		else if (Em_Operate_Type_Remove == nCtlType + 1)
		{
			AccessRemove();
		}
		else if (Em_Operate_Type_Clear == nCtlType + 1)
		{
			AccessClear();
		}
	}
	else if (Em_RecordSet_Type_Holiday == nSetType)
	{
		if (Em_Operate_Type_Insert == nCtlType + 1)
		{
			HolidayInsert();
		}
		else if (Em_Operate_Type_Get == nCtlType + 1)
		{
			HolidayGet();
		}
		else if (Em_Operate_Type_Update == nCtlType + 1)
		{
			HolidayUpdate();
		}
		else if (Em_Operate_Type_Remove == nCtlType + 1)
		{
			HolidayRemove();
		}
		else if (Em_Operate_Type_Clear == nCtlType + 1)
		{
			HolidayClear();
		}
	}
}
