cmake_minimum_required(VERSION 3.9)
project(TopDown)

set(CMAKE_CXX_STANDARD 14)
# GCC specific
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic")

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
        src/math/math.cpp src/math/math.h
        src/state/StateIntro.cpp src/state/StateIntro.h
        src/state/StateMoon.cpp src/state/StateMoon.h src/state/StateMoon_parseLevelData.cpp
        src/state/GameState.h
        src/sdl/Sound.cpp src/sdl/Sound.h
        src/sdl/Music.cpp src/sdl/Music.h
        src/assets/Texture.cpp src/assets/Texture.h
        src/engine/GraphicContext.cpp src/engine/GraphicContext.h
        src/engine/DefaultEngine.cpp src/engine/DefaultEngine.h src/engine/DefaultEngine_loadMedia.cpp
        src/engine/InputContext.cpp src/engine/InputContext.h
        src/object/GameObject.cpp src/object/GameObject.h
        src/object/Damageable.h src/object/Damageable.cpp
        src/object/Player.cpp src/object/Player.h
        src/object/Werewolf.cpp src/object/Werewolf.h
        src/object/Zombie.cpp src/object/Zombie.h
        src/object/WeaponBuilder.cpp src/object/WeaponBuilder.h
        src/object/Weapon.h src/object/Weapon.cpp
        src/object/Bullet.cpp src/object/Bullet.h
        src/assets/Assets.cpp src/assets/Assets.h
        src/engine/GState.h
        src/shape/Circle.cpp src/shape/Circle.h
        src/json/getValue.h src/json/getValue.cpp
        src/engine/Random.cpp src/engine/Random.h
        src/utils/demangle.cpp src/utils/demangle.h
        src/engine/Engine.cpp src/engine/Engine.h
        src/sdl/SdlInputContext.cpp src/sdl/SdlInputContext.h
        src/random/Mt19937Random.h src/random/Mt19937Random.cpp
        src/sdl/SdlGraphicContext.cpp src/sdl/SdlGraphicContext.h
        src/sdl/SdlAssets.cpp src/sdl/SdlAssets.h
        src/sdl/SdlTexture.cpp src/sdl/SdlTexture.h
        src/engine/ContextFactory.cpp src/engine/ContextFactory.h
        src/sdl/SdlContextFactory.cpp src/sdl/SdlContextFactory.h
        src/shape/Box.cpp src/shape/Box.h
        src/shape/Color.cpp src/shape/Color.h src/file/readFile.cpp src/file/readFile.h src/json/parseJson.cpp src/json/parseJson.h)

add_executable(TopDown ${SOURCE_FILES})
target_link_libraries(TopDown
        ${SDL2_LIBRARY}
        ${SDL2_IMAGE_LIBRARIES}
        ${SDL2_MIXER_LIBRARIES})
