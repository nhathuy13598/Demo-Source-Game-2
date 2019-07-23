#pragma once
#include "EnemyGroupInfo.h"
#include "Framework.h"

class EnemyGroup
{
public:
	EnemyGroup(EnemyGroupInfo *info);
	~EnemyGroup();

	void setInfo(EnemyGroupInfo *info);

	void update(float dt);
	
	bool isEmptyPostion();
	int getEmptyPositonIndex();
	Point getPositionAt(int index);

	void setPositionEmpty(int index, bool isEmpty);
private:
	EnemyGroupInfo *m_Info;
	Point *m_positions = nullptr;
	bool *m_emtyLayout = nullptr; // true is empty
	Rect m_groupRect;
	float m_vx = 100;
	float m_groupPositionX;
};
