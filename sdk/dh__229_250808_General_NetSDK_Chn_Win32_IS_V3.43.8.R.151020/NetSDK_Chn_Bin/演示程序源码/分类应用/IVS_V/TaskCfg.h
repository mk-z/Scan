#if !defined(AFX_TASK_H__CA89B9A6_D1AE_4565_8218_BDB5EA6AC8BB__INCLUDED_)
#define AFX_TASK_H__CA89B9A6_D1AE_4565_8218_BDB5EA6AC8BB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Task.h : header file
//

#include <VECTOR>
/////////////////////////////////////////////////////////////////////////////
// CTaskCfg dialog
class CProfileCfg;
class CTaskCfg : public CDialog
{
// Construction
public:
	CTaskCfg(CWnd* pParent = NULL);   // standard constructor
	CTaskCfg(CDialog* pProfileDlg, CWnd* pParent = NULL);
	~CTaskCfg();

// Dialog Data
	//{{AFX_DATA(CTaskCfg)
	enum { IDD = IDD_DLG_TASK };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTaskCfg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTaskCfg)
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeComboTaskList();
	afx_msg void OnBtnClearItem();
	afx_msg void OnBtnDeleteItem();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	BOOL InitTask();
	CRect GetTaskListRect();
	void SetOneDeviceInfo(CFG_TAST_SOURCES* pInfo, int nChannelID, int nChannelCount = 1);
	void OnBtnGetTask();
	void OnBtnSetTask();
	void GetTaskList(std::vector<std::string> & v);
private:
	void InitTaskConfig(CFG_VIDEODIAGNOSIS_TASK** pTask);
	void UnInitTaskConfig(CFG_VIDEODIAGNOSIS_TASK** pTask);
	
	// 任务表名称已经存在返回TRUE,否则返回FALSE
	BOOL HasSameName(char* szTaskName);

	void OnBtnAddTask();
	void OnBtnDeleteTask();
	void OnBtnModifyTask();
private:
	CProfileCfg* m_pProfileDlg;
	CComboBox    m_ComboProfileName;
	CComboBox    m_ComboDuration;
	CComboBox    m_ComboTaskList;
	CListCtrl    m_LstSubTask;

	CFG_VIDEODIAGNOSIS_TASK* m_pTaskCfg;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TASK_H__CA89B9A6_D1AE_4565_8218_BDB5EA6AC8BB__INCLUDED_)
