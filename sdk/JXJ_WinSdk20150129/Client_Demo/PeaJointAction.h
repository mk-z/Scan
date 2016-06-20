#pragma once
#include "afxwin.h"


// CPeaJointAction 对话框

class CPeaJointAction : public CDialog
{
	DECLARE_DYNAMIC(CPeaJointAction)

public:
	CPeaJointAction(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CPeaJointAction();

// 对话框数据
	enum { IDD = IDD_DIALOG3 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonSave();
	afx_msg void OnBnClickedButtoncancel();
	CButton m_JointActionChannel;
	CEdit m_JointRecTime;
	CButton m_JointOut;
	CEdit m_JointOutTime;
	CButton m_JointTakePicChannel;
	CEdit m_JoinTakePicLever;
	CButton m_TakePicFtpUp;
	CEdit m_TakePicCount;
	CButton m_JointVoice;
	CEdit m_JointVoiceTime;
	CButton m_JointEmail;

};
