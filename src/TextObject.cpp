#include "TextObject.h"
#include "Constants.h"
#include <SFML/Graphics.hpp>

using namespace PongConstants;

TextObject::TextObject(const sf::Font& font) 

	: m_font(&font)
	, m_text(std::make_unique<sf::Text>(font))
{
	m_text->setCharacterSize(FONT_SIZE_SCORE);
	m_text->setFillColor(sf::Color::Blue);
	m_text->setString("");
	m_text->setPosition({ 0.f, 0.f });
}

void TextObject::update(float deltaTime)
{
	if (m_text)
	{
		m_text->setPosition(m_position);
	}
}

void TextObject::draw(sf::RenderWindow& window)
{
	if (isValid())
	{
		window.draw(*m_text);
	}
}

void TextObject::centerHorizontally(float windowWidth)
{
	if (!isValid()) { return; }

	sf::FloatRect bounds = m_text->getLocalBounds();

	float centerX = windowWidth / 2.f - bounds.size.x / 2.f;

	m_position.x = centerX;
	m_text->setPosition(m_position);
}

void TextObject::setCharacterSize(unsigned int size)
{
	if (m_text) 
	{
		m_text->setCharacterSize(size);
	}
}

void TextObject::setColor(const sf::Color& color)
{
	if (m_text) 
	{
		m_text->setFillColor(color);
	}
}