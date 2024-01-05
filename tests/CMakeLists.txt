cmake_minimum_required(VERSION 3.27)
include(FetchContent)
project(LRU_Cache_Test)
set(CMAKE_CXX_STANDARD 14)

FetchContent_Declare(
  googletest
  # Specify the commit you depend on and update it regularly.
  URL https://github.com/google/googletest/archive/5376968f6948923e2411081fd9372e71a59d8e77.zip
)
FetchContent_MakeAvailable(googletest)
add_executable(LRU_Cache_Test test.cpp ../LRUCache.cpp ../LRUCache.h)
target_link_libraries(LRU_Cache_Test gtest_main)