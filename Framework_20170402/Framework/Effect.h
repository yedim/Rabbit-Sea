#pragma once
#include "Obj.h"
class CEffect :
	public CObj
{
public:
	float FrameTimer; //재생할 시간
	int FrameCount; //총 몇장인지
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

