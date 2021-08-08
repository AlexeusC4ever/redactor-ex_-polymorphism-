cmake_minimum_required(VERSION 3.5)

add_library(redactor STATIC 
	redactor.cpp
	redactor.h
	command.cpp
	command.h
	command_holder.cpp
	command_holder.h
	)
set_target_properties(
	redactor PROPERTIES
	CXX_STANDART 11
	CXX_STANDART_REQUIRED ON
)
target_include_directories(
	redactor
	PRIVATE			
	${CMAKE_CURRENT_BINARY_DIR}
)
