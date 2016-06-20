
// Client_DemoDlg.h : 头文件
//

#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include "VideoPlayBack.h"
#include "DeviceUpdateDlg.h"



// CClient_DemoDlg 对话框
class CClient_DemoDlg : public CDialog
{
// 构造
public:
	CClient_DemoDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_CLIENT_DEMO_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;
	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedStaticText2();
	afx_msg void OnTimer(UINT_PTR nIDEvent);

	static void  LoginDevice(LPVOID DBClickIp);   //登录设备
	static int WINAPI ConnEventCB(long lHandle, eJNetEvent eType,int iDataType,void* pEventData,int iDataLen,void* pUserParam);
	static BOOL WINAPI StreamCB(long lHandle, LPBYTE pBuff,DWORD dwRevLen,void* pUserParam);
    static BOOL __stdcall OnTalkStream(long lHandle, LPBYTE pBuff,DWORD dwRevLen,void* pUserParam);

	BOOL VideoTalk(int index);     //对讲功能
	static void CALLBACK PickAudioCallBack(const BYTE* pBuffer, DWORD dwBufSize, void* pUserData);
	
	BOOL OpenVideoStream(int iIndex); //打开实时流
	BOOL HiPlayerOpenVideoStream(int iIndex);
	void GetDevCap(int nIndex);       //获取设备能力集

	BOOL PreTranslateMessage(MSG* pMsg); //按钮按下和松开
	void ControlPtz(int iCmd);               //设置云台

	void EnablePTZ();						//云台不可用
	void ShowPtz();                       //云台可用
	void SubmitAlarm(int nIndex, void *pData);

public:
	void initComboxScreenNum();            
	void ArrangeOutputs(int iNumber);     //分割窗口
	void Hide_Window(int index);         //隐藏除了 index 的窗口 
	void Show_Window(int iNumber);      //显示 iNumber 个窗口
	void Set_StreamType(int index , int streamType);    //设置码流


	void GetAlarmData(int iAlarm, int iAction, CStringArray &strArray, int iIndex);
	void GetAlarmDataEnglish(int iAlarm, int iAction, CStringArray &strArray);
	void InitINIfile();
	int m_iDemoMode;

public:

	int m_iCurWndNum;      //窗口数
	int m_iCurWndIndex;   //窗口索引
	int m_iCurScreenWidth;  
	int m_iCurScreenHeight;
	int m_iDownIndex;
	bool m_bDragDown;
	bool m_bWarningMax;
	bool m_bDragFile;  //是否能拖动文件  只能在回放时拖动
	BOOL m_bDrag;
	int m_iLoginOk;
	long m_vSnapHandle;


	HTREEITEM m_hRoot;
	HTREEITEM m_hItem;
	HTREEITEM m_hDeleteItem;
	HTREEITEM     m_hBeginDrag;
	HTREEITEM     m_hDragItem;  //正在拖动的节点
	
	COleDateTime m_cTime;
	CTreeCtrl m_MainTree;
	CStatic m_ShowTime;
	CComboBox m_comScreenNum;
	CImageList*   m_pDragImage;      //拖动时显示的图象列表
	CString m_strDragItemText;
	CString m_strSelItemText;
	CListCtrl m_ListWarning;
	CImageList m_imageList;
	CButton m_bUp;
	CButton m_bLeft;
	CButton m_bRight;
	CButton m_bDown;
	CButton m_bAuto;
	CButton m_ScanJIa;
	CButton m_ScanJian;
	CComboBox m_combJD;
	CButton m_StartLight;
	CButton m_StartBrush;

	

	CDeviceUpdateDlg m_upgDlg;
	CVideoPlayBack m_videoPlayBack;

	afx_msg void OnNMRClickTreeMain(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnCbnSelchangeComboScreenNum();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnNMDblclkTreeMain(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDestroy();
	afx_msg void OnClose();
	afx_msg void OnBnClickedButtonPlayback();
	afx_msg void OnBnClickedButtonWatch();
	afx_msg void OnBnClickedCheckStartlight();
	afx_msg void OnBnClickedCheckStartbrush();
	afx_msg void OnLvnColumnclickListWarning(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnTvnSelchangedTreeMain(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnMenuDelete();
	afx_msg void OnBnClickedButtonRecode();
	afx_msg void OnTvnBegindragTreeMain(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedButtonCloseallvideo();
	afx_msg void OnMenuAttribute();
	afx_msg void OnNMRClickListWarning(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnMenuDellist();
	afx_msg void OnBnClickedButtonClearwarning();
	afx_msg void OnBnClickedButtonAllfullup();
	afx_msg void OnNMClickTreeMain(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButtonElse();
	afx_msg void OnLocalattribute();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnDropFiles(HDROP hDropInfo);


	void SetTreeIcon();
	void SaveLoginDevice();
	void DeleteDevice(int index);
	int GetDragItemIndex(CString strNode);   //得到正在拖拽的节点的播放成功的索引
	int GetDragToScreenNum(int iX, int iY);   //得到拖拽的目的窗口
	void RecoverToOldScreen();
	void HideButton(int iFlag); // 菜单栏按钮是否启用
	void RegDrawCallBackEx(int iChannel, HWND hwnd);
	afx_msg void OnMenuDeviceSnap();




	bool area_cross(JPoint region[], JPoint pos);
	int getBlockValue(char *data, int len, int isBit, int blockIndex);
	int	GetDevIndex(long lHandle);
	int	NoVideoSnap(int nIndex, char *pBuff, DWORD dwRevLen);


	

	JDomeCtrlPtz	m_domeCtrlPtz;
	
};
