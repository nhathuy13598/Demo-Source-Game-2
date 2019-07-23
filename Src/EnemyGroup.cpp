#include "EnemyGroup.h"
#include "GameDefines.h"
#include "GameConfigInfo.h"

EnemyGroup::EnemyGroup(EnemyGroupInfo * info)
{
	setInfo(info);
	m_vx = 100;
}

EnemyGroup::~EnemyGroup()
{
	if (m_positions) {
		delete[] m_positions;
	}
	if (m_emtyLayout) {
		delete[] m_emtyLayout;
	}
}

void EnemyGroup::setInfo(EnemyGroupInfo * info)
{
	m_Info = info;
	if (m_positions) {
		delete[] m_positions;
	}
	int count = m_Info->getRows() * m_Info->getCols();
	m_positions = new Point[count];

	m_groupRect.w = m_Info->getCols() * (ENEMY_SIZE + m_Info->getSpace()) - m_Info->getSpace();
	m_groupRect.h = m_Info->getRows() * (ENEMY_SIZE + m_Info->getSpace()) - m_Info->getSpace();
	m_groupRect.x = (DEF_WIDTH - m_groupRect.w) / 2;
	m_groupRect.y = 100;
	m_groupPositionX = m_groupRect.x;

	if (m_emtyLayout) {
		delete[] m_emtyLayout;
	}
	m_emtyLayout = new bool[count];
	for (int i = 0; i < count; i++) {
		m_emtyLayout[i] = true;
		if (m_Info->getLayout()[i] == 0) {
			m_emtyLayout[i] = false;
		}
		int colIndex = i % m_Info->getCols();
		int rowIndex = i / m_Info->getCols();
		m_positions[i].x = colIndex * (ENEMY_SIZE + m_Info->getSpace());
		m_positions[i].y = rowIndex * (ENEMY_SIZE + m_Info->getSpace());
	}
}

void EnemyGroup::update(float dt)
{

	float moveSpeed = m_vx * dt;
	m_groupPositionX += moveSpeed;
	m_groupRect.x = m_groupPositionX;
	if (m_groupRect.x > DEF_WIDTH - m_groupRect.w) {
		m_groupRect.x = DEF_WIDTH - m_groupRect.w;
		m_vx = -m_vx;
	}
	if (m_groupRect.x < 0) {
		m_groupRect.x = 0;
		m_vx = -m_vx;
	}

}

bool EnemyGroup::isEmptyPostion()
{
	int count = m_Info->getRows() * m_Info->getCols();
	for (int i = 0; i < count; i++) {
		if (m_emtyLayout[i] == true && m_Info->getLayout()[i] == 1) {
			return true;
		}
	}
	return false;
}

int EnemyGroup::getEmptyPositonIndex()
{
	int count = m_Info->getRows() * m_Info->getCols();
	for (int i = 0; i < count; i++) {
		if (m_emtyLayout[i] == true && m_Info->getLayout()[i] == 1) {
			return i;
		}
	}
	return -1; // no empty position
}

Point EnemyGroup::getPositionAt(int index)
{
	Point p = m_positions[index];
	p.x += m_groupRect.x;
	p.y += m_groupRect.y;
	return p;
}

void EnemyGroup::setPositionEmpty(int index, bool isEmpty)
{
	m_emtyLayout[index] = isEmpty;
}
