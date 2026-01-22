#pragma once

#include "GameObject.h"
#include <SFML/Graphics.hpp>
#include <memory>
#include <string>

class TextObject : public GameObject {
protected:
	std::unique_ptr<sf::Text> m_text;
	const sf::Font* m_font;

public:
	explicit TextObject(const sf::Font& font);

	virtual ~TextObject() = default;

	void update(float deltaTime) override;
	void draw(sf::RenderWindow& window) override;

	void centerHorizontally(float windowWidth);
	void setCharacterSize(unsigned int size);
	void setColor(const sf::Color& color);

	bool isValid() const { return m_font != nullptr && m_text != nullptr; }
};