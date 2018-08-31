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
        src/utils/math/maths.cpp src/utils/math/maths.h
        src/game/state/StateIntro.cpp src/game/state/StateIntro.h
        src/game/state/StateMoon.cpp src/game/state/StateMoon.h src/game/state/StateMoon_parse_level_data.cpp
        src/game/state/GameState.h
        src/engine/resources/Sound.cpp src/engine/resources/Sound.h
        src/engine/resources/Music.cpp src/engine/resources/Music.h
        src/engine/resources/Texture.cpp src/engine/resources/Texture.h
        src/engine/graphic/GraphicContext.cpp src/engine/graphic/GraphicContext.h
        src/engine/DefaultEngine.cpp src/engine/DefaultEngine.h src/engine/DefaultEngine_load_resources.cpp
        src/game/object/GameObject.cpp src/game/object/GameObject.h
        src/game/object/Damageable.h src/game/object/Damageable.cpp
        src/game/object/Player.cpp src/game/object/Player.h
        src/game/object/Werewolf.cpp src/game/object/Werewolf.h
        src/game/object/Zombie.cpp src/game/object/Zombie.h
        src/game/object/WeaponBuilder.cpp src/game/object/WeaponBuilder.h
        src/game/object/Weapon.h src/game/object/Weapon.cpp
        src/game/object/Bullet.cpp src/game/object/Bullet.h
        src/engine/resources/Resources.cpp src/engine/resources/Resources.h
        src/engine/StateId.h
        src/engine/graphic/shape/Circle.cpp src/engine/graphic/shape/Circle.h
        src/utils/json/get_value.h src/utils/json/get_value.cpp
        src/engine/Random.cpp src/engine/Random.h
        src/utils/demangle_type_name.cpp src/utils/demangle_type_name.h
        src/engine/Engine.cpp src/engine/Engine.h
        src/engine/sdl/SdlInputContext.cpp src/engine/sdl/SdlInputContext.h
        src/utils/random/Mt19937Random.h src/utils/random/Mt19937Random.cpp
        src/engine/sdl/SdlGraphicContext.cpp src/engine/sdl/SdlGraphicContext.h
        src/engine/sdl/SdlResources.cpp src/engine/sdl/SdlResources.h
        src/engine/sdl/SdlTexture.cpp src/engine/sdl/SdlTexture.h
        src/engine/ContextInjector.cpp src/engine/ContextInjector.h
        src/engine/sdl/SdlContextInjector.cpp src/engine/sdl/SdlContextInjector.h
        src/engine/graphic/shape/Box.cpp src/engine/graphic/shape/Box.h
        src/engine/graphic/shape/Color.cpp src/engine/graphic/shape/Color.h
        src/utils/file/read_file_to_string.cpp src/utils/file/read_file_to_string.h
        src/utils/json/parse_json.cpp src/utils/json/parse_json.h
        src/engine/AudioContext.cpp src/engine/AudioContext.h
        src/engine/sdl/SdlAudioContext.cpp src/engine/sdl/SdlAudioContext.h
        src/engine/sdl/SdlSound.cpp src/engine/sdl/SdlSound.h
        src/engine/sdl/SdlMusic.cpp src/engine/sdl/SdlMusic.h
        src/engine/Timer.cpp src/engine/Timer.h
        src/engine/Clock.cpp src/engine/Clock.h
        src/engine/sdl/SdlClock.cpp src/engine/sdl/SdlClock.h
        src/engine/input/InputContext.cpp src/engine/input/InputContext.h
        src/engine/input/WindowEventHandler.cpp src/engine/input/WindowEventHandler.h
        src/engine/input/KeyboardEventHandler.cpp src/engine/input/KeyboardEventHandler.h
        src/engine/input/MouseEventHandler.cpp src/engine/input/MouseEventHandler.h
        src/engine/input/EventHandler.h
        src/engine/input/WindowEvent.h src/engine/input/WindowEvent.cpp
        src/engine/input/KeyboardEvent.cpp src/engine/input/KeyboardEvent.h
        src/game/state/GameState.cpp src/engine/input/MouseEvent.cpp
        src/engine/input/MouseEvent.h src/engine/input/KeyboardKey.h
        src/engine/sdl/SdlInputContext_transform_sdl_key_code.cpp src/engine/sdl/SdlInputContext_transform_sdl_key_code.h
        src/utils/abort_handlers.cpp src/utils/abort_handlers.h
        )

add_executable(TopDown ${SOURCE_FILES})
target_link_libraries(TopDown
        ${SDL2_LIBRARY}
        ${SDL2_IMAGE_LIBRARIES}
        ${SDL2_MIXER_LIBRARIES})
