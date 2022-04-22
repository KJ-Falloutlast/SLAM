cmake_minimum_required(VERSION 3.10)
project(demo1)
aux_source_directory(./ SRC)
add_executable(demo ${SRC})