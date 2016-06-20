// TargetFilter.cpp : 实现文件
//

#include "stdafx.h"
#include "DemoIVSPC.h"
#include "TargetFilter.h"
#include "DemoIVSPCDlg.h"
#include "TargetFilterPreview.h"


// CTargetFilter 对话框

IMPLEMENT_DYNAMIC(CTargetFilter, CDialog)

CTargetFilter::CTargetFilter(CWnd* pParent /*=NULL*/)
	: CDialog(CTargetFilter::IDD, pParent)
	, m_pTargetFilterPreview(NULL)
	, m_nChannel(-1)
	, m_nMoudleIndex(0)
{
	m_pStObjectFileter = new CFG_OBJECT_SIZEFILTER_INFO;
	if (m_pStObjectFileter != NULL)
	{
		memset(m_pStObjectFileter, 0, sizeof(CFG_OBJECT_SIZEFILTER_INFO));
	}
}

CTargetFilter::~CTargetFilter()
{
	if (m_pTargetFilterPreview)
	{
		delete m_pTargetFilterPreview;
		m_pTargetFilterPreview = NULL;
	}

	if (m_pTargetFilterPreview != NULL)
	{
		delete m_pTargetFilterPreview;
	}
}

void CTargetFilter::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_FILTER_PATTERN, m_comboFilterPattern);
	DDX_Control(pDX, IDC_COMBO_FILTER_TYPE, m_comboFilterType);
	DDX_Control(pDX, IDC_CHECK_RECTANGLE, m_checkLenWidth);
}


BEGIN_MESSAGE_MAP(CTargetFilter, CDialog)
	ON_BN_CLICKED(IDC_BTN_FILTER_OK, CTargetFilter::OnBnClickedBtnFilterOk)
	ON_BN_CLICKED(IDC_BTN_FILTER_CANCEL, CTargetFilter::OnBnClickedBtnFilterCancel)
END_MESSAGE_MAP()


// CTargetFilter 消息处理程序

BOOL CTargetFilter::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	g_SetWndStaticText(this);
	CRect rt;
	GetDlgItem(IDC_STATIC_VEDIO_VIEW)->GetWindowRect(&rt);
	ScreenToClient(&rt);
	if (m_pTargetFilterPreview)
	{
		m_pTargetFilterPreview->Create(NULL,
			NULL,
			WS_CHILD | WS_VISIBLE,
			CRect(0, 0, 0, 0),
			this,
			5001);
		m_pTargetFilterPreview->MoveWindow(&rt);
		m_pTargetFilterPreview->ShowWindow(SW_SHOW);
	}
	

	if (m_pStObjectFileter == NULL)
	{
		return TRUE;
	}

	FillData();

	ShowView();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CTargetFilter::OnBnClickedBtnFilterOk()
{
	if (m_pStObjectFileter)
	{
		m_pStObjectFileter->stSizeFilter.bBySize
			= m_checkLenWidth.GetCheck() == BST_CHECKED ? true : false;
		m_pStObjectFileter->stSizeFilter.bFilterType 
			= (BYTE)(m_comboFilterType.GetItemData(m_comboFilterType.GetCurSel()));
	}
	
	OnOK();
}

void CTargetFilter::OnBnClickedBtnFilterCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	OnCancel();
}


void CTargetFilter::Init(CFG_OBJECT_SIZEFILTER_INFO* pStObjectFileter, int nChannel)
{
	m_nChannel = nChannel;

	memcpy(m_pStObjectFileter, pStObjectFileter, sizeof(CFG_OBJECT_SIZEFILTER_INFO));

	m_pTargetFilterPreview = new CTargetFilterPreview();
	if (!m_pTargetFilterPreview)
	{
		return ;
	}
	m_pTargetFilterPreview->SetModuleInfo(m_pStObjectFileter, m_nChannel);
};

void CTargetFilter::FillData()
{
	if (m_pStObjectFileter)
	{
		m_comboFilterPattern.AddString(ConvertString("image size"));
		m_comboFilterPattern.SetCurSel(0);
		//:0:"ByLength",1:"ByArea", 2:"ByWidthHeight", 3:"ByRatio": 按照宽高比，宽度除以高度的结果小于某个值或者大于某个值的问题将被过滤掉。
		int nIndex = m_comboFilterType.AddString(ConvertString("width or hight"));
		m_comboFilterType.SetItemData(nIndex, 0);
		nIndex = m_comboFilterType.AddString(ConvertString("Area"));
		m_comboFilterType.SetItemData(nIndex, 1);
		nIndex = m_comboFilterType.AddString(ConvertString("width and hight"));
		m_comboFilterType.SetItemData(nIndex, 2);

		m_checkLenWidth.SetCheck(m_pStObjectFileter->stSizeFilter.bBySize);
		for (int i=0; i<m_comboFilterType.GetCount(); ++i)
		{
			int nData = m_comboFilterType.GetItemData(i);
			if (nData == m_pStObjectFileter->stSizeFilter.bFilterType)
			{
				m_comboFilterType.SetCurSel(i);
				break;
			}
		}
	}
}

void CTargetFilter::ShowView()
{
	CDemoIVSPCDlg* pMainDlg = (CDemoIVSPCDlg*)AfxGetMainWnd();
	if (pMainDlg)
	{
		if (pMainDlg->GetLoginHandle())
		{
			if (pMainDlg->GetRealPlayHandle())
			{
				::CLIENT_StopRealPlay(pMainDlg->GetRealPlayHandle());
				g_PlayAPI.PLAY_Stop(g_nPlayPort);
				g_PlayAPI.PLAY_CloseStream(g_nPlayPort);
				pMainDlg->SetRealPlayHandel(0);
			}

			LLONG m_lPlayID = 0;
			HWND hWnd = m_pTargetFilterPreview->GetSafeHwnd();
			NET_DEVICEINFO* pDevInfo = pMainDlg->GetDevInfo();
			int nChnCount = 0;
			if (pDevInfo)
			{
				nChnCount = pDevInfo->byChanNum;
			}

			//Enable stream
			BOOL bOpenRet = g_PlayAPI.PLAY_OpenStream(g_nPlayPort, 0, 0, 1024 * 900);
			if(bOpenRet)
			{
				// 从码流中提取智能分析信息
				BOOL bRet = FALSE;
				bRet = g_PlayAPI.PLAY_RigisterDrawFun(g_nPlayPort, CTargetFilterPreview::DrawTargetFilterCfgProc, 
												(DWORD)m_pTargetFilterPreview);
				//Begin play 
				BOOL bPlayRet = g_PlayAPI.PLAY_Play(g_nPlayPort, hWnd);
				if(bPlayRet)
				{
					//Real-time play 
					m_lPlayID = CLIENT_RealPlay(pMainDlg->GetLoginHandle(), m_nChannel, 0);
					if(0 != m_lPlayID)
					{
						pMainDlg->SetRealPlayHandel(m_lPlayID);
						//Callback monitor data and then save 
						CLIENT_SetRealDataCallBackEx(m_lPlayID, RealDataCallBackEx, (LDWORD)this, 0x1f);
					}
					else
					{
						g_PlayAPI.PLAY_Stop(g_nPlayPort);
						g_PlayAPI.PLAY_CloseStream(g_nPlayPort);
						int x = ::CLIENT_GetLastError();
						MessageBox(ConvertString(_T("Fail to play!")), ConvertString("Prompt"));
					}
				}
				else
				{
				     g_PlayAPI.PLAY_CloseStream(g_nPlayPort);
				}
			}
		}
	}
};