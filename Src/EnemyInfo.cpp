#include "EnemyInfo.h"


EnemyInfo::EnemyInfo(int lvl, int hp, int as, int ms, std::vector<std::string*> *resNames)
{
	m_level = lvl;
	m_hp = hp;
	m_as = as;
	m_ms = ms;
	m_resNames = resNames;
}

EnemyInfo::~EnemyInfo()
{
	for (auto str : *m_resNames) {
		delete str;
	}
	delete m_resNames;
}

int EnemyInfo::getLevel()
{
	return m_level;
}

int EnemyInfo::getHP()
{
	return m_hp;
}

int EnemyInfo::getAttackSpeed()
{
	return m_as;
}

int EnemyInfo::getMoveSpeed()
{
	return m_ms;
}

int EnemyInfo::getResNameCount()
{
	return m_resNames->size();
}

std::string * EnemyInfo::getResName(int index)
{
	if (index < m_resNames->size()) {
		return m_resNames->at(index);
	}
	return nullptr;
}
