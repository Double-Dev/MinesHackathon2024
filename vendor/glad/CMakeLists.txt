cmake_minimum_required(VERSION 3.0)
project(GLAD)

# Setting up static library.
add_library( glad STATIC
	include/glad/glad.h
	src/glad.c )
target_include_directories(glad PUBLIC include/)