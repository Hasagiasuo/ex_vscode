cmake_minimum_required(VERSION 3.20)
project(Examen)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(INCL_DIR ${CMAKE_CURRENT_LIST_DIR}/include)
set(SRC_DIR ${CMAKE_CURRENT_LIST_DIR}/src)

find_package(wxWidgets REQUIRED COMPONENTS gl core base richtext OPTIONAL_COMPONENTS net)
include(${wxWidgets_USE_FILE})
file(GLOB SOURCES ${SRC_DIR}/*.cpp)

add_executable(main 
  main.cpp  
  ${SOURCES}
)

target_link_libraries(main PRIVATE 
  ${wxWidgets_LIBRARIES}
)
target_include_directories(main PRIVATE 
  ${wxWidgets_INCLUDE_DIRS}
  ${INCL_DIR}
)
