
set(COMMON_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/.. ${GRASSLAND_INCLUDE_DIRS})
set(COMMON_INCLUDE_DIRS ${COMMON_INCLUDE_DIRS} PARENT_SCOPE)

message(STATUS "COMMON_INCLUDE_DIRS: ${COMMON_INCLUDE_DIRS}")

add_executable(GameXMain main.cpp)
add_library(GameX GameX.cpp)

add_subdirectory(utils)
add_subdirectory(shaders)
add_subdirectory(renderer)
add_subdirectory(physics)
add_subdirectory(application)

target_include_directories(GameX PUBLIC ${COMMON_INCLUDE_DIRS})
target_link_libraries(GameX PUBLIC ${GAMEX_LIBS})

target_link_libraries(GameXMain PUBLIC GameX)
set(GAMEX_LIBS ${GAMEX_LIBS} PARENT_SCOPE)
