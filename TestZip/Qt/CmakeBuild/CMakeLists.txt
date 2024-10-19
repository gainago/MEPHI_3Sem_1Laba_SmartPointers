
execute_process(COMMAND sudo apt install -y qtcreator qtbase5-dev)
project(helloworld LANGUAGES CXX)
set(CMAKE_CXX_FLAGS -Wall)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 REQUIRED COMPONENTS Widgets Core )
include_directories("../../")
include_directories(${Qt_INCLUDE_DIRS})

add_executable(helloworld
    ../../TypesOfData/MyString.cpp
    ../../TypesOfData/Person.cpp
    ../UIClassInt.cpp
    ../main.cpp
    
)

target_link_libraries(helloworld PRIVATE Qt5::Widgets)

