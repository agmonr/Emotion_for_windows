// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "DRW.h"

#include "MainFrm.h"
#include "MemDC.h"

#include "VideoCapture.h"
#include "CameraPicture.h"
#include "SettingsDlg.h"
#include "Dib.h"
#include "StaticBasedDraw.h"
#include "CameraBasedDraw.h"
#include "3DDraw.h"
#include "Splash.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CAboutDlg1 dialog used for App About

class CAboutDlg1 : public CDialog
{
public:
	CAboutDlg1();

// Dialog Data
	//{{AFX_DATA(CAboutDlg1)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg1)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg1)
		// No message handlers
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg1::CAboutDlg1() : CDialog(CAboutDlg1::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg1)
	//}}AFX_DATA_INIT
}

void CAboutDlg1::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg1)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg1, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg1)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_UPDATE_COMMAND_UI(ID_VIEW_FULLSCREEN, OnUpdateViewFullScreen)
	ON_WM_ACTIVATE()
	ON_WM_TIMER()
	ON_WM_ERASEBKGND()
	ON_COMMAND(ID_VIEW_SETTINGS, OnViewSettings)
	ON_COMMAND(ID_VIEW_NEW_SETTINGS, OnViewNewSettings)
	ON_UPDATE_COMMAND_UI(ID_VIEW_SETTINGS, OnUpdateViewSettings)
	ON_WM_SETCURSOR()
	ON_COMMAND(ID_ABOUT, OnAppAbout)
	ON_COMMAND(ID_NEXT_DRAW, OnDoNextDraw)
	ON_COMMAND(ID_TOGGLE_CAPTURE, OnToggleCapture)
	ON_COMMAND(ID_SELECT_FUNTIONS, OnSelectFuntions)
	ON_WM_PAINT()
	ON_COMMAND(ID_VIEW_FULLSCREEN, OnViewFullScreen)
	ON_WM_ACTIVATEAPP()
	ON_WM_DESTROY()
	ON_WM_LBUTTONDOWN()
	ON_UPDATE_COMMAND_UI(ID_VIEW_NEW_SETTINGS, OnUpdateViewSettings)
	ON_COMMAND(ID_SETUP_MATRIX, OnSetupMatrix)

	ON_COMMAND(ID_MOVE_UP, OnMoveViewPoint)
	ON_COMMAND(ID_MOVE_DOWN, OnMoveViewPoint)
	ON_COMMAND(ID_MOVE_LEFT, OnMoveViewPoint)
	ON_COMMAND(ID_MOVE_RIGHT, OnMoveViewPoint)
	ON_COMMAND(ID_MOVE_FORWARD, OnMoveViewPoint)
	ON_COMMAND(ID_MOVE_BACK, OnMoveViewPoint)
	ON_COMMAND(ID_DEFAULT_MATRIX, OnMoveViewPoint)

	ON_COMMAND(ID_LOOK_LEFT, OnMoveViewPoint)
	ON_COMMAND(ID_LOOK_RIGHT, OnMoveViewPoint)
	ON_COMMAND(ID_LOOK_UP, OnMoveViewPoint)
	ON_COMMAND(ID_LOOK_DOWN, OnMoveViewPoint)
	ON_COMMAND(ID_LOOK_ZOOMIN, OnMoveViewPoint)
	ON_COMMAND(ID_LOOK_ZOOMOUT, OnMoveViewPoint)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
:	m_FullScreenWindowRect(0,0,0,0),
	m_pVideoCapture(NULL),
	m_RefreshTimerId(0), m_ChangeStaticPicTimerId(0), m_ChangeDrawTimerId(0),
	m_bInDlg(false), m_bActive(false)
{
	m_pVideoCapture = new CVideoCapture;
	m_pCameraPicture = new CCameraPicture;
	ReadSettings();

	//m_Drawings.AddTail(new CMotionBasedDraw(this));
	m_Drawings.AddTail(new C3DDraw(this));
}

CMainFrame::~CMainFrame()
{
	while (! m_Drawings.IsEmpty()) {
		delete m_Drawings.RemoveHead();
	}

	delete m_pVideoCapture;
	delete m_pCameraPicture;
}

void CMainFrame::OnDestroy() 
{
	// Init drawing objects
	POSITION pos = m_Drawings.GetHeadPosition();
	while (pos) {
		m_Drawings.GetNext(pos)->Terminate();
	}
	CFrameWnd::OnDestroy();
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	long Styles = ::GetWindowLong(m_hWnd, GWL_STYLE);
	long ExStyles = ::GetWindowLong(m_hWnd, GWL_EXSTYLE);

	ModifyStyle(WS_CAPTION, 0, 0);

	Styles = ::GetWindowLong(m_hWnd, GWL_STYLE);
	ExStyles = ::GetWindowLong(m_hWnd, GWL_EXSTYLE);

	// start in full screen mode
	OnViewFullScreen();

	m_pVideoCapture->Init(m_hWnd);
	InitTimers();
	m_pCameraPicture->SelectStaticPic(m_PicturesFolder);

	// Init drawing objects
	POSITION pos = m_Drawings.GetHeadPosition();
	while (pos) {
		m_Drawings.GetNext(pos)->Init();
	}

	// CG: The following line was added by the Splash Screen component.
	CSplashWnd::ShowSplashScreen(this);
	return 0;
}

BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT, CCreateContext* pContext)
{
	// default create client will create a view if asked for it
	if (pContext != NULL && pContext->m_pNewViewClass != NULL)
	{
		//if (CreateView(pContext, AFX_IDW_PANE_FIRST) == NULL)
		//	return FALSE;
	}
	return TRUE;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;

	cs.style = WS_OVERLAPPED;
	cs.hMenu = NULL;
	cs.dwExStyle = 0;

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

void CMainFrame::OnViewFullScreen()
{
	RECT rectDesktop;
	WINDOWPLACEMENT wpNew;
	
	// need to hide all status bars
	//m_wndStatusBar.ShowWindow(SW_HIDE);
	//m_wndToolBar.ShowWindow(SW_HIDE);
	
	// We'll need these to restore the original state.
	GetWindowPlacement (&m_wpPrev);
	
	m_wpPrev.length = sizeof m_wpPrev;
	
	//Adjust RECT to new size of window
	CWnd* pView = GetWindow(GW_CHILD);
	::GetWindowRect ( ::GetDesktopWindow(), &rectDesktop );

	CWinApp* pApp = AfxGetApp();
	m_FullViewRect.left = max(0, pApp->GetProfileInt("FullScreenRect", "left", rectDesktop.left));
	m_FullViewRect.top = max(0, pApp->GetProfileInt("FullScreenRect", "top", rectDesktop.top));
	m_FullViewRect.right = min(rectDesktop.right, (LONG)pApp->GetProfileInt("FullScreenRect", "right", rectDesktop.right));
	m_FullViewRect.bottom = min(rectDesktop.bottom, (LONG)pApp->GetProfileInt("FullScreenRect", "bottom", rectDesktop.bottom));


	CalcWindowRect(&m_FullViewRect, CWnd::adjustBorder);
	
	// Remember this for OnGetMinMaxInfo()
	m_FullScreenWindowRect = m_FullViewRect;
	
	wpNew = m_wpPrev;
	wpNew.showCmd =  SW_SHOWNORMAL;
	wpNew.rcNormalPosition = m_FullViewRect;
	
	SetWindowPlacement ( &wpNew );
	//MoveWindow();
}

void CMainFrame::OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI)
{
	lpMMI->ptMaxSize.y = m_FullScreenWindowRect.Height();
	lpMMI->ptMaxTrackSize.y = lpMMI->ptMaxSize.y;
	lpMMI->ptMaxSize.x = m_FullScreenWindowRect.Width();
	lpMMI->ptMaxTrackSize.x = lpMMI->ptMaxSize.x;
}

void CMainFrame::OnUpdateViewFullScreen(CCmdUI* pCmdUI)
{
	pCmdUI->Enable();
}

void CMainFrame::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized) 
{
	CWnd* pWnd = GetWindow(GW_CHILD);
	if (pWnd) {
		/*
		CDRWView* pView = (CDRWView*)pWnd;

		if (nState == WA_INACTIVE) {
			pView->DoActivate(false);

		} else if (nState == WA_ACTIVE || nState == WA_ACTIVE) {
			pView->DoActivate(true);
		}*/
	}
	if (nState == WA_INACTIVE) {
		DoActivate(false);
	} else if (nState == WA_ACTIVE || nState == WA_ACTIVE) {
		DoActivate(true);
	}
	CFrameWnd::OnActivate(nState, pWndOther, bMinimized);	
}

////////////////////////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////////////////////////

#define REFRESH_TIMER_ID 5
#define CHANGE_PIC_TIMER_ID 6
#define CHANGE_DRAW_TIMER_ID 7

void CMainFrame::InitTimers() 
{
	if (m_RefreshTimerId != 0) {
		KillTimer(m_RefreshTimerId);
		m_RefreshTimerId = 0;
	}
	if (m_ChangeStaticPicTimerId != 0) {
		KillTimer(m_ChangeStaticPicTimerId);
		m_ChangeStaticPicTimerId = 0;
	}
	if (m_ChangeDrawTimerId != 0) {
		KillTimer(m_ChangeDrawTimerId);
		m_ChangeDrawTimerId = 0;
	}

	m_RefreshTimerId = SetTimer(REFRESH_TIMER_ID, m_RefreshRate, NULL);
	if (m_NewImageRate > 0) {
		m_ChangeStaticPicTimerId = SetTimer(CHANGE_PIC_TIMER_ID, m_NewImageRate * 1000, NULL);
	}
	m_ChangeDrawTimerId = SetTimer(CHANGE_DRAW_TIMER_ID, 10000, NULL); 
}

void CMainFrame::OnTimer(UINT nIDEvent) 
{
	if (! m_bInDlg && m_bActive) {
		if (nIDEvent == m_RefreshTimerId) {
			//DWORD d1 = GetTickCount();
			ProcessChange();
			//DWORD d2 = GetTickCount();
			//TRACE("Capturing took %d\n", d2-d1);
			
			Invalidate();
			UpdateWindow();
		}
		else if (nIDEvent == m_ChangeStaticPicTimerId) {
			TRACE("%s Picture Timer\n" , CTime::GetCurrentTime().Format("%H:%M:%S"));
			m_pCameraPicture->SelectStaticPic(m_PicturesFolder);
		}
		else if (nIDEvent == m_ChangeDrawTimerId) {
			if (! m_Drawings.IsEmpty()) {
				CBaseDraw* pDraw = m_Drawings.RemoveHead();
				m_Drawings.AddTail(pDraw);
			}
		}
	}
	CFrameWnd::OnTimer(nIDEvent);
}

BOOL CMainFrame::OnEraseBkgnd(CDC* pDC) 
{
	if (!m_bActive) {
		CRect r;
		GetClientRect(r);
		CBrush* pOld = (CBrush*)pDC->SelectStockObject(BLACK_BRUSH);
		pDC->Rectangle(&r);
		pDC->SelectObject(pOld);
		return true;
	} else {
		return true;
	}
}

void CMainFrame::OnViewSettings() 
{
	CSettingsDlg dlg(this);
	dlg.m_bMotionColorsAffectWholeImage = m_bMotionColorsAffectWholeImage;
	dlg.m_PicturesFolder = m_PicturesFolder;
	dlg.m_RefreshRate = m_RefreshRate;
	dlg.m_NewImageRate = m_NewImageRate;
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	dlg.left = pFrame->m_FullViewRect.left;
	dlg.top = pFrame->m_FullViewRect.top;
	dlg.right = pFrame->m_FullViewRect.right;
	dlg.bottom = pFrame->m_FullViewRect.bottom;

	m_bInDlg = true;
	if (dlg.DoModal() == IDOK) {
		m_bMotionColorsAffectWholeImage = dlg.m_bMotionColorsAffectWholeImage;
		m_PicturesFolder = dlg.m_PicturesFolder;
		m_RefreshRate = dlg.m_RefreshRate;
		m_NewImageRate = dlg.m_NewImageRate;

		pFrame->m_FullViewRect.left = dlg.left;
		pFrame->m_FullViewRect.top = dlg.top;
		pFrame->m_FullViewRect.right = dlg.right;
		pFrame->m_FullViewRect.bottom = dlg.bottom;

		WriteSettings();
		InitTimers();
		pFrame->OnViewFullScreen();
	}
	m_bInDlg = false;
}

void CMainFrame::OnViewNewSettings() 
{
	POSITION pos = m_Drawings.GetHeadPosition();
	while (pos) {
		CBaseDraw* pDraw = m_Drawings.GetNext(pos);
		if (pDraw->IsMotionDraw()) {
			m_bInDlg = true;
			((CMotionBasedDraw*)pDraw)->DoSettings();
			m_bInDlg = false;
			break;
		}
	}
}

void CMainFrame::OnDoNextDraw() 
{
	POSITION pos = m_Drawings.GetHeadPosition();
	while (pos) {
		CBaseDraw* pDraw = m_Drawings.GetNext(pos);
		if (pDraw->IsMotionDraw()) {
			((CMotionBasedDraw*)pDraw)->DoNextDraw();
			break;
		}
	}	
}

void CMainFrame::OnSetupMatrix() 
{
	POSITION pos = m_Drawings.GetHeadPosition();
	while (pos) {
		CBaseDraw* pDraw = m_Drawings.GetNext(pos);
		if (pDraw->Is3DDraw()) {
			m_bInDlg = true;
			((C3DDraw*)pDraw)->DoSetupMatrix();
			m_bInDlg = false;
			break;
		}
	}
}

// App command to run the dialog
void CMainFrame::OnAppAbout()
{
	m_bInDlg = true;
	CAboutDlg1 aboutDlg;
	aboutDlg.DoModal();
	m_bInDlg = false;
}

void CMainFrame::OnUpdateViewSettings(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(true);
}

void CMainFrame::ReadSettings()
{
	CString Path;
	GetModuleFileName(AfxGetInstanceHandle(), Path.GetBuffer(1024),1024);
	Path.ReleaseBuffer();

	int i = Path.ReverseFind('\\');
	Path = Path.Mid(0,i+1);
	Path += "Pictures";

	CWinApp* pApp = AfxGetApp();
	m_RefreshRate = pApp->GetProfileInt("Settings", "RefreshRate", 1000);
	m_NewImageRate = pApp->GetProfileInt("Settings", "NewImageRate", 0);
	m_PicturesFolder = pApp->GetProfileString("Settings", "PicturesFolder", Path);
	m_bMotionColorsAffectWholeImage = pApp->GetProfileInt("Settings", "MotionChangeWholeImage", 1);

	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	if (pFrame) {
		RECT rectDesktop;
		::GetWindowRect ( ::GetDesktopWindow(), &rectDesktop );
		pFrame->m_FullViewRect.left = pApp->GetProfileInt("FullScreenRect", "left", rectDesktop.left);
		pFrame->m_FullViewRect.top = pApp->GetProfileInt("FullScreenRect", "top", rectDesktop.top);
		pFrame->m_FullViewRect.right = pApp->GetProfileInt("FullScreenRect", "right", rectDesktop.right);
		pFrame->m_FullViewRect.bottom = pApp->GetProfileInt("FullScreenRect", "bottom", rectDesktop.bottom);
	}
}

void CMainFrame::WriteSettings()
{
	CWinApp* pApp = AfxGetApp();
	pApp->WriteProfileInt("Settings", "RefreshRate", m_RefreshRate);
	pApp->WriteProfileInt("Settings", "NewImageRate", m_NewImageRate);
	pApp->WriteProfileString("Settings", "PicturesFolder", m_PicturesFolder);
	pApp->WriteProfileInt("Settings", "MotionChangeWholeImage", m_bMotionColorsAffectWholeImage);

	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	pApp->WriteProfileInt("FullScreenRect", "left", pFrame->m_FullViewRect.left);
	pApp->WriteProfileInt("FullScreenRect", "top", pFrame->m_FullViewRect.top);
	pApp->WriteProfileInt("FullScreenRect", "right", pFrame->m_FullViewRect.right);
	pApp->WriteProfileInt("FullScreenRect", "bottom", pFrame->m_FullViewRect.bottom);
}

//////////////////////////////////////////////////////////////////////////////

void CMainFrame::ProcessChange()
{
	//m_pVideoCapture->CaptureOneFrame();
	m_pVideoCapture->CaptureOneFrameToClipboard();
	if (! m_pCameraPicture->LoadCameraPicture()) {
		static once = 0;
		if (once == 0) {
			once = 1;
			//::MessageBox(m_hWnd, "Please connect a web camera", "Error", MB_OK);
		}
		m_bActive = false;
		return;
	}

	CBaseDraw* pDraw = GetCurrDraw();
	if (pDraw->IsStaticDraw()) {
		CStaticBasedDraw* pDraw1 = (CStaticBasedDraw*)pDraw;
		m_pCameraPicture->LoadStaticPic();

		pDraw1->ProcessCameraChangeOnStatic(m_pCameraPicture);
	} else {
		// do nothing at this stage - will do the draing in OnDraw
	}
}

/////////////////////////////////////////////////////////////////////////////
// CDRWView drawing

void CMainFrame::OnDraw(CDC* pDC)
{
	if (m_bActive) {		
		if (! m_pCameraPicture->IsInitialized()) {
			return;
		}

		CRect rect;
		GetClientRect( &rect );	
		//CMemDC MemDC(rect.Width(), rect.Height());
		//MemDC.BeforeDraw(pDC);

		CBaseDraw* pDraw = GetCurrDraw();
		if (pDraw->IsStaticDraw()) {
			//m_pCameraPicture->GetDibDraw()->Draw(MemDC, &rect, NULL);
		} else {
			CCameraBasedDraw* pCameraDraw = (CCameraBasedDraw*)pDraw;
			//pCameraDraw->Draw(rect.Size(), &MemDC, m_pCameraPicture);
			pCameraDraw->Draw(rect.Size(), pDC, m_pCameraPicture);
		}

		//MemDC.AfterDraw(pDC);
	}
	else
	{
		CFont f;
		f.CreatePointFont(1800, "Arial", pDC);
		pDC->SetBkColor(RGB(0,0,0));
		pDC->SetTextColor(RGB(112,145,225));

		CFont* pOldFont = pDC->SelectObject(&f);

		CString str = "e-Motion";
		CSize size = pDC->GetTextExtent(str);
		CRect r;
		GetClientRect(&r);

		long left = (r.Width() - size.cx) / 2;
		long top = (r.Height() - size.cy) / 2;
		pDC->TextOut(left, top, str);

		pDC->SelectObject(pOldFont);
		f.DeleteObject();
	}
}

/////////////////////////////////////////////////////////////////////////////

// Hide cursor from the view
BOOL CMainFrame::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	static HCURSOR hCur = AfxGetApp()->LoadCursor(IDC_NONE);
	::SetCursor(hCur);

	return TRUE;
}

void CMainFrame::DoActivate(bool bActive)
{
	m_bActive = bActive;
	Invalidate();
	UpdateWindow();
}

void CMainFrame::OnToggleCapture() 
{
	POSITION pos = m_Drawings.GetHeadPosition();
	while (pos) {
		CBaseDraw* pDraw = m_Drawings.GetNext(pos);
		if (pDraw->IsMotionDraw()) {
			((CMotionBasedDraw*)pDraw)->ToggleCapture();
			break;
		}
	}	
}


void CMainFrame::OnSelectFuntions() 
{
	POSITION pos = m_Drawings.GetHeadPosition();
	while (pos) {
		CBaseDraw* pDraw = m_Drawings.GetNext(pos);
		if (pDraw->IsMotionDraw()) {
			((CMotionBasedDraw*)pDraw)->SelectFunctions();
			break;
		}
	}	
}

void CMainFrame::OnPaint() 
{
	//CFrameWnd::OnPaint();
	CPaintDC dc(this); // device context for painting
	OnDraw(&dc);
}

void CMainFrame::OnMoveViewPoint() 
{
	// Init drawing objects
	POSITION pos = m_Drawings.GetHeadPosition();
	while (pos) {
		CBaseDraw* pDraw = m_Drawings.GetNext(pos);
		if (pDraw->Is3DDraw()) {
			UINT CommandId = LOWORD(GetCurrentMessage()->wParam);
			((C3DDraw*)pDraw)->OnMoveViewPoint(CommandId);
		}
	}
}

