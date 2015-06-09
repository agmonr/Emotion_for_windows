// DRWView.cpp : implementation of the CDRWView class//
#include "stdafx.h"
#include "DRW.h"

#include "DRWDoc.h"
#include "DRWView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About


/////////////////////////////////////////////////////////////////////////////
// CDRWView

IMPLEMENT_DYNCREATE(CDRWView, CView)

BEGIN_MESSAGE_MAP(CDRWView, CView)
	//{{AFX_MSG_MAP(CDRWView)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDRWView construction/destruction

CDRWView::CDRWView()
{
}

CDRWView::~CDRWView()
{
}

void CDRWView::OnDraw(CDC* pDC)
{
}
