// CameraPicture.cpp: implementation of the CCameraPicture class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DRW.h"
#include "CameraPicture.h"
#include "Dib.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCameraPicture::CCameraPicture()
:  m_StaticPicLoaded(FALSE)
{
	m_CurrCameraArray = 0;
	m_pDibCamera0 = new CDib;
	m_pDibCamera1 = new CDib;

	m_pDibDraw = new CDib;
	m_pDibStatic = new CDib;
}

CCameraPicture::~CCameraPicture()
{
	// Camera pictures
	delete m_pDibCamera0;
	delete m_pDibCamera1;

	// Static picture
	delete m_pDibDraw;
	delete m_pDibStatic;
}

bool CCameraPicture::IsInitialized()
{
	return m_pDibCamera0->IsInitialized() && m_pDibCamera1->IsInitialized(); 
}

bool CCameraPicture::LoadCameraPicture()
{
	m_CurrCameraArray = 1 - m_CurrCameraArray;
	CDib* pCameraDib = m_CurrCameraArray == 0 ? m_pDibCamera0 : m_pDibCamera1;
	return pCameraDib->LoadFromClipboard() != FALSE;	
}

void CCameraPicture::SelectStaticPic(const CString& PicturesFolder)
{
	if (m_Files.IsEmpty()) {
		CFileFind Finder;
		CString Filename;
		CString Path = PicturesFolder + "\\*.bmp";
		BOOL bMoreFiles = Finder.FindFile(Path);
		while (bMoreFiles) {
			bMoreFiles = Finder.FindNextFile();
			CString FullFilePath = Finder.GetFilePath();
			m_Files.AddTail(FullFilePath);
		}
	}

	if (! m_Files.IsEmpty()) {
		m_CurrStaticPicPath = m_Files.RemoveHead();
		m_Files.AddTail(m_CurrStaticPicPath);
		m_StaticPicLoaded = false;
	} else {
		m_CurrStaticPicPath.Empty();
	}
}

void CCameraPicture::LoadStaticPicture()
{
	if (! m_CurrStaticPicPath.IsEmpty()) {
		m_pDibStatic->Load(m_CurrStaticPicPath);
	}
}

void CCameraPicture::LoadStaticPic()
{
	if (! m_CurrStaticPicPath.IsEmpty()) {
		if (! m_StaticPicLoaded) {
			LoadStaticPicture();
			m_StaticPicLoaded = true;
		}
		*m_pDibDraw = *m_pDibStatic;
	}
}
