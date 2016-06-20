// DeviceListDlg.cpp : implementation file
//

#include "stdafx.h"
#include "IVS_VDemo.h"
#include "DeviceListDlg.h"
#include "LoginDlg.h"
#include "IVS_VDemoDlg.h"
#include "TaskCfg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDeviceListDlg dialog


CDeviceListDlg::CDeviceListDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDeviceListDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDeviceListDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_bDragging = FALSE;
	m_pDragImage = NULL;

	m_hItemDrag = 0;
}

CDeviceListDlg::~CDeviceListDlg()
{
	std::map<DWORD,CFG_TAST_SOURCES*>::iterator it = m_mapSources.begin();
	while(it != m_mapSources.end())
	{
		CFG_TAST_SOURCES* pSource = it->second;
		it++;
		SAFE_DELETE(pSource);
	}
}

void CDeviceListDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDeviceListDlg)
	DDX_Control(pDX, IDC_TREE_DEVICE, m_TreeDevices);
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDeviceListDlg, CDialog)
	//{{AFX_MSG_MAP(CDeviceListDlg)
	ON_BN_CLICKED(IDC_BTN_ADD, OnBtnAdd)
	ON_BN_CLICKED(IDC_BTN_DELETE, OnBtnDelete)
	ON_NOTIFY(TVN_BEGINDRAG, IDC_TREE_DEVICE, OnBegindragTreeDevice)
	ON_NOTIFY(NM_CLICK, IDC_TREE_DEVICE, OnClickTreeDevice)
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDeviceListDlg message handlers

void CDeviceListDlg::OnOK() 
{
	// TODO: Add extra validation here
	
	//CDialog::OnOK();
}

void CDeviceListDlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	//CDialog::OnCancel();
}

void CDeviceListDlg::OnBtnAdd() 
{
	// TODO: Add your control notification handler code here
	std::vector<BYTE> vecDvrType;
	vecDvrType.push_back(VIDEO_IVS_B);
	vecDvrType.push_back(VIDEO_IVS_F);
	vecDvrType.push_back(VIDEO_IVS_PC);
	vecDvrType.push_back(VIDEO_IVS_V);
	CLoginDlg dlg(NULL, &vecDvrType);
	DWORD dwRet = dlg.DoModal();
	if (IDOK == dwRet)
	{
		DWORD hLoginID = dlg.GetLoginHandle();
		HTREEITEM hItem = m_TreeDevices.InsertItem(dlg.GetLoginInfo().szAddress, 0, 0, m_TreeDevices.GetRootItem(), TVI_LAST);
		// 记录设备信息
		CFG_TAST_SOURCES* pSource = new CFG_TAST_SOURCES;
		memset(pSource,0x0,sizeof(CFG_TAST_SOURCES));
		memcpy(&pSource->stRemoteDevice, &dlg.GetLoginInfo(),sizeof(pSource->stRemoteDevice));
		//pSource->nVideoChannel = dlg.GetDevInfo().byChanNum;
		m_mapSources.insert(std::pair<DWORD,CFG_TAST_SOURCES*>((DWORD)hItem, pSource));

		m_TreeDevices.SetItemData(hItem,(DWORD)pSource + 1024);
		for (int i=0; i<dlg.GetDevInfo().byChanNum;i++)
		{
			char szTmp[MAX_PATH] = {0};
			sprintf(szTmp,"%d",i);
			HTREEITEM hChild = m_TreeDevices.InsertItem(szTmp,0,0,hItem,TVI_LAST);
			m_TreeDevices.SetItemData(hChild,i+1);
		}
		m_TreeDevices.Expand(hItem, TVE_EXPAND);
		m_TreeDevices.Expand(m_TreeDevices.GetRootItem(), TVE_EXPAND);
		//m_TreeDevices.EnsureVisible(m_TreeDevices.GetRootItem());

		dlg.Logout(hLoginID);
	}
}

void CDeviceListDlg::OnBtnDelete() 
{
	// TODO: Add your control notification handler code here
	HTREEITEM hItem = m_TreeDevices.GetSelectedItem();
	if (hItem>0 && hItem != m_TreeDevices.GetRootItem())
	{
		DWORD dwRet = m_TreeDevices.GetItemData(hItem);
		if (dwRet < 1024)
		{
			hItem = m_TreeDevices.GetParentItem(hItem);
		}
		m_TreeDevices.DeleteItem(hItem);
	}
}

BOOL CDeviceListDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	g_SetWndStaticText(this);
	
	// TODO: Add extra initialization here
	m_image.Create ( IDB_DEVICETREEIMAGE,16,1,RGB(255,255,255) );

	m_TreeDevices.InitType();
	m_TreeDevices.SetImageList ( &m_image,TVSIL_NORMAL );

	m_TreeDevices.InsertItem(ConvertString("DevicesTree"), 0, 1, TVI_ROOT, TVI_LAST);


	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDeviceListDlg::OnBegindragTreeDevice(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	*pResult = 0;

	//如果是无意拖曳，则放弃操作
	if( (GetTickCount() - m_dwDragStart) < 60 )
		return;
	CWnd* pWnd = GetOwner();
	if (NULL == pWnd)
	{
		return;
	}

	// 根节点不允许拖动
	m_hItemDrag = pNMTreeView->itemNew.hItem;
	if (m_hItemDrag == m_TreeDevices.GetRootItem())
	{
		return;
	}

	if (NULL == m_pDragImage)
	{
		m_pDragImage = m_TreeDevices.CreateDragImage( m_hItemDrag );
		if( !m_pDragImage )
			return;
	}

	m_bDragging = TRUE;

	m_pDragImage->BeginDrag ( 0,CPoint(0,0) );
	CPoint  pt = pNMTreeView->ptDrag;
	char szTmp[MAX_PATH] = {0};
	sprintf(szTmp, "BeginDrag (%d,%d) ",pt.x, pt.y);
	OutputDebugString(szTmp);

	m_pDragImage->DragEnter ( pWnd,pt );  //"this"将拖曳动作限制在该窗口
	SetCapture();
}

void CDeviceListDlg::OnClickTreeDevice(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	//处理无意拖曳
	m_dwDragStart = GetTickCount();
	*pResult = 0;
}

void CDeviceListDlg::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CWnd* pWnd = GetOwner();
	char szTmp[MAX_PATH] = {0};
	if (FALSE == m_bDragging || NULL == pWnd || 0 == m_hItemDrag)
	{
		CDialog::OnLButtonUp(nFlags, point);
		return;
	}
	m_bDragging = FALSE;
	CImageList::DragLeave( pWnd );
	CImageList::EndDrag();
	ReleaseCapture();
	SAFE_DELETE(m_pDragImage);

	CIVS_VDemoDlg* pTestDlg = reinterpret_cast<CIVS_VDemoDlg*>(pWnd);
	CRect rc = pTestDlg->GetTaskDlg()->GetTaskListRect();

	pWnd->ClientToScreen(&point);

	sprintf(szTmp, "OnLButtonUp 2 (%d,%d) ",point.x, point.y);
	OutputDebugString(szTmp);
	sprintf(szTmp, "OnLButtonUp 3 (%d,%d)(%d,%d) ",rc.left, rc.top, rc.right, rc.bottom);
	OutputDebugString(szTmp);
	if (PtInRect(&rc,point))
	{
		DWORD dwRet = m_TreeDevices.GetItemData(m_hItemDrag);
		if (dwRet>1024)
		{
			int nChildCount = 0;
			HTREEITEM hItem = m_TreeDevices.GetChildItem(m_hItemDrag);
			while(hItem) 
			{ 
				nChildCount++;
				hItem = m_TreeDevices.GetNextSiblingItem(hItem);
			}

			CFG_TAST_SOURCES* pSource = reinterpret_cast<CFG_TAST_SOURCES*>(dwRet-1024);
			pTestDlg->GetTaskDlg()->SetOneDeviceInfo(pSource, -1, nChildCount);
		}
		else
		{
			HTREEITEM hParent = m_TreeDevices.GetParentItem(m_hItemDrag);
			DWORD dwParent = m_TreeDevices.GetItemData(hParent);
			CFG_TAST_SOURCES* pSource = reinterpret_cast<CFG_TAST_SOURCES*>(dwParent-1024);
			pTestDlg->GetTaskDlg()->SetOneDeviceInfo(pSource, dwRet-1);
		}
	}

	CDialog::OnLButtonUp(nFlags, point);
}

void CDeviceListDlg::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CWnd* pWnd = GetOwner();
	if (FALSE == m_bDragging || NULL == pWnd)
	{
		CDialog::OnMouseMove(nFlags, point);
		return;
	}
#if 0
	CPoint  pt = point;
	CImageList::DragMove( pt );
#else
	CPoint pt1;
	GetCursorPos(&pt1);
	pWnd->ScreenToClient(&pt1);
	CImageList::DragMove( pt1 );
#endif
	CDialog::OnMouseMove(nFlags, point);
}
