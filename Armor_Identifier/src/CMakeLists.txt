cmake_minimum_required(VERSION 3.5)

set(LIBARMOR_IDENTIFIER_SRC armor_Detector.cpp armor_Identifier.cpp number_Identifier.cpp)


find_package(OpenCV REQUIRED)
add_library(Armor_Identifier_LIB SHARED ${LIBARMOR_IDENTIFIER_SRC})

target_link_libraries(Armor_Identifier_LIB ${OpenCV_LIBS})


