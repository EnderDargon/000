cmake_minimum_required(VERSION 3.5)

project(Armor_Identifier LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenCV REQUIRED)

INCLUDE_DIRECTORIES(include)

add_subdirectory(src REQUIRED)

add_executable(Armor_Identifier
  test/Test.cpp
)

target_link_libraries(Armor_Identifier ${OpenCV_LIBS})
target_link_libraries(Armor_Identifier Armor_Identifier_LIB)

