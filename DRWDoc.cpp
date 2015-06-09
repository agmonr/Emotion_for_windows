// DRWDoc.cpp : implementation of the CDRWDoc class
//

#include "stdafx.h"
#include "DRW.h"

#include "DRWDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDRWDoc

IMPLEMENT_DYNCREATE(CDRWDoc, CDocument)

BEGIN_MESSAGE_MAP(CDRWDoc, CDocument)
	//{{AFX_MSG_MAP(CDRWDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDRWDoc construction/destruction

CDRWDoc::CDRWDoc()
{
}

CDRWDoc::~CDRWDoc()
{
}

BOOL CDRWDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CDRWDoc serialization

void CDRWDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CDRWDoc diagnostics

#ifdef _DEBUG
void CDRWDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CDRWDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDRWDoc commands
