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
        object/Bullet.cpp
        object/Player.cpp
        object/Werewolf.cpp
        object/Zombie.cpp
        state/StateIntro.cpp state/StateIntro.h
        state/StateMoon.cpp state/StateMoon.h
        calculations.cpp calculations.h
        object/GameObject.cpp object/GameObject.h
        state/GameState.cpp state/GameState.h
        sdlwrap.cpp sdlwrap.h
        sound/Sound.cpp sound/Sound.h
        StopWatch.cpp StopWatch.h
        Texture.cpp Texture.h
        engine/RenderSystem.cpp engine/RenderSystem.h
        engine/Engine.cpp engine/Engine.h engine/InputSystem.cpp engine/InputSystem.h object/Damageable.h object/Damageable.cpp object/Bullet.h object/Weapon.h object/Pistol.h object/Shotgun.h object/Uzi.h object/Player.h object/Zombie.h object/Werewolf.h object/Pistol.cpp object/Shotgun.cpp object/Uzi.cpp sound/Music.cpp sound/Music.h)

add_executable(TopDown ${SOURCE_FILES})
target_link_libraries(TopDown ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARIES} ${SDL2_MIXER_LIBRARIES})

