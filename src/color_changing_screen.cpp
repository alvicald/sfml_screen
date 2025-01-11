#include <color_changing_screen.h>

#include <SFML/Graphics/RenderWindow.hpp>

namespace screen {

void ColorChangingScreen::change_state() noexcept
{
    m_enable_multicolored_screen = !m_enable_multicolored_screen;
}

void ColorChangingScreen::draw(sf::RenderWindow& window)
{
    if (m_enable_multicolored_screen)
    {
        if (m_colors.r == 255 && m_colors.g <= 255 && m_colors.b == 0) ++m_colors.g;
        if (m_colors.r >= 0 && m_colors.g == 255 && m_colors.b == 0) --m_colors.r;
        if (m_colors.r == 0 && m_colors.g == 255 && m_colors.b <= 255) ++m_colors.b;
        if (m_colors.r == 0 && m_colors.g <= 255 && m_colors.b == 255) --m_colors.g;
        if (m_colors.r <= 255 && m_colors.g == 0 && m_colors.b == 255) ++m_colors.r;
        if (m_colors.r == 255 && m_colors.g == 0 && m_colors.b >= 0) --m_colors.b;

        window.clear(m_colors);
    }
}

sf::Color const& ColorChangingScreen::get_color() const noexcept
{
    return m_colors;
}

} // namespace screen
