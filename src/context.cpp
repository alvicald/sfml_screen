#include <fstream>
#include <iostream>

#include <context.h>

namespace screen {

ScreenContext::ScreenContext(char const* config_file)
{
    std::ifstream fin;
    try
    {
        fin.open(config_file);
        if (!fin.is_open())
            throw std::runtime_error("Cant open config file.");

        fin >> m_screen_width;
        fin >> m_screen_height;

        fin.close();
    }
    catch (std::exception& e)
    {
        std::cout << e.what() << '\n';
        fin.close();
        std::exit(EXIT_FAILURE);
    }
}

} // namespace screen
