#pragma once

#include "GameObject.h"
#include <SFML/Graphics.hpp>

class Ball : public GameObject {
private:
    sf::CircleShape m_shape;
    float m_baseSpeed;
    float m_radius;

    static constexpr float PI = 3.14159265358979323846f;
    static constexpr float DEG_TO_RAD = PI / 180.0f;

public:
    Ball();

    void update(float deltaTime) override;
    void draw(sf::RenderWindow& window) override;

    void updatePhysics(float deltaTime, float windowWidth, float windowHeight);
    void checkCollision(const sf::FloatRect& bounds);
    int checkGoal(float windowWidth);

    void setRadius(float radius);
    void setColor(const sf::Color& color);
    void setSpeed(float speed);

    float getRadius() const { return m_radius; }
    float getSpeed() const { return m_baseSpeed; }

    sf::FloatRect getBounds() const;
};
