#include "EnemyGroupInfo.h"

EnemyGroupInfo::EnemyGroupInfo(int idx, int mc, int r, int c, int s, int * l)
{
	m_groupIdx = idx;
	m_maxEnemyCount = mc;
	m_rows = r;
	m_cols = c;
	m_space = s;
	layout = l;
}

EnemyGroupInfo::~EnemyGroupInfo()
{
	delete[] layout;
}

int EnemyGroupInfo::getGroupIdx()
{
	return m_groupIdx;
}

int EnemyGroupInfo::getMaxEnemyCount()
{
	return m_maxEnemyCount;
}

int EnemyGroupInfo::getRows()
{
	return m_rows;
}

int EnemyGroupInfo::getCols()
{
	return m_cols;
}

int EnemyGroupInfo::getSpace()
{
	return m_space;
}

const int * EnemyGroupInfo::getLayout()
{
	return layout;
}
