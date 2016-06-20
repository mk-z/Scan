// CapturePictureDlg.h : header file
//

#if !defined(AFX_CAPTUREPICTUREDLG_H__D9C45EF9_395C_4B97_BC84_822B259025D9__INCLUDED_)
#define AFX_CAPTUREPICTUREDLG_H__D9C45EF9_395C_4B97_BC84_822B259025D9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CCapturePictureDlg dialog
#include "dhnetsdk.h"
#include "dhconfigsdk.h"

struct VIDEO_SNAP_ATTR_EN_EX
{
	int*					m_pbQueried;
	CFG_SNAPCAPINFO_INFO*	m_pstuSnapAttrEx;
};

class CCapturePictureDlg : public CDialog
{
// Construction
public:
	void OnOnePicture(LONG ILoginID, BYTE *pBuf, UINT RevLen, UINT EncodeType, UINT CmdSerial);
	CCapturePictureDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CCapturePictureDlg)
	enum { IDD = IDD_CAPTUREPICTURE_DIALOG };
	CComboBox	m_ccbQuality;
	CComboBox	m_ccbSize;
	CComboBox	m_ccbSnapMode;
	CComboBox	m_ccbFrameRate;
	CStatic	m_showbmp;
	CComboBox	m_ctlChannel;
	CString	m_strCardNum;
	BOOL	m_bEnable;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCapturePictureDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL
// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CCapturePictureDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonLogin();
	afx_msg void OnButtonLogout();
	afx_msg void OnButtonStart();
	afx_msg void OnBtnStartsnap();
	afx_msg void OnBtnStopsnap();
	afx_msg void OnClose();
	afx_msg void OnRadioSnapone();
	afx_msg void OnRadioSnaptime();
	afx_msg void OnBtnEnable();
	afx_msg void OnSelchangeComboChannel();
	afx_msg void OnBtnGet();
	afx_msg void OnBTNSet();
	afx_msg void OnSelchangeComboSnapMode();
	afx_msg void OnSelchangeComboSnapSize();
	afx_msg void OnSelchangeComboSnapSpace();
	afx_msg void OnSelchangeComboSnapQuality();
	afx_msg void OnCheckTimeEnable();
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void InitSnapConfigUI(int nChn);
	void InitSnapConfigExUI(int nChn);
	void UpdateSnapConfig(int nChn, int nSnapMode);
	bool GetSnapConfigEx(int nChn);
	bool SetSnapConfigEx(int nChn);
	void UpdateSnapConfigEx(int nChn, int nSnapMode);
	bool SetImgSize(int nEm, int& nWidth, int& nHeight);
	bool GetImgSize(int nWidth, int nHeight, int& nEM);
private:
	int m_snapmode;
	void ShowBitmap(LPCSTR filename);
	int m_nChannelCount;
	LLONG m_LoginID;
	void ShowLoginErrorReason(int nError);
	void InitNetSDK();
	HBITMAP LoadImageFile(LPCSTR szImagePath, int &nWidth, int &nHeight);
	HBITMAP ExtractBitmap(IPicture *pPicture, int &nWidth, int &nHeight);
	void ShowSnapImage(LPCSTR szImagePath);
private:
	DH_SNAP_ATTR_EN			m_stuSnapAttr;
	VIDEO_SNAP_ATTR_EN_EX	m_stuSnapAttrEx;
	BOOL					m_bJSON;
	DHDEV_SNAP_CFG			m_stuSnapCfg[32];
	CFG_ENCODE_INFO*		m_pstuSnapCfgEx;
	DHDEV_SYSTEM_ATTR_CFG   m_stuDevAttrInfo;
	BOOL                    m_bDataError[32];
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CAPTUREPICTUREDLG_H__D9C45EF9_395C_4B97_BC84_822B259025D9__INCLUDED_)
