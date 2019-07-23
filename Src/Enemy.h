#pragma once
#include "GGameSprite.h"
#include "EnemyInfo.h"
#include "EnemyGroup.h"

typedef enum EnemyState {
	GETTING_TO_POSITION_STATE,
	ATTACKING_STATE
} EnemyState;

class Enemy;

class EnemyDelegate
{
public:
	virtual void EnemyDidFire(Enemy *ef) {};
	virtual void EnmeyNeedToAttack(Enemy *ea) = 0;
};

class Enemy : public GGameSprite
{
public:
	static Enemy *Create(int level, bool isBoss = false);

	Enemy(EnemyInfo *eInfo, bool isBoss = false);
	~Enemy();

	void update(float dt);

	void setDelegate(EnemyDelegate * d);

	EnemyInfo *getInfo();

	void setGroup(EnemyGroup *g, int groupIndex);

	void setIsEnd(bool ie);

	void render();

	EnemyState getCurrentState();
	void attackAt(int dx, int dy);

	bool isBoss();

	void damageTaken(int d);
private:
	EnemyDelegate *m_delegate = nullptr;
	EnemyInfo *m_info;

	float m_fireDelay = 0;
	float m_currentAttackSpeed;

	EnemyState m_currentState;

	int m_groupIndex = 0;
	EnemyGroup *m_group;
	bool m_isInPosition = false;

	float m_randomAttackDelay;
	float m_attackDesX, m_attackDesY;

	bool m_isBoss;
	float m_bossChangeDirectionDelay;
	float m_randomPx, m_randomPy;
	int m_currentHP;
};