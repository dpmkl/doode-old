cmake_minimum_required(VERSION 3.17)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(
    ../entt/single_include
    ../SFML/include
    ../spdlog/include
)

link_directories(CMAKE_LIBRARY_OUTPUT_DIRECTORY)

set(SRC 
    src/main.cpp
    src/Engine.cpp
    src/Scene.cpp
    src/scenes/DummyScene.cpp
    src/scenes/GameScene.cpp
    src/utility/Maze.cpp
)

set(LIBS 
    sfml-graphics
    sfml-system
    sfml-window
    spdlog
)

add_executable(doode ${SRC})
target_compile_options(doode PUBLIC -Wall -Wextra -Werror -Wpedantic)
target_link_libraries(doode ${LIBS})