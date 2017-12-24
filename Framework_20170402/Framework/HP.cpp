#include "stdafx.h"
#include "HP.h"
#include "TextureMgr.h"
#include "DeviceMgr.h"
#include "TimeMgr.h"
#include "ObjMgr.h"
#include "Player.h"

CHP::CHP()
{
}


CHP::~CHP()
{
}
void CHP::Initialize(void)
{
	Pos = D3DXVECTOR3(400, 40, 0);
	Angle = 0;
	Radius = 40;
	strTextureKey = L"HP_4";

	HP = 4;
	Dir = D3DXVECTOR3(0, 0, 0);
}

int CHP::Update(void)
{
	CObj* Player = CObjMgr::GetInst()->GetPlayer();

	if (Player == NULL)
		return 0;

	if (Player->HP == 4)
	{
		strTextureKey = L"HP_4";
	}
	if (Player->HP == 3)
	{
		strTextureKey = L"HP_3";
	}
	if (Player->HP == 2)
	{
		strTextureKey = L"HP_2";
	}
	if (Player->HP == 1)
	{
		strTextureKey = L"HP_1";
	}

	//UI의 경우에는 스크롤 값이 필요 없다. 딱 위치만 지정해준다.
	D3DXMatrixIdentity(&matWorld); // 단위행렬로 초기화
	matWorld._41 = Pos.x;
	matWorld._42 = Pos.y;

	return 0;
}

void CHP::Render(void)
{
	//이미지를 가져온다.
	TEXINFO*	pTexInfo = CTextureMgr::GetInst()->GetTextureInfo(strTextureKey);

	D3DXVECTOR3 vCenter = D3DXVECTOR3(pTexInfo->TexInfo.Width / 2.f
		, pTexInfo->TexInfo.Height / 2.f, 0.f);

	CDeviceMgr::GetInst()->GetSprite()->SetTransform(&matWorld);

	CDeviceMgr::GetInst()->GetSprite()->Draw(pTexInfo->pTexture
		, NULL, &vCenter, NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
}
void CHP::Release(void)
{

}