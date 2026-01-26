#pragma once

#include "GameObject.h"

#include <SFML/Graphics.hpp>

enum class FieldCollision
{
    None,
    TopWall,
    BottomWall,
    BotGoal,
    PlayerGoal
};

class Ball : public GameObject {
private:
    sf::CircleShape m_shape;
    float m_baseSpeed{ 0.f };

public:
    Ball();

    void update(float deltaTime) override;
    void draw(sf::RenderWindow& window) override;

    void setPosition(const sf::Vector2f& pos) override;
    void setPosition(float x, float y) override;
    sf::Vector2f getPosition() const override;

    void setColor(const sf::Color& color) override;
    sf::FloatRect getBounds() const override;

    FieldCollision handleFieldCollision(const sf::FloatRect& fieldBounds);
    void handlePaddleCollision(const sf::FloatRect& paddleBounds);

    void setRadius(float radius);
    float getRadius() const { return m_shape.getRadius(); }

    void setSpeed(float speed);
    float getSpeed() const { return m_baseSpeed; }

    float updateVelocity(float speed, float angleDeg);
};