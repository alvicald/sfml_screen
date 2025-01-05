#ifndef GRADIENT_SCREEN_H_
#define GRADIENT_SCREEN_H_

#include <cstdint>
#include <memory>

#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/System/Time.hpp>

namespace sf {
class RenderWindow;
class Shader;
}

namespace screen {

class GradientScreen
{
public:
    explicit GradientScreen(std::uint32_t width, std::uint32_t height);

    void update();

    void draw(::sf::RenderWindow&);

private:
    struct shader_deleter
    {
        void operator()(::sf::Shader* ptr)
        {
            if (ptr != nullptr)
                free_shader(ptr);
        }
    private:
        void free_shader(::sf::Shader*);
    };
private:
    std::unique_ptr< ::sf::Shader, shader_deleter > m_shader { nullptr };
    ::sf::VertexArray m_quad;
    float m_interpolar_koef { 0.f};
};

} // namespace screen

#endif // GRADIENT_SCREEN_H_
