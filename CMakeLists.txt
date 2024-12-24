cmake_minimum_required(VERSION 3.25.1)
project(Screen)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(SFML 2.5.1 COMPONENTS system window graphics audio network REQUIRED)

if (NOT SFML_FOUND)
	message(FATAL_ERROR "Cant find the SFML library!")
endif()

add_subdirectory(src)

target_include_directories(Screen PUBLIC
    ./src
)

target_link_libraries(Screen
	sfml-system
	sfml-window
	sfml-graphics
	sfml-audio
	sfml-network
)
