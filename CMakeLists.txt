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
 
add_executable(${TARGET} main.cpp)
 
target_link_libraries(${TARGET} PRIVATE sfml-graphics sfml-window sfml-system tomlplusplus::tomlplusplus)
 
# On Windows, SFML builds as DLLs — copy them next to the executable after building
# so it can actually find them at runtime. This is a no-op on Linux/macOS.
if (WIN32)
    add_custom_command(TARGET ${TARGET} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_RUNTIME_DLLS:${TARGET}>
            $<TARGET_FILE_DIR:${TARGET}>
        COMMAND_EXPAND_LISTS
    )
endif()
 
add_custom_command(TARGET ${TARGET} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_CURRENT_SOURCE_DIR}/config.toml"
        "$<TARGET_FILE_DIR:${TARGET}>/config.toml"
)