cmake_minimum_required(VERSION 3.25.1)
project(Screen)

include(CheckTypeSize)
include(cmake/Functions.cmake)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(PROJECT_SOURCE_DIRECTORY ${CMAKE_SOURCE_DIR}/src)
set(PROJECT_RESOURCE_DIR ${CMAKE_SOURCE_DIR}/resources)
set(PROJECT_CONFIG_DIR ${CMAKE_SOURCE_DIR}/conf)
set(SFML_DIR "${CMAKE_SOURCE_DIR}/SFML")
set(SFML_INCLUDE_DIR "${SFML_DIR}/include")

get_filename_component(CONFIG_DIR ${PROJECT_CONFIG_DIR} REALPATH)
get_filename_component(RESOURCE_DIR ${PROJECT_RESOURCE_DIR} REALPATH)
configure_file(general_config.h.in ${PROJECT_SOURCE_DIRECTORY}/general_config.h)

check_type_size(void* SIZEOF_VOID_PTR)
if(${SIZEOF_VOID_PTR} STREQUAL "4")
	set(ARCH_32BITS 1)
elseif(${SIZEOF_VOID_PTR} STREQUAL "8")
	set(ARCH_64BITS 1)
endif()

if (UNIX)
	if (ARCH_64BITS)
		set(SFML_LIBRARY_DIR "${SFML_DIR}/lib/linux")
		get_file_name_list("${SFML_LIBRARY_DIR}" "*.so" False SFML_LIBS)
	elseif(ARCH_32BITS)
		message(FATAL_ERROR "Not support libraries for x86 system. Maybe will be added latter")
	endif()
elseif(WIN32)
	if (ARCH_64BITS)
		set(SFML_LIBRARY_DIR "${SFML_DIR}/lib/windows")
		get_file_name_list("${SFML_LIBRARY_DIR}" "*.lib" False SFML_LIBS)
		get_file_name_list("${SFML_LIBRARY_DIR}" "*.dll" True SFML_DLL_LIBS_FOR_COPY)
	elseif(ARCH_32BITS)
		message(FATAL_ERROR "Not support libraries for x86 system. Maybe will be added latter")
	endif()
endif()

add_subdirectory(src)

target_link_directories(Screen PRIVATE ${SFML_LIBRARY_DIR})
target_include_directories(Screen PRIVATE ${SFML_INCLUDE_DIR} ${PROJECT_SOURCE_DIRECTORY})

target_link_libraries(Screen ${SFML_LIBS})
