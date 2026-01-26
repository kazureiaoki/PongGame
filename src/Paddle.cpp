#include "Paddle.h"

#include <algorithm>

Paddle::Paddle()
    : m_speed(0.f)
{
    m_shape.setFillColor(sf::Color::White);
}

void Paddle::update(float deltaTime) 
{
    const sf::Vector2f currentPos = m_shape.getPosition();
    const sf::Vector2f newPos = currentPos + m_velocity * deltaTime;

    m_shape.setPosition(newPos);
}

void Paddle::draw(sf::RenderWindow& window) 
{
    if (!m_visible)
    {
        return;
    }

    window.draw(m_shape);
}

void Paddle::setPosition(const sf::Vector2f& pos)
{
    m_shape.setPosition(pos);
}

void Paddle::setPosition(float x, float y)
{
    m_shape.setPosition({ x, y });
}

void Paddle::clampToWindow(const float windowHeight) 
{
    sf::Vector2f pos = m_shape.getPosition();
    const sf::Vector2f size = m_shape.getSize();

    if (pos.y < 0.f)
    {
        pos.y = 0.f;
    }

    if (pos.y + size.y > windowHeight)
    {
        pos.y = windowHeight - size.y;
    }

    m_shape.setPosition(pos);
}

void Paddle::setSize(const sf::Vector2f& size)
{
    m_shape.setSize(size);
}

void Paddle::setSize(float width, float height)
{
    setSize({ width, height });
}

void Paddle::setColor(const sf::Color& color) 
{
    m_shape.setFillColor(color);
}

void Paddle::setSpeed(float speed)
{
    m_speed = speed;
}

sf::Vector2f Paddle::getPosition() const
{
    return m_shape.getPosition();
}

sf::FloatRect Paddle::getBounds() const 
{
    return m_shape.getGlobalBounds();
}