#include "GameScreen.h"
#include "GGameSprite.h"

#include <vector>

#include "MainMenuItem.h"

class MainMenuScreen : public GameScreen
{
public:
	MainMenuScreen();
	~MainMenuScreen();

	void OnKeyDown(int key);

	void update(float dt);

	void render();

private:
	GGameSprite *m_background, *m_logo, *m_itemPointer;
	std::vector<MainMenuItem*> *m_items;
	int m_selectingIndex = 0;
	std::vector<std::string*> *m_logoNames;
	float m_logoDelay;
	float m_logoIndex;
};