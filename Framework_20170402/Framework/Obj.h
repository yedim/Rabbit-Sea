#pragma once

#include "Defines.h"

class CObj
{
public:
	//이미지 출력을 위한 텍스쳐 키값
	wstring		strTextureKey;

	//위치를 저장할 변수. z값은 쓰지 않는다.
	D3DXVECTOR3	Pos;

	//방향벡터 ex) 총알이 나가는 방향등을 저장하기위한 변수
	D3DXVECTOR3	Dir;

	//바라보는 각도 저장할것임
	float		Angle;
	//충돌 체크를 위한 반지름
	float		Radius;

	//월드 행렬! 크기,회전, 위치정보가 결국 이 행렬 하나에 담긴다.
	D3DXMATRIX	matWorld;

	//체력
	int HP;
public:
	virtual void Initialize(void);
	virtual int Update(void);
	virtual void Render(void);
	virtual void Release(void);
public:
	void ComputeMatrix();
public:
	CObj();
	virtual ~CObj();
};

