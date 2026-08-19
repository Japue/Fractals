cmake_minimum_required(VERSION 3.10)
project(fractals)
 
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_POLICY_VERSION_MINIMUM 3.10)
set(CMAKE_WARN_DEPRECATED OFF CACHE BOOL "" FORCE)
get_filename_component(TARGET "${CMAKE_CURRENT_SOURCE_DIR}" NAME)
 
include(FetchContent)
 
#SFML
FetchContent_Declare(
    SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.0
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM
)
FetchContent_MakeAvailable(SFML)
 
#TOML
FetchContent_Declare(
    tomlplusplus
    GIT_REPOSITORY https://github.com/marzer/tomlplusplus.git
    GIT_TAG v3.4.0
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
)
FetchContent_MakeAvailable(tomlplusplus)
 
add_executable(${TARGET} main.cpp 
simple_tree_fractal/simple_tree.cpp 
h_fractal/h_fractal.cpp
num_sys_fractal/num_sys_fractal.cpp
koch_fractal/koch_fractal.cpp)

target_compile_definitions(${TARGET} PRIVATE _USE_MATH_DEFINES)
 
target_link_libraries(${TARGET} PRIVATE sfml-graphics sfml-window sfml-system tomlplusplus::tomlplusplus)
 
add_custom_command(TARGET ${TARGET} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_CURRENT_SOURCE_DIR}/config.toml"
        "$<TARGET_FILE_DIR:${TARGET}>/config.toml"
)