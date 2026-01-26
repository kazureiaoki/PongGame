#include "GameOverText.h"
#include "Constants.h"

#include <SFML/Graphics.hpp>

using namespace PongConstants;

GameOverText::GameOverText(const sf::Font& font)
	: TextObject(font)
{
	m_text.setCharacterSize(FONT_SIZE_GAME_OVER);
	m_text.setFillColor(sf::Color::Red);
}

void GameOverText::setMessage(const std::string& message) 
{
	m_text.setString(message);
}