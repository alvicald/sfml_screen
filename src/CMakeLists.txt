set(TARGET Screen)

set(TARGET_BIN_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

set(HDRS_SRCS
	color_changing_screen.cpp
	color_changing_screen.h
	main.cpp
	screen.h
	screen.cpp
	menu.h
	menu.cpp
	context.h
	context.cpp
        gradient_screen.h
        gradient_screen.cpp
)

add_executable(${TARGET} ${HDRS_SRCS})

add_custom_command(TARGET ${TARGET} POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E make_directory "${TARGET_BIN_DIRECTORY}"
	COMMAND ${CMAKE_COMMAND} -E copy_if_different
	$<TARGET_FILE:${TARGET}> "${TARGET_BIN_DIRECTORY}"
)

if (WIN32)
	foreach(DLL_FILE ${SFML_DLL_LIBS_FOR_COPY})
		add_custom_command(
			TARGET ${TARGET} POST_BUILD
			COMMAND ${CMAKE_COMMAND} -E copy_if_different
			"${DLL_FILE}" "${TARGET_BIN_DIRECTORY}"
		)
	endforeach()
endif()


