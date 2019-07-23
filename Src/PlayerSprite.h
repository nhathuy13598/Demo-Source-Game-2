#pragma once

#include "GGameSprite.h"
#include "PlayerLevelInfo.h"

class PlayerSprite;

class PlayerSpriteDelegate
{
public:
	virtual void PlayerSpriteDidFire(PlayerSprite *ps) {};
	virtual void PlayerSpriteDidLevelUp(PlayerSprite *ps) {};
	virtual void PlayerSpriteDidChangeHP(PlayerSprite *ps) {};
};

class PlayerSprite : public GGameSprite
{
public:
	PlayerSprite();
	~PlayerSprite();

	void setMoveSpeed(int ms);
	int getMoveSpeed();

	void fire();

	void update(float dt);

	void setDelegate(PlayerSpriteDelegate * d);

	void setLevel(int lv);
	PlayerLevelInfo *getCurrentPlayerLevelInfo();
	
	void setCurrentScore(int sc);
	void changeScoreBy(int csc);
	int getScore();

	void resetHP();
	int getCurrentHP();
	void setCurrentHP(int shp);
	void changeCurrentHPWidthValue(int chp);
private:
	int m_moveSpeed;
	int m_fireSpeed; // per second
	float m_fireTimeDelay;
	PlayerSpriteDelegate *m_delegate = nullptr;
	PlayerLevelInfo *m_currentPlayerLevelInfo;
	int m_currentScore;
	int m_currentHP;
	bool checkScoreLevelUp();
};