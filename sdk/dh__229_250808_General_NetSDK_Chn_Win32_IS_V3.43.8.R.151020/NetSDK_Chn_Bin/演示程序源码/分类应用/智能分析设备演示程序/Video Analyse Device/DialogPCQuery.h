#if !defined(AFX_DIALOGPCQUERY_H__6EE4ED32_E389_4D72_8222_C60905713F23__INCLUDED_)
#define AFX_DIALOGPCQUERY_H__6EE4ED32_E389_4D72_8222_C60905713F23__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DialogPCQuery.h : header file
//

#include "PictureWnd.h"
#include "afxwin.h"
#include "stdafx.h"

/////////////////////////////////////////////////////////////////////////////
// CDialogPCQuery dialog

typedef  std::map<std::string, ALARM_ITEM> AlarmMap;
class CDialogEventRule;
class CDialogPCQuery : public CDialog
{
// Construction
public:
	CDialogPCQuery(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDialogPCQuery();

	//添加报警
	void AddAlarm(ALARM_ITEM& item);
	ALARM_ITEM* GetAlarmItemByGUID(const char* szGUID);
	ALARM_ITEM* GetQuerryedAlarmItemByGUID(const char* szGUID);
	void SetEventRuleDlg(CDialogEventRule* p){this->m_pLoadPicDlg = p;}
// Dialog Data
	//{{AFX_DATA(CDialogPCQuery)
	enum { IDD = IDD_DIALOG_PC_QUERY };
	CButton			m_ckState;
	CComboBox		m_cbQState;
	CListCtrl		m_lcResult;
	COleDateTime	m_dateS;
	COleDateTime	m_timeE;
	COleDateTime	m_timeS;
	COleDateTime	m_dateE;
	CString			m_csLP;
	int			        m_speedLow;
	int			        m_speedUper;
	int			        m_lane;
	
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialogPCQuery)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDialogPCQuery)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonQuery();
	afx_msg void OnClickListResult(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnButtonDelete();
	afx_msg void OnButtonSelAll();
	afx_msg void OnButtonAntiSel();
	afx_msg void OnDestroy();
	afx_msg void OnKeydownListResult(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCheckHideNoLp();
	afx_msg void OnCbnSelchangeComboType();
	afx_msg void OnBnClickedButtonNextPage();
	afx_msg void OnBnClickedButtonPrePage();
	afx_msg void OnBnClickedButtonLastPage();
	afx_msg void OnBnClickedButtonFirstPage();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnButtonOpenPic();
	afx_msg void OnButtonSave();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()


private:
	void AddOneItem(ALARM_ITEM& item);
	void RemoveItemByGUID(const char* szGUID);
	void RemoveReultItemByGUID(const char* szGUID);
	void DisplayResultPage(UINT page);
	void UpdatePageStr();
	BOOL DisplayPic(const char* szBMPFilePath);
	void ChangeDisplayTitle(DWORD dwAlarmType);
	void ClearResultListCtrl();
	void ClearQueryResultData();
	void ClearRecordData();
	void UpdateAccuracyStr();
	void DisplaySelectedPicInfo(int nItemIndex, CListCtrl* listCtrl);
	void UpdateEventState(int nItemIndex);
	void UpdateStaticCtrlState(int stateIndex);
	void SaveDataToDisk();

private:
	AlarmMap	m_mapQueryResult;	//查询结果
	AlarmMap	m_mapAllAlarmItem;	//所有的警报

	//CPictureWnd m_cPictureWnd;
	CStatic m_stuShowBmp;
	CFont* m_Font;
	CComboBox m_cbType;// 查询的类型
	std::string m_lastBMPFilePath;
	int			m_nCurSel;//当前选中ListCtrl的

	//For refresh BMP
	char*  m_szBmpBuffer;
	DWORD  m_dwBmpBufferSize;

	HBITMAP m_hBitmap;
	CDC*	m_MemDC;
	int		m_nWidth;
	int		m_nHeight;
	RECT	m_rect;
	CClientDC* m_ClientDC;
	int m_curPage;
	
	CDialogEventRule* m_pLoadPicDlg;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOGPCQUERY_H__6EE4ED32_E389_4D72_8222_C60905713F23__INCLUDED_)
