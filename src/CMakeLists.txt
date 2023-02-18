add_subdirectory(tests)


add_executable(
    demo 
    main.cpp
)

target_include_directories(
    demo PRIVATE
    src/util
)


target_compile_features(
    demo PRIVATE 
    cxx_std_17
)

target_compile_options(
    demo PRIVATE
    -fsanitize=address
)

target_link_libraries(
    demo
    glog::glog
    gtest_main
)

target_link_options(
    demo PRIVATE 
    -fsanitize=address
)