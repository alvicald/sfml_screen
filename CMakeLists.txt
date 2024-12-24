cmake_minimum_required(VERSION 3.25.1)
project(Screen)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(SFML_DIR "${CMAKE_SOURCE_DIR}/SFML")
set(SFML_INCLUDE_DIR "${SFML_DIR}/include")

message(STATUS "CMAKE_SOURCE_DIR = ${CMAKE_SOURCE_DIR}")

include(CheckTypeSize)
check_type_size(void* SIZEOF_VOID_PTR)
if(${SIZEOF_VOID_PTR} STREQUAL "4")
	set(ARCH_32BITS 1)
elseif(${SIZEOF_VOID_PTR} STREQUAL "8")
	set(ARCH_64BITS 1)
endif()

if (UNIX)
	if (ARCH_64BITS)
		set(SFML_SHARED_LIBRARY_DIR "${SFML_DIR}/linux/shared")
		set(SFML_STATIC_LIBRARY_DIR "${SFML_DIR}/linux/static")
	elseif(ARCH_32BITS)
		message(FATAL_ERROR "Not support libraries for x86 system. Maybe will be added latter")
	endif()
elseif(WIN32)
	if (ARCH_64BITS)
		set(SFML_SHARED_LIBRARY_DIR "${SFML_DIR}/windows/shared")
		set(SFML_STATIC_LIBRARY_DIR "${SFML_DIR}/windows/static")
	elseif(ARCH_32BITS)
		message(FATAL_ERROR "Not support libraries for x86 system. Maybe will be added latter")
	endif()
endif()

add_subdirectory(src)

target_link_directories(Screen PUBLIC ${SFML_SHARED_LIBRARY_DIR} ${SFML_STATIC_LIBRARY_DIR})
target_include_directories(Screen PUBLIC ${SFML_INCLUDE_DIR} ${CMAKE_SOURCE_DIR}/src)

target_link_libraries(Screen
	sfml-system
	sfml-window
	sfml-graphics
	sfml-audio
	sfml-network
)
