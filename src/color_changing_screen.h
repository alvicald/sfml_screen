#ifndef MULTICOLORED_SCREEN_H_
#define MULTICOLORED_SCREEN_H_

#include <cstdint>
#include <tuple>

namespace sf {
    class RenderWindow;
}

namespace screen {

class ColorChangingScreen
{
public:
    void change_state() noexcept;

    void draw(::sf::RenderWindow&);

private:
    std::uint8_t m_red { 255 }; 
    std::uint8_t m_green { 0 };
    std::uint8_t m_blue { 0 };
    bool m_enable_multicolored_screen { false };
};

} // namespace screen
#endif // MULTICOLORED_SCREEN_H_
