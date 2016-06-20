#if !defined(AFX_CONFIGCOMM_H__AD4CB71B_FE9B_449A_B4F7_B076352882A5__INCLUDED_)
#define AFX_CONFIGCOMM_H__AD4CB71B_FE9B_449A_B4F7_B076352882A5__INCLUDED_

#include "dhnetsdk.h"
#include "ComConstants.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ConfigComm.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CConfigComm dialog

// 串口配置结构体
typedef struct
{
	DWORD				dwSize;

	DWORD				dwDecProListNum;				// 解码器协议个数
	char				DecProName[DH_MAX_DECPRO_LIST_SIZE][DH_MAX_NAME_LEN]; // 协议名列表
	DH_485_CFG			stDecoder[CHANNEL_NUM_LIMIT];					// 各解码器当前属性

	DWORD				dw232FuncNameNum;		// 232功能个数
	char				s232FuncName[DH_MAX_232FUNCS][DH_MAX_NAME_LEN];	// 功能名列表
	DH_RS232_CFG		st232[DH_MAX_232_NUM];	// 各232串口当前属性
} DEV_COMM_CFG_EX;

class CConfigComm : public CDialog
{
// Construction
public:
	//Display COM information
	void InitDlgInfo(DEV_COMM_CFG_EX *pCommInfo, BYTE nCommCount,int nChannelCount);
	//Clear information
	void CleanAll();

	CConfigComm(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CConfigComm)
	enum { IDD = IDD_CONFIG_COMM };
	CComboBox	m_ctlParity485;
	CComboBox	m_ctlBaud485;
	CComboBox	m_ctlStopBit485;
	CComboBox	m_ctlData485;
	CComboBox	m_ctlProtocal485;
	CComboBox	m_ctlCom485;
	CComboBox	m_ctlCommParity;
	CComboBox	m_ctlCommBaud;
	CComboBox	m_ctlCommStopBit;
	CComboBox	m_ctlCommData;
	CComboBox	m_ctlCommFun;
	CComboBox	m_ctlCom232;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CConfigComm)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CConfigComm)
	afx_msg void OnButtonApply();
	afx_msg void OnButtonReadall();
	afx_msg void OnSelchangeCombo232com();
	afx_msg void OnSelchangeCombo485com();
	virtual BOOL OnInitDialog();
	afx_msg void OnCancelMode();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	DEV_COMM_CFG_EX m_CommInfo;
	void SaveComm485Info(int nNum);
	void SaveComm232Info(int nNum);
	int	 GetComm485Sel(int nStopBit);
	int m_nCur485;
	int m_nCur232;
	int m_nCommCount232;
	int m_nChannelCount485;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONFIGCOMM_H__AD4CB71B_FE9B_449A_B4F7_B076352882A5__INCLUDED_)
