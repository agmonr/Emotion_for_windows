//#include "D3DFont.h"

//-----------------------------------------------------------------------------
// Name: class CMeshRender
// Desc: Main class to run this application. Most functionality is inherited
//       from the CD3DApplication base class.
//-----------------------------------------------------------------------------
class CMeshRender
{
    TCHAR               m_strInitialDir[512];
    TCHAR               m_strMeshFilename[512]; // Filename of mesh
    LPD3DXPMESH*        m_pPMeshes;          
    LPD3DXPMESH         m_pPMeshFull;          
    DWORD               m_cPMeshes;
    DWORD               m_iPMeshCur;

    D3DMATERIAL9*       m_mtrlMeshMaterials;
    LPDIRECT3DTEXTURE9* m_pMeshTextures;        // Array of textures, entries are NULL if no texture specified
    DWORD               m_dwNumMaterials;       // Number of materials

    //CD3DArcBall         m_ArcBall;              // Mouse rotation utility
    D3DXVECTOR3         m_vObjectCenter;        // Center of bounding sphere of object
    FLOAT               m_fObjectRadius;        // Radius of bounding sphere of object

    //CD3DFont*           m_pFont;                // Font for displaying help
    BOOL                m_bDisplayHelp;
    BOOL                m_bShowOptimized;

    BOOL                m_bInitDone;            // hold off on any reactino to messages until fully inited
public:
	LPDIRECT3DDEVICE9	m_pd3dDevice;
public:
    void SetNumVertices(DWORD dwNumMeshVertices);
	HRESULT InitDeviceObjects();
	HRESULT RestoreDeviceObjects();
	HRESULT DeleteDeviceObjects();
	HRESULT InvalidateDeviceObjects();
	HRESULT Render();
	HRESULT FinalCleanup();

    CMeshRender();
};
