cmake_minimum_required(VERSION 3.0.0)

set(ProjectName "Lamina")

project("${ProjectName}" VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 20)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
find_package(OpenGL REQUIRED)

#add_library(GLFW STATIC IMPORTED)
#set_target_properties(GLFW PROPERTIES IMPORTED_LOCATION "${CMAKE_SOURCE_DIR}/dependencies/GLFW/lib/glfw3.lib")

add_library("${ProjectName}"
	#source files
	dependencies/glad/glad.c
	Lamina/src/GL/window.cpp
	Lamina/src/Primitives/rectangle.cpp
	Lamina/src/Primitives/triangle.cpp
	Lamina/src/GL/colors.cpp
	Lamina/src/Math/vector.cpp
	Lamina/src/Math/vertex.cpp
	Lamina/src/GL/opengl.cpp
	Lamina/src/GL/texture.cpp
	Lamina/src/GL/vertex_array.cpp
	Lamina/src/GL/GL_text.cpp
	Lamina/src/GL/camera.cpp
	Lamina/src/misc_graphics/text.cpp
	Lamina/src/misc_graphics/image.cpp
	

	#header files
	Lamina/include/GL/window.hpp
	Lamina/include/GL/colors.hpp
	Lamina/include/Math/vec2.hpp
	Lamina/include/Primitives/rectangle.hpp
	Lamina/include/Primitives/triangle.hpp
	Lamina/include/Math/vector.hpp
	Lamina/include/Math/vertex.hpp
	Lamina/include/Math/constants.hpp
	Lamina/include/Math/timer.hpp
	Lamina/include/GL/opengl.hpp
	Lamina/include/GL/texture.hpp
	Lamina/include/GL/vertex_array.hpp
	Lamina/include/GL/GL_text.hpp
	Lamina/include/GL/camera.hpp
	Lamina/include/misc_graphics/text.hpp
	Lamina/include/misc_graphics/image.hpp

	#dependency headers
	dependencies/STB/stb_image.h
	dependencies/STB/stb_truetype.h
	dependencies/STB/stb_rect_pack.h
)
add_subdirectory(dependencies/GLFW)
target_include_directories("${ProjectName}" PRIVATE dependencies)
target_link_libraries("${ProjectName}" glfw OpenGL::GL)

add_executable("${ProjectName}-GL-test"
	#source files
	tests/GLTests/GLDrawTest.cpp

	#header files
)
target_include_directories("${ProjectName}-GL-test" PRIVATE dependencies)
target_link_libraries("${ProjectName}-GL-test" "${ProjectName}")
add_custom_command(TARGET ${ProjectName}-GL-test POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory
			${PROJECT_SOURCE_DIR}/Objects
			${CMAKE_CURRENT_BINARY_DIR}/Objects
	COMMAND ${CMAKE_COMMAND} -E copy_directory
			${PROJECT_SOURCE_DIR}/Shaders
			${CMAKE_CURRENT_BINARY_DIR}/Shaders
	COMMAND ${CMAKE_COMMAND} -E copy_directory
			${PROJECT_SOURCE_DIR}/Textures
			${CMAKE_CURRENT_BINARY_DIR}/Textures
)

add_executable("${ProjectName}-main" 
	#source files
	src/main.cpp

	#header files
)

target_include_directories("${ProjectName}-main" PRIVATE dependencies)
target_link_libraries("${ProjectName}-main" "${ProjectName}")
#set_source_files_properties(src/main.cpp PROPERTIES COMPILE_OPTIONS "-Wall; -Wextra")
add_custom_command(
	TARGET ${ProjectName}-main PRE_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory
			${PROJECT_SOURCE_DIR}/Objects
			${CMAKE_CURRENT_BINARY_DIR}/Objects
	COMMAND ${CMAKE_COMMAND} -E copy_directory
			${PROJECT_SOURCE_DIR}/Shaders
			$<TARGET_FILE_DIR:${ProjectName}>/Shaders
)

#file(COPY "${PROJECT_SOURCE_DIR}/Objects" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")
#file(COPY "${PROJECT_SOURCE_DIR}/Shaders" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")