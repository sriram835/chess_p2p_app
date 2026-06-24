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


if (WIN32)


  set(RAYLIB_DIR "${CMAKE_SOURCE_DIR}/libs/raylib_win")
	target_include_directories(game_executable PRIVATE "${RAYLIB_DIR}/include")
	target_link_directories(game_executable PRIVATE "${RAYLIB_DIR}/lib")
    target_link_libraries(game_executable PRIVATE
        raylib
        winmm
        gdi32
        opengl32
    )

elseif (ANDROID) 
find_package(raylib REQUIRED)
target_link_libraries(game_executable PRIVATE raylib)

else()
target_include_directories(game_executable PRIVATE
	"${CMAKE_SOURCE_DIR}/libs/raylib_linux/include"
)

target_link_directories(game_executable PRIVATE
	"${CMAKE_SOURCE_DIR}/libs/raylib_linux/lib"
)

target_link_libraries(game_executable PRIVATE
    raylib
)


endif()
