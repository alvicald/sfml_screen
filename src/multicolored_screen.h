#ifndef MULTICOLORED_SCREEN_H_
#define MULTICOLORED_SCREEN_H_

#include <cstdint>
#include <tuple>

namespace screen {

struct color_changing_screen
{
    static void change_state()
    {
        enable_multicolored_screen = !enable_multicolored_screen;
    }

    static bool get_state()
    {
        return enable_multicolored_screen;
    }

    std::tuple<std::uint8_t, std::uint8_t, std::uint8_t> operator()()
    {
        if (enable_multicolored_screen)
        {
            if (red == 255 && green <= 255 && blue == 0) ++green;
            if (red >= 0 && green == 255 && blue == 0) --red;
            if (red == 0 && green == 255 && blue <= 255) ++blue;
            if (red == 0 && green <= 255 && blue == 255) --green;
            if (red <= 255 && green == 0 && blue == 255) ++red;
            if (red == 255 && green == 0 && blue >= 0) --blue;
        }

        return std::make_tuple(red, green, blue);
    }
private:
    static std::uint8_t red, green, blue;
    static bool enable_multicolored_screen;
};

bool color_changing_screen::enable_multicolored_screen { false };
std::uint8_t color_changing_screen::red { 255 };
std::uint8_t color_changing_screen::green { 0 } ;
std::uint8_t color_changing_screen::blue { 0 };

} // namespace screen
#endif // MULTICOLORED_SCREEN_H_
