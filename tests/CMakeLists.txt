include(FetchContent)

FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG release-1.12.1
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
        custom_ranges_tests
        custom_ranges_tests.cpp
)

target_link_libraries(
        custom_ranges_tests
        my_own_ranges
        GTest::gtest_main
)

target_include_directories(custom_ranges_tests PUBLIC ${PROJECT_SOURCE_DIR})

include(GoogleTest)

gtest_discover_tests(custom_ranges_tests)