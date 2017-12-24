#include "stdafx.h"
#include "Player.h"
#include "TextureMgr.h"
#include "DeviceMgr.h"
#include "TimeMgr.h"
#include "ObjMgr.h"
#include "Bullet.h"
#include "Mouse.h"

CPlayer::CPlayer()
{
}


CPlayer::~CPlayer()
{
}

void CPlayer::Initialize(void)
{
	Pos = D3DXVECTOR3(100, 200, 0);
	strTextureKey = L"Player";

	Angle = 0;
	PressKey = false;
	BulletTimer = 0;
	UnbeatableTime = 3;
	Radius = 60;

	PlayerUpgrade = 1;
	HP = 4;
}

int CPlayer::Update(void)
{
	KeyCheck();
	CollisionCheck();

	ComputeMatrix();
	return 0;
}
void CPlayer::CollisionCheck(void)
{
	float DeltaTime = CTimeMgr::GetInst()->GetTime();

	UnbeatableTime += DeltaTime;

	CObj* Monster = CObjMgr::GetInst()->GetObjToCollision(this, OBJ_MONSTER);

	if (Monster != NULL && UnbeatableTime > 3.f)
	{
		UnbeatableTime = 0;

		if (CObjMgr::GetInst()->Muzuk == true)
			return;

		--HP;
		if (HP <= 0)
		{
			//사망
			CObjMgr::GetInst()->CurrentStageKey = STAGE_ONE;
			CObjMgr::GetInst()->ChangeStage = true;
			CObjMgr::GetInst()->ScrollX = 0;
		}
	}
}
void CPlayer::KeyCheck(void)
{
	float DeltaTime = CTimeMgr::GetInst()->GetTime();

	if (GetAsyncKeyState(VK_RIGHT))
	{
		//여기서 2000은 (화면 갯수 - 1) * 화면 사이즈(혹은 이미지 사이즈) + 화면 반사이즈
		if (Pos.x < CObjMgr::GetInst()->ScrollMax + 400)
			Pos.x += DeltaTime * 200;

		//여기서 1600은 (화면 갯수 - 1) * 화면 사이즈(혹은 이미지 사이즈) 
		if (CObjMgr::GetInst()->ScrollX < CObjMgr::GetInst()->ScrollMax)
		{
			if (Pos.x > 150)
				CObjMgr::GetInst()->ScrollX += DeltaTime * 200;

			//플레이어 움직임에 따라 스크롤 좌표를 이동시킨다.
		}
	}

	if (GetAsyncKeyState(VK_LEFT))
	{
		if (Pos.x > 0)
			Pos.x = Pos.x - DeltaTime * 200;

		if (CObjMgr::GetInst()->ScrollX > 0)
		{
			//보스등장시에도 못움직이게 동시 조건을 걸어야 한다.
			if (Pos.x < CObjMgr::GetInst()->ScrollMax + 100)
			{
				CObjMgr::GetInst()->ScrollX -= DeltaTime * 200;
			}
		}
	}
	if (GetAsyncKeyState(VK_UP))
	{
		Pos.y = Pos.y - DeltaTime * 200;
	}
	if (GetAsyncKeyState(VK_DOWN))
	{
		Pos.y = Pos.y + DeltaTime * 200;
	}

	if (GetAsyncKeyState(VK_SPACE))
	{
		if (PressKey == true)
		{
			//계속 누르고 있을때
			BulletTimer += DeltaTime;
			if (BulletTimer >= 0.2f)
			{
				PressKey = false;
			}
			return;
		}
		//처음 눌렸을때
		PressKey = true;
		BulletTimer = 0;

		CObjMgr::GetInst()->AddObject(new CBullet, OBJ_BULLET, Pos);

		if (PlayerUpgrade <= 1)
			return;

		D3DXVECTOR3 Pos2 = Pos;
		Pos2.y -= 35;
		Pos2.x -= 20;

		D3DXVECTOR3 Dir1 = D3DXVECTOR3(1,-0.5f,0);
		CObjMgr::GetInst()->AddObject(new CBullet, OBJ_BULLET, Pos2, Dir1);

		D3DXVECTOR3 Pos3 = Pos;
		Pos3.y += 35;
		Pos3.x -= 20;
		D3DXVECTOR3 Dir2 = D3DXVECTOR3(1, 0.5f, 0);
		CObjMgr::GetInst()->AddObject(new CBullet, OBJ_BULLET, Pos3, Dir2);
	}
	else
	{
		BulletTimer = 0;
		if (PressKey == true)
		{
			//방금 버튼을 땟다
		}

		PressKey = false;
	}
}
void CPlayer::Render(void)
{
	//이미지를 가져온다.
	TEXINFO*	pTexInfo = CTextureMgr::GetInst()->GetTextureInfo(strTextureKey);

	D3DXVECTOR3 vCenter = D3DXVECTOR3(pTexInfo->TexInfo.Width / 2.f
		, pTexInfo->TexInfo.Height / 2.f, 0.f);

	CDeviceMgr::GetInst()->GetSprite()->SetTransform(&matWorld);

	//D3DCOLOR_ARGB(255, 255, 255, 255) 여기에서 첫번째 255가 알파값
	//알파값은 0~255까지 범위를 가지며 0이면 화면에 안보임.
	if (UnbeatableTime > 3.0f)
	{
		CDeviceMgr::GetInst()->GetSprite()->Draw(pTexInfo->pTexture
			, NULL, &vCenter, NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
	}
	else
	{
		CDeviceMgr::GetInst()->GetSprite()->Draw(pTexInfo->pTexture
			, NULL, &vCenter, NULL, D3DCOLOR_ARGB(100, 255, 255, 255));
	}
	

}
void CPlayer::Release(void)
{

}
