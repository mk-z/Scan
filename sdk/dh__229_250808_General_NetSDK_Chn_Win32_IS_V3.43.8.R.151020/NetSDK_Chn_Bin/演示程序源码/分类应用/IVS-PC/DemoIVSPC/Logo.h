#if !defined(AFX_LOGO_H__AFAAEBD9_517D_4CB3_938E_72669AC6FE44__INCLUDED_)
#define AFX_LOGO_H__AFAAEBD9_517D_4CB3_938E_72669AC6FE44__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CLogo : public CDialog
{
// Construction
public:
	CLogo(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CLogo)
	enum { IDD = IDD_SUBDLG_LOGO };
	//}}AFX_DATA

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	//{{AFX_MSG(CLogo)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	void stepIt();

private:
	CProgressCtrl	m_ctrlProgress;
};

#endif // !defined(AFX_LOGO_H__AFAAEBD9_517D_4CB3_938E_72669AC6FE44__INCLUDED_)
