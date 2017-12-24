#pragma once
#include "Obj.h"
class CPlayer :
	public CObj
{
public:
	//Ű�� �������� �������� ���� �����ϱ� ���� ����.
	float BulletTimer;
	bool PressKey;

	//�÷��̾� ���� ��ȭ �ܰ� 2�ܰ谡 3��
	int	 PlayerUpgrade;

	//���� �ð�üũ�� ���� ����
	float UnbeatableTime; 

public:
	virtual void Initialize(void);
	virtual int Update(void);
	virtual void Render(void);
	virtual void Release(void);

public:
	void CollisionCheck();
	void KeyCheck();

public:
	CPlayer();
	virtual ~CPlayer();
};

