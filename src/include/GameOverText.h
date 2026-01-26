#pragma once

#include "TextObject.h"

#include <SFML/Graphics.hpp>
#include <string>

class GameOverText : public TextObject {
public:
    explicit GameOverText(const sf::Font& font);

    void setMessage(const std::string& message);
};
