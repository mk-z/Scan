#if !defined(AFX_CONFIGNETWORK_H__B84400D8_26E7_47CA_B76C_EF6F4B0BC07D__INCLUDED_)
#define AFX_CONFIGNETWORK_H__B84400D8_26E7_47CA_B76C_EF6F4B0BC07D__INCLUDED_

#include <list>
#include "dhnetsdk.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ConfigNetwork.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CConfigNetwork dialog

class CConfigNetwork : public CDialog
{
// Construction
public:
	void CleanAll();
	void CleanRemoteDeviceInfo();
	
	// normal initialization
	void InitDlgInfo(DHDEV_NET_CFG_EX *pNetIOInfo,BYTE nNetIOCount,CFG_EMAIL_INFO *pMailInfo);
	
	// special initialization
	void InitDlgInfo(CFG_MULTICASTS_INFO_OUT* pInfo, DWORD dwChnCount);

	CConfigNetwork(CWnd* pParent = NULL);   // standard constructor

	void SetFrameEthernetInfo();  // 双网卡时显示部分控件
    BOOL m_bDBEthernet;    // 是否为双网卡
// Dialog Data
	//{{AFX_DATA(CConfigNetwork)
	enum { IDD = IDD_CONFIG_NETWORK };
	CComboBox	m_cmbStreamType;
	CComboBox	m_cmbCount;
	CComboBox	m_cmbChannel;
	CComboBox	m_cmbCastType;
	CIPAddressCtrl	m_ctrlLocalIP;
	CIPAddressCtrl	m_ctlMailIP;
	CIPAddressCtrl	m_ctlNetIPMask;
	CIPAddressCtrl	m_ctlNetIP;
	CIPAddressCtrl	m_ctlNetGateWay;
	CIPAddressCtrl	m_ctlHostIP;
	CButton	m_ctlChkRemote;
	CComboBox	m_ctlRemoteHost;
	CComboBox	m_ctlEthernet;
	CComboBox	m_ctlNetInterface;
    CComboBox   m_ctlNetMode;
    CComboBox   m_ctlDefaultCard;
	BOOL	m_bTransmit;
	BOOL	m_bValid;
	BOOL	m_bVideoCP;
	BOOL	m_bDefault;
	BOOL	m_bMailEn;
	BOOL	m_bMailSSLEn;
	BOOL	m_bAnoymity;
	int		m_nMaxTcp;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CConfigNetwork)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CConfigNetwork)
	afx_msg void OnButtonApply();
	afx_msg void OnButtonReadall();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeComboEthernet();
	afx_msg void OnSelchangeComboRemotehost();
	afx_msg void OnCancelMode();
	afx_msg void OnBnClickedCheckAnonymity();
	afx_msg void OnDestroy();
	afx_msg void OnCheckRemotehost();
	afx_msg void OnSelchangeComboCasttype();
	afx_msg void OnSelchangeComboChannel();
	afx_msg void OnSelchangeComboCount();
	afx_msg void OnButtonInc();
	afx_msg void OnButtonDec();
	afx_msg void OnFieldchangedIpaddressHostip(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnFieldchangedIpaddressLocalip(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnChangeEditHostport();
	afx_msg void OnSelchangeComboNetmode();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	DH_REMOTE_HOST GetRemoteHostType(int nType);
	void SaveRemoteHost(int nNum);
	int m_nCurRemoteHost;
	int m_nCurEthernet;
	void SaveNetWork(int nNum);
	DHDEV_NET_CFG_EX m_NetIOInfo;
	CFG_EMAIL_INFO m_MailInfo;
	void EnableAnonymityWin(bool bCheck);
	int m_nEthernetNum;
	// support special multicast configuration
	BOOL							m_b3Dev;
	DWORD							m_dwChannel;
	CFG_MULTICASTS_INFO_OUT*		m_pstuMulticastInfo;
	CFG_MULTICASTS_INFO_IN*			m_pstuMIn;
	std::list<CFG_MULTICAST_INFO*>	m_lsTS;
	std::list<CFG_MULTICAST_INFO*>	m_lsRTP;
	std::list<CFG_MULTICAST_INFO*>	m_lsVideoII;

	void ShowMulticastInfo();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONFIGNETWORK_H__B84400D8_26E7_47CA_B76C_EF6F4B0BC07D__INCLUDED_)
