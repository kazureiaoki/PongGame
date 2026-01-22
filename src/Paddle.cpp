#include "Paddle.h"
#include <SFML/Graphics.hpp>

Paddle::Paddle()
    : m_speed(0.f)
    , m_size(0.f, 0.f)
{
    m_shape.setSize({ 0.f,0.f });
    m_shape.setPosition({ 0.f,0.f });
    m_shape.setFillColor(sf::Color::White);
}

void Paddle::update(float deltaTime) 
{
    m_position += m_velocity * deltaTime;
    m_shape.setPosition(m_position);
}

void Paddle::draw(sf::RenderWindow& window) 
{
    window.draw(m_shape);
}

void Paddle::clampToWindow(float windowHeight) 
{
    if (m_position.y < 0.f) 
    {
        m_position.y = 0.f;
    }

    if (m_position.y + m_size.y > windowHeight) 
    {
        m_position.y = windowHeight - m_size.y;
    }

    m_shape.setPosition(m_position);
}

void Paddle::setSize(const sf::Vector2f& size)
{
    m_size = size;
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

sf::FloatRect Paddle::getBounds() const {
    return m_shape.getGlobalBounds();
}