# CMakeLists.txt

cmake_minimum_required(VERSION 3.10)
project(LibraryCLI)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
find_package(redis++ REQUIRED)
find_package(hiredis REQUIRED)

include_directories(
    ${REDIS++_INCLUDE_DIRS}
    ${HIREDIS_INCLUDE_DIRS}
    include
    /usr/local/include
)
add_executable(LibraryCLI
    src/main.cpp
	src/AuditObserver.cpp
	src/BookFactory.cpp
    src/Book.cpp
    src/Library.cpp
    src/RedisClient.cpp
    src/Logger.cpp
    src/Authenticator.cpp
)

#target_link_libraries(LibraryCLI
#    ${REDIS++_LIBRARIES}
#    ${HIREDIS_LIBRARIES}
#    pthread
#)

target_link_libraries(LibraryCLI PRIVATE redis++ hiredis pthread)
