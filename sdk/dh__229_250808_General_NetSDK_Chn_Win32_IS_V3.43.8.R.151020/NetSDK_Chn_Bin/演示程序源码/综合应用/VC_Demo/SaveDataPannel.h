#if !defined(AFX_SAVEDATAPANNEL_H__BC1C8E3F_0404_4A31_ADF5_D5F78C0D9524__INCLUDED_)
#define AFX_SAVEDATAPANNEL_H__BC1C8E3F_0404_4A31_ADF5_D5F78C0D9524__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SaveDataPannel.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSaveDataPannel dialog

class CSaveDataPannel : public CDialog
{
// Construction
public:
	CSaveDataPannel(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSaveDataPannel)
	enum { IDD = IDD_PANNEL_SAVEDATA };
	CButton	m_IsSaveDataRaw;
	CButton	m_IsSaveDataYuv;
	CButton	m_IsSaveDataStd;
	CButton	m_IsSaveDataPcm;
	CButton	m_IsSaveRealData;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSaveDataPannel)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSaveDataPannel)
	virtual BOOL OnInitDialog();
	afx_msg void OnSaveRealdata();
	afx_msg void OnSavecbdatastd();
	afx_msg void OnSavecbdatayuv();
	afx_msg void OnSavecbdatapcm();
	afx_msg void OnSavecbdataraw();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	void SetCheckReal(int nCheck);
	void SetCheckRaw(int nCheck);
	void SetCheckStd(int nCheck);
	void SetCheckPcm(int nCheck);
	void SetCheckYuv(int nCheck);

private:
	CBrush m_myBrush;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SAVEDATAPANNEL_H__BC1C8E3F_0404_4A31_ADF5_D5F78C0D9524__INCLUDED_)
