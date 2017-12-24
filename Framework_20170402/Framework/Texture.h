#pragma once

#include "Defines.h"


class CTexture
{
private:
	TEXINFO*	m_pTexInfo;

public:
	HRESULT AddTexture(const TCHAR* pFileName);
	virtual TEXINFO* GetTexture();
	void Release();
public:
	CTexture(void);
	~CTexture(void);
};

