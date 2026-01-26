#pragma once

#include "GameObject.h"

#include <SFML/Graphics.hpp>

class Paddle : public GameObject {
private:
    sf::RectangleShape m_shape;
    float m_speed{ 0.f };

public:
    Paddle();

    void update(float deltaTime) override;
    void draw(sf::RenderWindow& window) override;

    void setPosition(const sf::Vector2f& pos) override;
    void setPosition(float x, float y) override;
    sf::Vector2f getPosition() const override;

    void setColor(const sf::Color& color) override;
    sf::FloatRect getBounds() const override;

    void clampToWindow(const float windowHeight);

    void setSpeed(float speed);
    void setSize(const sf::Vector2f& size);
    void setSize(float width, float height);

    float getSpeed() const { return m_speed; }
    sf::Vector2f getSize() const { return m_shape.getSize(); }
};
