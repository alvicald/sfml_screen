#ifndef ERROR_H_
#define ERROR_H_

#include <stdexcept>

namespace screen {

class CantLoadFont : public std::runtime_error
{
public:
	explicit CantLoadFont(std::string const& msg): std::runtime_error(msg) {}
	explicit CantLoadFont(char const* msg): std::runtime_error(msg) {}
};

} // namespace screen

#endif