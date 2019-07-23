#pragma once
#include "GameScreen.h"

#include "PlayerSprite.h"
#include "Beam.h"
#include "Enemy.h"
#include "GameplayInfo.h"
#include "GameDefines.h"
#include "AnimationSprite.h"
#include "GameplayBackground.h"
#include "TextDisplay.h"
#include "EndStagePane.h"
#include "EnemyGroup.h"
#include "InGameMenu.h"
#include "GameOverPane.h"

#include <vector>

class GameplayScreen : public GameScreen
	, public PlayerSpriteDelegate
	, public EnemyDelegate
	, public InGameMenuDelegate
{
protected:
	bool init(int stage);

	void PlayerSpriteDidFire(PlayerSprite *ps);
	void PlayerSpriteDidLevelUp(PlayerSprite *ps);
	void PlayerSpriteDidChangeHP(PlayerSprite *ps);
	void EnemyDidFire(Enemy *ef);
	void EnmeyNeedToAttack(Enemy *ea);
	void ingameMenuDidConfirm(InGameMenuItemType type);

public:
	GameplayScreen();
	~GameplayScreen();

	void OnKeyDown(int key);

	void OnKeyUp(int key);

	void update(float dt);

	void render();

private:
	GameplayBackground *m_background;
	PlayerSprite *m_player;
	bool m_isKeyUpPressing = false;
	bool m_isKeyDownPressing = false;
	bool m_isKeyLeftPressing = false;
	bool m_isKeyRightPressing = false;
	bool m_isFireButtonPressing = false;

	std::vector<Beam*> *m_beams;
	std::vector<Enemy*> *m_enemies;
	std::vector<Beam*> *m_enemyBeams;
	std::vector<AnimationSprite*> *m_explorationSprites;

	std::vector<GGameSprite*> *m_allGameSprites;

	std::vector<GGameSprite*> *m_hearts;

	StageInfo *m_currentStageInfo; // weak
	GameplayInfo *m_currentGameplayInfo; 
	GameplayState m_currentGameState = PREPARE_STAGE_STATE;
	EnemyGroup *m_enemyGroup = nullptr;

	void changeState(GameplayState st);
	// gameplay update
	void prepareStageUpdate(float dt);

	void spritesUpdate(float dt);
	void playUpdate(float dt);
	void playerUpdate(float dt);
	void playerBulletUpdate(float dt);
	void enemyUpdate(float dt);
	void enemyBulletUpdate(float dt);

	void endingUpdate(float dt);

	TextDisplay *m_prepareText = 0;
	TextDisplay *m_fpsDisplayText = 0;
	TextDisplay *m_prepareDescText = 0;
	TextDisplay *m_gameplayEnemyCountText = 0;
	TextDisplay *m_playerScoreText = 0;
	TextDisplay *m_playerLevelText = 0;
	TextDisplay *m_StageText = 0;
	AnimationSprite *m_coinIcon = 0;

	EndStagePane *m_endStagePane;
	GameOverPane *m_gameOverPane;

	TextDisplay *m_suggestionText = 0;
	bool m_isSuggestionTextShow;
	float m_suggestionTextDuration;

	void spawnExplorationAt(int x, int y, int size);
	void spawnPlayerBeamAt(int x, int y, float vx, float vy);
	Beam *spawnEnemyBeamAt(int x, int y, float vx, float vy);
	void spawnEnemy();

	void loadStage(int stage);
	
	void enemyDidKill(Enemy *e);

	void setEnemyCountTitle(int ec);

	InGameMenu *m_inGameMenu;

	void clearStage();
};
