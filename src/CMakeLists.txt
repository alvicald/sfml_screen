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

if (WIN32)
	set(SFML_DLL_LIBS_FOR_COPY "")
	file(GLOB DLL_FILES "${SFML_LIBRARY_DIR}/*.dll")
	foreach(file ${DLL_FILES})
		get_filename_component(file_name ${file} NAME)
		list(APPEND SFML_DLL_LIBS_FOR_COPY ${file_name})
	endforeach()
	message(STATUS "SFML_DLL_LIBS_FOR_COPY = ${SFML_DLL_LIBS_FOR_COPY}")
endif()

add_executable(${TARGET} ${HDRS_SRCS})

if (WIN32)
	foreach(DLL ${SFML_DLL_LIBS_FOR_COPY})
		set(CURRENT_LIB ${SFML_LIBRARY_DIR}/${DLL})
		message(STATUS "CURRENT_LIB = ${CURRENT_LIB}")
		add_custom_command(
			TARGET Screen POST_BUILD
			COMMAND ${CMAKE_COMMAND} -E copy_if_different
			"${CURRENT_LIB}" $<TARGET_FILE_DIR:Screen>
			COMMENT "Copying ${CURRENT_LIB} to output directory"
    )
	endforeach()
endif()
