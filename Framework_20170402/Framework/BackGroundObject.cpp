#include "stdafx.h"
#include "BackGroundObject.h"
#include "TextureMgr.h"
#include "DeviceMgr.h"
#include "TimeMgr.h"
#include "ObjMgr.h"

CBackGroundObject::CBackGroundObject()
{
}


CBackGroundObject::~CBackGroundObject()
{
}

void CBackGroundObject::Initialize(void)
{
	Pos = D3DXVECTOR3(400, 30, 0);

	strTextureKey = L"BackObj";

	Angle = 0;
}

int CBackGroundObject::Update(void)
{
	D3DXMatrixIdentity(&matWorld);
	matWorld._41 = Pos.x - CObjMgr::GetInst()->ScrollX * 0.75f;
	matWorld._42 = Pos.y;

	return 0;
}

void CBackGroundObject::Render(void)
{
	//이미지를 가져온다.
	TEXINFO*	pTexInfo = CTextureMgr::GetInst()->GetTextureInfo(strTextureKey);

	D3DXVECTOR3 vCenter = D3DXVECTOR3(pTexInfo->TexInfo.Width / 2.f
		, pTexInfo->TexInfo.Height / 2.f, 0.f);

	CDeviceMgr::GetInst()->GetSprite()->SetTransform(&matWorld);

	CDeviceMgr::GetInst()->GetSprite()->Draw(pTexInfo->pTexture
		, NULL, &vCenter, NULL, D3DCOLOR_ARGB(255, 255, 255, 255));

}
void CBackGroundObject::Release(void)
{

}
