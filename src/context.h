#ifndef CONTEXT_H_
#define CONTEXT_H_

#include <cstdint>
#include <string>

namespace screen {

class ScreenContext
{
public:
    explicit ScreenContext(char const*);

private:
    friend class Screen;

    //! Screen width
    std::uint32_t m_screen_width { 0 };

    //! Screen height
    std::uint32_t m_screen_height { 0 };

    //! Fullscreen mode
    bool m_is_fullscreen{ false };
};

} // namespace screen

#endif // CONTEXT_H_
