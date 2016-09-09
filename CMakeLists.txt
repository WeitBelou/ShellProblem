cmake_minimum_required(VERSION 3.5)
project(ShellProblem)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
set(CMAKE_INCLUDE_CURRENT_DIR ON)
include_directories(src)

#Boost
find_package(Boost COMPONENTS
        program_options
        filesystem
        REQUIRED)

include_directories(${Boost_INCLUDE_DIR})

#Find and setup deal ii
find_package(deal.II REQUIRED
        HINTS $ENV{DEAL_II_DIR})
deal_ii_initialize_cached_variables()

file(GLOB_RECURSE SOURCES "${CMAKE_CURRENT_LIST_DIR}/src/*.cpp")
add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})
deal_ii_setup_target(${PROJECT_NAME})
