#pragma once

#include "Defines.h"

//클래스 전방 선언
class CObj;
class CStage;
class CMainGame
{
private:
	float		m_fTime;
	CStage*		m_CurrentStage;

public:
	HRESULT Initialize(void);
	void Update(void);
	void Render(void);
	void Release(void);

public:
	void ReadTexture();
	void CheckCheatKey();

public:
	CMainGame(void);
	~CMainGame(void);
};
