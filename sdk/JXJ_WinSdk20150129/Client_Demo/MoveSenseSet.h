#pragma once
#include "afxwin.h"
#include "MoveSenseScreen.h"
#include "VideoTime.h"

// CMoveSenseSet 对话框

class CMoveSenseSet : public CDialog
{
	DECLARE_DYNAMIC(CMoveSenseSet)

public:
	CMoveSenseSet(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CMoveSenseSet();

// 对话框数据
	enum { IDD = IDD_DIALOG_MOVE_SENSE_SET };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	CComboBox			m_Channel;
	CButton				m_StartMoveSense;
	CComboBox			m_Response;
	CComboBox			m_SenseSecond;
	CButton				m_bStartPaint;

	
	afx_msg void OnClose();
	afx_msg void OnDestroy();
	afx_msg void OnBnClickedButtonSave();
	afx_msg void OnBnClickedButtonFlash();
	afx_msg void OnBnClickedButtonHidetime();
	afx_msg void OnBnClickedButtonClear();
	afx_msg void OnBnClickedCheckStartpaint();


	void		 ShowVideoTime(int iIndex);
	int			 ReFreshWindow();
	CMoveSenseScreen	m_cMoveSenseScreen;
private:
	JMoveAlarm			m_moveAlarm;
	JJProcess			m_jProcess;
	CVideoTime			m_cVideoTime;
	
};
