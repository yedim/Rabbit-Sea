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
	//�÷��̾�, �Ѿ�, ���͵��� ������ �Լ�
	for (int i = 0; i < OBJ_MAX; ++i)
	{
		for (list<CObj*>::iterator iter = ObjList[i].begin()
			; iter != ObjList[i].end(); )
		{
			int Result = (*iter)->Update();
			// ���� 1�� ������ ����
			// �ٸ� ���� �޾ƿ°�쿡�� Ȱ�밡�� �ϴ�.
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
		//D3DXVec3Length - ������ ���̸� ��ȯ�ϴ� �Լ�
		//��ġ - ��ġ�� ����� ���� ���⺤���� ���̴� ��ü����
		//�Ÿ��̴�.
		float Distance = D3DXVec3Length(&DistanceVector);

		//�� ��ü�� �������� �պ��� �Ÿ��� ������ �浹 �Ȱ��̴�.
		if (Distance < (*iter)->Radius + Obj->Radius)
		{
			//�浹�� ��ü
			return (*iter);
		}
	}

	//�ƹ��͵� �Ⱥε������� NULL
	return NULL;
}

int CObjMgr::CollisionSphere(CObj* Obj, OBJ_TYPE Type)
{
	//���浹
	//�ʿ��Ѱ͵� - ��ġ, ������.
	//Obj->Pos 	//Obj->Radius

	for (list<CObj*>::iterator iter = ObjList[Type].begin(); iter != ObjList[Type].end(); ++iter)
	{
		D3DXVECTOR3 DistanceVector = (*iter)->Pos - Obj->Pos;

		float Distance = D3DXVec3Length(&DistanceVector);

		if (Distance < (*iter)->Radius + Obj->Radius)
		{
			/** Hard Coding */
			/** ���� ������ ���Ǹ� ���ؼ� �ӽ÷� ����� �ڵ���� ����. */
			if ((*iter)->strTextureKey == L"Player" 
				&& Muzuk == true)
			{
				return 0;
			}

			(*iter)->HP -= 1;
			//HP�� 0���� �������� �����Ѵ�.
			if ((*iter)->HP <= 0)
			{
				if ((*iter)->strTextureKey == L"Player")
				{
					//�÷��̾� ����ÿ� �޴� ȭ������
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
				// �������� ������ ����. % 2�� 50% Ȯ��
				/*int Rand = rand() % 2;
				if (Rand == 0)
				{
					AddObject(new CItem, OBJ_ITEM, (*iter)->Pos);
				}*/

				// �̹��� Ű���� �̿��ؼ� �����ϴ� ���� �ڵ� 
				/*if ((*iter)->strTextureKey == L"��������")
				{
					AddObject(new CItem, OBJ_ITEM, (*iter)->Pos);
				}*/

				AddObject(new CEffect, OBJ_EFFECT, (*iter)->Pos);
				//�浹 �ߴ�.
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
	//�÷��̾�� �Ѹ��� �ۿ� �ȵ���ִ�.
	//��� �ϸ� �÷��̾��.
	list<CObj*>::iterator iter = ObjList[OBJ_PLAYER].begin();

	//end�� �ƴϸ� ����ִ�. �׷� �÷��̾�.
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