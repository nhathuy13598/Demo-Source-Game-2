#pragma once
class EnemyGroupInfo
{
public:
	EnemyGroupInfo(int idx, int mc, int r, int c, int s, int *l);
	~EnemyGroupInfo();

	int getGroupIdx();
	int getMaxEnemyCount();
	int getRows();
	int getCols();
	int getSpace();
	const int *getLayout();
private:
	int m_groupIdx;
	int m_maxEnemyCount;
	int m_rows;
	int m_cols;
	int m_space;
	int *layout;
};