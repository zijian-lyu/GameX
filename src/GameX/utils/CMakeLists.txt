set(LIB_NAME GameXUtils)

file(GLOB_RECURSE SOURCES *.cpp *.h)

add_library(${LIB_NAME} ${SOURCES})

target_include_directories(${LIB_NAME} PUBLIC ${COMMON_INCLUDE_DIRS})
target_link_libraries(${LIB_NAME} PUBLIC grassland)

list(APPEND GAMEX_LIBS ${LIB_NAME})
set(GAMEX_LIBS ${GAMEX_LIBS} PARENT_SCOPE)
