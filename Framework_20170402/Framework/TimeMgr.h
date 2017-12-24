#pragma once

#include "Defines.h"
#include "Single.h"

class CTimeMgr
	: public CSingle<CTimeMgr>
{
private:
	LARGE_INTEGER		m_FrameTime;
	LARGE_INTEGER		m_FixTime;
	LARGE_INTEGER		m_LastTime;
	LARGE_INTEGER		m_CpuTick;

private: 
	float				m_fTime;

public:
	float GetTime(void) const {return m_fTime;}

public:
	void InitTimeMgr(void);
	void SetTimePerSec(void);

public:
	CTimeMgr(void);
public:
	~CTimeMgr(void);
};
