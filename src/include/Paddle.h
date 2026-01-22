#pragma once

#include "GameObject.h"
#include <SFML/Graphics.hpp>

class Paddle : public GameObject {
private:
    sf::RectangleShape m_shape;
    float m_speed;
    sf::Vector2f m_size;

public:
    Paddle();

    void update(float deltaTime) override;
    void draw(sf::RenderWindow& window) override;

    void clampToWindow(float windowHeight);

    void setSize(const sf::Vector2f& size);
    void setSize(float width, float height);
    void setColor(const sf::Color& color);
    void setSpeed(float speed);

    float getSpeed() const { return m_speed; }    
    sf::Vector2f getSize() const { return m_size; }
    sf::FloatRect getBounds() const;
};
