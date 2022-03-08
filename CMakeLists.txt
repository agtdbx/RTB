cmake_minimum_required(VERSION 3.21)
project(RTB)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")

add_executable(RTB src/main.cpp src/Menu.cpp include/Menu.h src/Functions.cpp include/Functions.h src/Button.cpp include/Button.h src/Game.cpp include/Game.h src/Select.cpp include/Select.h src/Switch.cpp include/Switch.h src/Personnage.cpp include/Personnage.h src/Map.cpp include/Map.h src/Tuile.cpp include/Tuile.h src/Camera.cpp include/Camera.h)

INCLUDE_DIRECTORIES(/usr/local)

INCLUDE(FindPkgConfig)

PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
PKG_SEARCH_MODULE(SDL2TTF REQUIRED SDL2_ttf>=2.0.0)
PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)
PKG_SEARCH_MODULE(SDL2MIXER REQUIRED SDL2_mixer>=2.0.0)

INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIRS} ${SDL2TTF_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS} ${SDL2MIXER_INCLUDE_DIRS})
TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${SDL2_LIBRARIES} ${SDL2TTF_LIBRARIES} ${SDL2IMAGE_LIBRARIES} ${SDL2MIXER_LIBRARIES} jsoncpp)