
add_executable(tests "")

add_subdirectory(googletest)
target_sources(tests PRIVATE client_interface_tests.cpp web_tests.cpp runAllTests.cpp)
target_include_directories(tests PRIVATE ${CMAKE_CURRENT_LIST_DIR} ${PROJECT_SOURCE_DIR}/src  ${GTEST_INCLUDE_DIR})
target_link_libraries(tests PRIVATE
        https_client
        gtest_main
        gtest)
add_test(tests tests)


