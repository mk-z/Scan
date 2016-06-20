#pragma once
#include "afxdtctl.h"
#include "afxwin.h"
#include "afxcmn.h"


// CSerachNote 对话框

class CSerachNote : public CDialog
{
	DECLARE_DYNAMIC(CSerachNote)

public:
	CSerachNote(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSerachNote();

// 对话框数据
	enum { IDD = IDD_DIALOG_SERACH_RECODE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	
	CDateTimeCtrl			m_StartDate;
	CDateTimeCtrl			m_StartTime;
	CDateTimeCtrl			m_EndDate;
	CDateTimeCtrl			m_EndTime;
	CComboBox				m_RecodeType;
	CListCtrl				m_ListRecode;
	CComboBox				m_RecodeDevice;
	

	afx_msg void OnClose();
	afx_msg void OnBnClickedButtonSerach();
	afx_msg void OnCbnSelchangeComboRecodedevice();


	void					AddToList();
	void					AddToListEnglish();
	time_t					LocalToUtc(CTime dateStart, CTime timeStart);
	void					GetRecodeType(int iIndex);
	int						ReFreshWindow();
private:
	JOperationLog			m_operationLog;
	int						m_iBeginNode;
	int						m_iEndNode;
	int						m_iSsid;
};
