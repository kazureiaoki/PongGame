#include "Ball.h"
#include "Constants.h"
#include <SFML/Graphics.hpp>
#include <cmath>
#include <algorithm>

using namespace PongConstants;

Ball::Ball()
    : m_baseSpeed(0.f)
    , m_radius(0.f)
{
    m_shape.setRadius(0.f);
    m_shape.setPosition({ 0.f, 0.f });
    m_shape.setFillColor(sf::Color::White);
    m_shape.setOrigin(sf::Vector2f(0.f, 0.f));
}

void Ball::update(float deltaTime) 
{
    m_position += m_velocity * deltaTime;
    m_shape.setPosition(m_position);
}

void Ball::draw(sf::RenderWindow& window) 
{
    window.draw(m_shape);
}

void Ball::updatePhysics(float deltaTime, float windowWidth, float windowHeight) 
{
    if (m_position.y - m_radius < 0.f) 
    {
        m_position.y = m_radius;
        m_velocity.y = -m_velocity.y;
    }

    if (m_position.y + m_radius > windowHeight) 
    {
        m_position.y = windowHeight - m_radius;
        m_velocity.y = -m_velocity.y;
    }

    m_shape.setPosition(m_position);
}

void Ball::checkCollision(const sf::FloatRect& paddleBounds) 
{
    sf::FloatRect ballBounds = m_shape.getGlobalBounds();
    auto intersection = ballBounds.findIntersection(paddleBounds);

    if (!intersection) { return; }

    const float paddleCenterY = paddleBounds.position.y + paddleBounds.size.y / 2.f;
    const float hitY = m_shape.getPosition().y;
    const float offset = hitY - paddleCenterY;
    const float maxOffset = paddleBounds.size.y / 2.f;

    float normalized = (maxOffset > 0.f) ? (offset / maxOffset) : 0.f;
    normalized = std::clamp(normalized, -1.f, 1.f);

    float angleDeg = normalized * BALL_MAX_BOUNCE_ANGLE_DEG;
    float angleRad = angleDeg * DEG_TO_RAD;

    m_baseSpeed += BALL_SPEED_INCREMENT;
    if (m_baseSpeed > BALL_MAX_SPEED) 
    {
        m_baseSpeed = BALL_MAX_SPEED;
    }

    float dirX = (m_velocity.x > 0.f) ? -1.f : 1.f;
    m_velocity.x = std::cos(angleRad) * m_baseSpeed * dirX;
    m_velocity.y = std::sin(angleRad) * m_baseSpeed;

    if (dirX > 0.f) 
    {
        m_position.x = paddleBounds.position.x + paddleBounds.size.x + m_radius;
    } else {
        m_position.x = paddleBounds.position.x - m_radius;
    }

    m_shape.setPosition(m_position);
}

int Ball::checkGoal(float windowWidth) 
{
    if (m_position.x + m_radius < 0.f) 
    {
        return -1;
    }

    if (m_position.x - m_radius > windowWidth) 
    {
        return +1;
    }

    return 0;
}

void Ball::setRadius(float radius)
{
    m_radius = radius;
    m_shape.setRadius(radius);
    m_shape.setOrigin(sf::Vector2f(radius, radius));
}

void Ball::setColor(const sf::Color& color)
{
    m_shape.setFillColor(color);
}

void Ball::setSpeed(float speed)
{
    m_baseSpeed = speed;

    if (m_velocity.x !=0.f || m_velocity.y !=0.f)
    {
        float currentSpeed = std::sqrt(m_velocity.x * m_velocity.x + m_velocity.y * m_velocity.y);

        if (currentSpeed > 0.f)
        {
            m_velocity = (m_velocity / currentSpeed) * m_baseSpeed;
        }
    }
}

sf::FloatRect Ball::getBounds() const {
    return m_shape.getGlobalBounds();
}