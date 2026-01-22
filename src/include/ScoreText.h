#pragma once

#include "TextObject.h"

class ScoreText : public TextObject {
public:
	explicit ScoreText(const sf::Font& font);

	void setScore(int playerScore, int botScore);
};