// DemoIVSbDlg.h : header file
//

#if !defined(AFX_DEMOIVSBDLG_H__FCB9A603_26B7_43E9_8657_752A8CD527BB__INCLUDED_)
#define AFX_DEMOIVSBDLG_H__FCB9A603_26B7_43E9_8657_752A8CD527BB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CPreview;
class CConfig;
class CAlarm;

class CLogo;
/////////////////////////////////////////////////////////////////////////////
// CDemoIVSbDlg dialog

class CDemoIVSbDlg : public CDialog
{
public:
	//设置当前查看的图像的通道号
	void setCurrentChannel(int nChannel)
	{
		m_nCurrentChn = nChannel;
	}

	int getCurrentChannel()
	{
		return m_nCurrentChn;
	}

	//获取/设置登录句柄
	LLONG getLoginHandle()
	{
		return m_lLoginHandle;
	}
	void setLoginHandel(LLONG lLoginHandle)
	{
		m_lLoginHandle = lLoginHandle;
	}

	//获取/设置预览句柄
	LLONG getRealPlayHandle()
	{
		return m_lRealPlayHandle;
	}
	void setRealPlayHandel(LLONG lRealPlayHandle)
	{
		m_lRealPlayHandle = lRealPlayHandle;
	}

	//获取设备信息结构体
	NET_DEVICEINFO* getDevInfo()
	{
		return &m_stuDeviceInfo;
	}


	//分配内存给配置信息
	BOOL newConfigInfo(int nChnCount);

	//释放配置信息的内存空间
	void deleteConfigInfo();

	//获取某通道的能力分析集
	CFG_CAP_ANALYSE_INFO* getCapAnalyseInfo(int nChannel);

	//获取某通道的全局配置信息
	CFG_ANALYSEGLOBAL_INFO* getAnalyseGlobalInfo(int nChannel);

	//获取某通道的模块配置信息
	CFG_ANALYSEMODULES_INFO* getAnalyseModuleInfo(int nChannel);

	//获取某通道的规则配置信息
	CFG_ANALYSERULES_INFO* getAnalyseRulesInfo(int nChannel);

	//获取该通道当前场景的序号
	int getScenceSeqOfCurChn(CFG_CAP_ANALYSE_INFO* pCapAnalyseInfo, CFG_ANALYSEGLOBAL_INFO* pAnalyseGlobalInfo);

	//启动订阅事件检测
	void startAlarmCallBack(std::list<DWORD>* plsdwChannel);

	//关闭订阅事件检测
	BOOL stopAlarmCallBack();

	//获取报警信息链表
	lsAlarmInfo* getAlarmInfoList()
	{
		return &m_lstAlarmInfo;
	}
	
	//调用SDK接口获取分析能力集信息
	BOOL getCap(int nChannel, CFG_CAP_ANALYSE_INFO* pCfgCapAnalyseInfo);
	
	//调用SDK接口获取全局配置
	BOOL getGlobal(int nChannel, CFG_ANALYSEGLOBAL_INFO* pCfgAnalyseGlobalInfo);
	
	//调用SDK接口获取模块配置
	BOOL getModule(int nChannel, CFG_ANALYSEMODULES_INFO* pCfgAnalyseModulesInfo);
	
	//调用SDK接口获取规则配置
	BOOL getRule(int nChannel, CFG_ANALYSERULES_INFO* pCfgAnalyseRulesInfo);

	//获取某通道支持的所有规则中，最大的规则结构体的大小
// 	int getMaxStuSize(DWORD* pRuleType, int nRuleNum);
	int getMaxStuSize(SCENE_SUPPORT_RULE* pRuleType, int nRuleNum);

protected:
	
public:
	typedef enum DlgType
	{
		dlgNone = 0,
		dlgPreview,
		dlgConfig,
		dlgAlarm,
	};
	DlgType		m_currentDlg;
	int			m_nCurrentChn;
	BOOL		m_bIsSwitchOn;
	CPreview*	m_pdlgPreview;
	CConfig*	m_pdlgConfig;
	CAlarm*		m_pdlgAlarm;
	
	//各个通道订阅的事件类型列表，关闭报警检测用
	std::list<LONG> m_lsAlarmHandle;

private:
	//
	CLogo* m_pdlgLogo;

	//登录句柄
	LLONG m_lLoginHandle;

	//播放句柄
	LLONG m_lRealPlayHandle;

	//分析句柄
	LLONG m_lAnalyzerHandle;

	//实际的设备通道数
	int m_nChnCount;

	//////////////////////////////////////////////////////////////////////////
	//设备配置信息的结构体们

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

	//报警信息节点链表
	lsAlarmInfo m_lstAlarmInfo;

// Construction
public:
	CDemoIVSbDlg(CWnd* pParent = NULL);	// standard constructor

public:
	void ShowDlg(enum DlgType dlgTYPE);

	// callback for receive alarminfo
	static int  __stdcall RealLoadPicCallback (LLONG lAnalyzerHandle, DWORD dwAlarmType, void* pAlarmInfo, BYTE *pBuffer, DWORD dwBufSize, LDWORD dwUser, int nSequence, void *userdata);

	// work thread for preventing from GUI stuck when a mount of channels call CLIENT_RealLoadPic() at same time
	static DWORD _stdcall ThreadStartAlarm(void* pParam);

// Dialog Data
	//{{AFX_DATA(CDemoIVSbDlg)
	enum { IDD = IDD_DEMOIVSB_DIALOG };
	CButton	m_chkSwitch;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDemoIVSbDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CDemoIVSbDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBtnPreview();
	afx_msg void OnBtnConfig();
	afx_msg void OnBtnAlarm();
	afx_msg void OnDestroy();
	afx_msg void OnMainChkSwitch();
	afx_msg void OnMainBtnLogout();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	
	// respond WM_CLEARINFO msg
	LRESULT OnClearAlarmInfo(WPARAM wParam, LPARAM lParam);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DEMOIVSBDLG_H__FCB9A603_26B7_43E9_8657_752A8CD527BB__INCLUDED_)
