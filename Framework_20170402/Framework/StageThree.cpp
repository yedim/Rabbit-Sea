#include "stdafx.h"
#include "StageThree.h"
#include "ObjMgr.h"
#include "Player.h"
#include "Monster.h"
#include "BackGround.h"
#include "FollowMonster.h"
#include "Item.h"
#include "HP.h"
#include "BossMonster.h"
#include "AlphaEffect.h"
#include "LastBoss.h"

CStageThree::CStageThree()
{
}


CStageThree::~CStageThree()
{
}

void CStageThree::Initialize(void)
{
	// (총장수 - 1) * 800(화면 가로 사이즈)
	CObjMgr::GetInst()->ScrollMax = 800;

	CObjMgr::GetInst()->AddObject(new CAlphaEffect, OBJ_POST_UI);

	CObjMgr::GetInst()->AddObject(new CHP, OBJ_UI);
	CObjMgr::GetInst()->AddObject(new CPlayer, OBJ_PLAYER);

	CObjMgr::GetInst()->AddObject(new CLastBoss, OBJ_MONSTER);

	CObjMgr::GetInst()->AddBackGround(new CBackGround, OBJ_BACKGROUND
		, 400, L"BackGround");
	CObjMgr::GetInst()->AddBackGround(new CBackGround, OBJ_BACKGROUND
		, 1200, L"BackGround");
}

int CStageThree::Update(void)
{
	return 0;
}

void CStageThree::Render(void)
{
}
void CStageThree::Release(void)
{

}