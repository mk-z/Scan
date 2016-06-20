// ConfigVideoIn.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo5.h"
#include "ConfigVideoIn.h"
#include "ClientDemo5Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CConfigVideoIn dialog


CConfigVideoIn::CConfigVideoIn(CWnd* pParent /*=NULL*/)
	: CDialog(CConfigVideoIn::IDD, pParent)
{
	//{{AFX_DATA_INIT(CConfigVideoIn)
	m_GainMin = 0;
	m_GainMax = 0;
	m_ExpMax = 0.0f;
	m_ExpMin = 0.0f;
	m_ExpSpeed = 0;
	m_GainBule = 0;
	m_GainRed = 0;
	m_StartHour = 0;
	m_StartMinute = 0;
	m_StartSecond = 0;
	m_EndHour = 0;
	m_EndMinute = 0;
	m_EndSecond = 0;
	m_Left = 0;
	m_Right = 0;
	m_Bottom = 0;
	m_Top = 0;
	m_WideDynamicRange = 0;
	m_GlareInhiBition = 0;
	//}}AFX_DATA_INIT
	m_pstCapVideoInput = NULL;
	m_pstVideoInOption = NULL;
	m_nChannelCount    = 0;
	m_nCurChannel      = -1;
	m_nCurTypeOption   = -1;
	m_nCurExpmode      = -1;
}


void CConfigVideoIn::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CConfigVideoIn)
	DDX_Control(pDX, IDC_COMBO_BACKLIGHTMODE, m_ctlBlackLightMode);
	DDX_Control(pDX, IDC_COMBO_OPTIONSWITCH, m_ctlOptionSwitch);
	DDX_Control(pDX, IDC_CHECK_IRISAUTO, m_ctlIrisAuto);
	DDX_Control(pDX, IDC_CHECK_MIRROR, m_ctlMirror);
	DDX_Control(pDX, IDC_CHECK_FLIP, m_ctlFlip);
	DDX_Control(pDX, IDC_COMBO_ROTATE, m_ctlRotate);
	DDX_Control(pDX, IDC_COMBO_DAYNIGHTCOLOR, m_ctlDayNightColor);
	DDX_Control(pDX, IDC_COMBO_WHITEBALANCE, m_ctlWhiteBalance);
	DDX_Control(pDX, IDC_COMBO_EXPMODE, m_ctlExpMode);
	DDX_Control(pDX, IDC_COMBO_ANTIFLIKER, m_ctlAntiFliker);
	DDX_Control(pDX, IDC_COMBO_OPTIONTYPE, m_ctlOptionType);
	DDX_Control(pDX, IDC_COMBO_CHANNO, m_ctlChannel);
	DDX_Text(pDX, IDC_EDIT_GAINMIN, m_GainMin);
	DDX_Text(pDX, IDC_EDIT_GAINMAX, m_GainMax);
	DDX_Text(pDX, IDC_EDIT_EXPVAMAX, m_ExpMax);
	DDX_Text(pDX, IDC_EDIT_EXPVAMIN, m_ExpMin);
	DDX_Text(pDX, IDC_EDIT_GAINBLUE, m_GainBule);
	DDV_MinMaxInt(pDX, m_GainBule, 0, 100);
	DDX_Text(pDX, IDC_EDIT_GAINRED, m_GainRed);
	DDV_MinMaxInt(pDX, m_GainRed, 0, 100);
	DDX_Text(pDX, IDC_EDIT_STARTHOUR, m_StartHour);
	DDX_Text(pDX, IDC_EDIT_STARTMINUTE, m_StartMinute);
	DDX_Text(pDX, IDC_EDIT_STARTSECOND, m_StartSecond);
	DDX_Text(pDX, IDC_EDIT_ENDHOUR, m_EndHour);
	DDX_Text(pDX, IDC_EDIT_ENDMINUTE, m_EndMinute);
	DDX_Text(pDX, IDC_EDIT_ENDSECOND, m_EndSecond);
	DDX_Text(pDX, IDC_EDIT_MLEFT2, m_Left);
	DDX_Text(pDX, IDC_EDIT_MRIGHT2, m_Right);
	DDX_Text(pDX, IDC_EDIT_MBOTTOM, m_Bottom);
	DDX_Text(pDX, IDC_EDIT_MTOP2, m_Top);
	DDX_Text(pDX, IDC_EDIT_WIDEDYNAMICRANGE, m_WideDynamicRange);
	DDX_Text(pDX, IDC_EDIT_GLAREINHIBITION, m_GlareInhiBition);
	DDX_Text(pDX, IDC_EDIT_EXPSPEED, m_ExpSpeed);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CConfigVideoIn, CDialog)
	//{{AFX_MSG_MAP(CConfigVideoIn)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, OnButtonSave)
	ON_BN_CLICKED(IDC_BUTTON_READALL, OnButtonReadall)
	ON_CBN_SELCHANGE(IDC_COMBO_CHANNO, OnSelchangeComboChanno)
	ON_CBN_SELCHANGE(IDC_COMBO_OPTIONTYPE, OnSelchangeComboOptiontype)
	ON_CBN_SELCHANGE(IDC_COMBO_ANTIFLIKER, OnSelchangeComboAntifliker)
	ON_CBN_SELCHANGE(IDC_COMBO_EXPMODE, OnSelchangeComboExpmode)
	ON_CBN_SELCHANGE(IDC_COMBO_OPTIONSWITCH, OnSelchangeComboOptionswitch)
	ON_CBN_SELCHANGE(IDC_COMBO_BACKLIGHTMODE, OnSelchangeComboBacklightmode)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CConfigVideoIn message handlers

void CConfigVideoIn::OnButtonSave() 
{
	// TODO: Add your control notification handler code here
	BOOL bSuccess = UpdateData(TRUE);
	if (!bSuccess)
	{
		return;
	}
	if(-1 != m_ctlChannel.GetCurSel())
	{
		SaveChannelInfo(m_nCurChannel);
		((CClientDemo5Dlg*)AfxGetMainWnd())->SetOneVideoInOption(&m_pstVideoInOption[m_nCurChannel],m_nCurChannel);
	}
	else
	{
		MessageBox(ConvertString("Input error!"), ConvertString("Prompt"));
	}

}

void CConfigVideoIn::OnButtonReadall() 
{
	// TODO: Add your control notification handler code here
	CleanAll();

	((CClientDemo5Dlg*)AfxGetMainWnd())->GetVideoInputOption();
}
void  CConfigVideoIn::InitDlgInfo(int nChannelCount)
{

	m_nChannelCount = nChannelCount;
	m_pstCapVideoInput = new CFG_CAP_VIDEOINPUT_INFO[CHANNEL_NUM_LIMIT];
	if(NULL == m_pstCapVideoInput)
	{
		return;
	}
	else
	{
		memset(m_pstCapVideoInput, 0 ,CHANNEL_NUM_LIMIT*sizeof(CFG_CAP_VIDEOINPUT_INFO));
	}

	m_pstVideoInOption = new CFG_VIDEO_IN_OPTIONS[CHANNEL_NUM_LIMIT];
	if(NULL == m_pstVideoInOption)
	{
		delete[] m_pstCapVideoInput;
		m_pstCapVideoInput = NULL;
		return;
	}
	else
	{
		memset(m_pstVideoInOption, 0 ,CHANNEL_NUM_LIMIT*sizeof(CFG_VIDEO_IN_OPTIONS));
	}
	
	int i = 0;
	int nIndex = 0;
	CString str;
	m_ctlChannel.ResetContent();
	for(i = 0; i < m_nChannelCount; i++)
	{
		str.Format("%d",i+1);
		nIndex = m_ctlChannel.AddString(str);
		m_ctlChannel.SetItemData(nIndex,i);
		//Save channel video information 
	}
	
	m_ctlOptionType.ResetContent();
	nIndex = 0;
	str.Format("Normal Option");
	nIndex = m_ctlOptionType.AddString(ConvertString(str));
	m_ctlOptionType.SetItemData(nIndex,0);
	
	str.Format("Day Option");
	nIndex = m_ctlOptionType.AddString(ConvertString(str));
	m_ctlOptionType.SetItemData(nIndex,1);
	
	str.Format("Night Option");
	nIndex = m_ctlOptionType.AddString(ConvertString(str));
	m_ctlOptionType.SetItemData(nIndex,2);

	
	m_ctlAntiFliker.ResetContent();
	nIndex = 0;
	nIndex = m_ctlAntiFliker.AddString(ConvertString("Outdoor"));
	m_ctlAntiFliker.SetItemData(nIndex,0);

	nIndex = m_ctlAntiFliker.AddString(ConvertString("50Hz"));
	m_ctlAntiFliker.SetItemData(nIndex,1);

	nIndex = m_ctlAntiFliker.AddString(ConvertString("60Hz"));
	m_ctlAntiFliker.SetItemData(nIndex,2);
	

	

	m_ctlWhiteBalance.ResetContent();
	nIndex = m_ctlWhiteBalance.AddString(ConvertString("Disable"));
	m_ctlWhiteBalance.SetItemData(nIndex,0);

	nIndex = m_ctlWhiteBalance.AddString(ConvertString("Auto"));
	m_ctlWhiteBalance.SetItemData(nIndex,1);

	nIndex = m_ctlWhiteBalance.AddString(ConvertString("Sunny"));
	m_ctlWhiteBalance.SetItemData(nIndex,3);
	
	nIndex = m_ctlWhiteBalance.AddString(ConvertString("Night"));
	m_ctlWhiteBalance.SetItemData(nIndex,7);

	nIndex = m_ctlWhiteBalance.AddString(ConvertString("Custom"));
	m_ctlWhiteBalance.SetItemData(nIndex,2);



	m_ctlDayNightColor.ResetContent();
	nIndex = m_ctlDayNightColor.AddString(ConvertString("Multicolour"));
	m_ctlDayNightColor.SetItemData(nIndex,0);
	
	nIndex = m_ctlDayNightColor.AddString(ConvertString("Auto"));
	m_ctlDayNightColor.SetItemData(nIndex,1);

	nIndex = m_ctlDayNightColor.AddString(ConvertString("Black and white"));
	m_ctlDayNightColor.SetItemData(nIndex,2);


	m_ctlRotate.ResetContent();
	nIndex = m_ctlRotate.AddString(ConvertString("Irrotional"));
	m_ctlRotate.SetItemData(nIndex,0);
	nIndex = m_ctlRotate.AddString(ConvertString("Clockwise 90"));
	m_ctlRotate.SetItemData(nIndex,1);
	nIndex = m_ctlRotate.AddString(ConvertString("AntiClockwise 90"));
	m_ctlRotate.SetItemData(nIndex,2);
	

	m_ctlOptionSwitch.ResetContent();
	nIndex = m_ctlOptionSwitch.AddString(ConvertString("Always day option"));
	m_ctlOptionSwitch.SetItemData(nIndex,0);
	nIndex = m_ctlOptionSwitch.AddString(ConvertString("According brightness"));
	m_ctlOptionSwitch.SetItemData(nIndex,1);
	nIndex = m_ctlOptionSwitch.AddString(ConvertString("According time"));
	m_ctlOptionSwitch.SetItemData(nIndex,2); 
	nIndex = m_ctlOptionSwitch.AddString(ConvertString("Always night option"));
	m_ctlOptionSwitch.SetItemData(nIndex,3);
	nIndex = m_ctlOptionSwitch.AddString(ConvertString("Always normal option"));
	m_ctlOptionSwitch.SetItemData(nIndex,4);

	
	m_ctlBlackLightMode.ResetContent();
	nIndex = m_ctlBlackLightMode.AddString(ConvertString("Close"));
	m_ctlBlackLightMode.SetItemData(nIndex,0);
	nIndex = m_ctlBlackLightMode.AddString(ConvertString("Open"));
	m_ctlBlackLightMode.SetItemData(nIndex,1);
	nIndex = m_ctlBlackLightMode.AddString(ConvertString("Designated area"));
	m_ctlBlackLightMode.SetItemData(nIndex,2);

	if(0 < m_ctlChannel.GetCount())
	{

		m_ctlChannel.SetCurSel(0);
		OnSelchangeComboChanno();
	}


}
void CConfigVideoIn::CleanAll()
{
	m_ctlChannel.SetCurSel(-1);
	m_ctlAntiFliker.SetCurSel(-1);
	m_ctlBlackLightMode.SetCurSel(-1);
	m_ctlDayNightColor.SetCurSel(-1);
	m_ctlOptionSwitch.SetCurSel(-1);
	m_ctlOptionType.SetCurSel(-1);
	m_ctlRotate.SetCurSel(-1);
	m_ctlWhiteBalance.SetCurSel(-1);
	m_ctlExpMode.SetCurSel(-1);
	
	SetDlgItemText(IDC_EDIT_GAINMIN,"");
	SetDlgItemText(IDC_EDIT_GAINMAX,"");
	SetDlgItemText(IDC_EDIT_EXPVAMIN,"");
	SetDlgItemText(IDC_EDIT_EXPVAMAX,"");
	SetDlgItemText(IDC_EDIT_GAINRED,"");
	SetDlgItemText(IDC_EDIT_GAINBLUE,"");
	SetDlgItemText(IDC_EDIT_WIDEDYNAMICRANGE,"");
	SetDlgItemText(IDC_EDIT_GLAREINHIBITION,"");
	SetDlgItemText(IDC_EDIT_MLEFT2,"");
	SetDlgItemText(IDC_EDIT_MTOP2,"");
	SetDlgItemText(IDC_EDIT_MRIGHT2,"");
	SetDlgItemText(IDC_EDIT_MBOTTOM,"");
	SetDlgItemText(IDC_EDIT_STARTHOUR,"");
	SetDlgItemText(IDC_EDIT_STARTMINUTE,"");
	SetDlgItemText(IDC_EDIT_STARTSECOND,"");
	SetDlgItemText(IDC_EDIT_ENDHOUR,"");
	SetDlgItemText(IDC_EDIT_ENDMINUTE,"");
	SetDlgItemText(IDC_EDIT_ENDSECOND,"");
	SetDlgItemText(IDC_EDIT_EXPSPEED,"");


	m_ctlMirror.SetCheck(0);
	m_ctlIrisAuto.SetCheck(0);
	m_ctlFlip.SetCheck(0);

	
	m_nChannelCount = 0;
	m_nCurChannel   = -1;
	m_nCurTypeOption = -1;
		
	

	if(m_pstVideoInOption)
	{
		delete[] m_pstVideoInOption;
		m_pstVideoInOption = NULL;
	}
	if(m_pstCapVideoInput)
	{
		delete[] m_pstCapVideoInput;
		m_pstCapVideoInput = NULL;
	}
}

void CConfigVideoIn::OnSelchangeComboChanno() 
{
	// TODO: Add your control notification handler code here
	int nIndex = m_ctlChannel.GetCurSel();
	if(CB_ERR != nIndex)
	{
		int nNum = (int)m_ctlChannel.GetItemData(nIndex);	
		SaveChannelInfo(m_nCurChannel);
		
		((CClientDemo5Dlg*)AfxGetMainWnd())->GetOneVideoCapVieoInfo(&m_pstCapVideoInput[nNum],nIndex);
		((CClientDemo5Dlg*)AfxGetMainWnd())->GetOneVideoInOption(&m_pstVideoInOption[nNum],nIndex);

	
		m_ctlOptionType.SetCurSel(0);
		OnSelchangeComboOptiontype();
		m_nCurChannel = nNum;
	}
}

void CConfigVideoIn::OnSelchangeComboOptiontype() 
{
	// TODO: Add your control notification handler code here
	int nIndex = m_ctlOptionType.GetCurSel();
	if(CB_ERR != nIndex)
	{
		int nItem = m_ctlOptionType.GetItemData(nIndex);
		nIndex = m_ctlChannel.GetCurSel();
		if(CB_ERR != nIndex)
		{
			int nNum = m_ctlChannel.GetItemData(nIndex);
			//First save Option Info
			SaveOptionInfo(m_nCurChannel,m_nCurTypeOption);
			m_nCurTypeOption = nItem;
			//Display bit stream information 
			ShowOptionInfo(nNum,nItem);
		}
	}




	
}
void CConfigVideoIn::ShowOptionInfo(int nNum,int nItem)
{
	if(NULL == m_pstVideoInOption || NULL == m_pstCapVideoInput)
	{
		return;
	}

	BYTE AntiFlicker   = 0;
	BYTE ExposureMode  = 0;
	BYTE WhiteBalance  = 0;
	BYTE DayNightColor = 0;
	BYTE Rotate        = 0;
	bool IrisAuto	   = 0;
	bool mirror		   = 0;
	bool bFlip		   = 0;
	BYTE GainMin       = 0;
	BYTE GainMax       = 0;
	float ExpMin       = 0;
	float ExpMax       = 0;
	BYTE  ExpSpeed     = 0;
	BYTE  Backlight    = 0;
	BYTE  GainBule     = 0;
	BYTE  GainRed      = 0;
	int   Left         = 0;
	int   Top          = 0;
	int   Right        = 0;
	int   Bottom       = 0;
	BYTE  WideDynamicRange  = 0;
	BYTE  GlareInhibition = 0;


	
	BYTE SwitchMode    = m_pstVideoInOption[nNum].stuNightOptions.bySwitchMode;
	BYTE SunriseHour   = m_pstVideoInOption[nNum].stuNightOptions.bySunriseHour;
	BYTE SunriseMinute = m_pstVideoInOption[nNum].stuNightOptions.bySunriseMinute;
	BYTE SunriseSecond = m_pstVideoInOption[nNum].stuNightOptions.bySunriseSecond;
	BYTE SunsetHour    = m_pstVideoInOption[nNum].stuNightOptions.bySunsetHour;
	BYTE SunsetMinute  = m_pstVideoInOption[nNum].stuNightOptions.bySunsetMinute;
	BYTE SunsetSecond  = m_pstVideoInOption[nNum].stuNightOptions.bySunsetSecond;



	if(nItem == 0) //Normal Option
	{
		 AntiFlicker   = m_pstVideoInOption[nNum].stuNormalOptions.byAntiFlicker;
		 ExposureMode  = m_pstVideoInOption[nNum].stuNormalOptions.byExposureMode;
		 WhiteBalance  = m_pstVideoInOption[nNum].stuNormalOptions.byWhiteBalance;
		 DayNightColor = m_pstVideoInOption[nNum].stuNormalOptions.byDayNightColor;
		 Rotate        = m_pstVideoInOption[nNum].stuNormalOptions.byRotate90;
		 IrisAuto	   = m_pstVideoInOption[nNum].stuNormalOptions.bIrisAuto;
		 mirror		   = m_pstVideoInOption[nNum].stuNormalOptions.bMirror;	
		 bFlip		   = m_pstVideoInOption[nNum].stuNormalOptions.bFlip;	
		 GainMin       = m_pstVideoInOption[nNum].stuNormalOptions.byGainMin;
		 GainMax       = m_pstVideoInOption[nNum].stuNormalOptions.byGainMax;
		 ExpMin        = m_pstVideoInOption[nNum].stuNormalOptions.fExposureValue1;
		 ExpMax        = m_pstVideoInOption[nNum].stuNormalOptions.fExposureValue2;
		 ExpSpeed      = m_pstVideoInOption[nNum].stuNormalOptions.byExposure;
		 Backlight     = m_pstVideoInOption[nNum].stuNormalOptions.byBacklight;
		 GainBule      = m_pstVideoInOption[nNum].stuNormalOptions.byGainBlue;
	     GainRed       = m_pstVideoInOption[nNum].stuNormalOptions.byGainRed;
	     Left          = m_pstVideoInOption[nNum].stuNormalOptions.stuBacklightRegion.nLeft;
		 Top		   = m_pstVideoInOption[nNum].stuNormalOptions.stuBacklightRegion.nTop;
		 Right	       = m_pstVideoInOption[nNum].stuNormalOptions.stuBacklightRegion.nRight;
		 Bottom        = m_pstVideoInOption[nNum].stuNormalOptions.stuBacklightRegion.nBottom;
		 WideDynamicRange  = m_pstVideoInOption[nNum].stuNormalOptions.byWideDynamicRange;
		 GlareInhibition   = m_pstVideoInOption[nNum].stuNormalOptions.byGlareInhibition;
	}	 
	else if(nItem == 1) //day
	{
		AntiFlicker   = m_pstVideoInOption[nNum].byAntiFlicker;
		ExposureMode  = m_pstVideoInOption[nNum].byExposureMode;
		WhiteBalance  = m_pstVideoInOption[nNum].byWhiteBalance;
		DayNightColor = m_pstVideoInOption[nNum].byDayNightColor;
		Rotate        = m_pstVideoInOption[nNum].byRotate90;
		IrisAuto	  = m_pstVideoInOption[nNum].bIrisAuto;
		mirror		  = m_pstVideoInOption[nNum].bMirror;
		bFlip		  = m_pstVideoInOption[nNum].bFlip;
		GainMin       = m_pstVideoInOption[nNum].byGainMin;
		GainMax       = m_pstVideoInOption[nNum].byGainMax;
		ExpMin        = m_pstVideoInOption[nNum].fExposureValue1;
		ExpMax        = m_pstVideoInOption[nNum].fExposureValue2;
		ExpSpeed      = m_pstVideoInOption[nNum].byExposure;
		Backlight     = m_pstVideoInOption[nNum].byBacklight;
		GainBule      = m_pstVideoInOption[nNum].byGainBlue;
	    GainRed       = m_pstVideoInOption[nNum].byGainRed;
		Left          = m_pstVideoInOption[nNum].stuBacklightRegion.nLeft;
		Top		      = m_pstVideoInOption[nNum].stuBacklightRegion.nTop;
		Right	      = m_pstVideoInOption[nNum].stuBacklightRegion.nRight;
		Bottom        = m_pstVideoInOption[nNum].stuBacklightRegion.nBottom;
		WideDynamicRange  = m_pstVideoInOption[nNum].byWideDynamicRange;
		GlareInhibition   = m_pstVideoInOption[nNum].byGlareInhibition;
	}
	else if(nItem == 2) //night
	{
		AntiFlicker   = m_pstVideoInOption[nNum].stuNightOptions.byAntiFlicker;
		ExposureMode  = m_pstVideoInOption[nNum].stuNightOptions.byExposureMode;
		WhiteBalance  = m_pstVideoInOption[nNum].stuNightOptions.byWhiteBalance;
		DayNightColor = m_pstVideoInOption[nNum].stuNightOptions.byDayNightColor;
		Rotate        = m_pstVideoInOption[nNum].stuNightOptions.byRotate90;
		IrisAuto	  = m_pstVideoInOption[nNum].stuNightOptions.bIrisAuto;
		mirror		  = m_pstVideoInOption[nNum].stuNightOptions.bMirror;
		bFlip		  = m_pstVideoInOption[nNum].stuNightOptions.bFlip;
		GainMin       = m_pstVideoInOption[nNum].stuNightOptions.byGainMin;
		GainMax       = m_pstVideoInOption[nNum].stuNightOptions.byGainMax;
		ExpMin        = m_pstVideoInOption[nNum].stuNightOptions.fExposureValue1;
		ExpMax        = m_pstVideoInOption[nNum].stuNightOptions.fExposureValue2;
		ExpSpeed      = m_pstVideoInOption[nNum].stuNightOptions.byExposure;
		Backlight     = m_pstVideoInOption[nNum].stuNightOptions.byBacklight;
		GainBule      = m_pstVideoInOption[nNum].stuNightOptions.byGainBlue;
	    GainRed       = m_pstVideoInOption[nNum].stuNightOptions.byGainRed;
		Left          = m_pstVideoInOption[nNum].stuNightOptions.stuBacklightRegion.nLeft;
		Top		      = m_pstVideoInOption[nNum].stuNightOptions.stuBacklightRegion.nTop;
		Right	      = m_pstVideoInOption[nNum].stuNightOptions.stuBacklightRegion.nRight;
		Bottom        = m_pstVideoInOption[nNum].stuNightOptions.stuBacklightRegion.nBottom;
		WideDynamicRange  = m_pstVideoInOption[nNum].stuNightOptions.byWideDynamicRange;
		GlareInhibition   = m_pstVideoInOption[nNum].stuNightOptions.byGlareInhibition;
	}
	int nIndex = 0;
	CString str;
	m_ctlExpMode.ResetContent();

	if(AntiFlicker == 0) //outdoor
	{
		nIndex = 0;
		m_ctlAntiFliker.SetCurSel(0);
		str.Format("Auto"); // 自动
		nIndex = m_ctlExpMode.AddString(ConvertString(str));
		m_ctlExpMode.SetItemData(nIndex, 0);
			
		str.Format("Low yawp"); //低噪声
		nIndex = m_ctlExpMode.AddString(ConvertString(str));
		m_ctlExpMode.SetItemData(nIndex, 1);
	
		str.Format("None shadow");//防拖影
		nIndex = m_ctlExpMode.AddString(ConvertString(str));
		m_ctlExpMode.SetItemData(nIndex, 2);
	
	
		str.Format("manual");//手动
		nIndex = m_ctlExpMode.AddString(ConvertString(str));
		m_ctlExpMode.SetItemData(nIndex, 4);

		if(ExposureMode == 0)
		{
			m_ctlExpMode.SetCurSel(0);
		}
		else if(ExposureMode == 1)
		{
			m_ctlExpMode.SetCurSel(1);
		}
		else if(ExposureMode == 2)
		{
			m_ctlExpMode.SetCurSel(2);
		}
		else if(ExposureMode == 4)
		{
			m_ctlExpMode.SetCurSel(3);
		}
	}
	else if(AntiFlicker == 1 //50hz,60hz
			|| AntiFlicker == 2)
	{
		if(AntiFlicker == 1)
		{
			m_ctlAntiFliker.SetCurSel(1);
		}
		else
		{
			m_ctlAntiFliker.SetCurSel(2);
		}
			
		nIndex = 0;

		str.Format("Auto"); // 自动
		nIndex = m_ctlExpMode.AddString(ConvertString(str));
		m_ctlExpMode.SetItemData(nIndex, 0);
			
		str.Format("manual");//手动
		nIndex = m_ctlExpMode.AddString(ConvertString(str));
		m_ctlExpMode.SetItemData(nIndex, 4);
			
		if(ExposureMode == 0)
		{
			m_ctlExpMode.SetCurSel(0);
		}
		else if(ExposureMode == 4)
		{
			m_ctlExpMode.SetCurSel(1);
		}
	}
	m_GainMin = GainMin;
	m_GainMax = GainMax;
	
	m_ExpMin  = ExpMin;
	m_ExpMax  = ExpMax;
		
	m_ExpSpeed = ExpSpeed;

	m_GainBule = GainBule;
	m_GainRed  = GainRed;
	
	if(m_pstCapVideoInput[nNum].nWideDynamicRange)
	{
		GetDlgItem(IDC_EDIT_WIDEDYNAMICRANGE)->EnableWindow(TRUE);
	}

	if(m_pstCapVideoInput[nNum].nGlareInhibition)
	{
		GetDlgItem(IDC_EDIT_GLAREINHIBITION)->EnableWindow(TRUE);
	}

	m_WideDynamicRange = WideDynamicRange;
	m_GlareInhiBition  = GlareInhibition;
	
	if(WhiteBalance == 0)//Disable
	{
		m_ctlWhiteBalance.SetCurSel(0);
	}
	else if(WhiteBalance == 1) //Auto
	{
		m_ctlWhiteBalance.SetCurSel(1);
	}
	else if(WhiteBalance == 3)//Sunny
	{
		m_ctlWhiteBalance.SetCurSel(2);
	}
	else if(WhiteBalance == 7)//Night
	{
		m_ctlWhiteBalance.SetCurSel(3);
	}
	else if(WhiteBalance == 2)//Custom
	{
		m_ctlWhiteBalance.SetCurSel(4);
	}

	
	m_ctlBlackLightMode.SetCurSel(Backlight);
	OnSelchangeComboBacklightmode();


	m_ctlMirror.SetCheck(mirror);
	m_ctlFlip.SetCheck(bFlip);
	m_ctlIrisAuto.SetCheck(IrisAuto);
		
	m_ctlDayNightColor.SetCurSel(DayNightColor);

	m_ctlRotate.SetCurSel(Rotate);

	m_ctlOptionSwitch.SetCurSel(SwitchMode);
	OnSelchangeComboOptionswitch();

	m_StartHour   = SunriseHour;
	m_StartMinute = SunriseMinute;
	m_StartSecond = SunriseSecond;

	m_EndHour     = SunsetHour;
	m_EndMinute   = SunsetMinute;
	m_EndSecond   = SunsetSecond;
	
	UpdateData(FALSE);
}
BOOL CConfigVideoIn::SaveOptionInfo(int nNum,int nItem)
{
	if(NULL == m_pstCapVideoInput || NULL == m_pstVideoInOption)
	{
		return FALSE;
	}
	if(nNum < 0 || nItem < 0)
	{
		return FALSE;
	}


	BYTE AntiFlicker   = 0;
	BYTE ExposureMode  = 0;
	BYTE WhiteBalance  = 0;
	BYTE DayNightColor = 0;
	BYTE Rotate        = 0;
	bool IrisAuto	   = 0;
	bool mirror		   = 0;
	bool bFlip		   = 0;
	BYTE GainMin       = 0;
	BYTE GainMax       = 0;
	float ExpMin       = 0;
	float ExpMax       = 0;
	BYTE  ExpSpeed     = 0;
	BYTE  Backlight    = 0;
	BYTE  GainBule     = 0;
	BYTE  GainRed      = 0;
	int   Left         = 0;
	int   Top          = 0;
	int   Right        = 0;
	int   Bottom       = 0;
	BYTE  WideDynamicRange  = 0;
	BYTE  GlareInhibition = 0;

	BYTE SwitchMode    = 0;
	BYTE SunriseHour   = 0;
	BYTE SunriseMinute = 0;
	BYTE SunriseSecond = 0;
	BYTE SunsetHour    = 0;
	BYTE SunsetMinute  = 0;
	BYTE SunsetSecond  = 0;

	
	UpdateData(TRUE);

	int nIndex = m_ctlAntiFliker.GetCurSel();
	if(CB_ERR != nIndex)
	{
		AntiFlicker = m_ctlAntiFliker.GetItemData(nIndex);
	}
	else
	{
		return FALSE;
	}

	nIndex = m_ctlExpMode.GetCurSel();
	if(CB_ERR != nIndex)
	{
		ExposureMode = m_ctlExpMode.GetItemData(nIndex);
	}
	else
	{
		return FALSE;
	}

	nIndex = m_ctlDayNightColor.GetCurSel();
	if(CB_ERR != nIndex)
	{
		DayNightColor = m_ctlDayNightColor.GetItemData(nIndex);
	}
	else
	{
		return FALSE;
	}

	if(m_GainMax  < m_GainMin)
	{
		MessageBox(ConvertString("Gain MAX should be bigger than the Gain min"));
		return FALSE;
	}
	
	GainMax = m_GainMax;
	GainMin = m_GainMin;

	if(m_ExpMax < m_ExpMin)
	{
		MessageBox(ConvertString("Exposure Max should be bigger than  the Exposure min"));
		return FALSE;
	}

	if ((4 == ExposureMode) && (0 >= m_ExpSpeed))
	{
		MessageBox(ConvertString("ExpSpeed must more than 1 in manual mode"));
	}

	ExpMax = m_ExpMax;
	ExpMin = m_ExpMin;

	ExpSpeed = m_ExpSpeed; //范围

	nIndex = m_ctlWhiteBalance.GetCurSel();
	if(CB_ERR != nIndex)
	{
		WhiteBalance = m_ctlWhiteBalance.GetItemData(nIndex);
		GainBule = m_GainBule;
		GainRed  = m_GainRed;
	}
	else
	{
		return FALSE;
	}


	nIndex = m_ctlBlackLightMode.GetCurSel();
	if(CB_ERR != nIndex)
	{
		Backlight = m_ctlBlackLightMode.GetCurSel();
		Left   = m_Left;
		Top    = m_Top;
		Right  = m_Right;
		Bottom = m_Bottom;
	}
	else
	{
		return FALSE;
	}

	WideDynamicRange = m_WideDynamicRange;
	GlareInhibition  = m_GlareInhiBition;

	IrisAuto  = m_ctlIrisAuto.GetCheck();
	mirror    = m_ctlMirror.GetCheck();
	bFlip     = m_ctlFlip.GetCheck();

	nIndex = m_ctlBlackLightMode.GetCurSel();
	if(CB_ERR != nIndex)
	{
		Backlight = m_ctlBlackLightMode.GetItemData(nIndex);
	}
	else
	{
		return FALSE;
	}

	nIndex = m_ctlRotate.GetCurSel();
	if(CB_ERR != nIndex)
	{
		Rotate = m_ctlRotate.GetItemData(nIndex);
	}
	else
	{
		return FALSE;
	}

	
	nIndex = m_ctlOptionSwitch.GetCurSel();
	if(CB_ERR != nIndex)
	{	
		SwitchMode = m_ctlOptionSwitch.GetItemData(nIndex);
		if(SwitchMode == 2)
		{
			SunriseHour   = m_StartHour;
			SunriseMinute = m_StartMinute;
			SunriseSecond = m_StartSecond;
			
			SunsetHour   = m_EndHour;
			SunsetMinute = m_EndMinute;
			SunsetSecond = m_EndSecond;
			
			if(SunriseHour > 23 || SunriseHour < 0 || SunriseMinute  > 59 || SunriseHour < 0
				|| SunriseSecond > 59 || SunriseSecond < 0)
			{
				AfxMessageBox(ConvertString("Input error,time should be 00:00:00~23:59:59!")); 
				return FALSE;
			}

			if(SunsetHour > 23 || SunsetHour < 0 || SunsetMinute > 59 || SunsetMinute < 0
				|| SunsetSecond > 59 || SunsetSecond < 0)
			{
				AfxMessageBox(ConvertString("Input error,time should be 00:00:00~23:59:59!")); 
				return FALSE;
			}
		}
	}
	else
	{
		return FALSE;
	}


     m_pstVideoInOption[nNum].bySwitchMode = SwitchMode;
	
	if(nItem == 0) //Normal
	{
		m_pstVideoInOption[nNum].stuNormalOptions.byAntiFlicker    = AntiFlicker;
		m_pstVideoInOption[nNum].stuNormalOptions.byExposureMode   = ExposureMode;
		m_pstVideoInOption[nNum].stuNormalOptions.byWhiteBalance   = WhiteBalance;
		if(WhiteBalance == 2) //Custom
		{
			m_pstVideoInOption[nNum].stuNormalOptions.byGainBlue = GainBule;
			m_pstVideoInOption[nNum].stuNormalOptions.byGainRed  = GainRed;
		}

		m_pstVideoInOption[nNum].stuNormalOptions.byDayNightColor  = DayNightColor;
		m_pstVideoInOption[nNum].stuNormalOptions.byRotate90 = Rotate;
		m_pstVideoInOption[nNum].stuNormalOptions.bIrisAuto = IrisAuto;
		m_pstVideoInOption[nNum].stuNormalOptions.bMirror = mirror;
		m_pstVideoInOption[nNum].stuNormalOptions.bFlip = bFlip;
		m_pstVideoInOption[nNum].stuNormalOptions.byGainMin = GainMin;
		m_pstVideoInOption[nNum].stuNormalOptions.byGainMax = GainMax;
		m_pstVideoInOption[nNum].stuNormalOptions.fExposureValue1 = ExpMin;
		m_pstVideoInOption[nNum].stuNormalOptions.fExposureValue2 = ExpMax;
		m_pstVideoInOption[nNum].stuNormalOptions.byExposure  = ExpSpeed;
		m_pstVideoInOption[nNum].stuNormalOptions.byBacklight = Backlight;
		if(Backlight == 2)
		{
			m_pstVideoInOption[nNum].stuNormalOptions.stuBacklightRegion.nLeft  = Left;
			m_pstVideoInOption[nNum].stuNormalOptions.stuBacklightRegion.nTop   = Top;
			m_pstVideoInOption[nNum].stuNormalOptions.stuBacklightRegion.nRight = Right;
			m_pstVideoInOption[nNum].stuNormalOptions.stuBacklightRegion.nBottom= Bottom;
		}
		if(m_pstCapVideoInput[nNum].nWideDynamicRange)
		{
			m_pstVideoInOption[nNum].stuNormalOptions.byWideDynamicRange = WideDynamicRange;
		}

		if(m_pstCapVideoInput[nNum].nGlareInhibition)
		{
			m_pstVideoInOption[nNum].stuNormalOptions.byGlareInhibition = GlareInhibition;
		}

	}
	else if(nItem == 1)//day
	{
		m_pstVideoInOption[nNum].byAntiFlicker    = AntiFlicker;
		m_pstVideoInOption[nNum].byExposureMode   = ExposureMode;
		m_pstVideoInOption[nNum].byWhiteBalance   = WhiteBalance;
		if(WhiteBalance == 2) //Custom
		{
			m_pstVideoInOption[nNum].byGainBlue = GainBule;
			m_pstVideoInOption[nNum].byGainRed  = GainRed;
		}
		
		m_pstVideoInOption[nNum].byDayNightColor  = DayNightColor;
		m_pstVideoInOption[nNum].byRotate90 = Rotate;
		m_pstVideoInOption[nNum].bIrisAuto = IrisAuto;
		m_pstVideoInOption[nNum].bMirror = mirror;
		m_pstVideoInOption[nNum].bFlip = bFlip;
		m_pstVideoInOption[nNum].byGainMin = GainMin;
		m_pstVideoInOption[nNum].byGainMax = GainMax;
		m_pstVideoInOption[nNum].fExposureValue1 = ExpMin;
		m_pstVideoInOption[nNum].fExposureValue2 = ExpMax;
		m_pstVideoInOption[nNum].byExposure  = ExpSpeed;
		m_pstVideoInOption[nNum].byBacklight = Backlight;
		if(Backlight == 2)
		{
			m_pstVideoInOption[nNum].stuBacklightRegion.nLeft  = Left;
			m_pstVideoInOption[nNum].stuBacklightRegion.nTop   = Top;
			m_pstVideoInOption[nNum].stuBacklightRegion.nRight = Right;
			m_pstVideoInOption[nNum].stuBacklightRegion.nBottom= Bottom;
		}
		if(m_pstCapVideoInput[nNum].nWideDynamicRange)
		{
			m_pstVideoInOption[nNum].byWideDynamicRange = WideDynamicRange;
		}
		
		if(m_pstCapVideoInput[nNum].nGlareInhibition)
		{
			m_pstVideoInOption[nNum].byGlareInhibition = GlareInhibition;
		}
	}
	else if(nItem == 2)//Night
	{
		m_pstVideoInOption[nNum].stuNightOptions.byAntiFlicker    = AntiFlicker;
		m_pstVideoInOption[nNum].stuNightOptions.byExposureMode   = ExposureMode;
		m_pstVideoInOption[nNum].stuNightOptions.byWhiteBalance   = WhiteBalance;
		m_pstVideoInOption[nNum].stuNightOptions.bySwitchMode	  = SwitchMode;
		if(WhiteBalance == 2) //Custom
		{
			m_pstVideoInOption[nNum].stuNightOptions.byGainBlue = GainBule;
			m_pstVideoInOption[nNum].stuNightOptions.byGainRed  = GainRed;
		}
		
		m_pstVideoInOption[nNum].stuNightOptions.byDayNightColor  = DayNightColor;
		m_pstVideoInOption[nNum].stuNightOptions.byRotate90 = Rotate;
		m_pstVideoInOption[nNum].stuNightOptions.bIrisAuto = IrisAuto;
		m_pstVideoInOption[nNum].stuNightOptions.bMirror = mirror;
		m_pstVideoInOption[nNum].stuNightOptions.bFlip = bFlip;
		m_pstVideoInOption[nNum].stuNightOptions.byGainMin = GainMin;
		m_pstVideoInOption[nNum].stuNightOptions.byGainMax = GainMax;
		m_pstVideoInOption[nNum].stuNightOptions.fExposureValue1 = ExpMin;
		m_pstVideoInOption[nNum].stuNightOptions.fExposureValue2 = ExpMax;
		m_pstVideoInOption[nNum].stuNightOptions.byExposure  = ExpSpeed;
		m_pstVideoInOption[nNum].stuNightOptions.byBacklight = Backlight;
		if(Backlight == 2)
		{
			m_pstVideoInOption[nNum].stuNightOptions.stuBacklightRegion.nLeft  = Left;
			m_pstVideoInOption[nNum].stuNightOptions.stuBacklightRegion.nTop   = Top;
			m_pstVideoInOption[nNum].stuNightOptions.stuBacklightRegion.nRight = Right;
			m_pstVideoInOption[nNum].stuNightOptions.stuBacklightRegion.nBottom= Bottom;
		}
		if(m_pstCapVideoInput[nNum].nWideDynamicRange)
		{
			m_pstVideoInOption[nNum].stuNightOptions.byWideDynamicRange = WideDynamicRange;
		}
		
		if(m_pstCapVideoInput[nNum].nGlareInhibition)
		{
			m_pstVideoInOption[nNum].stuNightOptions.byGlareInhibition = GlareInhibition;
		}
	}

    if(SwitchMode == 2)
    {
        m_pstVideoInOption[nNum].stuNightOptions.bySunriseHour = SunriseHour;
        m_pstVideoInOption[nNum].stuNightOptions.bySunriseMinute = SunriseMinute;
        m_pstVideoInOption[nNum].stuNightOptions.bySunriseSecond = SunriseSecond;
        m_pstVideoInOption[nNum].stuNightOptions.bySunsetHour = SunsetHour;
        m_pstVideoInOption[nNum].stuNightOptions.bySunsetMinute = SunsetMinute;
        m_pstVideoInOption[nNum].stuNightOptions.bySunsetSecond = SunsetSecond;
    }

	return TRUE;
}

void CConfigVideoIn::SaveChannelInfo(int nNum)
{	
	if(nNum > -1)
	{
		SaveOptionInfo(nNum,m_nCurTypeOption);
	}
}

void CConfigVideoIn::OnSelchangeComboAntifliker() 
{
	// TODO: Add your control notification handler code here
	int nIndexChannel = m_ctlChannel.GetCurSel();
	int nIndexAnti    = m_ctlAntiFliker.GetCurSel();
	int nIndexOption  = m_ctlOptionType.GetCurSel();
	if(CB_ERR != nIndexChannel && CB_ERR != nIndexAnti && CB_ERR != nIndexOption && NULL != m_pstCapVideoInput)
	{
		int nChannel = m_ctlChannel.GetItemData(nIndexChannel);
		int nAnti = m_ctlAntiFliker.GetItemData(nIndexAnti);
		int nOption = m_ctlOptionType.GetItemData(nIndexOption);
		int nIndex = 0;
		CString str;
		m_ctlExpMode.ResetContent();
		
		if(nAnti == 0) //outdoor
		{
			nIndex = 0;
			m_ctlAntiFliker.SetCurSel(0);
			if(m_pstCapVideoInput[nChannel].dwExposureMode & (1 << 0))
			{
				str.Format("Auto"); // 自动
				nIndex = m_ctlExpMode.AddString(ConvertString(str));
				m_ctlExpMode.SetItemData(nIndex, 0);
			}
			if(m_pstCapVideoInput[nChannel].dwExposureMode & (1 << 1))
			{	
				str.Format("Low yawp"); //低噪声
				nIndex = m_ctlExpMode.AddString(ConvertString(str));
				m_ctlExpMode.SetItemData(nIndex, 1);
			}
			if(m_pstCapVideoInput[nChannel].dwExposureMode & (1 << 2))
			{
				str.Format("None shadow");//防拖影
				nIndex = m_ctlExpMode.AddString(ConvertString(str));
				m_ctlExpMode.SetItemData(nIndex, 2);
			}
			if(m_pstCapVideoInput[nChannel].dwExposureMode & (1 << 4))
			{
				str.Format("manual");//手动
				nIndex = m_ctlExpMode.AddString(ConvertString(str));
				m_ctlExpMode.SetItemData(nIndex, 4);
			}
			m_ctlExpMode.SetCurSel(0);
			
		}
		else if(nAnti == 1 //50hz,60hz
			|| nAnti == 2)
		{
			if(nAnti == 1)
			{
				m_ctlAntiFliker.SetCurSel(1);
			}
			else
			{
				m_ctlAntiFliker.SetCurSel(2);
			}
			
			nIndex = 0;
			
			str.Format("Auto"); // 自动
			nIndex = m_ctlExpMode.AddString(ConvertString(str));
			m_ctlExpMode.SetItemData(nIndex, 0);
			
			str.Format("manual");//手动
			nIndex = m_ctlExpMode.AddString(ConvertString(str));
			m_ctlExpMode.SetItemData(nIndex, 4);
			
			m_ctlExpMode.SetCurSel(0);
				
		}
	
	}
}

void CConfigVideoIn::OnSelchangeComboExpmode() 
{
	// TODO: Add your control notification handler code here
	






}

void CConfigVideoIn::OnSelchangeComboOptionswitch() 
{
	
	// TODO: Add your control notification handler code here
	int nIndex = m_ctlOptionSwitch.GetCurSel();
	if(CB_ERR != nIndex)
	{
		if(nIndex == 2)
		{
			GetDlgItem(IDC_EDIT_STARTHOUR)->EnableWindow(TRUE);
			GetDlgItem(IDC_EDIT_STARTMINUTE)->EnableWindow(TRUE);
			GetDlgItem(IDC_EDIT_STARTSECOND)->EnableWindow(TRUE);
			GetDlgItem(IDC_EDIT_ENDHOUR)->EnableWindow(TRUE);
			GetDlgItem(IDC_EDIT_ENDMINUTE)->EnableWindow(TRUE);
			GetDlgItem(IDC_EDIT_ENDSECOND)->EnableWindow(TRUE);
		}
		else
		{
			GetDlgItem(IDC_EDIT_STARTHOUR)->EnableWindow(FALSE);
			GetDlgItem(IDC_EDIT_STARTMINUTE)->EnableWindow(FALSE);
			GetDlgItem(IDC_EDIT_STARTSECOND)->EnableWindow(FALSE);
			GetDlgItem(IDC_EDIT_ENDHOUR)->EnableWindow(FALSE);
			GetDlgItem(IDC_EDIT_ENDMINUTE)->EnableWindow(FALSE);
			GetDlgItem(IDC_EDIT_ENDSECOND)->EnableWindow(FALSE);

		}	
	}
}

void CConfigVideoIn::OnSelchangeComboBacklightmode() 
{
	// TODO: Add your control notification handler code here
	int nIndex = m_ctlBlackLightMode.GetCurSel();
	if(CB_ERR != nIndex)
	{
		if(nIndex == 2)
		{
			GetDlgItem(IDC_EDIT_MLEFT2)->EnableWindow(TRUE);
			GetDlgItem(IDC_EDIT_MTOP2)->EnableWindow(TRUE);
			GetDlgItem(IDC_EDIT_MRIGHT2)->EnableWindow(TRUE);
			GetDlgItem(IDC_EDIT_MBOTTOM)->EnableWindow(TRUE);
		}
		else
		{
			GetDlgItem(IDC_EDIT_MLEFT2)->EnableWindow(FALSE);
			GetDlgItem(IDC_EDIT_MTOP2)->EnableWindow(FALSE);
			GetDlgItem(IDC_EDIT_MRIGHT2)->EnableWindow(FALSE);
			GetDlgItem(IDC_EDIT_MBOTTOM)->EnableWindow(FALSE);
		}
	}
}

BOOL CConfigVideoIn::OnInitDialog() 
{
	CDialog::OnInitDialog();
	g_SetWndStaticText(this);
	

	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
