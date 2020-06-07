cmake_minimum_required(VERSION 3.17)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(
    ../entt/single_include
    ../SFML/include
    ../spdlog/include
    ../box2d/include
)

link_directories(CMAKE_LIBRARY_OUTPUT_DIRECTORY)

set(SRC 
    src/main.cpp
    src/Engine.cpp
    src/Scene.cpp
    src/scenes/DummyScene.cpp
    src/scenes/GameScene.cpp
    src/scenes/LaboratoryScene.cpp
    src/systems/Box2dRenderSystem.cpp
    src/systems/PhysicsSystem.cpp
    src/systems/CameraFollowSystem.cpp
    src/systems/CharacterControlSystem.cpp
    src/utility/ContactListener.cpp
    src/utility/GameFactory.cpp
    src/utility/Maze.cpp
    src/utility/Keyboard.cpp
    src/utility/Physics.cpp
)

set(LIBS 
    sfml-graphics
    sfml-system
    sfml-window
    spdlog
    box2d
)



add_executable(doode ${SRC})

if(CMAKE_BUILD_TYPE STREQUAL "Release")
    target_compile_options(doode PUBLIC -Wall -Wextra -Werror -Wpedantic)
else(CMAKE_BUILD_TYPE STREQUAL "Release")
    target_compile_options(doode PUBLIC -Wall -Wextra -Wpedantic)
endif(CMAKE_BUILD_TYPE STREQUAL "Release")

target_link_libraries(doode ${LIBS})