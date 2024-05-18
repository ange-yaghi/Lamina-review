cmake_minimum_required(VERSION 3.0.0)

set(ProjectName "Lamina")

set(CMAKE_CXX_STANDARD 20)

project("${ProjectName}" VERSION 0.0.1)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /EHsc")
find_package(OpenGL REQUIRED)

#add_library(GLFW STATIC IMPORTED)
#set_target_properties(GLFW PROPERTIES IMPORTED_LOCATION "${CMAKE_SOURCE_DIR}/dependencies/GLFW/lib/glfw3.lib")

add_library("${ProjectName}"
	#source files
	dependencies/glad/glad.c
	Lamina/src/GL/window.cpp
	Lamina/src/GL/colors.cpp
	
	Lamina/src/Math/vertex.cpp
	Lamina/src/GL/opengl.cpp
	Lamina/src/GL/texture.cpp
	Lamina/src/GL/vertex_array.cpp
	Lamina/src/GL/camera.cpp
	Lamina/src/misc_graphics/text.cpp
	Lamina/src/misc_graphics/glyph.cpp
	Lamina/src/misc_graphics/image.cpp
	Lamina/src/user_interface/event.cpp
	

	#header files
	Lamina/include/GL/window.hpp
	Lamina/include/GL/colors.hpp
	Lamina/include/Math/vector.hpp
	Lamina/include/Math/vertex.hpp
	Lamina/include/Math/constants.hpp
	Lamina/include/Math/timer.hpp
	Lamina/include/GL/opengl.hpp
	Lamina/include/GL/texture.hpp
	Lamina/include/GL/vertex_array.hpp
	Lamina/include/GL/camera.hpp
	Lamina/include/misc_graphics/text.hpp
	Lamina/include/misc_graphics/image.hpp
	Lamina/include/misc_graphics/glyph.hpp
	Lamina/include/user_interface/event.hpp

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

#pong demo
add_executable("${ProjectName}-pong" WIN32
	#source files
	tests/pong_demo/src/main.cpp

	#header files
)
target_include_directories("${ProjectName}-pong" PRIVATE dependencies)
target_link_libraries("${ProjectName}-pong" "${ProjectName}")
add_custom_command(TARGET ${ProjectName}-pong POST_BUILD
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