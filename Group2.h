#ifndef _GROUP2_H_
#define _GROUP2_H_

#include "BaseDraw.h"


class CGroup2
{
public:
	static COLORREF m_Averages[AVG_SIZE][AVG_SIZE];
	static CString m_BmpFile;
	static CStringList m_BmpFiles;
	static CWnd* m_pWnd;
	static bool m_SelectNewBmp;
	static CCameraPicture* m_pCameraPicture;

	static void DrawBackground(CDC* pDC, COLORREF cr);
	static void ApplyRgbChangeToDib(CDib& Dib, long RAll, long GAll, long BAll);

public:

	static void BTriangle19(CDC* pDC, CSize& ScreenSize,
		int CameraX, int CameraY, // position on camera
		long x, long y, // position on screen
		long lFactorX, long lFactorY, long CameraFactor,
		COLORREF Pix, COLORREF PrevPix, DWORD);
	static void Blines2color20(CDC* pDC, CSize& ScreenSize,
		int CameraX, int CameraY, // position on camera
		long x, long y, // position on screen
		long lFactorX, long lFactorY, long CameraFactor,
		COLORREF Pix, COLORREF PrevPix, DWORD);
	static void B9lines(CDC* pDC, CSize& ScreenSize,
		int CameraX, int CameraY, // position on camera
		long x, long y, // position on screen
		long lFactorX, long lFactorY, long CameraFactor,
		COLORREF Pix, COLORREF PrevPix, DWORD);
	static void Blinesfromcenter(CDC* pDC, CSize& ScreenSize,
		int CameraX, int CameraY, // position on camera
		long x, long y, // position on screen
		long lFactorX, long lFactorY, long CameraFactor,
		COLORREF Pix, COLORREF PrevPix, DWORD);

	static void Ellipse(CDC* pDC, CSize& ScreenSize,
		int CameraX, int CameraY, // position on camera
		long x, long y, // position on screen
		long lFactorX, long lFactorY, long CameraFactor,
		COLORREF Pix, COLORREF PrevPix, DWORD);

	static void Brectangle24(CDC* pDC, CSize& ScreenSize,
		int CameraX, int CameraY, // position on camera
		long x, long y, // position on screen
		long lFactorX, long lFactorY, long CameraFactor,
		COLORREF Pix, COLORREF PrevPix, DWORD);

	static void BColorLines25(CDC* pDC, CSize& ScreenSize,
		int CameraX, int CameraY, // position on camera
		long x, long y, // position on screen
		long lFactorX, long lFactorY, long CameraFactor,
		COLORREF Pix, COLORREF PrevPix, DWORD);

	static void BColorLines26(CDC* pDC, CSize& ScreenSize,
		int CameraX, int CameraY, // position on camera
		long x, long y, // position on screen
		long lFactorX, long lFactorY, long CameraFactor,
		COLORREF Pix, COLORREF PrevPix, DWORD);
	
	static void BColorLines27(CDC* pDC, CSize& ScreenSize,
		int CameraX, int CameraY, // position on camera
		long x, long y, // position on screen
		long lFactorX, long lFactorY, long CameraFactor,
		COLORREF Pix, COLORREF PrevPix, DWORD);
	
	static void BColorLines28 (CDC* pDC, CSize& ScreenSize,
		int CameraX, int CameraY, // position on camera
		long x, long y, // position on screen
		long lFactorX, long lFactorY, long CameraFactor,
		COLORREF Pix, COLORREF PrevPix, DWORD);
	
	
	static void DrawBitmap29(CDC* pDC, CSize& ScreenSize,
		int CameraX, int CameraY, // position on camera
		long x, long y, // position on screen
		long lFactorX, long lFactorY, long CameraFactor,
		COLORREF Pix, COLORREF PrevPix, DWORD);
};

#endif // _GROUP2_H_