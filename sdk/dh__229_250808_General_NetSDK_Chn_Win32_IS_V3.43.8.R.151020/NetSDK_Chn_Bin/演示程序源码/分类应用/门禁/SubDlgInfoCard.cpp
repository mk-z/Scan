// SubDlgInfoCard.cpp : implementation file
//

#include "stdafx.h"
#include "accesscontrol.h"
#include "SubDlgInfoCard.h"
#include "SubDlgSensorInfoDescription.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSubDlgInfoCard dialog

#define MAX_FINGER_PRINT_PACKET_SIZE	(10*256)
CSubDlgInfoCard::CSubDlgInfoCard(CWnd* pParent /* = NULL */, NET_RECORDSET_ACCESS_CTL_CARD* p /* = NULL */, int nAccessGroup /* = 1 */)
	: CDialog(CSubDlgInfoCard::IDD, pParent)/*, m_fingerPrintPacket(MAX_FINGER_PRINT_PACKET_SIZE)*/
{
	//{{AFX_DATA_INIT(CSubDlgInfoCard)
	m_strTestFingerPacketData = _T("");
	//}}AFX_DATA_INIT
	memset(&m_stuInfo, 0, sizeof(m_stuInfo));
	if (p != NULL)
	{
		memcpy(&m_stuInfo, p, sizeof(NET_RECORDSET_ACCESS_CTL_CARD));
	}
	m_stuInfo.dwSize = sizeof(m_stuInfo);
	m_stuInfo.stuFingerPrintInfo.dwSize = sizeof(m_stuInfo.stuFingerPrintInfo);

	m_emOperateType = Em_Operate_Type_Show;
    m_nAccessGroup  = nAccessGroup;
	m_bDirty = false;
}


void CSubDlgInfoCard::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSubDlgInfoCard)
	DDX_Control(pDX, IDC_RECSET_CARD_CHK_FIRSTENTER, m_chkFirstEnter);
	DDX_Control(pDX, IDC_RECSET_CARD_CMB_CARDTYPE, m_cmbCardType);
	DDX_Control(pDX, IDC_RECSET_CARD_CMB_CARDSTATUS, m_cmbCardStatus);
	DDX_Control(pDX, IDC_RECSET_CARD_DTP_VDSTART, m_dtpVDStart);
	DDX_Control(pDX, IDC_RECSET_CARD_DTP_VDEND, m_dtpVDEnd);
	DDX_Control(pDX, IDC_RECSET_CARD_DTP_CT_TIME, m_dtpCreateTimeTime);
	DDX_Control(pDX, IDC_RECSET_CARD_DTP_CT_DATE, m_dtpCreateTimeDate);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSubDlgInfoCard, CDialog)
	//{{AFX_MSG_MAP(CSubDlgInfoCard)
	ON_BN_CLICKED(IDC_RECSET_CARD_BTN_DOORS, OnRecsetCardBtnDoors)
	ON_BN_CLICKED(IDC_RECSET_CARD_BTN_TM, OnRecsetCardBtnTm)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CSubDlgInfoCard::InitDlg()
{
	int i = 0;

	// Card Status
	for (i = 0; i < sizeof(stuDemoCardStatus)/sizeof(stuDemoCardStatus[0]); i++)
	{
		m_cmbCardStatus.InsertString(-1, ConvertString(stuDemoCardStatus[i].szName, SUBDLG_INFO_CARD));
	}

	// Card Type
	for (i = 0; i < sizeof(stuDemoCardType)/sizeof(stuDemoCardType[0]); i++)
	{
		m_cmbCardType.InsertString(-1, ConvertString(stuDemoCardType[i].szName, SUBDLG_INFO_CARD));
	}

	// disable Finger Print edit box for default
	if (Em_Operate_Type_Show == m_emOperateType)
	{
		GetDlgItem(IDC_RECSET_CARD_EDT_RECNO)->EnableWindow(FALSE);
		StuToDlg();
	}
	else if (Em_Operate_Type_Insert == m_emOperateType || Em_Operate_Type_InsertEX == m_emOperateType)
	{
		GetDlgItem(IDC_RECSET_CARD_EDT_RECNO)->EnableWindow(FALSE);
	}
	else if (Em_Operate_Type_Get == m_emOperateType)
	{
		GetDlgItem(IDC_RECSET_CARD_EDT_RECNO)->EnableWindow();
		m_dtpCreateTimeDate.EnableWindow(FALSE);
		m_dtpCreateTimeTime.EnableWindow(FALSE);
		GetDlgItem(IDC_RECSET_CARD_EDT_CARDNO)->EnableWindow(FALSE);
		GetDlgItem(IDC_RECSET_CARD_EDT_USERID)->EnableWindow(FALSE);
		m_cmbCardStatus.EnableWindow(FALSE);
		m_cmbCardType.EnableWindow(FALSE);
		GetDlgItem(IDC_RECSET_CARD_EDT_PWD)->EnableWindow(FALSE);
		GetDlgItem(IDC_RECSET_CARD_EDT_USETIME)->EnableWindow(FALSE);
		m_dtpVDStart.EnableWindow(FALSE);
		m_dtpVDEnd.EnableWindow(FALSE);
        m_chkFirstEnter.EnableWindow(FALSE);
	}
	else if (Em_Operate_Type_Update == m_emOperateType || Em_Operate_Type_UpdateEX == m_emOperateType)
	{
		StuToDlg();
 		GetDlgItem(IDC_RECSET_CARD_EDT_RECNO)->EnableWindow(FALSE);
	}
	else if (Em_Operate_Type_Remove == m_emOperateType)
	{
		StuToDlg();
		GetDlgItem(IDC_RECSET_CARD_EDT_RECNO)->EnableWindow();
		m_dtpCreateTimeDate.EnableWindow(FALSE);
		m_dtpCreateTimeTime.EnableWindow(FALSE);
		GetDlgItem(IDC_RECSET_CARD_EDT_CARDNO)->EnableWindow(FALSE);
		GetDlgItem(IDC_RECSET_CARD_EDT_USERID)->EnableWindow(FALSE);
		m_cmbCardStatus.EnableWindow(FALSE);
		m_cmbCardType.EnableWindow(FALSE);
		GetDlgItem(IDC_RECSET_CARD_EDT_PWD)->EnableWindow(FALSE);
		GetDlgItem(IDC_RECSET_CARD_EDT_USETIME)->EnableWindow(FALSE);
		m_dtpVDStart.EnableWindow(FALSE);
        m_dtpVDEnd.EnableWindow(FALSE);
        m_chkFirstEnter.EnableWindow(FALSE);
	}
	else if (Em_Operate_Type_Clear == m_emOperateType)
	{
		// ...
	}
}

void CSubDlgInfoCard::StuToDlg()
{
	// RecNo
	SetDlgItemInt(IDC_RECSET_CARD_EDT_RECNO, m_stuInfo.nRecNo);

	// create time
	SYSTEMTIME st = {0};
	st.wYear	= (WORD)m_stuInfo.stuCreateTime.dwYear;
	st.wMonth	= (WORD)m_stuInfo.stuCreateTime.dwMonth;
	st.wDay		= (WORD)m_stuInfo.stuCreateTime.dwDay;
	m_dtpCreateTimeDate.SetTime(&st);
	st.wHour	= (WORD)m_stuInfo.stuCreateTime.dwHour;
	st.wMinute	= (WORD)m_stuInfo.stuCreateTime.dwMinute;
	st.wSecond	= (WORD)m_stuInfo.stuCreateTime.dwSecond;
	m_dtpCreateTimeTime.SetTime(&st);
	
	// card no
	SetDlgItemText(IDC_RECSET_CARD_EDT_CARDNO, m_stuInfo.szCardNo);

	// user id
	SetDlgItemText(IDC_RECSET_CARD_EDT_USERID, m_stuInfo.szUserID);

	// card status
	m_cmbCardStatus.SetCurSel(CardStatusToInt(m_stuInfo.emStatus));

	// card type
	m_cmbCardType.SetCurSel(CardTypeToInt(m_stuInfo.emType));

	// password
	SetDlgItemText(IDC_RECSET_CARD_EDT_PWD, m_stuInfo.szPsw);

	// use time
	SetDlgItemInt(IDC_RECSET_CARD_EDT_USETIME, m_stuInfo.nUserTime, TRUE);

	// valid time start
	st.wYear	= (WORD)m_stuInfo.stuValidStartTime.dwYear;
	st.wMonth	= (WORD)m_stuInfo.stuValidStartTime.dwMonth;
	st.wDay		= (WORD)m_stuInfo.stuValidStartTime.dwDay;
	m_dtpVDStart.SetTime(&st);

	// valid time end
	st.wYear	= (WORD)m_stuInfo.stuValidEndTime.dwYear;
	st.wMonth	= (WORD)m_stuInfo.stuValidEndTime.dwMonth;
	st.wDay		= (WORD)m_stuInfo.stuValidEndTime.dwDay;
	m_dtpVDEnd.SetTime(&st);

    // first enter
    if (m_stuInfo.bFirstEnter)
    {
        m_chkFirstEnter.SetCheck(BST_CHECKED);
    }
    else
    {
        m_chkFirstEnter.SetCheck(BST_UNCHECKED);
    }
}

void CSubDlgInfoCard::DlgToStu()
{
	// RecNo
	m_stuInfo.nRecNo = GetDlgItemInt(IDC_RECSET_CARD_EDT_RECNO);
	
	// create time
	SYSTEMTIME st = {0};
	m_dtpCreateTimeDate.GetTime(&st);
	m_stuInfo.stuCreateTime.dwYear	= st.wYear;
	m_stuInfo.stuCreateTime.dwMonth = st.wMonth;
	m_stuInfo.stuCreateTime.dwDay	= st.wDay;
	m_dtpCreateTimeTime.GetTime(&st);
	m_stuInfo.stuCreateTime.dwHour	= st.wHour;
	m_stuInfo.stuCreateTime.dwMinute = st.wMinute;
	m_stuInfo.stuCreateTime.dwSecond = st.wSecond;
	
	// card no
	GetDlgItemText(IDC_RECSET_CARD_EDT_CARDNO, m_stuInfo.szCardNo, sizeof(m_stuInfo.szCardNo) - 1);
	
	// user id
	GetDlgItemText(IDC_RECSET_CARD_EDT_USERID, m_stuInfo.szUserID, sizeof(m_stuInfo.szUserID) - 1);
	
	// card status
	m_stuInfo.emStatus = IntToCardStatus(m_cmbCardStatus.GetCurSel());
	
	// card type
	m_stuInfo.emType = IntToCardType(m_cmbCardType.GetCurSel());
	
	// password
	GetDlgItemText(IDC_RECSET_CARD_EDT_PWD, m_stuInfo.szPsw, sizeof(m_stuInfo.szPsw) - 1);
	
	// use time
	m_stuInfo.nUserTime = GetDlgItemInt(IDC_RECSET_CARD_EDT_USETIME, NULL, TRUE);
	
	// valid time start
	m_dtpVDStart.GetTime(&st);
	m_stuInfo.stuValidStartTime.dwYear = st.wYear;
	m_stuInfo.stuValidStartTime.dwMonth = st.wMonth;
	m_stuInfo.stuValidStartTime.dwDay = st.wDay;
	
	// valid time end
	m_dtpVDEnd.GetTime(&st);
	m_stuInfo.stuValidEndTime.dwYear = st.wYear;
	m_stuInfo.stuValidEndTime.dwMonth = st.wMonth;
	m_stuInfo.stuValidEndTime.dwDay = st.wDay;

	// test finger print packets(single) ²âÊÔÖ¸ÎÆÊý¾Ý£¬ÔÝÊ±²»É¾³ý
// 	if (m_emOperateType == Em_Operate_Type_UpdateEX || m_emOperateType == Em_Operate_Type_InsertEX)
// 	{
//  		if (m_stuInfo.stuFingerPrintInfo.nLength != 256) // 256:Ò»ÌõÖ¸ÎÆÊý¾Ý°üµÄ¹Ì¶¨´óÐ¡
//  		{
//  			m_bDirty = true;
//  			MessageBox(ConvertString("Finger Packets Length Wrong", SUBDLG_INFO_CARD));
//  			return;
//  		}
// 		
// 		// ÉèÖÃ²âÊÔÖ¸ÎÆÊý¾Ý°ü
// 		static const char pTestFingerPrint[] = {0x46, 0x50, 0x4D, 0x0D, 0x88, 0x0D, 0x25, 0xC8, 0x58, 0x58, 0x94, 0x65, 0x26, 0xD5, 0x88, 0x68, 0x93, 0xA9, 0x26, 0x56,
// 												0xA8,0x80 ,0x9A ,0xE9 ,0x25 ,0x4B ,0x58 ,0x58 ,0xA4 ,0x81 ,0x26 ,0x48 ,0x88 ,0x68 ,0xAC ,0xC1 ,0x15 ,0xC6 ,0x68 ,0x50 ,
// 												0xB6 ,0x21 ,0x17 ,0x40 ,0xA8 ,0x92 ,0xBC ,0x51 ,0x17 ,0x1B ,0xA8 ,0x8A ,0xC4 ,0x31 ,0x17 ,0x25 ,0xE8 ,0x79 ,0xCB ,0x9D ,
// 												0x17 ,0x91 ,0x88 ,0xA0 ,0xD1 ,0x09 ,0x17 ,0x23 ,0xB8 ,0x78 ,0xDD ,0xD1 ,0x15 ,0x38 ,0x48 ,0x80 ,0xFA ,0x3D ,0x17 ,0x16 ,
// 												0xA8 ,0xB8 ,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
// 												0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
// 												0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
// 												0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
// 												0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
// 												0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
// 												0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
// 												0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
// 												0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
// 												0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
// 												0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
// 												0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
// 												0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
// 												0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
// 												0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
// 												0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
// 												0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
// 		};
// 		
// 		m_fingerPrintPacket.Clear();
// 		for (int i=0; i<m_stuInfo.stuFingerPrintInfo.nCount; i++)
// 		{
// 			if (!m_fingerPrintPacket.AppendBuffer((char*)pTestFingerPrint, 256))
// 			{
// 				m_bDirty = true;
// 				MessageBox(ConvertString("Finger Packets Length Wrong", SUBDLG_INFO_CARD));
//  				return;
// 			}
// 		}
// 		m_stuInfo.stuFingerPrintInfo.pPacketData = (char*)m_fingerPrintPacket.GetBuffer();
// 	}

    // first enter
    if (m_chkFirstEnter.GetCheck())
    {
        m_stuInfo.bFirstEnter = TRUE;
    }
    else
    {
        m_stuInfo.bFirstEnter = FALSE;
    }
}

BOOL CSubDlgInfoCard::Get()
{
	m_stuInfo.nRecNo = GetDlgItemInt(IDC_RECSET_CARD_EDT_RECNO, NULL, TRUE);
	return TRUE;
}

BOOL CSubDlgInfoCard::Update()
{
	return TRUE;
}

BOOL CSubDlgInfoCard::Remove()
{
	return TRUE;
}

void CSubDlgInfoCard::Clear()
{

}

int CSubDlgInfoCard::CardStatusToInt(NET_ACCESSCTLCARD_STATE emStatus)
{
	int n = -1;
	if (NET_ACCESSCTLCARD_STATE_UNKNOWN == emStatus)
	{
		n = 0;
	}
	else if (NET_ACCESSCTLCARD_STATE_NORMAL == emStatus)
	{
		n = 1;
	}
	else if (NET_ACCESSCTLCARD_STATE_LOSE == emStatus)
	{
		n = 2;
	}
	else if (NET_ACCESSCTLCARD_STATE_LOGOFF == emStatus)
	{
		n = 3;
	}
	else if (NET_ACCESSCTLCARD_STATE_FREEZE == emStatus)
	{
		n = 4;
	}
	return n;
}

NET_ACCESSCTLCARD_STATE CSubDlgInfoCard::IntToCardStatus(int n)
{
	NET_ACCESSCTLCARD_STATE emStatua = NET_ACCESSCTLCARD_STATE_UNKNOWN;
	if (0 == n)
	{
	}
	else if (1 == n)
	{
		emStatua = NET_ACCESSCTLCARD_STATE_NORMAL;
	}
	else if (2 == n)
	{
		emStatua = NET_ACCESSCTLCARD_STATE_LOSE;
	}
	else if (3 == n)
	{
		emStatua = NET_ACCESSCTLCARD_STATE_LOGOFF;
	}
	else if (4 == n)
	{
		emStatua = NET_ACCESSCTLCARD_STATE_FREEZE;
	}
	return emStatua;
}

int CSubDlgInfoCard::CardTypeToInt(NET_ACCESSCTLCARD_TYPE emType)
{
	int n = -1;
	if (NET_ACCESSCTLCARD_TYPE_UNKNOWN == emType)
	{
		n = 0;
	}
	else if (NET_ACCESSCTLCARD_TYPE_GENERAL == emType)
	{
		n = 1;
	}
	else if (NET_ACCESSCTLCARD_TYPE_VIP == emType)
	{
		n = 2;
	}
	else if (NET_ACCESSCTLCARD_TYPE_GUEST == emType)
	{
		n = 3;
	}
	else if (NET_ACCESSCTLCARD_TYPE_PATROL == emType)
	{
		n = 4;
	}
	else if (NET_ACCESSCTLCARD_TYPE_BLACKLIST == emType)
	{
		n = 5;
	}
	else if (NET_ACCESSCTLCARD_TYPE_CORCE == emType)
	{
		n = 6;
	}
	else if (NET_ACCESSCTLCARD_TYPE_MOTHERCARD == emType)
	{
		n = 7;
	}
	return n;
}

NET_ACCESSCTLCARD_TYPE CSubDlgInfoCard::IntToCardType(int n)
{
	NET_ACCESSCTLCARD_TYPE emType = NET_ACCESSCTLCARD_TYPE_UNKNOWN;
	if (0 == n)
	{
	}
	else if (1 == n)
	{
		emType = NET_ACCESSCTLCARD_TYPE_GENERAL;
	}
	else if (2 == n)
	{
		emType = NET_ACCESSCTLCARD_TYPE_VIP;
	}
	else if (3 == n)
	{
		emType = NET_ACCESSCTLCARD_TYPE_GUEST;
	}
	else if (4 == n)
	{
		emType = NET_ACCESSCTLCARD_TYPE_PATROL;
	}
	else if (5 == n)
	{
		emType = NET_ACCESSCTLCARD_TYPE_BLACKLIST;
	}
	else if (6 == n)
	{
		emType = NET_ACCESSCTLCARD_TYPE_CORCE;
	}
	else if (7 == n)
	{
		emType = NET_ACCESSCTLCARD_TYPE_MOTHERCARD;
	}
	return emType;
}

/////////////////////////////////////////////////////////////////////////////
// CSubDlgInfoCard message handlers

BOOL CSubDlgInfoCard::OnInitDialog() 
{
	CDialog::OnInitDialog();
	g_SetWndStaticText(this, SUBDLG_INFO_CARD);
	// TODO: Add extra initialization here
	InitDlg();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSubDlgInfoCard::OnOK() 
{
	// TODO: Add extra validation here
	switch (m_emOperateType)
	{
	case Em_Operate_Type_Show:
		{
			StuToDlg();
		}
		break;
	case Em_Operate_Type_Insert:
	case Em_Operate_Type_InsertEX:
		{
			DlgToStu();
		}
		break;
	case Em_Operate_Type_Get:
		{
			DlgToStu();
		}
	case Em_Operate_Type_Update:
	case Em_Operate_Type_UpdateEX:
		{
			DlgToStu();
		}
		break;
	case Em_Operate_Type_Remove:
		{
			DlgToStu();
		}
		break;
	case Em_Operate_Type_Clear:
		break;
	default:
		break;
	}
	CDialog::OnOK();
}

void CSubDlgInfoCard::OnRecsetCardBtnDoors() 
{
	// TODO: Add your control notification handler code here	
	std::vector<int> vecChn;
	int i = 0;
	for (; i < m_stuInfo.nDoorNum; i++)
	{
		vecChn.push_back(m_stuInfo.sznDoors[i]);
	}
	
	CSubDlgSensorInfoDescription dlg(this, m_nAccessGroup);
	dlg.SetID(vecChn);
	if (IDOK == dlg.DoModal())
	{
		if (Em_Operate_Type_Insert == m_emOperateType
			|| Em_Operate_Type_Update == m_emOperateType
			|| Em_Operate_Type_InsertEX == m_emOperateType
			|| Em_Operate_Type_UpdateEX == m_emOperateType)
		{
			vecChn.clear();
			vecChn = dlg.GetID();
			std::vector<int>::iterator it = vecChn.begin();
			for (i = 0; i < __min(vecChn.size(), DH_MAX_DOOR_NUM) && it != vecChn.end(); i++, it++)
			{
				m_stuInfo.sznDoors[i] = *it;
			}
			m_stuInfo.nDoorNum = __min(vecChn.size(), DH_MAX_DOOR_NUM);
		}
	}
}

void CSubDlgInfoCard::OnRecsetCardBtnTm() 
{
	// TODO: Add your control notification handler code here	
	std::vector<int> vecChn;
	int i = 0;
	for (; i < m_stuInfo.nTimeSectionNum; i++)
	{
		vecChn.push_back(m_stuInfo.sznTimeSectionNo[i]);
	}
	
	CSubDlgSensorInfoDescription dlg(this, 128);
	dlg.SetID(vecChn);
	if (IDOK == dlg.DoModal())
	{
		if (Em_Operate_Type_Insert == m_emOperateType
			|| Em_Operate_Type_Update == m_emOperateType
			|| Em_Operate_Type_InsertEX == m_emOperateType
			|| Em_Operate_Type_UpdateEX == m_emOperateType)
		{
			vecChn.clear();
			vecChn = dlg.GetID();
			std::vector<int>::iterator it = vecChn.begin();
			for (i = 0; i < __min(vecChn.size(), DH_MAX_TIMESECTION_NUM) && it != vecChn.end(); i++, it++)
			{
				m_stuInfo.sznTimeSectionNo[i] = *it;
			}
			m_stuInfo.nTimeSectionNum = __min(vecChn.size(), DH_MAX_TIMESECTION_NUM);
		}
	}	
}
