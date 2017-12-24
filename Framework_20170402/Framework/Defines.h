#pragma once
#include "StdAfx.h"

//본래 변수는 Framework.cpp 에 선언되어 있다.
extern HWND g_hWnd;

using namespace std;

enum WINMODE
{
	WINMODE_FULL,
	WINMODE_WIN,
};

// 화면에 그려지는 순서대로 선언한다.
// 값이 클수록 나중에 그려진다.
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

// 현재 스테이지를 저장하기 위한 변수
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
