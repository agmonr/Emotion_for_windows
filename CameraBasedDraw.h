// CameraBasedDraw.h: interface for the CCameraBasedDraw class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CAMERABASEDDRAW_H__BE965736_D4E1_4182_A2F8_95C9D90ED8DF__INCLUDED_)
#define AFX_CAMERABASEDDRAW_H__BE965736_D4E1_4182_A2F8_95C9D90ED8DF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "BaseDraw.h"

struct MotionPixel
{
	short CameraX, CameraY;
	short x,y;
	COLORREF Pix, PrevPix;
};

class CCameraPicture;

class CCameraBasedDraw : public CBaseDraw  
{
public:
	CCameraBasedDraw();
	virtual ~CCameraBasedDraw();

	virtual IsCameraDraw() { return true; }
	virtual void Draw(CSize ScreenSize, CDC* pDC, CCameraPicture* pCameraPicture) = 0;
};

typedef void DrawFunc(CDC*, CSize&,	int, int, long, long, long, long, long, COLORREF, COLORREF, DWORD/*lParam*/);

class CMotionBasedDraw : public CCameraBasedDraw
{
protected:
	long m_FunctionSelect;
	long m_GroupSelect;

	static UINT m_DrawTimerId;
	static UINT m_ColorTimerId;
	static UINT m_CaptureTimerId;
	static BOOL m_NextDraw;
	static BOOL m_NextColor;
	static BOOL m_NextCapture;

	CWnd* m_pWnd;

	UINT m_TimerGroup[3];
	UINT m_TimerColor;
	BOOL m_DisplayGroup[3];
	CString m_CaptureFolder;
	UINT m_TimerCapture;
	UINT m_CameraFactor;
	UINT m_TempCameraFactor;
	BOOL m_AutoAdjust;
	UINT m_ColorThreshold;
	UINT m_MinNeighbours;
	BOOL m_UseSameFile;
	CString m_FileName;
	BOOL m_DisplayFunctionName;
	
	CArray<DrawFunc*, DrawFunc*> m_Group[3];
	CArray<DrawFunc*, DrawFunc*> m_AllGroups;
	CMap<DrawFunc*, DrawFunc*, LPCTSTR, LPCTSTR> m_FunctionNames;
	CMap<DrawFunc*, DrawFunc*, BOOL, BOOL> m_EnableFunctions;

	UINT m_Capturecounter;
	BOOL m_EnableCapture;

#define MAX_CAMERA_X 1024
#define MAX_CAMERA_Y 768
#define MAX_PIXELS (600*800)
	COLORREF PixArray[MAX_CAMERA_X][MAX_CAMERA_Y];
	COLORREF PrevPixArray[MAX_CAMERA_X][MAX_CAMERA_Y];
	COLORREF DiffArray[MAX_CAMERA_X][MAX_CAMERA_Y];
	DWORD RelevantPixels[MAX_CAMERA_X*MAX_CAMERA_Y];
	MotionPixel MotionPixels[MAX_PIXELS];

public:
	CMotionBasedDraw(CWnd* pWnd);
	virtual IsMotionDraw() { return true; }
	void DoSettings();
	static void CALLBACK TimerProc(HWND hWnd, UINT nMsg, UINT nTimerId, DWORD dwTime);
	void SelectDrawFunction(DrawFunc*& pDrawFunc);

	void GetMotionPoints(CSize ScreenSize, CCameraPicture* pCameraPicture, 
		MotionPixel* MotionPixels, long MaxMotionPixels, long& MotionPixelsCount);

	void SelectRandDrawFunc();
	void DoCapture(CDC* pDC, CSize ScreenSize);
	void DoNextDraw();
	void ToggleCapture();
	void SelectFunctions();
	void AddFunction(DrawFunc* pFunc, CArray<DrawFunc*, DrawFunc*>& Array,
		LPCTSTR szName = "");
	void DisplayFunctionName(CDC* pDC, DrawFunc* pDrawFunc);

	// Overrides
	virtual void Init();
	virtual void InitFunctions();
	virtual void Terminate();
	virtual void Draw(CSize ScreenSize, CDC* pDC, CCameraPicture* pCameraPicture);
};

#endif // !defined(AFX_CAMERABASEDDRAW_H__BE965736_D4E1_4182_A2F8_95C9D90ED8DF__INCLUDED_)
