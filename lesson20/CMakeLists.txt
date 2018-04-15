cmake_minimum_required(VERSION 3.5)
project(20_thread)

set(CMAKE_CXX_STANDARD 14)

find_package(Threads)

add_executable(thread thread.cpp)

target_link_libraries(thread
  ${CMAKE_THREAD_LIBS_INIT}
  )

add_executable(parallel_for parallel_for.cpp)

target_link_libraries(parallel_for
  tbb
  )
