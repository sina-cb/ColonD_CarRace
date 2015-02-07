add_definitions( -DFREEGLUT_STATIC -D_CRT_SECURE_NO_WARNINGS )

if(MSVC)
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W1")
endif(MSVC)

set(rapidjson_SRCS
    empty.cpp
	document.h
	filestream.h
	prettywriter.h
	rapidjson.h
	reader.h
	stringbuffer.h
	writer.h
    internal/pow10.h
    internal/stack.h
    internal/strfunc.h
)

add_library(rapidjson
	${rapidjson_SRCS}
)
