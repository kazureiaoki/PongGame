#pragma once
#include <SFML/Graphics.hpp> 

// Racket class
class Paddle
{
private:
    sf::RectangleShape shape;
    float speed;

public:
    Paddle(float x, float y)
    {
        // sf::Vector2f - two dimensional vector with two float (x і y)
        shape.setSize(sf::Vector2f(20.f, 100.f));

        shape.setFillColor(sf::Color::Green);

        // Start racket position
        shape.setPosition(sf::Vector2f(x, y));

        speed = 500.f;
    }

    // Racket movement: direction = -1 (up), 0 (still), +1 (down)
    void move(float direction, float deltaTime)
    {
        shape.move(sf::Vector2f(0.f, direction * speed * deltaTime));
    }

    // Racket drawing on the screen
    void draw(sf::RenderWindow& window)
    {
        window.draw(shape);
    }

    void clampToWindow(float windowHeight)
    {
        if (shape.getPosition().y < 0.f)
        {
            shape.setPosition(sf::Vector2f(shape.getPosition().x, 0.f));
        }

        if (shape.getPosition().y + shape.getSize().y > windowHeight)
        {
            shape.setPosition(sf::Vector2(shape.getPosition().x, windowHeight - shape.getSize().y));
        }
    }

    // Shape access (for collisions)
    sf::RectangleShape& getShape()
    {
        return shape;
    }

    sf::Vector2f getPosition() const
    {
        return shape.getPosition();
    }
};