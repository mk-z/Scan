#if !defined(AFX_PROJECT_H__FD45FC0A_2A58_4978_AACC_F5441AFB4AD3__INCLUDED_)
#define AFX_PROJECT_H__FD45FC0A_2A58_4978_AACC_F5441AFB4AD3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Project.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CProjectCfg dialog

class CTaskCfg;
class CProjectCfg : public CDialog
{
// Construction
public:
	CProjectCfg(CWnd* pParent = NULL);   // standard constructor
	CProjectCfg(CDialog* pTask, CWnd* pParent = NULL);
	~CProjectCfg();

// Dialog Data
	//{{AFX_DATA(CProjectCfg)
	enum { IDD = IDD_DLG_PROJECT };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CProjectCfg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CProjectCfg)
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnGetProject();
	afx_msg void OnBtnSetProject();
	afx_msg void OnBtnAddProject();
	afx_msg void OnBtnDelProject();
	afx_msg void OnBtnModifyProject();
	afx_msg void OnBtnAddTaskToProject();
	afx_msg void OnBtnDelTaskFromProject();
	afx_msg void OnSelchangeComboProject();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	BOOL UnInitProject(CFG_VIDEODIAGNOSIS_PROJECT* pProject);
	BOOL InitProject(CFG_VIDEODIAGNOSIS_PROJECT** pProject);

	// 刷新计划数据(m_pProject)到界面
	void UpDataToDlg();
	// 计划名称已经存在返回TRUE,否则返回FALSE
	BOOL HasSameName(char* szName);
public:
	BOOL GetDefaultProject();
private:
	CComboBox         m_comboProject;
	CComboBox         m_comboTask;
	CListCtrl         m_lstProjectInfo;
	CDateTimeCtrl     m_startTime;
	CDateTimeCtrl     m_endTime;

	CTaskCfg*         m_pTask;
	CFG_VIDEODIAGNOSIS_PROJECT * m_pProject;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROJECT_H__FD45FC0A_2A58_4978_AACC_F5441AFB4AD3__INCLUDED_)
