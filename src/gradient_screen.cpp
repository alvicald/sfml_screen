#include <iostream>

#include <gradient_screen.h>
#include <general_config.h>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Shader.hpp>
#include <SFML/Graphics/Glsl.hpp>

namespace screen {

GradientScreen::GradientScreen(std::uint32_t width, std::uint32_t height):
    m_quad(::sf::TriangleFan, 4)
{
    try
    {
        m_shader.reset(new ::sf::Shader);

        if (m_shader)
        {
            if(!m_shader->loadFromFile(RESOURCE_DIR"/shaders/gradient.vert", RESOURCE_DIR"/shaders/gradient.frag"))
                throw std::runtime_error("Shader load error.");

            m_shader->setUniform("color1", static_cast<::sf::Glsl::Vec4>(::sf::Color::Black));
            m_shader->setUniform("color2", static_cast<::sf::Glsl::Vec4>(::sf::Color::White));

            m_quad[0].position = ::sf::Vector2f(-1.f, -1.f);
            m_quad[1].position = ::sf::Vector2f(1.f, -1.f);
            m_quad[2].position = ::sf::Vector2f(1.f, 1.f);
            m_quad[3].position = ::sf::Vector2f(-1.f, 1.f);

            for (int i = 0; i < 4; ++i)
                m_quad[i].texCoords = m_quad[i].position * 0.5f + sf::Vector2f(0.5f, 0.5f);
        }
    }
    catch (std::bad_alloc& e)
    {
        std::cout << e.what() << '\n';
    }
    catch (std::exception& e)
    {
        std::cout << e.what() << '\n';
    }
}

void GradientScreen::update()
{
    m_shader->setUniform("time", m_interpolar_koef);
    m_interpolar_koef += 0.01;

    if (m_interpolar_koef >= 2)
        m_interpolar_koef = 0;
}

void GradientScreen::draw(sf::RenderWindow& window)
{
    window.draw(m_quad, m_shader.get());
}

void GradientScreen::shader_deleter::free_shader(sf::Shader* ptr)
{
    delete ptr;
}

} // namespace screen
