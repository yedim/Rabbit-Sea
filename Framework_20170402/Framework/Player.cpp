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
			//���
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
		//���⼭ 2000�� (ȭ�� ���� - 1) * ȭ�� ������(Ȥ�� �̹��� ������) + ȭ�� �ݻ�����
		if (Pos.x < CObjMgr::GetInst()->ScrollMax + 400)
			Pos.x += DeltaTime * 200;

		//���⼭ 1600�� (ȭ�� ���� - 1) * ȭ�� ������(Ȥ�� �̹��� ������) 
		if (CObjMgr::GetInst()->ScrollX < CObjMgr::GetInst()->ScrollMax)
		{
			if (Pos.x > 150)
				CObjMgr::GetInst()->ScrollX += DeltaTime * 200;

			//�÷��̾� �����ӿ� ���� ��ũ�� ��ǥ�� �̵���Ų��.
		}
	}

	if (GetAsyncKeyState(VK_LEFT))
	{
		if (Pos.x > 0)
			Pos.x = Pos.x - DeltaTime * 200;

		if (CObjMgr::GetInst()->ScrollX > 0)
		{
			//��������ÿ��� �������̰� ���� ������ �ɾ�� �Ѵ�.
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
			//��� ������ ������
			BulletTimer += DeltaTime;
			if (BulletTimer >= 0.2f)
			{
				PressKey = false;
			}
			return;
		}
		//ó�� ��������
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
			//��� ��ư�� ����
		}

		PressKey = false;
	}
}
void CPlayer::Render(void)
{
	//�̹����� �����´�.
	TEXINFO*	pTexInfo = CTextureMgr::GetInst()->GetTextureInfo(strTextureKey);

	D3DXVECTOR3 vCenter = D3DXVECTOR3(pTexInfo->TexInfo.Width / 2.f
		, pTexInfo->TexInfo.Height / 2.f, 0.f);

	CDeviceMgr::GetInst()->GetSprite()->SetTransform(&matWorld);

	//D3DCOLOR_ARGB(255, 255, 255, 255) ���⿡�� ù��° 255�� ���İ�
	//���İ��� 0~255���� ������ ������ 0�̸� ȭ�鿡 �Ⱥ���.
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
