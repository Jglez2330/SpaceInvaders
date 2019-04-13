cmake_minimum_required(VERSION 3.12)
project(SpaceInvaders C)

set(CMAKE_C_STANDARD 11)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/CMAKE")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake")


find_package(SDL2 REQUIRED)

add_executable(SpaceInvaders main.c invader.c invader.h linkedList.c linkedList.h InvaderHandler.h InvaderHandler.c misil.c misil.h nave.c nave.h bunker.c bunker.h)

include_directories(${SDL2_INCLUDE_DIR} ${SDL2TTF_INCLUDE_DIR} ${SDL2_IMAGE_INCLUDE_DIR} ${SDL2Mixer_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARY} ${SDL2TTF_LIBRARY} ${SDL2_IMAGE_LIBRARY} ${SDL2Mixer_LIBRARY})


