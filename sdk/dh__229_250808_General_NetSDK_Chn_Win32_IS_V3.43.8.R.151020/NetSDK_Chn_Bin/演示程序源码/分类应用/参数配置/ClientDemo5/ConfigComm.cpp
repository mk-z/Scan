// ConfigComm.cpp : implementation file
//

#include "stdafx.h"
#include "ClientDemo5.h"
#include "ConfigComm.h"
#include "ClientDemo5Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CConfigComm dialog


CConfigComm::CConfigComm(CWnd* pParent /*=NULL*/)
	: CDialog(CConfigComm::IDD, pParent)
{
	//{{AFX_DATA_INIT(CConfigComm)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_nCur232 = -1;
	m_nCur485 = -1;
	m_nChannelCount485 = -1;
	m_nCommCount232 = -1;
}


void CConfigComm::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CConfigComm)
	DDX_Control(pDX, IDC_COMBO_PARITY485, m_ctlParity485);
	DDX_Control(pDX, IDC_COMBO_BAUD485, m_ctlBaud485);
	DDX_Control(pDX, IDC_COMBO_STOPBIT485, m_ctlStopBit485);
	DDX_Control(pDX, IDC_COMBO_DATABIT485, m_ctlData485);
	DDX_Control(pDX, IDC_COMBO_PROTOCOL485, m_ctlProtocal485);
	DDX_Control(pDX, IDC_COMBO_485COM, m_ctlCom485);
	DDX_Control(pDX, IDC_COMBO_PARITY232, m_ctlCommParity);
	DDX_Control(pDX, IDC_COMBO_BAUD232, m_ctlCommBaud);
	DDX_Control(pDX, IDC_COMBO_STOPBIT232, m_ctlCommStopBit);
	DDX_Control(pDX, IDC_COMBO_DATABIT232, m_ctlCommData);
	DDX_Control(pDX, IDC_COMBO_FUNCTION232, m_ctlCommFun);
	DDX_Control(pDX, IDC_COMBO_232COM, m_ctlCom232);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CConfigComm, CDialog)
	//{{AFX_MSG_MAP(CConfigComm)
	ON_BN_CLICKED(IDC_BUTTON_APPLY, OnButtonApply)
	ON_BN_CLICKED(IDC_BUTTON_READALL, OnButtonReadall)
	ON_CBN_SELCHANGE(IDC_COMBO_232COM, OnSelchangeCombo232com)
	ON_CBN_SELCHANGE(IDC_COMBO_485COM, OnSelchangeCombo485com)
	ON_WM_CANCELMODE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CConfigComm message handlers

//Save
void CConfigComm::OnButtonApply() 
{
	// TODO: Add your control notification handler code here
	if(-1 != m_ctlCom232.GetCurSel() || -1 != m_ctlCom485.GetCurSel())
	{
		SaveComm232Info(m_nCur232);
		SaveComm485Info(m_nCur485);
		//Call father window to save data
		((CClientDemo5Dlg*)AfxGetMainWnd())->SetCommConfigInfo(&m_CommInfo, m_nCur485);
	}
	else // 表示(232,485)都没有获取到数据
	{
		MessageBox(ConvertString("Input error!"), ConvertString("Prompt"));
	}
}

//Read
void CConfigComm::OnButtonReadall() 
{
	// TODO: Add your control notification handler code here
	//Clear
	CleanAll();
	//Call father window to read data 
	((CClientDemo5Dlg*)AfxGetMainWnd())->GetCommConfigInfo();
}

/*
 *	Function：Display COM information
 *	Input parameter：
 *	pCommInfo：COM configuration structure 
 *	nCommCount：COm amount
 *	nChannelCount：Channel amount 
 */
void CConfigComm::InitDlgInfo(DEV_COMM_CFG_EX *pCommInfo, BYTE nCommCount, int nChannelCount)
{
	if(pCommInfo != NULL)
	{
		m_CommInfo = *pCommInfo;
		//Set 232 COM dropdown menu 
		m_ctlCom232.ResetContent();
		CString strCom;
		int i =0;
		int nIndex = 0;
		
		m_nCommCount232 = nCommCount;

		for (i = 0; i < m_nCommCount232; i++)
		{
			strCom.Format("COM %d", i+1);
			nIndex = m_ctlCom232.AddString(strCom);
			m_ctlCom232.SetItemData(nIndex,i);
		}
		
		//Set decoder dropdown menu 
		m_ctlCom485.ResetContent();
		CString strDecoder;
		
		m_nChannelCount485 = nChannelCount ;
	
		for (i = 0; i < m_nChannelCount485; i++)
		{
			strDecoder.Format("Decoder %d", i+1);
			nIndex = m_ctlCom485.AddString(strDecoder);
			m_ctlCom485.SetItemData(nIndex,i);
		}


		//Set fucntion dropdown menu 
		m_ctlCommFun.ResetContent();
		int nCount = pCommInfo->dw232FuncNameNum > DH_MAX_232FUNCS ? DH_MAX_232FUNCS: pCommInfo->dw232FuncNameNum;
		for (i = 0; i < nCount; i++)
		{
			nIndex = m_ctlCommFun.AddString((char *)(pCommInfo->s232FuncName[i]));
			m_ctlCommFun.SetItemData(nIndex,i);
		}

		//Set protocol dropdown menu 
		m_ctlProtocal485.ResetContent();
		nCount = pCommInfo->dwDecProListNum > DH_MAX_DECPRO_LIST_SIZE ? DH_MAX_DECPRO_LIST_SIZE: pCommInfo->dwDecProListNum;
		for (i = 0; i < nCount; i++)
		{
			nIndex = m_ctlProtocal485.AddString((char *)(pCommInfo->DecProName[i]));
			m_ctlProtocal485.SetItemData(nIndex,i);
		}

		if (m_ctlCom232.GetCount() > 0)
		{
			m_ctlCom232.SetCurSel(0);
			OnSelchangeCombo232com();
		}
		if (m_ctlCom485.GetCount() > 0)
		{
			m_ctlCom485.SetCurSel(0);
			OnSelchangeCombo485com();
		}
	}
}

//232 COM switch 
void CConfigComm::OnSelchangeCombo232com() 
{
	// TODO: Add your control notification handler code here
	int nIndex = m_ctlCom232.GetCurSel();
	if(CB_ERR != nIndex)
	{
		int nNum = (int)m_ctlCom232.GetItemData(nIndex);
		
		//First save 232 COM information 
		SaveComm232Info(m_nCur232);
		
		//Display 232 COM corresponding information
		m_ctlCommFun.SetCurSel(m_CommInfo.st232[nNum].byFunction);
		m_ctlCommData.SetCurSel(m_CommInfo.st232[nNum].struComm.byDataBit);
		m_ctlCommStopBit.SetCurSel(m_CommInfo.st232[nNum].struComm.byStopBit);
		m_ctlCommBaud.SetCurSel(m_CommInfo.st232[nNum].struComm.byBaudRate - 2); // 与设备端保持一致，去掉0：300，1：600两个选项
		m_ctlCommParity.SetCurSel(m_CommInfo.st232[nNum].struComm.byParity);
		
		m_nCur232 = nNum;
	}
}

//485 COM switch 
void CConfigComm::OnSelchangeCombo485com() 
{
	// TODO: Add your control notification handler code here
	int nIndex = m_ctlCom485.GetCurSel();
	if(CB_ERR != nIndex)
	{
		int nNum = (int)m_ctlCom485.GetItemData(nIndex);
		
		//First save 485 COM information 
		SaveComm485Info(m_nCur485);
		
		//Display 485 COM correponding information 
		m_ctlProtocal485.SetCurSel(m_CommInfo.stDecoder[nNum].wProtocol);
		m_ctlData485.SetCurSel(m_CommInfo.stDecoder[nNum].struComm.byDataBit);
		m_ctlStopBit485.SetCurSel(GetComm485Sel(m_CommInfo.stDecoder[nNum].struComm.byStopBit));

		m_ctlBaud485.SetCurSel(m_CommInfo.stDecoder[nNum].struComm.byBaudRate - 2); // 与设备端保持一致，去掉0：300，1：600两个选项
		m_ctlParity485.SetCurSel(m_CommInfo.stDecoder[nNum].struComm.byParity);
		SetDlgItemInt(IDC_EDIT_ADDR485, m_CommInfo.stDecoder[nNum].wDecoderAddress);
		
		m_nCur485 = nNum;
	}
}

//Save 232 COM information 
void CConfigComm::SaveComm232Info(int nNum)
{
	if(-1 < nNum)
	{
		m_CommInfo.st232[nNum].byFunction = m_ctlCommFun.GetCurSel();
		m_CommInfo.st232[nNum].struComm.byDataBit = m_ctlCommData.GetCurSel();
		m_CommInfo.st232[nNum].struComm.byStopBit = m_ctlCommStopBit.GetCurSel();
		m_CommInfo.st232[nNum].struComm.byBaudRate = m_ctlCommBaud.GetCurSel() + 2; // 与设备端保持一致，要在sdk内部得到正确的波特率，需+2
		m_CommInfo.st232[nNum].struComm.byParity = m_ctlCommParity.GetCurSel();
	}
}

//Save 485 COM information 
void CConfigComm::SaveComm485Info(int nNum)
{
	if(-1 < nNum)
	{
		m_CommInfo.stDecoder[nNum].wProtocol = m_ctlProtocal485.GetCurSel();
		m_CommInfo.stDecoder[nNum].struComm.byDataBit = m_ctlData485.GetCurSel();
		m_CommInfo.stDecoder[nNum].struComm.byStopBit = m_ctlStopBit485.GetItemData(m_ctlStopBit485.GetCurSel());
		m_CommInfo.stDecoder[nNum].struComm.byBaudRate = m_ctlBaud485.GetCurSel() + 2; // 与设备端保持一致，要在sdk内部得到正确的波特率，需+2
		m_CommInfo.stDecoder[nNum].struComm.byParity = m_ctlParity485.GetCurSel();
		m_CommInfo.stDecoder[nNum].wDecoderAddress = GetDlgItemInt(IDC_EDIT_ADDR485);
	}
}

//Clear information 
void CConfigComm::CleanAll()
{
	m_ctlCom232.SetCurSel(-1);
	m_ctlCommFun.SetCurSel(-1);
	m_ctlCommData.SetCurSel(-1);
	m_ctlCommStopBit.SetCurSel(-1);
	m_ctlCommBaud.SetCurSel(-1);
	m_ctlCommParity.SetCurSel(-1);
	
	m_ctlCom485.SetCurSel(-1);
	m_ctlProtocal485.SetCurSel(-1);
	m_ctlData485.SetCurSel(-1);
	m_ctlStopBit485.SetCurSel(-1);
	m_ctlBaud485.SetCurSel(-1);
	m_ctlParity485.SetCurSel(-1);
	
	SetDlgItemText(IDC_EDIT_ADDR485,"");
	
	m_nCur232 = -1;
	m_nCur485 = -1;
	m_nCommCount232 = -1;
	m_nChannelCount485 = -1;
}

BOOL CConfigComm::OnInitDialog() 
{
	CDialog::OnInitDialog();
	g_SetWndStaticText(this);
	// TODO: Add extra initialization here
	ConvertComboBox(m_ctlParity485);
	ConvertComboBox(m_ctlCommParity);

	m_ctlStopBit485.ResetContent();

	int index = m_ctlStopBit485.AddString("1");
	m_ctlStopBit485.SetItemData(index, 0);

	index = m_ctlStopBit485.AddString("1.5");
	m_ctlStopBit485.SetItemData(index, 1);

	index = m_ctlStopBit485.AddString("2");
	m_ctlStopBit485.SetItemData(index, 2);

	m_ctlStopBit485.SetCurSel(-1);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CConfigComm::OnCancelMode() 
{
	CDialog::OnCancelMode();
	
	// TODO: Add your message handler code here
	
}

int	 CConfigComm::GetComm485Sel(int nStopBit)
{
	for (int i = 0; i < m_ctlStopBit485.GetCount(); ++i)
	{
		if (m_ctlStopBit485.GetItemData(i) == nStopBit)
		{
			return i;
		}
	}
	return -1;
};
