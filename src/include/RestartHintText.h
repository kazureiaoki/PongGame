#pragma once

#include "TextObject.h"
#include <SFML/Graphics.hpp>

class RestartHintText : public TextObject {
public:
    explicit RestartHintText(const sf::Font& font);

    void show();
    void hide();
};
