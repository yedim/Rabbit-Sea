#pragma once

#include "Defines.h"
#include "Single.h"

class CTexture;
class CTextureMgr
	: public CSingle<CTextureMgr>
{
	//�̹����� �� ��Ƽ� ��´�.
	map<wstring, CTexture*>	TextureMgr;

public:
	//�ؽ��� �߰� - ���ڰ��� Ű��, �̹��� ���
	void AddTexture(wstring _Key, wstring _TextureDir);
	//�ؽ�ó ã�� - ã������ Ű���� ������ ã�´�.
	TEXINFO* GetTextureInfo(wstring _Key);

public:
	CTextureMgr();
	~CTextureMgr();
};
