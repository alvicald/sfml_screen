#include <iostream>

#include <menu.h>
#include <general_config.h>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>

namespace screen {

struct Menu::status_state
{
    //! Current mode is active
    bool is_active { false };

    //! Text of current mode status
    ::sf::Text status_state;
};

void Menu::setInitText(sf::Text& text, sf::String const& str, float xpos, float ypos)
{
    text.setFont(*m_font);
    text.setFillColor(m_menu_item_text_color);
    text.setString(str);
    text.setCharacterSize(m_size_font);
    text.setPosition(xpos, ypos);
    text.setOutlineThickness(3);
    text.setOutlineColor(m_outline_menu_item_text_color);
}

Menu::Menu(sf::RenderWindow& window, float menux, float menuy, std::vector< sf::String > const& names, int sizeFont, int step):
    m_render_window(window),
    m_menu_x(menux),
    m_menu_y(menuy),
    m_menu_step(step),
    m_size_font(sizeFont),
    m_main_menu_selected(0),
    m_menu_item_text_color(sf::Color(50, 50, 50)),
    m_choose_menu_item_text_color(sf::Color(255, 150, 0)),
    m_outline_menu_item_text_color(sf::Color(0, 0, 255))
{
    try
    {
        m_font = std::unique_ptr< sf::Font, font_deleter >(new sf::Font);

        if (m_font)
        {
            if (m_font->loadFromFile(RESOURCE_DIR"/font/showg.TTF"))
            {
                m_main_menu.resize(names.size());

                std::uint16_t ypos{ m_menu_y };
                std::uint32_t name_ind{ 0 };

                for (int i = 0; i < names.size(); ++i)
                {
                    setInitText(m_main_menu.at(i), names.at(name_ind++), m_menu_x, ypos);
                    m_statuses.emplace(i, std::unique_ptr< status_state, status_state_deleter >(new status_state));
                    setInitStatus(m_statuses.at(i)->status_state, "(OFF)", m_menu_x + m_main_menu.at(i).getLocalBounds().width / 2, ypos);
                    ypos += m_menu_step;
                }

                m_main_menu.at(m_main_menu_selected).setFillColor(m_choose_menu_item_text_color);
            }
            else
                throw std::runtime_error("Cant load font file.");
        }
        else
            throw std::runtime_error("Font pointer is null.");
    }
    catch (std::bad_alloc& e)
    {
        std::cout << e.what();
    }
    catch (std::exception& e)
    {
        std::cout << e.what();
    }
}

void Menu::draw()
{
    try
    {
        for (int i = 0; i < m_main_menu.size(); ++i)
        {
            m_render_window.draw(m_main_menu.at(i));
            m_render_window.draw(m_statuses.at(i)->status_state);
        }
    }
    catch (std::exception& e)
    {
        std::cout << e.what() << '\n';
    }
}

void Menu::move_up()
{
    try
    {
        if (--m_main_menu_selected >= 0)
        {
            m_main_menu.at(m_main_menu_selected).setFillColor(m_choose_menu_item_text_color);
            m_main_menu.at(static_cast< std::size_t >(m_main_menu_selected) + 1).setFillColor(m_menu_item_text_color);
        }
        else
        {
            m_main_menu.at(0).setFillColor(m_menu_item_text_color);
            m_main_menu_selected = m_main_menu.size() - 1;
            m_main_menu.at(m_main_menu_selected).setFillColor(m_choose_menu_item_text_color);
        }
    }
    catch (std::exception& e)
    {
        std::cout << e.what() << '\n';
    }
}

void Menu::move_down()
{
    try
    {
        if (++m_main_menu_selected < m_main_menu.size())
        {
            m_main_menu.at(static_cast< std::size_t >(m_main_menu_selected) - 1).setFillColor(m_menu_item_text_color);
            m_main_menu.at(m_main_menu_selected).setFillColor(m_choose_menu_item_text_color);
        }
        else
        {
            m_main_menu.at(m_main_menu.size() - 1).setFillColor(m_menu_item_text_color);
            m_main_menu_selected = 0;
            m_main_menu.at(m_main_menu_selected).setFillColor(m_choose_menu_item_text_color);
        }
    }
    catch (std::exception& e)
    {
        std::cout << e.what() << '\n';
    }
}

void Menu::align_menu(MenuAlignment align)
{
    double nullx{ 0 };
    for (auto& menu_el : m_main_menu)
    {
        switch (align)
        {
        case MenuAlignment::right:
            nullx = 0;
            break;
        case MenuAlignment::left:
            nullx = menu_el.getLocalBounds().width;
            break;
        case MenuAlignment::center:
            nullx = menu_el.getLocalBounds().width / 2;
            break;
        default:
            break;
        }
        menu_el.setPosition(menu_el.getPosition().x - nullx, menu_el.getPosition().y);
    }
}

std::int16_t Menu::get_menu_select_number() const
{
    return m_main_menu_selected;
}

void Menu::set_mode_status(int16_t selected_number)
{
    m_statuses.at(selected_number)->is_active = !m_statuses.at(selected_number)->is_active;

    if (m_statuses.at(selected_number)->is_active)
    {
        m_statuses.at(selected_number)->status_state.setString("(ON)");
        m_statuses.at(selected_number)->status_state.setFillColor(::sf::Color::Green);
    }
    else
    {
        m_statuses.at(selected_number)->status_state.setString("(OFF)");
        m_statuses.at(selected_number)->status_state.setFillColor(::sf::Color::Red);
    }
}

void Menu::setInitStatus(sf::Text &text, const sf::String &str, float xpos, float ypos)
{
    text.setFont(*m_font);
    text.setString(str);
    text.setPosition(xpos, ypos);
    text.setFillColor(::sf::Color::Red);
}

void Menu::font_deleter::free_font(sf::Font* ptr)
{
    delete ptr;
}

void Menu::status_state_deleter::free_status_state(status_state* ptr)
{
    delete ptr;
}

} // namespace screen
