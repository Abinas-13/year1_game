cmake_minimum_required(VERSION 3.11)
project(pong)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Output directory
set(OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIRECTORY})

# SFML include + lib paths
set(SFML_INCS "${CMAKE_SOURCE_DIR}/lib/SFML/include")
link_directories("${CMAKE_SOURCE_DIR}/lib/SFML/lib")

# Build Pong
add_executable(pong main.cpp)

target_include_directories(pong PRIVATE ${SFML_INCS})
target_link_libraries(pong sfml-graphics sfml-window sfml-system)

add_custom_command(TARGET pong POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "${CMAKE_SOURCE_DIR}/lib/SFML/bin/sfml-graphics-2.dll"
    "${CMAKE_SOURCE_DIR}/lib/SFML/bin/sfml-window-2.dll"
    "${CMAKE_SOURCE_DIR}/lib/SFML/bin/sfml-system-2.dll"
    $<TARGET_FILE_DIR:pong>)
