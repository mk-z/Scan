#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include "afxdtctl.h"
#include "RecodeScreenDlg.h"

#define REC_TYPE_MAX_COUNT 1024
// CVideoPlayBack 对话框

class CVideoPlayBack : public CDialog
{
	DECLARE_DYNAMIC(CVideoPlayBack)

public:
	CVideoPlayBack(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CVideoPlayBack();

// 对话框数据
	enum { IDD = IDD_DIALOG_VIDEO_PLAYBACK };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	CListCtrl		m_VideoPlayBack;
	CComboBox		m_RecordYype;
	CComboBox		m_StartHour;
	CComboBox		m_StartMinute;
	CComboBox		m_StartSecond;
	CComboBox		m_EndHour;
	CComboBox		m_EndMinute;
	CComboBox		m_EndSecond;
	CDateTimeCtrl	m_StartTime;
	CDateTimeCtrl	m_EndTime;
	CComboBox		m_ComDevice;


	afx_msg void OnNMDblclkListVideoplayback(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickListVideoplayback(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButtonDownload();
	afx_msg void OnBnClickedButtonSerachvideo();
	afx_msg void OnBnClickedButtonPlayfile();
	afx_msg void OnDestroy();
	afx_msg void OnBnClickedButtonPause();
	afx_msg void OnBnClickedButtonStop();
	afx_msg void OnClose();
	afx_msg void OnCbnSelchangeComboxDevice();
	afx_msg void OnBnClickedButtonFlashdevice();
	afx_msg void OnPaint();
	afx_msg void OnBnClickedButtonPlayslow();
	afx_msg void OnBnClickedButtonPlayfast();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

	static  DWORD DownLoadProgress(LPVOID lpThreadParameter);
	static  DWORD PlayThreadFun(LPVOID lpThreadParameter);
	static  DWORD PlayDeviceThreadFun(LPVOID lpThreadParameter);
	static int  __stdcall JRecStream(long lHandle, LPBYTE pBuff,DWORD dwRevLen,void* pUserParam);
	static int  __stdcall JRecDownload(long lHandle, LPBYTE pBuff,DWORD dwRevLen,void* pUserParam);

	void		PlayVideoFile(CString strFile);
	CString		getDate(CString str);
	void		AddToList(); 
	void		AddToListEnglish(); 
	int			GetRecodeType(CString str);//获取录像类型
	void		ReFreshVideoList();
	void        CloseDownload();
	void		SetPlaySpeed();

	CRecodeScreenDlg	m_recodeScreenDlg;
	int					m_PlayFiletime;
private:
	CString				m_strPasueS;
	CString				m_strPasueE;
	CString				m_strStop;
	long				m_lFrameCount;
	long				m_lstartTime;
	long				m_lEndTime;
	time_t				m_startPlayTime;
	long				m_Filetimes;
	int					m_PlayFastTime;
	int					m_PlaySlowTime;
	int					m_SleepTime;
	int					m_nSpeed;
	bool				m_bClosePlayLocal;
	bool				m_bCloseDevice;
	bool				m_nDownLoadFlag;
	long				m_lRecHandle;
	JStoreLog			m_storeLog;
	bool				m_bIsPasue;
	CProgressCtrl		m_progressDownLoad;
	int					m_iDecPort;
	uint32_t			m_lRecFileSize[REC_TYPE_MAX_COUNT]; //  录像文件大小
	int					m_HIPlayerPort;
	int					m_iListIndex;
	int					m_SerachRecodeByType;
	int					m_iBeginNode;
	int					m_iEndNode;
	int					m_iSsid;
	long				m_downloadHandle;
	long				m_lDownLoad;
	long				m_lDownLoadStartTime;
	long				m_lDownLoadTotalTime;
	int					m_RecType[REC_TYPE_MAX_COUNT];
};
