#pragma once

class GameScreen
{
public:
	GameScreen();
	virtual ~GameScreen();

	virtual void OnKeyDown(int key);
	virtual void OnKeyUp(int key);

	virtual void update(float dt);
	virtual void render();

	virtual void screenDidShow();
	virtual void screenWillHide();

private:

};
