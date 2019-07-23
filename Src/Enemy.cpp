#include "Enemy.h"
#include "SharedVariables.h"
#include "ResourcesManager.h"
#include "GameDefines.h"
#include <algorithm>
#include "GameConfigInfo.h"

Enemy * Enemy::Create(int level, bool isBoss)
{
	auto enemyInfo = SharedVariables::getInstance()->getEnemyInfoAtLevel(level);
	if (enemyInfo) {
		Enemy *enemy = new Enemy(enemyInfo, isBoss);
		return enemy;
	}
	return nullptr;
}

Enemy::Enemy(EnemyInfo * eInfo, bool isBoss)
{
	m_isBoss = isBoss;
	m_info = eInfo;
	auto resName = m_info->getResName(rand() % m_info->getResNameCount());
	m_texture = CacheImageName(resName->c_str(), m_rect.w, m_rect.h);
	float ratio = (float)ENEMY_SIZE / m_rect.w;
	m_rect.w = ENEMY_SIZE;
	m_rect.h *= ratio;

	m_randomAttackDelay = 3.0 + rand() % 10;

	m_currentHP = eInfo->getHP();

	m_currentAttackSpeed = eInfo->getAttackSpeed();

	if (m_isBoss) {
		m_currentHP *= BOSS_HP_MULTIPLE;
		m_rect.w *= BOSS_SIZE_MULTIPLE;
		m_rect.h *= BOSS_SIZE_MULTIPLE;
		m_currentAttackSpeed /= BOSS_ATTACK_SPEED_MULTIPLE;
		m_bossChangeDirectionDelay = 3 + rand() % 5;
		int m_randomPx = DEF_WIDTH - m_rect.w;
		if (m_randomPx <= 0) {
			m_randomPx /= 2;
		}
		else {
			m_randomPx = rand() % m_randomPx;
		}
		m_randomPy = rand() % (DEF_HEIGHT / 3);
	}

	m_fireDelay = m_currentAttackSpeed;

	m_scale = 1;
	m_angle = 0;

	int maxX = DEF_WIDTH - m_rect.w;
	if (maxX <= 0) {
		m_rect.x = maxX / 2;
	}
	else {
		m_rect.x = rand() % maxX;
	}
	m_rect.y = -m_rect.h;

	m_positionX = m_rect.x;
	m_positionY = m_rect.y;


	m_currentState = GETTING_TO_POSITION_STATE;



	m_isInPosition = false;
}

Enemy::~Enemy()
{
}

void Enemy::update(float dt)
{
	GGameSprite::update(dt);
	if (m_isEnd) {
		return;
	}
	m_fireDelay -= dt;
	if (m_currentAttackSpeed > 1) {
		m_currentAttackSpeed -= dt / 5;
	}
	if (m_fireDelay <= 0) {
		m_fireDelay = m_currentAttackSpeed;
		if (m_delegate)
			m_delegate->EnemyDidFire(this);
	}
	if (m_isBoss) {
		m_bossChangeDirectionDelay -= dt;
		float distance = sqrt(powf(m_randomPx - m_rect.x, 2) + powf(m_randomPy - m_rect.y, 2));
		if (distance > m_info->getMoveSpeed() * dt) {
			moveTo(m_randomPx, m_randomPy, m_info->getMoveSpeed() / 5, dt);
		}
		if (m_bossChangeDirectionDelay <= 0) {
			int maxX = DEF_WIDTH - m_rect.w;
			if (maxX <= 0) {
				m_randomPx = maxX / 2;
			}
			else {
				m_randomPx = rand() % maxX;
			}
			m_randomPy = rand() % (DEF_HEIGHT / 3);
			m_bossChangeDirectionDelay = 3 + rand() % 5;
		}
	} else {
		switch (m_currentState)
		{
		case GETTING_TO_POSITION_STATE: {
			auto p = m_group->getPositionAt(m_groupIndex);
			if (!m_isInPosition) {
				float dx = p.x - m_rect.x;
				float dy = p.y - m_rect.y;
				float distance = sqrtf(powf(dx, 2) + powf(dy, 2));

				if (distance <= (m_info->getMoveSpeed() / g_CurrentFPS)) {
					setX(p.x, true);
					setY(p.y, true);
					m_isInPosition = true;
					m_angle = 0;
				}
				else {
					moveTo(p.x, p.y, m_info->getMoveSpeed(), dt, true);
				}
			}
			else {
				setX(p.x, true);
				setY(p.y, true);

				m_randomAttackDelay -= dt;
				if (m_randomAttackDelay <= 0) {
					m_randomAttackDelay = 3.0 + rand() % 10;
					if (m_delegate) {
						m_delegate->EnmeyNeedToAttack(this);
					}
				}
			}
		}
										break;
		case ATTACKING_STATE: {
			float dx = m_attackDesX - m_rect.x;
			float dy = m_attackDesY - m_rect.y;
			float distance = sqrtf(powf(dx, 2) + powf(dy, 2));

			if (distance <= (m_info->getMoveSpeed() / g_CurrentFPS)) {
				m_isInPosition = false;
				m_currentState = GETTING_TO_POSITION_STATE;
			}
			else {
				moveTo(m_attackDesX, m_attackDesY, m_info->getMoveSpeed(), dt, true);
			}
		}
							  break;
		default:
			break;
		}
	}
}

void Enemy::setDelegate(EnemyDelegate * d)
{
	m_delegate = d;
}

EnemyInfo * Enemy::getInfo()
{
	return m_info;
}

void Enemy::setGroup(EnemyGroup * g, int groupIndex)
{
	m_group = g;
	m_groupIndex = groupIndex;
	m_group->setPositionEmpty(groupIndex, false);
}
void Enemy::setIsEnd(bool ie) {
	GGameSprite::setIsEnd(ie);
	m_group->setPositionEmpty(m_groupIndex, true);
}

void Enemy::render() {
	if (!m_isEnd)
		GGameSprite::render();
}

EnemyState Enemy::getCurrentState()
{
	return m_currentState;
}

void Enemy::attackAt(int dx, int dy)
{
	m_currentState = ATTACKING_STATE;
	m_attackDesX = dx;
	m_attackDesY = dy;
}

bool Enemy::isBoss()
{
	return m_isBoss;
}

void Enemy::damageTaken(int d)
{
	m_currentHP -= d;
	if (m_currentHP <= 0) {
		setIsEnd(true);
	}
}
