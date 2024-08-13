#pragma once
#include <chrono>
#include <time.h>

//그냥 항상 루프가 돌고 있다고 생각하자. 
//얘네들은 각각 N초마다 하나씩 증가한다.
class Timer
{
public:
	static Timer& GetInstance()
	{
		static Timer inst;
		return inst;
	}
	uint64_t counterFive = 0;
	uint64_t counterTen = 0;
	uint64_t counterOne = 0;
};


