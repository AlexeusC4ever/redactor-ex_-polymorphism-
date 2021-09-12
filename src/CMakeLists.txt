cmake_minimum_required(VERSION 3.5)

add_executable(main main.cpp)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/example.html
    ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)

include_directories(
	${CMAKE_CURRENT_SOURCE_DIR}/../redactor
)
target_link_libraries(main redactor)