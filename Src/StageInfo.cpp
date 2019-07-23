#include "StageInfo.h"

StageInfo::StageInfo(int s, int ec, float est, int minl, int maxl, bool ib)
{
	m_Stage = s;
	m_EnemyCount = ec;
	m_EnemySpawnTime = est;
	m_EnemyMinLevel = minl;
	m_EnemyMaxLevel = maxl;
	m_isBoss = ib;
}

StageInfo::~StageInfo()
{
}

int StageInfo::getStageNumber()
{
	return m_Stage;
}

int StageInfo::getEnemyCount()
{
	return m_EnemyCount;
}

float StageInfo::getEnemySpawnTime()
{
	return m_EnemySpawnTime;
}

int StageInfo::getEnemyMinLevel()
{
	return m_EnemyMinLevel;
}

int StageInfo::getENemyMaxLevel()
{
	return m_EnemyMaxLevel;
}

bool StageInfo::isBoss()
{
	return m_isBoss;
}
