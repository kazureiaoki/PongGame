#include "TextObject.h"
#include "Constants.h"

using namespace PongConstants;

TextObject::TextObject(const sf::Font& font) 

	: m_font(&font)
	, m_text(font, "")
{
	m_text.setCharacterSize(FONT_SIZE_SCORE);
	m_text.setFillColor(sf::Color::Blue);
}

void TextObject::update(float deltaTime) {}

void TextObject::draw(sf::RenderWindow& window)
{
	if (!m_visible)
	{
		return;
	}

	if (isValid())
	{
		window.draw(m_text);
	}
}

void TextObject::setPosition(const sf::Vector2f& pos)
{
	m_text.setPosition(pos);
}

void TextObject::setPosition(float x, float y)
{
	setPosition({ x,y });
}

void TextObject::centerHorizontally(float windowWidth)
{
	if (!isValid()) { return; }

	sf::FloatRect bounds = m_text.getLocalBounds();
	float centerX = windowWidth / HALF_DIVISOR - bounds.size.x / HALF_DIVISOR;

	sf::Vector2f currentPos = m_text.getPosition();
	currentPos.x = centerX;
	m_text.setPosition(currentPos);
}

void TextObject::setCharacterSize(unsigned int size)
{
	m_text.setCharacterSize(size);
}

void TextObject::setColor(const sf::Color& color)
{
	m_text.setFillColor(color);
}

sf::Vector2f TextObject::getPosition() const
{
	return m_text.getPosition();
}

sf::FloatRect TextObject::getBounds() const
{
	return m_text.getGlobalBounds();
}