cmake_minimum_required(VERSION 2.6)

project(indiestudio)

set(
		EXECUTABLE_OUTPUT_PATH 
		../
)

file(
		GLOB_RECURSE
		SRCS
		./src/*.cpp
)

file(
		GLOB_RECURSE
		HDRS
		./include/*.hh
)

include_directories(
						${CMAKE_SOURCE_DIR}/include
)

set(
	CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} \
	-Werror \
	-Wall \
	-Wextra"

)

add_executable(
				indiestudio
				${SRCS}
				${HDRS}
)