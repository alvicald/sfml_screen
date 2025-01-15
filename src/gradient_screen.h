#ifndef GRADIENT_SCREEN_H_
#define GRADIENT_SCREEN_H_

#include <cstdint>
#include <memory>

#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/System/Time.hpp>

namespace sf {

//! sf::RenderWindow Forward declaration
class RenderWindow;

//! sf::Shader forward declaration
class Shader;
}

namespace screen {

class GradientScreen
{
public:
    explicit GradientScreen(std::uint32_t width, std::uint32_t height);

    //! Update a gradient state
    void update();

    //! Draw a gradient
    void draw(sf::RenderWindow&);

    //! On/off gradient
    void change_state_of_gradient();

    //! On/off moving gradient
    void change_state_of_moving_gradient();

    //! Set colors
    void set_colors(sf::Color const&);

private:
    //! Deleter of sf::Shader pointer
    struct shader_deleter
    {
        void operator()(sf::Shader* ptr)
        {
            if (ptr != nullptr)
                free_shader(ptr);
        }
    private:
        void free_shader(sf::Shader*);
    };
private:
    //! Shader object pointer
    std::unique_ptr< sf::Shader, shader_deleter > m_shader { nullptr };

    //! Vertex array personifying a fullscreen
    sf::VertexArray m_quad;

    //! Interpolar koefficient for move a gradient
    float m_interpolar_koef { 0.f };

    //! Enable/disable gradient screen flag
    bool m_enable_gradient_screen { false };

    //! Enable/disable moving gradient screen flag
    bool m_enable_moving_gradient_screen { false };
};

} // namespace screen

#endif // GRADIENT_SCREEN_H_
