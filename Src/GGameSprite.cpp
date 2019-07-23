#include "GGameSprite.h"
#include "SharedVariables.h"

#include "ResourcesManager.h"

GGameSprite::GGameSprite() {

}

GGameSprite::~GGameSprite()
{
}

GGameSprite::GGameSprite(const char *fileName, int sizeWidth) {

	m_texture = CacheImageName(fileName, m_rect.w, m_rect.h);

	if (sizeWidth != 0) {
		float ratio = (float)sizeWidth / m_rect.w;
		m_rect.w = sizeWidth;
		m_rect.h *= ratio;
	}
	m_scale = 1;
	m_angle = 0;
}

Rect GGameSprite::getRect() {
	return m_rect;
}

void GGameSprite::setTexture(const char * fileName)
{
	int sizeW = m_rect.w;

	m_texture = CacheImageName(fileName, m_rect.w, m_rect.h);

	float ratio = (float)sizeW / m_rect.w;
	m_rect.w = sizeW;
	m_rect.h *= ratio;
}

void GGameSprite::setSize(int w, int h) {
	m_rect.w = w;
	m_rect.h = h;
}

void GGameSprite::setX(int x, bool isPosChange) {
	m_rect.x = x;
	if (isPosChange)
		m_positionX = x;
}

void GGameSprite::setY(int y, bool isPosChange) {
	m_rect.y = y;
	if (isPosChange)
		m_positionY = y;
}

void  GGameSprite::centerX(int x, int w, bool isPosChange) {
	m_rect.x = x + (w - m_rect.w) / 2.f;
	if (isPosChange)
		m_positionX = m_rect.x;
}
void  GGameSprite::centerY(int y, int h, bool isPosChange) {
	m_rect.y = y + (h - m_rect.h) / 2.f;
	if (isPosChange)
		m_positionY = m_rect.y;
}

void GGameSprite::setScale(float s) {
	m_scale = s;
}

float GGameSprite::getScale() {
	return m_scale;
}

void GGameSprite::setFlashing(float delay, float duration)
{
	m_isFlashing = true;
	m_isFlashOn = false;
	m_flashDelay = delay;
	m_currentFlashDelay = m_flashDelay;
	m_flashDuration = duration;
}

void GGameSprite::stopFlashing()
{
}

bool GGameSprite::isEnd()
{
	return m_isEnd;
}

void GGameSprite::setIsEnd(bool ie)
{
	m_isEnd = ie;
}

Point GGameSprite::getCenterPoint()
{
	Point result;
	result.x = m_rect.x + m_rect.w / 2;
	result.y = m_rect.y + m_rect.h / 2;
	return result;
}

void GGameSprite::setAngle(double a)
{
	m_angle = a;
}

double GGameSprite::getAngle()
{
	return m_angle;
}

void GGameSprite::caclMoveSPeed(float & vx, float & vy, float ms, double &a, float dt)
{
	float moveSpeed = ms * dt;
	float distance = sqrt(powf(vx, 2) + powf(vy, 2));

	vx = vx / distance * moveSpeed;
	vy = vy / distance * moveSpeed;

	a = atan2(vy, vx) * 180.f / M_PI - 90;
}

float GGameSprite::getPositionX()
{
	return m_positionX;
}

float GGameSprite::getPositionY()
{
	return m_positionY;
}

void GGameSprite::setPositionX(float px)
{
	m_positionX = px;
}

void GGameSprite::setPositionY(float py)
{
	m_positionY = py;
}

void GGameSprite::moveBy(int vx, int vy, float ms, float dt, bool angleChange)
{
	float dx = m_rect.x + vx;
	float dy = m_rect.y + vy;
	moveTo(dx, dy, ms, dt, angleChange);
}

void GGameSprite::moveTo(int desx, int desy, float ms, float dt, bool angleChange)
{
	double tempAngle = m_angle;
	float vx = desx - m_positionX;
	float vy = desy - m_positionY;
	GGameSprite::caclMoveSPeed(vx, vy, ms, tempAngle, dt);
	if (angleChange) {
		m_angle = tempAngle;
	}
	m_positionX += vx;
	m_positionY += vy;

	setX(m_positionX);
	setY(m_positionY);
}

bool GGameSprite::isHidden()
{
	return m_isHidden;
}

void GGameSprite::setHidden(bool h)
{
	m_isHidden = h;
}

void GGameSprite::update(float dt)
{
	if (m_isFlashing) {
		m_currentFlashDelay -= dt;
		m_flashDuration -= dt;
		if (m_currentFlashDelay <= 0) {
			m_isFlashOn = !m_isFlashOn;
			m_currentFlashDelay = m_flashDelay;
		}
		if (m_flashDuration <= 0) {
			m_isFlashing = false;
		}
	}
}

void GGameSprite::render() {
	if (m_isHidden) {
		return;
	}

	if (m_isFlashing) {
		if (!m_isFlashOn) {
			return;
		}
	}
	Rect drawRect = Rect(m_rect);
	if (m_scale != 1) {
		drawRect.x += drawRect.w * (1 - m_scale) / 2;
		drawRect.y += drawRect.h * (1 - m_scale) / 2;
		drawRect.w *= m_scale;
		drawRect.h *= m_scale;
	}
	if (m_angle != 0) {
		fwRenderTextureEx(m_texture, NULL, &drawRect, m_angle);
	}
	else {
		fwRenderTexture(m_texture, NULL, &drawRect);
	}
}