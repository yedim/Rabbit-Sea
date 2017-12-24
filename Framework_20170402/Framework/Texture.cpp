#include "stdafx.h"
#include "Texture.h"
#include "DeviceMgr.h"

CTexture::CTexture()
{
}

CTexture::~CTexture(void)
{
	Release();
}

HRESULT CTexture::AddTexture(const TCHAR* pFileName)
{

	TCHAR			szTmp0[128] = L"";
	TCHAR			szTmp1[128] = L"�̹��� �ε� ���п�";

	lstrcpy(szTmp0, pFileName);
	lstrcat(szTmp0, szTmp1);

	m_pTexInfo = new TEXINFO;

	// �̹����� ������ ������ �´�.
	if (FAILED(D3DXGetImageInfoFromFile(pFileName
		, &m_pTexInfo->TexInfo)))
	{
		//ERRORCHK(L"�̹��� ���� �������� ���п�");
		return E_FAIL;
	}

	if (FAILED(D3DXCreateTextureFromFileEx(CDeviceMgr::GetInst()->GetDevice()
		, pFileName
		, m_pTexInfo->TexInfo.Width
		, m_pTexInfo->TexInfo.Height
		, m_pTexInfo->TexInfo.MipLevels
		, 0, m_pTexInfo->TexInfo.Format
		, D3DPOOL_DEFAULT
		, D3DX_DEFAULT
		, D3DX_DEFAULT
		, D3DCOLOR_XRGB(0, 0, 0)
		, &m_pTexInfo->TexInfo
		, NULL, &m_pTexInfo->pTexture)))
	{
		MessageBox(NULL, szTmp0, L"", MB_OK);
		return E_FAIL;
	}
	return S_OK;
}

TEXINFO* CTexture::GetTexture()
{
	return m_pTexInfo;
}
void CTexture::Release(void)
{
	//SAFE_DELETE(m_pTexInfo);
}
