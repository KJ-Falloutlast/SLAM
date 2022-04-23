cmake_minimum_required(VERSION 3.10)
project(fuc)
aux_source_directory(. DIR_SRCS)
add_executable(demo ${DIR_SRCS})
add_subdirectory(math)#只有添加了math才能够检测到myfunctions这个链接库
target_link_libraries(demo myfuntions)