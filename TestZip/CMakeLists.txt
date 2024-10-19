cmake_minimum_required(VERSION 3.8)

project(Laba1 VERSION 1.0)

add_executable(${PROJECT_NAME} main.cpp Tests.cpp Tests/Tests_unique_ptr.cpp Tests/Tests_shared_ptr.cpp Tests/Tests_weak_ptr.cpp TypesOfData/Person.cpp TypesOfData/MyString.cpp)
#add_executable(${PROJECT_NAME} main.cpp)