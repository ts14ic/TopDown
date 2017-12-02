cmake_minimum_required(VERSION 3.9)
project(TopDown)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_mixer REQUIRED)
include_directories(${SDL2_INCLUDE_DIR} ${SDL2_IMAGE_INCLUDE_DIRS} ${SDL2_MIXER_INCLUDE_DIRS})

set(SOURCE_FILES
        Bullet.cpp
        calculations.cpp
        calculations.h
        GameObject.cpp
        GameObject.h
        GameState.cpp
        GameState.h
        main.cpp
        Player.cpp
        sdlwrap.cpp
        sdlwrap.h
        Sound.cpp
        Sound.h
        StateIntro.cpp
        StateMoon.cpp
        StopWatch.cpp
        StopWatch.h
        Texture.cpp
        Texture.h
        Weapon.cpp
        Werewolf.cpp
        Zombie.cpp)

add_executable(TopDown ${SOURCE_FILES})
target_link_libraries(TopDown ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARIES} ${SDL2_MIXER_LIBRARIES})

