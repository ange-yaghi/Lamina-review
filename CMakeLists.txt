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
	Lamina/src/glad.c
	Lamina/src/window.cpp
	Lamina/src/Primitives/rectangle.cpp
	Lamina/src/Primitives/triangle.cpp
	Lamina/src/colors.cpp
	Lamina/src/Math/vector.cpp
	Lamina/src/Math/vertex.cpp
	Lamina/src/GL/opengl.cpp

	#header files
	Lamina/include/window.hpp
	Lamina/include/colors.hpp
	Lamina/include/Math/vec2.hpp
	Lamina/include/Primitives/rectangle.hpp
	Lamina/include/Primitives/triangle.hpp
	Lamina/include/Math/vector.hpp
	Lamina/include/Math/vertex.hpp
	Lamina/include/GL/opengl.hpp
)
add_subdirectory(dependencies/GLFW)
target_include_directories("${ProjectName}" PRIVATE dependencies)
target_link_libraries("${ProjectName}" glfw OpenGL::GL)

add_executable("${ProjectName}-Vertex-test"
	#source files
	tests/vertex/src/ver-test-main.cpp

	#header files
)
target_include_directories("${ProjectName}-Vertex-test" PRIVATE dependencies)
target_link_libraries("${ProjectName}-Vertex-test" "${ProjectName}")
add_custom_command(TARGET ${ProjectName}-Vertex-test POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory
			${PROJECT_SOURCE_DIR}/Objects
			${CMAKE_CURRENT_BINARY_DIR}/Objects
	COMMAND ${CMAKE_COMMAND} -E copy_directory
			${PROJECT_SOURCE_DIR}/Shaders
			${CMAKE_CURRENT_BINARY_DIR}/Shaders
)

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