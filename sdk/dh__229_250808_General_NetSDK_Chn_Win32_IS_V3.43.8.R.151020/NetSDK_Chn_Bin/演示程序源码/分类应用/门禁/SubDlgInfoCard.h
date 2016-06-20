#if !defined(AFX_SUBDLGINFOCARD_H__2410B577_5B03_4F4D_8F44_54E07099336D__INCLUDED_)
#define AFX_SUBDLGINFOCARD_H__2410B577_5B03_4F4D_8F44_54E07099336D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SubDlgInfoCard.h : header file
//

//////////////////////////////////////////////////////////////////////////
// 注：insertex和updateex与非ex程序相比，多了指纹数据上报。流程一致
//////////////////////////////////////////////////////////////////////////

// card status
typedef struct tagDemoCardStatus 
{
	NET_ACCESSCTLCARD_STATE	emStatus;
	const char*				szName;
}DemoCardStatus;

const DemoCardStatus stuDemoCardStatus[] =
{
	{NET_ACCESSCTLCARD_STATE_UNKNOWN, "Unknown"},
	{NET_ACCESSCTLCARD_STATE_NORMAL, "Normal"},
	{NET_ACCESSCTLCARD_STATE_LOSE, "Lose"},
	{NET_ACCESSCTLCARD_STATE_LOGOFF, "LogOff"},
	{NET_ACCESSCTLCARD_STATE_FREEZE, "Freeze"},
};

// card type
typedef struct tagDemoCardType 
{
	NET_ACCESSCTLCARD_TYPE	emType;
	const char*				szName;
}DemoCardType;

const DemoCardType stuDemoCardType[] = 
{
	{NET_ACCESSCTLCARD_TYPE_UNKNOWN, "Unknown"},
	{NET_ACCESSCTLCARD_TYPE_GENERAL, "General"},
	{NET_ACCESSCTLCARD_TYPE_VIP, "VIP"},
	{NET_ACCESSCTLCARD_TYPE_GUEST, "Guest"},
	{NET_ACCESSCTLCARD_TYPE_PATROL, "Patrol"},
	{NET_ACCESSCTLCARD_TYPE_BLACKLIST, "BlackList"},
	{NET_ACCESSCTLCARD_TYPE_CORCE, "Duress"},
	{NET_ACCESSCTLCARD_TYPE_MOTHERCARD, "MotherCard"},
};


// 一段固定内存，做指纹数据包测试用
class CFixBuffer
{
public: 
	CFixBuffer(DWORD nSize)
	{
		m_pBuffer = NULL;
		m_pBuffer = new char[nSize];
		m_nMaxSize = nSize;
		m_nBufferLen = 0;
	}
	~CFixBuffer()
	{
		if (m_pBuffer)
		{
			delete[] m_pBuffer;
		}
	}
	
	void Clear() { m_nBufferLen = 0;}
	BOOL AppendBuffer(char* pBuffer, DWORD nLen)
	{
		if (nLen+m_nBufferLen > m_nMaxSize || NULL == m_pBuffer)
		{
			return FALSE;
		}
		
		memcpy(m_pBuffer+m_nBufferLen, pBuffer, nLen);
		m_nBufferLen += nLen;
		return TRUE;
	}
	const char* GetBuffer() const {return m_pBuffer;}
	DWORD GetLen() const {return m_nBufferLen;}
private:
	char* m_pBuffer;
	DWORD m_nBufferLen;
	DWORD m_nMaxSize;
};

/////////////////////////////////////////////////////////////////////////////
// CSubDlgInfoCard dialog

class CSubDlgInfoCard : public CDialog
{
// Construction
public:
	CSubDlgInfoCard(CWnd* pParent = NULL, NET_RECORDSET_ACCESS_CTL_CARD* p = NULL, int nAccessGroup = 1);   // standard constructor

	void		SetOperateType(Em_RecordSet_Operate_Type emType) {m_emOperateType = emType;}

	void		SetInfo(const NET_RECORDSET_ACCESS_CTL_CARD* p) {	
		memcpy(&m_stuInfo, p, sizeof(NET_RECORDSET_ACCESS_CTL_CARD));}

	const NET_RECORDSET_ACCESS_CTL_CARD& GetInfo() const { return m_stuInfo;}

	bool IsDirty() const { return m_bDirty;}

// Dialog Data
	//{{AFX_DATA(CSubDlgInfoCard)
	enum { IDD = IDD_SUBDLG_INFO_CARD };
	CButton	m_chkFirstEnter;
	CComboBox	m_cmbCardType;
	CComboBox	m_cmbCardStatus;
	CDateTimeCtrl	m_dtpVDStart;
	CDateTimeCtrl	m_dtpVDEnd;
	CDateTimeCtrl	m_dtpCreateTimeTime;
	CDateTimeCtrl	m_dtpCreateTimeDate;
	CString	m_strTestFingerPacketData;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSubDlgInfoCard)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSubDlgInfoCard)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnRecsetCardBtnDoors();
	afx_msg void OnRecsetCardBtnTm();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	void InitDlg();
	void StuToDlg();
	void DlgToStu();

	BOOL Get();
	BOOL Update();
	BOOL Remove();
	void Clear();

	int  CardStatusToInt(NET_ACCESSCTLCARD_STATE emStatus);
	NET_ACCESSCTLCARD_STATE IntToCardStatus(int n);

	int  CardTypeToInt(NET_ACCESSCTLCARD_TYPE emType);
	NET_ACCESSCTLCARD_TYPE IntToCardType(int n);

private:
	NET_RECORDSET_ACCESS_CTL_CARD	m_stuInfo;
	Em_RecordSet_Operate_Type		m_emOperateType;
    int                             m_nAccessGroup;
	bool							m_bDirty;
	//CFixBuffer						m_fingerPrintPacket;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SUBDLGINFOCARD_H__2410B577_5B03_4F4D_8F44_54E07099336D__INCLUDED_)
