cmake_minimum_required(VERSION 3.0.0)
project("Lamina" VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 20)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
find_package(OpenGL REQUIRED)

add_executable("Lamina" 
	src/main.cpp
	src/window.cpp
	src/glad.c
	src/Primitives/rectangle.cpp
	src/Primitives/triangle.cpp
	src/colors.cpp

	include/window.hpp
	include/colors.hpp
	include/vec2.hpp
	include/Primitives/rectangle.hpp
	include/Primitives/triangle.hpp
)

add_subdirectory(dependencies/GLFW)
target_include_directories("Lamina" PRIVATE dependencies)
target_link_libraries("Lamina" glfw OpenGL::GL)