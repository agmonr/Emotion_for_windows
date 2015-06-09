// VideoCapture.h: interface for the CVideoCapture class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_VIDEOCAPTURE_H__A10DE55E_B711_4B2F_AFEA_93936053DD7E__INCLUDED_)
#define AFX_VIDEOCAPTURE_H__A10DE55E_B711_4B2F_AFEA_93936053DD7E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CVideoCapture  
{
public:
	CVideoCapture();
	virtual ~CVideoCapture();

	void Init(HWND hWndView);
	BOOL vidcapInitHardware(HWND hwnd, HWND hwndCap, UINT uIndex);
	void vidcapSetLive(BOOL bLive);
	void vidcapSetOverlay(BOOL bOverlay);
	void CaptureOneFrame();
	void CaptureOneFrameToClipboard();

	BOOL           gbHaveHardware;
	WORD           gwDeviceIndex ;
	BOOL gbLive, gbOverlay;
	CAPDRIVERCAPS  gCapDriverCaps;
	CAPSTATUS      gCapStatus ;
	BOOL           gbIsScrncap;  // For Scrncap.drv, we must yield
	HWND		   ghWndCap;
};

#endif // !defined(AFX_VIDEOCAPTURE_H__A10DE55E_B711_4B2F_AFEA_93936053DD7E__INCLUDED_)
