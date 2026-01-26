#pragma once

#include <SFML/Graphics.hpp>

class GameObject {
protected:
	sf::Vector2f m_velocity;
	bool m_visible{ true };

public:
	GameObject() = default;
	virtual ~GameObject() = default;

	virtual void update(float deltaTime) = 0;
	virtual void draw(sf::RenderWindow& window) = 0;

	virtual void setPosition(const sf::Vector2f& pos) = 0;
	virtual void setPosition(float x, float y) = 0;
	virtual sf::Vector2f getPosition() const = 0;

	virtual void setColor(const sf::Color& color) = 0;
	virtual sf::FloatRect getBounds() const = 0;

	virtual void setVelocity(const sf::Vector2f& vel) { m_velocity = vel; }
	virtual void setVelocity(float x, float y) { m_velocity = { x, y }; }
	sf::Vector2f getVelocity() const { return m_velocity; }

	bool isVisible() const { return m_visible; }
	void setVisible(bool visible) { m_visible = visible; }
};