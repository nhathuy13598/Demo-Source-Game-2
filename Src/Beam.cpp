#include "Beam.h"
#include "SharedVariables.h"
#include "GameConfigInfo.h"

Beam::Beam(int damage) : GGameSprite(BEAM_TEXTURE)
{
	m_isEnd = false;
	m_vx = 0;
	m_vy = -BEAM_SPEED;
	m_speed = BEAM_SPEED;
	m_textureRect.x = 6;
	m_textureRect.y = 6;
	m_textureRect.w = 18;
	m_textureRect.h = 24;

	m_rect.w = m_textureRect.w;
	m_rect.h = m_textureRect.h;

	m_damage = damage;
}

Beam::~Beam()
{
}

void Beam::update(float dt) {
	GGameSprite::update(dt);
	if (!m_isEnd) {
		moveBy(m_vx, m_vy, m_speed, dt, true);
		if (m_rect.x < 0 || m_rect.x + m_rect.w > DEF_WIDTH || m_rect.y < 0 || m_rect.y + m_rect.h > DEF_HEIGHT) {
			m_isEnd = true;
		}
	}
}

void Beam::setV(float vx_, float vy_)
{
	m_vx = vx_;
	m_vy = vy_;
}

int Beam::getDamage()
{
	return m_damage;
}

void Beam::render() {
	if (!m_isEnd)
		fwRenderTexture(m_texture, &m_textureRect, &m_rect);
}

void Beam::setSpeed(float s)
{
	m_speed = s;
}
