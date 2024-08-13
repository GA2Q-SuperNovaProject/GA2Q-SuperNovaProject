#pragma once
#include <windows.h>

//[TW] FixedRate
const float FPS = 60.0f;
const int MILLISECS_PER_FRAME = 1000 / FPS;
const float FIXED_FPS = 1.0f / FPS;

const int PIXELS_PER_METER = 50;

class TimeManager
{
public:
	//타임 매니저 싱글톤으로 생성
	static TimeManager& GetInstance()
	{
		static TimeManager inst;
		return inst;
	}

	void Initialize();
	void StartCheckTime();
	void EndCheckTime();
	float GetDeltaTime();

private:
	TimeManager();
	~TimeManager();

	float m_deltaTime;	// 델타 타임

	// 총 이동량 * 1/프레임수 = 한번씩 이동해야하는 량
	// FPS를 구하고
	// 1 프레임당 시간 을 구할 수 있으며 
	// DeltaTime을 구할 수 있다
	// DeltaTime은 타임매니저에서 계속 구해야한다
	LARGE_INTEGER	m_llCurCount;
	LARGE_INTEGER	m_llPrevCount;
	LARGE_INTEGER	m_llFrequency;
	double			m_dDT;		 // DeltaTime (0) 프레임 사이의 시간값
	double			m_dAcc;		 // (0) 1초 체크를 위한 누적 시간
	UINT			m_iCallCount;// (0) 함수 호출 횟수 체크
	UINT			m_iFPS;		 // 초당 호출 횟수 체크

	// 라지 인티저를 쓰는 이유-> 쿼리퍼포먼스 카운터나 쿼리퍼포먼스 프리퀀시 같은
	// 함수를 사용하기 위해서는 크기가 큰 정수형이 필요
	// 왜? 더 자세한 시간값을 저장하기 위해서
	// 부호가 있는 64비트 정수형 데이터를 저장하기 위해 선언된 사용자 정의 자료형


};

