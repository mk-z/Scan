// ProfileInfo1.cpp : implementation file
//

#include "stdafx.h"
#include "IVS_VDemo.h"
#include "ProfileInfo1.h"
#include "ProfileCfg.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CProfileInfo1 dialog


CProfileInfo1::CProfileInfo1(CWnd* pParent /*=NULL*/)
	: CDialog(CProfileInfo1::IDD, pParent)
{
	//{{AFX_DATA_INIT(CProfileInfo1)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	m_pParent = reinterpret_cast<CProfileCfg* >(pParent);
}


void CProfileInfo1::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CProfileInfo1)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CProfileInfo1, CDialog)
	//{{AFX_MSG_MAP(CProfileInfo1)
	ON_EN_CHANGE(IDC_EDIT_PROFILE_NAME, OnChangeEditProfileName)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProfileInfo1 message handlers

void CProfileInfo1::OnOK() 
{
	// TODO: Add extra validation here
	
	//CDialog::OnOK();
}

void CProfileInfo1::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	//CDialog::OnCancel();
}

void CProfileInfo1::EnableControls(DWORD dwMaskControls)
{
	//if (dwMaskControls & EN_MASK_CONTROLS_NAME)
	GetDlgItem(IDC_EDIT_PROFILE_NAME)->EnableWindow(dwMaskControls & EN_MASK_CONTROLS_NAME);

	GetDlgItem(IDC_CHECK_ENABLE)->EnableWindow(dwMaskControls & EN_MASK_CONTROLS_ENABLE);
	GetDlgItem(IDC_EDIT_PROFILE_MINDURATION)->EnableWindow(dwMaskControls & EN_MASK_CONTROLS_MINDURATION);

	GetDlgItem(IDC_EDIT_PROFILE_THRESHOLD1)->EnableWindow(dwMaskControls & EN_MASK_CONTROLS_ALARMLOW);
	GetDlgItem(IDC_EDIT_PROFILE_THRESHOLD1_UP)->EnableWindow(dwMaskControls & EN_MASK_CONTROLS_ALARMUP);

	GetDlgItem(IDC_EDIT_PROFILE_THRESHOLD2)->EnableWindow(dwMaskControls & EN_MASK_CONTROLS_ERRLOW);
	GetDlgItem(IDC_EDIT_PROFILE_THRESHOLD2_UP)->EnableWindow(dwMaskControls & EN_MASK_CONTROLS_ERRUP);

	GetDlgItem(IDC_CHECK_UVD)->EnableWindow(dwMaskControls & EN_MASK_CONTROLS_UVD);
}

void CProfileInfo1::UpdateDataToDlg(char* szType, CFG_VIDEO_DIAGNOSIS_PROFILE * pstProfile)
{
	UpdateData(FALSE);

	if (NULL == pstProfile)
	{
		if (0 != strlen(szType))
		{
			SetDlgItemText(IDC_EDIT_PROFILE_NAME, szType);
		}	
		return;
	}

	if (0 == _stricmp(szType,ConvertString(NET_DIAGNOSIS_DITHER)))
	{
		if (NULL != pstProfile->pstDither)
		{
			CButton* pBtn = reinterpret_cast<CButton*>(GetDlgItem(IDC_CHECK_ENABLE));
			pBtn->SetCheck(pstProfile->pstDither->bEnable);
			SetDlgItemInt(IDC_EDIT_PROFILE_THRESHOLD1, pstProfile->pstDither->byThrehold1);
			SetDlgItemInt(IDC_EDIT_PROFILE_THRESHOLD2, pstProfile->pstDither->byThrehold2);
			SetDlgItemInt(IDC_EDIT_PROFILE_MINDURATION, pstProfile->pstDither->nMinDuration);
		}
	}
	else if (0 == _stricmp(szType,ConvertString(NET_DIAGNOSIS_STRIATION)))
	{
		if (NULL != pstProfile->pstStriation)
		{
			CButton* pBtn = reinterpret_cast<CButton*>(GetDlgItem(IDC_CHECK_ENABLE));
			pBtn->SetCheck(pstProfile->pstStriation->bEnable);

			SetDlgItemInt(IDC_EDIT_PROFILE_THRESHOLD1, pstProfile->pstStriation->byThrehold1);
			SetDlgItemInt(IDC_EDIT_PROFILE_THRESHOLD2, pstProfile->pstStriation->byThrehold2);
			SetDlgItemInt(IDC_EDIT_PROFILE_MINDURATION, pstProfile->pstStriation->nMinDuration);

			pBtn = reinterpret_cast<CButton*>(GetDlgItem(IDC_CHECK_UVD));
			pBtn->SetCheck(pstProfile->pstStriation->bUVDetection);
		}
	}
	else if (0 == _stricmp(szType,ConvertString(NET_DIAGNOSIS_LOSS)))
	{
		if (NULL != pstProfile->pstLoss)
		{
			CButton* pBtn = reinterpret_cast<CButton*>(GetDlgItem(IDC_CHECK_ENABLE));
			pBtn->SetCheck(pstProfile->pstLoss->bEnable);

			SetDlgItemInt(IDC_EDIT_PROFILE_MINDURATION, pstProfile->pstLoss->nMinDuration);
		}
	}
	else if (0 == _stricmp(szType,ConvertString(NET_DIAGNOSIS_COVER)))
	{
		if (NULL != pstProfile->pstCover)
		{
			CButton* pBtn = reinterpret_cast<CButton*>(GetDlgItem(IDC_CHECK_ENABLE));
			pBtn->SetCheck(pstProfile->pstCover->bEnable);

			SetDlgItemInt(IDC_EDIT_PROFILE_THRESHOLD1, pstProfile->pstCover->byThrehold1);
			SetDlgItemInt(IDC_EDIT_PROFILE_THRESHOLD2, pstProfile->pstCover->byThrehold2);
			SetDlgItemInt(IDC_EDIT_PROFILE_MINDURATION, pstProfile->pstCover->nMinDuration);
		}
	}
	else if (0 == _stricmp(szType,ConvertString(NET_DIAGNOSIS_FROZEN)))
	{
		if (NULL != pstProfile->pstFrozen)
		{
			CButton* pBtn = reinterpret_cast<CButton*>(GetDlgItem(IDC_CHECK_ENABLE));
			pBtn->SetCheck(pstProfile->pstFrozen->bEnable);

			SetDlgItemInt(IDC_EDIT_PROFILE_MINDURATION, pstProfile->pstFrozen->nMinDuration);
		}
	}
	else if (0 == _stricmp(szType,ConvertString(NET_DIAGNOSIS_BRIGHTNESS)))
	{
		if (NULL != pstProfile->pstBrightness)
		{
			CButton* pBtn = reinterpret_cast<CButton*>(GetDlgItem(IDC_CHECK_ENABLE));
			pBtn->SetCheck(pstProfile->pstBrightness->bEnable);

			SetDlgItemInt(IDC_EDIT_PROFILE_THRESHOLD1, pstProfile->pstBrightness->bylowerThrehold1);
			SetDlgItemInt(IDC_EDIT_PROFILE_THRESHOLD1_UP, pstProfile->pstBrightness->bylowerThrehold2);
			SetDlgItemInt(IDC_EDIT_PROFILE_THRESHOLD2, pstProfile->pstBrightness->byUpperThrehold1);
			SetDlgItemInt(IDC_EDIT_PROFILE_THRESHOLD2_UP, pstProfile->pstBrightness->byUpperThrehold2);
			SetDlgItemInt(IDC_EDIT_PROFILE_MINDURATION, pstProfile->pstBrightness->nMinDuration);
		}
	}
	else if (0 == _stricmp(szType,ConvertString(NET_DIAGNOSIS_CONTRAST)))
	{
		if (NULL != pstProfile->pstContrast)
		{
			CButton* pBtn = reinterpret_cast<CButton*>(GetDlgItem(IDC_CHECK_ENABLE));
			pBtn->SetCheck(pstProfile->pstContrast->bEnable);

			SetDlgItemInt(IDC_EDIT_PROFILE_THRESHOLD1, pstProfile->pstContrast->bylowerThrehold1);
			SetDlgItemInt(IDC_EDIT_PROFILE_THRESHOLD1_UP, pstProfile->pstContrast->bylowerThrehold2);
			SetDlgItemInt(IDC_EDIT_PROFILE_THRESHOLD2, pstProfile->pstContrast->byUpperThrehold1);
			SetDlgItemInt(IDC_EDIT_PROFILE_THRESHOLD2_UP, pstProfile->pstContrast->byUpperThrehold2);
			SetDlgItemInt(IDC_EDIT_PROFILE_MINDURATION, pstProfile->pstContrast->nMinDuration);
		}
	}
	else if (0 == _stricmp(szType,ConvertString(NET_DIAGNOSIS_UNBALANCE)))
	{
		if (NULL != pstProfile->pstUnbalance)
		{
			CButton* pBtn = reinterpret_cast<CButton*>(GetDlgItem(IDC_CHECK_ENABLE));
			pBtn->SetCheck(pstProfile->pstUnbalance->bEnable);

			SetDlgItemInt(IDC_EDIT_PROFILE_THRESHOLD1, pstProfile->pstUnbalance->byThrehold1);
			SetDlgItemInt(IDC_EDIT_PROFILE_THRESHOLD2, pstProfile->pstUnbalance->byThrehold2);
			SetDlgItemInt(IDC_EDIT_PROFILE_MINDURATION, pstProfile->pstUnbalance->nMinDuration);
		}
	}
	else if (0 == _stricmp(szType,ConvertString(NET_DIAGNOSIS_NOISE)))
	{
		if (NULL != pstProfile->pstNoise)
		{
			CButton* pBtn = reinterpret_cast<CButton*>(GetDlgItem(IDC_CHECK_ENABLE));
			pBtn->SetCheck(pstProfile->pstNoise->bEnable);

			SetDlgItemInt(IDC_EDIT_PROFILE_THRESHOLD1, pstProfile->pstNoise->byThrehold1);
			SetDlgItemInt(IDC_EDIT_PROFILE_THRESHOLD2, pstProfile->pstNoise->byThrehold2);
			SetDlgItemInt(IDC_EDIT_PROFILE_MINDURATION, pstProfile->pstNoise->nMinDuration);
		}
	}
	else if (0 == _stricmp(szType,ConvertString(NET_DIAGNOSIS_BLUR)))
	{
		if (NULL != pstProfile->pstBlur)
		{
			CButton* pBtn = reinterpret_cast<CButton*>(GetDlgItem(IDC_CHECK_ENABLE));
			pBtn->SetCheck(pstProfile->pstBlur->bEnable);

			SetDlgItemInt(IDC_EDIT_PROFILE_THRESHOLD1, pstProfile->pstBlur->byThrehold1);
			SetDlgItemInt(IDC_EDIT_PROFILE_THRESHOLD2, pstProfile->pstBlur->byThrehold2);
			SetDlgItemInt(IDC_EDIT_PROFILE_MINDURATION, pstProfile->pstBlur->nMinDuration);
		}
	}
	else if (0 == _stricmp(szType,ConvertString(NET_DIAGNOSIS_SCENECHANGE)))
	{
		if (NULL != pstProfile->pstSceneChange)
		{
			CButton* pBtn = reinterpret_cast<CButton*>(GetDlgItem(IDC_CHECK_ENABLE));
			pBtn->SetCheck(pstProfile->pstSceneChange->bEnable);

			SetDlgItemInt(IDC_EDIT_PROFILE_THRESHOLD1, pstProfile->pstSceneChange->byThrehold1);
			SetDlgItemInt(IDC_EDIT_PROFILE_THRESHOLD2, pstProfile->pstSceneChange->byThrehold2);
			SetDlgItemInt(IDC_EDIT_PROFILE_MINDURATION, pstProfile->pstSceneChange->nMinDuration);
		}
	}
	UpdateData(TRUE);
}

void CProfileInfo1::GetDlgData(char* szType, CFG_VIDEO_DIAGNOSIS_PROFILE * pstProfile)
{
	if (NULL == pstProfile)
		return;

	GetDlgItemText(IDC_EDIT_PROFILE_NAME, pstProfile->szName, sizeof(pstProfile->szName));

	if (0 == _stricmp(szType, ConvertString("VideoDitherDetection")))
	{
		if (NULL != pstProfile->pstDither)
		{
			CButton* pBtn = reinterpret_cast<CButton*>(GetDlgItem(IDC_CHECK_ENABLE));
			if (BST_CHECKED == pBtn->GetCheck())
				pstProfile->pstDither->bEnable = TRUE;
			else
				pstProfile->pstDither->bEnable = FALSE;
			
			pstProfile->pstDither->byThrehold1 = GetDlgItemInt(IDC_EDIT_PROFILE_THRESHOLD1);
			pstProfile->pstDither->byThrehold2 = GetDlgItemInt(IDC_EDIT_PROFILE_THRESHOLD2);
			pstProfile->pstDither->nMinDuration = GetDlgItemInt(IDC_EDIT_PROFILE_MINDURATION);
		}
	}
	else if (0 == _stricmp(szType, ConvertString("VideoStriationDetection")))
	{
		if (NULL != pstProfile->pstStriation)
		{
			CButton* pBtn = reinterpret_cast<CButton*>(GetDlgItem(IDC_CHECK_ENABLE));
			if (BST_CHECKED == pBtn->GetCheck())
				pstProfile->pstStriation->bEnable = TRUE;
			else
				pstProfile->pstStriation->bEnable = FALSE;
			
			pstProfile->pstStriation->byThrehold1 = GetDlgItemInt(IDC_EDIT_PROFILE_THRESHOLD1);
			pstProfile->pstStriation->byThrehold2 = GetDlgItemInt(IDC_EDIT_PROFILE_THRESHOLD2);
			pstProfile->pstStriation->nMinDuration = GetDlgItemInt(IDC_EDIT_PROFILE_MINDURATION);

			pBtn = reinterpret_cast<CButton*>(GetDlgItem(IDC_CHECK_UVD));
			if (BST_CHECKED == pBtn->GetCheck())
				pstProfile->pstStriation->bUVDetection = TRUE;
			else
				pstProfile->pstStriation->bUVDetection = FALSE;
		}
	}
	else if (0 == _stricmp(szType, ConvertString("VideoLossDetection")))
	{
		if (NULL != pstProfile->pstLoss)
		{
			CButton* pBtn = reinterpret_cast<CButton*>(GetDlgItem(IDC_CHECK_ENABLE));
			if (BST_CHECKED == pBtn->GetCheck())
				pstProfile->pstLoss->bEnable = TRUE;
			else
				pstProfile->pstLoss->bEnable = FALSE;
			
			pstProfile->pstLoss->nMinDuration = GetDlgItemInt(IDC_EDIT_PROFILE_MINDURATION);
		}
	}
	else if (0 == _stricmp(szType, ConvertString("VideoCoverDetection")))
	{
		if (NULL != pstProfile->pstCover)
		{
			CButton* pBtn = reinterpret_cast<CButton*>(GetDlgItem(IDC_CHECK_ENABLE));
			if (BST_CHECKED == pBtn->GetCheck())
				pstProfile->pstCover->bEnable = TRUE;
			else
				pstProfile->pstCover->bEnable = FALSE;
			
			pstProfile->pstCover->byThrehold1 = GetDlgItemInt(IDC_EDIT_PROFILE_THRESHOLD1);
			pstProfile->pstCover->byThrehold2 = GetDlgItemInt(IDC_EDIT_PROFILE_THRESHOLD2);
			pstProfile->pstCover->nMinDuration = GetDlgItemInt(IDC_EDIT_PROFILE_MINDURATION);
		}
	}
	else if (0 == _stricmp(szType, ConvertString("VideoFrozenDetection")))
	{
		if (NULL != pstProfile->pstFrozen)
		{
			CButton* pBtn = reinterpret_cast<CButton*>(GetDlgItem(IDC_CHECK_ENABLE));
			if (BST_CHECKED == pBtn->GetCheck())
				pstProfile->pstFrozen->bEnable = TRUE;
			else
				pstProfile->pstFrozen->bEnable = FALSE;
			
			pstProfile->pstFrozen->nMinDuration = GetDlgItemInt(IDC_EDIT_PROFILE_MINDURATION);
		}
	}
	else if (0 == _stricmp(szType, ConvertString("VideoBrightnessDetection")))
	{
		if (NULL != pstProfile->pstBrightness)
		{
			CButton* pBtn = reinterpret_cast<CButton*>(GetDlgItem(IDC_CHECK_ENABLE));
			if (BST_CHECKED == pBtn->GetCheck())
				pstProfile->pstBrightness->bEnable = TRUE;
			else
				pstProfile->pstBrightness->bEnable = FALSE;
			
			pstProfile->pstBrightness->bylowerThrehold1 = GetDlgItemInt(IDC_EDIT_PROFILE_THRESHOLD1);
			pstProfile->pstBrightness->bylowerThrehold2 = GetDlgItemInt(IDC_EDIT_PROFILE_THRESHOLD1_UP);
			pstProfile->pstBrightness->byUpperThrehold1 = GetDlgItemInt(IDC_EDIT_PROFILE_THRESHOLD2);
			pstProfile->pstBrightness->byUpperThrehold2 = GetDlgItemInt(IDC_EDIT_PROFILE_THRESHOLD2_UP);
			pstProfile->pstBrightness->nMinDuration = GetDlgItemInt(IDC_EDIT_PROFILE_MINDURATION);
		}
	}
	else if (0 == _stricmp(szType, ConvertString("VideoContrastDetection")))
	{
		if (NULL != pstProfile->pstContrast)
		{
			CButton* pBtn = reinterpret_cast<CButton*>(GetDlgItem(IDC_CHECK_ENABLE));
			if (BST_CHECKED == pBtn->GetCheck())
				pstProfile->pstContrast->bEnable = TRUE;
			else
				pstProfile->pstContrast->bEnable = FALSE;
			
			pstProfile->pstContrast->bylowerThrehold1 = GetDlgItemInt(IDC_EDIT_PROFILE_THRESHOLD1);
			pstProfile->pstContrast->bylowerThrehold2 = GetDlgItemInt(IDC_EDIT_PROFILE_THRESHOLD1_UP);
			pstProfile->pstContrast->byUpperThrehold1 = GetDlgItemInt(IDC_EDIT_PROFILE_THRESHOLD2);
			pstProfile->pstContrast->byUpperThrehold2 = GetDlgItemInt(IDC_EDIT_PROFILE_THRESHOLD2_UP);
			pstProfile->pstContrast->nMinDuration = GetDlgItemInt(IDC_EDIT_PROFILE_MINDURATION);
		}
	}
	else if (0 == _stricmp(szType, ConvertString("VideoUnbalanceDetection")))
	{
		if (NULL != pstProfile->pstUnbalance)
		{
			CButton* pBtn = reinterpret_cast<CButton*>(GetDlgItem(IDC_CHECK_ENABLE));
			if (BST_CHECKED == pBtn->GetCheck())
				pstProfile->pstUnbalance->bEnable = TRUE;
			else
				pstProfile->pstUnbalance->bEnable = FALSE;
			
			pstProfile->pstUnbalance->byThrehold1 = GetDlgItemInt(IDC_EDIT_PROFILE_THRESHOLD1);
			pstProfile->pstUnbalance->byThrehold2 = GetDlgItemInt(IDC_EDIT_PROFILE_THRESHOLD2);
			pstProfile->pstUnbalance->nMinDuration = GetDlgItemInt(IDC_EDIT_PROFILE_MINDURATION);
		}
	}
	else if (0 == _stricmp(szType, ConvertString("VideoNoiseDetection")))
	{
		if (NULL != pstProfile->pstNoise)
		{
			CButton* pBtn = reinterpret_cast<CButton*>(GetDlgItem(IDC_CHECK_ENABLE));
			if (BST_CHECKED == pBtn->GetCheck())
				pstProfile->pstNoise->bEnable = TRUE;
			else
				pstProfile->pstNoise->bEnable = FALSE;
			
			pstProfile->pstNoise->byThrehold1 = GetDlgItemInt(IDC_EDIT_PROFILE_THRESHOLD1);
			pstProfile->pstNoise->byThrehold2 = GetDlgItemInt(IDC_EDIT_PROFILE_THRESHOLD2);
			pstProfile->pstNoise->nMinDuration = GetDlgItemInt(IDC_EDIT_PROFILE_MINDURATION);
		}
	}
	else if (0 == _stricmp(szType, ConvertString("VideoBlurDetection")))
	{
		if (NULL != pstProfile->pstBlur)
		{
			CButton* pBtn = reinterpret_cast<CButton*>(GetDlgItem(IDC_CHECK_ENABLE));
			if (BST_CHECKED == pBtn->GetCheck())
				pstProfile->pstBlur->bEnable = TRUE;
			else
				pstProfile->pstBlur->bEnable = FALSE;
			
			pstProfile->pstBlur->byThrehold1 = GetDlgItemInt(IDC_EDIT_PROFILE_THRESHOLD1);
			pstProfile->pstBlur->byThrehold2 = GetDlgItemInt(IDC_EDIT_PROFILE_THRESHOLD2);
			pstProfile->pstBlur->nMinDuration = GetDlgItemInt(IDC_EDIT_PROFILE_MINDURATION);
		}
	}
	else if (0 == _stricmp(szType, ConvertString("VideoSceneChangeDetection")))
	{
		if (NULL != pstProfile->pstSceneChange)
		{
			CButton* pBtn = reinterpret_cast<CButton*>(GetDlgItem(IDC_CHECK_ENABLE));
			if (BST_CHECKED == pBtn->GetCheck())
				pstProfile->pstSceneChange->bEnable = TRUE;
			else
				pstProfile->pstSceneChange->bEnable = FALSE;
			
			pstProfile->pstSceneChange->byThrehold1 = GetDlgItemInt(IDC_EDIT_PROFILE_THRESHOLD1);
			pstProfile->pstSceneChange->byThrehold2 = GetDlgItemInt(IDC_EDIT_PROFILE_THRESHOLD2);
			pstProfile->pstSceneChange->nMinDuration = GetDlgItemInt(IDC_EDIT_PROFILE_MINDURATION);
		}
	}
}

BOOL CProfileInfo1::OnInitDialog()
{
	CDialog::OnInitDialog();
	g_SetWndStaticText(this);

	return TRUE;
}

void CProfileInfo1::OnChangeEditProfileName() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	if (NULL == m_pParent)
	{
		return;
	}

	//m_pParent->OnProfileNameChanged();
}
