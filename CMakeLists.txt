cmake_minimum_required(VERSION 3.16) 



project(chess_p2p VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB_RECURSE SOURCES
	"${CMAKE_SOURCE_DIR}/src/*.cpp"
)

add_executable(game_executable ${SOURCES})

target_include_directories(game_executable PRIVATE include)


target_include_directories(game_executable PRIVATE
	"${CMAKE_SOURCE_DIR}/libs/raylib_linux/include"
)

target_link_directories(game_executable PRIVATE
	"${CMAKE_SOURCE_DIR}/libs/raylib_linux/lib"
)

target_link_libraries(game_executable PRIVATE
    raylib
)
