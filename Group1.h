#ifndef _GROUP1_H_
#define _GROUP1_H_

class CGroup1
{
public:
	static long m_Color_Select;

	static COLORREF SelectColor (int CameraX, int CameraY, COLORREF Pix);
	static long GetNumColors();

public:
	static void DrawBasic(CDC* pDC, CSize& ScreenSize,
		int CameraX, int CameraY, // position on camera
		long x, long y, // position on screen
		long lFactorX, long lFactorY, long CameraFactor,
		COLORREF Pix, COLORREF PrevPix, DWORD);
	static void Draw1(CDC* pDC, CSize& ScreenSize,
		int CameraX, int CameraY, // position on camera
		long x, long y, // position on screen
		long lFactorX, long lFactorY, long CameraFactor,
		COLORREF Pix, COLORREF PrevPix, DWORD);
	static void Draw2(CDC* pDC, CSize& ScreenSize,
		int CameraX, int CameraY, // position on camera
		long x, long y, // position on screen
		long lFactorX, long lFactorY, long CameraFactor,
		COLORREF Pix, COLORREF PrevPix, DWORD);
	static void Draw3(CDC* pDC, CSize& ScreenSize,
		int CameraX, int CameraY, // position on camera
		long x, long y, // position on screen
		long lFactorX, long lFactorY, long CameraFactor,
		COLORREF Pix, COLORREF PrevPix, DWORD);
	static void Draw4(CDC* pDC, CSize& ScreenSize,
		int CameraX, int CameraY, // position on camera
		long x, long y, // position on screen
		long lFactorX, long lFactorY, long CameraFactor,
		COLORREF Pix, COLORREF PrevPix, DWORD);
	static void Draw5(CDC* pDC, CSize& ScreenSize,
		int CameraX, int CameraY, // position on camera
		long x, long y, // position on screen
		long lFactorX, long lFactorY, long CameraFactor,
		COLORREF Pix, COLORREF PrevPix, DWORD);
	static void Draw6(CDC* pDC, CSize& ScreenSize,
		int CameraX, int CameraY, // position on camera
		long x, long y, // position on screen
		long lFactorX, long lFactorY, long CameraFactor,
		COLORREF ix, COLORREF PrevPix, DWORD);
	static void Draw7(CDC* pDC, CSize& ScreenSize,
		int CameraX, int CameraY, // position on camera
		long x, long y, // position on screen
		long lFactorX, long lFactorY, long CameraFactor,
		COLORREF Pix, COLORREF PrevPix, DWORD);
	static void Draw8(CDC* pDC, CSize& ScreenSize,
		int CameraX, int CameraY, // position on camera
		long x, long y, // position on screen
		long lFactorX, long lFactorY, long CameraFactor,
		COLORREF Pix, COLORREF PrevPix, DWORD);
	static void ChangeCircle12(CDC* pDC, CSize& ScreenSize,
		int CameraX, int CameraY, // position on camera
		long x, long y, // position on screen
		long lFactorX, long lFactorY, long CameraFactor,
		COLORREF Pix, COLORREF PrevPix, DWORD);
	static void Cats(CDC* pDC, CSize& ScreenSize,
		int CameraX, int CameraY, // position on camera
		long x, long y, // position on screen
		long lFactorX, long lFactorY, long CameraFactor,
		COLORREF Pix, COLORREF PrevPix, DWORD);

	static void ChangeRect13(CDC* pDC, CSize& ScreenSize,
		int CameraX, int CameraY, // position on camera
		long x, long y, // position on screen
		long lFactorX, long lFactorY, long CameraFactor,
		COLORREF Pix, COLORREF PrevPix, DWORD);
	static void ColorHigh16(CDC* pDC, CSize& ScreenSize,
		int CameraX, int CameraY, // position on camera
		long x, long y, // position on screen
		long lFactorX, long lFactorY, long CameraFactor,
		COLORREF Pix, COLORREF PrevPix, DWORD);
	static void EllipsHigh17(CDC* pDC, CSize& ScreenSize,
		int CameraX, int CameraY, // position on camera
		long x, long y, // position on screen
		long lFactorX, long lFactorY, long CameraFactor,
		COLORREF Pix, COLORREF PrevPix, DWORD);
	static void Text18(CDC* pDC, CSize& ScreenSize,
		int CameraX, int CameraY, // position on camera
		long x, long y, // position on screen
		long lFactorX, long lFactorY, long CameraFactor,
		COLORREF Pix, COLORREF PrevPix, DWORD);
	static void ColorNames(CDC* pDC, CSize& ScreenSize,
		int CameraX, int CameraY, // position on camera
		long x, long y, // position on screen
		long lFactorX, long lFactorY, long CameraFactor,
		COLORREF Pix, COLORREF PrevPix, DWORD);


	// Group 3

	static void Draw9(CDC* pDC, CSize& ScreenSize,
		int CameraX, int CameraY, // position on camera
		long x, long y, // position on screen
		long lFactorX, long lFactorY, long CameraFactor,
		COLORREF Pix, COLORREF PrevPix, DWORD);
	static void Lots10(CDC* pDC, CSize& ScreenSize,
		int CameraX, int CameraY, // position on camera
		long x, long y, // position on screen
		long lFactorX, long lFactorY, long CameraFactor,
		COLORREF Pix, COLORREF PrevPix, DWORD);
	static void LotsOrder11(CDC* pDC, CSize& ScreenSize,
		int CameraX, int CameraY, // position on camera
		long x, long y, // position on screen
		long lFactorX, long lFactorY, long CameraFactor,
		COLORREF Pix, COLORREF PrevPix, DWORD);
	static void LinesTop14(CDC* pDC, CSize& ScreenSize,
		int CameraX, int CameraY, // position on camera
		long x, long y, // position on screen
		long lFactorX, long lFactorY, long CameraFactor,
		COLORREF Pix, COLORREF PrevPix, DWORD);
	static void LinesCenter15(CDC* pDC, CSize& ScreenSize,
		int CameraX, int CameraY, // position on camera
		long x, long y, // position on screen
		long lFactorX, long lFactorY, long CameraFactor,
		COLORREF Pix, COLORREF PrevPix, DWORD);

};

#endif // _GROUP1_H_