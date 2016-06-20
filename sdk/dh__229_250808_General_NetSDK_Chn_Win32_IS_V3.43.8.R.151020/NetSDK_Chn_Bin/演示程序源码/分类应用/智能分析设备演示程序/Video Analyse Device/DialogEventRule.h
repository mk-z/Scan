#if !defined(AFX_DIALOGEVENTRULE_H__742DB4C2_09E3_47C0_8293_0263C09BDFB8__INCLUDED_)
#define AFX_DIALOGEVENTRULE_H__742DB4C2_09E3_47C0_8293_0263C09BDFB8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DialogEventRule.h : header file
//

#include "PictureWnd.h"
#include "include/dhconfigsdk.h"
#include "stdafx.h"

/////////////////////////////////////////////////////////////////////////////
// CDialogEventRule dialog

#define WM_USER_ALAMR_COME (WM_USER + 1)
typedef std::map<int, GUID> GROUPIDMAP;

class CDialogPCQuery;
class CDialogEventRule : public CDialog
{
	typedef enum UI_STATE
	{
		UI_STATE_SUBSCRIBE_NOW,
			UI_STATE_SUBSCRIBE_STOP
	};
// Construction
public:
	void UpdateDeviceInfo(LONG lLoginID, NET_DEVICEINFO& netDevInfo, BOOL bLogin);
	void OnReceiveEvent(LONG lAnalyzerHandle, DWORD dwAlarmType, void* pAlarmInfo, BYTE *pBuffer, DWORD dwBufSize, int nSequence);
	CDialogEventRule(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDialogEventRule();

	void SetPCQueryDlg(CDialogPCQuery* p){this->m_pcQueryDlg = p;}
	void DeletAlarmInfo(char* pGUID);
	void DisplayFilter();

// Dialog Data
	//{{AFX_DATA(CDialogEventRule)
	enum { IDD = IDD_DIALOG_EVENT_RULE };
	CComboBox	m_cbArrange;
	CComboBox	m_cbMSChannel;
	CComboBox	m_cbDisplayFilter;
	CStatic	m_stuShowBmp;
	CListCtrl		m_lcRealEvent;
	CCheckListBox	m_lstEventType;
	CCheckListBox	m_lstEventDisplay;
	CCheckListBox	m_lstEventChannel;
	CComboBox		m_cbPreviewChannel;
	CString	m_strSnapSeq;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialogEventRule)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDialogEventRule)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeComboPreviewChannel();
	afx_msg void OnButtonStartPreview();
	afx_msg void OnButtonStopPreview();
	afx_msg void OnButtonStart();
	afx_msg void OnButtonStop();
	afx_msg void OnSelchangeComboDisplayFilter();
	afx_msg void OnNMClickListctrlRealEvent(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDestroy();
	afx_msg void OnBnClickedButtonChnSelAll();
	afx_msg void OnBnClickedButtonChnAntiSel();
	afx_msg void OnBnClickedButtonTypeSelAll();
	afx_msg void OnBnClickedButtonTypeAntiSel();
	afx_msg void OnBnClickedCheckTypeAll();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnButtonClear();
	afx_msg void OnBnClickedButtonClearData();
	afx_msg void OnKeydownListctrlRealEvent(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnButtonManualSnap();
	afx_msg void OnSelchangeComboArrange();
	afx_msg void OnFlagMosaic();
	afx_msg void OnFlagEvent();
	afx_msg void OnButtonPause();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	static int  __stdcall RealLoadPicCallback (LLONG lAnalyzerHandle, DWORD dwAlarmType, void* pAlarmInfo, BYTE *pBuffer, DWORD dwBufSize, LDWORD dwUser, int nSequence, void *userdata);
	LRESULT OnAlarmCome(WPARAM wParam, LPARAM lParam);	

public:
	void ReceiveRealData(LLONG lRealHandle, DWORD dwDataType, BYTE *pBuffer, DWORD dwBufSize);
	void OnDisConnect(LLONG lLoginID, char *pchDVRIP, LONG nDVRPort, LDWORD dwUser);

private:
	//保存事件的所有信息，包括图片
	BOOL StoreEvent(const char* szGUID, const char* szCFGFilePath, const char* szBMPFilePath, DWORD dwAlarmType, void* pAlarmInfo, BYTE *pBuffer, DWORD dwBufSize, GUID nPicGroupID, GUID nEvnGroupID);
	
	//显示事件的所有信息，包括图片
	BOOL DisplayEvent(const char* szGUID, const char* szBMPFilePath, DWORD dwAlarmType, void* pAlarmInfo, BYTE *pBuffer, DWORD dwBufSize);

	//显示图片
	//BOOL DisplayPic(const char* szBMPFilePath);

	//显示数据
	BOOL DisplayInfo(const char* szGUID, DWORD dwAlarmType, void* pAlarmInfo, GUID nPicGroupId, GUID nEvnGroupId);
	
	//改变数据的标题
	void ChangeDisplayTitle(DWORD dwAlarmType);

	// 改变数据显示方式
	void ChangeDisplayArrange(int nArrangMode);
	
	//改变UI,在订阅和停止订阅的情况下，UI有些区别
	void ChangeUI(int nState);
	
	//显示选中记录的图片信息，包括（图片，牌照，以及拍照文字）
	void DisplaySelectedPicInfo(int nItemIndex, CListCtrl* listCtrl);

	// 根据组id号及排列方式，查找新事件信息的插入位置
	void GetInsertIndex(int &nInsertIndex, GUID nPicGroupId, GUID nEvnGroupId);

private:
	LLONG			      m_lLoginID;
	NET_DEVICEINFO	      m_netDevInfo;
	LLONG			      m_lPlayID;
	int                   m_nArrangMode;
	GUID                  m_nCurrentPicGroupId;
	GROUPIDMAP            m_mapCurrentEvnGroupId;
	std::list<GUID>       m_lsGroupId;

	std::vector<LONG> m_allRealLoadPicHandle;
	
	std::list<ALARM_ITEM> m_allAlarmItems;
	CRITICAL_SECTION       m_csAlarmItems;

	CPictureWnd m_cPictureWnd;

	CFont* m_Font;

	unsigned int m_alarmCount;

	CDialogPCQuery*	m_pcQueryDlg;

private:
	//For refresh BMP
	char*  m_szBmpBuffer;
	DWORD  m_dwBmpBufferSize;

	HBITMAP m_hBitmap;
	CDC*	m_MemDC;
	int		m_nWidth;
	int		m_nHeight;
	RECT	m_rect;
	CClientDC* m_ClientDC;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOGEVENTRULE_H__742DB4C2_09E3_47C0_8293_0263C09BDFB8__INCLUDED_)
