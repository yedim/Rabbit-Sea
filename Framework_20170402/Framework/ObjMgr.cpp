#include "stdafx.h"
#include "ObjMgr.h"

#include "Obj.h"
#include "Effect.h"
#include "Item.h"


CObjMgr::CObjMgr()
{
}

CObjMgr::~CObjMgr()
{
}
HRESULT CObjMgr::Initialize(void)
{
	ScrollX = 0;
	ChangeStage = false;
	Muzuk = false;

	return S_OK;
}
void CObjMgr::AddObject(CObj* Obj, OBJ_TYPE Type)
{
	Obj->Initialize();
	ObjList[Type].push_back(Obj);
}
void CObjMgr::AddObject(CObj* Obj, OBJ_TYPE Type, D3DXVECTOR3 Pos)
{
	Obj->Initialize();
	Obj->Pos = Pos;
	ObjList[Type].push_back(Obj);
}
void CObjMgr::AddObject(CObj* Obj, OBJ_TYPE Type, D3DXVECTOR3 Pos, D3DXVECTOR3 Dir)
{
	Obj->Initialize();
	Obj->Pos = Pos;
	Obj->Dir = Dir;
	ObjList[Type].push_back(Obj);
}
void CObjMgr::AddBackGround(CObj* Obj, OBJ_TYPE Type, float PosX, wstring Texturekey)
{
	Obj->Initialize();
	Obj->Pos.x = PosX;
	Obj->strTextureKey = Texturekey;
	ObjList[Type].push_back(Obj);
}

void CObjMgr::Update(void)
{
	//플레이어, 총알, 몬스터등을 움직일 함수
	for (int i = 0; i < OBJ_MAX; ++i)
	{
		for (list<CObj*>::iterator iter = ObjList[i].begin()
			; iter != ObjList[i].end(); )
		{
			int Result = (*iter)->Update();
			// 리턴 1을 받으면 삭제
			// 다른 값을 받아온경우에도 활용가능 하다.
			if (Result == 1)
			{
				delete (*iter);
				(*iter) = NULL;
				iter = ObjList[i].erase(iter);
			}
			else
				++iter;
		}
	}
}

void CObjMgr::Render(void)
{
	for (int i = 0; i < OBJ_MAX; ++i)
	{
		for (list<CObj*>::iterator iter = ObjList[i].begin(); iter != ObjList[i].end(); ++iter)
		{
			(*iter)->Render();
		}
	}
}
CObj* CObjMgr::GetObjToCollision(CObj* Obj, OBJ_TYPE Type)
{
	for (list<CObj*>::iterator iter = ObjList[Type].begin(); iter != ObjList[Type].end(); ++iter)
	{
		D3DXVECTOR3 DistanceVector = (*iter)->Pos - Obj->Pos;
		//D3DXVec3Length - 벡터의 길이를 반환하는 함수
		//위치 - 위치의 결과로 나온 방향벡터의 길이는 객체간의
		//거리이다.
		float Distance = D3DXVec3Length(&DistanceVector);

		//두 객체의 반지름의 합보다 거리가 작으면 충돌 된것이다.
		if (Distance < (*iter)->Radius + Obj->Radius)
		{
			//충돌한 객체
			return (*iter);
		}
	}

	//아무것도 안부딛혔으면 NULL
	return NULL;
}

int CObjMgr::CollisionSphere(CObj* Obj, OBJ_TYPE Type)
{
	//구충돌
	//필요한것들 - 위치, 반지름.
	//Obj->Pos 	//Obj->Radius

	for (list<CObj*>::iterator iter = ObjList[Type].begin(); iter != ObjList[Type].end(); ++iter)
	{
		D3DXVECTOR3 DistanceVector = (*iter)->Pos - Obj->Pos;

		float Distance = D3DXVec3Length(&DistanceVector);

		if (Distance < (*iter)->Radius + Obj->Radius)
		{
			/** Hard Coding */
			/** 게임 로직의 편의를 위해서 임시로 사용한 코드들이 많다. */
			if ((*iter)->strTextureKey == L"Player" 
				&& Muzuk == true)
			{
				return 0;
			}

			(*iter)->HP -= 1;
			//HP가 0보다 작을때만 삭제한다.
			if ((*iter)->HP <= 0)
			{
				if ((*iter)->strTextureKey == L"Player")
				{
					//플레이어 사망시에 메뉴 화면으로
					CObjMgr::GetInst()->CurrentStageKey = STAGE_ONE;
					CObjMgr::GetInst()->ChangeStage = true;
					CObjMgr::GetInst()->ScrollX = 0;
					return NULL;
				}

				if ((*iter)->strTextureKey == L"BossMonster") 
				{
					CurrentStageKey = STAGE_THREE;
					ChangeStage = true;
					ScrollX = 0;
					return 0;
				}
				// 랜덤으로 아이템 생성. % 2면 50% 확률
				/*int Rand = rand() % 2;
				if (Rand == 0)
				{
					AddObject(new CItem, OBJ_ITEM, (*iter)->Pos);
				}*/

				// 이미지 키값을 이용해서 생성하는 예시 코드 
				/*if ((*iter)->strTextureKey == L"보스몬스터")
				{
					AddObject(new CItem, OBJ_ITEM, (*iter)->Pos);
				}*/

				AddObject(new CEffect, OBJ_EFFECT, (*iter)->Pos);
				//충돌 했다.
				delete (*iter);
				(*iter) = NULL;
				ObjList[Type].erase(iter);
			}

			return 1;
		}
	}

	return 0;
}

CObj* CObjMgr::GetPlayer(void)
{
	//플레이어는 한마리 밖에 안들어있다.
	//비긴 하면 플레이어다.
	list<CObj*>::iterator iter = ObjList[OBJ_PLAYER].begin();

	//end가 아니면 들어있다. 그럼 플레이어.
	if (iter != ObjList[OBJ_PLAYER].end())
	{
		return (*iter);
	}

	return NULL;
}

void CObjMgr::Release(void)
{
	for (int i = 0; i < OBJ_MAX; ++i)
	{
		for (list<CObj*>::iterator iter = ObjList[i].begin(); iter != ObjList[i].end(); ++iter)
		{
			delete (*iter);
			(*iter) = NULL;
		}
		ObjList[i].clear();
	}
}