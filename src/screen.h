#ifndef SCREEN_H_
#define SCREEN_H_

#include <memory>
#include <functional>

#include <context.h>
#include <color_changing_screen.h>
#include <gradient_screen.h>

#include <SFML/System/Time.hpp>

namespace sf {

//! sf::RenderWindow forward declaration
class RenderWindow;

//! sf::Text forward declaration
class Text;

//! sf::Font forward declaration
class Font;

} // namespace sf

namespace screen {

//! Menu forward declaration
class Menu;

class Screen
{
public:
    explicit Screen(ScreenContext const&);

    //! Run the screen program
    void run();

private:
    //! Update of window events
    void updateEvent();

    //! Update and print time and fps statistic
    void updateStatistic(sf::Time);

    //! Render all window elements
    void render();

    //! Update all screen modules
    void update(sf::Time);

private:
    //! Deleter of sf::RenderWindow pointer
    struct render_window_deleter
    {
        void operator()(sf::RenderWindow* ptr) noexcept
        {
            if (ptr != nullptr)
                free_screen(ptr);
        }
    private:
        void free_screen(sf::RenderWindow*);
    };

    //! Deleter of sf::Text pointer
    struct text_deleter
    {
        void operator()(sf::Text* ptr) noexcept
        {
            if (ptr != nullptr)
                free_text(ptr);
        }
    private:
        void free_text(sf::Text*);
    };

    //! Deleter of sf::Font pointer
    struct font_deleter
    {
        void operator()(sf::Font* ptr) noexcept
        {
            if (ptr != nullptr)
                free_font(ptr);
        }
    private:
        void free_font(sf::Font*);
    };

    //! Deleter of sf::Font pointer
    struct menu_deleter
    {
        void operator()(Menu* ptr) noexcept
        {
            if (ptr != nullptr)
                free_menu(ptr);
        }
    private:
        void free_menu(Menu*);
    };

private:
    //! Screen width
    std::uint32_t m_width { 0 };

    //! Screen height
    std::uint32_t m_height { 0 };

    //! Pointer to main render window
    std::unique_ptr< sf::RenderWindow, render_window_deleter > m_main_window { nullptr };

    //! Text font
    std::unique_ptr< sf::Font, font_deleter > m_font { nullptr };

    //! Statistic update time
    sf::Time m_statistic_update_time { sf::Time::Zero };

    //! Statistic frames count
    std::uint16_t m_statistics_frames_count { 0 };

    //! Statistic information text
    std::unique_ptr< sf::Text, text_deleter > m_statistic_text { nullptr };

    //! Menu object
    std::unique_ptr< Menu, menu_deleter > m_menu { nullptr };

    //! Color changing screen mode
    ColorChangingScreen m_color_changing_screen {};

    //! Gradient screen mode
    GradientScreen m_gradient_screen;

    //! Constant time per frame
    static sf::Time const TimePerFrame;
};

} // namespace screen

#endif
