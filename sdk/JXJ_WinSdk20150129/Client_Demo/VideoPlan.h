#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "VideoTime.h"

// CVideoPlan 对话框

class CVideoPlan : public CDialog
{
	DECLARE_DYNAMIC(CVideoPlan)

public:
	CVideoPlan(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CVideoPlan();

// 对话框数据
	enum { IDD = IDD_DIALOG_VIDEO_PLAN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	
	CComboBox		m_Channel;
	CListCtrl		m_ListDisk;
	CComboBox		m_StramType;
	CEdit			m_Yl;
	CButton			m_AutoCover;
	CProgressCtrl	m_FormatProgress;


	afx_msg void OnBnClickedButtonTimeset();
	afx_msg void OnBnClickedButtonFormatting();
	afx_msg void OnNMClickListDisk(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButtonFlash();
	afx_msg void OnBnClickedButtonSave();
	afx_msg void OnClose();
	


	void			ShowVideoTime(int iIndex);  //给选择时间对话框默认值
	static  DWORD   ThreadFun(LPVOID lpThreadParameter);
	int				ReFreshDisk();
	int				ReFreshRegin();
private:
	JRecordParameter		m_recordConfig;
	JDeviceDiskInfo			m_diskInfo;
	CVideoTime				m_cVideoTime;
	int						m_DiskNo;

};
