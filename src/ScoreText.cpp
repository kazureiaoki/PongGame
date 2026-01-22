#include "ScoreText.h"

ScoreText::ScoreText(const sf::Font& font)
	: TextObject(font)
{
	setColor(sf::Color::Blue);
	setScore(0, 0);
}

void ScoreText::setScore(int playerScore, int botScore) 
{
	if (!m_text) { return; }

	std::string scoreStr = std::to_string(playerScore) + " : " + std::to_string(botScore);
	m_text->setString(scoreStr);
}