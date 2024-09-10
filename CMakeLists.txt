cmake_minimum_required(VERSION 3.20)
project(Examen)

set(INCL_DIR ${CMAKE_CURRENT_LIST_DIR}/include)
set(SRC_DIR ${CMAKE_CURRENT_LIST_DIR}/src/*.cpp)
set(PQXX_INC ${CMAKE_CURRENT_LIST_DIR}/libpqxx/7.9.2/include)
set(PQXX_LIB ${CMAKE_CURRENT_LIST_DIR}/libpqxx/7.9.2/lib)

find_package(wxWidgets REQUIRED COMPONENTS gl core base OPTIONAL_COMPONENTS net)
file(GLOB SOURCES ${SRC_DIR})
include(${wxWidgets_USE_FILE})

add_executable(main 
  main.cpp
  ${SOURCES}
)

target_link_libraries(main PRIVATE ${wxWidgets_LIBRARIES} ${PQXX_LIB}/libpqxx.a)

target_include_directories(main PRIVATE 
  ${wxWidgets_INCLUDE_DIRS}
  ${INCL_DIR}
  ${LIBQ_INCLUDE} 
  ${PQXX_INC} 
)
