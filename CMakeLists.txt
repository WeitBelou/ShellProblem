cmake_minimum_required(VERSION 3.5)
project(ShellProblem)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_LIST_DIR}/bin")
set(CMAKE_INCLUDE_CURRENT_DIR ON)
include_directories(src)

#Boost
find_package(Boost COMPONENTS
        program_options
        filesystem
        REQUIRED)
include_directories(${Boost_INCLUDE_DIR})

#Download and install GTest
configure_file(CMakeLists.txt.in
        googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download)
execute_process(COMMAND ${CMAKE_COMMAND} --build .
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download)
add_subdirectory(${CMAKE_BINARY_DIR}/googletest-src
        ${CMAKE_BINARY_DIR}/googletest-build)

#Find and setup deal ii
find_package(deal.II REQUIRED
        HINTS $ENV{DEAL_II_DIR})
deal_ii_initialize_cached_variables()

file(GLOB_RECURSE SOURCES "${CMAKE_CURRENT_LIST_DIR}/src/*.cpp")
add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})
deal_ii_setup_target(${PROJECT_NAME})
