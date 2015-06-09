// SettingsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "DRW.h"
#include "SettingsDlg.h"
#include "BrowseForFolder.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSettingsDlg dialog


CSettingsDlg::CSettingsDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSettingsDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSettingsDlg)
	m_bMotionColorsAffectWholeImage = FALSE;
	m_PicturesFolder = _T("");
	m_RefreshRate = 0;
	m_NewImageRate = 0;
	left = 0;
	right = 0;
	top = 0;
	bottom = 0;
	//}}AFX_DATA_INIT
}


void CSettingsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSettingsDlg)
	DDX_Text(pDX, IDC_EDIT_REFRESH_RATE, m_RefreshRate);
	DDV_MinMaxUInt(pDX, m_RefreshRate, 10, 10000);
	DDX_Text(pDX, IDC_EDIT_LOAD_IMAGE, m_NewImageRate);
	DDV_MinMaxUInt(pDX, m_NewImageRate, 0, 3600);
	DDX_Text(pDX, IDC_X, left);
	DDX_Text(pDX, IDC_X1, right);
	DDX_Text(pDX, IDC_Y, top);
	DDX_Text(pDX, IDC_Y1, bottom);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSettingsDlg, CDialog)
	//{{AFX_MSG_MAP(CSettingsDlg)
	ON_BN_CLICKED(IDC_BROWSE, OnBrowse)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSettingsDlg message handlers

void CSettingsDlg::OnBrowse() 
{
	CBrowseForFolder BrowseForFolder;
	CString Message("Select directory");
	CString Path = m_PicturesFolder;
	if (BrowseForFolder.Browse(0,Path,Path,Message))
	{
		m_PicturesFolder = Path;
		UpdateData(FALSE);
	}
}

