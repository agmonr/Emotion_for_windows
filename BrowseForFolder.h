#ifndef _BrowseForFolder_H_
#define _BrowseForFolder_H_

#include <shlobj.h>

class CBrowseForFolder
{
public:
	CBrowseForFolder();
	bool Browse(HWND hWnd,
			    CString& Path,
			    LPCTSTR pszInitialPath = NULL,
			    LPCTSTR pszTitle = NULL,
			    UINT uFlags = BIF_RETURNONLYFSDIRS,
				int* piImage = NULL);

protected:
	static int CALLBACK BrowseCallbackProc(HWND hwnd, UINT uMsg, LPARAM lParam, LPARAM lpData); 

	CString m_InitialPath;
};

#endif	// _BrowseForFolder_H_