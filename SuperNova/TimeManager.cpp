#include "TimeManager.h"
#include "Debug.h"

TimeManager::TimeManager()
{
}

TimeManager::~TimeManager()
{

}

void TimeManager::Initialize()
{
	QueryPerformanceFrequency(&m_llFrequency);	// 성능 카운터의 빈도 검색
}

void TimeManager::StartCheckTime()
{
	QueryPerformanceCounter(&m_llPrevCount);	 // CPU의 틱 받아오기
}

void TimeManager::EndCheckTime()
{
	QueryPerformanceCounter(&m_llCurCount);	// 현재 커런트 타임 받기

	m_dDT = (double)(m_llCurCount.QuadPart - m_llPrevCount.QuadPart) / (double)(m_llFrequency.QuadPart);

	m_llPrevCount = m_llCurCount;	// 예전 카운트 업데이트
	++m_iCallCount;
	m_dAcc += m_dDT;
	if (m_dAcc >= 1.0)	// 디버깅을 위해 멈출 시->계속 쌓이게 누적시간이 1초이상 모으게 되면 초기화
	{
		m_iFPS = m_iCallCount;
		m_dAcc = 0.0;
		m_iCallCount = 0;
	}
	
	m_deltaTime = m_dDT * 1000;
	//Debug::Trace("FPS", (float)m_deltaTime);
}

float TimeManager::GetDeltaTime()
{

	return m_deltaTime;
}


