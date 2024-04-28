cmake_minimum_required(VERSION 3.0.0)
project("Lamina" VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 20)

#set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
#set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
#set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
find_package(OpenGL REQUIRED)

add_library(GLFW STATIC IMPORTED)
set_target_properties(GLFW PROPERTIES IMPORTED_LOCATION "${CMAKE_SOURCE_DIR}/dependencies/GLFW/lib/glfw3.lib")

add_library("Lamina"
	#source files
	Lamina/src/glad.c
	Lamina/src/window.cpp
	Lamina/src/Primitives/rectangle.cpp
	Lamina/src/Primitives/triangle.cpp
	Lamina/src/colors.cpp
	

	#header files
	Lamina/include/window.hpp
	Lamina/include/colors.hpp
	Lamina/include/Math/vec2.hpp
	Lamina/include/Primitives/rectangle.hpp
	Lamina/include/Primitives/triangle.hpp
)
#add_subdirectory(dependencies/GLFW)
target_include_directories("Lamina" PRIVATE dependencies)
target_link_libraries("Lamina" GLFW OpenGL::GL)

add_executable("Matrix-test"
	#source files
	tests/matrix/src/mat-test-main.cpp

	#header files
)
target_include_directories("Matrix-test" PRIVATE dependencies)
target_link_libraries("Matrix-test" "Lamina")

add_executable("Lamina-main" 
	#source files
	src/main.cpp

	#header files
)

target_include_directories("Lamina-main" PRIVATE dependencies)

target_link_libraries("Lamina-main" "Lamina")
#set_source_files_properties(src/main.cpp PROPERTIES COMPILE_OPTIONS "-Wall; -Wextra")