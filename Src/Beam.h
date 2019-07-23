#pragma once

#include "GGameSprite.h"

class Beam : public GGameSprite
{
public:
	Beam(int damage);
	~Beam();

	void update(float dt);

	void setV(float vx_, float vy_);

	int getDamage();

	void render();

	void setSpeed(float s);
private:
	Rect m_textureRect;
	float m_vx, m_vy;
	float m_speed;
	int m_damage;
};