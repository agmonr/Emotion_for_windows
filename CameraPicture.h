// CameraPicture.h: interface for the CCameraPicture class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CameraPicture_H__D1337711_7ABE_4518_BF11_F207B1D21923__INCLUDED_)
#define AFX_CameraPicture_H__D1337711_7ABE_4518_BF11_F207B1D21923__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CDib;

class CCameraPicture  
{
public:
	CCameraPicture();
	virtual ~CCameraPicture();

	bool LoadCameraPicture();

	CDib* GetCurrCameraDib() { return m_CurrCameraArray == 0 ? m_pDibCamera0 : m_pDibCamera1; }
	CDib* GetPrevCameraDib() { return m_CurrCameraArray == 0 ? m_pDibCamera1 : m_pDibCamera0; }

	CDib* GetDibDraw() { return m_pDibDraw; }

	bool IsInitialized();

	void SelectStaticPic(const CString& PicturesFolder);
	void LoadStaticPicture();
	void LoadStaticPic();

private:
	// Multi thread protection
	CMutex m_Mutex;

	// Camera picture
	CDib* m_pDibCamera0;
	CDib* m_pDibCamera1;
	long m_CurrCameraArray; // can be 0 or 1

	// Static picture
	CString m_CurrStaticPicPath;
	CStringList m_Files;
	bool m_StaticPicLoaded;
	CDib* m_pDibDraw;
	CDib* m_pDibStatic;

};

#endif // !defined(AFX_CameraPicture_H__D1337711_7ABE_4518_BF11_F207B1D21923__INCLUDED_)