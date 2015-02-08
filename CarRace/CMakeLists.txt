# Some flags for Freeglut and GLUI.
add_definitions( -DFREEGLUT_EXPORTS -DFREEGLUT_STATIC -D_CRT_SECURE_NO_WARNINGS )

# Define the framework files.
set(GAME_SRCS
        Game/Game.cpp
        Game/Game.h
        Game/Render.cpp
        Game/Render.h
        Game/Test.cpp
        Game/Test.h
        Game/Car.h
        Game/Car.cpp
        Game/Track.cpp
        Game/Track.h
)

#Define the learning files.
set(LEARNING_SRCS
	Learning/Driver.h
        Learning/SimpleDriver.h
        Learning/SimpleDriver.cpp
)

#Define the system files.
set(SYSTEM_SRCS
        System/main.cpp
)

# These are used to create visual studio folders.
source_group(Game FILES ${GAME_SRCS})
source_group(Learning FILES ${LEARNING_SRCS})
source_group(System FILES ${SYSTEM_SRCS})

include_directories (
	${OPENGL_INCLUDE_DIR}
	${Box2D_SOURCE_DIR}
	../rapidjson
	/usr/local/include
)

if(APPLE)
	# We are not using the Apple's framework version, but X11's
	include_directories( /usr/X11/include )
	link_directories( /usr/X11/lib )
	set (OPENGL_LIBRARIES GL GLU GLUT X11)
endif(APPLE)

add_executable(DrivingLicenceTest
        ${SYSTEM_SRCS}
        ${GAME_SRCS}
        ${LEARNING_SRCS}
)

find_library(M_LIB m)
find_library(FANN_LIB fann)

target_link_libraries (
        DrivingLicenceTest
	Box2D
	freeglut_static
	glui
	rapidjson
	${OPENGL_LIBRARIES}
	${FANN_LIB}
	${M_LIB}
)
