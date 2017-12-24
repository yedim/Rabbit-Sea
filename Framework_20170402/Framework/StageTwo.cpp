#include "stdafx.h"
#include "StageTwo.h"
#include "ObjMgr.h"
#include "Player.h"
#include "Monster.h"
#include "BackGround.h"
#include "FollowMonster.h"
#include "Item.h"
#include "HP.h"
#include "BossMonster.h"
#include "MonsterBullet.h"
#include "BackGroundObject.h"


CStageTwo::CStageTwo()
{
}
CStageTwo::~CStageTwo()
{
}

void CStageTwo::Initialize(void)
{
	CObjMgr::GetInst()->ScrollMax = 1600;


	CObjMgr::GetInst()->AddObject(new CBackGroundObject, OBJ_UI);


	CObjMgr::GetInst()->AddObject(new CHP, OBJ_UI);

	CObjMgr::GetInst()->AddObject(new CItem, OBJ_ITEM
		, D3DXVECTOR3(1000, 300, 0));

	CObjMgr::GetInst()->AddObject(new CPlayer, OBJ_PLAYER);

	//CObjMgr::GetInst()->AddObject(new CMonster, OBJ_MONSTER);

	CObjMgr::GetInst()->AddObject(new CMonster, OBJ_MONSTER
		, D3DXVECTOR3(500, 200, 0), D3DXVECTOR3(2.0f, 0, 0));

	/*CObjMgr::GetInst()->AddObject(new CMonster, OBJ_MONSTER
		, D3DXVECTOR3(550, 250, 0), D3DXVECTOR3(2.0f, 0, 0));*/

	CObjMgr::GetInst()->AddObject(new CMonster, OBJ_MONSTER
		, D3DXVECTOR3(600, 300, 0), D3DXVECTOR3(2.0f, 0, 0));


	CObjMgr::GetInst()->AddObject(new CMonster, OBJ_MONSTER
		, D3DXVECTOR3(1200, 200, 0), D3DXVECTOR3(2.0f, 0, 0));

	CObjMgr::GetInst()->AddObject(new CMonster, OBJ_MONSTER
		, D3DXVECTOR3(1550, 450, 0), D3DXVECTOR3(2.0f, 0, 0));

	CObjMgr::GetInst()->AddObject(new CMonster, OBJ_MONSTER
		, D3DXVECTOR3(1300, 400, 0), D3DXVECTOR3(2.0f, 0, 0));

	CObjMgr::GetInst()->AddObject(new CBossMonster, OBJ_MONSTER
		, D3DXVECTOR3(2200, 200, 0));

	/*CObjMgr::GetInst()->AddObject(new CFollowMonster, OBJ_MONSTER
		, D3DXVECTOR3(300, 500, 0));*/

	CObjMgr::GetInst()->AddBackGround(new CBackGround, OBJ_BACKGROUND
		, 400, L"BackGround");
	CObjMgr::GetInst()->AddBackGround(new CBackGround, OBJ_BACKGROUND
		, 1200, L"BackGround");
	CObjMgr::GetInst()->AddBackGround(new CBackGround, OBJ_BACKGROUND
		, 2000, L"BackGround");

	/*
	CObjMgr::GetInst()->AddBackGround(new CBackGround, OBJ_BACKGROUND
	, 2800, L"BackGround_1");
	CObjMgr::GetInst()->AddBackGround(new CBackGround, OBJ_BACKGROUND
	, 3600, L"BackGround_2");*/

}

int CStageTwo::Update(void)
{


	return 0;
}

void CStageTwo::Render(void)
{
}
void CStageTwo::Release(void)
{

}