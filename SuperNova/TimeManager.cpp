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
	QueryPerformanceFrequency(&m_llFrequency);	// ���� ī������ �� �˻�
}

void TimeManager::StartCheckTime()
{
	QueryPerformanceCounter(&m_llPrevCount);	 // CPU�� ƽ �޾ƿ���
}

void TimeManager::EndCheckTime()
{
	QueryPerformanceCounter(&m_llCurCount);	// ���� Ŀ��Ʈ Ÿ�� �ޱ�

	m_dDT = (double)(m_llCurCount.QuadPart - m_llPrevCount.QuadPart) / (double)(m_llFrequency.QuadPart);

	m_llPrevCount = m_llCurCount;	// ���� ī��Ʈ ������Ʈ
	++m_iCallCount;
	m_dAcc += m_dDT;
	if (m_dAcc >= 1.0)	// ������� ���� ���� ��->��� ���̰� �����ð��� 1���̻� ������ �Ǹ� �ʱ�ȭ
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


