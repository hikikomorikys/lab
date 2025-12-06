cmake_minimum_required(VERSION 3.10)
project(LibraryProject)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(PostgreSQL_ROOT "/opt/homebrew/opt/libpq")
set(PQXX_ROOT "/opt/homebrew/opt/libpqxx")

include_directories(
    src
    ${PostgreSQL_ROOT}/include
    ${PQXX_ROOT}/include
)

link_directories(
    ${PostgreSQL_ROOT}/lib
    ${PQXX_ROOT}/lib
)

file(GLOB SOURCES
    src/*.cpp
)

add_executable(library_app ${SOURCES})

target_link_libraries(library_app pq pqxx)