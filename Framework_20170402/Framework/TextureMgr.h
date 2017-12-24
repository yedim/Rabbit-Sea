#pragma once

#include "Defines.h"
#include "Single.h"

class CTexture;
class CTextureMgr
	: public CSingle<CTextureMgr>
{
	//이미지를 다 모아서 담는다.
	map<wstring, CTexture*>	TextureMgr;

public:
	//텍스쳐 추가 - 인자값은 키값, 이미지 경로
	void AddTexture(wstring _Key, wstring _TextureDir);
	//텍스처 찾기 - 찾을때는 키값만 가지고 찾는다.
	TEXINFO* GetTextureInfo(wstring _Key);

public:
	CTextureMgr();
	~CTextureMgr();
};
