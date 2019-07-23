#include "EndStagePane.h"

#include "SharedVariables.h"
#include "GameConfigInfo.h"

EndStagePane::EndStagePane(int stg)
{
	auto titleStr = new std::string(NEXT_STAGE_TITLE);
	titleStr->append(std::to_string(stg));
	m_titleText = new TextDisplay(titleStr->c_str(), g_font, 100);
	delete titleStr;
	m_titleText->centerX(0, DEF_WIDTH);
	m_titleText->centerY(0, DEF_HEIGHT);

	m_descText = new TextDisplay(SKIP_DESC, g_font);
	m_descText->centerX(0, DEF_WIDTH);
	m_descText->setY(DEF_HEIGHT - m_descText->getRect().h - 10);
	m_descText->setFlashing(0.5, 10);

	m_rect.x = 0;
	m_rect.y = 0;
	m_rect.w = DEF_WIDTH;
	m_rect.h = DEF_HEIGHT;

	m_coverColor.r = 0;
	m_coverColor.g = 0;
	m_coverColor.b = 0;
	m_coverColor.a = 128;

}

EndStagePane::~EndStagePane()
{
	delete m_titleText;
	delete m_descText;
}

void EndStagePane::update(float dt)
{
	m_descText->update(dt);
}

void EndStagePane::render()
{
	fwFillRect(m_rect, m_coverColor);
	m_titleText->render();
	m_descText->render();
}

void EndStagePane::setNextStage(int stg)
{
	auto titleStr = new std::string(NEXT_STAGE_TITLE);
	titleStr->append(std::to_string(stg));
	m_titleText->setText(titleStr->c_str());
	m_titleText->centerX(0, DEF_WIDTH);
	delete titleStr;

	m_descText->setFlashing(0.5, 10);
}
