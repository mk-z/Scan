#if !defined(AFX_PREVIEW_H__8E9C1545_CAAC_4618_9A5D_7889CFA50EA4__INCLUDED_)
#define AFX_PREVIEW_H__8E9C1545_CAAC_4618_9A5D_7889CFA50EA4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define WM_CLOSEPREVIEW		(WM_USER + 300)

class CPreview : public CDialog
{
// Construction
public:
	CPreview(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CPreview)
	enum { IDD = IDD_PREVIEW };
	CComboBox	m_cmbChannel;
	//}}AFX_DATA


protected:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	//{{AFX_MSG(CPreview)
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	afx_msg void OnSelchangePreviewCmbChannel();
	afx_msg void OnRclickPreviewListAlarm(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClosePreview();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	//获取设备登录句柄和设备信息后初始化本窗口
	void InitPreviewDlg(int nChnCount);

	//登出设备后，清理窗口界面信息
	void UninitPreviewDlg();

	void ShowPreview(LONG lLoginHanlde, int nChannel);
	void ClosePreview(LONG lRealPlayHandle);
	
	//实时画面上绘制规则信息
	static void _stdcall DrawIvsInfoPreviewProc(long nPort,HDC hdc,LONG nUser);
	
	//实时画面上绘制实时的智能分析信息
	static void _stdcall GetIvsInfoProc(char* buf, long type, long len, long reallen, long reserved, long nUser);

};


#endif // !defined(AFX_PREVIEW_H__8E9C1545_CAAC_4618_9A5D_7889CFA50EA4__INCLUDED_)
