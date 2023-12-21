
set(COMMON_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/.. ${GRASSLAND_INCLUDE_DIRS})

message(STATUS "COMMON_INCLUDE_DIRS: ${COMMON_INCLUDE_DIRS}")

add_executable(GameX main.cpp)

add_subdirectory(utils)
add_subdirectory(shaders)
add_subdirectory(renderer)
add_subdirectory(application)

target_include_directories(GameX PUBLIC ${COMMON_INCLUDE_DIRS})
target_link_libraries(GameX PUBLIC ${GAMEX_LIBS})
