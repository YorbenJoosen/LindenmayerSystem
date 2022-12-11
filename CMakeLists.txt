cmake_minimum_required(VERSION 3.23)
project(lindenmayer_system)

set(CMAKE_CXX_STANDARD 17)

add_library(LindenmayerLib STATIC
        "src/lindenmayer-system/lindenmayer.cpp")

target_include_directories(LindenmayerLib PRIVATE "include/")

add_executable(TestSuite
        "test/main.cpp"
        "test/lindenmayer.cpp")

target_include_directories(TestSuite PRIVATE "include/")

target_link_libraries(TestSuite PRIVATE LindenmayerLib)

