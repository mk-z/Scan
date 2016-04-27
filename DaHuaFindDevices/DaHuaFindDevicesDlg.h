
// DaHuaFindDevicesDlg.h : 头文件
//

#pragma once
#include "afxcmn.h"

namespace DH
{
#include "DHVideoServer/dhnetsdk.h"
}


#include "JXJVideoServer/JNetSDK.h"
#include "JXJVideoServer/mb_api.h"


//查询设备
typedef struct queryDevConfig
{
	char				dst_id[MB_SERIAL_LEN];
	j_Device_T			stDev;
}DevConfig;

// CDaHuaFindDevicesDlg 对话框
class CDaHuaFindDevicesDlg : public CDialogEx
{
// 构造
public:
	CDaHuaFindDevicesDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_DAHUAFINDDEVICES_DIALOG };

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
	afx_msg void OnBnClickedButton1();
	CListCtrl m_list;
	afx_msg void OnBnClickedButton2();	
	static LLONG  CALLBACK SearchDevicesCB1(DH::DEVICE_NET_INFO_EX *pDevNetInfo, void *pUserData);
	static int CALLBACK CDaHuaFindDevicesDlg::fcbJMBNotify(long lHandle, DWORD dwPortocol, int iErr, int iMsgID, LPCTSTR lpszDstID, void* pData, int iDataLen, void* pUserParam);
	afx_msg void OnBnClickedButton3();

	DevConfig m_devConfig;
	CString GetDeviceType(int i);
};
