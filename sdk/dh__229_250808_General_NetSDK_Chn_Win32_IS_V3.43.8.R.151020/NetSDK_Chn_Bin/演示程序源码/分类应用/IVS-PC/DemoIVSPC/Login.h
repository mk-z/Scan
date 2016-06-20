
// 本窗口类用于登录IVS-B设备，输入设备IP、端口号、用户名、用户密码；
// 返回设备的登录句柄

#if !defined(AFX_LOGIN_H__FA603AD0_C268_4383_8AA5_B9B59FA350D9__INCLUDED_)
#define AFX_LOGIN_H__FA603AD0_C268_4383_8AA5_B9B59FA350D9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CLogin : public CDialog
{
public:
	CLogin(CWnd* pParent = NULL);   // standard constructor

	enum { IDD = IDD_LOGIN };

	inline LONG GetLoginHandle(){ return m_lLongHandle;}

	inline NET_DEVICEINFO* GetNetDeviceInfo(){return &m_stuNetDevInfo;}

	CIPAddressCtrl	m_ctrlIP;
	
	//{{AFX_VIRTUAL(CLogin)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CLogin)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	LLONG m_lLongHandle;
	NET_DEVICEINFO m_stuNetDevInfo;
};


#endif // !defined(AFX_LOGIN_H__FA603AD0_C268_4383_8AA5_B9B59FA350D9__INCLUDED_)
