#pragma once
#include "Obj.h"
class CHowToButton :
	public CObj
{
public:
	int Width;
	int Height;
public:
	virtual void Initialize(void);
	virtual int Update(void);
	virtual void Render(void);
	virtual void Release(void);

public:
	CHowToButton();
	virtual ~CHowToButton();
};

