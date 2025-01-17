#ifndef MENU_H_
#define MENU_H_

#include <memory>
#include <cstdint>
#include <vector>
#include <map>

#include <SFML/Graphics/Color.hpp>
#include <SFML/System/String.hpp>

namespace sf{

//! sf::Font forward declaration
class Font;

//! sf::Text forward declaration
class Text;

//! sf::RenderWindow forward declaration
class RenderWindow;

} // namespace sf

namespace screen{

enum class MenuAlignment
{
    //! Alignment to left side
    left,

    //! Alignment to center
    center,

    //! Alignment to right side
    right
};

class Menu
{
public:
    Menu(sf::RenderWindow& window,
        float menux,
        float menuy,
        std::vector< sf::String > const& names,
        int sizeFont = 60,
        int step = 80);

    //! Draw menu on render window
    void draw();

    //! Up of choose of menu item
    void move_up();

    //! Down of choose of menu item
    void move_down();

    //! Align menu position
    void align_menu(MenuAlignment align);

    //! Get current selected menu item number
    std::int16_t get_menu_select_number() const;

    //! Set mode status
    void set_mode_status(std::int16_t selected_number);

private:
    //!Settings of menu items statuses
    void set_init_status(sf::Text& text, sf::String const& str, float xpos, float ypos);

    //!Settings of menu items
    void set_init_text(sf::Text& text, sf::String const& str, float xpos, float ypos);

    //! Deleter of sf::Font pointer
    struct font_deleter
    {
        void operator()(sf::Font* ptr)
        {
            if (ptr != nullptr)
                free_font(ptr);
        }
    private:
        void free_font(sf::Font*);
    };

    //! State of current mode status
    struct status_state;

    struct status_state_deleter
    {
        void operator()(status_state* ptr)
        {
            if (ptr != nullptr)
                free_status_state(ptr);
        }
    private:
        void free_status_state(status_state*);
    };

private:
    //! Reference to main render window
    sf::RenderWindow& m_render_window;

    //! Menu position x
    std::uint16_t m_menu_x { 0 };

    //! Menu position y
    std::uint16_t m_menu_y { 0 };

    //! Interval beetwen menu items
    std::uint16_t m_menu_step { 0 };

    //! Menu font size
    std::uint16_t m_size_font { 0 };

    //! Selected menu item number
    std::int16_t m_main_menu_selected { 0 };

    //! Menu font object
    std::unique_ptr< sf::Font, font_deleter > m_font { nullptr };

    //! Menu items names
    std::vector< sf::Text > m_main_menu;

    //! Menu items statuses
    std::map< std::int16_t, std::unique_ptr< status_state, status_state_deleter > > m_statuses;

    //!Menu item text color
    sf::Color m_menu_item_text_color;

    //!Choose menu item text color
    sf::Color m_choose_menu_item_text_color;

    //!Outline menu item text color
    sf::Color m_outline_menu_item_text_color;
};

} // namespace screen

#endif // MENU_H_
