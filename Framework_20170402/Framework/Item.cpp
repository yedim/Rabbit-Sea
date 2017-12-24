#include "stdafx.h"
#include "Item.h"
#include "TextureMgr.h"
#include "DeviceMgr.h"
#include "TimeMgr.h"
#include "ObjMgr.h"
#include "Player.h"

CItem::CItem()
{
}


CItem::~CItem()
{
}
void CItem::Initialize(void)
{
	Pos = D3DXVECTOR3(1000, 300, 0);
	Angle = 0;
	Radius = 20;
	strTextureKey = L"Item";

	HP = 1;
	Dir = D3DXVECTOR3(0, 0, 0);
}

int CItem::Update(void)
{
	float DeltaTime = CTimeMgr::GetInst()->GetTime();

	CObj* Player = CObjMgr::GetInst()->GetPlayer();

	if (Player == NULL)
		return 0;

	//충돌체크
	D3DXVECTOR3 DistanceVector = Player->Pos - Pos;
	float Distance = D3DXVec3Length(&DistanceVector);

	if (Distance < Radius + Player->Radius)
	{
		//강제 다운 캐스팅
		((CPlayer*)Player)->PlayerUpgrade = 2;
		return 1;
	}

	ComputeMatrix();
	return 0;
}

void CItem::Render(void)
{
	//이미지를 가져온다.
	TEXINFO*	pTexInfo = CTextureMgr::GetInst()->GetTextureInfo(strTextureKey);

	D3DXVECTOR3 vCenter = D3DXVECTOR3(pTexInfo->TexInfo.Width / 2.f
		, pTexInfo->TexInfo.Height / 2.f, 0.f);

	CDeviceMgr::GetInst()->GetSprite()->SetTransform(&matWorld);

	CDeviceMgr::GetInst()->GetSprite()->Draw(pTexInfo->pTexture
		, NULL, &vCenter, NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
}
void CItem::Release(void)
{

}