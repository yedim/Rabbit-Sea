#pragma once

#include "Defines.h"

class CObj
{
public:
	//�̹��� ����� ���� �ؽ��� Ű��
	wstring		strTextureKey;

	//��ġ�� ������ ����. z���� ���� �ʴ´�.
	D3DXVECTOR3	Pos;

	//���⺤�� ex) �Ѿ��� ������ ������� �����ϱ����� ����
	D3DXVECTOR3	Dir;

	//�ٶ󺸴� ���� �����Ұ���
	float		Angle;
	//�浹 üũ�� ���� ������
	float		Radius;

	//���� ���! ũ��,ȸ��, ��ġ������ �ᱹ �� ��� �ϳ��� ����.
	D3DXMATRIX	matWorld;

	//ü��
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

