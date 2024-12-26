set(TARGET Screen)

set(HDRS_SRCS
	multicolored_screen.h
	main.cpp
	screen.h
	screen.cpp
	menu.h
	menu.cpp
	error.h
)

add_executable(${TARGET} ${HDRS_SRCS})

if (WIN32)
	foreach(DLL_FILE ${SFML_DLL_LIBS_FOR_COPY})
		add_custom_command(
			TARGET Screen POST_BUILD
			COMMAND ${CMAKE_COMMAND} -E copy_if_different
			"${DLL_FILE}" $<TARGET_FILE_DIR:Screen>
		)
	endforeach()
endif()
