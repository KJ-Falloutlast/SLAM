project(sayhello)
cmake_minimum_required(VERSION 3.10)
set(CMAKE_BUILD_TYPE "RELEASE")
#提供头文件的路径
include_directories(${PROJECT_SOURCE_DIR}/include)
#设置生成的可执行文件的输出路径
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
#设置生成的动态库文件的输出路径
set(LIBRARY_OUTPUT_PATH $${PROJECT_SOURCE_DIR}/lib)
#设置动态库文件文件路径
set(LIBHELLO_SRC src/hello.cpp)
#设置动态链接库
add_library(hello SHARED ${LIBHELLO_SRC})
#或者直接使用路径添加动态连接件库
add_library(hello SHARED src/hello.cpp)
#生成可执行文件
add_executable(sayHello src/useHello.cpp)
#将可执行文件链接到动态库上
target_link_libraries(sayhello hello)