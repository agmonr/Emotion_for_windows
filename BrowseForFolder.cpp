#include "StdAfx.h"
#include "BrowseForFolder.h"

CBrowseForFolder::CBrowseForFolder()
{
	m_InitialPath = _T("");
}

bool CBrowseForFolder::Browse(HWND hWnd,
							  CString& Path,
							  LPCTSTR pszInitialPath,
							  LPCTSTR pszTitle,
							  UINT uFlags,
							  int* piImage)
{
	if (pszInitialPath) {
		m_InitialPath = pszInitialPath;
		m_InitialPath.TrimLeft();
		m_InitialPath.TrimRight();
		if (! m_InitialPath.IsEmpty() && m_InitialPath.Right(1) == '\\') {
			m_InitialPath.SetAt(m_InitialPath.GetLength()-1, 0);
		}
	} else {
		m_InitialPath = _T("");
	}

	char szPath[MAX_PATH];

	BROWSEINFO bi;
	bi.hwndOwner = hWnd; 
    bi.pidlRoot = NULL; 
    bi.pszDisplayName = szPath; 
    bi.lpszTitle = (pszTitle ? pszTitle : ""); 
    bi.ulFlags = uFlags; 
    bi.lpfn = BrowseCallbackProc; 
    bi.lParam = (LPARAM)this;
    
	ITEMIDLIST* pidl;
	if (pidl = SHBrowseForFolder(&bi))
	{
		if (piImage)
			*piImage = bi.iImage;

		SHGetPathFromIDList(pidl, szPath);
		Path = szPath;

		return true;
	}

	return false;
}

int CALLBACK CBrowseForFolder::BrowseCallbackProc(HWND hwnd, UINT uMsg, LPARAM lParam, LPARAM lpData)
{
	CBrowseForFolder* pBrowseForFolder = (CBrowseForFolder*)lpData;

	if (uMsg == BFFM_INITIALIZED && !pBrowseForFolder->m_InitialPath.IsEmpty())
		::SendMessage(hwnd,BFFM_SETSELECTION,TRUE,(LPARAM)(LPCSTR)pBrowseForFolder->m_InitialPath);

	return 0;
}
