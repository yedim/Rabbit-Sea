#pragma once
#include "Obj.h"
class CAlphaEffect :
	public CObj
{
public:
	float FrameTimer; //재생할 시간
	float DrawAlpha;

public:
	virtual void Initialize(void);
	virtual int Update(void);
	virtual void Render(void);
	virtual void Release(void);
public:
	CAlphaEffect();
	virtual ~CAlphaEffect();
};

