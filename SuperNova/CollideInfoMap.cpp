#include "CollideInfoMap.h"
#include <algorithm>

void CollideInfoMap::AddWidthHeightToMap(int imageIndex, float width, float height)
{
	FLOATPAIR floatPair = FLOATPAIR(width, height);
	m_InfoMap.insert(std::pair<int, FLOATPAIR>(imageIndex, floatPair));
}

float CollideInfoMap::GetWidthByImageIndex(int imageIndex)
{
	auto tmpGoal = m_InfoMap.find(imageIndex);
	if (tmpGoal != m_InfoMap.end())
	{
		return tmpGoal->second.first; // Width를 변환!
	}
	else
	{
		return -1;
	}
}

float CollideInfoMap::GetHeightByImageIndex(int imageIndex)
{
	auto tmpGoal = m_InfoMap.find(imageIndex);
	if (tmpGoal != m_InfoMap.end())
	{
		return tmpGoal->second.second; // Width를 변환!
	}
	else
	{
		return -1;
	}
}

void CollideInfoMap::SetWidthByImageIndex(int imageIndex, float widthValue)
{
	FLOATPAIR tmpPair = m_InfoMap.at(imageIndex);
	m_InfoMap.at(imageIndex) = FLOATPAIR(widthValue, tmpPair.second);
}

void CollideInfoMap::SetHeightByImageIndex(int imageIndex, float heightValue)
{
	FLOATPAIR tmpPair = m_InfoMap.at(imageIndex);
	m_InfoMap.at(imageIndex) = FLOATPAIR(tmpPair.first, heightValue);
}

void CollideInfoMap::AddWidthHeightToGIFMap(int imageIndex, float width, float height)
{
	FLOATPAIR floatPair = FLOATPAIR(width, height);
	m_GIFMap.insert(std::pair<int, FLOATPAIR>(imageIndex, floatPair));
}

void CollideInfoMap::SetWidthByGIFIndex(int imageIndex, float widthValue)
{
	FLOATPAIR tmpPair = m_GIFMap.at(imageIndex);
	m_GIFMap.at(imageIndex) = FLOATPAIR(widthValue, tmpPair.second);
}

void CollideInfoMap::SetHeightByGIFIndex(int imageIndex, float heightValue)
{
	FLOATPAIR tmpPair = m_GIFMap.at(imageIndex);
	m_GIFMap.at(imageIndex) = FLOATPAIR(tmpPair.first, heightValue);
}

float CollideInfoMap::GetWidthByGIFIndex(int imageIndex)
{
	auto tmpGoal = m_GIFMap.find(imageIndex);
	if (tmpGoal != m_GIFMap.end())
	{
		return tmpGoal->second.first; // Width를 변환!
	}
	else
	{
		return -1;
	}
}

float CollideInfoMap::GetHeightByGIFIndex(int imageIndex)
{
	auto tmpGoal = m_GIFMap.find(imageIndex);
	if (tmpGoal != m_GIFMap.end())
	{
		return tmpGoal->second.second; // Width를 변환!
	}
	else
	{
		return -1;
	}
}
