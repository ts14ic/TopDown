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
        src/utils/math/math.cpp src/utils/math/math.h
        src/game/state/StateIntro.cpp src/game/state/StateIntro.h
        src/game/state/StateMoon.cpp src/game/state/StateMoon.h src/game/state/StateMoon_parseLevelData.cpp
        src/game/state/GameState.h
        src/engine/resources/Sound.cpp src/engine/resources/Sound.h
        src/engine/resources/Music.cpp src/engine/resources/Music.h
        src/engine/resources/Texture.cpp src/engine/resources/Texture.h
        src/engine/GraphicContext.cpp src/engine/GraphicContext.h
        src/engine/DefaultEngine.cpp src/engine/DefaultEngine.h src/engine/DefaultEngine_loadMedia.cpp
        src/game/object/GameObject.cpp src/game/object/GameObject.h
        src/game/object/Damageable.h src/game/object/Damageable.cpp
        src/game/object/Player.cpp src/game/object/Player.h
        src/game/object/Werewolf.cpp src/game/object/Werewolf.h
        src/game/object/Zombie.cpp src/game/object/Zombie.h
        src/game/object/WeaponBuilder.cpp src/game/object/WeaponBuilder.h
        src/game/object/Weapon.h src/game/object/Weapon.cpp
        src/game/object/Bullet.cpp src/game/object/Bullet.h
        src/engine/resources/Resources.cpp src/engine/resources/Resources.h
        src/engine/GState.h
        src/shape/Circle.cpp src/shape/Circle.h
        src/utils/json/getValue.h src/utils/json/getValue.cpp
        src/engine/Random.cpp src/engine/Random.h
        src/utils/demangleTypeName.cpp src/utils/demangleTypeName.h
        src/engine/Engine.cpp src/engine/Engine.h
        src/sdl/SdlInputContext.cpp src/sdl/SdlInputContext.h
        src/utils/random/Mt19937Random.h src/utils/random/Mt19937Random.cpp
        src/sdl/SdlGraphicContext.cpp src/sdl/SdlGraphicContext.h
        src/sdl/SdlResources.cpp src/sdl/SdlResources.h
        src/sdl/SdlTexture.cpp src/sdl/SdlTexture.h
        src/engine/ContextInjector.cpp src/engine/ContextInjector.h
        src/sdl/SdlContextInjector.cpp src/sdl/SdlContextInjector.h
        src/shape/Box.cpp src/shape/Box.h
        src/shape/Color.cpp src/shape/Color.h
        src/utils/file/readFile.cpp src/utils/file/readFile.h
        src/utils/json/parseJson.cpp src/utils/json/parseJson.h
        src/engine/AudioContext.cpp src/engine/AudioContext.h
        src/sdl/SdlAudioContext.cpp src/sdl/SdlAudioContext.h
        src/sdl/SdlSound.cpp src/sdl/SdlSound.h
        src/sdl/SdlMusic.cpp src/sdl/SdlMusic.h
        src/engine/Timer.cpp src/engine/Timer.h
        src/engine/Clock.cpp src/engine/Clock.h
        src/sdl/SdlClock.cpp src/sdl/SdlClock.h
        src/engine/input/InputContext.cpp src/engine/input/InputContext.h
        src/engine/input/WindowEventHandler.cpp src/engine/input/WindowEventHandler.h
        src/engine/input/KeyboardEventHandler.cpp src/engine/input/KeyboardEventHandler.h
        src/engine/input/MouseEventHandler.cpp src/engine/input/MouseEventHandler.h
        src/engine/input/EventHandler.h
        src/engine/input/WindowEvent.h src/engine/input/WindowEvent.cpp
        src/engine/input/KeyboardEvent.cpp src/engine/input/KeyboardEvent.h
        src/game/state/GameState.cpp src/engine/input/MouseEvent.cpp
        src/engine/input/MouseEvent.h src/engine/input/KeyboardKey.h
        src/sdl/SdlInputContext_transformSdlKeyCode.cpp src/sdl/SdlInputContext_transformSdlKeyCode.h
        )

add_executable(TopDown ${SOURCE_FILES})
target_link_libraries(TopDown
        ${SDL2_LIBRARY}
        ${SDL2_IMAGE_LIBRARIES}
        ${SDL2_MIXER_LIBRARIES})
