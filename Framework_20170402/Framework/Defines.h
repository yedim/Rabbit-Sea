#pragma once
#include "StdAfx.h"

//���� ������ Framework.cpp �� ����Ǿ� �ִ�.
extern HWND g_hWnd;

using namespace std;

enum WINMODE
{
	WINMODE_FULL,
	WINMODE_WIN,
};

// ȭ�鿡 �׷����� ������� �����Ѵ�.
// ���� Ŭ���� ���߿� �׷�����.
enum OBJ_TYPE
{
	OBJ_BACKGROUND = 0,
	OBJ_PLAYER,
	OBJ_MONSTER,
	OBJ_BULLET,
	OBJ_MONSTER_BULLET,
	OBJ_ITEM,
	OBJ_EFFECT,
	OBJ_UI,
	OBJ_POST_UI,

	OBJ_MAX,
};

// ���� ���������� �����ϱ� ���� ����
enum STAGE_TYPE
{
	STAGE_ONE = 0,
	STAGE_TWO,
	STAGE_THREE,

	STAGE_END,
};

typedef struct tagTextureInfo
{
	LPDIRECT3DTEXTURE9			pTexture;
	D3DXIMAGE_INFO				TexInfo;
}TEXINFO;

#define PI 3.141592f

#define WIN_X 800
#define WIN_Y 600
