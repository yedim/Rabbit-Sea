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

	// c_str()함수가 wstring에서 문자열 주소를 가져와줌.
	pTexture->AddTexture(_TextureDir.c_str());

	TextureMgr.insert(make_pair(_Key, pTexture));
}

TEXINFO* CTextureMgr::GetTextureInfo(wstring _Key)
{
	map<wstring, CTexture*>::iterator iter = TextureMgr.find(_Key);

	//키를 가지고 검색해서 못찾았을경우에 end()를 반환
	if (iter != TextureMgr.end())
	{
		//first가 키값 second 값
		return iter->second->GetTexture();
	}

	return NULL;
}