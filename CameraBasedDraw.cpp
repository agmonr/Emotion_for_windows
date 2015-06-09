// CameraBasedDraw.cpp: implementation of the CCameraBasedDraw class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DRW.h"
#include "CameraBasedDraw.h"
#include "CameraPicture.h"
#include "Dib.h"
#include "Utils.h"
#include "MotionSettingsDlg.h"
#include "Group1.h"
#include "Group2.h"
#include "MemDC.h"
#include "SelectDrawingsDlg.h"
#include "MainFrm.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCameraBasedDraw::CCameraBasedDraw()
{
}

CCameraBasedDraw::~CCameraBasedDraw()
{
}

//////////////////////////////////////////////////////////////////////

UINT CMotionBasedDraw::m_DrawTimerId = 0;
UINT CMotionBasedDraw::m_ColorTimerId = 0;
UINT CMotionBasedDraw::m_CaptureTimerId = 0;
BOOL CMotionBasedDraw::m_NextDraw = TRUE;
BOOL CMotionBasedDraw::m_NextColor = TRUE;
BOOL CMotionBasedDraw::m_NextCapture = TRUE;

CMotionBasedDraw::CMotionBasedDraw(CWnd* pWnd)
{
	m_FunctionSelect = 0;
	m_GroupSelect = 0;
	m_pWnd = pWnd;
	
	// Seed the random-number generator with current time so that
	// the numbers will be different every time we run.
	srand( (unsigned)time( NULL ) );
	
	// Set timer values
	m_TimerGroup[0] = 2000;
	m_TimerGroup[1] = 5000;
	m_TimerGroup[2] = 2000;
	m_TimerColor = 2000;
	m_TempCameraFactor = m_CameraFactor = 2;
	m_AutoAdjust = FALSE;
	m_ColorThreshold = 22;
	m_MinNeighbours = 3;
	m_DisplayFunctionName = 1;
	
	CWinApp* pApp = AfxGetApp();
	m_TimerGroup[0] = pApp->GetProfileInt("Settings", "Timer1", 2000);
	m_TimerGroup[1] = pApp->GetProfileInt("Settings", "Timer2", 5000);
	m_TimerGroup[2] = pApp->GetProfileInt("Settings", "Timer3", 2000);
	m_TimerColor = pApp->GetProfileInt("Settings", "TimerColor", 2000);
	m_DisplayGroup[0] = pApp->GetProfileInt("Settings", "DisplayGroup1", 1);
	m_DisplayGroup[1] = pApp->GetProfileInt("Settings", "DisplayGroup2", 1);
	m_DisplayGroup[2] = pApp->GetProfileInt("Settings", "DisplayGroup3", 1);
	m_CaptureFolder = pApp->GetProfileString("Settings", "CaptureFolder", "");
	m_TimerCapture = pApp->GetProfileInt("Settings", "CapturePeriod", 0);
	m_CameraFactor = pApp->GetProfileInt("Settings", "CameraFactor", 2);
	m_TempCameraFactor = m_CameraFactor;
	m_AutoAdjust = pApp->GetProfileInt("Settings", "AutoAdjust", 0);
	m_ColorThreshold = pApp->GetProfileInt("Settings", "ColorThreshold", 22);
	m_MinNeighbours = pApp->GetProfileInt("Settings", "MinNeighbours", 3);
	m_UseSameFile = pApp->GetProfileInt("Settings", "UseSameFile", 0);
	m_FileName = pApp->GetProfileString("Settings", "FileName", "");
	m_DisplayFunctionName = pApp->GetProfileInt("Settings", "DisplayFunctionName", 1);

	
	CGroup2::m_pWnd = m_pWnd;
	
	SelectRandDrawFunc();
	
	m_Capturecounter = 0;
	m_EnableCapture = false;
}

void CMotionBasedDraw::Init()
{
	// init drawing functions
	InitFunctions();
}

void CMotionBasedDraw::Terminate()
{
}

//////////////////////////////////////////////////////////////////////

void CMotionBasedDraw::DoSettings()
{
	CMotionSettingsDlg dlg(m_pWnd);
	dlg.m_Timer1 = m_TimerGroup[0];
	dlg.m_Timer2 = m_TimerGroup[1];
	dlg.m_Timer3 = m_TimerGroup[2];
	dlg.m_TimerColor = m_TimerColor;
	dlg.m_bGroup1 = m_DisplayGroup[0];
	dlg.m_bGroup2 = m_DisplayGroup[1];
	dlg.m_bGroup3 = m_DisplayGroup[2];
	dlg.m_CaptureFolder = m_CaptureFolder;
	dlg.m_CaptureMsec = m_TimerCapture;
	dlg.m_CameraFactor = m_CameraFactor;
	dlg.m_AutoAdjust = m_AutoAdjust;
	dlg.m_ColorThreshold = m_ColorThreshold;
	dlg.m_MinNeighbours = m_MinNeighbours;
	dlg.m_UseSameFile = m_UseSameFile;
	dlg.m_FileName = m_FileName;
	dlg.m_DisplayFunctionName = m_DisplayFunctionName;
	
	if (dlg.DoModal() == IDOK) {
		m_TimerGroup[0] = dlg.m_Timer1;
		m_TimerGroup[1] = dlg.m_Timer2;
		m_TimerGroup[2] = dlg.m_Timer3;
		m_TimerColor = dlg.m_TimerColor;
		m_DisplayGroup[0] = dlg.m_bGroup1;
		m_DisplayGroup[1] = dlg.m_bGroup2;
		m_DisplayGroup[2] = dlg.m_bGroup3;
		m_CaptureFolder = dlg.m_CaptureFolder;
		m_TimerCapture = dlg.m_CaptureMsec;
		m_CameraFactor = dlg.m_CameraFactor;
		m_TempCameraFactor = m_CameraFactor;
		m_AutoAdjust = dlg.m_AutoAdjust;
		m_ColorThreshold = dlg.m_ColorThreshold;
		m_MinNeighbours = dlg.m_MinNeighbours;
		m_UseSameFile = dlg.m_UseSameFile;
		m_FileName = dlg.m_FileName;
		m_DisplayFunctionName = dlg.m_DisplayFunctionName;

		CWinApp* pApp = AfxGetApp();
		pApp->WriteProfileInt("Settings", "Timer1", m_TimerGroup[0]);
		pApp->WriteProfileInt("Settings", "Timer2", m_TimerGroup[1]);
		pApp->WriteProfileInt("Settings", "Timer3", m_TimerGroup[2]);
		pApp->WriteProfileInt("Settings", "TimerColor", m_TimerColor);
		pApp->WriteProfileInt("Settings", "DisplayGroup1", m_DisplayGroup[0]);
		pApp->WriteProfileInt("Settings", "DisplayGroup2", m_DisplayGroup[1]);
		pApp->WriteProfileInt("Settings", "DisplayGroup3", m_DisplayGroup[2]);
		pApp->WriteProfileString("Settings", "CaptureFolder", m_CaptureFolder);
		pApp->WriteProfileInt("Settings", "CapturePeriod", m_TimerCapture );
		pApp->WriteProfileInt("Settings", "CameraFactor", m_CameraFactor);
		pApp->WriteProfileInt("Settings", "AutoAdjust", m_AutoAdjust);
		pApp->WriteProfileInt("Settings", "ColorThreshold", m_ColorThreshold);
		pApp->WriteProfileInt("Settings", "MinNeighbours", m_MinNeighbours);
		pApp->WriteProfileInt("Settings", "UseSameFile", m_UseSameFile);
		pApp->WriteProfileString("Settings", "FileName", m_FileName);
		pApp->WriteProfileInt("Settings", "DisplayFunctionName", m_DisplayFunctionName);
	}
}

//////////////////////////////////////////////////////////////////////

void CMotionBasedDraw::DoNextDraw()
{
	::KillTimer(m_pWnd->m_hWnd, m_DrawTimerId);
	m_DrawTimerId = 0;
	m_NextDraw = TRUE;
}

void CALLBACK CMotionBasedDraw::TimerProc(HWND hWnd, UINT nMsg, UINT nTimerId, DWORD dwTime)
{
	if (nTimerId == m_DrawTimerId) {
		::KillTimer(hWnd, m_DrawTimerId);
		m_DrawTimerId = 0;
		m_NextDraw = TRUE;
	}
	else if (nTimerId == m_ColorTimerId) {
		::KillTimer(hWnd, m_ColorTimerId);
		m_ColorTimerId = 0;
		m_NextColor = TRUE;
	} else if (nTimerId == m_CaptureTimerId) {
		::KillTimer(hWnd, m_CaptureTimerId);
		m_CaptureTimerId = 0;
		m_NextCapture = TRUE;
	}
}

void CMotionBasedDraw::SelectRandDrawFunc()
{
	long PrevFunctionSelect = m_FunctionSelect;

	long FunctionSelect = m_FunctionSelect;
	long GroupSelect = m_GroupSelect;

	long EnabledFunctionsCount = m_EnableFunctions.GetCount();

	// Try 5 times to find a different function
	for (int Counter = 0; m_FunctionSelect == FunctionSelect && 
			m_GroupSelect == GroupSelect && Counter < 5; Counter++) 
	{
		// select function
		int r = rand();
		TRACE("----------------------------\n");
		TRACE("Random is %d\n", r);
		// select group
		int GroupSelect = rand() % 3;
		for (int i = 0; 
			i < 3 && (m_DisplayGroup[GroupSelect] == 0 ||
			m_Group[GroupSelect].GetSize() == 0); i++) {
			//TRACE("m_DisplayGroup[GroupSelect]=%d GroupSelect=%d\n", 
			//	m_DisplayGroup[GroupSelect], GroupSelect);
			GroupSelect++;
			GroupSelect %= 3;
		}
		//TRACE("GroupSelect %d Size %d\n", GroupSelect, m_Group[GroupSelect].GetSize());

		if (m_Group[GroupSelect].GetSize() > 0) 
		{
			CArray<int, int> EnabledFuncIndexes;
			// find out how many enabled functions in the group
			long EnableFuncCount = 0;
			long GroupSize = m_Group[GroupSelect].GetSize();
			for (int i = 0; i < GroupSize; i++) {
				BOOL bEnable = FALSE;
				DrawFunc* pDrawFunc = m_Group[GroupSelect].GetAt(i);
				if (m_EnableFunctions.Lookup(pDrawFunc, bEnable) && bEnable) {
					EnabledFuncIndexes.Add(i);
					EnableFuncCount++;
				}
			}
			long EnabledFuncIndex = r % EnableFuncCount;
			FunctionSelect = EnabledFuncIndexes[EnabledFuncIndex];
			//TRACE("Counter = %d  FunctionSelect = %d\n", Counter, FunctionSelect);
		} else {
			// this will force another loop...
			FunctionSelect = m_FunctionSelect;
			//TRACE("%% Counter = %d  FunctionSelect = %d\n", Counter, FunctionSelect);
		}
	}
	
	m_FunctionSelect = FunctionSelect;
	m_GroupSelect = GroupSelect;

	TRACE("Group %d FunctionSelect %d\n",m_GroupSelect, m_FunctionSelect);
}


void CMotionBasedDraw::GetMotionPoints(CSize ScreenSize, CCameraPicture* pCameraPicture, 
									   MotionPixel* MotionPixels, long MaxMotionPixels,
									   long& MotionPixelsCount)
{
	CDib* pCameraDib = pCameraPicture->GetCurrCameraDib();
	CDib* pPrevCameraDib = pCameraPicture->GetPrevCameraDib();
	CSize CameraSize = pCameraDib->GetSize();
	
	const int CameraSizeX = CameraSize.cx;
	const int CameraSizeY = CameraSize.cy;
	// By camera image
	double FactorX = (double)ScreenSize.cx / (double)CameraSizeX;
	double FactorY = (double)ScreenSize.cy / (double)CameraSizeY;
	long lFactorX = (long)FactorX;
	long lFactorY = (long)FactorY;
	if (FactorX - (double)lFactorX > 0.5) lFactorX++;
	if (FactorY - (double)lFactorY > 0.5) lFactorY++;

	const int CameraFactor = min(40, max(m_TempCameraFactor, 1));
	const int MinNeighbours = min(m_MinNeighbours, 8);

	long PixCounter = 0;

	for (int CameraX=0; CameraX < CameraSizeX; CameraX+=CameraFactor)
	{
		for (int CameraY=0; CameraY < CameraSizeY; CameraY+=CameraFactor)
		{		
			if (CameraX < CameraSizeX && CameraY < CameraSizeY) {
				COLORREF Pix = pCameraDib->GetPixel(CameraX, CameraY);
				COLORREF PrevPix = pPrevCameraDib->GetPixel(CameraX, CameraY);
				long Diff = Pix - PrevPix;
				DWORD R = GetRValue(Pix);
				DWORD G = GetGValue(Pix);
				DWORD B = GetBValue(Pix);
				DWORD R1 = GetRValue(PrevPix);
				DWORD G1 = GetGValue(PrevPix);
				DWORD B1 = GetBValue(PrevPix);

				DWORD Rd = abs(R - R1);
				DWORD Gd = abs(G - G1);
				DWORD Bd = abs(B - B1);
				
				// check if a significant change was made
				if (! (Rd < m_ColorThreshold && Gd < m_ColorThreshold && Bd < m_ColorThreshold)) {
					RelevantPixels[PixCounter++] = MAKELONG(CameraX, CameraY);
					PixArray[CameraX][CameraY] = Pix;
					PrevPixArray[CameraX][CameraY] = PrevPix;
					DiffArray[CameraX][CameraY] = Diff;
				} else {
					PixArray[CameraX][CameraY] = 
						PrevPixArray[CameraX][CameraY] =
						DiffArray[CameraX][CameraY] = 0;
				}
			}
		}
	}

	long MaxPixels = (CameraSizeX / CameraFactor) * (CameraSizeY / CameraFactor);
	BOOL bSkipPoints = PixCounter > MaxPixels/3 && m_TempCameraFactor <= m_CameraFactor;
	//TRACE("MaxPixels = %d Count = %d\n",MaxPixels, PixCounter);
	// Go over relevant pixels and take into account only those
	// with enough neighbours (i.e. remove camera noise)
	long SkippedPoints = 0;
	MotionPixelsCount = 0;
	for (int i = 0; i < PixCounter; i++) 
	{ 
		int CameraX = LOWORD(RelevantPixels[i]);
		int CameraY = HIWORD(RelevantPixels[i]);
		bool bSkip = bSkipPoints && 
			((CameraX / CameraFactor) % 2 == (CameraY / CameraFactor) % 2);

		if (! bSkip) {
			int CountNeighbours = 0;
			if (CameraX > 0 && CameraY > 0 && 
				CameraX < CameraSizeX-CameraFactor && CameraY < CameraSizeY-CameraFactor) 
			{
#define Once(x) (x != 0 ? 1 : 0)
				CountNeighbours = 
					Once(DiffArray[CameraX-CameraFactor][CameraY-CameraFactor]) +
					Once(DiffArray[CameraX][CameraY-CameraFactor]) +
					Once(DiffArray[CameraX+CameraFactor][CameraY-CameraFactor]) +
					Once(DiffArray[CameraX-CameraFactor][CameraY]) +
					Once(DiffArray[CameraX+CameraFactor][CameraY]) +
					Once(DiffArray[CameraX-CameraFactor][CameraY+CameraFactor]) +
					Once(DiffArray[CameraX][CameraY+CameraFactor]) +
					Once(DiffArray[CameraX+CameraFactor][CameraY+CameraFactor]);
			}
			// count neightbours
			if (CountNeighbours >= MinNeighbours) {
				long x = max((long)((double)CameraX * FactorX), 0);
				long y = max((long)((double)CameraY * FactorY), 0);

				MotionPixels[MotionPixelsCount].CameraX = CameraX;
				MotionPixels[MotionPixelsCount].CameraY = CameraY;
				MotionPixels[MotionPixelsCount].x = (short)x;
				MotionPixels[MotionPixelsCount].y = (short)y;
				MotionPixels[MotionPixelsCount].Pix = PixArray[CameraX][CameraY];
				MotionPixels[MotionPixelsCount].PrevPix = PrevPixArray[CameraX][CameraY];

				MotionPixelsCount++;
					/*
				pDrawFunc(pDC, ScreenSize, 
					CameraX, CameraY, // position on camera 
					x, y, // position on screen 
					lFactorX, lFactorY, CameraFactor,
					PixArray[CameraX][CameraY], PrevPixArray[CameraX][CameraY]);
					*/
			}
		} else {
			SkippedPoints++;
			//TRACE("Skipped point %d %d\n", CameraX, CameraY);
		}
	}
	if (SkippedPoints > 0) {
		TRACE("Skipped %d points\n", SkippedPoints);
	}

	// check if too many pixels displayed
	if (m_AutoAdjust) {
		UINT Prev = m_TempCameraFactor;
		const int MaxDiff = 4;
		// too many pixels - decrease density
		if (PixCounter > MaxPixels/3) {
			m_TempCameraFactor+=2;
		} else if (PixCounter < MaxPixels/4 && m_TempCameraFactor > m_CameraFactor) {
			m_TempCameraFactor--;
		}
		long Diff = m_TempCameraFactor - m_CameraFactor;
		if (Diff > MaxDiff)
			m_TempCameraFactor = m_CameraFactor + MaxDiff;
		else if (Diff < -MaxDiff)
			m_TempCameraFactor = m_CameraFactor - MaxDiff;
		if (m_TempCameraFactor < 1)
			m_TempCameraFactor = 1;
		if (Prev != m_TempCameraFactor)
			TRACE("Prev %d Next %d\n", Prev, m_TempCameraFactor);
	}
}

void CMotionBasedDraw::Draw(CSize ScreenSize, CDC* pDC, 
							CCameraPicture* pCameraPicture)
{
	CDib* pCameraDib = pCameraPicture->GetCurrCameraDib();

	if (m_NextDraw) {
		CGroup2::m_SelectNewBmp = true;
		//m_FunctionSelect++;
		//long Size = m_Group[0].GetSize() + m_Group[1].GetSize() + m_Group[2].GetSize();
		//m_FunctionSelect %= Size;
		SelectRandDrawFunc();
	}
	if (m_NextColor) {
		CGroup1::m_Color_Select++;
		CGroup1::m_Color_Select %= CGroup1::GetNumColors();	
	}

	DrawFunc* pDrawFunc = NULL;
	SelectDrawFunction(pDrawFunc);

	if (m_GroupSelect == 1)
	{
		CalcColorAreas(pCameraDib, CGroup2::m_Averages);
		CGroup2::m_pCameraPicture = pCameraPicture;
	}

	if (pDrawFunc) 
	{
		CSize CameraSize = pCameraDib->GetSize();
		
		const int CameraSizeX = CameraSize.cx;
		const int CameraSizeY = CameraSize.cy;
		// By camera image
		double FactorX = (double)ScreenSize.cx / (double)CameraSizeX;
		double FactorY = (double)ScreenSize.cy / (double)CameraSizeY;
		long lFactorX = (long)FactorX;
		long lFactorY = (long)FactorY;
		if (FactorX - (double)lFactorX > 0.5) lFactorX++;
		if (FactorY - (double)lFactorY > 0.5) lFactorY++;
		const int CameraFactor = min(40, max(m_TempCameraFactor, 1));

		if (m_GroupSelect != 1)
		{
			long PixCount = 0;
			GetMotionPoints(ScreenSize, pCameraPicture, MotionPixels, MAX_PIXELS, PixCount);
			for (int i = 0; i < PixCount; i++) 
			{
				pDrawFunc(pDC, ScreenSize, 
					MotionPixels[i].CameraX, MotionPixels[i].CameraY, // position on camera 
					MotionPixels[i].x, MotionPixels[i].y, // position on screen 
					lFactorX, lFactorY, CameraFactor,
					MotionPixels[i].Pix, MotionPixels[i].PrevPix, 0);
			}
		}
		else
		{
			// group2 draws only once
			pDrawFunc(pDC, ScreenSize, 
				0, 0, // position on camera 
				0, 0, // position on screen 
				lFactorX, lFactorY, CameraFactor,
				0, 0, 0);
		}
		// Display name
		if (m_DisplayFunctionName)
		{
			LPTSTR szName = NULL; 
			m_FunctionNames.Lookup(pDrawFunc, szName);
			if (szName) {
				COLORREF FgColor = CGroup1::SelectColor(0, 0, pCameraDib->GetPixel(0, 0));
				WORD Hue, Luminance, Saturation;
				CUtils::RGBtoHLS(FgColor, Hue, Luminance, Saturation);
				if (Luminance < 120) Luminance += 120;
				FgColor = CUtils::HLStoRGB(Hue, Luminance, Saturation);

				COLORREF oldT = pDC->SetTextColor(FgColor);
				COLORREF oldBK = pDC->SetBkColor(RGB(0,0,0));

				CFont f;
				f.CreatePointFont(140, "Arial", pDC);
				CFont* pOldF = pDC->SelectObject(&f);
				pDC->TextOut(0, 0, szName);
				pDC->SetTextColor(oldT);
				pDC->SetBkColor(oldBK);
				pDC->SelectObject(pOldF);
				f.DeleteObject();
			}
		}
	}


	if (m_NextDraw == TRUE) {
		long TimerPeriod = m_TimerGroup[m_GroupSelect];
		m_DrawTimerId = ::SetTimer(NULL, 555, TimerPeriod, TimerProc);
		m_NextDraw = FALSE;
	}
	if (m_NextColor == TRUE) {
		long TimerPeriod = m_TimerColor;
		m_ColorTimerId = ::SetTimer(NULL, 999, TimerPeriod, TimerProc);
		m_NextColor = FALSE;
	}
	if (m_NextCapture == TRUE) {
		long TimerPeriod = m_TimerCapture;
		if (TimerPeriod > 0) {
			DoCapture(pDC, ScreenSize);
			m_CaptureTimerId = ::SetTimer(NULL, 777, TimerPeriod, TimerProc);
			m_NextCapture = FALSE;
		}
	}
}


//////////////////////////////////////////////////////////////////////

void CMotionBasedDraw::DoCapture(CDC* pDC, CSize ScreenSize)
{
	if (m_EnableCapture && !m_CaptureFolder.IsEmpty()) {
		CString Path;
		if (m_UseSameFile && !m_FileName.IsEmpty()) {
			Path.Format("%s\\%s", m_CaptureFolder, m_FileName);
		} else {
			Path.Format("%s\\Capture%05d.bmp", m_CaptureFolder, m_Capturecounter ++);
		}
		/*
		// Code to be used in GDI drawing
		CMemDC* pMemDC = (CMemDC*)pDC;		
		CBitmap& bmp = *pMemDC->GetBitmap();
		HBITMAP hbm = (HBITMAP)bmp;
		CUtils::CreateBMPFile(Path, hbm, pDC->GetSafeHdc()); 
		*/
	}
}

//////////////////////////////////////////////////////////////////////
void CMotionBasedDraw::AddFunction(DrawFunc* pFunc, CArray<DrawFunc*, DrawFunc*>& GroupArray,
								   LPCTSTR szName)
{
	GroupArray.Add(pFunc);
	m_AllGroups.Add(pFunc);
	m_FunctionNames.SetAt(pFunc, szName);
	BOOL bEnable = AfxGetApp()->GetProfileInt("Functions", szName, 1);
	if (bEnable)
		m_EnableFunctions.SetAt(pFunc, bEnable);
	else
		m_EnableFunctions.RemoveKey(pFunc);
}

void CMotionBasedDraw::InitFunctions()
{
	//////////////////////////////
	// Group1
	//////////////////////////////

	// Basic draw of the last pic
	AddFunction(CGroup1::DrawBasic, m_Group[0], "תנועה טהורה");
	AddFunction(CGroup1::Draw1, m_Group[0], "סוכריות עגולות בטעמים");
	AddFunction(CGroup1::Draw2, m_Group[0], "משחק ילדים");
	AddFunction(CGroup1::Draw3, m_Group[0], "פעימות לב עם סוכריות");
	AddFunction(CGroup1::Draw4, m_Group[0], "עיר מופרעת");
	AddFunction(CGroup1::Draw5, m_Group[0], "קססה באקסטה");
	AddFunction(CGroup1::Draw6, m_Group[0], "פירפור חדרים");
	AddFunction(CGroup1::Draw7, m_Group[0], "כדוריות דם בסוטול");
	AddFunction(CGroup1::Draw8, m_Group[0], "המטוטלת של פוקו");
	AddFunction(CGroup1::ChangeCircle12, m_Group[0], "בועות");
	AddFunction(CGroup1::ChangeRect13, m_Group[0], "בועות בורגניות");
	AddFunction(CGroup1::ColorHigh16, m_Group[0], "חיסול ממוקד");
	AddFunction(CGroup1::EllipsHigh17, m_Group[0], "פעימות לב עם עיגולים בלחץ");
	AddFunction(CGroup1::Text18, m_Group[0], "כל הזכויות שמורות ל: (C)");
	AddFunction(CGroup1::ColorNames, m_Group[0], "ימין ישראלי");
	AddFunction(CGroup1::Cats, m_Group[0], "חתולים");
//	AddFunction(CGroup1::BlackAnger);
	//שמות המופיעים בצבעים שונים - מסרים פוליטיים
//	AddFunction(CGroup1::Cohavit);
	
	//////////////////////////////
	// Group2
	//////////////////////////////
	
	AddFunction(CGroup2::BTriangle19, m_Group[1], "מגן דוד בצבעי יסוד");
	AddFunction(CGroup2::Blines2color20, m_Group[1], "20 = ארבעה קווים בצבעים שונים");
	AddFunction(CGroup2::B9lines, m_Group[1], "21 = עשרים חמש צורות מגיבות");
	AddFunction(CGroup2::Blinesfromcenter, m_Group[1], "22 = עכביש צבעוני");
	AddFunction(CGroup2::Ellipse, m_Group[1], "Ellipse");
	AddFunction(CGroup2::Brectangle24, m_Group[1], "Brectangle24");
	AddFunction(CGroup2::BColorLines25, m_Group[1], "BColorLines25");
	AddFunction(CGroup2::BColorLines26, m_Group[1], "BColorLines26");
	AddFunction(CGroup2::BColorLines27, m_Group[1], "BColorLines27");
	AddFunction(CGroup2::BColorLines28, m_Group[1], "BColorLines28");
	AddFunction(CGroup2::DrawBitmap29, m_Group[1], "DrawBitmap29");
	
	//////////////////////////////
	// Group3
	//////////////////////////////
	
	AddFunction(CGroup1::Draw9, m_Group[2], "קווים מופשטים - אלכסונים מוזרים");
	AddFunction(CGroup1::Lots10, m_Group[2], "פופ ארט מעוך");
	AddFunction(CGroup1::LotsOrder11, m_Group[2], "פופ ארט תקין שלוש על שלוש");
	AddFunction(CGroup1::LinesTop14, m_Group[2], "LinesTop14");
	AddFunction(CGroup1::LinesCenter15, m_Group[2], "LinesCenter15");
}

void CMotionBasedDraw::SelectDrawFunction(DrawFunc*& pDrawFunc)							
{
	pDrawFunc = m_Group[m_GroupSelect].GetAt(m_FunctionSelect);
	if (pDrawFunc == NULL) {
		if (m_Group[m_GroupSelect].GetSize() > 0) {
			pDrawFunc = m_Group[m_GroupSelect].GetAt(0);
		}
	}
}

void CMotionBasedDraw::ToggleCapture()
{
	m_EnableCapture = !m_EnableCapture;
}

void CMotionBasedDraw::SelectFunctions()
{
	CSelectDrawingsDlg dlg;
	for (int i = 0; i < m_AllGroups.GetSize(); i++) {
		DrawFunc* pFunc = m_AllGroups.GetAt(i);
		LPTSTR szName = NULL;
		BOOL bEnable = FALSE;
		if (m_FunctionNames.Lookup(pFunc, szName) && szName) {
			m_EnableFunctions.Lookup(pFunc, bEnable);
			dlg.m_Names.AddTail(szName);
			dlg.m_Enable.SetAt(szName, (void*)bEnable);
		}
	}
	if (dlg.DoModal() == IDOK) {
		for (int i = 0; i < m_AllGroups.GetSize(); i++) {
			DrawFunc* pFunc = m_AllGroups.GetAt(i);
			LPTSTR szName = NULL;
			if (m_FunctionNames.Lookup(pFunc, szName) && szName) {
				BOOL bEnable = TRUE;
				dlg.m_Enable.Lookup(szName, (void*&)bEnable);
				if (bEnable)
					m_EnableFunctions.SetAt(pFunc, bEnable);
				else
					m_EnableFunctions.RemoveKey(pFunc);
				AfxGetApp()->WriteProfileInt("Functions", szName, bEnable);
			}
		}
	}
}
