#include "GameplayBackground.h"

GameplayBackground::GameplayBackground()
{
	m_stars = new std::vector<Star*>;
	m_maxStarCount = 30;
	m_minSpeed = 0.5f;
	m_maxSpeed = 0.7f;
}

GameplayBackground::~GameplayBackground()
{
	for (auto star : *m_stars) {
		delete star;
	}
	delete m_stars;
}

void GameplayBackground::update(float dt)
{
	if (m_stars->size() < m_maxStarCount) {
		auto star = new Star();
		int random = 1 + rand() % 99;
		star->setSpeed(m_minSpeed + (m_maxSpeed - m_minSpeed)*(float)random / 100);
		m_stars->push_back(star);
	}
	auto endStars = new std::vector<Star*>;
	for (auto star : *m_stars) {
		star->update(dt);
		if (star->isEnd()) {
			endStars->push_back(star);
		}
	}
	for (auto star : *endStars) {
		auto itr = std::find(m_stars->begin(), m_stars->end(), star);
		if (itr != m_stars->end()) {
			m_stars->erase(itr);
		}
		delete star;
	}
	delete endStars;
}

void GameplayBackground::render()
{
	for (auto star : *m_stars) {
		star->render();
	}
}

void GameplayBackground::setSpeed(float min, float max)
{
	m_minSpeed = min;
	m_maxSpeed = max;
	for (auto star : *m_stars) {
		int random = 1 + rand() % 99;
		star->setSpeed(m_minSpeed + (m_maxSpeed - m_minSpeed)*(float)random / 100);
	}
}
