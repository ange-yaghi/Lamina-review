cmake_minimum_required(VERSION 3.0.0)
project("Lamina" VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 20)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
find_package(OpenGL REQUIRED)

add_library("Lamina"
	#source files
	Lamina/src/glad.c
	Lamina/src/window.cpp
	Lamina/src/Primitives/rectangle.cpp
	Lamina/src/Primitives/triangle.cpp
	Lamina/src/colors.cpp
	Lamina/src/Math/matrix.cpp
	Lamina/src/Math/vec3.cpp

	#header files
	Lamina/include/window.hpp
	Lamina/include/colors.hpp
	Lamina/include/Math/vec2.hpp
	Lamina/include/Primitives/rectangle.hpp
	Lamina/include/Primitives/triangle.hpp
	Lamina/include/Math/matrix.hpp
	Lamina/include/Math/vec3.hpp
)

add_executable("Lamina-main" 
	#source files
	src/main.cpp

	#header files
)

add_subdirectory(dependencies/GLFW)
target_include_directories("Lamina-main" PRIVATE dependencies)
target_link_libraries("Lamina-main" "Lamina" glfw OpenGL::GL)

target_include_directories("Lamina" PRIVATE dependencies)
target_link_libraries("Lamina" glfw OpenGL::GL)