project(pong)
cmake_minimum_required(VERSION 3.11)
# Require modern C++
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#### Setup Directories ####
#Main output directory
SET(OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/")
# Ouput all DLLs from all libs into main build folder
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIRECTORY})

#### Add External Dependencies ####
add_subdirectory("${CMAKE_SOURCE_DIR}/lib/SFML" "${CMAKE_BINARY_DIR}/SFML_build")
set(SFML_INCS "${CMAKE_SOURCE_DIR}/lib/SFML/include")
link_directories("${CMAKE_SOURCE_DIR}/lib/SFML/lib")

#### Practical 1 ####
add_executable(pong main.cpp)
target_include_directories(pong PRIVATE ${SFML_INCS})
target_link_libraries(pong sfml-graphics)
set_target_properties(pong 
    PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY
    ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$(Configuration)
)
add_custom_target(copy_resources ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/resources"
        "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/resources"
)
add_dependencies(pong copy_resources)
