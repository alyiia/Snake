cmake_minimum_required(VERSION 3.26)
project(Snake)

set(CMAKE_CXX_STANDARD 17)

set(RAYLIB_DIR D:/Library/raylib-5.0_win32_mingw-w64)
set(INC_DIR ${RAYLIB_DIR}/include)
set(LINK_DIR ${RAYLIB_DIR}/lib)


include_directories(${INC_DIR})
link_directories(${LINK_DIR})

add_executable(${PROJECT_NAME} main.cpp
        Game.cpp
        Game.h)

target_link_libraries(${PROJECT_NAME} raylib winmm)
