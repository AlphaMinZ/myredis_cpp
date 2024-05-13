cmake_minimum_required(VERSION 3.6.2)

project(alphaDB)

set(CMAKE_CXX_STANDARD 11)

include_directories(./myredis)

file(GLOB SRC ${CMAKE_CURRENT_SOURCE_DIR}/myredis/*.cc)

link_directories(${CMAKE_CURRENT_SOURCE_DIR}/lib)

find_package(ZLIB REQUIRED)

set(
    LIB_LIB
    pthread
    alpha
    ZLIB::ZLIB    
)

# add_executable(test_flock tests/test_flock.cc ${SRC})
# target_link_libraries(test_flock ${LIB_LIB}) 

SET(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/bin)
SET(CMAKE_BUILD_TYPE "Debug")  # 定义编译类型
SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -g2 -ggdb") # 定义Debug编译参数
SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall") # 定义Release编译参数