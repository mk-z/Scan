#if !defined(AFX_PROFILE_H__778DDB99_29A6_44C3_AD1D_B7F476CAABF6__INCLUDED_)
#define AFX_PROFILE_H__778DDB99_29A6_44C3_AD1D_B7F476CAABF6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Profile.h : header file
//

#include "control/virtTree.h"
class CProfileInfo1;
/////////////////////////////////////////////////////////////////////////////
// CProfileCfg dialog
class CProfileCfg : public CDialog
{
// Construction
public:
	CProfileCfg(CWnd* pParent = NULL);   // standard constructor
	~CProfileCfg();

// Dialog Data
	//{{AFX_DATA(CProfileCfg)
	enum { IDD = IDD_DLG_PROFILE };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CProfileCfg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CProfileCfg)
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnTvnSelchangedTreeProject(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBtnGetConfig();
	afx_msg void OnBtnSetConfig();
	afx_msg void OnBtnAddProfile();
	afx_msg void OnBtnDeleteProfile();
public:
	afx_msg void OnBtnSavePage();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	STtreeData* InitTreeLink(char *szName, DWORD dwProfile, BOOL bFirstChild = FALSE);
	void InitOneProfile(CFG_VIDEO_DIAGNOSIS_PROFILE& p);
	void UnInitProfile(CFG_VIDEODIAGNOSIS_PROFILE ** pstProfile);
	void InitProfileCfg(CFG_VIDEODIAGNOSIS_PROFILE ** pProfile);
	void CopyAllProfile(CFG_VIDEODIAGNOSIS_PROFILE**pDest, CFG_VIDEODIAGNOSIS_PROFILE* pSrc);
	void UpdateDataToDlg();
	void GetDlgData();
	void GetOneProfileData(CFG_VIDEO_DIAGNOSIS_PROFILE* pInfo, HTREEITEM hDetect);
// 	void SetOneProfileData(CFG_VIDEO_DIAGNOSIS_PROFILE* pInfo, HTREEITEM hDetect);
	void CopyProfile(CFG_VIDEO_DIAGNOSIS_PROFILE & stFrom, CFG_VIDEO_DIAGNOSIS_PROFILE& stDest);
public:
	void GetData();
	inline STtreeData &GetTreeData(){return m_stTreeData;}
private:
	CVirtTree    m_TreeProfile;
	STtreeData   m_stTreeData;

	CProfileInfo1 * m_pProfileInfo1;
	CFG_VIDEODIAGNOSIS_PROFILE * m_pstProfile; 

	bool         m_bSavePage;        /// 当前配置页是否需要保存
	HTREEITEM    m_hSelectTreeItem;  /// 当前树被选中的项
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROFILE_H__778DDB99_29A6_44C3_AD1D_B7F476CAABF6__INCLUDED_)
