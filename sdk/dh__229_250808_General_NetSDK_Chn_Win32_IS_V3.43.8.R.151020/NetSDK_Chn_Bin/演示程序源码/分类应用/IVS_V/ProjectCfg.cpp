// Project.cpp : implementation file
//

#include "stdafx.h"
#include "IVS_VDemo.h"
#include "ProjectCfg.h"
#include "IVS_VDemoDlg.h"
#include "TaskCfg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CProjectCfg dialog


CProjectCfg::CProjectCfg(CWnd* pParent /*=NULL*/)
	: CDialog(CProjectCfg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CProjectCfg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	m_pProject = NULL;
}

CProjectCfg::CProjectCfg(CDialog* pTask, CWnd* pParent /*=NULL*/)
: CDialog(CProjectCfg::IDD, pParent),m_pTask(reinterpret_cast<CTaskCfg*>(pTask)),m_pProject(NULL)
{
}

CProjectCfg::~CProjectCfg()
{
	if (NULL != m_pProject)
	{
		UnInitProject(m_pProject);
		m_pProject = NULL;
	}
}

void CProjectCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CProjectCfg)
	DDX_Control(pDX, IDC_COMBO_PROJECT, m_comboProject);
	DDX_Control(pDX, IDC_COMBO_TASK, m_comboTask);
	DDX_Control(pDX, IDC_LIST_PROJECT_INFO, m_lstProjectInfo);
	DDX_Control(pDX, IDC_DATETIMEPICKER_START, m_startTime);
	DDX_Control(pDX, IDC_DATETIMEPICKER_END, m_endTime);
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CProjectCfg, CDialog)
	//{{AFX_MSG_MAP(CProjectCfg)
	ON_BN_CLICKED(IDC_BTN_GET,OnBtnGetProject)
	ON_BN_CLICKED(IDC_BTN_SET,OnBtnSetProject)
	ON_BN_CLICKED(IDC_BTN_ADD,OnBtnAddProject)
	ON_BN_CLICKED(IDC_BTN_DEL,OnBtnDelProject)
	ON_BN_CLICKED(IDC_BTN_MODIFY,OnBtnModifyProject)
	ON_BN_CLICKED(IDC_BTN_ADD_TASK,OnBtnAddTaskToProject)
	ON_BN_CLICKED(IDC_BTN_DEL_TASK,OnBtnDelTaskFromProject)
	ON_CBN_SELCHANGE(IDC_COMBO_PROJECT, OnSelchangeComboProject)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProjectCfg message handlers

void CProjectCfg::OnOK() 
{
	// TODO: Add extra validation here
	
	//CDialog::OnOK();
}

void CProjectCfg::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	//CDialog::OnCancel();
}

BOOL CProjectCfg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_lstProjectInfo.ModifyStyle(0, LVS_SINGLESEL | LVS_REPORT);
	m_lstProjectInfo.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	m_lstProjectInfo.InsertColumn(0, ConvertString("NO."), LVCFMT_CENTER, 50);
	m_lstProjectInfo.InsertColumn(1, ConvertString("task name"), LVCFMT_CENTER, 100);
	m_lstProjectInfo.InsertColumn(2, ConvertString("Start time"), LVCFMT_CENTER, 100);
	m_lstProjectInfo.InsertColumn(3, ConvertString("End time"), LVCFMT_CENTER, 100);

	m_startTime.ModifyStyleEx(0, DTS_TIMEFORMAT);
	m_endTime.ModifyStyleEx(0, DTS_TIMEFORMAT);
	m_startTime.SetFormat("HH:mm");
	m_endTime.SetFormat("HH:mm");

	g_SetWndStaticText(this);

	return TRUE;
}

BOOL CProjectCfg::UnInitProject(CFG_VIDEODIAGNOSIS_PROJECT* pProject)
{
	if (NULL == pProject || NULL == pProject->pstProjects || pProject->nTotalProjectNum == 0)
	{
		return FALSE;
	}
	
	if (pProject->pstProjects != NULL)
	{
		for (int i=0; i<pProject->nTotalProjectNum; i++)
		{
			CFG_DIAGNOSIS_PROJECT &stProject = pProject->pstProjects[i];
			for (int j=0; j<stProject.nTotalTaskNum; j++)
			{
				SAFE_DELETE_A(stProject.pstProjectTasks);
			}
		}
	}
	
	SAFE_DELETE_A(pProject->pstProjects);
	SAFE_DELETE(pProject);

	return TRUE;
}
BOOL CProjectCfg::InitProject(CFG_VIDEODIAGNOSIS_PROJECT** pProject)
{
	if (NULL == pProject)
	{
		return FALSE;
	}

	if (NULL != *pProject)
	{
		// 删除已申请资源
		UnInitProject(*pProject);
		*pProject = NULL;
	}

	*pProject = new CFG_VIDEODIAGNOSIS_PROJECT;
	if (NULL == *pProject)
	{
		return FALSE;
	}
	memset(*pProject, 0x0, sizeof(CFG_VIDEODIAGNOSIS_PROJECT));
	
	CIVS_VDemoDlg* pParent =  reinterpret_cast<CIVS_VDemoDlg*>(GetOwner());
	(*pProject)->nTotalProjectNum = pParent->GetMaxProjects();
	if ((*pProject)->nTotalProjectNum > 0)
	{
		(*pProject)->pstProjects = new CFG_DIAGNOSIS_PROJECT[(*pProject)->nTotalProjectNum];
		memset((*pProject)->pstProjects, 0x0, (*pProject)->nTotalProjectNum * sizeof(CFG_DIAGNOSIS_PROJECT));
		for (int i=0; i<(*pProject)->nTotalProjectNum; i++)
		{
			CFG_DIAGNOSIS_PROJECT &stProject = (*pProject)->pstProjects[i];
			stProject.nTotalTaskNum = pParent->GetMaxTasks();
			if (stProject.nTotalTaskNum > 0)
			{
				stProject.pstProjectTasks = new CFG_PROJECT_TASK[stProject.nTotalTaskNum];
				memset(stProject.pstProjectTasks, 0x0, stProject.nTotalTaskNum * sizeof(CFG_PROJECT_TASK));
			}
			else
			{
				return FALSE;
			}
		}
	}
	else
	{
		return FALSE;
	}
	return TRUE;
}

void CProjectCfg::UpDataToDlg()
{
	if (NULL == m_pProject || NULL == m_pProject->pstProjects)
	{
		return;
	}

	for (int i=0; i<m_pProject->nReturnProjectNum; i++)
	{
		CFG_DIAGNOSIS_PROJECT& stProject = m_pProject->pstProjects[i];
		int nIndex = m_comboProject.GetCount();
		m_comboProject.InsertString(nIndex, stProject.szProjectName);
	}
}

BOOL CProjectCfg::GetDefaultProject()
{
	ClearComboBox(m_comboTask);

#if 0
	// 从任务面板获取任务名称列表，并更新到计划列表
	if (NULL != m_pTask)
	{
		std::vector<std::string> v;
		m_pTask->GetTaskList(v);
		for (int i=0; i<v.size(); i++)
		{
			int nIndex = m_comboTask.GetCount();
			std::string s = v[i];
			m_comboTask.InsertString(nIndex, s.c_str());
		}
	}
#else
	CIVS_VDemoDlg* pParent =  reinterpret_cast<CIVS_VDemoDlg*>(GetOwner());
	std::vector<std::string> v;
	pParent->GetCmdMembers(v, CFG_CMD_VIDEODIAGNOSIS_TASK, pParent->GetMaxTasks());
	for (int i=0; i<v.size(); i++)
	{
		m_comboTask.InsertString(i, v[i].c_str());
	}
#endif
	m_comboTask.SetCurSel(0);

	OnBtnGetProject();

	return TRUE;
}

void CProjectCfg::OnBtnGetProject()
{
	ClearComboBox(m_comboProject);
	CString szDebugMsg;
	
	CIVS_VDemoDlg* pParent =  reinterpret_cast<CIVS_VDemoDlg*>(GetOwner());
	DWORD lLoginID = pParent->GetLoginID();
	if (lLoginID <= 0)
	{
		return;
	}
		
	InitProject(&m_pProject);
	
	int nErr = 0;
	int nJsonLen = 1024*1024;
	char * szJson = new char[nJsonLen+1];
	memset(szJson, 0x0, nJsonLen+1);
	char szCmd[] = CFG_CMD_VIDEODIAGNOSIS_PROJECT;
	
	BOOL bSuccess = CLIENT_GetNewDevConfig(lLoginID, szCmd, 0, szJson, nJsonLen, &nErr, 3000);
	szDebugMsg.Format(ConvertString("(0x%x) CLIENT_GetNewDevConfig %s return %s LastError:0x%x !"),
		lLoginID, szCmd, bSuccess == TRUE ? ConvertString("successfully"):ConvertString("failure"),CLIENT_GetLastError());
	OutputDebugString(szDebugMsg);
	if (bSuccess)
	{
		int nRet = 0;
		BOOL bRet = CLIENT_ParseData(szCmd,szJson, m_pProject,sizeof(CFG_VIDEODIAGNOSIS_PROJECT),&nRet);
		szDebugMsg.Format(ConvertString("CLIENT_ParseData %s return %s !"),szCmd,bRet==TRUE?"succesfully":"failure");
		OutputDebugString(szDebugMsg);
		if (bRet)
		{
			// 刷新数据到界面上
			UpDataToDlg();
		}
		else
		{
			AfxMessageBox(szDebugMsg);;
		}
	}
	else
	{
		AfxMessageBox(szDebugMsg);;
	}
	SAFE_DELETE_A(szJson);
	m_comboProject.SetCurSel(0);
}

void CProjectCfg::OnBtnSetProject()
{
	CString sDebugMsg;
	
	CIVS_VDemoDlg* pParent =  reinterpret_cast<CIVS_VDemoDlg*>(GetOwner());
	DWORD lLoginID = pParent->GetLoginID();
	if (lLoginID <= 0)
	{
		return;
	}
	
	// 封装并设置数据
	char szCmd[] = CFG_CMD_VIDEODIAGNOSIS_PROJECT;
	
	int nJsonLen = 1024*1024;
	char * szJson = new char[nJsonLen+1];
	memset(szJson, 0x0, nJsonLen+1);
	
	m_pProject->nTotalProjectNum = m_pProject->nReturnProjectNum;
	{
		for (int i=0; i<m_pProject->nTotalProjectNum;i++)
		{
			m_pProject->pstProjects[i].nTotalTaskNum = m_pProject->pstProjects[i].nReturnTaskNum;
		}
	}

	BOOL bRet = CLIENT_PacketData(szCmd, m_pProject, sizeof(CFG_VIDEODIAGNOSIS_PROJECT), szJson, nJsonLen);
	sDebugMsg.Format(ConvertString("(0x%x) CLIENT_PacketData %s return %s !"),lLoginID, szCmd, bRet == TRUE ? "succesfully":"failure");
	OutputDebugString(sDebugMsg);
	if (bRet == TRUE)
	{
		int nErr = 0;
		int nrestart = 0;
		BOOL bSuccess = CLIENT_SetNewDevConfig(lLoginID, szCmd, 0, szJson, strlen(szJson), &nErr, &nrestart, 3000);		
		sDebugMsg.Format(ConvertString("(0x%x) CLIENT_SetNewDevConfig %s return %s LastError:0x%x !"),
			lLoginID, szCmd, bSuccess == TRUE ? ConvertString("successfully"):ConvertString("failure"),CLIENT_GetLastError());
		OutputDebugString(sDebugMsg);
		if (bSuccess == TRUE)
		{
		}
		else
		{
			AfxMessageBox(sDebugMsg);;
		}
	}
	else
	{
		AfxMessageBox(sDebugMsg);;
	}
	SAFE_DELETE_A(szJson);

	{
		for(int i=0; i<m_pProject->nTotalProjectNum; i++)
		{
			m_pProject->pstProjects[i].nTotalTaskNum = pParent->GetMaxTasks();
		}
	}
	m_pProject->nTotalProjectNum = pParent->GetMaxProjects();
}

BOOL CProjectCfg::HasSameName(char* szName)
{
	for (int i=0; i<m_pProject->nReturnProjectNum; i++)
	{
		CFG_DIAGNOSIS_PROJECT& stProject = m_pProject->pstProjects[i];
		if (0 == _stricmp(stProject.szProjectName, szName))
		{
			return TRUE;
		}
	}
	return FALSE;
}
void CProjectCfg::OnBtnAddProject()
{
	if (NULL == m_pProject)
	{
		return;
	}
	
	if (m_pProject->nTotalProjectNum - m_pProject->nReturnProjectNum <= 0)
	{
		char szDebug[MAX_PATH] = {0};
		sprintf(szDebug, ConvertString("The count of project is already maximized !"));
		OutputDebugString(szDebug);
		AfxMessageBox(szDebug);;
		return;
	}

	int n = m_lstProjectInfo.GetItemCount();
	if (0 >= n)
	{
		AfxMessageBox(ConvertString("Project information can not be empty !"));
		return;
	}
	
	CFG_DIAGNOSIS_PROJECT& stProject = m_pProject->pstProjects[m_pProject->nReturnProjectNum];

	if (stProject.nTotalTaskNum < n)
	{
		char szDebug[MAX_PATH] = {0};
		sprintf(szDebug, ConvertString("The count of tasks in one project is already maximized, %d !"), stProject.nTotalTaskNum);
		OutputDebugString(szDebug);
		AfxMessageBox(szDebug);;
		return;
	}

	GetDlgItemText(IDC_EDIT_PROJECT_NAME, stProject.szProjectName, sizeof(stProject.szProjectName));
	if (0 >= strlen(stProject.szProjectName))
	{
		AfxMessageBox(ConvertString("Project name can not be empty !"));
		return;
	}

	if (HasSameName(stProject.szProjectName))
	{
		CString szDebug;
		szDebug.Format(ConvertString("The name of '%s' exists already!"), stProject.szProjectName);
		OutputDebugString(szDebug);
		AfxMessageBox(szDebug);;
		
		memset(stProject.szProjectName, 0x0, sizeof(stProject.szProjectName));
		return;
	}

	if (0 == strlen(stProject.szProjectName))
	{
		CString szDebug;
		szDebug.Format(ConvertString("The name of '%s' can't be empty !"), stProject.szProjectName);
		OutputDebugString(szDebug);
		AfxMessageBox(szDebug);;
		
		memset(stProject.szProjectName, 0x0, sizeof(stProject.szProjectName));
		return ;
	}
	
	m_pProject->nReturnProjectNum++;

	for (int i=0; i< n; i++)
	{
		stProject.nReturnTaskNum++;

		CFG_PROJECT_TASK &stProjectTask = stProject.pstProjectTasks[i];
		stProjectTask.bEnable = TRUE;
		m_lstProjectInfo.GetItemText(i, 1, stProjectTask.szTaskName, sizeof(stProjectTask.szTaskName));
		{// 开始时间
			char szTmp[MAX_PATH] = {0};
			m_lstProjectInfo.GetItemText(i, 2, szTmp, sizeof(szTmp));
			char* pS= strstr(szTmp,":");
			*pS++ = '\0';
			for (int j=0; j<WEEK_DAY_NUM;j++)
			{
				stProjectTask.stTimeSection[j][0].nBeginHour = atoi(szTmp);
				stProjectTask.stTimeSection[j][0].nBeginMin = atoi(pS);
			}
		}
		{// 结束时间
			char szTmp[MAX_PATH] = {0};
			m_lstProjectInfo.GetItemText(i, 3, szTmp, sizeof(szTmp));
			char* pS= strstr(szTmp,":");
			*pS++ = '\0';
			for (int j=0; j<WEEK_DAY_NUM;j++)
			{
				stProjectTask.stTimeSection[j][0].nEndHour = atoi(szTmp);
				stProjectTask.stTimeSection[j][0].nEndMin = atoi(pS);
			}
		}
	}

	int nIndex = m_comboProject.GetCount();
	m_comboProject.InsertString(nIndex, stProject.szProjectName);
	m_comboProject.SetCurSel(nIndex);
}
void CProjectCfg::OnBtnDelProject()
{
	int nSel = m_comboProject.GetCurSel();
	char szTmp[MAX_PATH] = {0};
	m_comboProject.GetLBText(nSel, szTmp);

	BOOL bHas = FALSE;
	for (int i=0; i<m_pProject->nReturnProjectNum; i++)
	{
		CFG_DIAGNOSIS_PROJECT& stProject = m_pProject->pstProjects[i];
		if (0 == _stricmp(stProject.szProjectName, szTmp))
		{
			bHas = TRUE;

			if (i +1 == m_pProject->nReturnProjectNum)
			{
				memset(stProject.pstProjectTasks, 0x0, sizeof(stProject.pstProjectTasks));
				memset(stProject.szProjectName, 0x0, sizeof(stProject.szProjectName));
				stProject.nReturnTaskNum = 0;
			}
			else
			{
				int j = i+1;
				// 后边数据前移
				for (; j<m_pProject->nReturnProjectNum; j++)
				{
					CFG_DIAGNOSIS_PROJECT& stProject = m_pProject->pstProjects[j-1];
					CFG_DIAGNOSIS_PROJECT& stProject2 = m_pProject->pstProjects[j];
					memcpy(stProject.pstProjectTasks, stProject2.pstProjectTasks, sizeof(stProject.pstProjectTasks));
					memcpy(stProject.szProjectName, stProject2.szProjectName, sizeof(stProject.szProjectName));
					stProject.nReturnTaskNum = stProject2.nReturnTaskNum;
					stProject.nTotalTaskNum = stProject2.nTotalTaskNum;
				}

				// 最后数据恢复默认
				memset(m_pProject->pstProjects[j-1].pstProjectTasks, 0x0, sizeof(CFG_PROJECT_TASK));
				memset(m_pProject->pstProjects[j-1].szProjectName, 0x0, sizeof(m_pProject->pstProjects[j-1].szProjectName));
				m_pProject->pstProjects[j-1].nReturnTaskNum = 0;
			}
			m_pProject->nReturnProjectNum--;
			break;
		}
	}
	if (bHas)
	{
		m_comboProject.DeleteString(nSel);
		m_comboProject.SetCurSel(nSel);
	}
}

void CProjectCfg::OnBtnModifyProject()
{
	//OnSelchangeComboProject();
	//OnBtnDelProject();

	//OnBtnAddProject();
}

void CProjectCfg::OnBtnAddTaskToProject()
{
	CString s;
	GetDlgItemText(IDC_COMBO_TASK,s);
	if (0 == s.GetLength())
	{
		AfxMessageBox(ConvertString("Task name can not be empty !"));
		return ;
	}
	if (m_comboTask.GetCount() > 0)
	{
		int nIndexOfTask = m_comboTask.GetCurSel();
		
		int nIndexTask = m_lstProjectInfo.GetItemCount();
		char szTmp[MAX_PATH] = {0};
		sprintf(szTmp, "%d", nIndexTask);
		m_lstProjectInfo.InsertItem(nIndexTask, szTmp);
		
		memset(szTmp, 0x0, sizeof(szTmp));
		m_comboTask.GetLBText(nIndexOfTask, szTmp);
		m_lstProjectInfo.SetItemText(nIndexTask, 1, szTmp);
		
		{
			memset(szTmp, 0x0, sizeof(szTmp));
			SYSTEMTIME tm;
			m_startTime.GetTime(&tm);
			sprintf(szTmp, "%2d:%2d",tm.wHour, tm.wMinute);
			m_lstProjectInfo.SetItemText(nIndexTask, 2, szTmp);
		}
		
		{
			memset(szTmp, 0x0, sizeof(szTmp));
			SYSTEMTIME tm;
			m_endTime.GetTime(&tm);
			sprintf(szTmp, "%2d:%2d",tm.wHour, tm.wMinute);
			m_lstProjectInfo.SetItemText(nIndexTask, 3, szTmp);
		}
	}

}
void CProjectCfg::OnBtnDelTaskFromProject()
{
	if (m_lstProjectInfo.GetItemCount() <= 0)
	{
		return;
	}

	POSITION  p = m_lstProjectInfo.GetFirstSelectedItemPosition();
	while (NULL != p)
	{
		// 删除
		int nSel = m_lstProjectInfo.GetNextSelectedItem(p);
		m_lstProjectInfo.DeleteItem(nSel);

		// 更新后边的序号
		int nCount = m_lstProjectInfo.GetItemCount();
		for (int i=nSel; i<nCount; i++)
		{
			char szTmp[MAX_PATH] ={0};
			sprintf(szTmp, "%d", i);
			m_lstProjectInfo.SetItemText(i, 0, szTmp);
		}
	}
}
void CProjectCfg::OnSelchangeComboProject() 
{
	// TODO: Add your control notification handler code here
	if (NULL == m_pProject)
	{
		return;
	}

	m_lstProjectInfo.DeleteAllItems();
	
	int nSel = m_comboProject.GetCurSel();
	if (0 > nSel)
	{
		return;
	}

	CString s;
	m_comboProject.GetLBText(nSel,s);

	for (int i=0; i<m_pProject->nReturnProjectNum; i++)
	{
		CFG_DIAGNOSIS_PROJECT &stProject = m_pProject->pstProjects[i];
		if (s.Compare(stProject.szProjectName) == 0)
		{
			for (int j=0; j< stProject.nReturnTaskNum; j++)
			{
				char szTmp[MAX_PATH] = {0};
				sprintf(szTmp, "%d", j);
				m_lstProjectInfo.InsertItem(j, szTmp);

				CFG_PROJECT_TASK& stProjectTask = stProject.pstProjectTasks[j];
				m_lstProjectInfo.SetItemText(j, 1, stProjectTask.szTaskName);

				sprintf(szTmp, "%2d:%2d", stProjectTask.stTimeSection[0][0].nBeginHour, stProjectTask.stTimeSection[0][0].nBeginMin);
				m_lstProjectInfo.SetItemText(j, 2, szTmp);
				sprintf(szTmp, "%2d:%2d", stProjectTask.stTimeSection[0][0].nEndHour, stProjectTask.stTimeSection[0][0].nEndMin);
				m_lstProjectInfo.SetItemText(j, 3, szTmp);
			}
		}
	}
}