#pragma once
class PlayerLevelInfo
{
public:
	PlayerLevelInfo(int lv, int bt, int bd, int sc);
	~PlayerLevelInfo();

	int getLevel();
	int getBeamType();
	int getBeamDamage();
	int getNextScore();
private:
	int m_level;
	int m_beamType;
	int m_beamDamage;
	int m_nextLevelScore;
};