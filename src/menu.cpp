#include <menu.h>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>

namespace screen {

void Menu::setInitText(sf::Text& text, sf::String const& str, float xpos, float ypos)
{
    text.setFont(*m_font);
    text.setFillColor(m_choose_menu_item_text_color);
    text.setString(str);
    text.setCharacterSize(m_size_font);
    text.setPosition(xpos, ypos);
    text.setOutlineThickness(3);
    text.setOutlineColor(m_outline_menu_item_text_color);
}

Menu::Menu(sf::RenderWindow& window, float menux, float menuy, int index, std::vector< sf::String > const& name, int sizeFont, int step):
    m_render_window(window),
    m_menu_x(menux),
    m_menu_y(menuy),
    m_menu_step(step),
    m_size_font(sizeFont),
    m_menu_el_count(index),
    m_main_menu_selected(0),
    m_menu_item_text_color(::sf::Color(0, 0, 0)),
    m_choose_menu_item_text_color(::sf::Color(170, 170, 0)),
    m_outline_menu_item_text_color(::sf::Color(0, 0, 255))
{
    m_font.reset(new ::sf::Font);

    if (m_font)
    {
        if (m_font->loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSansMono.ttf"))
        {
            m_main_menu.resize(m_menu_el_count);

            std::uint16_t ypos { m_menu_y };
            std::uint32_t name_ind { 0 };

            for (::sf::Text& menu_el : m_main_menu)
            {
                setInitText(menu_el, name.at(name_ind++), m_menu_x, ypos);
                ypos += m_menu_step;
            }
            m_main_menu.at(m_main_menu_selected).setFillColor(m_choose_menu_item_text_color);
        }
    }
}

void Menu::draw()
{

}

void Menu::font_deleter::free_font(sf::Font* ptr)
{
    delete ptr;
}




} // namespace screen
