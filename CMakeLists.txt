cmake_minimum_required(VERSION 3.9)
project(TopDown)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_mixer REQUIRED)
find_package(RapidJSON REQUIRED)
include_directories(${SDL2_INCLUDE_DIR}
        ${SDL2_IMAGE_INCLUDE_DIRS}
        ${SDL2_MIXER_INCLUDE_DIRS}
        ${RapidJSON_INCLUDE_DIRS})

set(SOURCE_FILES
        src/main.cpp
        src/timer/StopWatch.cpp src/timer/StopWatch.h
        src/utils/calculations.cpp src/utils/calculations.h
        src/state/StateIntro.cpp src/state/StateIntro.h
        src/state/StateMoon.cpp src/state/StateMoon.h
        src/state/GameState.h
        src/sound/Sound.cpp src/sound/Sound.h
        src/sound/Music.cpp src/sound/Music.h
        src/texture/Texture.cpp src/texture/Texture.h
        src/engine/RenderContext.cpp src/engine/RenderContext.h
        src/engine/Engine.cpp src/engine/Engine.h
        src/engine/InputContext.cpp src/engine/InputContext.h
        src/object/GameObject.cpp src/object/GameObject.h
        src/object/Damageable.h src/object/Damageable.cpp
        src/object/Player.cpp src/object/Player.h
        src/object/Werewolf.cpp src/object/Werewolf.h
        src/object/Zombie.cpp src/object/Zombie.h
        src/object/Weapon.h
        src/object/Bullet.cpp src/object/Bullet.h
        src/object/Pistol.cpp src/object/Pistol.h
        src/object/Shotgun.cpp src/object/Shotgun.h
        src/object/Uzi.cpp src/object/Uzi.h
        src/assets/Assets.cpp src/assets/Assets.h
        src/engine/GState.h
        src/utils/Circle.cpp src/utils/Circle.h)

add_executable(TopDown ${SOURCE_FILES})
target_link_libraries(TopDown
        ${SDL2_LIBRARY}
        ${SDL2_IMAGE_LIBRARIES}
        ${SDL2_MIXER_LIBRARIES})
