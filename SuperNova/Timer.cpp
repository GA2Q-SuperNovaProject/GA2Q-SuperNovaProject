#include "Timer.h"
using namespace std::chrono;

////�� �ѹ��� �ߵ� ����. �Ƹ� ����ź�� ���� ��?
//bool Timer::WaitForSecondsOnce(int time)
//{
//	static uint64_t startPoint = duration_cast<seconds>(system_clock::now().time_since_epoch()).count();
//	static uint64_t endPoint = startPoint + time;
//	
//	long long nowTime = duration_cast<seconds>(system_clock::now().time_since_epoch()).count();
//	if (nowTime >= endPoint)
//	{
//		return true;
//	}
//	else
//	{
//		return false;
//	}
//}
// uint64_t Timer::counterOne = 0;
// uint64_t Timer::counterFive = 0;
// uint64_t Timer::counterTen = 0;
