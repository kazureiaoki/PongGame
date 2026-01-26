#include "Ball.h"
#include "Constants.h"

#include <cmath>
#include <algorithm>

using namespace PongConstants;

Ball::Ball()
    : m_baseSpeed(0.f)
{
    m_shape.setFillColor(sf::Color::White);
}

void Ball::update(float deltaTime) 
{
    const sf::Vector2f currentPos = m_shape.getPosition();
    const sf::Vector2f newPos = currentPos + m_velocity * deltaTime;

    m_shape.setPosition(newPos);
}

void Ball::draw(sf::RenderWindow& window) 
{
    if (!m_visible)
    {
        return;
    }

    window.draw(m_shape);
}

FieldCollision Ball::handleFieldCollision(const sf::FloatRect& fieldBounds)
{
    sf::Vector2f pos = m_shape.getPosition();
    const float radius = m_shape.getRadius();

    if (pos.x + radius < fieldBounds.position.x)
    {
        return FieldCollision::BotGoal;
    }

    if (pos.x - radius > fieldBounds.position.x + fieldBounds.size.x)
    {
        return FieldCollision::PlayerGoal;
    }

    FieldCollision result = FieldCollision::None;

    if (pos.y - radius < fieldBounds.position.y)
    {
        pos.y = fieldBounds.position.y + radius;

        m_velocity.y = -m_velocity.y;

        result = FieldCollision::TopWall;
    }

    if (pos.y + radius > fieldBounds.position.y + fieldBounds.size.y)
    {
        pos.y = fieldBounds.position.y + fieldBounds.size.y - radius;
        
        m_velocity.y = -m_velocity.y;

        result = FieldCollision::BottomWall;
    }

    m_shape.setPosition(pos);

    return result;
}

void Ball::handlePaddleCollision(const sf::FloatRect& paddleBounds)
{
    const sf::FloatRect ballBounds = m_shape.getGlobalBounds();
    const auto intersection = ballBounds.findIntersection(paddleBounds);

    if (!intersection)
    {
        return;
    }

    const float paddleCenterY = paddleBounds.position.y + paddleBounds.size.y / HALF_DIVISOR;
    const float hitY = m_shape.getPosition().y;
    const float offset = hitY - paddleCenterY;

    const float maxOffset = paddleBounds.size.y / HALF_DIVISOR;
    float normalized = (maxOffset > 0.f) ? (offset / maxOffset) : 0.f;
    normalized = std::clamp(normalized, -1.f, 1.f);

    m_baseSpeed += BALL_SPEED_INCREMENT;

    if (m_baseSpeed > BALL_MAX_SPEED)
    {
        m_baseSpeed = BALL_MAX_SPEED;
    }

    const float angleDeg = normalized * BALL_MAX_BOUNCE_ANGLE_DEG;
    const float dirX = updateVelocity(m_baseSpeed, angleDeg);

    sf::Vector2f pos = m_shape.getPosition();
    const float radius = m_shape.getRadius();

    if (dirX > 0.f)
    {
        pos.x = paddleBounds.position.x + paddleBounds.size.x + radius;
    } else {
        pos.x = paddleBounds.position.x - radius;
    }

    m_shape.setPosition(pos);
}

void Ball::setRadius(float radius)
{
    m_shape.setRadius(radius);
    m_shape.setOrigin({ radius, radius });
}

void Ball::setColor(const sf::Color& color)
{
    m_shape.setFillColor(color);
}

void Ball::setSpeed(float speed)
{
    m_baseSpeed = speed;

    if (m_velocity.x != 0.f || m_velocity.y != 0.f)
    {
        const float currentSpeed = std::sqrt(m_velocity.x * m_velocity.x + m_velocity.y * m_velocity.y);

        if (currentSpeed > 0.f)
        {
            m_velocity = (m_velocity / currentSpeed) * m_baseSpeed;
        }
    }
}

float Ball::updateVelocity(float speed, float angleDeg)
{
    const float angleRad = angleDeg * DEG_TO_RAD;
    const float dirX = (m_velocity.x > 0.f) ? -1.f : 1.f;
    
    m_velocity.x = std::cos(angleRad) * speed * dirX;
    m_velocity.y = std::sin(angleRad) * speed;

    return dirX;
}

void Ball::setPosition(const sf::Vector2f& pos)
{
    m_shape.setPosition(pos);
}

void Ball::setPosition(float x, float y)
{
    m_shape.setPosition({ x, y });
}

sf::Vector2f Ball::getPosition() const
{
    return m_shape.getPosition();
}

sf::FloatRect Ball::getBounds() const {
    return m_shape.getGlobalBounds();
}