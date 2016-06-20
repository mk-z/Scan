// Task.cpp : implementation file
//

#include "stdafx.h"
#include "IVS_VDemo.h"
#include "TaskCfg.h"
#include "ProfileCfg.h"
#include "IVS_VDemoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTaskCfg dialog


CTaskCfg::CTaskCfg(CWnd* pParent /*=NULL*/)
	: CDialog(CTaskCfg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTaskCfg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}
CTaskCfg::CTaskCfg(CDialog* pProfileDlg, CWnd* pParent /*= NULL*/)
	: CDialog(CTaskCfg::IDD, pParent),m_pProfileDlg(reinterpret_cast<CProfileCfg*>(pProfileDlg))
{
	m_pTaskCfg = NULL;
}


CTaskCfg::~CTaskCfg()
{
	if (NULL != m_pTaskCfg)
	{
		UnInitTaskConfig(&m_pTaskCfg);
		m_pTaskCfg = NULL;
	}
}

void CTaskCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTaskCfg)
	DDX_Control(pDX, IDC_COMBO_PROFILENAME, m_ComboProfileName);
	DDX_Control(pDX, IDC_COMBO_DURATION, m_ComboDuration);
	DDX_Control(pDX, IDC_COMBO_TASKLIST, m_ComboTaskList);
	DDX_Control(pDX, IDC_LIST_SUBTASK, m_LstSubTask);
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTaskCfg, CDialog)
	//{{AFX_MSG_MAP(CTaskCfg)
	ON_BN_CLICKED(IDC_BTN_ADD_TASK, OnBtnAddTask)
	ON_BN_CLICKED(IDC_BTN_GET_TASK, OnBtnGetTask)
	ON_BN_CLICKED(IDC_BTN_SET_TASK, OnBtnSetTask)
	ON_BN_CLICKED(IDC_BTN_MODIFY_TASK, OnBtnModifyTask)
	ON_BN_CLICKED(IDC_BTN_DELETE_TASK, OnBtnDeleteTask)
	ON_CBN_SELCHANGE(IDC_COMBO_TASKLIST, OnSelchangeComboTaskList)
	ON_BN_CLICKED(IDC_BTN_CLEAR_ITEM, OnBtnClearItem)
	ON_BN_CLICKED(IDC_BTN_DEL_ITEM, OnBtnDeleteItem)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTaskCfg message handlers

void CTaskCfg::OnOK() 
{
	// TODO: Add extra validation here
	
	//CDialog::OnOK();
}

void CTaskCfg::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	//CDialog::OnCancel();
}

BOOL CTaskCfg::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	int nIndex = m_LstSubTask.InsertColumn(0,ConvertString("NO."),LVCFMT_LEFT, 150);
	nIndex = m_LstSubTask.InsertColumn(nIndex+1, ConvertString("DeviceIP"), LVCFMT_LEFT, 250);
	nIndex = m_LstSubTask.InsertColumn(nIndex+1, ConvertString("ChannelID"), LVCFMT_LEFT, 250);
	m_LstSubTask.ModifyStyle(0, LVS_REPORT | LVS_SHOWSELALWAYS | LVS_SINGLESEL);
	m_LstSubTask.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	m_ComboDuration.InsertString(0,"10");
	m_ComboDuration.InsertString(1,"30");
	m_ComboDuration.InsertString(2,"60");
	m_ComboDuration.SetCurSel(0);

	g_SetWndStaticText(this);

	return TRUE;
}

#if 0
void CTaskCfg::ClearComboBox(CComboBox &stComboBox)
{
	stComboBox.Clear();
	{
		int n = stComboBox.GetCount();
		for (int i=0; i<n; i++)
		{
			stComboBox.DeleteString(0);
		}
	}
}
#endif
BOOL CTaskCfg::InitTask()
{
	if (NULL == m_pProfileDlg)
	{
		return FALSE;
	}

	ClearComboBox(m_ComboProfileName);
#if 1
	CIVS_VDemoDlg* pParent =  reinterpret_cast<CIVS_VDemoDlg*>(GetOwner());

	std::vector<std::string> v;
	pParent->GetCmdMembers(v, CFG_CMD_VIDEODIAGNOSIS_PROFILE, pParent->GetMaxProfiles());
	for (int i=0; i<v.size(); i++)
	{
		m_ComboProfileName.InsertString(i, v[i].c_str());
	}
#else
	if (NULL != m_pProfileDlg->GetTreeData().pChild)
	{
		m_ComboProfileName.InsertString(0, m_pProfileDlg->GetTreeData().pChild->strName.c_str());
		struct STtreeData* pBrother = m_pProfileDlg->GetTreeData().pChild->pBrother;
		while(NULL != pBrother)
		{
			int nIndex = m_ComboProfileName.GetCount();
			m_ComboProfileName.InsertString(nIndex, pBrother->strName.c_str());
			pBrother = pBrother->pBrother;
		}
	}
#endif
	m_ComboProfileName.SetCurSel(0);

	ClearComboBox(m_ComboTaskList);
	OnBtnGetTask();
	m_ComboTaskList.SetCurSel(0);
	return TRUE;
}

CRect CTaskCfg::GetTaskListRect()
{
	CIVS_VDemoDlg* pParent =  reinterpret_cast<CIVS_VDemoDlg*>(GetOwner());
	CRect rc;
	GetDlgItem(IDC_LIST_SUBTASK)->GetClientRect(&rc);
	char szTmp[MAX_PATH] = {0};
	sprintf(szTmp, "GetTaskListRect 1 (%d,%d)(%d,%d) ",rc.left, rc.top, rc.right, rc.bottom);
	OutputDebugString(szTmp);

	GetDlgItem(IDC_LIST_SUBTASK)->ClientToScreen(&rc);
	sprintf(szTmp, "GetTaskListRect 2 (%d,%d)(%d,%d) ",rc.left, rc.top, rc.right, rc.bottom);
	OutputDebugString(szTmp);
	return rc;
}

void CTaskCfg::SetOneDeviceInfo(CFG_TAST_SOURCES* pInfo, int nChannelID, int nChannelCount /*= 1*/)
{
	CIVS_VDemoDlg* pParent =  reinterpret_cast<CIVS_VDemoDlg*>(GetOwner());
	if (NULL == pParent)
	{
		return;
	}

	int nSourceOfTask = pParent->GetMaxSourcesOfTask();
	int nItemCount = m_LstSubTask.GetItemCount();
	if ( nSourceOfTask < nItemCount + nChannelCount)
	{
		char szTmp[MAX_PATH] = {0};
		sprintf(szTmp, ConvertString("Only can add [%d] item, not [%d] !"), nSourceOfTask - nItemCount, nChannelCount);
		AfxMessageBox(szTmp);
		return;
	}
	for (int i=0; i<nChannelCount; i++)
	{
		char szTmp[MAX_PATH] = {0};
		int nIndex = m_LstSubTask.GetItemCount();
		sprintf(szTmp, "%d", nIndex);
		m_LstSubTask.InsertItem(nIndex, szTmp);
		m_LstSubTask.SetItemText(nIndex, 1, pInfo->stRemoteDevice.szAddress);
		m_LstSubTask.SetItemData(i, (DWORD)pInfo);
		if (-1 == nChannelID)
		{
			sprintf(szTmp, "%d", i);
		}
		else
		{
			sprintf(szTmp, "%d", nChannelID);
		}
		m_LstSubTask.SetItemText(nIndex, 2, szTmp);
	}
}

BOOL CTaskCfg::HasSameName(char* szTaskName)
{
	if (NULL == szTaskName || 0 == strlen(szTaskName))
	{
		return TRUE;
	}

	for (int i=0; i<m_pTaskCfg->nReturnTaskNum; i++)
	{
		if (0 == _stricmp(m_pTaskCfg->pstTasks[i].szTaskName, szTaskName))
		{
			return TRUE;
		}
	}
	return FALSE;
}
void CTaskCfg::OnBtnAddTask()
{
	// 效验数据
	CString s;
	GetDlgItemText(IDC_COMBO_PROFILENAME,s);
	if (0 == s.GetLength())
	{
		AfxMessageBox(ConvertString("Profile name can not be empty !"));
		return ;
	}
	GetDlgItemText(IDC_COMBO_DURATION,s);
	if (0 == s.GetLength())
	{
		AfxMessageBox(ConvertString("Duration time can not be empty !"));
		return ;
	}
	int nSubTask = m_LstSubTask.GetItemCount();
	if (nSubTask <= 0)
	{
		AfxMessageBox(ConvertString("Sub tasks can not be empty !"));
		return ;
	}
	GetDlgItemText(IDC_EDIT_TASKNAME,s);
	if (0 == s.GetLength())
	{
		AfxMessageBox(ConvertString("Task name can not be empty !"));
		return ;
	}
	if (HasSameName(s.GetBuffer(0)) )
	{
		CString szDebug;
		szDebug.Format(ConvertString("The name of '%s' exists already!"), s.GetBuffer(0));
		OutputDebugString(szDebug);
		AfxMessageBox(szDebug);
		return;
	}
	if (m_pTaskCfg->nReturnTaskNum+1 > m_pTaskCfg->nTotalTaskNum)
	{
		char szDebug[MAX_PATH] = {0};
		sprintf(szDebug, ConvertString("The count of task form is already maximized !"));
		OutputDebugString(szDebug);
		AfxMessageBox(szDebug);
		return;
	}
	int nList = m_ComboTaskList.GetCount();
	m_ComboTaskList.InsertString(nList, s);
	m_ComboTaskList.SetCurSel(nList);

	// 任务个数自增
	m_pTaskCfg->nReturnTaskNum++;

	int nIndex = 0;
	for (; nIndex < m_pTaskCfg->nTotalTaskNum; nIndex++)
	{
		if (0 == strlen(m_pTaskCfg->pstTasks[nIndex].szTaskName))
		{
			break;
		}
	}
	// 保存数据到内存
	CFG_DIAGNOSIS_TASK &stTask = m_pTaskCfg->pstTasks[nIndex];
	GetDlgItemText(IDC_EDIT_TASKNAME,stTask.szTaskName, sizeof(stTask.szTaskName));
	GetDlgItemText(IDC_COMBO_PROFILENAME,stTask.szProfileName, sizeof(stTask.szProfileName));
	{// source处理
		int nIndex = m_LstSubTask.GetItemCount();
		stTask.nReturnSourceNum = __min(stTask.nTotalSourceNum, nIndex);
		memset(stTask.pstSources, 0x0, sizeof(CFG_TAST_SOURCES)*stTask.nReturnSourceNum);
		for (int i=0; i<stTask.nReturnSourceNum; i++)
		{
			CFG_TAST_SOURCES &stSource = stTask.pstSources[i];
			stSource.abRemoteDevice = true;
			stSource.abDeviceID = true;

			stSource.nDuration = GetDlgItemInt(IDC_COMBO_DURATION);

			CFG_TAST_SOURCES *pstSource = reinterpret_cast<CFG_TAST_SOURCES*>(m_LstSubTask.GetItemData(i));
			if (NULL != pstSource)
			{
				memcpy(&stSource.stRemoteDevice, &pstSource->stRemoteDevice, sizeof(CFG_TASK_REMOTEDEVICE));
			}

			m_LstSubTask.GetItemText(i, 1, stSource.stRemoteDevice.szAddress, sizeof(stSource.stRemoteDevice.szAddress));
			
			sprintf(stSource.szDeviceID, "%s",stSource.stRemoteDevice.szAddress);

			char szTmp[MAX_PATH] = {0};
			m_LstSubTask.GetItemText(i, 2, szTmp, sizeof(szTmp));
			stSource.nVideoChannel = atoi(szTmp);
		}
	}
	
}

void CTaskCfg::OnBtnModifyTask()
{
	// 修改内存数据
}

void CTaskCfg::OnBtnDeleteTask()
{
	UpdateData(FALSE);
	int n = m_ComboTaskList.GetCount();
	if (1 > n)
	{
		return;
	}

	int nIndex = m_ComboTaskList.GetCurSel();
	if (nIndex <0)
	{
		return;
	}
	
	char szTmp[MAX_PATH] = {0};
	m_ComboTaskList.GetLBText(nIndex, szTmp);

	BOOL bHas = FALSE;
	for (int i=0; i<m_pTaskCfg->nTotalTaskNum; i++)
	{
		CFG_DIAGNOSIS_TASK& stTask = m_pTaskCfg->pstTasks[i];
		if (0 == _strnicmp(szTmp, stTask.szTaskName, sizeof(stTask.szTaskName)))
		{
			m_pTaskCfg->nReturnTaskNum--;
			memset(stTask.szTaskName, 0x0, sizeof(stTask.szTaskName));
			bHas = TRUE;
			break;
		}
	}

	if (bHas)
	{
		m_ComboTaskList.DeleteString(nIndex);
		m_ComboTaskList.SetCurSel(nIndex);
		
		//m_LstSubTask.DeleteAllItems();
	}
	UpdateData(TRUE);

	// 向设备发送请求，删除对应任务项
	CIVS_VDemoDlg* pParent =  reinterpret_cast<CIVS_VDemoDlg*>(GetOwner());
	DWORD lLoginID = pParent->GetLoginID();
	if (lLoginID <= 0)
	{
		return;
	}

	NET_IN_DELETECFG stInParam = {sizeof(NET_IN_DELETECFG)};
	stInParam.szCommand = new char[128];
	if (NULL == stInParam.szCommand)
	{
		return;
	}
	memset(stInParam.szCommand, 0, 128);
	strcpy(stInParam.szCommand,"VideoDiagnosisTask."); 
	strncat(stInParam.szCommand, szTmp, 128-strlen(stInParam.szCommand));
	NET_OUT_DELETECFG stOutParam = {sizeof(NET_OUT_DELETECFG)};
	
	BOOL bret = CLIENT_DeleteDevConfig(lLoginID, &stInParam, &stOutParam, 1000);
	if (!bret)
	{
		AfxMessageBox("delete task failed!");
	}

	if (NULL != stInParam.szCommand)
	{
		delete []stInParam.szCommand;
	}
}

void CTaskCfg::UnInitTaskConfig(CFG_VIDEODIAGNOSIS_TASK** pTask)
{
	if (NULL == pTask || NULL == *pTask)
	{
		return;
	}

	for (int i=0; i<(*pTask)->nTotalTaskNum; i++)
	{
		CFG_DIAGNOSIS_TASK& stTask = (*pTask)->pstTasks[i];
		SAFE_DELETE_A(stTask.pstSources);
	}
	SAFE_DELETE_A((*pTask)->pstTasks);
	SAFE_DELETE((*pTask))
}
void CTaskCfg::InitTaskConfig(CFG_VIDEODIAGNOSIS_TASK** pTaskPtr)
{
	UnInitTaskConfig(pTaskPtr);

	if (NULL != *pTaskPtr)
	{
		return;
	}

	CIVS_VDemoDlg* pParent =  reinterpret_cast<CIVS_VDemoDlg*>(GetOwner());

	*pTaskPtr = new CFG_VIDEODIAGNOSIS_TASK;
	memset(*pTaskPtr, 0x0, sizeof(CFG_VIDEODIAGNOSIS_TASK));

	(*pTaskPtr)->nTotalTaskNum = pParent->GetMaxTasks();
	if ((*pTaskPtr)->nTotalTaskNum > 0)
	{
		(*pTaskPtr)->pstTasks = new CFG_DIAGNOSIS_TASK[(*pTaskPtr)->nTotalTaskNum];
		memset((*pTaskPtr)->pstTasks, 0x0, sizeof(CFG_DIAGNOSIS_TASK)*(*pTaskPtr)->nTotalTaskNum);
		for (int i=0; i<(*pTaskPtr)->nTotalTaskNum; i++)
		{
			CFG_DIAGNOSIS_TASK& stTask = (*pTaskPtr)->pstTasks[i];
			stTask.nTotalSourceNum = pParent->GetMaxSourcesOfTask();
			stTask.pstSources = new CFG_TAST_SOURCES[stTask.nTotalSourceNum];
			memset(stTask.pstSources, 0x0, stTask.nTotalSourceNum* sizeof(CFG_TAST_SOURCES) );			
		}
	}
}

void CTaskCfg::OnBtnGetTask()
{
	CString szDebugMsg;
	
	CIVS_VDemoDlg* pParent =  reinterpret_cast<CIVS_VDemoDlg*>(GetOwner());
	DWORD lLoginID = pParent->GetLoginID();
	if (lLoginID <= 0)
	{
		return;
	}
	
	ClearComboBox(m_ComboTaskList);

	InitTaskConfig(&m_pTaskCfg);

	int nJsonLen = 1024*1024;
	char * szJson = new char[nJsonLen+1];
	if (NULL == szJson)
	{
		return;
	}

	std::vector<std::string> vec_str;
	pParent->GetCmdMembers(vec_str, CFG_CMD_VIDEODIAGNOSIS_TASK, pParent->GetMaxTasks());
	for (int i=0; i<vec_str.size(); i++)
	{
		char szCmd[MAX_PATH] = {"VideoDiagnosisTask."};
		if (sizeof(szCmd)-strlen(szCmd) < vec_str[i].length())
		{
			continue;
		}
		strncat(szCmd, vec_str[i].c_str(), vec_str[i].length());

		memset(szJson, 0x0, nJsonLen+1);

		int nErr = 0;
		BOOL bSuccess = CLIENT_GetNewDevConfig(lLoginID, szCmd, 0, szJson, nJsonLen, &nErr, 3000);
		szDebugMsg.Format(ConvertString("(0x%x) CLIENT_GetNewDevConfig %s return %s LastError:0x%x !"),
			lLoginID, szCmd, bSuccess == TRUE ? ConvertString("successfully"):ConvertString("failure"),CLIENT_GetLastError());
		OutputDebugString(szDebugMsg);
		if (bSuccess)
		{
			int nRet = 0;
			int nLenOut = sizeof(CFG_VIDEODIAGNOSIS_TASK);

			CFG_VIDEODIAGNOSIS_TASK* pTask = NULL;
			InitTaskConfig(&pTask);

			BOOL bRet = CLIENT_ParseData(CFG_CMD_VIDEODIAGNOSIS_TASK_ONE, szJson, pTask, nLenOut, &nRet);
			szDebugMsg.Format(ConvertString("CLIENT_ParseData %s return %s !"),szCmd,bRet==TRUE?ConvertString("successfully"):ConvertString("failure"));
			OutputDebugString(szDebugMsg);
			if (bRet)
			{
				if (m_pTaskCfg->nReturnTaskNum < m_pTaskCfg->nTotalTaskNum)
				{
					// 保存数据到内存中
					int nSource = __min(pTask->pstTasks[0].nReturnSourceNum,m_pTaskCfg->pstTasks[i].nTotalSourceNum);
					memcpy(m_pTaskCfg->pstTasks[i].pstSources, pTask->pstTasks[0].pstSources, sizeof(CFG_TAST_SOURCES)*nSource);
					m_pTaskCfg->pstTasks[i].nReturnSourceNum = nSource;
					memcpy(m_pTaskCfg->pstTasks[i].szProfileName, pTask->pstTasks[0].szProfileName, sizeof(m_pTaskCfg->pstTasks[i].szProfileName));
					memcpy(m_pTaskCfg->pstTasks[i].szTaskName, pTask->pstTasks[0].szTaskName, sizeof(m_pTaskCfg->pstTasks[i].szTaskName));
					if (strlen(m_pTaskCfg->pstTasks[i].szTaskName) == 0)
					{
						int nNameLen = __min(sizeof(m_pTaskCfg->pstTasks[i].szTaskName),vec_str[i].length());
						memcpy(m_pTaskCfg->pstTasks[i].szTaskName, vec_str[i].c_str(), nNameLen);
					}

					// 添加任务到界面
					int n = m_ComboTaskList.GetCount();
					m_ComboTaskList.InsertString(n, vec_str[i].c_str());
					m_ComboTaskList.SetItemData(n, (DWORD)&m_pTaskCfg->pstTasks[i]);

					m_pTaskCfg->nReturnTaskNum++;
				}
			}
			else
			{
				UnInitTaskConfig(&pTask);
				AfxMessageBox(szDebugMsg);;
				break;
			}

			UnInitTaskConfig(&pTask);
		}
		else
		{
			AfxMessageBox(szDebugMsg);;
			break;
		}
	}
	m_ComboTaskList.SetCurSel(0);
	// 内存释放
	SAFE_DELETE_A(szJson);	
}

void CTaskCfg::OnBtnSetTask()
{
	if (NULL == m_pTaskCfg || m_pTaskCfg->nReturnTaskNum ==0)
	{
		return;
	}

	CString sDebugMsg;

	CIVS_VDemoDlg* pParent =  reinterpret_cast<CIVS_VDemoDlg*>(GetOwner());
	DWORD lLoginID = pParent->GetLoginID();
	if (lLoginID <= 0)
	{
		return;
	}
	
	// 封装并设置数据
	int nJsonLen = 1024*1024;
	char * szJson = new char[nJsonLen+1];

	CFG_VIDEODIAGNOSIS_TASK* pTask = new CFG_VIDEODIAGNOSIS_TASK;
	memset(pTask, 0x0, sizeof(CFG_VIDEODIAGNOSIS_TASK));
	pTask->nTotalTaskNum = 1;
 	pTask->pstTasks = new CFG_DIAGNOSIS_TASK[pTask->nTotalTaskNum];
	for (int i=0; i<m_pTaskCfg->nReturnTaskNum; i++)
	{
		memset(pTask->pstTasks, 0x0, sizeof(CFG_DIAGNOSIS_TASK));
		CFG_DIAGNOSIS_TASK &stTask = m_pTaskCfg->pstTasks[i];
		pTask->pstTasks[0] = m_pTaskCfg->pstTasks[i];
		pTask->pstTasks[0].nTotalSourceNum = pTask->pstTasks[0].nReturnSourceNum;

		memset(szJson, 0x0, nJsonLen+1);
		BOOL bRet = CLIENT_PacketData(CFG_CMD_VIDEODIAGNOSIS_TASK_ONE, pTask, sizeof(CFG_VIDEODIAGNOSIS_TASK), szJson, nJsonLen);
		sDebugMsg.Format(ConvertString("(0x%x) CLIENT_PacketData %s return %s !"),lLoginID, CFG_CMD_VIDEODIAGNOSIS_TASK_ONE, bRet == TRUE ? ConvertString("successfully"):ConvertString("failure"));
		OutputDebugString(sDebugMsg);
		if (bRet == TRUE)
		{
			int nErr = 0;
			int nrestart = 0;
			char szCmd[MAX_PATH] = {"VideoDiagnosisTask."};
			strncat(szCmd, pTask->pstTasks[0].szTaskName,sizeof(szCmd)-strlen(szCmd));
			BOOL bSuccess = CLIENT_SetNewDevConfig(lLoginID, szCmd, 0, szJson, nJsonLen, &nErr, &nrestart, 3000);		
			sDebugMsg.Format(ConvertString("(0x%x) CLIENT_SetNewDevConfig %s return %s LastError:0x%x !"),
				lLoginID, szCmd, bSuccess == TRUE ? ConvertString("successfully"):ConvertString("failure"),CLIENT_GetLastError());
			OutputDebugString(sDebugMsg);
			if (bSuccess == TRUE)
			{
			}
			else
				AfxMessageBox(sDebugMsg);;
		}
		else
			AfxMessageBox(sDebugMsg);;
	}
	SAFE_DELETE(pTask->pstTasks);
	SAFE_DELETE(pTask);
	SAFE_DELETE(szJson);
}

void CTaskCfg::GetTaskList(std::vector<std::string> & v)
{
	if (NULL == m_pTaskCfg)
	{
		return;
	}
	for (int i=0; i<m_pTaskCfg->nReturnTaskNum; i++)
	{
		CFG_DIAGNOSIS_TASK& stTask = m_pTaskCfg->pstTasks[i];
		v.push_back(stTask.szTaskName);
	}
}

void CTaskCfg::OnSelchangeComboTaskList()
{
	if (NULL == m_pTaskCfg)
	{
		return;
	}
	m_LstSubTask.DeleteAllItems();

	int nSel = m_ComboTaskList.GetCurSel();
	if (0 > nSel)
	{
		return;
	}

	CString s;
	m_ComboTaskList.GetLBText(nSel,s);
	if (nSel <m_pTaskCfg->nReturnTaskNum)
	{
		CFG_DIAGNOSIS_TASK *pstTask = NULL;
		{
			for (int i=0; i<m_pTaskCfg->nTotalTaskNum; i++)
			{
				CFG_DIAGNOSIS_TASK& stTask = m_pTaskCfg->pstTasks[i];
				if (0 == s.Compare(stTask.szTaskName))
				{
					pstTask = & stTask;
				}
			}
		}
		if (NULL == pstTask)
		{
			return;
		}

		{
			for (int i=0; i<pstTask->nReturnSourceNum; i++)
			{
				char szTmp[MAX_PATH] = {0};
				sprintf(szTmp, "%d", i);
				m_LstSubTask.InsertItem(i,szTmp);
				
				CFG_TAST_SOURCES& stSource = pstTask->pstSources[i];
				
				m_LstSubTask.SetItemText(i, 1, stSource.stRemoteDevice.szAddress);
				
				sprintf(szTmp, "%d", stSource.nVideoChannel);
				m_LstSubTask.SetItemText(i, 2, szTmp);
			}
		}

		{
			for (int i=0; i< m_ComboProfileName.GetCount();i++)
			{
				CString t;
				m_ComboProfileName.GetLBText(i,t);
				if (0 == t.Compare(pstTask->szProfileName))
				{
					m_ComboProfileName.SetCurSel(i);
				}
			}
		}
		{// duration time
			BOOL bHas = FALSE;
			for (int i=0; i< m_ComboDuration.GetCount();i++)
			{
				CString t;
				m_ComboDuration.GetLBText(i,t);
				if (atoi(t.GetBuffer(0)) == pstTask->pstSources[0].nDuration)
				{
					m_ComboDuration.SetCurSel(i);
					bHas = TRUE;
				}
			}
			if (!bHas)
			{
				char szTmp[MAX_PATH] ={0};
				sprintf(szTmp, "%d",pstTask->pstSources[0].nDuration);
				int n = m_ComboDuration.GetCount();
				m_ComboDuration.InsertString(n,szTmp);
				m_ComboDuration.SetCurSel(n);
			}
				}
		SetDlgItemText(IDC_EDIT_TASKNAME,pstTask->szTaskName);
	}
}

void CTaskCfg::OnBtnDeleteItem()
{
	if (m_LstSubTask.GetItemCount() <= 0)
	{
		return;
	}
	
	POSITION  p = m_LstSubTask.GetFirstSelectedItemPosition();
	while (NULL != p)
	{
		// 删除
		int nSel = m_LstSubTask.GetNextSelectedItem(p);
		m_LstSubTask.DeleteItem(nSel);
		
		// 更新后边的序号
		int nCount = m_LstSubTask.GetItemCount();
		for (int i=nSel; i<nCount; i++)
		{
			char szTmp[MAX_PATH] ={0};
			sprintf(szTmp, "%d", i);
			m_LstSubTask.SetItemText(i, 0, szTmp);
		}
	}
}
void CTaskCfg::OnBtnClearItem()
{
	m_LstSubTask.DeleteAllItems();
}