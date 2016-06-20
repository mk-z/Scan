#ifndef __DLG_QUERY_HEADER__
#define __DLG_QUERY_HEADER__

// CDlgQuery 对话框
class CDrawFrame;

class CDlgQuery : public CDialog
{
	DECLARE_DYNAMIC(CDlgQuery)

public:
	CDlgQuery(CWnd* pParent = NULL);   // 标准构造函数
	CDlgQuery(int nChannelCount, CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgQuery();

	void InitQueryDlg(int nChanCount);
	void UninitQueryDlg();
	void ShowListResult( NET_OUT_DOFINDNUMBERSTAT &FindNumber);
	void ShowListResultRange(NET_OUT_DOFINDNUMBERSTAT &FindNumber, int nIndex, int nCount);
	void ResizeWnd();
	void Draw(NET_OUT_DOFINDNUMBERSTAT &FindNumber,int nIndexStart, int nCount);
	void InitCommboxDate();
	void ShowPreNextEnable();

// 对话框数据
	enum { IDD = IDD_QUERY };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedBtnPreview();
	afx_msg void OnBnClickedBtnNext();
	afx_msg void OnBnClickedQueryStart();
	afx_msg LRESULT OnSelectRecord(WPARAM, LPARAM);

private:
	/// \var CDateTimeCtrl	m_dtpStartTime
	/// 开始时间点控件
	CDateTimeCtrl	m_dtpStartTime;
	/// \var CDateTimeCtrl	m_dtpStartDate
	/// 开始日期点控件
	CDateTimeCtrl	m_dtpStartDate;
	/// \var CDateTimeCtrl	m_dtpEndTime
	/// 结束时间点控件
	CDateTimeCtrl	m_dtpEndTime;
	/// \var CDateTimeCtrl	m_dtpEndDate
    /// 结束日期控件
	CDateTimeCtrl	m_dtpEndDate;
	/// \var CComboBox	    m_cmbChannel
	/// 通道选择控件
	CComboBox	    m_cmbChannel;
	/// \var CComboBox       m_cmbTypes
	/// 粒度选择控件
	CComboBox       m_cmbTypes;
	/// \var CEdit  m_editBegin
	/// 查询开始序号控件
	CEdit           m_editBegin;
	/// \var  CEdit m_editCount
	/// 查询条目控件
	CEdit           m_editCount;
	/// \var int    m_nChannelCount
	/// 设备通道数总数
	int             m_nChannelCount;
	/// \var CListCtrl  m_listResult
    /// 返回结果信息
	CListCtrl       m_listResult;
	CDrawFrame * m_dlgDrawFrame;
	NET_OUT_DOFINDNUMBERSTAT m_stuDoFindNumberStat_out;
	//此索引用于查询时，分页显示
	int m_dwIndexStart;
	//此索引用于查询时，分页显示
	int m_dwIndexEnd;
	//用于记录上一个选中的项

	// 用于表示分页的大小
	int m_nPageNum;
};
#endif