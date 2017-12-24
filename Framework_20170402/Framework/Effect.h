#pragma once
#include "Obj.h"
class CEffect :
	public CObj
{
public:
	float FrameTimer; //����� �ð�
	int FrameCount; //�� ��������
	int CurrentIndex;
public:
	virtual void Initialize(void);
	virtual int Update(void);
	virtual void Render(void);
	virtual void Release(void);

public:
	CEffect();
	virtual ~CEffect();
};

