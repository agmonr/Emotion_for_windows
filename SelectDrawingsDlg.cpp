// SelectDrawingsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "drw.h"
#include "SelectDrawingsDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSelectDrawingsDlg dialog


CSelectDrawingsDlg::CSelectDrawingsDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSelectDrawingsDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSelectDrawingsDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CSelectDrawingsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSelectDrawingsDlg)
	DDX_Control(pDX, IDC_LIST, m_List);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSelectDrawingsDlg, CDialog)
	//{{AFX_MSG_MAP(CSelectDrawingsDlg)
	ON_BN_CLICKED(IDC_SELECTALL, OnSelectall)
	ON_BN_CLICKED(IDC_UNSELECTALL, OnUnselectall)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSelectDrawingsDlg message handlers

void CSelectDrawingsDlg::OnOK() 
{
	m_Names.RemoveAll();
	CString str;
	for (int i = 0; i < m_List.GetCount(); i++) {
		int Selected = m_List.GetSel(i);
		m_List.GetText(i, str);
		m_Enable.SetAt(str, (void*&)Selected);
	}
	
	CDialog::OnOK();
}

BOOL CSelectDrawingsDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	POSITION pos = m_Names.GetHeadPosition();
	while (pos) {
		CString Name = m_Names.GetNext(pos);
		int i = m_List.AddString(Name);
		BOOL Enable = TRUE;
		BOOL ret = m_Enable.Lookup(Name, (void*&)Enable);
		m_List.SetSel(i, Enable);
	}
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSelectDrawingsDlg::OnSelectall() 
{
	for (int i = 0; i < m_List.GetCount(); i++) {
		m_List.SetSel(i, 1);
	}
}

void CSelectDrawingsDlg::OnUnselectall() 
{
	for (int i = 0; i < m_List.GetCount(); i++) {
		m_List.SetSel(i, 0);
	}	
}
