#ifndef SCREEN_H_
#define SCREEN_H_

#include <memory>

#include "general_config.h"

#include <SFML/Window/Event.hpp>
#include <SFML/System/Time.hpp>

namespace sf{

//! sf::RenderWindow forward declaration
class RenderWindow;

//! sf::Text forward declaration
class Text;

//! sf::Font forward declaration
class Font;

} // namespace sf

namespace screen {

static char const* font_path { RESOURCE_DIR"/font/showg.TTF" };

//! Menu forward declaration
class Menu;

class Screen
{
public:
    explicit Screen(uint32_t width, uint32_t height);

    //! Run the screen program
    void run();

private:
    //! Update of window events
    void updateEvent();

    //! Update and print time and fps statistic
    void updateStatistic(::sf::Time elapsedTime);

    //! Render all window elements
    void render();

private:
    //! Deleter of sf::RenderWindow pointer
    struct render_window_deleter
    {
        void operator()(::sf::RenderWindow* ptr) noexcept
        {
            if (ptr != nullptr)
                free_screen(ptr);
        }
    private:
        void free_screen(::sf::RenderWindow*);
    };

    //! Deleter of sf::Text pointer
    struct text_deleter
    {
        void operator()(::sf::Text* ptr) noexcept
        {
            if (ptr != nullptr)
                free_text(ptr);
        }
    private:
        void free_text(::sf::Text*);
    };

    //! Deleter of sf::Font pointer
    struct font_deleter
    {
        void operator()(::sf::Font* ptr) noexcept
        {
            if (ptr != nullptr)
                free_font(ptr);
        }
    private:
        void free_font(::sf::Font*);
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
    std::uint32_t m_width;

    //! Screen height
    std::uint32_t m_height;

    //! Pointer to main render window
    std::unique_ptr< ::sf::RenderWindow, render_window_deleter > m_main_window;

    //! Event object for render window handling
    ::sf::Event m_event;

    //! Text font
    std::unique_ptr< ::sf::Font, font_deleter > m_font;

    //! Statistic update time
    ::sf::Time m_statistic_update_time;

    //! Statistic frames count
    std::size_t m_statistics_frames_count;

    //! Statistic information text
    std::unique_ptr< ::sf::Text, text_deleter > m_statistic_text;

    //! Menu object
    std::unique_ptr< Menu, menu_deleter > m_menu;

    //! Constant time per frame
    static ::sf::Time const TimePerFrame;
};

} // namespace screen

#endif
