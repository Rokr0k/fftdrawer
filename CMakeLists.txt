cmake_minimum_required(VERSION 3.17)

project(fftdrawer)

find_package(PkgConfig REQUIRED)
pkg_check_modules(SDL REQUIRED sdl SDL_gfx)

add_executable(fftdrawer)

add_subdirectory("src")

target_include_directories(fftdrawer PRIVATE ${SDL_INCLUDE_DIRS})
target_link_libraries(fftdrawer ${SDL_LIBRARIES} m)