cmake_minimum_required(VERSION 3.22)

set(CMAKE_TOOLCHAIN_FILE ${CMAKE_CURRENT_SOURCE_DIR}/external/grassland/external/vcpkg/scripts/buildsystems/vcpkg.cmake)

project(GameX)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(external/grassland)

add_subdirectory(src/GameX)
