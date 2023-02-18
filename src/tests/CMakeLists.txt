add_executable(
    thread_pool_test
    ThreadPoolTest.cpp
)

target_include_directories(
    thread_pool_test PRIVATE
    src/util
)


target_compile_features(
    thread_pool_test PRIVATE 
    cxx_std_17
)

target_compile_options(
    thread_pool_test PRIVATE
    -fsanitize=address
)

target_link_libraries(
    thread_pool_test
    glog::glog
    GTest::gtest_main
)

target_link_options(
    thread_pool_test PRIVATE 
    -fsanitize=address
)