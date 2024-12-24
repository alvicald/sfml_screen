
set(TARGET Screen)

set(HDRS_SRCS
	multicolored_screen.h
	main.cpp
        screen.h
        screen.cpp
        menu.h
        menu.cpp
)

add_executable(${TARGET} ${HDRS_SRCS})
