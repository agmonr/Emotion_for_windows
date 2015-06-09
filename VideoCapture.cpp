// VideoCapture.cpp: implementation of the CVideoCapture class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DRW.h"
#include "VideoCapture.h"
#include <windowsx.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CVideoCapture::CVideoCapture()
:	gbHaveHardware(false), gwDeviceIndex(0), gbLive(false), gbOverlay(false),
	gbIsScrncap(FALSE), ghWndCap(NULL)
{
	ZeroMemory(&gCapDriverCaps, sizeof(gCapDriverCaps));
	ZeroMemory(&gCapStatus, sizeof(gCapStatus));

}

CVideoCapture::~CVideoCapture()
{

}


//////////////////////////////////////////////////////////////////////

void CVideoCapture::Init(HWND hWndView)
{
	ghWndCap = capCreateCaptureWindow(
                    NULL,
                    WS_CHILD /*| WS_VISIBLE*/,
                    0, 0, 160, 120,
                    hWndView,               // parent window
                    1                   // child window id
              );

	if (ghWndCap) {
		vidcapInitHardware(hWndView, ghWndCap, 0);
	} else {
		AfxMessageBox("Failed to create capture window");
	}
}

//////////////////////////////////////////////////////////////////////

/*
 * Connect the capture window to a capture driver.
 * uIndex specifies the index of the driver to use.
 * Returns TRUE on success, or FALSE if the driver connection failed.
 */
BOOL CVideoCapture::vidcapInitHardware(HWND hwnd, HWND hwndCap, UINT uIndex)
{
    UINT    uError;
//    UINT    uI;
//    HMENU   hMenu;
    char    szName[MAX_PATH];
    char    szVersion[MAX_PATH];

    // Since the driver may not provide a reliable error string
    // provide a default
	CString gachLastError;
    gachLastError.LoadString(IDS_ERR_FIND_HARDWARE);

    // Try connecting to the capture driver
    if (uError = capDriverConnect(hwndCap, uIndex)) {
        gbHaveHardware = TRUE;
        gwDeviceIndex = uIndex;
    }
    else {
        gbHaveHardware = FALSE;
        gbLive = FALSE;
        gbOverlay = FALSE;
    }

    // Get the capabilities of the capture driver
    capDriverGetCaps(hwndCap, &gCapDriverCaps, sizeof(CAPDRIVERCAPS)) ;

    // Get the settings for the capture window
    capGetStatus(hwndCap, &gCapStatus , sizeof(gCapStatus));

    // Unlike all other capture drivers, Scrncap.drv needs to use
    // a Yield callback, and we don't want to abort on mouse clicks,
    // so determine if the current driver is Scrncap.drv
    capGetDriverDescription (uIndex, 
                szName, sizeof (szName),
                szVersion, sizeof (szVersion));

    // Set a flag if we're using Scrncap.drv
    gbIsScrncap = (BOOL) _fstrstr (szName, "Screen Capture");

    // Get video format and adjust capture window
    //vidcapLayout(ghWndMain);
    //InvalidateRect(ghWndMain, NULL, TRUE);

    // set the preview rate (units are millisecs)
    capPreviewRate(hwndCap, gbHaveHardware ? 33 : 0); 

    // set live/overlay to default
    vidcapSetLive(gbLive);
    vidcapSetOverlay(gbOverlay);

    strcat (szName, ",   ");
    strcat (szName, szVersion);

    return gbHaveHardware;
}

void CVideoCapture::vidcapSetLive(BOOL bLive)
{
    capPreview(ghWndCap, bLive);
/*
    gbLive = bLive;

    if (bLive == TRUE) {
        vidcapSetOverlay(FALSE);
    }
*/
}

void CVideoCapture::vidcapSetOverlay(BOOL bOverlay)
{
    if (!gCapDriverCaps.fHasOverlay) {
        //CheckMenuItem(GetMenu(ghWndMain), IDM_O_OVERLAY,
        //    MF_BYCOMMAND | MF_UNCHECKED);
        gbOverlay = FALSE;
        return;
    }

    capOverlay(ghWndCap, bOverlay);

    gbOverlay = bOverlay;

    if (bOverlay == TRUE) {
        vidcapSetLive(FALSE);
    }
}

void CVideoCapture::CaptureOneFrame()
{
	BOOL fResult = 0;
	static int fofo = 0;
	char FileName[255];
    // Turn off overlay / preview (gets turned off by frame capture)
    vidcapSetLive(FALSE);
    vidcapSetOverlay(FALSE);

    // Grab a frame
    fResult = capGrabFrameNoStop(ghWndCap) ;

	sprintf(FileName, "c:\\1\\test%d.bmp", fofo);
	//fofo++;
	fResult = capFileSaveDIB(ghWndCap, FileName);
}

void CVideoCapture::CaptureOneFrameToClipboard()
{
	BOOL fResult = 0;
    // Turn off overlay / preview (gets turned off by frame capture)
    vidcapSetLive(FALSE);
    vidcapSetOverlay(FALSE);

    // Grab a frame
    fResult = capGrabFrameNoStop(ghWndCap) ;

	fResult = capEditCopy(ghWndCap);
}
