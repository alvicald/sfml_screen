#ifndef MULTICOLORED_SCREEN_H_
#define MULTICOLORED_SCREEN_H_

#include <cstdint>
#include <tuple>

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

private:
    //! Red color
    std::uint8_t m_red { 255 };

    //! Green color
    std::uint8_t m_green { 0 };

    //! Blue color
    std::uint8_t m_blue { 0 };

    //! State flag of change color working
    bool m_enable_multicolored_screen { false };
};

} // namespace screen
#endif // MULTICOLORED_SCREEN_H_
