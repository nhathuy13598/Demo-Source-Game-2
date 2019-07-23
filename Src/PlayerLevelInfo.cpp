#include "PlayerLevelInfo.h"


PlayerLevelInfo::PlayerLevelInfo(int lv, int bt, int bd, int sc)
{
	m_level = lv;
	m_beamType = bt;
	m_beamDamage = bd;
	m_nextLevelScore = sc;
}

PlayerLevelInfo::~PlayerLevelInfo()
{
}

int PlayerLevelInfo::getLevel()
{
	return m_level;
}

int PlayerLevelInfo::getBeamType()
{
	return m_beamType;
}

int PlayerLevelInfo::getBeamDamage()
{
	return m_beamDamage;
}

int PlayerLevelInfo::getNextScore()
{
	return m_nextLevelScore;
}
