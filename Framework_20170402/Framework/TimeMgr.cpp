#include "StdAfx.h"
#include "TimeMgr.h"

CTimeMgr::CTimeMgr(void)
: m_fTime(0.f)
{
}

CTimeMgr::~CTimeMgr(void)
{
}

void CTimeMgr::InitTimeMgr(void)
{
	// ���� cpu�� ī�����ϰ� �ִ� ���� ��������
	QueryPerformanceCounter(&m_FrameTime);
	QueryPerformanceCounter(&m_FixTime);
	QueryPerformanceCounter(&m_LastTime);

	// cpu�� 1�ʿ� ī�����Ҽ� �ִ� ����. ������.
	QueryPerformanceFrequency(&m_CpuTick);
}

void CTimeMgr::SetTimePerSec(void)
{
	QueryPerformanceCounter(&m_FrameTime);

	if(m_FrameTime.QuadPart - m_FixTime.QuadPart > m_CpuTick.QuadPart)
	{
		QueryPerformanceFrequency(&m_CpuTick);
		m_FixTime = m_FrameTime;
	}

	m_fTime = (m_FrameTime.QuadPart - m_LastTime.QuadPart) / float(m_CpuTick.QuadPart);

	m_LastTime = m_FrameTime;	
}