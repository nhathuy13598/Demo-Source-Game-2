#pragma once

#define DEF_WIDTH		GameConfigInfo::getInstance()->getScreenWidth()
#define DEF_HEIGHT		GameConfigInfo::getInstance()->getScreenHeight()

#define DEF_FPS			GameConfigInfo::getInstance()->getFPS()

#define PLAYER_MOVE_SPEED	GameConfigInfo::getInstance()->getPlayerMoveSpeed()
#define BEAM_SPEED			GameConfigInfo::getInstance()->getBeamSpeed()

#define ENEMY_STOP_CHACING_Y GameConfigInfo::getInstance()->getEnemyStopChasingY()

#define START_STAGE_PLAYER_HP GameConfigInfo::getInstance()->getStartStagePlayerHP()

#define PLAYER_SIZE		GameConfigInfo::getInstance()->getPlayerSize()

#define ENEMY_SIZE			GameConfigInfo::getInstance()->getEnemySize()
#define BOSS_SIZE_MULTIPLE	GameConfigInfo::getInstance()->getBossSize()
#define BOSS_HP_MULTIPLE	GameConfigInfo::getInstance()->getBossHP()
#define BOSS_ATTACK_SPEED_MULTIPLE GameConfigInfo::getInstance()->getBossAttackSpeed()

class GameConfigInfo
{
public:
	GameConfigInfo();
	~GameConfigInfo();

	static GameConfigInfo * getInstance();
	static void DestroyInstance();

	int getScreenWidth();
	int getScreenHeight();
	int getFPS();
	int getPlayerMoveSpeed();
	int getBeamSpeed();
	int getEnemyStopChasingY();
	int getStartStagePlayerHP();
	int getPlayerSize();
	int getEnemySize();
	int getBossSize();
	int getBossHP();
	int getBossAttackSpeed();

	void loadConfig();

private:
	static GameConfigInfo * ms_Instance;

	int m_screenWidth;
	int m_screenHeight;
	int m_fps;
	int m_playerMoveSpeed;
	int m_beamSpeed;
	int m_enemyStopChasingY;
	int m_startStagePlayerHP;
	int m_playerSize;
	int m_enemySize;
	int m_bossSize;
	int m_bossHP;
	int m_bossAtkSpd;
};
