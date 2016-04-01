cmake_minimum_required(VERSION 2.8)
project(justify)

set(
	CMAKE_CXX_FLAGS
	"${CMAKE_CXX_FLAGS} -std=c++14 -W -Wall -Wextra -Winline -pedantic"
)

include_directories(
	src/
)

add_executable(
	justify
	justify.cc
	src/line_accumulator.cc
)
