#pragma once

#include "TextObject.h"

class ScoreText : public TextObject {
private:
	int m_playerScore{ 0 };
	int m_botScore{ 0 };

	void updateScoreText();

public:
	explicit ScoreText(const sf::Font& font);

	void addPlayerPoint();
	void addBotPoint();
	void reset();

	int getPlayerScore() const { return m_playerScore; }
	int getBotScore() const { return m_botScore; }
};