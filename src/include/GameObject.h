#pragma once

#include <SFML/Graphics.hpp>

class GameObject {
protected:
	sf::Vector2f m_position{ 0.f,0.f };
	sf::Vector2f m_velocity{ 0.f,0.f };

public:
	GameObject() 
		: m_position(0.f, 0.f)
		, m_velocity(0.f, 0.f)	
	{}

	virtual ~GameObject() = default;

	virtual void update(float deltaTime) = 0;
	virtual void draw(sf::RenderWindow& window) = 0;

	void setPosition(const sf::Vector2f& pos) { m_position = pos; }
	void setPosition(float x, float y) { m_position = { x, y }; }

	void setVelocity(const sf::Vector2f& vel) { m_velocity = vel; }
	void setVelocity(float x, float y) { m_velocity = { x, y }; }

	sf::Vector2f getPosition() const { return m_position; }
	sf::Vector2f getVelocity() const { return m_velocity; }
};