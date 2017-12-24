#include "StdAfx.h"
#include "MainGame.h"

#include "Texture.h"
#include "DeviceMgr.h"
#include "TimeMgr.h"
#include "TextureMgr.h"
#include "ObjMgr.h"
#include "Obj.h"
#include "Player.h"
#include "Monster.h"
#include "Bullet.h"
#include "BackGround.h"
#include "Mouse.h"
#include "MenuButton.h"
#include "StageOne.h"
#include "StageTwo.h"
#include "StageThree.h"

CMainGame::CMainGame(void)
{
}

CMainGame::~CMainGame(void)
{
	Release();
}
HRESULT CMainGame::Initialize(void)
{
	srand(unsigned(time(NULL)));

	m_fTime = 0.f;

	//WINMODE_FULL //WINMODE_WIN
	CDeviceMgr::GetInst()->InitDevice(WINMODE_WIN);

	// 이미지 로드
	ReadTexture();

	//타이머를 시작해주세요
	CTimeMgr::GetInst()->InitTimeMgr();
	CObjMgr::GetInst()->Initialize();

	CObjMgr::GetInst()->CurrentStageKey = STAGE_ONE;
	m_CurrentStage = new CStageOne;
	m_CurrentStage->Initialize();

	return S_OK;
}
void CMainGame::CheckCheatKey(void)
{
	// 스테이지 전환 치트키 - 메뉴
	if (GetAsyncKeyState(VK_F1))
	{
		CObjMgr::GetInst()->CurrentStageKey = STAGE_ONE;
		CObjMgr::GetInst()->ChangeStage = true;
	}
	// 스테이지 전환 치트키 - 1스테이지
	if (GetAsyncKeyState(VK_F2))
	{
		CObjMgr::GetInst()->CurrentStageKey = STAGE_TWO;
		CObjMgr::GetInst()->ChangeStage = true;
	}
	// 스테이지 전환 치트키 - 2스테이지
	if (GetAsyncKeyState(VK_F3))
	{
		CObjMgr::GetInst()->CurrentStageKey = STAGE_THREE;
		CObjMgr::GetInst()->ChangeStage = true;
	}
	//무기 업그레이드
	if (GetAsyncKeyState(VK_F4))
	{
		CObj* Player = CObjMgr::GetInst()->GetPlayer();
		if (Player != NULL)
		{
			((CPlayer*)Player)->PlayerUpgrade = 2;
		}
	}
	// 무적모드
	if (GetAsyncKeyState(VK_F5))
	{
		CObjMgr::GetInst()->Muzuk = true;
	}
}
void CMainGame::Update(void)
{
	CheckCheatKey();

	//마우스 좌표를 갱신
	CMouse::SetMousePos();

	//타이머의 값을 갱신시켜 주세요
	CTimeMgr::GetInst()->SetTimePerSec();

	//매니저 클래스안에 들어있는 객체들을 갱신시킨다.
	CObjMgr::GetInst()->Update();

	//해당 스테이지 전용 로직이 필요한 경우에 사용한다.
	m_CurrentStage->Update();


	//스테이지 전환 코드
	if (CObjMgr::GetInst()->ChangeStage == true)
	{
		//스테이지 전환했으면 꼭 다시 false로 바꿔준다.
		CObjMgr::GetInst()->ChangeStage = false;
		//전 스테이지에 있는 객체들을 다 지운다.
		CObjMgr::GetInst()->Release();

		//스테이지 객체에 다시 할당한다.
		delete m_CurrentStage;

		if (CObjMgr::GetInst()->CurrentStageKey == STAGE_ONE)
		{
			m_CurrentStage = new CStageOne;
		}
		else if (CObjMgr::GetInst()->CurrentStageKey == STAGE_TWO)
		{
			m_CurrentStage = new CStageTwo;
		}
		else if (CObjMgr::GetInst()->CurrentStageKey == STAGE_THREE)
		{
			m_CurrentStage = new CStageThree;
		}

		//스테이지를 초기화 == 해당 스테이지의 오브젝트들을 추가한다.
		m_CurrentStage->Initialize();
	}
}

void CMainGame::Render( void )
{
	CDeviceMgr::GetInst()->Render_Begin();
	CObjMgr::GetInst()->Render();
	CDeviceMgr::GetInst()->Render_End();
}

void CMainGame::Release( void )
{
	CObjMgr::GetInst()->Release();
}

void CMainGame::ReadTexture()
{
	CTextureMgr::GetInst()->AddTexture(L"Player"
		, L"../Texture/Player.png");

	CTextureMgr::GetInst()->AddTexture(L"Item"
		, L"../Texture/Item.png");

	// 몬스터
	CTextureMgr::GetInst()->AddTexture(L"Monster"
		, L"../Texture/Monster_0.png");

	CTextureMgr::GetInst()->AddTexture(L"Monster_R"
		, L"../Texture/Monster_01.png");

	CTextureMgr::GetInst()->AddTexture(L"BossMonster"
		, L"../Texture/Boss.png");

	CTextureMgr::GetInst()->AddTexture(L"LastBossMonster"
		, L"../Texture/Boss_2.png");

	CTextureMgr::GetInst()->AddTexture(L"FollowMonster"
		, L"../Texture/Monster_1.png");

	// 배경
	CTextureMgr::GetInst()->AddTexture(L"Title"
		, L"../Texture/Title.png");

	CTextureMgr::GetInst()->AddTexture(L"BackGround"
		, L"../Texture/BackGround.png");

	CTextureMgr::GetInst()->AddTexture(L"BackObj"
		, L"../Texture/BackObj.png");

	CTextureMgr::GetInst()->AddTexture(L"NextStage"
		, L"../Texture/NextStage.png");

	// 총알
	CTextureMgr::GetInst()->AddTexture(L"Bullet"
		, L"../Texture/Bullet.png");
	CTextureMgr::GetInst()->AddTexture(L"MonsterBullet"
		, L"../Texture/MonsterBullet.png");

	// 장수 많은 이펙트
	for (int i = 0; i < 17; ++i)
	{
		TCHAR szEffectKey[64] = {};
		TCHAR szEffectDir[128] = {};

		wsprintf(szEffectKey, L"Effect_%d", i);
		wsprintf(szEffectDir, L"../Texture/Effect/Effect_%d.png", i);

		CTextureMgr::GetInst()->AddTexture(szEffectKey, szEffectDir);
	}

	CTextureMgr::GetInst()->AddTexture(L"StartButton"
		, L"../Texture/StartButton.png");
	CTextureMgr::GetInst()->AddTexture(L"HowToPlayButton"
		, L"../Texture/howtoplay.png");

	//HP UI
	CTextureMgr::GetInst()->AddTexture(L"HP_1"
		, L"../Texture/HP_1.png");
	CTextureMgr::GetInst()->AddTexture(L"HP_2"
		, L"../Texture/HP_2.png");
	CTextureMgr::GetInst()->AddTexture(L"HP_3"
		, L"../Texture/HP_3.png");
	CTextureMgr::GetInst()->AddTexture(L"HP_4"
		, L"../Texture/HP_4.png");
}
