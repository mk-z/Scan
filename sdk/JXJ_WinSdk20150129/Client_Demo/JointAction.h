#pragma once
#include "afxwin.h"


// CJointAction 对话框

class CJointAction : public CDialog
{
	DECLARE_DYNAMIC(CJointAction)

public:
	CJointAction(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CJointAction();

// 对话框数据
	enum { IDD = IDD_DIALOG_JOINT_ACTION };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	CComboBox			m_JointWarnType;
	CButton				m_JointVideoChannel;
	CButton				m_JointOut;
	CButton				m_JointTakePic;
	CButton				m_JointVoice;
	CButton				m_JointEmail;
	CEdit				m_eJointVideoTime;
	CEdit				m_eJointVoice;
	CEdit				m_JointOutTime;
	CEdit				m_JointLever;
	CEdit				m_JointPicCount;
	CButton				m_PictureUpLoadFtp;
	CComboBox			m_chooseChannel;
	CStatic				m_StaticText;
	CButton				m_recordAction;
	CButton				m_snapAction;
	CButton				m_snapFtp;
	CButton				m_outAction;

	afx_msg void OnBnClickedButtonSave();
	afx_msg void OnBnClickedButtonFlash();
	afx_msg void OnCbnSelchangeComboChoosechannel();
	afx_msg void OnCbnSelchangeComboWrtningtype();
	afx_msg void OnClose();
	int			 ReFreshWindow();
	
private:
	JJointAction			m_jointAction;
	int						m_alarmType;

};
