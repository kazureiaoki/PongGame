#pragma once

#include "GameObject.h"

#include <SFML/Graphics.hpp>
#include <memory>

class TextObject : public GameObject {
protected:
	sf::Text m_text;
	const sf::Font* m_font;

public:
	explicit TextObject(const sf::Font& font);

	void update(float deltaTime) override;
	void draw(sf::RenderWindow& window) override;

	void setPosition(const sf::Vector2f& pos) override;
	void setPosition(float x, float y) override;
	sf::Vector2f getPosition() const override;

	void setColor(const sf::Color& color) override;
	sf::FloatRect getBounds() const override;

	void centerHorizontally(float windowWidth);
	void setCharacterSize(unsigned int size);

	bool isValid() const { return m_font != nullptr; }
};