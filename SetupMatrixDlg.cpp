// SetupMatrixDlg.cpp : implementation file
//

#include "stdafx.h"
#include "drw.h"
#include "SetupMatrixDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSetupMatrixDlg dialog


CSetupMatrixDlg::CSetupMatrixDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSetupMatrixDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSetupMatrixDlg)
	//}}AFX_DATA_INIT
}


void CSetupMatrixDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSetupMatrixDlg)
	DDX_Text(pDX, IDC_ASPECT, m_MatrixOptions.Aspect);
	DDX_Text(pDX, IDC_EYEX, m_MatrixOptions.EyePt.x);
	DDX_Text(pDX, IDC_EYEY, m_MatrixOptions.EyePt.y);
	DDX_Text(pDX, IDC_EYEZ, m_MatrixOptions.EyePt.z);
	DDX_Text(pDX, IDC_FARZ, m_MatrixOptions.ZFar);
	DDX_Text(pDX, IDC_FIELDOFVIEW, m_MatrixOptions.FieldOfView);
	DDX_Text(pDX, IDC_LOOKATX, m_MatrixOptions.LookAtPt.x);
	DDX_Text(pDX, IDC_LOOKATY, m_MatrixOptions.LookAtPt.y);
	DDX_Text(pDX, IDC_LOOKATZ, m_MatrixOptions.LookAtPt.z);
	DDX_Text(pDX, IDC_NEARZ, m_MatrixOptions.ZNear);
	DDX_Text(pDX, IDC_ROTATEX, m_MatrixOptions.fRotateX);
	DDX_Text(pDX, IDC_ROTATEY, m_MatrixOptions.fRotateY);
	DDX_Text(pDX, IDC_ROTATEZ, m_MatrixOptions.fRotateZ);
	DDX_Text(pDX, IDC_UPX, m_MatrixOptions.UpVec.x);
	DDX_Text(pDX, IDC_UPY, m_MatrixOptions.UpVec.y);
	DDX_Text(pDX, IDC_UPZ, m_MatrixOptions.UpVec.z);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSetupMatrixDlg, CDialog)
	//{{AFX_MSG_MAP(CSetupMatrixDlg)
	ON_BN_CLICKED(IDC_DEFAULT, OnDefault)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSetupMatrixDlg message handlers

void CSetupMatrixDlg::OnDefault() 
{
	m_MatrixOptions.SetDefault();
	UpdateData(FALSE);
}

