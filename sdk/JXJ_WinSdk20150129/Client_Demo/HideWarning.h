#pragma once
#include "afxwin.h"
#include "VideoTime.h"
#include "HideAlarmScreen.h"


// CHideWarning 对话框

class CHideWarning : public CDialog
{
	DECLARE_DYNAMIC(CHideWarning)

public:
	CHideWarning(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CHideWarning();

// 对话框数据
	enum { IDD = IDD_DIALOG_HIDE_WARNING };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	CComboBox			m_Channel;
	CButton				m_StartHideAlarm;
	CButton				m_bStartPaint;
	CComboBox			m_Response;
	CComboBox			m_SenseSecond;
	CVideoTime			m_cVideoTime;
	CHideAlarmScreen	m_cHideAlarmScreen;
	
	
	afx_msg void OnClose();
	afx_msg void OnDestroy();
	afx_msg void OnBnClickedButtonSave();
	afx_msg void OnBnClickedButtonFlash();
	afx_msg void OnBnClickedButtonClear();
	afx_msg void OnBnClickedButtonHidetime();
	afx_msg void OnBnClickedCheckStartpaint();


	void		ShowVideoTime(int iIndex);
	int			ReFreshWindow();


private:
	JHideAlarm			m_hideAlarm;
};
