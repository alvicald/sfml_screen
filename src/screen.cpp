#include <iostream>

#include <screen.h>
#include <menu.h>
#include <general_config.h>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Sleep.hpp>
#include <SFML/Window/Event.hpp>

namespace screen {

sf::Time const Screen::TimePerFrame { sf::seconds(1.f / 60.f) };

Screen::Screen(ScreenContext const& context):
    m_width(context.m_screen_width),
    m_height(context.m_screen_height),
    m_gradient_screen(m_width, m_height)
{
    try
    {
        auto screen_style { context.m_is_fullscreen == true ? static_cast< std::uint32_t >(::sf::Style::Fullscreen) : static_cast<std::uint32_t>(::sf::Style::Default) };
        m_main_window.reset(new ::sf::RenderWindow(::sf::VideoMode(m_width, m_height), "Screen", screen_style));
        m_statistic_text.reset(new ::sf::Text);
        m_font.reset(new ::sf::Font);
        m_menu.reset(new Menu(*m_main_window,
                              m_width / 2,
                              m_height / 2,
                              std::vector< ::sf::String > {"Changing color mode", "Gradient mode"},
                              30,
                              30));
        if (m_menu)
        {
            m_menu->align_menu(MenuAlignment::center);
        }
        else
            throw std::runtime_error("Menu pointer initialize error.");

        if (m_font)
        {
            if (!m_font->loadFromFile(RESOURCE_DIR"/font/showg.TTF"))
                throw std::runtime_error("Loading font error");

            m_statistic_text->setFont(*m_font);
            m_statistic_text->setPosition(5.f, 5.f);
            m_statistic_text->setCharacterSize(10);
        }
        else
            throw std::runtime_error("Font pointer initialize error.");
    }
    catch(std::bad_alloc& e)
    {
        std::cout << "Memory allocation failure: " << e.what() << '\n';
    }
    catch(std::exception& e)
    { 
        std::cout << e.what() << '\n';
    }
}

void Screen::run()
{
    sf::Clock clock;

    while (m_main_window->isOpen())
    {
        sf::Time elapsedTime = clock.restart();

        updateEvent();
        update(elapsedTime);

        updateStatistic(elapsedTime);
        render();

        sf::Time sleepTime = TimePerFrame - clock.getElapsedTime();
        if (sleepTime > sf::Time::Zero)
            sf::sleep(sleepTime);
    }
}

void Screen::updateEvent()
{
    ::sf::Event ev;

    while (m_main_window->pollEvent(ev))
    {
        switch (ev.type)
        {
        case ::sf::Event::Closed:
            m_main_window->close();
            break;
        case ::sf::Event::KeyReleased:
            switch (ev.key.code)
            {
            case ::sf::Keyboard::Escape:
                m_main_window->close();
                break;
            case ::sf::Keyboard::Up:
                m_menu->move_up();
                break;
            case ::sf::Keyboard::Down:
                m_menu->move_down();
                break;
            case ::sf::Keyboard::Return:
                switch (m_menu->get_menu_select_number())
                {
                case 0:
                    m_color_changing_screen.change_state();
                    break;
                case 1:
                    m_gradient_screen.change_state();
                    break;
                default:
                    break;
                }
                m_menu->set_mode_status(m_menu->get_menu_select_number());
                break;
            default:
                break;
            }
            break;
        default:
            break;
        }
    }
}

void Screen::updateStatistic(sf::Time elapsedTime)
{
    m_statistic_update_time += elapsedTime;
    m_statistics_frames_count += 1;

    if (m_statistic_update_time >= sf::seconds(1.0f))
    {
        m_statistic_text->setString(
                    "FPS = " + std::to_string(m_statistics_frames_count) + "\n" +
                    "Update for 1 frame = " + std::to_string(m_statistic_update_time.asSeconds() / m_statistics_frames_count) + " sec");
        m_statistic_update_time -= sf::seconds(1.0f);
        m_statistics_frames_count = 0;
    }
}

void Screen::render()
{
    m_main_window->clear(::sf::Color{0, 0, 0});
    m_color_changing_screen.draw(*m_main_window);
    m_gradient_screen.draw(*m_main_window);
    m_main_window->draw(*m_statistic_text);
    m_menu->draw();
    m_main_window->display();
}

void Screen::update(sf::Time elapsed)
{
//    m_gradient_screen.update();
    m_gradient_screen.set_colors(m_color_changing_screen.get_color());
}

void Screen::render_window_deleter::free_screen(::sf::RenderWindow* ptr)
{
    delete ptr;
}

void Screen::text_deleter::free_text(::sf::Text* ptr)
{
    delete ptr;
}

void Screen::font_deleter::free_font(sf::Font* ptr)
{
    delete ptr;
}

void Screen::menu_deleter::free_menu(Menu* ptr)
{
    delete ptr;
}

} // namespace screen
