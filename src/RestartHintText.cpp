#include "RestartHintText.h"
#include "Constants.h"

using namespace PongConstants;

RestartHintText::RestartHintText(const sf::Font& font)
    : TextObject(font)
{
    m_text.setCharacterSize(FONT_SIZE_RESTART_HINT);
    m_text.setFillColor(sf::Color::Yellow);
    m_text.setString("Press R to restart");
}
