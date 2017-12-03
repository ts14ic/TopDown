cmake_minimum_required(VERSION 3.9)
project(TopDown)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_mixer REQUIRED)
include_directories(${SDL2_INCLUDE_DIR} ${SDL2_IMAGE_INCLUDE_DIRS} ${SDL2_MIXER_INCLUDE_DIRS})

set(SOURCE_FILES
        main.cpp
        StopWatch.cpp StopWatch.h
        calculations.cpp calculations.h
        state/StateIntro.cpp state/StateIntro.h
        state/StateMoon.cpp state/StateMoon.h
        state/GameState.cpp state/GameState.h
        sound/Sound.cpp sound/Sound.h
        sound/Music.cpp sound/Music.h
        Texture.cpp Texture.h
        sdlwrap.cpp sdlwrap.h
        engine/RenderSystem.cpp engine/RenderSystem.h
        engine/Engine.cpp engine/Engine.h
        engine/InputSystem.cpp engine/InputSystem.h
        object/GameObject.cpp object/GameObject.h
        object/Damageable.h object/Damageable.cpp
        object/Player.cpp object/Player.h
        object/Werewolf.cpp object/Werewolf.h
        object/Zombie.cpp object/Zombie.h
        object/Weapon.h
        object/Bullet.cpp object/Bullet.h
        object/Pistol.cpp object/Pistol.h
        object/Shotgun.cpp object/Shotgun.h
        object/Uzi.cpp object/Uzi.h)

add_executable(TopDown ${SOURCE_FILES})
target_link_libraries(TopDown ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARIES} ${SDL2_MIXER_LIBRARIES})

