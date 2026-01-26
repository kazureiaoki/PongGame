#include "ScoreText.h"

ScoreText::ScoreText(const sf::Font& font)
	: TextObject(font)
	, m_playerScore(0)
	, m_botScore(0)
{
	setColor(sf::Color::Blue);
	updateScoreText();
}

void ScoreText::addPlayerPoint()
{
	++m_playerScore;
	updateScoreText();
}

void ScoreText::addBotPoint()
{
	++m_botScore;
	updateScoreText();
}

void ScoreText::reset()
{
	m_playerScore = 0;
	m_botScore = 0;
	updateScoreText();
}

void ScoreText::updateScoreText()
{
	std::string scoreStr = std::to_string(m_playerScore) + " : " + std::to_string(m_botScore);
	m_text.setString(scoreStr);
}