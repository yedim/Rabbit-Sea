#include "stdafx.h"
#include "TextureMgr.h"
#include "Texture.h"

CTextureMgr::CTextureMgr()
{
}

CTextureMgr::~CTextureMgr()
{
}

void CTextureMgr::AddTexture(wstring _Key, wstring _TextureDir)
{
	CTexture* pTexture = new CTexture;

	// c_str()�Լ��� wstring���� ���ڿ� �ּҸ� ��������.
	pTexture->AddTexture(_TextureDir.c_str());

	TextureMgr.insert(make_pair(_Key, pTexture));
}

TEXINFO* CTextureMgr::GetTextureInfo(wstring _Key)
{
	map<wstring, CTexture*>::iterator iter = TextureMgr.find(_Key);

	//Ű�� ������ �˻��ؼ� ��ã������쿡 end()�� ��ȯ
	if (iter != TextureMgr.end())
	{
		//first�� Ű�� second ��
		return iter->second->GetTexture();
	}

	return NULL;
}