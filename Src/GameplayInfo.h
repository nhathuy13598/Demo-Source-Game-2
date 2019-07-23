#pragma once

#include "StageInfo.h"


class GameplayInfo
{
public:
	GameplayInfo(StageInfo *stgInfo);
	~GameplayInfo();

	void setStageInfo(StageInfo *stgInfo);

	float getEnemySpawnDelay();
	void decreaseEnemySpawnDelayBy(float f);
	void setEnemySpawnDelay(float esd);

	int getEnemyCountRemain();
	void decreaseEnemyCountRemainBy(int c);
	void setEnemyCountRemain(int ecr);

private:
	float m_enemySpawnDelay = 0;
	int m_enemyCountRemain = 0;
};