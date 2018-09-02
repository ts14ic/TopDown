cmake_minimum_required(VERSION 3.9)
project(TopDown)

set(CMAKE_CXX_STANDARD 14)
# GCC specific
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -rdynamic -Wall -pedantic")

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_mixer REQUIRED)
find_package(RapidJSON REQUIRED)
include_directories(
        ${PROJECT_SOURCE_DIR}/src
        ${SDL2_INCLUDE_DIR}
        ${SDL2_IMAGE_INCLUDE_DIRS}
        ${SDL2_MIXER_INCLUDE_DIRS}
        ${RapidJSON_INCLUDE_DIRS}
)

set(SOURCE_FILES
        src/main.cpp
        src/io/json/json.h src/io/json/json.cpp src/io/json/json.tcc
        src/io/files/files.cpp src/io/files/files.h
        src/utils/sys/demangle_type_name.cpp src/utils/sys/demangle_type_name.h
        src/utils/sys/abort_handlers.cpp src/utils/sys/abort_handlers.h
        src/random/Mt19937Random.h src/random/Mt19937Random.cpp
        src/engine/graphic/Texture.cpp src/engine/graphic/Texture.h
        src/engine/graphic/Graphic.cpp src/engine/graphic/Graphic.h
        src/engine/Engine.cpp src/engine/Engine.h
        src/engine/random/Random.cpp src/engine/random/Random.h
        src/engine/geometry/maths.cpp src/engine/geometry/maths.h
        src/engine/geometry/Circle.cpp src/engine/geometry/Circle.h
        src/engine/geometry/Box.cpp src/engine/geometry/Box.h
        src/engine/geometry/Color.cpp src/engine/geometry/Color.h
        src/engine/geometry/Point2.h
        src/engine/geometry/Size2.h
        src/engine/geometry/Speed2.h
        src/engine/audio/Audio.cpp src/engine/audio/Audio.h
        src/engine/clock/Clock.cpp src/engine/clock/Clock.h
        src/engine/input/Input.cpp src/engine/input/Input.h
        src/engine/input/WindowEventHandler.cpp src/engine/input/WindowEventHandler.h
        src/engine/input/KeyboardEventHandler.cpp src/engine/input/KeyboardEventHandler.h
        src/engine/input/MouseEventHandler.cpp src/engine/input/MouseEventHandler.h
        src/engine/input/EventHandler.h
        src/engine/input/WindowEvent.h src/engine/input/WindowEvent.cpp
        src/engine/input/KeyboardEvent.cpp src/engine/input/KeyboardEvent.h
        src/engine/input/MouseScrollEvent.h src/engine/input/KeyboardKey.h
        src/engine/input/MousePointEvent.cpp src/engine/input/MousePointEvent.h
        src/engine_sdl/input/SdlInput.cpp src/engine_sdl/input/SdlInput.h
        src/engine_sdl/graphic/SdlGraphic.cpp src/engine_sdl/graphic/SdlGraphic.h
        src/engine_sdl/SdlEngine.cpp src/engine_sdl/SdlEngine.h
        src/engine_sdl/graphic/SdlTexture.cpp src/engine_sdl/graphic/SdlTexture.h
        src/engine_sdl/audio/SdlAudio.cpp src/engine_sdl/audio/SdlAudio.h
        src/engine_sdl/audio/SdlSound.cpp src/engine_sdl/audio/SdlSound.h
        src/engine_sdl/audio/SdlMusic.cpp src/engine_sdl/audio/SdlMusic.h
        src/engine_sdl/clock/SdlClock.cpp src/engine_sdl/clock/SdlClock.h
        src/engine_sdl/SdlGuard.cpp src/engine_sdl/SdlGuard.h
        src/game/state/StateIntro.cpp src/game/state/StateIntro.h
        src/game/state/StateMoon.cpp src/game/state/StateMoon.h
        src/game/state/GameState.h
        src/game/GameImpl.cpp src/game/GameImpl.h
        src/game/object/GameObject.cpp src/game/object/GameObject.h
        src/game/object/Damageable.h src/game/object/Damageable.cpp
        src/game/object/Player.cpp src/game/object/Player.h
        src/game/object/Werewolf.cpp src/game/object/Werewolf.h
        src/game/object/Zombie.cpp src/game/object/Zombie.h
        src/game/object/WeaponBuilder.cpp src/game/object/WeaponBuilder.h
        src/game/object/Weapon.h src/game/object/Weapon.cpp
        src/game/object/Bullet.cpp src/game/object/Bullet.h
        src/game/StateId.h
        src/game/Game.cpp src/game/Game.h
        src/game/timer/Timer.cpp src/game/timer/Timer.h
        src/game/state/GameState.cpp src/engine/input/MouseScrollEvent.cpp
        src/game/components/Transform.h)

add_executable(TopDown ${SOURCE_FILES})
target_link_libraries(TopDown
        ${SDL2_LIBRARY}
        ${SDL2_IMAGE_LIBRARIES}
        ${SDL2_MIXER_LIBRARIES})
