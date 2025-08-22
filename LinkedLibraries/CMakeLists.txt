cmake_minimum_required(VERSION 3.10)
project(MySharedLibrary)

set(CMAKE_CXX_STANDARD 17)

# Create the shared library from sources
add_library(mylib SHARED src/mylib.cpp)

# Optionally specify include directories
#target_include_directories(mylib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)

# Create an executable that uses the shared library
add_executable(my_app main.cpp)

# Link the executable with the shared library
#target_link_libraries(my_app PRIVATE mylib)

# Link only against dl (not against libmylib.so!)
target_link_libraries(my_app PRIVATE dl)