#pragma once
#include "Stage.h"
class CStageOne :
	public CStage
{
public:
	virtual void Initialize(void);
	virtual int Update(void);
	virtual void Render(void);
	virtual void Release(void);

public:
	CStageOne();
	virtual ~CStageOne();
};

