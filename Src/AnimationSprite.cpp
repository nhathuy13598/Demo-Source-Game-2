#include "AnimationSprite.h"

AnimationSprite::AnimationSprite(const char *fileName, int col, int row) : GGameSprite(fileName)
{
	m_animationFrameCount = col * row;
	m_animationFrames = new Rect[m_animationFrameCount];
	int frameWidth = m_rect.w / col;
	int frameHeight = m_rect.h / row;
	for (int r = 0; r < row; r++) {
		for (int c = 0; c < col; c++) {
			Rect frame;
			frame.x = c * frameWidth;
			frame.y = r * frameHeight;
			frame.w = frameWidth;
			frame.h = frameHeight;
			m_animationFrames[r * col + c] = frame;
		}
	}
	m_foreverLoop = false;
	m_rect.w = 200;
	m_rect.h = 200;
}

AnimationSprite::~AnimationSprite()
{
	delete[] m_animationFrames;
}

void AnimationSprite::setFrameDelay(float fd)
{
	m_frameDelay = fd;
	m_currentFrameDelay = m_frameDelay;
}

float AnimationSprite::getFrameDelay()
{
	return m_frameDelay;
}

void AnimationSprite::centerX(int x, int w)
{
	m_rect.x = x + (w - m_rect.w) / 2;
}

void AnimationSprite::centerY(int y, int h)
{
	m_rect.y = y + (h - m_rect.h) / 2;
}

void AnimationSprite::update(float dt) {
	if (m_isEnd) {
		return;
	}
	GGameSprite::update(dt);
	m_currentFrameDelay -= dt;
	if (m_currentFrameDelay <= 0) {
		m_currentFrameDelay = m_frameDelay;
		m_animationFrameIndex++;
		if (m_animationFrameIndex >= m_animationFrameCount) {
			if (m_foreverLoop) {
				m_animationFrameIndex = 0;
			}
			else {
				m_isEnd = true;
			}
		}
	}
}

void AnimationSprite::render() {
	if (!m_isEnd)
		fwRenderTexture(m_texture, &m_animationFrames[m_animationFrameIndex], &m_rect);
}

void AnimationSprite::setIsForeverLoop(bool isfl)
{
	m_foreverLoop = isfl;
}
