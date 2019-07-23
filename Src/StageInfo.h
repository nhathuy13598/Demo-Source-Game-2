#pragma once
class StageInfo
{
public:
	StageInfo(int s, int ec, float est, int minl, int maxl, bool ib = false);
	~StageInfo();

	int getStageNumber();
	int getEnemyCount();
	float getEnemySpawnTime();
	int getEnemyMinLevel();
	int getENemyMaxLevel();
	bool isBoss();

private:
	int m_Stage;
	int m_EnemyCount;
	float m_EnemySpawnTime; // delay spawn
	int m_EnemyMinLevel;
	int m_EnemyMaxLevel;
	bool m_isBoss;
};