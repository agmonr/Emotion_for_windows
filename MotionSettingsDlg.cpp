// MotionSettingsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MotionSettingsDlg.h"
#include "BrowseForFolder.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMotionSettingsDlg dialog


CMotionSettingsDlg::CMotionSettingsDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMotionSettingsDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMotionSettingsDlg)
	m_bGroup1 = FALSE;
	m_bGroup2 = FALSE;
	m_Timer1 = 0;
	m_Timer2 = 0;
	m_TimerColor = 0;
	m_bGroup3 = FALSE;
	m_Timer3 = 0;
	m_CaptureFolder = _T("");
	m_CaptureMsec = 0;
	m_CameraFactor = 0;
	m_UseSameFile = FALSE;
	m_FileName = _T("");
	m_MinNeighbours = 0;
	m_ColorThreshold = 0;
	m_DisplayFunctionName = FALSE;
	m_AutoAdjust = FALSE;
	//}}AFX_DATA_INIT
}


void CMotionSettingsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMotionSettingsDlg)
	DDX_Check(pDX, IDC_CHECK_GROUP1, m_bGroup1);
	DDX_Check(pDX, IDC_CHECK_GROUP2, m_bGroup2);
	DDX_Text(pDX, IDC_EDIT_TIMER1, m_Timer1);
	DDX_Text(pDX, IDC_EDIT_TIMER2, m_Timer2);
	DDX_Text(pDX, IDC_EDIT_TIMERCOLOR, m_TimerColor);
	DDX_Check(pDX, IDC_CHECK_GROUP3, m_bGroup3);
	DDX_Text(pDX, IDC_EDIT_TIMER3, m_Timer3);
	DDX_Text(pDX, IDC_CAMERAFACTOR, m_CameraFactor);
	DDV_MinMaxUInt(pDX, m_CameraFactor, 1, 40);
	DDX_Text(pDX, IDC_MIN_NEIGHBOURS, m_MinNeighbours);
	DDV_MinMaxUInt(pDX, m_MinNeighbours, 0, 8);
	DDX_Text(pDX, IDC_COLOR_THRESHOLD, m_ColorThreshold);
	DDV_MinMaxUInt(pDX, m_ColorThreshold, 1, 100);
	DDX_Check(pDX, IDC_DISPLAYFUNCNAME, m_DisplayFunctionName);
	DDX_Check(pDX, IDC_ADJUST_AUTOMATICALLY, m_AutoAdjust);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMotionSettingsDlg, CDialog)
	//{{AFX_MSG_MAP(CMotionSettingsDlg)
	ON_BN_CLICKED(IDC_BROWSE, OnBrowse)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMotionSettingsDlg message handlers

BOOL CMotionSettingsDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	SetForegroundWindow();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CMotionSettingsDlg::OnOK() 
{
	UpdateData(TRUE);
	if (m_bGroup1 == FALSE && m_bGroup2 == FALSE && m_bGroup3 == FALSE) {
		AfxMessageBox("Select at least one group");
		return;
	}

	CDialog::OnOK();
}

void CMotionSettingsDlg::OnBrowse() 
{
	CBrowseForFolder BrowseForFolder;
	CString Message("Select directory");
	CString Path = m_CaptureFolder;
	if (BrowseForFolder.Browse(0,Path,Path,Message))
	{
		m_CaptureFolder = Path;
		UpdateData(FALSE);
	}
}
