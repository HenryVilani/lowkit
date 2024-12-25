cmake_minimum_required(VERSION 3.9.1)
project(CLowKit)
add_executable(cmake_lowkit_main main.cpp "core/process/thread/thread.h" "core/process/module/module.h" "core/memory/page/page.h")