#include "Random.h"

Random::Random() 
{
	
}

Random::~Random()
{

}

int Random::RandomRangeInt(int _begin, int _end)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distrib(_begin, _end);
	int toReturn = distrib(gen);
	return toReturn;
}
