#pragma once
#include <vector>

class EnemyInfo
{
public:
	EnemyInfo(int lvl, int hp, int as, int ms, std::vector<std::string*> *resNames);
	~EnemyInfo();

	int getLevel();
	int getHP();
	int getAttackSpeed();
	int getMoveSpeed();

	int getResNameCount();
	std::string *getResName(int index);
private:
	int m_level;
	int m_hp;
	int m_as;
	int m_ms;
	std::vector<std::string*> *m_resNames;
};
