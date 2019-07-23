#pragma once
#include "GGameSprite.h"

class AnimationSprite : public GGameSprite
{
public:
	AnimationSprite(const char *fileName, int col, int row);
	~AnimationSprite();

	void setFrameDelay(float fd);
	float getFrameDelay();

	void  centerX(int x, int w);
	void  centerY(int y, int h);

	void update(float dt);
	void render();

	void setIsForeverLoop(bool isfl);
private:
	int m_animationFrameIndex = 0;
	Rect *m_animationFrames;
	int m_animationFrameCount;
	float m_currentFrameDelay = 1;
	float m_frameDelay = 1;
	bool m_foreverLoop;
};