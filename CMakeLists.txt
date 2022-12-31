cmake_minimum_required(VERSION 3.17)

project(fourierdrawer)

find_package(PkgConfig REQUIRED)
pkg_check_modules(SDL REQUIRED sdl SDL_gfx)

add_executable(fourierdrawer)

add_subdirectory("src")

target_include_directories(fourierdrawer PRIVATE ${SDL_INCLUDE_DIRS})
target_link_libraries(fourierdrawer ${SDL_LIBRARIES} m)
