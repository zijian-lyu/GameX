file(GLOB_RECURSE SOURCES "*.cpp" "*.h" "*.hpp" "*.c" "*.cc" "*.hh" "*.cxx" "*.hxx")

add_executable(GameXTest ${SOURCES})

enable_testing()

find_package(GTest CONFIG REQUIRED)
target_link_libraries(GameXTest PRIVATE GTest::gtest GTest::gtest_main ${GAMEX_LIBS} GameBallLib)
target_include_directories(GameXTest PRIVATE ${COMMON_INCLUDE_DIRS})

add_test(AllTestsInMain GameXTest)
