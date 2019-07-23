#include "PlayerSprite.h"
#include "GameConfigInfo.h"
#include "SharedVariables.h"

PlayerSprite::PlayerSprite() : GGameSprite(PLAYER_TEXTURE, PLAYER_SIZE)
{
	m_fireTimeDelay = 0;
	m_currentScore = 0;
}

PlayerSprite::~PlayerSprite()
{
}

void PlayerSprite::setMoveSpeed(int ms)
{
	m_moveSpeed = ms;
}

int PlayerSprite::getMoveSpeed()
{
	return m_moveSpeed;
}

#define FIRE_TIME_DELAY 0.3

void PlayerSprite::fire() 
{
	if (m_fireTimeDelay > FIRE_TIME_DELAY) {
		m_fireTimeDelay = 0;
		if (m_delegate)
			m_delegate->PlayerSpriteDidFire(this);
	}
}

void PlayerSprite::update(float dt) {
	GGameSprite::update(dt);
	m_fireTimeDelay += dt;
}

void PlayerSprite::setDelegate(PlayerSpriteDelegate * d)
{
	m_delegate = d;
}

void PlayerSprite::setLevel(int lv)
{
	m_currentPlayerLevelInfo = SharedVariables::getInstance()->getLevelInfo(lv);
	checkScoreLevelUp();
}

PlayerLevelInfo * PlayerSprite::getCurrentPlayerLevelInfo()
{
	return m_currentPlayerLevelInfo;
}

void PlayerSprite::setCurrentScore(int sc)
{
	m_currentScore = sc;
	checkScoreLevelUp();
}

void PlayerSprite::changeScoreBy(int csc)
{
	m_currentScore += csc;
	checkScoreLevelUp();
}

int PlayerSprite::getScore()
{
	return m_currentScore;
}

void PlayerSprite::resetHP()
{
	setCurrentHP(START_STAGE_PLAYER_HP);
}

int PlayerSprite::getCurrentHP()
{
	return m_currentHP;
}

void PlayerSprite::setCurrentHP(int shp)
{
	m_currentHP = shp;
	if (m_delegate) {
		m_delegate->PlayerSpriteDidChangeHP(this);
	}
}

void PlayerSprite::changeCurrentHPWidthValue(int chp)
{
	m_currentHP += chp;
	if (m_delegate) {
		m_delegate->PlayerSpriteDidChangeHP(this);
	}
}

bool PlayerSprite::checkScoreLevelUp()
{
	if (m_currentScore > m_currentPlayerLevelInfo->getNextScore()
		&& m_currentPlayerLevelInfo->getLevel() < SharedVariables::getInstance()->getPlayerMaxLevel()) 
	{
		setLevel(m_currentPlayerLevelInfo->getLevel() + 1);
		if (m_delegate)
			m_delegate->PlayerSpriteDidLevelUp(this);
		return true;
	}
	return false;
}
