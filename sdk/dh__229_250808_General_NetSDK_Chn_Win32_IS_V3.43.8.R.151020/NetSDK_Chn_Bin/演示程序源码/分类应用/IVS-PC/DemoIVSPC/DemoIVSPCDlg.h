// DemoIVSPCDlg.h : header file
//

#if !defined(AFX_DEMOIVSPCDLG_H__FCB9A603_26B7_43E9_8657_752A8CD527BB__INCLUDED_)
#define AFX_DEMOIVSPCDLG_H__FCB9A603_26B7_43E9_8657_752A8CD527BB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CPreview;
class CConfig;
class CDlgQuery;

class CLogo;

struct DeviceDisConnectData 
{
	LONG lLoginID;
	char pchDVRIP[40];
	LONG nDVRPort;
};
/////////////////////////////////////////////////////////////////////////////
// CDemoIVSPCDlg dialog

class CDemoIVSPCDlg : public CDialog
{
// Construction
public:
	CDemoIVSPCDlg(CWnd* pParent = NULL);	// standard constructor
	~CDemoIVSPCDlg();

	//设置当前查看的图像的通道号
	inline void SetCurrentChannel(int nChannel){m_nCurrentChn = nChannel;}
	inline int GetCurrentChannel(){return m_nCurrentChn;}

	//获取/设置登录句柄
	inline LONG GetLoginHandle(){return m_lLoginHandle;}
	inline void SetLoginHandel(LONG lLoginHandle){m_lLoginHandle = lLoginHandle;}

	//获取/设置预览句柄
	inline LONG GetRealPlayHandle(){return m_lRealPlayHandle;}
	inline void SetRealPlayHandel(LONG lRealPlayHandle){m_lRealPlayHandle = lRealPlayHandle;}

	//获取设备信息结构体
	inline NET_DEVICEINFO* GetDevInfo(){return &m_stuDeviceInfo;}

	//分配内存给配置信息
	BOOL NewConfigInfo(int nChnCount);

	//释放配置信息的内存空间
	void DeleteConfigInfo();

	//获取某通道的能力分析集
	CFG_CAP_ANALYSE_INFO* GetCapAnalyseInfo(int nChannel);

	//获取某通道的全局配置信息
	CFG_ANALYSEGLOBAL_INFO* GetAnalyseGlobalInfo(int nChannel);

	//获取某通道的模块配置信息
	CFG_ANALYSEMODULES_INFO* GetAnalyseModuleInfo(int nChannel);

	//获取某通道的规则配置信息
	CFG_ANALYSERULES_INFO* GetAnalyseRulesInfo(int nChannel);

	//获取该通道当前场景的序号
	int GetScenceSeqOfCurChn(CFG_CAP_ANALYSE_INFO* pCapAnalyseInfo, CFG_ANALYSEGLOBAL_INFO* pAnalyseGlobalInfo);

	//获取单独规则信息链表的头指针
	lsRuleList* GetRuleList(int nChannel);

	void EnableLoginWindow(LoginState emState);

	void RefreshModuleInfo();
	void RefreshGlobalInfo();
	void RefreshRuleInfo();

	CConfig*	m_pdlgConfig;


// Dialog Data
	//{{AFX_DATA(CDemoIVSPCDlg)
	enum { IDD = IDD_DEMOIVSPC_DIALOG };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDemoIVSPCDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CDemoIVSPCDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBtnPreview();
	afx_msg void OnBtnConfig();
	afx_msg void OnDestroy();
	afx_msg void OnMainBtnLogout();
	afx_msg void OnBnClickedMainBtnQuery();
	afx_msg LRESULT DeviceDisConnect(WPARAM wpara, LPARAM lpara);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	//调用SDK接口获取分析能力集信息
	BOOL GetCap(int nChannel, CFG_CAP_ANALYSE_INFO* pCfgCapAnalyseInfo);

	//调用SDK接口获取全局配置
	BOOL GetGlobal(int nChannel, CFG_ANALYSEGLOBAL_INFO* pCfgAnalyseGlobalInfo);

	//调用SDK接口获取模块配置
	BOOL GetModule(int nChannel, CFG_ANALYSEMODULES_INFO* pCfgAnalyseModulesInfo);

	//调用SDK接口获取规则配置
	BOOL GetRule(int nChannel, CFG_ANALYSERULES_INFO* pCfgAnalyseRulesInfo);

	//获取某通道支持的所有规则中，最大的规则结构体的大小
	// 	int getMaxStuSize(DWORD* pRuleType, int nRuleNum);
	int GetMaxStuSize(SCENE_SUPPORT_RULE* pRuleType, int nRuleNum);

	void PutRuleInfoIntoList(int nChnCount);

private:
	typedef enum DlgType
	{
		dlgNone = 0,
		dlgPreview,
		dlgConfig,
		dlgQuery,
	};

	void ShowDlg(enum DlgType dlgTYPE);

	CLogo* m_pdlgLogo;

	//登录句柄
	LONG m_lLoginHandle;

	//播放句柄
	LONG m_lRealPlayHandle;

	//分析句柄
	LONG m_lAnalyzerHandle;

	//实际的设备通道数
	int m_nChnCount;
		
	//设备信息，每个设备对应一个结构体
	NET_DEVICEINFO m_stuDeviceInfo;
	
	//能力分析集，每个通道对应一个结构体
	CFG_CAP_ANALYSE_INFO* m_pStuCfgCapAnalyseInfo;
	
	//全局配置，每个通道对应一个结构体
	CFG_ANALYSEGLOBAL_INFO* m_pStuCfgAnalyseGlobalInfo;
	
	//模块配置，每个通道对应一个结构体，每个通道对应多个模块配置信息
	CFG_ANALYSEMODULES_INFO* m_pStuCfgAnalyseModuleInfo;
	
	//规则配置，每个通道对应一个结构体，每个通道对应多个规则配置信息
	CFG_ANALYSERULES_INFO* m_pStuCfgAnalyseRuleInfo;

	//各个通道的具体规则列表
	lsRuleList* m_pRuleList;
	
	DlgType		m_currentDlg;
	int			m_nCurrentChn;
	BOOL		m_bIsSwitchOn;
	CPreview*	m_pdlgPreview;
	CDlgQuery*  m_pdlgQuery;

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DEMOIVSPCDLG_H__FCB9A603_26B7_43E9_8657_752A8CD527BB__INCLUDED_)
