#include "GameplayScreen.h"
#include "SharedVariables.h"
#include <algorithm>
#include "GameConfigInfo.h"

void GameplayScreen::update(float dt) {
	m_background->update(dt);
	m_coinIcon->update(dt);
	switch (m_currentGameState)
	{
	case PREPARE_STAGE_STATE:
		prepareStageUpdate(dt);
		break;
	case PLAYING_STAGE_STATE:
		playUpdate(dt);
		break;
	case ENDING_STAGE_STATE:
		endingUpdate(dt);
		break;
	case INGAME_MENU_STATE:
		m_inGameMenu->update(dt);
		break;
	case GAME_OVER_STATE:
		m_gameOverPane->update(dt);
		break;
	default:
		break;
	}

	std::string *fpsStr = new std::string(FPS_TITLE);
	fpsStr->append(std::to_string(g_CurrentFPS));
	m_fpsDisplayText->setText(fpsStr->c_str());
	delete fpsStr;
	m_fpsDisplayText->setX(DEF_WIDTH - m_fpsDisplayText->getRect().w);
}

void GameplayScreen::prepareStageUpdate(float dt) {
	spritesUpdate(dt);
	if (m_prepareText) {
		m_prepareText->update(dt);
	}
	if (m_prepareDescText) {
		m_prepareDescText->update(dt);
	}
}

void GameplayScreen::spritesUpdate(float dt)
{
	if (m_enemyGroup) {
		m_enemyGroup->update(dt);
	}
	std::vector<GGameSprite*> *endedSprites = new std::vector<GGameSprite*>;

	std::vector<GGameSprite*> *allSprites = new std::vector<GGameSprite*>(*m_allGameSprites);
	// on sprite update call create new beam function and add to allsprites cause assertion failure
	// enemy fire beam
	for (auto sprite : *allSprites) {
		sprite->update(dt);
		if (sprite->isEnd())
			endedSprites->push_back(sprite);
	}
	delete allSprites;

	if (endedSprites->size()) {
		for (auto endedSprite : *endedSprites) {
			{
				auto eItr = std::find(m_enemies->begin(), m_enemies->end(), endedSprite);
				if (eItr != m_enemies->end()) {
					m_enemies->erase(eItr);
				}
			}
			{
				auto bItr = std::find(m_beams->begin(), m_beams->end(), endedSprite);
				if (bItr != m_beams->end()) {
					m_beams->erase(bItr);
				}
			}
			{
				auto ebItr = std::find(m_enemyBeams->begin(), m_enemyBeams->end(), endedSprite);
				if (ebItr != m_enemyBeams->end()) {
					m_enemyBeams->erase(ebItr);
				}
			}
			{
				auto exploItr = std::find(m_explorationSprites->begin(), m_explorationSprites->end(), endedSprite);
				if (exploItr != m_explorationSprites->end()) {
					m_explorationSprites->erase(exploItr);
				}
			}
			{
				auto itr = std::find(m_allGameSprites->begin(), m_allGameSprites->end(), endedSprite);
				if (itr != m_allGameSprites->end()) {
					m_allGameSprites->erase(itr);
				}
			}
			delete endedSprite;
		}
	}
	delete endedSprites;
}

void GameplayScreen::playUpdate(float dt) {
	spritesUpdate(dt);
	playerUpdate(dt);
	playerBulletUpdate(dt);
	enemyBulletUpdate(dt);
	enemyUpdate(dt);
}

void GameplayScreen::playerUpdate(float dt) {
	bool moving = false;
	if (m_isKeyDownPressing || m_isKeyUpPressing || m_isKeyLeftPressing || m_isKeyRightPressing) {
		// move player
		moving = true;
		float vx = 0;
		float vy = 0;
		if (m_isKeyDownPressing) {
			vy = m_player->getMoveSpeed();
		}
		else if (m_isKeyUpPressing) {
			vy = -m_player->getMoveSpeed();
		}
		if (m_isKeyRightPressing) {
			vx = m_player->getMoveSpeed();
		}
		else if (m_isKeyLeftPressing) {
			vx -= m_player->getMoveSpeed();
		}
		m_player->moveBy(vx, vy, m_player->getMoveSpeed(), dt);

		int px = m_player->getRect().x;
		int mx = DEF_WIDTH - m_player->getRect().w;
		px = std::min(px, mx);
		px = std::max(px, 0);
		m_player->setX(px);

		int py = m_player->getRect().y;
		int my = DEF_HEIGHT - m_player->getRect().h;
		py = std::min(py, my);
		py = std::max(py, 0);
		m_player->setY(py);
	}
	if (m_isFireButtonPressing) {
		m_player->fire();
		m_suggestionTextDuration = 3;
		m_isSuggestionTextShow = false;
	}
	else {
		m_suggestionTextDuration -= dt;
		if (m_suggestionTextDuration < 0 && !m_isSuggestionTextShow) {
			m_isSuggestionTextShow = true;
			m_suggestionText->setFlashing(0.5, 1000);
		}
	}

	if (m_isSuggestionTextShow) {
		m_suggestionText->update(dt);
		auto mRect = m_player->getRect();
		m_suggestionText->centerX(mRect.x, mRect.w);
		m_suggestionText->setY(mRect.y - m_suggestionText->getRect().h);
	}
}

void GameplayScreen::playerBulletUpdate(float dt) {
	for (auto beam : *m_beams) {
		if (!beam->isEnd()) {
			for (auto enemy : *m_enemies) {
				if (fwIsRectOverlap(&beam->getRect(), &enemy->getRect())) {
					beam->setIsEnd(true);
					Point explorationPoint = beam->getCenterPoint();
					spawnExplorationAt(explorationPoint.x, explorationPoint.y, beam->getRect().w * 3);
					enemy->damageTaken(beam->getDamage());
					if (enemy->isEnd()) {
						enemyDidKill(enemy);
					}
					continue;
				}
			}
		}
		if (!beam->isEnd()) {
			for (auto eBeam : *m_enemyBeams) {
				if (fwIsRectOverlap(&beam->getRect(), &eBeam->getRect())) {
					beam->setIsEnd(true);
					eBeam->setIsEnd(true);
					Point explorationPoint = beam->getCenterPoint();
					spawnExplorationAt(explorationPoint.x, explorationPoint.y, beam->getRect().w * 3);
					explorationPoint = eBeam->getCenterPoint();
					spawnExplorationAt(explorationPoint.x, explorationPoint.y, eBeam->getRect().w * 3);
				}
			}
		}
	}
}

void GameplayScreen::enemyBulletUpdate(float dt) {
	for (auto beam : *m_enemyBeams) {
		if (!beam->isEnd()) {
			if (fwIsRectOverlap(&beam->getRect(), &m_player->getRect())) {
				beam->setIsEnd(true);
				Point explorationPoint = beam->getCenterPoint();
				spawnExplorationAt(explorationPoint.x, explorationPoint.y, beam->getRect().w * 3);
				m_player->changeCurrentHPWidthValue(-beam->getDamage());
			}
		}
	}
}

void GameplayScreen::enemyUpdate(float dt) {
	// enemy update
	if (m_currentGameplayInfo->getEnemyCountRemain() > 0 && m_enemyGroup->isEmptyPostion()) {
		m_currentGameplayInfo->decreaseEnemySpawnDelayBy(dt);
		float enemySpawnTime = m_currentGameplayInfo->getEnemySpawnDelay();
		if (enemySpawnTime <= 0) {
			m_currentGameplayInfo->setEnemySpawnDelay(m_currentStageInfo->getEnemySpawnTime());
			spawnEnemy();
		}
	}
	for (auto enemy : *m_enemies) {
		if (!enemy->isEnd()) {
			if (enemy->getCurrentState() == ATTACKING_STATE && enemy->getRect().y < ENEMY_STOP_CHACING_Y) {
				enemy->attackAt(m_player->getRect().x, m_player->getRect().y);
			}

			if (fwIsRectOverlap(&enemy->getRect(), &m_player->getRect())) {
				enemyDidKill(enemy);
				m_player->changeCurrentHPWidthValue(-enemy->getInfo()->getLevel());
			}
		}
	}
}

void GameplayScreen::endingUpdate(float dt) {
	spritesUpdate(dt);
	if (m_endStagePane) {
		m_endStagePane->update(dt);
	}
}
