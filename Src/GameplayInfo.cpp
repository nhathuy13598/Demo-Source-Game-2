#include "GameplayInfo.h"

GameplayInfo::GameplayInfo(StageInfo * stgInfo)
{
	setStageInfo(stgInfo);
}

GameplayInfo::~GameplayInfo()
{
}

void GameplayInfo::setStageInfo(StageInfo * stgInfo)
{
	m_enemyCountRemain = stgInfo->getEnemyCount();
	m_enemySpawnDelay = stgInfo->getEnemySpawnTime();
}

float GameplayInfo::getEnemySpawnDelay()
{
	return m_enemySpawnDelay;
}

void GameplayInfo::decreaseEnemySpawnDelayBy(float f)
{
	m_enemySpawnDelay -= f;
}

void GameplayInfo::setEnemySpawnDelay(float esd)
{
	m_enemySpawnDelay = esd;
}

int GameplayInfo::getEnemyCountRemain()
{
	return m_enemyCountRemain;
}

void GameplayInfo::decreaseEnemyCountRemainBy(int c)
{
	m_enemyCountRemain -= c;
}

void GameplayInfo::setEnemyCountRemain(int ecr)
{
	m_enemyCountRemain = ecr;
}