// IVS_VDemoDlg.h : header file
//

#if !defined(AFX_IVS_VDemoDLG_H__8B920535_DF45_494B_A10D_FC18CA771CA2__INCLUDED_)
#define AFX_IVS_VDemoDLG_H__8B920535_DF45_494B_A10D_FC18CA771CA2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <iostream>
#include <vector>
/////////////////////////////////////////////////////////////////////////////
// CIVS_VDemoDlg dialog

#define SHOW_DLG_COUNT 5
enum {
	ENUM_DLG_PROFILE,
	ENUM_DLG_TAST,
	ENUM_DLG_PROJECT,
	ENUM_DLG_LISTEN,
	ENUM_DLG_QUERY,
};

class CDeviceListDlg;
class CTaskCfg;
class CIVS_VDemoDlg : public CDialog
{
// Construction
public:
	CIVS_VDemoDlg(CWnd* pParent = NULL);	// standard constructor
	~CIVS_VDemoDlg();

// Dialog Data
	//{{AFX_DATA(CIVS_VDemoDlg)
	enum { IDD = IDD_IVS_VDemo_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CIVS_VDemoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CIVS_VDemoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnMprofile();
	afx_msg void OnBtnProfileCfg();
	afx_msg void OnBtnTaskCfg();
	afx_msg void OnBtnProjectCfg();
	afx_msg void OnBtnListen();
	afx_msg void OnBtnQuery();
	afx_msg void OnBtnLogin();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void GetShowArea(int nId, CRect &rc);
	void ShowDialog(int nDlg);
	void EnableWindowArr(const DWORD dwIDArr[], int nIDCount, BOOL bEnable);
public:
	DWORD GetLoginID(){ return m_hLoginID; }
	int   GetMaxProfiles() { return m_stCapsInfo.nMaxProfiles; }
	int   GetMaxTasks() { return m_stCapsInfo.nMaxTasks; }
	int   GetMaxSourcesOfTask() { return m_stCapsInfo.nMaxSourcesOfTask; }
	int   GetMaxProjects() { return m_stCapsInfo.nMaxProjects; }
	CTaskCfg* GetTaskDlg(){return reinterpret_cast<CTaskCfg*>(m_pDlgArr[ENUM_DLG_TAST]);}
	
	void GetCmdMembers(std::vector<std::string> & v, char* szInCmd, int nTotalNameCount);
private:
	CDialog*      m_pDlgArr[SHOW_DLG_COUNT];
	int           m_nCurrentDlg;

	CDeviceListDlg * m_pDevLstDlg;

	/// µÇÂ½¾ä±ú
	LLONG         m_hLoginID;

	/// ÄÜÁ¦¼¯
	CFG_VIDEODIAGNOSIS_CAPS_INFO   m_stCapsInfo;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IVS_VDemoDLG_H__8B920535_DF45_494B_A10D_FC18CA771CA2__INCLUDED_)
