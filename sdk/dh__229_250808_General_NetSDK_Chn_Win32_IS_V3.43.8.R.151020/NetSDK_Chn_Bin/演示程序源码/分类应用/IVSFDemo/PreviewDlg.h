#if !defined(AFX_PREVIEWDLG_H__58374936_3D1A_44D8_A934_4DBD6E7CD0A4__INCLUDED_)
#define AFX_PREVIEWDLG_H__58374936_3D1A_44D8_A934_4DBD6E7CD0A4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PreviewDlg.h : header file
//
#include "include/dhnetsdk.h"
#include "ItemPanel.h"
#include <string>
/////////////////////////////////////////////////////////////////////////////
// CPreviewDlg dialog

typedef struct 
{
	CString                          strGuid;
	DEV_EVENT_FACERECOGNITION_INFO   stAlarmInfo;
	CString							 strFilePre;
}AlarmItem;

typedef struct
{
	DWORD dwAlarmType; 
	void *pAlarmInfo;
	BYTE *pBuffer;
	DWORD dwBufSize;
}EventData;

class CIVSFDemoDlg;
class CItemPanel;
class CAlarmShow;
class CPreviewDlg : public CDialog
{
// Construction
public:
	CPreviewDlg(CWnd* pParent = NULL);   // standard constructor
// Dialog Data
	//{{AFX_DATA(CPreviewDlg)
	enum { IDD = IDD_DIALOG_PREVIEW };
	CComboBox	m_cbChannel;
	CListCtrl	m_lsEvent;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPreviewDlg)
	public:
	virtual void OnFinalRelease();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPreviewDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonStartview();
	afx_msg void OnButtonStopview();
	afx_msg void OnDestroy();
	afx_msg void OnClickListEvent(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	LRESULT OnDeletExceededItems(WPARAM wParam, LPARAM lParam);
	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CPreviewDlg)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()

private:
	CIVSFDemoDlg*          m_pIVSFDemodlg;
	CAlarmShow*	           m_pAlarmShow;
	
	int                    m_nChannelCount;
	LLONG                  m_lLogHandle;
	LLONG                  m_lRealPlayHandle;
	std::list<AlarmItem*>  m_lsAlarmItems;
	CRITICAL_SECTION       m_csAlarmItems;

public:
	void Init(CIVSFDemoDlg* pDlg, LONG lLogHandle);
	void Clean();
	void SetChannelCount(int nChannel);
	void ShowAlarmInfo(DWORD dwAlarmType, void* pAlarmInfo, BYTE *pBuffer, DWORD dwBufSize);
	void OperateStream(BOOL bResume);
	void ShowEventInfo(DWORD dwAlarmType, void* pAlarmInfo, BYTE *pBuffer, DWORD dwBufSize);

private:

	CString GetDataFolder();
	void ShowItemInfo(char* pGuid);
	void SaveAlarmInfo(void* pAlarmInfo, BYTE *pBuffer, DWORD dwBufSize, CString strFilePreName, CString strGuid);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PREVIEWDLG_H__58374936_3D1A_44D8_A934_4DBD6E7CD0A4__INCLUDED_)
