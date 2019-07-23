#include "GameplayScreen.h"

#include "SharedVariables.h"
#include "GameScreenManager.h"
#include "GameConfigInfo.h"

bool GameplayScreen::init(int stage)
{
	m_background = new GameplayBackground();
	m_fpsDisplayText = new TextDisplay(FPS_TITLE, g_font);
	m_fpsDisplayText->setY(0);

	m_player = new PlayerSprite();
	m_player->centerX(0, DEF_WIDTH, true);
	m_player->setY(DEF_HEIGHT - m_player->getRect().h, true);
	m_player->setMoveSpeed(PLAYER_MOVE_SPEED);
	m_player->setDelegate(this);

	m_beams = new std::vector<Beam*>;
	m_enemies = new std::vector<Enemy*>;
	m_explorationSprites = new std::vector<AnimationSprite*>;
	m_enemyBeams = new std::vector<Beam*>;

	m_allGameSprites = new std::vector<GGameSprite*>;

	m_allGameSprites->push_back(m_player);

	m_currentGameplayInfo = 0;

	m_StageText = new TextDisplay(STAGE_TITLE, g_font);
	m_StageText->setY(0);
	m_StageText->setX(10);

	m_gameplayEnemyCountText = new TextDisplay(ENEMY_COUNT_TITLE, g_font);
	m_gameplayEnemyCountText->setY(m_fpsDisplayText->getRect().y + m_fpsDisplayText->getRect().h);
	m_gameplayEnemyCountText->setX(DEF_WIDTH - m_gameplayEnemyCountText->getRect().w);

	m_playerLevelText = new TextDisplay(PLAYER_LEVEL_TITLE, g_font);
	m_playerLevelText->setY(m_gameplayEnemyCountText->getRect().y + m_gameplayEnemyCountText->getRect().h);
	m_playerLevelText->setX(DEF_WIDTH - m_playerLevelText->getRect().w);

	m_coinIcon = new AnimationSprite(COIN_TEXTURE, 3, 2);
	m_coinIcon->setFrameDelay(0.3);
	m_coinIcon->setIsForeverLoop(true);
	m_coinIcon->setSize(20, 20);
	m_coinIcon->setX(m_StageText->getRect().x);
	m_coinIcon->setY(m_StageText->getRect().y + m_StageText->getRect().h);

	m_playerScoreText = new TextDisplay("0", g_font);
	m_playerScoreText->centerY(m_coinIcon->getRect().y, m_coinIcon->getRect().h);
	m_playerScoreText->setX(m_coinIcon->getRect().x + m_coinIcon->getRect().w);

	m_inGameMenu = new InGameMenu();
	m_inGameMenu->setDelegate(this);

	m_gameOverPane = new GameOverPane();
	m_gameOverPane->setDelegate(this);

	m_hearts = new std::vector<GGameSprite*>;

	m_endStagePane = nullptr;

	m_suggestionText = new TextDisplay(GAME_PLAY_SUGGESTION, g_font);
	m_isSuggestionTextShow = false;
	
	loadStage(stage);

	return true;
}

GameplayScreen::GameplayScreen()
{
	int stage = 1;
	int pLvl = 1;
	int sc = 0;
	SharedVariables::getInstance()->loadGame(stage, pLvl, sc);
	init(stage);
	m_player->setLevel(pLvl);
	m_player->setCurrentScore(sc);

	std::string *str = new std::string(PLAYER_LEVEL_TITLE);
	str->append(std::to_string(pLvl));
	m_playerLevelText->setText(str->c_str());
	m_playerLevelText->setX(DEF_WIDTH - m_playerLevelText->getRect().w);

	str->assign(std::to_string(sc));
	str->append("/");
	str->append(std::to_string(m_player->getCurrentPlayerLevelInfo()->getNextScore()));
	m_playerScoreText->setText(str->c_str());
	delete str;
}

GameplayScreen::~GameplayScreen()
{
	delete m_background;
	delete m_fpsDisplayText;
	delete m_playerLevelText;
	delete m_playerScoreText;

	delete m_suggestionText;

	delete m_StageText;

	delete m_beams;
	delete m_enemies;
	delete m_explorationSprites;
	delete m_enemyBeams;

	delete m_coinIcon;

	delete m_currentGameplayInfo;

	if (m_prepareText) {
		delete m_prepareText;
		m_prepareText = 0;
	}

	if (m_prepareDescText) {
		delete m_prepareDescText;
		m_prepareDescText = 0;
	}

	for (auto sprite : *m_allGameSprites) {
		delete sprite;
	}
	delete m_allGameSprites;

	for (auto heart : *m_hearts) {
		delete heart;
	}
	delete m_hearts;

	if (m_endStagePane) {
		delete m_endStagePane;
	}

	if (m_enemyGroup) {
		delete m_enemyGroup;
	}

	delete m_inGameMenu;
	delete m_gameOverPane;
}

void GameplayScreen::OnKeyDown(int key) {

	switch (m_currentGameState)
	{
	case PREPARE_STAGE_STATE:
			changeState(PLAYING_STAGE_STATE);
		return;
	case PLAYING_STAGE_STATE:
		break;
	case ENDING_STAGE_STATE:
		// reset game with next level
			loadStage(m_currentStageInfo->getStageNumber() + 1);
			changeState(PREPARE_STAGE_STATE);
		
		return;
	case INGAME_MENU_STATE:
		m_inGameMenu->OnKeyDown(key);
		return;
	case GAME_OVER_STATE:
		m_gameOverPane->OnKeyDown(key);
		return;
	default:
		return;
	}

	switch (key)
	{
	case SDLK_o: {
		m_player->setCurrentScore(m_player->getCurrentPlayerLevelInfo()->getNextScore() + 1);
		PlayerSpriteDidLevelUp(m_player);
		break;
	}
	case SDLK_p: {
		m_player->setCurrentScore(0);
		m_player->setLevel(1);
		PlayerSpriteDidLevelUp(m_player);
		break;
	}
	case SDLK_w:
	case SDLK_UP:
			m_isKeyUpPressing = true;
			m_isKeyDownPressing = false;
		break;
	case SDLK_s:
	case SDLK_DOWN:
			m_isKeyDownPressing = true;
			m_isKeyUpPressing = false;
		break;
	case SDLK_a:
	case SDLK_LEFT:
		m_isKeyLeftPressing = true;
		m_isKeyRightPressing = false;
		break;
	case SDLK_d:
	case SDLK_RIGHT:
			m_isKeyRightPressing = true;
			m_isKeyLeftPressing = false;
		break;
	case SDLK_SPACE:
		m_isFireButtonPressing = true;
		break;
	case SDLK_ESCAPE:
		changeState(INGAME_MENU_STATE);
		break;
	default:
		break;
	}
}

void GameplayScreen::OnKeyUp(int key) {
	switch (key)
	{
	case SDLK_w:
	case SDLK_UP:
		m_isKeyUpPressing = false;
		break;
	case SDLK_s:
	case SDLK_DOWN:
		m_isKeyDownPressing = false;
		break;
	case SDLK_a:
	case SDLK_LEFT:
		m_isKeyLeftPressing = false;
		break;
	case SDLK_d:
	case SDLK_RIGHT:
		m_isKeyRightPressing = false;
		break;
	case SDLK_SPACE:
 		m_isFireButtonPressing = false;
		break;
	default:
		break;
	}
}


void GameplayScreen::render() {
	m_background->render();

	for (auto sprite : *m_allGameSprites) {
		sprite->render();
	}


	for (auto heart : *m_hearts) {
		heart->render();
	}

	switch (m_currentGameState)
	{
	case PREPARE_STAGE_STATE:
		if (m_prepareText) {
			m_prepareText->render();
		}
		if (m_prepareDescText) {
			m_prepareDescText->render();
		}
		break;
	case PLAYING_STAGE_STATE:
		break;
	case ENDING_STAGE_STATE:
		if (m_endStagePane) {
			m_endStagePane->render();
		}
		break;
	case INGAME_MENU_STATE:
		m_inGameMenu->render();
		break;
	case GAME_OVER_STATE:
		m_gameOverPane->render();
	default:
		break;
	}

	m_StageText->render();
	m_fpsDisplayText->render();
	m_gameplayEnemyCountText->render();
	m_coinIcon->render();
	m_playerScoreText->render();
	m_playerLevelText->render();

	if (m_isSuggestionTextShow) {
		m_suggestionText->render();
	}
}

void GameplayScreen::PlayerSpriteDidFire(PlayerSprite *ps) {
	auto levelInfo = ps->getCurrentPlayerLevelInfo();
	int spawnPx = ps->getRect().x + ps->getRect().w / 2;
	int spawnPy = ps->getRect().y;
	int beamType = levelInfo->getBeamType();
	switch (beamType)
	{
	case 1:
		spawnPlayerBeamAt(spawnPx, spawnPy, 0.f, -BEAM_SPEED);
		break;
	case 2:
		spawnPlayerBeamAt(spawnPx - 30, spawnPy, 0.f, -BEAM_SPEED);
		spawnPlayerBeamAt(spawnPx + 30, spawnPy, 0.f, -BEAM_SPEED);
		break;
	default:
		double deltaAngle = 5;
		double totalAngle = deltaAngle * beamType;
		double beginAngle = 270 - totalAngle / 2;
		for (int i = 0; i < beamType; i++) {
			
			float vx = cos(degree2radian(beginAngle)) * BEAM_SPEED;
			float vy = sin(degree2radian(beginAngle)) * BEAM_SPEED;
			spawnPlayerBeamAt(spawnPx, spawnPy, vx, vy);
			beginAngle += deltaAngle;
		}
		break;
	}
}

void GameplayScreen::PlayerSpriteDidLevelUp(PlayerSprite * ps)
{
	std::string *str = new std::string(PLAYER_LEVEL_TITLE);
	str->append(std::to_string(ps->getCurrentPlayerLevelInfo()->getLevel()));
	m_playerLevelText->setText(str->c_str());	
	m_playerLevelText->setX(DEF_WIDTH - m_playerLevelText->getRect().w);
	delete str;
}

void GameplayScreen::PlayerSpriteDidChangeHP(PlayerSprite *ps) {

	int currentHP = ps->getCurrentHP();

	int m_heartSize = m_hearts->size();
	if (m_heartSize != currentHP) {
		if (m_heartSize > currentHP) {
			ps->setFlashing(0.03, 0.5);
			// remove heart
			for (int i = m_heartSize - 1; i >= 0; i--) {
				if (i >= currentHP) {
					auto h = m_hearts->at(i);
					auto itr = std::find(m_hearts->begin(), m_hearts->end(), h);
					if (itr != m_hearts->end()) {
						m_hearts->erase(itr);
						delete h;
					}
				}
			}
		}
		else {
			// add heart
			int hx = 10, hy = m_coinIcon->getRect().y + m_coinIcon->getRect().h;
			for (auto i = 0; i < currentHP; i++) {
				if (i < m_heartSize) {
					auto rec = m_hearts->at(i)->getRect();
					hx = rec.x + rec.w;
				}
				else {
					auto heart = new GGameSprite(HEART_TEXTURE, 20);
					heart->setX(hx, true);
					heart->setY(hy, true);
					m_hearts->push_back(heart);
					auto rec = heart->getRect();
					hx = rec.x + rec.w;
				}
			}
		}
	}

	if (currentHP <= 0) {
		changeState(GAME_OVER_STATE);
	}
}

void GameplayScreen::EnemyDidFire(Enemy * ef)
{
	float sx = ef->getRect().x + ef->getRect().w / 2;
	float sy = ef->getRect().y + ef->getRect().h;
	if (ef->isBoss()) {
	//	int random beam
		int randomBeam = 3 + rand() % 5;

		double deltaAngle = 25;
		double totalAngle = deltaAngle * randomBeam;
		float lx = m_player->getCenterPoint().x - ef->getCenterPoint().x;
		float ly = m_player->getCenterPoint().y - ef->getCenterPoint().y;
		double lookAngle = atan2(ly, lx) * 180.f / M_PI;
		double beginAngle = lookAngle - totalAngle / 2;
		float beamSpeed = BEAM_SPEED / (1 + rand() % 3);
		for (int i = 0; i < randomBeam; i++) {
			float vx = cos(degree2radian(beginAngle)) * BEAM_SPEED;
			float vy = sin(degree2radian(beginAngle)) * BEAM_SPEED;
			auto beam = spawnEnemyBeamAt(sx, sy, vx, vy);
			beam->setSpeed(beamSpeed);
			beginAngle += deltaAngle;
		}
	}
	else {
		spawnEnemyBeamAt(sx, sy, 0, BEAM_SPEED);
	}
}

void GameplayScreen::EnmeyNeedToAttack(Enemy * ea)
{
	ea->attackAt(m_player->getRect().x, m_player->getRect().y);
}

void GameplayScreen::ingameMenuDidConfirm(InGameMenuItemType type)
{
	switch (type)
	{
	case InGameMenuItemType_CONTINUE:
		if (m_currentGameState == GAME_OVER_STATE) {
			clearStage();
			loadStage(m_currentStageInfo->getStageNumber());
		}
		else {
			changeState(PLAYING_STAGE_STATE);
		}
		break;
	case InGameMenuItemType_QUIT:
		GameScreenManager::getInstance()->showMainMenuScreen();
		break;
	default:
		break;
	}
}


void GameplayScreen::changeState(GameplayState st) {
	m_currentGameState = st;

	m_isSuggestionTextShow = false;

	switch (m_currentGameState)
	{
	case PREPARE_STAGE_STATE:
		m_player->setHidden(false);
		m_background->setSpeed(0.02f, 0.05f);
		if (!m_prepareText) {
			m_prepareText = new TextDisplay(PREPARE_TITLE, g_font, 200);
			m_prepareText->centerX(0, DEF_WIDTH);
			m_prepareText->centerY(0, DEF_HEIGHT);
		}
		if (!m_prepareDescText) {
			m_prepareDescText = new TextDisplay(SKIP_DESC, g_font, 50);
			m_prepareDescText->centerX(0, DEF_WIDTH);
			m_prepareDescText->setY(m_prepareText->getRect().y + m_prepareText->getRect().h);
		}
		m_prepareDescText->setFlashing(0.3f, 10.f);
		break;
	case PLAYING_STAGE_STATE:
		m_suggestionTextDuration = 3;
		m_background->setSpeed(1.f, 2.f);
		break;
	case ENDING_STAGE_STATE:
		m_background->setSpeed(0.02f, 0.05f);
		if (!m_endStagePane) {
			m_endStagePane = new EndStagePane(m_currentStageInfo->getStageNumber() + 1);
		}
		else {
			m_endStagePane->setNextStage(m_currentStageInfo->getStageNumber() + 1);
		}
		break;
	case INGAME_MENU_STATE:
		m_background->setSpeed(0.02f, 0.05f);
		break;
	case GAME_OVER_STATE:
		auto cp = m_player->getCenterPoint();
		spawnExplorationAt(cp.x, cp.y, m_player->getRect().w * 3);
		m_background->setSpeed(0.02f, 0.05f);

		m_player->setHidden(true);
		m_player->centerX(0, DEF_WIDTH, true);
		m_player->setY(DEF_HEIGHT - m_player->getRect().h, true);

		break;
	default:
		break;
	}
}

void GameplayScreen::spawnExplorationAt(int x, int y, int size)
{
	AnimationSprite *exploration = new AnimationSprite(EXLORATION_TEXTURE, EXLORATION_TEXTURE_COL, EXLORATION_TEXTURE_ROW);
	exploration->setSize(size, size);
	exploration->centerX(x, 0);
	exploration->centerY(y, 0);
	exploration->setFrameDelay(0.05f);
	m_explorationSprites->push_back(exploration);
	m_allGameSprites->push_back(exploration);
}

void GameplayScreen::spawnPlayerBeamAt(int x, int y, float vx, float vy)
{
	Beam *beam = new Beam(m_player->getCurrentPlayerLevelInfo()->getBeamDamage());
	beam->centerX(x, 0, true);
	beam->centerY(y, 0, true);
	beam->setV(vx, vy);
	m_beams->push_back(beam);
	m_allGameSprites->push_back(beam);
}

Beam *GameplayScreen::spawnEnemyBeamAt(int x, int y, float vx, float vy)
{
	Beam *beam = new Beam(1);
	beam->centerX(x, 0, true);
	beam->setY(y + beam->getRect().h / 2, true);
	beam->setV(vx, vy);
	m_enemyBeams->push_back(beam);
	m_allGameSprites->push_back(beam);
	return beam;
}

void GameplayScreen::spawnEnemy()
{
	int minLv = m_currentStageInfo->getEnemyMinLevel();
	int maxLv = m_currentStageInfo->getENemyMaxLevel();
	int deltaLv = maxLv - minLv;
	int randomLevel = minLv;
	if (deltaLv > 0) {
		randomLevel = minLv + rand() % deltaLv;
	}

	bool isBoss = false;
	if (m_currentStageInfo->isBoss() && m_currentGameplayInfo->getEnemyCountRemain() == 1) {
		isBoss = true;
		randomLevel = maxLv;
	}
	Enemy *enemy = Enemy::Create(randomLevel, isBoss);
	if (enemy) {
		enemy->setDelegate(this);
		m_currentGameplayInfo->decreaseEnemyCountRemainBy(1);
		m_enemies->push_back(enemy);
		m_allGameSprites->push_back(enemy);
		enemy->setGroup(m_enemyGroup, m_enemyGroup->getEmptyPositonIndex());
	}
}

void GameplayScreen::loadStage(int stage)
{
	m_currentStageInfo = SharedVariables::getInstance()->getStageInfoAt(stage);
	if (m_currentGameplayInfo) {
		delete m_currentGameplayInfo;
	}
	m_currentGameplayInfo = new GameplayInfo(m_currentStageInfo);

	setEnemyCountTitle(m_currentGameplayInfo->getEnemyCountRemain());

	if (!m_enemyGroup) {
		m_enemyGroup = new EnemyGroup(SharedVariables::getInstance()->getRandomGroup());
	}
	else {
		m_enemyGroup->setInfo(SharedVariables::getInstance()->getRandomGroup());
	}

	auto stageStr = new std::string(STAGE_TITLE);
	stageStr->append(std::to_string(stage));
	m_StageText->setText(stageStr->c_str());
	delete stageStr;

	m_player->resetHP();

	changeState(PREPARE_STAGE_STATE);

}

void GameplayScreen::enemyDidKill(Enemy * e)
{
	e->setIsEnd(true);

	m_player->changeScoreBy(e->getInfo()->getLevel());

	std::string *str = new std::string(std::to_string(m_player->getScore()));
	str->append("/");
	str->append(std::to_string(m_player->getCurrentPlayerLevelInfo()->getNextScore()));
	m_playerScoreText->setText(str->c_str());
	m_coinIcon->setFlashing(0.1, 0.5);
	delete str;

	Point explorationPoint = e->getCenterPoint();
	spawnExplorationAt(explorationPoint.x, explorationPoint.y, e->getRect().w * 3);

	int aliveEnemyCount = m_currentGameplayInfo->getEnemyCountRemain();
	for (auto enemy : *m_enemies) {
		if (!enemy->isEnd()) {
			aliveEnemyCount++;
		}
	}
	setEnemyCountTitle(aliveEnemyCount);

	if (aliveEnemyCount <= 0) {
		changeState(ENDING_STAGE_STATE);
		int saveStage = m_currentStageInfo->getStageNumber() + 1;
		int savePlayerLevel = m_player->getCurrentPlayerLevelInfo()->getLevel();
		int saveScore = m_player->getScore();
		SharedVariables::getInstance()->saveGame(saveStage, savePlayerLevel, saveScore);
	}
}

void GameplayScreen::setEnemyCountTitle(int ec)
{
	std::string *eCountStr = new std::string(ENEMY_COUNT_TITLE);
	eCountStr->append(std::to_string(ec));
	m_gameplayEnemyCountText->setText(eCountStr->c_str());
	m_gameplayEnemyCountText->setX(DEF_WIDTH - m_gameplayEnemyCountText->getRect().w);
	delete eCountStr;
}

void GameplayScreen::clearStage()
{
	for (auto obj : *m_enemies) {
		auto itr = std::find(m_allGameSprites->begin(), m_allGameSprites->end(), obj);
		if (itr != m_allGameSprites->end()) {
			m_allGameSprites->erase(itr);
		}
		delete obj;
	}
	m_enemies->clear();

	for (auto obj : *m_enemyBeams) {
		auto itr = std::find(m_allGameSprites->begin(), m_allGameSprites->end(), obj);
		if (itr != m_allGameSprites->end()) {
			m_allGameSprites->erase(itr);
		}
		delete obj;
	}
	m_enemyBeams->clear();

	for (auto obj : *m_beams) {
		auto itr = std::find(m_allGameSprites->begin(), m_allGameSprites->end(), obj);
		if (itr != m_allGameSprites->end()) {
			m_allGameSprites->erase(itr);
		}
		delete obj;
	}
	m_beams->clear();
}
