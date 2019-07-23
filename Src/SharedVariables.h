#pragma once

#include "GameScreen.h"
#include <string>
#include "Framework.h"
#include "GameDefines.h"
#include "EnemyInfo.h"
#include "StageInfo.h"
#include "EnemyGroupInfo.h"
#include <vector>
#include "PlayerLevelInfo.h"

#define SHARE_CalcCurrentFPS(dt) SharedVariables::getInstance()->calcFPS(dt);

extern TTF_Font *g_font;
extern int g_CurrentFPS;

class SharedVariables
{
public:
	SharedVariables();
	~SharedVariables();

	static SharedVariables * getInstance();
	static void DestroyInstance();

	const std::string *getTexturePath();
	TTF_Font *getFont();

	void load();

	EnemyInfo *getEnemyInfoAtLevel(int lvl);
	StageInfo *getStageInfoAt(int stage);
	EnemyGroupInfo *getRandomGroup();

	void calcFPS(float dt);

	void loadGame(int &stage, int &playerLv, int &score);
	void saveGame(int stage, int playerLv, int score);

	PlayerLevelInfo *getLevelInfo(int lv);
	int getPlayerMaxLevel();
private:
	static SharedVariables * ms_Instance;

	TTF_Font *m_font;

	std::string *m_texturePath;


	std::vector<EnemyInfo*> *m_enemyInfos = nullptr;
	void loadEnemyInfos();

	std::vector<StageInfo*> *m_stageInfos = nullptr;
	void loadStageInfos();

	std::vector<EnemyGroupInfo*> *m_enemyGroups = nullptr;
	void loadEnemyGroups();

	std::vector<PlayerLevelInfo*> *m_playerLevelInfos = nullptr;
	void loadPlayerLevelInfo();
};