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

set(HDR
    src/Engine.hpp
    src/Types.hpp
    src/Scene.hpp
    src/Services.hpp
    src/systems/Box2dRenderSystem.hpp
    src/systems/MovingPlatformSystem.hpp
    src/systems/CharacterControlSystem.hpp
    src/systems/SystemBase.hpp
    src/systems/CameraFollowSystem.hpp
    src/systems/PhysicsSystem.hpp
    src/scenes/GameScene.hpp
    src/scenes/DummyScene.hpp
    src/scenes/LaboratoryScene.hpp
    src/utility/ContactListener.hpp
    src/utility/ContactFilter.hpp
    src/utility/GameFactory.hpp
    src/utility/Gamepad.hpp
    src/utility/Physics.hpp
    src/utility/Keyboard.hpp
    src/utility/Maze.hpp
    src/utility/Random.hpp
    src/components/CollisionResponseComponent.hpp
    src/components/Tags.hpp
    src/components/PhysicsComponent.hpp
    src/components/CharacterControlComponent.hpp
    src/components/MovingPlatformComponent.hpp
)

set(SRC 
    src/main.cpp
    src/Engine.cpp
    src/Scene.cpp
    src/scenes/DummyScene.cpp
    src/scenes/GameScene.cpp
    src/scenes/LaboratoryScene.cpp
    src/systems/Box2dRenderSystem.cpp
    src/systems/CameraFollowSystem.cpp
    src/systems/CharacterControlSystem.cpp
    src/systems/MovingPlatformSystem.cpp
    src/systems/PhysicsSystem.cpp
    src/utility/ContactFilter.cpp
    src/utility/ContactListener.cpp
    src/utility/GameFactory.cpp
    src/utility/Gamepad.cpp
    src/utility/Maze.cpp
    src/utility/Keyboard.cpp
    src/utility/Physics.cpp
    src/utility/Random.cpp
)

#list(APPEND SRC ${HDR})

set(LIBS 
    sfml-graphics
    sfml-system
    sfml-window
    spdlog
    box2d
)



add_executable(doode ${SRC} ${HDR})

if(CMAKE_BUILD_TYPE STREQUAL "Release")
#    target_compile_options(doode PUBLIC -Wall -Wextra -Werror -Wpedantic)
else(CMAKE_BUILD_TYPE STREQUAL "Release")
#    target_compile_options(doode PUBLIC -Wall -Wextra -Wpedantic)
endif(CMAKE_BUILD_TYPE STREQUAL "Release")

target_link_libraries(doode ${LIBS})
