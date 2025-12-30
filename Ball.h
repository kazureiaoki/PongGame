#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>
#include <random>

class Ball
{
private:
	sf::CircleShape shape;
	sf::Vector2f velocity;

	float baseSpeed = 400.f;
public:
	Ball(float x, float y, float radius)
	{
		shape.setRadius(radius);

		shape.setOrigin(sf::Vector2f(radius, radius));
		
		shape.setFillColor(sf::Color::White);
		
		shape.setPosition(sf::Vector2f(x, y));
		
		baseSpeed = 400.f;
		float angleRad = 30.f * 3.14159265f / 180.f;
		velocity.x = std::cos(angleRad) * baseSpeed;
		velocity.y = std::sin(angleRad) * baseSpeed;
	}

	// Ball's position update
	void update(float deltaTime, float windowWidth, float windowHeight)
	{
		// Movement: new position = old position + velocity * deltaTime
		shape.move(sf::Vector2f(velocity.x * deltaTime, velocity.y * deltaTime));

		// Current position
		sf::Vector2f pos = shape.getPosition();
		float radius = shape.getRadius();

		// Bouncing from the ceiling
		if (pos.y - radius < 0.f)
		{
			pos.y = radius;
			velocity.y = -velocity.y;
			shape.setPosition(pos);
		}

		// Bouncing from the bottom
		if (pos.y + radius > windowHeight)
		{
			pos.y = windowHeight - radius;
			velocity.y = -velocity.y;
			shape.setPosition(pos);
		}
	}

	// Paddle collision cheking and handling
	void checkCollision(sf::RectangleShape& paddle)
	{
		sf::FloatRect ballBounds = shape.getGlobalBounds();
		sf::FloatRect paddleBounds = paddle.getGlobalBounds();

		auto intersection = ballBounds.findIntersection(paddleBounds);
		if (!intersection)
		{
			return;
		}

		// Vertical ball's hit calculation
		const float paddleCenterY = paddleBounds.position.y + paddleBounds.size.y / 2.f;
		const float hitY = shape.getPosition().y;
		const float offset = hitY - paddleCenterY;

		// Normalization for rations [-1; 1]
		const float maxOffset = paddleBounds.size.y / 2.f;
		float normalized = 0.f;
		if (maxOffset > 0.f)
		{
			normalized = offset / maxOffset;
		}

		// Limitations (just in case)
		if (normalized < -1.f) normalized = -1.f;
		if (normalized > 1.f) normalized = 1.f;

		// Bounce angle from -45° to 45°
		const float maxAngleDeg = 45.f;
		float angleDeg = normalized * maxAngleDeg;
		float angleRad = angleDeg * 3.14159265f / 180.f;

		// Increasing velocity by little
		baseSpeed += 20.f;
		if (baseSpeed > 800.f)
		{
			baseSpeed = 800.f;
		}

		// Initializing direction by X axis after bouncing
		float dirX = (velocity.x > 0.f) ? -1.f : 1.f; // If went right, goes left after hit

		velocity.x = std::cos(angleRad) * baseSpeed * dirX;
		velocity.y = std::sin(angleDeg) * baseSpeed;

		// Pushing the ball out of racket, so it's not stuck
		const float radius = shape.getRadius();
		const float newY = shape.getPosition().y;

		if (dirX > 0.f)
		{
			// Goes right -> put rightish from the racket
			float paddleRight = paddleBounds.position.x + paddleBounds.size.x;
			float newX = paddleRight + radius;
			shape.setPosition(sf::Vector2f(newX, newY));
		}
		else
		{
			// Goes left -> put leftish from the racket
			float paddleLeft = paddleBounds.position.x;
			float newX = paddleLeft - radius;
			shape.setPosition(sf::Vector2f(newX, newY));
		}
	}

	// Checking goal:
	// -1 = goal for the left gates
	// +1 = goal for the right gates
	//  0 = no goal
	int checkGoal(float windowWidth)
	{
		sf::Vector2f pos = shape.getPosition();
		float radius = shape.getRadius();

		// Left wing
		if (pos.x + radius < 0.f)
		{
			return -1; // Player looses
		}

		// Right wing
		if (pos.x - radius > windowWidth)
		{
			return +1; // Bot looses
		}

		return 0; // Still in the ring
	}

	// Ball center reset with new speed
	void reset(float centerX, float centerY, int directionX)
	{
		shape.setPosition(sf::Vector2f(centerX, centerY));

		// Reducing speed after goal
		baseSpeed = 400.f;

		// Little randomized angle from -45° to 45°
		static std::random_device rd;
		static std::mt19937 rng(rd());
		std::uniform_real_distribution<float> distAngle(-45.f, 45.f);

		float angleDeg = distAngle(rng);
		float angleRad = angleDeg * 3.14159265f / 180.f;

		float dirX = static_cast<float>(directionX); // -1 or +1

		velocity.x = std::cos(angleRad) * baseSpeed * dirX;
		velocity.y = std::sin(angleRad) * baseSpeed;
	}

	void draw(sf::RenderWindow& window)
	{
		window.draw(shape);
	}

	void setVelocity(const sf::Vector2f& v)
	{
		velocity = v;
	}

	sf::CircleShape& getShape()
	{
		return shape;
	}

	sf::Vector2f getPosition() const
	{
		return shape.getPosition();
	}

	sf::Vector2f getVelocity() const
	{
		return velocity;
	}
};