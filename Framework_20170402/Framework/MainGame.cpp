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

	// �̹��� �ε�
	ReadTexture();

	//Ÿ�̸Ӹ� �������ּ���
	CTimeMgr::GetInst()->InitTimeMgr();
	CObjMgr::GetInst()->Initialize();

	CObjMgr::GetInst()->CurrentStageKey = STAGE_ONE;
	m_CurrentStage = new CStageOne;
	m_CurrentStage->Initialize();

	return S_OK;
}
void CMainGame::CheckCheatKey(void)
{
	// �������� ��ȯ ġƮŰ - �޴�
	if (GetAsyncKeyState(VK_F1))
	{
		CObjMgr::GetInst()->CurrentStageKey = STAGE_ONE;
		CObjMgr::GetInst()->ChangeStage = true;
	}
	// �������� ��ȯ ġƮŰ - 1��������
	if (GetAsyncKeyState(VK_F2))
	{
		CObjMgr::GetInst()->CurrentStageKey = STAGE_TWO;
		CObjMgr::GetInst()->ChangeStage = true;
	}
	// �������� ��ȯ ġƮŰ - 2��������
	if (GetAsyncKeyState(VK_F3))
	{
		CObjMgr::GetInst()->CurrentStageKey = STAGE_THREE;
		CObjMgr::GetInst()->ChangeStage = true;
	}
	//���� ���׷��̵�
	if (GetAsyncKeyState(VK_F4))
	{
		CObj* Player = CObjMgr::GetInst()->GetPlayer();
		if (Player != NULL)
		{
			((CPlayer*)Player)->PlayerUpgrade = 2;
		}
	}
	// �������
	if (GetAsyncKeyState(VK_F5))
	{
		CObjMgr::GetInst()->Muzuk = true;
	}
}
void CMainGame::Update(void)
{
	CheckCheatKey();

	//���콺 ��ǥ�� ����
	CMouse::SetMousePos();

	//Ÿ�̸��� ���� ���Ž��� �ּ���
	CTimeMgr::GetInst()->SetTimePerSec();

	//�Ŵ��� Ŭ�����ȿ� ����ִ� ��ü���� ���Ž�Ų��.
	CObjMgr::GetInst()->Update();

	//�ش� �������� ���� ������ �ʿ��� ��쿡 ����Ѵ�.
	m_CurrentStage->Update();


	//�������� ��ȯ �ڵ�
	if (CObjMgr::GetInst()->ChangeStage == true)
	{
		//�������� ��ȯ������ �� �ٽ� false�� �ٲ��ش�.
		CObjMgr::GetInst()->ChangeStage = false;
		//�� ���������� �ִ� ��ü���� �� �����.
		CObjMgr::GetInst()->Release();

		//�������� ��ü�� �ٽ� �Ҵ��Ѵ�.
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

		//���������� �ʱ�ȭ == �ش� ���������� ������Ʈ���� �߰��Ѵ�.
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

	// ����
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

	// ���
	CTextureMgr::GetInst()->AddTexture(L"Title"
		, L"../Texture/Title.png");

	CTextureMgr::GetInst()->AddTexture(L"BackGround"
		, L"../Texture/BackGround.png");

	CTextureMgr::GetInst()->AddTexture(L"BackObj"
		, L"../Texture/BackObj.png");

	CTextureMgr::GetInst()->AddTexture(L"NextStage"
		, L"../Texture/NextStage.png");

	// �Ѿ�
	CTextureMgr::GetInst()->AddTexture(L"Bullet"
		, L"../Texture/Bullet.png");
	CTextureMgr::GetInst()->AddTexture(L"MonsterBullet"
		, L"../Texture/MonsterBullet.png");

	// ��� ���� ����Ʈ
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
