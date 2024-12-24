#ifndef MENU_H_
#define MENU_H_

#include <memory>
#include <cstdint>
#include <vector>

#include <SFML/Graphics/Color.hpp>
#include <SFML/System/String.hpp>

namespace sf{

//! sf::Font forward declaration
class Font;

//! sf::Text forward declaration
class Text;

class RenderWindow;
} // namespace sf

namespace screen{

class Menu
{
private:
    //! Deleter of sf::Font pointer
    struct font_deleter
    {
        void operator()(::sf::Font* ptr)
        {
            if (ptr != nullptr)
                free_font(ptr);
        }
    private:
        void free_font(::sf::Font*);
    };

private:
    //! Reference to main render window
    ::sf::RenderWindow& m_render_window;

    //! Menu position x
    std::uint16_t m_menu_x;

    //! Menu position y
    std::uint16_t m_menu_y;

    //! Interval beetwen menu items
    std::uint8_t m_menu_step;

    //! Menu elements count
    std::uint8_t m_menu_el_count;

    //! Menu font size
    std::uint8_t m_size_font;

    //! Selected menu item number
    std::uint8_t m_main_menu_selected;

    //! Menu font object
    std::unique_ptr< ::sf::Font, font_deleter > m_font;

    //! Menu items names
    std::vector< ::sf::Text > m_main_menu;

    //!Menu item text color
    ::sf::Color m_menu_item_text_color;

    //!Choose menu item text color
    ::sf::Color m_choose_menu_item_text_color;

    //!Outline menu item text color
    ::sf::Color m_outline_menu_item_text_color;

    //!Settings of menu items
    void setInitText(sf::Text& text, sf::String const& str, float xpos, float ypos);

public:
    // Конструктор
    // Параметры: ссылка на графическое окно, координаты игрового меню по x и y
    // количество пунктов меню, массив названий пунктов меню, размер шрифта, шаг между пунктами меню
    Menu(sf::RenderWindow& window, float menux, float menuy,
             int index, std::vector< sf::String > const& name, int sizeFont = 60, int step = 80);


};

} // namespace screen

#endif // MENU_H_
