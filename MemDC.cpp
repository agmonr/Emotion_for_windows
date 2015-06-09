// MemDC.cpp : implementation file
//

#include "stdafx.h"
#include "MemDC.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNAMIC(CMemDC, CDC);

void CMemDC::BeforeDraw(CDC* pDC)
{
	pDC->GetClipBox(&m_Rect);
	m_pOldBitmap = SelectObject(&m_Bitmap);
	//SetWindowOrg(0,0);//m_Rect.left, m_Rect.top);
	SetWindowOrg(m_Rect.left, m_Rect.top);
}

void CMemDC::AfterDraw(CDC* pDC)
{	
	pDC->BitBlt(m_Rect.left, m_Rect.top, m_Rect.Width(), m_Rect.Height(),
				this, m_Rect.left, m_Rect.top, SRCCOPY);
	SelectObject(m_pOldBitmap);
}


/////////////////////////////////////////////////////////////////////////////
// CMemDC
CMemDC::CMemDC(int MaxX,int MaxY) : CDC(), m_pOldBitmap(NULL)
{
	CreateCompatibleDC(NULL);
	CRect Rect;
	CWnd *pWnd=CWnd::GetDesktopWindow();
	pWnd->GetClientRect(Rect);
	CDC *pDC=pWnd->GetDC();
	m_Bitmap.CreateCompatibleBitmap(pDC, __min(MaxX,Rect.Width()),__min(MaxY,Rect.Height()));
	pWnd->ReleaseDC(pDC);
}


CMemDC::~CMemDC()
{	
}

/*
HRESULT CMemDC::DestroyDDrawSurfaces()
{
	
	//Release DirectDrawEx interfaces
	if (m_pOffscreenSurface != NULL) 
	{
		m_pOffscreenSurface->Release();
		m_pOffscreenSurface=NULL;
	}	
	if (m_pDDClipper != NULL) 
	{
		m_pDDClipper->Release();
		m_pDDClipper=NULL;
	}
	if (m_pPrimarySurface != NULL) 
	{
		m_pPrimarySurface->Release();
		m_pPrimarySurface=NULL;
	}
	if (m_pDD != NULL) 
	{
		m_pDD->Release();
		m_pDD=NULL;
	}
	return NOERROR;
}


void CMemDC::PrepareOffScreenSurface()
{
	HRESULT		hr;
	//GetClientRect(&Rect); 

	// start GDI operations to perform overlay on top of offscreen #1
	m_pOffscreenSurface->GetDC(&hDC);

	m_pDC = CDC::FromHandle(hDC);

	m_pDC->SetMapMode(MM_ANISOTROPIC);
	m_pDC->SetViewportExt(m_Rect.Width(),m_Rect.Height());
	m_pDC->SetWindowExt(m_Rect.Width(), m_Rect.Height());	

}

void CMemDC::CopyFromOffScreenSurfaceToPrimarySurface()
{		
	HRESULT hr;
	m_pOffscreenSurface->ReleaseDC(hDC);

	hr = m_pPrimarySurface->Blt(&m_Rect, m_pOffscreenSurface, &m_Rect, DDBLT_WAIT, NULL);
}


HRESULT CMemDC::CreateDDrawSurfaces(CWnd *pWnd)
{
	pWnd->GetClientRect(&m_Rect);
	HRESULT			hr=NOERROR;
	DDSURFACEDESC	ddsd, ddsd2;

	hr= CoCreateInstance(CLSID_DirectDraw,
		    NULL, CLSCTX_ALL, IID_IDirectDraw7,(void**)&m_pDD);

	if(!FAILED(hr))
		hr= IDirectDraw7_Initialize(m_pDD, NULL);

	// query for IDirectDraw3 interface
//	CComQIPtr <IDirectDraw3, &IID_IDirectDraw3> m_pDD3(m_pDD);

    //Initialize the DDSURFACEDESC structure for the primary surface
	::ZeroMemory(&ddsd, sizeof(ddsd));
    ddsd.dwSize = sizeof(ddsd);    
	ddsd.dwFlags = DDSD_CAPS;
    ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE; 
    hr = m_pDD->CreateSurface(&ddsd, &m_pPrimarySurface, NULL);

    if(FAILED(hr))
    {   
		AfxMessageBox(_T("Couldn't create Primary Surface"));
    	return E_FAIL;
	}


	// Now, do the same for the offscreen surfaces.

    // The offscreen surface needs to use the same pixel format as the primary.
    // Query the primary surface to for its pixel format.
    hr = m_pPrimarySurface->GetSurfaceDesc(&ddsd);
    if(FAILED(hr))
    {   
		AfxMessageBox(_T("Couldn't GetSurfaceDesc"));
		return E_FAIL;
    }

	// Now, set the info for the offscreen surface #1, using the primary's pixel format.
    ::ZeroMemory(&ddsd2, sizeof(ddsd2));
	ddsd2.dwSize = sizeof(ddsd2);    
	ddsd2.dwFlags = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH | DDSD_PIXELFORMAT;
    ddsd2.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN;
    ddsd2.dwHeight = ddsd.dwHeight;	//set the height of the surfaces equal
    ddsd2.dwWidth  = ddsd.dwWidth;	//set the width of the surfaces equal
    ddsd2.ddpfPixelFormat = ddsd.ddpfPixelFormat; //set the pixel formats equal


    // Now, create the offscreen surface #1 and query for the latest interface.
	hr = m_pDD->CreateSurface(&ddsd2, &m_pOffscreenSurface, NULL);
	if(FAILED(hr))
    {   
		AfxMessageBox(_T("Couldn't create Offscreen Surface"));
		return E_FAIL;
    }


	//Add code for Clipper
	hr = m_pDD->CreateClipper(0, &m_pDDClipper, NULL);
	if(FAILED(hr))
    {   
		AfxMessageBox(_T("Couldn't create Clipper"));
		return E_FAIL;
    }
	
	hr = m_pPrimarySurface->SetClipper(m_pDDClipper);
	if(FAILED(hr))
    {   
		AfxMessageBox(_T("Call to SetClipper failed"));
		return E_FAIL;
    }

	
	hr = m_pDDClipper->SetHWnd(0, pWnd->m_hWnd);
	if(FAILED(hr))
    {   
		AfxMessageBox(_T("Call to SetHWnd failed"));
	    return E_FAIL;
    }

	return NOERROR;
}*/