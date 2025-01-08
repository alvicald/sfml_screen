#ifndef MULTICOLORED_SCREEN_H_
#define MULTICOLORED_SCREEN_H_

#include <cstdint>
#include <tuple>

#include <SFML/Graphics/Color.hpp>

namespace sf {

//! sf::RenderWindow forward declaration
class RenderWindow;

}

namespace screen {

class ColorChangingScreen
{
public:
    //! On/off change color
    void change_state() noexcept;

    //! Draw the current color on Render Window
    void draw(::sf::RenderWindow&);

    ::sf::Color const& get_color() const noexcept;

private:
    //! Colors(red, green, blue, alpha)
    ::sf::Color m_colors { 255, 0, 0 };

    //! State flag of change color working
    bool m_enable_multicolored_screen { false };
};

} // namespace screen
#endif // MULTICOLORED_SCREEN_H_
