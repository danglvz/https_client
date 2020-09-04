
add_executable(tests "")

find_package(Threads REQUIRED)

find_package(GTest REQUIRED)


target_sources(tests PRIVATE
        client_interface_tests.cpp
        https_client_web_test.cpp
        http_client_web_test.cpp
        runAllTests.cpp)
target_include_directories(tests PRIVATE 
                                ${CMAKE_CURRENT_LIST_DIR} 
                                ${PROJECT_SOURCE_DIR}/include  
                                ${GTEST_INCLUDE_DIR})
target_link_libraries(tests PRIVATE
        https_client
        gtest_main
        gtest
        Threads::Threads)
add_test(tests tests)


