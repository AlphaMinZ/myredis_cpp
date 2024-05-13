cmake_minimum_required(VERSION 3.6.2)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

project(myredis)

set(CMAKE_CXX_STANDARD 11)

include_directories(./myredis)

file(GLOB SRC ${CMAKE_CURRENT_SOURCE_DIR}/myredis/*.cc)

link_directories(${CMAKE_CURRENT_SOURCE_DIR}/lib)

find_package(ZLIB REQUIRED)

find_package(Boost REQUIRED)
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
endif()

find_package(MySQL REQUIRED)
if(MYSQL_FOUND)
    include_directories(${MYSQL_INCLUDE_DIR})
endif()

find_package(OpenSSL REQUIRED)
if(OPENSSL_FOUND)
    include_directories(${OPENSSL_INCLUDE_DIR})
endif()

find_library(PTHREAD pthread)

set(
    LIB_LIB
    pthread
    alpha
    ZLIB::ZLIB    
    yaml-cpp
    dl
    mysqlclient
    ${OPENSSL_LIBRARIES}
)

# add_executable(test tests/test.cc ${SRC})
add_executable(test_test tests/test.cc ${SRC})
target_link_libraries(test_test ${LIB_LIB}) 

SET(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/bin)
SET(CMAKE_BUILD_TYPE "Debug")  # 定义编译类型
SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -g2 -ggdb") # 定义Debug编译参数
SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall") # 定义Release编译参数