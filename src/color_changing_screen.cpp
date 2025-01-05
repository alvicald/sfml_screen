#include <color_changing_screen.h>

#include <SFML/Graphics/RenderWindow.hpp>

namespace screen {

void ColorChangingScreen::change_state() noexcept
{
    m_enable_multicolored_screen = !m_enable_multicolored_screen;
}

void ColorChangingScreen::draw(::sf::RenderWindow& window)
{
    if (m_enable_multicolored_screen)
    {
        if (m_red == 255 && m_green <= 255 && m_blue == 0) ++m_green;
        if (m_red >= 0 && m_green == 255 && m_blue == 0) --m_red;
        if (m_red == 0 && m_green == 255 && m_blue <= 255) ++m_blue;
        if (m_red == 0 && m_green <= 255 && m_blue == 255) --m_green;
        if (m_red <= 255 && m_green == 0 && m_blue == 255) ++m_red;
        if (m_red == 255 && m_green == 0 && m_blue >= 0) --m_blue;

        window.clear(::sf::Color {m_red, m_green, m_blue});
    }
    else
        window.clear(::sf::Color{0, 0, 0});
}
} // namespace screen
