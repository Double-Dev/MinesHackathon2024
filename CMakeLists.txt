cmake_minimum_required(VERSION 3.16)
project(ParticleDemo)

# Load headers.
file(GLOB_RECURSE HEADERS
	${ParticleDemo_SOURCE_DIR}/src/*.hpp
)
# Load sources.
file(GLOB_RECURSE SOURCES
	${ParticleDemo_SOURCE_DIR}/src/*.cpp
)

# Define the executable/target.
add_executable( ${PROJECT_NAME} ${HEADERS} ${SOURCES} )
set_target_properties( ${PROJECT_NAME} PROPERTIES OUTPUT_NAME "ParticleDemo" )
set_target_properties( ${PROJECT_NAME} PROPERTIES CXX_STANDARD 17 )

# Include /src path.
target_include_directories( ${PROJECT_NAME} PUBLIC ${ParticleDemo_SOURCE_DIR}/src )
# Include vendor /includes directories.
target_include_directories( ${PROJECT_NAME} SYSTEM PUBLIC
	${ParticleDemo_SOURCE_DIR}/vendor/glad/include
	${ParticleDemo_SOURCE_DIR}/vendor/glfw/include
	${ParticleDemo_SOURCE_DIR}/vendor/glm
	${ParticleDemo_SOURCE_DIR}/vendor/imgui
	${ParticleDemo_SOURCE_DIR}/vendor/stb
)
# Setup pre-compiled headers.
# target_precompile_headers( ${PROJECT_NAME} PUBLIC ${ParticleDemo_SOURCE_DIR}/src/pch.hpp )

# Linking GLFW.
add_subdirectory( ${ParticleDemo_SOURCE_DIR}/vendor/glfw )
target_link_libraries( ${PROJECT_NAME} glfw )
# Linking GLAD.
add_subdirectory( ${ParticleDemo_SOURCE_DIR}/vendor/glad )
target_link_libraries( ${PROJECT_NAME} glad )
# Linking ImGui.
add_subdirectory( ${ParticleDemo_SOURCE_DIR}/vendor/imgui )
target_link_libraries( ${PROJECT_NAME} imgui )
