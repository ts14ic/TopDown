cmake_minimum_required(VERSION 3.9)
project(TopDown)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_mixer REQUIRED)
include_directories(${SDL2_INCLUDE_DIR} ${SDL2_IMAGE_INCLUDE_DIRS} ${SDL2_MIXER_INCLUDE_DIRS})

set(SOURCE_FILES
        src/main.cpp
        src/StopWatch.cpp src/StopWatch.h
        src/calculations.cpp src/calculations.h
        src/state/StateIntro.cpp src/state/StateIntro.h
        src/state/StateMoon.cpp src/state/StateMoon.h
        src/state/GameState.cpp src/state/GameState.h
        src/sound/Sound.cpp src/sound/Sound.h
        src/sound/Music.cpp src/sound/Music.h
        src/Texture.cpp src/Texture.h
        src/sdlwrap.cpp src/sdlwrap.h
        src/engine/RenderSystem.cpp src/engine/RenderSystem.h
        src/engine/Engine.cpp src/engine/Engine.h
        src/engine/InputSystem.cpp src/engine/InputSystem.h
        src/object/GameObject.cpp src/object/GameObject.h
        src/object/Damageable.h src/object/Damageable.cpp
        src/object/Player.cpp src/object/Player.h
        src/object/Werewolf.cpp src/object/Werewolf.h
        src/object/Zombie.cpp src/object/Zombie.h
        src/object/Weapon.h
        src/object/Bullet.cpp src/object/Bullet.h
        src/object/Pistol.cpp src/object/Pistol.h
        src/object/Shotgun.cpp src/object/Shotgun.h
        src/object/Uzi.cpp src/object/Uzi.h)

add_executable(TopDown ${SOURCE_FILES})
target_link_libraries(TopDown ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARIES} ${SDL2_MIXER_LIBRARIES})

