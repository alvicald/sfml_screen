#include <iostream>

#include <screen.h>
#include <multicolored_screen.h>
#include <menu.h>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Sleep.hpp>

namespace screen {

sf::Time const Screen::TimePerFrame = sf::seconds(1.f / 60.f);

Screen::Screen(ScreenContext const& context):
    m_width(context.m_screen_width),
    m_height(context.m_screen_height)
{
    try
    {
        m_main_window.reset(new ::sf::RenderWindow(::sf::VideoMode(m_width, m_height), "Screen"));
        m_statistic_text.reset(new ::sf::Text);
        m_font.reset(new ::sf::Font);
        //m_menu.reset(new Menu(*m_main_window,
        //                      200,
        //                      200,
        //                      10,
        //                      std::vector< ::sf::String > {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10"},
        //                      13,
        //                      5));

        if (m_font)
        {
            if (!m_font->loadFromFile(font_path))
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
        updateStatistic(elapsedTime);
        render();

        sf::Time sleepTime = TimePerFrame - clock.getElapsedTime();
        if (sleepTime > sf::Time::Zero)
            sf::sleep(sleepTime);
    }
}

void Screen::updateEvent()
{
    while (m_main_window->pollEvent(m_event))
    {
        switch (m_event.type)
        {
        case ::sf::Event::Closed:
            m_main_window->close();
            break;
        case ::sf::Event::KeyPressed:
            switch (m_event.key.code)
            {
            case ::sf::Keyboard::M:
                ::screen::color_changing_screen::change_state();
                break;
            case ::sf::Keyboard::Z:
                m_main_window->clear(sf::Color(0, 0, 0));
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
    if (::screen::color_changing_screen::get_state())
    {
        auto cls = ::screen::color_changing_screen()();
        m_main_window->clear(sf::Color(std::get<0>(cls), std::get<1>(cls), std::get<2>(cls)));
    }
    else
        m_main_window->clear();

    m_main_window->draw(*m_statistic_text);
    m_main_window->display();
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
