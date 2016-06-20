#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "afxcolorbutton.h"


// CElevatorSet 对话框

class CElevatorSet : public CDialog
{
	DECLARE_DYNAMIC(CElevatorSet)

public:
	CElevatorSet(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CElevatorSet();

// 对话框数据
	enum { IDD = IDD_DIALOG_ELEVATOR };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	CEdit			m_editTop;
	CEdit			m_editCurrent;
	CListCtrl		m_floorList;
	CEdit			m_SubItemEdit;
	CEdit			m_loopAdd;
	CEdit			m_showTextX;
	CEdit			m_showTextY;
	CMFCColorButton m_showTextColor;

	int				m_listSelFlag[3];
	CString			m_cstrItemTextEdit;
	




	afx_msg void OnBnClickedButtonSettop();
	afx_msg void OnBnClickedButtonSetcurrent();
	afx_msg void OnBnClickedButtonFlash();
	afx_msg void OnBnClickedButtonSave();
	afx_msg void OnNMDblclkListFloor(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnEnKillfocusEditListedit();
	afx_msg void OnBnClickedButtonSetloopadd();


	void	SetListItemText(void);
	BOOL	PreTranslateMessage(MSG* pMsg);
	int		ReFreshWindow();
	int		RedrawWindow();

private:
	JElevatorCfg	m_elevatorCfg;

};
