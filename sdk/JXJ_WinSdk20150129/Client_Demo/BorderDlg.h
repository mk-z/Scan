#pragma once


// CBorderDlg 对话框

class CBorderDlg : public CDialog
{
	DECLARE_DYNAMIC(CBorderDlg)

public:
	CBorderDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CBorderDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG_BORDERDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	void DrewWinBorder();
	afx_msg void OnPaint();
};
