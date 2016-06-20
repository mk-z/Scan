// TargetFilter.cpp : 实现文件
//

#include "stdafx.h"
#include "DemoIVSb.h"
#include "TargetFilter.h"
#include "DemoIVSbDlg.h"
#include "TargetFilterPreview.h"


// CTargetFilter 对话框

IMPLEMENT_DYNAMIC(CTargetFilter, CDialog)

CTargetFilter::CTargetFilter(CWnd* pParent /*=NULL*/)
	: CDialog(CTargetFilter::IDD, pParent)
	, m_pTargetFilterPreview(NULL)
	, m_nChannel(-1)
	, m_nMoudleIndex(0)
	, m_pAnalyseModulesInfo(NULL)
{
}

CTargetFilter::~CTargetFilter()
{
	if (m_pTargetFilterPreview)
	{
		delete m_pTargetFilterPreview;
		m_pTargetFilterPreview = NULL;
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
	ON_BN_CLICKED(IDC_BTN_FILTER_OK, OnBnClickedBtnFilterOk)
	ON_BN_CLICKED(IDC_BTN_FILTER_CANCEL, OnBnClickedBtnFilterCancel)
	ON_CBN_SELCHANGE(IDC_COMBO_FILTER_TYPE, OnCbnSelendcancelComboFilterType)
	ON_CBN_SELCHANGE(IDC_COMBO_FILTER_PATTERN, OnCbnSelendcancelComboFilterPattern)
	ON_BN_CLICKED(IDC_CHECK_RECTANGLE, OnBnClickedCheckRectangle)
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
	

	if (m_pAnalyseModulesInfo == NULL)
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
	// TODO: 在此添加控件通知处理程序代码
	if (m_pAnalyseModulesInfo)
	{
		m_pAnalyseModulesInfo->stuModuleInfo[m_nMoudleIndex].abBySize = true;
		m_pAnalyseModulesInfo->stuModuleInfo[m_nMoudleIndex].bBySize 
			= m_checkLenWidth.GetCheck() == BST_CHECKED ? true : false;
		if (m_checkLenWidth.GetCheck())
		{
			m_pAnalyseModulesInfo->stuModuleInfo[m_nMoudleIndex].bFilterMaxSizeEnable = true;
			m_pAnalyseModulesInfo->stuModuleInfo[m_nMoudleIndex].bFilterMinSizeEnable = true;
		}
		else
		{
			m_pAnalyseModulesInfo->stuModuleInfo[m_nMoudleIndex].bFilterMaxSizeEnable = false;
			m_pAnalyseModulesInfo->stuModuleInfo[m_nMoudleIndex].bFilterMinSizeEnable = false;
		}

		m_pAnalyseModulesInfo->stuModuleInfo[m_nMoudleIndex].nFilterType 
			= (BYTE)(m_comboFilterType.GetItemData(m_comboFilterType.GetCurSel()));
// 		if (m_pAnalyseModulesInfo->stuModuleInfo[m_nMoudleIndex].nFilterType == 1)
// 		{
// 			m_pAnalyseModulesInfo->stuModuleInfo[m_nMoudleIndex].bByArea = true;
// 		}
// 		else
// 		{
// 			m_pAnalyseModulesInfo->stuModuleInfo[m_nMoudleIndex].bByArea = false;
// 		}
		m_pAnalyseModulesInfo->stuModuleInfo[m_nMoudleIndex].bFilterTypeEnable = true;
	}
	
	OnOK();
}

void CTargetFilter::OnBnClickedBtnFilterCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	OnCancel();
}


void CTargetFilter::OnCbnSelendcancelComboFilterType()
{
	// TODO: 在此添加控件通知处理程序代码
// 	int nSel = m_comboFilterType.GetCurSel();
// 	m_pAnalyseModulesInfo->stuModuleInfo[0].nFilterType = m_comboFilterType.GetItemData(nSel);
}

void CTargetFilter::OnCbnSelendcancelComboFilterPattern()
{
	// TODO: 在此添加控件通知处理程序代码
}

void CTargetFilter::OnBnClickedCheckRectangle()
{
	// TODO: 在此添加控件通知处理程序代码
	if (!m_pTargetFilterPreview)
	{
		return;
	}

	if (!m_pTargetFilterPreview->GetSafeHwnd())
	{
		return;
	}

	CGuard guard(&m_pTargetFilterPreview->m_cs);
	if (m_checkLenWidth.GetCheck())
	{
		m_pAnalyseModulesInfo->stuModuleInfo[0].abBySize = true;
		m_pAnalyseModulesInfo->stuModuleInfo[0].bBySize = true;
		m_comboFilterType.EnableWindow(TRUE);
	} 
	else
	{
		m_pAnalyseModulesInfo->stuModuleInfo[0].abBySize = false;
		m_pAnalyseModulesInfo->stuModuleInfo[0].bBySize = false;
		m_comboFilterType.EnableWindow(FALSE);
	}
}

void CTargetFilter::Init(CFG_ANALYSEMODULES_INFO* pAnalyseModulesInfo, int nChannel)
{
	m_nChannel = nChannel;
	m_pAnalyseModulesInfo = pAnalyseModulesInfo;

	if ((!m_pAnalyseModulesInfo->stuModuleInfo[0].stuCalibrateBoxs[0].stuCenterPoint.nX
		 || !m_pAnalyseModulesInfo->stuModuleInfo[0].stuCalibrateBoxs[0].stuCenterPoint.nY))
	{
		m_pAnalyseModulesInfo->stuModuleInfo[0].stuCalibrateBoxs[0].stuCenterPoint.nX = 1000;
		m_pAnalyseModulesInfo->stuModuleInfo[0].stuCalibrateBoxs[0].stuCenterPoint.nY = 1000;
		m_pAnalyseModulesInfo->stuModuleInfo[0].stuFilterMaxSize.nWidth = 800;
		m_pAnalyseModulesInfo->stuModuleInfo[0].stuFilterMaxSize.nHeight = 800;
		m_pAnalyseModulesInfo->stuModuleInfo[0].stuFilterMinSize.nWidth = 500;
		m_pAnalyseModulesInfo->stuModuleInfo[0].stuFilterMinSize.nHeight= 500;

		m_pAnalyseModulesInfo->stuModuleInfo[0].bFilterMaxSizeEnable = true;
		m_pAnalyseModulesInfo->stuModuleInfo[0].bFilterMinSizeEnable = true;
		m_pAnalyseModulesInfo->stuModuleInfo[0].nCalibrateBoxNum = 1;
	}

	m_pTargetFilterPreview = new CTargetFilterPreview();
	
	if (!m_pTargetFilterPreview)
	{
		return ;
	}
	m_pTargetFilterPreview->SetModuleInfo(pAnalyseModulesInfo, m_nChannel);
};

void CTargetFilter::FillData()
{
	if (m_pAnalyseModulesInfo)
	{
		m_comboFilterPattern.AddString(ConvertString("image size"));
		m_comboFilterPattern.SetCurSel(0);
		//:0:"ByLength",1:"ByArea", 2:"ByWidthHeight", 3:"ByRatio": 按照宽高比，宽度除以高度的结果小于某个值或者大于某个值的问题将被过滤掉。
		int nIndex = m_comboFilterType.AddString(ConvertString("width or hight"));
		m_comboFilterType.SetItemData(nIndex, 0);
// 		nIndex = m_comboFilterType.AddString(ConvertString("Area"));
// 		m_comboFilterType.SetItemData(nIndex, 1);
		nIndex = m_comboFilterType.AddString(ConvertString("width and hight"));
		m_comboFilterType.SetItemData(nIndex, 2);

		m_checkLenWidth.SetCheck(m_pAnalyseModulesInfo->stuModuleInfo[m_nMoudleIndex].bBySize);
		if (m_checkLenWidth.GetCheck())
		{
			m_comboFilterType.EnableWindow(TRUE);
		}
		else
		{
			m_comboFilterType.EnableWindow(FALSE);
		}

		for (int i=0; i<m_comboFilterType.GetCount(); ++i)
		{
			int nData = m_comboFilterType.GetItemData(i);
			if (nData == m_pAnalyseModulesInfo->stuModuleInfo[m_nMoudleIndex].nFilterType)
			{
				m_comboFilterType.SetCurSel(i);
				break;
			}
		}
	}
}

void CTargetFilter::ShowView()
{
	CDemoIVSbDlg* pMainDlg = (CDemoIVSbDlg*)AfxGetMainWnd();
	if (pMainDlg)
	{
		if (pMainDlg->getLoginHandle())
		{
			if (pMainDlg->getRealPlayHandle())
			{
				::CLIENT_StopRealPlay(pMainDlg->getRealPlayHandle());
				s_PlayAPI.PLAY_Stop(g_nPlayPort);
				s_PlayAPI.PLAY_CloseStream(g_nPlayPort);
				pMainDlg->setRealPlayHandel(0);
			}

			LLONG m_lPlayID = 0;
			HWND hWnd = m_pTargetFilterPreview->GetSafeHwnd();
			NET_DEVICEINFO* pDevInfo = pMainDlg->getDevInfo();
			int nChnCount = 0;
			if (pDevInfo)
			{
				nChnCount = pDevInfo->byChanNum;
			}

			//Enable stream
			BOOL bOpenRet = s_PlayAPI.PLAY_OpenStream(g_nPlayPort, 0, 0, 1024 * 900);
			if(bOpenRet)
			{
				// 从码流中提取智能分析信息
				BOOL bRet = FALSE;
				bRet = s_PlayAPI.PLAY_RigisterDrawFun(g_nPlayPort, CTargetFilterPreview::DrawTargetFilterCfgProc, 
												(DWORD)m_pTargetFilterPreview);
				//Begin play 
				BOOL bPlayRet = s_PlayAPI.PLAY_Play(g_nPlayPort, hWnd);
				if(bPlayRet)
				{
					//Real-time play 
					m_lPlayID = CLIENT_RealPlay(pMainDlg->getLoginHandle(), m_nChannel, 0);
					if(0 != m_lPlayID)
					{
						pMainDlg->setRealPlayHandel(m_lPlayID);
						//Callback monitor data and then save 
						CLIENT_SetRealDataCallBackEx(m_lPlayID, RealDataCallBackEx, (DWORD)this, 0x1f);
					}
					else
					{
						s_PlayAPI.PLAY_Stop(g_nPlayPort);
						s_PlayAPI.PLAY_CloseStream(g_nPlayPort);
						MessageBox(ConvertString("Fail to play!"), ConvertString("Prompt"));
					}
				}
				else
				{
					s_PlayAPI.PLAY_CloseStream(g_nPlayPort);
				}
			}
		}
	}
};