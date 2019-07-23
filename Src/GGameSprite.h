#pragma once
#include "Framework.h"

class GGameSprite
{
public:
	GGameSprite();
	virtual ~GGameSprite();
	GGameSprite(const char *fileName, int sizeWidth = 0);
	
	Rect getRect();

	void setTexture(const char *fileName);

	void setX(int x, bool isPosChange = false);
	void setY(int y, bool isPosChange = false);

	void  centerX(int x, int w, bool isPosChange = false);
	void  centerY(int y, int h, bool isPosChange = false);

	virtual void update(float dt);
	virtual void render();

	void setSize(int w, int h);

	void setScale(float s);
	float getScale();
	
	void setFlashing(float delay, float duration);
	void stopFlashing();

	virtual bool isEnd();
	virtual void setIsEnd(bool ie);

	Point getCenterPoint();

	// rotation
	void setAngle(double a);
	double getAngle();


	float getPositionX();
	float getPositionY();
	void setPositionX(float px);
	void setPositionY(float py);

	void moveBy(int vx, int vy, float ms, float dt, bool angleChange = false);
	void moveTo(int desx, int desy, float ms, float dt, bool angleChange = false);

	bool isHidden();
	void setHidden(bool h);

protected:
	Texture *m_texture = nullptr;
	Rect m_rect;
	float m_scale = 1;

	bool m_isFlashing = false;
	bool m_isFlashOn = true;
	float m_flashDelay = 0;
	float m_currentFlashDelay = 0;
	float m_flashDuration = 0;

	double m_angle = 0;

	bool m_isEnd = false;

	float m_positionX, m_positionY;

	bool m_isHidden = false;

	void caclMoveSPeed(float &vx, float &vy, float ms, double &a, float dt);
};