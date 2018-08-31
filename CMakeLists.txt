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
        src/math/maths.cpp src/math/maths.h
        src/game/state/StateIntro.cpp src/game/state/StateIntro.h
        src/game/state/StateMoon.cpp src/game/state/StateMoon.h src/game/state/StateMoon_parse_level_data.cpp
        src/game/state/GameState.h
        src/engine/audio/Sound.cpp src/engine/audio/Sound.h
        src/engine/audio/Music.cpp src/engine/audio/Music.h
        src/engine/graphic/Texture.cpp src/engine/graphic/Texture.h
        src/engine/graphic/GraphicContext.cpp src/engine/graphic/GraphicContext.h
        src/game/GameImpl.cpp src/game/GameImpl.h src/game/GameImpl_load_resources.cpp
        src/game/object/GameObject.cpp src/game/object/GameObject.h
        src/game/object/Damageable.h src/game/object/Damageable.cpp
        src/game/object/Player.cpp src/game/object/Player.h
        src/game/object/Werewolf.cpp src/game/object/Werewolf.h
        src/game/object/Zombie.cpp src/game/object/Zombie.h
        src/game/object/WeaponBuilder.cpp src/game/object/WeaponBuilder.h
        src/game/object/Weapon.h src/game/object/Weapon.cpp
        src/game/object/Bullet.cpp src/game/object/Bullet.h
        src/engine/Resources.cpp src/engine/Resources.h
        src/game/StateId.h
        src/engine/graphic/Circle.cpp src/engine/graphic/Circle.h
        src/io/json/get_value.h src/io/json/get_value.cpp
        src/engine/random/Random.cpp src/engine/random/Random.h
        src/utils/sys/demangle_type_name.cpp src/utils/sys/demangle_type_name.h
        src/game/Game.cpp src/game/Game.h
        src/sdl/SdlInputContext.cpp src/sdl/SdlInputContext.h
        src/random/Mt19937Random.h src/random/Mt19937Random.cpp
        src/sdl/SdlGraphicContext.cpp src/sdl/SdlGraphicContext.h
        src/sdl/SdlResources.cpp src/sdl/SdlResources.h
        src/sdl/SdlTexture.cpp src/sdl/SdlTexture.h
        src/engine/ContextInjector.cpp src/engine/ContextInjector.h
        src/sdl/SdlContextInjector.cpp src/sdl/SdlContextInjector.h
        src/engine/graphic/Box.cpp src/engine/graphic/Box.h
        src/engine/graphic/Color.cpp src/engine/graphic/Color.h
        src/io/files/files.cpp src/io/files/files.h
        src/io/json/parse_json.cpp src/io/json/parse_json.h
        src/engine/audio/AudioContext.cpp src/engine/audio/AudioContext.h
        src/sdl/SdlAudioContext.cpp src/sdl/SdlAudioContext.h
        src/sdl/SdlSound.cpp src/sdl/SdlSound.h
        src/sdl/SdlMusic.cpp src/sdl/SdlMusic.h
        src/game/timer/Timer.cpp src/game/timer/Timer.h
        src/engine/clock/Clock.cpp src/engine/clock/Clock.h
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
        src/sdl/SdlInputContext_transform_sdl_key_code.cpp src/sdl/SdlInputContext_transform_sdl_key_code.h
        src/utils/sys/abort_handlers.cpp src/utils/sys/abort_handlers.h
        )

add_executable(TopDown ${SOURCE_FILES})
target_link_libraries(TopDown
        ${SDL2_LIBRARY}
        ${SDL2_IMAGE_LIBRARIES}
        ${SDL2_MIXER_LIBRARIES})
