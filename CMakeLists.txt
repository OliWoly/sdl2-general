# https://chatgpt.com/share/67616d25-17c8-800b-9a53-cd2c320c49a9
# https://codevion.github.io/#!cpp/cmake.md

cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(sdl2-snake VERSION 1.0)

# Find SDL2 using Homebrew's path on Apple Silicon
set(CMAKE_PREFIX_PATH "/opt/homebrew")
find_package(SDL2 REQUIRED)

# Add the executable
add_executable(main src/main.cpp src/player.cpp)

# Include SDL2 headers
target_include_directories(main PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${SDL2_INCLUDE_DIRS}
)

# Link SDL2 to the executable
target_link_libraries(main ${SDL2_LIBRARIES})
